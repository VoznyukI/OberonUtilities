/* voc 2.1.0 [2017/09/06]. Bootstrapping compiler for address size 8, alignment 8. xtaSv */

#define SHORTINT INT8
#define INTEGER  INT16
#define LONGINT  INT32
#define SET      UINT32

#include "SYSTEM.h"
#include "OPA.h"
#include "OPB.h"
#include "OPM.h"
#include "OPS.h"
#include "OPT.h"

struct OPP__2 {
	INT32 low, high;
};

struct OPP__1 {
	OPT_Object obj;
	INT8 level;
};

typedef
	struct OPP__2 OPP_CaseTable[128];

typedef
	struct OPP_FixDesc *OPP_FixPtr;

typedef
	struct OPP_FixDesc {
		INT32 mode;
		OPT_Object scope;
		INT8 level;
		OPT_Node node;
		OPS_Token stream;
		OPP_FixPtr next;
	} OPP_FixDesc;

typedef
	struct OPP_TypeFix {
		INT32 pos;
		OPS_Name name;
		OPT_Object scope;
		INT8 level;
	} OPP_TypeFix;

typedef
	struct OPP_ObjFixDesc {
		INT32 pos;
		OPS_Name name;
		OPT_Object scope;
		INT8 level;
		OPT_Object obj;
	} OPP_ObjFixDesc;

typedef
	struct OPP_StructFixDesc {
		INT32 pos;
		OPS_Name name;
		OPT_Object scope;
		INT8 level;
		OPT_Struct typ;
	} OPP_StructFixDesc;


export CHAR OPP_SignOnMessage[80];
static INT8 OPP_sym, OPP_level;
static INT16 OPP_LoopLevel;
static OPT_Node OPP_TDinit, OPP_lastTDinit, OPP_RecInit, OPP_lastRecInit, OPP_CondNodes;
static INT8 OPP_CondCount;
static BOOLEAN OPP_UndefFlag, OPP_FixPhase;
static OPT_Object OPP_UndefObj;
static BOOLEAN OPP_scopeLock;
static OPP_FixPtr OPP_FixList, OPP_FixLast;
static OPT_Object OPP_ExtObj, OPP_inc;
static OPT_Struct OPP_ptrToRec;
static OPP_ObjFixDesc OPP_ObjFix[128];
static struct OPP__1 OPP_ObjCheck[256];
static OPP_StructFixDesc OPP_TypFix[128];
static INT32 OPP_nofCheck, OPP_nofObjFix, OPP_nofTypFix;

export ADDRESS *OPP__2__typ;
export ADDRESS *OPP_FixDesc__typ;
export ADDRESS *OPP_TypeFix__typ;
export ADDRESS *OPP_ObjFixDesc__typ;
export ADDRESS *OPP_StructFixDesc__typ;
export ADDRESS *OPP__1__typ;

static void OPP_ActualParameters (OPT_Node *aparlist, OPT_Object fpar);
static void OPP_AddTraceCode (OPT_Object owner, OPT_Node *statseq);
static void OPP_ArrayType (OPT_Struct *typ, OPT_Struct *banned);
static void OPP_Await (OPT_Node *x, INT16 *n);
static void OPP_Block (OPT_Node *procdec, OPT_Node *statseq);
static void OPP_BlockMode (UINT32 *flag, BOOLEAN local, BOOLEAN *lock);
static void OPP_CaseLabelList (OPT_Node *lab, INT16 LabelForm, INT16 *n, OPP_CaseTable tab);
static void OPP_CheckAndFix (OPT_Struct typ);
static void OPP_CheckArray (OPT_Struct typ);
static void OPP_CheckBool (OPT_Node *x);
static void OPP_CheckMark (INT8 *vis, BOOLEAN rdonlyAllowed);
static void OPP_CheckObj (OPT_Object obj);
static void OPP_CheckPointer (OPT_Struct typ);
static void OPP_CheckProcedure (OPT_Struct typ);
static void OPP_CheckRecord (OPT_Struct typ);
static void OPP_CheckStruct (OPT_Struct str);
static void OPP_CheckSym (INT16 s);
static void OPP_CheckSysFlag (INT8 *sysflag, INT8 default_, UINT32 allowed);
static void OPP_ConstExpression (OPT_Node *x);
static void OPP_CreateHiddenStructs (void);
static void OPP_DoFixes (void);
static void OPP_DumpScope (OPT_Object o);
static void OPP_Element (OPT_Node *x);
static void OPP_Expression (OPT_Node *x);
static void OPP_Factor (OPT_Node *x);
static void OPP_FormalParameters (OPT_Object *firstPar, OPT_Struct *resTyp, INT8 sysflag);
static void OPP_FullName (OPS_Name fullname);
static UINT32 OPP_GetFlags (OPT_Object obj);
static OPT_Object OPP_GetSelf (void);
static void OPP_InlineProc (OPT_Node *x, OPT_Node *apar, OPT_Object fpar);
static void OPP_InsertFix (INT32 mode, OPS_Token stream, OPT_Node node);
static BOOLEAN OPP_IsModuleScope (void);
static BOOLEAN OPP_IsObjectScope (void);
static BOOLEAN OPP_IsRecordScope (void);
export void OPP_Module (OPT_Node *prog, OPS_Name modName);
static void OPP_NewCheck (OPT_Object obj);
static void OPP_NewFix (OPP_TypeFix *f, ADDRESS *f__typ, OPS_Name name);
static void OPP_NewType (OPT_Object obj);
static void OPP_ObjectType (OPT_Struct *typ, OPT_Struct *banned);
static void OPP_OpCall (OPT_Object *op, OPT_Node *x, OPT_Node y);
static void OPP_OwnScope (OPT_Object *obj);
static void OPP_PointerType (OPT_Struct *typ, OPT_Struct *banned);
static void OPP_ProcedureDeclaration (OPT_Node *x);
static void OPP_RecordType (OPT_Struct *typ, OPT_Struct *banned, OPT_Object owner);
static void OPP_Resolve (OPT_Object *obj, CHAR *name, ADDRESS name__len, OPT_Node *x, OPT_Node *y);
static void OPP_SetFlags (OPT_Object obj, UINT32 flag);
static void OPP_Sets (OPT_Node *x);
static void OPP_SimpleExpression (OPT_Node *x);
static void OPP_StandProcCall (OPT_Node *x);
static void OPP_StatBlock (OPT_Node *statseq, BOOLEAN local);
static void OPP_StatSeq (OPT_Node *stat);
static void OPP_Term (OPT_Node *x);
static void OPP_TypeDecl (OPT_Struct *typ, OPT_Struct *banned, OPT_Object owner);
static void OPP_err (INT16 n);
static void OPP_qualident (OPT_Object *id);
static void OPP_selector (OPT_Node *x);


static void OPP_err (INT16 n)
{
	OPM_err(n);
}

static void OPP_CheckSym (INT16 s)
{
	if ((INT16)OPP_sym == s) {
		(*OPS_Get)(&OPP_sym);
	} else {
		OPM_err(s);
	}
}

static BOOLEAN OPP_IsModuleScope (void)
{
	return OPT_topScope->link->mode == 11;
}

static BOOLEAN OPP_IsObjectScope (void)
{
	return OPT_topScope->link->mode == 5;
}

static BOOLEAN OPP_IsRecordScope (void)
{
	OPT_Object owner;
	owner = OPT_topScope->link;
	return (((owner->mode == 5 && owner->typ != NIL)) && owner->typ->comp == 6);
}

static void OPP_SetFlags (OPT_Object obj, UINT32 flag)
{
	obj->conval->setval = obj->conval->setval | flag;
}

static UINT32 OPP_GetFlags (OPT_Object obj)
{
	return obj->conval->setval;
}

static void OPP_DumpScope (OPT_Object o)
{
	if (o != NIL) {
		OPP_DumpScope(o->left);
		OPM_LogWLn();
		OPM_LogWStr(o->name, 32);
		OPM_LogWNum(o->mode, 4);
		OPP_DumpScope(o->right);
	}
}

static OPT_Object OPP_GetSelf (void)
{
	OPT_Object self;
	OPT_FindInScope((CHAR*)"@SELF", 6, OPT_topScope, &self);
	return self;
}

static void OPP_InsertFix (INT32 mode, OPS_Token stream, OPT_Node node)
{
	OPP_FixPtr fix;
	__NEW(fix, OPP_FixDesc);
	fix->mode = mode;
	fix->stream = stream;
	fix->scope = OPT_topScope;
	fix->level = OPP_level;
	fix->node = node;
	fix->next = NIL;
	if (OPP_FixLast == NIL) {
		OPP_FixList = fix;
	} else {
		OPP_FixLast->next = fix;
	}
	OPP_FixLast = fix;
	node->link = NIL;
}

static void OPP_NewFix (OPP_TypeFix *f, ADDRESS *f__typ, OPS_Name name)
{
	OPS_Name name__copy;
	__DUPARR(name, OPS_Name);
	(*f).pos = OPM_errpos;
	(*f).scope = OPT_topScope;
	__MOVE(name, (*f).name, 32);
	(*f).level = OPP_level;
}

static void OPP_NewCheck (OPT_Object obj)
{
	OPP_ObjCheck[__X(OPP_nofCheck, 256)].obj = obj;
	OPP_ObjCheck[__X(OPP_nofCheck, 256)].level = OPP_level;
	OPP_nofCheck += 1;
}

static void OPP_NewType (OPT_Object obj)
{
	INT32 i;
	INT8 old;
	i = 0;
	while (i < OPP_nofTypFix) {
		if ((OPT_topScope == OPP_TypFix[__X(i, 128)].scope && __STRCMP(obj->name, OPP_TypFix[__X(i, 128)].name) == 0)) {
			OPP_TypFix[__X(i, 128)].typ->BaseTyp = obj->typ;
			OPP_CheckStruct(OPP_TypFix[__X(i, 128)].typ);
			obj->flag |= __SETOF(1,32);
			if ((!OPP_TypFix[__X(i, 128)].typ->incomplete && OPP_TypFix[__X(i, 128)].typ->strobj != NIL)) {
				OPP_CheckObj(OPP_TypFix[__X(i, 128)].typ->strobj);
				OPP_TypFix[__X(i, 128)].typ->strobj->mode = __ABS(OPP_TypFix[__X(i, 128)].typ->strobj->mode);
			}
			OPP_TypFix[__X(i, 128)].scope = NIL;
			OPP_TypFix[__X(i, 128)].typ = NIL;
		}
		i += 1;
	}
	while (i < OPP_nofObjFix) {
		if ((OPT_topScope == OPP_ObjFix[__X(i, 128)].scope && __STRCMP(obj->name, OPP_ObjFix[__X(i, 128)].name) == 0)) {
			OPP_ObjFix[__X(i, 128)].obj->typ = obj->typ;
			OPP_CheckObj(OPP_ObjFix[__X(i, 128)].obj);
			obj->flag |= __SETOF(1,32);
			if (!obj->typ->incomplete) {
				OPP_ObjFix[__X(i, 128)].obj->mode = __ABS(OPP_ObjFix[__X(i, 128)].obj->mode);
			}
			OPP_ObjFix[__X(i, 128)].scope = NIL;
			OPP_ObjFix[__X(i, 128)].obj = NIL;
		}
		i += 1;
	}
	i = 0;
	while (i < OPP_nofCheck) {
		if ((OPP_ObjCheck[__X(i, 256)].obj != NIL && OPP_ObjCheck[__X(i, 256)].obj->typ != NIL)) {
			OPP_CheckStruct(OPP_ObjCheck[__X(i, 256)].obj->typ);
			if (!OPP_ObjCheck[__X(i, 256)].obj->typ->incomplete) {
				old = OPP_level;
				OPP_level = OPP_ObjCheck[__X(i, 256)].level;
				OPP_ObjCheck[__X(i, 256)].obj->mode = __ABS(OPP_ObjCheck[__X(i, 256)].obj->mode);
				OPP_CheckObj(OPP_ObjCheck[__X(i, 256)].obj);
				OPP_ObjCheck[__X(i, 256)].obj = NIL;
				OPP_level = old;
			}
		}
		i += 1;
	}
}

static struct CheckRecord__19 {
	OPT_Struct *typ;
	struct CheckRecord__19 *lnk;
} *CheckRecord__19_s;

static void Traverse__20 (OPT_Object p);

static void Traverse__20 (OPT_Object p)
{
	OPT_Object fwd;
	if (p != NIL) {
		Traverse__20(p->left);
		if (p->mode == 13) {
			OPT_FindField((void*)p->name, 32, (*CheckRecord__19_s->typ)->BaseTyp, &fwd, 1);
			if ((fwd != NIL && fwd->mode == 13)) {
				OPM_errpos = p->conval->intval;
				OPB_CheckParameters(p->link->link, fwd->link->link, 0);
			}
			p->conval->intval = 0;
		} else if (p->mode == 4) {
			OPT_FindField((void*)p->name, 32, (*CheckRecord__19_s->typ)->BaseTyp, &fwd, 1);
			if (fwd != NIL) {
				OPM_Mark(1, p->conval->intval);
			}
		}
		Traverse__20(p->right);
	}
}

static void OPP_CheckRecord (OPT_Struct typ)
{
	OPT_Struct t, base;
	struct CheckRecord__19 _s;
	_s.typ = &typ;
	_s.lnk = CheckRecord__19_s;
	CheckRecord__19_s = &_s;
	__ASSERT(typ->comp == 6, 0);
	if (typ->rectest == 4660) {
		OPP_err(58);
		typ->BaseTyp = NIL;
		CheckRecord__19_s = _s.lnk;
		return;
	}
	base = typ->BaseTyp;
	if (base != NIL) {
		typ->rectest = 4660;
		OPP_CheckStruct(base);
		typ->rectest = 0;
		if (base->incomplete) {
			CheckRecord__19_s = _s.lnk;
			return;
		}
	}
	if (base == NIL) {
	} else if (base == OPT_undftyp) {
		typ->BaseTyp = NIL;
		OPP_err(999);
	} else {
		if (base->form == 13) {
			base = base->BaseTyp;
			typ->BaseTyp = base;
			if (typ->ptr == NIL) {
				OPM_Mark(249, typ->txtpos);
			}
		}
		OPT_MarkType(base);
		if (base->comp != 6) {
			OPM_Mark(52, typ->txtpos2);
			CheckRecord__19_s = _s.lnk;
			return;
		}
		if (base->sysflag == 1 || typ->sysflag == 1) {
			OPM_Mark(200, typ->txtpos2);
		}
		typ->extlev = base->extlev + 1;
		OPP_SetFlags(typ->strobj, (OPP_GetFlags(base->strobj) & 0x10));
		if (typ->strobj->link2 == NIL) {
			typ->strobj->link2 = base->strobj->link2;
		}
		t = base;
		while ((t != NIL && !__IN(1, OPP_GetFlags(t->strobj), 32))) {
			t = t->BaseTyp;
		}
		if (t != NIL) {
			OPP_SetFlags(typ->strobj, 0x04);
		}
		if (__IN(31, typ->strobj->conval->setval, 32)) {
			Traverse__20(typ->strobj->scope->right);
		}
	}
	typ->incomplete = 0;
	CheckRecord__19_s = _s.lnk;
}

static void OPP_CheckArray (OPT_Struct typ)
{
	OPT_Struct base;
	__ASSERT(__IN(typ->comp, 0x3c, 32), 0);
	OPP_CheckStruct(typ->BaseTyp);
	base = typ->BaseTyp;
	if (base->incomplete) {
		return;
	}
	switch (typ->comp) {
		case 2: 
			if (__IN(base->comp, 0x38, 32)) {
				OPM_Mark(89, typ->txtpos2);
			}
			break;
		case 5: case 4: 
			if (__IN(base->comp, (0x38 & ~__SETOF(typ->comp,32)), 32)) {
				OPM_Mark(89, typ->txtpos2);
			} else if (base->comp == typ->comp) {
				typ->n = base->n + 1;
			} else {
				typ->n = 0;
			}
			break;
		case 3: 
			if (__IN(base->comp, 0x30, 32)) {
				OPM_Mark(89, typ->txtpos2);
			}
			typ->offset = 0;
			break;
		default: __CASECHK;
	}
	typ->incomplete = 0;
}

static void OPP_CheckPointer (OPT_Struct typ)
{
	OPT_Struct base;
	__ASSERT(typ->form == 13, 0);
	OPP_CheckStruct(typ->BaseTyp);
	base = typ->BaseTyp;
	if (base->incomplete) {
		return;
	}
	if (!__IN(base->comp, 0x74, 32)) {
		typ->BaseTyp = OPT_undftyp;
		OPM_Mark(57, typ->txtpos2);
	}
	typ->incomplete = 0;
}

static void OPP_CheckProcedure (OPT_Struct typ)
{
	OPT_Object par;
	BOOLEAN quit;
	if (typ->BaseTyp == NIL) {
		return;
	}
	par = typ->link;
	quit = 0;
	while ((par != NIL && !quit)) {
		if (par->typ->incomplete) {
			OPP_CheckObj(par);
			quit = par->typ->incomplete;
		}
		par = par->link;
	}
	OPP_CheckStruct(typ->BaseTyp);
	typ->incomplete = quit || typ->BaseTyp->incomplete;
}

static void OPP_CheckStruct (OPT_Struct str)
{
	if (!str->incomplete || str == OPT_ToBeFixed) {
		return;
	}
	if (str->comp == 6) {
		OPP_CheckRecord(str);
	} else if (__IN(str->comp, 0x3c, 32)) {
		OPP_CheckArray(str);
	} else if (str->form == 13) {
		OPP_CheckPointer(str);
	} else if (str->form == 14) {
		OPP_CheckProcedure(str);
	} else {
		OPM_err(200);
	}
}

static void OPP_CheckObj (OPT_Object obj)
{
	if ((((__IN(obj->mode, 0xc0, 32) && obj->typ == NIL)) && OPP_FixPhase)) {
		obj->typ = OPT_undftyp;
		return;
	}
	OPP_CheckStruct(obj->typ);
	if (obj->typ->incomplete) {
		return;
	}
	if ((obj->typ->comp == 3 && OPP_level == 0)) {
		OPM_Mark(90, obj->txtpos);
	} else {
		switch (obj->mode) {
			case 1: case 2: 
				if (__IN(3, obj->flag, 32)) {
					if (obj->typ->comp == 4) {
						OPM_Mark(91, obj->txtpos);
					}
				} else {
					if (obj->typ->comp == 5) {
						OPM_Mark(88, obj->txtpos);
					}
				}
				break;
			case 4: 
				if (__IN(obj->typ->comp, 0x38, 32)) {
					OPM_Mark(88, obj->txtpos);
				}
				break;
			case 7: case 6: 
				if ((obj->typ == NIL && OPP_FixPhase)) {
					obj->typ = OPT_notyp;
				}
				break;
			default: 
				break;
		}
	}
}

static void OPP_qualident (OPT_Object *id)
{
	OPT_Object obj, self;
	INT8 lev;
	BOOLEAN m;
	OPT_Find(&obj);
	(*OPS_Get)(&OPP_sym);
	if ((((OPP_sym == 18 && obj != NIL)) && obj->mode == 11)) {
		m = 1;
		(*OPS_Get)(&OPP_sym);
		if (OPP_sym == 40) {
			OPT_FindImport(obj, &obj);
			(*OPS_Get)(&OPP_sym);
		} else {
			OPP_err(40);
			obj = NIL;
		}
	} else {
		m = 0;
	}
	if (obj == NIL) {
		if (OPP_FixPhase || m) {
			OPP_err(0);
			obj = OPT_NewObj();
			obj->mode = 1;
			obj->typ = OPT_undftyp;
			obj->adr = 0;
		} else {
			OPP_UndefFlag = 1;
			obj = OPP_UndefObj;
		}
	} else {
		if (__IN(obj->mode, 0x2010, 32)) {
			self = OPP_GetSelf();
			lev = self->mnolev;
		} else {
			lev = obj->mnolev;
		}
		if ((__IN(obj->mode, 0x2016, 32) && lev != OPP_level)) {
			obj->leaf = 0;
			if (lev > 0) {
				OPB_StaticLink(OPP_level - lev);
			}
		}
	}
	*id = obj;
	if ((*id == OPP_UndefObj && __IN(21, OPM_parserOptions, 32))) {
		OPP_err(260);
	}
}

static void OPP_ConstExpression (OPT_Node *x)
{
	BOOLEAN tmp;
	tmp = OPP_FixPhase;
	OPP_FixPhase = 1;
	OPP_Expression(&*x);
	if ((*x)->class != 7) {
		OPP_err(50);
		*x = OPB_NewIntConst(1);
	}
	OPP_FixPhase = tmp;
}

static void OPP_CheckMark (INT8 *vis, BOOLEAN rdonlyAllowed)
{
	(*OPS_Get)(&OPP_sym);
	if (OPP_sym == 1 || OPP_sym == 7) {
		if (OPP_level > 0) {
			OPP_err(47);
		}
		if (OPP_sym == 1) {
			*vis = 1;
		} else if (rdonlyAllowed) {
			*vis = 2;
		} else {
			OPP_err(47);
		}
		(*OPS_Get)(&OPP_sym);
	} else {
		*vis = 0;
	}
}

static void OPP_CheckSysFlag (INT8 *sysflag, INT8 default_, UINT32 allowed)
{
	OPT_Node x;
	INT32 sf;
	sf = default_;
	if (OPP_sym == 31) {
		if (!OPT_SYSimported) {
			OPP_err(135);
		}
		(*OPS_Get)(&OPP_sym);
		if (OPP_sym == 40) {
			if (__STRCMP(OPS_name, "C") == 0) {
				sf = 3;
			} else if (__STRCMP(OPS_name, "WINAPI") == 0) {
				sf = 2;
			} else if (__STRCMP(OPS_name, "NOTAG") == 0) {
				sf = 1;
			} else if (__STRCMP(OPS_name, "UNTRACED") == 0) {
				sf = 4;
			} else {
				OPP_err(115);
			}
			(*OPS_Get)(&OPP_sym);
		} else {
			OPP_err(40);
		}
		OPP_CheckSym(23);
	} else if (OPP_sym == 32) {
		(*OPS_Get)(&OPP_sym);
		if (OPP_sym == 40) {
			if (__STRCMP(OPS_name, "DELEGATE") == 0) {
				sf = 5;
			} else {
				OPP_err(115);
			}
			(*OPS_Get)(&OPP_sym);
		} else {
			OPP_err(40);
		}
		OPP_CheckSym(24);
	}
	if ((sf != default_ && !__IN(sf, allowed, 32))) {
		sf = default_;
		OPP_err(200);
	}
	*sysflag = (INT8)((INT16)sf);
}

static struct BlockMode__8 {
	struct BlockMode__8 *lnk;
} *BlockMode__8_s;

static void ProtectScope__9 (void);

static void ProtectScope__9 (void)
{
	OPT_Object p;
	p = OPT_topScope;
	if ((((p != NIL && __IN(p->link->mode, 0xc0, 32))) && __IN(p->link->typ->comp, 0x28, 32))) {
		OPP_err(200);
	}
	while ((p != NIL && !__IN(p->link->mode, 0x0820, 32))) {
		p = p->left;
	}
	if (p == NIL) {
		OPP_err(1000);
	} else if ((p->link->mode == 5 && p->link->typ->ptr == NIL)) {
		OPP_err(252);
	}
	p->link->conval->setval |= __SETOF(4,32);
}

static void OPP_BlockMode (UINT32 *flag, BOOLEAN local, BOOLEAN *lock)
{
	OPT_Node x;
	BOOLEAN objscope;
	struct BlockMode__8 _s;
	_s.lnk = BlockMode__8_s;
	BlockMode__8_s = &_s;
	*lock = 0;
	objscope = OPP_IsObjectScope();
	if (OPP_sym == 32) {
		(*OPS_Get)(&OPP_sym);
		for (;;) {
			if (OPP_sym == 40) {
				if (__STRCMP(OPS_name, "EXCLUSIVE") == 0) {
					(*OPS_Get)(&OPP_sym);
					ProtectScope__9();
					*flag |= __SETOF(6,32);
					*lock = 1;
				} else if (!local) {
					if (__STRCMP(OPS_name, "ACTIVE") == 0) {
						if (!objscope) {
							OPP_err(200);
						}
						*flag |= __SETOF(5,32);
						(*OPS_Get)(&OPP_sym);
					} else if (__STRCMP(OPS_name, "PRIORITY") == 0) {
						if (!objscope) {
							OPP_err(200);
						}
						if (!__IN(5, *flag, 32)) {
							OPP_err(272);
						}
						(*OPS_Get)(&OPP_sym);
						if (OPP_sym == 30) {
							OPP_ConstExpression(&x);
							if (x->class != 7) {
								OPP_err(50);
							} else if (x->typ->form != 4) {
								OPP_err(220);
							} else {
								OPT_topScope->link->prio = (INT8)((INT16)x->conval->intval);
							}
						} else {
							x = OPB_NewIntConst(0);
						}
					} else if (__STRCMP(OPS_name, "SAFE") == 0) {
						if (!__IN(5, *flag, 32)) {
							OPP_err(272);
						}
						*flag |= __SETOF(8,32);
						(*OPS_Get)(&OPP_sym);
					} else {
						OPP_err(0);
						(*OPS_Get)(&OPP_sym);
					}
				} else {
					OPP_err(0);
					(*OPS_Get)(&OPP_sym);
				}
			} else if (OPP_sym != 24) {
				OPP_err(0);
				(*OPS_Get)(&OPP_sym);
			}
			if (OPP_sym == 24) {
				break;
			}
			OPP_CheckSym(19);
		}
		OPP_CheckSym(24);
	}
	if ((((!local && objscope)) && !__IN(5, *flag, 32))) {
		OPP_err(999);
	}
	BlockMode__8_s = _s.lnk;
}

static void OPP_RecordType (OPT_Struct *typ, OPT_Struct *banned, OPT_Object owner)
{
	OPT_Object base;
	INT8 sysflag;
	INT32 c;
	OPT_Node procdec, statseq, p;
	INT8 lev;
	*typ = OPT_NewStr(15, 6);
	(*typ)->BaseTyp = NIL;
	if (OPP_ptrToRec != NIL) {
		(*typ)->ptr = OPP_ptrToRec;
		OPP_ptrToRec = NIL;
	}
	if (owner == NIL) {
		owner = OPT_NewObj();
		owner->mode = 5;
		owner->name[0] = 0x00;
		owner->vis = 0;
		owner->typ = *typ;
	}
	owner->conval = OPT_NewConst();
	(*typ)->strobj = owner;
	OPP_CheckSysFlag(&sysflag, 0, 0x03);
	(*typ)->incomplete = 1;
	if (OPP_sym == 30) {
		(*OPS_Get)(&OPP_sym);
		if (OPP_sym == 40) {
			(*typ)->txtpos2 = OPM_errpos;
			OPP_qualident(&base);
			if ((base != OPP_UndefObj && base->mode == 5)) {
				if (base->typ == *banned) {
					OPP_err(58);
				} else {
					(*typ)->BaseTyp = base->typ;
				}
			} else if (base == OPP_UndefObj) {
				OPP_UndefFlag = 0;
				if (OPP_sym == 18) {
					OPT_FindInScope(OPS_name, 32, OPP_ExtObj, &base);
					(*OPS_Get)(&OPP_sym);
					if ((base != NIL && base->mode == 11)) {
						OPT_FindImport(base, &base);
					}
					OPP_CheckSym(40);
					if (base == NIL) {
						OPP_err(0);
					} else if (base->mode != 5) {
						OPP_err(52);
					} else if (base->typ == *banned) {
						OPP_err(58);
					} else {
						(*typ)->BaseTyp = base->typ;
					}
				} else {
					(*typ)->BaseTyp = OPT_ToBeFixed;
					OPP_NewFix((void*)&OPP_TypFix[__X(OPP_nofTypFix, 128)], OPP_StructFixDesc__typ, OPS_name);
					OPP_TypFix[__X(OPP_nofTypFix, 128)].typ = *typ;
					OPP_nofTypFix += 1;
				}
			} else {
				OPP_err(52);
			}
		} else {
			OPP_err(40);
		}
		OPP_CheckSym(22);
	}
	(*typ)->sysflag = sysflag;
	OPP_CheckRecord(*typ);
	OPT_OpenScope(0, owner);
	lev = OPP_level;
	OPP_level = 0;
	c = OPM_errpos;
	if (OPP_sym == 41) {
		(*OPS_Get)(&OPP_sym);
	}
	OPP_Block(&procdec, &statseq);
	if ((*typ)->link == NIL) {
		(*typ)->link = OPT_topScope->right;
	}
	__ASSERT(statseq == NIL || __IN(1, owner->conval->setval, 32), 0);
	if ((procdec != NIL || __IN(1, owner->conval->setval, 32)) || statseq != NIL) {
		p = OPP_CondNodes;
		while (p != NIL) {
			p->obj->mnolev = 1;
			p = p->link;
		}
		OPB_Enter(&OPP_CondNodes, statseq, owner);
		OPP_CondNodes->link = procdec;
		procdec = OPP_CondNodes;
		procdec->conval = OPT_NewConst();
		procdec->conval->intval = c;
		OPB_Link(&OPP_RecInit, &OPP_lastRecInit, procdec);
	}
	OPP_level = lev;
	OPT_CloseScope();
}

static void OPP_OwnScope (OPT_Object *obj)
{
	if (!__IN((*obj)->mode, 0x0128, 32)) {
		if (OPP_IsRecordScope() || ((((*obj)->mnolev == OPT_topScope->mnolev && (*obj)->link2 == NIL)) && (*obj)->myscope == OPT_topScope)) {
			OPP_err(90);
		}
	}
}

static struct ArrayType__3 {
	struct ArrayType__3 *lnk;
} *ArrayType__3_s;

static OPT_Object HiddenVar__4 (CHAR *name, ADDRESS name__len, OPT_Node exp);

static OPT_Object HiddenVar__4 (CHAR *name, ADDRESS name__len, OPT_Node exp)
{
	OPT_Object dim, owner;
	OPT_Node y;
	__DUP(name, name__len, CHAR);
	owner = OPT_topScope;
	while ((OPT_topScope->left != NIL && OPT_topScope->link == OPT_topScope->left->link)) {
		OPT_topScope = OPT_topScope->left;
	}
	OPT_Insert((CHAR*)"@@", 3, &dim);
	__COPY(name, dim->name, 32);
	dim->link = NIL;
	dim->mode = 1;
	dim->typ = OPT_linttyp;
	dim->flag = 0x02;
	if (OPT_topScope->scope == NIL) {
		OPT_topScope->scope = dim;
	} else {
		dim->link = OPT_topScope->scope;
		OPT_topScope->scope = dim;
	}
	OPT_topScope = owner;
	y = OPB_NewLeaf(dim);
	OPB_Assign(&y, exp);
	y->conval = OPT_NewConst();
	y->conval->intval = OPM_errpos;
	OPB_CodeInsert(&y);
	__DEL(name);
	return dim;
}

static void OPP_ArrayType (OPT_Struct *typ, OPT_Struct *banned)
{
	OPT_Node x;
	INT32 n;
	INT8 sysflag;
	struct ArrayType__3 _s;
	_s.lnk = ArrayType__3_s;
	ArrayType__3_s = &_s;
	OPP_CheckSysFlag(&sysflag, 0, 0x03);
	if (OPP_sym == 1) {
		*typ = OPT_NewStr(15, 4);
		(*typ)->sysflag = sysflag;
		(*OPS_Get)(&OPP_sym);
		if (__IN(21, OPM_parserOptions, 32)) {
			OPP_err(271);
		}
	} else if (OPP_sym != 25) {
		OPP_Expression(&x);
		if (x->class == 7) {
			*typ = OPT_NewStr(15, 2);
			(*typ)->sysflag = sysflag;
			if (__IN(x->typ->form, 0x70, 32)) {
				n = x->conval->intval;
				if (n <= 0 || n > 2147483647) {
					OPP_err(63);
					n = 1;
				}
			} else {
				OPP_err(51);
				n = 1;
			}
			(*typ)->n = n;
			(*typ)->link = NIL;
		} else {
			*typ = OPT_NewStr(15, 3);
			(*typ)->sysflag = sysflag;
			(*typ)->n = 0;
			if (x->typ == NIL || !__IN(x->typ->form, 0x70, 32)) {
				(*typ)->comp = 2;
				OPP_err(68);
			} else {
				(*typ)->link = HiddenVar__4((CHAR*)"@dim", 5, x);
			}
			if (__IN(21, OPM_parserOptions, 32)) {
				OPP_err(271);
			}
		}
	} else {
		*typ = OPT_NewStr(15, 5);
		(*typ)->sysflag = sysflag;
	}
	(*typ)->incomplete = 1;
	if (OPP_sym == 19) {
		(*OPS_Get)(&OPP_sym);
		(*typ)->txtpos2 = OPM_errpos;
		OPP_ArrayType(&(*typ)->BaseTyp, &*banned);
	} else if (OPP_sym == 25) {
		(*OPS_Get)(&OPP_sym);
		(*typ)->txtpos2 = OPM_errpos;
		OPP_TypeDecl(&(*typ)->BaseTyp, &*banned, NIL);
		if ((*typ)->BaseTyp == OPT_ToBeFixed) {
			OPP_NewFix((void*)&OPP_TypFix[__X(OPP_nofTypFix, 128)], OPP_StructFixDesc__typ, OPS_name);
			OPP_TypFix[__X(OPP_nofTypFix, 128)].typ = *typ;
			OPP_nofTypFix += 1;
		}
	}
	OPP_CheckArray(*typ);
	ArrayType__3_s = _s.lnk;
}

static void OPP_ObjectType (OPT_Struct *typ, OPT_Struct *banned)
{
	*typ = OPT_NewStr(13, 1);
	(*typ)->incomplete = 1;
	OPP_ptrToRec = *typ;
	(*typ)->txtpos2 = OPM_curpos;
	OPP_RecordType(&(*typ)->BaseTyp, &*banned, NIL);
	if ((*typ)->BaseTyp == OPT_ToBeFixed) {
		OPP_NewFix((void*)&OPP_TypFix[__X(OPP_nofTypFix, 128)], OPP_StructFixDesc__typ, OPS_name);
		OPP_TypFix[__X(OPP_nofTypFix, 128)].typ = *typ;
		OPP_nofTypFix += 1;
	}
	OPP_CheckPointer(*typ);
}

static void OPP_PointerType (OPT_Struct *typ, OPT_Struct *banned)
{
	OPT_Object id;
	*typ = OPT_NewStr(13, 1);
	OPP_CheckSysFlag(&(*typ)->sysflag, 0, 0x01);
	(*typ)->incomplete = 1;
	OPP_CheckSym(28);
	if (OPP_sym == 40) {
		OPT_Find(&id);
		(*typ)->txtpos2 = OPM_errpos;
		if (id == NIL) {
			OPP_NewFix((void*)&OPP_TypFix[__X(OPP_nofTypFix, 128)], OPP_StructFixDesc__typ, OPS_name);
			OPP_TypFix[__X(OPP_nofTypFix, 128)].typ = *typ;
			OPP_nofTypFix += 1;
			(*typ)->BaseTyp = OPT_ToBeFixed;
			(*OPS_Get)(&OPP_sym);
		} else {
			OPP_qualident(&id);
			if (id->mode == 5) {
				(*typ)->BaseTyp = id->typ;
			} else {
				(*typ)->BaseTyp = OPT_undftyp;
				OPP_err(52);
			}
		}
	} else {
		if (OPP_sym == 58) {
			OPP_ptrToRec = *typ;
		}
		(*typ)->txtpos2 = OPM_curpos;
		OPP_TypeDecl(&(*typ)->BaseTyp, &*banned, NIL);
		if ((*typ)->BaseTyp == OPT_ToBeFixed) {
			OPP_NewFix((void*)&OPP_TypFix[__X(OPP_nofTypFix, 128)], OPP_StructFixDesc__typ, OPS_name);
			OPP_TypFix[__X(OPP_nofTypFix, 128)].typ = *typ;
			OPP_nofTypFix += 1;
		}
		OPP_CheckPointer(*typ);
	}
}

static void OPP_FormalParameters (OPT_Object *firstPar, OPT_Struct *resTyp, INT8 sysflag)
{
	INT8 mode;
	OPT_Object par, first, last, res;
	OPT_Struct typ, btyp;
	first = NIL;
	last = *firstPar;
	if (OPP_sym == 40 || OPP_sym == 64) {
		for (;;) {
			if (OPP_sym == 64) {
				(*OPS_Get)(&OPP_sym);
				mode = 2;
			} else {
				mode = 1;
			}
			for (;;) {
				if (OPP_sym == 40) {
					OPT_Insert(OPS_name, 32, &par);
					(*OPS_Get)(&OPP_sym);
					par->flag = 0x08;
					par->mode = mode;
					par->link = NIL;
					if (first == NIL) {
						first = par;
					}
					if (*firstPar == NIL) {
						*firstPar = par;
					} else {
						last->link = par;
					}
					last = par;
				} else {
					OPP_err(40);
				}
				if (OPP_sym == 19) {
					(*OPS_Get)(&OPP_sym);
				} else if (OPP_sym == 40) {
					OPP_err(19);
				} else if (OPP_sym == 64) {
					OPP_err(19);
					(*OPS_Get)(&OPP_sym);
				} else {
					break;
				}
			}
			OPP_CheckSym(20);
			OPP_TypeDecl(&typ, &OPT_notyp, NIL);
			if ((((!typ->incomplete && typ->strobj == NIL)) && typ->comp != 5)) {
				OPP_err(-305);
			}
			if (__IN(sysflag, 0x0c, 32)) {
				if ((__IN(typ->comp, 0x60, 32) && typ->sysflag != 1)) {
					OPP_err(200);
				}
				if (__IN(typ->comp, 0x18, 32)) {
					OPP_err(200);
				}
			}
			if (mode == 1) {
				OPT_MarkType(typ);
			}
			while (first != NIL) {
				if (typ == OPT_ToBeFixed) {
					OPP_NewFix((void*)&OPP_ObjFix[__X(OPP_nofObjFix, 128)], OPP_ObjFixDesc__typ, OPS_name);
					OPP_ObjFix[__X(OPP_nofObjFix, 128)].obj = first;
					OPP_nofObjFix += 1;
				}
				if (typ->incomplete) {
					OPP_NewCheck(first);
					first->mode = -first->mode;
				}
				first->typ = typ;
				first = first->link;
			}
			if (OPP_sym == 41) {
				(*OPS_Get)(&OPP_sym);
			} else if (OPP_sym == 40) {
				OPP_err(41);
			} else {
				break;
			}
		}
	}
	OPP_CheckSym(22);
	if (OPP_sym == 20) {
		(*OPS_Get)(&OPP_sym);
		*resTyp = OPT_undftyp;
		typ = NIL;
		while (OPP_sym == 56) {
			(*OPS_Get)(&OPP_sym);
			OPP_CheckSym(25);
			btyp = typ;
			typ = OPT_NewStr(15, 5);
			typ->incomplete = 1;
			typ->BaseTyp = btyp;
			if (btyp == NIL) {
				*resTyp = typ;
			}
		}
		if (OPP_sym == 40) {
			OPP_qualident(&res);
			if (res == OPP_UndefObj) {
				if (typ != NIL) {
					OPP_NewFix((void*)&OPP_TypFix[__X(OPP_nofTypFix, 128)], OPP_StructFixDesc__typ, OPS_name);
					OPP_TypFix[__X(OPP_nofTypFix, 128)].typ = *resTyp;
					OPP_nofTypFix += 1;
					*resTyp = typ;
				} else {
					*resTyp = NIL;
				}
				if (sysflag != 0) {
					OPP_err(200);
				}
			} else if (res->mode == 5) {
				if (typ != NIL) {
					(*resTyp)->BaseTyp = res->typ;
					*resTyp = typ;
					OPP_CheckStruct(typ);
				} else {
					*resTyp = res->typ;
				}
				if ((sysflag != 0 && (*resTyp)->form == 15)) {
					OPP_err(200);
				}
			} else {
				OPP_err(52);
			}
		} else {
			OPP_err(40);
		}
	} else {
		*resTyp = OPT_notyp;
	}
}

static void OPP_CheckAndFix (OPT_Struct typ)
{
	INT8 lev;
	while (typ->comp == 3) {
		lev = typ->link->mnolev;
		if (lev != OPP_level) {
			typ->link->leaf = 0;
			if (lev > 0) {
				OPB_StaticLink(OPP_level - lev);
			}
		}
		typ = typ->BaseTyp;
	}
}

static void OPP_TypeDecl (OPT_Struct *typ, OPT_Struct *banned, OPT_Object owner)
{
	OPT_Object id;
	OPS_Name name;
	*typ = OPT_undftyp;
	if (OPP_sym < 30) {
		OPP_err(12);
		do {
			(*OPS_Get)(&OPP_sym);
		} while (!(OPP_sym >= 30));
	}
	__COPY(OPS_name, name, 32);
	if (OPP_sym == 40) {
		OPP_qualident(&id);
		__COPY(name, OPS_name, 32);
		if (id == OPP_UndefObj) {
			*typ = OPT_undftyp;
			OPP_UndefFlag = 0;
			if (OPP_sym == 18) {
				OPT_FindInScope(name, 32, OPP_ExtObj, &id);
				if ((id != NIL && id->mode == 11)) {
					(*OPS_Get)(&OPP_sym);
					OPT_FindImport(id, &id);
					(*OPS_Get)(&OPP_sym);
				}
				if (id == NIL) {
					OPP_err(0);
					*typ = OPT_undftyp;
				} else if (id->mode == 5) {
					if (id->typ != *banned) {
						*typ = id->typ;
					} else {
						OPP_err(58);
					}
				} else {
					OPP_err(52);
					*typ = OPT_undftyp;
				}
			} else {
				*typ = OPT_ToBeFixed;
			}
		} else if (id->mode == 5) {
			if (id->typ != *banned) {
				*typ = id->typ;
			} else {
				OPP_err(58);
			}
		} else {
			OPP_err(52);
		}
		if (id != NIL) {
			OPP_CheckAndFix(id->typ);
		}
	} else if (OPP_sym == 56) {
		(*OPS_Get)(&OPP_sym);
		OPP_ArrayType(&*typ, &*banned);
	} else if (OPP_sym == 58) {
		(*OPS_Get)(&OPP_sym);
		OPP_RecordType(&*typ, &*banned, owner);
		OPB_Inittd(&OPP_TDinit, &OPP_lastTDinit, *typ);
	} else if (OPP_sym == 59) {
		(*OPS_Get)(&OPP_sym);
		OPP_PointerType(&*typ, &*banned);
	} else if (OPP_sym == 57) {
		(*OPS_Get)(&OPP_sym);
		OPP_ObjectType(&*typ, &*banned);
		OPB_Inittd(&OPP_TDinit, &OPP_lastTDinit, (*typ)->BaseTyp);
	} else if (OPP_sym == 65) {
		(*OPS_Get)(&OPP_sym);
		*typ = OPT_NewStr(14, 1);
		OPP_CheckSysFlag(&(*typ)->sysflag, 0, 0x2d);
		if (OPP_sym == 30) {
			(*OPS_Get)(&OPP_sym);
			OPT_OpenScope(OPP_level, NIL);
			OPP_FormalParameters(&(*typ)->link, &(*typ)->BaseTyp, (*typ)->sysflag);
			OPT_CloseScope();
			id = (*typ)->link;
			while ((id != NIL && !id->typ->incomplete)) {
				id = id->link;
			}
			(*typ)->incomplete = (id != NIL && id->typ->incomplete);
			if ((*typ)->BaseTyp == NIL) {
				OPP_NewFix((void*)&OPP_TypFix[__X(OPP_nofTypFix, 128)], OPP_StructFixDesc__typ, OPS_name);
				OPP_TypFix[__X(OPP_nofTypFix, 128)].typ = *typ;
				OPP_nofTypFix += 1;
				(*typ)->incomplete = 1;
			}
			OPP_UndefFlag = 0;
		} else {
			(*typ)->BaseTyp = OPT_notyp;
			(*typ)->link = NIL;
		}
	} else {
		OPP_err(12);
	}
	for (;;) {
		if ((((OPP_sym >= 41 && OPP_sym <= 44) || OPP_sym == 22) || OPP_sym == 68) || OPP_sym == 40) {
			break;
		}
		OPP_err(15);
		if (OPP_sym == 40) {
			break;
		}
		(*OPS_Get)(&OPP_sym);
	}
}

static void OPP_selector (OPT_Node *x)
{
	OPT_Object obj, proc;
	OPT_Node y;
	OPT_Struct typ;
	OPS_Name name;
	if (__STRCMP((*x)->obj->name, "SELF") == 0) {
		OPT_FindInScope((CHAR*)"@SELF", 6, OPT_topScope, &obj);
		if (obj->typ->comp == 6) {
			*x = OPB_NewLeaf(obj);
			if ((obj->typ->ptr != NIL && OPP_sym != 18)) {
				OPB_StPar0(&*x, 20);
				OPB_StFct(&*x, 20, 1);
				(*x)->typ = obj->typ->ptr;
			}
		} else if (obj->typ != OPT_ptrtyp) {
			*x = OPB_NewLeaf(obj);
		}
	}
	for (;;) {
		if (OPP_sym == 31) {
			(*OPS_Get)(&OPP_sym);
			for (;;) {
				if (((*x)->typ != NIL && (*x)->typ->form == 13)) {
					OPB_DeRef(&*x);
				}
				OPP_Expression(&y);
				if (!OPP_UndefFlag) {
					OPB_Index(&*x, y);
				}
				if (OPP_sym == 19) {
					(*OPS_Get)(&OPP_sym);
				} else {
					break;
				}
			}
			OPP_CheckSym(23);
		} else if (OPP_sym == 18) {
			(*OPS_Get)(&OPP_sym);
			if (OPP_sym == 40) {
				__MOVE(OPS_name, name, 32);
				(*OPS_Get)(&OPP_sym);
				if ((OPP_UndefFlag && !OPP_FixPhase)) {
				} else if ((*x)->typ != NIL) {
					if ((*x)->typ->form == 13) {
						OPT_MarkObj((*x)->typ->strobj);
						OPB_DeRef(&*x);
					}
					if ((*x)->typ->comp == 6) {
						OPT_FindField((void*)name, 32, (*x)->typ, &obj, 1);
						if (((obj == NIL || obj->mode < 0) && !OPP_FixPhase)) {
							OPP_UndefFlag = 1;
						} else {
							OPB_Field(&*x, obj);
						}
					} else if (((*x)->typ == OPT_undftyp && !OPP_FixPhase)) {
						OPP_UndefFlag = 1;
					} else {
						OPP_err(53);
					}
				} else {
					OPP_err(52);
				}
			} else {
				OPP_err(40);
			}
		} else if (OPP_sym == 17) {
			(*OPS_Get)(&OPP_sym);
			if ((OPP_UndefFlag && !OPP_FixPhase)) {
			} else if (((*x)->obj != NIL && (*x)->obj->mode == 13)) {
				y = (*x)->left;
				if (y->class == 3) {
					y = y->left;
				}
				if (y->obj != NIL) {
					proc = OPT_topScope;
					while ((proc->link != NIL && proc->link->mode != 13)) {
						proc = proc->left;
					}
					if (proc->link == NIL || proc->link->link != y->obj) {
						OPP_err(75);
					}
					typ = y->obj->typ;
					if (typ->form == 13) {
						typ = typ->BaseTyp;
					}
					OPT_FindField((void*)(*x)->obj->name, 32, typ->BaseTyp, &proc, 1);
					if (proc != NIL) {
						(*x)->subcl = 1;
					} else {
						OPP_err(74);
					}
				} else {
					OPP_err(75);
				}
			} else if ((*x)->typ->form != 13) {
				OPP_err(84);
			} else {
				OPB_DeRef(&*x);
			}
		} else if ((((OPP_sym == 30 && OPP_UndefFlag)) && !OPP_FixPhase)) {
			(*OPS_Get)(&OPP_sym);
			OPP_UndefFlag = 0;
			if (OPP_sym != 22) {
				OPP_Expression(&*x);
				while (OPP_sym == 19) {
					(*OPS_Get)(&OPP_sym);
					OPP_UndefFlag = 0;
					OPP_Expression(&*x);
				}
			}
			OPP_CheckSym(22);
			OPP_UndefFlag = 1;
		} else if ((((((((OPP_sym == 30 && (*x)->class < 7)) && (*x)->typ != NIL)) && (*x)->typ->form != 14)) && ((*x)->obj == NIL || (*x)->obj->mode != 13))) {
			(*OPS_Get)(&OPP_sym);
			if (OPP_sym == 40) {
				OPP_qualident(&obj);
				if (obj->mode == 5) {
					OPB_TypTest(&*x, obj, 1);
				} else if (!OPP_UndefFlag) {
					OPP_err(52);
				} else if (OPP_sym == 18) {
					OPP_err(0);
					(*OPS_Get)(&OPP_sym);
					OPP_CheckSym(40);
				}
			} else {
				OPP_err(40);
			}
			OPP_CheckSym(22);
		} else {
			break;
		}
	}
}

static void OPP_ActualParameters (OPT_Node *aparlist, OPT_Object fpar)
{
	OPT_Node apar, last, aparret, lastret;
	BOOLEAN b;
	*aparlist = NIL;
	last = NIL;
	b = OPP_UndefFlag;
	lastret = NIL;
	aparret = NIL;
	if (OPP_sym != 22) {
		for (;;) {
			OPP_Expression(&apar);
			if (fpar != NIL) {
				OPP_UndefFlag = OPP_UndefFlag || fpar->mode < 0;
				if ((!OPP_UndefFlag && !b)) {
					OPB_Param(&apar, fpar);
					OPB_Link(&*aparlist, &last, apar);
				}
				fpar = fpar->link;
			} else if ((!OPP_UndefFlag && !b)) {
				OPP_err(64);
			}
			if (OPP_sym == 19) {
				(*OPS_Get)(&OPP_sym);
			} else if ((30 <= OPP_sym && OPP_sym <= 40)) {
				OPP_err(19);
			} else {
				break;
			}
		}
		if (aparret != NIL) {
			lastret->link = *aparlist;
			*aparlist = aparret;
		}
	}
	if ((((fpar != NIL && !OPP_UndefFlag)) && !b)) {
		OPP_err(65);
	}
	OPP_UndefFlag = OPP_UndefFlag || b;
}

static void OPP_Await (OPT_Node *x, INT16 *n)
{
	OPT_Object proc, self;
	OPT_Node exp, cond;
	OPS_Name name;
	INT32 i;
	OPS_Token ts;
	self = OPP_GetSelf();
	if (OPP_sym == 30) {
		*n = 1;
		(*OPS_Get)(&OPP_sym);
		if (OPT_topScope->link == NIL) {
			__COPY("$$", name, 32);
		} else {
			__COPY(OPT_topScope->link->name, name, 32);
		}
		i = 0;
		while (name[__X(i, 32)] != 0x00) {
			i += 1;
		}
		name[__X(i, 32)] = '.';
		name[__X(i + 1, 32)] = '@';
		name[__X(i + 2, 32)] = (CHAR)((INT16)(int)__MOD(__DIV(OPP_CondCount, 100), 10) + 48);
		name[__X(i + 3, 32)] = (CHAR)((INT16)(int)__MOD(__DIV(OPP_CondCount, 10), 10) + 48);
		name[__X(i + 4, 32)] = (CHAR)((INT16)(int)__MOD(OPP_CondCount, 10) + 48);
		name[__X(i + 5, 32)] = 0x00;
		OPP_CondCount += 1;
		OPT_Insert(name, 32, &proc);
		proc->mode = 7;
		proc->link = NIL;
		proc->vis = 0;
		proc->adr = 0;
		proc->typ = OPT_booltyp;
		proc->conval = OPT_NewConst();
		proc->conval->setval = 0x0a;
		proc->conval->intval = 12;
		OPP_level += 1;
		OPT_OpenScope(OPP_level, proc);
		OPP_Expression(&*x);
		if (OPP_UndefFlag) {
			exp = *x;
			proc->typ = (*x)->typ;
			OPB_Return(&*x, proc);
			proc->typ = OPT_booltyp;
		} else {
			OPB_StPar0(&*x, 64);
			OPB_Return(&*x, proc);
		}
		OPT_CloseScope();
		OPP_level -= 1;
		(*x)->conval = OPT_NewConst();
		(*x)->conval->intval = OPM_errpos;
		cond = NIL;
		OPB_Enter(&cond, *x, proc);
		cond->link = OPP_CondNodes;
		OPP_CondNodes = cond;
		cond->conval = OPT_NewConst();
		cond->conval->intval = OPM_errpos;
		*x = OPB_NewLeaf(proc);
		(*x)->link = OPB_NewLeaf(self);
		OPP_CheckSym(22);
	} else {
		OPP_err(65);
	}
	(*x)->link->link = OPB_NewIntConst(0);
	if (OPP_UndefFlag) {
		OPP_UndefFlag = 0;
		OPS_StopRecording(&ts);
		OPP_InsertFix(7, ts, exp);
	}
}

static void OPP_StandProcCall (OPT_Node *x)
{
	OPT_Node y;
	INT8 m;
	INT16 n;
	BOOLEAN flag, flag1;
	m = (INT8)((INT16)(*x)->obj->adr);
	n = 0;
	flag = 0;
	if (((m == 12 || m == 17) && OPB_verify != NIL)) {
		flag = 1;
		OPB_verify = NIL;
		flag1 = OPP_FixPhase;
		OPP_FixPhase = 1;
	}
	if (m == 64) {
		OPP_Await(&*x, &n);
	} else if (OPP_sym == 30) {
		(*OPS_Get)(&OPP_sym);
		if (OPP_sym != 22) {
			for (;;) {
				if (n == 0) {
					OPP_Expression(&*x);
					if ((((((((!OPP_UndefFlag && !OPP_FixPhase)) && m == 1)) && n == 0)) && (*x)->typ->BaseTyp == OPT_undftyp)) {
						OPP_UndefFlag = 1;
					}
					if (!OPP_UndefFlag) {
						OPB_StPar0(&*x, m);
					}
					n = 1;
				} else if (n == 1) {
					OPP_Expression(&y);
					if (!OPP_UndefFlag) {
						OPB_StPar1(&*x, y, m);
					}
					n = 2;
				} else {
					OPP_Expression(&y);
					if (!OPP_UndefFlag) {
						OPB_StParN(&*x, y, m, n);
					}
					n += 1;
				}
				if (OPP_sym == 19) {
					(*OPS_Get)(&OPP_sym);
				} else if ((30 <= OPP_sym && OPP_sym <= 40)) {
					OPP_err(19);
				} else {
					break;
				}
			}
			OPP_CheckSym(22);
		} else {
			(*OPS_Get)(&OPP_sym);
		}
	}
	if (!OPP_UndefFlag) {
		OPB_StFct(&*x, m, n);
	}
	if (flag) {
		OPB_verify = OPP_OwnScope;
		OPP_FixPhase = flag1;
	}
	if ((OPP_level > 0 && (m == 1 || m == 30))) {
		OPT_topScope->link->leaf = 0;
	}
}

static struct InlineProc__38 {
	OPT_Object *inline, *par;
	BOOLEAN *assembly;
	struct InlineProc__38 *lnk;
} *InlineProc__38_s;

static void CopyLocals__39 (OPT_Object obj);

static void CopyLocals__39 (OPT_Object obj)
{
	OPT_Object new;
	OPS_Name name;
	INT32 i, j;
	if (obj != NIL) {
		if (obj->mode == 1 || (*InlineProc__38_s->assembly && obj->mode == 2)) {
			i = 0;
			while ((*InlineProc__38_s->inline)->name[__X(i, 32)] != 0x00) {
				name[__X(i, 32)] = (*InlineProc__38_s->inline)->name[__X(i, 32)];
				i += 1;
			}
			name[__X(i, 32)] = '.';
			i += 1;
			j = 0;
			while (obj->name[__X(j, 32)] != 0x00) {
				name[__X(i, 32)] = obj->name[__X(j, 32)];
				j += 1;
				i += 1;
			}
			name[__X(i, 32)] = 0x00;
			OPT_Insert(name, 32, &new);
			new->flag = 0x02;
			(*InlineProc__38_s->par)->link = new;
			*InlineProc__38_s->par = new;
			new->leaf = 0;
			new->mode = obj->mode;
			new->vis = 0;
			new->typ = obj->typ;
			obj->link2 = new;
			if (*InlineProc__38_s->assembly) {
				new->link2 = obj;
			}
		}
		CopyLocals__39(obj->left);
		CopyLocals__39(obj->right);
	}
}

static void OPP_InlineProc (OPT_Node *x, OPT_Node *apar, OPT_Object fpar)
{
	OPT_Object inline, par, list;
	OPT_Node glueCode, src, trg;
	BOOLEAN assembly;
	OPT_Const c;
	struct InlineProc__38 _s;
	_s.inline = &inline;
	_s.par = &par;
	_s.assembly = &assembly;
	_s.lnk = InlineProc__38_s;
	InlineProc__38_s = &_s;
	inline = (*x)->obj;
	assembly = __IN(7, inline->conval->setval, 32);
	if (!OPM_noerr) {
		if (assembly) {
			(*x)->class = 13;
			(*x)->typ = (*x)->obj->typ;
			(*x)->subcl = 2;
		}
		InlineProc__38_s = _s.lnk;
		return;
	}
	if (!__IN(1, inline->conval->setval, 32)) {
		OPP_err(129);
		InlineProc__38_s = _s.lnk;
		return;
	}
	if ((!assembly && inline->link2 != OPT_topScope)) {
		par = OPT_topScope->scope;
		if (par != NIL) {
			while (par->link != NIL) {
				par = par->link;
			}
			CopyLocals__39(inline->scope->right);
		} else {
			__NEW(list, OPT_ObjDesc);
			par = list;
			CopyLocals__39(inline->scope->right);
			if (OPT_topScope->scope != NIL) {
				OPT_topScope->scope = list->link;
			}
		}
		inline->link2 = OPT_topScope;
	}
	if (assembly) {
		OPB_Call(&*x, *apar, fpar);
		OPB_CopyAndSubst(&(*x)->left, inline->code);
		(*x)->subcl = 2;
	} else {
		*x = NIL;
		glueCode = NIL;
		c = OPT_NewConst();
		c->intval = OPM_errpos;
		while (fpar != NIL) {
			if (fpar->mode == 2) {
				fpar->link2 = (*apar)->obj;
				*apar = (*apar)->link;
			} else {
				src = *apar;
				*apar = (*apar)->link;
				src->link = NIL;
				trg = OPB_NewLeaf(fpar->link2);
				OPB_Assign(&trg, src);
				trg->conval = c;
				if (glueCode == NIL) {
					*x = trg;
				} else {
					glueCode->link = trg;
				}
				glueCode = trg;
			}
			fpar = fpar->link;
		}
		if (glueCode == NIL) {
			OPB_CopyAndSubst(&*x, inline->code);
		} else {
			OPB_CopyAndSubst(&glueCode->link, inline->code);
		}
	}
	InlineProc__38_s = _s.lnk;
}

static void OPP_Element (OPT_Node *x)
{
	OPT_Node y;
	OPP_Expression(&*x);
	if (OPP_sym == 21) {
		(*OPS_Get)(&OPP_sym);
		OPP_Expression(&y);
		if (!OPP_UndefFlag) {
			OPB_SetRange(&*x, y);
		}
	} else if (!OPP_UndefFlag) {
		OPB_SetElem(&*x);
	}
}

static void OPP_Sets (OPT_Node *x)
{
	OPT_Node y;
	if (OPP_sym != 24) {
		OPP_Element(&*x);
		for (;;) {
			if (OPP_sym == 19) {
				(*OPS_Get)(&OPP_sym);
			} else if ((30 <= OPP_sym && OPP_sym <= 40)) {
				OPP_err(19);
			} else {
				break;
			}
			OPP_Element(&y);
			if (!OPP_UndefFlag) {
				OPB_Op(6, &*x, y);
			}
		}
	} else {
		*x = OPB_EmptySet();
	}
	OPP_CheckSym(24);
}

static void OPP_Resolve (OPT_Object *obj, CHAR *name, ADDRESS name__len, OPT_Node *x, OPT_Node *y)
{
	__DUP(name, name__len, CHAR);
	*obj = OPT_Resolve((void*)name, name__len, &*x, &*y);
	OPT_MarkObj(*obj);
	__DEL(name);
}

static void OPP_OpCall (OPT_Object *op, OPT_Node *x, OPT_Node y)
{
	OPT_Object fpar;
	OPT_Node proc, apar, last, retlist, lastret;
	apar = NIL;
	last = NIL;
	retlist = NIL;
	lastret = NIL;
	if (*op != NIL) {
		proc = OPB_NewLeaf(*op);
		OPB_PrepCall(&proc, &fpar);
		if (((*x)->typ->form == 13 && (*op)->link->typ->comp == 4)) {
			OPB_DeRef(&*x);
		}
		OPB_Link(&apar, &last, *x);
		if (y != NIL) {
			OPB_Link(&apar, &last, y);
		}
		if (retlist != NIL) {
			lastret->link = apar;
			apar = retlist;
		}
		OPB_Call(&proc, apar, fpar);
		*x = proc;
	} else {
		OPP_err(137);
	}
}

static void OPP_Factor (OPT_Node *x)
{
	OPT_Object fpar, id;
	OPT_Node apar, y;
	OPS_Name name;

    id = NIL; //TODO

	if (OPP_sym < 30) {
		OPP_err(13);
		do {
			(*OPS_Get)(&OPP_sym);
		} while (!(OPP_sym >= 30));
	}
	if (OPP_sym == 40) {
		OPP_qualident(&id);
	}
	if ((id != NIL && id->prio != 127)) {
		*x = OPB_NewLeaf(id);
		OPP_selector(&*x);
		if (((*x)->class == 9 && (*x)->obj->mode == 8)) {
			if ((__STRCMP((*x)->obj->name, "SIZE") == 0 && !OPP_FixPhase)) {
				OPP_UndefFlag = 1;
			}
			OPP_StandProcCall(&*x);
		} else if (OPP_sym == 30) {
			OPP_UndefFlag = OPP_UndefFlag || (*x)->typ == NIL;
			(*OPS_Get)(&OPP_sym);
			if (OPP_UndefFlag) {
				OPP_ActualParameters(&apar, fpar);
			} else {
				OPB_PrepCall(&*x, &fpar);
				OPP_ActualParameters(&apar, fpar);
				if (((*x)->class == 9 && (*x)->obj->mode == 9)) {
					OPP_InlineProc(&*x, &apar, fpar);
				} else {
					OPB_Call(&*x, apar, fpar);
				}
			}
			OPP_CheckSym(22);
			if (OPP_level > 0) {
				OPT_topScope->link->leaf = 0;
			}
		}
	} else if ((id != NIL && id->prio == 127)) {
		(*OPS_Get)(&OPP_sym);
		OPP_Factor(&*x);
		OPP_Resolve(&id, name, 32, &*x, &y);
		OPP_OpCall(&id, &*x, NIL);
	} else if (OPP_sym == 35) {
		switch (OPS_numtyp) {
			case 1: 
				*x = OPB_NewIntConst(OPS_intval);
				(*x)->typ = OPT_chartyp;
				break;
			case 2: 
				*x = OPB_NewIntConst(OPS_intval);
				break;
			case 3: 
				*x = OPB_NewRealConst(OPS_realval, OPT_realtyp);
				break;
			case 4: 
				*x = OPB_NewRealConst(OPS_lrlval, OPT_lrltyp);
				break;
			default: __CASECHK;
		}
		(*OPS_Get)(&OPP_sym);
	} else if (OPP_sym == 37) {
		*x = OPB_BoolConst(1);
		(*OPS_Get)(&OPP_sym);
	} else if (OPP_sym == 38) {
		*x = OPB_BoolConst(0);
		(*OPS_Get)(&OPP_sym);
	} else if (OPP_sym == 39) {
		*x = OPB_NewString(OPS_str, OPS_intval);
		(*OPS_Get)(&OPP_sym);
	} else if (OPP_sym == 36) {
		*x = OPB_Nil();
		(*OPS_Get)(&OPP_sym);
	} else if (OPP_sym == 30) {
		(*OPS_Get)(&OPP_sym);
		OPP_Expression(&*x);
		OPP_CheckSym(22);
	} else if (OPP_sym == 31) {
		(*OPS_Get)(&OPP_sym);
		OPP_err(30);
		OPP_Expression(&*x);
		OPP_CheckSym(22);
	} else if (OPP_sym == 32) {
		(*OPS_Get)(&OPP_sym);
		OPP_Sets(&*x);
	} else if (OPP_sym == 33) {
		__MOVE(OPS_name, name, 32);
		(*OPS_Get)(&OPP_sym);
		y = NIL;
		id = NIL;
		OPP_Factor(&*x);
		if (!OPP_UndefFlag) {
			OPP_Resolve(&id, name, 32, &*x, &y);
			if (id == NIL) {
				OPB_MOp(33, &*x);
			} else {
				OPP_OpCall(&id, &*x, y);
			}
		}
	} else {
		OPP_err(13);
		(*OPS_Get)(&OPP_sym);
		*x = NIL;
	}
	if (*x == NIL) {
		*x = OPB_NewIntConst(1);
		(*x)->typ = OPT_undftyp;
	}
}

static void OPP_Term (OPT_Node *x)
{
	OPT_Node y;
	INT8 mulop;
	OPS_Name name;
	OPT_Object op;
	BOOLEAN b;
	b = OPP_UndefFlag;
	OPP_UndefFlag = 0;
	OPP_Factor(&*x);
	while ((1 <= OPP_sym && OPP_sym <= 5)) {
		op = NIL;
		mulop = OPP_sym;
		__MOVE(OPS_name, name, 32);
		(*OPS_Get)(&OPP_sym);
		OPP_Factor(&y);
		if (!OPP_UndefFlag) {
			OPP_Resolve(&op, name, 32, &*x, &y);
			if (op == NIL) {
				OPB_Op(mulop, &*x, y);
			} else {
				OPP_OpCall(&op, &*x, y);
			}
		}
	}
	OPP_UndefFlag = OPP_UndefFlag || b;
}

static void OPP_SimpleExpression (OPT_Node *x)
{
	OPT_Node y;
	INT8 addop;
	OPS_Name name;
	OPT_Object op;
	BOOLEAN b;
	b = OPP_UndefFlag;
	OPP_UndefFlag = 0;
	if (OPP_sym == 6 || OPP_sym == 7) {
		op = NIL;
		addop = OPP_sym;
		__MOVE(OPS_name, name, 32);
		(*OPS_Get)(&OPP_sym);
		OPP_Term(&*x);
		y = NIL;
		if (!OPP_UndefFlag) {
			OPP_Resolve(&op, name, 32, &*x, &y);
			if (op == NIL) {
				OPB_MOp(addop, &*x);
			} else {
				OPP_OpCall(&op, &*x, y);
			}
		}
	} else {
		OPP_Term(&*x);
	}
	while ((6 <= OPP_sym && OPP_sym <= 8)) {
		op = NIL;
		addop = OPP_sym;
		__MOVE(OPS_name, name, 32);
		(*OPS_Get)(&OPP_sym);
		OPP_Term(&y);
		if (!OPP_UndefFlag) {
			OPP_Resolve(&op, name, 32, &*x, &y);
			if (op == NIL) {
				OPB_Op(addop, &*x, y);
			} else {
				OPP_OpCall(&op, &*x, y);
			}
		}
	}
	OPP_UndefFlag = OPP_UndefFlag || b;
}

static void OPP_Expression (OPT_Node *x)
{
	OPT_Node y;
	OPT_Object obj;
	INT8 relation;
	OPS_Name name;
	OPP_SimpleExpression(&*x);
	if ((9 <= OPP_sym && OPP_sym <= 14)) {
		obj = NIL;
		relation = OPP_sym;
		__MOVE(OPS_name, name, 32);
		(*OPS_Get)(&OPP_sym);
		OPP_SimpleExpression(&y);
		if (!OPP_UndefFlag) {
			OPP_Resolve(&obj, name, 32, &*x, &y);
			if (obj == NIL) {
				OPB_Op(relation, &*x, y);
			} else {
				OPP_OpCall(&obj, &*x, y);
			}
		}
	} else if (OPP_sym == 15) {
		obj = NIL;
		__MOVE(OPS_name, name, 32);
		(*OPS_Get)(&OPP_sym);
		OPP_SimpleExpression(&y);
		if (!OPP_UndefFlag) {
			OPP_Resolve(&obj, name, 32, &*x, &y);
			if (obj == NIL) {
				OPB_In(&*x, y);
			} else {
				OPP_OpCall(&obj, &*x, y);
			}
		}
	} else if (OPP_sym == 16) {
		(*OPS_Get)(&OPP_sym);
		if (OPP_sym == 40) {
			OPP_qualident(&obj);
			if (!OPP_UndefFlag) {
				if (obj->mode == 5) {
					OPB_TypTest(&*x, obj, 0);
				} else {
					OPP_err(52);
				}
			} else {
				if (OPP_sym == 18) {
					OPP_err(0);
					(*OPS_Get)(&OPP_sym);
					OPP_CheckSym(40);
				}
			}
		} else {
			OPP_err(40);
		}
	}
}

static struct ProcedureDeclaration__53 {
	OPT_Node *x;
	OPT_Object *proc, *fwd;
	INT8 *sysflag, *mode, *prio;
	BOOLEAN *forward, *init, *redef;
	OPS_Name *selfname;
	OPT_Struct *selftype, *selfrec;
	INT8 *selfmode;
	struct ProcedureDeclaration__53 *lnk;
} *ProcedureDeclaration__53_s;

static void Body__54 (void);
static void GetParam__56 (void);
static void Receiver__58 (void);

static void GetParam__56 (void)
{
    *ProcedureDeclaration__53_s->sysflag = 0;
	(*ProcedureDeclaration__53_s->proc)->typ = OPT_notyp;
	(*ProcedureDeclaration__53_s->proc)->link = NIL;
	(*ProcedureDeclaration__53_s->proc)->sysflag = *ProcedureDeclaration__53_s->sysflag;
	if (*ProcedureDeclaration__53_s->mode == 13) {
		OPT_Insert(*ProcedureDeclaration__53_s->selfname, 32, &(*ProcedureDeclaration__53_s->proc)->link);
		(*ProcedureDeclaration__53_s->proc)->link->mode = *ProcedureDeclaration__53_s->selfmode;
		(*ProcedureDeclaration__53_s->proc)->link->typ = *ProcedureDeclaration__53_s->selftype;
	}
	if (OPP_sym == 30) {
		(*OPS_Get)(&OPP_sym);
		if (*ProcedureDeclaration__53_s->mode != 13) {
			OPP_FormalParameters(&(*ProcedureDeclaration__53_s->proc)->link, &(*ProcedureDeclaration__53_s->proc)->typ, *ProcedureDeclaration__53_s->sysflag);
		} else {
			OPP_FormalParameters(&(*ProcedureDeclaration__53_s->proc)->link->link, &(*ProcedureDeclaration__53_s->proc)->typ, *ProcedureDeclaration__53_s->sysflag);
		}
		if ((*ProcedureDeclaration__53_s->proc)->typ == NIL) {
			OPP_NewFix((void*)&OPP_ObjFix[__X(OPP_nofObjFix, 128)], OPP_ObjFixDesc__typ, OPS_name);
			OPP_ObjFix[__X(OPP_nofObjFix, 128)].obj = *ProcedureDeclaration__53_s->proc;
			OPP_nofObjFix += 1;
		}
		if ((*ProcedureDeclaration__53_s->proc)->typ == NIL || (*ProcedureDeclaration__53_s->proc)->typ->incomplete) {
			OPP_NewCheck(*ProcedureDeclaration__53_s->proc);
		}
	} else if (*ProcedureDeclaration__53_s->prio == 126) {
		OPP_err(30);
	}
	if (*ProcedureDeclaration__53_s->prio == 126) {
		if (__STRCMP((*ProcedureDeclaration__53_s->proc)->name, ":=") == 0) {
			if ((*ProcedureDeclaration__53_s->proc)->typ != OPT_notyp) {
				OPP_err(147);
			}
			if (((*ProcedureDeclaration__53_s->proc)->link != NIL && (*ProcedureDeclaration__53_s->proc)->link->mode != 2)) {
				OPP_err(148);
			}
		} else if ((*ProcedureDeclaration__53_s->proc)->typ == OPT_notyp) {
			OPP_err(141);
		}
		if (!*ProcedureDeclaration__53_s->forward) {
			OPT_Contextualize(&*ProcedureDeclaration__53_s->proc);
			(*ProcedureDeclaration__53_s->proc)->prio = 125;
			OPT_topScope->link = *ProcedureDeclaration__53_s->proc;
		} else {
			OPP_err(145);
		}
	}
	if ((*ProcedureDeclaration__53_s->fwd != NIL && *ProcedureDeclaration__53_s->prio < 126)) {
		if ((*ProcedureDeclaration__53_s->mode == 13 && *ProcedureDeclaration__53_s->redef)) {
			(*ProcedureDeclaration__53_s->proc)->flag |= __SETOF(1,32);
			OPB_CheckParameters((*ProcedureDeclaration__53_s->proc)->link->link, (*ProcedureDeclaration__53_s->fwd)->link->link, 0);
			if ((*ProcedureDeclaration__53_s->proc)->link->mode != (*ProcedureDeclaration__53_s->fwd)->link->mode) {
				OPP_err(115);
			}
		} else {
			OPB_CheckParameters((*ProcedureDeclaration__53_s->proc)->link, (*ProcedureDeclaration__53_s->fwd)->link, 1);
		}
		if ((*ProcedureDeclaration__53_s->proc)->typ != (*ProcedureDeclaration__53_s->fwd)->typ) {
			OPP_err(117);
		}
		if (!*ProcedureDeclaration__53_s->redef) {
			*ProcedureDeclaration__53_s->proc = *ProcedureDeclaration__53_s->fwd;
			OPT_topScope = (*ProcedureDeclaration__53_s->fwd)->scope;
		} else {
			(*ProcedureDeclaration__53_s->proc)->conval->setval |= __SETOF(2,32);
		}
	}
	if ((*ProcedureDeclaration__53_s->init && (*ProcedureDeclaration__53_s->proc)->typ != OPT_notyp)) {
		OPP_err(134);
	}
	if ((((*ProcedureDeclaration__53_s->init && OPT_topScope->left->link->mode == 11)) && (*ProcedureDeclaration__53_s->proc)->link != NIL)) {
		OPP_err(133);
	}
	if ((((__IN(21, OPM_parserOptions, 32) && (*ProcedureDeclaration__53_s->proc)->typ != NIL)) && (*ProcedureDeclaration__53_s->proc)->typ->form == 15)) {
		OPP_err(270);
	}
}

static void Body__54 (void)
{
	INT32 c, n;
	OPT_ConstExt ext;
	OPT_Node procdec, statseq;
	c = OPM_errpos;
	(*ProcedureDeclaration__53_s->proc)->conval->setval |= __SETOF(1,32);
	if (OPP_sym == 35) {
		if (!OPT_SYSimported) {
			OPP_err(135);
		}
		statseq = OPT_NewNode(30);
		statseq->conval = OPT_NewConst();
		procdec = NIL;
		n = 0;
		ext = OPT_NewExt();
		statseq->conval->ext = ext;
		OPB_Construct(29, &statseq, NIL);
		statseq->conval = OPT_NewConst();
		statseq->conval->intval = c;
		statseq->obj = *ProcedureDeclaration__53_s->proc;
		(*ProcedureDeclaration__53_s->proc)->conval->setval |= __SETOF(7,32);
		(*ProcedureDeclaration__53_s->proc)->conval->ext = ext;
		for (;;) {
			if (OPP_sym == 35) {
				n += 1;
				if ((OPS_intval < 0 || OPS_intval > 255) || n == 256) {
					OPP_err(63);
					OPS_intval = 1;
					n = 1;
				}
				(*ext)[__X(n, 256)] = (CHAR)OPS_intval;
				(*OPS_Get)(&OPP_sym);
			}
			if (OPP_sym == 19) {
				(*OPS_Get)(&OPP_sym);
			} else if (OPP_sym == 35) {
				OPP_err(19);
			} else {
				(*ext)[0] = (CHAR)n;
				break;
			}
		}
	} else {
		OPP_CheckSym(41);
		OPP_Block(&procdec, &statseq);
		if (OPP_sym == 35 || OPP_sym == 39) {
			__COPY(OPS_str, OPS_name, 32);
			OPP_sym = 40;
			(*ProcedureDeclaration__53_s->proc)->prio = *ProcedureDeclaration__53_s->prio;
		}
		if (OPP_sym == 40) {
			if (__STRCMP(OPS_name, (*ProcedureDeclaration__53_s->proc)->name) != 0) {
				OPP_err(4);
			}
			(*OPS_Get)(&OPP_sym);
		} else {
			OPP_err(40);
		}
	}
	if (*ProcedureDeclaration__53_s->mode == 9) {
		if ((!__IN(7, (*ProcedureDeclaration__53_s->proc)->conval->setval, 32) && ((*ProcedureDeclaration__53_s->proc)->typ != OPT_notyp || procdec != NIL))) {
			OPP_err(200);
		}
		(*ProcedureDeclaration__53_s->proc)->code = statseq;
		procdec = NIL;
	} else {
		OPB_Enter(&procdec, statseq, *ProcedureDeclaration__53_s->proc);
		procdec->conval = OPT_NewConst();
		procdec->conval->intval = c;
	}
	*ProcedureDeclaration__53_s->x = procdec;
}

static void Receiver__58 (void)
{
	OPT_Object obj;
	OPT_Struct rec;
	if (OPP_IsObjectScope()) {
		*ProcedureDeclaration__53_s->mode = 13;
		rec = OPT_topScope->link->typ;
		__ASSERT(rec->comp == 6, 0);
		if (rec->ptr != NIL) {
			__ASSERT(rec->ptr->form == 13, 0);
			*ProcedureDeclaration__53_s->selfmode = 1;
			__MOVE("@SELF", *ProcedureDeclaration__53_s->selfname, 6);
			*ProcedureDeclaration__53_s->selftype = rec->ptr;
			*ProcedureDeclaration__53_s->selfrec = rec;
		} else {
			*ProcedureDeclaration__53_s->selfmode = 2;
			__MOVE("@SELF", *ProcedureDeclaration__53_s->selfname, 6);
			*ProcedureDeclaration__53_s->selftype = rec;
			*ProcedureDeclaration__53_s->selfrec = rec;
		}
		if (__IN(21, OPM_parserOptions, 32)) {
			OPP_err(261);
		}
	} else if ((OPP_sym == 30 && __IN(19, OPM_parserOptions, 32))) {
		*ProcedureDeclaration__53_s->mode = 13;
		(*OPS_Get)(&OPP_sym);
		if (OPP_sym == 64) {
			*ProcedureDeclaration__53_s->selfmode = 2;
			(*OPS_Get)(&OPP_sym);
		} else {
			*ProcedureDeclaration__53_s->selfmode = 1;
		}
		__MOVE(OPS_name, *ProcedureDeclaration__53_s->selfname, 32);
		OPP_CheckSym(40);
		OPP_CheckSym(20);
		if (OPP_sym == 40) {
			OPT_Find(&obj);
			(*OPS_Get)(&OPP_sym);
			if (obj == NIL) {
				OPP_err(0);
				*ProcedureDeclaration__53_s->selftype = OPT_undftyp;
			} else if (obj->mode != 5) {
				OPP_err(72);
				*ProcedureDeclaration__53_s->selftype = OPT_undftyp;
			} else {
				*ProcedureDeclaration__53_s->selftype = obj->typ;
				*ProcedureDeclaration__53_s->selfrec = *ProcedureDeclaration__53_s->selftype;
				if ((*ProcedureDeclaration__53_s->selftype)->form == 13) {
					*ProcedureDeclaration__53_s->selfrec = (*ProcedureDeclaration__53_s->selfrec)->BaseTyp;
				}
				if (!((((*ProcedureDeclaration__53_s->selfmode == 1 && (*ProcedureDeclaration__53_s->selftype)->form == 13)) && (*ProcedureDeclaration__53_s->selfrec)->comp == 6) || (*ProcedureDeclaration__53_s->selfmode == 2 && (*ProcedureDeclaration__53_s->selftype)->comp == 6))) {
					OPP_err(70);
				}
				if ((*ProcedureDeclaration__53_s->selfrec != NIL && (*ProcedureDeclaration__53_s->selfrec)->mno != OPP_level)) {
					OPP_err(72);
				}
				if ((*ProcedureDeclaration__53_s->selfrec)->comp == 6) {
					OPT_topScope = (*ProcedureDeclaration__53_s->selfrec)->strobj->scope;
				}
			}
		} else {
			OPP_err(40);
		}
		OPP_CheckSym(22);
	}
}

static void OPP_ProcedureDeclaration (OPT_Node *x)
{
	OPT_Object proc, fwd;
	OPS_Name name;
	INT8 sysflag, mode, vis, prio;
	BOOLEAN forward, init;
	UINT32 flags;
	OPT_Object scope;
	BOOLEAN redef;
	OPS_Name selfname;
	OPT_Struct selftype, selfrec;
	INT8 selfmode;
	struct ProcedureDeclaration__53 _s;
	_s.x = x;
	_s.proc = &proc;
	_s.fwd = &fwd;
	_s.sysflag = &sysflag;
	_s.mode = &mode;
	_s.prio = &prio;
	_s.forward = &forward;
	_s.init = &init;
	_s.redef = &redef;
	_s.selfname = (void*)selfname;
	_s.selftype = &selftype;
	_s.selfrec = &selfrec;
	_s.selfmode = &selfmode;
	_s.lnk = ProcedureDeclaration__53_s;
	ProcedureDeclaration__53_s = &_s;
	forward = 0;
	scope = OPT_topScope;
	proc = NIL;
	*x = NIL;
	mode = 6;
	init = 0;
	flags = 0x0;
	prio = 0;
	if (OPP_sym == 17) {
		forward = 1;
		(*OPS_Get)(&OPP_sym);
	}
	Receiver__58();
	if ((((OPP_sym != 40 && OPP_sym != 39)) && OPP_sym != 35)) {
		if (OPP_sym == 31) {
			if (mode == 13) {
				OPP_CheckSysFlag(&sysflag, 0, 0x01);
			} else {
				OPP_CheckSysFlag(&sysflag, 0, 0x0d);
			}
		}
		if (OPP_sym == 1) {
			(*OPS_Get)(&OPP_sym);
		} else if (OPP_sym == 6) {
			if (mode == 13) {
				OPP_err(47);
			}
			mode = 10;
			if (!OPT_SYSimported) {
				OPP_err(135);
			}
			(*OPS_Get)(&OPP_sym);
		} else if (OPP_sym == 5) {
			init = 1;
			if (!OPP_IsObjectScope()) {
				OPP_err(253);
			}
			if ((OPT_topScope->link->link2 != NIL && OPT_topScope->link->link2->link->typ->strobj->scope == OPT_topScope)) {
				OPP_err(144);
			}
			if (OPT_topScope->link->typ->ptr == NIL) {
				OPP_err(249);
			}
			(*OPS_Get)(&OPP_sym);
		} else if (OPP_sym == 7) {
			if (mode == 13) {
				OPP_err(47);
			}
			mode = 9;
			(*OPS_Get)(&OPP_sym);
		} else if (sysflag == 0) {
			OPP_err(40);
		}
	}
	if (OPP_sym == 35 || OPP_sym == 39) {
		OPS_CheckOperator(&prio);
		if (prio == 126) {
			OPP_sym = 40;
			if (OPP_IsObjectScope()) {
				OPP_err(140);
			} else if ((!forward && __IN(8, OPT_topScope->conval->setval, 32))) {
				OPP_err(-212);
			}
		} else {
			OPP_err(142);
		}
	} else if (!OPP_IsObjectScope()) {
		OPT_topScope->conval->setval |= __SETOF(8,32);
	}
	if ((OPP_sym == 40 || OPP_sym == 35) || OPP_sym == 39) {
		OPT_Find(&fwd);
		__MOVE(OPS_name, name, 32);
		OPP_CheckMark(&vis, 1);
		if (init) {
			vis = 1;
		}
		if ((vis != 0 && mode == 6)) {
			mode = 7;
		}
		if ((fwd != NIL && (((!__IN(fwd->mode, 0x26c0, 32) || (fwd->mnolev >= 0 && fwd->mnolev != OPP_level)) || (mode == 13 && fwd->mode != 13)) || prio == 126))) {
			fwd = NIL;
		}
		redef = (((((((fwd != NIL && mode == 13)) && fwd->mode == 13)) && selfrec != fwd->link->typ)) && selfrec != fwd->link->typ->BaseTyp);
		if (fwd == NIL || redef) {
			if ((!__IN(19, OPM_parserOptions, 32) || mode != 13) || selftype != NIL) {
				OPT_Insert(name, 32, &proc);
			} else {
				proc = OPT_NewObj();
				__COPY(name, proc->name, 32);
			}
			if ((scope != OPT_topScope && selfrec->link == NIL)) {
				selfrec->link = OPT_topScope->right;
			}
			proc->prio = prio;
		} else {
			if (vis != fwd->vis) {
				OPP_err(118);
			}
			if (__IN(1, fwd->conval->setval, 32)) {
				OPP_err(1);
			}
			proc = OPT_NewObj();
			proc->leaf = 1;
		}
		proc->mode = mode;
		proc->vis = vis;
		proc->conval = OPT_NewConst();
		proc->conval->setval = flags;
		if ((((OPP_IsObjectScope() && selfrec->BaseTyp != NIL)) && selfrec->BaseTyp->incomplete)) {
			OPP_SetFlags(OPT_topScope->link, 0x80000000);
			proc->conval->intval = OPM_errpos;
		}
		if ((mode != 6 && OPP_level > 0)) {
			OPP_err(73);
		}
		if (init) {
			OPT_topScope->link->link2 = proc;
		}
		OPT_topScope = scope;
		OPP_level += 1;
		OPT_OpenScope(OPP_level, proc);
		OPT_topScope->adr = OPM_errpos;
		OPT_topScope->conval = OPT_NewConst();
		GetParam__56();
		if (!forward) {
			Body__54();
		}
		OPP_level -= 1;
		OPT_CloseScope();
	} else {
		OPP_err(40);
	}
	ProcedureDeclaration__53_s = _s.lnk;
}

static void OPP_CaseLabelList (OPT_Node *lab, INT16 LabelForm, INT16 *n, OPP_CaseTable tab)
{
	OPT_Node x, y, lastlab;
	INT16 i, f;
	INT32 xval, yval;
	*lab = NIL;
	lastlab = NIL;
	for (;;) {
		OPP_ConstExpression(&x);
		f = x->typ->form;
		if (__IN(f, 0x78, 32)) {
			xval = x->conval->intval;
		} else {
			OPP_err(61);
			xval = 1;
		}
		if (__IN(f, 0x70, 32)) {
			if (LabelForm < f) {
				OPP_err(60);
			}
		} else if (LabelForm != f) {
			OPP_err(60);
		}
		if (OPP_sym == 21) {
			(*OPS_Get)(&OPP_sym);
			OPP_ConstExpression(&y);
			yval = y->conval->intval;
			if (((INT16)y->typ->form != f && !((__IN(f, 0x70, 32) && __IN(y->typ->form, 0x70, 32))))) {
				OPP_err(60);
			}
			if (yval < xval) {
				OPP_err(63);
				yval = xval;
			}
		} else {
			yval = xval;
		}
		x->conval->intval2 = yval;
		i = *n;
		if (i < 128) {
			for (;;) {
				if (i == 0) {
					break;
				}
				if (tab[__X(i - 1, 128)].low <= yval) {
					if (tab[__X(i - 1, 128)].high >= xval) {
						OPP_err(62);
					}
					break;
				}
				tab[__X(i, 128)] = tab[__X(i - 1, 128)];
				i -= 1;
			}
			tab[__X(i, 128)].low = xval;
			tab[__X(i, 128)].high = yval;
			*n += 1;
		} else {
			OPP_err(213);
		}
		OPB_Link(&*lab, &lastlab, x);
		if (OPP_sym == 19) {
			(*OPS_Get)(&OPP_sym);
		} else if (OPP_sym == 35 || OPP_sym == 40) {
			OPP_err(19);
		} else {
			break;
		}
	}
}

static void OPP_CheckBool (OPT_Node *x)
{
	if (((*x)->class == 8 || (*x)->class == 9) || ((*x)->class == 2 && (*x)->obj->mode == 13)) {
		OPP_err(126);
		*x = OPB_NewBoolConst(0);
	} else if ((*x)->typ == NIL) {
		OPP_err(120);
		*x = OPB_NewBoolConst(0);
	} else if ((*x)->typ->form != 2) {
		OPP_err(120);
		*x = OPB_NewBoolConst(0);
	}
}

static void OPP_DoFixes (void)
{
	OPT_Object id, obj, typ, fpar, topscope, op;
	OPT_Node x, y, z, link, apar;
	OPT_Const conval;
	INT32 i;
	BOOLEAN sysflag, done;
	topscope = OPT_topScope;
	i = 0;
	do {
		i = 0;
		done = 0;
		while (i < OPP_nofObjFix) {
			if (OPP_ObjFix[__X(i, 128)].obj != NIL) {
				OPM_errpos = OPP_ObjFix[__X(i, 128)].pos;
				OPP_level = OPP_ObjFix[__X(i, 128)].level;
				OPT_FindInScope(OPP_ObjFix[__X(i, 128)].name, 32, OPP_ObjFix[__X(i, 128)].scope, &typ);
				if (typ != NIL) {
					OPP_ObjFix[__X(i, 128)].obj->mode = __ABS(OPP_ObjFix[__X(i, 128)].obj->mode);
					OPP_ObjFix[__X(i, 128)].obj->typ = typ->typ;
					OPP_ObjFix[__X(i, 128)].obj = NIL;
					done = 1;
				}
			}
			i += 1;
		}
	} while (!(!done));
	OPP_FixPhase = 1;
	i = 0;
	while (i < OPP_nofObjFix) {
		if (OPP_ObjFix[__X(i, 128)].obj != NIL) {
			OPM_Mark(0, OPP_ObjFix[__X(i, 128)].pos);
			OPP_ObjFix[__X(i, 128)].obj = NIL;
			OPP_ObjFix[__X(i, 128)].scope = NIL;
		}
		i += 1;
	}
	OPP_nofObjFix = 0;
	while (0 < OPP_nofTypFix) {
		OPP_nofTypFix -= 1;
		if (OPP_TypFix[__X(OPP_nofTypFix, 128)].typ != NIL) {
			OPM_errpos = OPP_TypFix[__X(OPP_nofTypFix, 128)].pos;
			OPP_level = OPP_TypFix[__X(OPP_nofObjFix, 128)].level;
			OPT_FindInScope(OPP_TypFix[__X(OPP_nofTypFix, 128)].name, 32, OPP_TypFix[__X(OPP_nofTypFix, 128)].scope, &typ);
			if (typ != NIL) {
				OPP_TypFix[__X(OPP_nofTypFix, 128)].typ->BaseTyp = typ->typ;
			} else if (OPP_TypFix[__X(OPP_nofTypFix, 128)].typ->comp == 6) {
				OPP_err(0);
				OPP_TypFix[__X(OPP_nofTypFix, 128)].typ->BaseTyp = NIL;
			} else {
				OPP_err(0);
				OPP_TypFix[__X(OPP_nofTypFix, 128)].typ->BaseTyp = OPT_undftyp;
			}
			OPP_TypFix[__X(OPP_nofTypFix, 128)].typ = NIL;
			OPP_TypFix[__X(OPP_nofTypFix, 128)].scope = NIL;
		}
	}
	i = 0;
	while (i < OPP_nofCheck) {
		if (OPP_ObjCheck[__X(i, 256)].obj != NIL) {
			OPP_level = OPP_ObjCheck[__X(i, 256)].level;
			OPP_ObjCheck[__X(i, 256)].obj->mode = __ABS(OPP_ObjCheck[__X(i, 256)].obj->mode);
			OPP_CheckObj(OPP_ObjCheck[__X(i, 256)].obj);
			OPP_ObjCheck[__X(i, 256)].obj = NIL;
		}
		i += 1;
	}
	while (OPP_FixList != NIL) {
		OPT_topScope = OPP_FixList->scope;
		OPP_level = OPP_FixList->level;
		OPS_StartPlaying(OPP_FixList->stream);
		x = OPP_FixList->node;
		(*OPS_Get)(&OPP_sym);
		link = x->link;
		x->link = NIL;
		conval = x->conval;
		x->conval = NIL;
		switch (OPP_FixList->mode) {
			case 1: 
				__NEW(y, OPT_NodeDesc);
				y = x->left;
				OPP_qualident(&id);
				z = OPB_NewLeaf(id);
				OPP_selector(&z);
				OPP_Resolve(&op, (CHAR*)":=", 3, &z, &y);
				if (op == NIL) {
					OPB_Assign(&z, y);
				} else {
					OPP_OpCall(&op, &z, y);
				}
				break;
			case 2: 
				__NEW(z, OPT_NodeDesc);
				__GUARDEQP(z, OPT_NodeDesc) = *x;
				OPP_Expression(&y);
				OPP_Resolve(&op, (CHAR*)":=", 3, &z, &y);
				if (op == NIL) {
					OPB_Assign(&z, y);
				} else {
					OPP_OpCall(&op, &z, y);
				}
				break;
			case 3: 
				OPP_qualident(&id);
				z = OPB_NewLeaf(id);
				OPP_selector(&z);
				if (OPP_sym == 34) {
					(*OPS_Get)(&OPP_sym);
					OPP_Expression(&y);
					OPP_Resolve(&op, (CHAR*)":=", 3, &z, &y);
					if (op == NIL) {
						OPB_Assign(&z, y);
					} else {
						OPP_OpCall(&op, &z, y);
					}
				} else {
					OPP_err(1002);
				}
				break;
			case 4: 
				OPP_qualident(&id);
				z = OPB_NewLeaf(id);
				OPP_selector(&z);
				if ((z->class == 9 && z->obj->mode == 8)) {
					OPP_StandProcCall(&z);
					if ((z != NIL && z->typ != OPT_notyp)) {
						OPP_err(55);
					}
				} else {
					OPB_PrepCall(&z, &fpar);
					if (OPP_sym == 30) {
						(*OPS_Get)(&OPP_sym);
						OPP_ActualParameters(&apar, fpar);
						OPP_CheckSym(22);
					} else {
						apar = NIL;
						if (fpar != NIL) {
							OPP_err(65);
						}
					}
					if (z->class == 9 || z->class == 29) {
						sysflag = z->obj->sysflag != 0;
					} else {
						sysflag = z->typ->sysflag != 0;
					}
					if ((z->class == 9 && z->obj->mode == 9)) {
						OPP_InlineProc(&z, &apar, fpar);
					} else {
						OPB_Call(&z, apar, fpar);
					}
					if (z->typ != OPT_notyp) {
						if (!sysflag) {
							OPP_err(55);
						} else {
							z->typ = OPT_notyp;
						}
					}
					if (OPP_level > 0) {
						OPT_topScope->link->leaf = 0;
					}
				}
				break;
			case 5: 
				OPP_Expression(&z);
				OPP_CheckBool(&z);
				conval = z->conval;
				break;
			case 6: 
				obj = x->obj;
				OPP_Expression(&z);
				OPB_Param(&z, obj);
				break;
			case 7: 
				(*OPS_Get)(&OPP_sym);
				(*OPS_Get)(&OPP_sym);
				OPP_Expression(&z);
				conval = z->conval;
				OPB_StPar0(&z, 64);
				break;
			case 9: 
				OPP_Expression(&z);
				OPB_Return(&z, OPT_topScope->link);
				break;
			default: __CASECHK;
		}
		if (z == NIL) {
			OPB_Construct(14, &z, NIL);
		}
		__GUARDEQP(x, OPT_NodeDesc) = *z;
		x->link = link;
		x->conval = conval;
		OPP_FixList = OPP_FixList->next;
	}
	OPT_topScope = topscope;
}

static struct StatSeq__67 {
	INT32 *pos;
	struct StatSeq__67 *lnk;
} *StatSeq__67_s;

static void CasePart__68 (OPT_Node *x);
static void SetPos__70 (OPT_Node x);

static void CasePart__68 (OPT_Node *x)
{
	INT16 n;
	INT32 low, high;
	BOOLEAN e;
	OPP_CaseTable tab;
	OPT_Node cases, lab, y, lastcase;
	OPP_FixPhase = 1;
	OPP_Expression(&*x);
	OPP_FixPhase = 0;
	*StatSeq__67_s->pos = OPM_errpos;
	if ((*x)->class == 8 || (*x)->class == 9) {
		OPP_err(126);
	} else if (!__IN((*x)->typ->form, 0x78, 32)) {
		OPP_err(125);
	}
	OPP_CheckSym(25);
	cases = NIL;
	lastcase = NIL;
	n = 0;
	for (;;) {
		if (OPP_sym < 42) {
			OPP_FixPhase = 1;
			OPP_CaseLabelList(&lab, (*x)->typ->form, &n, tab);
			OPP_FixPhase = 0;
			OPP_CheckSym(20);
			OPP_StatSeq(&y);
			OPB_Construct(17, &lab, y);
			OPB_Link(&cases, &lastcase, lab);
		}
		if (OPP_sym == 42) {
			(*OPS_Get)(&OPP_sym);
		} else {
			break;
		}
	}
	if (n > 0) {
		low = tab[0].low;
		high = tab[__X(n - 1, 128)].high;
		if (high - low > 512) {
			OPP_err(209);
		}
	} else {
		low = 1;
		high = 0;
		OPP_err(213);
	}
	e = OPP_sym == 44;
	if (e) {
		(*OPS_Get)(&OPP_sym);
		OPP_StatSeq(&y);
	} else {
		y = NIL;
	}
	OPB_Construct(16, &cases, y);
	OPB_Construct(21, &*x, cases);
	cases->conval = OPT_NewConst();
	cases->conval->intval = low;
	cases->conval->intval2 = high;
	if (e) {
		cases->conval->setval = 0x02;
	} else {
		cases->conval->setval = 0x0;
	}
}

static void SetPos__70 (OPT_Node x)
{
	x->conval = OPT_NewConst();
	x->conval->intval = *StatSeq__67_s->pos;
}

static void OPP_StatSeq (OPT_Node *stat)
{
	OPT_Object fpar, id, t, obj, owner, op;
	OPT_Struct typ, idtyp;
	BOOLEAN sysflag, e;
	OPT_Node x1, x2, s, x, y, z, apar, last, lastif;
	INT32 pos;
	OPS_Token ts;
	struct StatSeq__67 _s;
	_s.pos = &pos;
	_s.lnk = StatSeq__67_s;
	StatSeq__67_s = &_s;
	*stat = NIL;
	last = NIL;

    //TODO
    fpar = NIL, id = NIL, t = NIL, obj = NIL, owner = NIL, op = NIL;
	typ = NIL, idtyp = NIL;
	x1 = NIL, x2 = NIL, s = NIL, x = NIL, y = NIL, z = NIL, apar = NIL, last = NIL, lastif = NIL;
	ts = NIL;

	OPP_UndefFlag = 0;
	for (;;) {
		x = NIL;
		if (OPP_sym < 40) {
			OPP_err(14);
			do {
				(*OPS_Get)(&OPP_sym);
			} while (!(OPP_sym >= 40));
		}
		if (OPP_UndefFlag) {
			OPP_err(1001);
			OPP_UndefFlag = 0;
		}
		if (OPP_sym == 40) {
			OPS_StartRecording(OPP_sym);
			OPP_qualident(&id);
			x = OPB_NewLeaf(id);
			OPP_selector(&x);
			if (OPP_sym == 34) {
				(*OPS_Get)(&OPP_sym);
				if (OPP_UndefFlag) {
					OPP_UndefFlag = 0;
					x = NIL;
					OPP_Expression(&x);
					OPS_StopRecording(&ts);
					if (OPP_UndefFlag) {
						OPP_InsertFix(3, ts, x);
						OPP_UndefFlag = 0;
					} else {
						OPB_Construct(28, &x, NIL);
						OPP_InsertFix(1, ts, x);
					}
				} else {
					OPS_StartRecording(OPP_sym);
					OPP_Expression(&y);
					OPS_StopRecording(&ts);
					if (OPP_UndefFlag) {
						OPP_InsertFix(2, ts, x);
						OPP_UndefFlag = 0;
					} else {
						OPP_Resolve(&op, (CHAR*)":=", 3, &x, &y);
						if (op == NIL) {
							OPB_Assign(&x, y);
						} else {
							OPP_OpCall(&op, &x, y);
						}
					}
				}
			} else if (OPP_sym == 9) {
				OPP_err(34);
				(*OPS_Get)(&OPP_sym);
				OPP_Expression(&y);
				OPB_Assign(&x, y);
			} else if ((x->class == 9 && x->obj->mode == 8)) {
				OPP_StandProcCall(&x);
				OPS_StopRecording(&ts);
				if (OPP_UndefFlag) {
					OPP_UndefFlag = 0;
					OPP_InsertFix(4, ts, x);
				} else if ((x != NIL && x->typ != OPT_notyp)) {
					OPP_err(55);
				}
			} else {
				if (!OPP_UndefFlag) {
					OPB_PrepCall(&x, &fpar);
				}
				if (OPP_sym == 30) {
					(*OPS_Get)(&OPP_sym);
					OPP_ActualParameters(&apar, fpar);
					OPP_CheckSym(22);
				} else {
					apar = NIL;
					if ((fpar != NIL && !OPP_UndefFlag)) {
						OPP_err(65);
					}
				}
				if (!OPP_UndefFlag) {
					if (x->class == 9 || x->class == 29) {
						sysflag = x->obj->sysflag != 0;
					} else {
						sysflag = x->typ->sysflag != 0;
					}
					if ((x->class == 9 && x->obj->mode == 9)) {
						OPP_InlineProc(&x, &apar, fpar);
					} else {
						OPB_Call(&x, apar, fpar);
					}
					if ((x != NIL && x->typ != OPT_notyp)) {
						if (!sysflag) {
							OPP_err(55);
						} else {
							x->typ = OPT_notyp;
						}
					}
				}
				OPS_StopRecording(&ts);
				if (OPP_UndefFlag) {
					OPP_UndefFlag = 0;
					OPP_InsertFix(4, ts, x);
				}
				if (OPP_level > 0) {
					OPT_topScope->link->leaf = 0;
				}
			}
			pos = OPM_errpos;
		} else if (OPP_sym == 47) {
			(*OPS_Get)(&OPP_sym);
			OPS_StartRecording(OPP_sym);
			OPP_Expression(&x);
			OPS_StopRecording(&ts);
			if (OPP_UndefFlag) {
				OPP_InsertFix(5, ts, x);
				s = x;
				x->class = 0;
				OPP_UndefFlag = 0;
			} else {
				OPP_CheckBool(&x);
				s = NIL;
			}
			OPP_CheckSym(26);
			OPP_StatSeq(&y);
			OPB_Construct(15, &x, y);
			SetPos__70(x);
			lastif = x;
			while (OPP_sym == 45) {
				(*OPS_Get)(&OPP_sym);
				OPS_StartRecording(OPP_sym);
				OPP_Expression(&y);
				OPS_StopRecording(&ts);
				if (OPP_UndefFlag) {
					OPP_InsertFix(5, ts, y);
					s = x;
					x->class = 0;
					OPP_UndefFlag = 0;
				} else {
					OPP_CheckBool(&y);
				}
				OPP_CheckSym(26);
				OPP_StatSeq(&z);
				OPB_Construct(15, &y, z);
				SetPos__70(y);
				OPB_Link(&x, &lastif, y);
			}
			if (OPP_sym == 44) {
				(*OPS_Get)(&OPP_sym);
				OPP_StatSeq(&y);
			} else {
				y = NIL;
			}
			OPB_Construct(20, &x, y);
			OPP_CheckSym(43);
			if (s == NIL) {
				OPB_OptIf(&x);
			}
			pos = OPM_errpos;
		} else if (OPP_sym == 48) {
			(*OPS_Get)(&OPP_sym);
			CasePart__68(&x);
			OPP_CheckSym(43);
		} else if (OPP_sym == 49) {
			(*OPS_Get)(&OPP_sym);
			OPS_StartRecording(OPP_sym);
			OPP_Expression(&x);
			OPS_StopRecording(&ts);
			if (OPP_UndefFlag) {
				OPP_InsertFix(5, ts, x);
				OPP_UndefFlag = 0;
			} else {
				OPP_CheckBool(&x);
			}
			OPP_CheckSym(27);
			OPP_StatSeq(&y);
			OPP_CheckSym(43);
			if ((x->class == 7 && x->conval->intval == 0)) {
				x = NIL;
			} else {
				OPB_Construct(22, &x, y);
			}
		} else if (OPP_sym == 50) {
			(*OPS_Get)(&OPP_sym);
			OPP_StatSeq(&x);
			if (OPP_sym == 46) {
				(*OPS_Get)(&OPP_sym);
				pos = OPM_errpos;
				OPS_StartRecording(OPP_sym);
				OPP_Expression(&y);
				OPS_StopRecording(&ts);
				if (OPP_UndefFlag) {
					OPP_InsertFix(5, ts, y);
					OPP_UndefFlag = 0;
				} else {
					OPP_CheckBool(&y);
				}
			} else {
				OPP_err(46);
			}
			OPB_Construct(23, &x, y);
		} else if (OPP_sym == 51) {
			(*OPS_Get)(&OPP_sym);
			if (OPP_sym == 40) {
				OPP_FixPhase = 1;
				OPP_qualident(&id);
				x = OPB_NewLeaf(id);
				OPP_selector(&x);
				OPB_CopyAndSubst(&x1, x);
				OPB_CopyAndSubst(&x2, x);
				if (!__IN(x->typ->form, 0x70, 32)) {
					OPP_err(68);
				}
				OPP_CheckSym(34);
				OPP_FixPhase = 0;
				typ = x->typ;
				OPS_StartRecording(OPP_sym);
				OPP_Expression(&y);
				OPS_StopRecording(&ts);
				pos = OPM_errpos;
				if (OPP_UndefFlag) {
					OPP_InsertFix(2, ts, x);
					OPP_UndefFlag = 0;
				} else {
					OPB_Assign(&x, y);
				}
				SetPos__70(x);
				OPP_CheckSym(28);
				OPS_StartRecording(OPP_sym);
				OPP_Expression(&y);
				OPS_StopRecording(&ts);
				pos = OPM_errpos;
				if (y->class != 7 || OPP_UndefFlag) {
					owner = OPT_topScope;
					while ((OPT_topScope->left != NIL && OPT_topScope->link == OPT_topScope->left->link)) {
						OPT_topScope = OPT_topScope->left;
					}
					OPT_Insert((CHAR*)"@@", 3, &t);
					__MOVE("@for", t->name, 5);
					t->mode = 1;
					t->typ = typ;
					t->flag = 0x02;
					obj = OPT_topScope->scope;
					if (obj == NIL) {
						OPT_topScope->scope = t;
					} else {
						while (obj->link != NIL) {
							obj = obj->link;
						}
						obj->link = t;
					}
					OPT_topScope = owner;
					if ((t->mnolev == 0 && OPP_IsRecordScope())) {
						t->mnolev = 1;
					}
					z = OPB_NewLeaf(t);
					if (OPP_UndefFlag) {
						OPP_InsertFix(2, ts, z);
						OPP_UndefFlag = 0;
					} else {
						OPB_Assign(&z, y);
					}
					SetPos__70(z);
					OPB_Link(&*stat, &last, z);
					y = OPB_NewLeaf(t);
				} else if (y->typ->form < 4 || y->typ->form > typ->form) {
					OPP_err(113);
				}
				OPB_Link(&*stat, &last, x);
				if (OPP_sym == 29) {
					(*OPS_Get)(&OPP_sym);
					OPP_ConstExpression(&z);
				} else {
					z = OPB_NewIntConst(1);
				}
				pos = OPM_errpos;
				x = x1;
				if (z->conval->intval > 0) {
					OPB_Op(12, &x, y);
				} else if (z->conval->intval < 0) {
					OPB_Op(14, &x, y);
				} else {
					OPP_err(63);
					OPB_Op(14, &x, y);
				}
				OPP_CheckSym(27);
				OPP_StatSeq(&s);
				y = x2;
				OPB_StPar1(&y, z, 13);
				SetPos__70(y);
				if (s == NIL) {
					s = y;
				} else {
					z = s;
					while (z->link != NIL) {
						z = z->link;
					}
					z->link = y;
				}
				OPP_CheckSym(43);
				OPB_Construct(22, &x, s);
			} else {
				OPP_err(40);
			}
		} else if (OPP_sym == 52) {
			(*OPS_Get)(&OPP_sym);
			OPP_LoopLevel += 1;
			OPP_StatSeq(&x);
			OPP_LoopLevel -= 1;
			OPB_Construct(24, &x, NIL);
			OPP_CheckSym(43);
			pos = OPM_errpos;
		} else if (OPP_sym == 53) {
			(*OPS_Get)(&OPP_sym);
			idtyp = NIL;
			x = NIL;
			for (;;) {
				if (OPP_sym == 40) {
					OPP_qualident(&id);
					y = OPB_NewLeaf(id);
					//if ((((id != NIL && id->typ->form == 13)) && (id->mode == 2 || !id->leaf))) { //TODO
					//	OPP_err(-302);
					//}
					OPP_CheckSym(20);
					if (OPP_sym == 40) {
						OPP_qualident(&t);
						if (t->mode == 5) {
							if (id != NIL) {
								idtyp = id->typ;
								OPB_TypTest(&y, t, 0);
								if (id->mnolev < 0) {
									id->typ = t->typ;
								} else {
									owner = OPT_topScope->link;
									OPT_OpenScope(OPP_level, owner);
									OPT_Insert(id->name, 32, &obj);
									obj->mode = id->mode;
									obj->scope = id;
									obj->typ = t->typ;
								}
							} else {
								OPP_err(130);
							}
						} else {
							OPP_err(52);
						}
					} else {
						OPP_err(40);
					}
				} else {
					OPP_err(40);
				}
				pos = OPM_errpos;
				OPP_CheckSym(27);
				OPP_StatSeq(&s);
				OPB_Construct(15, &y, s);
				SetPos__70(y);
				if (id == NIL) {
					break;
				} else if (id->mnolev < 0) {
					id->typ = idtyp;
				} else {
					if (idtyp != NIL) {
						OPT_CloseScope();
						owner->scope = OPT_topScope;
						idtyp = NIL;
					}
				}
				if (x == NIL) {
					x = y;
					lastif = x;
				} else {
					OPB_Link(&x, &lastif, y);
				}
				if ((OPP_sym == 42 && __IN(19, OPM_parserOptions, 32))) {
					(*OPS_Get)(&OPP_sym);
				} else {
					break;
				}
			}
			e = OPP_sym == 44;
			if ((e && __IN(19, OPM_parserOptions, 32))) {
				(*OPS_Get)(&OPP_sym);
				OPP_StatSeq(&s);
			} else {
				s = NIL;
			}
			OPB_Construct(27, &x, s);
			OPP_CheckSym(43);
			if (e) {
				x->subcl = 1;
			}
		} else if (OPP_sym == 54) {
			(*OPS_Get)(&OPP_sym);
			if (OPP_LoopLevel == 0) {
				OPP_err(38);
			}
			OPB_Construct(25, &x, NIL);
			pos = OPM_errpos;
		} else if (OPP_sym == 55) {
			(*OPS_Get)(&OPP_sym);
			if (OPP_sym < 41) {
				OPS_StartRecording(OPP_sym);
				OPP_Expression(&x);
				OPS_StopRecording(&ts);
			}
			if (OPP_UndefFlag || OPT_topScope->link->typ == NIL) {
				OPP_InsertFix(9, ts, x);
				OPP_UndefFlag = 0;
			} else {
				if (OPP_level > 0) {
					OPB_Return(&x, OPT_topScope->link);
				} else {
					OPB_Return(&x, NIL);
				}
			}
			pos = OPM_errpos;
		} else if (OPP_sym == 60) {
			(*OPS_Get)(&OPP_sym);
			OPP_StatBlock(&x, 1);
		}
		if (OPP_UndefFlag) {
			OPP_err(1000);
			OPP_UndefFlag = 0;
		}
		if (x != NIL) {
			SetPos__70(x);
			OPB_Link(&*stat, &last, x);
		}
		if (OPP_sym == 41) {
			(*OPS_Get)(&OPP_sym);
		} else if (OPP_sym <= 40 || (47 <= OPP_sym && OPP_sym <= 55)) {
			OPP_err(41);
		} else {
			break;
		}
	}
	StatSeq__67_s = _s.lnk;
}

static void OPP_StatBlock (OPT_Node *statseq, BOOLEAN local)
{
	BOOLEAN lock, oldScopeLock;
	INT32 pos;
	OPT_Object owner;
	owner = OPT_topScope->link;
	pos = OPM_errpos;
	OPP_BlockMode(&owner->conval->setval, local, &lock);
	if ((OPP_scopeLock && lock)) {
		OPP_err(246);
	}
	oldScopeLock = OPP_scopeLock;
	OPP_scopeLock = OPP_scopeLock || lock;
	OPP_StatSeq(&*statseq);
	OPP_CheckSym(43);
	OPP_scopeLock = oldScopeLock;
	if (lock) {
		OPB_Lock(&*statseq, OPP_GetSelf(), 1);
		(*statseq)->conval = OPT_NewConst();
		(*statseq)->conval->intval = pos;
	}
}

static void OPP_AddTraceCode (OPT_Object owner, OPT_Node *statseq)
{
	OPT_Object curScope, obj, last;
	OPT_Node x;
	OPS_Name name;
	INT8 i, m;
	curScope = OPT_topScope;
	OPT_topScope = (OPT_Object)(OPT_modules->data)[0];
	__MOVE("trace", name, 6);
	i = 0;
	while ((i < 26 && owner->name[__X(i, 32)] != 0x00)) {
		name[__X(5 + i, 32)] = owner->name[__X(i, 32)];
		i += 1;
	}
	name[__X(5 + i, 32)] = 0x00;
	OPT_Insert(name, 32, &obj);
	obj->mode = 1;
	obj->typ = OPT_linttyp;
	last = OPT_topScope->scope;
	if (last != NIL) {
		while (last->link != NIL) {
			last = last->link;
		}
		last->link = obj;
	} else {
		OPT_topScope->scope = obj;
	}
	OPT_topScope = curScope;
	m = (INT8)((INT16)OPP_inc->adr);
	x = OPB_NewLeaf(obj);
	OPB_StPar0(&x, m);
	OPB_StFct(&x, m, 1);
	x->conval = OPT_NewConst();
	x->conval->intval = OPM_errpos;
	x->link = *statseq;
	*statseq = x;
}

static void OPP_Block (OPT_Node *procdec, OPT_Node *statseq)
{
	OPT_Struct typ;
	OPT_Object owner, obj, first, last, dmy;
	OPT_Node x, lastdec;
	INT32 pos;
	BOOLEAN vars, proc;
	first = NIL;
	last = NIL;
	*procdec = NIL;
	lastdec = NIL;
	proc = 0;
	vars = 0;
	for (;;) {
		if (OPP_sym == 62) {
			if ((__IN(21, OPM_parserOptions, 32) && proc)) {
				OPP_err(262);
			}
			(*OPS_Get)(&OPP_sym);
			while (OPP_sym == 40) {
				OPT_Insert(OPS_name, 32, &obj);
				OPP_CheckMark(&obj->vis, 0);
				if ((OPP_IsObjectScope() && obj->vis == 1)) {
					OPP_err(47);
				}
				obj->typ = OPT_sinttyp;
				obj->mode = 1;
				if (OPP_sym == 9) {
					(*OPS_Get)(&OPP_sym);
					OPP_ConstExpression(&x);
				} else if (OPP_sym == 34) {
					OPP_err(9);
					(*OPS_Get)(&OPP_sym);
					OPP_ConstExpression(&x);
				} else {
					OPP_err(9);
					x = OPB_NewIntConst(1);
				}
				obj->mode = 3;
				obj->typ = x->typ;
				obj->conval = x->conval;
				OPP_CheckSym(41);
				while (OPP_sym == 41) {
					(*OPS_Get)(&OPP_sym);
				}
			}
		}
		if (OPP_sym == 63) {
			if ((__IN(21, OPM_parserOptions, 32) && proc)) {
				OPP_err(262);
			}
			(*OPS_Get)(&OPP_sym);
			while (OPP_sym == 40) {
				OPT_Insert(OPS_name, 32, &obj);
				obj->mode = 5;
				obj->typ = OPT_undftyp;
				x = NIL;
				OPP_CheckMark(&obj->vis, 0);
				if (OPP_sym == 9) {
					(*OPS_Get)(&OPP_sym);
					OPP_TypeDecl(&obj->typ, &obj->typ, obj);
				} else if (OPP_sym == 34 || OPP_sym == 20) {
					OPP_err(9);
					(*OPS_Get)(&OPP_sym);
					OPP_TypeDecl(&obj->typ, &obj->typ, obj);
				} else {
					OPP_err(9);
				}
				if (obj->typ == OPT_ToBeFixed) {
					OPP_NewFix((void*)&OPP_ObjFix[__X(OPP_nofObjFix, 128)], OPP_ObjFixDesc__typ, OPS_name);
					OPP_ObjFix[__X(OPP_nofObjFix, 128)].obj = obj;
					OPP_nofObjFix += 1;
					obj->mode = -obj->mode;
				} else {
					OPP_NewType(obj);
				}
				if (obj->typ->incomplete) {
					OPP_NewCheck(obj);
				} else {
					OPP_CheckObj(obj);
				}
				if (((obj->typ->comp == 6 || (obj->typ->form == 13 && obj->typ->BaseTyp->comp == 6)) && OPP_sym == 40)) {
					if (__STRCMP(obj->name, OPS_name) != 0) {
						OPP_err(4);
					}
					(*OPS_Get)(&OPP_sym);
				}
				if (obj->typ->strobj == NIL) {
					obj->typ->strobj = obj;
				}
				if (obj->conval == NIL) {
					obj->conval = OPT_NewConst();
				}
				OPP_CheckSym(41);
			}
			if (OPT_topScope->scope != NIL) {
				first = OPT_topScope->scope;
				while (first->link != NIL) {
					first = first->link;
				}
				last = first;
				first = NIL;
			}
		}
		if (OPP_sym == 64 || (OPP_IsObjectScope() && OPP_sym == 40)) {
			vars = 1;
			if ((__IN(21, OPM_parserOptions, 32) && proc)) {
				OPP_err(262);
			}
			if (OPP_sym == 64) {
				(*OPS_Get)(&OPP_sym);
			}
			while (OPP_sym == 40) {
				for (;;) {
					if (OPP_sym == 40) {
						if (!OPP_IsObjectScope()) {
						} else if (OPT_topScope->link->typ->incomplete) {
							OPP_SetFlags(OPT_topScope->link, 0x80000000);
						} else {
							OPT_FindField((void*)OPS_name, 32, OPT_topScope->link->typ, &obj, 0);
							if ((obj != NIL && __IN(obj->mode, 0x2010, 32))) {
								OPP_err(1);
							}
						}
						OPT_Insert(OPS_name, 32, &obj);
						OPP_CheckMark(&obj->vis, 1);
						if (OPP_level == 0) {
							OPP_CheckSysFlag(&obj->sysflag, 0, 0x11);
						} else {
							OPP_CheckSysFlag(&obj->sysflag, 0, 0x01);
						}
						if (OPP_IsObjectScope()) {
							obj->mode = 4;
							obj->conval = OPT_NewConst();
							obj->conval->intval = OPM_errpos;
							OPT_FindField((void*)obj->name, 32, OPT_topScope->link->typ->BaseTyp, &dmy, 1);
						} else {
							obj->mode = 1;
							obj->leaf = obj->vis == 0;
						}
						obj->link = NIL;
						obj->typ = OPT_undftyp;
						obj->myscope = OPT_topScope;
						if (first == NIL) {
							first = obj;
						}
						if (last == NIL) {
							if (OPP_IsObjectScope()) {
								OPT_topScope->link->typ->link = obj;
							} else {
								OPT_topScope->scope = obj;
							}
						} else {
							last->link = obj;
						}
						last = obj;
					} else {
						OPP_err(40);
					}
					if (OPP_sym == 19) {
						(*OPS_Get)(&OPP_sym);
					} else if (OPP_sym == 40) {
						OPP_err(19);
					} else {
						break;
					}
				}
				OPP_CheckSym(20);
				OPP_TypeDecl(&typ, &OPT_notyp, NIL);
				if ((OPP_IsObjectScope() && OPT_topScope->link->typ == typ)) {
					OPP_err(58);
				}
				OPT_MarkType(typ);
				while (first != NIL) {
					first->typ = typ;
					if (typ->incomplete) {
						if (typ == OPT_ToBeFixed) {
							OPP_NewFix((void*)&OPP_ObjFix[__X(OPP_nofObjFix, 128)], OPP_ObjFixDesc__typ, OPS_name);
							OPP_ObjFix[__X(OPP_nofObjFix, 128)].obj = first;
							OPP_nofObjFix += 1;
						}
						OPP_NewCheck(first);
						first->mode = -first->mode;
					} else {
						OPP_CheckObj(first);
					}
					first = first->link;
				}
				if (!OPP_IsObjectScope() || OPP_sym != 43) {
					OPP_CheckSym(41);
				}
				while (OPP_sym == 41) {
					(*OPS_Get)(&OPP_sym);
				}
			}
		}
		if (OPP_sym == 65) {
			proc = 1;
			(*OPS_Get)(&OPP_sym);
			OPP_ProcedureDeclaration(&x);
			if (x != NIL) {
				if (lastdec == NIL) {
					*procdec = x;
				} else {
					lastdec->link = x;
				}
				lastdec = x;
			}
			OPP_CheckSym(41);
		}
		if (OPP_sym < 62 || OPP_sym > 65) {
			break;
		}
	}
	OPT_topScope->adr = OPM_errpos;
	if ((OPP_IsObjectScope() && last == NIL)) {
		OPT_topScope->link->typ->link = OPT_topScope->right;
	}
	OPP_CondNodes = NIL;
	OPP_CondCount = 0;
	owner = OPT_topScope->link;
	if (OPP_sym == 60) {
		if ((owner->mode == 9 && owner->vis != 0)) {
			OPP_err(250);
		}
		if (OPP_IsObjectScope()) {
			typ = owner->typ;
			if (typ->ptr == NIL) {
				OPP_err(249);
			}
			__ASSERT(typ != NIL, 0);
			if (typ->ptr != NIL) {
				OPT_Insert((CHAR*)"@SELF", 6, &obj);
				obj->mode = 1;
				obj->typ = typ->ptr;
			} else {
				OPT_Insert((CHAR*)"@SELF", 6, &obj);
				obj->mode = 2;
				obj->typ = typ;
			}
			obj->adr = OPM_errpos;
			obj->mnolev = 1;
			obj->link = NIL;
			owner->link = obj;
			if (owner->typ->link == NIL) {
				owner->typ->link = obj;
			}
		}
		(*OPS_Get)(&OPP_sym);
		OPP_StatBlock(&*statseq, 0);
		OPP_SetFlags(owner, 0x02);
		if ((__IN(22, OPM_codeOptions, 32) && OPP_level == 1)) {
			OPP_AddTraceCode(owner, &*statseq);
		}
		if ((OPP_CondNodes != NIL && !OPP_IsObjectScope())) {
			if (lastdec == NIL) {
				*procdec = OPP_CondNodes;
			} else {
				lastdec->link = OPP_CondNodes;
			}
			lastdec = OPP_CondNodes;
		}
	} else if (OPP_sym == 61) {
		if ((owner->mode == 9 && vars)) {
			OPP_err(247);
		}
		pos = OPM_errpos;
		OPP_SetFlags(owner, 0x80);
		OPA_Assemble(&*statseq, owner->vis != 0, owner->mode == 9);
		if (*statseq != NIL) {
			(*statseq)->conval = OPT_NewConst();
			(*statseq)->conval->intval = pos;
			(*statseq)->obj = owner;
		}
		(*OPS_Get)(&OPP_sym);
	} else {
		*statseq = NIL;
		OPP_CheckSym(43);
	}
	if ((((OPP_level == 0 && OPP_TDinit != NIL)) && OPP_IsModuleScope())) {
		OPP_lastTDinit->link = *statseq;
		*statseq = OPP_TDinit;
	}
	if ((((OPP_level == 0 && OPP_RecInit != NIL)) && OPP_IsModuleScope())) {
		OPP_lastRecInit->link = *procdec;
		*procdec = OPP_RecInit;
		OPP_RecInit = NIL;
	}
}

static struct CreateHiddenStructs__26 {
	struct CreateHiddenStructs__26 *lnk;
} *CreateHiddenStructs__26_s;

static void CreateStruct__27 (CHAR *name, ADDRESS name__len, OPT_Object *obj);

static void CreateStruct__27 (CHAR *name, ADDRESS name__len, OPT_Object *obj)
{
	OPT_Struct typ;
	__DUP(name, name__len, CHAR);
	typ = OPT_NewStr(15, 6);
	typ->BaseTyp = NIL;
	typ->sysflag = 6;
	OPT_Insert(name, name__len, &*obj);
	(*obj)->mode = 5;
	(*obj)->typ = typ;
	(*obj)->vis = 0;
	typ->strobj = *obj;
	(*obj)->flag |= __SETOF(1,32);
	(*obj)->conval = OPT_NewConst();
	__DEL(name);
}

static void OPP_CreateHiddenStructs (void)
{
	OPT_Object obj, fld1, fld2;
	struct CreateHiddenStructs__26 _s;
	_s.lnk = CreateHiddenStructs__26_s;
	CreateHiddenStructs__26_s = &_s;
	CreateStruct__27((CHAR*)"@delegate", 10, &obj);
	OPT_OpenScope(0, obj);
	OPT_Insert((CHAR*)"proc", 5, &fld1);
	fld1->mode = 4;
	fld1->typ = OPT_linttyp;
	obj->typ->link = fld1;
	fld1->flag |= __SETOF(1,32);
	OPT_Insert((CHAR*)"self", 5, &fld2);
	fld2->mode = 4;
	fld2->typ = OPT_ptrtyp;
	fld2->link = fld1;
	fld2->flag |= __SETOF(1,32);
	OPT_CloseScope();
	OPP_CheckObj(obj);
	CreateStruct__27((CHAR*)"@pointer", 9, &obj);
	OPT_OpenScope(0, obj);
	OPT_Insert((CHAR*)"ptr", 4, &fld1);
	fld1->mode = 4;
	fld1->typ = OPT_ptrtyp;
	obj->typ->link = fld1;
	fld1->flag |= __SETOF(1,32);
	OPT_CloseScope();
	OPP_CheckObj(obj);
	CreateHiddenStructs__26_s = _s.lnk;
}

static void OPP_FullName (OPS_Name fullname)
{
	INT32 i, j;
	i = 0;
	while (OPS_name[__X(i, 32)] != 0x00) {
		fullname[__X(i, 32)] = OPS_name[__X(i, 32)];
		i += 1;
	}
	(*OPS_Get)(&OPP_sym);
	while (OPP_sym == 18) {
		if (i < 31) {
			fullname[__X(i, 32)] = '.';
			i += 1;
		}
		(*OPS_Get)(&OPP_sym);
		if (OPP_sym == 40) {
			j = 0;
			while ((OPS_name[__X(j, 32)] != 0x00 && i < 31)) {
				fullname[__X(i, 32)] = OPS_name[__X(j, 32)];
				i += 1;
				j += 1;
			}
			if (OPS_name[__X(j, 32)] != 0x00) {
				OPP_err(240);
			}
			(*OPS_Get)(&OPP_sym);
		} else {
			OPP_err(40);
		}
	}
	fullname[__X(i, 32)] = 0x00;
}

void OPP_Module (OPT_Node *prog, OPS_Name modName)
{
	OPS_Name shortName, impName, aliasName;
	OPT_Node procdec, statseq;
	INT32 c;
	OPT_Object mod;
	OPP_ptrToRec = NIL;
	OPP_nofObjFix = 0;
	OPP_nofTypFix = 0;
	OPP_nofCheck = 0;
	OPP_UndefObj = OPT_NewObj();
	OPP_UndefObj->mode = 1;
	OPP_UndefObj->typ = OPT_undftyp;
	OPP_UndefObj->adr = 0;
	OPP_FixList = NIL;
	OPP_FixPhase = 0;
	OPP_UndefFlag = 0;
	OPP_FixLast = NIL;
	OPP_LoopLevel = 0;
	OPP_level = 0;
	OPP_scopeLock = 0;
	(*OPS_Get)(&OPP_sym);
	if (OPP_sym == 67) {
		(*OPS_Get)(&OPP_sym);
	} else {
		OPP_err(16);
	}
	if (OPP_sym == 40) {
		OPP_FullName(modName);
		if (__IN(24, OPM_parserOptions, 32)) {
			OPM_LogWLn();
			OPM_LogWStr((CHAR*)"M ", 3);
			OPM_LogWStr(OPS_name, 32);
		}
		__COPY(OPS_name, shortName, 32);
		OPT_Init(modName);
		mod = OPT_NewObj();
		mod->scope = OPT_topScope;
		OPT_topScope->link = mod;
		OPT_topScope->conval = OPT_NewConst();
		mod->mode = 11;
		mod->conval = OPT_NewConst();
		mod->typ = OPT_notyp;
		mod->conval->setval |= __SETOF(4,32);
		OPP_ExtObj = OPT_topScope;
		__COPY(modName, mod->name, 32);
		OPP_CheckSym(41);
		if (OPP_sym == 66) {
			(*OPS_Get)(&OPP_sym);
			for (;;) {
				if (OPP_sym == 40) {
					__COPY(OPS_name, aliasName, 32);
					__COPY(aliasName, impName, 32);
					(*OPS_Get)(&OPP_sym);
					if (OPP_sym == 34) {
						(*OPS_Get)(&OPP_sym);
						if (OPP_sym == 40) {
							OPP_FullName(impName);
						} else {
							OPP_err(40);
						}
					} else if (OPP_sym == 18) {
						OPP_err(200);
					}
					if ((__IN(8, OPM_parserOptions, 32) && __STRCMP(impName, "SYSTEM") == 0)) {
						OPP_err(152);
					} else {
						OPT_Import(aliasName, impName, modName);
					}
				} else {
					OPP_err(40);
				}
				if (OPP_sym == 19) {
					(*OPS_Get)(&OPP_sym);
				} else if (OPP_sym == 40) {
					OPP_err(19);
				} else {
					break;
				}
			}
			OPP_CheckSym(41);
		}
		if (OPM_noerr) {
			OPP_TDinit = NIL;
			OPP_lastTDinit = NIL;
			c = OPM_errpos;
			OPP_RecInit = NIL;
			OPP_lastRecInit = NIL;
			OPP_CreateHiddenStructs();
			OPP_Block(&procdec, &statseq);
			OPB_Enter(&procdec, statseq, NIL);
			*prog = procdec;
			(*prog)->conval = OPT_NewConst();
			(*prog)->conval->intval = c;
			if (OPP_sym == 40) {
				if (__STRCMP(OPS_name, shortName) != 0) {
					OPP_err(4);
				}
				(*OPS_Get)(&OPP_sym);
			} else {
				OPP_err(40);
			}
			if (OPP_sym != 18) {
				OPP_err(18);
			}
		}
	} else {
		OPP_err(40);
	}
	OPP_TDinit = NIL;
	OPP_lastTDinit = NIL;
	OPP_RecInit = NIL;
	OPP_lastRecInit = NIL;
	if (OPM_noerr) {
		OPP_DoFixes();
	} else {
		while (OPP_nofObjFix > 0) {
			OPP_nofObjFix -= 1;
			OPP_ObjFix[__X(OPP_nofObjFix, 128)].scope = NIL;
			OPP_ObjFix[__X(OPP_nofObjFix, 128)].obj = NIL;
		}
		while (OPP_nofTypFix > 0) {
			OPP_nofTypFix -= 1;
			OPP_TypFix[__X(OPP_nofTypFix, 128)].scope = NIL;
			OPP_TypFix[__X(OPP_nofTypFix, 128)].typ = NIL;
		}
		while (OPP_nofCheck > 0) {
			OPP_nofCheck -= 1;
			OPP_ObjCheck[__X(OPP_nofCheck, 256)].obj = NIL;
		}
	}
	if ((OPM_noerr && __IN(12, OPM_parserOptions, 32))) {
		OPT_TraverseObjects(OPT_topScope->right);
	}
}

static void EnumPtrs(void (*P)(void*))
{
	P(OPP_TDinit);
	P(OPP_lastTDinit);
	P(OPP_RecInit);
	P(OPP_lastRecInit);
	P(OPP_CondNodes);
	P(OPP_UndefObj);
	P(OPP_FixList);
	P(OPP_FixLast);
	P(OPP_ExtObj);
	P(OPP_inc);
	P(OPP_ptrToRec);
	__ENUMR(OPP_ObjFix, OPP_ObjFixDesc__typ, 48, 128, P);
	__ENUMR(OPP_ObjCheck, OPP__1__typ, 8, 256, P);
	__ENUMR(OPP_TypFix, OPP_StructFixDesc__typ, 48, 128, P);
}

__TDESC(OPP__2, 1, 0) = {__TDFLDS("", 8), {-4}};
__TDESC(OPP_FixDesc, 1, 4) = {__TDFLDS("FixDesc", 24), {4, 12, 16, 20, -20}};
__TDESC(OPP_TypeFix, 1, 1) = {__TDFLDS("TypeFix", 44), {36, -8}};
__TDESC(OPP_ObjFixDesc, 1, 2) = {__TDFLDS("ObjFixDesc", 48), {36, 44, -12}};
__TDESC(OPP_StructFixDesc, 1, 2) = {__TDFLDS("StructFixDesc", 48), {36, 44, -12}};
__TDESC(OPP__1, 1, 1) = {__TDFLDS("", 8), {0, -8}};

export void *OPP__init(void)
{
	__DEFMOD;
	__MODULE_IMPORT(OPA);
	__MODULE_IMPORT(OPB);
	__MODULE_IMPORT(OPM);
	__MODULE_IMPORT(OPS);
	__MODULE_IMPORT(OPT);
	__REGMOD("OPP", EnumPtrs);
	__INITYP(OPP__2, OPP__2, 0);
	__INITYP(OPP_FixDesc, OPP_FixDesc, 0);
	__INITYP(OPP_TypeFix, OPP_TypeFix, 0);
	__INITYP(OPP_ObjFixDesc, OPP_TypeFix, 1);
	__INITYP(OPP_StructFixDesc, OPP_TypeFix, 1);
	__INITYP(OPP__1, OPP__1, 0);
/* BEGIN */
	__MOVE("Oberon Parser (Active & X Extensions) / prk", OPP_SignOnMessage, 44);
	__MOVE("INC", OPS_name, 4);
	OPT_Find(&OPP_inc);
	__ENDMOD;
}
