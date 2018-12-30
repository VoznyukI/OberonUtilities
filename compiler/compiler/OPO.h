/* voc 2.1.0 [2017/09/06]. Bootstrapping compiler for address size 8, alignment 8. xtaSv */

#ifndef OPO__h
#define OPO__h

#include "SYSTEM.h"

typedef
	struct {
		ADDRESS len[1];
		CHAR data[1];
	} *OPO_ConstArray;


import INT32 OPO_pc, OPO_dsize, OPO_csize;
import INT8 OPO_lastImmSize;
import OPO_ConstArray OPO_constant;
import CHAR OPO_code[65000];
import BOOLEAN OPO_CodeErr;


import void OPO_GenBT (INT8 mode, INT16 reg, INT16 base, INT16 inx, INT8 scale, INT32 disp, INT32 imm);
import void OPO_GenBTR (INT8 mode, INT16 reg, INT16 base, INT16 inx, INT8 scale, INT32 disp, INT32 imm);
import void OPO_GenBTS (INT8 mode, INT16 reg, INT16 base, INT16 inx, INT8 scale, INT32 disp, INT32 imm);
import void OPO_GenCALL (INT8 mode, INT16 reg, INT16 base, INT16 inx, INT8 scale, INT32 disp);
import void OPO_GenDEC (INT8 mode, INT16 reg, INT16 base, INT16 inx, INT8 scale, INT32 disp);
import void OPO_GenFADD (INT8 mode, INT8 size, INT16 base, INT16 inx, INT8 scale, INT32 disp);
import void OPO_GenFCOM (INT8 mode, INT8 size, INT16 base, INT16 inx, INT8 scale, INT32 disp);
import void OPO_GenFCOMP (INT8 mode, INT8 size, INT16 base, INT16 inx, INT8 scale, INT32 disp);
import void OPO_GenFDIV (INT8 mode, INT8 size, INT16 base, INT16 inx, INT8 scale, INT32 disp);
import void OPO_GenFDIVR (INT8 mode, INT8 size, INT16 base, INT16 inx, INT8 scale, INT32 disp);
import void OPO_GenFFREE (INT16 freg);
import void OPO_GenFLD (INT8 mode, INT8 size, INT16 base, INT16 inx, INT8 scale, INT32 disp);
import void OPO_GenFLDCW (INT16 base, INT16 inx, INT8 scale, INT32 disp);
import void OPO_GenFMUL (INT8 mode, INT8 size, INT16 base, INT16 inx, INT8 scale, INT32 disp);
import void OPO_GenFST (INT8 mode, INT8 size, INT16 base, INT16 inx, INT8 scale, INT32 disp);
import void OPO_GenFSTCW (INT16 base, INT16 inx, INT8 scale, INT32 disp);
import void OPO_GenFSTP (INT8 mode, INT8 size, INT16 base, INT16 inx, INT8 scale, INT32 disp);
import void OPO_GenFSUB (INT8 mode, INT8 size, INT16 base, INT16 inx, INT8 scale, INT32 disp);
import void OPO_GenFSUBR (INT8 mode, INT8 size, INT16 base, INT16 inx, INT8 scale, INT32 disp);
import void OPO_GenFop1 (INT16 op);
import void OPO_GenFtyp1 (INT8 op, INT8 mode, INT8 size, INT16 base, INT16 inx, INT8 scale, INT32 disp);
import void OPO_GenIDIV (INT8 mode, INT16 reg, INT16 base, INT16 inx, INT8 scale, INT32 disp);
import void OPO_GenIMUL (INT8 mode, BOOLEAN shortform, INT16 reg, INT16 base, INT16 inx, INT8 scale, INT32 disp, INT32 imm);
import void OPO_GenIN (INT16 size);
import void OPO_GenINC (INT8 mode, INT16 reg, INT16 base, INT16 inx, INT8 scale, INT32 disp);
import void OPO_GenINT (INT16 intNumber);
import void OPO_GenJMP (INT8 mode, INT16 reg, INT16 base, INT16 inx, INT8 scale, INT32 disp);
import void OPO_GenJcc (INT8 op, INT32 disp);
import void OPO_GenLEA (INT16 reg, INT16 base, INT16 inx, INT8 scale, INT32 disp);
import void OPO_GenMOV (INT8 mode, INT16 reg, INT16 base, INT16 inx, INT8 scale, INT32 disp, INT32 imm);
import void OPO_GenMOVSX (INT8 mode, INT8 s, INT16 reg, INT16 base, INT16 inx, INT8 scale, INT32 disp);
import void OPO_GenMOVZX (INT8 mode, INT8 s, INT16 reg, INT16 base, INT16 inx, INT8 scale, INT32 disp);
import void OPO_GenNEG (INT8 mode, INT16 reg, INT16 base, INT16 inx, INT8 scale, INT32 disp);
import void OPO_GenNOT (INT8 mode, INT16 reg, INT16 base, INT16 inx, INT8 scale, INT32 disp);
import void OPO_GenOUT (INT16 size);
import void OPO_GenPOP (INT8 mode, INT16 reg, INT16 base, INT16 inx, INT8 scale, INT32 disp);
import void OPO_GenPUSH (INT8 mode, INT16 reg, INT16 base, INT16 inx, INT8 scale, INT32 disp, INT32 imm);
import void OPO_GenRET (INT32 size);
import void OPO_GenRepCmpsScas (INT16 op, INT16 size);
import void OPO_GenRepString (INT16 op, INT16 size);
import void OPO_GenSetcc (INT8 op, INT8 mode, INT16 base, INT16 inx, INT8 scale, INT32 disp);
import void OPO_GenShiftRot (INT8 op, INT8 mode, INT16 reg, INT16 base, INT16 inx, INT8 scale, INT32 disp, INT32 imm);
import void OPO_GenString (INT16 op, INT16 size);
import void OPO_GenTEST (INT8 mode, INT16 reg, INT16 base, INT16 inx, INT8 scale, INT32 disp, INT32 imm);
import void OPO_GenTyp1 (INT8 op, INT8 mode, INT16 reg, INT16 base, INT16 inx, INT8 scale, INT32 disp, INT32 imm);
import void OPO_GenXCHG (INT8 mode, INT16 reg, INT16 base, INT16 inx, INT8 scale, INT32 disp);
import void OPO_GetConsDWord (INT32 pos, INT32 *dw);
import void OPO_GetDWord (INT32 pos, INT32 *dw);
import void OPO_InlineCode (CHAR *code, ADDRESS code__len, INT16 parSize);
import void OPO_Prefix (INT16 reg, INT8 *w);
import void OPO_PutByte (INT16 b);
import void OPO_PutByteAt (INT32 pos, INT16 byte);
import void OPO_PutConsDWord (INT32 pos, INT32 dw);
import void OPO_PutDWord (INT32 dw);
import void OPO_PutDWordAt (INT32 pos, INT32 dw);
import void *OPO__init(void);


#endif // OPO
