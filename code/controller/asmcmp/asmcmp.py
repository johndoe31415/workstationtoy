#!/usr/bin/python3
import re
import sys

class AsmFile():
	_SYMBOL = re.compile("^[0-9a-f]+ <(?P<symbol>[^>]+)>:$")

	def __init__(self, filename):
		cursym = None
		lineno = 0

		self._code = { }
		self._symbols = [ ]
		for line in open(filename, "r"):
			line = line[:-1]
			line = line.replace("\t", "    ")
			lineno += 1
			result = AsmFile._SYMBOL.match(line)
			if result:
				result = result.groupdict()
				cursym = result["symbol"]
				if cursym in self._code:
					print("WARNING: Duplicate symbol '%s'!" % (cursym))
				else:
					self._code[cursym] = [ ]
					self._symbols.append(cursym)
			if cursym is not None:
				self._code[cursym].append(line)

	def get(self, symbol):
		if symbol not in self._code:
			return [ ]
		else:
			return self._code[symbol]

	def __iter__(self):
		return iter(self._symbols)

class AsmCmp():
	def __init__(self, file1, file2):
		self._f1 = AsmFile(file1)
		self._f2 = AsmFile(file2)

	def write(self, out1, out2, merge):
		for sym in self._f1:
			code1 = self._f1.get(sym)
			code2 = self._f2.get(sym)
			
			length = max(len(code1), len(code2))
			code1 += [ "" ] * (length - len(code1))
			code2 += [ "" ] * (length - len(code2))

			for line in code1:
				print(line, file = out1)
			for line in code2:
				print(line, file = out2)

			for i in range(length):				
				if len(code1[i]) > 100:
					code1[i] = code1[i][:100]
				line = "%-100s %-s" % (code1[i], code2[i])
				print(line, file = merge)

comparison = AsmCmp(sys.argv[1], sys.argv[2])
comparison.write(open("out1.S", "w"), open("out2.S", "w"), open("merge", "w"))
