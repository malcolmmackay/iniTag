# This is a sample Python script.

# Press Shift+F10 to execute it or replace it with your code.
# Press Double Shift to search everywhere for classes, files, tool windows, actions, and settings.

from smbus2 import SMBus
import ndef
from time import sleep

BLOCK0 = [0x55 << 1, 61, 106, 106, 9, 79, 128, 0, 68, 0, 0, 0, 0xE1, 0x10, 0x6D, 0]
TAG_NDEF_MESSSAGE = 0x03

# Read NT3H2111 Block 0.
nt3h = SMBus(1)
blk0 = nt3h.read_i2c_block_data(0x55, 0, 16)

# Write the first block
nt3h.write_i2c_block_data(0x55, 0, BLOCK0)
sleep(0.1)

# Create an NDEF record
record = ndef.TextRecord("Second text record", "en")
octetbytes = b''.join(ndef.message_encoder([record]))
# Convert list of bytes to a list of integers
octets = list(octetbytes)
noctets = len(octets)

# Prepend the Type and Length fields
octets.insert(0, TAG_NDEF_MESSSAGE)

# Prepend 0xFF to the Length field
octets.insert(1, 0xFF)
octets.insert(2, ((noctets & 0xFF00) >> 8))
octets.insert(3, noctets & 0xFF)

# Payload starts with block 1.
blk = 1
# Iterate until all bytes are written.
while len(octets) > 0:
    # Write 16 octets to the active block
    blkoctets = octets[0:16]
    blkoctets += [0] * (16 - len(blkoctets))
    nt3h.write_i2c_block_data(0x55, blk, blkoctets)
    sleep(0.1)
    # Remove the 16 octets from the list to write
    octets = octets[16:]
    # Increment the block
    blk = blk + 1
