import pycom
import struct
import time
import socket
import binascii

from network import LoRa

# Py sense => https://docs.pycom.io/pytrackpysense/apireference/pysense.html
from pysense import Pysense
from MPL3115A2 import MPL3115A2         # Barometric Pressure Sensor with Altimeter (MPL3115A2)
from LTR329ALS01 import LTR329ALS01     # Digital Ambient Light Sensor (LTR-329ALS-01)
from SI7006A20 import SI7006A20         # Humidity and Temperature Sensor (SI7006A20)
from LIS2HH12 import LIS2HH12           # 3-Axis Accelerometer (LIS2HH12)

# for EU868
LORA_FREQUENCY = 868100000
#LORA_GW_DR = "SF7BW125" # DR_5
LORA_NODE_DR = 5


# Disable the heartbeat LED
pycom.heartbeat(False)

# Make the LED light up in black
pycom.rgbled(0x000000)

# Init the libraries
pysense = Pysense()
mpl3115a2 = MPL3115A2() # Barometric Pressure Sensor with Altimeter
ltr329als01 = LTR329ALS01() # Digital Ambient Light Sensor
si7006a20 = SI7006A20() # Humidity and Temperature sensor
lis2hh12 = LIS2HH12() # 3-Axis Accelerometer

# Show Init
pycom.rgbled(0x0000ff)
time.sleep(0.5)
pycom.rgbled(0x000000)
time.sleep(0.1)
pycom.rgbled(0x0000ff)
time.sleep(0.5)
pycom.rgbled(0x000000)

# initialize LoRa in LORAWAN mode.
# Please pick the region that matches where you are using the device:
# Asia = LoRa.AS923
# Australia = LoRa.AU915
# Europe = LoRa.EU868
# United States = LoRa.US915
lora = LoRa(mode=LoRa.LORAWAN, region=LoRa.EU868)

# create an ABP authentication params

dev_addr = struct.unpack(">l", binascii.unhexlify('xxxxxxxx'))[0]
nwk_swkey = binascii.unhexlify('xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx')
app_swkey = binascii.unhexlify('xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx')

# remove all the non-default channels
for i in range(3, 16):
    lora.remove_channel(i)

# set the 3 default channels to the same frequency
lora.add_channel(0, frequency=LORA_FREQUENCY, dr_min=0, dr_max=5)
lora.add_channel(1, frequency=LORA_FREQUENCY, dr_min=0, dr_max=5)
lora.add_channel(2, frequency=LORA_FREQUENCY, dr_min=0, dr_max=5)

# join a network using ABP (Activation By Personalization)
lora.join(activation=LoRa.ABP, auth=(dev_addr, nwk_swkey, app_swkey))

# create a LoRa socket
s = socket.socket(socket.AF_LORA, socket.SOCK_RAW)

# set the LoRaWAN data rate
s.setsockopt(socket.SOL_LORA, socket.SO_DR, LORA_NODE_DR)

# make the socket non-blocking
s.setblocking(False)

while True:
    
    # Read the values from the sensors
    voltage = pysense.read_battery_voltage()
    temperature = mpl3115a2.temperature()
    humidity = si7006a20.humidity()
    pressure = mpl3115a2.pressure()    
    # Read the light levels of both LTR329ALS01 sensors. Returns a tuple with two values for light levels in lux.
    # Light (channel Blue lux, channel Red lux)
    lightBlue = ltr329als01.light()[0] 
    lightRed = ltr329als01.light()[1]     
    roll = lis2hh12.roll()
    pitch = lis2hh12.pitch()
    
    # Debug sensor values
    #print('voltage:{}, temperature:{}, pressure:{}, light:{}, humidity:{}, roll:{}, pitch:{}'.format(voltage, temperature, pressure, light, humidity, roll, pitch))

    print('voltage:{}, temperature:{}, humidity:{}, pressure:{}'.format(voltage, temperature, humidity ,pressure))
    print()
    #print('lightBlue:{},lightRed:{}, roll:{}, pitch:{}'.format(lightBlue, lightRed, roll, pitch))
    #print()
    
    # h short integer 2 (-32768 hasta 32767)
    # H short unsigned integer 2 (65535)
    pck1_bytes = struct.pack(">HhHH",
        int(voltage * 100),         # Battery voltage
        int(temperature * 100),     # Temperature in celcius 
        int(humidity * 100),        # Humidity in percentages
        int(pressure / 10)          # Atmospheric pressure in bar
        ) # 8 bytes 
    
    # send the data over LPWAN network
    print (pck1_bytes)
    print('Sending:', pck1_bytes)    
    s.send(pck1_bytes)
    
    pycom.rgbled(0x007f00) # Make the LED light up in green
    time.sleep(0.3)
    pycom.rgbled(0x000000)    

    time.sleep(4)
    rx, port = s.recvfrom(256)
    if rx:
        print('Received: {}, on port: {}'.format(rx, port))
    
    '''
    # h short integer 2 (-32768 hasta 32767)
    # H short unsigned integer 2 (65535)
    pck2_bytes = struct.pack(">HHhh",        
        int(lightBlue),             # Light in lux
        int(lightRed),              # Light in lux
        int(roll * 100),            # Roll in degrees in the range -180 to 180
        int(pitch * 100),           # Pitch in degrees in the range -90 to 90
        ) # 8 bytes 
    
    # send the data over LPWAN network
    print (pck2_bytes)
    #s.send(pck_bytes)
    print()
    '''    
    
    # Wait for 60 seconds before moving to the next iteration
    time.sleep(55)