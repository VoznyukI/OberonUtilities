/* voc 2.1.0 [2017/09/06]. Bootstrapping compiler for address size 8, alignment 8. xtaSv */

#define SHORTINT INT8
#define INTEGER  INT16
#define LONGINT  INT32
#define SET      UINT32

#include "SYSTEM.h"
#include "OPL.h"
#include "OPM.h"
#include "OPO.h"
#include "OPT.h"

typedef
	struct OPC_Item {
		INT8 mode, mnolev, scale;
		OPT_Struct typ;
		OPT_Node node;
		INT32 adr, offs, inx, descReg, descOffs;
	} OPC_Item;


export INT8 OPC_level;
export INT16 OPC_pc;
static OPC_Item OPC_True, OPC_False, OPC_Stack, OPC_ebp;
static INT8 OPC_formTab[16];
static INT16 OPC_CCtab[2][6];
static INT16 OPC_InvCCtab[12];
static OPC_Item OPC_lastTD;
static OPT_Struct OPC_delegateType;

export ADDRESS *OPC_Item__typ;

export void OPC_AbsVal (OPC_Item *z, ADDRESS *z__typ, OPC_Item *x, ADDRESS *x__typ);
export void OPC_Add (OPC_Item *z, ADDRESS *z__typ, OPC_Item *x, ADDRESS *x__typ, OPC_Item *y, ADDRESS *y__typ, INT16 f);
export void OPC_AllocSDynArr (OPT_Object *proc);
export void OPC_AllocateStatic (OPC_Item *tos, ADDRESS *tos__typ, INT32 size);
export void OPC_And (OPC_Item *z, ADDRESS *z__typ, OPC_Item *x, ADDRESS *x__typ, OPC_Item *y, ADDRESS *y__typ);
static INT32 OPC_ArgSize (OPT_Object par);
static void OPC_ArrayBaseSize (OPC_Item *len, ADDRESS *len__typ, OPC_Item arr);
static void OPC_ArrayLen (OPC_Item *len, ADDRESS *len__typ, OPC_Item arr, INT32 n);
export void OPC_Ash (OPC_Item *z, ADDRESS *z__typ, OPC_Item *x, ADDRESS *x__typ, OPC_Item *y, ADDRESS *y__typ);
export void OPC_Assign (OPC_Item *z, ADDRESS *z__typ, OPC_Item *x, ADDRESS *x__typ);
export void OPC_Await (OPC_Item z, OPC_Item self, OPC_Item y);
export void OPC_Call (OPC_Item *x, ADDRESS *x__typ, OPT_Object proc, OPT_Node node);
export void OPC_CallRecBody (OPC_Item *self, ADDRESS *self__typ, OPC_Item *body, ADDRESS *body__typ, OPT_Struct typ);
export void OPC_Cap (OPC_Item *z, ADDRESS *z__typ, OPC_Item *x, ADDRESS *x__typ);
export void OPC_Case (OPC_Item *x, ADDRESS *x__typ, INT32 low, INT32 high, INT32 *tab, INT32 *L, OPT_Node node);
export void OPC_CaseFixup (INT32 tab, INT32 elseLabel, INT32 len);
static void OPC_ChangeType (OPC_Item *item, ADDRESS *item__typ, INT8 form);
static void OPC_CheckIndex (OPC_Item *index, ADDRESS *index__typ, OPC_Item *len, ADDRESS *len__typ);
static void OPC_CheckIntRange (OPC_Item *x, ADDRESS *x__typ, INT8 form);
static void OPC_CheckOverflow (OPC_Item *x, ADDRESS *x__typ);
static void OPC_CheckRealRange (OPC_Item *x, ADDRESS *x__typ, INT8 form);
export void OPC_Cmp (OPC_Item *z, ADDRESS *z__typ, OPC_Item *x, ADDRESS *x__typ, OPC_Item *y, ADDRESS *y__typ, INT16 rel);
static void OPC_CompleteSL (OPC_Item *x, ADDRESS *x__typ);
export void OPC_CondAnd (OPC_Item *x, ADDRESS *x__typ);
export void OPC_CondOr (OPC_Item *x, ADDRESS *x__typ);
export void OPC_Convert (OPC_Item *x, ADDRESS *x__typ, INT8 form);
export void OPC_Copy (OPC_Item *z, ADDRESS *z__typ, OPC_Item *x, ADDRESS *x__typ);
static void OPC_CopyDynArr (OPC_Item *x, ADDRESS *x__typ, OPC_Item *y, ADDRESS *y__typ);
export void OPC_CorrectStackAdr (OPC_Item *x, ADDRESS *x__typ, INT32 size, INT32 dynblocks);
export void OPC_DeRef (OPC_Item *x, ADDRESS *x__typ);
export void OPC_DefLabel (INT32 *L);
export void OPC_Div (OPC_Item *z, ADDRESS *z__typ, OPC_Item *x, ADDRESS *x__typ, OPC_Item *y, ADDRESS *y__typ, INT16 f);
static void OPC_DumpItem (OPC_Item *x, ADDRESS *x__typ);
static void OPC_EndCall (OPT_Object proc, OPT_Struct typ);
export void OPC_Enter (OPT_Object proc, INT32 dataSize, OPT_Node node);
export void OPC_Exit (OPT_Object proc);
export void OPC_Field (OPC_Item *x, ADDRESS *x__typ, INT32 offset);
export void OPC_FixLink (INT32 L);
static void OPC_FixLinkWith (INT32 L, INT32 val);
static void OPC_Gen0 (INT16 op);
static void OPC_Gen1 (INT16 op, INT32 adr, OPT_Node node);
static void OPC_Gen2 (INT16 op, OPC_Item *z, ADDRESS *z__typ, OPC_Item *x, ADDRESS *x__typ);
static void OPC_Gen3 (INT16 op, OPC_Item *z, ADDRESS *z__typ, OPC_Item *x, ADDRESS *x__typ, OPC_Item *y, ADDRESS *y__typ);
export void OPC_GenAsm (OPT_Node n);
static void OPC_GenCall (INT16 op, INT32 adr, INT32 parSize, OPT_Node node);
export void OPC_GenDimTrap (OPC_Item *len, ADDRESS *len__typ);
static void OPC_GenFlags (INT16 op, OPC_Item *x, ADDRESS *x__typ, OPC_Item *y, ADDRESS *y__typ);
static void OPC_GenLoad (INT16 op, OPC_Item *z, ADDRESS *z__typ, OPC_Item *x, ADDRESS *x__typ);
static void OPC_GenLoadProc (INT16 op, OPC_Item *z, ADDRESS *z__typ, INT32 val, OPT_Node node);
static void OPC_GenPhi (INT32 reg0, INT32 reg1);
static void OPC_GenPop (OPC_Item *x, ADDRESS *x__typ);
static void OPC_GenPopReg (INT8 hint, INT8 form);
static void OPC_GenPush (OPC_Item *x, ADDRESS *x__typ);
static void OPC_GenRepMovs (OPC_Item *z, ADDRESS *z__typ, OPC_Item *x, ADDRESS *x__typ, OPC_Item *nofElem, ADDRESS *nofElem__typ, INT8 moveSize, BOOLEAN reverse);
static void OPC_GenSetC (INT16 op, OPC_Item *z, ADDRESS *z__typ);
static void OPC_GenStore (INT16 op, OPC_Item *z, ADDRESS *z__typ, OPC_Item *x, ADDRESS *x__typ);
export void OPC_GetTdAdr (OPT_Struct *typ, OPC_Item *tag, ADDRESS *tag__typ);
export void OPC_In (OPC_Item *z, ADDRESS *z__typ, OPC_Item *x, ADDRESS *x__typ, OPC_Item *y, ADDRESS *y__typ);
export void OPC_IncDec (OPC_Item *z, ADDRESS *z__typ, OPC_Item *x, ADDRESS *x__typ, BOOLEAN increment);
static void OPC_IncReg (INT32 pReg);
export void OPC_Include (OPC_Item *z, ADDRESS *z__typ, OPC_Item *x, ADDRESS *x__typ, BOOLEAN incl);
export void OPC_Index (OPC_Item *z, ADDRESS *z__typ, OPC_Item *index, ADDRESS *index__typ);
export void OPC_Init (void);
static void OPC_InitInstr (INT16 op, INT8 mode, INT8 form, OPT_Node node);
export void OPC_Jcc (OPC_Item *x, ADDRESS *x__typ, INT32 *loc, OPT_Node node);
export void OPC_Jmp (INT32 *loc, OPT_Node node);
export void OPC_Jncc (OPC_Item *x, ADDRESS *x__typ, INT32 *loc, OPT_Node node);
export void OPC_Len (OPC_Item *len, ADDRESS *len__typ, OPC_Item *x, ADDRESS *x__typ, OPC_Item *y, ADDRESS *y__typ);
static void OPC_Length (OPC_Item *len, ADDRESS *len__typ, OPC_Item *x, ADDRESS *x__typ);
export void OPC_Lock (OPC_Item self, OPC_Item excl);
export void OPC_MakeCon (OPC_Item *cons, ADDRESS *cons__typ, OPT_Struct typ, INT32 val);
static void OPC_MakeVar (OPC_Item *x, ADDRESS *x__typ, OPT_Object var);
static void OPC_Mem (OPC_Item *x, ADDRESS *x__typ);
export INT32 OPC_MergedLinks (INT32 L0, INT32 L1);
export void OPC_Method (OPC_Item *x, ADDRESS *x__typ, OPT_Object obj);
export void OPC_Mod (OPC_Item *z, ADDRESS *z__typ, OPC_Item *x, ADDRESS *x__typ, OPC_Item *y, ADDRESS *y__typ);
static void OPC_Move (OPC_Item *z, ADDRESS *z__typ, OPC_Item *x, ADDRESS *x__typ);
static void OPC_MoveBlock (OPC_Item *z, ADDRESS *z__typ, OPC_Item *x, ADDRESS *x__typ, OPC_Item *size, ADDRESS *size__typ, INT8 moveSize);
static void OPC_MoveBlockReversed (OPC_Item *z, ADDRESS *z__typ, OPC_Item *x, ADDRESS *x__typ, OPC_Item *size, ADDRESS *size__typ, INT8 moveSize);
static void OPC_MoveCoc (OPC_Item *z, ADDRESS *z__typ, OPC_Item *y, ADDRESS *y__typ);
export void OPC_Msk (OPC_Item *z, ADDRESS *z__typ, OPC_Item *x, ADDRESS *x__typ, OPC_Item *y, ADDRESS *y__typ);
export void OPC_Mul (OPC_Item *z, ADDRESS *z__typ, OPC_Item *x, ADDRESS *x__typ, OPC_Item *y, ADDRESS *y__typ, INT16 f);
export void OPC_MulDim (OPC_Item *nofelem, ADDRESS *nofelem__typ, OPC_Item *len, ADDRESS *len__typ);
export void OPC_Neg (OPC_Item *z, ADDRESS *z__typ, OPC_Item *x, ADDRESS *x__typ);
export void OPC_NewArray (OPC_Item *z, ADDRESS *z__typ, OPC_Item *nofelem, ADDRESS *nofelem__typ, INT32 nofdim, OPT_Struct typ, BOOLEAN dimUsed);
export void OPC_NewRec (OPC_Item *z, ADDRESS *z__typ, OPT_Struct typ);
export void OPC_NewStat (INT32 textPos);
export void OPC_NewSys (OPC_Item *z, ADDRESS *z__typ, OPC_Item *x, ADDRESS *x__typ);
static void OPC_NextWord (OPC_Item *z, ADDRESS *z__typ, OPC_Item y);
export void OPC_Not (OPC_Item *z, ADDRESS *z__typ, OPC_Item *x, ADDRESS *x__typ);
export void OPC_Odd (OPC_Item *z, ADDRESS *z__typ, OPC_Item *x, ADDRESS *x__typ);
export void OPC_Or (OPC_Item *z, ADDRESS *z__typ, OPC_Item *x, ADDRESS *x__typ, OPC_Item *y, ADDRESS *y__typ);
static void OPC_ParRecord (OPT_Object fp, OPC_Item *ap, ADDRESS *ap__typ, BOOLEAN apIsDeref, BOOLEAN alwaysRef);
export void OPC_Parameter (OPC_Item *ap, ADDRESS *ap__typ, OPT_Object fp, BOOLEAN apIsDeref, BOOLEAN alwaysRef);
export void OPC_PopLen (OPC_Item *block, ADDRESS *block__typ);
export void OPC_PopResult (OPT_Node n, OPC_Item *z, ADDRESS *z__typ);
export INT32 OPC_PrepRetDest (OPC_Item z);
export void OPC_Procedure (OPC_Item *proc, ADDRESS *proc__typ, OPT_Node n);
static void OPC_PushArrLen (OPT_Object fp, OPC_Item *ap, ADDRESS *ap__typ, OPC_Item *dest, ADDRESS *dest__typ, BOOLEAN useDest);
static void OPC_PushComp (OPT_Object fp, OPC_Item *ap, ADDRESS *ap__typ);
export void OPC_PushLen (OPC_Item *z, ADDRESS *z__typ);
export void OPC_PushRegs (void);
export void OPC_PushRetDesc (OPC_Item *x, ADDRESS *x__typ, OPC_Item *tos, ADDRESS *tos__typ);
export void OPC_Relation (OPC_Item *x, ADDRESS *x__typ);
export void OPC_RemoveStatic (INT32 size);
export void OPC_ResetStack (INT32 dynblocks);
export void OPC_Return (OPC_Item *res, ADDRESS *res__typ, OPT_Object proc);
export void OPC_SYSdop (OPC_Item *z, ADDRESS *z__typ, OPC_Item *x, ADDRESS *x__typ, OPC_Item *y, ADDRESS *y__typ, INT8 subcl);
export void OPC_SYSgetput (OPC_Item *z, ADDRESS *z__typ, OPC_Item *x, ADDRESS *x__typ, BOOLEAN getfn);
export void OPC_SYSgetputReg (OPC_Item *z, ADDRESS *z__typ, OPC_Item *x, ADDRESS *x__typ, BOOLEAN getrfn);
export void OPC_SYSinterrupt (BOOLEAN clear);
export void OPC_SYSmop (OPC_Item *z, ADDRESS *z__typ, OPC_Item *x, ADDRESS *x__typ, INT8 subcl, OPT_Struct typ);
export void OPC_SYSmove (OPC_Item *z, ADDRESS *z__typ, OPC_Item *x, ADDRESS *x__typ, OPC_Item *nofBytes, ADDRESS *nofBytes__typ);
export void OPC_SYSportio (OPC_Item *z, ADDRESS *z__typ, OPC_Item *x, ADDRESS *x__typ, BOOLEAN pin);
static void OPC_SetCC (OPC_Item *x, ADDRESS *x__typ, INT32 cc);
export void OPC_SetElem (OPC_Item *z, ADDRESS *z__typ, OPC_Item *x, ADDRESS *x__typ);
export void OPC_SetRange (OPC_Item *z, ADDRESS *z__typ, OPC_Item *x, ADDRESS *x__typ, OPC_Item *y, ADDRESS *y__typ);
export void OPC_Sub (OPC_Item *z, ADDRESS *z__typ, OPC_Item *x, ADDRESS *x__typ, OPC_Item *y, ADDRESS *y__typ, INT16 f);
export void OPC_Trap (INT32 n, OPT_Node node);
static void OPC_TypeSize (OPC_Item x, OPC_Item *size, ADDRESS *size__typ, INT8 *step, INT8 *scale);
export void OPC_TypeTest (OPC_Item *x, ADDRESS *x__typ, OPT_Struct testtyp, BOOLEAN guard, BOOLEAN equal, BOOLEAN varRec);
export void OPC_Unlock (OPC_Item self, OPC_Item excl);
static void OPC_load (OPC_Item *x, ADDRESS *x__typ);
static void OPC_loadAdr (OPC_Item *x, ADDRESS *x__typ);
static void OPC_loadDynArr (OPC_Item *z, ADDRESS *z__typ);
static void OPC_loadf (OPC_Item *x, ADDRESS *x__typ);


static void OPC_DumpItem (OPC_Item *x, ADDRESS *x__typ)
{
	OPM_LogWNum((*x).mode, 2);
	OPM_LogW('/');
	OPM_LogWNum((*x).mnolev, 1);
	OPM_LogW('/');
	OPM_LogWNum((*x).adr, 1);
	OPM_LogW('/');
	OPM_LogWNum((*x).offs, 3);
	OPM_LogW('/');
	OPM_LogWNum((*x).inx, 1);
	OPM_LogW('/');
	OPM_LogWNum((*x).descReg, 1);
	OPM_LogW('/');
	OPM_LogWNum((*x).descOffs, 3);
	OPM_LogW('/');
	OPM_LogWNum((*x).scale, 1);
	OPM_LogW('/');
}

void OPC_Init (void)
{
	OPC_pc = 0;
	OPC_level = 0;
}

static void OPC_IncReg (INT32 pReg)
{
	if (pReg >= 0) {
		(OPL_Instr->data)[__X(pReg, OPL_Instr->len[0])].used += 1;
	}
}

static void OPC_InitInstr (INT16 op, INT8 mode, INT8 form, OPT_Node node)
{
	INT32 i;
	OPL_InstructionTable instr;
	if (OPC_pc >= 1) {
		instr = __NEWARR(OPL_Instruction__typ, 40, 4, 1, 1, 2);
		i = 0;
		while (i <= 0) {
			(instr->data)[__X(i, instr->len[0])] = (OPL_Instr->data)[__X(i, OPL_Instr->len[0])];
			i += 1;
		}
		OPL_Instr = instr;
	}
	__ASSERT((mode >= 0 && mode <= 3), 0);
	__ASSERT((__MASK(op, -32) == 0 && op > 0), 0);
	(OPL_Instr->data)[__X(OPC_pc, OPL_Instr->len[0])].op = (op + (INT16)OPC_formTab[__X(form, 16)]) + (INT16)__ASHL(mode, 3);
	(OPL_Instr->data)[__X(OPC_pc, OPL_Instr->len[0])].node = node;
	(OPL_Instr->data)[__X(OPC_pc, OPL_Instr->len[0])].src1 = -1;
	(OPL_Instr->data)[__X(OPC_pc, OPL_Instr->len[0])].src2 = -1;
	(OPL_Instr->data)[__X(OPC_pc, OPL_Instr->len[0])].inx = -1;
	(OPL_Instr->data)[__X(OPC_pc, OPL_Instr->len[0])].dest = OPC_pc;
	(OPL_Instr->data)[__X(OPC_pc, OPL_Instr->len[0])].used = 0;
	(OPL_Instr->data)[__X(OPC_pc, OPL_Instr->len[0])].hint = -1;
	(OPL_Instr->data)[__X(OPC_pc, OPL_Instr->len[0])].pc = -1;
	(OPL_Instr->data)[__X(OPC_pc, OPL_Instr->len[0])].reg = -1;
	(OPL_Instr->data)[__X(OPC_pc, OPL_Instr->len[0])].abs = 0;
}

void OPC_NewStat (INT32 textPos)
{
	OPC_InitInstr(3136, 0, 0, NIL);
	(OPL_Instr->data)[__X(OPC_pc, OPL_Instr->len[0])].src1 = textPos;
	OPM_errpos = textPos;
	OPC_pc += 1;
}

static void OPC_GenLoad (INT16 op, OPC_Item *z, ADDRESS *z__typ, OPC_Item *x, ADDRESS *x__typ)
{
	switch ((*x).mode) {
		case 16: 
			OPC_InitInstr(op, 2, (*x).typ->form, (*x).node);
			(OPL_Instr->data)[__X(OPC_pc, OPL_Instr->len[0])].src2 = (*x).adr;
			(OPL_Instr->data)[__X(OPC_pc, OPL_Instr->len[0])].inx = (*x).inx;
			(OPL_Instr->data)[__X(OPC_pc, OPL_Instr->len[0])].scale = (*x).scale;
			(OPL_Instr->data)[__X(OPC_pc, OPL_Instr->len[0])].src1 = -1;
			OPC_IncReg((*x).inx);
			break;
		case 1: 
			__ASSERT((*x).mnolev > 0, 0);
			OPC_InitInstr(op, 2, (*x).typ->form, (*x).node);
			(OPL_Instr->data)[__X(OPC_pc, OPL_Instr->len[0])].src2 = (*x).adr;
			(OPL_Instr->data)[__X(OPC_pc, OPL_Instr->len[0])].inx = -1;
			(OPL_Instr->data)[__X(OPC_pc, OPL_Instr->len[0])].scale = (*x).scale;
			(OPL_Instr->data)[__X(OPC_pc, OPL_Instr->len[0])].src1 = -2;
			break;
		case 3: 
			__ASSERT((((((op != 384 && op != 2528)) && op != 2624)) && op != 480), 0);
			__ASSERT(op < 64 || op > 224, 0);
			OPC_InitInstr(op, 3, (*x).typ->form, (*x).node);
			(OPL_Instr->data)[__X(OPC_pc, OPL_Instr->len[0])].src2 = (*x).adr;
			break;
		case 15: 
			__ASSERT((op != 384 && op != 2624), 0);
			OPC_InitInstr(op, 0, (*x).typ->form, (*x).node);
			(OPL_Instr->data)[__X(OPC_pc, OPL_Instr->len[0])].src1 = (*x).adr;
			if (op != 480) {
				OPC_IncReg((*x).adr);
			}
			break;
		case 17: 
			OPC_InitInstr(op, 2, (*x).typ->form, (*x).node);
			(OPL_Instr->data)[__X(OPC_pc, OPL_Instr->len[0])].src1 = (*x).adr;
			(OPL_Instr->data)[__X(OPC_pc, OPL_Instr->len[0])].src2 = (*x).offs;
			(OPL_Instr->data)[__X(OPC_pc, OPL_Instr->len[0])].inx = (*x).inx;
			(OPL_Instr->data)[__X(OPC_pc, OPL_Instr->len[0])].scale = (*x).scale;
			OPC_IncReg((*x).adr);
			OPC_IncReg((*x).inx);
			break;
		case 18: 
			OPC_MoveCoc(&*z, z__typ, &*x, x__typ);
			return;
			break;
		default: 
			__HALT(40);
			break;
	}
	(*z).adr = OPC_pc;
	(*z).mode = 15;
	OPC_pc += 1;
}

static void OPC_GenPush (OPC_Item *x, ADDRESS *x__typ)
{
	OPC_Item dummy;
	__ASSERT((*x).mode == 15 || (*x).mode == 3, 100);
	dummy.node = NIL;
	OPC_GenLoad(448, &dummy, OPC_Item__typ, &*x, x__typ);
}

static void OPC_GenPop (OPC_Item *x, ADDRESS *x__typ)
{
	OPC_Item dummy;
	dummy.node = NIL;
	(*x).mode = 15;
	(*x).adr = OPC_pc;
	(*x).node = NIL;
	OPC_GenLoad(480, &dummy, OPC_Item__typ, &*x, x__typ);
}

static void OPC_GenLoadProc (INT16 op, OPC_Item *z, ADDRESS *z__typ, INT32 val, OPT_Node node)
{
	OPC_InitInstr(op, 3, 6, node);
	(*z).mode = 15;
	(*z).typ = OPT_ptrtyp;
	(*z).adr = OPC_pc;
	(OPL_Instr->data)[__X(OPC_pc, OPL_Instr->len[0])].src1 = val;
	OPC_pc += 1;
}

static void OPC_GenStore (INT16 op, OPC_Item *z, ADDRESS *z__typ, OPC_Item *x, ADDRESS *x__typ)
{
	__ASSERT((*x).mode == 15, 0);
	switch ((*z).mode) {
		case 16: 
			OPC_InitInstr(op, 1, (*z).typ->form, (*z).node);
			(OPL_Instr->data)[__X(OPC_pc, OPL_Instr->len[0])].dest = (*x).adr;
			(OPL_Instr->data)[__X(OPC_pc, OPL_Instr->len[0])].src2 = (*z).adr;
			(OPL_Instr->data)[__X(OPC_pc, OPL_Instr->len[0])].inx = (*z).inx;
			(OPL_Instr->data)[__X(OPC_pc, OPL_Instr->len[0])].scale = (*z).scale;
			(OPL_Instr->data)[__X(OPC_pc, OPL_Instr->len[0])].src1 = -1;
			OPC_IncReg((*z).inx);
			break;
		case 1: 
			__ASSERT((*z).mnolev > 0, 0);
			OPC_InitInstr(op, 1, (*z).typ->form, (*z).node);
			(OPL_Instr->data)[__X(OPC_pc, OPL_Instr->len[0])].dest = (*x).adr;
			(OPL_Instr->data)[__X(OPC_pc, OPL_Instr->len[0])].src2 = (*z).adr;
			(OPL_Instr->data)[__X(OPC_pc, OPL_Instr->len[0])].inx = -1;
			(OPL_Instr->data)[__X(OPC_pc, OPL_Instr->len[0])].src1 = -2;
			break;
		case 17: 
			OPC_InitInstr(op, 1, (*z).typ->form, (*z).node);
			(OPL_Instr->data)[__X(OPC_pc, OPL_Instr->len[0])].dest = (*x).adr;
			(OPL_Instr->data)[__X(OPC_pc, OPL_Instr->len[0])].src1 = (*z).adr;
			(OPL_Instr->data)[__X(OPC_pc, OPL_Instr->len[0])].src2 = (*z).offs;
			(OPL_Instr->data)[__X(OPC_pc, OPL_Instr->len[0])].inx = (*z).inx;
			(OPL_Instr->data)[__X(OPC_pc, OPL_Instr->len[0])].scale = (*z).scale;
			OPC_IncReg((*z).adr);
			OPC_IncReg((*z).inx);
			break;
		default: 
			__HALT(40);
			break;
	}
	if (op != 256) {
		OPC_IncReg((*x).adr);
	}
	OPC_pc += 1;
}

static void OPC_GenPopReg (INT8 hint, INT8 form)
{
	if (hint == -1) {
		OPC_InitInstr(2400, 0, 0, NIL);
	} else {
		OPC_InitInstr(2400, 0, form, NIL);
		(OPL_Instr->data)[__X(OPC_pc, OPL_Instr->len[0])].hint = hint;
	}
	OPC_pc += 1;
}

static void OPC_Gen0 (INT16 op)
{
	OPC_InitInstr(op, 0, 0, NIL);
	OPC_pc += 1;
}

static void OPC_Gen1 (INT16 op, INT32 adr, OPT_Node node)
{
	if (op == 1920) {
		OPC_InitInstr(op, 0, 6, node);
		OPC_IncReg(adr);
	} else {
		OPC_InitInstr(op, 0, 0, node);
	}
	(OPL_Instr->data)[__X(OPC_pc, OPL_Instr->len[0])].src2 = adr;
	OPC_pc += 1;
}

static void OPC_Gen2 (INT16 op, OPC_Item *z, ADDRESS *z__typ, OPC_Item *x, ADDRESS *x__typ)
{
	__ASSERT((*x).mode == 15, 0);
	OPC_InitInstr(op, 0, (*x).typ->form, (*x).node);
	(OPL_Instr->data)[__X(OPC_pc, OPL_Instr->len[0])].src1 = (*x).adr;
	OPC_IncReg((*x).adr);
	(*z).adr = OPC_pc;
	(*z).mode = 15;
	OPC_pc += 1;
}

static void OPC_Gen3 (INT16 op, OPC_Item *z, ADDRESS *z__typ, OPC_Item *x, ADDRESS *x__typ, OPC_Item *y, ADDRESS *y__typ)
{
	if ((*y).mode == 3) {
		OPC_InitInstr(op, 3, (*x).typ->form, (*x).node);
	} else {
		OPC_InitInstr(op, 0, (*x).typ->form, (*x).node);
		OPC_IncReg((*y).adr);
	}
	(OPL_Instr->data)[__X(OPC_pc, OPL_Instr->len[0])].src1 = (*x).adr;
	(OPL_Instr->data)[__X(OPC_pc, OPL_Instr->len[0])].src2 = (*y).adr;
	OPC_IncReg((*x).adr);
	if (op == 608 || op == 640) {
		(OPL_Instr->data)[__X((*x).adr, OPL_Instr->len[0])].hint = 16;
	} else if ((((op >= 832 && op <= 928)) && (*y).mode != 3)) {
		(OPL_Instr->data)[__X((*y).adr, OPL_Instr->len[0])].hint = 1;
	} else if ((op == 576 && (*x).typ->form == 4)) {
		(OPL_Instr->data)[__X((*x).adr, OPL_Instr->len[0])].hint = 16;
	}
	(*z).adr = OPC_pc;
	(*z).mode = 15;
	OPC_pc += 1;
}

void OPC_PushRegs (void)
{
	OPC_Gen0(2368);
}

static void OPC_GenCall (INT16 op, INT32 adr, INT32 parSize, OPT_Node node)
{
	if (op == 2112) {
		OPC_InitInstr(op, 0, 6, node);
		OPC_IncReg(adr);
	} else {
		OPC_InitInstr(op, 0, 0, node);
	}
	(OPL_Instr->data)[__X(OPC_pc, OPL_Instr->len[0])].src1 = parSize;
	(OPL_Instr->data)[__X(OPC_pc, OPL_Instr->len[0])].src2 = adr;
	OPC_pc += 1;
}

static void OPC_GenFlags (INT16 op, OPC_Item *x, ADDRESS *x__typ, OPC_Item *y, ADDRESS *y__typ)
{
	__ASSERT(((*x).mode == 15 && __IN((*y).mode, 0x8008, 32)), 100);
	if ((*y).mode == 3) {
		OPC_InitInstr(op, 3, (*x).typ->form, (*x).node);
	} else {
		OPC_InitInstr(op, 0, (*x).typ->form, (*x).node);
		OPC_IncReg((*y).adr);
	}
	(OPL_Instr->data)[__X(OPC_pc, OPL_Instr->len[0])].src1 = (*x).adr;
	(OPL_Instr->data)[__X(OPC_pc, OPL_Instr->len[0])].src2 = (*y).adr;
	OPC_IncReg((*x).adr);
	OPC_pc += 1;
}

static void OPC_GenSetC (INT16 op, OPC_Item *z, ADDRESS *z__typ)
{
	OPC_InitInstr(op, 0, 4, (*z).node);
	(*z).adr = OPC_pc;
	(*z).mode = 15;
	OPC_pc += 1;
}

static void OPC_GenRepMovs (OPC_Item *z, ADDRESS *z__typ, OPC_Item *x, ADDRESS *x__typ, OPC_Item *nofElem, ADDRESS *nofElem__typ, INT8 moveSize, BOOLEAN reverse)
{
	OPC_InitInstr(2304, 0, 0, NIL);
	(OPL_Instr->data)[__X(OPC_pc, OPL_Instr->len[0])].dest = (*z).adr;
	(OPL_Instr->data)[__X(OPC_pc, OPL_Instr->len[0])].src1 = (*x).adr;
	(OPL_Instr->data)[__X(OPC_pc, OPL_Instr->len[0])].src2 = (*nofElem).adr;
	(OPL_Instr->data)[__X(OPC_pc, OPL_Instr->len[0])].inx = moveSize;
	if (reverse) {
		(OPL_Instr->data)[__X(OPC_pc, OPL_Instr->len[0])].hint = 1;
	}
	OPC_pc += 1;
}

static void OPC_GenPhi (INT32 reg0, INT32 reg1)
{
	OPC_InitInstr(2464, 0, 0, NIL);
	(OPL_Instr->data)[__X(OPC_pc, OPL_Instr->len[0])].src1 = reg0;
	(OPL_Instr->data)[__X(OPC_pc, OPL_Instr->len[0])].src2 = reg1;
	(OPL_Instr->data)[__X(reg1, OPL_Instr->len[0])].hint = (INT16)(-1 - reg0);
	OPC_pc += 1;
}

void OPC_MakeCon (OPC_Item *cons, ADDRESS *cons__typ, OPT_Struct typ, INT32 val)
{
	(*cons).mode = 3;
	(*cons).adr = val;
	(*cons).offs = 0;
	(*cons).typ = typ;
	(*cons).node = NIL;
}

static void OPC_SetCC (OPC_Item *x, ADDRESS *x__typ, INT32 cc)
{
	(*x).typ = OPT_booltyp;
	(*x).mode = 18;
	(*x).adr = cc;
	(*x).offs = -1;
	(*x).inx = -1;
	(*x).node = NIL;
}

void OPC_DefLabel (INT32 *L)
{
	*L = OPC_pc;
	OPC_Gen0(2496);
}

static void OPC_FixLinkWith (INT32 L, INT32 val)
{
	INT32 L1;
	__ASSERT((L < 0 && val >= 0), 0);
	L = -2 - L;
	while (L != -1) {
		L1 = -2 - (OPL_Instr->data)[__X(L, OPL_Instr->len[0])].src2;
		(OPL_Instr->data)[__X(L, OPL_Instr->len[0])].src2 = val;
		L = L1;
	}
}

void OPC_FixLink (INT32 L)
{
	INT32 L1;
	__ASSERT(L < 0, 0);
	L = -2 - L;
	if (L != -1) {
		do {
			L1 = -2 - (OPL_Instr->data)[__X(L, OPL_Instr->len[0])].src2;
			(OPL_Instr->data)[__X(L, OPL_Instr->len[0])].src2 = OPC_pc;
			L = L1;
		} while (!(L == -1));
		OPC_Gen0(2496);
	}
}

INT32 OPC_MergedLinks (INT32 L0, INT32 L1)
{
	INT32 L2, L3;
	L2 = -2 - L0;
	if (L2 != -1) {
		for (;;) {
			L3 = -2 - (OPL_Instr->data)[__X(L2, OPL_Instr->len[0])].src2;
			if (L3 == -1) {
				break;
			}
			L2 = L3;
		}
		(OPL_Instr->data)[__X(L2, OPL_Instr->len[0])].src2 = L1;
		return L0;
	} else {
		return L1;
	}
	__RETCHK;
}

void OPC_Jmp (INT32 *loc, OPT_Node node)
{
	INT32 pos;
	if (*loc < 0) {
		pos = *loc;
		*loc = -2 - OPC_pc;
		OPC_Gen1(1888, pos, node);
	} else {
		OPC_Gen1(1888, *loc, node);
	}
}

void OPC_Jcc (OPC_Item *x, ADDRESS *x__typ, INT32 *loc, OPT_Node node)
{
	if ((*x).mode != 18) {
		__ASSERT((*x).typ->form == 2, 0);
		OPC_load(&*x, x__typ);
		OPC_GenFlags(1056, &*x, x__typ, &OPC_True, OPC_Item__typ);
		OPC_SetCC(&*x, x__typ, 1504);
	}
	if ((*x).adr != -1) {
		if (*loc < 0) {
			OPC_Gen1((INT16)(*x).adr, (*x).offs, node);
			*loc = -2 - (OPC_pc - 1);
		} else {
			OPC_Gen1((INT16)(*x).adr, *loc, node);
			OPC_FixLinkWith((*x).offs, *loc);
		}
	} else if (*loc >= 0) {
		OPC_FixLinkWith((*x).offs, *loc);
	}
	OPC_FixLink((*x).inx);
}

void OPC_Jncc (OPC_Item *x, ADDRESS *x__typ, INT32 *loc, OPT_Node node)
{
	INT16 j;
	if ((*x).mode != 18) {
		__ASSERT((*x).typ->form == 2, 0);
		OPC_load(&*x, x__typ);
		OPC_GenFlags(1056, &*x, x__typ, &OPC_True, OPC_Item__typ);
		OPC_SetCC(&*x, x__typ, 1504);
	}
	if ((*x).adr != 1888) {
		if ((*x).adr == -1) {
			j = 1888;
		} else {
			j = OPC_InvCCtab[__X(__ASHR((*x).adr - 1504, 5), 12)];
		}
		if (*loc < 0) {
			OPC_Gen1(j, (*x).inx, node);
			*loc = -2 - (OPC_pc - 1);
		} else {
			OPC_Gen1(j, *loc, node);
			OPC_FixLinkWith((*x).inx, *loc);
		}
	} else if (*loc >= 0) {
		OPC_FixLinkWith((*x).inx, *loc);
	}
	OPC_FixLink((*x).offs);
}

static void OPC_CompleteSL (OPC_Item *x, ADDRESS *x__typ)
{
	INT16 n;
	OPC_Item sl;
	if ((*x).mnolev > 0) {
		n = OPC_level - (*x).mnolev;
		if ((__IN((*x).mode, 0x06, 32) && n > 0)) {
			sl.mode = 17;
			sl.typ = OPT_ptrtyp;
			sl.mnolev = OPC_level;
			sl.inx = -1;
			sl.adr = -2;
			sl.offs = 8;
			sl.node = NIL;
			if (n > 1) {
				OPC_load(&sl, OPC_Item__typ);
				sl.mode = 17;
				sl.offs = 8;
				while (n > 2) {
					OPC_load(&sl, OPC_Item__typ);
					sl.mode = 17;
					sl.offs = 8;
					n -= 1;
				}
			}
			OPC_load(&sl, OPC_Item__typ);
			(*x).mode = 17;
			(*x).offs = (*x).adr;
			(*x).adr = sl.adr;
			(*x).inx = -1;
		}
	}
}

static void OPC_loadAdr (OPC_Item *x, ADDRESS *x__typ)
{
	OPT_Struct typ;
	__ASSERT(__IN((*x).mode, 0x030006, 32), 0);
	typ = (*x).typ;
	if ((*x).mode == 2 || ((*x).mode == 1 && __IN(typ->comp, 0x28, 32))) {
		OPC_CompleteSL(&*x, x__typ);
		(*x).typ = OPT_ptrtyp;
		if ((*x).mode == 2) {
			(*x).mode = 17;
			(*x).offs = (*x).adr;
			(*x).adr = -2;
			(*x).inx = -1;
		}
		OPC_GenLoad(32, &*x, x__typ, &*x, x__typ);
	} else {
		OPC_CompleteSL(&*x, x__typ);
		(*x).typ = OPT_ptrtyp;
		OPC_GenLoad(384, &*x, x__typ, &*x, x__typ);
	}
	(*x).offs = 0;
	(*x).inx = -1;
	(*x).scale = 0;
	(*x).typ = typ;
}

static void OPC_loadf (OPC_Item *x, ADDRESS *x__typ)
{
	if ((*x).mode != 15) {
		if ((*x).mode == 2) {
			OPC_loadAdr(&*x, x__typ);
			(*x).mode = 17;
		} else {
			OPC_CompleteSL(&*x, x__typ);
		}
		OPC_GenLoad(2528, &*x, x__typ, &*x, x__typ);
	}
}

static void OPC_load (OPC_Item *x, ADDRESS *x__typ)
{
	OPC_Item y;
	if ((*x).mode != 15) {
		if ((*x).mode == 2) {
			OPC_loadAdr(&*x, x__typ);
			(*x).mode = 17;
		} else {
			OPC_CompleteSL(&*x, x__typ);
		}
		if (((*x).typ->form == 14 && (*x).typ->sysflag == 5)) {
			OPC_NextWord(&y, OPC_Item__typ, *x);
			OPC_GenLoad(32, &*x, x__typ, &*x, x__typ);
			OPC_GenLoad(32, &y, OPC_Item__typ, &y, OPC_Item__typ);
			(*x).descReg = y.adr;
		} else {
			OPC_GenLoad(32, &*x, x__typ, &*x, x__typ);
		}
	}
}

static void OPC_NextWord (OPC_Item *z, ADDRESS *z__typ, OPC_Item y)
{
	__GUARDEQR(z, z__typ, OPC_Item) = y;
	switch ((*z).mode) {
		case 15: 
			(*z).adr = y.offs;
			break;
		case 1: case 16: 
			(*z).adr += 4;
			break;
		case 17: 
			(*z).offs += 4;
			break;
		default: __CASECHK;
	}
}

void OPC_DeRef (OPC_Item *x, ADDRESS *x__typ)
{
	OPT_Struct btyp;
	btyp = (*x).typ->BaseTyp;
	OPC_load(&*x, x__typ);
	(*x).mode = 17;
	(*x).offs = 0;
	(*x).inx = -1;
	(*x).scale = 0;
	if (btyp != NIL) {
		(*x).typ = btyp;
		if (btyp->comp == 5) {
			(*x).offs = 16 + __ASHL(__ASHR(1 + btyp->n, 1), 3);
			(*x).descReg = (*x).adr;
			(*x).descOffs = 12 + __ASHL(btyp->n, 2);
		} else if (btyp->comp == 2) {
			(*x).offs = 16;
		} else if (btyp->comp == 4) {
		}
	}
}

void OPC_GetTdAdr (OPT_Struct *typ, OPC_Item *tag, ADDRESS *tag__typ)
{
	__ASSERT(*typ != NIL, 0);
	if ((*typ)->tdadr == -1) {
		OPL_AllocTypDesc(*typ);
	}
	(*tag).mode = 16;
	(*tag).mnolev = (*typ)->mno;
	(*tag).typ = OPT_ptrtyp;
	(*tag).inx = -1;
	(*tag).adr = 0;
	(*tag).node = NIL;
	(*tag).adr = (*typ)->tdadr;
}

void OPC_TypeTest (OPC_Item *x, ADDRESS *x__typ, OPT_Struct testtyp, BOOLEAN guard, BOOLEAN equal, BOOLEAN varRec)
{
	OPC_Item testTag, t0, t1, z;
	__ASSERT(testtyp != NIL, 0);
	if (!guard || __IN(3, OPM_codeOptions, 32)) {
		z = *x;
		if (varRec) {
			OPC_CompleteSL(&z, OPC_Item__typ);
			if (__IN(z.mode, 0x06, 32)) {
				z.adr += 4;
				z.mode = 1;
			} else {
				__ASSERT(z.mode == 17, 0);
				z.offs += 4;
			}
		} else {
			if (testtyp->form == 13) {
				testtyp = testtyp->BaseTyp;
				OPC_DeRef(&z, OPC_Item__typ);
			}
			z.offs = -4;
		}
		if (!equal) {
			OPC_DeRef(&z, OPC_Item__typ);
			z.offs = (z.offs + -8) - __ASHL(testtyp->extlev, 2);
		}
		OPC_load(&z, OPC_Item__typ);
		OPC_GetTdAdr(&testtyp, &testTag, OPC_Item__typ);
		OPC_load(&testTag, OPC_Item__typ);
		OPC_GenFlags(1056, &z, OPC_Item__typ, &testTag, OPC_Item__typ);
		if (equal) {
			OPC_Gen1(1984, 5, NIL);
		} else if (guard) {
			OPC_Gen1(1984, 6, NIL);
		} else {
			OPC_SetCC(&*x, x__typ, 1504);
		}
	}
}

void OPC_Procedure (OPC_Item *proc, ADDRESS *proc__typ, OPT_Node n)
{
	OPT_Object obj;
	INT32 index;
	obj = n->obj;
	(*proc).mode = obj->mode;
	(*proc).node = n;
	(*proc).mnolev = obj->mnolev;
	(*proc).inx = -1;
	if (!__IN((*proc).mode, 0x2020, 32)) {
		if ((((__IN((*proc).mode, 0x80, 32) && (*proc).mnolev < 0)) && __ASHR(obj->adr, 16) == 0)) {
			OPL_NewLink(-obj->mnolev, obj->adr, &index);
			obj->adr = __ASHL(index, 16) + obj->adr;
		}
		(*proc).adr = obj->adr;
	} else {
		(*proc).offs = -72 - __ASHL(__ASHR(obj->adr, 16), 2);
	}
}

static void OPC_CheckOverflow (OPC_Item *x, ADDRESS *x__typ)
{
	if (__IN(1, OPM_codeOptions, 32)) {
		OPC_Gen1(2912, 4, NIL);
	}
}

static void OPC_CheckIntRange (OPC_Item *x, ADDRESS *x__typ, INT8 form)
{
}

static void OPC_CheckRealRange (OPC_Item *x, ADDRESS *x__typ, INT8 form)
{
}

static void OPC_CheckIndex (OPC_Item *index, ADDRESS *index__typ, OPC_Item *len, ADDRESS *len__typ)
{
	if (((*index).mode == 3 && (*len).mode != 3)) {
		if ((*len).mode != 15) {
			OPC_load(&*len, len__typ);
		}
		OPC_GenFlags(1056, &*len, len__typ, &*index, index__typ);
		OPC_Gen1(2944, 7, NIL);
	} else {
		if ((*index).mode != 15) {
			OPC_load(&*index, index__typ);
		}
		if ((*len).mode != 3) {
			OPC_load(&*len, len__typ);
		}
		OPC_GenFlags(1056, &*index, index__typ, &*len, len__typ);
		OPC_Gen1(2880, 7, NIL);
	}
}

static void OPC_ChangeType (OPC_Item *item, ADDRESS *item__typ, INT8 form)
{
	switch (form) {
		case 1: 
			(*item).typ = OPT_bytetyp;
			break;
		case 2: 
			(*item).typ = OPT_booltyp;
			break;
		case 3: 
			(*item).typ = OPT_chartyp;
			break;
		case 4: 
			(*item).typ = OPT_sinttyp;
			break;
		case 5: 
			(*item).typ = OPT_inttyp;
			break;
		case 6: 
			(*item).typ = OPT_linttyp;
			break;
		case 7: 
			(*item).typ = OPT_realtyp;
			break;
		case 8: 
			(*item).typ = OPT_lrltyp;
			break;
		case 9: 
			(*item).typ = OPT_settyp;
			break;
		case 13: 
			(*item).typ = OPT_ptrtyp;
			break;
		case 14: 
			(*item).typ = OPT_notyp;
			break;
		default: 
			__HALT(40);
			break;
	}
}

void OPC_SetElem (OPC_Item *z, ADDRESS *z__typ, OPC_Item *x, ADDRESS *x__typ)
{
	OPC_MakeCon(&*z, z__typ, OPT_settyp, 0);
	OPC_load(&*z, z__typ);
	if ((*x).typ->form != 6) {
		OPC_Convert(&*x, x__typ, 6);
	} else {
		OPC_load(&*x, x__typ);
	}
	OPC_Gen3(800, &*z, z__typ, &*z, z__typ, &*x, x__typ);
}

static struct Convert__28 {
	struct Convert__28 *lnk;
} *Convert__28_s;

static void ByteToInt__29 (OPC_Item *z, ADDRESS *z__typ, OPC_Item *x, ADDRESS *x__typ, INT8 zform);
static void CharToInt__31 (OPC_Item *z, ADDRESS *z__typ, OPC_Item *x, ADDRESS *x__typ, INT8 zform);
static void IntToCharByte__33 (OPC_Item *z, ADDRESS *z__typ, OPC_Item *x, ADDRESS *x__typ, INT8 form);
static void IntToInt__35 (OPC_Item *z, ADDRESS *z__typ, OPC_Item *x, ADDRESS *x__typ, INT8 xform, INT8 zform);
static void IntToReal__37 (OPC_Item *z, ADDRESS *z__typ, OPC_Item *x, ADDRESS *x__typ, INT8 xform, INT8 zform);
static void RealToInt__39 (OPC_Item *z, ADDRESS *z__typ, OPC_Item *x, ADDRESS *x__typ, INT8 xform, INT8 zform);
static void RealToReal__41 (OPC_Item *z, ADDRESS *z__typ, OPC_Item *x, ADDRESS *x__typ, INT8 xform, INT8 zform);

static void IntToInt__35 (OPC_Item *z, ADDRESS *z__typ, OPC_Item *x, ADDRESS *x__typ, INT8 xform, INT8 zform)
{
	__ASSERT((((((__IN(xform, 0x70, 32) && __IN(zform, 0x70, 32))) && __IN((*x).typ->form, 0x70, 32))) && __IN((*z).typ->form, 0x70, 32)), 0);
	if (xform < zform) {
		if ((*x).mode == 2) {
			OPC_loadAdr(&*x, x__typ);
			(*x).mode = 17;
		} else {
			OPC_CompleteSL(&*x, x__typ);
		}
		OPC_ChangeType(&*x, x__typ, zform);
		if ((*x).mode != 3) {
			if (zform == 5) {
				OPC_GenLoad(128, &*z, z__typ, &*x, x__typ);
			} else if (xform == 5) {
				OPC_GenLoad(96, &*z, z__typ, &*x, x__typ);
			} else {
				OPC_GenLoad(64, &*z, z__typ, &*x, x__typ);
			}
		} else {
			__GUARDEQR(z, z__typ, OPC_Item) = *x;
		}
	} else {
		if ((*x).mode == 15) {
			OPC_ChangeType(&*x, x__typ, zform);
			OPC_Gen2(2976, &*z, z__typ, &*x, x__typ);
		}
		OPC_CheckIntRange(&*x, x__typ, zform);
	}
}

static void IntToReal__37 (OPC_Item *z, ADDRESS *z__typ, OPC_Item *x, ADDRESS *x__typ, INT8 xform, INT8 zform)
{
	OPC_Item temp, cons;
	if ((*x).mode == 2) {
		OPC_loadAdr(&*x, x__typ);
		(*x).mode = 17;
	} else {
		OPC_CompleteSL(&*x, x__typ);
	}
	OPC_ChangeType(&*x, x__typ, 6);
	if (xform == 4) {
		OPC_GenLoad(64, &*x, x__typ, &*x, x__typ);
	} else if (xform == 5) {
		OPC_GenLoad(96, &*x, x__typ, &*x, x__typ);
	} else {
		OPC_load(&*x, x__typ);
	}
	OPC_GenPush(&*x, x__typ);
	temp.mode = 17;
	temp.typ = OPT_linttyp;
	temp.adr = -3;
	temp.offs = 0;
	temp.inx = -1;
	temp.node = NIL;
	OPC_ChangeType(&*z, z__typ, zform);
	OPC_ChangeType(&temp, OPC_Item__typ, zform);
	OPC_GenLoad(2624, &*z, z__typ, &temp, OPC_Item__typ);
	OPC_MakeCon(&cons, OPC_Item__typ, OPT_linttyp, 4);
	temp = OPC_Stack;
	OPC_Gen3(512, &temp, OPC_Item__typ, &OPC_Stack, OPC_Item__typ, &cons, OPC_Item__typ);
}

static void IntToCharByte__33 (OPC_Item *z, ADDRESS *z__typ, OPC_Item *x, ADDRESS *x__typ, INT8 form)
{
	if (((*x).typ->form != 4 && (*x).mode == 15)) {
		OPC_ChangeType(&*x, x__typ, form);
		OPC_Gen2(2976, &*z, z__typ, &*x, x__typ);
	}
	OPC_CheckIntRange(&*x, x__typ, form);
}

static void RealToReal__41 (OPC_Item *z, ADDRESS *z__typ, OPC_Item *x, ADDRESS *x__typ, INT8 xform, INT8 zform)
{
	if (xform < zform) {
		__GUARDEQR(z, z__typ, OPC_Item) = *x;
		OPC_loadf(&*z, z__typ);
	} else {
		__GUARDEQR(z, z__typ, OPC_Item) = *x;
		OPC_loadf(&*z, z__typ);
		OPC_CheckRealRange(&*x, x__typ, 7);
	}
}

static void RealToInt__39 (OPC_Item *z, ADDRESS *z__typ, OPC_Item *x, ADDRESS *x__typ, INT8 xform, INT8 zform)
{
	OPC_loadf(&*x, x__typ);
	OPC_ChangeType(&*x, x__typ, 6);
	OPC_Gen2(3104, &*z, z__typ, &*x, x__typ);
}

static void CharToInt__31 (OPC_Item *z, ADDRESS *z__typ, OPC_Item *x, ADDRESS *x__typ, INT8 zform)
{
	if ((*x).mode == 2) {
		OPC_loadAdr(&*x, x__typ);
		(*x).mode = 17;
	} else {
		OPC_CompleteSL(&*x, x__typ);
	}
	OPC_ChangeType(&*x, x__typ, zform);
	if (zform == 5) {
		OPC_GenLoad(224, &*z, z__typ, &*x, x__typ);
	} else if (zform == 6) {
		OPC_GenLoad(160, &*z, z__typ, &*x, x__typ);
	}
}

static void ByteToInt__29 (OPC_Item *z, ADDRESS *z__typ, OPC_Item *x, ADDRESS *x__typ, INT8 zform)
{
	if ((*x).mode == 2) {
		OPC_loadAdr(&*x, x__typ);
		(*x).mode = 17;
	} else {
		OPC_CompleteSL(&*x, x__typ);
	}
	OPC_ChangeType(&*x, x__typ, zform);
	if (zform == 5) {
		OPC_GenLoad(128, &*z, z__typ, &*x, x__typ);
	} else if (zform == 6) {
		OPC_GenLoad(64, &*z, z__typ, &*x, x__typ);
	}
}

void OPC_Convert (OPC_Item *x, ADDRESS *x__typ, INT8 form)
{
	OPC_Item t;
	INT8 xform;
	struct Convert__28 _s;
	_s.lnk = Convert__28_s;
	Convert__28_s = &_s;
	if ((*x).mode == 18) {
		t = *x;
		OPC_MoveCoc(&*x, x__typ, &t, OPC_Item__typ);
	}
	t = *x;
	xform = (*x).typ->form;
	if (__IN(xform, 0x70, 32)) {
		if (__IN(form, 0x70, 32)) {
			IntToInt__35(&*x, x__typ, &t, OPC_Item__typ, xform, form);
		} else if (__IN(form, 0x0180, 32)) {
			IntToReal__37(&*x, x__typ, &t, OPC_Item__typ, xform, form);
		} else if (__IN(form, 0x0a, 32)) {
			IntToCharByte__33(&*x, x__typ, &t, OPC_Item__typ, form);
		} else {
			__HALT(40);
		}
	} else if (__IN(xform, 0x0180, 32)) {
		if (__IN(form, 0x0180, 32)) {
			RealToReal__41(&*x, x__typ, &t, OPC_Item__typ, xform, form);
		} else if (form == 6) {
			RealToInt__39(&*x, x__typ, &t, OPC_Item__typ, xform, form);
		} else if (__IN(form, 0x30, 32)) {
			RealToInt__39(&*x, x__typ, &t, OPC_Item__typ, xform, form);
			OPC_ChangeType(&*x, x__typ, 6);
			t = *x;
			IntToInt__35(&*x, x__typ, &t, OPC_Item__typ, 6, form);
		} else if (__IN(form, 0x0a, 32)) {
			RealToInt__39(&*x, x__typ, &t, OPC_Item__typ, xform, 6);
			OPC_ChangeType(&*x, x__typ, 6);
			t = *x;
			IntToCharByte__33(&*x, x__typ, &t, OPC_Item__typ, form);
		} else {
			__HALT(40);
		}
	} else if ((__IN(xform, 0x0a, 32) && __IN(form, 0x0a, 32))) {
	} else if (xform == 3) {
		__ASSERT(__IN(form, 0x01f0, 32), 0);
		if (__IN(form, 0x70, 32)) {
			CharToInt__31(&*x, x__typ, &t, OPC_Item__typ, form);
		} else {
			CharToInt__31(&*x, x__typ, &t, OPC_Item__typ, 6);
			t = *x;
			IntToReal__37(&*x, x__typ, &t, OPC_Item__typ, 6, form);
		}
	} else if (xform == 1) {
		if (__IN(form, 0x70, 32)) {
			ByteToInt__29(&*x, x__typ, &t, OPC_Item__typ, form);
		} else if (__IN(form, 0x0180, 32)) {
			RealToInt__39(&*x, x__typ, &t, OPC_Item__typ, xform, form);
		} else {
			__HALT(40);
		}
	} else if ((form == 14 && xform != 12)) {
		__HALT(40);
	}
	OPC_ChangeType(&*x, x__typ, form);
	Convert__28_s = _s.lnk;
}

static struct Include__77 {
	struct Include__77 *lnk;
} *Include__77_s;

static INT32 exp2__78 (INT32 x);

static INT32 exp2__78 (INT32 x)
{
	INT32 i;
	__ASSERT(x >= 0, 0);
	i = 1;
	while (x > 0) {
		i = __ASHL(i, 1);
		x -= 1;
	}
	return i;
}

void OPC_Include (OPC_Item *z, ADDRESS *z__typ, OPC_Item *x, ADDRESS *x__typ, BOOLEAN incl)
{
	OPC_Item y, v;
	struct Include__77 _s;
	_s.lnk = Include__77_s;
	Include__77_s = &_s;
	v = *z;
	OPC_load(&v, OPC_Item__typ);
	y = v;
	if (incl) {
		if ((*x).mode == 3) {
			if ((*x).adr == 31) {
				(*x).adr = (-2147483647-1);
			} else {
				(*x).adr = exp2__78((*x).adr);
			}
			OPC_Gen3(672, &v, OPC_Item__typ, &y, OPC_Item__typ, &*x, x__typ);
		} else {
			if ((*x).typ->form != 6) {
				OPC_Convert(&*x, x__typ, 6);
			}
			OPC_load(&*x, x__typ);
			OPC_Gen3(800, &v, OPC_Item__typ, &y, OPC_Item__typ, &*x, x__typ);
		}
	} else {
		if ((*x).mode == 3) {
			if ((*x).adr == 31) {
				(*x).adr = 2147483647;
			} else {
				(*x).adr = -1 - exp2__78((*x).adr);
			}
			OPC_Gen3(736, &v, OPC_Item__typ, &y, OPC_Item__typ, &*x, x__typ);
		} else {
			if ((*x).typ->form != 6) {
				OPC_Convert(&*x, x__typ, 6);
			}
			OPC_load(&*x, x__typ);
			OPC_Gen3(768, &v, OPC_Item__typ, &y, OPC_Item__typ, &*x, x__typ);
		}
	}
	if ((*z).mode == 2) {
		OPC_loadAdr(&*z, z__typ);
		(*z).mode = 17;
	} else {
		OPC_CompleteSL(&*z, z__typ);
	}
	OPC_GenStore(416, &*z, z__typ, &v, OPC_Item__typ);
	Include__77_s = _s.lnk;
}

static void OPC_MoveCoc (OPC_Item *z, ADDRESS *z__typ, OPC_Item *y, ADDRESS *y__typ)
{
	INT32 L;
	OPC_Item phiItem;
	__ASSERT((*y).mode == 18, 0);
	if (((*y).offs == -1 && (*y).inx == -1)) {
		OPC_GenSetC((INT16)((1120 + (*y).adr) - 1504), &*z, z__typ);
	} else {
		OPC_Jncc(&*y, y__typ, &(*y).inx, NIL);
		OPC_GenLoad(32, &*z, z__typ, &OPC_True, OPC_Item__typ);
		phiItem = *z;
		L = -1;
		OPC_Jmp(&L, NIL);
		OPC_FixLink((*y).inx);
		OPC_GenLoad(32, &*z, z__typ, &OPC_False, OPC_Item__typ);
		OPC_GenPhi(phiItem.adr, (*z).adr);
		OPC_FixLink(L);
	}
}

void OPC_Relation (OPC_Item *x, ADDRESS *x__typ)
{
	OPC_Item y;
	if ((*x).mode == 18) {
		y = *x;
		OPC_MoveCoc(&*x, x__typ, &y, OPC_Item__typ);
	}
}

void OPC_Cmp (OPC_Item *z, ADDRESS *z__typ, OPC_Item *x, ADDRESS *x__typ, OPC_Item *y, ADDRESS *y__typ, INT16 rel)
{
	INT16 xform;
	OPC_Item s, t;
	xform = (*x).typ->form;
	if ((xform == 14 && (*x).typ->sysflag == 5) || ((*y).typ->form == 14 && (*y).typ->sysflag == 5)) {
		if ((*x).mode == 3) {
			(*y).typ->sysflag = 0;
			OPC_load(&*y, y__typ);
			(*y).typ->sysflag = 5;
			OPC_GenFlags(1056, &*y, y__typ, &*x, x__typ);
		} else if ((*y).mode == 3) {
			(*x).typ->sysflag = 0;
			OPC_load(&*x, x__typ);
			(*x).typ->sysflag = 5;
			OPC_GenFlags(1056, &*x, x__typ, &*y, y__typ);
		} else {
			OPC_load(&*x, x__typ);
			OPC_load(&*y, y__typ);
			OPC_GenFlags(1056, &*x, x__typ, &*y, y__typ);
			OPC_SetCC(&*z, z__typ, OPC_CCtab[1][__X(rel - 9, 6)]);
			OPC_Gen1(1536, -1, NIL);
			if (rel == 9) {
				(*z).inx = -2 - (OPC_pc - 1);
			} else if (rel == 10) {
				(*z).offs = -2 - (OPC_pc - 1);
			} else {
				__HALT(99);
			}
			s = *x;
			s.adr = s.descReg;
			t = *y;
			t.adr = t.descReg;
			OPC_GenFlags(1056, &s, OPC_Item__typ, &t, OPC_Item__typ);
			return;
		}
	} else if (__IN(xform, 0x6a7a, 32)) {
		OPC_load(&*x, x__typ);
		if ((*y).mode != 3) {
			OPC_load(&*y, y__typ);
		}
		OPC_GenFlags(1056, &*x, x__typ, &*y, y__typ);
	} else if (__IN(xform, 0x0180, 32)) {
		OPC_loadf(&*y, y__typ);
		OPC_loadf(&*x, x__typ);
		OPC_GenFlags(2848, &*x, x__typ, &*y, y__typ);
	} else if (xform == 2) {
		OPC_load(&*x, x__typ);
		if ((*y).mode == 18) {
			__GUARDEQR(z, z__typ, OPC_Item) = *y;
			OPC_MoveCoc(&*y, y__typ, &*z, z__typ);
		} else if ((*y).mode != 3) {
			OPC_load(&*y, y__typ);
		}
		OPC_GenFlags(1056, &*x, x__typ, &*y, y__typ);
	} else {
		__ASSERT(xform == 10 || __IN((*x).typ->comp, 0x3c, 32), 0);
		OPC_loadAdr(&*x, x__typ);
		OPC_loadAdr(&*y, y__typ);
		OPC_GenFlags(2336, &*x, x__typ, &*y, y__typ);
		xform = 10;
	}
	__ASSERT(__IN(rel, 0x7e00, 32), 0);
	if (__IN(xform, 0x0588, 32)) {
		OPC_SetCC(&*z, z__typ, OPC_CCtab[1][__X(rel - 9, 6)]);
	} else {
		OPC_SetCC(&*z, z__typ, OPC_CCtab[0][__X(rel - 9, 6)]);
	}
}

void OPC_In (OPC_Item *z, ADDRESS *z__typ, OPC_Item *x, ADDRESS *x__typ, OPC_Item *y, ADDRESS *y__typ)
{
	OPC_Item t;
	if (((*y).mode != 3 && (*y).typ->form != 9)) {
		t = *y;
		OPC_SetElem(&*y, y__typ, &t, OPC_Item__typ);
	} else {
		OPC_load(&*y, y__typ);
	}
	if ((*x).mode != 3) {
		if ((*x).typ->form != 6) {
			OPC_Convert(&*x, x__typ, 6);
		} else {
			OPC_load(&*x, x__typ);
		}
		OPC_GenFlags(1088, &*y, y__typ, &*x, x__typ);
		OPC_SetCC(&*z, z__typ, 1824);
	} else {
		(*x).adr = __LSH(1, (*x).adr, 32);
		(*x).typ = OPT_linttyp;
		OPC_GenFlags(3424, &*y, y__typ, &*x, x__typ);
		OPC_SetCC(&*z, z__typ, 1536);
	}
}

void OPC_SetRange (OPC_Item *z, ADDRESS *z__typ, OPC_Item *x, ADDRESS *x__typ, OPC_Item *y, ADDRESS *y__typ)
{
	OPC_Item t, xShifted, yShifted, maxSet, fullSet;
	INT32 val;
	(*z).typ = OPT_settyp;
	OPC_MakeCon(&fullSet, OPC_Item__typ, OPT_linttyp, -1);
	OPC_MakeCon(&maxSet, OPC_Item__typ, OPT_linttyp, 31);
	if ((*x).mode == 3) {
		__ASSERT((*y).mode != 3, 0);
		OPC_load(&*y, y__typ);
		maxSet.typ = (*y).typ;
		OPC_load(&maxSet, OPC_Item__typ);
		t = *y;
		OPC_Gen3(544, &*y, y__typ, &maxSet, OPC_Item__typ, &t, OPC_Item__typ);
		OPC_load(&fullSet, OPC_Item__typ);
		OPC_Gen3(896, &*z, z__typ, &fullSet, OPC_Item__typ, &*y, y__typ);
		if ((*x).adr != 0) {
			if ((*x).adr == 31) {
				(*x).adr = (-2147483647-1);
			} else {
				val = 2;
				while ((*x).adr > 1) {
					val = __ASHL(val, 1);
					(*x).adr -= 1;
				}
				(*x).adr = -val;
			}
			t = *z;
			OPC_Gen3(736, &*z, z__typ, &t, OPC_Item__typ, &*x, x__typ);
		}
	} else if ((*y).mode == 3) {
		OPC_load(&*x, x__typ);
		OPC_load(&fullSet, OPC_Item__typ);
		OPC_Gen3(832, &*z, z__typ, &fullSet, OPC_Item__typ, &*x, x__typ);
		if ((*y).adr != 31) {
			if ((*y).adr == 30) {
				(*y).adr = 2147483647;
			} else {
				val = 2;
				while ((*y).adr > 0) {
					val = __ASHL(val, 1);
					(*y).adr -= 1;
				}
				(*y).adr = val - 1;
			}
			t = *z;
			OPC_Gen3(736, &*z, z__typ, &t, OPC_Item__typ, &*y, y__typ);
		}
	} else {
		OPC_load(&*x, x__typ);
		t = fullSet;
		OPC_load(&t, OPC_Item__typ);
		xShifted.typ = OPT_linttyp;
		xShifted.node = NIL;
		OPC_Gen3(832, &xShifted, OPC_Item__typ, &t, OPC_Item__typ, &*x, x__typ);
		OPC_load(&*y, y__typ);
		maxSet.typ = (*y).typ;
		OPC_load(&maxSet, OPC_Item__typ);
		t = *y;
		OPC_Gen3(544, &*y, y__typ, &maxSet, OPC_Item__typ, &t, OPC_Item__typ);
		OPC_load(&fullSet, OPC_Item__typ);
		yShifted.typ = OPT_linttyp;
		yShifted.node = NIL;
		OPC_Gen3(896, &yShifted, OPC_Item__typ, &fullSet, OPC_Item__typ, &*y, y__typ);
		OPC_Gen3(736, &*z, z__typ, &xShifted, OPC_Item__typ, &yShifted, OPC_Item__typ);
	}
}

void OPC_Not (OPC_Item *z, ADDRESS *z__typ, OPC_Item *x, ADDRESS *x__typ)
{
	INT32 temp;
	if ((*x).mode == 18) {
		__GUARDEQR(z, z__typ, OPC_Item) = *x;
		(*z).adr = OPC_InvCCtab[__X(__ASHR((*z).adr - 1504, 5), 12)];
		temp = (*z).offs;
		(*z).offs = (*z).inx;
		(*z).inx = temp;
	} else {
		OPC_load(&*x, x__typ);
		OPC_GenFlags(1056, &*x, x__typ, &OPC_False, OPC_Item__typ);
		OPC_SetCC(&*z, z__typ, 1504);
	}
}

void OPC_Neg (OPC_Item *z, ADDRESS *z__typ, OPC_Item *x, ADDRESS *x__typ)
{
	__ASSERT(((*x).typ->form == 9 || __IN((*x).typ->form, 0x70, 32)) || __IN((*x).typ->form, 0x0180, 32), 0);
	if ((*x).typ->form == 9) {
		OPC_load(&*x, x__typ);
		OPC_Gen2(1024, &*z, z__typ, &*x, x__typ);
	} else if (__IN((*x).typ->form, 0x70, 32)) {
		OPC_load(&*x, x__typ);
		OPC_Gen2(960, &*z, z__typ, &*x, x__typ);
	} else {
		OPC_loadf(&*x, x__typ);
		OPC_Gen2(2816, &*z, z__typ, &*x, x__typ);
	}
}

void OPC_AbsVal (OPC_Item *z, ADDRESS *z__typ, OPC_Item *x, ADDRESS *x__typ)
{
	__ASSERT(__IN((*x).typ->form, 0x70, 32) || __IN((*x).typ->form, 0x0180, 32), 0);
	if (__IN((*x).typ->form, 0x70, 32)) {
		OPC_load(&*x, x__typ);
		OPC_Gen2(992, &*z, z__typ, &*x, x__typ);
		if (__IN((*x).typ->form, 0x60, 32)) {
			(OPL_Instr->data)[__X(OPC_pc - 1, OPL_Instr->len[0])].hint = 0;
		}
	} else {
		OPC_loadf(&*x, x__typ);
		OPC_Gen2(2784, &*z, z__typ, &*x, x__typ);
	}
}

void OPC_Cap (OPC_Item *z, ADDRESS *z__typ, OPC_Item *x, ADDRESS *x__typ)
{
	OPC_Item c;
	OPC_MakeCon(&c, OPC_Item__typ, OPT_chartyp, 95);
	OPC_load(&*x, x__typ);
	OPC_Gen3(736, &*z, z__typ, &*x, x__typ, &c, OPC_Item__typ);
}

void OPC_Odd (OPC_Item *z, ADDRESS *z__typ, OPC_Item *x, ADDRESS *x__typ)
{
	OPC_Item c;
	OPC_MakeCon(&c, OPC_Item__typ, OPT_sinttyp, 1);
	OPC_load(&*x, x__typ);
	OPC_Gen3(736, &*z, z__typ, &*x, x__typ, &c, OPC_Item__typ);
}

void OPC_Ash (OPC_Item *z, ADDRESS *z__typ, OPC_Item *x, ADDRESS *x__typ, OPC_Item *y, ADDRESS *y__typ)
{
	INT32 L, Lc;
	OPC_Item t, phiItem;
	if ((*y).mode == 3) {
		if ((*x).mode == 3) {
			OPC_MakeCon(&*z, z__typ, OPT_linttyp, __ASH((*x).adr, (*y).adr));
		} else if ((*y).adr > 0) {
			OPC_load(&*x, x__typ);
			OPC_Gen3(832, &*z, z__typ, &*x, x__typ, &*y, y__typ);
		} else if ((*y).adr < 0) {
			(*y).adr = __ABS((*y).adr);
			OPC_load(&*x, x__typ);
			OPC_Gen3(864, &*z, z__typ, &*x, x__typ, &*y, y__typ);
		}
	} else {
		OPC_load(&*x, x__typ);
		OPC_load(&*y, y__typ);
		(*z).typ = OPT_linttyp;
		OPC_MakeCon(&t, OPC_Item__typ, OPT_linttyp, 0);
		OPC_GenFlags(1056, &*y, y__typ, &t, OPC_Item__typ);
		Lc = -2 - OPC_pc;
		OPC_Gen1(1568, -1, NIL);
		OPC_Gen3(832, &*z, z__typ, &*x, x__typ, &*y, y__typ);
		L = -2 - OPC_pc;
		OPC_Gen1(1888, -1, NIL);
		phiItem = *z;
		OPC_FixLink(Lc);
		OPC_Gen2(960, &t, OPC_Item__typ, &*y, y__typ);
		OPC_Gen3(864, &*z, z__typ, &*x, x__typ, &t, OPC_Item__typ);
		OPC_GenPhi(phiItem.adr, (*z).adr);
		OPC_FixLink(L);
	}
}

void OPC_Add (OPC_Item *z, ADDRESS *z__typ, OPC_Item *x, ADDRESS *x__typ, OPC_Item *y, ADDRESS *y__typ, INT16 f)
{
	__ASSERT((__IN(f, 0x0180, 32) || f == 9) || __IN(f, 0x70, 32), 0);
	if (__IN(f, 0x0180, 32)) {
		OPC_loadf(&*x, x__typ);
		OPC_loadf(&*y, y__typ);
		OPC_Gen3(2656, &*z, z__typ, &*x, x__typ, &*y, y__typ);
	} else if (f == 9) {
		if ((*x).mode == 3) {
			OPC_load(&*y, y__typ);
			OPC_Gen3(672, &*z, z__typ, &*y, y__typ, &*x, x__typ);
		} else {
			OPC_load(&*x, x__typ);
			if ((*y).mode != 3) {
				OPC_load(&*y, y__typ);
			}
			OPC_Gen3(672, &*z, z__typ, &*x, x__typ, &*y, y__typ);
		}
	} else {
		if ((*x).mode == 3) {
			OPC_load(&*y, y__typ);
			OPC_Gen3(512, &*z, z__typ, &*y, y__typ, &*x, x__typ);
		} else {
			OPC_load(&*x, x__typ);
			if ((*y).mode != 3) {
				OPC_load(&*y, y__typ);
			}
			OPC_Gen3(512, &*z, z__typ, &*x, x__typ, &*y, y__typ);
		}
		OPC_CheckOverflow(&*z, z__typ);
	}
}

void OPC_Sub (OPC_Item *z, ADDRESS *z__typ, OPC_Item *x, ADDRESS *x__typ, OPC_Item *y, ADDRESS *y__typ, INT16 f)
{
	OPC_Item t;
	__ASSERT((__IN(f, 0x0180, 32) || f == 9) || __IN(f, 0x70, 32), 0);
	if (__IN(f, 0x0180, 32)) {
		OPC_loadf(&*x, x__typ);
		OPC_loadf(&*y, y__typ);
		OPC_Gen3(2688, &*z, z__typ, &*x, x__typ, &*y, y__typ);
	} else if (f == 9) {
		OPC_load(&*x, x__typ);
		if ((*y).mode != 3) {
			OPC_load(&*y, y__typ);
			OPC_Gen2(1024, &t, OPC_Item__typ, &*y, y__typ);
		} else {
			(*y).adr = -1 - (*y).adr;
			t = *y;
		}
		__GUARDEQR(z, z__typ, OPC_Item) = *x;
		OPC_Gen3(736, &*z, z__typ, &*x, x__typ, &t, OPC_Item__typ);
	} else {
		OPC_load(&*x, x__typ);
		if ((*y).mode != 3) {
			OPC_load(&*y, y__typ);
		}
		OPC_Gen3(544, &*z, z__typ, &*x, x__typ, &*y, y__typ);
		OPC_CheckOverflow(&*z, z__typ);
	}
}

void OPC_Mul (OPC_Item *z, ADDRESS *z__typ, OPC_Item *x, ADDRESS *x__typ, OPC_Item *y, ADDRESS *y__typ, INT16 f)
{
	INT32 val, exp;
	OPC_Item shift;
	__ASSERT((f == 9 || __IN(f, 0x70, 32)) || __IN(f, 0x0180, 32), 0);
	if (__IN(f, 0x0180, 32)) {
		OPC_loadf(&*x, x__typ);
		OPC_loadf(&*y, y__typ);
		OPC_Gen3(2720, &*z, z__typ, &*x, x__typ, &*y, y__typ);
	} else if (f == 9) {
		if ((*x).mode == 3) {
			OPC_load(&*y, y__typ);
			OPC_Gen3(736, &*z, z__typ, &*y, y__typ, &*x, x__typ);
		} else {
			OPC_load(&*x, x__typ);
			if (((*y).mode != 15 && (*y).mode != 3)) {
				OPC_load(&*y, y__typ);
			}
			OPC_Gen3(736, &*z, z__typ, &*x, x__typ, &*y, y__typ);
		}
	} else {
		OPC_MakeCon(&shift, OPC_Item__typ, OPT_linttyp, 0);
		if ((*x).mode == 3) {
			val = (*x).adr;
			exp = 0;
			__ASSERT(val != 0, 0);
			while (!__ODD(val)) {
				val = __ASHR(val, 1);
				exp += 1;
			}
			OPC_load(&*y, y__typ);
			if ((val == 1 && !__IN(1, OPM_codeOptions, 32))) {
				if (exp != 0) {
					shift.adr = exp;
					OPC_Gen3(832, &*z, z__typ, &*y, y__typ, &shift, OPC_Item__typ);
				} else {
					__GUARDEQR(z, z__typ, OPC_Item) = *y;
				}
			} else {
				OPC_Gen3(576, &*z, z__typ, &*y, y__typ, &*x, x__typ);
			}
		} else if ((*y).mode == 3) {
			val = (*y).adr;
			exp = 0;
			__ASSERT(val != 0, 0);
			while (!__ODD(val)) {
				val = __ASHR(val, 1);
				exp += 1;
			}
			OPC_load(&*x, x__typ);
			if ((val == 1 && !__IN(1, OPM_codeOptions, 32))) {
				if (exp != 0) {
					shift.adr = exp;
					OPC_Gen3(832, &*z, z__typ, &*x, x__typ, &shift, OPC_Item__typ);
				} else {
					__GUARDEQR(z, z__typ, OPC_Item) = *x;
				}
			} else {
				OPC_Gen3(576, &*z, z__typ, &*x, x__typ, &*y, y__typ);
			}
		} else {
			OPC_load(&*x, x__typ);
			OPC_load(&*y, y__typ);
			OPC_Gen3(576, &*z, z__typ, &*x, x__typ, &*y, y__typ);
		}
		OPC_CheckOverflow(&*z, z__typ);
	}
}

void OPC_Div (OPC_Item *z, ADDRESS *z__typ, OPC_Item *x, ADDRESS *x__typ, OPC_Item *y, ADDRESS *y__typ, INT16 f)
{
	__ASSERT((__IN(f, 0x0180, 32) || f == 9) || __IN(f, 0x70, 32), 0);
	if (__IN(f, 0x0180, 32)) {
		OPC_loadf(&*x, x__typ);
		OPC_loadf(&*y, y__typ);
		OPC_Gen3(2752, &*z, z__typ, &*x, x__typ, &*y, y__typ);
	} else if (f == 9) {
		if ((*x).mode == 3) {
			OPC_load(&*y, y__typ);
			OPC_Gen3(704, &*z, z__typ, &*y, y__typ, &*x, x__typ);
		} else {
			OPC_load(&*x, x__typ);
			if (((*y).mode != 15 && (*y).mode != 3)) {
				OPC_load(&*y, y__typ);
			}
			OPC_Gen3(704, &*z, z__typ, &*x, x__typ, &*y, y__typ);
		}
	} else {
		OPC_load(&*x, x__typ);
		if ((*y).mode != 3) {
			OPC_load(&*y, y__typ);
		}
		OPC_Gen3(608, &*z, z__typ, &*x, x__typ, &*y, y__typ);
	}
}

void OPC_Mod (OPC_Item *z, ADDRESS *z__typ, OPC_Item *x, ADDRESS *x__typ, OPC_Item *y, ADDRESS *y__typ)
{
	OPC_load(&*x, x__typ);
	if ((*y).mode != 3) {
		OPC_load(&*y, y__typ);
	}
	OPC_Gen3(640, &*z, z__typ, &*x, x__typ, &*y, y__typ);
}

void OPC_CondAnd (OPC_Item *x, ADDRESS *x__typ)
{
	INT16 jcc;
	if ((*x).mode == 18) {
		jcc = OPC_InvCCtab[__X(__ASHR((*x).adr - 1504, 5), 12)];
	} else {
		__ASSERT(((*x).typ->form == 2 && (*x).mode != 3), 0);
		OPC_load(&*x, x__typ);
		OPC_GenFlags(1056, &*x, x__typ, &OPC_True, OPC_Item__typ);
		OPC_SetCC(&*x, x__typ, 1536);
		jcc = 1536;
	}
	OPC_Gen1(jcc, (*x).inx, NIL);
	(*x).inx = -2 - (OPC_pc - 1);
	OPC_FixLink((*x).offs);
}

void OPC_And (OPC_Item *z, ADDRESS *z__typ, OPC_Item *x, ADDRESS *x__typ, OPC_Item *y, ADDRESS *y__typ)
{
	__GUARDEQR(z, z__typ, OPC_Item) = *x;
	if ((*y).mode != 18) {
		if ((*y).mode == 3) {
			if ((*y).adr == 1) {
				OPC_SetCC(&*y, y__typ, 1888);
			} else {
				OPC_SetCC(&*y, y__typ, -1);
			}
		} else {
			OPC_load(&*y, y__typ);
			OPC_GenFlags(1056, &*y, y__typ, &OPC_True, OPC_Item__typ);
			OPC_SetCC(&*y, y__typ, 1504);
		}
	}
	if ((*y).inx != -1) {
		(*z).inx = OPC_MergedLinks((*z).inx, (*y).inx);
	}
	(*z).adr = (*y).adr;
	(*z).offs = (*y).offs;
}

void OPC_CondOr (OPC_Item *x, ADDRESS *x__typ)
{
	INT16 jcc;
	if ((*x).mode == 18) {
		jcc = (INT16)(*x).adr;
	} else {
		__ASSERT(((*x).typ->form == 2 && (*x).mode != 3), 0);
		OPC_load(&*x, x__typ);
		OPC_GenFlags(1056, &*x, x__typ, &OPC_True, OPC_Item__typ);
		OPC_SetCC(&*x, x__typ, 1504);
		jcc = 1504;
	}
	OPC_Gen1(jcc, (*x).offs, NIL);
	(*x).offs = -2 - (OPC_pc - 1);
	OPC_FixLink((*x).inx);
}

void OPC_Or (OPC_Item *z, ADDRESS *z__typ, OPC_Item *x, ADDRESS *x__typ, OPC_Item *y, ADDRESS *y__typ)
{
	__GUARDEQR(z, z__typ, OPC_Item) = *x;
	if ((*y).mode != 18) {
		if ((*y).mode == 3) {
			if ((*y).adr == 1) {
				OPC_SetCC(&*y, y__typ, 1888);
			} else {
				OPC_SetCC(&*y, y__typ, -1);
			}
		} else {
			OPC_load(&*y, y__typ);
			OPC_GenFlags(1056, &*y, y__typ, &OPC_True, OPC_Item__typ);
			OPC_SetCC(&*y, y__typ, 1504);
		}
	}
	if ((*y).offs != -1) {
		(*z).offs = OPC_MergedLinks((*x).offs, (*y).offs);
	}
	(*z).adr = (*y).adr;
	(*z).inx = (*y).inx;
}

void OPC_SYSmop (OPC_Item *z, ADDRESS *z__typ, OPC_Item *x, ADDRESS *x__typ, INT8 subcl, OPT_Struct typ)
{
	INT8 xform, typform;
	OPC_Item t, const_;
	switch (subcl) {
		case 24: 
			OPC_loadAdr(&*z, z__typ);
			break;
		case 25: 
			__GUARDEQR(z, z__typ, OPC_Item) = *x;
			OPM_err(200);
			break;
		case 29: 
			xform = (*x).typ->form;
			typform = typ->form;
			OPC_MakeCon(&const_, OPC_Item__typ, OPT_linttyp, 4);
			if ((((__IN(xform, 0x627a, 32) && __IN(typform, 0x0180, 32))) && (*x).mode == 15)) {
				OPC_GenPush(&*x, x__typ);
				t.mode = 17;
				t.adr = -3;
				t.offs = 0;
				t.inx = -1;
				t.typ = OPT_realtyp;
				t.node = NIL;
				OPC_GenLoad(2528, &*z, z__typ, &t, OPC_Item__typ);
				t = OPC_Stack;
				OPC_Gen3(512, &t, OPC_Item__typ, &t, OPC_Item__typ, &const_, OPC_Item__typ);
			} else if ((((__IN(xform, 0x0180, 32) && __IN(typform, 0x627a, 32))) && (*x).mode == 15)) {
				t = OPC_Stack;
				OPC_Gen3(544, &t, OPC_Item__typ, &t, OPC_Item__typ, &const_, OPC_Item__typ);
				t.mode = 17;
				t.adr = -3;
				t.offs = 0;
				t.inx = -1;
				t.typ = OPT_realtyp;
				t.node = NIL;
				OPC_loadf(&*x, x__typ);
				OPC_GenStore(2560, &t, OPC_Item__typ, &*x, x__typ);
				t.typ = typ;
				OPC_GenLoad(32, &*z, z__typ, &t, OPC_Item__typ);
				t = OPC_Stack;
				OPC_Gen3(512, &t, OPC_Item__typ, &t, OPC_Item__typ, &const_, OPC_Item__typ);
			} else if ((((typform == 14 && typ->sysflag == 5)) && xform != 14)) {
				__GUARDEQR(z, z__typ, OPC_Item) = *x;
				OPC_load(&*z, z__typ);
				OPC_MakeCon(&t, OPC_Item__typ, OPT_linttyp, 0);
				OPC_load(&t, OPC_Item__typ);
				(*z).descReg = t.adr;
				(*z).typ = typ;
			}
			if (((*z).typ->size != typ->size && ((*x).mode != 3 || typ->size > 4))) {
				OPM_err(-304);
			}
			(*z).typ = typ;
			break;
		case 30: case 31: case 32: 
			OPC_load(&*z, z__typ);
			(*z).mode = 17;
			(*z).offs = 0;
			(*z).inx = -1;
			(*z).typ = typ;
			OPC_load(&*z, z__typ);
			break;
		default: __CASECHK;
	}
}

static void OPC_Mem (OPC_Item *x, ADDRESS *x__typ)
{
	if ((*x).mode == 3) {
		(*x).mode = 16;
		(*x).inx = -1;
	} else {
		OPC_load(&*x, x__typ);
		(*x).mode = 17;
		(*x).offs = 0;
		(*x).inx = -1;
	}
}

void OPC_SYSdop (OPC_Item *z, ADDRESS *z__typ, OPC_Item *x, ADDRESS *x__typ, OPC_Item *y, ADDRESS *y__typ, INT8 subcl)
{
	OPC_Item t, phiItem;
	INT32 L, Lc;
	switch (subcl) {
		case 26: 
			OPC_Mem(&*x, x__typ);
			OPC_load(&*x, x__typ);
			if ((*y).mode != 3) {
				OPC_load(&*y, y__typ);
			}
			OPC_GenFlags(1088, &*x, x__typ, &*y, y__typ);
			OPC_GenSetC(1440, &*z, z__typ);
			break;
		case 27: 
			if ((*y).mode == 3) {
				if ((*x).mode == 3) {
					OPC_MakeCon(&*z, z__typ, OPT_linttyp, __LSH((*x).adr, (*y).adr, 32));
				} else if ((*y).adr > 0) {
					OPC_load(&*x, x__typ);
					OPC_Gen3(832, &*z, z__typ, &*x, x__typ, &*y, y__typ);
				} else if ((*y).adr < 0) {
					(*y).adr = __ABS((*y).adr);
					OPC_load(&*x, x__typ);
					OPC_Gen3(896, &*z, z__typ, &*x, x__typ, &*y, y__typ);
				}
			} else {
				OPC_load(&*x, x__typ);
				OPC_load(&*y, y__typ);
				OPC_MakeCon(&t, OPC_Item__typ, OPT_linttyp, 0);
				OPC_GenFlags(1056, &*y, y__typ, &t, OPC_Item__typ);
				Lc = -2 - OPC_pc;
				OPC_Gen1(1568, -1, NIL);
				OPC_Gen3(832, &*z, z__typ, &*x, x__typ, &*y, y__typ);
				phiItem = *z;
				L = -2 - OPC_pc;
				OPC_Gen1(1888, -1, NIL);
				OPC_FixLink(Lc);
				OPC_Gen2(960, &t, OPC_Item__typ, &*y, y__typ);
				OPC_Gen3(896, &*z, z__typ, &*x, x__typ, &t, OPC_Item__typ);
				OPC_GenPhi(phiItem.adr, (*z).adr);
				OPC_FixLink(L);
			}
			break;
		case 28: 
			if ((*y).mode == 3) {
				if ((*x).mode == 3) {
					OPC_MakeCon(&*z, z__typ, (*x).typ, 0);
					switch ((*x).typ->form) {
						case 1: case 3: case 4: 
							(*z).adr = __ROT(__VAL(INT8, (*x).adr), (INT16)(*y).adr, 8);
							break;
						case 5: 
							(*z).adr = __ROT(__VAL(INT16, (*x).adr), (INT16)(*y).adr, 16);
							break;
						case 6: 
							(*z).adr = __ROT((*x).adr, (INT16)(*y).adr, 32);
							break;
						default: __CASECHK;
					}
				} else {
					OPC_load(&*x, x__typ);
					OPC_Gen3(928, &*z, z__typ, &*x, x__typ, &*y, y__typ);
				}
			} else {
				OPC_load(&*x, x__typ);
				OPC_load(&*y, y__typ);
				OPC_Gen3(928, &*z, z__typ, &*x, x__typ, &*y, y__typ);
			}
			break;
		default: __CASECHK;
	}
}

void OPC_SYSgetput (OPC_Item *z, ADDRESS *z__typ, OPC_Item *x, ADDRESS *x__typ, BOOLEAN getfn)
{
	INT8 form;
	BOOLEAN constAddr;
	if (getfn) {
		constAddr = (*x).mode == 3;
		OPC_Mem(&*x, x__typ);
		(*x).typ = (*z).typ;
		form = (*z).typ->form;
	} else {
		constAddr = (*z).mode == 3;
		OPC_Mem(&*z, z__typ);
		(*z).typ = (*x).typ;
		form = (*x).typ->form;
	}
	if (__IN(form, 0x0180, 32)) {
		OPC_loadf(&*x, x__typ);
	} else {
		OPC_load(&*x, x__typ);
	}
	(OPL_Instr->data)[__X(OPC_pc - 1, OPL_Instr->len[0])].abs = (constAddr && getfn);
	if ((*z).mode == 2) {
		OPC_loadAdr(&*z, z__typ);
		(*z).mode = 17;
	} else {
		OPC_CompleteSL(&*z, z__typ);
	}
	if (__IN(form, 0x0180, 32)) {
		OPC_GenStore(2560, &*z, z__typ, &*x, x__typ);
	} else {
		OPC_GenStore(416, &*z, z__typ, &*x, x__typ);
	}
	(OPL_Instr->data)[__X(OPC_pc - 1, OPL_Instr->len[0])].abs = (constAddr && !getfn);
}

void OPC_SYSportio (OPC_Item *z, ADDRESS *z__typ, OPC_Item *x, ADDRESS *x__typ, BOOLEAN pin)
{
	OPC_Item reg;
	reg.mode = 15;
	reg.node = NIL;
	if (pin) {
		if ((*x).mode != 15) {
			OPC_load(&*x, x__typ);
		}
		(OPL_Instr->data)[__X((*x).adr, OPL_Instr->len[0])].hint = 2;
		__ASSERT(((*x).mode == 15 && (*x).typ == OPT_inttyp), 0);
		(*x).typ = (*z).typ;
		OPC_GenLoad(3232, &reg, OPC_Item__typ, &*x, x__typ);
		(OPL_Instr->data)[__X(OPC_pc - 1, OPL_Instr->len[0])].hint = 0;
		if ((*z).mode == 2) {
			OPC_loadAdr(&*z, z__typ);
			(*z).mode = 17;
		} else {
			OPC_CompleteSL(&*z, z__typ);
		}
		OPC_GenStore(416, &*z, z__typ, &reg, OPC_Item__typ);
	} else {
		if ((*z).mode != 15) {
			OPC_load(&*z, z__typ);
		}
		(OPL_Instr->data)[__X((*z).adr, OPL_Instr->len[0])].hint = 2;
		__ASSERT((*z).mode == 15, 0);
		if ((*x).mode == 2) {
			OPC_loadAdr(&*x, x__typ);
			(*x).mode = 17;
		} else {
			OPC_CompleteSL(&*x, x__typ);
		}
		if ((*x).mode != 15) {
			OPC_GenLoad(32, &*x, x__typ, &*x, x__typ);
		}
		(OPL_Instr->data)[__X((*x).adr, OPL_Instr->len[0])].hint = 0;
		__ASSERT((*x).mode == 15, 0);
		OPC_GenLoad(3264, &reg, OPC_Item__typ, &*x, x__typ);
		(OPL_Instr->data)[__X(OPC_pc - 1, OPL_Instr->len[0])].dest = (*z).adr;
	}
}

void OPC_SYSgetputReg (OPC_Item *z, ADDRESS *z__typ, OPC_Item *x, ADDRESS *x__typ, BOOLEAN getrfn)
{
	OPC_Item reg;
	reg.mode = 15;
	reg.node = NIL;
	__ASSERT((*x).typ != OPT_lrltyp, 0);
	if (getrfn) {
		if ((*z).typ == OPT_realtyp) {
			(*z).typ = OPT_linttyp;
		}
		reg.adr = (*x).adr;
		reg.typ = (*z).typ;
		if ((*z).mode == 2) {
			OPC_loadAdr(&*z, z__typ);
			(*z).mode = 17;
		} else {
			OPC_CompleteSL(&*z, z__typ);
		}
		OPC_GenStore(256, &*z, z__typ, &reg, OPC_Item__typ);
		(OPL_Instr->data)[__X(OPC_pc - 1, OPL_Instr->len[0])].hint = (*x).adr;
	} else {
		if ((*x).typ == OPT_realtyp) {
			(*x).typ = OPT_linttyp;
		}
		if ((*x).mode == 3) {
			(*x).typ = OPT_linttyp;
		} else if ((*x).mode == 2) {
			OPC_loadAdr(&*x, x__typ);
			(*x).mode = 17;
		} else {
			OPC_CompleteSL(&*x, x__typ);
		}
		OPC_GenLoad(288, &reg, OPC_Item__typ, &*x, x__typ);
		(OPL_Instr->data)[__X(OPC_pc - 1, OPL_Instr->len[0])].hint = (*z).adr;
	}
}

void OPC_SYSinterrupt (BOOLEAN clear)
{
	if (clear) {
		OPC_Gen0(3168);
	} else {
		OPC_Gen0(3200);
	}
}

void OPC_Msk (OPC_Item *z, ADDRESS *z__typ, OPC_Item *x, ADDRESS *x__typ, OPC_Item *y, ADDRESS *y__typ)
{
	(*y).adr = -1 - (*y).adr;
	OPC_load(&*x, x__typ);
	OPC_Gen3(736, &*z, z__typ, &*x, x__typ, &*y, y__typ);
}

void OPC_Field (OPC_Item *x, ADDRESS *x__typ, INT32 offset)
{
	__ASSERT(__IN((*x).mode, 0x030006, 32), 0);
	if (__IN((*x).mode, 0x010002, 32)) {
		(*x).adr += offset;
	} else if ((*x).mode == 2) {
		OPC_loadAdr(&*x, x__typ);
		(*x).mode = 17;
		(*x).offs = offset;
	} else {
		(*x).offs += offset;
	}
}

void OPC_Method (OPC_Item *x, ADDRESS *x__typ, OPT_Object obj)
{
	INT32 reg;
	__ASSERT(obj->mode == 13, 201);
	(*x).typ = OPT_ptrtyp;
	OPC_loadAdr(&*x, x__typ);
	reg = (*x).adr;
	(*x).mode = 17;
	(*x).offs = -4;
	OPC_load(&*x, x__typ);
	(OPL_Instr->data)[__X(OPC_pc - 1, OPL_Instr->len[0])].hint = 3;
	(*x).mode = 17;
	(*x).offs = -72 - __ASHL(__ASHR(obj->adr, 16), 2);
	OPC_load(&*x, x__typ);
	(*x).descReg = reg;
	(*x).typ = OPC_delegateType;
}

static void OPC_MakeVar (OPC_Item *x, ADDRESS *x__typ, OPT_Object var)
{
	__ASSERT(var->mode == 1, 100);
	(*x).mode = 1;
	(*x).adr = var->linkadr;
	(*x).offs = 0;
	(*x).typ = var->typ;
	(*x).node = NIL;
	(*x).mnolev = var->mnolev;
	(*x).inx = -1;
	if ((*x).typ->comp == 5) {
		(*x).descReg = -2;
		(*x).descOffs = (*x).adr + __ASHL((*x).typ->n + 1, 2);
	} else {
		(*x).descReg = -1;
	}
}

static void OPC_ArrayLen (OPC_Item *len, ADDRESS *len__typ, OPC_Item arr, INT32 n)
{
	OPT_Struct typ;
	INT32 i;
	if (arr.typ->sysflag == 1) {
		OPM_err(200);
	}
	typ = arr.typ;
	i = n;
	while (i > 0) {
		typ = typ->BaseTyp;
		i -= 1;
	}
	__ASSERT(__IN(typ->comp, 0x3c, 32), 100);
	if (typ->comp == 2) {
		OPC_MakeCon(&*len, len__typ, OPT_linttyp, typ->n);
	} else if (typ->comp == 3) {
		__ASSERT(typ->link != NIL, 101);
		OPC_MakeVar(&*len, len__typ, typ->link);
	} else {
		if (arr.descReg == -1) {
			if (typ->comp == 4) {
				OPC_loadDynArr(&arr, OPC_Item__typ);
			} else {
				__ASSERT(__IN(arr.mode, 0x06, 32), 103);
				arr.descReg = -2;
				arr.descOffs = arr.adr + __ASHL(arr.typ->n + 1, 2);
			}
		}
		__ASSERT(arr.descReg != -1, 102);
		if (arr.descReg == -2) {
			(*len).mode = 1;
			(*len).adr = arr.descOffs - __ASHL(n, 2);
			(*len).offs = 0;
		} else {
			(*len).mode = 17;
			(*len).adr = arr.descReg;
			(*len).offs = arr.descOffs - __ASHL(n, 2);
		}
		(*len).typ = OPT_linttyp;
		(*len).node = NIL;
		(*len).mnolev = arr.mnolev;
		(*len).inx = -1;
	}
}

void OPC_Len (OPC_Item *len, ADDRESS *len__typ, OPC_Item *x, ADDRESS *x__typ, OPC_Item *y, ADDRESS *y__typ)
{
	__ASSERT((*y).mode == 3, 100);
	__ASSERT(__IN((*x).typ->comp, 0x30, 32), 101);
	OPC_ArrayLen(&*len, len__typ, *x, (*y).adr);
}

static void OPC_ArrayBaseSize (OPC_Item *len, ADDRESS *len__typ, OPC_Item arr)
{
	OPT_Struct typ;
	INT32 dim;
	OPC_Item t, tt;
	__ASSERT(__IN(arr.typ->comp, 0x3c, 32), 100);
	typ = arr.typ->BaseTyp;
	dim = 1;
	OPC_MakeCon(&*len, len__typ, OPT_linttyp, 1);
	while (__IN(typ->comp, 0x3c, 32)) {
		OPC_ArrayLen(&t, OPC_Item__typ, arr, dim);
		if ((t.mode == 3 && (*len).mode == 3)) {
			(*len).adr = (*len).adr * t.adr;
		} else {
			tt = *len;
			OPC_Mul(&*len, len__typ, &t, OPC_Item__typ, &tt, OPC_Item__typ, 6);
		}
		typ = typ->BaseTyp;
		dim += 1;
	}
	OPC_MakeCon(&t, OPC_Item__typ, OPT_linttyp, typ->size);
	if ((t.mode == 3 && (*len).mode == 3)) {
		(*len).adr = (*len).adr * t.adr;
	} else {
		tt = *len;
		OPC_Mul(&*len, len__typ, &t, OPC_Item__typ, &tt, OPC_Item__typ, 6);
	}
}

static void OPC_TypeSize (OPC_Item x, OPC_Item *size, ADDRESS *size__typ, INT8 *step, INT8 *scale)
{
	OPT_Struct typ;
	INT32 dim, rest;
	OPC_Item t, tt;
	typ = x.typ;
	dim = 0;
	OPC_MakeCon(&*size, size__typ, OPT_linttyp, 1);
	while (__IN(typ->comp, 0x3c, 32)) {
		OPC_ArrayLen(&t, OPC_Item__typ, x, dim);
		if ((t.mode == 3 && (*size).mode == 3)) {
			(*size).adr = (*size).adr * t.adr;
		} else {
			tt = *size;
			OPC_Mul(&*size, size__typ, &t, OPC_Item__typ, &tt, OPC_Item__typ, 6);
		}
		typ = typ->BaseTyp;
		dim += 1;
	}
	if (__MASK(typ->size, -4) == 0) {
		*scale = 2;
		*step = 0;
		rest = __ASHR(typ->size, 2);
	} else if (__MASK(typ->size, -2) == 0) {
		*scale = 1;
		*step = 8;
		rest = __ASHR(typ->size, 1);
	} else {
		*scale = 0;
		*step = 16;
		rest = typ->size;
	}
	if (rest != 0) {
		if ((*size).mode == 3) {
			(*size).adr = (*size).adr * rest;
		} else {
			OPC_MakeCon(&t, OPC_Item__typ, OPT_linttyp, rest);
			tt = *size;
			OPC_Mul(&*size, size__typ, &t, OPC_Item__typ, &tt, OPC_Item__typ, 6);
		}
	}
	__ASSERT(__IN((*size).mode, 0x8008, 32), 110);
}

static void OPC_Length (OPC_Item *len, ADDRESS *len__typ, OPC_Item *x, ADDRESS *x__typ)
{
	if ((*x).typ->form == 10) {
		OPC_MakeCon(&*len, len__typ, OPT_linttyp, (*x).offs);
	} else {
		OPC_ArrayLen(&*len, len__typ, *x, 0);
	}
}

static void OPC_loadDynArr (OPC_Item *z, ADDRESS *z__typ)
{
	__ASSERT((*z).typ->comp == 4, 100);
	__ASSERT((*z).descReg == -1, 101);
	OPC_load(&*z, z__typ);
	(*z).descReg = (*z).adr;
	(*z).descOffs = 12 + __ASHL((*z).typ->n, 2);
	(*z).mode = 17;
	(*z).offs = 16 + __ASHL(__ASHR(1 + (*z).typ->n, 1), 3);
}

void OPC_Index (OPC_Item *z, ADDRESS *z__typ, OPC_Item *index, ADDRESS *index__typ)
{
	OPC_Item t, len, size;
	OPT_Struct typ;
	INT32 scale, comp, check;
	check = (*z).mode;
	__ASSERT(__IN(check, 0x030006, 32), 100);
	typ = (*z).typ;
	comp = typ->comp;
	__ASSERT(__IN(comp, 0x3c, 32), 101);
	if (((*z).descReg == -1 && comp != 2)) {
		__ASSERT((*z).mode != 15, 102);
		if (comp == 4) {
			OPC_loadDynArr(&*z, z__typ);
		} else if ((comp == 3 && (*z).mode != 17)) {
			__ASSERT(__IN((*z).mode, 0x06, 32), 103);
			(*z).mode = 1;
			OPC_load(&*z, z__typ);
			(*z).mode = 17;
			(*z).offs = 0;
		} else if (comp == 5) {
			__ASSERT(__IN((*z).mode, 0x06, 32), 103);
			(*z).descReg = -2;
			(*z).descOffs = (*z).adr + __ASHL((*z).typ->n + 1, 2);
			(*z).mode = 1;
			OPC_load(&*z, z__typ);
			(*z).mode = 17;
			(*z).offs = 0;
		}
	}
	if ((*index).typ->form != 6) {
		OPC_Convert(&*index, index__typ, 6);
	}
	if ((__IN(0, OPM_codeOptions, 32) && ((*index).mode != 3 || comp != 2))) {
		OPC_ArrayLen(&len, OPC_Item__typ, *z, 0);
		OPC_CheckIndex(&*index, index__typ, &len, OPC_Item__typ);
	} else if (!__IN((*index).mode, 0x8008, 32)) {
		OPC_load(&*index, index__typ);
	}
	__ASSERT(__IN((*index).mode, 0x8008, 32), 106);
	__ASSERT(__IN((*z).mode, 0x030006, 32), 107);
	if (((*z).mode == 1 && OPC_level - (*z).mnolev > 0)) {
		OPC_CompleteSL(&*z, z__typ);
	}
	if ((*index).mode != 3 || (*index).adr != 0) {
		OPC_ArrayBaseSize(&size, OPC_Item__typ, *z);
		__ASSERT(__IN(size.mode, 0x8008, 32), 105);
		if ((size.mode == 3 && size.adr == 0)) {
		} else if (((*index).mode == 3 && size.mode == 3)) {
			(*index).adr = (*index).adr * size.adr;
			if ((*z).mode == 16) {
				(*z).adr += (*index).adr;
			} else if ((*z).mode == 1) {
				(*z).adr += (*index).adr;
			} else if ((*z).mode != 17) {
				OPC_loadAdr(&*z, z__typ);
				(*z).mode = 17;
				(*z).offs = (*index).adr;
			} else {
				(*z).offs += (*index).adr;
			}
		} else {
			if ((*z).inx == -1) {
				if ((*z).mode == 1) {
					(*z).mode = 17;
					(*z).offs = (*z).adr;
					(*z).adr = -2;
				} else if ((*z).mode == 2) {
					OPC_loadAdr(&*z, z__typ);
					(*z).mode = 17;
				}
				(*z).inx = (*index).adr;
				(*z).scale = (INT8)((INT16)scale);
			} else {
				OPC_loadAdr(&*z, z__typ);
				(*z).mode = 17;
				(*z).offs = 0;
				(*z).inx = (*index).adr;
				(*z).scale = (INT8)((INT16)scale);
			}
			if ((((size.mode == 3 && size.adr <= 8)) && __IN(size.adr, 0x0116, 32))) {
				switch (size.adr) {
					case 1: 
						(*z).scale = 0;
						break;
					case 2: 
						(*z).scale = 1;
						break;
					case 4: 
						(*z).scale = 2;
						break;
					case 8: 
						(*z).scale = 3;
						break;
					default: __CASECHK;
				}
			} else {
				OPC_Mul(&t, OPC_Item__typ, &size, OPC_Item__typ, &*index, index__typ, 6);
				__GUARDEQR(index, index__typ, OPC_Item) = t;
			}
			(*z).inx = (*index).adr;
		}
	}
	(*z).typ = typ->BaseTyp;
	(*z).descOffs -= 4;
}

static void OPC_MoveBlock (OPC_Item *z, ADDRESS *z__typ, OPC_Item *x, ADDRESS *x__typ, OPC_Item *size, ADDRESS *size__typ, INT8 moveSize)
{
	OPT_Struct type;
	OPC_Item src;
	INT32 oldSize;
	__ASSERT(__IN(moveSize, 0x010101, 32), 0);
	if (((*size).mode == 3 && __IN(moveSize, 0x010100, 32))) {
		oldSize = (*size).adr;
		if ((__MASK((*size).adr, -4) == 0 && moveSize == 16)) {
			(*size).adr = __ASHR((*size).adr, 2);
			moveSize = 0;
		} else if (__MASK((*size).adr, -2) == 0) {
			(*size).adr = __ASHR((*size).adr, 1);
			moveSize -= 8;
		}
	}
	if (((*size).mode == 3 && (*size).adr == 0)) {
	} else if (((*size).mode == 3 && (*size).adr == 1)) {
		__ASSERT(__IN(moveSize, 0x010101, 32), 0);
		if (moveSize == 16) {
			type = OPT_sinttyp;
		} else if (moveSize == 8) {
			type = OPT_inttyp;
		} else {
			type = OPT_linttyp;
		}
		if ((*x).mode == 15) {
			(*x).mode = 17;
			(*x).offs = 0;
			(*x).inx = -1;
		}
		(*x).typ = type;
		OPC_load(&*x, x__typ);
		if ((*z).mode == 2 || ((*z).mode == 1 && OPC_level - (*z).mnolev != 0)) {
			OPC_loadAdr(&*z, z__typ);
		}
		if ((*z).mode == 15) {
			(*z).mode = 17;
			(*z).offs = 0;
			(*z).inx = -1;
		}
		(*z).typ = type;
		OPC_GenStore(416, &*z, z__typ, &*x, x__typ);
		if (__IN((*z).mode, 0x010002, 32)) {
			(*z).adr += oldSize;
		} else {
			(*z).offs += oldSize;
		}
	} else if (((((*size).mode == 3 && (*size).adr == 3)) && moveSize == 16)) {
		if ((*x).mode != 15) {
			OPC_loadAdr(&*x, x__typ);
		}
		if ((*z).mode != 15) {
			OPC_loadAdr(&*z, z__typ);
		}
		(*x).mode = 17;
		(*x).offs = 0;
		(*x).inx = -1;
		(*x).typ = OPT_inttyp;
		(*z).mode = 17;
		(*z).offs = 0;
		(*z).inx = -1;
		(*z).typ = OPT_inttyp;
		src = *x;
		OPC_load(&src, OPC_Item__typ);
		OPC_GenStore(416, &*z, z__typ, &src, OPC_Item__typ);
		(*x).offs = 2;
		(*x).typ = OPT_sinttyp;
		(*z).offs = 2;
		(*z).typ = OPT_sinttyp;
		OPC_load(&*x, x__typ);
		OPC_GenStore(416, &*z, z__typ, &*x, x__typ);
		(*z).offs = 3;
	} else {
		if (((*size).typ->form != 6 && (*size).mode != 3)) {
			OPC_Convert(&*size, size__typ, 6);
			(OPL_Instr->data)[__X((*size).adr, OPL_Instr->len[0])].hint = 1;
		} else {
			if ((*size).mode != 15) {
				(*size).typ = OPT_linttyp;
				OPC_load(&*size, size__typ);
				(OPL_Instr->data)[__X((*size).adr, OPL_Instr->len[0])].hint = 1;
			} else if (((*size).adr > 0 && (OPL_Instr->data)[__X((*size).adr, OPL_Instr->len[0])].hint == -1)) {
				(OPL_Instr->data)[__X((*size).adr, OPL_Instr->len[0])].hint = 17;
			}
		}
		if ((*x).mode != 15) {
			OPC_loadAdr(&*x, x__typ);
			(OPL_Instr->data)[__X((*x).adr, OPL_Instr->len[0])].hint = 6;
		} else if (((*x).adr >= 0 && (OPL_Instr->data)[__X((*x).adr, OPL_Instr->len[0])].hint == -1)) {
			(OPL_Instr->data)[__X((*x).adr, OPL_Instr->len[0])].hint = 22;
		}
		if ((*z).mode != 15) {
			OPC_loadAdr(&*z, z__typ);
			(OPL_Instr->data)[__X((*z).adr, OPL_Instr->len[0])].hint = 7;
		} else if (((*z).adr >= 0 && (OPL_Instr->data)[__X((*z).adr, OPL_Instr->len[0])].hint == -1)) {
			(OPL_Instr->data)[__X((*z).adr, OPL_Instr->len[0])].hint = 23;
		}
		OPC_Gen0(2272);
		OPC_GenRepMovs(&*z, z__typ, &*x, x__typ, &*size, size__typ, moveSize, 0);
		OPC_IncReg((*size).adr);
		OPC_IncReg((*x).adr);
		OPC_IncReg((*z).adr);
	}
}

static void OPC_MoveBlockReversed (OPC_Item *z, ADDRESS *z__typ, OPC_Item *x, ADDRESS *x__typ, OPC_Item *size, ADDRESS *size__typ, INT8 moveSize)
{
	INT8 scale;
	INT32 t;
	__ASSERT(__IN(moveSize, 0x010101, 32), 0);
	if (((*size).mode == 3 && __IN(moveSize, 0x010100, 32))) {
		if ((__MASK((*size).adr, -4) == 0 && moveSize == 16)) {
			(*size).adr = __ASHR((*size).adr, 2);
			moveSize = 0;
		} else if (__MASK((*size).adr, -2) == 0) {
			(*size).adr = __ASHR((*size).adr, 1);
			moveSize -= 8;
		}
	}
	if (((*size).typ->form != 6 && (*size).mode != 3)) {
		OPC_Convert(&*size, size__typ, 6);
		(OPL_Instr->data)[__X((*size).adr, OPL_Instr->len[0])].hint = 1;
	} else {
		if ((*size).mode != 15) {
			(*size).typ = OPT_linttyp;
			OPC_load(&*size, size__typ);
			(OPL_Instr->data)[__X((*size).adr, OPL_Instr->len[0])].hint = 1;
		} else if (((*size).adr > 0 && (OPL_Instr->data)[__X((*size).adr, OPL_Instr->len[0])].hint == -1)) {
			(OPL_Instr->data)[__X((*size).adr, OPL_Instr->len[0])].hint = 17;
		}
	}
	__ASSERT((*size).mode == 15, 0);
	switch (moveSize) {
		case 16: 
			scale = 0;
			break;
		case 8: 
			scale = 1;
			break;
		case 0: 
			scale = 2;
			break;
		default: __CASECHK;
	}
	t = __ASH(1, scale);
	if ((*x).mode == 15) {
		(*x).mode = 17;
		(*x).offs = 0;
	} else if (((*x).mode != 17 || (*x).inx != -1) || (*z).typ->form == 15) {
		OPC_loadAdr(&*x, x__typ);
		(*x).mode = 17;
		(*x).offs = 0;
	}
	__ASSERT((*x).mode == 17, 0);
	(*x).typ = OPT_linttyp;
	(*x).inx = (*size).adr;
	(*x).scale = scale;
	(*x).offs -= t;
	OPC_loadAdr(&*x, x__typ);
	(OPL_Instr->data)[__X((*x).adr, OPL_Instr->len[0])].hint = 6;
	if ((*z).mode == 15) {
		(*z).mode = 17;
		(*z).offs = 0;
	} else if (((*z).mode != 17 || (*z).inx != -1) || (*z).typ->form == 15) {
		OPC_loadAdr(&*z, z__typ);
		(*z).mode = 17;
		(*z).offs = 0;
	}
	__ASSERT((*z).mode == 17, 0);
	(*z).typ = OPT_linttyp;
	(*z).inx = (*size).adr;
	(*z).scale = scale;
	(*z).offs -= t;
	OPC_loadAdr(&*z, z__typ);
	(OPL_Instr->data)[__X((*z).adr, OPL_Instr->len[0])].hint = 7;
	OPC_Gen0(3392);
	OPC_GenRepMovs(&*z, z__typ, &*x, x__typ, &*size, size__typ, moveSize, 1);
	OPC_IncReg((*size).adr);
	OPC_IncReg((*x).adr);
	OPC_IncReg((*z).adr);
	OPC_Gen0(2272);
}

static void OPC_Move (OPC_Item *z, ADDRESS *z__typ, OPC_Item *x, ADDRESS *x__typ)
{
	OPC_Item src, dst;
	if ((*z).mode == 2) {
		OPC_loadAdr(&*z, z__typ);
		(*z).mode = 17;
	} else {
		OPC_CompleteSL(&*z, z__typ);
	}
	if ((*x).typ == OPT_hinttyp) {
		(*x).typ = OPT_linttyp;
		(*z).typ = OPT_linttyp;
		if ((*x).mode == 2) {
			OPC_loadAdr(&*x, x__typ);
			(*x).mode = 17;
			(*x).inx = -1;
		}
		src = *x;
		dst = *z;
		OPC_NextWord(&*x, x__typ, src);
		OPC_NextWord(&*z, z__typ, dst);
		OPC_load(&src, OPC_Item__typ);
		OPC_GenStore(416, &dst, OPC_Item__typ, &src, OPC_Item__typ);
	} else if (((*z).typ->form == 14 && (*z).typ->sysflag == 5)) {
		(*x).typ = OPT_linttyp;
		(*z).typ = OPT_linttyp;
		if ((*z).mode == 2) {
			OPC_loadAdr(&*z, z__typ);
			(*z).mode = 17;
			(*z).offs = 0;
			(*z).inx = -1;
		}
		if ((*x).mode == 3) {
			OPC_load(&*x, x__typ);
			src = *x;
		} else if ((*x).mode == 15) {
			src = *x;
			src.adr = (*x).descReg;
		} else {
			if ((*x).mode == 2) {
				OPC_loadAdr(&*x, x__typ);
				(*x).mode = 17;
				(*x).offs = 0;
				(*x).inx = -1;
			}
			OPC_NextWord(&src, OPC_Item__typ, *x);
		}
		OPC_load(&src, OPC_Item__typ);
		OPC_NextWord(&dst, OPC_Item__typ, *z);
		OPC_GenStore(416, &dst, OPC_Item__typ, &src, OPC_Item__typ);
	}
	OPC_load(&*x, x__typ);
	OPC_GenStore(416, &*z, z__typ, &*x, x__typ);
}

void OPC_SYSmove (OPC_Item *z, ADDRESS *z__typ, OPC_Item *x, ADDRESS *x__typ, OPC_Item *nofBytes, ADDRESS *nofBytes__typ)
{
	__ASSERT((__IN((*z).typ->form, 0x2040, 32) && __IN((*x).typ->form, 0x2040, 32)), 0);
	if ((*x).mode != 15) {
		OPC_load(&*x, x__typ);
		(OPL_Instr->data)[__X((*x).adr, OPL_Instr->len[0])].hint = 6;
	} else if ((OPL_Instr->data)[__X((*x).adr, OPL_Instr->len[0])].hint == -1) {
		(OPL_Instr->data)[__X((*x).adr, OPL_Instr->len[0])].hint = 22;
	}
	if ((*z).mode != 15) {
		OPC_load(&*z, z__typ);
		(OPL_Instr->data)[__X((*z).adr, OPL_Instr->len[0])].hint = 7;
	} else if ((OPL_Instr->data)[__X((*z).adr, OPL_Instr->len[0])].hint == -1) {
		(OPL_Instr->data)[__X((*z).adr, OPL_Instr->len[0])].hint = 23;
	}
	OPC_MoveBlock(&*z, z__typ, &*x, x__typ, &*nofBytes, nofBytes__typ, 16);
}

void OPC_Copy (OPC_Item *z, ADDRESS *z__typ, OPC_Item *x, ADDRESS *x__typ)
{
	OPC_Item zLen, xLen, zLen0, xLen0, char0X, len, z0, x0, t;
	INT32 Lfix, L;
	OPC_MakeCon(&char0X, OPC_Item__typ, OPT_chartyp, 0);
	OPC_Length(&zLen, OPC_Item__typ, &*z, z__typ);
	OPC_Length(&xLen, OPC_Item__typ, &*x, x__typ);
	if ((zLen.mode == 3 && xLen.mode == 3)) {
		if (zLen.adr >= xLen.adr) {
			OPC_MoveBlock(&*z, z__typ, &*x, x__typ, &xLen, OPC_Item__typ, 16);
		} else {
			zLen.adr -= 1;
			OPC_MoveBlock(&*z, z__typ, &*x, x__typ, &zLen, OPC_Item__typ, 16);
			if ((*z).mode == 15) {
				t.adr = (*z).adr;
				t.mode = 17;
				t.offs = 0;
				t.inx = -1;
				t.typ = OPT_chartyp;
				t.node = NIL;
			} else {
				t = *z;
				t.typ = OPT_chartyp;
			}
			OPC_Move(&t, OPC_Item__typ, &char0X, OPC_Item__typ);
		}
	} else {
		if ((*x).mode != 15) {
			OPC_loadAdr(&*x, x__typ);
		} else {
			x0 = *x;
			OPC_MakeCon(&len, OPC_Item__typ, OPT_linttyp, 0);
			OPC_Add(&*x, x__typ, &x0, OPC_Item__typ, &len, OPC_Item__typ, 6);
		}
		(OPL_Instr->data)[__X((*x).adr, OPL_Instr->len[0])].hint = 22;
		OPC_loadAdr(&*z, z__typ);
		(OPL_Instr->data)[__X((*z).adr, OPL_Instr->len[0])].hint = 23;
		if (zLen.mode == 3) {
			xLen0 = xLen;
			if (xLen.typ->form != 6) {
				OPC_Convert(&xLen0, OPC_Item__typ, 6);
			} else {
				OPC_load(&xLen0, OPC_Item__typ);
			}
			(OPL_Instr->data)[__X(xLen0.adr, OPL_Instr->len[0])].hint = 17;
			OPC_GenFlags(1056, &xLen0, OPC_Item__typ, &zLen, OPC_Item__typ);
			Lfix = -2 - OPC_pc;
			OPC_Gen1(1632, -1, NIL);
		} else {
			zLen0 = zLen;
			if (zLen0.typ->form != 6) {
				OPC_Convert(&zLen0, OPC_Item__typ, 6);
			} else {
				OPC_load(&zLen0, OPC_Item__typ);
			}
			(OPL_Instr->data)[__X(zLen0.adr, OPL_Instr->len[0])].hint = 17;
			xLen0 = xLen;
			if (xLen0.mode != 3) {
				if (xLen0.typ->form != 6) {
					OPC_Convert(&xLen0, OPC_Item__typ, 6);
				} else {
					OPC_load(&xLen0, OPC_Item__typ);
				}
			}
			OPC_GenFlags(1056, &zLen0, OPC_Item__typ, &xLen0, OPC_Item__typ);
			Lfix = -2 - OPC_pc;
			OPC_Gen1(1568, -1, NIL);
		}
		z0 = *z;
		x0 = *x;
		OPC_MoveBlock(&z0, OPC_Item__typ, &x0, OPC_Item__typ, &xLen, OPC_Item__typ, 16);
		L = -2 - OPC_pc;
		OPC_Gen1(1888, -1, NIL);
		OPC_FixLink(Lfix);
		if (zLen.mode == 3) {
			zLen.adr -= 1;
		} else {
			OPC_MakeCon(&len, OPC_Item__typ, OPT_linttyp, 1);
			OPC_load(&zLen, OPC_Item__typ);
			(OPL_Instr->data)[__X(zLen.adr, OPL_Instr->len[0])].hint = 1;
			t = zLen;
			OPC_Sub(&zLen, OPC_Item__typ, &t, OPC_Item__typ, &len, OPC_Item__typ, 6);
		}
		OPC_MoveBlock(&*z, z__typ, &*x, x__typ, &zLen, OPC_Item__typ, 16);
		if ((*z).mode == 15) {
			t.mode = 17;
			t.adr = (*z).adr;
			t.offs = 0;
			t.inx = -1;
			t.typ = OPT_chartyp;
			t.node = NIL;
		} else {
			t = *z;
			t.typ = OPT_chartyp;
		}
		OPC_Move(&t, OPC_Item__typ, &char0X, OPC_Item__typ);
		OPC_FixLink(L);
	}
}

void OPC_Assign (OPC_Item *z, ADDRESS *z__typ, OPC_Item *x, ADDRESS *x__typ)
{
	INT8 zform, xform, step, scale;
	OPC_Item temp, zero, sizeItem;
	OPT_Object proc;
	zform = (*z).typ->form;
	xform = (*x).typ->form;
	if ((__IN(zform, 0x01e0, 32) && zform != xform)) {
		OPC_Convert(&*x, x__typ, zform);
	}
	switch (zform) {
		case 2: 
			if ((*x).mode == 18) {
				temp = *x;
				OPC_MoveCoc(&*x, x__typ, &temp, OPC_Item__typ);
			} else {
				OPC_load(&*x, x__typ);
			}
			if ((*z).mode == 2) {
				OPC_loadAdr(&*z, z__typ);
				(*z).mode = 17;
			} else {
				OPC_CompleteSL(&*z, z__typ);
			}
			OPC_GenStore(416, &*z, z__typ, &*x, x__typ);
			break;
		case 1: case 3: case 4: case 9: case 5: 
		case 6: case 16: 
			OPC_Move(&*z, z__typ, &*x, x__typ);
			break;
		case 7: 
			OPC_loadf(&*x, x__typ);
			if ((*z).mode == 2) {
				OPC_loadAdr(&*z, z__typ);
				(*z).mode = 17;
			} else {
				OPC_CompleteSL(&*z, z__typ);
			}
			OPC_GenStore(2560, &*z, z__typ, &*x, x__typ);
			break;
		case 8: 
			OPC_loadf(&*x, x__typ);
			if ((*z).mode == 2) {
				OPC_loadAdr(&*z, z__typ);
				(*z).mode = 17;
			} else {
				OPC_CompleteSL(&*z, z__typ);
			}
			OPC_GenStore(2560, &*z, z__typ, &*x, x__typ);
			break;
		case 13: 
			if (xform == 11) {
				OPC_MakeCon(&zero, OPC_Item__typ, OPT_linttyp, 0);
				OPC_load(&zero, OPC_Item__typ);
				if ((*z).mode == 2) {
					OPC_loadAdr(&*z, z__typ);
					(*z).mode = 17;
				} else {
					OPC_CompleteSL(&*z, z__typ);
				}
				OPC_GenStore(416, &*z, z__typ, &zero, OPC_Item__typ);
			} else {
				OPC_load(&*x, x__typ);
				if ((*z).mode == 2) {
					OPC_loadAdr(&*z, z__typ);
					(*z).mode = 17;
				} else {
					OPC_CompleteSL(&*z, z__typ);
				}
				temp = *z;
				OPC_GenStore(416, &*z, z__typ, &*x, x__typ);
			}
			break;
		case 14: 
			if ((*z).typ == (*x).typ || xform == 11) {
				if (xform == 11) {
					OPC_MakeCon(&*x, x__typ, OPT_linttyp, 0);
				}
				OPC_Move(&*z, z__typ, &*x, x__typ);
			} else if ((*x).mode == 15) {
				__ASSERT((*x).typ == OPC_delegateType, 0);
				OPC_Move(&*z, z__typ, &*x, x__typ);
			} else {
				proc = (*x).node->obj;
				if ((*x).mnolev == 0) {
					OPC_GenLoadProc(320, &*x, x__typ, __MASK(proc->adr, -65536), (*x).node);
				} else {
					OPC_GenLoadProc(352, &*x, x__typ, __ASHR(proc->adr, 16), (*x).node);
				}
				if ((*z).typ->sysflag == 5) {
					OPC_MakeCon(&zero, OPC_Item__typ, OPT_ptrtyp, 0);
					OPC_load(&zero, OPC_Item__typ);
					(*x).descReg = zero.adr;
				}
				OPC_Move(&*z, z__typ, &*x, x__typ);
			}
			break;
		case 15: 
			__ASSERT((*z).typ->comp == 6 || __IN((*z).typ->comp, 0x1c, 32), 0);
			if ((*x).typ->form == 10) {
				OPC_Copy(&*z, z__typ, &*x, x__typ);
			} else {
				if (__IN((*z).typ->comp, 0x08, 32)) {
					OPC_TypeSize(*z, &sizeItem, OPC_Item__typ, &step, &scale);
					temp = *z;
					OPC_MoveBlock(&*z, z__typ, &*x, x__typ, &sizeItem, OPC_Item__typ, step);
				} else if ((*z).typ->comp == 4) {
					OPC_CopyDynArr(&*z, z__typ, &*x, x__typ);
				} else if ((*x).typ->size != 4) {
					OPC_MakeCon(&sizeItem, OPC_Item__typ, OPT_linttyp, (*z).typ->size);
					step = 16;
					temp = *z;
					OPC_MoveBlock(&*z, z__typ, &*x, x__typ, &sizeItem, OPC_Item__typ, step);
				} else {
					temp = *z;
					OPC_Move(&*z, z__typ, &*x, x__typ);
				}
			}
			break;
		default: 
			__HALT(40);
			break;
	}
}

void OPC_IncDec (OPC_Item *z, ADDRESS *z__typ, OPC_Item *x, ADDRESS *x__typ, BOOLEAN increment)
{
	OPC_Item z0, temp;
	z0 = *z;
	OPC_load(&z0, OPC_Item__typ);
	temp = z0;
	if (increment) {
		OPC_Add(&z0, OPC_Item__typ, &temp, OPC_Item__typ, &*x, x__typ, (*z).typ->form);
	} else {
		OPC_Sub(&z0, OPC_Item__typ, &temp, OPC_Item__typ, &*x, x__typ, (*z).typ->form);
	}
	OPC_Assign(&*z, z__typ, &z0, OPC_Item__typ);
}

void OPC_MulDim (OPC_Item *nofelem, ADDRESS *nofelem__typ, OPC_Item *len, ADDRESS *len__typ)
{
	OPC_Item t;
	if (((*nofelem).mode == 3 && (*len).mode == 3)) {
		(*nofelem).adr = (*nofelem).adr * (*len).adr;
	} else {
		t = *nofelem;
		OPC_Mul(&*nofelem, nofelem__typ, &t, OPC_Item__typ, &*len, len__typ, 6);
	}
}

void OPC_PushLen (OPC_Item *z, ADDRESS *z__typ)
{
	if ((*z).mode != 3) {
		if ((*z).typ->form != 6) {
			if ((*z).mode == 1) {
				OPC_load(&*z, z__typ);
			}
			OPC_Convert(&*z, z__typ, 6);
		} else {
			OPC_load(&*z, z__typ);
		}
	}
	OPC_GenPush(&*z, z__typ);
}

void OPC_PopLen (OPC_Item *block, ADDRESS *block__typ)
{
	OPC_Item reg;
	reg.typ = OPT_linttyp;
	OPC_GenPop(&reg, OPC_Item__typ);
	OPC_GenStore(416, &*block, block__typ, &reg, OPC_Item__typ);
}

void OPC_NewSys (OPC_Item *z, ADDRESS *z__typ, OPC_Item *x, ADDRESS *x__typ)
{
	if ((*z).mode != 15) {
		OPC_loadAdr(&*z, z__typ);
	}
	OPC_GenPush(&*z, z__typ);
	if (__IN((*x).typ->form, 0x30, 32)) {
		if ((*x).mode == 3) {
			(*x).typ = OPT_linttyp;
		} else {
			OPC_Convert(&*x, x__typ, 6);
		}
	}
	if ((*x).mode != 3) {
		OPC_load(&*x, x__typ);
	}
	OPC_GenPush(&*x, x__typ);
	OPC_GenCall(2144, 196860, 8, NIL);
}

void OPC_NewArray (OPC_Item *z, ADDRESS *z__typ, OPC_Item *nofelem, ADDRESS *nofelem__typ, INT32 nofdim, OPT_Struct typ, BOOLEAN dimUsed)
{
	OPC_Item cons, tdesc, t;
	INT32 nofArrElems;
	OPT_Object o;
	nofArrElems = 1;
	while (typ->comp == 2) {
		nofArrElems = nofArrElems * typ->n;
		typ = typ->BaseTyp;
	}
	if (nofArrElems != 1) {
		OPC_MakeCon(&cons, OPC_Item__typ, OPT_linttyp, nofArrElems);
		OPC_MulDim(&*nofelem, nofelem__typ, &cons, OPC_Item__typ);
	}
	OPC_loadAdr(&*z, z__typ);
	if (dimUsed) {
		OPC_GenPush(&*z, z__typ);
	}
	if ((typ->form == 13 || typ->comp == 6) || (typ->form == 14 && typ->sysflag == 5)) {
		t = *z;
		OPC_GenPush(&t, OPC_Item__typ);
		if (typ->form == 13) {
			OPT_FindInScope((CHAR*)"@pointer", 9, OPT_topScope, &o);
			typ = o->typ;
		} else if (typ->form == 14) {
			OPT_FindInScope((CHAR*)"@delegate", 10, OPT_topScope, &o);
			typ = o->typ;
		}
		OPC_GetTdAdr(&typ, &tdesc, OPC_Item__typ);
		OPC_load(&tdesc, OPC_Item__typ);
		OPC_GenPush(&tdesc, OPC_Item__typ);
		if ((*nofelem).mode != 3) {
			OPC_load(&*nofelem, nofelem__typ);
		}
		OPC_GenPush(&*nofelem, nofelem__typ);
		OPC_MakeCon(&cons, OPC_Item__typ, OPT_linttyp, nofdim);
		OPC_GenPush(&cons, OPC_Item__typ);
		OPC_GenCall(2144, 262395, 16, NIL);
	} else {
		if ((*nofelem).mode == 3) {
			(*nofelem).adr = (((*nofelem).adr * typ->size + 8) + 8) + __ASHL(__ASHR(nofdim, 1), 3);
		} else {
			OPC_MakeCon(&cons, OPC_Item__typ, OPT_linttyp, typ->size);
			t = *nofelem;
			OPC_Mul(&*nofelem, nofelem__typ, &t, OPC_Item__typ, &cons, OPC_Item__typ, 6);
			cons.adr = 16 + __ASHL(__ASHR(nofdim, 1), 3);
			t = *nofelem;
			OPC_Add(&*nofelem, nofelem__typ, &t, OPC_Item__typ, &cons, OPC_Item__typ, 6);
		}
		t = *z;
		OPC_NewSys(&t, OPC_Item__typ, &*nofelem, nofelem__typ);
	}
	if (dimUsed) {
		OPC_GenPop(&*z, z__typ);
		(*z).mode = 17;
		(*z).offs = 0;
		OPC_load(&*z, z__typ);
		(*z).mode = 17;
		(*z).typ = OPT_ptrtyp;
		(*z).offs = 8;
		(*z).inx = -1;
	}
}

void OPC_NewRec (OPC_Item *z, ADDRESS *z__typ, OPT_Struct typ)
{
	OPC_Item tag, size;
	OPT_Struct btyp;
	INT32 len;
	OPT_Object o;
	if (typ->comp == 2) {
		len = typ->n;
		btyp = typ->BaseTyp;
		while (btyp->comp == 2) {
			len = len * btyp->n;
			btyp = btyp->BaseTyp;
		}
		OPC_MakeCon(&size, OPC_Item__typ, OPT_linttyp, len);
		if ((btyp->comp == 6 || btyp->form == 13) || (btyp->form == 14 && btyp->sysflag == 5)) {
			OPC_NewArray(&*z, z__typ, &size, OPC_Item__typ, 1, btyp, 0);
		} else {
			size.adr = typ->size + 16;
			OPC_NewSys(&*z, z__typ, &size, OPC_Item__typ);
		}
	} else {
		OPC_loadAdr(&*z, z__typ);
		OPC_GenPush(&*z, z__typ);
		if (typ->comp == 4) {
			OPT_FindInScope((CHAR*)"@pointer", 9, OPT_topScope, &o);
			typ = o->typ;
		}
		OPC_GetTdAdr(&typ, &tag, OPC_Item__typ);
		OPC_load(&tag, OPC_Item__typ);
		OPC_GenPush(&tag, OPC_Item__typ);
		OPC_GenCall(2144, 131325, 8, NIL);
	}
}

static struct CallRecBody__13 {
	struct CallRecBody__13 *lnk;
} *CallRecBody__13_s;

static void GetBody__14 (OPT_Struct curtype, OPT_Struct bodytype, OPC_Item *body, ADDRESS *body__typ);

static void GetBody__14 (OPT_Struct curtype, OPT_Struct bodytype, OPC_Item *body, ADDRESS *body__typ)
{
	OPC_Item tag;
	OPC_GetTdAdr(&curtype, &tag, OPC_Item__typ);
	OPC_DeRef(&tag, OPC_Item__typ);
	if (curtype != bodytype) {
		tag.mode = 17;
		tag.offs = -8 - __ASHL(bodytype->extlev, 2);
		tag.inx = -1;
		tag.typ = OPT_ptrtyp;
		OPC_load(&tag, OPC_Item__typ);
	}
	(*body).adr = tag.adr;
	(*body).mode = 17;
	(*body).typ = OPT_ptrtyp;
}

void OPC_CallRecBody (OPC_Item *self, ADDRESS *self__typ, OPC_Item *body, ADDRESS *body__typ, OPT_Struct typ)
{
	OPC_Item con;
	INT32 type;
	OPC_Item tag, t0, t1;
	struct CallRecBody__13 _s;
	_s.lnk = CallRecBody__13_s;
	CallRecBody__13_s = &_s;
	if ((typ->strobj != NIL && __IN(5, typ->strobj->conval->setval, 32))) {
		__ASSERT((*self).typ->form == 13, 0);
		GetBody__14((*self).typ->BaseTyp, typ, &*body, body__typ);
		OPC_load(&*body, body__typ);
		OPC_GenPush(&*body, body__typ);
		OPC_MakeCon(&con, OPC_Item__typ, OPT_sinttyp, typ->strobj->prio);
		OPC_GenPush(&con, OPC_Item__typ);
		type = 0;
		if (__IN(8, typ->strobj->conval->setval, 32)) {
			type += 1;
		}
		OPC_MakeCon(&con, OPC_Item__typ, OPT_sinttyp, type);
		OPC_GenPush(&con, OPC_Item__typ);
		OPC_load(&*self, self__typ);
		OPC_GenPush(&*self, self__typ);
		OPC_GenCall(2144, 327930, 16, NIL);
	} else {
		tag = *self;
		OPC_loadAdr(&tag, OPC_Item__typ);
		tag.mode = 17;
		tag.offs = -4;
		tag.inx = -1;
		tag.typ = OPT_linttyp;
		OPC_load(&tag, OPC_Item__typ);
		OPC_GenPush(&tag, OPC_Item__typ);
		OPC_load(&*self, self__typ);
		OPC_GenPush(&*self, self__typ);
		GetBody__14((*self).typ->BaseTyp, typ, &*body, body__typ);
		OPC_load(&*body, body__typ);
		OPC_GenCall(2112, (*body).adr, 4, NIL);
	}
	CallRecBody__13_s = _s.lnk;
}

static void OPC_PushArrLen (OPT_Object fp, OPC_Item *ap, ADDRESS *ap__typ, OPC_Item *dest, ADDRESS *dest__typ, BOOLEAN useDest)
{
	OPT_Struct atyp, ftyp;
	INT32 depth;
	OPC_Item len, size, t;
	atyp = (*ap).typ;
	ftyp = fp->typ;
	depth = 0;
	while (__IN(ftyp->comp, 0x28, 32)) {
		if (ftyp->BaseTyp == OPT_bytetyp) {
			if ((atyp->comp == 6 && (*ap).mode == 2)) {
				len = *ap;
				OPC_CompleteSL(&len, OPC_Item__typ);
				if (__IN(len.mode, 0x06, 32)) {
					len.adr += 4;
					len.mode = 1;
				} else {
					__ASSERT(len.mode == 17, 0);
					len.offs += 4;
				}
				OPC_DeRef(&len, OPC_Item__typ);
				OPC_load(&len, OPC_Item__typ);
			} else if (__IN(atyp->comp, 0x38, 32)) {
				OPC_ArrayLen(&len, OPC_Item__typ, *ap, depth);
				OPC_ArrayBaseSize(&size, OPC_Item__typ, *ap);
				if ((len.mode == 3 && size.mode == 3)) {
					len.adr = len.adr * size.adr;
				} else {
					OPC_Mul(&t, OPC_Item__typ, &len, OPC_Item__typ, &size, OPC_Item__typ, 6);
					len = t;
				}
			} else {
				OPC_MakeCon(&len, OPC_Item__typ, OPT_linttyp, atyp->size);
			}
		} else if (atyp->form == 10) {
			__ASSERT((*ap).mode == 16, 0);
			OPC_MakeCon(&len, OPC_Item__typ, OPT_linttyp, (*ap).offs);
		} else {
			__ASSERT(__IN(atyp->comp, 0x3c, 32), 100);
			OPC_ArrayLen(&len, OPC_Item__typ, *ap, depth);
		}
		len.typ = OPT_linttyp;
		if (useDest) {
			if (len.mode != 15) {
				OPC_load(&len, OPC_Item__typ);
			}
			(*dest).offs -= 4;
			t = *dest;
			OPC_GenStore(416, &t, OPC_Item__typ, &len, OPC_Item__typ);
		} else {
			if (!__IN(len.mode, 0x8008, 32)) {
				OPC_load(&len, OPC_Item__typ);
			}
			OPC_GenPush(&len, OPC_Item__typ);
		}
		atyp = atyp->BaseTyp;
		ftyp = ftyp->BaseTyp;
		depth += 1;
	}
	if (((*ap).mode == 17 && (*ap).adr == -3)) {
		(*ap).offs += __ASHL(depth, 2);
	}
}

static void OPC_PushComp (OPT_Object fp, OPC_Item *ap, ADDRESS *ap__typ)
{
	OPC_Item sizeItem, t;
	INT32 size;
	if ((*ap).typ->form == 10) {
		size = fp->typ->size;
		size += __MASK(-size, -4);
		OPC_MakeCon(&sizeItem, OPC_Item__typ, OPT_linttyp, size);
		t = OPC_Stack;
		OPC_Sub(&t, OPC_Item__typ, &OPC_Stack, OPC_Item__typ, &sizeItem, OPC_Item__typ, 6);
		OPC_MakeCon(&sizeItem, OPC_Item__typ, OPT_linttyp, (*ap).offs);
		t = OPC_Stack;
		OPC_MoveBlock(&t, OPC_Item__typ, &*ap, ap__typ, &sizeItem, OPC_Item__typ, 16);
	} else if ((*ap).typ->size != 4) {
		size = fp->typ->size;
		size += __MASK(-size, -4);
		OPC_MakeCon(&sizeItem, OPC_Item__typ, OPT_linttyp, size);
		t = OPC_Stack;
		OPC_Sub(&t, OPC_Item__typ, &OPC_Stack, OPC_Item__typ, &sizeItem, OPC_Item__typ, 6);
		OPC_MakeCon(&sizeItem, OPC_Item__typ, OPT_linttyp, fp->typ->size);
		t = OPC_Stack;
		OPC_MoveBlock(&t, OPC_Item__typ, &*ap, ap__typ, &sizeItem, OPC_Item__typ, 16);
	} else {
		OPC_load(&*ap, ap__typ);
		OPC_GenPush(&*ap, ap__typ);
	}
}

static void OPC_ParRecord (OPT_Object fp, OPC_Item *ap, ADDRESS *ap__typ, BOOLEAN apIsDeref, BOOLEAN alwaysRef)
{
	OPC_Item t, t0, t1, tag;
	BOOLEAN pushtag;
	pushtag = fp->typ->sysflag != 1;
	if ((*ap).mode == 2) {
		if (fp->mode == 2 || alwaysRef) {
			if (pushtag) {
				t.mode = 1;
				t.adr = (*ap).adr + 4;
				t.typ = OPT_ptrtyp;
				t.node = NIL;
				t.inx = -1;
				t.offs = 0;
				t.mnolev = (*ap).mnolev;
				OPC_load(&t, OPC_Item__typ);
				OPC_GenPush(&t, OPC_Item__typ);
				OPC_lastTD = t;
				if (((*ap).mode == 17 && (*ap).adr == -3)) {
					(*ap).offs += 4;
				}
			}
			if ((*ap).mode != 15) {
				OPC_loadAdr(&*ap, ap__typ);
			}
			OPC_GenPush(&*ap, ap__typ);
		} else {
			OPC_PushComp(fp, &*ap, ap__typ);
		}
	} else {
		if (fp->mode == 2 || alwaysRef) {
			if (pushtag) {
				if (apIsDeref) {
					__ASSERT(((*ap).mode == 17 && (*ap).offs == 0), 0);
					tag.mode = 17;
					tag.scale = 0;
					tag.typ = OPT_ptrtyp;
					tag.offs = -4;
					tag.adr = (*ap).adr;
					tag.inx = -1;
					tag.descReg = -1;
				} else {
					OPC_GetTdAdr(&(*ap).typ, &tag, OPC_Item__typ);
				}
				OPC_load(&tag, OPC_Item__typ);
				OPC_GenPush(&tag, OPC_Item__typ);
				if (((*ap).mode == 17 && (*ap).adr == -3)) {
					(*ap).offs += 4;
				}
				OPC_lastTD = tag;
			}
			if ((*ap).mode != 15) {
				OPC_loadAdr(&*ap, ap__typ);
			}
			OPC_GenPush(&*ap, ap__typ);
		} else {
			OPC_PushComp(fp, &*ap, ap__typ);
		}
	}
}

void OPC_Parameter (OPC_Item *ap, ADDRESS *ap__typ, OPT_Object fp, BOOLEAN apIsDeref, BOOLEAN alwaysRef)
{
	INT8 form, apMode;
	OPC_Item temp, cons, stack, tag;
	OPT_Object proc;
	OPT_Struct apTyp, fpTyp;
	BOOLEAN pushtag;
	fpTyp = fp->typ;
	apTyp = (*ap).typ;
	pushtag = (fpTyp->sysflag != 1 && apTyp->sysflag != 1);
	if (((*ap).typ->form == 11 && (!pushtag || fp->mode == 2))) {
		OPC_load(&*ap, ap__typ);
		OPC_GenPush(&*ap, ap__typ);
		return;
	}
	if ((((apTyp->comp == 4 && fpTyp->comp != 4)) && (*ap).descReg == -1)) {
		OPC_loadDynArr(&*ap, ap__typ);
	}
	if (fp->mode == 2 || __IN(fpTyp->comp, 0x6c, 32)) {
		form = fpTyp->comp;
		if (form == 6) {
			OPC_ParRecord(fp, &*ap, ap__typ, apIsDeref, alwaysRef);
		} else if ((((fp->mode == 1 && fpTyp->comp == 2)) && pushtag)) {
			OPC_PushComp(fp, &*ap, ap__typ);
		} else if (fpTyp->comp == 5) {
			if (pushtag) {
				OPC_PushArrLen(fp, &*ap, ap__typ, &*ap, ap__typ, 0);
			}
			if ((*ap).mode != 15) {
				OPC_loadAdr(&*ap, ap__typ);
			}
			if ((*ap).typ == OPT_hinttyp) {
				(*ap).typ = OPT_linttyp;
			}
			OPC_GenPush(&*ap, ap__typ);
		} else {
			apMode = (*ap).mode;
			if (apTyp->form == 10) {
				__HALT(100);
				(*ap).node = NIL;
			}
			if (apTyp == OPT_hinttyp) {
				(*ap).typ = OPT_linttyp;
			}
			if ((*ap).mode != 15) {
				OPC_loadAdr(&*ap, ap__typ);
			}
			OPC_GenPush(&*ap, ap__typ);
			if ((fpTyp == OPT_ptrtyp && apTyp != OPT_ptrtyp)) {
				if (apTyp->BaseTyp->comp == 6) {
					OPC_GetTdAdr(&apTyp->BaseTyp, &tag, OPC_Item__typ);
				} else {
					OPC_MakeCon(&tag, OPC_Item__typ, OPT_linttyp, 0);
				}
				(*ap).mode = 17;
				OPC_Assign(&*ap, ap__typ, &tag, OPC_Item__typ);
			} else if ((((fpTyp == OPT_ptrtyp && apTyp == OPT_ptrtyp)) && apMode != 2)) {
				OPC_MakeCon(&cons, OPC_Item__typ, OPT_linttyp, 0);
				(*ap).mode = 17;
				OPC_Assign(&*ap, ap__typ, &cons, OPC_Item__typ);
			}
		}
	} else {
		__ASSERT(__IN((*ap).mode, 0x0780ce, 32), 0);
		form = apTyp->form;
		if ((((apTyp != fpTyp && !__IN((*ap).mode, 0xc0, 32))) && !__IN(form, 0x7800, 32))) {
			OPC_Convert(&*ap, ap__typ, fp->typ->form);
			form = (*ap).typ->form;
		}
		if ((__IN(form, 0x0180, 32) && (*ap).mode == 15)) {
			if (fp->typ->form == 7) {
				OPC_MakeCon(&cons, OPC_Item__typ, OPT_linttyp, 4);
			} else {
				OPC_MakeCon(&cons, OPC_Item__typ, OPT_linttyp, 8);
			}
			stack = OPC_Stack;
			OPC_Gen3(544, &stack, OPC_Item__typ, &stack, OPC_Item__typ, &cons, OPC_Item__typ);
			stack.mode = 17;
			stack.offs = 0;
			stack.inx = -1;
			stack.typ = fp->typ;
			OPC_GenStore(2560, &stack, OPC_Item__typ, &*ap, ap__typ);
		} else {
			if (__IN((*ap).mode, 0xc0, 32)) {
				proc = (*ap).node->obj;
				if ((*ap).mnolev == 0) {
					OPC_GenLoadProc(320, &*ap, ap__typ, __MASK(proc->adr, -65536), (*ap).node);
				} else {
					OPC_GenLoadProc(352, &*ap, ap__typ, __ASHR(proc->adr, 16), (*ap).node);
				}
				if ((fpTyp->form == 14 && fpTyp->sysflag == 5)) {
					(*ap).descReg = 0;
				}
			} else if (__IN(form, 0x010100, 32)) {
				(*ap).typ = OPT_linttyp;
				temp = *ap;
				if (temp.mode == 2) {
					OPC_loadAdr(&temp, OPC_Item__typ);
					temp.mode = 17;
					temp.offs = 0;
				}
				if (temp.mode == 17) {
					temp.offs += 4;
				} else if (temp.mode == 15) {
					temp.adr = temp.offs;
				} else {
					temp.adr += 4;
				}
				OPC_load(&*ap, ap__typ);
				OPC_load(&temp, OPC_Item__typ);
				OPC_GenPush(&temp, OPC_Item__typ);
			} else if ((*ap).mode == 18) {
				temp = *ap;
				OPC_MoveCoc(&*ap, ap__typ, &temp, OPC_Item__typ);
			}
			if ((*ap).mode != 3) {
				if (__IN((*ap).typ->form, 0x010180, 32)) {
					(*ap).typ = OPT_linttyp;
				}
				OPC_load(&*ap, ap__typ);
			}
			if ((fpTyp->form == 14 && fpTyp->sysflag == 5)) {
				if ((*ap).descReg == 0) {
					OPC_MakeCon(&temp, OPC_Item__typ, OPT_linttyp, 0);
				} else {
					temp = *ap;
					temp.adr = temp.descReg;
				}
				OPC_GenPush(&temp, OPC_Item__typ);
			}
			OPC_GenPush(&*ap, ap__typ);
			OPC_lastTD = *ap;
		}
	}
}

INT32 OPC_PrepRetDest (OPC_Item z)
{
	OPC_Item t, from;
	INT32 size;
	__ASSERT(z.typ->form == 15, 0);
	size = 4;
	if (z.mode == 0) {
		if (z.typ->comp == 6) {
			size += 1;
			from.mode = 17;
			from.adr = -2;
			from.offs = z.offs + 4;
			from.typ = OPT_linttyp;
			from.inx = -1;
			OPC_load(&from, OPC_Item__typ);
			OPC_GenPush(&from, OPC_Item__typ);
		}
		from.mode = 17;
		from.adr = -2;
		from.offs = z.offs;
		from.typ = OPT_linttyp;
		from.inx = -1;
		OPC_load(&from, OPC_Item__typ);
		OPC_GenPush(&from, OPC_Item__typ);
	} else {
		if (z.typ->comp == 6) {
			OPC_MakeCon(&t, OPC_Item__typ, OPT_linttyp, z.typ->size);
			OPC_GenPush(&t, OPC_Item__typ);
			size += 4;
		}
		if (__IN(z.mode, 0x030006, 32)) {
			OPC_loadAdr(&z, OPC_Item__typ);
		}
		OPC_GenPush(&z, OPC_Item__typ);
	}
	return size;
}

void OPC_PushRetDesc (OPC_Item *x, ADDRESS *x__typ, OPC_Item *tos, ADDRESS *tos__typ)
{
	OPC_Item con;
	__ASSERT(((*tos).mode == 17 && (*tos).adr == -3), 101);
	if ((*x).typ->comp == 6) {
		if (((*x).mode == 17 && (*x).adr == -3)) {
			(*x).offs += 4;
		}
		OPC_MakeCon(&con, OPC_Item__typ, OPT_linttyp, (*x).typ->size);
		OPC_GenPush(&con, OPC_Item__typ);
		(*tos).offs += 4;
	}
	OPC_loadAdr(&*x, x__typ);
	OPC_GenPush(&*x, x__typ);
	(*tos).offs += 4;
}

void OPC_CorrectStackAdr (OPC_Item *x, ADDRESS *x__typ, INT32 size, INT32 dynblocks)
{
	INT32 oldoff;
	OPT_Struct typ;
	typ = (*x).typ;
	(*x).typ = OPT_linttyp;
	if ((((dynblocks != 0 && (*x).mode == 17)) && (*x).adr == -3)) {
		oldoff = (*x).offs;
		(*x).offs = size;
		while (dynblocks != 0) {
			OPC_load(&*x, x__typ);
			(*x).mode = 17;
			(*x).offs = 0;
			dynblocks -= 1;
		}
		(*x).offs = oldoff;
	} else if ((((size != 0 && (*x).mode == 17)) && (*x).adr == -3)) {
		(*x).offs += size;
	}
	(*x).typ = typ;
}

void OPC_ResetStack (INT32 dynblocks)
{
	OPC_Item t;
	t = OPC_Stack;
	while (dynblocks != 0) {
		OPC_GenPop(&t, OPC_Item__typ);
		(OPL_Instr->data)[__X(OPC_pc - 1, OPL_Instr->len[0])].hint = 4;
		dynblocks -= 1;
	}
}

void OPC_AllocateStatic (OPC_Item *tos, ADDRESS *tos__typ, INT32 size)
{
	OPC_Item t, con;
	__ASSERT(size >= 0, 100);
	__ASSERT(__MASK(size, -4) == 0, 101);
	if (size != 0) {
		t = OPC_Stack;
		OPC_MakeCon(&con, OPC_Item__typ, OPT_linttyp, size);
		OPC_Sub(&t, OPC_Item__typ, &OPC_Stack, OPC_Item__typ, &con, OPC_Item__typ, 6);
	}
	(*tos).mode = 17;
	(*tos).adr = -3;
	(*tos).offs = 0;
	(*tos).inx = -1;
	(*tos).typ = OPT_linttyp;
}

void OPC_RemoveStatic (INT32 size)
{
	OPC_Item t, con;
	__ASSERT(size >= 0, 100);
	__ASSERT(__MASK(size, -4) == 0, 101);
	if (size != 0) {
		t = OPC_Stack;
		OPC_MakeCon(&con, OPC_Item__typ, OPT_linttyp, size);
		OPC_Add(&t, OPC_Item__typ, &OPC_Stack, OPC_Item__typ, &con, OPC_Item__typ, 6);
	}
}

static void OPC_CopyDynArr (OPC_Item *x, ADDRESS *x__typ, OPC_Item *y, ADDRESS *y__typ)
{
	INT32 dim;
	OPC_Item yy, xx, size, t;
	OPT_Struct typ;
	INT8 step, scale;
	if (!__IN((*y).mode, 0x010006, 32)) {
		OPC_load(&*y, y__typ);
		OPC_GenPush(&*y, y__typ);
	}
	yy = *y;
	typ = (*y).typ;
	dim = 0;
	if ((*y).descReg == -1) {
		OPC_loadDynArr(&*y, y__typ);
	}
	OPC_MakeCon(&size, OPC_Item__typ, OPT_linttyp, 1);
	while (typ->comp == 4) {
		OPC_ArrayLen(&t, OPC_Item__typ, *y, dim);
		OPC_Mul(&size, OPC_Item__typ, &size, OPC_Item__typ, &t, OPC_Item__typ, 6);
		typ = typ->BaseTyp;
		dim += 1;
	}
	OPC_NewArray(&*x, x__typ, &size, OPC_Item__typ, dim, typ, 1);
	(*x).offs += 4;
	xx = *x;
	(*x).offs += __ASHL(__ASHR(dim, 1), 3) + 4;
	__GUARDEQR(y, y__typ, OPC_Item) = yy;
	if (!__IN((*y).mode, 0x010006, 32)) {
		OPC_GenPop(&*y, y__typ);
	}
	if ((*y).descReg == -1) {
		OPC_loadDynArr(&*y, y__typ);
	}
	OPC_TypeSize(*y, &size, OPC_Item__typ, &step, &scale);
	OPC_MoveBlock(&*x, x__typ, &*y, y__typ, &size, OPC_Item__typ, step);
	(*y).mode = 17;
	(*y).adr = (*y).descReg;
	(*y).offs = 12;
	(*y).typ = OPT_linttyp;
	__GUARDEQR(x, x__typ, OPC_Item) = xx;
	(*x).typ = OPT_linttyp;
	while (dim > 0) {
		xx = *x;
		yy = *y;
		OPC_Move(&xx, OPC_Item__typ, &yy, OPC_Item__typ);
		(*x).offs += 4;
		(*y).offs += 4;
		dim -= 1;
	}
}

static INT32 OPC_ArgSize (OPT_Object par)
{
	OPT_Struct typ;
	INT32 size;
	size = 0;
	while (par != NIL) {
		typ = par->typ;
		if (par->mode == 2 || __IN(typ->form, 0x8400, 32)) {
			size += 4;
			if ((__IN(typ->comp, 0x50, 32) && typ->sysflag != 1)) {
				size += 4;
			}
		} else if (__MASK(typ->size, -4) != 0) {
			size += (typ->size + 4) - __MASK(typ->size, -4);
		} else {
			size += typ->size;
		}
		par = par->link;
	}
	return size;
}

static void OPC_EndCall (OPT_Object proc, OPT_Struct typ)
{
	OPC_Item Z, X, Y;
	if ((proc != NIL && proc->sysflag == 3) || (typ != NIL && typ->sysflag == 3)) {
		Z.mode = 15;
		Z.typ = OPT_ptrtyp;
		Z.node = NIL;
		Z.adr = -3;
		Z.offs = 0;
		Z.inx = -1;
		X.mode = 15;
		X.typ = OPT_ptrtyp;
		X.node = NIL;
		X.adr = -3;
		X.offs = 0;
		X.inx = -1;
		Y.mode = 3;
		Y.typ = OPT_ptrtyp;
		Y.node = NIL;
		if (proc != NIL) {
			Y.adr = OPC_ArgSize(proc->link);
		} else {
			Y.adr = OPC_ArgSize(typ->link);
		}
		Y.offs = 0;
		Y.inx = -1;
		OPC_Gen3(512, &Z, OPC_Item__typ, &X, OPC_Item__typ, &Y, OPC_Item__typ);
	}
}

void OPC_Call (OPC_Item *x, ADDRESS *x__typ, OPT_Object proc, OPT_Node node)
{
	INT16 n;
	OPC_Item sl;
	OPT_Object param;
	OPC_Item tag, t0, t1, self, y, z;
	INT32 label;
	if (__IN((*x).mode, 0x0240, 32) || (__IN((*x).mode, 0x80, 32) && (*x).mnolev >= 0)) {
		if (__IN(3, proc->conval->setval, 32)) {
			n = OPC_level - (*x).mnolev;
			if (__IN(24, OPM_parserOptions, 32)) {
				OPM_LogWLn();
				OPM_LogWStr((CHAR*)"Call/SL ", 9);
				if ((*x).node->obj != NIL) {
					OPM_LogWStr((*x).node->obj->name, 32);
				}
				OPM_LogWNum(OPC_level, 2);
				OPM_LogWStr((CHAR*)" -> ", 5);
				OPM_LogWNum((*x).mnolev, 2);
			}
			sl.mode = 1;
			sl.typ = OPT_linttyp;
			sl.mnolev = OPC_level;
			sl.inx = -1;
			sl.node = NIL;
			if (n == 0) {
				sl.mode = 15;
				sl.adr = -2;
				OPC_GenPush(&sl, OPC_Item__typ);
			} else if (n == 1) {
				sl.adr = 8;
				OPC_load(&sl, OPC_Item__typ);
				OPC_GenPush(&sl, OPC_Item__typ);
			} else {
				sl.adr = 8;
				OPC_load(&sl, OPC_Item__typ);
				sl.mode = 17;
				sl.offs = 8;
				while (n > 2) {
					OPC_load(&sl, OPC_Item__typ);
					sl.mode = 17;
					sl.offs = 8;
					n -= 1;
				}
				OPC_load(&sl, OPC_Item__typ);
				OPC_GenPush(&sl, OPC_Item__typ);
			}
		}
		OPC_GenCall(2080, proc->linkadr, proc->conval->intval - 4, node);
		if (((*x).mode != 9 && proc->linkadr < 0)) {
			proc->linkadr = -2 - (OPC_pc - 1);
		}
		OPC_EndCall(proc, NIL);
	} else if ((*x).mode == 7) {
		OPC_GenCall(2144, (*x).adr, proc->conval->intval - 4, node);
		OPC_EndCall(proc, NIL);
	} else if (__IN((*x).mode, 0x2020, 32)) {
		if (node->left->subcl == 1) {
			if (node->right->obj->typ->form == 13) {
				OPC_GetTdAdr(&node->right->obj->typ->BaseTyp->BaseTyp, &tag, OPC_Item__typ);
			} else {
				OPC_GetTdAdr(&node->right->obj->typ->BaseTyp, &tag, OPC_Item__typ);
			}
			OPC_load(&tag, OPC_Item__typ);
		} else {
			if (node->obj->mode == 2) {
				tag = OPC_lastTD;
			} else {
				tag.mode = 17;
				tag.typ = OPT_ptrtyp;
				tag.node = NIL;
				tag.adr = -3;
				tag.offs = 0;
				tag.inx = -1;
				OPC_DeRef(&tag, OPC_Item__typ);
				tag.mode = 17;
				tag.offs = -4;
				OPC_DeRef(&tag, OPC_Item__typ);
			}
		}
		(*x).adr = tag.adr;
		(*x).mode = 17;
		(*x).typ = OPT_ptrtyp;
		OPC_load(&*x, x__typ);
		OPC_GenCall(2112, (*x).adr, proc->conval->intval - 4, node);
		OPC_EndCall(proc, NIL);
	} else {
		__ASSERT((*x).typ->form == 14, 0);
		if ((*x).typ->sysflag == 5) {
			OPC_load(&*x, x__typ);
			param = (*x).typ->link;
			label = -1;
			self.mode = 15;
			self.adr = (*x).descReg;
			self.typ = OPT_ptrtyp;
			OPC_MakeCon(&y, OPC_Item__typ, OPT_ptrtyp, 0);
			OPC_Cmp(&z, OPC_Item__typ, &self, OPC_Item__typ, &y, OPC_Item__typ, 9);
			OPC_Jcc(&z, OPC_Item__typ, &label, NIL);
			OPC_GenPush(&self, OPC_Item__typ);
			OPC_FixLink(label);
			if (param == NIL) {
				OPC_GenCall(2112, (*x).adr, 0, node);
			} else {
				OPC_GenCall(2112, (*x).adr, param->adr, node);
				OPC_EndCall(proc, NIL);
			}
		} else {
			OPC_load(&*x, x__typ);
			param = (*x).typ->link;
			if (param == NIL) {
				OPC_GenCall(2112, (*x).adr, 0, node);
			} else {
				OPC_GenCall(2112, (*x).adr, param->adr, node);
				OPC_EndCall(proc, NIL);
			}
		}
	}
}

void OPC_PopResult (OPT_Node n, OPC_Item *z, ADDRESS *z__typ)
{
	if (n != NIL) {
		if ((n->typ->form == 14 && n->typ->sysflag == 5)) {
			(*z).typ = OPC_delegateType;
			(*z).mode = 15;
			(*z).adr = OPC_pc;
			(*z).descReg = OPC_pc - 1;
			OPC_GenPopReg(0, OPT_linttyp->form);
			(OPL_Instr->data)[__X(OPC_pc - 1, OPL_Instr->len[0])].src1 = (*z).descReg;
			(OPL_Instr->data)[__X(OPC_pc - 1, OPL_Instr->len[0])].op += 5;
		} else if (__IN(n->typ->form, 0x627e, 32)) {
			(*z).typ = n->typ;
			(*z).mode = 15;
			(*z).adr = OPC_pc;
			OPC_GenPopReg(0, (*z).typ->form);
		} else if (n->typ->form == 16) {
			(*z).typ = n->typ;
			(*z).mode = 15;
			(*z).adr = OPC_pc;
			(*z).offs = OPC_pc - 1;
			OPC_GenPopReg(0, OPT_linttyp->form);
			(OPL_Instr->data)[__X(OPC_pc - 1, OPL_Instr->len[0])].src1 = (*z).offs;
			(OPL_Instr->data)[__X(OPC_pc - 1, OPL_Instr->len[0])].op += 5;
		} else if (__IN(n->typ->comp, 0x4c, 32)) {
			OPC_GenPopReg(-1, 0);
		} else {
			__ASSERT(__IN(n->typ->form, 0x0180, 32), 0);
			(*z).typ = n->typ;
			(*z).mode = 15;
			(*z).adr = OPC_pc;
			OPC_GenPopReg(8, (*z).typ->form);
		}
	} else {
		OPC_GenPopReg(-1, 0);
	}
}

void OPC_AllocSDynArr (OPT_Object *proc)
{
	OPT_Object locals;
	OPC_Item t, t0, size, len, x, adj, shift;
	locals = (*proc)->scope->scope;
	while (locals != NIL) {
		if (locals->typ->comp == 3) {
			x.mode = 1;
			x.typ = locals->typ;
			x.adr = locals->linkadr;
			x.node = NIL;
			x.mnolev = locals->mnolev;
			OPC_MakeVar(&len, OPC_Item__typ, locals->typ->link);
			OPC_GenDimTrap(&len, OPC_Item__typ);
			OPC_ArrayBaseSize(&size, OPC_Item__typ, x);
			if ((len.mode == 3 && size.mode == 3)) {
				size.adr = size.adr * len.adr;
			} else {
				t = size;
				OPC_Mul(&size, OPC_Item__typ, &t, OPC_Item__typ, &len, OPC_Item__typ, 6);
			}
			__ASSERT(__IN(size.mode, 0x8008, 32), 130);
			OPC_MakeCon(&adj, OPC_Item__typ, OPT_linttyp, 3);
			t0 = size;
			OPC_Gen3(512, &size, OPC_Item__typ, &t0, OPC_Item__typ, &adj, OPC_Item__typ);
			OPC_MakeCon(&shift, OPC_Item__typ, OPT_linttyp, 2);
			t0 = size;
			OPC_Gen3(864, &size, OPC_Item__typ, &t0, OPC_Item__typ, &shift, OPC_Item__typ);
			OPC_Gen0(3328);
			(OPL_Instr->data)[__X(OPC_pc - 1, OPL_Instr->len[0])].src1 = size.adr;
			t = OPC_Stack;
			OPC_Move(&x, OPC_Item__typ, &t, OPC_Item__typ);
		}
		locals = locals->link;
	}
}

void OPC_Enter (OPT_Object proc, INT32 dataSize, OPT_Node node)
{
	OPT_Object par;
	OPC_Item x, z, t0, t1, size;
	INT8 step, scale;
	BOOLEAN useRef;
	useRef = (proc != NIL && proc->sysflag != 0);
	if (proc != NIL) {
		OPL_FixupLocalProcCall(proc);
		par = proc->link;
	} else {
		par = NIL;
	}
	OPC_Gen1(2208, dataSize, node);
	while (par != NIL) {
		if (par->mode == 1) {
			if (__IN(par->typ->comp, 0x28, 32)) {
				OPC_MakeVar(&x, OPC_Item__typ, par);
				OPC_TypeSize(x, &size, OPC_Item__typ, &step, &scale);
				__ASSERT(__IN(step, 0x010101, 32), 0);
				__ASSERT(__IN(scale, 0x07, 32), 0);
				OPC_load(&size, OPC_Item__typ);
				__ASSERT(size.mode == 15, 0);
				OPC_Gen2(960, &t0, OPC_Item__typ, &size, OPC_Item__typ);
				z.mode = 17;
				z.adr = -3;
				z.inx = t0.adr;
				z.scale = scale;
				z.typ = OPT_linttyp;
				OPC_loadAdr(&z, OPC_Item__typ);
				(OPL_Instr->data)[__X(OPC_pc - 1, OPL_Instr->len[0])].hint = 4;
				if (step != 0) {
					z.typ = OPT_linttyp;
					OPC_MakeCon(&t0, OPC_Item__typ, OPT_linttyp, -4);
					t1 = z;
					OPC_Gen3(736, &z, OPC_Item__typ, &t1, OPC_Item__typ, &t0, OPC_Item__typ);
					(OPL_Instr->data)[__X(OPC_pc - 1, OPL_Instr->len[0])].hint = 4;
				}
				OPC_MoveBlockReversed(&z, OPC_Item__typ, &x, OPC_Item__typ, &size, OPC_Item__typ, step);
				OPC_MakeVar(&x, OPC_Item__typ, par);
				x.typ = OPT_linttyp;
				z.mode = 15;
				z.adr = -3;
				OPC_Move(&x, OPC_Item__typ, &z, OPC_Item__typ);
			} else if (par->typ->comp == 4) {
				OPC_MakeCon(&x, OPC_Item__typ, OPT_linttyp, 0);
				OPC_GenPush(&x, OPC_Item__typ);
				OPC_MakeVar(&z, OPC_Item__typ, par);
				x.mode = 17;
				x.adr = -3;
				x.offs = 0;
				x.inx = -1;
				x.typ = par->typ;
				x.descReg = -1;
				OPC_CopyDynArr(&x, OPC_Item__typ, &z, OPC_Item__typ);
				OPC_GenPop(&x, OPC_Item__typ);
				OPC_MakeVar(&z, OPC_Item__typ, par);
				OPC_Move(&z, OPC_Item__typ, &x, OPC_Item__typ);
			} else if ((useRef && __IN(par->typ->comp, 0x44, 32))) {
				z.mode = 1;
				z.typ = OPT_linttyp;
				z.node = NIL;
				z.adr = par->linkadr;
				z.mnolev = par->mnolev;
				x.mode = 2;
				x.typ = OPT_linttyp;
				x.adr = par->adr;
				x.node = NIL;
				x.mnolev = par->mnolev;
				OPC_MakeCon(&size, OPC_Item__typ, OPT_linttyp, par->typ->size);
				OPC_MoveBlockReversed(&z, OPC_Item__typ, &x, OPC_Item__typ, &size, OPC_Item__typ, 16);
			}
		}
		par = par->link;
	}
}

void OPC_Return (OPC_Item *res, ADDRESS *res__typ, OPT_Object proc)
{
	OPC_Item res1, t, size, negsize;
	INT32 pReg;
	INT8 procform;
	OPT_Struct typ;
	OPC_Item tos, sp, ref, t1;
	INT8 step, scale;
	OPC_Item savedPC, savedFP, callerTOS;
	typ = proc->typ;
	procform = typ->form;
	if ((*res).mode == 18) {
		t = *res;
		if ((t.offs == -1 && t.inx == -1)) {
			OPC_MoveCoc(&*res, res__typ, &t, OPC_Item__typ);
			(OPL_Instr->data)[__X((*res).adr, OPL_Instr->len[0])].hint = 0;
		} else {
			OPC_MoveCoc(&*res, res__typ, &t, OPC_Item__typ);
			__ASSERT((OPL_Instr->data)[__X(OPC_pc - 2, OPL_Instr->len[0])].op == 2464, 0);
			pReg = (OPL_Instr->data)[__X(OPC_pc - 2, OPL_Instr->len[0])].src1;
			(OPL_Instr->data)[__X(pReg, OPL_Instr->len[0])].hint = 0;
		}
	} else {
		if ((*res).typ->form == 12 || __IN((*res).mode, 0xc0, 32)) {
			if ((*res).mnolev == 0) {
				OPC_GenLoadProc(320, &*res, res__typ, __MASK((*res).node->obj->adr, -65536), (*res).node);
			} else {
				OPC_GenLoadProc(352, &*res, res__typ, __ASHR((*res).node->obj->adr, 16), (*res).node);
			}
			if (typ->sysflag == 5) {
				OPC_MakeCon(&t1, OPC_Item__typ, OPT_linttyp, 0);
				OPC_load(&t1, OPC_Item__typ);
				(*res).descReg = t1.adr;
			}
		} else if ((procform != (*res).typ->form && (*res).typ->form != 11)) {
			__ASSERT(procform != 9, 0);
			OPC_Convert(&*res, res__typ, procform);
		}
		if (__IN((*res).typ->form, 0x0180, 32)) {
			OPC_loadf(&*res, res__typ);
		} else if (__IN(typ->comp, 0x28, 32)) {
			callerTOS.mode = 17;
			callerTOS.adr = -2;
			callerTOS.offs = proc->conval->intval;
			callerTOS.inx = -1;
			callerTOS.typ = OPT_linttyp;
			OPC_load(&callerTOS, OPC_Item__typ);
			sp = callerTOS;
			sp.mode = 17;
			sp.offs = 0;
			OPC_PushArrLen(proc, &*res, res__typ, &sp, OPC_Item__typ, 1);
			sp.offs -= 4;
			ref = sp;
			OPC_TypeSize(*res, &size, OPC_Item__typ, &step, &scale);
			if (size.mode == 3) {
				OPC_MakeCon(&negsize, OPC_Item__typ, OPT_linttyp, -size.adr - -__MASK(size.adr, -4));
				sp.offs += negsize.adr;
				if ((*res).mode != 1) {
					OPC_load(&negsize, OPC_Item__typ);
				}
			} else {
				OPC_load(&size, OPC_Item__typ);
				negsize.typ = OPT_linttyp;
				OPC_Gen2(960, &negsize, OPC_Item__typ, &size, OPC_Item__typ);
				if (__IN(step, 0x010100, 32)) {
					OPC_MakeCon(&t, OPC_Item__typ, OPT_linttyp, -4);
					t1 = negsize;
					OPC_Gen3(736, &negsize, OPC_Item__typ, &t1, OPC_Item__typ, &t, OPC_Item__typ);
				}
				sp.inx = negsize.adr;
				sp.scale = scale;
			}
			if ((*res).mode != 1) {
				t = OPC_Stack;
				t.mode = 17;
				t.offs = -12;
				t.inx = negsize.adr;
				t.scale = scale;
				OPC_loadAdr(&t, OPC_Item__typ);
				(OPL_Instr->data)[__X(OPC_pc - 1, OPL_Instr->len[0])].hint = 4;
			}
			OPC_loadAdr(&sp, OPC_Item__typ);
			t = sp;
			OPC_GenStore(416, &ref, OPC_Item__typ, &t, OPC_Item__typ);
			sp.mode = 17;
			sp.offs = 0;
			sp.inx = -1;
			savedFP.mode = 17;
			savedFP.adr = -2;
			savedFP.offs = 0;
			savedFP.inx = -1;
			savedFP.typ = OPT_linttyp;
			OPC_load(&savedFP, OPC_Item__typ);
			OPC_GenPush(&savedFP, OPC_Item__typ);
			savedPC.mode = 17;
			savedPC.adr = -2;
			savedPC.offs = 4;
			savedPC.inx = -1;
			savedPC.typ = OPT_linttyp;
			OPC_load(&savedPC, OPC_Item__typ);
			OPC_GenPush(&savedPC, OPC_Item__typ);
			t = sp;
			OPC_MoveBlockReversed(&t, OPC_Item__typ, &*res, res__typ, &size, OPC_Item__typ, step);
			t = sp;
			t.offs -= 4;
			OPC_GenStore(416, &t, OPC_Item__typ, &callerTOS, OPC_Item__typ);
			t = sp;
			t.offs -= 8;
			OPC_GenPop(&savedPC, OPC_Item__typ);
			OPC_GenStore(416, &t, OPC_Item__typ, &savedPC, OPC_Item__typ);
			t = sp;
			t.offs -= 12;
			OPC_GenPop(&savedFP, OPC_Item__typ);
			OPC_GenStore(416, &t, OPC_Item__typ, &savedFP, OPC_Item__typ);
			sp.offs -= 12;
			OPC_loadAdr(&sp, OPC_Item__typ);
			(OPL_Instr->data)[__X(OPC_pc - 1, OPL_Instr->len[0])].hint = 4;
			__ASSERT(sp.typ == OPT_linttyp, 0);
		} else if (typ->comp == 4) {
			t.mode = 17;
			t.adr = -2;
			t.offs = proc->conval->intval;
			t.typ = (*res).typ;
			t.inx = -1;
			OPC_load(&t, OPC_Item__typ);
			t.mode = 17;
			t.offs = 0;
			if ((*res).mode == 1) {
				OPC_Move(&t, OPC_Item__typ, &*res, res__typ);
			} else {
				OPC_CopyDynArr(&t, OPC_Item__typ, &*res, res__typ);
			}
		} else if (typ->form == 15) {
			__ASSERT(typ->comp != 4, 0);
			t.mode = 17;
			t.adr = -2;
			t.offs = proc->conval->intval;
			t.typ = (*res).typ;
			t.inx = -1;
			OPC_load(&t, OPC_Item__typ);
			if (typ->comp == 6) {
				size.mode = 17;
				size.adr = -2;
				size.offs = proc->conval->intval + 4;
				size.inx = -1;
				size.typ = OPT_linttyp;
			} else {
				OPC_MakeCon(&size, OPC_Item__typ, OPT_linttyp, typ->size);
			}
			OPC_MoveBlock(&t, OPC_Item__typ, &*res, res__typ, &size, OPC_Item__typ, 16);
		} else if (typ == OPT_hinttyp) {
			if ((*res).mode == 15) {
				(OPL_Instr->data)[__X((*res).adr, OPL_Instr->len[0])].hint = 0;
				(OPL_Instr->data)[__X((*res).offs, OPL_Instr->len[0])].hint = 2;
			} else {
				(*res).typ = OPT_linttyp;
				OPC_loadAdr(&*res, res__typ);
				(*res).mode = 17;
				res1 = *res;
				res1.offs += 4;
				OPC_load(&*res, res__typ);
				(OPL_Instr->data)[__X((*res).adr, OPL_Instr->len[0])].hint = 0;
				OPC_load(&res1, OPC_Item__typ);
				(OPL_Instr->data)[__X(res1.adr, OPL_Instr->len[0])].hint = 2;
			}
		} else if ((typ->form == 14 && typ->sysflag == 5)) {
			if ((*res).mode == 3) {
				OPC_load(&*res, res__typ);
				OPC_MakeCon(&t1, OPC_Item__typ, OPT_linttyp, 0);
				OPC_load(&t1, OPC_Item__typ);
				(*res).descReg = t1.adr;
			} else {
				OPC_load(&*res, res__typ);
			}
			(OPL_Instr->data)[__X((*res).adr, OPL_Instr->len[0])].hint = 0;
			(OPL_Instr->data)[__X((*res).descReg, OPL_Instr->len[0])].hint = 2;
		} else {
			OPC_load(&*res, res__typ);
			(OPL_Instr->data)[__X((*res).adr, OPL_Instr->len[0])].hint = 0;
		}
	}
}

void OPC_Exit (OPT_Object proc)
{
	INT32 size;
	OPC_Item ebp;
	if (proc == NIL) {
		OPC_Gen1(2240, 0, NIL);
		OPC_Gen1(2176, 0, NIL);
	} else if (__IN(proc->typ->comp, 0x28, 32)) {
		ebp.typ = OPT_linttyp;
		OPC_GenPop(&ebp, OPC_Item__typ);
		(OPL_Instr->data)[__X(OPC_pc - 1, OPL_Instr->len[0])].hint = 5;
		OPC_Gen1(2176, 0, NIL);
	} else {
		OPC_Gen1(2240, proc->conval->intval2, NIL);
		if (proc->sysflag == 3) {
			size = 0;
		} else if (proc->mode == 5 || proc->typ->form != 15) {
			size = proc->conval->intval - 8;
		} else if (proc->typ->comp == 6) {
			size = (proc->conval->intval - 8) + 8;
		} else {
			size = (proc->conval->intval - 8) + 4;
		}
		OPC_Gen1(2176, size, NIL);
	}
}

void OPC_Lock (OPC_Item self, OPC_Item excl)
{
	if (self.typ->comp == 6) {
		OPC_loadAdr(&self, OPC_Item__typ);
	} else {
		OPC_load(&self, OPC_Item__typ);
	}
	OPC_GenPush(&self, OPC_Item__typ);
	OPC_GenPush(&excl, OPC_Item__typ);
	OPC_GenCall(2144, 458999, 4, NIL);
}

void OPC_Unlock (OPC_Item self, OPC_Item excl)
{
	if (self.typ->comp == 6) {
		OPC_loadAdr(&self, OPC_Item__typ);
	} else {
		OPC_load(&self, OPC_Item__typ);
	}
	OPC_GenPush(&self, OPC_Item__typ);
	OPC_GenPush(&excl, OPC_Item__typ);
	OPC_GenCall(2144, 524534, 4, NIL);
}

void OPC_Await (OPC_Item z, OPC_Item self, OPC_Item y)
{
	if (z.typ == OPT_niltyp) {
		OPC_MakeCon(&z, OPC_Item__typ, OPT_linttyp, -1);
	} else {
		OPC_GenLoadProc(320, &z, OPC_Item__typ, __MASK(z.node->obj->adr, -65536), z.node);
	}
	OPC_GenPush(&z, OPC_Item__typ);
	z.mode = 15;
	z.adr = -2;
	OPC_GenPush(&z, OPC_Item__typ);
	if (self.mode != 3) {
		if (self.typ->comp == 6) {
			OPC_loadAdr(&self, OPC_Item__typ);
		} else {
			OPC_load(&self, OPC_Item__typ);
		}
	}
	OPC_GenPush(&self, OPC_Item__typ);
	OPC_GenPush(&y, OPC_Item__typ);
	OPC_GenCall(2144, 393465, 8, NIL);
}

void OPC_Trap (INT32 n, OPT_Node node)
{
	OPC_Gen1(2048, n, node);
}

void OPC_GenAsm (OPT_Node n)
{
	OPC_Gen1(3296, 0, n);
}

void OPC_GenDimTrap (OPC_Item *len, ADDRESS *len__typ)
{
	OPC_Item const_;
	if (__IN(0, OPM_codeOptions, 32)) {
		OPC_MakeCon(&const_, OPC_Item__typ, OPT_linttyp, -1);
		OPC_load(&*len, len__typ);
		OPC_GenFlags(1056, &*len, len__typ, &const_, OPC_Item__typ);
		OPC_Gen1(2944, 9, NIL);
	}
}

void OPC_Case (OPC_Item *x, ADDRESS *x__typ, INT32 low, INT32 high, INT32 *tab, INT32 *L, OPT_Node node)
{
	OPC_Item c, y;
	OPC_MakeCon(&c, OPC_Item__typ, OPT_linttyp, low);
	if ((*x).typ->form != 6) {
		if ((*x).mode == 3) {
			(*x).typ = OPT_linttyp;
			OPC_load(&*x, x__typ);
		} else {
			OPC_Convert(&*x, x__typ, 6);
		}
	} else {
		OPC_load(&*x, x__typ);
	}
	if (low != 0) {
		OPC_Gen3(544, &*x, x__typ, &*x, x__typ, &c, OPC_Item__typ);
	}
	c.adr = high - low;
	OPC_GenFlags(1056, &*x, x__typ, &c, OPC_Item__typ);
	*L = -2 - OPC_pc;
	OPC_Gen1(1696, -1, node);
	OPL_AllocCaseTab(low, high, &*tab);
	c.mode = 16;
	c.typ = OPT_linttyp;
	c.adr = *tab;
	c.inx = (*x).adr;
	c.scale = 2;
	c.node = NIL;
	OPC_GenLoad(32, &y, OPC_Item__typ, &c, OPC_Item__typ);
	OPC_Gen1(1920, y.adr, node);
}

void OPC_CaseFixup (INT32 tab, INT32 elseLabel, INT32 len)
{
	OPC_InitInstr(2432, 0, 0, NIL);
	(OPL_Instr->data)[__X(OPC_pc, OPL_Instr->len[0])].src1 = tab;
	(OPL_Instr->data)[__X(OPC_pc, OPL_Instr->len[0])].src2 = elseLabel;
	(OPL_Instr->data)[__X(OPC_pc, OPL_Instr->len[0])].inx = __ASHL(len, 2);
	OPC_pc += 1;
}

static void EnumPtrs(void (*P)(void*))
{
	__ENUMR(&OPC_True, OPC_Item__typ, 32, 1, P);
	__ENUMR(&OPC_False, OPC_Item__typ, 32, 1, P);
	__ENUMR(&OPC_Stack, OPC_Item__typ, 32, 1, P);
	__ENUMR(&OPC_ebp, OPC_Item__typ, 32, 1, P);
	__ENUMR(&OPC_lastTD, OPC_Item__typ, 32, 1, P);
	P(OPC_delegateType);
}

__TDESC(OPC_Item, 1, 2) = {__TDFLDS("Item", 32), {4, 8, -12}};

export void *OPC__init(void)
{
	__DEFMOD;
	__MODULE_IMPORT(OPL);
	__MODULE_IMPORT(OPM);
	__MODULE_IMPORT(OPO);
	__MODULE_IMPORT(OPT);
	__REGMOD("OPC", EnumPtrs);
	__REGCMD("Init", OPC_Init);
	__REGCMD("PushRegs", OPC_PushRegs);
	__INITYP(OPC_Item, OPC_Item, 0);
/* BEGIN */
	OPC_MakeCon(&OPC_True, OPC_Item__typ, OPT_booltyp, 1);
	OPC_MakeCon(&OPC_False, OPC_Item__typ, OPT_booltyp, 0);
	OPC_Stack.mode = 15;
	OPC_Stack.adr = -3;
	OPC_Stack.node = NIL;
	OPC_Stack.typ = OPT_linttyp;
	OPC_Stack.offs = 0;
	OPC_Stack.inx = -1;
	OPC_ebp.mode = 15;
	OPC_ebp.adr = -2;
	OPC_ebp.node = NIL;
	OPC_ebp.typ = OPT_linttyp;
	OPC_formTab[0] = 0;
	OPC_formTab[1] = 2;
	OPC_formTab[2] = 2;
	OPC_formTab[3] = 2;
	OPC_formTab[4] = 2;
	OPC_formTab[5] = 1;
	OPC_formTab[6] = 0;
	OPC_formTab[9] = 0;
	OPC_formTab[13] = 0;
	OPC_formTab[14] = 0;
	OPC_formTab[11] = 0;
	OPC_formTab[15] = 0;
	OPC_formTab[7] = 3;
	OPC_formTab[8] = 4;
	OPC_CCtab[0][0] = 1504;
	OPC_CCtab[0][1] = 1536;
	OPC_CCtab[0][2] = 1568;
	OPC_CCtab[0][3] = 1600;
	OPC_CCtab[0][4] = 1632;
	OPC_CCtab[0][5] = 1664;
	OPC_CCtab[1][0] = 1504;
	OPC_CCtab[1][1] = 1536;
	OPC_CCtab[1][2] = 1760;
	OPC_CCtab[1][3] = 1792;
	OPC_CCtab[1][4] = 1696;
	OPC_CCtab[1][5] = 1728;
	OPC_InvCCtab[0] = 1536;
	OPC_InvCCtab[1] = 1504;
	OPC_InvCCtab[2] = 1664;
	OPC_InvCCtab[3] = 1632;
	OPC_InvCCtab[4] = 1600;
	OPC_InvCCtab[5] = 1568;
	OPC_InvCCtab[6] = 1792;
	OPC_InvCCtab[7] = 1760;
	OPC_InvCCtab[8] = 1728;
	OPC_InvCCtab[9] = 1696;
	OPC_InvCCtab[10] = 1856;
	OPC_InvCCtab[11] = 1824;
	OPC_delegateType = OPT_NewStr(14, 1);
	OPC_delegateType->BaseTyp = OPT_notyp;
	OPC_delegateType->link = NIL;
	OPC_delegateType->sysflag = 5;
	__ENDMOD;
}
