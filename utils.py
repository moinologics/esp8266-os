from utime import sleep
import network
import ujson as json
from uos import statvfs


with open('data/config.json', 'r') as f:
	conf = json.load(f)


def log(msg, label='info'):
	memory = statvfs('/')
	mem_free = memory[0] * memory[3] #bytes
	if mem_free > 1024*1024: #1 mb
		with open('data/logs.txt', 'a') as l:
			l.write('[{}]: {} \n'.format(label,msg))
		return True
	return False


def setup_ap():
	ap_conf = conf['network']['ap']
	ap = network.WLAN(network.AP_IF)
	ap.active(True)
	ap.config(essid=ap_conf['ssid'], password=ap_conf['password'])
	ap.ifconfig((ap_conf['ip'], ap_conf['mask'], ap_conf['subnet'], ap_conf['dns']))
	if ap.active() == True:
		print('ap config:', ap.ifconfig())
	return ap

def setup_sta():
	sta_conf = conf['network']['sta'][0]
	sta = network.WLAN(network.STA_IF)
	sta.active(True)
	sta.connect(sta_conf['ssid'], sta_conf['password'])
	if sta.isconnected():
		print('sta config:', sta.ifconfig())
	return sta

def setup_display():
	from libs.tm1637 import TM1637
	#from machine import Pin
	display_conf = conf['display']['tm1637']
	display = TM1637(clk=Pin(display_conf['CLK']), dio=Pin(display_conf['DIO']))
	return display

def led_blink(PinObj, duration_s):
	PinObj.value(1)
	sleep(duration_s)
	PinObj.value(0)


def network_status(ap,sta,p):
	if ap.isconnected():
		led_blink(p, 0.5)
		sleep(0.5)
	if sta.isconnected():
		led_blink(p, 0.5)
		sleep(0.5)
	p.value(1)
	sleep(2)

def run_clock(display):
	hour,minute = localtime()[3:5]
	display.numbers(hour, minute, colon=True)
	sleep(1)
	display.numbers(hour, minute, colon=False)
	sleep(1)
	#print(hour,minute)



