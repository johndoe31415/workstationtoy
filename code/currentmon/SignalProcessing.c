#include <stdio.h>
#include <stdint.h>

#include "CurrentMonitor.h"

#define SAMPLE_WINDOW_SIZE			256

static uint32_t averageAccu;
static uint32_t integralAccu;
static uint16_t sampleCount;
static uint16_t dcOffsetADU = 0x3ff / 2;

void nextSample(uint16_t aSampleValue) {
	sampleCount += 1;
	averageAccu += aSampleValue;
	integralAccu += (aSampleValue >= dcOffsetADU) ? (aSampleValue - dcOffsetADU) : (dcOffsetADU - aSampleValue);	

	if (sampleCount == SAMPLE_WINDOW_SIZE) {
		dcOffsetADU = averageAccu / SAMPLE_WINDOW_SIZE;
		uint16_t integralValue = (integralAccu >= 0xffffUL) ? 0xffff : integralAccu;
		uint32_t currentValue = (uint32_t)integralValue * 125 / 682;
#ifndef DEBUG
		determinedMomentaryCurrentValue(currentValue);
#else
		printf("dcOffset = %d, current = %.3f A ~ %.1f W\n", dcOffsetADU, (float)currentValue / 1000, (float)currentValue / 1000 * 230);
#endif
		averageAccu = 0;
		integralAccu = 0;
		sampleCount = 0;
	}
}

#ifdef DEBUG
int main(int argc, char **argv) { 
	char buf[256];
	while (fgets(buf, sizeof(buf) - 1, stdin)) {
		uint16_t adcValue = atoi(buf);
		nextSample(adcValue);
	}
	return 0;
}
#endif
