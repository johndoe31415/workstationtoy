class CWrapper():
	_TYPEMAP_PRIMITIVE = {
		"uint8":		"uint8_t",
		"uint16":		"uint16_t",
		"uint32":		"uint32_t",
	}

	def __init__(self, cmddef):
		self._cmddef = cmddef

	def structelement_to_declaration(self, element):
		if element.typedef.primitive:
			if not element.typedef.isarray:
				return CWrapper._TYPEMAP_PRIMITIVE[element.typedef.name] + " " + element.name
			else:
				return CWrapper._TYPEMAP_PRIMITIVE[element.typedef.name] + " " + element.name + "[" + str(element.typedef.cardinality) + "]"
		else:
			return "enum " + self._cmddef.getproperty("enumprefix") + element.typedef.name + " " + element.name

	def cmddefine(self, cmd, definename):
		return self._cmddef.getproperty("defineprefix") + cmd.name.upper() + "_" + definename

