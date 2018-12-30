/* voc 2.1.0 [2017/09/06]. Bootstrapping compiler for address size 8, alignment 8. xtaSv */

#ifndef OPL__h
#define OPL__h

#include "SYSTEM.h"
#include "OPT.h"

struct OPL__1 {
	INT32 pos, pc;
};

typedef
	struct OPL_Instruction {
		INT8 scale, reg;
		INT16 op;
		INT32 dest, src1, src2, inx, pc, hint;
		INT16 link, used;
		OPT_Node node;
		BOOLEAN abs;
	} OPL_Instruction;

typedef
	struct {
		ADDRESS len[1];
		OPL_Instruction data[1];
	} *OPL_InstructionTable;

typedef
	struct OPL__1 *OPL_MapDesc;

typedef
	struct {
		ADDRESS len[1];
		struct OPL__1 data[1];
	} *OPL_Map;


import OPL_InstructionTable OPL_Instr;
import INT32 OPL_mapSize;
import OPL_Map OPL_map;
import INT32 OPL_linkTable, OPL_gVarLink;

import ADDRESS *OPL_Instruction__typ;
import ADDRESS *OPL__1__typ;

import void OPL_AllocCaseTab (INT32 low, INT32 high, INT32 *tab);
import void OPL_AllocConst (SYSTEM_BYTE *s, ADDRESS s__len, INT32 len, INT32 align, INT32 *adr);
import void OPL_AllocTypDesc (OPT_Struct typ);
import void OPL_CaseJump (INT32 Label, INT32 tab, INT32 from, INT32 to);
import void OPL_Close (void);
import void OPL_FixupLocalProcCall (OPT_Object proc);
import void OPL_GenCode (INT16 pSize);
import void OPL_Init (void);
import void OPL_NewEntry (INT32 *entryNr);
import void OPL_NewLink (INT32 mod, INT32 entry, INT32 *index);
import void OPL_NewVarCons (INT16 mod, INT16 entry, INT32 *index);
import void OPL_OutCode (CHAR *modName, ADDRESS modName__len);
import void OPL_OutRefName (CHAR *name, ADDRESS name__len);
import void OPL_OutRefPoint (OPT_Object proc);
import void OPL_OutRefs (OPT_Object obj);
import void *OPL__init(void);


#endif // OPL
