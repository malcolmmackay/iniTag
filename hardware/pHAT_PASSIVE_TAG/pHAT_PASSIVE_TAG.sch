EESchema Schematic File Version 4
EELAYER 30 0
EELAYER END
$Descr A4 11693 8268
encoding utf-8
Sheet 1 1
Title "pHAT PASSIVE TAG"
Date "2021-10-19"
Rev "1"
Comp "COPYRIGHT Plotsensor Ltd. 2021"
Comment1 "Licenced under CERN OHL-v2-S"
Comment2 "https://github.com/malcolmmackay/pHAT_PASSIVE_TAG"
Comment3 ""
Comment4 ""
$EndDescr
$Comp
L Connector-ML:RPi_GPIO J2
U 1 1 5516AE26
P 7250 2800
F 0 "J2" H 8000 3050 60  0000 C CNN
F 1 "RPi_GPIO" H 8000 2950 60  0000 C CNN
F 2 "Connector_PinSocket_2.54mm:PinSocket_2x20_P2.54mm_Vertical" H 7250 2800 60  0001 C CNN
F 3 "" H 7250 2800 60  0000 C CNN
F 4 "BOOMELE" H 7250 2800 50  0001 C CNN "MANF"
F 5 "C50982" H 7250 2800 50  0001 C CNN "MANF#"
F 6 "LCSC" H 7250 2800 50  0001 C CNN "SUPPLIER"
F 7 "C50982" H 7250 2800 50  0001 C CNN "SUPPLIER#"
	1    7250 2800
	1    0    0    -1  
$EndComp
Text Notes 7250 5050 0    100  Italic 0
Thru-Hole Connector
$Comp
L power:GND #PWR05
U 1 1 5CB4EC50
P 6600 3250
F 0 "#PWR05" H 6600 3000 50  0001 C CNN
F 1 "GND" H 6605 3077 50  0000 C CNN
F 2 "" H 6600 3250 50  0000 C CNN
F 3 "" H 6600 3250 50  0000 C CNN
	1    6600 3250
	1    0    0    -1  
$EndComp
$Comp
L power:GND #PWR08
U 1 1 5CB4EC7F
P 9150 3050
F 0 "#PWR08" H 9150 2800 50  0001 C CNN
F 1 "GND" H 9155 2877 50  0000 C CNN
F 2 "" H 9150 3050 50  0000 C CNN
F 3 "" H 9150 3050 50  0000 C CNN
	1    9150 3050
	1    0    0    -1  
$EndComp
Wire Wire Line
	8950 3000 9150 3000
Wire Wire Line
	9150 3000 9150 3050
Wire Wire Line
	7050 3200 6600 3200
Wire Wire Line
	6600 3200 6600 3250
$Comp
L power:+3V3 #PWR01
U 1 1 5CB4FFA4
P 4500 2000
F 0 "#PWR01" H 4500 1850 50  0001 C CNN
F 1 "+3V3" H 4515 2173 50  0000 C CNN
F 2 "" H 4500 2000 50  0000 C CNN
F 3 "" H 4500 2000 50  0000 C CNN
	1    4500 2000
	1    0    0    -1  
$EndComp
$Comp
L power:+3V3 #PWR04
U 1 1 5CB4FFF4
P 6950 2650
F 0 "#PWR04" H 6950 2500 50  0001 C CNN
F 1 "+3V3" H 6965 2823 50  0000 C CNN
F 2 "" H 6950 2650 50  0000 C CNN
F 3 "" H 6950 2650 50  0000 C CNN
	1    6950 2650
	1    0    0    -1  
$EndComp
$Comp
L power:GND #PWR0101
U 1 1 5CB5DE9C
P 5000 3950
F 0 "#PWR0101" H 5000 3700 50  0001 C CNN
F 1 "GND" H 5005 3777 50  0000 C CNN
F 2 "" H 5000 3950 50  0000 C CNN
F 3 "" H 5000 3950 50  0000 C CNN
	1    5000 3950
	1    0    0    -1  
$EndComp
$Comp
L Device:C C2
U 1 1 5CB79642
P 3600 2650
F 0 "C2" H 3715 2696 50  0000 L CNN
F 1 "0P" H 3715 2605 50  0000 L CNN
F 2 "Capacitors_SMD:C_0603" H 3638 2500 50  0001 C CNN
F 3 "http://www.farnell.com/datasheets/1731432.pdf?_ga=2.28182204.1044651491.1556565859-289093737.1544555023&_gac=1.19854794.1555367884.Cj0KCQjw19DlBRCSARIsAOnfRei64FcwOFGwHccevtvnCF1_gtAlQkzaoKMfBkZYkqlx40vjUC8V3ZkaAmTjEALw_wcB" H 3600 2650 50  0001 C CNN
F 4 "JOHANSON" H 3600 2650 50  0001 C CNN "MANF"
F 5 "251R14S3R9CV4T" H 3600 2650 50  0001 C CNN "MANF#"
F 6 "FARNELL" H 3600 2650 50  0001 C CNN "SUPPLIER"
F 7 "1885381" H 3600 2650 50  0001 C CNN "SUPPLIER#"
F 8 "NF" H 3600 2550 50  0000 L CNN "FIT"
	1    3600 2650
	1    0    0    -1  
$EndComp
$Comp
L power:GND #PWR02
U 1 1 5CB7B973
P 4500 3350
F 0 "#PWR02" H 4500 3100 50  0001 C CNN
F 1 "GND" H 4505 3177 50  0000 C CNN
F 2 "" H 4500 3350 50  0000 C CNN
F 3 "" H 4500 3350 50  0000 C CNN
	1    4500 3350
	1    0    0    -1  
$EndComp
$Comp
L Device:C C3
U 1 1 5CB89FF2
P 5000 3700
F 0 "C3" H 5115 3746 50  0000 L CNN
F 1 "100N" H 5115 3655 50  0000 L CNN
F 2 "Capacitors_SMD:C_0603" H 5038 3550 50  0001 C CNN
F 3 "http://www.farnell.com/datasheets/2244871.pdf?_ga=2.95289884.1044651491.1556565859-289093737.1544555023&_gac=1.26614863.1555367884.Cj0KCQjw19DlBRCSARIsAOnfRei64FcwOFGwHccevtvnCF1_gtAlQkzaoKMfBkZYkqlx40vjUC8V3ZkaAmTjEALw_wcB" H 5000 3700 50  0001 C CNN
F 4 "VISHAY" H 5000 3700 50  0001 C CNN "MANF"
F 5 "VJ0603Y104KXACW1BC" H 5000 3700 50  0001 C CNN "MANF#"
F 6 "FARNELL" H 5000 3700 50  0001 C CNN "SUPPLIER"
F 7 "2407338" H 5000 3700 50  0001 C CNN "SUPPLIER#"
	1    5000 3700
	1    0    0    -1  
$EndComp
$Comp
L Device:C C4
U 1 1 5CB8A02F
P 5450 3700
F 0 "C4" H 5565 3746 50  0000 L CNN
F 1 "1U" H 5565 3655 50  0000 L CNN
F 2 "Capacitors_SMD:C_0603" H 5488 3550 50  0001 C CNN
F 3 "http://www.farnell.com/datasheets/2237828.pdf?_ga=2.64948655.1044651491.1556565859-289093737.1544555023&_gac=1.263000574.1555367884.Cj0KCQjw19DlBRCSARIsAOnfRei64FcwOFGwHccevtvnCF1_gtAlQkzaoKMfBkZYkqlx40vjUC8V3ZkaAmTjEALw_wcB" H 5450 3700 50  0001 C CNN
F 4 "AVX" H 5450 3700 50  0001 C CNN "MANF"
F 5 "0603YD105MAT2A" H 5450 3700 50  0001 C CNN "MANF#"
F 6 "FARNELL" H 5450 3700 50  0001 C CNN "SUPPLIER"
F 7 "2332677" H 5450 3700 50  0001 C CNN "SUPPLIER#"
	1    5450 3700
	1    0    0    -1  
$EndComp
Wire Wire Line
	7050 2800 6950 2800
Wire Wire Line
	6950 2650 6950 2800
$Comp
L CUPL:NT3H2111 U1
U 1 1 616B5582
P 4500 2700
F 0 "U1" H 4150 3150 60  0000 C CNN
F 1 "NT3H2111" H 4800 2350 60  0000 C CNN
F 2 "Package_SO:SO-8_3.9x4.9mm_P1.27mm" H 5750 1750 60  0001 C CNN
F 3 "https://www.nxp.com/docs/en/data-sheet/NT3H2111_2211.pdf" H 4650 2250 60  0001 L CNN
F 4 "NXP" H 4650 2150 60  0001 L CNN "MANF"
F 5 "NT3H2111W0FT1" H 4650 2050 60  0001 L CNN "MANF#"
F 6 "DIGIKEY" H 4650 1950 60  0001 L CNN "SUPPLIER"
F 7 "568-12904-1-ND" H 4650 1850 60  0001 L CNN "SUPPLIER#"
	1    4500 2700
	1    0    0    -1  
$EndComp
$Comp
L Device:Antenna_Loop AE1
U 1 1 616BA367
P 2450 2600
F 0 "AE1" V 2183 2568 50  0000 C CNN
F 1 "Antenna_Loop" V 2274 2568 50  0000 C CNN
F 2 "CUPL:Class_6_NXP_7loop_150u_OUTSIDE" H 2450 2600 50  0001 C CNN
F 3 "~" H 2450 2600 50  0001 C CNN
	1    2450 2600
	0    -1   1    0   
$EndComp
Wire Wire Line
	4500 2000 4500 2100
Wire Wire Line
	4500 3200 4500 3350
Wire Wire Line
	2900 2600 2900 2400
Wire Wire Line
	2900 2700 2900 2900
Wire Wire Line
	3200 2500 3200 2400
Wire Wire Line
	3600 2500 3600 2400
Wire Wire Line
	3200 2800 3200 2900
Wire Wire Line
	3600 2800 3600 2900
Wire Wire Line
	2650 2600 2900 2600
Wire Wire Line
	2650 2700 2900 2700
Connection ~ 3200 2400
Connection ~ 3200 2900
Connection ~ 3600 2400
Wire Wire Line
	3600 2400 3900 2400
Connection ~ 3600 2900
Wire Wire Line
	3600 2900 3900 2900
Wire Wire Line
	2900 2400 3200 2400
Wire Wire Line
	2900 2900 3200 2900
Wire Wire Line
	3200 2400 3600 2400
Wire Wire Line
	3200 2900 3600 2900
Wire Wire Line
	5100 2900 6550 2900
Text Label 5200 2700 0    50   ~ 0
FD
NoConn ~ 5100 2450
Text Label 5200 2800 0    50   ~ 0
SCL
Text Label 6850 3000 0    50   ~ 0
SCL
Wire Wire Line
	7050 3100 6800 3100
Text Label 6850 3100 0    50   ~ 0
FD
$Comp
L power:GND #PWR0102
U 1 1 61701F36
P 5450 3950
F 0 "#PWR0102" H 5450 3700 50  0001 C CNN
F 1 "GND" H 5455 3777 50  0000 C CNN
F 2 "" H 5450 3950 50  0000 C CNN
F 3 "" H 5450 3950 50  0000 C CNN
	1    5450 3950
	1    0    0    -1  
$EndComp
$Comp
L power:+3V3 #PWR0103
U 1 1 61702415
P 5000 3450
F 0 "#PWR0103" H 5000 3300 50  0001 C CNN
F 1 "+3V3" H 5015 3623 50  0000 C CNN
F 2 "" H 5000 3450 50  0000 C CNN
F 3 "" H 5000 3450 50  0000 C CNN
	1    5000 3450
	1    0    0    -1  
$EndComp
$Comp
L power:+3V3 #PWR0104
U 1 1 61702F86
P 5450 3450
F 0 "#PWR0104" H 5450 3300 50  0001 C CNN
F 1 "+3V3" H 5465 3623 50  0000 C CNN
F 2 "" H 5450 3450 50  0000 C CNN
F 3 "" H 5450 3450 50  0000 C CNN
	1    5450 3450
	1    0    0    -1  
$EndComp
Wire Wire Line
	5000 3550 5000 3450
Wire Wire Line
	5450 3450 5450 3550
Wire Wire Line
	5450 3850 5450 3950
Wire Wire Line
	5000 3850 5000 3950
$Comp
L Device:R R1
U 1 1 6171442F
P 5800 2500
F 0 "R1" H 5870 2591 50  0000 L CNN
F 1 "10K" H 5870 2500 50  0000 L CNN
F 2 "Resistor_SMD:R_0603_1608Metric" V 5730 2500 50  0001 C CNN
F 3 "~" H 5800 2500 50  0001 C CNN
F 4 "NF" H 5870 2409 50  0000 L CNN "FIT"
	1    5800 2500
	1    0    0    -1  
$EndComp
$Comp
L Device:R R2
U 1 1 617151E2
P 6100 2500
F 0 "R2" H 6170 2591 50  0000 L CNN
F 1 "10K" H 6170 2500 50  0000 L CNN
F 2 "Resistor_SMD:R_0603_1608Metric" V 6030 2500 50  0001 C CNN
F 3 "~" H 6100 2500 50  0001 C CNN
F 4 "NF" H 6170 2409 50  0000 L CNN "FIT"
	1    6100 2500
	1    0    0    -1  
$EndComp
$Comp
L power:+3V3 #PWR0105
U 1 1 617157CF
P 5800 2300
F 0 "#PWR0105" H 5800 2150 50  0001 C CNN
F 1 "+3V3" H 5815 2473 50  0000 C CNN
F 2 "" H 5800 2300 50  0000 C CNN
F 3 "" H 5800 2300 50  0000 C CNN
	1    5800 2300
	1    0    0    -1  
$EndComp
$Comp
L power:+3V3 #PWR0106
U 1 1 61715C95
P 6100 2300
F 0 "#PWR0106" H 6100 2150 50  0001 C CNN
F 1 "+3V3" H 6115 2473 50  0000 C CNN
F 2 "" H 6100 2300 50  0000 C CNN
F 3 "" H 6100 2300 50  0000 C CNN
	1    6100 2300
	1    0    0    -1  
$EndComp
Wire Wire Line
	5800 2700 5800 2650
Wire Wire Line
	5100 2700 5800 2700
Wire Wire Line
	5800 2350 5800 2300
Wire Wire Line
	6100 2800 6100 2650
Wire Wire Line
	5100 2800 6100 2800
Wire Wire Line
	6100 2300 6100 2350
$Comp
L Device:R R3
U 1 1 6171BDC0
P 6550 2500
F 0 "R3" H 6620 2546 50  0000 L CNN
F 1 "10K" H 6620 2455 50  0000 L CNN
F 2 "Resistor_SMD:R_0603_1608Metric" V 6480 2500 50  0001 C CNN
F 3 "~" H 6550 2500 50  0001 C CNN
	1    6550 2500
	1    0    0    -1  
$EndComp
$Comp
L power:+3V3 #PWR0107
U 1 1 6171C48E
P 6550 2300
F 0 "#PWR0107" H 6550 2150 50  0001 C CNN
F 1 "+3V3" H 6565 2473 50  0000 C CNN
F 2 "" H 6550 2300 50  0000 C CNN
F 3 "" H 6550 2300 50  0000 C CNN
	1    6550 2300
	1    0    0    -1  
$EndComp
Wire Wire Line
	6550 2300 6550 2350
Wire Wire Line
	6550 2650 6550 2900
Connection ~ 6550 2900
Wire Wire Line
	6550 2900 7050 2900
Wire Wire Line
	7050 3000 6800 3000
$Comp
L Device:C C1
U 1 1 5CB7975E
P 3200 2650
F 0 "C1" H 3315 2696 50  0000 L CNN
F 1 "18P" H 3315 2605 50  0000 L CNN
F 2 "Capacitors_SMD:C_0603" H 3238 2500 50  0001 C CNN
F 3 "http://www.farnell.com/datasheets/1731432.pdf?_ga=2.99920414.1044651491.1556565859-289093737.1544555023&_gac=1.26737999.1555367884.Cj0KCQjw19DlBRCSARIsAOnfRei64FcwOFGwHccevtvnCF1_gtAlQkzaoKMfBkZYkqlx40vjUC8V3ZkaAmTjEALw_wcB" H 3200 2650 50  0001 C CNN
F 4 "JOHANSON" H 3200 2650 50  0001 C CNN "MANF"
F 5 "251R14S0R3AV4T" H 3200 2650 50  0001 C CNN "MANF#"
F 6 "FARNELL" H 3200 2650 50  0001 C CNN "SUPPLIER"
F 7 "1885351" H 3200 2650 50  0001 C CNN "SUPPLIER#"
F 8 "" H 3050 2550 50  0001 L CNN "FIT"
	1    3200 2650
	1    0    0    -1  
$EndComp
Text Label 6850 2900 0    50   ~ 0
SDA
$Comp
L Graphic:Logo_Open_Hardware_Small LOGO1
U 1 1 617614A1
P 10900 6850
F 0 "LOGO1" H 10900 7125 50  0001 C CNN
F 1 "Logo_Open_Hardware_Small" H 10900 6625 50  0001 C CNN
F 2 "CUPL:OSHW-Symbol_5.7x6mm_SilkScreen" H 10900 6850 50  0001 C CNN
F 3 "~" H 10900 6850 50  0001 C CNN
	1    10900 6850
	1    0    0    -1  
$EndComp
NoConn ~ 7050 3300
NoConn ~ 7050 3400
NoConn ~ 7050 3500
NoConn ~ 7050 3600
NoConn ~ 7050 3700
NoConn ~ 7050 3800
NoConn ~ 8950 2800
NoConn ~ 8950 2900
NoConn ~ 8950 3100
NoConn ~ 8950 3200
NoConn ~ 8950 3300
NoConn ~ 8950 3400
NoConn ~ 8950 3500
NoConn ~ 8950 3600
NoConn ~ 8950 3700
NoConn ~ 8950 3800
NoConn ~ 8950 3900
NoConn ~ 8950 4000
NoConn ~ 8950 4100
NoConn ~ 8950 4200
NoConn ~ 8950 4300
NoConn ~ 8950 4400
NoConn ~ 8950 4500
NoConn ~ 8950 4600
NoConn ~ 8950 4700
NoConn ~ 7050 3900
NoConn ~ 7050 4000
NoConn ~ 7050 4100
NoConn ~ 7050 4200
NoConn ~ 7050 4300
NoConn ~ 7050 4400
NoConn ~ 7050 4500
NoConn ~ 7050 4600
NoConn ~ 7050 4700
$Comp
L Mechanical:MountingHole H2
U 1 1 61772D73
P 4300 5000
F 0 "H2" H 4400 5046 50  0000 L CNN
F 1 "MountingHole" H 4400 4955 50  0000 L CNN
F 2 "CUPL:RPi_Hat_Mounting_Hole" H 4300 5000 50  0001 C CNN
F 3 "~" H 4300 5000 50  0001 C CNN
	1    4300 5000
	1    0    0    -1  
$EndComp
$Comp
L Mechanical:MountingHole H1
U 1 1 6177427E
P 3350 5000
F 0 "H1" H 3450 5046 50  0000 L CNN
F 1 "MountingHole" H 3450 4955 50  0000 L CNN
F 2 "CUPL:RPi_Hat_Mounting_Hole" H 3350 5000 50  0001 C CNN
F 3 "~" H 3350 5000 50  0001 C CNN
	1    3350 5000
	1    0    0    -1  
$EndComp
$Comp
L Mechanical:MountingHole H3
U 1 1 61774479
P 3350 5300
F 0 "H3" H 3450 5346 50  0000 L CNN
F 1 "MountingHole" H 3450 5255 50  0000 L CNN
F 2 "CUPL:RPi_Hat_Mounting_Hole" H 3350 5300 50  0001 C CNN
F 3 "~" H 3350 5300 50  0001 C CNN
	1    3350 5300
	1    0    0    -1  
$EndComp
$Comp
L Mechanical:MountingHole H4
U 1 1 6177478A
P 4300 5300
F 0 "H4" H 4400 5346 50  0000 L CNN
F 1 "MountingHole" H 4400 5255 50  0000 L CNN
F 2 "CUPL:RPi_Hat_Mounting_Hole" H 4300 5300 50  0001 C CNN
F 3 "~" H 4300 5300 50  0001 C CNN
	1    4300 5300
	1    0    0    -1  
$EndComp
$EndSCHEMATC
