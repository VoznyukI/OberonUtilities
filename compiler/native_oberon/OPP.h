/* voc 2.1.0 [2017/09/06]. Bootstrapping compiler for address size 8, alignment 8. xtaSv */

#ifndef OPP__h
#define OPP__h

#include "SYSTEM.h"
#include "OPS.h"
#include "OPT.h"


import CHAR OPP_SignOnMessage[80];


import void OPP_Module (OPT_Node *prog, OPS_Name modName);
import void *OPP__init(void);


#endif // OPP
