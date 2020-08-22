#ifndef __SPISLAVEVM_H__
#define __SPISLAVEVM_H__

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

#define VM_TESTSPI_CMDID			0x0
#define VM_TESTSPI_MASTERLEN		11
#define VM_TESTSPI_DELAY_US		500
#define VM_TESTSPI_TOTALLEN		21
struct vmCmd_TestSPI {
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
static_assert(sizeof(struct vmCmd_TestSPI) == 21);
/*****************************************************************************
	struct vmCmd_TestSPI cmd;
	memset(&cmd, 0, sizeof(cmd));
	cmd.master.cmdId = VM_TESTSPI_CMDID;
	spiTransmitToSlave(SLAVE_FOOBAR, &cmd, VM_TESTSPI_TOTALLEN, VM_TESTSPI_MASTERLEN, VM_TESTSPI_DELAY_US);
*****************************************************************************/



#ifdef SPI_SLAVE
void spiSlaveInit(void);
void checkSPIForReset(void);

void executeTestSPI(struct vmCmd_TestSPI *aCommand);
#endif

#endif
