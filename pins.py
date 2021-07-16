from machine import Pin
from utils import conf

class Gpio:

	def __init__(self):
		self.__pins = {}
		self.__configs = {}
		for pin,config in conf['pins'].items():
			self.__configs[pin] = config
		for p_no,cnf in self.__configs.items():
			self.__pins[p_no] = Pin(int(p_no), Pin.IN if cnf['mode']=='in' else Pin.OUT)
			if cnf['mode']==Pin.OUT:
				self.__pins[p_no].value(cnf['value'])

	def set_states(self, states):
		for p_no,value in states.items():
			if (p_no in self.__pins) and (self.__configs[p_no]['mode'] == 'out') and (value in [0,1]):
				self.__pins[p_no].value(value)
				self.__configs[p_no]['value'] = value
	
	def get_states(self):
		for p_no,cnf in self.__configs.items():
			if cnf['mode'] == 'in':
				self.__configs[p_no]['value'] = self.__pins[p_no].value()
		return self.__configs
	
	def get_info(self):
		return {'pins': self.__pins, 'config': self.__configs}
	
	#def set_pin(self, no, val):
	#	self.__pins[no].value(val)

#p = Pin(2, Pin.OUT) #pin function for esp-12f led is revert






