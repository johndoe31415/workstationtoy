# workstationtoy
This is a piece of industrial equipment that I built around 2012. It never
fully completed, but disappointingly, I stopped developing it once it was "good
enough" to fit its purpose. Essentially, it's a 230 VAC switchbox with an
autotransformer, isolating transformer and some protection equipment. I used to
power my workbench with it. It has nice features such as auto-poweroff, soft
fuses (current measuring and isolating before the hard circuit breaker comes) and
a bunch of plausibilization features.

One nice thing is that the way I wired everything up was so that the main
controller was controlled by the (industially manufactured) front plate and
that firmware had all other sub-controller firmwares in its belly and could
update everything. Also it had some kind of mashalling protocol that I've
invented to create minimalistic stubs for SPI communication between
controllers.

It is entirely dysfunctional now and I've ripped everything apart and will
repurpose it to be a toy for my baby daughter. She loves pressing buttons and
flashing lights and it's got all that.

I'm still pushing all the code from 2012 to Github so that if I am interested
one day I can go back in the history and see how I've done stuff.

## License
GNU GPL-3. There's one dependency in the original files from AVR-Crypto-Lib,
which I used for self-verification of firmware integrity (also GPL-3).
