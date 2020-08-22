import sys
import os

import mako.lookup

class Template():
	def __init__(self, templatename):
		basedir = os.path.dirname(os.path.realpath(sys.argv[0]))
		lookup = mako.lookup.TemplateLookup(directories = [ basedir + "/templates/" ], input_encoding = "utf-8")
		self._template = lookup.get_template(templatename)

	def render(self, variables):
		return self._template.render(**variables)
