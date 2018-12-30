/* voc 2.1.0 [2017/09/06]. Bootstrapping compiler for address size 8, alignment 8. xtaSv */

#ifndef OPS__h
#define OPS__h

#include "SYSTEM.h"

typedef
	void (*OPS_GetProc)(INT8*);

typedef
	CHAR OPS_Name[32];

typedef
	CHAR OPS_String[256];

typedef
	struct OPS_Tok *OPS_Token;

typedef
	struct OPS_Tok {
		INT32 pos;
		INT8 sym;
		OPS_Token next;
	} OPS_Tok;

typedef
	OPS_Tok *OPS_Token;


import OPS_Name OPS_name;
import OPS_String OPS_str;
import INT16 OPS_numtyp;
import INT32 OPS_intval;
import REAL OPS_realval;
import LONGREAL OPS_lrlval;
import OPS_GetProc OPS_Get;
import CHAR OPS_ch;

import ADDRESS *OPS_Tok__typ;

import BOOLEAN OPS_CheckCardinality (OPS_Name name, INT8 nofp);
import void OPS_CheckOperator (INT8 *id);
import void OPS_Init (void);
import void OPS_Number (void);
import void OPS_StartPlaying (OPS_Token s);
import void OPS_StartRecording (INT8 sym);
import void OPS_StopRecording (OPS_Token *s);
import void *OPS__init(void);


#endif // OPS
