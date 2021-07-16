from libs.umqtt_simple2 import MQTTClient
from utils import conf, log
import ujson as json


HOST = conf['mqtt']['host']
PORT = conf['mqtt']['port']
ClientId = conf['mqtt']['ClientId']


def cb(topic, msg, a, b):
	global gpio
	try:
		#log('topic: {}\n msg: {}'.format(topic, msg))
		msg = json.loads(msg)
		if ('key' in msg) and (msg['key'] == conf['mqtt']['authKey']):
			if ('states' in msg) and (type(msg['states']) is dict):
				gpio.set_states(msg['states'])
	except Exception as e:
		log(e, 'Error')

def mqtt_setup(pins):
	global gpio
	gpio = pins
	mqtt.connect()
	mqtt.subscribe(conf['mqtt']['SubscribeTopic'])
	return mqtt

mqtt = MQTTClient(client_id=ClientId, server=HOST, port=PORT)
mqtt.set_callback(cb)


