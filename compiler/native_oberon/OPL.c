/* voc 2.1.0 [2017/09/06]. Bootstrapping compiler for address size 8, alignment 8. xtaSv */

#define SHORTINT INT8
#define INTEGER  INT16
#define LONGINT  INT32
#define SET      UINT32

#include "SYSTEM.h"
#include "OPM.h"
#include "OPO.h"
#include "OPT.h"

struct OPL__1 {
	INT32 pos, pc;
};

typedef
	struct {
		ADDRESS len[1];
		INT16 data[1];
	} *OPL_EntryTable;

typedef
	struct {
		ADDRESS len[1];
		INT32 data[1];
	} *OPL_ExpTable;

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
	struct OPL_LinkRec {
		INT16 offset, mod, entry;
	} OPL_LinkRec;

typedef
	struct OPL__1 *OPL_MapDesc;

typedef
	struct {
		ADDRESS len[1];
		struct OPL__1 data[1];
	} *OPL_Map;

typedef
	struct {
		ADDRESS len[1];
		INT32 data[1];
	} *OPL_PtrTable;

typedef
	struct {
		ADDRESS len[1];
		OPT_Struct data[1];
	} *OPL_RecTable;

typedef
	struct OPL_SavedRegRec {
		INT16 reg[8], sreg[8], freg[8];
	} OPL_SavedRegRec;

typedef
	struct OPL_VarConsLinkRec {
		INT16 offset, next;
	} OPL_VarConsLinkRec;

typedef
	struct {
		ADDRESS len[1];
		OPL_VarConsLinkRec data[1];
	} *OPL_VarConsLinkTable;

typedef
	struct OPL_VarConsRec {
		INT16 mod, entry, noflinks, index;
	} OPL_VarConsRec;

typedef
	struct {
		ADDRESS len[1];
		OPL_VarConsRec data[1];
	} *OPL_VarConsTable;


export OPL_InstructionTable OPL_Instr;
export INT32 OPL_mapSize;
export OPL_Map OPL_map;
static OPL_PtrTable OPL_ptrTab;
static OPL_RecTable OPL_recTab;
static OPL_EntryTable OPL_entry;
static OPL_VarConsTable OPL_varConsLink;
static OPL_LinkRec OPL_link[512];
static OPL_VarConsLinkTable OPL_varConsTab;
static INT16 OPL_nofVarCons, OPL_noVarEntries, OPL_nofEntries, OPL_nofVarConsLinks, OPL_nofLinks, OPL_nofrecs;
static INT32 OPL_nofptrs;
static BOOLEAN OPL_ConstErr, OPL_RegErr, OPL_VarEntryErr, OPL_LinkErr;
static INT32 OPL_regTab[8], OPL_sregTab[8], OPL_fregTab[8];
static OPL_SavedRegRec OPL_savedRegs[32];
static INT16 OPL_nofSavedLevel;
static INT8 OPL_ftop;
static INT32 OPL_trapFixupTab[10];
static INT8 OPL_JmpConvert[12];
static INT8 OPL_SetccConvert[12];
static INT8 OPL_FreeRegDisp;
static INT16 OPL_nofStr;
export INT32 OPL_linkTable, OPL_gVarLink;
static OPL_ExpTable OPL_explist;
static INT32 OPL_exppos;

export ADDRESS *OPL_Instruction__typ;
export ADDRESS *OPL__1__typ;
export ADDRESS *OPL_LinkRec__typ;
export ADDRESS *OPL_VarConsRec__typ;
export ADDRESS *OPL_VarConsLinkRec__typ;
export ADDRESS *OPL_SavedRegRec__typ;

static void OPL_AbsAccess (OPT_Node node, INT32 offset);
static void OPL_AddLink (INT32 index, INT32 offset);
export void OPL_AllocCaseTab (INT32 low, INT32 high, INT32 *tab);
export void OPL_AllocConst (SYSTEM_BYTE *s, ADDRESS s__len, INT32 len, INT32 align, INT32 *adr);
export void OPL_AllocTypDesc (OPT_Struct typ);
static void OPL_AssignFreg (INT32 pReg);
static void OPL_AssignNewReg (INT32 pReg);
static void OPL_AssignReg (INT32 pReg, INT8 *reg, INT8 *base, INT8 *inx);
static void OPL_AssignThisReg (INT32 pReg, INT8 this);
export void OPL_CaseJump (INT32 Label, INT32 tab, INT32 from, INT32 to);
static void OPL_ClearSDynArr (OPL_Instruction *instr, ADDRESS *instr__typ);
export void OPL_Close (void);
static void OPL_DecCheckFreg (INT8 freg);
static void OPL_DecCheckReg (INT32 pReg, INT8 src, INT8 base, INT8 inx);
static void OPL_DecReg (INT8 reg);
static void OPL_EncodeFixup (INT32 i);
static void OPL_Export (OPT_Object obj, INT16 *nofExp);
static void OPL_FindFreg (INT32 pReg, INT8 *freg);
static void OPL_FindLoadReg (INT32 pReg, INT8 *reg);
static void OPL_FindMemReg (OPL_Instruction *instr, ADDRESS *instr__typ, INT8 *mode, INT8 *scale, INT8 *size, INT8 *base, INT8 *inx, INT32 *disp);
static void OPL_FindReg (INT32 pReg, INT8 *reg);
static void OPL_FixupAndGenTrap (void);
static void OPL_FixupCaseTab (OPL_Instruction *instr, ADDRESS *instr__typ);
static void OPL_FixupJcc (INT32 label);
export void OPL_FixupLocalProcCall (OPT_Object proc);
static void OPL_Flags (OPL_Instruction *instr, ADDRESS *instr__typ);
static void OPL_Fload (OPL_Instruction *instr, ADDRESS *instr__typ);
static void OPL_FloatCmp (OPL_Instruction *instr, ADDRESS *instr__typ);
static void OPL_FloatGen1 (OPL_Instruction *instr, ADDRESS *instr__typ);
static void OPL_FloatGen3 (OPL_Instruction *instr, ADDRESS *instr__typ);
static void OPL_FreeFreg (INT8 freg);
static void OPL_FreeReg (INT8 reg);
static void OPL_Fstore (OPL_Instruction *instr, ADDRESS *instr__typ);
static void OPL_Gen1 (OPL_Instruction *instr, ADDRESS *instr__typ, INT32 RiscPC);
static void OPL_Gen2 (OPL_Instruction *instr, ADDRESS *instr__typ);
static void OPL_Gen3 (OPL_Instruction *instr, ADDRESS *instr__typ);
static void OPL_GenAbs (OPL_Instruction *instr, ADDRESS *instr__typ);
static void OPL_GenAsm (OPL_Instruction instr);
static void OPL_GenCmpString (OPL_Instruction *instr, ADDRESS *instr__typ);
export void OPL_GenCode (INT16 pSize);
static void OPL_GenDivMod (OPL_Instruction *instr, ADDRESS *instr__typ);
static void OPL_GenEnter (INT32 locSize, OPT_Object locals, INT8 sysflag);
static void OPL_GenEntier (OPL_Instruction *instr, ADDRESS *instr__typ);
static void OPL_GenIntpt (OPL_Instruction Instr);
static void OPL_GenLeave (INT8 sysflag);
static void OPL_GenMul (OPL_Instruction *instr, ADDRESS *instr__typ);
static void OPL_GenPhi (OPL_Instruction *instr, ADDRESS *instr__typ);
static void OPL_GenPop (OPL_Instruction *instr, ADDRESS *instr__typ);
static void OPL_GenPortIO (OPL_Instruction *instr, ADDRESS *instr__typ);
static void OPL_GenPush (OPL_Instruction *instr, ADDRESS *instr__typ);
static void OPL_GenRepMovs (OPL_Instruction *instr, ADDRESS *instr__typ);
static void OPL_GenShort (OPL_Instruction *instr, ADDRESS *instr__typ);
static void OPL_GenTrap (INT32 trapNr);
static void OPL_GenTrapCC (OPL_Instruction *instr, ADDRESS *instr__typ);
static void OPL_GetFreg (INT8 *freg);
static void OPL_GetReg (INT8 *reg);
static void OPL_GetReg8 (INT8 *reg);
static void OPL_GetSplittableReg (INT8 *reg);
static void OPL_GetThisReg (INT8 this);
static void OPL_GetThisReg8 (INT8 this);
export void OPL_Init (void);
static INT32 OPL_LSW (INT32 x);
static BOOLEAN OPL_LastUse (INT8 reg);
static BOOLEAN OPL_LastUseF (INT8 freg);
static void OPL_Load (OPL_Instruction *instr, ADDRESS *instr__typ);
static void OPL_LoadProc (OPL_Instruction *instr, ADDRESS *instr__typ);
export void OPL_NewEntry (INT32 *entryNr);
export void OPL_NewLink (INT32 mod, INT32 entry, INT32 *index);
export void OPL_NewVarCons (INT16 mod, INT16 entry, INT32 *index);
export void OPL_OutCode (CHAR *modName, ADDRESS modName__len);
export void OPL_OutRefName (CHAR *name, ADDRESS name__len);
export void OPL_OutRefPoint (OPT_Object proc);
export void OPL_OutRefs (OPT_Object obj);
static void OPL_PopRegs (OPL_Instruction *instr, ADDRESS *instr__typ);
static void OPL_PushRegs (void);
static void OPL_ReleaseFreg (INT8 freg);
static void OPL_Setcc (OPL_Instruction *instr, ADDRESS *instr__typ);
static void OPL_Store (OPL_Instruction *instr, ADDRESS *instr__typ);
static void OPL_TakeFreg (INT32 pReg, INT8 freg);
static void OPL_Use (OPT_Object obj);
static void OPL_VarConsLink (INT32 index, INT32 offset);
static BOOLEAN OPL_loaded (INT32 pReg);


void OPL_Init (void)
{
	OPO_CodeErr = 0;
	OPL_ConstErr = 0;
	OPL_VarEntryErr = 0;
	OPL_LinkErr = 0;
	OPO_dsize = 0;
	OPO_csize = 0;
	OPO_pc = 0;
	OPL_noVarEntries = 0;
	OPL_nofptrs = 0;
	OPL_nofVarConsLinks = 0;
	OPL_nofrecs = 0;
	OPL_nofEntries = 0;
	OPL_nofSavedLevel = 0;
	OPO_csize = 4;
	(OPL_varConsLink->data)[0].noflinks = 0;
	(OPL_varConsLink->data)[0].entry = -1;
	(OPL_varConsLink->data)[0].noflinks = 0;
	(OPL_varConsLink->data)[0].index = -1;
	OPL_nofVarCons = 1;
	OPL_link[0].mod = 0;
	OPL_link[0].entry = 255;
	OPL_link[0].offset = -1;
	OPL_link[1].mod = 0;
	OPL_link[1].entry = 254;
	OPL_link[1].offset = -1;
	OPL_link[2].mod = 0;
	OPL_link[2].entry = 253;
	OPL_link[2].offset = -1;
	OPL_link[3].mod = 0;
	OPL_link[3].entry = 252;
	OPL_link[3].offset = -1;
	OPL_link[4].mod = 0;
	OPL_link[4].entry = 251;
	OPL_link[4].offset = -1;
	OPL_link[5].mod = 0;
	OPL_link[5].entry = 250;
	OPL_link[5].offset = -1;
	OPL_link[6].mod = 0;
	OPL_link[6].entry = 249;
	OPL_link[6].offset = -1;
	OPL_link[7].mod = 0;
	OPL_link[7].entry = 247;
	OPL_link[7].offset = -1;
	OPL_link[8].mod = 0;
	OPL_link[8].entry = 246;
	OPL_link[8].offset = -1;
	OPL_nofLinks = 9;
}

static void OPL_GetReg8 (INT8 *reg)
{
	INT8 i;
	i = 3;
	while ((i >= 0 && !((OPL_regTab[__X(i, 8)] == -32767 && (OPL_sregTab[__X(i, 8)] == -1 || OPL_sregTab[__X(i + 4, 8)] == -1))))) {
		i -= 1;
	}
	if (i < 0) {
		i = 3;
		while ((i >= 0 && OPL_regTab[__X(i, 8)] != -1)) {
			i -= 1;
		}
		if (i < 0) {
			i = 3;
			while ((i >= 0 && OPL_regTab[__X(i, 8)] == -32767)) {
				i -= 1;
			}
			if (i < 0) {
				OPM_err(215);
				OPL_RegErr = 1;
				*reg = 16;
				return;
			}
		}
		OPL_GetThisReg(i);
		OPL_regTab[__X(i, 8)] = -32767;
	} else if (OPL_sregTab[__X(i, 8)] != -1) {
		i += 4;
	}
	OPL_sregTab[__X(i, 8)] = (-32767-1);
	*reg = i + 16;
}

static void OPL_GetThisReg8 (INT8 this)
{
	INT8 i, reg;
	__ASSERT(__IN(this, 0xff0000, 32), 0);
	reg = __MASK(this, -4);
	if ((OPL_regTab[__X(reg, 8)] == -32767 && OPL_sregTab[__X(this - 16, 8)] == -1)) {
		OPL_sregTab[__X(this - 16, 8)] = (-32767-1);
	} else if (OPL_regTab[__X(reg, 8)] != -1) {
		if (OPL_regTab[__X(reg, 8)] == -32767) {
			OPL_GetReg8(&i);
			__ASSERT(OPL_sregTab[__X(this - 16, 8)] >= 0, 0);
			(OPL_Instr->data)[__X(OPL_sregTab[__X(this - 16, 8)], OPL_Instr->len[0])].reg = i;
			OPO_GenMOV(0, i, this, -1, 0, 0, 0);
			OPL_sregTab[__X(i - 16, 8)] = OPL_sregTab[__X(this - 16, 8)];
			OPL_sregTab[__X(this - 16, 8)] = (-32767-1);
		} else {
			OPL_GetThisReg(reg);
			OPL_regTab[__X(reg, 8)] = -32767;
			OPL_sregTab[__X(this - 16, 8)] = (-32767-1);
		}
	} else {
		OPL_regTab[__X(reg, 8)] = -32767;
		OPL_sregTab[__X(this - 16, 8)] = (-32767-1);
	}
}

static void OPL_GetSplittableReg (INT8 *reg)
{
	INT8 r;
	r = 3;
	while ((r >= 0 && OPL_regTab[__X(r, 8)] != -1)) {
		r -= 1;
	}
	if (r < 0) {
		r = 3;
		while ((r >= 0 && OPL_regTab[__X(r, 8)] == -32767)) {
			r -= 1;
		}
		if (r < 0) {
			OPM_err(215);
			OPL_RegErr = 1;
			*reg = 0;
			return;
		}
		OPL_GetThisReg(r);
	}
	OPL_regTab[__X(r, 8)] = (-32767-1);
	*reg = r;
}

static void OPL_GetReg (INT8 *reg)
{
	INT8 r;
	r = 3;
	while ((r >= 0 && OPL_regTab[__X(r, 8)] != -1)) {
		r -= 1;
	}
	if (r < 0) {
		if (OPL_regTab[7] == -1) {
			r = 7;
		} else if (OPL_regTab[6] == -1) {
			r = 6;
		}
	}
	if (r < 0) {
		OPM_err(215);
		OPL_RegErr = 1;
		*reg = 0;
		return;
	}
	OPL_regTab[__X(r, 8)] = (-32767-1);
	*reg = r;
}

static void OPL_GetThisReg (INT8 this)
{
	INT8 r, reg, r0, r1;
	INT32 pReg;
	__ASSERT(__IN(this, 0xffff, 32), 0);
	reg = __MASK(this, -8);
	if (OPL_regTab[__X(reg, 8)] == -32767) {
		OPL_regTab[__X(reg, 8)] = (-32767-1);
		if (OPL_sregTab[__X(reg, 8)] == -1 || OPL_sregTab[__X(reg + 4, 8)] == -1) {
			if (OPL_sregTab[__X(reg, 8)] == -1) {
				r0 = (reg + 16) + 4;
				r1 = reg + 4;
			} else {
				r0 = reg + 16;
				r1 = reg;
			}
			OPL_GetReg8(&r);
			OPO_GenMOV(0, r, r0, -1, 0, 0, 0);
			OPL_sregTab[__X(r - 16, 8)] = OPL_sregTab[__X(r1, 8)];
			(OPL_Instr->data)[__X(OPL_sregTab[__X(r1, 8)], OPL_Instr->len[0])].reg = r;
			OPL_sregTab[__X(r1, 8)] = -1;
		} else {
			r = 3;
			while ((r >= 0 && OPL_regTab[__X(r, 8)] != -1)) {
				r -= 1;
			}
			if (r < 0) {
				OPL_GetReg8(&r0);
				OPO_GenMOV(0, r0, reg + 16, -1, 0, 0, 0);
				OPL_GetReg8(&r1);
				OPO_GenMOV(0, r1, (reg + 16) + 4, -1, 0, 0, 0);
			} else {
				OPO_GenMOV(0, r, reg, -1, 0, 0, 0);
				r0 = r + 16;
				r1 = r0 + 4;
				OPL_regTab[__X(r, 8)] = -32767;
			}
			OPL_sregTab[__X(r0 - 16, 8)] = OPL_sregTab[__X(reg + 16, 8)];
			(OPL_Instr->data)[__X(OPL_sregTab[__X(reg + 16, 8)], OPL_Instr->len[0])].reg = r0;
			OPL_sregTab[__X(r0 - 16, 8)] = -1;
			OPL_sregTab[__X(r1 - 16, 8)] = OPL_sregTab[__X((reg + 16) + 4, 8)];
			(OPL_Instr->data)[__X(OPL_sregTab[__X((reg + 16) + 4, 8)], OPL_Instr->len[0])].reg = r1;
			OPL_sregTab[__X(r1 - 16, 8)] = -1;
		}
	} else if (OPL_regTab[__X(reg, 8)] != -1) {
		pReg = OPL_regTab[__X(reg, 8)];
		__ASSERT(pReg >= 0, 0);
		OPL_GetReg(&r);
		OPL_regTab[__X(r, 8)] = pReg;
		r += (INT8)__ASHL(__MASK((OPL_Instr->data)[__X(pReg, OPL_Instr->len[0])].op, -8), 3);
		(OPL_Instr->data)[__X(pReg, OPL_Instr->len[0])].reg = r;
		OPO_GenMOV(0, r, reg, -1, 0, 0, 0);
	}
	OPL_regTab[__X(reg, 8)] = (-32767-1);
}

static void OPL_AssignNewReg (INT32 pReg)
{
	INT8 reg;
	INT32 size;
	size = __MASK((OPL_Instr->data)[__X(pReg, OPL_Instr->len[0])].op, -8);
	if (size == 2) {
		OPL_GetReg8(&reg);
		OPL_sregTab[__X(reg - 16, 8)] = pReg;
	} else {
		OPL_GetReg(&reg);
		OPL_regTab[__X(reg, 8)] = pReg;
		if (size == 1) {
			reg += 8;
		}
	}
	(OPL_Instr->data)[__X(pReg, OPL_Instr->len[0])].reg = reg;
}

static void OPL_AssignThisReg (INT32 pReg, INT8 this)
{
	if (__IN(this, 0xff0000, 32)) {
		OPL_GetThisReg8(this);
		OPL_sregTab[__X(this - 16, 8)] = pReg;
	} else if (!__IN(this, 0x3030, 32)) {
		OPL_GetThisReg(this);
		OPL_regTab[__X(__MASK(this, -8), 8)] = pReg;
	}
	(OPL_Instr->data)[__X(pReg, OPL_Instr->len[0])].reg = this;
}

static void OPL_AssignReg (INT32 pReg, INT8 *reg, INT8 *base, INT8 *inx)
{
	INT32 hint, size, pRegBase, pRegInx, pRegReg;
	hint = (OPL_Instr->data)[__X(pReg, OPL_Instr->len[0])].hint;
	size = __ASHL(__MASK((OPL_Instr->data)[__X(pReg, OPL_Instr->len[0])].op, -8), 3);
	__ASSERT(((*reg == -1 || (size == 16 && *reg >= 16)) || (size == 8 && *reg >= 8)) || (size == 0 && *reg >= 0), 0);
	if (hint >= 16) {
		if (size == 16) {
			if (OPL_sregTab[__X(hint - 16, 8)] == -1) {
				OPL_AssignThisReg(pReg, (INT8)((INT16)((hint - 16) + 16)));
				return;
			}
		} else if (OPL_regTab[__X(hint - 16, 8)] == -1) {
			OPL_AssignThisReg(pReg, (INT8)((INT16)((hint - 16) + size)));
			return;
		}
		hint = -1;
	}
	if (hint <= -1) {
		if (*reg == -1 || !OPL_LastUse(*reg)) {
			OPL_AssignNewReg(pReg);
		} else {
			(OPL_Instr->data)[__X(pReg, OPL_Instr->len[0])].reg = *reg;
		}
	} else {
		if (*reg >= 16) {
			pRegReg = OPL_sregTab[__X(*reg - 16, 8)];
		} else if (*reg != -1) {
			pRegReg = OPL_regTab[__X(__MASK(*reg, -8), 8)];
		}
		if (*inx >= 16) {
			pRegInx = OPL_sregTab[__X(*inx - 16, 8)];
		} else if (*inx != -1) {
			pRegInx = OPL_regTab[__X(__MASK(*inx, -8), 8)];
		}
		if (*base >= 16) {
			pRegBase = OPL_sregTab[__X(*base - 16, 8)];
		} else if (*base != -1) {
			pRegBase = OPL_regTab[__X(__MASK(*base, -8), 8)];
		}
		OPL_AssignThisReg(pReg, (INT8)((INT16)(hint + size)));
		if ((*reg != -1 && pRegReg >= 0)) {
			*reg = (OPL_Instr->data)[__X(pRegReg, OPL_Instr->len[0])].reg;
		}
		if ((*inx != -1 && pRegInx >= 0)) {
			*inx = (OPL_Instr->data)[__X(pRegInx, OPL_Instr->len[0])].reg;
		}
		if ((*base != -1 && pRegBase >= 0)) {
			*base = (OPL_Instr->data)[__X(pRegBase, OPL_Instr->len[0])].reg;
		}
	}
}

static void OPL_FreeReg (INT8 reg)
{
	INT8 i;
	if ((reg > -1 && !__IN(reg, 0x3030, 32))) {
		if (__IN(reg, 0xff0000, 32)) {
			i = reg - 16;
			if (OPL_sregTab[__X(i, 8)] >= 0) {
				(OPL_Instr->data)[__X(OPL_sregTab[__X(i, 8)], OPL_Instr->len[0])].reg = -2 - reg;
			}
			OPL_sregTab[__X(i, 8)] = -1;
			if (i < 4) {
				if (OPL_sregTab[__X(i + 4, 8)] == -1) {
					OPL_regTab[__X(i, 8)] = -1;
				}
			} else if (OPL_sregTab[__X(i - 4, 8)] == -1) {
				OPL_regTab[__X(__MASK(i, -4), 8)] = -1;
			}
		} else {
			i = __MASK(reg, -8);
			if (OPL_regTab[__X(i, 8)] >= 0) {
				(OPL_Instr->data)[__X(OPL_regTab[__X(i, 8)], OPL_Instr->len[0])].reg = -2 - reg;
			}
			if (__IN(i, 0x3030, 32)) {
				OPL_regTab[__X(i, 8)] = (-32767-1);
			} else {
				OPL_regTab[__X(i, 8)] = -1;
			}
		}
	}
}

static void OPL_DecReg (INT8 reg)
{
	INT32 pReg;
	if (reg > -1) {
		if (reg >= 16) {
			pReg = OPL_sregTab[__X(reg - 16, 8)];
		} else {
			pReg = OPL_regTab[__X(__MASK(reg, -8), 8)];
		}
		if (pReg > -1) {
			(OPL_Instr->data)[__X(pReg, OPL_Instr->len[0])].used -= 1;
			if (((OPL_Instr->data)[__X(pReg, OPL_Instr->len[0])].used == 0 && (OPL_Instr->data)[__X(pReg, OPL_Instr->len[0])].reg > -1)) {
				OPL_FreeReg((OPL_Instr->data)[__X(pReg, OPL_Instr->len[0])].reg);
			}
		}
	}
}

static struct DecCheckReg__14 {
	struct DecCheckReg__14 *lnk;
} *DecCheckReg__14_s;

static void CheckRegister__15 (INT8 reg, INT8 src);
static void ReleaseReg__17 (INT8 reg);

static void ReleaseReg__17 (INT8 reg)
{
	INT32 pReg;
	if (reg > -1) {
		if (reg >= 16) {
			pReg = OPL_sregTab[__X(reg - 16, 8)];
		} else {
			pReg = OPL_regTab[__X(__MASK(reg, -8), 8)];
		}
		if (pReg > -1) {
			(OPL_Instr->data)[__X(pReg, OPL_Instr->len[0])].reg = -2 - reg;
		}
	}
}

static void CheckRegister__15 (INT8 reg, INT8 src)
{
	INT8 s;
	if (__IN(src, 0xff0000, 32)) {
		s = __MASK(src, -4);
	} else {
		s = __MASK(src, -8);
	}
	if (__IN(reg, 0xff0000, 32)) {
		if (__IN(src, 0xff0000, 32)) {
			if (reg == src) {
				ReleaseReg__17(src);
			} else {
				OPL_DecReg(src);
			}
		} else if (__MASK(reg, -4) == s) {
			ReleaseReg__17(src);
		} else {
			OPL_DecReg(src);
		}
	} else if (__MASK(reg, -8) == s) {
		ReleaseReg__17(src);
	} else {
		OPL_DecReg(src);
	}
}

static void OPL_DecCheckReg (INT32 pReg, INT8 src, INT8 base, INT8 inx)
{
	INT8 reg, r;
	struct DecCheckReg__14 _s;
	_s.lnk = DecCheckReg__14_s;
	DecCheckReg__14_s = &_s;
	reg = (OPL_Instr->data)[__X(pReg, OPL_Instr->len[0])].reg;
	CheckRegister__15(reg, src);
	CheckRegister__15(reg, base);
	CheckRegister__15(reg, inx);
	if (reg >= 16) {
		OPL_regTab[__X(__MASK(reg, -4), 8)] = -32767;
		OPL_sregTab[__X(reg - 16, 8)] = pReg;
	} else if ((reg != -1 && !__IN(reg, 0x3030, 32))) {
		r = __MASK(reg, -8);
		OPL_regTab[__X(r, 8)] = pReg;
		if (__IN(reg, 0x0f0f, 32)) {
			OPL_sregTab[__X(r, 8)] = -1;
			OPL_sregTab[__X(r + 4, 8)] = -1;
		}
	}
	DecCheckReg__14_s = _s.lnk;
}

static BOOLEAN OPL_loaded (INT32 pReg)
{
	if (pReg > -1) {
		return (OPL_Instr->data)[__X(pReg, OPL_Instr->len[0])].reg > -1;
	} else {
		return pReg == -3 || pReg == -2;
	}
	__RETCHK;
}

static void OPL_FindReg (INT32 pReg, INT8 *reg)
{
	__ASSERT(OPL_loaded(pReg), 0);
	if (pReg > -1) {
		*reg = (OPL_Instr->data)[__X(pReg, OPL_Instr->len[0])].reg;
	} else if (pReg == -3) {
		*reg = 4;
	} else {
		*reg = 5;
	}
}

static void OPL_FindLoadReg (INT32 pReg, INT8 *reg)
{
	if (pReg > -1) {
		if (!OPL_loaded(pReg)) {
			OPL_Load(&(OPL_Instr->data)[__X(pReg, OPL_Instr->len[0])], OPL_Instruction__typ);
		}
		*reg = (OPL_Instr->data)[__X(pReg, OPL_Instr->len[0])].reg;
	} else if (pReg == -3) {
		*reg = 4;
	} else if (pReg == -2) {
		*reg = 5;
	} else {
		*reg = -1;
	}
}

static BOOLEAN OPL_LastUse (INT8 reg)
{
	INT32 pReg;
	__ASSERT(__IN(reg, 0xffffff, 32), 0);
	if (reg >= 16) {
		pReg = OPL_sregTab[__X(reg - 16, 8)];
	} else {
		pReg = OPL_regTab[__X(__MASK(reg, -8), 8)];
	}
	if (pReg > -1) {
		return (OPL_Instr->data)[__X(pReg, OPL_Instr->len[0])].used == 1;
	} else {
		__ASSERT(__IN(reg, 0x3030, 32), 0);
		return 1;
	}
	__RETCHK;
}

static void OPL_FindMemReg (OPL_Instruction *instr, ADDRESS *instr__typ, INT8 *mode, INT8 *scale, INT8 *size, INT8 *base, INT8 *inx, INT32 *disp)
{
	*size = __ASHL((INT8)__MASK((*instr).op, -8), 3);
	*mode = (INT8)__MASK(__ASHR((*instr).op, 3), -4);
	*scale = (*instr).scale;
	if (__IN(*mode, 0x06, 32)) {
		OPL_FindLoadReg((*instr).src1, &*base);
		*disp = (*instr).src2;
		OPL_FindLoadReg((*instr).inx, &*inx);
	} else if (*mode == 0) {
		OPL_FindLoadReg((*instr).src1, &*base);
		*disp = 0;
		*inx = -1;
	} else {
		__ASSERT(*mode == 3, 0);
		*base = -1;
		*disp = 0;
		*inx = -1;
	}
}

static struct Load__83 {
	OPL_Instruction *instr;
	ADDRESS *instr__typ;
	struct Load__83 *lnk;
} *Load__83_s;

static void AssignReg__84 (INT32 pReg, INT8 *baseReg, INT8 *inxReg);

static void AssignReg__84 (INT32 pReg, INT8 *baseReg, INT8 *inxReg)
{
	INT32 hint, size, pRegBase, pRegInx;
	INT8 base, inx, op;
	hint = (OPL_Instr->data)[__X(pReg, OPL_Instr->len[0])].hint;
	size = __ASHL(__MASK((OPL_Instr->data)[__X(pReg, OPL_Instr->len[0])].op, -8), 3);
	if (hint >= 16) {
		if (size == 16) {
			if ((OPL_sregTab[__X(hint - 16, 8)] == -1 && OPL_regTab[__X(hint - 16, 8)] == -1)) {
				OPL_AssignThisReg(pReg, (INT8)((INT16)((hint - 16) + 16)));
				return;
			}
		} else if (OPL_regTab[__X(hint - 16, 8)] == -1) {
			OPL_AssignThisReg(pReg, (INT8)((INT16)((hint - 16) + size)));
			return;
		}
		hint = -1;
	}
	base = *baseReg;
	inx = *inxReg;
	if (hint <= -1) {
		op = (INT8)__ASHR((*Load__83_s->instr).op, 5);
		if (((((op == 2 || op == 4) || op == 3) || op == 5) || op == 7) || op == 6) {
			OPL_AssignNewReg(pReg);
		} else if (((base == -1 || __IN(base, 0x30, 32)) || !OPL_LastUse(base)) || (size == 16 && __IN(base, 0xf0f0, 32))) {
			if (((inx == -1 || __IN(inx, 0x30, 32)) || !OPL_LastUse(inx)) || (size == 16 && __IN(inx, 0xf0f0, 32))) {
				OPL_AssignNewReg(pReg);
			} else {
				(OPL_Instr->data)[__X(pReg, OPL_Instr->len[0])].reg = __MASK(inx, -8) + (INT8)((INT16)size);
			}
		} else {
			(OPL_Instr->data)[__X(pReg, OPL_Instr->len[0])].reg = __MASK(base, -8) + (INT8)((INT16)size);
		}
	} else {
		if (inx >= 16) {
			pRegInx = OPL_sregTab[__X(inx - 16, 8)];
		} else if (inx != -1) {
			pRegInx = OPL_regTab[__X(__MASK(inx, -8), 8)];
		}
		if (base >= 16) {
			pRegBase = OPL_sregTab[__X(base - 16, 8)];
		} else if (base != -1) {
			pRegBase = OPL_regTab[__X(__MASK(base, -8), 8)];
		}
		OPL_AssignThisReg(pReg, (INT8)((INT16)(hint + size)));
		if ((inx != -1 && pRegInx >= 0)) {
			*inxReg = (OPL_Instr->data)[__X(pRegInx, OPL_Instr->len[0])].reg;
		}
		if ((base != -1 && pRegBase >= 0)) {
			*baseReg = (OPL_Instr->data)[__X(pRegBase, OPL_Instr->len[0])].reg;
		}
	}
}

static void OPL_Load (OPL_Instruction *instr, ADDRESS *instr__typ)
{
	INT8 mode, scale, size, base, inx, dummy;
	INT32 disp;
	struct Load__83 _s;
	_s.instr = instr; _s.instr__typ = instr__typ;
	_s.lnk = Load__83_s;
	Load__83_s = &_s;
	OPL_FindMemReg(&*instr, instr__typ, &mode, &scale, &size, &base, &inx, &disp);
	__ASSERT((size == 16 || size == 8) || size == 0, 0);
	if (__ASHR((*instr).op, 5) != 9) {
		AssignReg__84((*instr).dest, &base, &inx);
	}
	switch (__ASHR((*instr).op, 5)) {
		case 1: 
			__ASSERT(mode != 0 || (mode == 0 && (*instr).reg != base), 0);
			OPO_GenMOV(mode, (*instr).reg, base, inx, scale, disp, (*instr).src2);
			break;
		case 12: 
			__ASSERT(mode != 0 || (mode == 0 && (*instr).reg != base), 0);
			OPO_GenLEA((*instr).reg, base, inx, scale, disp);
			break;
		case 2: case 4: 
			OPO_GenMOVSX(mode, 0, (*instr).reg, base, inx, scale, disp);
			break;
		case 3: 
			OPO_GenMOVSX(mode, 1, (*instr).reg, base, inx, scale, disp);
			break;
		case 5: case 7: 
			OPO_GenMOVZX(mode, 0, (*instr).reg, base, inx, scale, disp);
			break;
		case 6: 
			OPO_GenMOVZX(mode, 1, (*instr).reg, base, inx, scale, disp);
			break;
		case 9: 
			OPO_GenMOV(mode, (INT16)((*instr).hint + size), base, inx, scale, disp, (*instr).src2);
			break;
		default: 
			__HALT(41);
			break;
	}
	dummy = -1;
	OPL_DecCheckReg((*instr).dest, dummy, base, inx);
	if ((((__IN(mode, 0x06, 32) && base == -1)) && !(*instr).abs)) {
		OPL_AbsAccess((*instr).node, OPO_pc - 4);
	}
	Load__83_s = _s.lnk;
}

static struct LoadProc__86 {
	OPL_Instruction *instr;
	ADDRESS *instr__typ;
	struct LoadProc__86 *lnk;
} *LoadProc__86_s;

static void AssignReg__87 (INT32 pReg);

static void AssignReg__87 (INT32 pReg)
{
	INT32 hint, size;
	hint = (OPL_Instr->data)[__X(pReg, OPL_Instr->len[0])].hint;
	size = __ASHL(__MASK((OPL_Instr->data)[__X(pReg, OPL_Instr->len[0])].op, -8), 3);
	if (hint >= 16) {
		if (size == 16) {
			if (OPL_sregTab[__X(hint - 16, 8)] == -1) {
				OPL_AssignThisReg(pReg, (INT8)((INT16)((hint - 16) + 16)));
				return;
			}
		} else if (OPL_regTab[__X(hint - 16, 8)] == -1) {
			OPL_AssignThisReg(pReg, (INT8)((INT16)((hint - 16) + size)));
			return;
		}
		hint = -1;
	}
	if (hint == -1) {
		OPL_AssignNewReg((*LoadProc__86_s->instr).dest);
	} else {
		__ASSERT(hint > -1, 0);
		OPL_AssignThisReg(pReg, (INT8)((INT16)(hint + size)));
	}
}

static void OPL_LoadProc (OPL_Instruction *instr, ADDRESS *instr__typ)
{
	INT8 dummy;
	struct LoadProc__86 _s;
	_s.instr = instr; _s.instr__typ = instr__typ;
	_s.lnk = LoadProc__86_s;
	LoadProc__86_s = &_s;
	AssignReg__87((*instr).dest);
	if (__ASHR((*instr).op, 5) == 10) {
		OPO_GenMOV(3, (*instr).reg, -1, -1, 0, 0, __MASK((*instr).src1, -65536));
		OPL_AddLink(1, OPO_pc - 4);
	} else {
		OPO_GenMOV(3, (*instr).reg, -1, -1, 0, 0, 65535);
		OPL_AddLink(__MASK((*instr).src1, -65536), OPO_pc - 4);
	}
	dummy = -1;
	OPL_DecCheckReg((*instr).dest, dummy, dummy, dummy);
	LoadProc__86_s = _s.lnk;
}

static void OPL_Store (OPL_Instruction *instr, ADDRESS *instr__typ)
{
	INT8 mode, scale, size, reg, base, inx;
	INT32 disp, delta;
	OPL_FindMemReg(&*instr, instr__typ, &mode, &scale, &size, &base, &inx, &disp);
	if (__ASHR((*instr).op, 5) == 8) {
		OPO_GenMOV(mode, (INT16)((*instr).hint + size), base, inx, scale, disp, 0);
		reg = -1;
		delta = 0;
	} else if ((!OPL_loaded((*instr).dest) && __MASK(__ASHR((OPL_Instr->data)[__X((*instr).dest, OPL_Instr->len[0])].op, 3), -4) == 3)) {
		OPO_GenMOV(4, size, base, inx, scale, disp, (OPL_Instr->data)[__X((*instr).dest, OPL_Instr->len[0])].src2);
		mode = 4;
		if (OPO_lastImmSize == 16) {
			delta = 1;
		} else if (OPO_lastImmSize == 8) {
			delta = 2;
		} else {
			delta = 4;
		}
	} else {
		delta = 0;
		OPL_FindLoadReg((*instr).dest, &reg);
		__ASSERT((size == 16 && (__IN(reg, 0x0f0f, 32) || __IN(reg, 0xff0000, 32))) || size != 16, 0);
		OPO_GenMOV(mode, __MASK(reg, -8) + size, base, inx, scale, disp, 0);
	}
	OPL_DecReg(reg);
	OPL_DecReg(base);
	OPL_DecReg(inx);
	if ((((__IN(mode, 0x16, 32) && base == -1)) && !(*instr).abs)) {
		OPL_AbsAccess((*instr).node, (OPO_pc - delta) - 4);
	}
}

static void OPL_GenPortIO (OPL_Instruction *instr, ADDRESS *instr__typ)
{
	INT16 size;
	BOOLEAN pin;
	size = __ASHL(__MASK((*instr).op, -8), 3);
	pin = __ASHR((*instr).op, 5) == 101;
	if (pin) {
		__ASSERT(!OPL_loaded((*instr).dest), 0);
		if (size == 16) {
			OPL_AssignThisReg((*instr).dest, 16);
		} else if (size == 8) {
			OPL_AssignThisReg((*instr).dest, 8);
		} else if (size == 0) {
			OPL_AssignThisReg((*instr).dest, 0);
		} else {
			__HALT(41);
		}
		__ASSERT(OPL_loaded((*instr).dest), 0);
	} else {
		__ASSERT(OPL_loaded((*instr).src1), 0);
		OPL_FreeReg((OPL_Instr->data)[__X((*instr).src1, OPL_Instr->len[0])].reg);
	}
	if (pin) {
		OPO_GenIN(size);
	} else {
		OPO_GenOUT(size);
	}
	OPL_FreeReg(10);
}

static void OPL_GenPush (OPL_Instruction *instr, ADDRESS *instr__typ)
{
	INT8 reg, i;
	__ASSERT(__IN(__MASK(__ASHR((*instr).op, 3), -4), 0x09, 32), 0);
	if (__MASK(__ASHR((*instr).op, 3), -4) == 3) {
		OPO_GenPUSH(3, 0, -1, -1, 0, 0, (*instr).src2);
	} else {
		OPL_FindLoadReg((*instr).src1, &reg);
		if (__IN(reg, 0xf00000, 32)) {
			i = 3;
			while ((i >= 0 && !((OPL_regTab[__X(i, 8)] == -32767 && OPL_sregTab[__X(i, 8)] == -1)))) {
				i -= 1;
			}
			if (i < 0) {
				i = 3;
				while ((i >= 0 && OPL_regTab[__X(i, 8)] != -1)) {
					i -= 1;
				}
				if (i < 0) {
					OPL_GetReg(&i);
				}
			}
			if (__IN(i, 0x0f0f, 32)) {
				OPL_GetThisReg8(i + 16);
				OPO_GenMOV(0, i + 16, reg, -1, 0, 0, 0);
				OPO_GenPUSH(0, i, -1, -1, 0, 0, 0);
			} else {
				OPO_GenMOVSX(0, 0, i, reg, -1, 0, 0);
				OPO_GenPUSH(0, i, -1, -1, 0, 0, 0);
			}
			OPL_FreeReg(i);
		} else {
			if (__IN(reg, 0x0f0000, 32)) {
				i = __MASK(reg, -4);
			} else {
				i = __MASK(reg, -8);
			}
			OPO_GenPUSH(0, i, -1, -1, 0, 0, 0);
		}
		OPL_DecReg(reg);
	}
}

static void OPL_GenPop (OPL_Instruction *instr, ADDRESS *instr__typ)
{
	INT8 reg, dummy;
	dummy = -1;
	OPL_AssignReg((*instr).dest, &dummy, &dummy, &dummy);
	reg = (*instr).reg;
	__ASSERT((__MASK(__ASHR((*instr).op, 3), -4) == 0 && !__IN(reg, 0xff0000, 32)), 0);
	reg = __MASK(reg, -8);
	OPO_GenPOP(0, reg, -1, -1, 0, 0);
}

static void OPL_Gen1 (OPL_Instruction *instr, ADDRESS *instr__typ, INT32 RiscPC)
{
	INT8 op, mode, scale, size, reg, base, inx;
	INT32 disp;
	op = (INT8)__ASHR((*instr).op, 5);
	if (op == 60) {
		if (!OPL_loaded((*instr).src2)) {
			OPL_FindMemReg(&(OPL_Instr->data)[__X((*instr).src2, OPL_Instr->len[0])], OPL_Instruction__typ, &mode, &scale, &size, &base, &inx, &disp);
			OPO_GenJMP(2, 0, base, inx, scale, disp);
			OPL_DecReg(base);
			OPL_DecReg(inx);
		} else {
			OPL_FindReg((*instr).src2, &reg);
			OPO_GenJMP(0, reg, -1, -1, 0, 0);
			OPL_DecReg(reg);
		}
	} else if (op == 59) {
		if (RiscPC >= (*instr).src2) {
			disp = (OPL_Instr->data)[__X((*instr).src2, OPL_Instr->len[0])].pc - (OPO_pc + 2);
			if (disp < -128) {
				disp -= 3;
			}
			OPO_GenJMP(3, -1, -1, -1, 0, disp);
		} else {
			OPO_GenJMP(3, -1, -1, -1, 0, (-2 - (OPL_Instr->data)[__X((*instr).src2, OPL_Instr->len[0])].pc) - 65536);
			(OPL_Instr->data)[__X((*instr).src2, OPL_Instr->len[0])].pc = RiscPC;
		}
	} else {
		__ASSERT((op >= 47 && op <= 58), 0);
		op = OPL_JmpConvert[__X(op - 47, 12)];
		if (RiscPC >= (*instr).src2) {
			disp = (OPL_Instr->data)[__X((*instr).src2, OPL_Instr->len[0])].pc - (OPO_pc + 2);
			if (disp < -128) {
				disp -= 4;
			}
			OPO_GenJcc(op, disp);
		} else {
			OPO_GenJcc(op, (-2 - (OPL_Instr->data)[__X((*instr).src2, OPL_Instr->len[0])].pc) - 65536);
			(OPL_Instr->data)[__X((*instr).src2, OPL_Instr->len[0])].pc = RiscPC;
		}
	}
}

static void OPL_Gen2 (OPL_Instruction *instr, ADDRESS *instr__typ)
{
	INT8 src, dummy;
	__ASSERT(__ASHR((*instr).op, 5) == 30 || __ASHR((*instr).op, 5) == 32, 0);
	dummy = -1;
	OPL_FindLoadReg((*instr).src1, &src);
	OPL_AssignReg((*instr).dest, &src, &dummy, &dummy);
	if ((*instr).reg != src) {
		OPO_GenMOV(0, (*instr).reg, src, -1, 0, 0, 0);
	}
	if (__ASHR((*instr).op, 5) == 30) {
		OPO_GenNEG(0, (*instr).reg, -1, -1, 0, 0);
	} else {
		OPO_GenNOT(0, (*instr).reg, -1, -1, 0, 0);
	}
	OPL_DecCheckReg((*instr).dest, src, dummy, dummy);
}

static void OPL_Gen3 (OPL_Instruction *instr, ADDRESS *instr__typ)
{
	INT8 op, mode, scale, size, base, inx, src, dummy, shiftReg;
	INT32 disp;
	op = (INT8)__ASHR((*instr).op, 5);
	mode = (INT8)__MASK(__ASHR((*instr).op, 3), -4);
	size = __ASHL((INT8)__MASK((*instr).op, -8), 3);
	if (mode == 3) {
		OPL_FindLoadReg((*instr).src1, &src);
		base = -1;
		inx = -1;
		scale = 0;
		disp = 0;
	} else if (!OPL_loaded((*instr).src1)) {
		if (!OPL_loaded((*instr).src2)) {
			OPL_FindLoadReg((*instr).src1, &src);
			OPL_FindMemReg(&(OPL_Instr->data)[__X((*instr).src2, OPL_Instr->len[0])], OPL_Instruction__typ, &dummy, &scale, &dummy, &base, &inx, &disp);
			mode = 2;
		} else if (((op == 16 || op == 21) || op == 22) || op == 23) {
			OPL_FindReg((*instr).src2, &src);
			OPL_FindMemReg(&(OPL_Instr->data)[__X((*instr).src1, OPL_Instr->len[0])], OPL_Instruction__typ, &dummy, &scale, &dummy, &base, &inx, &disp);
			mode = 2;
		} else {
			OPL_FindLoadReg((*instr).src1, &src);
			OPL_FindReg((*instr).src2, &base);
			inx = -1;
			scale = 0;
			disp = 0;
			mode = 0;
		}
	} else if (!OPL_loaded((*instr).src2)) {
		mode = 2;
		OPL_FindReg((*instr).src1, &src);
		OPL_FindMemReg(&(OPL_Instr->data)[__X((*instr).src2, OPL_Instr->len[0])], OPL_Instruction__typ, &dummy, &scale, &dummy, &base, &inx, &disp);
	} else {
		mode = 0;
		OPL_FindReg((*instr).src1, &src);
		OPL_FindReg((*instr).src2, &base);
		inx = -1;
		scale = 0;
		disp = 0;
	}
	src = __MASK(src, -8) + size;
	OPL_AssignReg((*instr).dest, &src, &base, &inx);
	if ((*instr).reg != src) {
		OPO_GenMOV(0, (*instr).reg, src, -1, 0, 0, 0);
	}
	if (op <= 23) {
		switch (op) {
			case 16: 
				op = 0;
				break;
			case 17: 
				op = 40;
				break;
			case 21: 
				op = 8;
				break;
			case 22: 
				op = 48;
				break;
			case 23: 
				op = 32;
				break;
			default: 
				__HALT(41);
				break;
		}
		OPO_GenTyp1(op, mode, (*instr).reg, base, inx, scale, disp, (*instr).src2);
	} else if (op == 25) {
		OPO_GenBTS(mode, (*instr).reg, base, inx, scale, disp, (*instr).src2);
	} else if (op == 24) {
		OPO_GenBTR(mode, (*instr).reg, base, inx, scale, disp, (*instr).src2);
	} else {
		__ASSERT(op <= 29, 0);
		if ((mode == 0 && !__IN(base, 0x020202, 32))) {
			shiftReg = 1 + __ASHL(__ASHR(base, 3), 3);
			OPL_AssignThisReg((*instr).src2, shiftReg);
			OPO_GenMOV(0, shiftReg, base, -1, 0, 0, 0);
			if (__IN(base, 0xff0000, 32)) {
				OPL_sregTab[__X(base - 16, 8)] = (-32767-1);
				OPL_FreeReg(base);
			} else {
				OPL_regTab[__X(__MASK(base, -8), 8)] = -1;
			}
			base = shiftReg;
		}
		switch (op) {
			case 26: 
				op = 4;
				break;
			case 27: 
				op = 7;
				break;
			case 28: 
				op = 5;
				break;
			case 29: 
				op = 0;
				break;
			default: 
				__HALT(41);
				break;
		}
		OPO_GenShiftRot(op, mode, (*instr).reg, base, inx, scale, disp, (*instr).src2);
	}
	OPL_DecCheckReg((*instr).dest, src, base, inx);
}

static void OPL_Flags (OPL_Instruction *instr, ADDRESS *instr__typ)
{
	INT8 op, mode, scale, size, base, inx, reg, dummy;
	INT32 disp;
	op = (INT8)__ASHR((*instr).op, 5);
	mode = (INT8)__MASK(__ASHR((*instr).op, 3), -4);
	size = __ASHL((INT8)__MASK((*instr).op, -8), 3);
	if (mode != 3) {
		if (!OPL_loaded((*instr).src1)) {
			if (!OPL_loaded((*instr).src2)) {
				OPL_FindLoadReg((*instr).src1, &reg);
				OPL_FindMemReg(&(OPL_Instr->data)[__X((*instr).src2, OPL_Instr->len[0])], OPL_Instruction__typ, &dummy, &scale, &dummy, &base, &inx, &disp);
				mode = 2;
			} else {
				OPL_FindReg((*instr).src2, &reg);
				OPL_FindMemReg(&(OPL_Instr->data)[__X((*instr).src1, OPL_Instr->len[0])], OPL_Instruction__typ, &dummy, &scale, &dummy, &base, &inx, &disp);
				mode = 1;
			}
		} else {
			OPL_FindReg((*instr).src1, &reg);
			if (!OPL_loaded((*instr).src2)) {
				OPL_FindMemReg(&(OPL_Instr->data)[__X((*instr).src2, OPL_Instr->len[0])], OPL_Instruction__typ, &dummy, &scale, &dummy, &base, &inx, &disp);
				mode = 1;
			} else {
				OPL_FindReg((*instr).src2, &base);
				inx = -1;
				disp = 0;
				mode = 0;
			}
		}
	} else if (!OPL_loaded((*instr).src1)) {
		OPL_FindMemReg(&(OPL_Instr->data)[__X((*instr).src1, OPL_Instr->len[0])], OPL_Instruction__typ, &dummy, &scale, &dummy, &base, &inx, &disp);
		reg = size;
		mode = 4;
	} else {
		OPL_FindReg((*instr).src1, &reg);
		base = -1;
		inx = -1;
		disp = 0;
	}
	if (op == 33) {
		OPO_GenTyp1(56, mode, reg, base, inx, scale, disp, (*instr).src2);
	} else if (op == 107) {
		OPO_GenTEST(mode, reg, base, inx, scale, disp, (*instr).src2);
	} else {
		OPO_GenBT(mode, reg, base, inx, scale, disp, (*instr).src2);
	}
	OPL_DecReg(reg);
	OPL_DecReg(base);
	OPL_DecReg(inx);
}

static void OPL_GenAbs (OPL_Instruction *instr, ADDRESS *instr__typ)
{
	INT8 size, src, reg, dummy;
	size = (INT8)__ASHL(__MASK((*instr).op, -8), 3);
	OPL_FindLoadReg((*instr).src1, &src);
	if (size == 16) {
		if (__IN((*instr).hint, 0xff, 32)) {
			if ((OPL_LastUse(src) && __MASK(src, -4) == (*instr).hint)) {
				if (__IN(src, 0x0f0000, 32)) {
					OPL_GetThisReg8(src + 4);
				} else {
					OPL_GetThisReg8(src - 4);
				}
				reg = __MASK(src, -4);
			} else {
				reg = (INT8)((INT16)(*instr).hint);
				OPL_GetThisReg(reg);
			}
		} else {
			if ((__IN((*instr).hint, 0xcf0000, 32) && OPL_regTab[__X((*instr).hint - 16, 8)] == -1)) {
				reg = (INT8)((INT16)((*instr).hint - 16));
			} else {
				reg = 3;
				while ((reg >= 0 && OPL_regTab[__X(reg, 8)] != -1)) {
					reg -= 1;
				}
				if ((OPL_LastUse(src) && ((__IN(src, 0x0f0000, 32) && OPL_sregTab[__X((src - 16) + 4, 8)] == -1) || (__IN(src, 0xf00000, 32) && OPL_sregTab[__X((src - 16) - 4, 8)] == -1)))) {
					reg = __MASK(src, -4);
				} else if (reg < 0) {
					OPL_GetSplittableReg(&reg);
				}
			}
		}
		OPO_GenMOVSX(0, 0, reg, src, -1, 0, 0);
		if (OPL_LastUse(src)) {
			OPL_FreeReg(src);
			src = -1;
		}
		OPL_regTab[__X(reg, 8)] = -32767;
		OPL_sregTab[__X(reg, 8)] = (*instr).dest;
		OPL_sregTab[__X(reg + 4, 8)] = -1;
		reg += 16;
		(*instr).reg = reg;
		OPO_GenTyp1(48, 0, reg, reg + 4, -1, 0, 0, 0);
		OPO_GenTyp1(40, 0, reg, reg + 4, -1, 0, 0, 0);
	} else {
		if (OPL_regTab[2] == -1) {
			OPL_regTab[2] = (-32767-1);
		}
		if ((!OPL_LastUse(src) && __IN(src, 0x0101, 32))) {
			OPL_AssignNewReg((*instr).src1);
			OPL_regTab[0] = (-32767-1);
			OPO_GenMOV(0, (OPL_Instr->data)[__X((*instr).src1, OPL_Instr->len[0])].reg, 0, -1, 0, 0, 0);
		} else if (!__IN(src, 0x0101, 32)) {
			OPL_GetThisReg(0);
			OPO_GenMOV(0, 0, src, -1, 0, 0, 0);
			if (OPL_LastUse(src)) {
				OPL_FreeReg(src);
				src = -1;
			}
		} else {
			OPL_FreeReg(src);
			src = -1;
			OPL_GetThisReg(0);
		}
		(*instr).reg = size;
		OPL_regTab[0] = (*instr).dest;
		if (OPL_regTab[2] != (-32767-1)) {
			OPL_GetThisReg(2);
		}
		OPO_Prefix(size, &dummy);
		OPO_PutByte(153);
		OPO_GenTyp1(48, 0, size, 2 + size, -1, 0, 0, 0);
		OPO_GenTyp1(40, 0, size, 2 + size, -1, 0, 0, 0);
		OPL_FreeReg(2);
	}
	OPL_DecReg(src);
	if ((__IN((*instr).hint, 0xff, 32) && __MASK((*instr).reg, -8) != (*instr).hint)) {
		src = (*instr).reg;
		OPL_AssignThisReg((*instr).dest, (INT8)((INT16)(*instr).hint) + size);
		OPO_GenMOV(0, (*instr).reg, src, -1, 0, 0, 0);
		OPL_FreeReg(src);
	}
}

static void OPL_GenDivMod (OPL_Instruction *instr, ADDRESS *instr__typ)
{
	INT8 size, mode, src, base, inx, scale, dummy;
	INT32 disp, pRegBase, pRegInx;
	size = __ASHL((INT8)__MASK((*instr).op, -8), 3);
	mode = (INT8)__MASK(__ASHR((*instr).op, 3), -4);
	if ((size != 16 && OPL_regTab[2] == -1)) {
		OPL_regTab[2] = (-32767-1);
	}
	if (mode != 3) {
		if (OPL_loaded((*instr).src2)) {
			OPL_FindReg((*instr).src2, &base);
			inx = -1;
			scale = 0;
			disp = 0;
		} else {
			mode = 2;
			OPL_FindMemReg(&(OPL_Instr->data)[__X((*instr).src2, OPL_Instr->len[0])], OPL_Instruction__typ, &dummy, &scale, &dummy, &base, &inx, &disp);
		}
	} else {
		inx = -1;
		base = -1;
	}
	if (!OPL_loaded((*instr).src1)) {
		(OPL_Instr->data)[__X((*instr).src1, OPL_Instr->len[0])].hint = 0;
		OPL_FindLoadReg((*instr).src1, &src);
	} else {
		OPL_FindReg((*instr).src1, &src);
	}
	if (base >= 16) {
		pRegBase = OPL_sregTab[__X(base - 16, 8)];
	} else if (base != -1) {
		pRegBase = OPL_regTab[__X(__MASK(base, -8), 8)];
	}
	if (inx != -1) {
		__ASSERT(__IN(inx, 0xff, 32), 0);
		pRegInx = OPL_regTab[__X(inx, 8)];
	}
	if (size == 16) {
		if ((OPL_LastUse(src) && __IN(src, 0x110000, 32))) {
			if (src == 16) {
				OPL_GetThisReg8(20);
			} else {
				OPL_GetThisReg8(16);
			}
			OPL_regTab[0] = (-32767-1);
		} else {
			OPL_GetThisReg(0);
		}
		OPO_GenMOVSX(0, 0, 8, src, -1, 0, 0);
		if (OPL_LastUse(src)) {
			OPL_FreeReg(src);
			src = -1;
		}
		if (mode == 3) {
			mode = 0;
			inx = -1;
			scale = 0;
			disp = 0;
			OPL_GetReg8(&base);
			OPO_GenMOV(3, base, -1, -1, 0, 0, (*instr).src2);
		}
	} else {
		if ((!OPL_LastUse(src) && __IN(src, 0x0101, 32))) {
			OPL_AssignNewReg((*instr).src1);
			src = (OPL_Instr->data)[__X((*instr).src1, OPL_Instr->len[0])].reg;
			OPO_GenMOV(0, src, 0, -1, 0, 0, 0);
			OPL_regTab[0] = (-32767-1);
		} else if (!__IN(src, 0x0101, 32)) {
			OPL_GetThisReg(0);
			OPO_GenMOV(0, size, src, -1, 0, 0, 0);
			if (OPL_LastUse(src)) {
				OPL_FreeReg(src);
				src = -1;
			}
		} else {
			OPL_FreeReg(src);
			src = -1;
			OPL_regTab[0] = (-32767-1);
		}
		if (OPL_regTab[2] != (-32767-1)) {
			OPL_GetThisReg(2);
		}
		if (mode == 3) {
			OPL_GetReg(&base);
			base += size;
			inx = -1;
			OPO_GenMOV(3, base, -1, -1, 0, 0, (*instr).src2);
			mode = 0;
		}
		OPO_Prefix(size, &dummy);
		OPO_PutByte(153);
	}
	if ((base != -1 && __MASK(__ASHR((*instr).op, 3), -4) != 3)) {
		base = (OPL_Instr->data)[__X(pRegBase, OPL_Instr->len[0])].reg;
	}
	if (inx != -1) {
		inx = (OPL_Instr->data)[__X(pRegInx, OPL_Instr->len[0])].reg;
	}
	if (mode == 0) {
		OPO_GenIDIV(0, base, -1, -1, 0, 0);
	} else {
		OPO_GenIDIV(mode, size, base, inx, scale, disp);
	}
	if (__ASHR((*instr).op, 5) == 19) {
		OPO_GenShiftRot(4, 3, 2 + size, -1, -1, 0, 0, 1);
		OPO_GenTyp1(24, 3, size, -1, -1, 0, 0, 0);
		(*instr).reg = size;
		if (size == 16) {
			OPL_regTab[0] = -32767;
			OPL_sregTab[0] = (*instr).dest;
			OPL_sregTab[4] = -1;
		} else {
			OPL_regTab[0] = (*instr).dest;
			OPL_FreeReg(2);
		}
	} else {
		if (size == 16) {
			OPO_GenTyp1(56, 3, 20, -1, -1, 0, 0, 0);
		} else {
			OPO_GenTyp1(56, 3, 2 + size, -1, -1, 0, 0, 0);
		}
		__ASSERT(__ASHR((*instr).op, 5) == 20, 0);
		if (size == 8) {
			OPO_GenJcc(13, 3);
		} else {
			OPO_GenJcc(13, 2);
		}
		if (size == 16) {
			OPO_GenTyp1(0, mode, 20, base, inx, scale, disp, 0);
			(*instr).reg = 20;
			OPL_regTab[0] = -32767;
			OPL_sregTab[4] = (*instr).dest;
			OPL_sregTab[0] = -1;
		} else {
			OPO_GenTyp1(0, mode, 2 + size, base, inx, scale, disp, 0);
			(*instr).reg = 2 + size;
			OPL_regTab[2] = (*instr).dest;
			OPL_FreeReg(0);
		}
	}
	if (__MASK(__ASHR((*instr).op, 3), -4) == 3) {
		OPL_FreeReg(base);
		base = -1;
	}
	OPL_DecCheckReg((*instr).dest, src, base, inx);
	if ((__IN((*instr).hint, 0xff, 32) && __MASK((*instr).reg, -8) != (*instr).hint)) {
		src = (*instr).reg;
		OPL_AssignThisReg((*instr).dest, (INT8)((INT16)(*instr).hint) + size);
		OPO_GenMOV(0, (*instr).reg, src, -1, 0, 0, 0);
		OPL_FreeReg(src);
	}
}

static void OPL_GenMul (OPL_Instruction *instr, ADDRESS *instr__typ)
{
	INT8 size, mode, src, base, inx, scale, dummy;
	INT32 disp, pRegBase, pRegInx;
	size = (INT8)__ASHL(__MASK((*instr).op, -8), 3);
	mode = (INT8)__MASK(__ASHR((*instr).op, 3), -4);
	if (mode != 3) {
		if (OPL_loaded((*instr).src2)) {
			OPL_FindReg((*instr).src2, &base);
			inx = -1;
			scale = 0;
			disp = 0;
		} else {
			mode = 1;
			OPL_FindMemReg(&(OPL_Instr->data)[__X((*instr).src2, OPL_Instr->len[0])], OPL_Instruction__typ, &dummy, &scale, &dummy, &base, &inx, &disp);
		}
	}
	if (!OPL_loaded((*instr).src1)) {
		if (size == 16) {
			(OPL_Instr->data)[__X((*instr).src1, OPL_Instr->len[0])].hint = 0;
		}
		OPL_FindLoadReg((*instr).src1, &src);
	} else {
		OPL_FindReg((*instr).src1, &src);
	}
	if ((mode == 3 && size != 16)) {
		inx = -1;
		base = -1;
		OPL_AssignReg((*instr).dest, &src, &base, &inx);
		OPO_GenIMUL(3, 0, (*instr).reg, src, -1, 0, 0, (*instr).src2);
	} else {
		if (size == 16) {
			if (mode != 3) {
				if (base >= 16) {
					pRegBase = OPL_sregTab[__X(base - 16, 8)];
				} else if (base != -1) {
					pRegBase = OPL_regTab[__X(__MASK(base, -8), 8)];
				}
				if (inx != -1) {
					__ASSERT(inx < 16, 0);
					pRegInx = OPL_regTab[__X(__MASK(inx, -8), 8)];
				}
			}
			if ((OPL_LastUse(src) && __IN(src, 0x110000, 32))) {
				if (src == 16) {
					if (!((mode == 0 && OPL_LastUse(base)))) {
						OPL_GetThisReg8(20);
					}
				} else {
					OPL_GetThisReg8(16);
					OPO_GenMOV(0, 16, src, -1, 0, 0, 0);
				}
			} else {
				OPL_GetThisReg(0);
				src = (OPL_Instr->data)[__X((*instr).src1, OPL_Instr->len[0])].reg;
				OPO_GenMOV(0, 16, src, -1, 0, 0, 0);
			}
			if (OPL_LastUse(src)) {
				OPL_FreeReg(src);
				src = -1;
			}
			(*instr).reg = 16;
			OPL_regTab[0] = -32767;
			OPL_sregTab[0] = (*instr).dest;
			OPL_sregTab[4] = -1;
			if (mode == 3) {
				mode = 0;
				OPL_GetReg8(&base);
				inx = -1;
				scale = 0;
				disp = 0;
				OPO_GenMOV(3, base, -1, -1, 0, 0, (*instr).src2);
				OPO_GenIMUL(mode, 1, (*instr).reg, base, inx, scale, disp, 0);
				OPL_FreeReg(base);
				base = -1;
			} else {
				if (base != -1) {
					base = (OPL_Instr->data)[__X(pRegBase, OPL_Instr->len[0])].reg;
				}
				if (inx != -1) {
					inx = (OPL_Instr->data)[__X(pRegInx, OPL_Instr->len[0])].reg;
				}
				OPO_GenIMUL(mode, 1, (*instr).reg, base, inx, scale, disp, 0);
			}
		} else {
			__ASSERT(__IN(size, 0x0101, 32), 0);
			OPL_AssignReg((*instr).dest, &src, &base, &inx);
			if ((*instr).reg != src) {
				OPO_GenMOV(0, (*instr).reg, src, -1, 0, 0, 0);
			}
			if ((__IN((*instr).reg, 0x0101, 32) && OPL_regTab[2] == -1)) {
				OPO_GenIMUL(mode, 1, (*instr).reg, base, inx, scale, disp, 0);
			} else {
				OPO_GenIMUL(mode, 0, (*instr).reg, base, inx, scale, disp, 0);
			}
		}
	}
	OPL_DecCheckReg((*instr).dest, src, base, inx);
}

static void OPL_GenRepMovs (OPL_Instruction *instr, ADDRESS *instr__typ)
{
	INT8 src, dest, nofElem, tmp;
	OPL_FindLoadReg((*instr).dest, &dest);
	__ASSERT(__IN(dest, 0xff, 32), 0);
	if (dest != 7) {
		if ((*instr).dest >= 0) {
			OPL_AssignThisReg((*instr).dest, 7);
		} else {
			OPL_GetThisReg(7);
		}
		OPO_GenMOV(0, 7, dest, -1, 0, 0, 0);
		if (!__IN(dest, 0x30, 32)) {
			OPL_regTab[__X(dest, 8)] = -1;
		}
	}
	OPL_FindLoadReg((*instr).src1, &src);
	__ASSERT(__IN(src, 0xff, 32), 0);
	if (src != 6) {
		if ((*instr).src1 >= 0) {
			OPL_AssignThisReg((*instr).src1, 6);
		} else {
			OPL_GetThisReg(6);
		}
		OPO_GenMOV(0, 6, src, -1, 0, 0, 0);
		if (!__IN(src, 0x30, 32)) {
			OPL_regTab[__X(src, 8)] = -1;
		}
	}
	OPL_FindLoadReg((*instr).src2, &nofElem);
	__ASSERT(__IN(nofElem, 0xff, 32), 0);
	if (nofElem != 1) {
		if ((*instr).src2 >= 0) {
			OPL_AssignThisReg((*instr).src2, 1);
		} else {
			OPL_GetThisReg(1);
		}
		OPO_GenMOV(0, 1, nofElem, -1, 0, 0, 0);
		if (!__IN(nofElem, 0x30, 32)) {
			OPL_regTab[__X(nofElem, 8)] = -1;
		}
	}
	if (((*instr).inx == 16 && (*instr).hint == -1)) {
		OPL_GetReg8(&tmp);
		OPO_GenMOV(0, tmp, 17, -1, 0, 0, 0);
		OPO_GenShiftRot(5, 3, 1, -1, -1, 0, 0, 2);
		OPO_GenTyp1(32, 3, tmp, -1, -1, 0, 0, 3);
		OPO_GenRepString(82, 0);
		OPO_GenMOV(0, 17, tmp, -1, 0, 0, 0);
		OPO_GenRepString(82, 16);
		OPL_FreeReg(tmp);
	} else if (((*instr).inx == 16 && (*instr).hint == 1)) {
		OPL_GetReg(&tmp);
		OPO_GenMOV(0, tmp, 1, -1, 0, 0, 0);
		OPO_GenShiftRot(5, 3, tmp, -1, -1, 0, 0, 2);
		OPO_GenTyp1(32, 3, 17, -1, -1, 0, 0, 3);
		OPO_GenRepString(82, 16);
		OPO_GenTyp1(40, 3, 6, -1, -1, 0, 0, 3);
		OPO_GenTyp1(40, 3, 7, -1, -1, 0, 0, 3);
		OPO_GenMOV(0, 1, tmp, -1, 0, 0, 0);
		OPO_GenRepString(82, 0);
		OPL_FreeReg(tmp);
	} else {
		OPO_GenRepString(82, (INT16)(*instr).inx);
	}
	if (OPL_regTab[1] == (-32767-1)) {
		OPL_FreeReg(1);
	} else {
		OPL_DecReg(1);
	}
	if (OPL_regTab[6] == (-32767-1)) {
		OPL_FreeReg(6);
	} else {
		OPL_DecReg(6);
	}
	if (OPL_regTab[7] == (-32767-1)) {
		OPL_FreeReg(7);
	} else {
		OPL_DecReg(7);
	}
}

static void OPL_GenCmpString (OPL_Instruction *instr, ADDRESS *instr__typ)
{
	INT8 src, srcAdr, src2Adr;
	INT32 Lfix, L0, L1;
	Lfix = OPO_pc;
	OPL_FindLoadReg((*instr).src1, &srcAdr);
	OPL_FindLoadReg((*instr).src2, &src2Adr);
	OPL_GetReg8(&src);
	OPO_GenMOV(2, src, srcAdr, -1, 0, 0, 0);
	OPO_GenTyp1(56, 2, src, src2Adr, -1, 0, 0, 0);
	OPO_GenJcc(5, 0);
	L0 = OPO_pc - 1;
	OPO_GenTyp1(56, 3, src, -1, -1, 0, 0, 0);
	OPO_GenJcc(4, 0);
	L1 = OPO_pc - 1;
	OPO_GenINC(3, srcAdr, -1, -1, 0, 0);
	OPO_GenINC(3, src2Adr, -1, -1, 0, 0);
	OPO_GenJMP(3, -1, -1, -1, 0, Lfix - (OPO_pc + 2));
	OPO_PutByteAt(L0, (INT16)(OPO_pc - (L0 + 1)));
	OPO_PutByteAt(L1, (INT16)(OPO_pc - (L1 + 1)));
	OPL_FreeReg(src);
	OPL_DecReg(srcAdr);
	OPL_DecReg(src2Adr);
}

static void OPL_Setcc (OPL_Instruction *instr, ADDRESS *instr__typ)
{
	INT8 dummy;
	dummy = -1;
	OPL_AssignReg((*instr).dest, &dummy, &dummy, &dummy);
	OPO_GenSetcc(OPL_SetccConvert[__X(__ASHR((*instr).op, 5) - 35, 12)], 0, (*instr).reg, -1, 0, 0);
}

static void OPL_GenTrap (INT32 trapNr)
{
	OPO_GenPUSH(3, 0, -1, -1, 0, 0, trapNr);
	OPO_PutByte(204);
}

static void OPL_GenIntpt (OPL_Instruction Instr)
{
	OPO_PutByte(205);
	OPO_PutByte((INT8)((INT16)Instr.src2));
	OPL_FreeReg(0);
	OPL_FreeReg(3);
	OPL_FreeReg(1);
	OPL_FreeReg(2);
}

static void OPL_GenTrapCC (OPL_Instruction *instr, ADDRESS *instr__typ)
{
	INT8 op;
	if (__ASHR((*instr).op, 5) == 91) {
		OPO_PutByte(206);
	} else {
		switch (__ASHR((*instr).op, 5)) {
			case 61: 
				op = 5;
				break;
			case 62: 
				op = 4;
				break;
			case 92: 
				op = 15;
				break;
			case 63: 
				op = 6;
				break;
			case 90: 
				op = 2;
				break;
			default: 
				__HALT(41);
				break;
		}
		OPO_GenJcc(op, 3);
		OPO_GenPUSH(3, 0, -1, -1, 0, 0, (*instr).src2);
		OPO_PutByte(204);
	}
}

static void OPL_FixupAndGenTrap (void)
{
	INT32 i, fixuppos, pos, next;
	i = 0;
	while (i < 10) {
		if (OPL_trapFixupTab[__X(i, 10)] != -1) {
			fixuppos = OPO_pc;
			pos = OPL_trapFixupTab[__X(i, 10)];
			do {
				OPO_GetDWord(pos, &next);
				OPO_PutDWordAt(pos, fixuppos - (pos + 4));
				pos = (-2 - next) - 65536;
			} while (!(pos == -1));
			OPL_GenTrap(i);
		}
		i += 1;
	}
}

static void OPL_GenShort (OPL_Instruction *instr, ADDRESS *instr__typ)
{
	INT8 src, reg, hint;
	OPL_FindReg((*instr).src1, &src);
	hint = (INT8)((INT16)(*instr).hint);
	__ASSERT(OPL_LastUse(src), 0);
	if (__ASHL(__MASK((*instr).op, -8), 3) == 8) {
		__ASSERT(__IN(src, 0xff, 32), 0);
		if ((__IN(hint, 0xff, 32) && src != hint)) {
			OPL_AssignThisReg((*instr).dest, hint + 8);
			OPO_GenMOV(0, (*instr).reg, src, -1, 0, 0, 0);
			OPL_FreeReg(src);
		} else {
			OPL_FreeReg(src);
			OPL_AssignThisReg((*instr).dest, src + 8);
		}
	} else {
		__ASSERT((__ASHL(__MASK((*instr).op, -8), 3) == 16 && __IN(src, 0xffff, 32)), 0);
		if ((__IN(hint, 0xff, 32) && __MASK(src, -8) != hint)) {
			__ASSERT(__IN(hint, 0x0f, 32), 0);
			OPL_AssignThisReg((*instr).dest, hint + 16);
			if (__IN(src, 0x0f0f, 32)) {
				OPO_GenMOV(0, (*instr).reg, __MASK(src, -8) + 16, -1, 0, 0, 0);
			} else {
				OPL_GetThisReg8((*instr).reg + 4);
				OPL_FreeReg((*instr).reg + 4);
				OPO_GenMOV(0, __MASK((*instr).reg, -4), src, -1, 0, 0, 0);
			}
			OPL_FreeReg(src);
		} else if (__IN(src, 0x0f0f, 32)) {
			OPL_FreeReg(src);
			OPL_AssignThisReg((*instr).dest, __MASK(src, -8) + 16);
		} else {
			OPL_GetSplittableReg(&reg);
			OPO_GenMOV(0, reg, src, -1, 0, 0, 0);
			OPL_FreeReg(src);
			OPL_FreeReg(reg);
			OPL_AssignThisReg((*instr).dest, __MASK(reg, -8) + 16);
		}
	}
}

static void OPL_GenPhi (OPL_Instruction *instr, ADDRESS *instr__typ)
{
	INT8 src1, src2;
	__ASSERT(((OPL_Instr->data)[__X((*instr).src2, OPL_Instr->len[0])].reg >= 0 && (OPL_Instr->data)[__X((*instr).src1, OPL_Instr->len[0])].reg != -1), 0);
	if ((OPL_Instr->data)[__X((*instr).src1, OPL_Instr->len[0])].reg < 0) {
		src1 = -2 - (OPL_Instr->data)[__X((*instr).src1, OPL_Instr->len[0])].reg;
	} else {
		src1 = (OPL_Instr->data)[__X((*instr).src1, OPL_Instr->len[0])].reg;
		OPL_FreeReg(src1);
	}
	src2 = (OPL_Instr->data)[__X((*instr).src2, OPL_Instr->len[0])].reg;
	if (src1 != src2) {
		OPL_AssignThisReg((*instr).src2, src1);
		OPO_GenMOV(0, src1, src2, -1, 0, 0, 0);
		if (src2 >= 16) {
			src2 -= 16;
			OPL_sregTab[__X(src2, 8)] = -1;
			if (src2 < 4) {
				if (OPL_sregTab[__X(src2 + 4, 8)] == -1) {
					OPL_regTab[__X(src2, 8)] = -1;
				}
			} else if (OPL_sregTab[__X(src2 - 4, 8)] == -1) {
				OPL_regTab[__X(__MASK(src2, -4), 8)] = -1;
			}
		} else {
			OPL_regTab[__X(__MASK(src2, -8), 8)] = -1;
		}
	}
}

static void OPL_GetFreg (INT8 *freg)
{
	OPL_ftop = __MASK(OPL_ftop - 1, -8);
	if (OPL_fregTab[__X(OPL_ftop, 8)] != -1) {
		OPM_err(216);
		OPL_RegErr = 1;
		*freg = OPL_ftop;
		return;
	}
	OPL_fregTab[__X(OPL_ftop, 8)] = (-32767-1);
	*freg = OPL_ftop;
}

static void OPL_FreeFreg (INT8 freg)
{
	if (freg > -1) {
		if (OPL_fregTab[__X(freg, 8)] > -1) {
			(OPL_Instr->data)[__X(OPL_fregTab[__X(freg, 8)], OPL_Instr->len[0])].reg = -2 - freg;
		}
		OPL_fregTab[__X(freg, 8)] = -1;
		if (freg == OPL_ftop) {
			OPL_ftop = __MASK(OPL_ftop + 1, -8);
			while ((OPL_FreeRegDisp > 0 && OPL_fregTab[__X(OPL_ftop, 8)] == -1)) {
				OPL_ftop = __MASK(OPL_ftop + 1, -8);
				OPL_FreeRegDisp -= 1;
			}
		} else {
			OPO_GenFFREE(__MASK(freg - OPL_ftop, -8));
			OPL_FreeRegDisp += 1;
		}
	}
}

static void OPL_ReleaseFreg (INT8 freg)
{
	if (freg > -1) {
		if (OPL_fregTab[__X(freg, 8)] > -1) {
			(OPL_Instr->data)[__X(OPL_fregTab[__X(freg, 8)], OPL_Instr->len[0])].reg = -2 - freg;
		}
		OPL_fregTab[__X(freg, 8)] = -1;
		OPL_ftop = __MASK(OPL_ftop + 1, -8);
	}
}

static void OPL_AssignFreg (INT32 pReg)
{
	INT8 freg;
	OPL_GetFreg(&freg);
	OPL_fregTab[__X(freg, 8)] = pReg;
	(OPL_Instr->data)[__X(pReg, OPL_Instr->len[0])].reg = freg;
}

static void OPL_TakeFreg (INT32 pReg, INT8 freg)
{
	__ASSERT(OPL_fregTab[__X(freg, 8)] == -1, 0);
	OPL_fregTab[__X(freg, 8)] = pReg;
	(OPL_Instr->data)[__X(pReg, OPL_Instr->len[0])].reg = freg;
}

static void OPL_FindFreg (INT32 pReg, INT8 *freg)
{
	__ASSERT((pReg >= 0 && (OPL_Instr->data)[__X(pReg, OPL_Instr->len[0])].reg >= 0), 0);
	*freg = (OPL_Instr->data)[__X(pReg, OPL_Instr->len[0])].reg;
}

static BOOLEAN OPL_LastUseF (INT8 freg)
{
	__ASSERT((__IN(freg, 0xff, 32) && OPL_fregTab[__X(freg, 8)] >= 0), 0);
	return (OPL_Instr->data)[__X(OPL_fregTab[__X(freg, 8)], OPL_Instr->len[0])].used == 1;
}

static void OPL_DecCheckFreg (INT8 freg)
{
	INT32 pReg;
	if (freg > -1) {
		pReg = OPL_fregTab[__X(freg, 8)];
		(OPL_Instr->data)[__X(pReg, OPL_Instr->len[0])].used -= 1;
		if ((OPL_Instr->data)[__X(pReg, OPL_Instr->len[0])].used == 0) {
			OPL_FreeFreg(freg);
		}
	}
}

static void OPL_Fload (OPL_Instruction *instr, ADDRESS *instr__typ)
{
	INT8 mode, scale, size, base, inx;
	INT32 disp;
	OPL_FindMemReg(&*instr, instr__typ, &mode, &scale, &size, &base, &inx, &disp);
	size = __ASHL(__ASHR(size, 3) - 3, 1);
	__ASSERT(mode != 0, 0);
	OPL_AssignFreg((*instr).dest);
	if (__ASHR((*instr).op, 5) == 82) {
		OPO_GenFLD(mode, 1, base, inx, scale, disp);
	} else {
		OPO_GenFLD(mode, size, base, inx, scale, disp);
	}
	OPL_DecReg(base);
	OPL_DecReg(inx);
	if ((((__IN(mode, 0x06, 32) && base == -1)) && !(*instr).abs)) {
		OPL_AbsAccess((*instr).node, OPO_pc - 4);
	}
}

static void OPL_Fstore (OPL_Instruction *instr, ADDRESS *instr__typ)
{
	INT8 mode, scale, size, base, inx, src;
	INT32 disp;
	OPL_FindMemReg(&*instr, instr__typ, &mode, &scale, &size, &base, &inx, &disp);
	size = __ASHL(__ASHR(size, 3) - 3, 1);
	if (__ASHR((*instr).op, 5) == 81) {
		size = 1;
	}
	OPL_FindFreg((*instr).dest, &src);
	__ASSERT((OPL_LastUseF(src) && src == OPL_ftop), 0);
	OPO_GenFSTP(mode, size, base, inx, scale, disp);
	OPL_DecCheckFreg(src);
	OPL_DecReg(base);
	OPL_DecReg(inx);
	if ((((__IN(mode, 0x06, 32) && base == -1)) && !(*instr).abs)) {
		OPL_AbsAccess((*instr).node, OPO_pc - 4);
	}
	OPO_PutByte(155);
}

static void OPL_FloatGen1 (OPL_Instruction *instr, ADDRESS *instr__typ)
{
	INT8 src;
	OPL_FindFreg((*instr).src1, &src);
	__ASSERT((OPL_LastUseF(src) && src == OPL_ftop), 0);
	OPL_ReleaseFreg(src);
	OPL_AssignFreg((*instr).dest);
	if (__ASHR((*instr).op, 5) == 87) {
		OPO_GenFop1(4);
	} else {
		__ASSERT(__ASHR((*instr).op, 5) == 88, 0);
		OPO_GenFop1(5);
	}
}

static void OPL_FloatGen3 (OPL_Instruction *instr, ADDRESS *instr__typ)
{
	INT8 mode, size, src, src1, src2;
	BOOLEAN reverse, r2;
	size = (INT8)__ASHL(__MASK((*instr).op, -8) - 3, 1);
	OPL_FindFreg((*instr).src1, &src1);
	OPL_FindFreg((*instr).src2, &src2);
	r2 = 0;
	if ((!OPL_LastUseF(src1) && !OPL_LastUseF(src2))) {
		OPO_GenFLD(0, size, __MASK(src1 - OPL_ftop, -8), -1, 0, 0);
		src = src2;
		mode = 5;
		reverse = 0;
	} else if (src1 == OPL_ftop) {
		reverse = 1;
		if (OPL_LastUseF(src1)) {
			if (OPL_LastUseF(src2)) {
				mode = 7;
			} else {
				mode = 5;
				reverse = 0;
			}
		} else {
			mode = 6;
		}
		src = src2;
	} else if (src2 == OPL_ftop) {
		reverse = 0;
		r2 = 1;
		if (OPL_LastUseF(src2)) {
			if (OPL_LastUseF(src1)) {
				mode = 7;
			} else {
				mode = 5;
				reverse = 1;
			}
		} else {
			mode = 6;
		}
		src = src1;
	} else {
		OPO_GenFLD(0, size, __MASK(src1 - OPL_ftop, -8), -1, 0, 0);
		if (OPL_LastUseF(src1)) {
			OPL_FreeFreg(src1);
			src1 = -1;
		}
		if (OPL_LastUseF(src2)) {
			mode = 7;
			reverse = 1;
		} else {
			mode = 5;
			reverse = 0;
		}
		src = src2;
	}
	switch (__ASHR((*instr).op, 5)) {
		case 83: 
			OPO_GenFADD(mode, size, __MASK(src - OPL_ftop, -8), -1, 0, 0);
			break;
		case 84: 
			if (reverse) {
				OPO_GenFSUBR(mode, size, __MASK(src - OPL_ftop, -8), -1, 0, 0);
			} else {
				OPO_GenFSUB(mode, size, __MASK(src - OPL_ftop, -8), -1, 0, 0);
			}
			break;
		case 85: 
			OPO_GenFMUL(mode, size, __MASK(src - OPL_ftop, -8), -1, 0, 0);
			break;
		case 86: 
			if (reverse) {
				OPO_GenFDIVR(mode, size, __MASK(src - OPL_ftop, -8), -1, 0, 0);
			} else {
				OPO_GenFDIV(mode, size, __MASK(src - OPL_ftop, -8), -1, 0, 0);
			}
			break;
		default: 
			__HALT(41);
			break;
	}
	if (r2) {
		OPL_DecCheckFreg(src2);
		OPL_DecCheckFreg(src1);
	} else {
		OPL_DecCheckFreg(src1);
		OPL_DecCheckFreg(src2);
	}
	if (mode == 5) {
		OPL_AssignFreg((*instr).dest);
	} else if ((mode == 7 && __MASK(src + 1, -8) == OPL_ftop)) {
		OPL_AssignFreg((*instr).dest);
	} else {
		OPL_TakeFreg((*instr).dest, src);
	}
}

static void OPL_FloatCmp (OPL_Instruction *instr, ADDRESS *instr__typ)
{
	INT8 size, src1, src2, reg;
	BOOLEAN stackOK;
	size = (INT8)__ASHL(__MASK((*instr).op, -8) - 3, 1);
	OPL_FindFreg((*instr).src1, &src1);
	OPL_FindFreg((*instr).src2, &src2);
	__ASSERT((OPL_LastUseF(src1) && OPL_LastUseF(src2)), 0);
	if (src1 == OPL_ftop) {
		if (src2 == __MASK(OPL_ftop + 1, -8)) {
			OPO_GenFop1(0);
			stackOK = 1;
		} else {
			OPO_GenFCOMP(0, size, __MASK(src2 - OPL_ftop, -8), -1, 0, 0);
			stackOK = 0;
		}
	} else {
		stackOK = 0;
		OPL_GetFreg(&reg);
		OPO_GenFLD(0, size, __MASK((src1 - OPL_ftop) - 1, -8), -1, 0, 0);
		OPO_GenFCOMP(0, size, __MASK(src2 - OPL_ftop, -8), -1, 0, 0);
		OPL_ReleaseFreg(reg);
	}
	OPL_GetThisReg(0);
	OPO_GenFop1(6);
	OPO_PutByte(158);
	if (stackOK) {
		OPL_DecCheckFreg(src1);
		OPL_DecCheckFreg(src2);
	} else {
		OPL_DecCheckFreg(src1);
		OPL_DecCheckFreg(src2);
		OPO_GenFFREE(0);
	}
	OPL_FreeReg(0);
}

static void OPL_GenEntier (OPL_Instruction *instr, ADDRESS *instr__typ)
{
	INT8 dest, src, reg, dummy;
	OPL_FindFreg((*instr).src1, &src);
	dummy = -1;
	OPL_AssignReg((*instr).dest, &dummy, &dummy, &dummy);
	dest = (*instr).reg;
	__ASSERT(__IN(dest, 0xff, 32), 0);
	OPO_GenTyp1(40, 3, 4, -1, -1, 0, 0, 8);
	OPO_GenFSTCW(4, -1, 0, 0);
	OPO_PutByte(155);
	OPO_GenMOV(2, dest, 4, -1, 0, 0, 0);
	OPO_GenTyp1(32, 3, dest, -1, -1, 0, 0, 62463);
	OPO_GenTyp1(8, 3, dest, -1, -1, 0, 0, 1024);
	OPO_GenMOV(1, dest, 4, -1, 0, 4, 0);
	OPO_GenFLDCW(4, -1, 0, 4);
	if (!OPL_LastUseF(src)) {
		if (src != OPL_ftop) {
			OPL_GetFreg(&reg);
			OPO_GenFLD(0, reg, src, -1, 0, 0);
			OPO_GenFSTP(1, 1, 4, -1, 0, 4);
			OPL_ReleaseFreg(reg);
		} else {
			OPO_GenFST(1, 1, 4, -1, 0, 4);
		}
	} else {
		OPO_GenFSTP(1, 1, 4, -1, 0, 4);
	}
	OPO_PutByte(155);
	OPO_GenFLDCW(4, -1, 0, 0);
	OPO_GenMOV(2, dest, 4, -1, 0, 4, 0);
	OPO_GenTyp1(0, 3, 4, -1, -1, 0, 0, 8);
	OPL_DecCheckFreg(src);
}

static void OPL_ClearSDynArr (OPL_Instruction *instr, ADDRESS *instr__typ)
{
	INT32 L;
	INT8 reg;
	OPL_FindReg((*instr).src1, &reg);
	OPO_GenTyp1(48, 0, 0, 0, -1, 0, 0, 0);
	L = OPO_pc;
	OPO_GenPUSH(0, 0, -1, -1, 0, 0, -1);
	OPO_GenDEC(3, reg, -1, -1, 0, 0);
	OPO_GenJcc(15, L - (OPO_pc + 2));
	OPL_FreeReg(reg);
}

static struct GenEnter__52 {
	BOOLEAN *first;
	INT32 *enoff, *ensize, *last;
	struct GenEnter__52 *lnk;
} *GenEnter__52_s;

static void ClearStack__53 (INT32 off, INT32 size);
static void FullClearStack__55 (INT32 size);
static void TraverseLocals__57 (INT32 offset, OPT_Object obj);

static void ClearStack__53 (INT32 off, INT32 size)
{
	INT32 L;
	if (*GenEnter__52_s->first) {
		OPO_GenTyp1(48, 0, 0, 0, -1, 0, 0, 0);
		*GenEnter__52_s->first = 0;
		*GenEnter__52_s->last = 0;
	}
	while ((*GenEnter__52_s->last - off) - size > 4096) {
		*GenEnter__52_s->last -= 4096;
		OPO_GenMOV(1, 0, 5, -1, 0, *GenEnter__52_s->last, 0);
	}
	*GenEnter__52_s->last = off;
	if (size <= 20) {
		while (size >= 4) {
			size -= 4;
			OPO_GenMOV(1, 0, 5, -1, 0, off + size, 0);
		}
	} else {
		OPO_GenMOV(3, 1, -1, -1, 0, 0, __ASHR(size, 2));
		OPO_GenLEA(3, 5, -1, 0, off);
		L = OPO_pc;
		OPO_GenDEC(3, 1, -1, -1, 0, 0);
		OPO_GenMOV(1, 0, 3, 1, 2, 0, 0);
		OPO_GenJcc(5, L - (OPO_pc + 2));
	}
}

static struct TraverseLocals__57__58 {
	struct TraverseLocals__57__58 *lnk;
} *TraverseLocals__57__58_s;

static void TraverseRecord__59 (INT32 offset, OPT_Struct t);

static void TraverseRecord__59 (INT32 offset, OPT_Struct t)
{
	if (t->BaseTyp != NIL) {
		TraverseRecord__59(offset, t->BaseTyp);
	}
	TraverseLocals__57(offset, t->link);
}

static void TraverseLocals__57 (INT32 offset, OPT_Object obj)
{
	INT32 size, adr, oldoff, oldsize;
	OPT_Struct t;
	struct TraverseLocals__57__58 _s;
	_s.lnk = TraverseLocals__57__58_s;
	TraverseLocals__57__58_s = &_s;
	while (obj != NIL) {
		while ((obj != NIL && !__IN(obj->mode, 0x12, 32))) {
			obj = obj->link;
		}
		if (obj != NIL) {
			if (obj->mode == 4) {
				TraverseLocals__57(offset, obj->link);
			}
			t = obj->typ;
			size = 0;
			if (obj->mode == 1) {
				adr = obj->linkadr;
			} else {
				adr = offset + obj->adr;
			}
			if ((t->form == 13 || t->form == 14) || __STRCMP(obj->name, "@ptr") == 0) {
				size = 4;
			} else if (t->comp == 6) {
				while (t != NIL) {
					TraverseLocals__57(adr, t->link);
					t = t->BaseTyp;
				}
				size = 0;
			} else if (t->comp == 2) {
				while (t->comp == 2) {
					t = t->BaseTyp;
				}
				if (t->form == 13 || t->form == 14) {
					size = obj->typ->size;
				} else if (t->comp == 6) {
					oldoff = *GenEnter__52_s->enoff;
					oldsize = *GenEnter__52_s->ensize;
					*GenEnter__52_s->enoff = 0;
					*GenEnter__52_s->ensize = 0;
					TraverseLocals__57(10000, t->link);
					if (*GenEnter__52_s->ensize != 0) {
						size = obj->typ->size;
					}
					*GenEnter__52_s->enoff = oldoff;
					*GenEnter__52_s->ensize = oldsize;
				}
			}
			size += __MASK(-size, -4);
			if (size == 0) {
			} else if ((offset <= 0 && *GenEnter__52_s->enoff != adr + size)) {
				if (*GenEnter__52_s->ensize != 0) {
					ClearStack__53(*GenEnter__52_s->enoff, *GenEnter__52_s->ensize);
				}
				*GenEnter__52_s->enoff = adr;
				*GenEnter__52_s->ensize = size;
			} else {
				*GenEnter__52_s->ensize += size;
				*GenEnter__52_s->enoff = adr;
			}
			if (obj->mode == 1) {
				obj = obj->link;
			} else {
				obj = NIL;
			}
		}
	}
	TraverseLocals__57__58_s = _s.lnk;
}

static void FullClearStack__55 (INT32 size)
{
	INT32 i;
	__ASSERT(size > 0, 100);
	if (size < 8) {
		OPO_GenTyp1(48, 0, 0, 0, -1, 0, 0, 0);
		while (size > 0) {
			OPO_GenPUSH(0, 0, -1, -1, 0, 0, 0);
			size -= 1;
		}
	} else {
		OPO_GenMOV(3, 1, -1, -1, 0, 0, __ASHR(size, 2));
		OPO_GenTyp1(48, 0, 0, 0, -1, 0, 0, 0);
		i = __MASK(size, -4);
		while (i > 0) {
			OPO_GenPUSH(0, 0, -1, -1, 0, 0, 0);
			i -= 1;
		}
		OPO_GenDEC(3, 1, -1, -1, 0, 0);
		OPO_GenPUSH(0, 0, -1, -1, 0, 0, 0);
		OPO_GenPUSH(0, 0, -1, -1, 0, 0, 0);
		OPO_GenPUSH(0, 0, -1, -1, 0, 0, 0);
		OPO_GenPUSH(0, 0, -1, -1, 0, 0, 0);
		OPO_GenJcc(5, -7);
	}
}

static void OPL_GenEnter (INT32 locSize, OPT_Object locals, INT8 sysflag)
{
	BOOLEAN first;
	INT32 enoff, ensize, last;
	struct GenEnter__52 _s;
	_s.first = &first;
	_s.enoff = &enoff;
	_s.ensize = &ensize;
	_s.last = &last;
	_s.lnk = GenEnter__52_s;
	GenEnter__52_s = &_s;
	__ASSERT(__MASK(locSize, -4) == 0, 0);
	OPO_GenPUSH(0, 5, -1, -1, 0, 0, 0);
	OPO_GenMOV(0, 5, 4, -1, 0, 0, 0);
	if (locSize != 0) {
		if (__IN(5, OPM_codeOptions, 32)) {
			first = 1;
			if (__IN(20, OPM_codeOptions, 32)) {
				FullClearStack__55(__ASHR(locSize, 2));
			} else {
				OPO_GenTyp1(40, 3, 4, -1, -1, 0, 0, locSize);
				enoff = 0;
				ensize = 0;
				TraverseLocals__57(0, locals);
				if (ensize != 0) {
					ClearStack__53(enoff, ensize);
				}
				ClearStack__53(-locSize, 0);
			}
		} else {
			OPO_GenTyp1(40, 3, 4, -1, -1, 0, 0, locSize);
			ClearStack__53(-locSize, 0);
		}
	}
	if (sysflag == 2 || sysflag == 3) {
		OPO_GenPUSH(0, 3, -1, -1, 0, 0, 0);
		OPO_GenPUSH(0, 6, -1, -1, 0, 0, 0);
		OPO_GenPUSH(0, 7, -1, -1, 0, 0, 0);
	}
	GenEnter__52_s = _s.lnk;
}

static void OPL_GenLeave (INT8 sysflag)
{
	if (sysflag == 2 || sysflag == 3) {
		OPO_GenPOP(0, 7, -1, -1, 0, 0);
		OPO_GenPOP(0, 6, -1, -1, 0, 0);
		OPO_GenPOP(0, 3, -1, -1, 0, 0);
	}
	OPO_GenMOV(0, 4, 5, -1, 0, 0, 0);
	OPO_GenPOP(0, 5, -1, -1, 0, 0);
}

static void OPL_PushRegs (void)
{
	INT8 i;
	INT32 disp;
	if (OPL_nofSavedLevel > 32) {
		OPM_err(251);
	} else {
		i = 0;
		while (i < 8) {
			OPL_savedRegs[__X(OPL_nofSavedLevel, 32)].sreg[__X(i, 8)] = (INT16)OPL_sregTab[__X(i, 8)];
			OPL_savedRegs[__X(OPL_nofSavedLevel, 32)].reg[__X(i, 8)] = (INT16)OPL_regTab[__X(i, 8)];
			if ((OPL_regTab[__X(i, 8)] != -1 && !__IN(i, 0x30, 32))) {
				OPO_GenPUSH(0, i, -1, -1, 0, 0, 0);
				OPL_regTab[__X(i, 8)] = -1;
			}
			i += 1;
		}
		disp = 0;
		i = 0;
		while (i < 8) {
			if (OPL_fregTab[__X(i, 8)] != -1) {
				disp += 8;
			}
			i += 1;
		}
		i = 0;
		if (disp > 0) {
			OPO_GenTyp1(40, 3, 4, -1, -1, 0, 0, disp);
			disp = disp - 8;
			while (disp >= 0) {
				if (OPL_fregTab[__X(OPL_ftop, 8)] != -1) {
					OPO_GenFSTP(1, 2, 4, -1, 0, disp);
					OPL_savedRegs[__X(OPL_nofSavedLevel, 32)].freg[__X(i, 8)] = (INT16)OPL_fregTab[__X(OPL_ftop, 8)];
					i += 1;
					OPL_fregTab[__X(OPL_ftop, 8)] = -1;
					disp -= 8;
				} else {
					OPO_GenFop1(7);
				}
				OPL_ftop = __MASK(OPL_ftop + 1, -8);
			}
			OPO_PutByte(155);
		}
		while (i < 8) {
			OPL_savedRegs[__X(OPL_nofSavedLevel, 32)].freg[__X(i, 8)] = -1;
			i += 1;
		}
		OPL_nofSavedLevel += 1;
	}
}

static void OPL_PopRegs (OPL_Instruction *instr, ADDRESS *instr__typ)
{
	INT8 i, j, size, freg;
	INT16 Eax;
	INT32 disp;
	OPL_nofSavedLevel -= 1;
	if ((*instr).hint != -1) {
		size = (INT8)__ASHL(__MASK((*instr).op, -8), 3);
	} else {
		size = -1;
	}
	i = 7;
	while ((i >= 0 && OPL_savedRegs[__X(OPL_nofSavedLevel, 32)].freg[__X(i, 8)] == -1)) {
		i -= 1;
	}
	if (((*instr).hint == 8 && i >= 0)) {
		disp = 8;
		OPO_GenTyp1(40, 3, 4, -1, -1, 0, 0, 8);
		OPO_GenFSTP(1, 2, 4, -1, 0, 0);
		OPO_PutByte(155);
		OPL_fregTab[__X(OPL_ftop, 8)] = -1;
		OPL_ftop = __MASK(OPL_ftop + 1, -8);
	} else {
		disp = 0;
	}
	j = i;
	while (j >= 0) {
		OPL_GetFreg(&freg);
		OPO_GenFLD(2, 2, 4, -1, 0, disp);
		OPL_fregTab[__X(freg, 8)] = OPL_savedRegs[__X(OPL_nofSavedLevel, 32)].freg[__X(j, 8)];
		(OPL_Instr->data)[__X(OPL_fregTab[__X(freg, 8)], OPL_Instr->len[0])].reg = freg;
		disp += 8;
		j -= 1;
	}
	if ((*instr).hint == 8) {
		size = -1;
		if (i >= 0) {
			OPL_GetFreg(&freg);
			OPO_GenFLD(2, 2, 4, -1, 0, 0);
			OPL_fregTab[__X(freg, 8)] = (*instr).dest;
			(*instr).reg = freg;
		} else {
			OPL_fregTab[__X(OPL_ftop, 8)] = (*instr).dest;
			(*instr).reg = OPL_ftop;
		}
	}
	if (disp > 0) {
		OPO_GenTyp1(0, 3, 4, -1, -1, 0, 0, disp);
	}
	if (size == 16) {
		OPL_regTab[0] = -32767;
		OPL_sregTab[0] = (*instr).dest;
		OPL_sregTab[4] = -1;
		(*instr).reg = size;
	} else if (size == 8 || size == 0) {
		OPL_regTab[0] = (*instr).dest;
		(*instr).reg = size;
	} else if (size == 40) {
		OPL_regTab[0] = (*instr).dest;
		OPL_regTab[2] = (*instr).src1;
		(*instr).reg = 0;
		(OPL_Instr->data)[__X((*instr).src1, OPL_Instr->len[0])].reg = 2;
	}
	i = 7;
	while (i >= 0) {
		if (OPL_savedRegs[__X(OPL_nofSavedLevel, 32)].reg[__X(i, 8)] == -1) {
		} else if (__IN(i, 0x30, 32)) {
			OPL_sregTab[__X(i, 8)] = OPL_savedRegs[__X(OPL_nofSavedLevel, 32)].sreg[__X(i, 8)];
			OPL_regTab[__X(i, 8)] = OPL_savedRegs[__X(OPL_nofSavedLevel, 32)].reg[__X(i, 8)];
		} else if (OPL_regTab[__X(i, 8)] == -1) {
			OPL_sregTab[__X(i, 8)] = OPL_savedRegs[__X(OPL_nofSavedLevel, 32)].sreg[__X(i, 8)];
			OPL_regTab[__X(i, 8)] = OPL_savedRegs[__X(OPL_nofSavedLevel, 32)].reg[__X(i, 8)];
			OPO_GenPOP(0, i, -1, -1, 0, 0);
		} else {
			j = 3;
			while ((j > i && OPL_regTab[__X(j, 8)] != -1)) {
				j -= 1;
			}
			if (j == i) {
				j = 3;
				while ((j > i && OPL_regTab[__X(j, 8)] != -32767)) {
					j -= 1;
				}
				if (j == i) {
					OPM_err(215);
					OPL_RegErr = 1;
					return;
				}
			}
			OPL_GetThisReg(j);
			OPO_GenPOP(0, j, -1, -1, 0, 0);
			OPL_sregTab[__X(j, 8)] = OPL_savedRegs[__X(OPL_nofSavedLevel, 32)].sreg[__X(i, 8)];
			OPL_regTab[__X(j, 8)] = OPL_savedRegs[__X(OPL_nofSavedLevel, 32)].reg[__X(i, 8)];
			if (OPL_regTab[__X(j, 8)] == -32767) {
				if (OPL_sregTab[__X(j, 8)] >= 0) {
					(OPL_Instr->data)[__X(OPL_sregTab[__X(j, 8)], OPL_Instr->len[0])].reg = j + 16;
				}
				if (OPL_sregTab[__X(j + 4, 8)] >= 0) {
					(OPL_Instr->data)[__X(OPL_sregTab[__X(j + 4, 8)], OPL_Instr->len[0])].reg = (j + 4) + 16;
				}
			} else if (__MASK((OPL_Instr->data)[__X(OPL_regTab[__X(j, 8)], OPL_Instr->len[0])].op, -8) == 1) {
				(OPL_Instr->data)[__X(OPL_regTab[__X(j, 8)], OPL_Instr->len[0])].reg = j + 8;
			} else {
				(OPL_Instr->data)[__X(OPL_regTab[__X(j, 8)], OPL_Instr->len[0])].reg = j;
			}
		}
		i -= 1;
	}
}

static void OPL_FixupJcc (INT32 label)
{
	INT32 pos, nextLabel;
	while (label != -1) {
		if ((OPL_Instr->data)[__X(label, OPL_Instr->len[0])].op == 1888) {
			pos = (OPL_Instr->data)[__X(label, OPL_Instr->len[0])].pc + 1;
		} else {
			pos = (OPL_Instr->data)[__X(label, OPL_Instr->len[0])].pc + 2;
		}
		OPO_GetDWord(pos, &nextLabel);
		OPO_PutDWordAt(pos, OPO_pc - (pos + 4));
		label = (-2 - nextLabel) - 65536;
	}
}

static void OPL_FixupCaseTab (OPL_Instruction *instr, ADDRESS *instr__typ)
{
	INT32 elseLabel, from, to, val, caseFixup;
	caseFixup = OPL_link[0].offset;
	elseLabel = (OPL_Instr->data)[__X((*instr).src2, OPL_Instr->len[0])].pc;
	from = (*instr).src1;
	to = ((*instr).src1 + (*instr).inx) - 4;
	while (from <= to) {
		OPO_GetConsDWord(from, &val);
		if (val == -1) {
			val = elseLabel;
		} else {
			val = (OPL_Instr->data)[__X(val, OPL_Instr->len[0])].pc;
		}
		if (from == to) {
			if (caseFixup >= 32768) {
				val = __ASHL(caseFixup - 65536, 16) + val;
			} else {
				val = __ASHL(caseFixup, 16) + val;
			}
		} else {
			if (from + 4 >= 32768) {
				val = __ASHL((from + 4) - 65536, 16) + val;
			} else {
				val = __ASHL(from + 4, 16) + val;
			}
		}
		OPO_PutConsDWord(from, val);
		from = from + 4;
	}
	OPL_link[0].offset = (INT16)(*instr).src1;
}

static void OPL_EncodeFixup (INT32 i)
{
	INT32 L, L1;
	OPT_Node node;
	node = (OPL_Instr->data)[__X(i, OPL_Instr->len[0])].node;
	node->left->obj->linkadr = (-2 - (OPL_Instr->data)[__X(i, OPL_Instr->len[0])].pc) - 65536;
	L = i;
	while (L > -1) {
		OPO_GetDWord((OPL_Instr->data)[__X(L, OPL_Instr->len[0])].pc + 1, &L1);
		if ((L1 > -65536 && -2 - L1 > -1)) {
			L1 = -2 - L1;
			OPO_PutDWordAt((OPL_Instr->data)[__X(L, OPL_Instr->len[0])].pc + 1, (-2 - (OPL_Instr->data)[__X(L1, OPL_Instr->len[0])].pc) - 65536);
		}
		L = L1;
	}
}

static void OPL_GenAsm (OPL_Instruction instr)
{
	OPT_Node n, code, fix;
	INT32 pc;
	pc = OPO_pc;
	n = instr.node;
	code = n->left;
	while (code != NIL) {
		OPO_InlineCode((void*)*code->conval->ext, 256, 0);
		code = code->link;
	}
	fix = n->right;
	while (fix != NIL) {
		if ((fix->obj->mode == 1 && fix->obj->mnolev <= 0)) {
			OPO_PutDWordAt(pc + fix->conval->intval, fix->obj->linkadr);
			OPL_AbsAccess(fix, pc + fix->conval->intval);
		} else if ((fix->obj->linkadr <= 127 && fix->obj->linkadr >= -128)) {
			OPO_PutByteAt(pc + fix->conval->intval, (INT8)((INT16)fix->obj->linkadr));
		} else {
			OPM_Mark(600, (INT16)fix->conval->intval2);
		}
		fix = fix->link;
	}
}

static struct GenCode__48 {
	INT32 *i;
	struct GenCode__48 *lnk;
} *GenCode__48_s;

static void MarkPos__49 (void);

static void MarkPos__49 (void)
{
	INT32 j;
	if (OPL_mapSize < 0) {
		(OPL_map->data)[__X(OPL_mapSize, OPL_map->len[0])].pos = (OPL_Instr->data)[__X(*GenCode__48_s->i, OPL_Instr->len[0])].src1;
		(OPL_map->data)[__X(OPL_mapSize, OPL_map->len[0])].pc = OPO_pc;
		j = OPL_mapSize - 1;
		while ((j >= 0 && (OPL_map->data)[__X(j, OPL_map->len[0])].pos < 0)) {
			(OPL_map->data)[__X(j, OPL_map->len[0])].pos = (OPL_map->data)[__X(OPL_mapSize, OPL_map->len[0])].pos;
			j -= 1;
		}
		OPL_mapSize += 1;
	} else {
		(OPL_map->data)[__X(OPL_mapSize - 1, OPL_map->len[0])].pos = -1;
		(OPL_map->data)[__X(OPL_mapSize - 1, OPL_map->len[0])].pc = -1;
	}
}

void OPL_GenCode (INT16 pSize)
{
	OPT_Object obj, list;
	INT32 i, k;
	INT8 op, reg, ret, sysflag;
	OPT_Node node;
	struct GenCode__48 _s;
	_s.i = &i;
	_s.lnk = GenCode__48_s;
	GenCode__48_s = &_s;
	OPL_ftop = 7;
	OPL_FreeRegDisp = 0;
	i = 0;
	while (i < 10) {
		OPL_trapFixupTab[__X(i, 10)] = -1;
		i += 1;
	}
	i = 0;
	while (i < 8) {
		OPL_regTab[__X(i, 8)] = -1;
		OPL_sregTab[__X(i, 8)] = -1;
		OPL_fregTab[__X(i, 8)] = -1;
		i += 1;
	}
	OPL_regTab[4] = (-32767-1);
	OPL_regTab[5] = (-32767-1);
	OPL_RegErr = 0;
	i = 0;
	while ((((!OPO_CodeErr && !OPL_RegErr)) && i < pSize)) {
		node = (OPL_Instr->data)[__X(i, OPL_Instr->len[0])].node;
		OPL_FixupJcc((OPL_Instr->data)[__X(i, OPL_Instr->len[0])].pc);
		(OPL_Instr->data)[__X(i, OPL_Instr->len[0])].pc = OPO_pc;
		op = (INT8)__ASHR((OPL_Instr->data)[__X(i, OPL_Instr->len[0])].op, 5);
		if (op > 0) {
			switch (op) {
				case 98: 
					OPM_errpos = (OPL_Instr->data)[__X(i, OPL_Instr->len[0])].src1;
					if (OPL_map != NIL) {
						MarkPos__49();
					}
					break;
				case 1: case 12: case 2: case 3: case 4: 
				case 5: case 6: case 7: case 9: 
					OPL_Load(&(OPL_Instr->data)[__X(i, OPL_Instr->len[0])], OPL_Instruction__typ);
					break;
				case 10: case 11: 
					OPL_LoadProc(&(OPL_Instr->data)[__X(i, OPL_Instr->len[0])], OPL_Instruction__typ);
					break;
				case 13: case 8: 
					OPL_Store(&(OPL_Instr->data)[__X(i, OPL_Instr->len[0])], OPL_Instruction__typ);
					break;
				case 14: 
					OPL_GenPush(&(OPL_Instr->data)[__X(i, OPL_Instr->len[0])], OPL_Instruction__typ);
					break;
				case 15: 
					OPL_GenPop(&(OPL_Instr->data)[__X(i, OPL_Instr->len[0])], OPL_Instruction__typ);
					break;
				case 16: case 17: case 21: case 22: case 23: 
				case 24: case 25: case 26: case 27: case 28: 
				case 29: 
					OPL_Gen3(&(OPL_Instr->data)[__X(i, OPL_Instr->len[0])], OPL_Instruction__typ);
					break;
				case 19: case 20: 
					OPL_GenDivMod(&(OPL_Instr->data)[__X(i, OPL_Instr->len[0])], OPL_Instruction__typ);
					break;
				case 18: 
					OPL_GenMul(&(OPL_Instr->data)[__X(i, OPL_Instr->len[0])], OPL_Instruction__typ);
					break;
				case 30: case 32: 
					OPL_Gen2(&(OPL_Instr->data)[__X(i, OPL_Instr->len[0])], OPL_Instruction__typ);
					break;
				case 31: 
					OPL_GenAbs(&(OPL_Instr->data)[__X(i, OPL_Instr->len[0])], OPL_Instruction__typ);
					break;
				case 33: case 34: case 107: 
					OPL_Flags(&(OPL_Instr->data)[__X(i, OPL_Instr->len[0])], OPL_Instruction__typ);
					break;
				case 35: case 36: case 37: case 38: case 39: 
				case 40: case 41: case 42: case 43: case 44: 
				case 45: case 46: 
					OPL_Setcc(&(OPL_Instr->data)[__X(i, OPL_Instr->len[0])], OPL_Instruction__typ);
					break;
				case 47: case 48: case 49: case 50: case 51: 
				case 52: case 53: case 54: case 55: case 56: 
				case 57: case 58: case 59: case 60: 
					OPL_Gen1(&(OPL_Instr->data)[__X(i, OPL_Instr->len[0])], OPL_Instruction__typ, i);
					break;
				case 61: case 62: case 63: case 91: case 90: 
				case 92: 
					OPL_GenTrapCC(&(OPL_Instr->data)[__X(i, OPL_Instr->len[0])], OPL_Instruction__typ);
					break;
				case 64: 
					OPL_GenTrap((OPL_Instr->data)[__X(i, OPL_Instr->len[0])].src2);
					break;
				case 65: 
					node = (OPL_Instr->data)[__X(i, OPL_Instr->len[0])].node;
					obj = node->left->obj;
					if (obj->mode == 9) {
						__HALT(99);
					} else if ((OPL_Instr->data)[__X(i, OPL_Instr->len[0])].src2 >= 0) {
						OPO_GenCALL(3, -1, -1, -1, 0, (OPL_Instr->data)[__X(i, OPL_Instr->len[0])].src2 - (OPO_pc + 5));
					} else {
						OPO_GenCALL(3, -1, -1, -1, 0, (OPL_Instr->data)[__X(i, OPL_Instr->len[0])].src2);
						if (-2 - node->left->obj->linkadr == i) {
							OPL_EncodeFixup(i);
						}
					}
					break;
				case 67: 
					OPO_GenCALL(3, -1, -1, -1, 0, 0);
					OPL_AddLink(__ASHR((OPL_Instr->data)[__X(i, OPL_Instr->len[0])].src2, 16), (OPL_Instr->data)[__X(i, OPL_Instr->len[0])].pc + 1);
					break;
				case 66: 
					OPL_FindReg((OPL_Instr->data)[__X(i, OPL_Instr->len[0])].src2, &reg);
					OPO_GenCALL(0, reg, -1, -1, 0, 0);
					OPL_DecReg(reg);
					break;
				case 69: 
					if (OPL_map != NIL) {
						MarkPos__49();
					}
					if (node != NIL) {
						list = node->obj->scope->scope;
						sysflag = node->obj->sysflag;
					} else {
						list = NIL;
						sysflag = 0;
					}
					OPL_GenEnter((OPL_Instr->data)[__X(i, OPL_Instr->len[0])].src2, list, sysflag);
					break;
				case 70: 
					OPL_GenLeave(sysflag);
					break;
				case 68: 
					k = 0;
					ret = -1;
					while (k <= 7) {
						if ((!__IN(k, 0x30, 32) && OPL_regTab[__X(k, 8)] != -1)) {
							if (ret == -1) {
								ret = (INT8)((INT16)k);
							} else if ((ret == 0 && k == 2)) {
								OPL_FreeReg(2);
							} else {
								OPM_err(200);
							}
						}
						k += 1;
					}
					if (ret != -1) {
						if ((OPL_regTab[__X(ret, 8)] == -32767 && OPL_sregTab[__X(ret + 4, 8)] != -1)) {
							OPO_GenMOV(0, 16, 20 + ret, -1, 0, 0, 0);
						} else if (ret != 0) {
							OPO_GenMOV(0, 0, ret, -1, 0, 0, 0);
						}
						if (OPL_regTab[__X(ret, 8)] == -32767) {
							OPL_FreeReg(ret + 16);
							OPL_FreeReg((ret + 16) + 4);
						} else if (OPL_regTab[__X(ret, 8)] != -1) {
							OPL_FreeReg(ret);
						}
					}
					if (OPL_fregTab[__X(OPL_ftop, 8)] != -1) {
						OPL_FreeFreg(OPL_ftop);
					}
					k = 0;
					while (k < 8) {
						if (OPL_fregTab[__X(k, 8)] != -1) {
							OPM_err(-1001);
						}
						k += 1;
					}
					if (OPL_FreeRegDisp != 0) {
						OPM_LogWLn();
						OPM_LogWStr((CHAR*)"Error FreeReg", 14);
						OPM_LogWLn();
					}
					if (sysflag == 3) {
						OPO_GenRET(0);
					} else {
						OPO_GenRET((OPL_Instr->data)[__X(i, OPL_Instr->len[0])].src2);
					}
					break;
				case 72: 
					OPL_GenRepMovs(&(OPL_Instr->data)[__X(i, OPL_Instr->len[0])], OPL_Instruction__typ);
					break;
				case 73: 
					OPL_GenCmpString(&(OPL_Instr->data)[__X(i, OPL_Instr->len[0])], OPL_Instruction__typ);
					break;
				case 71: 
					OPO_PutByte(252);
					break;
				case 106: 
					OPO_PutByte(253);
					break;
				case 74: 
					OPL_PushRegs();
					break;
				case 75: 
					OPL_PopRegs(&(OPL_Instr->data)[__X(i, OPL_Instr->len[0])], OPL_Instruction__typ);
					break;
				case 76: 
					OPL_FixupCaseTab(&(OPL_Instr->data)[__X(i, OPL_Instr->len[0])], OPL_Instruction__typ);
					break;
				case 77: 
					OPL_GenPhi(&(OPL_Instr->data)[__X(i, OPL_Instr->len[0])], OPL_Instruction__typ);
					break;
				case 93: 
					OPL_GenShort(&(OPL_Instr->data)[__X(i, OPL_Instr->len[0])], OPL_Instruction__typ);
					break;
				case 97: 
					OPL_GenEntier(&(OPL_Instr->data)[__X(i, OPL_Instr->len[0])], OPL_Instruction__typ);
					break;
				case 78: 
					break;
				case 79: case 82: 
					OPL_Fload(&(OPL_Instr->data)[__X(i, OPL_Instr->len[0])], OPL_Instruction__typ);
					break;
				case 80: case 81: 
					OPL_Fstore(&(OPL_Instr->data)[__X(i, OPL_Instr->len[0])], OPL_Instruction__typ);
					break;
				case 87: case 88: 
					OPL_FloatGen1(&(OPL_Instr->data)[__X(i, OPL_Instr->len[0])], OPL_Instruction__typ);
					break;
				case 83: case 84: case 85: case 86: 
					OPL_FloatGen3(&(OPL_Instr->data)[__X(i, OPL_Instr->len[0])], OPL_Instruction__typ);
					break;
				case 89: 
					OPL_FloatCmp(&(OPL_Instr->data)[__X(i, OPL_Instr->len[0])], OPL_Instruction__typ);
					break;
				case 99: 
					OPO_PutByte(250);
					break;
				case 100: 
					OPO_PutByte(251);
					break;
				case 101: case 102: 
					OPL_GenPortIO(&(OPL_Instr->data)[__X(i, OPL_Instr->len[0])], OPL_Instruction__typ);
					break;
				case 103: 
					OPL_GenAsm((OPL_Instr->data)[__X(i, OPL_Instr->len[0])]);
					break;
				case 104: 
					OPL_ClearSDynArr(&(OPL_Instr->data)[__X(i, OPL_Instr->len[0])], OPL_Instruction__typ);
					break;
				default: 
					__HALT(41);
					break;
			}
		}
		i += 1;
	}
	OPL_FixupAndGenTrap();
	GenCode__48_s = _s.lnk;
}

void OPL_FixupLocalProcCall (OPT_Object proc)
{
	INT32 L, L1, entryNr;
	if ((proc->linkadr < 0 && !__IN(proc->mode, 0x2020, 32))) {
		L = (-2 - proc->linkadr) - 65536;
		while (L > -1) {
			OPO_GetDWord(L + 1, &L1);
			OPO_PutDWordAt(L + 1, OPO_pc - (L + 5));
			L = (-2 - L1) - 65536;
		}
	}
	proc->linkadr = OPO_pc;
	if (__IN(proc->mode, 0x20a0, 32)) {
		if (__IN(proc->mode, 0x2020, 32)) {
			entryNr = __MASK(proc->adr, -65536);
		} else {
			entryNr = proc->adr;
		}
		if (OPO_pc > 32767) {
			(OPL_entry->data)[__X(entryNr, OPL_entry->len[0])] = (INT16)(OPO_pc - 65536);
		} else {
			(OPL_entry->data)[__X(entryNr, OPL_entry->len[0])] = (INT16)OPO_pc;
		}
	}
}

void OPL_NewVarCons (INT16 mod, INT16 entry, INT32 *index)
{
	INT32 i;
	OPL_VarConsTable var;
	if (OPL_nofVarCons >= 0) {
		var = __NEWARR(NIL, 8, 2, 1, 1, 2);
		i = 0;
		while (i <= 0) {
			(var->data)[__X(i, var->len[0])] = (OPL_varConsLink->data)[__X(i, OPL_varConsLink->len[0])];
			i += 1;
		}
		OPL_varConsLink = var;
	}
	(OPL_varConsLink->data)[__X(OPL_nofVarCons, OPL_varConsLink->len[0])].mod = mod;
	(OPL_varConsLink->data)[__X(OPL_nofVarCons, OPL_varConsLink->len[0])].entry = entry;
	(OPL_varConsLink->data)[__X(OPL_nofVarCons, OPL_varConsLink->len[0])].noflinks = 0;
	(OPL_varConsLink->data)[__X(OPL_nofVarCons, OPL_varConsLink->len[0])].index = -1;
	*index = OPL_nofVarCons;
	OPL_nofVarCons += 1;
}

static void OPL_VarConsLink (INT32 index, INT32 offset)
{
	INT32 i;
	OPL_VarConsLinkTable var;
	if (OPL_nofVarConsLinks >= 1) {
		var = __NEWARR(NIL, 4, 2, 1, 1, 2);
		i = 0;
		while (i <= 0) {
			(var->data)[__X(i, var->len[0])] = (OPL_varConsTab->data)[__X(i, OPL_varConsTab->len[0])];
			i += 1;
		}
		OPL_varConsTab = var;
	}
	(OPL_varConsLink->data)[__X(index, OPL_varConsLink->len[0])].noflinks += 1;
	if ((OPL_varConsLink->data)[__X(index, OPL_varConsLink->len[0])].noflinks == 1) {
		(OPL_varConsLink->data)[__X(index, OPL_varConsLink->len[0])].index = OPL_nofVarConsLinks;
	} else {
		index = (OPL_varConsLink->data)[__X(index, OPL_varConsLink->len[0])].index;
		while ((OPL_varConsTab->data)[__X(index, OPL_varConsTab->len[0])].next != -1) {
			index = (OPL_varConsTab->data)[__X(index, OPL_varConsTab->len[0])].next;
		}
		(OPL_varConsTab->data)[__X(index, OPL_varConsTab->len[0])].next = OPL_nofVarConsLinks;
	}
	(OPL_varConsTab->data)[__X(OPL_nofVarConsLinks, OPL_varConsTab->len[0])].offset = (INT16)offset;
	(OPL_varConsTab->data)[__X(OPL_nofVarConsLinks, OPL_varConsTab->len[0])].next = -1;
	OPL_nofVarConsLinks += 1;
}

static void OPL_AbsAccess (OPT_Node node, INT32 offset)
{
	if (OPM_noerr) {
		if ((((((((node != NIL && node->link == NIL)) && node->obj == NIL)) && node->left == NIL)) && node->right == NIL)) {
			OPL_VarConsLink(0, offset);
		} else {
			while ((node != NIL && node->left != NIL)) {
				node = node->left;
			}
			if (node == NIL || node->obj->mnolev == 0) {
				OPL_VarConsLink(0, offset);
			} else {
				OPL_VarConsLink(__ASHR(node->obj->adr, 16), offset);
			}
		}
	}
}

void OPL_NewEntry (INT32 *entryNr)
{
	OPL_EntryTable table;
	INT32 i;
	if (OPL_nofEntries >= 1) {
		table = __NEWARR(NIL, 2, 2, 1, 1, 2);
		i = 0;
		while (i <= 0) {
			(table->data)[__X(i, table->len[0])] = (OPL_entry->data)[__X(i, OPL_entry->len[0])];
			i += 1;
		}
		OPL_entry = table;
	}
	(OPL_entry->data)[__X(OPL_nofEntries, OPL_entry->len[0])] = -1;
	*entryNr = OPL_nofEntries;
	OPL_nofEntries += 1;
}

void OPL_NewLink (INT32 mod, INT32 entry, INT32 *index)
{
	if (OPL_nofLinks >= 512) {
		if (!OPL_LinkErr) {
			OPM_err(231);
			OPL_LinkErr = 1;
			*index = 0;
		}
	} else {
		OPL_link[__X(OPL_nofLinks, 512)].mod = (INT16)mod;
		OPL_link[__X(OPL_nofLinks, 512)].entry = (INT16)entry;
		OPL_link[__X(OPL_nofLinks, 512)].offset = -1;
		*index = OPL_nofLinks;
		OPL_nofLinks += 1;
	}
}

static void OPL_AddLink (INT32 index, INT32 offset)
{
	INT32 old;
	if (!OPL_LinkErr) {
		OPO_GetDWord(offset, &old);
		if (OPL_link[__X(index, 512)].offset == -1) {
			OPO_PutDWordAt(offset, -65536 + __MASK(old, -65536));
		} else {
			if (OPL_link[__X(index, 512)].offset >= 32768) {
				OPO_PutDWordAt(offset, __ASHL(OPL_link[__X(index, 512)].offset - 65536, 16) + __MASK(old, -65536));
			} else {
				OPO_PutDWordAt(offset, __ASHL(OPL_link[__X(index, 512)].offset, 16) + __MASK(old, -65536));
			}
		}
		OPL_link[__X(index, 512)].offset = (INT16)offset;
	}
}

void OPL_AllocConst (SYSTEM_BYTE *s, ADDRESS s__len, INT32 len, INT32 align, INT32 *adr)
{
	INT32 fill;
	OPO_ConstArray table;
	if (!OPL_ConstErr) {
		*adr = OPO_csize;
		OPO_csize = OPO_csize + len;
		fill = (int)__MOD(-len, align);
		if (OPO_csize + fill > 65536) {
			OPM_err(230);
			OPL_ConstErr = 1;
		} else {
			if (OPO_csize + fill >= 1) {
				table = __NEWARR(NIL, 1, 1, 1, 1, 2);
				__MOVE((ADDRESS)&(OPO_constant->data)[0], (ADDRESS)&(table->data)[0], *adr);
				OPO_constant = table;
			}
			while (fill > 0) {
				(OPO_constant->data)[__X(OPO_csize, OPO_constant->len[0])] = 0x00;
				OPO_csize += 1;
				fill -= 1;
			}
			__MOVE((ADDRESS)&s[0], (ADDRESS)&(OPO_constant->data)[__X(*adr, OPO_constant->len[0])], len);
		}
	} else {
		*adr = 0;
	}
}

void OPL_AllocCaseTab (INT32 low, INT32 high, INT32 *tab)
{
	INT32 len, i;
	OPO_ConstArray table;
	if (!OPL_ConstErr) {
		len = __ASHL((high - low) + 1, 2);
		*tab = OPO_csize;
		OPO_csize = OPO_csize + len;
		if (OPO_csize > 65536) {
			OPM_err(230);
			OPL_ConstErr = 1;
		} else {
			if (OPO_csize >= 1) {
				table = __NEWARR(NIL, 1, 1, 1, 1, 2);
				__MOVE((ADDRESS)&(OPO_constant->data)[0], (ADDRESS)&(table->data)[0], *tab);
				OPO_constant = table;
			}
			i = *tab;
			while (i < OPO_csize) {
				(OPO_constant->data)[__X(i, OPO_constant->len[0])] = 0xff;
				i += 1;
			}
		}
	} else {
		*tab = 0;
	}
}

void OPL_AllocTypDesc (OPT_Struct typ)
{
	INT32 nil;
	OPL_RecTable table;
	INT32 i;
	if (typ->comp == 6) {
		nil = 0;
		OPL_AllocConst((void*)&nil, 4, 4, 4, &typ->tdadr);
		if (typ->extlev > 15) {
			OPM_err(233);
		} else if (typ->mno == 0) {
			if (OPL_nofrecs >= 1) {
				table = __NEWARR(POINTER__typ, 4, 4, 1, 1, 2);
				i = 0;
				while (i <= 0) {
					(table->data)[__X(i, table->len[0])] = (OPL_recTab->data)[__X(i, OPL_recTab->len[0])];
					i += 1;
				}
				OPL_recTab = table;
			}
			(OPL_recTab->data)[__X(OPL_nofrecs, OPL_recTab->len[0])] = typ;
			OPL_nofrecs += 1;
		}
	}
}

void OPL_CaseJump (INT32 Label, INT32 tab, INT32 from, INT32 to)
{
	if (!OPL_ConstErr) {
		from = tab + __ASHL(from, 2);
		to = tab + __ASHL(to, 2);
		while (from <= to) {
			OPO_PutConsDWord(from, Label);
			from = from + 4;
		}
	}
}

void OPL_OutRefPoint (OPT_Object proc)
{
	OPT_Object obj;
	INT32 n;
	if (proc == NIL) {
		OPM_RefW(0x8c);
		OPM_RefW(0xf8);
		OPM_RefWNum(0);
	} else {
		OPM_RefW(0xf9);
		OPM_RefWNum(proc->linkadr);
		obj = proc->link;
		n = 0;
		while (obj != NIL) {
			n += 1;
			obj = obj->link;
		}
		OPM_RefWNum(n);
		n = proc->typ->form;
		if (__IN(n, 0x1801, 32)) {
			n = 0;
		} else if (n == 15) {
			n = 16 + proc->typ->comp;
		}
		OPM_RefW((CHAR)n);
		OPM_RefW((CHAR)proc->mnolev);
		if (__IN(3, proc->conval->setval, 32)) {
			OPM_RefW(0x01);
		} else {
			OPM_RefW(0x00);
		}
	}
}

void OPL_OutRefName (CHAR *name, ADDRESS name__len)
{
	CHAR ch;
	INT16 i;
	__DUP(name, name__len, CHAR);
	i = 0;
	do {
		ch = name[__X(i, name__len)];
		OPM_RefW(ch);
		i += 1;
	} while (!(ch == 0x00));
	__DEL(name);
}

void OPL_OutRefs (OPT_Object obj)
{
	INT16 f;
	if (obj != NIL) {
		OPL_OutRefs(obj->left);
		if (__IN(obj->mode, 0x06, 32)) {
			f = obj->typ->form;
			if ((__IN(f, 0x0163fe, 32) || obj->typ->comp == 6) || (__IN(obj->typ->comp, 0x24, 32) && __IN(obj->typ->BaseTyp->form, 0x63fe, 32))) {
				if ((obj->mode == 1 && obj->typ->comp != 5)) {
					OPM_RefW(0x01);
				} else {
					OPM_RefW(0x03);
				}
				if (obj->typ->comp == 2) {
					OPM_RefW((CHAR)(128 + (INT16)obj->typ->BaseTyp->form));
					OPM_RefWNum(obj->typ->n);
				} else if (obj->typ->comp == 5) {
					OPM_RefW((CHAR)(128 + (INT16)obj->typ->BaseTyp->form));
					OPM_RefWNum(0);
				} else if (obj->typ->comp == 6) {
					OPM_RefW(0x16);
					OPM_RefWNum(obj->typ->tdadr);
				} else if ((((f == 13 && obj->typ->BaseTyp != NIL)) && obj->typ->BaseTyp->comp == 6)) {
					OPM_RefW(0x1d);
					OPM_RefWNum(obj->typ->BaseTyp->tdadr);
				} else {
					OPM_RefW((CHAR)f);
				}
				OPM_RefWNum(obj->linkadr);
				OPL_OutRefName(obj->name, 32);
			}
		}
		OPL_OutRefs(obj->right);
	}
}

static INT32 OPL_LSW (INT32 x)
{
	return (INT32)(((UINT32)x & (UINT32)65535));
}

static struct Export__21 {
	struct Export__21 *lnk;
} *Export__21_s;

static void ExportMeth__22 (OPT_Object fld, OPT_Struct basetyp, INT16 *noFld);
static void ExportRecord__24 (OPT_Struct typ);

static void ExportMeth__22 (OPT_Object fld, OPT_Struct basetyp, INT16 *noFld)
{
	if (fld != NIL) {
		ExportMeth__22(fld->left, basetyp, &*noFld);
		if ((fld->mode == 13 && fld->vis != 0)) {
			*noFld += 1;
			OPM_ObjWNum(fld->fp);
		}
		ExportMeth__22(fld->right, basetyp, &*noFld);
	}
}

static void ExportRecord__24 (OPT_Struct typ)
{
	OPT_Object fld;
	INT32 pos;
	INT16 nofld;
	if (typ->mno == 0) {
		OPM_ObjW(0x01);
		if (typ->oref != 0) {
			OPM_ObjWNum(-typ->oref);
		} else {
			OPL_nofStr += 1;
			typ->oref = OPL_nofStr;
			OPM_ObjWNum(typ->tdadr);
			OPT_FPrintTyp(typ);
			pos = OPM_ObjAllocInt();
			nofld = 2;
			if ((typ->BaseTyp != NIL && (INT16)typ->mno == OPT_modNo)) {
				ExportRecord__24(typ->BaseTyp);
			}
			OPM_ObjWNum(typ->pbfp);
			OPM_ObjWNum(typ->pvfp);
			ExportMeth__22(typ->link, typ->BaseTyp, &nofld);
			fld = typ->link;
			while ((fld != NIL && fld->mode != 13)) {
				if (fld->vis != 0) {
					nofld += 1;
					OPM_ObjWNum(fld->fp);
					typ = fld->typ;
					while ((typ != NIL && ((typ->form == 15 && typ->comp != 6) || typ->form == 13))) {
						typ = typ->BaseTyp;
					}
					if ((((typ != NIL && typ->form == 15)) && typ->comp == 6)) {
						ExportRecord__24(typ);
					}
				}
				fld = fld->link;
			}
			OPM_ObjW(0x00);
			OPM_ObjFillInt(pos, nofld);
		}
	}
}

static void OPL_Export (OPT_Object obj, INT16 *nofExp)
{
	OPT_Struct typ;
	INT32 i;
	OPL_ExpTable tmp;
	struct Export__21 _s;
	_s.lnk = Export__21_s;
	Export__21_s = &_s;
	if (obj != NIL) {
		if (obj->prio == 127) {
			OPL_Export(obj->link2, &*nofExp);
			OPL_Export(obj->left, &*nofExp);
			OPL_Export(obj->right, &*nofExp);
		} else {
			OPL_Export(obj->left, &*nofExp);
			if (obj->vis != 0) {
				OPT_FPrintObj(obj);
				OPM_ObjWNum(obj->fp);
				i = 0;
				while (i < OPL_exppos) {
					if (obj->fp == (OPL_explist->data)[__X(i, OPL_explist->len[0])]) {
						OPM_Mark(280, obj->txtpos);
					}
					i += 1;
				}
				if (OPL_exppos == 1) {
					tmp = __NEWARR(NIL, 4, 4, 1, 1, 33);
					__MOVE((ADDRESS)&(OPL_explist->data)[0], (ADDRESS)&(tmp->data)[0], 4);
					OPL_explist = tmp;
				}
				(OPL_explist->data)[__X(OPL_exppos, OPL_explist->len[0])] = obj->fp;
				OPL_exppos += 1;
				if (obj->mode == 1) {
					OPM_ObjWNum(obj->linkadr);
				} else if (obj->mode == 7) {
					OPM_ObjWNum(OPL_LSW((OPL_entry->data)[__X(obj->adr, OPL_entry->len[0])]));
				} else {
					OPM_ObjW(0x00);
				}
				*nofExp += 1;
				if (obj->mode == 5 || obj->mode == 1) {
					typ = obj->typ;
					while ((typ != NIL && ((typ->form == 15 && typ->comp != 6) || typ->form == 13))) {
						typ = typ->BaseTyp;
					}
					if ((((typ != NIL && typ->form == 15)) && typ->comp == 6)) {
						ExportRecord__24(typ);
					}
				}
			}
			OPL_Export(obj->right, &*nofExp);
		}
	}
	Export__21_s = _s.lnk;
}

static struct Use__112 {
	struct Use__112 *lnk;
} *Use__112_s;

static void UseRecord__113 (OPT_Struct typ);

static void UseRecord__113 (OPT_Struct typ)
{
	CHAR name[32];
	if ((typ->oref == 0 && (INT16)typ->mno == OPT_modNo)) {
		OPM_ObjW(0x01);
		if (typ->tdadr == -1 || typ->tdadr == -2) {
			OPM_ObjWNum(0);
		} else {
			OPM_ObjWNum(-typ->tdadr);
		}
		OPT_FPrintTyp(typ);
		typ->oref = -1;
		if (typ->pvused) {
			__MOVE("@", name, 2);
			OPM_ObjWNum(typ->pvfp);
			OPM_ObjWString((void*)name, 32);
		} else if (typ->pbused) {
			__MOVE("@", name, 2);
			OPM_ObjWNum(typ->pbfp);
			OPM_ObjWString((void*)name, 32);
		}
		OPM_ObjW(0x00);
	}
}

static void OPL_Use (OPT_Object obj)
{
	OPT_Struct typ;
	BOOLEAN alias;
	struct Use__112 _s;
	_s.lnk = Use__112_s;
	Use__112_s = &_s;
	if (obj != NIL) {
		if (obj->prio == 127) {
			OPL_Use(obj->link2);
			OPL_Use(obj->left);
			OPL_Use(obj->right);
		} else {
			OPL_Use(obj->left);
			alias = 0;
			if ((((((((((!obj->used && obj->mode == 5)) && obj->vis != 0)) && obj->typ->strobj != obj)) && obj->typ->strobj->vis == 0)) && obj->typ->strobj->used)) {
				alias = 1;
			}
			if (alias || (((((obj->used && obj->vis != 0)) && (obj->mode != 7 || (__ASHR(obj->adr, 16) != 0 && OPL_link[__X(__ASHR(obj->adr, 16), 512)].offset != -1)))) && (obj->mode != 1 || obj->adr != 0))) {
				OPT_FPrintObj(obj);
				OPM_ObjWNum(obj->fp);
				OPM_ObjWString((void*)obj->name, 32);
				if (obj->mode == 1) {
					OPM_ObjWNum(__ASHR(obj->adr, 16));
				} else if (obj->mode == 7) {
					OPM_ObjWNum((INT64)OPL_LSW(OPL_link[__X(__ASHR(obj->adr, 16), 512)].offset) + 2147483648LL);
				} else {
					OPM_ObjW(0x00);
				}
				if (obj->mode == 5 || obj->mode == 1) {
					typ = obj->typ;
					while ((typ != NIL && ((typ->form == 15 && typ->comp != 6) || typ->form == 13))) {
						typ = typ->BaseTyp;
					}
					if ((((typ != NIL && typ->form == 15)) && typ->comp == 6)) {
						UseRecord__113(typ);
						if (typ->strobj->fp == 0) {
							typ->strobj->fp = obj->fp;
						}
					}
				}
			}
			OPL_Use(obj->right);
		}
	}
	Use__112_s = _s.lnk;
}

static struct OutCode__92 {
	INT16 *nofcmds, *nofnewmth;
	OPT_Object (*commandTab)[128];
	OPT_Object (*newMthTab)[128];
	struct OutCode__92 *lnk;
} *OutCode__92_s;

static void FindNewMths__93 (OPT_Object obj);
static void FindPtrs__95 (OPT_Struct typ, INT32 adr);
static void WriteName__99 (CHAR *name, ADDRESS name__len);
static void traverse__101 (OPT_Object obj);

static void WriteName__99 (CHAR *name, ADDRESS name__len)
{
	INT16 i;
	CHAR ch;
	i = 0;
	do {
		ch = name[__X(i, name__len)];
		OPM_ObjW(ch);
		i += 1;
	} while (!(ch == 0x00));
}

static struct FindPtrs__95__96 {
	INT32 *i;
	struct FindPtrs__95__96 *lnk;
} *FindPtrs__95__96_s;

static void Add__97 (INT32 adr);

static void Add__97 (INT32 adr)
{
	OPL_PtrTable table;
	if (OPL_nofptrs >= 1) {
		table = __NEWARR(NIL, 4, 4, 1, 1, 2);
		*FindPtrs__95__96_s->i = 0;
		while (*FindPtrs__95__96_s->i <= 0) {
			(table->data)[__X(*FindPtrs__95__96_s->i, table->len[0])] = (OPL_ptrTab->data)[__X(*FindPtrs__95__96_s->i, OPL_ptrTab->len[0])];
			*FindPtrs__95__96_s->i += 1;
		}
		OPL_ptrTab = table;
	}
	(OPL_ptrTab->data)[__X(OPL_nofptrs, OPL_ptrTab->len[0])] = adr;
	OPL_nofptrs += 1;
}

static void FindPtrs__95 (OPT_Struct typ, INT32 adr)
{
	OPT_Object fld;
	INT32 i, n, s;
	OPT_Struct btyp;
	struct FindPtrs__95__96 _s;
	_s.i = &i;
	_s.lnk = FindPtrs__95__96_s;
	FindPtrs__95__96_s = &_s;
	if (typ->form == 13) {
		if (typ->sysflag == 0) {
			Add__97(adr);
		}
	} else if ((typ->form == 14 && typ->sysflag == 5)) {
		Add__97(adr + 4);
	} else if (typ->comp == 6) {
		btyp = typ->BaseTyp;
		if (btyp != NIL) {
			FindPtrs__95(btyp, adr);
		}
		fld = typ->link;
		while ((fld != NIL && fld->mode == 4)) {
			if (__STRCMP(fld->name, "@ptr") == 0) {
				Add__97(adr);
			} else if (fld->sysflag != 4) {
				FindPtrs__95(fld->typ, fld->adr + adr);
			}
			fld = fld->link;
		}
	} else if (typ->comp == 2) {
		btyp = typ->BaseTyp;
		n = typ->n;
		while (btyp->comp == 2) {
			n = btyp->n * n;
			btyp = btyp->BaseTyp;
		}
		if ((btyp->form == 13 || __IN(btyp->comp, 0x50, 32)) || (btyp->form == 14 && btyp->sysflag == 5)) {
			i = 0;
			s = btyp->size;
			while (i < n) {
				FindPtrs__95(btyp, i * s + adr);
				i += 1;
			}
		}
	} else if (typ->comp == 4) {
		Add__97(adr);
	}
	FindPtrs__95__96_s = _s.lnk;
}

static void traverse__101 (OPT_Object obj)
{
	if (obj != NIL) {
		if (obj->mode == 7) {
			if (obj->vis != 0) {
				if ((obj->link == NIL && obj->typ == OPT_notyp)) {
					if (*OutCode__92_s->nofcmds <= 128) {
						(*OutCode__92_s->commandTab)[__X(*OutCode__92_s->nofcmds, 128)] = obj;
						*OutCode__92_s->nofcmds += 1;
					} else {
						OPM_err(232);
					}
				} else if ((((((obj->typ == OPT_ptrtyp && obj->link != NIL)) && obj->link->typ == OPT_ptrtyp)) && obj->link->link == NIL)) {
					if (*OutCode__92_s->nofcmds <= 128) {
						(*OutCode__92_s->commandTab)[__X(*OutCode__92_s->nofcmds, 128)] = obj;
						*OutCode__92_s->nofcmds += 1;
					} else {
						OPM_err(232);
					}
				}
			}
		} else if ((obj->mode == 1 && obj->sysflag != 4)) {
			FindPtrs__95(obj->typ, obj->linkadr);
		} else if (obj->mode == 11) {
			(OPT_modules->data)[__X(-obj->mnolev, OPT_modules->len[0])]->used = 1;
		}
		traverse__101(obj->left);
		traverse__101(obj->right);
	}
}

static void FindNewMths__93 (OPT_Object obj)
{
	if (obj != NIL) {
		if (obj->mode == 13 || (((obj->mode == 5 && obj->conval != NIL)) && __IN(1, obj->conval->setval, 32))) {
			(*OutCode__92_s->newMthTab)[__X(*OutCode__92_s->nofnewmth, 128)] = obj;
			*OutCode__92_s->nofnewmth += 1;
		}
		if (obj->mode == 5) {
			FindNewMths__93(obj->typ->link);
		} else {
			FindNewMths__93(obj->left);
			FindNewMths__93(obj->right);
		}
	}
}

void OPL_OutCode (CHAR *modName, ADDRESS modName__len)
{
	INT32 i, k, pos;
	INT16 nofcmds, nofnewmth, nofinhmth, linkCorrection, nofExp, nofImp;
	OPT_Object obj;
	OPT_Struct typ, btyp;
	OPT_Object commandTab[128];
	OPT_Object newMthTab[128];
	INT8 modMap[128];
	struct OutCode__92 _s;
	_s.nofcmds = &nofcmds;
	_s.nofnewmth = &nofnewmth;
	_s.commandTab = (void*)commandTab;
	_s.newMthTab = (void*)newMthTab;
	_s.lnk = OutCode__92_s;
	OutCode__92_s = &_s;
	linkCorrection = 0;
	i = 0;
	while (i < OPL_nofLinks) {
		if (OPL_link[__X(i, 512)].offset == -1 || OPL_link[__X(i, 512)].mod > 0) {
			linkCorrection += 1;
		}
		i += 1;
	}
	i = __MASK(-OPO_csize, -4);
	while (i > 0) {
		(OPO_constant->data)[__X(OPO_csize, OPO_constant->len[0])] = 0x00;
		OPO_csize += 1;
		i -= 1;
	}
	nofcmds = 0;
	traverse__101(OPT_topScope->right);
	nofImp = 0;
	i = 1;
	while (i < OPT_nofmod) {
		if ((OPT_modules->data)[__X(i, OPT_modules->len[0])]->used) {
			nofImp += 1;
			modMap[__X(i, 128)] = (INT8)nofImp;
		}
		i += 1;
	}
	i = 0;
	OPM_ObjWInt(OPL_nofEntries);
	OPM_ObjWInt(nofcmds);
	if (OPL_nofptrs > 32767) {
		OPM_err(222);
	}
	OPM_ObjWInt((INT16)OPL_nofptrs);
	OPM_ObjWInt(OPL_nofrecs);
	OPM_ObjWInt(nofImp);
	OPM_ObjWInt(OPL_nofVarCons);
	OPM_ObjWInt(OPL_nofLinks - linkCorrection);
	OPM_ObjWBytes((void*)&OPO_dsize, 4, 4);
	OPM_ObjWInt((INT16)OPO_csize);
	OPM_ObjWInt((INT16)OPO_pc);
	WriteName__99((void*)modName, modName__len);
	OPM_ObjW(0x82);
	i = 0;
	while (i < OPL_nofEntries) {
		OPM_ObjWInt((OPL_entry->data)[__X(i, OPL_entry->len[0])]);
		i += 1;
	}
	OPM_ObjW(0x83);
	i = 0;
	while (i < nofcmds) {
		obj = commandTab[__X(i, 128)];
		if (obj->link != NIL) {
			OPM_ObjW('$');
		}
		WriteName__99((void*)obj->name, 32);
		OPM_ObjWInt((OPL_entry->data)[__X(__MASK(obj->adr, -65536), OPL_entry->len[0])]);
		i += 1;
	}
	OPM_ObjW(0x84);
	i = 0;
	while (i < OPL_nofptrs) {
		OPM_ObjWBytes((void*)&(OPL_ptrTab->data)[__X(i, OPL_ptrTab->len[0])], 4, 4);
		i += 1;
	}
	OPM_ObjW(0x85);
	i = 1;
	while (i < OPT_nofmod) {
		obj = (OPT_Object)(OPT_modules->data)[__X(i, OPT_modules->len[0])];
		if (obj->used) {
			WriteName__99((void*)obj->name, 32);
		}
		i += 1;
	}
	OPM_ObjW(0x8d);
	i = 0;
	while (i < OPL_nofVarCons) {
		OPM_ObjW((CHAR)modMap[__X((OPL_varConsLink->data)[__X(i, OPL_varConsLink->len[0])].mod, 128)]);
		OPM_ObjWInt((OPL_varConsLink->data)[__X(i, OPL_varConsLink->len[0])].entry);
		OPM_ObjWInt((OPL_varConsLink->data)[__X(i, OPL_varConsLink->len[0])].noflinks);
		k = (OPL_varConsLink->data)[__X(i, OPL_varConsLink->len[0])].index;
		while (k != -1) {
			OPM_ObjWInt((OPL_varConsTab->data)[__X(k, OPL_varConsTab->len[0])].offset);
			k = (OPL_varConsTab->data)[__X(k, OPL_varConsTab->len[0])].next;
		}
		i += 1;
	}
	OPM_ObjW(0x86);
	i = 0;
	while (i < OPL_nofLinks) {
		if ((OPL_link[__X(i, 512)].offset != -1 && OPL_link[__X(i, 512)].mod <= 0)) {
			OPM_ObjW((CHAR)modMap[__X(OPL_link[__X(i, 512)].mod, 128)]);
			OPM_ObjW((CHAR)OPL_link[__X(i, 512)].entry);
			OPM_ObjWInt(OPL_link[__X(i, 512)].offset);
		}
		i += 1;
	}
	OPM_ObjW(0x87);
	i = 0;
	while (i < OPO_csize) {
		OPM_ObjW((OPO_constant->data)[__X(i, OPO_constant->len[0])]);
		i += 1;
	}
	OPM_ObjW(0x88);
	pos = OPM_ObjAllocInt();
	nofExp = 0;
	OPL_nofStr = 0;
	OPT_modNo = 0;
	OPL_exppos = 0;
	OPL_Export(OPT_topScope->right, &nofExp);
	OPM_ObjW(0x00);
	OPM_ObjFillInt(pos, nofExp);
	OPM_ObjW(0x89);
	i = 0;
	while (i < OPO_pc) {
		OPM_ObjW(OPO_code[__X(i, 65000)]);
		i += 1;
	}
	OPM_ObjW(0x8a);
	i = 1;
	while (i < OPT_nofmod) {
		if ((OPT_modules->data)[__X(i, OPT_modules->len[0])]->used) {
			OPM_ObjWString((void*)(OPT_modules->data)[__X(i, OPT_modules->len[0])]->name, 32);
			OPT_modNo = (INT16)i;
			OPL_Use((OPT_modules->data)[__X(i, OPT_modules->len[0])]->right);
			OPM_ObjW(0x00);
		}
		i += 1;
	}
	OPM_ObjW(0x00);
	OPM_ObjW(0x8b);
	i = 0;
	while (i < OPL_nofrecs) {
		typ = (OPL_recTab->data)[__X(i, OPL_recTab->len[0])];
		OPL_nofptrs = 0;
		FindPtrs__95(typ, 0);
		OPM_ObjWBytes((void*)&typ->size, 4, 4);
		OPM_ObjWInt((INT16)typ->tdadr);
		btyp = typ->BaseTyp;
		if (btyp == NIL) {
			nofinhmth = 0;
			OPM_ObjWInt(-1);
			OPM_ObjWLInt(-1);
		} else {
			nofinhmth = (INT16)btyp->n;
			OPM_ObjWInt(modMap[__X(btyp->mno, 128)]);
			if (btyp->mno == 0) {
				OPM_ObjWBytes((void*)&btyp->tdadr, 4, 4);
			} else {
				OPM_ObjWLInt(btyp->strobj->fp);
			}
		}
		OPM_ObjWInt((INT16)typ->n);
		OPM_ObjWInt(nofinhmth);
		nofnewmth = 0;
		FindNewMths__93(typ->strobj);
		OPM_ObjWInt(nofnewmth);
		if (OPL_nofptrs > 32767) {
			OPM_err(221);
		}
		OPM_ObjWInt((INT16)OPL_nofptrs);
		if ((typ->strobj != NIL && typ->strobj->mnolev == 0)) {
			if (typ->ptr != NIL) {
				if (typ->ptr->strobj == NIL) {
					WriteName__99((void*)typ->strobj->name, 32);
				} else {
					WriteName__99((void*)typ->ptr->strobj->name, 32);
				}
			} else {
				WriteName__99((void*)typ->strobj->name, 32);
			}
		} else {
			OPM_ObjW(0x00);
		}
		while (nofnewmth > 0) {
			nofnewmth -= 1;
			OPM_ObjWInt((INT16)__ASHR(newMthTab[__X(nofnewmth, 128)]->adr, 16));
			OPM_ObjWInt((INT16)__MASK(newMthTab[__X(nofnewmth, 128)]->adr, -65536));
		}
		k = 0;
		while (k < OPL_nofptrs) {
			OPM_ObjWBytes((void*)&(OPL_ptrTab->data)[__X(k, OPL_ptrTab->len[0])], 4, 4);
			k += 1;
		}
		i += 1;
	}
	OPM_CloseObj();
	OutCode__92_s = _s.lnk;
}

void OPL_Close (void)
{
	INT32 i;
	i = 0;
	while (i <= 0) {
		(OPL_Instr->data)[__X(i, OPL_Instr->len[0])].node = NIL;
		i += 1;
	}
	i = 0;
	while (i < 1) {
		(OPL_recTab->data)[__X(i, OPL_recTab->len[0])] = NIL;
		i += 1;
	}
}

static void EnumPtrs(void (*P)(void*))
{
	P(OPL_Instr);
	P(OPL_map);
	P(OPL_ptrTab);
	P(OPL_recTab);
	P(OPL_entry);
	P(OPL_varConsLink);
	P(OPL_varConsTab);
	P(OPL_explist);
}

__TDESC(OPL_Instruction, 1, 1) = {__TDFLDS("Instruction", 40), {32, -8}};
__TDESC(OPL__1, 1, 0) = {__TDFLDS("", 8), {-4}};
__TDESC(OPL_LinkRec, 1, 0) = {__TDFLDS("LinkRec", 6), {-4}};
__TDESC(OPL_VarConsRec, 1, 0) = {__TDFLDS("VarConsRec", 8), {-4}};
__TDESC(OPL_VarConsLinkRec, 1, 0) = {__TDFLDS("VarConsLinkRec", 4), {-4}};
__TDESC(OPL_SavedRegRec, 1, 0) = {__TDFLDS("SavedRegRec", 48), {-4}};

export void *OPL__init(void)
{
	__DEFMOD;
	__MODULE_IMPORT(OPM);
	__MODULE_IMPORT(OPO);
	__MODULE_IMPORT(OPT);
	__REGMOD("OPL", EnumPtrs);
	__REGCMD("Close", OPL_Close);
	__REGCMD("Init", OPL_Init);
	__INITYP(OPL_Instruction, OPL_Instruction, 0);
	__INITYP(OPL__1, OPL__1, 0);
	__INITYP(OPL_LinkRec, OPL_LinkRec, 0);
	__INITYP(OPL_VarConsRec, OPL_VarConsRec, 0);
	__INITYP(OPL_VarConsLinkRec, OPL_VarConsLinkRec, 0);
	__INITYP(OPL_SavedRegRec, OPL_SavedRegRec, 0);
/* BEGIN */
	OPL_ptrTab = __NEWARR(NIL, 4, 4, 1, 1, 512);
	OPL_recTab = __NEWARR(POINTER__typ, 4, 4, 1, 1, 64);
	OPL_entry = __NEWARR(NIL, 2, 2, 1, 1, 128);
	OPL_Instr = __NEWARR(OPL_Instruction__typ, 40, 4, 1, 1, 500);
	OPL_varConsLink = __NEWARR(NIL, 8, 2, 1, 1, 100);
	OPL_varConsTab = __NEWARR(NIL, 4, 2, 1, 1, 500);
	OPL_explist = __NEWARR(NIL, 4, 4, 1, 1, 32);
	OPL_JmpConvert[0] = 4;
	OPL_JmpConvert[1] = 5;
	OPL_JmpConvert[2] = 12;
	OPL_JmpConvert[3] = 14;
	OPL_JmpConvert[4] = 15;
	OPL_JmpConvert[5] = 13;
	OPL_JmpConvert[6] = 7;
	OPL_JmpConvert[7] = 3;
	OPL_JmpConvert[8] = 2;
	OPL_JmpConvert[9] = 6;
	OPL_JmpConvert[10] = 2;
	OPL_JmpConvert[11] = 3;
	OPL_SetccConvert[0] = 4;
	OPL_SetccConvert[1] = 5;
	OPL_SetccConvert[2] = 12;
	OPL_SetccConvert[3] = 14;
	OPL_SetccConvert[4] = 15;
	OPL_SetccConvert[5] = 13;
	OPL_SetccConvert[6] = 7;
	OPL_SetccConvert[7] = 3;
	OPL_SetccConvert[8] = 2;
	OPL_SetccConvert[9] = 6;
	OPL_SetccConvert[10] = 2;
	OPL_SetccConvert[11] = 3;
	__ENDMOD;
}
