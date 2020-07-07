#include "driverlib.h"
#include "hdc2010.h"
#include "sample.h"
#include "comms_uart.h"
#include "confignfc.h"
#include "nt3h.h"
#include "stat.h"
#include "defs.h"
#include <stdlib.h>

#define SLAVE_ADDRESS 0x5F

volatile uint8_t receiveData;
volatile int whoami;

//*****************************************************************************
//
//Specify Expected Receive data count.
//
//*****************************************************************************
#define RXCOUNT 0x05

//*****************************************************************************
//
//Target frequency for SMCLK in kHz
//
//*****************************************************************************
#define CS_SMCLK_DESIRED_FREQUENCY_IN_KHZ   16000

//*****************************************************************************
//
//SMCLK/FLLRef Ratio
//
//*****************************************************************************
#define CS_SMCLK_FLLREF_RATIO   30

#define LED_PORT    GPIO_PORT_P3
#define LED_PIN     GPIO_PIN2

#define CS_XT1_CRYSTAL_FREQUENCY 32768
#define CS_XT1_TIMEOUT 65000

#define CP10MS 41 // Counts per 10 millisecond at ACLK = 32768 kHz and 8 divider.

#define EXIT_STATE sc_error
#define ENTRY_STATE sc_init

volatile int rtcFlag = 0;
volatile int timerFlag = 0;
volatile int hdcFlag = 0;

typedef enum state_codes {
    sc_init,
    sc_init_reqsyson,
    sc_init_waitsyson,
    sc_init_ntagandfd,
    sc_init_nfccheck,
    sc_init_serialcheck,
    sc_init_errorcheck,
    sc_init_rtc,
    sc_smpl_checkcounter,
    sc_smpl_hdcreq,
    sc_smpl_hdcwait,
    sc_smpl_hdcread,
    sc_smpl_wait,
    sc_rtc_reqsyson,
    sc_rtc_waitsyson,
    sc_end,
    sc_error 
} tstate;

typedef enum ret_codes { 
    tr_ok, 
    tr_hdcreq,
    tr_updatemin,
    tr_fail,
    tr_timeout,
    tr_wait
} tretcode;

typedef enum event_codes {
    evt_none,
    evt_rtc,
    evt_timerfinished,
    evt_hdcint
} tevent;

// https://stackoverflow.com/questions/1371460/state-machines-tutorials
tretcode init_state(tevent);
tretcode init_reqsyson(tevent);
tretcode init_waitsyson(tevent);
tretcode init_ntag(tevent);
tretcode init_nfccheck(tevent);
tretcode init_serialcheck(tevent);
tretcode init_errorcheck(tevent);
tretcode init_rtc(tevent);
tretcode smpl_checkcounter(tevent);
tretcode smpl_hdcreq(tevent);
tretcode smpl_hdcwait(tevent);
tretcode smpl_hdcread(tevent);
tretcode smpl_wait(tevent);
tretcode rtc_reqsyson(tevent);
tretcode rtc_waitsyson(tevent);
tretcode end_state(tevent);
tretcode error_state(tevent);

/* array and enum below must be in sync! */
tretcode (* state_fcns[])(tevent) = {
                          init_state,
                          init_reqsyson,
                          init_waitsyson,
                          init_ntag,
                          init_nfccheck,
                          init_serialcheck,
                          init_errorcheck,
                          init_rtc,
                          smpl_checkcounter,
                          smpl_hdcreq,
                          smpl_hdcwait,
                          smpl_hdcread,
                          smpl_wait,
                          rtc_reqsyson,
                          rtc_waitsyson,
                          end_state,
                          error_state
};


struct transition {
    tstate      src_state;
    tretcode    ret_code;
    tstate      dst_state;
};

struct transition state_transitions[] = {
                                         {sc_init,          tr_ok,      sc_init_reqsyson},

                                         {sc_init_reqsyson, tr_ok,      sc_init_waitsyson},

                                         {sc_init_waitsyson, tr_ok,      sc_init_ntagandfd},
                                         {sc_init_waitsyson, tr_wait,    sc_init_waitsyson},

                                         {sc_init_ntagandfd, tr_ok,     sc_init_nfccheck},

                                         {sc_init_nfccheck, tr_ok,     sc_init_serialcheck},

                                         {sc_init_serialcheck,  tr_ok,      sc_init_errorcheck},
                                         {sc_init_serialcheck,  tr_fail,    sc_init_serialcheck},
                                         {sc_init_serialcheck,  tr_wait,    sc_init_serialcheck}, // Wait for serial number to be RXed.

                                         {sc_init_errorcheck,  tr_ok,      sc_init_rtc},
                                         {sc_init_errorcheck,  tr_fail,      sc_end},

                                         {sc_init_rtc,      tr_ok,      sc_smpl_checkcounter}, // sc_smpl_checkcounter

                                         {sc_smpl_hdcreq,   tr_ok,      sc_smpl_hdcwait},

                                         {sc_smpl_hdcwait,  tr_ok,      sc_smpl_hdcread},
                                         {sc_smpl_hdcwait,  tr_wait,    sc_smpl_hdcwait},

                                         {sc_smpl_hdcread,  tr_ok,      sc_smpl_wait}, // sc_smpl_wait
                                         {sc_smpl_hdcread,  tr_fail,    sc_error},

                                         {sc_smpl_wait,     tr_timeout,     sc_rtc_reqsyson},
                                         {sc_smpl_wait,     tr_wait,        sc_smpl_wait},

                                         {sc_rtc_reqsyson,  tr_ok,      sc_rtc_waitsyson},

                                         {sc_smpl_checkcounter, tr_hdcreq,      sc_smpl_hdcreq},
                                         {sc_smpl_checkcounter, tr_updatemin,   sc_smpl_wait},

                                         {sc_rtc_waitsyson, tr_ok, sc_smpl_checkcounter},
                                         {sc_rtc_waitsyson, tr_wait,   sc_rtc_waitsyson}
                                         
};

/* Look up transitions from the table for a current state and given return code. */
tstate lookup_transitions(tstate curstate, tretcode rc)
{
    tstate nextstate = sc_error;
    int i=0;

    for (i=0; i<sizeof(state_transitions)/sizeof(state_transitions[0]); i++)
    {
        if ((state_transitions[i].src_state == curstate) && (state_transitions[i].ret_code == rc))
        {
            nextstate = state_transitions[i].dst_state;
            break;
        }
    }

    if (nextstate == sc_error)
    {
        while(1);
    }

    return nextstate;
}

static void wdog_kick()
{
    WDTCTL = WDTPW | WDTSSEL__ACLK | WDTCNTCL | WDTIS__8192K;
}

static void start_timer(unsigned int intervalCycles)
{
    // Start timer in continuous mode sourced by SMCLK
        Timer_B_initContinuousModeParam initContParam = {0};
        initContParam.clockSource = TIMER_B_CLOCKSOURCE_ACLK;
        initContParam.clockSourceDivider = TIMER_B_CLOCKSOURCE_DIVIDER_8;
        initContParam.timerInterruptEnable_TBIE = TIMER_B_TBIE_INTERRUPT_DISABLE;
        initContParam.timerClear = TIMER_B_DO_CLEAR;
        initContParam.startTimer = false;
        Timer_B_initContinuousMode(TB1_BASE, &initContParam);

        //Initialise compare mode
        Timer_B_clearCaptureCompareInterrupt(TB1_BASE, TIMER_B_CAPTURECOMPARE_REGISTER_0);

        Timer_B_initCompareModeParam initCompParam = {0};
        initCompParam.compareRegister = TIMER_B_CAPTURECOMPARE_REGISTER_0;
        initCompParam.compareInterruptEnable = TIMER_B_CAPTURECOMPARE_INTERRUPT_ENABLE;
        initCompParam.compareOutputMode = TIMER_B_OUTPUTMODE_OUTBITVALUE;
        initCompParam.compareValue = intervalCycles;
        Timer_B_initCompareMode(TB1_BASE, &initCompParam);

        Timer_B_startCounter(TB1_BASE, TIMER_B_CONTINUOUS_MODE);
}

static void syson()
{
    // Configure I/O pins

    // P3.5 nPRG as input
    GPIO_setAsInputPin(
            GPIO_PORT_P3,
            GPIO_PIN5
    );

    // P1.6 UART RX as input
    GPIO_setAsInputPin(
            GPIO_PORT_P1,
            GPIO_PIN6
    );

    // P4.3 HDC_INT as input
    GPIO_setAsInputPin(
            GPIO_PORT_P4,
            GPIO_PIN3
    );

    // P4.2 EN as output high
    GPIO_setAsOutputPin(
            GPIO_PORT_P4,
            GPIO_PIN2
    );


    GPIO_setOutputHighOnPin(
            GPIO_PORT_P4,
            GPIO_PIN2
    );

    start_timer(2*CP10MS);
}

static void sysoff()
{
    GPIO_setOutputLowOnPin(
            GPIO_PORT_P4,
            GPIO_PIN2
    );
}

// sensorinit -> SYSON. FDint OFF. RTCint OFF.
// waitforserial -> SYSOFF. FDint ON. RTCint OFF.
// reqsensor -> SYSON. FDint ON. HDCint ON. RTCint OFF.
// updateurl -> SYSON. FDint ON. RTCint OFF.
// updatesc -> SYSON. FDint OFF. RTCint ON. wait a few seconds before leaving this state as hysteresis.
// waitrtc -> SYSOFF. FDint ON. RTCint ON.

tretcode init_state(tevent evt)
{
    int error;

    WDTCTL = WDTPW | WDTHOLD;               // Stop WDT
    PMM_disableSVSH(); // Disable Supply Voltage Supervisor.

    //Set wait state to 1
    FRAMCtl_configureWaitStateControl(FRAMCTL_ACCESS_TIME_CYCLES_1);

    // Initialise IO to reduce power.
    // P1.2 FD as input
    // P1.1 UART RX as input
    // P4.2 HDC_INT as input
    // P2.7 EN as output low
    P1DIR = 0x3F; P2DIR = 0x3F; P3DIR = 0xDF; P4DIR = 0x00;
    P5DIR = 0xFF; P6DIR = 0xFF; P7DIR = 0xFF; P8DIR = 0xFF;
    P1OUT = 0x00; P2OUT = 0x00; P3OUT = 0x00; P4OUT = 0x00;
    P5OUT = 0x00; P6OUT = 0x00; P7OUT = 0x00; P8OUT = 0x00;

    P2SEL1 |= BIT6 | BIT7;                  // P2.6~P2.7: crystal pins

    // Disable the GPIO power-on default high-impedance mode
    // to activate previously configured port settings
    PM5CTL0 &= ~LOCKLPM5;

    // Read the reset cause.
    stat_rdrstcause();

    //Initializes the XT1 and XT2 crystal frequencies being used
    CS_setExternalClockSource(CS_XT1_CRYSTAL_FREQUENCY);

    //Initialize XT1. Returns STATUS_SUCCESS if initializes successfully
    error = CS_turnOnXT1LFWithTimeout(CS_XT1_DRIVE_0, CS_XT1_TIMEOUT);

    if (error == STATUS_FAIL)
    {
        stat_setclockfailure();
    }

    CS_initClockSignal(
            CS_ACLK,
            CS_XT1CLK_SELECT,
            CS_CLOCK_DIVIDER_1
    );

    //Set DCO FLL reference = REFO
    CS_initClockSignal(
            CS_FLLREF,
            CS_XT1CLK_SELECT,
            CS_CLOCK_DIVIDER_1
    );

    //Set Ratio and Desired MCLK Frequency  and initialize DCO
    error = CS_initFLLSettle(
                CS_SMCLK_DESIRED_FREQUENCY_IN_KHZ,
                487
    );

    if (error == STATUS_FAIL)
    {
        stat_setclockfailure();
    }

    //
    //Set SMCLK = DCO with frequency divider of 1
    CS_initClockSignal(
            CS_SMCLK,
            CS_DCOCLKDIV_SELECT,
            CS_CLOCK_DIVIDER_1
    );
    //
    //Set MCLK = DCO with frequency divider of 1
    CS_initClockSignal(
            CS_MCLK,
            CS_DCOCLKDIV_SELECT,
            CS_CLOCK_DIVIDER_1
    );

    // Enable watchdog timer.
    wdog_kick();


    return tr_ok;
}

static tretcode reqsyson(tevent evt)
{
    /* Power up the I2C bus. */
    syson();

    return tr_ok;
}

static tretcode waitsyson(tevent evt)
{
    tretcode rc = tr_wait;

    if (evt == evt_timerfinished)
    {
        /* SYS is up. Initialise I2C. */
        i2c_init();

        rc = tr_ok;
    }

    return rc;
}

tretcode init_reqsyson(tevent evt)
{
    return reqsyson(evt);
}

tretcode init_waitsyson(tevent evt)
{
    return waitsyson(evt);
}

tretcode init_ntag(tevent evt)
{
    /* Initialise the NTAG. */
    nt3h_init();

    /* Read the whoami registers of both the NT3H and the HDC2010. */
    return tr_ok;
}

tretcode init_nfccheck(tevent evt)
{
    // Checks for an NFC text record.
    tretcode rc;

    // Read from the NFC tag.
    if (confignfc_check())
    {
        confignfc_readtext();
    }

    rc = tr_ok;

    return rc;
}

tretcode init_serialcheck(tevent evt)
{
    tretcode rc;
    int nPRG;
    t_ustat uartstatus;

    // Kick the watchdog.
    wdog_kick();

    // Read the nPRG pin
    nPRG = GPIO_getInputPinValue(GPIO_PORT_P3, GPIO_PIN5);

    uartstatus = uart_run(nPRG);

    // Continue if serial present and nPRG de-asserted.
    if (uartstatus == ustat_running)
    {
        rc = tr_fail;
    }
    else if (uartstatus == ustat_waiting)
    {
        rc = tr_wait;
    }
    else
    {
        rc = tr_ok;
    }

    return rc;
}

tretcode init_errorcheck(tevent evt)
{
    tretcode rc;
    bool err = false;
    unsigned int status;
    int resetsalltime, resetsperloop;

    nvparams_incrcounters(); // Increment reset counter.
    resetsalltime = nvparams_getresetsalltime();
    resetsperloop = nvparams_getresetsperloop();

    // Check for low battery here.
    status = stat_get(&err, resetsalltime);

    // Safety feature to prevent wearing out the EEPROM after repeated resets.
    if (resetsperloop < 50)
    {
        wdog_kick();
        enc_init(status, err);
    }

    // Go to LPM4 in the event of an error.
    if (err == false)
    {
        nvparams_cresetsperloop();
        rc = tr_ok;
    }
    else
    {
        rc = tr_fail;
    }

    return rc;
}

tretcode init_rtc(tevent evt)
{
    // Enable Supply voltage supervisor
    PMM_enableSVSH();

    // Configure RTC
    // Interrupt and reset happen every 1024/32768 * 32 = 1 sec.
    RTCMOD = 1920-1;
    RTCCTL = RTCSS__XT1CLK | RTCSR |RTCPS__1024;
    RTCCTL |= RTCIE;

    return tr_ok;
}

tretcode error_state(tevent evt)
{
    return tr_wait;
}

tretcode smpl_hdcreq(tevent evt)
{
    /* Enable HDCint P4.2 rising edge interrupt. */
    P4IFG &= ~BIT3; // Clear flag.
    P4IES |= BIT3 ; // Falling edge detect.
    P4IE |= BIT3 ; // Allow interrupt.

    hdc2010_startconv();

    return tr_ok;
}

tretcode smpl_hdcwait(tevent evt)
{
    tretcode rc = tr_wait;

    if (evt == evt_hdcint)
    {
        rc = tr_ok;
    }

    return rc;
}

tretcode smpl_hdcread(tevent evt)
{
    int temp, rh;

    /* Disable HDCint P4.3 rising edge interrupt. */
    P4IE &= ~BIT3 ; // Disable interrupt on port 2 bit 3.

    // If event shows HDC interrupt read the temperature, otherwise tr_wait.
    hdc2010_read_temp(&temp, &rh);

    if (enc_pushsample(temp, rh) > 0)
    {
        // Looping around
        nvparams_cresetsperloop();
    }

    /* Power down the I2C bus. */
    sysoff();

    return tr_ok;
}



tretcode smpl_wait(tevent evt)
{
    tretcode rc;

    // Kick the watchdog.
    wdog_kick();

    if (evt == evt_rtc)
    {
        rc = tr_timeout;
    }
    else
    {
        rc = tr_wait;
    }

    return rc;
}

tretcode smpl_checkcounter(tevent evt)
{
    tretcode rc = tr_fail;
    static int minutecounter = 0;

    if (minutecounter == 0)
    {
        rc = tr_hdcreq;
    }
    else
    {
        rc = tr_updatemin;
        enc_setelapsed(minutecounter);
        // Check for a configuration text record.
        if (confignfc_check())
        {
            PMMCTL0 = PMMPW | PMMSWPOR; // Reset if a text record has been found.
        }

        /* Power down peripherals on the I2C bus. */
        sysoff();
    }

    if (minutecounter < nvparams_getsmplintmins()-1)
    {
        minutecounter++;
    }
    else
    {
        minutecounter = 0;
    }

    return rc;
}

tretcode rtc_reqsyson(tevent evt)
{
    return reqsyson(evt);
}

tretcode rtc_waitsyson(tevent evt)
{
    return waitsyson(evt);
}

tretcode end_state(tevent evt)
{
    // Turn peripheral power off.
    sysoff();
    /* Disable HDCint P4.2 rising edge interrupt. */
    P4IE = 0 ; // Disable interrupt on port 2 bit 3.
    // Go to deep sleep mode.
    WDTCTL = WDTPW | WDTHOLD;        // Hold the watchdog.
    PMMCTL0_H = PMMPW_H;                // Open PMM Registers for write
    PMMCTL0_L &= ~(SVSHE);              // Disable high-side SVS
    PMMCTL0_L |= PMMREGOFF;             // and set PMMREGOFF
    PMMCTL0_H = 0;                      // Lock PMM Registers
    TB0CTL = MC_0;                   //turn off timer A
    TB1CTL = MC_0;                   //turn off timer A
    RTCCTL = 0;                      // Stop the RTC.
    __delay_cycles(10000);
    // Deep sleep.
    __bis_SR_register(LPM4_bits | GIE);
}



void main(void)
{
    volatile int error;
    tstate cur_state = ENTRY_STATE;
    tretcode rc;
    tretcode (* state_fun)(tevent);
    tevent evt;

    while (1) {
        // Process events
        if (rtcFlag)
        {
            rtcFlag = 0;
            evt = evt_rtc;
        }
        else if (timerFlag)
        {
            timerFlag = 0;
            evt = evt_timerfinished;
        }
        else if (hdcFlag)
        {
            hdcFlag = 0;
            evt = evt_hdcint;
        }
        else
        {
            evt = evt_none;
        }

        state_fun = state_fcns[cur_state];
        rc = state_fun(evt);
        if (rc == tr_wait)
        {
            // Sleep whilst waiting for an event
            __bis_SR_register(LPM3_bits + GIE);
        }
        cur_state = lookup_transitions(cur_state, rc);
        if (EXIT_STATE == cur_state)
            break;

    }

}

//******************************************************************************
//
//This is the TIMER1_A3 interrupt vector service routine.
//
//******************************************************************************
#if defined(__TI_COMPILER_VERSION__) || defined(__IAR_SYSTEMS_ICC__)
#pragma vector=TIMER1_B0_VECTOR
__interrupt
#elif defined(__GNUC__)
__attribute__((interrupt(TIMER1_A0_VECTOR)))
#endif
void TIMER1_B0_ISR(void)
{
    Timer_B_stop(TB1_BASE);
    Timer_B_disableInterrupt(TB1_BASE);
    timerFlag = 1;
    __bic_SR_register_on_exit(LPM3_bits); // Clear LPM bits upon ISR Exit
}


//******************************************************************************
//
//This is the PORT_2 interrupt vector service routine.
//
//******************************************************************************
#if defined(__TI_COMPILER_VERSION__) || defined(__IAR_SYSTEMS_ICC__)
#pragma vector=PORT4_VECTOR
__interrupt void Port_4(void)
#elif defined(__GNUC__)
void __attribute__ ((interrupt(PORT2_VECTOR))) Port_2 (void)
#else
#error Compiler not supported!
#endif
{
  P4IFG &= ~BIT3;                           // P2.3 IFG cleared
  if ((P4IN & BIT3) == 0)
  {
      // P4.3 is low.
      hdcFlag = 1;
      __bic_SR_register_on_exit(LPM3_bits);     // Clear LPM bits upon ISR Exit
  }
}

#if defined(__TI_COMPILER_VERSION__) || defined(__IAR_SYSTEMS_ICC__)
#pragma vector = RTC_VECTOR
__interrupt void RTC_ISR(void)
#elif defined(__GNUC__)
void __attribute__ ((interrupt(RTC_VECTOR))) RTC_ISR (void)
#else
#error Compiler not supported!
#endif
{
    switch(__even_in_range(RTCIV, RTCIV_RTCIF))
    {
        case RTCIV_NONE : break;            // No interrupt pending
        case RTCIV_RTCIF:                   // RTC Overflow
            rtcFlag = 1;
            __bic_SR_register_on_exit(LPM3_bits); // Clear LPM bits upon ISR Exit
            break;
        default:          break;
    }
}
