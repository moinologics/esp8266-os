from gc import mem_free
from utime import sleep, time as ticks_s
from utils import setup_ap,setup_sta,log
from mqtt_client import mqtt_setup
from pins import Gpio

#log('start')

ap = setup_ap()
sta = setup_sta()

pins = Gpio()
mqtt = False
last_publish = 0


while mqtt==False:
	try:
		mqtt = mqtt_setup(pins)
	except Exception as e:
		sleep(1)

while True:
	try:
		mqtt.check_msg()
		if last_publish + 5 < ticks_s():
			last_publish = ticks_s()
			mqtt.publish('esp/a42c16/test', 'Free Memory: {} bytes'.format(mem_free()))
		sleep(1)
	except Exception as e:
		log(e, 'Error')



