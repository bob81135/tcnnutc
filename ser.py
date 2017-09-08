import serial
import requests
import time
import json
h=[]
ser = serial.Serial('/dev/ttyACM0',115200)  # open serial port
print(ser.name)         # check which port was really used
while(1):
        ans=ser.readline()
        strlist = ans.split(',')[1]
	data = {'hook_id':strlist.split('\r\n')[0] , 'tag_id':ans.split(',')[0] ,'status':'1'}
	response = requests.post('http://192.168.43.175/sethookSatus', data)
	print(data)
	led = requests.post('http://192.168.43.175/getLightSatus')
	a=json.dumps(led.json())
	print a
#	print type(a)
	h=a[26]+a[55]+a[84]+a[113]
        #time.sleep(1)
	print h
	#ser.write(h)
	#time.sleep(1)
	#print(ser.readline())
ser.close()

