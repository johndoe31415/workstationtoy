#!/usr/bin/python3
import re
import sys

class Bit():
	def __init__(self):
		pass

	def getvalue(self, 

class BitTemplate():
	def __init__(self, bits):
		self._stream = [ ]
		bits = bits.replace(" ", "")
		
		fixedval_re = re.compile("^(?P<value>[01])(?P<remainder>.*)")
		variable_param_re = re.compile("^(?P<varname>[a-zA-Z])\((?P<parameter>[^\)]+)\)(?P<remainder>.*)")
		no_param_re = re.compile("^(?P<varname>[a-zA-Z])(?P<remainder>.*)")
		
		while len(bits) > 0:
			result = fixedval_re.match(bits)
			if result is not None:
				result = result.groupdict()
				bits = result["remainder"]
				self._add("fixed", result)
				continue

			result = variable_param_re.match(bits)
			if result is not None:
				result = result.groupdict()
				bits = result["remainder"]
				self._add("param", result)
				continue
			
			result = no_param_re.match(bits)
			if result is not None:
				result = result.groupdict()
				bits = result["remainder"]
				self._add("noparam", result)
				continue

			raise Exception("Parse error: %s" % (bits))

	def _add(self, bittype, bitparams):
		print(bittype, bitparams)

cmds = {
	"ProgrammingEnable":	BitTemplate("1010 1100       0101 0011   xxxx xxxx   xxxx xxxx"),
	"ChipErase":			BitTemplate("1010 1100       100x xxxx   xxxx xxxx   xxxx xxxx"),
	"ReadProgramMemory":	BitTemplate("0010 a(!0)100   0000 a(12)aaa   aaaa aaaa   xxxx xxxx"),
}
