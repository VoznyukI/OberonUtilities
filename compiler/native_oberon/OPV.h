/* voc 2.1.0 [2017/09/06]. Bootstrapping compiler for address size 8, alignment 8. xtaSv */

#ifndef OPV__h
#define OPV__h

#include "SYSTEM.h"
#include "OPS.h"
#include "OPT.h"


import BOOLEAN OPV_dumpCode;
import OPS_Name OPV_ProcName;
import INT16 OPV_EntryNr;


import void OPV_AdrAndSize (OPT_Object topScope);
import void OPV_AssignEntries (OPT_Object obj, BOOLEAN browse);
import void OPV_Init (INT32 bpc);
import void OPV_Module (OPT_Node prog);
import void OPV_TypSize (OPT_Struct typ, BOOLEAN allocDesc);
import void *OPV__init(void);


#endif // OPV
