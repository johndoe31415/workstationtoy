#ifndef __${cmddef.getproperty("includeguard")}_H__
#define __${cmddef.getproperty("includeguard")}_H__

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

%for enum in cmddef.enums:
enum ${cmddef.getproperty("enumprefix")}${enum.name} {
	%for enumsymbol in enum:
	%if not enumsymbol.hasfixedvalue():
	${enum.prefix}${enumsymbol.name.upper()},
	%else:
	${enum.prefix}${enumsymbol.name.upper()} = ${hex(enumsymbol.fixedvalue)},
	%endif
	%endfor
};

%endfor
%for cmd in cmddef.cmds:
#define ${cwrp.cmddefine(cmd, "CMDID")}			${hex(cmd.cmdid)}
#define ${cwrp.cmddefine(cmd, "MASTERLEN")}		${cmd.masterlen}
#define ${cwrp.cmddefine(cmd, "DELAY_US")}		${cmd.delay}
#define ${cwrp.cmddefine(cmd, "TOTALLEN")}		${len(cmd)}
struct ${cmddef.getproperty("cmdprefix")}${cmd.name} {
	%if cmd.mastercnt > 0:
	MODIFIER_MASTER struct {
		%for element in cmd.masteriter:
		${cwrp.structelement_to_declaration(element)};
		%endfor
	} master;
	%endif
	%if cmd.slavecnt > 0:
	MODIFIER_SLAVE struct {
		%for element in cmd.slaveiter:
		${cwrp.structelement_to_declaration(element)};
		%endfor
	} slave;
	%endif
} PACKED;
static_assert(sizeof(struct ${cmddef.getproperty("cmdprefix")}${cmd.name}) == ${len(cmd)});
/*****************************************************************************
	struct ${cmddef.getproperty("cmdprefix")}${cmd.name} cmd;
	memset(&cmd, 0, sizeof(cmd));
	cmd.master.${cmddef.getproperty("cmdidfieldname")} = ${cwrp.cmddefine(cmd, "CMDID")};
	spiTransmitToSlave(SLAVE_${cmddef.getproperty("slavename")}, &cmd, ${cwrp.cmddefine(cmd, "TOTALLEN")}, ${cwrp.cmddefine(cmd, "MASTERLEN")}, ${cwrp.cmddefine(cmd, "DELAY_US")});
*****************************************************************************/


%endfor

#ifdef SPI_SLAVE
void spiSlaveInit(void);
void checkSPIForReset(void);

%for cmd in cmddef.cmds:
void execute${cmd.name}(struct ${cmddef.getproperty("cmdprefix")}${cmd.name} *aCommand);
%endfor
#endif

#endif
