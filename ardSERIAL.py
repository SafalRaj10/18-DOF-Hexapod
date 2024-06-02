import serial
import struct
import errno

serial_port = '/dev/ttyUSB0' 
baud_rate = 115200 

MESSAGE_LENGTH = 13
ser = serial.Serial(serial_port, baud_rate)

try:
    with open('data.txt', 'a+') as f:
        while True:
            if ser.in_waiting > 0:
                serial_data = ser.readline()
                try:
                    decoded_string = "%1.6f" %  struct.unpack_from('<f', serial_data, 1)+" %1.6f" %  struct.unpack_from('<f', serial_data, 5)+" %1.6f" %  struct.unpack_from('<f', serial_data, 9)
                    print("SensorID:"+str(serial_data[0]), decoded_string)
                    f.write(decoded_string)
                except struct.error:
                    print("Data Loss")
except KeyboardInterrupt:
    ser.close()
