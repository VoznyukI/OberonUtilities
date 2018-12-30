/* voc 2.1.0 [2017/09/06]. Bootstrapping compiler for address size 8, alignment 8. xtaSv */

#define SHORTINT INT8
#define INTEGER  INT16
#define LONGINT  INT32
#define SET      UINT32

#include "SYSTEM.h"
#include "Files.h"
#include "OPM.h"
#include "OPS.h"

typedef
	struct OPT_ConstDesc *OPT_Const;

typedef
	OPS_String *OPT_ConstExt;

typedef
	struct OPT_ConstDesc {
		OPT_ConstExt ext;
		INT32 intval, intval2;
		UINT32 setval;
		LONGREAL realval;
	} OPT_ConstDesc;

typedef
	struct OPT_ModDesc *OPT_Module;

typedef
	struct {
		ADDRESS len[1];
		OPT_Module data[1];
	} *OPT_ModArr;

typedef
	struct OPT_ObjDesc *OPT_Object;

typedef
	struct OPT_NodeDesc *OPT_Node;

typedef
	struct OPT_StrDesc *OPT_Struct;

typedef
	struct OPT_ObjDesc {
		OPT_Object left, right, link, scope, myscope, link2, old;
		INT8 prio, sysflag;
		OPT_Node code;
		OPS_Name name;
		BOOLEAN leaf;
		INT8 mode, mnolev, vis;
		OPT_Struct typ;
		OPT_Const conval;
		INT32 adr, linkadr;
		OPT_Object nxtobj, sibling;
		BOOLEAN par, inited, used;
		INT32 fp;
		INT8 history;
		INT32 txtpos;
		UINT32 flag;
	} OPT_ObjDesc;

typedef
	struct {
		ADDRESS len[1];
		OPT_Struct data[1];
	} *OPT_StructArr;

typedef
	struct OPT_ModDesc { /* OPT_ObjDesc */
		OPT_Object left, right, link, scope, myscope, link2, old;
		INT8 prio, sysflag;
		OPT_Node code;
		OPS_Name name;
		BOOLEAN leaf;
		INT8 mode, mnolev, vis;
		OPT_Struct typ;
		OPT_Const conval;
		INT32 adr, linkadr;
		OPT_Object nxtobj, sibling;
		BOOLEAN par, inited, used;
		INT32 fp;
		INT8 history;
		INT32 txtpos;
		UINT32 flag;
		OPT_Object publics;
		BOOLEAN directImp;
		INT16 nofimp;
		OPT_ModArr import_;
		INT16 nofstr;
		OPT_StructArr struct_;
		INT16 nofreimp;
		OPT_StructArr reimp;
	} OPT_ModDesc;

typedef
	struct OPT_NodeDesc {
		OPT_Node left, right, link;
		INT8 class, subcl;
		BOOLEAN readonly;
		OPT_Struct typ;
		OPT_Object obj;
		OPT_Const conval;
		BOOLEAN global;
		OPT_Node up, down;
		INT32 ref;
		INT8 flag, subflg;
	} OPT_NodeDesc;

typedef
	struct OPT_StrDesc {
		INT8 form, comp, mno, extlev;
		INT16 ref;
		INT8 align, sysflag;
		INT32 rectest, n, size, tdadr, offset, txtpos, txtpos2;
		OPT_Struct BaseTyp;
		OPT_Object link, strobj;
		INT16 fpdone, sref, oref;
		BOOLEAN pvused, pbused;
		INT32 fp, pvfp, pbfp;
		BOOLEAN incomplete;
		OPT_Struct ptr;
	} OPT_StrDesc;


export OPT_Object OPT_topScope, OPT_objects;
export OPT_Struct OPT_undftyp, OPT_bytetyp, OPT_booltyp, OPT_chartyp, OPT_sinttyp, OPT_inttyp, OPT_linttyp, OPT_hinttyp, OPT_realtyp, OPT_lrltyp, OPT_settyp, OPT_stringtyp, OPT_niltyp, OPT_notyp, OPT_ptrtyp;
export BOOLEAN OPT_SYSimported;
export INT8 OPT_nofmod;
export OPT_ModArr OPT_modules;
static INT8 OPT_nofemod;
static OPT_ModArr OPT_emodules;
export INT16 OPT_modNo;
static OPT_Object OPT_universe, OPT_syslink;
static INT8 OPT_strucForm[52];
static INT8 OPT_strucComp[52];
static OPT_Struct OPT_predefStruct[15];
static INT8 OPT_strucFormSF[16];
static INT8 OPT_strucCompSF[16];
static BOOLEAN OPT_export;
static OPT_Object OPT_exp[16];
static INT16 OPT_nofstruc;
static BOOLEAN OPT_newSF, OPT_extSF, OPT_symNew, OPT_symExtended, OPT_sfpresent, OPT_impSelf, OPT_expGlobal;
export void (*OPT_typSize)(OPT_Struct, BOOLEAN);
export OPT_Struct OPT_ToBeFixed;

export ADDRESS *OPT_ConstDesc__typ;
export ADDRESS *OPT_ObjDesc__typ;
export ADDRESS *OPT_ModDesc__typ;
export ADDRESS *OPT_StrDesc__typ;
export ADDRESS *OPT_NodeDesc__typ;

export void OPT_Close (void);
export void OPT_CloseScope (void);
static void OPT_CompOldSym (OPT_Object obj);
static INT8 OPT_CompOldTyp (OPT_Struct typ, OPT_Struct oldtyp);
export void OPT_Contextualize (OPT_Object *sentinel);
static void OPT_CopyOp (OPT_Object *new, OPT_Object *obj);
static void OPT_Distance (OPT_Struct typ, OPT_Struct otyp, INT8 *distance);
static void OPT_DoubleModArr (OPT_ModArr *x);
static void OPT_DoubleStructArr (OPT_StructArr *x);
static void OPT_EnterIntConst (CHAR *name, ADDRESS name__len, INT32 value);
static void OPT_EnterProc (CHAR *name, ADDRESS name__len, INT16 num);
static void OPT_EnterPtr (CHAR *name, ADDRESS name__len, INT32 num);
static void OPT_EnterTyp (CHAR *name, ADDRESS name__len, INT8 form, INT16 size, OPT_Struct *res, INT8 sref);
static void OPT_EnterTypAlias (CHAR *name, ADDRESS name__len, OPT_Struct typ);
static void OPT_Enumerate (OPT_Object obj);
export void OPT_Export (OPS_Name modName, BOOLEAN *newsf, BOOLEAN *extsf);
static void OPT_FPrintErr (OPT_Object obj);
static void OPT_FPrintMeth (INT32 *pbfp, INT32 *pvfp, OPT_Object fld);
static void OPT_FPrintName (INT32 *fp, CHAR *name, ADDRESS name__len);
export void OPT_FPrintObj (OPT_Object obj);
static void OPT_FPrintRecord (OPT_Struct typ);
static void OPT_FPrintSign (INT32 *fp, OPT_Struct result, OPT_Object par);
export void OPT_FPrintTyp (OPT_Struct typ);
static void OPT_FPrintTyp0 (OPT_Struct typ);
export void OPT_Find (OPT_Object *res);
export void OPT_FindField (CHAR *name, ADDRESS name__len, OPT_Struct typ, OPT_Object *res, BOOLEAN mark);
export void OPT_FindImport (OPT_Object mod, OPT_Object *res);
export void OPT_FindInScope (CHAR *name, ADDRESS name__len, OPT_Object scope, OPT_Object *res);
static void OPT_Imp (OPS_Name impName, OPS_Name modName, OPT_Module *M);
export void OPT_Import (OPS_Name aliasName, OPS_Name impName, OPS_Name selfName);
export void OPT_Init (OPS_Name name);
static void OPT_InitStruct (OPT_Struct *typ, INT8 form, INT8 sref);
export void OPT_Insert (CHAR *name, ADDRESS name__len, OPT_Object *obj);
static void OPT_InsertImport (OPT_Object obj, OPT_Object root);
static BOOLEAN OPT_IsExtern (OPT_Object obj);
export void OPT_MarkObj (OPT_Object obj);
export void OPT_MarkType (OPT_Struct typ);
static OPT_Object OPT_MatchOp (OPT_Object op, OPT_Object list);
export OPT_Const OPT_NewConst (void);
export OPT_ConstExt OPT_NewExt (void);
static OPT_Module OPT_NewMod (void);
export OPT_Node OPT_NewNode (INT8 class);
export OPT_Object OPT_NewObj (void);
export OPT_Struct OPT_NewStr (INT8 form, INT8 comp);
export void OPT_OpenScope (INT8 level, OPT_Object owner);
static void OPT_OutCProc (OPT_Node n);
static void OPT_OutConst (INT8 form, OPT_Const conval);
static void OPT_OutFld (OPT_Object fld);
export void OPT_OutMod (OPT_Module mod);
static void OPT_OutObj (OPT_Object obj);
static void OPT_OutParList (OPT_Object par);
static void OPT_OutRecord (OPT_Struct typ);
export void OPT_OutScope (OPT_Object scope, BOOLEAN public);
static void OPT_OutStruct (OPT_Struct typ);
export void OPT_QualResolve (OPT_Object *obj, OPT_Node *x, OPT_Node *y, INT8 *distance, BOOLEAN *wrn);
static void OPT_ReadString (OFS_Rider *R, ADDRESS *R__typ, CHAR *string, ADDRESS string__len);
export OPT_Object OPT_Resolve (CHAR *name, ADDRESS name__len, OPT_Node *x, OPT_Node *y);
export void OPT_TraverseObjects (OPT_Object top);
static void OPT_err (INT16 n);


static void OPT_err (INT16 n)
{
	OPM_err(n);
}

void OPT_Close (void)
{
	INT16 i;
	OPT_topScope = NIL;
	OPT_objects = NIL;
	i = 0;
	while (i < OPT_modules->len[0]) {
		(OPT_modules->data)[__X(i, OPT_modules->len[0])] = NIL;
		i += 1;
	}
	i = 0;
	while (i < OPT_emodules->len[0]) {
		(OPT_emodules->data)[__X(i, OPT_emodules->len[0])] = NIL;
		i += 1;
	}
	i = 0;
	while (i < 15) {
		OPT_exp[__X(i, 16)] = NIL;
		i += 1;
	}
	OPT_nofmod = 0;
	OPT_nofemod = 0;
}

static OPT_Module OPT_NewMod (void)
{
	OPT_Module M;
	__NEW(M, OPT_ModDesc);
	M->struct_ = __NEWARR(POINTER__typ, 4, 4, 1, 1, 32);
	M->reimp = __NEWARR(POINTER__typ, 4, 4, 1, 1, 32);
	M->import_ = __NEWARR(POINTER__typ, 4, 4, 1, 1, 64);
	return M;
}

OPT_Const OPT_NewConst (void)
{
	OPT_Const const_;
	__NEW(const_, OPT_ConstDesc);
	return const_;
}

OPT_Object OPT_NewObj (void)
{
	OPT_Object obj;
	__NEW(obj, OPT_ObjDesc);
	obj->txtpos = OPM_errpos;
	return obj;
}

OPT_Struct OPT_NewStr (INT8 form, INT8 comp)
{
	OPT_Struct typ;
	__NEW(typ, OPT_StrDesc);
	typ->form = form;
	typ->comp = comp;
	typ->tdadr = -1;
	typ->offset = -1;
	typ->txtpos = OPM_errpos;
	typ->size = -1;
	typ->BaseTyp = OPT_undftyp;
	return typ;
}

OPT_Node OPT_NewNode (INT8 class)
{
	OPT_Node node;
	__NEW(node, OPT_NodeDesc);
	node->class = class;
	return node;
}

OPT_ConstExt OPT_NewExt (void)
{
	OPT_ConstExt ext;
	ext = __NEWARR(NIL, 1, 1, 1, 0, 256);
	return ext;
}

static void OPT_DoubleStructArr (OPT_StructArr *x)
{
	INT32 i;
	OPT_StructArr h;
	i = (*x)->len[0];
	h = *x;
	*x = __NEWARR(POINTER__typ, 4, 4, 1, 1, ((ADDRESS)((__ASHL(i, 1)))));
	__ASSERT(*x != NIL, 0);
	__MOVE((ADDRESS)&(h->data)[0], (ADDRESS)&((*x)->data)[0], __ASHL(i, 2));
}

static void OPT_DoubleModArr (OPT_ModArr *x)
{
	INT32 i;
	OPT_ModArr h;
	i = (*x)->len[0];
	h = *x;
	*x = __NEWARR(POINTER__typ, 4, 4, 1, 1, ((ADDRESS)((__ASHL(i, 1)))));
	__ASSERT(*x != NIL, 0);
	__MOVE((ADDRESS)&(h->data)[0], (ADDRESS)&((*x)->data)[0], __ASHL(i, 2));
}

void OPT_MarkObj (OPT_Object obj)
{
	if (obj != NIL) {
		obj->used = 1;
		if (obj->mnolev < 0) {
			(OPT_modules->data)[__X(-obj->mnolev, OPT_modules->len[0])]->used = 1;
		}
	}
}

void OPT_MarkType (OPT_Struct typ)
{
	typ->pvused = 1;
	OPT_MarkObj(typ->strobj);
}

void OPT_TraverseObjects (OPT_Object top)
{
	UINT32 flag;
	OPT_Struct type;
	if (top != NIL) {
		OPT_TraverseObjects(top->left);
		if ((((__IN(top->mode, 0x2a7e, 32) && top->vis == 0)) && __STRCMP(top->name, "@SELF") != 0)) {
			flag = (top->flag & 0x0a);
			if (flag == 0x08) {
				OPM_Mark(-913, top->txtpos);
			} else if (flag == 0x0) {
				OPM_Mark(-900, top->txtpos);
			}
		}
		if (__IN(top->mode, 0x20c0, 32)) {
			OPT_TraverseObjects(top->scope->right);
		}
		type = top->typ;
		while (type->form == 13 || type->comp == 2) {
			type = type->BaseTyp;
		}
		if ((((type->comp == 6 && type->mno == 0)) && type->rectest != 2147483647)) {
			type->rectest = 2147483647;
			OPT_TraverseObjects(type->link);
		}
		OPT_TraverseObjects(top->right);
	}
}

void OPT_FindImport (OPT_Object mod, OPT_Object *res)
{
	OPT_Object obj;
	obj = mod->scope;
	for (;;) {
		if (obj == NIL) {
			break;
		}
		if (__STRCMP(OPS_name, obj->name) < 0) {
			obj = obj->left;
		} else if (__STRCMP(OPS_name, obj->name) > 0) {
			obj = obj->right;
		} else {
			if ((obj->mode == 5 && obj->vis == 0)) {
				obj = NIL;
			} else {
				OPT_MarkObj(obj);
			}
			break;
		}
	}
	*res = obj;
}

void OPT_FindField (CHAR *name, ADDRESS name__len, OPT_Struct typ, OPT_Object *res, BOOLEAN mark)
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
		if ((((((*res != NIL && (*res)->mode == 13)) && (*res)->mnolev < 0)) && (*res)->vis == 0)) {
			*res = NIL;
		}
		if (*res == NIL) {
			if ((((((typ->BaseTyp != NIL && typ->BaseTyp != OPT_ToBeFixed)) && typ->BaseTyp->strobj->vis == 0)) && mark)) {
				OPT_MarkObj(typ->strobj);
			}
			typ = typ->BaseTyp;
		}
	}
	if (*res == NIL) {
		return;
	}
	if (mark) {
		(*res)->used = 1;
		OPT_MarkObj(typ->strobj);
		typ->pbused = 1;
	}
}

void OPT_FindInScope (CHAR *name, ADDRESS name__len, OPT_Object scope, OPT_Object *res)
{
	OPT_Object obj, head;
	BOOLEAN inRec;
	__DUP(name, name__len, CHAR);
	head = scope;
	inRec = 0;
	for (;;) {
		if ((head->link != NIL && head->link->mode == 5)) {
			OPT_FindField((void*)name, name__len, head->link->typ, &obj, 1);
			if ((((inRec && obj != NIL)) && !__IN(obj->mode, 0x28, 32))) {
				OPT_err(200);
			}
			inRec = 1;
			if (obj != NIL || head->link->typ->incomplete) {
				break;
			}
		} else {
			obj = head->right;
			for (;;) {
				if (obj == NIL) {
					break;
				}
				if (__STRCMP(name, obj->name) < 0) {
					obj = obj->left;
				} else if (__STRCMP(name, obj->name) > 0) {
					obj = obj->right;
				} else {
					if ((((((inRec && head->link != NIL)) && head->link->mode != 11)) && !__IN(obj->mode, 0x28, 32))) {
						OPT_err(200);
					}
					obj->flag |= __SETOF(1,32);
					break;
				}
			}
			if (obj != NIL) {
				break;
			}
		}
		head = head->left;
		if (head == NIL) {
			break;
		}
	}
	if ((obj != NIL && obj->mode < 0)) {
		obj = NIL;
	}
	*res = obj;
	__DEL(name);
}

void OPT_Find (OPT_Object *res)
{
	OPT_FindInScope(OPS_name, 32, OPT_topScope, &*res);
}

void OPT_Insert (CHAR *name, ADDRESS name__len, OPT_Object *obj)
{
	OPT_Object ob0, ob1;
	BOOLEAN left;
	__DUP(name, name__len, CHAR);
	ob0 = OPT_topScope;
	ob1 = ob0->right;
	left = 0;
	for (;;) {
		if (ob1 != NIL) {
			if (__STRCMP(name, ob1->name) < 0) {
				ob0 = ob1;
				ob1 = ob0->left;
				left = 1;
			} else if (__STRCMP(name, ob1->name) > 0) {
				ob0 = ob1;
				ob1 = ob0->right;
				left = 0;
			} else {
				if (ob1->prio < 126) {
					OPT_err(1);
					ob0 = ob1;
					ob1 = ob0->right;
				} else {
					break;
				}
			}
		} else {
			ob1 = OPT_NewObj();
			ob1->leaf = 1;
			if (left) {
				ob0->left = ob1;
			} else {
				ob0->right = ob1;
			}
			ob1->left = NIL;
			ob1->right = NIL;
			__COPY(name, ob1->name, 32);
			ob1->mnolev = OPT_topScope->mnolev;
			break;
		}
	}
	*obj = ob1;
	__DEL(name);
}

static void OPT_CopyOp (OPT_Object *new, OPT_Object *obj)
{
	(*new)->link = (*obj)->link;
	(*new)->scope = (*obj)->scope;
	(*new)->prio = (*obj)->prio;
	(*new)->code = (*obj)->code;
	__MOVE((*obj)->name, (*new)->name, 32);
	(*new)->leaf = (*obj)->leaf;
	(*new)->mode = (*obj)->mode;
	(*new)->mnolev = (*obj)->mnolev;
	(*new)->vis = (*obj)->vis;
	(*new)->typ = (*obj)->typ;
	(*new)->conval = (*obj)->conval;
}

static BOOLEAN OPT_IsExtern (OPT_Object obj)
{
	OPT_Object res;
	if (obj->typ->strobj != NIL) {
		OPT_FindInScope(obj->typ->strobj->name, 32, OPT_topScope, &res);
		OPT_FindInScope(obj->typ->strobj->name, 32, OPT_universe, &obj);
	}
	return (res != NIL && res == obj);
}

static struct Contextualize__5 {
	struct Contextualize__5 *lnk;
} *Contextualize__5_s;

static BOOLEAN eqptyp__6 (OPT_Struct t1, OPT_Struct t2);

static BOOLEAN eqptyp__6 (OPT_Struct t1, OPT_Struct t2)
{
	if (t1 == t2) {
		return 1;
	} else if ((t1->comp == 4 && t2->comp == 4)) {
		while ((t1->comp == 4 && t2->comp == 4)) {
			t1 = t1->BaseTyp;
			t2 = t2->BaseTyp;
		}
		return t1 == t2;
	} else {
		return 0;
	}
	__RETCHK;
}

void OPT_Contextualize (OPT_Object *sentinel)
{
	OPT_Object new, t1, t2, aop, fp, scope;
	struct Contextualize__5 _s;
	_s.lnk = Contextualize__5_s;
	Contextualize__5_s = &_s;
	new = OPT_NewObj();
	t1 = (*sentinel)->link;
	if (t1 == NIL) {
		OPT_err(143);
	} else {
		t2 = t1->link;
		if ((t2 == NIL && !OPS_CheckCardinality((*sentinel)->name, 1))) {
			OPT_err(143);
		} else if (t2 != NIL) {
			if (!OPS_CheckCardinality((*sentinel)->name, 2) || t2->link != NIL) {
				OPT_err(143);
			} else if ((OPT_IsExtern(t1) && OPT_IsExtern(t2))) {
				OPT_err(146);
			}
		} else if (OPT_IsExtern(t1)) {
			OPT_err(146);
		}
	}
	aop = (*sentinel)->link2;
	scope = (*sentinel)->scope->left;
	while ((scope != NIL && scope->mnolev >= 0)) {
		while (aop != NIL) {
			fp = aop->link;
			if (eqptyp__6(t1->typ, fp->typ)) {
				if ((((t2 != NIL && fp->link != NIL)) && eqptyp__6(t2->typ, fp->link->typ))) {
					OPT_err(139);
				} else if ((t2 == NIL && fp->link == NIL)) {
					OPT_err(139);
				}
			}
			aop = aop->left;
		}
		scope = scope->left;
		if (scope != NIL) {
			OPT_FindInScope((*sentinel)->name, 32, scope, &aop);
			if (aop != NIL) {
				aop = aop->link2;
			}
		}
	}
	OPT_CopyOp(&new, &*sentinel);
	new->left = (*sentinel)->link2;
	(*sentinel)->link2 = new;
	(*sentinel)->prio = 127;
	*sentinel = new;
	Contextualize__5_s = _s.lnk;
}

static void OPT_Distance (OPT_Struct typ, OPT_Struct otyp, INT8 *distance)
{
	OPT_Struct t;
	*distance = 127;
	if ((typ->form == 13 && __IN(otyp->comp, 0x3c, 32))) {
		typ = typ->BaseTyp;
	}
	if (typ == otyp) {
		*distance = 0;
	} else if (typ == OPT_sinttyp) {
		if (otyp == OPT_inttyp) {
			*distance = 1;
		} else if (otyp == OPT_linttyp) {
			*distance = 2;
		} else if (otyp == OPT_realtyp) {
			*distance = 3;
		} else if (otyp == OPT_lrltyp) {
			*distance = 4;
		}
	} else if (typ == OPT_inttyp) {
		if (otyp == OPT_linttyp) {
			*distance = 1;
		} else if (otyp == OPT_realtyp) {
			*distance = 2;
		} else if (otyp == OPT_lrltyp) {
			*distance = 3;
		}
	} else if (typ == OPT_linttyp) {
		if (otyp == OPT_realtyp) {
			*distance = 1;
		} else if (otyp == OPT_lrltyp) {
			*distance = 2;
		}
	} else if (typ == OPT_realtyp) {
		if (otyp == OPT_lrltyp) {
			*distance = 1;
		}
	} else if ((typ->comp == otyp->comp && typ->comp == 6)) {
		t = typ;
		while ((((t != otyp && t != OPT_undftyp)) && t != NIL)) {
			t = t->BaseTyp;
		}
		if (t == otyp) {
			*distance = typ->extlev - otyp->extlev;
		}
	} else if ((((typ->form == 10 && otyp->comp == 5)) && otyp->BaseTyp->form == 3)) {
		*distance = 1;
	} else if ((__IN(typ->comp, 0x3c, 32) && otyp->comp == 5)) {
		while (otyp->comp == 5) {
			otyp = otyp->BaseTyp;
			typ = typ->BaseTyp;
		}
		if (typ == otyp) {
			*distance = 1;
		} else if ((typ->form == 13 && otyp->form == 13)) {
			OPT_Distance(typ->BaseTyp, otyp->BaseTyp, &*distance);
		}
	} else if ((typ->form == 13 && otyp->form == 13)) {
		typ = typ->BaseTyp;
		otyp = otyp->BaseTyp;
		if ((typ->comp == 6 && otyp->comp == 6)) {
			t = typ;
			while ((((t != otyp && t != NIL)) && t != OPT_undftyp)) {
				t = t->BaseTyp;
			}
			if (t == otyp) {
				*distance = typ->extlev - otyp->extlev;
			}
		}
	}
}

static struct QualResolve__77 {
	struct QualResolve__77 *lnk;
} *QualResolve__77_s;

static BOOLEAN CheckVarPar__78 (OPT_Node act, OPT_Object form);

static BOOLEAN CheckVarPar__78 (OPT_Node act, OPT_Object form)
{
	return (form->mode != 2 || act->class < 7) || act->class == 13;
}

void OPT_QualResolve (OPT_Object *obj, OPT_Node *x, OPT_Node *y, INT8 *distance, BOOLEAN *wrn)
{
	OPT_Object op, yp;
	INT8 d1, d2;
	struct QualResolve__77 _s;
	_s.lnk = QualResolve__77_s;
	QualResolve__77_s = &_s;
	op = (*obj)->link2;
	*obj = NIL;
	*distance = 127;
	while (op != NIL) {
		if (CheckVarPar__78(*x, op->link)) {
			OPT_Distance((*x)->typ, op->link->typ, &d1);
			if (d1 != 127) {
				yp = op->link->link;
				if (*y != NIL) {
					if (yp != NIL) {
						if (CheckVarPar__78(*y, yp)) {
							OPT_Distance((*y)->typ, yp->typ, &d2);
							if (d2 < 127) {
								d1 = d1 + d2;
								if (d1 < *distance) {
									*distance = d1;
									*obj = op;
									*wrn = 0;
								} else if (d1 == *distance) {
									*wrn = 1;
								}
							}
						}
					}
				} else if (yp == NIL) {
					if (d1 < *distance) {
						*distance = d1;
						*obj = op;
						*wrn = 0;
					} else if (d1 == *distance) {
						*wrn = 1;
					}
				}
			}
		}
		op = op->left;
	}
	QualResolve__77_s = _s.lnk;
}

OPT_Object OPT_Resolve (CHAR *name, ADDRESS name__len, OPT_Node *x, OPT_Node *y)
{
	OPT_Object op, res, scope;
	INT8 i, d, distance;
	BOOLEAN wrn, warning;
	res = NIL;
	i = 0;
	distance = 127;
	scope = OPT_topScope;
	wrn = 0;
	warning = 0;
	while (scope != NIL) {
		OPT_FindInScope(name, name__len, scope, &op);
		if ((op != NIL && op->scope != NIL)) {
			scope = op->scope->left->left;
			OPT_QualResolve(&op, &*x, &*y, &d, &wrn);
			if (d < distance) {
				res = op;
				distance = d;
				warning = wrn;
			} else if (d == distance) {
				if (d == 0) {
					__HALT(99);
				} else if (d < 127) {
					warning = 1;
				}
			}
		} else {
			scope = NIL;
		}
	}
	i = 1;
	while (i < OPT_nofmod) {
		OPT_FindInScope(name, name__len, (void*)(OPT_modules->data)[__X(i, OPT_modules->len[0])], &op);
		if (op != NIL) {
			OPT_QualResolve(&op, &*x, &*y, &d, &wrn);
			if (d < distance) {
				res = op;
				distance = d;
				warning = wrn;
			} else if (d == distance) {
				if (d == 0) {
					__HALT(99);
				} else if (d < 127) {
					warning = 1;
				}
			}
		}
		i += 1;
	}
	if (warning) {
		OPT_err(-310);
	}
	return res;
}

void OPT_OpenScope (INT8 level, OPT_Object owner)
{
	OPT_Object head;
	head = OPT_NewObj();
	head->mode = 12;
	head->mnolev = level;
	head->link = owner;
	if (owner != NIL) {
		owner->scope = head;
	}
	head->left = OPT_topScope;
	head->right = NIL;
	head->scope = NIL;
	OPT_topScope = head;
}

void OPT_CloseScope (void)
{
	if (OPT_topScope != NIL) {
		OPT_topScope = OPT_topScope->left;
	}
}

void OPT_Init (OPS_Name name)
{
	OPT_topScope = OPT_universe;
	OPT_OpenScope(0, NIL);
	OPT_nofmod = 1;
	OPT_SYSimported = 0;
	OPT_impSelf = 0;
	OPT_sfpresent = 1;
	OPT_newSF = __IN(10, OPM_parserOptions, 32);
	OPT_extSF = OPT_newSF || __IN(11, OPM_parserOptions, 32);
	(OPT_modules->data)[0] = OPT_NewMod();
	__MOVE((INT32)(ADDRESS)OPT_topScope, (INT32)(ADDRESS)(OPT_modules->data)[0], 116);
	__MOVE(name, (OPT_modules->data)[0]->name, 32);
	OPT_topScope = (OPT_Object)(OPT_modules->data)[0];
}

static void OPT_FPrintName (INT32 *fp, CHAR *name, ADDRESS name__len)
{
	INT16 i;
	CHAR ch;
	i = 0;
	do {
		ch = name[__X(i, name__len)];
		OPM_FPrint(&*fp, (INT16)ch);
		i += 1;
	} while (!(ch == 0x00));
}

static void OPT_FPrintSign (INT32 *fp, OPT_Struct result, OPT_Object par)
{
	OPT_FPrintTyp0(result);
	OPM_FPrint(&*fp, result->fp);
	while (par != NIL) {
		OPM_FPrint(&*fp, par->mode);
		if (par->typ != NIL) {
			OPT_FPrintTyp0(par->typ);
			OPM_FPrint(&*fp, par->typ->fp);
		}
		par = par->link;
	}
}

static void OPT_FPrintMeth (INT32 *pbfp, INT32 *pvfp, OPT_Object fld)
{
	INT32 fp;
	if (fld != NIL) {
		OPT_FPrintMeth(&*pbfp, &*pvfp, fld->left);
		if ((fld->mode == 13 && fld->vis != 0)) {
			fp = 0;
			OPM_FPrint(&fp, 13);
			OPT_FPrintName(&fp, (void*)fld->name, 32);
			OPT_FPrintSign(&fp, fld->typ, fld->link);
			if (fld == fld->link->typ->strobj->link2) {
				OPM_FPrint(&fp, -1);
			}
			fld->fp = fp;
			OPM_FPrint(&fp, __ASHR(fld->adr, 16));
			OPM_FPrint(&*pbfp, fp);
			OPM_FPrint(&*pvfp, fp);
		}
		OPT_FPrintMeth(&*pbfp, &*pvfp, fld->right);
	}
}

static void OPT_FPrintRecord (OPT_Struct typ)
{
	OPT_Object fld;
	INT32 fp, pbfp, pvfp;
	pvfp = typ->fp;
	pbfp = typ->fp;
	if (typ->BaseTyp != NIL) {
		OPM_FPrint(&pvfp, typ->BaseTyp->pvfp);
		OPM_FPrint(&pbfp, typ->BaseTyp->pbfp);
	}
	if (typ->size < 0) {
		(*OPT_typSize)(typ, 0);
	}
	fld = typ->link;
	OPT_FPrintMeth(&pbfp, &pvfp, fld);
	while ((fld != NIL && fld->mode == 4)) {
		OPT_FPrintTyp(fld->typ);
		if (fld->vis != 0) {
			fp = 0;
			OPM_FPrint(&fp, fld->mode);
			OPT_FPrintName(&fp, (void*)fld->name, 32);
			OPM_FPrint(&fp, fld->vis);
			if (fld->sysflag != 0) {
				OPM_FPrint(&fp, fld->sysflag);
			}
			OPM_FPrint(&fp, fld->typ->fp);
			fld->fp = fp;
			OPM_FPrint(&pbfp, fld->typ->pbfp);
			OPM_FPrint(&pbfp, fld->adr);
			OPM_FPrint(&pvfp, fld->typ->pvfp);
			OPM_FPrint(&pvfp, fld->adr);
			OPM_FPrint(&pvfp, fp);
			OPM_FPrint(&pbfp, fp);
			fld = fld->link;
		} else {
			fp = 0;
			if (fld->sysflag != 0) {
				OPM_FPrint(&fp, fld->sysflag);
			}
			fld->fp = fp;
			OPM_FPrint(&pvfp, fld->fp);
			fld = fld->link;
		}
	}
	OPM_FPrintSet(&pbfp, (typ->strobj->conval->setval & 0x32));
	typ->pbfp = pbfp;
	typ->pvfp = pvfp;
}

static void OPT_FPrintTyp0 (OPT_Struct typ)
{
	INT32 fp, fp1, fp2;
	INT8 f, c;
	OPT_Struct btyp;
	if ((typ != NIL && typ->fpdone >= 0)) {
		fp = 0;
		f = typ->form;
		c = typ->comp;
		OPM_FPrint(&fp, f);
		OPM_FPrint(&fp, c);
		fp1 = fp;
		if (typ->sysflag != 0) {
			OPM_FPrint(&fp, typ->sysflag);
		}
		if ((INT16)typ->mno != OPT_modNo) {
			OPT_FPrintName(&fp, (void*)(OPT_modules->data)[__X(typ->mno, OPT_modules->len[0])]->name, 32);
			OPT_FPrintName(&fp, (void*)typ->strobj->name, 32);
		}
		fp2 = fp;
		btyp = typ->BaseTyp;
		typ->fp = fp;
		if ((c == 6 && btyp != NIL) || f == 13) {
			OPT_FPrintTyp0(btyp);
			OPM_FPrint(&typ->fp, btyp->fp);
		} else if (__IN(c, 0x3c, 32)) {
			OPT_FPrintTyp0(btyp);
			OPM_FPrint(&typ->fp, btyp->fp);
			if (c == 2) {
				OPM_FPrint(&typ->fp, typ->n);
			}
			typ->pbfp = typ->fp;
			typ->pvfp = typ->fp;
		} else if (f == 14) {
			OPT_FPrintSign(&typ->fp, btyp, typ->link);
			typ->pbfp = typ->fp;
			typ->pvfp = typ->fp;
		} else if (f == 13) {
			OPM_FPrint(&typ->fp, 1);
		}
	}
}

void OPT_FPrintTyp (OPT_Struct typ)
{
	if ((((typ != NIL && typ->fpdone != OPT_modNo + 1)) && typ->fpdone >= 0)) {
		OPT_FPrintTyp0(typ);
		if (typ->comp != 6) {
			typ->fpdone = OPT_modNo + 1;
		}
		if (typ->BaseTyp != NIL) {
			OPT_FPrintTyp(typ->BaseTyp);
		}
		if (typ->comp == 6) {
			OPT_FPrintRecord(typ);
		}
		typ->fpdone = OPT_modNo + 1;
	}
}

void OPT_FPrintObj (OPT_Object obj)
{
	INT32 fp, fp1;
	REAL rval;
	INT16 f, m;
	OPT_ConstExt ext;
	OPT_Node n;
	fp = 0;
	OPM_FPrint(&fp, obj->mode);
	OPT_FPrintName(&fp, (void*)obj->name, 32);
	OPM_FPrint(&fp, obj->vis);
	if (obj->mode == 3) {
		f = obj->typ->form;
		OPM_FPrint(&fp, f);
		OPM_FPrint(&fp, obj->typ->comp);
		switch (f) {
			case 2: case 3: case 4: case 5: case 6: 
				OPM_FPrint(&fp, obj->conval->intval);
				break;
			case 9: 
				OPM_FPrintSet(&fp, obj->conval->setval);
				break;
			case 7: 
				rval = obj->conval->realval;
				OPM_FPrintReal(&fp, rval);
				break;
			case 8: 
				OPM_FPrintLReal(&fp, obj->conval->realval);
				break;
			case 10: 
				OPT_FPrintName(&fp, (void*)*obj->conval->ext, 256);
				break;
			case 11: 
				break;
			default: __CASECHK;
		}
	} else if (obj->mode == 1) {
		OPT_FPrintTyp(obj->typ);
		OPM_FPrint(&fp, obj->typ->fp);
	} else if (obj->mode == 7) {
		OPT_FPrintSign(&fp, obj->typ, obj->link);
		if (obj->sysflag != 0) {
			OPM_FPrint(&fp, obj->sysflag);
		}
	} else if (obj->mode == 9) {
		OPT_FPrintSign(&fp, obj->typ, obj->link);
		n = obj->code->left;
		while (n != NIL) {
			ext = n->conval->ext;
			m = (INT16)(*ext)[0];
			f = 1;
			OPM_FPrint(&fp, m);
			while (f <= m) {
				OPM_FPrint(&fp, (INT16)(*ext)[__X(f, 256)]);
				f += 1;
			}
			n = n->link;
		}
	} else if (obj->mode == 5) {
		OPT_FPrintTyp(obj->typ);
		OPM_FPrint(&fp, obj->typ->fp);
	}
	obj->fp = fp;
}

static void OPT_FPrintErr (OPT_Object obj)
{
	INT16 errNo;
	if (OPT_expGlobal) {
		if (obj->history == 3) {
			errNo = 450;
		} else if (obj->history == 0) {
			errNo = 451;
		} else if (obj->history == 4) {
			errNo = 452;
		} else {
			return;
		}
		__COPY(obj->name, OPM_errName, 32);
		if (errNo == 451) {
			if (!OPT_extSF) {
				OPT_err(errNo);
			}
			OPT_symExtended = 1;
		} else {
			if (!OPT_newSF) {
				OPT_err(errNo);
			}
			OPT_symNew = 1;
		}
		if (errNo == 450) {
			obj->vis = 0;
		}
	}
}

static OPT_Object OPT_MatchOp (OPT_Object op, OPT_Object list)
{
	OPT_FPrintObj(op);
	list = list->link2;
	while ((list != NIL && list->old == NIL)) {
		if (list->fp == 0) {
			OPT_FPrintObj(list);
		}
		if (op->fp == list->fp) {
			return list;
		}
		list = list->left;
	}
	return NIL;
}

static void OPT_InsertImport (OPT_Object obj, OPT_Object root)
{
	OPT_Object ob0, ob1;
	BOOLEAN left;
	ob0 = root;
	ob1 = ob0->right;
	left = 0;
	for (;;) {
		if (ob1 != NIL) {
			if (__STRCMP(obj->name, ob1->name) < 0) {
				ob0 = ob1;
				ob1 = ob1->left;
				left = 1;
			} else if (__STRCMP(obj->name, ob1->name) > 0) {
				ob0 = ob1;
				ob1 = ob1->right;
				left = 0;
			} else if (obj->name[0] == 0x00) {
				obj->scope = NIL;
				return;
			} else {
				obj->old = ob1;
				if ((ob1->prio == 127 && root->mnolev != 0)) {
					obj->right = NIL;
					obj->left = ob1->link2;
					ob1->link2 = obj;
					obj->mnolev = root->mnolev;
				}
				break;
			}
		} else {
			if (obj->prio == 126) {
				obj->left = NIL;
				ob1 = obj;
				obj = OPT_NewObj();
				OPT_CopyOp(&obj, &ob1);
				obj->prio = 127;
				obj->link2 = ob1;
				ob1->old = NIL;
				ob1->mnolev = root->mnolev;
			}
			if (left) {
				ob0->left = obj;
			} else {
				ob0->right = obj;
			}
			obj->left = NIL;
			obj->right = NIL;
			obj->old = NIL;
			obj->mnolev = root->mnolev;
			return;
		}
	}
}

static INT8 OPT_CompOldTyp (OPT_Struct typ, OPT_Struct oldtyp)
{
	if ((typ->form == 15 && typ->comp != 6) || typ->form == 13) {
		return OPT_CompOldTyp(typ->BaseTyp, oldtyp->BaseTyp);
	} else if ((typ->form == 15 && typ->comp == 6)) {
		if (typ->pvfp != oldtyp->pvfp || typ->pbfp != oldtyp->pbfp) {
			return 4;
		} else {
			return 1;
		}
	} else {
		return 1;
	}
	__RETCHK;
}

static void OPT_CompOldSym (OPT_Object obj)
{
	OPT_Object old;
	while (obj != NIL) {
		old = obj->old;
		if ((old != NIL && old->prio == 127)) {
			old = OPT_MatchOp(obj, old);
			obj->old = old;
		}
		if (old != NIL) {
			if (obj->prio != 126) {
				OPT_FPrintObj(obj);
				OPT_FPrintObj(old);
			}
			if (obj->fp != old->fp) {
				if ((obj->vis != old->vis && old->vis == 0)) {
					obj->history = 3;
					OPT_FPrintErr(obj);
				} else {
					old->history = 4;
				}
			} else if (obj->mode == 5 || (((obj->typ->form == 15 && obj->typ->comp == 6)) && obj->typ->strobj->name[0] == 0x00)) {
				old->history = OPT_CompOldTyp(obj->typ, old->typ);
			} else {
				old->history = 1;
			}
		} else {
			obj->history = 3;
		}
		obj = obj->nxtobj;
	}
}

static void OPT_ReadString (OFS_Rider *R, ADDRESS *R__typ, CHAR *string, ADDRESS string__len)
{
	INT16 i;
	CHAR ch;
	i = 0;
	for (;;) {
		Files_Read(&*R, R__typ, (void*)&ch);
		if (ch == 0x00) {
			string[__X(i, string__len)] = 0x00;
			return;
		} else if (ch < 0x7f) {
			string[__X(i, string__len)] = ch;
			i += 1;
		} else if (ch > 0x7f) {
			string[__X(i, string__len)] = (CHAR)((INT16)ch - 128);
			string[__X(i + 1, string__len)] = 0x00;
			return;
		} else {
			break;
		}
	}
	for (;;) {
		Files_Read(&*R, R__typ, (void*)&ch);
		if (ch == 0x00) {
			string[__X(i, string__len)] = 0x00;
			return;
		} else {
			string[__X(i, string__len)] = ch;
			i += 1;
		}
	}
}

static struct Imp__31 {
	OPS_Name *modName;
	OPT_Module *M;
	OFS_Rider *R;
	INT32 *tag;
	INT8 *mode;
	OPT_Object *obj, *last;
	BOOLEAN *operator;
	struct Imp__31 *lnk;
} *Imp__31_s;

static void GetImports__32 (void);
static void InCProc__34 (void);
static void InConst__36 (void);
static void InObj__38 (void);
static void InParList__40 (OPT_Object *first);
static void InRecord__42 (OPT_Struct typ);
static void InStruct__44 (OPT_Struct *typ, BOOLEAN par);
static void SetTypFlags__46 (OPT_Struct typ);

static void GetImports__32 (void)
{
	OPS_Name name;
	OPT_Module TM;
	OPT_ReadString(&*Imp__31_s->R, OFS_Rider__typ, (void*)name, 32);
	while (name[0] != 0x00) {
		OPT_Imp(name, Imp__31_s->modName, &TM);
		((*Imp__31_s->M)->import_->data)[__X((*Imp__31_s->M)->nofimp, (*Imp__31_s->M)->import_->len[0])] = TM;
		(*Imp__31_s->M)->nofimp += 1;
		if ((*Imp__31_s->M)->nofimp >= (*Imp__31_s->M)->import_->len[0]) {
			OPT_DoubleModArr(&(*Imp__31_s->M)->import_);
		}
		(*Imp__31_s->M)->nofreimp = 0;
		OPT_ReadString(&*Imp__31_s->R, OFS_Rider__typ, (void*)name, 32);
	}
}

static void InParList__40 (OPT_Object *first)
{
	OPT_Object last, par;
	*first = NIL;
	last = NIL;
	Files_ReadNum(&*Imp__31_s->R, OFS_Rider__typ, &*Imp__31_s->tag);
	while (*Imp__31_s->tag != 63) {
		__NEW(par, OPT_ObjDesc);
		if (last == NIL) {
			*first = par;
		} else {
			last->link = par;
		}
		last = par;
		if (*Imp__31_s->tag == 56) {
			par->mode = 2;
			Files_ReadNum(&*Imp__31_s->R, OFS_Rider__typ, &*Imp__31_s->tag);
		} else {
			par->mode = 1;
		}
		InStruct__44(&par->typ, 1);
		OPT_ReadString(&*Imp__31_s->R, OFS_Rider__typ, (void*)par->name, 32);
		Files_ReadNum(&*Imp__31_s->R, OFS_Rider__typ, &*Imp__31_s->tag);
	}
}

static void SetTypFlags__46 (OPT_Struct typ)
{
	if (typ->extlev == -1 || typ->n < 0) {
		if (typ->BaseTyp != NIL) {
			SetTypFlags__46(typ->BaseTyp);
			typ->extlev = typ->BaseTyp->extlev + 1;
			typ->n = typ->BaseTyp->n;
			typ->strobj->conval->setval = typ->strobj->conval->setval | (typ->BaseTyp->strobj->conval->setval & 0x10);
		} else {
			typ->extlev = 0;
			typ->n = 0;
			typ->strobj->scope->left = OPT_topScope;
		}
	}
}

static void InRecord__42 (OPT_Struct typ)
{
	OPT_Object scope, last, fld;
	OPT_Struct btyp;
	INT32 n;
	UINT32 flags;
	OPT_Const conval;
	__NEW(scope, OPT_ObjDesc);
	scope->mode = 12;
	scope->mnolev = -typ->mno;
	last = NIL;
	btyp = typ->BaseTyp;
	conval = OPT_NewConst();
	typ->strobj->conval = conval;
	Files_ReadNum(&*Imp__31_s->R, OFS_Rider__typ, (INT32*)&flags);
	if (__IN(0, flags, 32)) {
		conval->setval |= __SETOF(4,32);
	}
	if (__IN(1, flags, 32)) {
		conval->setval |= __SETOF(5,32);
	}
	if (__IN(2, flags, 32)) {
		conval->setval |= __SETOF(8,32);
	}
	Files_Read(&*Imp__31_s->R, OFS_Rider__typ, (void*)&typ->strobj->prio);
	Files_ReadNum(&*Imp__31_s->R, OFS_Rider__typ, &*Imp__31_s->tag);
	while (*Imp__31_s->tag < 60) {
		__NEW(fld, OPT_ObjDesc);
		if (last != NIL) {
			last->link = fld;
		}
		last = fld;
		if (*Imp__31_s->tag == 55) {
			Files_Read(&*Imp__31_s->R, OFS_Rider__typ, (void*)&fld->sysflag);
			Files_ReadNum(&*Imp__31_s->R, OFS_Rider__typ, &*Imp__31_s->tag);
		}
		if (*Imp__31_s->tag == 54) {
			Files_ReadNum(&*Imp__31_s->R, OFS_Rider__typ, &*Imp__31_s->tag);
			fld->vis = 2;
		} else {
			fld->vis = 1;
		}
		fld->mode = 4;
		InStruct__44(&fld->typ, 0);
		OPT_ReadString(&*Imp__31_s->R, OFS_Rider__typ, (void*)fld->name, 32);
		if (fld->name[0] == 0x00) {
			fld->vis = 0;
		}
		OPT_InsertImport(fld, scope);
		Files_ReadNum(&*Imp__31_s->R, OFS_Rider__typ, &*Imp__31_s->tag);
	}
	if (*Imp__31_s->tag == 60) {
		Files_ReadNum(&*Imp__31_s->R, OFS_Rider__typ, &*Imp__31_s->tag);
		while (*Imp__31_s->tag != 63) {
			__NEW(fld, OPT_ObjDesc);
			fld->mode = 13;
			fld->vis = 1;
			fld->conval = OPT_NewConst();
			fld->linkadr = -1;
			fld->conval->setval = 0x02;
			InStruct__44(&fld->typ, 0);
			OPT_ReadString(&*Imp__31_s->R, OFS_Rider__typ, (void*)fld->name, 32);
			if (fld->name[0] == 0x00) {
				fld->vis = 0;
				OPT_ReadString(&*Imp__31_s->R, OFS_Rider__typ, (void*)fld->name, 32);
			}
			InParList__40(&fld->link);
			if (__STRCMP(fld->name, "@Body") == 0) {
				typ->strobj->link = fld->link;
				fld = typ->strobj;
				conval->setval |= __SETOF(1,32);
			} else {
				if (fld->name[0] == '&') {
					n = 0;
					do {
						fld->name[__X(n, 32)] = fld->name[__X(n + 1, 32)];
						n += 1;
					} while (!(fld->name[__X(n, 32)] == 0x00));
					typ->strobj->link2 = fld;
				}
				OPT_InsertImport(fld, scope);
			}
			Files_ReadNum(&*Imp__31_s->R, OFS_Rider__typ, &*Imp__31_s->tag);
		}
	}
	__ASSERT(!__IN(5, conval->setval, 32) || __IN(1, conval->setval, 32), 0);
	typ->strobj->scope = scope;
	typ->link = scope->right;
}

static void InStruct__44 (OPT_Struct *typ, BOOLEAN par)
{
	INT32 typtag, typadr;
	INT8 vis;
	OPT_Object tobj;
	OPT_Struct btyp;
	OPS_Name typname;
	OPT_Module mod;
	INT16 i;
	if (*Imp__31_s->tag <= 0) {
		*Imp__31_s->tag -= 1;
		__ASSERT(*Imp__31_s->tag > -(*Imp__31_s->M)->struct_->len[0], 0);
		*typ = ((*Imp__31_s->M)->struct_->data)[__X(-*Imp__31_s->tag, (*Imp__31_s->M)->struct_->len[0])];
	} else if (*Imp__31_s->tag <= 14) {
		*typ = OPT_predefStruct[__X(*Imp__31_s->tag, 15)];
	} else if (*Imp__31_s->tag <= 45) {
		if (*Imp__31_s->tag == 45) {
			Files_ReadNum(&*Imp__31_s->R, OFS_Rider__typ, &*Imp__31_s->tag);
		} else {
			*Imp__31_s->tag = *Imp__31_s->tag - 15;
		}
		mod = ((*Imp__31_s->M)->import_->data)[__X(*Imp__31_s->tag, (*Imp__31_s->M)->import_->len[0])];
		OPT_ReadString(&*Imp__31_s->R, OFS_Rider__typ, (void*)typname, 32);
		if (typname[0] != 0x00) {
			i = 1;
			while ((i < mod->nofstr && __STRCMP((mod->struct_->data)[__X(i, mod->struct_->len[0])]->strobj->name, typname) != 0)) {
				i += 1;
			}
			if (i < mod->nofstr) {
				*typ = (mod->struct_->data)[__X(i, mod->struct_->len[0])];
			} else {
				*typ = OPT_niltyp;
				if (!OPT_impSelf) {
					OPT_err(150);
				}
			}
			mod->nofreimp += 1;
			if (mod->nofreimp >= mod->reimp->len[0]) {
				OPT_DoubleStructArr(&mod->reimp);
			}
			(mod->reimp->data)[__X(mod->nofreimp, mod->reimp->len[0])] = *typ;
		} else {
			Files_ReadNum(&*Imp__31_s->R, OFS_Rider__typ, &typadr);
			typadr += 1;
			__ASSERT(typadr < mod->reimp->len[0], 0);
			*typ = (mod->reimp->data)[__X(typadr, mod->reimp->len[0])];
		}
	} else {
		__NEW(*typ, OPT_StrDesc);
		((*Imp__31_s->M)->struct_->data)[__X((*Imp__31_s->M)->nofstr, (*Imp__31_s->M)->struct_->len[0])] = *typ;
		(*typ)->tdadr = -1;
		(*typ)->offset = -1;
		(*typ)->sref = -(*Imp__31_s->M)->nofstr;
		(*Imp__31_s->M)->nofstr += 1;
		if ((*Imp__31_s->M)->nofstr >= (*Imp__31_s->M)->struct_->len[0]) {
			OPT_DoubleStructArr(&(*Imp__31_s->M)->struct_);
		}
		if (*Imp__31_s->tag == 53) {
			vis = 0;
			Files_ReadNum(&*Imp__31_s->R, OFS_Rider__typ, &*Imp__31_s->tag);
		} else {
			vis = 1;
		}
		if (*Imp__31_s->tag == 52) {
			Files_ReadNum(&*Imp__31_s->R, OFS_Rider__typ, &*Imp__31_s->tag);
			(*typ)->sysflag = (INT8)((INT16)*Imp__31_s->tag);
			Files_ReadNum(&*Imp__31_s->R, OFS_Rider__typ, &*Imp__31_s->tag);
		}
		(*typ)->form = OPT_strucForm[__X(*Imp__31_s->tag, 52)];
		(*typ)->comp = OPT_strucComp[__X(*Imp__31_s->tag, 52)];
		(*typ)->mno = -(*Imp__31_s->M)->mnolev;
		(*typ)->size = -1;
		typtag = *Imp__31_s->tag;
		Files_ReadNum(&*Imp__31_s->R, OFS_Rider__typ, &*Imp__31_s->tag);
		(*typ)->extlev = -1;
		InStruct__44(&(*typ)->BaseTyp, par);
		btyp = (*typ)->BaseTyp;
		if (((*typ)->comp == 6 && (btyp == OPT_notyp || btyp == OPT_niltyp))) {
			(*typ)->BaseTyp = NIL;
		} else if (((((*typ)->comp == 6 && btyp != NIL)) && btyp->form == 13)) {
			(*typ)->BaseTyp = btyp->BaseTyp;
		} else if (((((*typ)->form == 13 && btyp->comp == 6)) && btyp->strobj->name[0] == 0x00)) {
			btyp->ptr = *typ;
		}
		__NEW(tobj, OPT_ObjDesc);
		tobj->mode = 5;
		tobj->nxtobj = *Imp__31_s->last;
		*Imp__31_s->last = tobj;
		tobj->typ = *typ;
		OPT_ReadString(&*Imp__31_s->R, OFS_Rider__typ, (void*)tobj->name, 32);
		(*typ)->strobj = tobj;
		if (tobj->name[0] != 0x00) {
			tobj->vis = vis;
			tobj->typ = *typ;
			OPT_InsertImport(tobj, (void*)*Imp__31_s->M);
		}
		switch (typtag) {
			case 47: case 46: 
				if (__IN(btyp->comp, 0x30, 32)) {
					(*typ)->n = btyp->n + 1;
				} else {
					(*typ)->n = 0;
				}
				break;
			case 48: 
				Files_ReadNum(&*Imp__31_s->R, OFS_Rider__typ, &(*typ)->n);
				break;
			case 49: 
				break;
			case 50: 
				InRecord__42(*typ);
				(*typ)->n = -1;
				break;
			case 51: 
				InParList__40(&(*typ)->link);
				break;
			default: __CASECHK;
		}
		if ((((OPT_impSelf && tobj->name[0] != 0x00)) && tobj->vis != 0)) {
			(*typ)->sref = 0;
		}
	}
}

static void InObj__38 (void)
{
	__NEW(*Imp__31_s->obj, OPT_ObjDesc);
	(*Imp__31_s->obj)->mode = *Imp__31_s->mode;
	(*Imp__31_s->obj)->nxtobj = *Imp__31_s->last;
	*Imp__31_s->last = *Imp__31_s->obj;
	if (*Imp__31_s->tag == 55) {
		Files_Read(&*Imp__31_s->R, OFS_Rider__typ, (void*)&(*Imp__31_s->obj)->sysflag);
		Files_ReadNum(&*Imp__31_s->R, OFS_Rider__typ, &*Imp__31_s->tag);
	}
	if (*Imp__31_s->tag == 54) {
		Files_ReadNum(&*Imp__31_s->R, OFS_Rider__typ, &*Imp__31_s->tag);
		(*Imp__31_s->obj)->vis = 2;
	} else {
		(*Imp__31_s->obj)->vis = 1;
	}
	InStruct__44(&(*Imp__31_s->obj)->typ, 0);
	OPT_ReadString(&*Imp__31_s->R, OFS_Rider__typ, (void*)(*Imp__31_s->obj)->name, 32);
	if (*Imp__31_s->operator) {
		(*Imp__31_s->obj)->prio = 126;
	}
	OPT_InsertImport(*Imp__31_s->obj, (void*)*Imp__31_s->M);
}

static void InCProc__34 (void)
{
	OPT_Node n, last;
	OPT_ConstExt ext;
	CHAR ch;
	INT32 i, len;
	__NEW((*Imp__31_s->obj)->code, OPT_NodeDesc);
	(*Imp__31_s->obj)->code->class = 29;
	(*Imp__31_s->obj)->code->conval = OPT_NewConst();
	(*Imp__31_s->obj)->code->obj = *Imp__31_s->obj;
	Files_Read(&*Imp__31_s->R, OFS_Rider__typ, (void*)&ch);
	do {
		__NEW(n, OPT_NodeDesc);
		n->conval = OPT_NewConst();
		ext = OPT_NewExt();
		n->conval->ext = ext;
		if ((*Imp__31_s->obj)->code->left == NIL) {
			(*Imp__31_s->obj)->code->left = n;
		} else {
			last->link = n;
		}
		last = n;
		len = (INT16)ch;
		(*ext)[0] = ch;
		i = 1;
		while (i <= len) {
			Files_Read(&*Imp__31_s->R, OFS_Rider__typ, (void*)&(*ext)[__X(i, 256)]);
			i += 1;
		}
		Files_Read(&*Imp__31_s->R, OFS_Rider__typ, (void*)&ch);
	} while (!(ch == 0x00));
}

static void InConst__36 (void)
{
	OPT_Const conval;
	INT16 s;
	REAL r;
	__NEW(conval, OPT_ConstDesc);
	(*Imp__31_s->obj)->conval = conval;
	switch (*Imp__31_s->tag) {
		case 1: case 2: case 3: case 4: case 5: 
			Files_ReadNum(&*Imp__31_s->R, OFS_Rider__typ, &conval->intval);
			break;
		case 9: 
			Files_ReadNum(&*Imp__31_s->R, OFS_Rider__typ, (INT32*)&conval->setval);
			break;
		case 7: 
			Files_ReadReal(&*Imp__31_s->R, OFS_Rider__typ, &r);
			conval->realval = r;
			conval->intval = -1;
			break;
		case 8: 
			Files_ReadLReal(&*Imp__31_s->R, OFS_Rider__typ, &conval->realval);
			conval->intval = -1;
			break;
		case 10: 
			conval->ext = __NEWARR(NIL, 1, 1, 1, 0, 256);
			OPT_ReadString(&*Imp__31_s->R, OFS_Rider__typ, (void*)*conval->ext, 256);
			s = 0;
			while ((*conval->ext)[__X(s, 256)] != 0x00) {
				s += 1;
			}
			conval->intval = -1;
			conval->intval2 = s + 1;
			break;
		case 12: 
			break;
		default: __CASECHK;
	}
}

static void OPT_Imp (OPS_Name impName, OPS_Name modName, OPT_Module *M)
{
	OFS_Rider R;
	INT16 i;
	INT32 tag;
	BOOLEAN done;
	INT8 mode;
	OPT_Object obj, last;
	OPT_Struct tdum;
	BOOLEAN new, operator;
	struct Imp__31 _s;
	_s.modName = (void*)modName;
	_s.M = M;
	_s.R = &R;
	_s.tag = &tag;
	_s.mode = &mode;
	_s.obj = &obj;
	_s.last = &last;
	_s.operator = &operator;
	_s.lnk = Imp__31_s;
	Imp__31_s = &_s;
	i = 0;
	while ((i < (INT16)OPT_nofmod && __STRCMP(impName, (OPT_modules->data)[__X(i, OPT_modules->len[0])]->name) != 0)) {
		i += 1;
	}
	if (i < (INT16)OPT_nofmod) {
		*M = (OPT_modules->data)[__X(i, OPT_modules->len[0])];
		new = 0;
	} else {
		*M = OPT_NewMod();
		__COPY(impName, (*M)->name, 32);
		(*M)->mnolev = -OPT_nofmod;
		(OPT_modules->data)[__X(OPT_nofmod, OPT_modules->len[0])] = *M;
		OPT_nofmod += 1;
		if (OPT_nofmod >= OPT_modules->len[0]) {
			OPT_DoubleModArr(&OPT_modules);
		}
		new = 1;
	}
	(*M)->nofreimp = 0;
	if (new || (OPT_impSelf && i == 0)) {
		(*M)->nofimp = 0;
		((*M)->struct_->data)[0] = NIL;
		(*M)->nofstr = 1;
		operator = 0;
		OPM_OpenSym(&R, OFS_Rider__typ, (void*)impName, 32, OPT_impSelf, &done);
		if (done) {
			GetImports__32();
			if (OPM_noerr) {
				i = 0;
				while (i < (INT16)OPT_nofmod) {
					(OPT_modules->data)[__X(i, OPT_modules->len[0])]->nofreimp = 0;
					i += 1;
				}
				last = NIL;
				Files_ReadNum(&R, OFS_Rider__typ, &tag);
				if (tag == 55) {
					mode = 3;
					Files_ReadNum(&R, OFS_Rider__typ, &tag);
					while (tag < 56) {
						InObj__38();
						InConst__36();
						Files_ReadNum(&R, OFS_Rider__typ, &tag);
					}
				}
				if (tag == 56) {
					mode = 1;
					Files_ReadNum(&R, OFS_Rider__typ, &tag);
					while (tag < 58) {
						InObj__38();
						Files_ReadNum(&R, OFS_Rider__typ, &tag);
					}
				}
				if (tag == 58) {
					mode = 7;
					Files_ReadNum(&R, OFS_Rider__typ, &tag);
					while (tag < 59) {
						InObj__38();
						InParList__40(&obj->link);
						Files_ReadNum(&R, OFS_Rider__typ, &tag);
						obj->conval = OPT_NewConst();
						obj->conval->setval = 0x0;
					}
				}
				if (tag == 59) {
					mode = 7;
					operator = 1;
					Files_ReadNum(&R, OFS_Rider__typ, &tag);
					while (tag < 60) {
						InObj__38();
						InParList__40(&obj->link);
						obj->conval = OPT_NewConst();
						obj->conval->setval = 0x0;
						Files_ReadNum(&R, OFS_Rider__typ, &tag);
					}
					operator = 0;
				}
				if (tag == 60) {
					mode = 9;
					Files_ReadNum(&R, OFS_Rider__typ, &tag);
					while (tag < 61) {
						InObj__38();
						InParList__40(&obj->link);
						obj->conval = OPT_NewConst();
						obj->conval->setval = 0x82;
						InCProc__34();
						Files_ReadNum(&R, OFS_Rider__typ, &tag);
					}
				}
				if (tag == 61) {
					Files_ReadNum(&R, OFS_Rider__typ, &tag);
					while (tag < 62) {
						__NEW(obj, OPT_ObjDesc);
						obj->vis = 1;
						obj->mode = 5;
						InStruct__44(&obj->typ, 0);
						OPT_ReadString(&R, OFS_Rider__typ, (void*)obj->name, 32);
						if (obj->typ->strobj->vis == 0) {
							obj->typ->strobj->flag |= __SETOF(8,32);
						}
						OPT_InsertImport(obj, (void*)*M);
						OPT_CompOldSym(obj);
						Files_ReadNum(&R, OFS_Rider__typ, &tag);
					}
				}
				if (tag == 62) {
					Files_ReadNum(&R, OFS_Rider__typ, &tag);
					while (tag < 63) {
						InStruct__44(&tdum, 0);
						Files_ReadNum(&R, OFS_Rider__typ, &tag);
					}
				}
				(*M)->publics = last;
				while (last != NIL) {
					if ((((last->mode == 5 && last->typ->form == 15)) && last->typ->comp == 6)) {
						SetTypFlags__46(last->typ);
					}
					last = last->nxtobj;
				}
				Files_Close(Files_Base(&R, OFS_Rider__typ));
			}
		} else {
			if (OPT_impSelf) {
				OPT_newSF = 1;
				OPT_extSF = 1;
				OPT_sfpresent = 0;
			} else {
				OPT_err(152);
			}
		}
	} else if ((i == 0 && !OPT_impSelf)) {
		OPT_err(154);
	}
	Imp__31_s = _s.lnk;
}

void OPT_Import (OPS_Name aliasName, OPS_Name impName, OPS_Name selfName)
{
	OPT_Object ali;
	OPT_Module M;
	OPT_Insert(aliasName, 32, &ali);
	ali->mode = 11;
	ali->typ = OPT_notyp;
	if (__STRCMP(impName, "SYSTEM") == 0) {
		OPT_SYSimported = 1;
		ali->mnolev = 0;
		ali->scope = OPT_syslink;
		ali->adr = 0;
	} else {
		if ((__STRCMP(impName, selfName) == 0 && __STRCMP(aliasName, "@self") != 0)) {
			M = OPT_NewMod();
			OPT_err(49);
		}
		OPT_impSelf = __STRCMP(impName, (OPT_modules->data)[0]->name) == 0;
		OPT_Imp(impName, selfName, &M);
		M->directImp = 1;
		ali->scope = M->right;
		ali->mnolev = M->mnolev;
	}
}

void OPT_OutMod (OPT_Module mod)
{
	if (mod->mode == 0) {
		OPM_SymWMod((void*)mod->name, 32);
		OPT_nofemod += 1;
		if (OPT_nofemod >= OPT_emodules->len[0]) {
			OPT_DoubleModArr(&OPT_emodules);
		}
		(OPT_emodules->data)[__X(OPT_nofemod, OPT_emodules->len[0])] = mod;
		mod->mode = OPT_nofemod;
	}
}

static void OPT_Enumerate (OPT_Object obj)
{
	OPT_Object p;
	if (obj != NIL) {
		if (obj->prio == 127) {
			p = obj->link2;
			while (p != NIL) {
				p->sibling = OPT_exp[15];
				OPT_exp[15] = p;
				p = p->left;
			}
			OPT_Enumerate(obj->left);
			OPT_Enumerate(obj->right);
		} else {
			OPT_Enumerate(obj->left);
			if (obj->vis > 0 == OPT_export) {
				if ((OPT_expGlobal && obj->history == 3)) {
					OPT_FPrintErr(obj);
					obj->mode = 0;
				} else {
					if (obj->mode != 5 || obj->typ->strobj != obj) {
						OPT_FPrintErr(obj);
					}
					if ((obj->mode == 5 && obj->typ->strobj != obj)) {
						obj->sibling = OPT_exp[14];
						OPT_exp[14] = obj;
					} else if (obj->mode != 1 || !obj->par) {
						obj->sibling = OPT_exp[__X(obj->mode, 16)];
						OPT_exp[__X(obj->mode, 16)] = obj;
					}
				}
			}
			OPT_Enumerate(obj->right);
		}
	}
}

static void OPT_OutCProc (OPT_Node n)
{
	OPT_ConstExt ext;
	INT32 i, len;
	do {
		ext = n->conval->ext;
		len = (INT16)(*ext)[0];
		i = 0;
		while (i <= len) {
			OPM_SymW((*ext)[__X(i, 256)]);
			i += 1;
		}
		n = n->link;
	} while (!(n == NIL));
	OPM_SymW(0x00);
}

static void OPT_OutParList (OPT_Object par)
{
	while (par != NIL) {
		if (par->mode == 2) {
			OPM_SymW('8');
		}
		OPT_OutStruct(par->typ);
		OPM_SymWString((void*)par->name, 32);
		par->par = 1;
		par->nxtobj = par->link;
		par = par->link;
	}
	OPM_SymWNum(63);
}

static void OPT_OutFld (OPT_Object fld)
{
	while (fld != NIL) {
		if (fld->sysflag != 0) {
			OPM_SymW('7');
			OPM_SymW((CHAR)fld->sysflag);
		}
		if (fld->vis == 2) {
			OPM_SymW('6');
		}
		OPT_OutStruct(fld->typ);
		if (fld->vis > 0) {
			OPM_SymWString((void*)fld->name, 32);
		} else {
			OPM_SymW(0x00);
		}
		fld = fld->link;
	}
}

static struct OutRecord__70 {
	OPT_Struct *typ;
	INT32 *count;
	struct OutRecord__70 *lnk;
} *OutRecord__70_s;

static void TraverseBody__71 (OPT_Object fld);
static void TraverseT__73 (OPT_Object fld);

static void TraverseBody__71 (OPT_Object fld)
{
	CHAR str[32];
	if ((fld != NIL && __IN(1, fld->conval->setval, 32))) {
		OPM_SymW('<');
		__COPY("@Body", str, 32);
		*OutRecord__70_s->count += 1;
		OPT_OutStruct(OPT_notyp);
		OPM_SymWString((void*)str, 32);
		OPT_OutParList(fld->link);
	}
}

static void TraverseT__73 (OPT_Object fld)
{
	if (fld != NIL) {
		TraverseT__73(fld->left);
		if (fld->mode == 13) {
			if (*OutRecord__70_s->count == 0) {
				OPM_SymW('<');
			}
			*OutRecord__70_s->count += 1;
			OPT_OutStruct(fld->typ);
			if (fld->vis == 0) {
				OPM_SymW(0x00);
			}
			if (fld == (*OutRecord__70_s->typ)->strobj->link2) {
				OPM_SymW('&');
			}
			OPM_SymWString((void*)fld->name, 32);
			OPT_OutParList(fld->link);
		}
		TraverseT__73(fld->right);
	}
}

static void OPT_OutRecord (OPT_Struct typ)
{
	OPT_Struct btyp;
	INT32 count;
	UINT32 flag;
	struct OutRecord__70 _s;
	_s.typ = &typ;
	_s.count = &count;
	_s.lnk = OutRecord__70_s;
	OutRecord__70_s = &_s;
	btyp = typ->BaseTyp;
	flag = 0x0;
	if (__IN(4, typ->strobj->conval->setval, 32)) {
		flag |= __SETOF(0,32);
	}
	if (__IN(5, typ->strobj->conval->setval, 32)) {
		flag |= __SETOF(1,32);
	}
	if (__IN(8, typ->strobj->conval->setval, 32)) {
		flag |= __SETOF(2,32);
	}
	OPM_SymWSet(flag);
	OPM_SymWCh((CHAR)typ->strobj->prio);
	if ((typ->link != NIL && typ->link->mode == 4)) {
		OPT_OutFld(typ->link);
	}
	count = 0;
	TraverseBody__71(typ->strobj);
	TraverseT__73(typ->link);
	OPM_SymWNum(63);
	OutRecord__70_s = _s.lnk;
}

static void OPT_OutStruct (OPT_Struct typ)
{
	INT8 tag;
	OPT_Module mod;
	OPT_Object tobj;
	if (typ == NIL) {
		OPM_SymW(0x00);
	} else if (typ->mno != 0) {
		mod = (OPT_modules->data)[__X(typ->mno, OPT_modules->len[0])];
		OPT_OutMod(mod);
		if (mod->nofstr > 0) {
			mod->nofstr = 0;
		}
		if (mod->mode > 31) {
			OPM_SymW('-');
			OPM_SymWNum(mod->mode - 1);
		} else {
			OPM_SymW((CHAR)(14 + mod->mode));
		}
		if (typ->sref < 0) {
			mod->nofstr -= 1;
			typ->sref = -mod->nofstr;
			OPM_SymWString((void*)typ->strobj->name, 32);
		} else {
			OPM_SymW(0x00);
			OPM_SymWNum(typ->sref - 1);
		}
	} else if (typ->sref > 0) {
		OPM_SymWNum(typ->sref);
	} else if (typ->sref != 0) {
		OPM_SymWNum(typ->sref + 1);
	} else {
		OPT_nofstruc -= 1;
		typ->sref = OPT_nofstruc;
		tag = OPT_strucFormSF[__X(typ->form, 16)] + OPT_strucCompSF[__X(typ->comp, 16)];
		if ((((OPT_export && typ->strobj != NIL)) && typ->strobj->vis == 0)) {
			OPM_SymW('5');
		}
		if (typ->sysflag != 0) {
			OPM_SymW('4');
			OPM_SymW((CHAR)typ->sysflag);
		}
		OPM_SymW((CHAR)tag);
		if ((((typ->comp == 6 && typ->BaseTyp != NIL)) && typ->BaseTyp->ptr != NIL)) {
			OPT_OutStruct(typ->BaseTyp->ptr);
		} else if ((typ->comp == 6 && typ->BaseTyp == NIL)) {
			OPT_OutStruct(OPT_notyp);
		} else {
			OPT_OutStruct(typ->BaseTyp);
		}
		__NEW(tobj, OPT_ObjDesc);
		tobj->mode = 5;
		tobj->nxtobj = OPT_objects;
		OPT_objects = tobj;
		tobj->typ = typ;
		if (typ->strobj == NIL || typ->strobj->name[0] == 0x00) {
			OPM_SymW(0x00);
		} else {
			OPT_FPrintErr(typ->strobj);
			OPM_SymWString((void*)typ->strobj->name, 32);
			__COPY(typ->strobj->name, tobj->name, 32);
		}
		switch (tag) {
			case 47: case 46: 
				break;
			case 48: 
				OPM_SymWNum(typ->n);
				break;
			case 49: 
				break;
			case 50: 
				OPT_OutRecord(typ);
				break;
			case 51: 
				OPT_OutParList(typ->link);
				break;
			default: __CASECHK;
		}
	}
}

static void OPT_OutConst (INT8 form, OPT_Const conval)
{
	switch (form) {
		case 2: case 3: case 4: case 5: case 6: 
			OPM_SymWNum(conval->intval);
			break;
		case 9: 
			OPM_SymWSet(conval->setval);
			break;
		case 7: 
			OPM_SymWReal(conval->realval);
			break;
		case 8: 
			OPM_SymWLReal(conval->realval);
			break;
		case 10: 
			OPM_SymWString((void*)*conval->ext, 256);
			break;
		case 11: 
			break;
		default: __CASECHK;
	}
}

static void OPT_OutObj (OPT_Object obj)
{
	obj->nxtobj = OPT_objects;
	OPT_objects = obj;
	OPT_OutStruct(obj->typ);
	if (obj == OPT_topScope->link->link2) {
		OPM_SymW('&');
	}
	OPM_SymWString((void*)obj->name, 32);
}

void OPT_OutScope (OPT_Object scope, BOOLEAN public)
{
	OPT_Object obj;
	BOOLEAN first;
	INT32 i;
	OPT_export = public;
	OPT_exp[3] = NIL;
	OPT_exp[1] = NIL;
	OPT_exp[6] = NIL;
	OPT_exp[7] = NIL;
	OPT_exp[14] = NIL;
	OPT_exp[5] = NIL;
	OPT_exp[15] = NIL;
	OPT_Enumerate(scope);
	i = 1;
	while ((i < 100 && (OPT_modules->data)[__X(i, OPT_modules->len[0])] != NIL)) {
		if ((OPT_modules->data)[__X(i, OPT_modules->len[0])]->directImp) {
			OPT_OutMod((OPT_modules->data)[__X(i, OPT_modules->len[0])]);
		}
		i += 1;
	}
	if (OPT_exp[3] != NIL) {
		OPM_SymW('7');
		obj = OPT_exp[3];
		while (obj != NIL) {
			OPT_OutObj(obj);
			OPT_OutConst(obj->typ->form, obj->conval);
			obj = obj->sibling;
		}
	}
	if (OPT_exp[1] != NIL) {
		OPM_SymW('8');
		obj = OPT_exp[1];
		while (obj != NIL) {
			if (obj->vis == 2) {
				OPM_SymW('6');
			}
			OPT_OutObj(obj);
			obj = obj->sibling;
		}
	}
	if (OPT_exp[6] != NIL) {
		OPM_SymW('9');
		obj = OPT_exp[6];
		while (obj != NIL) {
			OPT_OutObj(obj);
			OPT_OutParList(obj->link);
			obj = obj->sibling;
		}
	}
	if (OPT_exp[7] != NIL) {
		OPM_SymW(':');
		obj = OPT_exp[7];
		while (obj != NIL) {
			if (obj->sysflag != 0) {
				OPM_SymW('7');
				OPM_SymW((CHAR)obj->sysflag);
			}
			OPT_OutObj(obj);
			OPT_OutParList(obj->link);
			obj = obj->sibling;
		}
	}
	if (OPT_exp[15] != NIL) {
		OPM_SymW(';');
		obj = OPT_exp[15];
		while (obj != NIL) {
			OPT_OutObj(obj);
			OPT_OutParList(obj->link);
			obj = obj->sibling;
		}
	}
	if (OPT_exp[9] != NIL) {
		OPM_SymW('<');
		obj = OPT_exp[9];
		while (obj != NIL) {
			OPT_OutObj(obj);
			OPT_OutParList(obj->link);
			OPT_OutCProc(obj->code->left);
			obj = obj->sibling;
		}
	}
	if (OPT_exp[14] != NIL) {
		OPM_SymW('=');
		obj = OPT_exp[14];
		while (obj != NIL) {
			OPT_OutStruct(obj->typ);
			OPM_SymWString((void*)obj->name, 32);
			obj = obj->sibling;
		}
	}
	if (OPT_exp[5] != NIL) {
		obj = OPT_exp[5];
		first = 1;
		while (obj != NIL) {
			if (obj->typ->sref == 0) {
				if (first) {
					OPM_SymW('>');
					first = 0;
				}
				if (!OPT_export || (obj->typ->strobj != NIL && obj->typ->strobj->vis != 0)) {
					OPT_OutStruct(obj->typ);
				}
			}
			obj = obj->sibling;
		}
	}
	OPM_SymWNum(63);
}

void OPT_Export (OPS_Name modName, BOOLEAN *newsf, BOOLEAN *extsf)
{
	INT8 mods;
	OPS_Name aliasName;
	OPT_symExtended = 0;
	OPT_symNew = 0;
	OPT_nofstruc = 0;
	OPT_nofemod = 0;
	OPT_objects = NIL;
	OPT_modNo = 0;
	__COPY("@self", aliasName, 32);
	mods = OPT_nofmod;
	OPT_Import(aliasName, modName, modName);
	OPT_nofmod = mods;
	if (OPM_noerr) {
		OPT_expGlobal = 1;
		OPT_CompOldSym((OPT_modules->data)[0]->publics);
		OPT_OutScope(OPT_topScope->right, 1);
		OPT_expGlobal = 0;
		*extsf = (OPT_sfpresent && OPT_symExtended);
		*newsf = !OPT_sfpresent || OPT_symNew;
		OPM_EndSym();
		if (!OPM_noerr) {
			OPT_err(155);
			*newsf = 0;
			*extsf = 0;
		}
	} else {
		OPT_newSF = 0;
		OPT_extSF = 0;
	}
}

static void OPT_InitStruct (OPT_Struct *typ, INT8 form, INT8 sref)
{
	*typ = OPT_NewStr(form, 1);
	(*typ)->ref = form;
	(*typ)->size = 1;
	(*typ)->sref = sref;
	OPT_predefStruct[__X(sref, 15)] = *typ;
	(*typ)->tdadr = 0;
	(*typ)->offset = 0;
	(*typ)->strobj = OPT_NewObj();
	(*typ)->fpdone = -1;
	(*typ)->pvfp = form;
	(*typ)->pbfp = form;
	(*typ)->fp = form;
}

static void OPT_EnterIntConst (CHAR *name, ADDRESS name__len, INT32 value)
{
	OPT_Object obj;
	__DUP(name, name__len, CHAR);
	OPT_Insert(name, name__len, &obj);
	obj->conval = OPT_NewConst();
	obj->mode = 3;
	obj->typ = OPT_sinttyp;
	obj->conval->intval = value;
	__DEL(name);
}

static void OPT_EnterTyp (CHAR *name, ADDRESS name__len, INT8 form, INT16 size, OPT_Struct *res, INT8 sref)
{
	OPT_Object obj;
	OPT_Struct typ;
	__DUP(name, name__len, CHAR);
	OPT_Insert(name, name__len, &obj);
	typ = OPT_NewStr(form, 1);
	obj->mode = 5;
	obj->typ = typ;
	obj->vis = 1;
	typ->sref = sref;
	OPT_predefStruct[__X(sref, 15)] = typ;
	typ->strobj = obj;
	typ->size = size;
	typ->tdadr = 0;
	typ->offset = 0;
	typ->ref = form;
	*res = typ;
	typ->fpdone = -1;
	typ->pvfp = size;
	typ->pbfp = form;
	typ->fp = form;
	__DEL(name);
}

static void OPT_EnterTypAlias (CHAR *name, ADDRESS name__len, OPT_Struct typ)
{
	OPT_Object obj;
	__DUP(name, name__len, CHAR);
	OPT_Insert(name, name__len, &obj);
	obj->mode = 5;
	obj->typ = typ;
	obj->vis = 1;
	__DEL(name);
}

static void OPT_EnterProc (CHAR *name, ADDRESS name__len, INT16 num)
{
	OPT_Object obj;
	__DUP(name, name__len, CHAR);
	OPT_Insert(name, name__len, &obj);
	obj->mode = 8;
	obj->typ = OPT_notyp;
	obj->adr = num;
	__DEL(name);
}

static void OPT_EnterPtr (CHAR *name, ADDRESS name__len, INT32 num)
{
	OPT_Object obj;
	__DUP(name, name__len, CHAR);
	OPT_Insert(name, name__len, &obj);
	obj->mode = 1;
	obj->typ = OPT_ptrtyp;
	obj->adr = num;
	obj->linkadr = num;
	obj->mnolev = 0;
	__DEL(name);
}

static void EnumPtrs(void (*P)(void*))
{
	P(OPT_topScope);
	P(OPT_objects);
	P(OPT_undftyp);
	P(OPT_bytetyp);
	P(OPT_booltyp);
	P(OPT_chartyp);
	P(OPT_sinttyp);
	P(OPT_inttyp);
	P(OPT_linttyp);
	P(OPT_hinttyp);
	P(OPT_realtyp);
	P(OPT_lrltyp);
	P(OPT_settyp);
	P(OPT_stringtyp);
	P(OPT_niltyp);
	P(OPT_notyp);
	P(OPT_ptrtyp);
	P(OPT_modules);
	P(OPT_emodules);
	P(OPT_universe);
	P(OPT_syslink);
	__ENUMP(OPT_predefStruct, 15, P);
	__ENUMP(OPT_exp, 16, P);
	P(OPT_ToBeFixed);
}

__TDESC(OPT_ConstDesc, 1, 1) = {__TDFLDS("ConstDesc", 24), {0, -8}};
__TDESC(OPT_ObjDesc, 1, 12) = {__TDFLDS("ObjDesc", 116), {0, 4, 8, 12, 16, 20, 24, 32, 72, 76, 88, 92, -52}};
__TDESC(OPT_ModDesc, 1, 16) = {__TDFLDS("ModDesc", 144), {0, 4, 8, 12, 16, 20, 24, 32, 72, 76, 88, 92, 116, 124, 132, 140, 
	-68}};
__TDESC(OPT_StrDesc, 1, 4) = {__TDFLDS("StrDesc", 76), {36, 40, 44, 72, -20}};
__TDESC(OPT_NodeDesc, 1, 8) = {__TDFLDS("NodeDesc", 48), {0, 4, 8, 16, 20, 24, 32, 36, -36}};

export void *OPT__init(void)
{
	__DEFMOD;
	__MODULE_IMPORT(Files);
	__MODULE_IMPORT(OPM);
	__MODULE_IMPORT(OPS);
	__REGMOD("OPT", EnumPtrs);
	__REGCMD("Close", OPT_Close);
	__REGCMD("CloseScope", OPT_CloseScope);
	__INITYP(OPT_ConstDesc, OPT_ConstDesc, 0);
	__INITYP(OPT_ObjDesc, OPT_ObjDesc, 0);
	__INITYP(OPT_ModDesc, OPT_ObjDesc, 1);
	__INITYP(OPT_StrDesc, OPT_StrDesc, 0);
	__INITYP(OPT_NodeDesc, OPT_NodeDesc, 0);
/* BEGIN */
	OPT_topScope = NIL;
	OPT_modules = __NEWARR(POINTER__typ, 4, 4, 1, 1, 64);
	OPT_emodules = __NEWARR(POINTER__typ, 4, 4, 1, 1, 64);
	OPT_OpenScope(0, NIL);
	OPM_errpos = 0;
	OPT_InitStruct(&OPT_undftyp, 0, 0);
	OPT_InitStruct(&OPT_notyp, 12, 11);
	OPT_InitStruct(&OPT_stringtyp, 10, 10);
	OPT_InitStruct(&OPT_niltyp, 11, 12);
	OPT_undftyp->BaseTyp = OPT_undftyp;
	OPT_EnterTyp((CHAR*)"BYTE", 5, 1, 1, &OPT_bytetyp, 13);
	OPT_EnterTyp((CHAR*)"PTR", 4, 13, 4, &OPT_ptrtyp, 14);
	OPT_EnterProc((CHAR*)"ADR", 4, 20);
	OPT_EnterProc((CHAR*)"CC", 3, 21);
	OPT_EnterProc((CHAR*)"LSH", 4, 22);
	OPT_EnterProc((CHAR*)"ROT", 4, 23);
	OPT_EnterProc((CHAR*)"GET", 4, 24);
	OPT_EnterProc((CHAR*)"PUT", 4, 25);
	OPT_EnterProc((CHAR*)"GETREG", 7, 26);
	OPT_EnterProc((CHAR*)"PUTREG", 7, 27);
	OPT_EnterProc((CHAR*)"BIT", 4, 28);
	OPT_EnterProc((CHAR*)"VAL", 4, 29);
	OPT_EnterProc((CHAR*)"NEW", 4, 30);
	OPT_EnterProc((CHAR*)"MOVE", 5, 31);
	OPT_EnterProc((CHAR*)"PORTOUT", 8, 35);
	OPT_EnterProc((CHAR*)"PORTIN", 7, 36);
	OPT_EnterProc((CHAR*)"STI", 4, 33);
	OPT_EnterProc((CHAR*)"CLI", 4, 34);
	OPT_EnterProc((CHAR*)"HALT", 5, 37);
	OPT_EnterProc((CHAR*)"GET8", 5, 38);
	OPT_EnterProc((CHAR*)"GET16", 6, 39);
	OPT_EnterProc((CHAR*)"GET32", 6, 40);
	OPT_EnterProc((CHAR*)"PUT8", 5, 41);
	OPT_EnterProc((CHAR*)"PUT16", 6, 42);
	OPT_EnterProc((CHAR*)"PUT32", 6, 43);
	OPT_EnterProc((CHAR*)"TYPECODE", 9, 44);
	OPT_syslink = OPT_topScope->right;
	OPT_universe = OPT_topScope;
	OPT_topScope->right = NIL;
	OPT_EnterTyp((CHAR*)"CHAR", 5, 3, 1, &OPT_chartyp, 2);
	OPT_EnterTyp((CHAR*)"SET", 4, 9, 4, &OPT_settyp, 9);
	OPT_EnterTyp((CHAR*)"REAL", 5, 7, 4, &OPT_realtyp, 7);
	OPT_EnterTyp((CHAR*)"INTEGER", 8, 5, 2, &OPT_inttyp, 4);
	OPT_EnterTyp((CHAR*)"LONGINT", 8, 6, 4, &OPT_linttyp, 5);
	OPT_EnterTyp((CHAR*)"HUGEINT", 8, 16, 8, &OPT_hinttyp, 6);
	OPT_EnterTyp((CHAR*)"LONGREAL", 9, 8, 8, &OPT_lrltyp, 8);
	OPT_EnterTyp((CHAR*)"SHORTINT", 9, 4, 1, &OPT_sinttyp, 3);
	OPT_EnterTyp((CHAR*)"BOOLEAN", 8, 2, 1, &OPT_booltyp, 1);
	OPT_EnterTypAlias((CHAR*)"PTR", 4, OPT_ptrtyp);
	OPT_universe = OPT_topScope->right;
	OPT_topScope->right = OPT_syslink;
	OPT_EnterIntConst((CHAR*)"EAX", 4, 8);
	OPT_EnterIntConst((CHAR*)"ECX", 4, 9);
	OPT_EnterIntConst((CHAR*)"EDX", 4, 10);
	OPT_EnterIntConst((CHAR*)"EBX", 4, 11);
	OPT_EnterIntConst((CHAR*)"ESP", 4, 12);
	OPT_EnterIntConst((CHAR*)"EBP", 4, 13);
	OPT_EnterIntConst((CHAR*)"ESI", 4, 14);
	OPT_EnterIntConst((CHAR*)"EDI", 4, 15);
	OPT_EnterIntConst((CHAR*)"AX", 3, 16);
	OPT_EnterIntConst((CHAR*)"CX", 3, 17);
	OPT_EnterIntConst((CHAR*)"DX", 3, 18);
	OPT_EnterIntConst((CHAR*)"BX", 3, 19);
	OPT_EnterIntConst((CHAR*)"SP", 3, 20);
	OPT_EnterIntConst((CHAR*)"BP", 3, 21);
	OPT_EnterIntConst((CHAR*)"SI", 3, 22);
	OPT_EnterIntConst((CHAR*)"DI", 3, 23);
	OPT_EnterIntConst((CHAR*)"AL", 3, 24);
	OPT_EnterIntConst((CHAR*)"CL", 3, 25);
	OPT_EnterIntConst((CHAR*)"DL", 3, 26);
	OPT_EnterIntConst((CHAR*)"BL", 3, 27);
	OPT_EnterIntConst((CHAR*)"AH", 3, 28);
	OPT_EnterIntConst((CHAR*)"CH", 3, 29);
	OPT_EnterIntConst((CHAR*)"DH", 3, 30);
	OPT_EnterIntConst((CHAR*)"BH", 3, 31);
	OPT_topScope->right = OPT_universe;
	OPT_universe = OPT_topScope;
	OPT_EnterProc((CHAR*)"HALT", 5, 0);
	OPT_EnterProc((CHAR*)"NEW", 4, 1);
	OPT_EnterProc((CHAR*)"ABS", 4, 2);
	OPT_EnterProc((CHAR*)"CAP", 4, 3);
	OPT_EnterProc((CHAR*)"ORD", 4, 4);
	OPT_EnterProc((CHAR*)"ENTIER", 7, 5);
	OPT_EnterProc((CHAR*)"ODD", 4, 6);
	OPT_EnterProc((CHAR*)"MIN", 4, 7);
	OPT_EnterProc((CHAR*)"MAX", 4, 8);
	OPT_EnterProc((CHAR*)"CHR", 4, 9);
	OPT_EnterProc((CHAR*)"SHORT", 6, 10);
	OPT_EnterProc((CHAR*)"LONG", 5, 11);
	OPT_EnterProc((CHAR*)"SIZE", 5, 12);
	OPT_EnterProc((CHAR*)"INC", 4, 13);
	OPT_EnterProc((CHAR*)"DEC", 4, 14);
	OPT_EnterProc((CHAR*)"INCL", 5, 15);
	OPT_EnterProc((CHAR*)"EXCL", 5, 16);
	OPT_EnterProc((CHAR*)"LEN", 4, 17);
	OPT_EnterProc((CHAR*)"COPY", 5, 18);
	OPT_EnterProc((CHAR*)"ASH", 4, 19);
	OPT_EnterProc((CHAR*)"ASSERT", 7, 32);
	OPT_EnterProc((CHAR*)"AWAIT", 6, 64);
	OPT_EnterPtr((CHAR*)"@SELF", 6, 0);
	OPT_EnterPtr((CHAR*)"SELF", 5, 0);
	OPT_strucForm[49] = 13;
	OPT_strucForm[50] = 15;
	OPT_strucForm[51] = 14;
	OPT_strucForm[47] = 15;
	OPT_strucForm[48] = 15;
	OPT_strucForm[46] = 15;
	OPT_strucComp[49] = 1;
	OPT_strucComp[50] = 6;
	OPT_strucComp[51] = 1;
	OPT_strucComp[47] = 4;
	OPT_strucComp[48] = 2;
	OPT_strucComp[46] = 5;
	OPT_strucFormSF[13] = 49;
	OPT_strucFormSF[14] = 51;
	OPT_strucCompSF[2] = 48;
	OPT_strucCompSF[4] = 47;
	OPT_strucCompSF[6] = 50;
	OPT_strucCompSF[5] = 46;
	__NEW(OPT_ToBeFixed, OPT_StrDesc);
	OPT_ToBeFixed->incomplete = 1;
	__ENDMOD;
}
