/* voc 2.1.0 [2017/09/06]. Bootstrapping compiler for address size 8, alignment 8. xtaSv */

#ifndef Modules__h
#define Modules__h

#include "SYSTEM.h"
#include "Kernel.h"


import INT16 Modules_res;
import CHAR Modules_resMsg[256];
import CHAR Modules_extension[8];


import Kernel_Module Modules_FindMod (CHAR *name, ADDRESS name__len);
import void Modules_Free (CHAR *name, ADDRESS name__len, BOOLEAN all);
import void Modules_InstallTermHandler (Kernel_Proc h);
import Kernel_Proc Modules_ThisCommand (Kernel_Module mod, CHAR *name, ADDRESS name__len);
import Kernel_Module Modules_ThisMod (CHAR *name, ADDRESS name__len);
import void *Modules__init(void);


#endif // Modules
