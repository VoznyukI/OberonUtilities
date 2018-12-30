/* voc 2.1.0 [2017/09/06]. Bootstrapping compiler for address size 8, alignment 8. xtaSv */

#ifndef OPC__h
#define OPC__h

#include "SYSTEM.h"
#include "OPT.h"

typedef
	struct OPC_Item {
		INT8 mode, mnolev, scale;
		OPT_Struct typ;
		OPT_Node node;
		INT32 adr, offs, inx, descReg, descOffs;
	} OPC_Item;


import INT8 OPC_level;
import INT16 OPC_pc;

import ADDRESS *OPC_Item__typ;

import void OPC_AbsVal (OPC_Item *z, ADDRESS *z__typ, OPC_Item *x, ADDRESS *x__typ);
import void OPC_Add (OPC_Item *z, ADDRESS *z__typ, OPC_Item *x, ADDRESS *x__typ, OPC_Item *y, ADDRESS *y__typ, INT16 f);
import void OPC_AllocSDynArr (OPT_Object *proc);
import void OPC_AllocateStatic (OPC_Item *tos, ADDRESS *tos__typ, INT32 size);
import void OPC_And (OPC_Item *z, ADDRESS *z__typ, OPC_Item *x, ADDRESS *x__typ, OPC_Item *y, ADDRESS *y__typ);
import void OPC_Ash (OPC_Item *z, ADDRESS *z__typ, OPC_Item *x, ADDRESS *x__typ, OPC_Item *y, ADDRESS *y__typ);
import void OPC_Assign (OPC_Item *z, ADDRESS *z__typ, OPC_Item *x, ADDRESS *x__typ);
import void OPC_Await (OPC_Item z, OPC_Item self, OPC_Item y);
import void OPC_Call (OPC_Item *x, ADDRESS *x__typ, OPT_Object proc, OPT_Node node);
import void OPC_CallRecBody (OPC_Item *self, ADDRESS *self__typ, OPC_Item *body, ADDRESS *body__typ, OPT_Struct typ);
import void OPC_Cap (OPC_Item *z, ADDRESS *z__typ, OPC_Item *x, ADDRESS *x__typ);
import void OPC_Case (OPC_Item *x, ADDRESS *x__typ, INT32 low, INT32 high, INT32 *tab, INT32 *L, OPT_Node node);
import void OPC_CaseFixup (INT32 tab, INT32 elseLabel, INT32 len);
import void OPC_Cmp (OPC_Item *z, ADDRESS *z__typ, OPC_Item *x, ADDRESS *x__typ, OPC_Item *y, ADDRESS *y__typ, INT16 rel);
import void OPC_CondAnd (OPC_Item *x, ADDRESS *x__typ);
import void OPC_CondOr (OPC_Item *x, ADDRESS *x__typ);
import void OPC_Convert (OPC_Item *x, ADDRESS *x__typ, INT8 form);
import void OPC_Copy (OPC_Item *z, ADDRESS *z__typ, OPC_Item *x, ADDRESS *x__typ);
import void OPC_CorrectStackAdr (OPC_Item *x, ADDRESS *x__typ, INT32 size, INT32 dynblocks);
import void OPC_DeRef (OPC_Item *x, ADDRESS *x__typ);
import void OPC_DefLabel (INT32 *L);
import void OPC_Div (OPC_Item *z, ADDRESS *z__typ, OPC_Item *x, ADDRESS *x__typ, OPC_Item *y, ADDRESS *y__typ, INT16 f);
import void OPC_Enter (OPT_Object proc, INT32 dataSize, OPT_Node node);
import void OPC_Exit (OPT_Object proc);
import void OPC_Field (OPC_Item *x, ADDRESS *x__typ, INT32 offset);
import void OPC_FixLink (INT32 L);
import void OPC_GenAsm (OPT_Node n);
import void OPC_GenDimTrap (OPC_Item *len, ADDRESS *len__typ);
import void OPC_GetTdAdr (OPT_Struct *typ, OPC_Item *tag, ADDRESS *tag__typ);
import void OPC_In (OPC_Item *z, ADDRESS *z__typ, OPC_Item *x, ADDRESS *x__typ, OPC_Item *y, ADDRESS *y__typ);
import void OPC_IncDec (OPC_Item *z, ADDRESS *z__typ, OPC_Item *x, ADDRESS *x__typ, BOOLEAN increment);
import void OPC_Include (OPC_Item *z, ADDRESS *z__typ, OPC_Item *x, ADDRESS *x__typ, BOOLEAN incl);
import void OPC_Index (OPC_Item *z, ADDRESS *z__typ, OPC_Item *index, ADDRESS *index__typ);
import void OPC_Init (void);
import void OPC_Jcc (OPC_Item *x, ADDRESS *x__typ, INT32 *loc, OPT_Node node);
import void OPC_Jmp (INT32 *loc, OPT_Node node);
import void OPC_Jncc (OPC_Item *x, ADDRESS *x__typ, INT32 *loc, OPT_Node node);
import void OPC_Len (OPC_Item *len, ADDRESS *len__typ, OPC_Item *x, ADDRESS *x__typ, OPC_Item *y, ADDRESS *y__typ);
import void OPC_Lock (OPC_Item self, OPC_Item excl);
import void OPC_MakeCon (OPC_Item *cons, ADDRESS *cons__typ, OPT_Struct typ, INT32 val);
import INT32 OPC_MergedLinks (INT32 L0, INT32 L1);
import void OPC_Method (OPC_Item *x, ADDRESS *x__typ, OPT_Object obj);
import void OPC_Mod (OPC_Item *z, ADDRESS *z__typ, OPC_Item *x, ADDRESS *x__typ, OPC_Item *y, ADDRESS *y__typ);
import void OPC_Msk (OPC_Item *z, ADDRESS *z__typ, OPC_Item *x, ADDRESS *x__typ, OPC_Item *y, ADDRESS *y__typ);
import void OPC_Mul (OPC_Item *z, ADDRESS *z__typ, OPC_Item *x, ADDRESS *x__typ, OPC_Item *y, ADDRESS *y__typ, INT16 f);
import void OPC_MulDim (OPC_Item *nofelem, ADDRESS *nofelem__typ, OPC_Item *len, ADDRESS *len__typ);
import void OPC_Neg (OPC_Item *z, ADDRESS *z__typ, OPC_Item *x, ADDRESS *x__typ);
import void OPC_NewArray (OPC_Item *z, ADDRESS *z__typ, OPC_Item *nofelem, ADDRESS *nofelem__typ, INT32 nofdim, OPT_Struct typ, BOOLEAN dimUsed);
import void OPC_NewRec (OPC_Item *z, ADDRESS *z__typ, OPT_Struct typ);
import void OPC_NewStat (INT32 textPos);
import void OPC_NewSys (OPC_Item *z, ADDRESS *z__typ, OPC_Item *x, ADDRESS *x__typ);
import void OPC_Not (OPC_Item *z, ADDRESS *z__typ, OPC_Item *x, ADDRESS *x__typ);
import void OPC_Odd (OPC_Item *z, ADDRESS *z__typ, OPC_Item *x, ADDRESS *x__typ);
import void OPC_Or (OPC_Item *z, ADDRESS *z__typ, OPC_Item *x, ADDRESS *x__typ, OPC_Item *y, ADDRESS *y__typ);
import void OPC_Parameter (OPC_Item *ap, ADDRESS *ap__typ, OPT_Object fp, BOOLEAN apIsDeref, BOOLEAN alwaysRef);
import void OPC_PopLen (OPC_Item *block, ADDRESS *block__typ);
import void OPC_PopResult (OPT_Node n, OPC_Item *z, ADDRESS *z__typ);
import INT32 OPC_PrepRetDest (OPC_Item z);
import void OPC_Procedure (OPC_Item *proc, ADDRESS *proc__typ, OPT_Node n);
import void OPC_PushLen (OPC_Item *z, ADDRESS *z__typ);
import void OPC_PushRegs (void);
import void OPC_PushRetDesc (OPC_Item *x, ADDRESS *x__typ, OPC_Item *tos, ADDRESS *tos__typ);
import void OPC_Relation (OPC_Item *x, ADDRESS *x__typ);
import void OPC_RemoveStatic (INT32 size);
import void OPC_ResetStack (INT32 dynblocks);
import void OPC_Return (OPC_Item *res, ADDRESS *res__typ, OPT_Object proc);
import void OPC_SYSdop (OPC_Item *z, ADDRESS *z__typ, OPC_Item *x, ADDRESS *x__typ, OPC_Item *y, ADDRESS *y__typ, INT8 subcl);
import void OPC_SYSgetput (OPC_Item *z, ADDRESS *z__typ, OPC_Item *x, ADDRESS *x__typ, BOOLEAN getfn);
import void OPC_SYSgetputReg (OPC_Item *z, ADDRESS *z__typ, OPC_Item *x, ADDRESS *x__typ, BOOLEAN getrfn);
import void OPC_SYSinterrupt (BOOLEAN clear);
import void OPC_SYSmop (OPC_Item *z, ADDRESS *z__typ, OPC_Item *x, ADDRESS *x__typ, INT8 subcl, OPT_Struct typ);
import void OPC_SYSmove (OPC_Item *z, ADDRESS *z__typ, OPC_Item *x, ADDRESS *x__typ, OPC_Item *nofBytes, ADDRESS *nofBytes__typ);
import void OPC_SYSportio (OPC_Item *z, ADDRESS *z__typ, OPC_Item *x, ADDRESS *x__typ, BOOLEAN pin);
import void OPC_SetElem (OPC_Item *z, ADDRESS *z__typ, OPC_Item *x, ADDRESS *x__typ);
import void OPC_SetRange (OPC_Item *z, ADDRESS *z__typ, OPC_Item *x, ADDRESS *x__typ, OPC_Item *y, ADDRESS *y__typ);
import void OPC_Sub (OPC_Item *z, ADDRESS *z__typ, OPC_Item *x, ADDRESS *x__typ, OPC_Item *y, ADDRESS *y__typ, INT16 f);
import void OPC_Trap (INT32 n, OPT_Node node);
import void OPC_TypeTest (OPC_Item *x, ADDRESS *x__typ, OPT_Struct testtyp, BOOLEAN guard, BOOLEAN equal, BOOLEAN varRec);
import void OPC_Unlock (OPC_Item self, OPC_Item excl);
import void *OPC__init(void);


#endif // OPC
