from serial import Serial
from detect_uarts import serial_ports
from datetime import datetime
from time import sleep

serial = Serial(port=serial_ports()[0], baudrate=9600, timeout=0.5)
serial.write(datetime.now().replace(microsecond=0).isoformat() + '\n')
serial.flushOutput()
while True:
    serial.flushInput()
    line = serial.readline()
    if line.endswith('\n'):
        print "Clock responded: " + line
        serial.close()
        exit()