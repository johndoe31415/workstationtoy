#ifdef __AVR__

#include <avr/io.h>
#include <avr/pgmspace.h>

#define emulationdbg(msg, ...)
#define emulationcallback(cbtype, ...)

#else

#include <stdio.h>
#include <string.h>

#define PROGMEM
#define memcpy_P		memcpy

#define emulationdbg(msg, ...)		fprintf(stderr, msg, ##__VA_ARGS__)

void emulationcallback(int aCallbacktype, ...);

#endif
