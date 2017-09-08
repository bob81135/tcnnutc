import serial
import MySQLdb
import time
ser = serial.Serial('/dev/ttyACM0',115200)  # open serial port
print(ser.name)         # check which port was really used
while(1):
	ans=ser.readline()
	strlist = ans.split(',')
	to=ans.split(',')[0]
	print(to)
	time.sleep(1)
ser.close()   
