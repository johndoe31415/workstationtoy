#!/usr/bin/python3

import re
import threading
import time
from gi.repository import Gtk
from gi.repository import GObject


class Handler():
	def __init__(self, builder):
		self._builder = builder
		self._red = 0
		self._green = 0

	def _setled(self, filename):
		self._builder.get_object("image1").set_from_file(filename)

	def _getname(self, widget):
		return Gtk.Buildable.get_name(widget)

	def onDeleteWindow(self, *args):
		Gtk.main_quit(*args)

	def onButtonPressed(self, button):
		self._red = int(self._builder.get_object("entry1").get_text(), 16)
		self._green = int(self._builder.get_object("entry1").get_text(), 16)
		self._update()

	def onGroupChanged(self, radiobutton):
		button_name = self._getname(radiobutton)
		btnregex = re.compile("radiobutton_bit(?P<bit>\d+)_(?P<btnno>\d+)")
		result = btnregex.match(button_name)
		if result:
			result = result.groupdict()
			bit = int(result["bit"]) - 1
			btn = int(result["btnno"])
			if btn == 1:
				self._red &= ~(1 << bit)
				self._green &= ~(1 << bit)
			elif btn == 2:
				self._red |= (1 << bit)
				self._green &= ~(1 << bit)
			elif btn == 3:
				self._red &= ~(1 << bit)
				self._green |= (1 << bit)
			elif btn == 4:
				self._red |= (1 << bit)
				self._green |= (1 << bit)
			self._update()

	def _update(self):
		self._builder.get_object("entry1").set_text("%04x" % (self._red))
		self._builder.get_object("entry2").set_text("%04x" % (self._green))

class UpdateThread(threading.Thread):
	def __init__(self, hdlr):
		threading.Thread.__init__(self)
		self._handler = hdlr
		self._bitno = 0
		
	def run(self):
		while True:
			self._bitno = (self._bitno + 1) % 16
			green = (self._handler._green & (1 << self._bitno)) >> self._bitno
			red = (self._handler._red & (1 << self._bitno)) >> self._bitno
			ledstate = (green << 1) | red
			if ledstate == 0:
				self._handler._setled("led_klar.jpg")
			elif ledstate == 1:
				self._handler._setled("led_red.jpg")
			elif ledstate == 2:
				self._handler._setled("led_green.jpg")
			elif ledstate == 3:
				self._handler._setled("led_orange.jpg")
			time.sleep(0.05)
			

GObject.threads_init()

builder = Gtk.Builder()
builder.add_from_file("ledsim.glade")
handler = Handler(builder)
builder.connect_signals(handler)

updth = UpdateThread(handler)
updth.start()

window = builder.get_object("window1")
window.show_all()

Gtk.main()

