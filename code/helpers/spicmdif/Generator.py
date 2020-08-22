import os

from Template import Template
from CWrapper import CWrapper

class Generator():
	def __init__(self, spicmds):
		self._cmds = spicmds

	def _generate_template(self, templatename):
		template = Template(templatename)
		data = {
			"cmddef":	self._cmds,
			"cwrp":		CWrapper(self._cmds),
		}
		return template.render(data)


	def generate(self):
		files = [ "SPISlave.h", "SPISlave.c", "SPISlaveImplementation.c" ]
		for filename in files:
			if os.path.exists(filename):
				print("Will not overwrite '%s'." % (filename))
			else:
				open(filename, "w").write(self._generate_template(filename))
