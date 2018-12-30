/* voc 2.1.0 [2017/09/06]. Bootstrapping compiler for address size 8, alignment 8. xtaSv */

#define SHORTINT INT8
#define INTEGER  INT16
#define LONGINT  INT32
#define SET      UINT32

#include "SYSTEM.h"
#include "OPM.h"
#include "OPT.h"

typedef
	struct {
		ADDRESS len[1];
		CHAR data[1];
	} *OPO_ConstArray;


export INT32 OPO_pc, OPO_dsize, OPO_csize;
export INT8 OPO_lastImmSize;
export OPO_ConstArray OPO_constant;
export CHAR OPO_code[65000];
export BOOLEAN OPO_CodeErr;


export void OPO_GenBT (INT8 mode, INT16 reg, INT16 base, INT16 inx, INT8 scale, INT32 disp, INT32 imm);
export void OPO_GenBTR (INT8 mode, INT16 reg, INT16 base, INT16 inx, INT8 scale, INT32 disp, INT32 imm);
export void OPO_GenBTS (INT8 mode, INT16 reg, INT16 base, INT16 inx, INT8 scale, INT32 disp, INT32 imm);
export void OPO_GenCALL (INT8 mode, INT16 reg, INT16 base, INT16 inx, INT8 scale, INT32 disp);
export void OPO_GenDEC (INT8 mode, INT16 reg, INT16 base, INT16 inx, INT8 scale, INT32 disp);
export void OPO_GenFADD (INT8 mode, INT8 size, INT16 base, INT16 inx, INT8 scale, INT32 disp);
export void OPO_GenFCOM (INT8 mode, INT8 size, INT16 base, INT16 inx, INT8 scale, INT32 disp);
export void OPO_GenFCOMP (INT8 mode, INT8 size, INT16 base, INT16 inx, INT8 scale, INT32 disp);
export void OPO_GenFDIV (INT8 mode, INT8 size, INT16 base, INT16 inx, INT8 scale, INT32 disp);
export void OPO_GenFDIVR (INT8 mode, INT8 size, INT16 base, INT16 inx, INT8 scale, INT32 disp);
export void OPO_GenFFREE (INT16 freg);
export void OPO_GenFLD (INT8 mode, INT8 size, INT16 base, INT16 inx, INT8 scale, INT32 disp);
export void OPO_GenFLDCW (INT16 base, INT16 inx, INT8 scale, INT32 disp);
export void OPO_GenFMUL (INT8 mode, INT8 size, INT16 base, INT16 inx, INT8 scale, INT32 disp);
export void OPO_GenFST (INT8 mode, INT8 size, INT16 base, INT16 inx, INT8 scale, INT32 disp);
export void OPO_GenFSTCW (INT16 base, INT16 inx, INT8 scale, INT32 disp);
export void OPO_GenFSTP (INT8 mode, INT8 size, INT16 base, INT16 inx, INT8 scale, INT32 disp);
export void OPO_GenFSUB (INT8 mode, INT8 size, INT16 base, INT16 inx, INT8 scale, INT32 disp);
export void OPO_GenFSUBR (INT8 mode, INT8 size, INT16 base, INT16 inx, INT8 scale, INT32 disp);
export void OPO_GenFop1 (INT16 op);
export void OPO_GenFtyp1 (INT8 op, INT8 mode, INT8 size, INT16 base, INT16 inx, INT8 scale, INT32 disp);
export void OPO_GenIDIV (INT8 mode, INT16 reg, INT16 base, INT16 inx, INT8 scale, INT32 disp);
export void OPO_GenIMUL (INT8 mode, BOOLEAN shortform, INT16 reg, INT16 base, INT16 inx, INT8 scale, INT32 disp, INT32 imm);
export void OPO_GenIN (INT16 size);
export void OPO_GenINC (INT8 mode, INT16 reg, INT16 base, INT16 inx, INT8 scale, INT32 disp);
export void OPO_GenINT (INT16 intNumber);
export void OPO_GenJMP (INT8 mode, INT16 reg, INT16 base, INT16 inx, INT8 scale, INT32 disp);
export void OPO_GenJcc (INT8 op, INT32 disp);
export void OPO_GenLEA (INT16 reg, INT16 base, INT16 inx, INT8 scale, INT32 disp);
export void OPO_GenMOV (INT8 mode, INT16 reg, INT16 base, INT16 inx, INT8 scale, INT32 disp, INT32 imm);
export void OPO_GenMOVSX (INT8 mode, INT8 s, INT16 reg, INT16 base, INT16 inx, INT8 scale, INT32 disp);
export void OPO_GenMOVZX (INT8 mode, INT8 s, INT16 reg, INT16 base, INT16 inx, INT8 scale, INT32 disp);
export void OPO_GenNEG (INT8 mode, INT16 reg, INT16 base, INT16 inx, INT8 scale, INT32 disp);
export void OPO_GenNOT (INT8 mode, INT16 reg, INT16 base, INT16 inx, INT8 scale, INT32 disp);
export void OPO_GenOUT (INT16 size);
export void OPO_GenPOP (INT8 mode, INT16 reg, INT16 base, INT16 inx, INT8 scale, INT32 disp);
export void OPO_GenPUSH (INT8 mode, INT16 reg, INT16 base, INT16 inx, INT8 scale, INT32 disp, INT32 imm);
export void OPO_GenRET (INT32 size);
export void OPO_GenRepCmpsScas (INT16 op, INT16 size);
export void OPO_GenRepString (INT16 op, INT16 size);
export void OPO_GenSetcc (INT8 op, INT8 mode, INT16 base, INT16 inx, INT8 scale, INT32 disp);
export void OPO_GenShiftRot (INT8 op, INT8 mode, INT16 reg, INT16 base, INT16 inx, INT8 scale, INT32 disp, INT32 imm);
export void OPO_GenString (INT16 op, INT16 size);
export void OPO_GenTEST (INT8 mode, INT16 reg, INT16 base, INT16 inx, INT8 scale, INT32 disp, INT32 imm);
export void OPO_GenTyp1 (INT8 op, INT8 mode, INT16 reg, INT16 base, INT16 inx, INT8 scale, INT32 disp, INT32 imm);
export void OPO_GenXCHG (INT8 mode, INT16 reg, INT16 base, INT16 inx, INT8 scale, INT32 disp);
static void OPO_GetByte (INT32 pos, INT16 *byte);
export void OPO_GetConsDWord (INT32 pos, INT32 *dw);
export void OPO_GetDWord (INT32 pos, INT32 *dw);
export void OPO_InlineCode (CHAR *code, ADDRESS code__len, INT16 parSize);
export void OPO_Prefix (INT16 reg, INT8 *w);
export void OPO_PutByte (INT16 b);
export void OPO_PutByteAt (INT32 pos, INT16 byte);
export void OPO_PutConsDWord (INT32 pos, INT32 dw);
export void OPO_PutDWord (INT32 dw);
export void OPO_PutDWordAt (INT32 pos, INT32 dw);
static void OPO_PutDisp (INT32 disp, INT16 size);
static void OPO_PutMem (INT16 reg, INT16 base, INT16 inx, INT8 scale, INT32 disp);
static void OPO_PutRMInx (INT8 mode, INT16 reg, INT16 base, INT16 inx, INT16 scale, INT32 disp);
static void OPO_PutReg (INT16 reg1, INT16 reg2);
static void OPO_PutRegMem (INT8 mode, INT16 reg, INT16 base, INT32 disp);
static void OPO_PutWord (INT32 w);


void OPO_PutByte (INT16 b)
{
	if (OPO_pc >= 65000) {
		if (!OPO_CodeErr) {
			OPM_err(210);
			OPO_CodeErr = 1;
		}
		OPO_pc = 0;
	} else {
		OPO_code[__X(OPO_pc, 65000)] = (CHAR)b;
		OPO_pc += 1;
		if (OPO_pc >= OPM_breakpc) {
			OPM_err(255);
			OPM_breakpc = 2147483647;
		}
	}
}

static void OPO_PutWord (INT32 w)
{
	if (OPO_pc >= 64998) {
		if (!OPO_CodeErr) {
			OPM_err(210);
			OPO_CodeErr = 1;
		}
		OPO_pc = 0;
	} else {
		OPO_code[__X(OPO_pc, 65000)] = (CHAR)__MASK(w, -256);
		OPO_pc += 1;
		OPO_code[__X(OPO_pc, 65000)] = (CHAR)__MASK(__ASHR(w, 8), -256);
		OPO_pc += 1;
		if (OPO_pc >= OPM_breakpc) {
			OPM_err(255);
			OPM_breakpc = 2147483647;
		}
	}
}

void OPO_PutDWord (INT32 dw)
{
	if (OPO_pc >= 64996) {
		if (!OPO_CodeErr) {
			OPM_err(210);
			OPO_CodeErr = 1;
		}
		OPO_pc = 0;
	} else {
		OPO_code[__X(OPO_pc, 65000)] = (CHAR)__MASK(dw, -256);
		OPO_pc += 1;
		OPO_code[__X(OPO_pc, 65000)] = (CHAR)__MASK(__ASHR(dw, 8), -256);
		OPO_pc += 1;
		OPO_code[__X(OPO_pc, 65000)] = (CHAR)__MASK(__ASHR(dw, 16), -256);
		OPO_pc += 1;
		OPO_code[__X(OPO_pc, 65000)] = (CHAR)__ASHR(dw, 24);
		OPO_pc += 1;
		if (OPO_pc >= OPM_breakpc) {
			OPM_err(255);
			OPM_breakpc = 2147483647;
		}
	}
}

void OPO_PutByteAt (INT32 pos, INT16 byte)
{
	INT32 currentPC;
	currentPC = OPO_pc;
	OPO_pc = pos;
	OPO_PutByte(byte);
	OPO_pc = currentPC;
}

void OPO_PutDWordAt (INT32 pos, INT32 dw)
{
	INT32 currentPC;
	currentPC = OPO_pc;
	OPO_pc = pos;
	OPO_PutDWord(dw);
	OPO_pc = currentPC;
}

static void OPO_GetByte (INT32 pos, INT16 *byte)
{
	*byte = (INT16)OPO_code[__X(pos, 65000)];
}

void OPO_GetDWord (INT32 pos, INT32 *dw)
{
	INT16 byte;
	*dw = (OPO_code[__X(pos, 65000)] + __ASHL(OPO_code[__X(pos + 1, 65000)], 8)) + __ASHL(OPO_code[__X(pos + 2, 65000)], 16);
	byte = (INT16)OPO_code[__X(pos + 3, 65000)];
	if (byte >= 128) {
		byte = byte - 256;
	}
	*dw = __ASHL(byte, 24) + *dw;
}

void OPO_PutConsDWord (INT32 pos, INT32 dw)
{
	(OPO_constant->data)[__X(pos, OPO_constant->len[0])] = (CHAR)__MASK(dw, -256);
	(OPO_constant->data)[__X(pos + 1, OPO_constant->len[0])] = (CHAR)__MASK(__ASHR(dw, 8), -256);
	(OPO_constant->data)[__X(pos + 2, OPO_constant->len[0])] = (CHAR)__MASK(__ASHR(dw, 16), -256);
	(OPO_constant->data)[__X(pos + 3, OPO_constant->len[0])] = (CHAR)__ASHR(dw, 24);
}

void OPO_GetConsDWord (INT32 pos, INT32 *dw)
{
	INT16 byte;
	*dw = ((OPO_constant->data)[__X(pos, OPO_constant->len[0])] + __ASHL((OPO_constant->data)[__X(pos + 1, OPO_constant->len[0])], 8)) + __ASHL((OPO_constant->data)[__X(pos + 2, OPO_constant->len[0])], 16);
	byte = (INT16)(OPO_constant->data)[__X(pos + 3, OPO_constant->len[0])];
	if (byte >= 128) {
		byte = byte - 256;
	}
	*dw = __ASHL(byte, 24) + *dw;
}

static void OPO_PutReg (INT16 reg1, INT16 reg2)
{
	reg1 = __MASK(reg1, -8);
	reg2 = __MASK(reg2, -8);
	OPO_PutByte((192 + __ASHL(reg1, 3)) + reg2);
}

static void OPO_PutRMInx (INT8 mode, INT16 reg, INT16 base, INT16 inx, INT16 scale, INT32 disp)
{
	reg = __MASK(reg, -8);
	inx = __MASK(inx, -8);
	if (mode == 16) {
		OPO_PutByte(__ASHL(reg, 3) + 4);
		OPO_PutByte((__ASHL(scale, 6) + __ASHL(inx, 3)) + 5);
		OPO_PutDWord(disp);
	} else {
		base = __MASK(base, -8);
		if ((disp == 0 && base != 5)) {
			OPO_PutByte(__ASHL(reg, 3) + 4);
			OPO_PutByte((__ASHL(scale, 6) + __ASHL(inx, 3)) + base);
		} else if ((disp <= 127 && disp >= -128)) {
			OPO_PutByte((64 + __ASHL(reg, 3)) + 4);
			OPO_PutByte((__ASHL(scale, 6) + __ASHL(inx, 3)) + base);
			OPO_PutByte((INT16)disp);
		} else {
			OPO_PutByte((128 + __ASHL(reg, 3)) + 4);
			OPO_PutByte((__ASHL(scale, 6) + __ASHL(inx, 3)) + base);
			OPO_PutDWord(disp);
		}
	}
}

static void OPO_PutRegMem (INT8 mode, INT16 reg, INT16 base, INT32 disp)
{
	reg = __MASK(reg, -8);
	if (mode == 16) {
		OPO_PutByte(__ASHL(reg, 3) + 5);
		OPO_PutDWord(disp);
	} else {
		base = __MASK(base, -8);
		if (base == 4) {
			OPO_PutRMInx(mode, reg, base, 4, 0, disp);
		} else if ((disp == 0 && base != 5)) {
			OPO_PutByte(__ASHL(reg, 3) + base);
		} else if ((disp <= 127 && disp >= -128)) {
			OPO_PutByte((64 + __ASHL(reg, 3)) + base);
			OPO_PutByte((INT16)disp);
		} else {
			OPO_PutByte((128 + __ASHL(reg, 3)) + base);
			OPO_PutDWord(disp);
		}
	}
}

static void OPO_PutMem (INT16 reg, INT16 base, INT16 inx, INT8 scale, INT32 disp)
{
	if (base == -1) {
		if (inx == -1) {
			OPO_PutRegMem(16, reg, -1, disp);
		} else {
			OPO_PutRMInx(16, reg, -1, inx, scale, disp);
		}
	} else if (inx == -1) {
		OPO_PutRegMem(17, reg, base, disp);
	} else {
		OPO_PutRMInx(17, reg, base, inx, scale, disp);
	}
}

static void OPO_PutDisp (INT32 disp, INT16 size)
{
	OPO_lastImmSize = (INT8)size;
	if (size >= 16) {
		OPO_PutByte((INT16)disp);
	} else if (size >= 8) {
		OPO_PutWord(disp);
	} else {
		OPO_PutDWord(disp);
	}
}

void OPO_Prefix (INT16 reg, INT8 *w)
{
	if (__IN(reg, 0xff00, 32)) {
		OPO_PutByte(102);
		*w = 1;
	} else if (__IN(reg, 0xff, 32)) {
		*w = 1;
	} else {
		*w = 0;
	}
}

void OPO_GenMOV (INT8 mode, INT16 reg, INT16 base, INT16 inx, INT8 scale, INT32 disp, INT32 imm)
{
	INT8 w;
	INT16 r;
	OPO_Prefix(reg, &w);
	switch (mode) {
		case 0: 
			OPO_PutByte(138 + (INT16)w);
			OPO_PutReg(reg, base);
			break;
		case 1: 
			if ((((((reg == 0 || reg == 8) || reg == 16) && inx == -1)) && base == -1)) {
				OPO_PutByte(162 + (INT16)w);
				OPO_PutDWord(disp);
			} else {
				OPO_PutByte(136 + (INT16)w);
				OPO_PutMem(reg, base, inx, scale, disp);
			}
			break;
		case 2: 
			if ((((((reg == 0 || reg == 8) || reg == 16) && inx == -1)) && base == -1)) {
				OPO_PutByte(160 + (INT16)w);
				OPO_PutDWord(disp);
			} else {
				OPO_PutByte(138 + (INT16)w);
				OPO_PutMem(reg, base, inx, scale, disp);
			}
			break;
		case 3: 
			r = reg;
			reg = __MASK(reg, -8);
			OPO_PutByte((176 + (INT16)__ASHL(w, 3)) + reg);
			OPO_PutDisp(imm, r);
			break;
		case 4: 
			OPO_PutByte(198 + (INT16)w);
			OPO_PutMem(reg, base, inx, scale, disp);
			OPO_PutDisp(imm, reg);
			break;
		default: 
			__HALT(42);
			break;
	}
}

void OPO_GenMOVSX (INT8 mode, INT8 s, INT16 reg, INT16 base, INT16 inx, INT8 scale, INT32 disp)
{
	INT8 w;
	OPO_Prefix(reg, &w);
	OPO_PutByte(15);
	OPO_PutByte(190 + (INT16)s);
	switch (mode) {
		case 0: 
			OPO_PutReg(reg, base);
			break;
		case 2: 
			OPO_PutMem(reg, base, inx, scale, disp);
			break;
		default: 
			__HALT(42);
			break;
	}
}

void OPO_GenMOVZX (INT8 mode, INT8 s, INT16 reg, INT16 base, INT16 inx, INT8 scale, INT32 disp)
{
	INT8 w;
	OPO_Prefix(reg, &w);
	OPO_PutByte(15);
	OPO_PutByte(182 + (INT16)s);
	switch (mode) {
		case 0: 
			OPO_PutReg(reg, base);
			break;
		case 2: 
			OPO_PutMem(reg, base, inx, scale, disp);
			break;
		default: 
			__HALT(42);
			break;
	}
}

void OPO_GenIN (INT16 size)
{
	switch (size) {
		case 0: 
			OPO_PutByte(237);
			break;
		case 8: 
			OPO_PutWord(60774);
			break;
		case 16: 
			OPO_PutByte(236);
			break;
		default: __CASECHK;
	}
}

void OPO_GenOUT (INT16 size)
{
	switch (size) {
		case 0: 
			OPO_PutByte(239);
			break;
		case 8: 
			OPO_PutWord(61286);
			break;
		case 16: 
			OPO_PutByte(238);
			break;
		default: __CASECHK;
	}
}

void OPO_GenPUSH (INT8 mode, INT16 reg, INT16 base, INT16 inx, INT8 scale, INT32 disp, INT32 imm)
{
	INT8 w;
	OPO_Prefix(reg, &w);
	switch (mode) {
		case 0: 
			reg = __MASK(reg, -8);
			OPO_PutByte(80 + reg);
			break;
		case 2: 
			reg = 6;
			OPO_PutByte(255);
			OPO_PutMem(reg, base, inx, scale, disp);
			break;
		case 3: 
			if ((imm <= 127 && imm >= -128)) {
				OPO_PutByte(106);
				OPO_PutByte((INT16)imm);
			} else {
				OPO_PutByte(104);
				OPO_PutDWord(imm);
			}
			break;
		default: 
			__HALT(42);
			break;
	}
}

void OPO_GenPOP (INT8 mode, INT16 reg, INT16 base, INT16 inx, INT8 scale, INT32 disp)
{
	INT8 w;
	OPO_Prefix(reg, &w);
	switch (mode) {
		case 0: 
			reg = __MASK(reg, -8);
			OPO_PutByte(88 + reg);
			break;
		case 2: 
			reg = 0;
			OPO_PutByte(143);
			OPO_PutMem(reg, base, inx, scale, disp);
			break;
		default: 
			__HALT(42);
			break;
	}
}

void OPO_GenXCHG (INT8 mode, INT16 reg, INT16 base, INT16 inx, INT8 scale, INT32 disp)
{
	INT8 w;
	OPO_Prefix(reg, &w);
	switch (mode) {
		case 0: 
			if (reg == 0 || reg == 8) {
				base = __MASK(base, -8);
				OPO_PutByte(144 + base);
			} else {
				OPO_PutByte(134 + (INT16)w);
				OPO_PutReg(reg, base);
			}
			break;
		case 1: 
			OPO_PutByte(134 + (INT16)w);
			OPO_PutMem(reg, base, inx, scale, disp);
			break;
		default: 
			__HALT(42);
			break;
	}
}

void OPO_GenLEA (INT16 reg, INT16 base, INT16 inx, INT8 scale, INT32 disp)
{
	if ((((reg == base && inx == -1)) && disp == 0)) {
	} else {
		OPO_PutByte(141);
		OPO_PutMem(reg, base, inx, scale, disp);
	}
}

void OPO_GenTyp1 (INT8 op, INT8 mode, INT16 reg, INT16 base, INT16 inx, INT8 scale, INT32 disp, INT32 imm)
{
	INT8 w, wImm;
	OPO_Prefix(reg, &w);
	switch (mode) {
		case 0: 
			OPO_PutByte((op + 2) + w);
			OPO_PutReg(reg, base);
			break;
		case 1: 
			OPO_PutByte(op + w);
			OPO_PutMem(reg, base, inx, scale, disp);
			break;
		case 2: 
			OPO_PutByte((op + 2) + w);
			OPO_PutMem(reg, base, inx, scale, disp);
			break;
		case 3: 
			if ((reg == 0 || reg == 8) || reg == 16) {
				OPO_PutByte((op + 4) + w);
				OPO_PutDisp(imm, reg);
			} else {
				if (reg >= 16) {
					OPO_PutByte(128);
					wImm = 16;
				} else if ((imm <= 127 && imm >= -128)) {
					OPO_PutByte(131);
					wImm = 16;
				} else {
					OPO_PutByte(129);
					wImm = (INT8)reg;
				}
				OPO_PutReg(__ASHR(op, 3), reg);
				OPO_PutDisp(imm, wImm);
			}
			break;
		case 4: 
			if (reg >= 16) {
				OPO_PutByte(128);
				wImm = 16;
			} else if ((imm <= 127 && imm >= -128)) {
				OPO_PutByte(131);
				wImm = 16;
			} else {
				OPO_PutByte(129);
				wImm = (INT8)reg;
			}
			OPO_PutMem(__ASHR(op, 3), base, inx, scale, disp);
			OPO_PutDisp(imm, wImm);
			break;
		default: 
			__HALT(42);
			break;
	}
}

void OPO_GenINC (INT8 mode, INT16 reg, INT16 base, INT16 inx, INT8 scale, INT32 disp)
{
	INT8 w;
	OPO_Prefix(reg, &w);
	if (mode == 3) {
		if (w != 0) {
			reg = __MASK(reg, -8);
			OPO_PutByte(64 + reg);
		} else {
			OPO_PutByte(254 + (INT16)w);
			OPO_PutReg(0, reg);
		}
	} else {
		OPO_PutByte(254 + (INT16)w);
		OPO_PutMem(0, base, inx, scale, disp);
	}
}

void OPO_GenDEC (INT8 mode, INT16 reg, INT16 base, INT16 inx, INT8 scale, INT32 disp)
{
	INT8 w;
	OPO_Prefix(reg, &w);
	if (mode == 3) {
		if (w != 0) {
			reg = __MASK(reg, -8);
			OPO_PutByte(72 + reg);
		} else {
			OPO_PutByte(254 + (INT16)w);
			OPO_PutReg(1, reg);
		}
	} else {
		OPO_PutByte(254 + (INT16)w);
		OPO_PutMem(1, base, inx, scale, disp);
	}
}

void OPO_GenNEG (INT8 mode, INT16 reg, INT16 base, INT16 inx, INT8 scale, INT32 disp)
{
	INT8 w;
	OPO_Prefix(reg, &w);
	OPO_PutByte(246 + (INT16)w);
	if (mode == 0) {
		OPO_PutReg(3, reg);
	} else {
		OPO_PutMem(3, base, inx, scale, disp);
	}
}

void OPO_GenIMUL (INT8 mode, BOOLEAN shortform, INT16 reg, INT16 base, INT16 inx, INT8 scale, INT32 disp, INT32 imm)
{
	INT8 w;
	OPO_Prefix(reg, &w);
	switch (mode) {
		case 0: 
			if (shortform) {
				OPO_PutByte(246 + (INT16)w);
				OPO_PutReg(5, base);
			} else {
				OPO_PutByte(15);
				OPO_PutByte(175);
				OPO_PutReg(reg, base);
			}
			break;
		case 2: 
			if (shortform) {
				OPO_PutByte(246 + (INT16)w);
				OPO_PutMem(5, base, inx, scale, disp);
			} else {
				OPO_PutByte(15);
				OPO_PutByte(175);
				OPO_PutMem(reg, base, inx, scale, disp);
			}
			break;
		case 3: 
			if ((imm <= 127 && imm >= -128)) {
				OPO_PutByte(107);
				OPO_PutReg(reg, base);
				OPO_PutByte((INT16)imm);
			} else {
				OPO_PutByte(105);
				OPO_PutReg(reg, base);
				OPO_PutDisp(imm, base);
			}
			break;
		case 4: 
			if ((imm <= 127 && imm >= -128)) {
				OPO_PutByte(107);
				OPO_PutMem(reg, base, inx, scale, disp);
				OPO_PutByte((INT16)imm);
			} else {
				OPO_PutByte(105);
				OPO_PutMem(reg, base, inx, scale, disp);
				OPO_PutDisp(imm, base);
			}
			break;
		default: 
			__HALT(42);
			break;
	}
}

void OPO_GenIDIV (INT8 mode, INT16 reg, INT16 base, INT16 inx, INT8 scale, INT32 disp)
{
	INT8 w;
	OPO_Prefix(reg, &w);
	OPO_PutByte(246 + (INT16)w);
	if (mode == 0) {
		OPO_PutReg(7, reg);
	} else {
		OPO_PutMem(7, base, inx, scale, disp);
	}
}

void OPO_GenShiftRot (INT8 op, INT8 mode, INT16 reg, INT16 base, INT16 inx, INT8 scale, INT32 disp, INT32 imm)
{
	INT8 w;
	OPO_Prefix(reg, &w);
	switch (mode) {
		case 0: 
			OPO_PutByte(210 + (INT16)w);
			OPO_PutReg(op, reg);
			break;
		case 1: 
			OPO_PutByte(210 + (INT16)w);
			OPO_PutMem(op, base, inx, scale, disp);
			break;
		case 3: 
			if (imm == 1) {
				OPO_PutByte(208 + (INT16)w);
				OPO_PutReg(op, reg);
			} else {
				OPO_PutByte(192 + (INT16)w);
				OPO_PutReg(op, reg);
				OPO_PutByte((INT16)imm);
			}
			break;
		case 4: 
			if (imm == 1) {
				OPO_PutByte(208 + (INT16)w);
				OPO_PutMem(op, base, inx, scale, disp);
			} else {
				OPO_PutByte(192 + (INT16)w);
				OPO_PutMem(op, base, inx, scale, disp);
				OPO_PutByte((INT16)imm);
			}
			break;
		default: 
			__HALT(42);
			break;
	}
}

void OPO_GenNOT (INT8 mode, INT16 reg, INT16 base, INT16 inx, INT8 scale, INT32 disp)
{
	INT8 w;
	OPO_Prefix(reg, &w);
	OPO_PutByte(246 + (INT16)w);
	if (mode == 0) {
		OPO_PutReg(2, reg);
	} else {
		OPO_PutMem(2, base, inx, scale, disp);
	}
}

void OPO_GenString (INT16 op, INT16 size)
{
	INT8 w;
	OPO_Prefix(size, &w);
	OPO_PutByte(__ASHL(op, 1) + (INT16)w);
}

void OPO_GenRepString (INT16 op, INT16 size)
{
	INT8 w;
	OPO_Prefix(size, &w);
	OPO_PutByte(243);
	OPO_PutByte(__ASHL(op, 1) + (INT16)w);
}

void OPO_GenRepCmpsScas (INT16 op, INT16 size)
{
	INT8 w;
	OPO_Prefix(size, &w);
	OPO_PutByte(243);
	OPO_PutByte(__ASHL(op, 1) + (INT16)w);
}

void OPO_GenTEST (INT8 mode, INT16 reg, INT16 base, INT16 inx, INT8 scale, INT32 disp, INT32 imm)
{
	INT8 w;
	OPO_Prefix(reg, &w);
	switch (mode) {
		case 0: 
			if (w == 0) {
				OPO_PutByte(132);
			} else {
				OPO_PutByte(133);
			}
			OPO_PutReg(base, reg);
			break;
		case 1: 
			if (w == 0) {
				OPO_PutByte(132);
			} else {
				OPO_PutByte(133);
			}
			OPO_PutMem(reg, base, inx, scale, disp);
			break;
		case 3: 
			if (__IN(reg, 0x010101, 32)) {
				if (w == 0) {
					OPO_PutByte(168);
				} else {
					OPO_PutByte(169);
				}
				OPO_PutDisp(imm, __ASHL(__ASHR(reg, 3), 3));
			} else {
				if (w == 0) {
					OPO_PutByte(246);
				} else {
					OPO_PutByte(247);
				}
				OPO_PutReg(0, reg);
				OPO_PutDisp(imm, __ASHL(__ASHR(reg, 3), 3));
			}
			break;
		case 4: 
			if (w == 0) {
				OPO_PutByte(246);
			} else {
				OPO_PutByte(247);
			}
			OPO_PutMem(0, base, inx, scale, disp);
			OPO_PutDisp(imm, __ASHL(__ASHR(reg, 3), 3));
			break;
		default: 
			__HALT(42);
			break;
	}
}

void OPO_GenBT (INT8 mode, INT16 reg, INT16 base, INT16 inx, INT8 scale, INT32 disp, INT32 imm)
{
	INT8 w;
	OPO_Prefix(reg, &w);
	OPO_PutByte(15);
	switch (mode) {
		case 0: 
			OPO_PutByte(163);
			OPO_PutReg(base, reg);
			break;
		case 1: 
			OPO_PutByte(163);
			OPO_PutMem(reg, base, inx, scale, disp);
			break;
		case 3: 
			OPO_PutByte(186);
			OPO_PutReg(4, reg);
			OPO_PutByte((INT16)imm);
			break;
		case 4: 
			OPO_PutByte(186);
			OPO_PutMem(4, base, inx, scale, disp);
			OPO_PutByte((INT16)imm);
			break;
		default: 
			__HALT(42);
			break;
	}
}

void OPO_GenBTR (INT8 mode, INT16 reg, INT16 base, INT16 inx, INT8 scale, INT32 disp, INT32 imm)
{
	INT8 w;
	OPO_Prefix(reg, &w);
	OPO_PutByte(15);
	switch (mode) {
		case 0: 
			OPO_PutByte(179);
			OPO_PutReg(base, reg);
			break;
		case 1: 
			OPO_PutByte(179);
			OPO_PutMem(reg, base, inx, scale, disp);
			break;
		case 3: 
			OPO_PutByte(186);
			OPO_PutReg(6, reg);
			OPO_PutByte((INT16)imm);
			break;
		case 4: 
			OPO_PutByte(186);
			OPO_PutMem(6, base, inx, scale, disp);
			OPO_PutByte((INT16)imm);
			break;
		default: 
			__HALT(42);
			break;
	}
}

void OPO_GenBTS (INT8 mode, INT16 reg, INT16 base, INT16 inx, INT8 scale, INT32 disp, INT32 imm)
{
	INT8 w;
	OPO_Prefix(reg, &w);
	OPO_PutByte(15);
	switch (mode) {
		case 0: 
			OPO_PutByte(171);
			OPO_PutReg(base, reg);
			break;
		case 1: 
			OPO_PutByte(171);
			OPO_PutMem(reg, base, inx, scale, disp);
			break;
		case 3: 
			OPO_PutByte(186);
			OPO_PutReg(5, reg);
			OPO_PutByte((INT16)imm);
			break;
		case 4: 
			OPO_PutByte(186);
			OPO_PutMem(5, base, inx, scale, disp);
			OPO_PutByte((INT16)imm);
			break;
		default: 
			__HALT(42);
			break;
	}
}

void OPO_GenCALL (INT8 mode, INT16 reg, INT16 base, INT16 inx, INT8 scale, INT32 disp)
{
	if (mode == 3) {
		OPO_PutByte(232);
		OPO_PutDWord(disp);
	} else {
		OPO_PutByte(255);
		if (mode == 0) {
			OPO_PutReg(2, reg);
		} else {
			OPO_PutMem(2, base, inx, scale, disp);
		}
	}
}

void OPO_GenJMP (INT8 mode, INT16 reg, INT16 base, INT16 inx, INT8 scale, INT32 disp)
{
	if (mode == 3) {
		if ((disp <= 127 && disp >= -128)) {
			OPO_PutByte(235);
			OPO_PutByte((INT16)disp);
		} else {
			OPO_PutByte(233);
			OPO_PutDWord(disp);
		}
	} else {
		OPO_PutByte(255);
		if (mode == 0) {
			OPO_PutReg(4, reg);
		} else {
			OPO_PutMem(4, base, inx, scale, disp);
		}
	}
}

void OPO_GenRET (INT32 size)
{
	if (size == 0) {
		OPO_PutByte(195);
	} else if (size > 65535) {
		OPO_GenPOP(0, 3, -1, -1, 0, 0);
		OPO_GenTyp1(0, 3, 4, -1, -1, 0, 0, size);
		OPO_GenJMP(0, 3, -1, -1, 0, 0);
	} else {
		OPO_PutByte(194);
		OPO_PutWord(size);
	}
}

void OPO_GenJcc (INT8 op, INT32 disp)
{
	if ((disp <= 127 && disp >= -128)) {
		OPO_PutByte(112 + op);
		OPO_PutByte((INT16)disp);
	} else {
		OPO_PutByte(15);
		OPO_PutByte(128 + (INT16)op);
		OPO_PutDWord(disp);
	}
}

void OPO_GenSetcc (INT8 op, INT8 mode, INT16 base, INT16 inx, INT8 scale, INT32 disp)
{
	OPO_PutByte(15);
	OPO_PutByte(144 + (INT16)op);
	if (mode == 0) {
		OPO_PutReg(0, base);
	} else {
		OPO_PutMem(0, base, inx, scale, disp);
	}
}

void OPO_GenINT (INT16 intNumber)
{
	OPO_PutByte(205);
	OPO_PutByte(intNumber);
}

void OPO_InlineCode (CHAR *code, ADDRESS code__len, INT16 parSize)
{
	INT16 i, n;
	n = (INT16)code[0];
	i = 1;
	while (i <= n) {
		OPO_PutByte((INT16)code[__X(i, code__len)]);
		i += 1;
	}
}

void OPO_GenFLD (INT8 mode, INT8 size, INT16 base, INT16 inx, INT8 scale, INT32 disp)
{
	switch (mode) {
		case 0: 
			OPO_PutByte(217);
			OPO_PutByte(192 + base);
			break;
		case 2: 
			if (size == 4) {
				OPO_PutByte(219);
				OPO_PutMem(5, base, inx, scale, disp);
			} else {
				OPO_PutByte(217 + (INT16)__ASHL(size, 1));
				OPO_PutMem(0, base, inx, scale, disp);
			}
			break;
		default: 
			__HALT(42);
			break;
	}
}

void OPO_GenFST (INT8 mode, INT8 size, INT16 base, INT16 inx, INT8 scale, INT32 disp)
{
	switch (mode) {
		case 0: 
			OPO_PutByte(221);
			OPO_PutByte(208 + base);
			break;
		case 1: 
			OPO_PutByte(217 + (INT16)__ASHL(size, 1));
			OPO_PutMem(2, base, inx, scale, disp);
			break;
		default: 
			__HALT(42);
			break;
	}
}

void OPO_GenFSTP (INT8 mode, INT8 size, INT16 base, INT16 inx, INT8 scale, INT32 disp)
{
	switch (mode) {
		case 0: 
			OPO_PutByte(221);
			OPO_PutByte(216 + base);
			break;
		case 1: 
			if (size == 4) {
				OPO_PutByte(219);
				OPO_PutMem(7, base, inx, scale, disp);
			} else {
				OPO_PutByte(217 + (INT16)__ASHL(size, 1));
				OPO_PutMem(3, base, inx, scale, disp);
			}
			break;
		default: 
			__HALT(42);
			break;
	}
}

void OPO_GenFCOM (INT8 mode, INT8 size, INT16 base, INT16 inx, INT8 scale, INT32 disp)
{
	switch (mode) {
		case 0: 
			OPO_PutByte(216);
			OPO_PutByte(208 + base);
			break;
		case 2: 
			OPO_PutByte(216 + (INT16)__ASHL(size, 1));
			OPO_PutMem(2, base, inx, scale, disp);
			break;
		default: 
			__HALT(42);
			break;
	}
}

void OPO_GenFCOMP (INT8 mode, INT8 size, INT16 base, INT16 inx, INT8 scale, INT32 disp)
{
	switch (mode) {
		case 0: 
			OPO_PutByte(216);
			OPO_PutByte(216 + base);
			break;
		case 2: 
			OPO_PutByte(216 + (INT16)__ASHL(size, 1));
			OPO_PutMem(3, base, inx, scale, disp);
			break;
		default: 
			__HALT(42);
			break;
	}
}

void OPO_GenFtyp1 (INT8 op, INT8 mode, INT8 size, INT16 base, INT16 inx, INT8 scale, INT32 disp)
{
	switch (mode) {
		case 5: 
			OPO_PutByte(216);
			OPO_PutByte((192 + __ASHL((INT16)op, 3)) + base);
			break;
		case 6: 
			OPO_PutByte(220);
			OPO_PutByte((192 + __ASHL((INT16)op, 3)) + base);
			break;
		case 7: 
			OPO_PutByte(222);
			OPO_PutByte((192 + __ASHL((INT16)op, 3)) + base);
			break;
		case 8: 
			OPO_PutByte(216 + (INT16)__ASHL(size, 1));
			OPO_PutMem(op, base, inx, scale, disp);
			break;
		default: 
			__HALT(42);
			break;
	}
}

void OPO_GenFADD (INT8 mode, INT8 size, INT16 base, INT16 inx, INT8 scale, INT32 disp)
{
	OPO_GenFtyp1(0, mode, size, base, inx, scale, disp);
}

void OPO_GenFSUB (INT8 mode, INT8 size, INT16 base, INT16 inx, INT8 scale, INT32 disp)
{
	if (mode == 6 || mode == 7) {
		OPO_GenFtyp1(5, mode, size, base, inx, scale, disp);
	} else {
		OPO_GenFtyp1(4, mode, size, base, inx, scale, disp);
	}
}

void OPO_GenFSUBR (INT8 mode, INT8 size, INT16 base, INT16 inx, INT8 scale, INT32 disp)
{
	if (mode == 6 || mode == 7) {
		OPO_GenFtyp1(4, mode, size, base, inx, scale, disp);
	} else {
		OPO_GenFtyp1(5, mode, size, base, inx, scale, disp);
	}
}

void OPO_GenFMUL (INT8 mode, INT8 size, INT16 base, INT16 inx, INT8 scale, INT32 disp)
{
	OPO_GenFtyp1(1, mode, size, base, inx, scale, disp);
}

void OPO_GenFDIV (INT8 mode, INT8 size, INT16 base, INT16 inx, INT8 scale, INT32 disp)
{
	if (mode == 6 || mode == 7) {
		OPO_GenFtyp1(7, mode, size, base, inx, scale, disp);
	} else {
		OPO_GenFtyp1(6, mode, size, base, inx, scale, disp);
	}
}

void OPO_GenFDIVR (INT8 mode, INT8 size, INT16 base, INT16 inx, INT8 scale, INT32 disp)
{
	if (mode == 6 || mode == 7) {
		OPO_GenFtyp1(6, mode, size, base, inx, scale, disp);
	} else {
		OPO_GenFtyp1(7, mode, size, base, inx, scale, disp);
	}
}

void OPO_GenFFREE (INT16 freg)
{
	OPO_PutByte(221);
	OPO_PutByte(192 + freg);
}

void OPO_GenFop1 (INT16 op)
{
	switch (op) {
		case 0: 
			OPO_PutByte(222);
			OPO_PutByte(217);
			break;
		case 1: 
			OPO_PutByte(217);
			OPO_PutByte(228);
			break;
		case 2: 
			OPO_PutByte(217);
			OPO_PutByte(238);
			break;
		case 3: 
			OPO_PutByte(217);
			OPO_PutByte(232);
			break;
		case 4: 
			OPO_PutByte(217);
			OPO_PutByte(225);
			break;
		case 5: 
			OPO_PutByte(217);
			OPO_PutByte(224);
			break;
		case 6: 
			OPO_PutByte(223);
			OPO_PutByte(224);
			break;
		case 7: 
			OPO_PutByte(217);
			OPO_PutByte(247);
			break;
		case 8: 
			OPO_PutByte(217);
			OPO_PutByte(246);
			break;
		default: 
			__HALT(42);
			break;
	}
}

void OPO_GenFSTCW (INT16 base, INT16 inx, INT8 scale, INT32 disp)
{
	OPO_PutByte(217);
	OPO_PutMem(7, base, inx, scale, disp);
}

void OPO_GenFLDCW (INT16 base, INT16 inx, INT8 scale, INT32 disp)
{
	OPO_PutByte(217);
	OPO_PutMem(5, base, inx, scale, disp);
}

static void EnumPtrs(void (*P)(void*))
{
	P(OPO_constant);
}


export void *OPO__init(void)
{
	__DEFMOD;
	__MODULE_IMPORT(OPM);
	__MODULE_IMPORT(OPT);
	__REGMOD("OPO", EnumPtrs);
/* BEGIN */
	OPO_constant = __NEWARR(NIL, 1, 1, 1, 1, 1024);
	__ENDMOD;
}
