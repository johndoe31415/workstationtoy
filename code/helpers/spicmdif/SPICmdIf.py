import re
import collections

from XMLParser import XMLParser

_PrimitiveTypeDefinition = collections.namedtuple("_PrimitiveTypeDefinition", [ "sizebytes" ])
class _PrimitiveType():
	_PRIMITIVE_TYPES = {
		"uint8":	_PrimitiveTypeDefinition(sizebytes = 1),
		"uint16":	_PrimitiveTypeDefinition(sizebytes = 2),
		"uint32":	_PrimitiveTypeDefinition(sizebytes = 4),
	}

	_ARRAY_RE = re.compile("^(?P<identifier>[a-zA-Z0-9]+)(?:\[(?P<cardinality>\d+)\])?$")
	def __init__(self, name):
		result = _PrimitiveType._ARRAY_RE.match(name)
		if not result:
			raise TypeError("'%s' does not conform to formal syntax" % (name))
		result = result.groupdict()
		name = result["identifier"]

		if name not in _PrimitiveType._PRIMITIVE_TYPES:
			raise TypeError("'%s' is not a known primitive type" % (name))
		if result["cardinality"] is None:
			self._cardinality = None
		else:
			self._cardinality = int(result["cardinality"])
		self._name = name

	@property
	def cardinality(self):
		return self._cardinality

	@property
	def isarray(self):
		return self.cardinality is not None

	@property
	def name(self):
		return self._name
	
	@property
	def primitive(self):
		return True

	def __len__(self):
		if not self.isarray:
			return _PrimitiveType._PRIMITIVE_TYPES[self.name].sizebytes
		else:
			return _PrimitiveType._PRIMITIVE_TYPES[self.name].sizebytes * self.cardinality

class _EnumElement():
	def __init__(self, rootnode):
		self._name = rootnode["name"]
		if rootnode.get("value") is not None:
			self._fixedvalue = int(rootnode["value"])
		else:
			self._fixedvalue = None
	
	@property
	def name(self):
		return self._name
	
	@property
	def fixedvalue(self):
		return self._fixedvalue

	def hasfixedvalue(self):
		return self.fixedvalue is not None

class _Enum():
	def __init__(self, rootnode):
		self._name = rootnode["name"]
		self._prefix = rootnode.get("prefix", "")
		self._fixedvalues = { }
		elements = [ ]
		for element in rootnode.element:
			elements.append(_EnumElement(element))
		self._elements = elements
		self._elementsbyname = { x.name: x for x in self._elements }
		assert(len(self._elements) == len(self._elementsbyname))

	def getsymbol(self, symbol):
		return self._elementsbyname[symbol]

	def getbasetype(self):
		return _PrimitiveType("uint8")
	
	@property
	def primitive(self):
		return False

	@property
	def name(self):
		return self._name

	@property
	def prefix(self):
		return self._prefix

	def __iter__(self):
		return iter(self._elements)

	def __len__(self):
		return len(self.getbasetype())

class _CmdElement():
	def __init__(self, cmdif, cmdelement):
		if cmdif is not None:
			self._typedef = cmdif.gettype(cmdelement["type"])
			self._name = cmdelement["name"]
	
	@property
	def name(self):
		return self._name
	
	@property
	def typedef(self):
		return self._typedef

	def __len__(self):
		return len(self._typedef)


class _Command():
	def __init__(self, cmdif, rootnode, cmdid):
		assert(isinstance(cmdid, int))
		self._cmdid = cmdid
		self._name = rootnode["name"]
		self._delay = int(rootnode.get("delay", "500"))
		self._master = [ ]
		self._slave = [ ]

		self._master.append(_CmdElement(cmdif, {
			"type":		"uint8",
			"name":		cmdif.getproperty("cmdidfieldname"),
		}))
		self._master.append(_CmdElement(cmdif, {
			"type":		"uint16",
			"name":		cmdif.getproperty("crcfieldname"),
		}))
		if rootnode.getchild("mastertx"):
			for mastertx in rootnode.mastertx:
				self._master.append(_CmdElement(cmdif, mastertx))
		if rootnode.getchild("slavetx"):
			for slavetx in rootnode.slavetx:
				self._slave.append(_CmdElement(cmdif, slavetx))
		self._slave.append(_CmdElement(cmdif, {
			"type":		"uint16",
			"name":		cmdif.getproperty("crcfieldname"),
		}))

	@property
	def masterlen(self):
		return sum([ len(x) for x in self._master ])
	
	@property
	def slavelen(self):
		return sum([ len(x) for x in self._slave ])

	@property
	def mastercnt(self):
		return len(self._master)
	
	@property
	def slavecnt(self):
		return len(self._slave)

	@property
	def masteriter(self):
		return iter(self._master)
	
	@property
	def slaveiter(self):
		return iter(self._slave)

	@property
	def name(self):
		return self._name
	
	@property
	def delay(self):
		return self._delay
	
	@property
	def cmdid(self):
		return self._cmdid

	def __len__(self):
		return self.masterlen + self.slavelen

class SPICmdIf():
	def __init__(self, filename):
		self._enums = [ ]
		self._commands = [ ]
		self._enumsbyname = { }
		self._properties = {
			"cmdprefix":			"",
			"enumprefix":			"",
			"includeguard":			"SPISLAVE",
			"defineprefix":			"",
			"cmdidfieldname":		"cmdId",
			"crcfieldname":			"crc",
			"slavename":			"FOOBAR",
		}

		self._xml = XMLParser().parsefile(filename)
		self._parseenums()
		self._parsecommands()
		self._parseproperties()
	
	def getproperty(self, name):
		return self._properties[name]

	def _parseproperties(self):
		if self._xml.getchild("properties") is None:
			return
		for propname in self._properties.keys():
			node = self._xml.properties.getchild(propname)
			if node is not None:
				self._properties[propname] = node["value"]

	def _parseenums(self):
		if self._xml.getchild("enum") is None:
			return
		for enumnode in self._xml.enum:
			parsedenum = _Enum(enumnode)
			self._enums.append(parsedenum)
			self._enumsbyname[parsedenum.name] = parsedenum

	def _parsecommands(self):
		if self._xml.getchild("command") is None:
			return
		for commandnode in self._xml.command:
			self._commands.append(_Command(self, commandnode, len(self._commands)))

	@property
	def enums(self):
		return iter(self._enums)

	@property
	def cmds(self):
		return iter(self._commands)

	def getmaxmsglength(self):
		return max([ len(cmd) for cmd in self.cmds ])

	def getmaxcmdid(self):
		return max([ cmd.cmdid for cmd in self.cmds ])

	def gettype(self, typename):
		try:
			return _PrimitiveType(typename)
		except TypeError:
			pass
		if typename not in self._enumsbyname:
			raise TypeError("'%s' is neither a primitive type nor a enum" % (typename))
		return self._enumsbyname[typename]


