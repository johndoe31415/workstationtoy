#ifndef __SPISLAVECM_H__
#define __SPISLAVECM_H__

#include <stdint.h>
#include <stdbool.h>

#ifndef PACKED
#define PACKED				__attribute__ ((packed))
#endif

#ifndef static_assert
#define static_assert(x)	_Static_assert(x, #x)
#endif

#if defined(SPI_MASTER)
#define MODIFIER_MASTER
#define MODIFIER_SLAVE			const
#elif defined(SPI_SLAVE)
#define MODIFIER_MASTER			const
#define MODIFIER_SLAVE
#else
#error Neither SPI_MASTER nor SPI_SLAVE is defined.
#endif

#define CM_READCURRENTVALUES_CMDID			0x0
#define CM_READCURRENTVALUES_MASTERLEN		3
#define CM_READCURRENTVALUES_DELAY_US		500
#define CM_READCURRENTVALUES_TOTALLEN		9
struct cmCmd_ReadCurrentValues {
	MODIFIER_MASTER struct {
		uint8_t cmdId;
		uint16_t crc;
	} master;
	MODIFIER_SLAVE struct {
		uint16_t currentMilliamps;
		uint16_t currentLimitMilliamps;
		uint16_t crc;
	} slave;
} PACKED;
static_assert(sizeof(struct cmCmd_ReadCurrentValues) == 9);
/*****************************************************************************
	struct cmCmd_ReadCurrentValues cmd;
	memset(&cmd, 0, sizeof(cmd));
	cmd.master.cmdId = CM_READCURRENTVALUES_CMDID;
	spiTransmitToSlave(SLAVE_CURRENTMONITOR, &cmd, CM_READCURRENTVALUES_TOTALLEN, CM_READCURRENTVALUES_MASTERLEN, CM_READCURRENTVALUES_DELAY_US);
*****************************************************************************/



#ifdef SPI_SLAVE
void spiSlaveInit(void);
void checkSPIForReset(void);

void executeReadCurrentValues(struct cmCmd_ReadCurrentValues *aCommand);
#endif

#endif
