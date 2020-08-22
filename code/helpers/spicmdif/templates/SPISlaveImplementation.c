#include "SPISlave.h"

%for cmd in cmddef.cmds:
void execute${cmd.name}(struct ${cmddef.getproperty("cmdprefix")}${cmd.name} *aCommand) {
}

%endfor

