/* voc 2.1.0 [2017/09/06]. Bootstrapping compiler for address size 8, alignment 8. xtaSv */

#define SHORTINT INT8
#define INTEGER  INT16
#define LONGINT  INT32
#define SET      UINT32

#include "SYSTEM.h"
#include "OPC.h"
#include "OPL.h"
#include "OPM.h"
#include "OPO.h"
#include "OPS.h"
#include "OPT.h"
#include "Oberon.h"

typedef
	void (*OPV_ParamAdrProc)(OPT_Object*, INT32*, INT32*, BOOLEAN, BOOLEAN, BOOLEAN);


export BOOLEAN OPV_dumpCode;
export OPS_Name OPV_ProcName;
export INT16 OPV_EntryNr;
static INT32 OPV_ExitChain;
static BOOLEAN OPV_allocTd;
static OPC_Item OPV_dummy;
static OPV_ParamAdrProc OPV_ParamAdr[6];


export void OPV_AdrAndSize (OPT_Object topScope);
static void OPV_AlignBlock (INT32 adr, INT32 *dsize);
static void OPV_AlignFld (INT32 *offset, INT32 elemsize);
static void OPV_AlignPar (INT32 *elemsize);
static void OPV_AlignRec (INT32 *size);
static void OPV_AlignVar (INT32 *adr, INT32 elemsize);
static void OPV_AllocAddEntries (OPT_Object obj);
static void OPV_AllocFld (INT32 *offset, INT32 *this, INT32 elemsize);
static void OPV_AllocPar (INT32 *adr, INT32 *this, INT32 elemsize);
static void OPV_AllocVar (INT32 *adr, INT32 *this, INT32 elemsize);
static INT32 OPV_ArgSize (OPT_Object par);
export void OPV_AssignEntries (OPT_Object obj, BOOLEAN browse);
static void OPV_AssignOwnEntries (OPT_Object obj);
static void OPV_AssignTent (OPT_Object obj);
static void OPV_Call (OPT_Node proc, OPC_Item *res, ADDRESS *res__typ, BOOLEAN assignment);
static void OPV_CallLR (OPT_Node proc, OPC_Item *res, ADDRESS *res__typ, BOOLEAN assignment);
static void OPV_CallRL (OPT_Node proc, OPC_Item *res, ADDRESS *res__typ, BOOLEAN assignment);
static void OPV_CaseStat (OPT_Node n, OPT_Node selfForUnlock);
static void OPV_Designator (OPT_Node n, OPC_Item *x, ADDRESS *x__typ);
static void OPV_Dim (OPC_Item *z, ADDRESS *z__typ, OPC_Item *nofelem, ADDRESS *nofelem__typ, OPT_Node n, OPT_Struct typ, INT32 nofdim);
static void OPV_Expression (OPT_Node n, OPC_Item *z, ADDRESS *z__typ, OPT_Node selfForUnlock);
static void OPV_FindMth (INT8 curmod, OPS_Name name, OPT_Struct typ, OPT_Object *res);
static void OPV_IfStat (OPT_Node n, OPT_Node selfForUnlock, INT32 *Lfix, INT32 *Lcfix, BOOLEAN else_);
static void OPV_IncAdr (INT32 *adr, INT32 s);
export void OPV_Init (INT32 bpc);
export void OPV_Module (OPT_Node prog);
static void OPV_ParamAdrLR (OPT_Object *firstPar, INT32 *psize, INT32 *dsize, BOOLEAN TProc, BOOLEAN Inline, BOOLEAN allocDesc);
static void OPV_ParamAdrRL (OPT_Object *firstPar, INT32 *psize, INT32 *dsize, BOOLEAN TProc, BOOLEAN Inline, BOOLEAN allocDesc);
static void OPV_ProcSize (OPT_Object obj, BOOLEAN firstpass);
static void OPV_ProcSize0 (OPT_Object obj, BOOLEAN firstpass);
static BOOLEAN OPV_RecursionTest (OPT_Struct typ, INT32 mode);
static void OPV_Statement (OPT_Node n, OPT_Node selfForUnlock);
static void OPV_Traverse (OPT_Object obj, BOOLEAN exported);
export void OPV_TypSize (OPT_Struct typ, BOOLEAN allocDesc);
static void OPV_TypeName (OPT_Struct t);
static void OPV_VarAdr (OPT_Object var, INT32 *dsize);
static void OPV_VisitTProcs (OPT_Object obj);


void OPV_Init (INT32 bpc)
{
	INT16 res;
	OPV_allocTd = 1;
	if (__IN(7, OPM_parserOptions, 32)) {
		OPM_breakpc = bpc;
	} else {
		OPM_breakpc = 2147483647;
	}
	if (OPV_dumpCode) {
		Oberon_Call((CHAR*)"OPI.Init", 9, Oberon_Par, 0, &res);
	}
}

static void OPV_IncAdr (INT32 *adr, INT32 s)
{
	if ((s >= 0 && *adr <= 2147483647 - s) || (s < 0 && (INT64)*adr >= (-2147483647-1) - (INT64)s)) {
		*adr += s;
	} else {
		OPM_err(242);
	}
}

static void OPV_AlignFld (INT32 *offset, INT32 elemsize)
{
	if (elemsize >= 4) {
		OPV_IncAdr(&*offset, __MASK(-*offset, -4));
	} else if (elemsize == 2) {
		OPV_IncAdr(&*offset, __MASK(*offset, -2));
	}
}

static void OPV_AllocFld (INT32 *offset, INT32 *this, INT32 elemsize)
{
	*this = *offset;
	OPV_IncAdr(&*offset, elemsize);
}

static void OPV_AlignRec (INT32 *size)
{
	OPV_IncAdr(&*size, __MASK(-*size, -4));
}

static void OPV_AlignPar (INT32 *elemsize)
{
	OPV_IncAdr(&*elemsize, __MASK(-*elemsize, -4));
}

static void OPV_AllocPar (INT32 *adr, INT32 *this, INT32 elemsize)
{
	OPV_IncAdr(&*adr, elemsize);
	*this = *adr;
}

static void OPV_AlignVar (INT32 *adr, INT32 elemsize)
{
	if (elemsize >= 4) {
		OPV_IncAdr(&*adr, -__MASK(*adr, -4));
	} else if (elemsize == 2) {
		OPV_IncAdr(&*adr, -__MASK(*adr, -2));
	}
}

static void OPV_AllocVar (INT32 *adr, INT32 *this, INT32 elemsize)
{
	OPV_IncAdr(&*adr, -elemsize);
	*this = *adr;
}

static void OPV_AlignBlock (INT32 adr, INT32 *dsize)
{
	OPV_IncAdr(&adr, -__MASK(adr, -4));
	*dsize = -adr;
}

static BOOLEAN OPV_RecursionTest (OPT_Struct typ, INT32 mode)
{
	OPT_Object p;
	if (typ != NIL) {
		if (typ->rectest < 0) {
			return 0;
		} else if (typ->rectest < mode || typ->rectest > 5) {
			if (typ->form == 15) {
				typ->rectest = -typ->rectest;
				if (!OPV_RecursionTest(typ->BaseTyp, mode)) {
					return 0;
				}
				if (typ->comp == 6) {
					p = typ->link;
					while ((p != NIL && p->mode == 4)) {
						if (!OPV_RecursionTest(p->typ, 2)) {
							OPM_errpos = p->conval->intval;
							OPM_err(58);
							p->typ = OPT_undftyp;
						}
						p = p->link;
					}
				}
			}
		}
		typ->rectest = mode;
	}
	return 1;
}

void OPV_TypSize (OPT_Struct typ, BOOLEAN allocDesc)
{
	INT16 f, c;
	INT32 offset, size, dummy;
	OPT_Object fld;
	OPT_Struct btyp, ftyp;
	BOOLEAN sizeUndef, doAlloc;
	if (typ == OPT_undftyp) {
		OPM_err(58);
	} else {
		sizeUndef = typ->size == -1;
		if (!OPV_RecursionTest(typ, 1)) {
			OPM_errpos = typ->txtpos;
			OPM_err(58);
			typ->BaseTyp = OPT_undftyp;
		}
		doAlloc = (((((allocDesc && typ->tdadr == -1)) && typ->offset == -1)) && typ->sysflag != 6);
		if (sizeUndef || doAlloc) {
			if (doAlloc) {
				typ->tdadr = -2;
			}
			f = typ->form;
			c = typ->comp;
			btyp = typ->BaseTyp;
			if (c == 6) {
				if (btyp == NIL) {
					offset = 0;
				} else {
					OPV_TypSize(btyp, allocDesc);
					offset = btyp->size;
				}
				fld = typ->link;
				while (fld != NIL) {
					if (fld->mode == 4) {
						ftyp = fld->typ;
						OPV_TypSize(ftyp, allocDesc);
						if (sizeUndef) {
							size = ftyp->size;
							while (ftyp->comp == 2) {
								ftyp = ftyp->BaseTyp;
							}
							OPV_AlignFld(&offset, ftyp->size);
							OPV_AllocFld(&offset, &fld->adr, size);
						}
					}
					fld = fld->link;
				}
				if (sizeUndef) {
					OPV_AlignRec(&offset);
					typ->size = offset;
				}
				if ((doAlloc && typ->mno <= 0)) {
					if (OPV_allocTd) {
						OPL_AllocTypDesc(typ);
					}
					OPV_Traverse(typ->link, 1);
					OPV_Traverse(typ->link, 0);
				}
				if (btyp == NIL) {
					typ->n = 0;
				} else {
					typ->n = btyp->n;
				}
				if ((typ->strobj != NIL && __IN(1, typ->strobj->conval->setval, 32))) {
					OPV_VisitTProcs(typ->strobj);
				}
				OPV_VisitTProcs(typ->link);
			} else if (__IN(c, 0x3c, 32)) {
				OPV_TypSize(btyp, allocDesc);
				if (sizeUndef) {
					switch (c) {
						case 2: 
							typ->size = typ->n * btyp->size;
							break;
						case 3: 
							typ->size = 4;
							break;
						case 5: 
							typ->size = __ASHL(typ->n + 1, 2) + 4;
							break;
						case 4: 
							typ->size = 4;
							break;
						default: __CASECHK;
					}
				}
				if (__IN(btyp->comp, 0x3c, 32)) {
					typ->offset = btyp->offset + 4;
				} else {
					typ->offset = 4;
				}
			} else if (f == 13) {
				typ->size = 4;
				if (doAlloc) {
					OPV_TypSize(btyp, allocDesc);
				}
			} else if (f == 14) {
				if (typ->sysflag == 5) {
					typ->size = 8;
				} else {
					typ->size = 4;
				}
				if (doAlloc) {
					OPV_TypSize(btyp, 1);
					size = 8;
				}
				(*OPV_ParamAdr[__X(typ->sysflag, 6)])(&typ->link, &size, &dummy, 0, 0, allocDesc);
			} else {
				__HALT(99);
			}
		}
	}
}

static void OPV_ParamAdrLR (OPT_Object *firstPar, INT32 *psize, INT32 *dsize, BOOLEAN TProc, BOOLEAN Inline, BOOLEAN allocDesc)
{
	OPT_Object par;
	OPT_Struct typ;
	INT32 adr, s;
	adr = 0;
	if (TProc) {
		par = (*firstPar)->link;
	} else {
		par = *firstPar;
	}
	while (par != NIL) {
		typ = par->typ;
		OPV_TypSize(typ, allocDesc);
		if (par->mode == 2) {
			if (typ->comp == 6) {
				s = 8;
				if (typ->sysflag == 1) {
					s -= 4;
				}
			} else if (typ->comp == 5) {
				s = typ->size;
			} else {
				s = 4;
			}
		} else {
			s = typ->size;
		}
		OPV_AlignPar(&s);
		OPV_AllocPar(&adr, &par->adr, s);
		par = par->link;
	}
	if (TProc) {
		OPV_TypSize((*firstPar)->typ, 1);
		if ((*firstPar)->mode == 2) {
			s = 8;
		} else {
			s = (*firstPar)->typ->size;
		}
		OPV_AlignPar(&s);
		OPV_AllocPar(&adr, &(*firstPar)->adr, s);
	}
	*psize = *psize + adr;
	par = *firstPar;
	if (!Inline) {
		while (par != NIL) {
			par->adr = *psize - par->adr;
			par->linkadr = par->adr;
			par = par->link;
		}
	}
}

static void OPV_ParamAdrRL (OPT_Object *firstPar, INT32 *psize, INT32 *dsize, BOOLEAN TProc, BOOLEAN Inline, BOOLEAN allocDesc)
{
	OPT_Object par, parOld;
	OPT_Struct typ;
	INT32 adr, s;
	BOOLEAN stop;
	__ASSERT(!Inline, 0);
	adr = 0;
	par = *firstPar;
	if (par != NIL) {
		stop = 0;
		while (par->link != NIL) {
			par = par->link;
		}
		while (!stop) {
			stop = par == *firstPar;
			typ = par->typ;
			OPV_TypSize(typ, allocDesc);
			if (typ->comp == 5) {
				s = typ->size;
				if (typ->sysflag == 1) {
					s = 4;
				}
			} else if (par->mode == 2 || (typ->size > 4 && typ->form != 8)) {
				if ((typ->comp == 6 && par->mode == 2)) {
					s = 8;
					if (typ->sysflag == 1) {
						s -= 4;
					}
				} else {
					s = 4;
				}
			} else {
				s = typ->size;
			}
			OPV_AlignPar(&s);
			OPV_AllocPar(&adr, &par->adr, s);
			parOld = par;
			par = *firstPar;
			while ((!stop && par->link != parOld)) {
				par = par->link;
			}
		}
	}
	*psize = *psize + adr;
	par = *firstPar;
	if (par != NIL) {
		stop = 0;
		while (par->link != NIL) {
			par = par->link;
		}
		while (!stop) {
			stop = par == *firstPar;
			par->adr = *psize - par->adr;
			if ((par->mode == 1 && __IN(par->typ->comp, 0x44, 32))) {
				*dsize = *dsize + par->typ->size;
				par->linkadr = -*dsize;
			} else {
				par->linkadr = par->adr;
			}
			parOld = par;
			par = *firstPar;
			while ((!stop && par->link != parOld)) {
				par = par->link;
			}
		}
	}
}

static void OPV_VarAdr (OPT_Object var, INT32 *dsize)
{
	INT32 adr, s;
	OPT_Object list;
	adr = -*dsize;
	list = var;
	while (var != NIL) {
		if ((var->link2 == NIL && var->vis == 0)) {
			OPV_TypSize(var->typ, 1);
			s = var->typ->size;
			OPV_AlignVar(&adr, s);
			OPV_AllocVar(&adr, &var->linkadr, s);
			var->adr = 0;
		}
		var = var->link;
	}
	OPV_AlignBlock(adr, &*dsize);
	while (list != NIL) {
		if (list->link2 != NIL) {
			list->linkadr = list->link2->adr + *dsize;
		}
		list = list->link;
	}
}

static INT32 OPV_ArgSize (OPT_Object par)
{
	INT32 size;
	INT8 comp;
	OPT_Struct typ;
	size = 0;
	while (par != NIL) {
		typ = par->typ;
		comp = typ->comp;
		if (comp == 5) {
			size += typ->size;
		} else if (par->mode == 2) {
			if (comp == 6) {
				size += 8;
			} else {
				size += 4;
			}
		} else if (par->typ->form == 8) {
			size += 8;
		} else if (__IN(comp, 0x54, 32)) {
			size += typ->size;
			OPV_AlignPar(&size);
		} else {
			size += 4;
		}
		par = par->link;
	}
	OPV_AlignPar(&size);
	return size;
}

static void OPV_ProcSize0 (OPT_Object obj, BOOLEAN firstpass)
{
	INT32 psize, oldPos, entryNr;
	__ASSERT(obj->prio != 127, 0);
	oldPos = OPM_errpos;
	if (obj->scope != NIL) {
		OPM_errpos = obj->scope->adr;
	} else {
		OPM_errpos = 0;
	}
	OPV_TypSize(obj->typ, 1);
	if ((obj->vis != 0) == firstpass || __IN(obj->mode, 0x2020, 32)) {
		if (obj->mode == 6 || (((obj->mode == 7 && obj->mnolev >= 0)) && __IN(3, obj->conval->setval, 32))) {
			if (__IN(3, obj->conval->setval, 32)) {
				psize = 12;
			} else {
				psize = 8;
			}
			obj->adr = 0;
		} else {
			psize = 8;
		}
		if (!__IN(obj->mode, 0x2240, 32)) {
			OPL_NewEntry(&entryNr);
			obj->adr += entryNr;
		}
		OPV_TypSize(obj->typ, 1);
		(*OPV_ParamAdr[__X(obj->sysflag, 6)])(&obj->link, &psize, &obj->conval->intval2, __IN(obj->mode, 0x2000, 32), obj->mode == 9, 1);
		obj->conval->intval = psize;
		obj->linkadr = -1;
	}
	if ((!firstpass && obj->mode != 13)) {
		if (!__IN(1, obj->conval->setval, 32)) {
			OPM_err(129);
		}
		OPV_VarAdr(obj->scope->scope, &obj->conval->intval2);
		OPV_Traverse(obj->scope->right, 0);
	}
	OPM_errpos = oldPos;
}

static void OPV_ProcSize (OPT_Object obj, BOOLEAN firstpass)
{
	if (obj->prio == 127) {
		obj = obj->link2;
		while (obj != NIL) {
			OPV_ProcSize0(obj, firstpass);
			obj = obj->left;
		}
	} else {
		OPV_ProcSize0(obj, firstpass);
	}
}

static void OPV_FindMth (INT8 curmod, OPS_Name name, OPT_Struct typ, OPT_Object *res)
{
	OPT_Object obj;
	*res = NIL;
	while ((((((typ != NIL && typ != OPT_ToBeFixed)) && typ != OPT_undftyp)) && *res == NIL)) {
		obj = typ->link;
		while (obj != NIL) {
			if (__STRCMP(name, obj->name) < 0) {
				obj = obj->left;
			} else if (__STRCMP(name, obj->name) > 0) {
				obj = obj->right;
			} else {
				obj->flag |= __SETOF(1,32);
				*res = obj;
				obj = NIL;
			}
		}
		if ((((((*res != NIL && (*res)->mode == 13)) && (*res)->mnolev != curmod)) && (*res)->vis == 0)) {
			*res = NIL;
		}
		if (*res == NIL) {
			typ = typ->BaseTyp;
		}
	}
}

static void OPV_TypeName (OPT_Struct t)
{
	if (t->strobj->name[0] != 0x00) {
		OPM_LogWStr(t->strobj->name, 32);
	} else if (t->ptr != NIL) {
		OPM_LogWStr(t->ptr->strobj->name, 32);
	} else {
		OPM_LogWStr((CHAR*)"<!!!>", 6);
	}
}

static void OPV_VisitTProcs (OPT_Object obj)
{
	OPT_Struct typ, t;
	OPT_Object redef;
	if (obj != NIL) {
		if (obj->mode != 5) {
			OPV_VisitTProcs(obj->left);
		}
		if (__IN(obj->mode, 0x2020, 32)) {
			typ = obj->link->typ;
			if (typ->form == 13) {
				typ = typ->BaseTyp;
			}
			redef = NIL;
			if (obj->mode == 5) {
				t = typ->BaseTyp;
				while ((t != NIL && !__IN(1, t->strobj->conval->setval, 32))) {
					t = t->BaseTyp;
				}
				if (t != NIL) {
					redef = t->strobj;
				}
			} else if (typ->BaseTyp != NIL) {
				OPV_FindMth(-typ->mno, obj->name, typ->BaseTyp, &redef);
				if ((redef != NIL && redef->mode != 13)) {
					redef = NIL;
				}
			}
			if (redef != NIL) {
				obj->adr = __ASHL(__ASHR(redef->adr, 16), 16) + __MASK(obj->adr, -65536);
			} else {
				obj->adr = __MASK(obj->adr, -65536) + __ASHL(typ->n, 16);
				typ->n += 1;
			}
		}
		if (obj->mode != 5) {
			OPV_VisitTProcs(obj->right);
		}
	}
}

static void OPV_Traverse (OPT_Object obj, BOOLEAN exported)
{
	if (obj != NIL) {
		OPV_Traverse(obj->left, exported);
		if ((obj->mode == 5 && (obj->vis != 0) == exported)) {
			OPV_TypSize(obj->typ, 1);
			if ((((obj->typ->comp == 6 && obj->typ->tdadr <= -1)) && obj->typ->sysflag != 6)) {
				OPL_AllocTypDesc(obj->typ);
			}
		} else if (__IN(obj->mode, 0x26c0, 32)) {
			OPV_ProcSize(obj, exported);
		}
		OPV_Traverse(obj->right, exported);
	}
}

static struct AssignTent__14 {
	struct AssignTent__14 *lnk;
} *AssignTent__14_s;

static void AssignBody__15 (OPT_Object body);
static void EnumTprocs__17 (OPT_Object fld);

static void AssignBody__15 (OPT_Object body)
{
	INT32 entryNr;
	if ((((((body != NIL && body->conval != NIL)) && __IN(1, body->conval->setval, 32))) && __MASK(body->adr, -65536) == 0)) {
		body->conval->intval2 = 0;
		body->conval->intval = 8;
		(*OPV_ParamAdr[__X(body->sysflag, 6)])(&body->link, &body->conval->intval, &body->conval->intval2, 1, 0, 0);
		OPV_VarAdr(body->scope->scope, &body->conval->intval2);
		OPL_NewEntry(&entryNr);
		body->adr += entryNr;
	}
}

static void EnumTprocs__17 (OPT_Object fld)
{
	INT32 entryNr;
	if (fld != NIL) {
		EnumTprocs__17(fld->left);
		if (fld->mode == 13) {
			if (__MASK(fld->adr, -65536) == 0) {
				if (!__IN(1, fld->conval->setval, 32)) {
					OPM_err(129);
				}
				OPV_VarAdr(fld->scope->scope, &fld->conval->intval2);
				OPV_Traverse(fld->scope->right, 0);
				OPL_NewEntry(&entryNr);
				fld->adr += entryNr;
			}
		}
		EnumTprocs__17(fld->right);
	}
}

static void OPV_AssignTent (OPT_Object obj)
{
	OPT_Struct typ;
	struct AssignTent__14 _s;
	_s.lnk = AssignTent__14_s;
	AssignTent__14_s = &_s;
	if (obj != NIL) {
		OPV_AssignTent(obj->left);
		if (obj->history == 3) {
			obj->mode = 0;
		}
		typ = obj->typ;
		if (obj->mode == 1) {
			if ((((((typ->form == 13 && typ->strobj == NIL)) && typ->BaseTyp->comp == 6)) && typ->BaseTyp->ptr == typ)) {
				typ = typ->BaseTyp;
				AssignBody__15(typ->strobj);
				EnumTprocs__17(typ->link);
			} else if ((typ->comp == 6 && typ->strobj->name[0] == 0x00)) {
				AssignBody__15(typ->strobj);
				EnumTprocs__17(typ->link);
			}
		} else if ((((obj->mode == 5 && typ->mno == 0)) && typ->strobj == obj)) {
			if ((((typ->form == 13 && typ->BaseTyp->comp == 6)) && typ->BaseTyp->ptr == typ)) {
				typ = typ->BaseTyp;
				AssignBody__15(typ->strobj);
				EnumTprocs__17(typ->link);
			} else if (typ->comp == 6) {
				AssignBody__15(typ->strobj);
				EnumTprocs__17(typ->link);
			}
		} else if (__IN(obj->mode, 0xc0, 32)) {
			OPV_AssignTent(obj->scope->right);
		}
		OPV_AssignTent(obj->right);
	}
	AssignTent__14_s = _s.lnk;
}

void OPV_AssignEntries (OPT_Object obj, BOOLEAN browse)
{
	INT32 adr, nofEntries, nofRecs;
	OPT_Struct typ;
	OPV_allocTd = 0;
	adr = 0;
	nofEntries = 1;
	nofRecs = -4;
	while (obj != NIL) {
		if (obj->mode == 1) {
			typ = obj->typ;
			OPV_TypSize(typ, 1);
			if (browse) {
				OPV_AlignVar(&adr, typ->size);
				OPV_AllocVar(&adr, &obj->linkadr, typ->size);
				obj->adr = adr;
			}
		} else if (obj->mode == 7) {
			obj->adr = nofEntries;
			nofEntries += 1;
			if (obj->conval == NIL) {
				obj->conval = OPT_NewConst();
			}
			obj->linkadr = -1;
			obj->conval->intval = -1;
			(*OPV_ParamAdr[__X(obj->sysflag, 6)])(&obj->link, &obj->conval->intval, &obj->conval->intval2, 0, 0, 1);
		} else if (obj->mode == 5) {
			typ = obj->typ;
			obj->linkadr = -1;
			OPV_TypSize(typ, 1);
			if (typ->comp == 6) {
				typ->tdadr = -1;
				if (browse) {
					typ->tdadr = nofRecs;
					nofRecs -= 4;
				}
			}
		}
		obj = obj->nxtobj;
	}
	OPV_allocTd = 1;
}

static void OPV_AssignOwnEntries (OPT_Object obj)
{
	INT32 size;
	OPV_allocTd = 0;
	while (obj != NIL) {
		if (obj->mode == 1) {
			OPV_TypSize(obj->typ, 1);
			size = obj->typ->size;
			OPV_AlignVar(&OPO_dsize, size);
			OPV_AllocVar(&OPO_dsize, &obj->linkadr, size);
			obj->adr = 0;
		} else if (obj->mode == 7) {
			OPV_ProcSize(obj, 1);
		} else if ((obj->mode == 5 && obj->typ->comp == 6)) {
			if (obj->typ->tdadr <= 0) {
				OPV_TypSize(obj->typ, 1);
				if (obj->typ->sysflag != 6) {
					OPL_AllocTypDesc(obj->typ);
				}
			}
		}
		obj = obj->nxtobj;
	}
	OPV_allocTd = 1;
}

static void OPV_AllocAddEntries (OPT_Object obj)
{
	OPT_Struct typ;
	while (obj != NIL) {
		typ = obj->typ;
		if ((obj->mode == 5 && obj->used)) {
			if ((typ->comp == 6 && typ->tdadr <= 0)) {
				OPL_AllocTypDesc(obj->typ);
			} else if ((((obj->typ->form == 13 && typ->BaseTyp->tdadr <= 0)) && typ->sysflag != 6)) {
				OPL_AllocTypDesc(obj->typ->BaseTyp);
			}
		}
		obj = obj->nxtobj;
	}
}

void OPV_AdrAndSize (OPT_Object topScope)
{
	INT16 i;
	INT32 dsize;
	OPM_errpos = topScope->adr;
	OPO_dsize = 0;
	i = 1;
	while (i < (INT16)OPT_nofmod) {
		OPV_AssignEntries((OPT_modules->data)[__X(i, OPT_modules->len[0])]->publics, 0);
		i += 1;
	}
	OPV_AssignOwnEntries(OPT_objects);
	OPV_Traverse(topScope->right, 0);
	OPV_AssignTent(topScope->right);
	dsize = -OPO_dsize;
	OPV_VarAdr(topScope->scope, &dsize);
	OPO_dsize = dsize;
	i = 1;
	while (i < (INT16)OPT_nofmod) {
		OPV_AllocAddEntries((OPT_modules->data)[__X(i, OPT_modules->len[0])]->publics);
		i += 1;
	}
}

static void OPV_Designator (OPT_Node n, OPC_Item *x, ADDRESS *x__typ)
{
	OPT_Object obj;
	OPC_Item y;
	INT32 index;
	BOOLEAN varRec;
	switch (n->class) {
		case 0: case 1: 
			obj = n->obj;
			while (obj->scope != NIL) {
				obj = obj->scope;
				n->obj = obj;
			}
			(*x).node = n;
			(*x).mnolev = obj->mnolev;
			(*x).scale = 0;
			(*x).inx = -1;
			if (obj->mnolev <= 0) {
				(*x).mode = 16;
				if (obj->mnolev < 0) {
					if (__ASHR(obj->adr, 16) == 0) {
						OPL_NewVarCons(-obj->mnolev, (INT16)obj->adr, &index);
						obj->adr = __ASHL(index, 16) + obj->adr;
					}
					(*x).adr = 0;
				} else {
					(*x).adr = obj->linkadr;
				}
			} else {
				(*x).mode = obj->mode;
				(*x).adr = obj->linkadr;
			}
			(*x).offs = 0;
			(*x).descReg = -1;
			break;
		case 2: 
			OPV_Designator(n->left, &*x, x__typ);
			if (n->obj->mode == 13) {
				OPC_Method(&*x, x__typ, n->obj);
				return;
			} else {
				OPC_Field(&*x, x__typ, n->obj->adr);
			}
			break;
		case 3: 
			OPV_Designator(n->left, &*x, x__typ);
			OPC_DeRef(&*x, x__typ);
			break;
		case 4: 
			OPV_Expression(n->right, &y, OPC_Item__typ, NIL);
			OPV_Designator(n->left, &*x, x__typ);
			OPC_Index(&*x, x__typ, &y, OPC_Item__typ);
			break;
		case 5: 
			varRec = (n->left->class == 1 && n->left->typ->comp == 6);
			OPV_Designator(n->left, &*x, x__typ);
			OPC_TypeTest(&*x, x__typ, n->typ, 1, 0, varRec);
			break;
		case 6: 
			varRec = (n->left->class == 1 && n->left->typ->comp == 6);
			OPV_Designator(n->left, &*x, x__typ);
			OPC_TypeTest(&*x, x__typ, n->typ, 1, 1, varRec);
			break;
		case 9: 
			if ((__IN(n->obj->mode, 0x2080, 32) && n->obj->conval->intval == -1)) {
				n->obj->conval->intval = OPV_ArgSize(n->obj->link) + 8;
			}
			if (__IN(24, OPM_parserOptions, 32)) {
				obj = n->obj;
				OPM_LogWLn();
				switch (obj->mode) {
					case 7: 
						OPM_LogWStr((CHAR*)"CX ", 4);
						if (obj->mnolev < 0) {
							OPM_LogWStr((OPT_modules->data)[__X(-obj->mnolev, OPT_modules->len[0])]->name, 32);
							OPM_LogW('/');
						}
						break;
					case 8: 
						OPM_LogWStr((CHAR*)"CS ", 4);
						OPM_LogWNum(obj->adr, 1);
						break;
					default: 
						OPM_LogWStr((CHAR*)"C\? ", 4);
						if (obj->scope != NIL) {
							__ASSERT(obj->scope->mode == 12, 0);
							if (obj->scope->left != NIL) {
								__ASSERT(obj->scope->left->mode == 12, 0);
								if (obj->scope->left->link != NIL) {
									OPM_LogWStr(obj->scope->left->link->name, 32);
									OPM_LogW('/');
								}
							}
						}
						break;
				}
				OPM_LogWStr(obj->name, 32);
			}
			OPC_Procedure(&*x, x__typ, n);
			break;
		default: __CASECHK;
	}
	(*x).typ = n->typ;
}

static struct CallLR__20 {
	struct CallLR__20 *lnk;
} *CallLR__20_s;

static void AllocTempSpace__21 (INT32 *dynblocks, INT32 *staticsize, OPT_Node ap, OPT_Object fp);

static void AllocTempSpace__21 (INT32 *dynblocks, INT32 *staticsize, OPT_Node ap, OPT_Object fp)
{
	OPC_Item tos;
	if (ap != NIL) {
		AllocTempSpace__21(&*dynblocks, &*staticsize, ap->link, fp->link);
		if ((ap->class == 13 && ap->typ->form == 15)) {
			if (__IN(ap->typ->comp, 0x28, 32)) {
				OPC_AllocateStatic(&tos, OPC_Item__typ, __ASHL(ap->typ->n, 2) + 8);
				tos.offs += __ASHL(ap->typ->n, 2) + 8;
				tos.typ = OPT_linttyp;
				OPV_Call(ap, &tos, OPC_Item__typ, 0);
				*dynblocks += 1;
			} else if (fp->typ->comp == 5 || fp->mode == 2) {
				*staticsize += ap->typ->size + __MASK(-ap->typ->size, -4);
			}
		}
	}
}

static void OPV_CallLR (OPT_Node proc, OPC_Item *res, ADDRESS *res__typ, BOOLEAN assignment)
{
	OPT_Node firstap, ap;
	OPT_Object firstfp, fp;
	OPC_Item x, dynptr, tos;
	INT32 s, dynblocks, staticsize;
	BOOLEAN tproc;
	struct CallLR__20 _s;
	_s.lnk = CallLR__20_s;
	CallLR__20_s = &_s;
	if (!assignment) {
		OPC_PushRegs();
	}
	firstap = proc->right;
	firstfp = proc->obj;
	tproc = (proc->left->obj != NIL && proc->left->obj->mode == 13);
	if (tproc) {
		firstap = firstap->link;
		firstfp = firstfp->link;
	}
	staticsize = 0;
	dynblocks = 0;
	AllocTempSpace__21(&dynblocks, &staticsize, firstap, firstfp);
	OPC_AllocateStatic(&tos, OPC_Item__typ, staticsize);
	if (proc->typ->form == 15) {
		OPC_CorrectStackAdr(&*res, res__typ, staticsize, dynblocks);
		OPC_PushRetDesc(&*res, res__typ, &tos, OPC_Item__typ);
	}
	dynptr = tos;
	OPC_CorrectStackAdr(&dynptr, OPC_Item__typ, staticsize, 0);
	ap = firstap;
	fp = firstfp;
	while (ap != NIL) {
		if ((ap->class == 13 && ap->typ->form == 15)) {
			if (__IN(ap->typ->comp, 0x28, 32)) {
				x = dynptr;
				OPC_DeRef(&dynptr, OPC_Item__typ);
				x.typ = ap->typ;
				x.offs += 4;
				x.descReg = dynptr.adr;
				x.descOffs = dynptr.offs - 4;
				OPC_Parameter(&x, OPC_Item__typ, fp, 0, 0);
			} else if (fp->typ->comp == 5 || fp->mode == 2) {
				x = tos;
				x.typ = ap->typ;
				OPV_Call(ap, &x, OPC_Item__typ, 0);
				x = tos;
				x.typ = ap->typ;
				OPC_Parameter(&x, OPC_Item__typ, fp, 0, 0);
				OPC_CorrectStackAdr(&tos, OPC_Item__typ, ap->typ->size + __MASK(-ap->typ->size, -4), 0);
			} else {
				OPC_AllocateStatic(&x, OPC_Item__typ, fp->typ->size);
				x.typ = fp->typ;
				OPV_Call(ap, &x, OPC_Item__typ, 0);
			}
		} else {
			OPV_Expression(ap, &x, OPC_Item__typ, NIL);
			OPC_Parameter(&x, OPC_Item__typ, fp, ap->class == 3, 0);
		}
		if (fp->mode == 2) {
			if (fp->typ->comp == 6) {
				s = 8;
			} else if (fp->typ->comp == 5) {
				s = fp->typ->size;
			} else {
				s = 4;
			}
		} else {
			s = fp->typ->size;
		}
		OPV_AlignPar(&s);
		OPC_CorrectStackAdr(&tos, OPC_Item__typ, s, 0);
		OPC_CorrectStackAdr(&dynptr, OPC_Item__typ, s, 0);
		ap = ap->link;
		fp = fp->link;
	}
	if (tproc) {
		OPV_Expression(proc->right, &x, OPC_Item__typ, NIL);
		OPC_Parameter(&x, OPC_Item__typ, proc->obj, proc->right->class == 3, 0);
	}
	if (proc->subcl == 2) {
		OPV_Statement(proc->left, NIL);
	} else {
		OPV_Designator(proc->left, &x, OPC_Item__typ);
		if (proc->left->class == 9) {
			OPC_Call(&x, OPC_Item__typ, proc->left->obj, proc);
		} else {
			OPC_Call(&x, OPC_Item__typ, NIL, proc);
		}
	}
	if (!__IN(proc->typ->comp, 0x28, 32)) {
		OPC_RemoveStatic(staticsize);
		OPC_ResetStack(dynblocks);
	}
	if (proc->typ == OPT_notyp || proc->typ->form == 15) {
		OPC_PopResult(NIL, &*res, res__typ);
	} else {
		OPC_PopResult(proc, &*res, res__typ);
	}
	CallLR__20_s = _s.lnk;
}

static void OPV_CallRL (OPT_Node proc, OPC_Item *res, ADDRESS *res__typ, BOOLEAN assignment)
{
	OPC_Item ap;
	OPT_Node n, p, q;
	OPT_Object fp, formPar;
	n = proc->right;
	fp = proc->obj;
	if (!assignment) {
		OPC_PushRegs();
	}
	if (n != NIL) {
		p = n;
		formPar = fp;
		while (p->link != NIL) {
			p = p->link;
			formPar = formPar->link;
		}
		while (p != n) {
			OPV_Expression(p, &ap, OPC_Item__typ, NIL);
			OPC_Parameter(&ap, OPC_Item__typ, formPar, p->class == 3, 1);
			q = n;
			formPar = fp;
			while (q->link != p) {
				q = q->link;
				formPar = formPar->link;
			}
			p = q;
		}
		OPV_Expression(n, &ap, OPC_Item__typ, NIL);
		OPC_Parameter(&ap, OPC_Item__typ, fp, n->class == 3, 1);
	}
	if (proc->subcl == 2) {
		OPV_Statement(proc->left, NIL);
	} else {
		OPV_Designator(proc->left, &*res, res__typ);
		if (proc->left->class == 9) {
			OPC_Call(&*res, res__typ, proc->left->obj, proc);
		} else {
			OPC_Call(&*res, res__typ, NIL, proc);
		}
	}
	if (proc->typ == OPT_notyp) {
		OPC_PopResult(NIL, &*res, res__typ);
	} else {
		OPC_PopResult(proc, &*res, res__typ);
	}
}

static void OPV_Call (OPT_Node proc, OPC_Item *res, ADDRESS *res__typ, BOOLEAN assignment)
{
	OPT_Object obj;
	OPT_Node n;
	INT32 i;
	n = proc->left;
	if (n->class == 9 || n->class == 29) {
		obj = n->obj;
		if (__IN(obj->sysflag, 0x0c, 32)) {
			OPV_CallRL(proc, &*res, res__typ, assignment);
		} else {
			OPV_CallLR(proc, &*res, res__typ, assignment);
		}
	} else {
		i = n->class;
		__ASSERT(n->typ->form == 14, 0);
		if (__IN(n->typ->sysflag, 0x0c, 32)) {
			OPV_CallRL(proc, &*res, res__typ, assignment);
		} else {
			OPV_CallLR(proc, &*res, res__typ, assignment);
		}
	}
}

static struct Expression__27 {
	OPT_Node *n;
	OPT_Const *con;
	struct Expression__27 *lnk;
} *Expression__27_s;

static void AllocConst__28 (SYSTEM_BYTE *bytes, ADDRESS bytes__len, INT32 len, INT32 align);

static void AllocConst__28 (SYSTEM_BYTE *bytes, ADDRESS bytes__len, INT32 len, INT32 align)
{
	OPT_Const con1, con2;
	con1 = *Expression__27_s->con;
	if ((*Expression__27_s->n)->obj == NIL) {
		OPL_AllocConst((void*)bytes, bytes__len * 1, len, align, &con1->intval);
	} else {
		con2 = (*Expression__27_s->n)->obj->conval;
		if (con2->intval == -1) {
			OPL_AllocConst((void*)bytes, bytes__len * 1, len, align, &con2->intval);
		}
		con1->intval = con2->intval;
	}
}

static void OPV_Expression (OPT_Node n, OPC_Item *z, ADDRESS *z__typ, OPT_Node selfForUnlock)
{
	OPC_Item x, y;
	INT16 f;
	REAL real;
	OPT_Const con;
	OPT_Struct typ;
	struct Expression__27 _s;
	_s.n = &n;
	_s.con = &con;
	_s.lnk = Expression__27_s;
	Expression__27_s = &_s;
	(*z).node = NIL;
	switch (n->class) {
		case 7: 
			(*z).typ = n->typ;
			(*z).mnolev = 0;
			(*z).node = NIL;
			con = n->conval;
			switch ((*z).typ->form) {
				case 1: case 2: case 3: case 4: case 5: 
				case 6: case 11: case 13: 
					(*z).mode = 3;
					(*z).adr = con->intval;
					break;
				case 9: 
					(*z).mode = 3;
					(*z).adr = (INT32)con->setval;
					break;
				case 10: 
					AllocConst__28((void*)*con->ext, 256, con->intval2, 4);
					(*z).mode = 16;
					(*z).adr = con->intval;
					(*z).offs = con->intval2;
					(*z).inx = -1;
					break;
				case 7: 
					real = con->realval;
					AllocConst__28((void*)&real, 4, 4, 4);
					(*z).mode = 16;
					(*z).adr = con->intval;
					(*z).inx = -1;
					break;
				case 8: 
					AllocConst__28((void*)&con->realval, 8, 8, 4);
					(*z).mode = 16;
					(*z).adr = con->intval;
					(*z).inx = -1;
					break;
				default: __CASECHK;
			}
			break;
		case 10: 
			OPV_Expression(n->left, &x, OPC_Item__typ, selfForUnlock);
			OPV_Expression(n->right, &y, OPC_Item__typ, selfForUnlock);
			OPC_SetRange(&*z, z__typ, &x, OPC_Item__typ, &y, OPC_Item__typ);
			break;
		case 11: 
			if ((n->subcl != 16 && n->subcl != 34)) {
				OPV_Expression(n->left, &x, OPC_Item__typ, selfForUnlock);
			}
			__GUARDEQR(z, z__typ, OPC_Item) = x;
			switch (n->subcl) {
				case 33: 
					OPC_Not(&*z, z__typ, &x, OPC_Item__typ);
					break;
				case 7: 
					OPC_Neg(&*z, z__typ, &x, OPC_Item__typ);
					break;
				case 16: 
					OPV_Designator(n->left, &*z, z__typ);
					if (n->obj->typ->form == 13) {
						OPC_TypeTest(&*z, z__typ, n->obj->typ, 0, 0, 0);
					} else {
						OPC_TypeTest(&*z, z__typ, n->obj->typ, 0, 0, 1);
					}
					break;
				case 20: 
					if (n->typ->form == 9) {
						OPC_SetElem(&*z, z__typ, &x, OPC_Item__typ);
					} else {
						__GUARDEQR(z, z__typ, OPC_Item) = x;
						OPC_Convert(&*z, z__typ, n->typ->form);
					}
					break;
				case 21: 
					OPC_AbsVal(&*z, z__typ, &x, OPC_Item__typ);
					break;
				case 22: 
					OPC_Cap(&*z, z__typ, &x, OPC_Item__typ);
					break;
				case 23: 
					OPC_Odd(&*z, z__typ, &x, OPC_Item__typ);
					break;
				case 24: case 25: case 29: case 30: case 31: 
				case 32: 
					OPC_SYSmop(&*z, z__typ, &x, OPC_Item__typ, n->subcl, n->typ);
					break;
				case 34: 
					typ = n->left->typ;
					if (typ->form == 13) {
						typ = typ->BaseTyp;
					}
					__ASSERT(typ->comp == 6, 0);
					OPC_GetTdAdr(&typ, &*z, z__typ);
					(*z).typ = OPT_linttyp;
					break;
				default: __CASECHK;
			}
			break;
		case 12: 
			OPV_Expression(n->left, &x, OPC_Item__typ, selfForUnlock);
			f = x.typ->form;
			if (n->subcl == 5) {
				OPC_CondAnd(&x, OPC_Item__typ);
			} else if (n->subcl == 8) {
				OPC_CondOr(&x, OPC_Item__typ);
			} else if ((n->subcl >= 9 && n->subcl <= 14)) {
				OPC_Relation(&x, OPC_Item__typ);
			}
			OPV_Expression(n->right, &y, OPC_Item__typ, selfForUnlock);
			switch (n->subcl) {
				case 1: 
					OPC_Mul(&*z, z__typ, &x, OPC_Item__typ, &y, OPC_Item__typ, f);
					break;
				case 2: case 3: 
					OPC_Div(&*z, z__typ, &x, OPC_Item__typ, &y, OPC_Item__typ, f);
					break;
				case 4: 
					OPC_Mod(&*z, z__typ, &x, OPC_Item__typ, &y, OPC_Item__typ);
					break;
				case 5: 
					OPC_And(&*z, z__typ, &x, OPC_Item__typ, &y, OPC_Item__typ);
					break;
				case 6: 
					OPC_Add(&*z, z__typ, &x, OPC_Item__typ, &y, OPC_Item__typ, f);
					break;
				case 7: 
					OPC_Sub(&*z, z__typ, &x, OPC_Item__typ, &y, OPC_Item__typ, f);
					break;
				case 8: 
					OPC_Or(&*z, z__typ, &x, OPC_Item__typ, &y, OPC_Item__typ);
					break;
				case 9: case 10: case 11: case 12: case 13: 
				case 14: 
					OPC_Cmp(&*z, z__typ, &x, OPC_Item__typ, &y, OPC_Item__typ, n->subcl);
					break;
				case 15: 
					OPC_In(&*z, z__typ, &x, OPC_Item__typ, &y, OPC_Item__typ);
					break;
				case 17: 
					OPC_Ash(&*z, z__typ, &x, OPC_Item__typ, &y, OPC_Item__typ);
					break;
				case 18: 
					OPC_Msk(&*z, z__typ, &x, OPC_Item__typ, &y, OPC_Item__typ);
					break;
				case 19: 
					OPC_Len(&*z, z__typ, &x, OPC_Item__typ, &y, OPC_Item__typ);
					break;
				case 26: case 27: case 28: 
					OPC_SYSdop(&*z, z__typ, &x, OPC_Item__typ, &y, OPC_Item__typ, n->subcl);
					break;
				default: __CASECHK;
			}
			break;
		case 13: 
			OPV_Call(n, &*z, z__typ, 0);
			break;
		default: 
			OPV_Designator(n, &*z, z__typ);
			Expression__27_s = _s.lnk;
			return;
			break;
	}
	(*z).typ = n->typ;
	Expression__27_s = _s.lnk;
}

static void OPV_IfStat (OPT_Node n, OPT_Node selfForUnlock, INT32 *Lfix, INT32 *Lcfix, BOOLEAN else_)
{
	OPC_Item x;
	for (;;) {
		OPM_errpos = n->conval->intval;
		OPV_Expression(n->left, &x, OPC_Item__typ, selfForUnlock);
		OPC_Jncc(&x, OPC_Item__typ, &*Lcfix, n);
		OPV_Statement(n->right, selfForUnlock);
		if (n->link == NIL) {
			break;
		}
		OPC_Jmp(&*Lfix, n);
		OPC_FixLink(*Lcfix);
		n = n->link;
	}
	if (else_) {
		OPC_Jmp(&*Lfix, n);
	}
}

static void OPV_CaseStat (OPT_Node n, OPT_Node selfForUnlock)
{
	OPT_Node case_, interval;
	OPC_Item x;
	INT32 L, elseLabel, dummy, low, high, tab;
	OPV_Expression(n->left, &x, OPC_Item__typ, selfForUnlock);
	low = n->right->conval->intval;
	high = n->right->conval->intval2;
	L = -1;
	OPC_Case(&x, OPC_Item__typ, low, high, &tab, &elseLabel, n);
	case_ = n->right->left;
	while (case_ != NIL) {
		OPC_DefLabel(&dummy);
		interval = case_->left;
		while (interval != NIL) {
			OPL_CaseJump(OPC_pc, tab, interval->conval->intval - low, interval->conval->intval2 - low);
			interval = interval->link;
		}
		OPV_Statement(case_->right, selfForUnlock);
		OPC_Jmp(&L, n);
		case_ = case_->link;
	}
	OPC_FixLink(elseLabel);
	elseLabel = OPC_pc;
	if (n->right->conval->setval != 0x0) {
		OPV_Statement(n->right->right, selfForUnlock);
	} else {
		OPC_Trap(2, n);
	}
	OPC_CaseFixup(tab, elseLabel, (high - low) + 1);
	OPC_FixLink(L);
}

static void OPV_Dim (OPC_Item *z, ADDRESS *z__typ, OPC_Item *nofelem, ADDRESS *nofelem__typ, OPT_Node n, OPT_Struct typ, INT32 nofdim)
{
	OPC_Item len;
	__ASSERT(__IN(typ->comp, 0x34, 32), 0);
	OPV_Expression(n, &len, OPC_Item__typ, NIL);
	if (len.mode != 3) {
		OPC_PushLen(&len, OPC_Item__typ);
		OPC_GenDimTrap(&len, OPC_Item__typ);
	}
	if (nofdim == 1) {
		__GUARDEQR(nofelem, nofelem__typ, OPC_Item) = len;
		(*nofelem).typ = OPT_linttyp;
	} else {
		OPC_MulDim(&*nofelem, nofelem__typ, &len, OPC_Item__typ);
	}
	if (n->link != NIL) {
		OPV_Dim(&*z, z__typ, &*nofelem, nofelem__typ, n->link, typ->BaseTyp, nofdim + 1);
	} else {
		OPC_NewArray(&*z, z__typ, &*nofelem, nofelem__typ, nofdim, typ->BaseTyp, 1);
		(*z).offs += 4;
	}
	if (len.mode != 3) {
		OPC_PopLen(&*z, z__typ);
	} else {
		(*z).typ = OPT_linttyp;
		OPC_Assign(&*z, z__typ, &len, OPC_Item__typ);
	}
	(*z).offs += 4;
}

static void OPV_Statement (OPT_Node n, OPT_Node selfForUnlock)
{
	OPC_Item x, y, z, times;
	OPT_Struct t;
	OPT_Node p;
	INT32 L, Lc, prevExitChain;
	OPT_Object proc, par;
	CHAR name[64];
	INT32 i, j;
	INT16 res;
	while ((!OPO_CodeErr && n != NIL)) {
		OPC_NewStat(n->conval->intval);
		switch (n->class) {
			case 18: 
				if (n->obj == NIL) {
					if (__IN(24, OPM_parserOptions, 32)) {
						OPM_LogWLn();
						OPM_LogWStr((CHAR*)"B", 2);
					}
					OPC_pc = 0;
					OPC_Enter(NIL, 0, NIL);
					OPV_Statement(n->right, NIL);
					OPC_Exit(NIL);
					if (OPV_dumpCode) {
						__MOVE("Body", OPV_ProcName, 5);
						OPV_EntryNr = -1;
						Oberon_Call((CHAR*)"OPI.DumpCode", 13, Oberon_Par, 0, &res);
					}
					OPL_GenCode(OPC_pc);
					OPL_OutRefPoint(NIL);
					OPL_OutRefName((CHAR*)"$$", 3);
					OPL_OutRefs(OPT_topScope);
					OPC_level += 1;
					OPV_Statement(n->left, NIL);
					OPC_level -= 1;
				} else {
					if (__IN(24, OPM_parserOptions, 32)) {
						OPM_LogWLn();
						OPM_LogWStr((CHAR*)"P ", 3);
						OPM_LogWStr(n->obj->name, 32);
					}
					proc = n->obj;
					par = proc->link;
					OPC_level += 1;
					OPV_Statement(n->left, NIL);
					OPC_level -= 1;
					OPC_pc = 0;
					if (__IN(1, proc->conval->setval, 32)) {
						OPC_Enter(proc, proc->conval->intval2, n);
						if (proc->code != NIL) {
							OPV_Statement(proc->code, NIL);
							OPC_AllocSDynArr(&proc);
						}
						OPV_Statement(n->right, NIL);
						if ((((proc->typ != OPT_notyp && !__IN(7, proc->conval->setval, 32))) && proc->mode != 5)) {
							OPC_Trap(3, n);
						} else {
							OPC_Exit(proc);
						}
						OPL_OutRefPoint(proc);
						if (__IN(proc->mode, 0x2020, 32)) {
							t = proc->link->typ;
							if ((((t->comp == 6 && t->ptr != NIL)) && t->ptr->strobj != NIL)) {
								par = t->ptr->strobj;
							} else if (t->comp == 6 || t->BaseTyp->strobj->name[0] == 0x00) {
								par = t->strobj;
							} else {
								par = t->BaseTyp->strobj;
							}
							i = 0;
							if (par != NIL) {
								while (par->name[__X(i, 32)] != 0x00) {
									name[__X(i, 64)] = par->name[__X(i, 32)];
									i += 1;
								}
								name[__X(i, 64)] = '.';
								i += 1;
							} else {
								__COPY("\?\?.", name, 64);
								i = 3;
							}
							if (proc->mode == 13) {
								j = 0;
								while (proc->name[__X(j, 32)] != 0x00) {
									name[__X(i, 64)] = proc->name[__X(j, 32)];
									i += 1;
									j += 1;
								}
								name[__X(i, 64)] = 0x00;
							} else if (proc->mode == 5) {
								name[__X(i, 64)] = '$';
								name[__X(i + 1, 64)] = '$';
								name[__X(i + 2, 64)] = 0x00;
							}
						} else {
							__COPY(proc->name, name, 64);
						}
						OPL_OutRefName(name, 64);
						OPL_OutRefs(proc->scope->right);
						if (OPV_dumpCode) {
							__MOVE(proc->name, OPV_ProcName, 32);
							if (proc->vis == 1) {
								OPV_EntryNr = (INT16)__MASK(proc->adr, -65536);
							} else {
								OPV_EntryNr = -1;
							}
							Oberon_Call((CHAR*)"OPI.DumpCode", 13, Oberon_Par, 0, &res);
						}
						OPL_GenCode(OPC_pc);
					}
				}
				break;
			case 14: 
				break;
			case 19: 
				if (n->subcl == 0) {
					if ((n->right->class == 13 && n->right->typ->form == 15)) {
						OPC_PushRegs();
						OPV_Expression(n->left, &z, OPC_Item__typ, selfForUnlock);
						OPV_Call(n->right, &z, OPC_Item__typ, 1);
					} else {
						OPV_Expression(n->right, &x, OPC_Item__typ, selfForUnlock);
						OPC_Relation(&x, OPC_Item__typ);
						OPV_Expression(n->left, &z, OPC_Item__typ, selfForUnlock);
						OPC_Assign(&z, OPC_Item__typ, &x, OPC_Item__typ);
					}
				} else if (n->subcl == 33 || n->subcl == 34) {
					OPC_SYSinterrupt(n->subcl == 34);
				} else {
					if (n->subcl != 66) {
						OPV_Expression(n->left, &z, OPC_Item__typ, selfForUnlock);
					}
					if (n->subcl != 1) {
						OPV_Expression(n->right, &x, OPC_Item__typ, selfForUnlock);
					}
					if (n->subcl == 31) {
						OPV_Expression(n->right->link, &times, OPC_Item__typ, selfForUnlock);
						OPC_SYSmove(&z, OPC_Item__typ, &x, OPC_Item__typ, &times, OPC_Item__typ);
					} else {
						switch (n->subcl) {
							case 13: case 14: 
								OPC_IncDec(&z, OPC_Item__typ, &x, OPC_Item__typ, n->subcl == 13);
								break;
							case 15: case 16: 
								OPC_Include(&z, OPC_Item__typ, &x, OPC_Item__typ, n->subcl == 15);
								break;
							case 24: case 25: 
								OPC_SYSgetput(&z, OPC_Item__typ, &x, OPC_Item__typ, n->subcl == 24);
								break;
							case 26: case 27: 
								OPC_SYSgetputReg(&z, OPC_Item__typ, &x, OPC_Item__typ, n->subcl == 26);
								break;
							case 36: case 35: 
								OPC_SYSportio(&z, OPC_Item__typ, &x, OPC_Item__typ, n->subcl == 36);
								break;
							case 64: 
								OPV_Expression(n->right->link, &y, OPC_Item__typ, selfForUnlock);
								OPC_Await(z, x, y);
								break;
							case 66: 
								OPV_Expression(n->right->link, &z, OPC_Item__typ, NIL);
								OPC_Lock(x, z);
								OPV_Statement(n->left, n->right);
								OPV_Expression(n->right, &x, OPC_Item__typ, NIL);
								OPV_Expression(n->right->link, &z, OPC_Item__typ, NIL);
								OPC_Unlock(x, z);
								break;
							case 18: 
								OPC_Copy(&z, OPC_Item__typ, &x, OPC_Item__typ);
								break;
							case 30: 
								OPC_NewSys(&z, OPC_Item__typ, &x, OPC_Item__typ);
								break;
							case 1: 
								t = n->left->typ;
								if ((n->right != NIL && (__IN(t->comp, 0x3c, 32) || __IN(t->BaseTyp->comp, 0x3c, 32)))) {
									if (t->form == 13) {
										t = t->BaseTyp;
										if (t->comp == 4) {
											x = z;
											OPC_NewRec(&x, OPC_Item__typ, t);
											OPC_DeRef(&z, OPC_Item__typ);
										}
									}
									OPV_Dim(&z, OPC_Item__typ, &x, OPC_Item__typ, n->right, t, 1);
								} else {
									__ASSERT(t->form == 13, 0);
									t = t->BaseTyp;
									OPC_NewRec(&z, OPC_Item__typ, z.typ->BaseTyp);
									if ((((t->comp != 2 && t->strobj != NIL)) && t->strobj->conval != NIL)) {
										if (n->left->link != NIL) {
											n->left->link->conval = n->conval;
											OPV_Statement(n->left->link, selfForUnlock);
										}
										p = n->right;
										while (p != NIL) {
											OPV_Expression(n->left, &z, OPC_Item__typ, selfForUnlock);
											OPV_Expression(p, &x, OPC_Item__typ, selfForUnlock);
											OPC_CallRecBody(&z, OPC_Item__typ, &x, OPC_Item__typ, p->obj->typ);
											p = p->link;
										}
									}
								}
								break;
							default: __CASECHK;
						}
					}
				}
				break;
			case 13: 
				OPV_Call(n, &x, OPC_Item__typ, 0);
				break;
			case 20: 
				if (n->subcl != 32 || __IN(6, OPM_codeOptions, 32)) {
					L = -1;
					Lc = -1;
					OPV_IfStat(n->left, selfForUnlock, &L, &Lc, n->right != NIL);
					OPC_FixLink(Lc);
					if (n->right != NIL) {
						OPV_Statement(n->right, selfForUnlock);
					}
					OPC_FixLink(L);
				}
				break;
			case 21: 
				OPV_CaseStat(n, selfForUnlock);
				break;
			case 22: 
				L = -1;
				OPC_Jmp(&L, n);
				OPC_DefLabel(&Lc);
				OPV_Statement(n->right, selfForUnlock);
				OPC_FixLink(L);
				OPV_Expression(n->left, &x, OPC_Item__typ, selfForUnlock);
				OPC_Jcc(&x, OPC_Item__typ, &Lc, n);
				break;
			case 23: 
				OPC_DefLabel(&L);
				OPV_Statement(n->left, selfForUnlock);
				OPV_Expression(n->right, &x, OPC_Item__typ, selfForUnlock);
				OPC_Jncc(&x, OPC_Item__typ, &L, n);
				break;
			case 24: 
				prevExitChain = OPV_ExitChain;
				OPV_ExitChain = -1;
				OPC_DefLabel(&L);
				OPV_Statement(n->left, selfForUnlock);
				OPC_Jmp(&L, n);
				OPC_FixLink(OPV_ExitChain);
				OPV_ExitChain = prevExitChain;
				break;
			case 25: 
				OPC_Jmp(&OPV_ExitChain, n);
				break;
			case 26: 
				if (n->left != NIL) {
					if ((n->left->class == 13 && n->left->typ->form == 15)) {
						OPC_PushRegs();
						OPV_dummy.mode = 2;
						OPV_dummy.mnolev = OPC_level;
						OPV_dummy.adr = n->obj->conval->intval;
						OPV_dummy.typ = n->left->typ;
						OPV_Call(n->left, &OPV_dummy, OPC_Item__typ, 1);
						OPV_dummy.mode = 0;
					} else {
						OPV_Expression(n->left, &x, OPC_Item__typ, NIL);
						OPC_Return(&x, OPC_Item__typ, n->obj);
					}
				}
				if (selfForUnlock != NIL) {
					OPC_PushRegs();
					OPV_Expression(selfForUnlock, &x, OPC_Item__typ, NIL);
					OPV_Expression(selfForUnlock->link, &z, OPC_Item__typ, NIL);
					OPC_Unlock(x, z);
					OPC_PopResult(NIL, &x, OPC_Item__typ);
				}
				OPC_Exit(n->obj);
				break;
			case 27: 
				L = -1;
				Lc = -1;
				OPV_IfStat(n->left, selfForUnlock, &L, &Lc, 1);
				OPC_FixLink(Lc);
				if (n->subcl == 1) {
					OPV_Statement(n->right, selfForUnlock);
				} else {
					OPC_Trap(1, n);
				}
				OPC_FixLink(L);
				break;
			case 28: 
				OPC_Trap(n->right->conval->intval, n);
				break;
			case 29: 
				OPC_GenAsm(n);
				break;
			default: __CASECHK;
		}
		n = n->link;
	}
}

void OPV_Module (OPT_Node prog)
{
	OPV_Statement(prog, NIL);
	if ((__IN(7, OPM_parserOptions, 32) && OPM_noerr)) {
		OPM_err(254);
	}
}

static void EnumPtrs(void (*P)(void*))
{
	__ENUMR(&OPV_dummy, OPC_Item__typ, 32, 1, P);
}


export void *OPV__init(void)
{
	__DEFMOD;
	__MODULE_IMPORT(OPC);
	__MODULE_IMPORT(OPL);
	__MODULE_IMPORT(OPM);
	__MODULE_IMPORT(OPO);
	__MODULE_IMPORT(OPS);
	__MODULE_IMPORT(OPT);
	__MODULE_IMPORT(Oberon);
	__REGMOD("OPV", EnumPtrs);
/* BEGIN */
	OPV_dummy.mode = 0;
	OPT_typSize = OPV_TypSize;
	OPV_ParamAdr[0] = OPV_ParamAdrLR;
	OPV_ParamAdr[5] = OPV_ParamAdrLR;
	OPV_ParamAdr[2] = OPV_ParamAdrRL;
	OPV_ParamAdr[3] = OPV_ParamAdrRL;
	__ENDMOD;
}
