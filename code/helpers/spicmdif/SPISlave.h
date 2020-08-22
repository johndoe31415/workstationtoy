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

#define CM_TESTSPI_CMDID			0x0
#define CM_TESTSPI_MASTERLEN		11
#define CM_TESTSPI_DELAY_US		500
#define CM_TESTSPI_TOTALLEN		21
struct cmCmd_TestSPI {
	MODIFIER_MASTER struct {
		uint8_t cmdId;
		uint16_t crc;
		uint8_t challenge[8];
	} master;
	MODIFIER_SLAVE struct {
		uint8_t response[8];
		uint16_t crc;
	} slave;
} PACKED;
static_assert(sizeof(struct cmCmd_TestSPI) == 21);
/*****************************************************************************
	struct cmCmd_TestSPI cmd;
	memset(&cmd, 0, sizeof(cmd));
	cmd.master.cmdId = CM_TESTSPI_CMDID;
	spiTransmitWithPause(&cmd, sizeof(cmd), CM_TESTSPI_MASTERLEN, CM_TESTSPI_DELAY_US);
*****************************************************************************/




#ifdef SPI_SLAVE
void spiSlaveInit(void);
void checkSPIForReset(void);

void executeTestSPI(struct cmCmd_TestSPI *aCommand);
#endif

#endif
