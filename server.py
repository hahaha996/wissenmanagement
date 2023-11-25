import os, sys
from typing import List
from LoRaRF import SX127x
import time
import random
import string
import struct
import array


# Begin LoRa radio and set NSS, reset, busy, IRQ, txen, and rxen pin with connected Raspberry Pi gpio pins
# IRQ pin not used in this example (set to -1). Set txen and rxen pin to -1 if RF module doesn't have one
busId = 0; csId = 0
resetPin = 22; irqPin = -1; txenPin = -1; rxenPin = -1
LoRa = SX127x()
print("Begin LoRa radio")
if not LoRa.begin(busId, csId, resetPin, irqPin, txenPin, rxenPin) :
    raise Exception("Something wrong, can't begin LoRa radio")

# Set frequency to 915 Mhz
print("Set frequency to 915 Mhz")
LoRa.setFrequency(866000000)

# Set TX power, this function will set PA config with optimal setting for requested TX power
print("Set TX power to +17 dBm")
LoRa.setTxPower(17, LoRa.TX_POWER_PA_BOOST)                     # TX power +17 dBm using PA boost pin

# Configure modulation parameter including spreading factor (SF), bandwidth (BW), and coding rate (CR)
# Receiver must have same SF and BW setting with transmitter to be able to receive LoRa packet
print("Set modulation parameters:\n\tSpreading factor = 7\n\tBandwidth = 125 kHz\n\tCoding rate = 4/5")
LoRa.setSpreadingFactor(7)                                      # LoRa spreading factor: 7
LoRa.setBandwidth(125000)                                       # Bandwidth: 125 kHz
LoRa.setCodeRate(5)                                             # Coding rate: 4/5

# Configure packet parameter including header type, preamble length, payload length, and CRC type
# The explicit packet includes header contain CR, number of byte, and CRC type
# Receiver can receive packet with different CR and packet parameters in explicit header mode
# print("Set packet parameters:\n\tExplicit header type\n\tPreamble length = 12\n\tPayload Length = 15\n\tCRC on")
# LoRa.setHeaderType(LoRa.HEADER_EXPLICIT)                        # Explicit header mode
# LoRa.setPreambleLength(12)                                      # Set preamble length to 12
# LoRa.setPayloadLength(15)                                       # Initialize payloadLength to 15
# LoRa.setCrcEnable(True)                                         # Set CRC enable

# Set syncronize word for public network (0x34)
print("Set syncronize word to 0x34")
LoRa.setSyncWord(0xF3)

print("\n-- LoRa Transmitter --\n")

counter = 0

#
host_code = 123# hex(123)
flag = 1#hex(1)    # 1: request accept, 
payload_length = 100#hex(100)
packet_format = "BBBIIB100s"
headerType = LoRa.HEADER_IMPLICIT
preambleLength = struct.calcsize(packet_format)
payloadLength = struct.calcsize(packet_format)
crcType = True
# LoRa.setLoRaPacket(headerType, preambleLength, payloadLength, crcType)
print(f"Set packet parameters:\n\tImplicit header type\n\tPreamble length = {preambleLength}\n\tPayload Length = {payloadLength}\n\tCRC {'on' if crcType else 'off'}")

# Transmit message continuously
# length_msg = 10
while True :
    print("waiting for request ...")
    # Request for receiving new LoRa packet
    LoRa.request()
    # Wait for incoming LoRa packet
    LoRa.wait()

    # Put received packet to message and counter variable
    # read() and available() method must be called after request() or listen() method
    reiv_message = ""
    # available() method return remaining received payload length and will decrement each read() or get() method called
    while LoRa.available() > 1 :
        reiv_message += chr(LoRa.read())
    counter = LoRa.read()
    print((reiv_message))
    