/* voc 2.1.0 [2017/09/06]. Bootstrapping compiler for address size 8, alignment 8. xtaSv */

#define SHORTINT INT8
#define INTEGER  INT16
#define LONGINT  INT32
#define SET      UINT32

#include "SYSTEM.h"
#include "OPM.h"
#include "OPS.h"
#include "OPT.h"


export void (*OPB_typSize)(OPT_Struct, BOOLEAN);
export void (*OPB_verify)(OPT_Object*);
static INT16 OPB_exp;
static INT32 OPB_maxExp;
static OPT_Object OPB_InitPar;


export void OPB_Assign (OPT_Node *x, OPT_Node y);
static void OPB_BindNodes (INT8 class, OPT_Struct typ, OPT_Node *x, OPT_Node y);
export OPT_Node OPB_BoolConst (INT16 value);
static INT32 OPB_BoolToInt (BOOLEAN b);
export void OPB_Call (OPT_Node *x, OPT_Node apar, OPT_Object fp);
static void OPB_CharToString (OPT_Node n);
static void OPB_CheckAssign (OPT_Struct x, OPT_Node ynode);
static void OPB_CheckLeaf (OPT_Node x, BOOLEAN dynArrToo);
export void OPB_CheckParameters (OPT_Object fp, OPT_Object ap, BOOLEAN checkNames);
static void OPB_CheckProc (OPT_Struct x, OPT_Object y);
static void OPB_CheckPtr (OPT_Node *x, OPT_Node *y);
static void OPB_CheckRealType (INT16 f, INT16 nr, OPT_Const x);
static void OPB_CheckReceiver (OPT_Node *x, OPT_Object fp);
export void OPB_CodeInsert (OPT_Node *stat);
static void OPB_ConstOp (INT16 op, OPT_Node x, OPT_Node y);
export void OPB_Construct (INT8 class, OPT_Node *x, OPT_Node y);
static void OPB_Convert (OPT_Node *x, OPT_Struct typ);
export void OPB_CopyAndSubst (OPT_Node *new, OPT_Node old);
export void OPB_DeRef (OPT_Node *x);
export OPT_Node OPB_EmptySet (void);
export void OPB_Enter (OPT_Node *procdec, OPT_Node stat, OPT_Object proc);
export void OPB_Field (OPT_Node *x, OPT_Object y);
export void OPB_In (OPT_Node *x, OPT_Node y);
export void OPB_Index (OPT_Node *x, OPT_Node y);
static void OPB_InitAppend (OPT_Node *x);
export void OPB_InitInsert (OPT_Node *stat);
export void OPB_Inittd (OPT_Node *inittd, OPT_Node *last, OPT_Struct typ);
static BOOLEAN OPB_IntToBool (INT32 i);
export void OPB_Link (OPT_Node *x, OPT_Node *last, OPT_Node y);
export void OPB_Lock (OPT_Node *x, OPT_Object self, BOOLEAN excl);
export void OPB_MOp (INT8 op, OPT_Node *x);
export OPT_Node OPB_NewBoolConst (BOOLEAN boolval);
export OPT_Node OPB_NewIntConst (INT32 intval);
export OPT_Node OPB_NewLeaf (OPT_Object obj);
export OPT_Node OPB_NewRealConst (LONGREAL realval, OPT_Struct typ);
export OPT_Node OPB_NewString (OPS_String str, INT32 len);
export OPT_Node OPB_Nil (void);
static BOOLEAN OPB_NotVar (OPT_Node x);
export void OPB_Op (INT8 op, OPT_Node *x, OPT_Node y);
static void OPB_OpenArrParCheck (OPT_Struct ftyp, OPT_Struct atyp, BOOLEAN fvarpar);
export void OPB_OptIf (OPT_Node *x);
export void OPB_Param (OPT_Node *ap, OPT_Object fp);
export void OPB_PrepCall (OPT_Node *x, OPT_Object *fpar);
export void OPB_Return (OPT_Node *x, OPT_Object proc);
export void OPB_SetElem (OPT_Node *x);
static void OPB_SetIntType (OPT_Node node);
export void OPB_SetRange (OPT_Node *x, OPT_Node y);
export void OPB_StFct (OPT_Node *par0, INT8 fctno, INT16 parno);
export void OPB_StPar0 (OPT_Node *par0, INT16 fctno);
export void OPB_StPar1 (OPT_Node *par0, OPT_Node x, INT8 fctno);
export void OPB_StParN (OPT_Node *par0, OPT_Node x, INT16 fctno, INT16 n);
export void OPB_StaticLink (INT8 dlev);
export void OPB_TypTest (OPT_Node *x, OPT_Object obj, BOOLEAN guard);
static void OPB_Val (OPT_Node *x, OPT_Struct typ);
static void OPB_err (INT16 n);
static INT32 OPB_log (INT32 x);


static void OPB_err (INT16 n)
{
	OPM_err(n);
}

void OPB_InitInsert (OPT_Node *stat)
{
	OPT_Node t;
	if (OPT_topScope->code == NIL) {
		OPT_topScope->code = *stat;
	} else {
		t = OPT_topScope->code;
		while (t->link != NIL) {
			t = t->link;
		}
		t->link = *stat;
		(*stat)->link = NIL;
	}
}

void OPB_CodeInsert (OPT_Node *stat)
{
	OPT_Node t;
	if (OPT_topScope->link->code == NIL) {
		OPT_topScope->link->code = *stat;
	} else {
		t = OPT_topScope->link->code;
		while (t->link != NIL) {
			t = t->link;
		}
		t->link = *stat;
		(*stat)->link = NIL;
	}
}

static void OPB_InitAppend (OPT_Node *x)
{
	OPT_Node t;
	t = OPT_topScope->code;
	if (t != NIL) {
		while (t->link != NIL) {
			t = t->link;
		}
		t->link = *x;
		*x = OPT_topScope->code;
		OPT_topScope->code = NIL;
	}
}

OPT_Node OPB_NewLeaf (OPT_Object obj)
{
	OPT_Node node;
	OPT_Object self;
	if (OPB_verify != NIL) {
		(*OPB_verify)(&obj);
	}
	switch (obj->mode) {
		case 1: 
			node = OPT_NewNode(0);
			node->readonly = (obj->vis == 2 && obj->mnolev < 0);
			break;
		case 2: 
			node = OPT_NewNode(1);
			break;
		case 3: 
			node = OPT_NewNode(7);
			node->conval = OPT_NewConst();
			__GUARDEQP(node->conval, OPT_ConstDesc) = *obj->conval;
			break;
		case 5: 
			node = OPT_NewNode(8);
			break;
		case 6: case 7: case 8: case 9: case 10: 
			node = OPT_NewNode(9);
			break;
		case 4: case 13: 
			OPT_FindInScope((CHAR*)"@SELF", 6, OPT_topScope, &self);
			node = OPB_NewLeaf(self);
			if (node->typ->form == 13) {
				OPB_DeRef(&node);
			}
			OPB_Field(&node, obj);
			return node;
			break;
		default: 
			OPB_err(127);
			node = OPT_NewNode(0);
			break;
	}
	node->obj = obj;
	node->typ = obj->typ;
	return node;
}

void OPB_Construct (INT8 class, OPT_Node *x, OPT_Node y)
{
	OPT_Node node;
	node = OPT_NewNode(class);
	node->typ = OPT_notyp;
	node->left = *x;
	node->right = y;
	*x = node;
}

void OPB_Link (OPT_Node *x, OPT_Node *last, OPT_Node y)
{
	if (*x == NIL) {
		*x = y;
	} else {
		(*last)->link = y;
	}
	while (y->link != NIL) {
		y = y->link;
	}
	*last = y;
}

static INT32 OPB_BoolToInt (BOOLEAN b)
{
	if (b) {
		return 1;
	} else {
		return 0;
	}
	__RETCHK;
}

static BOOLEAN OPB_IntToBool (INT32 i)
{
	if (i == 0) {
		return 0;
	} else {
		return 1;
	}
	__RETCHK;
}

OPT_Node OPB_NewBoolConst (BOOLEAN boolval)
{
	OPT_Node x;
	x = OPT_NewNode(7);
	x->typ = OPT_booltyp;
	x->conval = OPT_NewConst();
	x->conval->intval = OPB_BoolToInt(boolval);
	return x;
}

void OPB_OptIf (OPT_Node *x)
{
	OPT_Node if_, pred;
	if_ = (*x)->left;
	while (if_->left->class == 7) {
		if (OPB_IntToBool(if_->left->conval->intval)) {
			*x = if_->right;
			return;
		} else if (if_->link == NIL) {
			*x = (*x)->right;
			return;
		} else {
			if_ = if_->link;
			(*x)->left = if_;
		}
	}
	pred = if_;
	if_ = if_->link;
	while (if_ != NIL) {
		if (if_->left->class == 7) {
			if (OPB_IntToBool(if_->left->conval->intval)) {
				pred->link = NIL;
				(*x)->right = if_->right;
				return;
			} else {
				if_ = if_->link;
				pred->link = if_;
			}
		} else {
			pred = if_;
			if_ = if_->link;
		}
	}
}

OPT_Node OPB_Nil (void)
{
	OPT_Node x;
	x = OPT_NewNode(7);
	x->typ = OPT_niltyp;
	x->conval = OPT_NewConst();
	x->conval->intval = 0;
	return x;
}

OPT_Node OPB_BoolConst (INT16 value)
{
	OPT_Node x;
	x = OPT_NewNode(7);
	x->typ = OPT_booltyp;
	x->conval = OPT_NewConst();
	x->conval->intval = value;
	return x;
}

OPT_Node OPB_EmptySet (void)
{
	OPT_Node x;
	x = OPT_NewNode(7);
	x->typ = OPT_settyp;
	x->conval = OPT_NewConst();
	x->conval->setval = 0x0;
	return x;
}

static void OPB_SetIntType (OPT_Node node)
{
	INT32 v;
	v = node->conval->intval;
	if ((-128 <= v && v <= 127)) {
		node->typ = OPT_sinttyp;
	} else if (((-32767-1) <= v && v <= 32767)) {
		node->typ = OPT_inttyp;
	} else if (((-2147483647-1) <= (INT64)v && v <= 2147483647)) {
		node->typ = OPT_linttyp;
	} else {
		OPB_err(203);
		node->typ = OPT_sinttyp;
		node->conval->intval = 1;
	}
}

OPT_Node OPB_NewIntConst (INT32 intval)
{
	OPT_Node x;
	x = OPT_NewNode(7);
	x->conval = OPT_NewConst();
	x->conval->intval = intval;
	OPB_SetIntType(x);
	return x;
}

OPT_Node OPB_NewRealConst (LONGREAL realval, OPT_Struct typ)
{
	OPT_Node x;
	x = OPT_NewNode(7);
	x->conval = OPT_NewConst();
	x->conval->realval = realval;
	x->typ = typ;
	x->conval->intval = -1;
	return x;
}

OPT_Node OPB_NewString (OPS_String str, INT32 len)
{
	OPT_Node x;
	x = OPT_NewNode(7);
	x->conval = OPT_NewConst();
	x->typ = OPT_stringtyp;
	x->conval->intval = -1;
	x->conval->intval2 = len;
	x->conval->ext = OPT_NewExt();
	__MOVE(str, *x->conval->ext, 256);
	return x;
}

static void OPB_CharToString (OPT_Node n)
{
	CHAR ch;
	n->typ = OPT_stringtyp;
	ch = (CHAR)n->conval->intval;
	n->conval->ext = OPT_NewExt();
	if (ch == 0x00) {
		n->conval->intval2 = 1;
	} else {
		n->conval->intval2 = 2;
		(*n->conval->ext)[1] = 0x00;
	}
	(*n->conval->ext)[0] = ch;
	n->conval->intval = -1;
	n->obj = NIL;
}

static void OPB_BindNodes (INT8 class, OPT_Struct typ, OPT_Node *x, OPT_Node y)
{
	OPT_Node node;
	node = OPT_NewNode(class);
	node->typ = typ;
	node->left = *x;
	node->right = y;
	*x = node;
}

static BOOLEAN OPB_NotVar (OPT_Node x)
{
	if (x->obj != NIL) {
		x->obj->used = 1;
	}
	return (x->class >= 7 && ((x->class != 11 || x->subcl != 29) || x->left->class >= 7));
}

void OPB_DeRef (OPT_Node *x)
{
	if (((*x)->class >= 7 && (*x)->class != 13)) {
		OPB_err(78);
	} else if ((*x)->typ->form == 13) {
		OPB_BindNodes(3, (*x)->typ->BaseTyp, &*x, NIL);
	} else {
		OPB_err(84);
	}
}

void OPB_Index (OPT_Node *x, OPT_Node y)
{
	INT16 f;
	OPT_Struct typ;
	f = y->typ->form;
	if ((*x)->class >= 7) {
		OPB_err(79);
	} else if (!__IN(f, 0x70, 32) || __IN(y->class, 0x0300, 32)) {
		OPB_err(80);
		y->typ = OPT_inttyp;
	}
	if ((*x)->typ->comp == 2) {
		typ = (*x)->typ->BaseTyp;
		if ((y->class == 7 && (y->conval->intval < 0 || y->conval->intval >= (*x)->typ->n))) {
			OPB_err(81);
		}
	} else if (__IN((*x)->typ->comp, 0x38, 32)) {
		typ = (*x)->typ->BaseTyp;
		if ((y->class == 7 && y->conval->intval < 0)) {
			OPB_err(81);
		}
	} else {
		OPB_err(82);
		typ = OPT_undftyp;
	}
	OPB_BindNodes(4, typ, &*x, y);
	(*x)->readonly = (*x)->left->readonly;
}

void OPB_Field (OPT_Node *x, OPT_Object y)
{
	__ASSERT((*x)->typ->comp == 6, 0);
	if ((*x)->class >= 7) {
		OPB_err(77);
	} else if ((y != NIL && __IN(y->mode, 0x2010, 32))) {
		OPB_BindNodes(2, y->typ, &*x, NIL);
		(*x)->obj = y;
		(*x)->readonly = (*x)->left->readonly || (y->vis == 2 && y->mnolev < 0);
	} else if ((y != NIL && __IN(y->mode, 0x08, 32))) {
		*x = OPB_NewLeaf(y);
	} else {
		OPB_err(83);
		(*x)->typ = OPT_undftyp;
	}
}

static struct TypTest__63 {
	OPT_Node *x;
	OPT_Object *obj;
	BOOLEAN *guard;
	struct TypTest__63 *lnk;
} *TypTest__63_s;

static void GTT__64 (OPT_Struct t0, OPT_Struct t1);

static void GTT__64 (OPT_Struct t0, OPT_Struct t1)
{
	OPT_Node node;
	OPT_Struct t;
	OPT_MarkType(t1);
	t = t0;
	if (t0->sysflag == 1 || t1->sysflag == 1) {
		OPB_err(200);
	}
	while ((((t != NIL && t != t1)) && t != OPT_undftyp)) {
		t = t->BaseTyp;
	}
	if (t != t1) {
		while ((((t1 != NIL && t1 != t0)) && t1 != OPT_undftyp)) {
			t1 = t1->BaseTyp;
		}
		if (t1 == t0 || (*TypTest__63_s->x)->typ == OPT_ptrtyp) {
			if (*TypTest__63_s->guard) {
				OPB_BindNodes(5, NIL, &*TypTest__63_s->x, NIL);
				(*TypTest__63_s->x)->readonly = (*TypTest__63_s->x)->left->readonly;
			} else {
				node = OPT_NewNode(11);
				node->subcl = 16;
				node->left = *TypTest__63_s->x;
				node->obj = *TypTest__63_s->obj;
				*TypTest__63_s->x = node;
			}
		} else {
			OPB_err(85);
		}
	} else if (t0 != t1) {
		OPB_err(85);
	} else if (!*TypTest__63_s->guard) {
		if ((*TypTest__63_s->x)->class == 5) {
			node = OPT_NewNode(11);
			node->subcl = 16;
			node->left = *TypTest__63_s->x;
			node->obj = *TypTest__63_s->obj;
			*TypTest__63_s->x = node;
		} else {
			*TypTest__63_s->x = OPB_NewBoolConst(1);
		}
	}
}

void OPB_TypTest (OPT_Node *x, OPT_Object obj, BOOLEAN guard)
{
	struct TypTest__63 _s;
	_s.x = x;
	_s.obj = &obj;
	_s.guard = &guard;
	_s.lnk = TypTest__63_s;
	TypTest__63_s = &_s;
	OPT_MarkObj(obj);
	if (OPB_NotVar(*x)) {
		OPB_err(112);
	} else if ((*x)->typ->form == 13) {
		if (obj->typ->form != 13) {
			OPB_err(86);
		} else if (obj->typ->BaseTyp->comp != 6) {
			OPB_err(85);
		} else if ((*x)->typ == OPT_ptrtyp) {
			GTT__64((*x)->typ, obj->typ->BaseTyp);
		} else if ((*x)->typ->BaseTyp->comp != 6) {
			OPB_err(85);
		} else {
			GTT__64((*x)->typ->BaseTyp, obj->typ->BaseTyp);
		}
	} else if (((((*x)->typ->comp == 6 && ((*x)->class == 1 || (*x)->class == 3))) && obj->typ->comp == 6)) {
		GTT__64((*x)->typ, obj->typ);
	} else {
		OPB_err(87);
	}
	if (guard) {
		(*x)->typ = obj->typ;
	} else {
		(*x)->typ = OPT_booltyp;
	}
	TypTest__63_s = _s.lnk;
}

void OPB_In (OPT_Node *x, OPT_Node y)
{
	INT16 f;
	INT32 k;
	f = (*x)->typ->form;
	if ((((*x)->class == 8 || (*x)->class == 9) || y->class == 8) || y->class == 9) {
		OPB_err(126);
	} else if ((__IN(f, 0x70, 32) && y->typ->form == 9)) {
		if ((*x)->class == 7) {
			k = (*x)->conval->intval;
			if (k < 0 || k > 31) {
				OPB_err(202);
			} else if (y->class == 7) {
				(*x)->conval->intval = OPB_BoolToInt(__IN(k, y->conval->setval, 32));
				(*x)->obj = NIL;
			} else {
				OPB_BindNodes(12, OPT_booltyp, &*x, y);
				(*x)->subcl = 15;
			}
		} else {
			OPB_BindNodes(12, OPT_booltyp, &*x, y);
			(*x)->subcl = 15;
		}
	} else {
		OPB_err(92);
	}
	(*x)->typ = OPT_booltyp;
}

static INT32 OPB_log (INT32 x)
{
	OPB_exp = 0;
	if (x > 0) {
		while (!__ODD(x)) {
			x = __ASHR(x, 1);
			OPB_exp += 1;
		}
	}
	return x;
}

static void OPB_CheckRealType (INT16 f, INT16 nr, OPT_Const x)
{
	LONGREAL min, max, r;
	if (f == 7) {
		min = OPM_MinReal;
		max = OPM_MaxReal;
	} else {
		min = OPM_MinLReal;
		max = OPM_MaxLReal;
	}
	r = __ABS(x->realval);
	if (r > max || r < min) {
		OPB_err(nr);
		x->realval = (LONGREAL)1;
	} else if (f == 7) {
		x->realval = x->realval;
	}
	x->intval = -1;
}

static struct MOp__33 {
	struct MOp__33 *lnk;
} *MOp__33_s;

static OPT_Node NewOp__34 (INT8 op, OPT_Struct typ, OPT_Node z);

static OPT_Node NewOp__34 (INT8 op, OPT_Struct typ, OPT_Node z)
{
	OPT_Node node;
	node = OPT_NewNode(11);
	node->subcl = op;
	node->typ = typ;
	node->left = z;
	return node;
}

void OPB_MOp (INT8 op, OPT_Node *x)
{
	INT16 f;
	OPT_Struct typ;
	OPT_Node z;
	struct MOp__33 _s;
	_s.lnk = MOp__33_s;
	MOp__33_s = &_s;
	z = *x;
	if (((z->class == 8 || z->class == 9) && op != 34)) {
		OPB_err(126);
	} else if ((z->class == 2 && z->obj->mode == 13)) {
		OPB_err(30);
	} else {
		typ = z->typ;
		f = typ->form;
		switch (op) {
			case 33: 
				if (f == 2) {
					if (z->class == 7) {
						z->conval->intval = OPB_BoolToInt(!OPB_IntToBool(z->conval->intval));
						z->obj = NIL;
					} else {
						z = NewOp__34(op, typ, z);
					}
				} else {
					OPB_err(98);
				}
				break;
			case 6: 
				if (!__IN(f, 0x01f0, 32)) {
					OPB_err(96);
				}
				break;
			case 7: 
				if (__IN(f, 0x03f0, 32)) {
					if (z->class == 7) {
						if (__IN(f, 0x70, 32)) {
							if (z->conval->intval == (-2147483647-1)) {
								OPB_err(203);
							} else {
								z->conval->intval = -z->conval->intval;
								OPB_SetIntType(z);
							}
						} else if (__IN(f, 0x0180, 32)) {
							z->conval->realval = -z->conval->realval;
						} else {
							z->conval->setval = ~z->conval->setval;
						}
						z->obj = NIL;
					} else {
						z = NewOp__34(op, typ, z);
					}
				} else {
					OPB_err(97);
				}
				break;
			case 21: 
				if (__IN(f, 0x01f0, 32)) {
					if (z->class == 7) {
						if (__IN(f, 0x70, 32)) {
							if (z->conval->intval == (-2147483647-1)) {
								OPB_err(203);
							} else {
								z->conval->intval = __ABS(z->conval->intval);
								OPB_SetIntType(z);
							}
						} else {
							z->conval->realval = __ABS(z->conval->realval);
						}
						z->obj = NIL;
					} else {
						z = NewOp__34(op, typ, z);
					}
				} else {
					OPB_err(111);
				}
				break;
			case 22: 
				if (f == 3) {
					if (z->class == 7) {
						z->conval->intval = (INT16)__CAP((CHAR)z->conval->intval);
						z->obj = NIL;
					} else {
						z = NewOp__34(op, typ, z);
					}
				} else {
					OPB_err(111);
					z->typ = OPT_chartyp;
				}
				break;
			case 23: 
				if (__IN(f, 0x70, 32)) {
					if (z->class == 7) {
						z->conval->intval = OPB_BoolToInt(__ODD(z->conval->intval));
						z->obj = NIL;
					} else {
						z = NewOp__34(op, typ, z);
					}
				} else {
					OPB_err(111);
				}
				z->typ = OPT_booltyp;
				break;
			case 24: 
				if (z->class < 7 || f == 10) {
					z = NewOp__34(op, typ, z);
				} else {
					OPB_err(127);
				}
				z->typ = OPT_linttyp;
				break;
			case 25: 
				if ((__IN(f, 0x70, 32) && z->class == 7)) {
					if ((0 <= z->conval->intval && z->conval->intval <= -1)) {
						z = NewOp__34(op, typ, z);
					} else {
						OPB_err(219);
					}
				} else {
					OPB_err(69);
				}
				z->typ = OPT_booltyp;
				break;
			case 30: 
				z = NewOp__34(op, OPT_sinttyp, z);
				break;
			case 31: 
				z = NewOp__34(op, OPT_inttyp, z);
				break;
			case 32: 
				z = NewOp__34(op, OPT_linttyp, z);
				break;
			case 34: 
				OPT_MarkType(z->typ);
				z = NewOp__34(op, OPT_linttyp, z);
				break;
			default: __CASECHK;
		}
	}
	*x = z;
	MOp__33_s = _s.lnk;
}

static void OPB_CheckPtr (OPT_Node *x, OPT_Node *y)
{
	INT16 g;
	OPT_Struct p, q, t;
	g = (*y)->typ->form;
	if (g == 13) {
		p = (*x)->typ->BaseTyp;
		q = (*y)->typ->BaseTyp;
		if ((*x)->typ == OPT_ptrtyp || (*y)->typ == OPT_ptrtyp) {
		} else if ((p->comp == 6 && q->comp == 6)) {
			if (p->extlev < q->extlev) {
				t = p;
				p = q;
				q = t;
			}
			while ((((p != q && p != NIL)) && p != OPT_undftyp)) {
				p = p->BaseTyp;
			}
			if (p == NIL) {
				OPB_err(100);
			}
		} else {
			OPB_err(100);
		}
	} else if (__IN((*x)->typ->BaseTyp->comp, 0x3c, 32)) {
		if (__IN((*y)->typ->comp, 0x3c, 32)) {
			OPB_DeRef(&*x);
		} else if ((*y)->typ->form == 10) {
			OPB_DeRef(&*x);
		} else if (g == 11) {
		} else {
			OPB_err(100);
		}
	} else if (((((*y)->typ->comp == 6 && (*y)->obj != NIL)) && __STRCMP((*y)->obj->name, "@SELF") == 0)) {
		OPB_err(170);
	} else if (g != 11) {
		OPB_err(100);
	}
}

void OPB_CheckParameters (OPT_Object fp, OPT_Object ap, BOOLEAN checkNames)
{
	OPT_Struct ft, at;
	while (fp != NIL) {
		if (ap != NIL) {
			ft = fp->typ;
			at = ap->typ;
			if (ft->sysflag != at->sysflag) {
				OPB_err(115);
			}
			while ((ft->comp == 5 && at->comp == 5)) {
				ft = ft->BaseTyp;
				at = at->BaseTyp;
			}
			if (ft != at) {
				if ((ft->form == 14 && at->form == 14)) {
					if (ft->BaseTyp == at->BaseTyp) {
						OPB_CheckParameters(ft->link, at->link, 0);
					} else {
						OPB_err(117);
					}
				} else {
					OPB_err(115);
				}
			}
			if (fp->mode != ap->mode || (checkNames && __STRCMP(fp->name, ap->name) != 0)) {
				OPB_err(115);
			}
			ap = ap->link;
		} else {
			OPB_err(116);
		}
		fp = fp->link;
	}
	if (ap != NIL) {
		OPB_err(116);
	}
}

static void OPB_CheckProc (OPT_Struct x, OPT_Object y)
{
	if ((x->sysflag == 5 && y->mode == 13)) {
		if (x->BaseTyp == y->typ) {
			OPB_CheckParameters(x->link, y->link->link, 0);
		} else {
			OPB_err(117);
		}
		if (y->sysflag != 0) {
			OPB_err(113);
		}
	} else {
		if (__IN(y->mode, 0x04c0, 32)) {
			if (y->mode == 6) {
				if (y->mnolev == 0) {
					y->mode = 7;
				} else {
					OPB_err(73);
				}
			}
			if (x->BaseTyp == y->typ) {
				OPB_CheckParameters(x->link, y->link, 0);
			} else {
				OPB_err(117);
			}
			if (x->sysflag == 5) {
				if (y->sysflag != 0) {
					OPB_err(113);
				}
			} else if (x->sysflag != y->sysflag) {
				if (x->sysflag != 0) {
					OPB_err(113);
				} else if (y->sysflag == 3) {
					OPB_err(113);
				}
			}
		} else {
			OPB_err(113);
		}
	}
}

static struct ConstOp__15 {
	OPT_Node *x;
	INT16 *f;
	OPT_Const *xval, *yval;
	struct ConstOp__15 *lnk;
} *ConstOp__15_s;

static INT16 ConstCmp__16 (void);

static INT16 ConstCmp__16 (void)
{
	INT16 res;
	switch (*ConstOp__15_s->f) {
		case 0: 
			res = 9;
			break;
		case 1: case 3: case 4: case 5: case 6: 
			if ((*ConstOp__15_s->xval)->intval < (*ConstOp__15_s->yval)->intval) {
				res = 11;
			} else if ((*ConstOp__15_s->xval)->intval > (*ConstOp__15_s->yval)->intval) {
				res = 13;
			} else {
				res = 9;
			}
			break;
		case 7: case 8: 
			if ((*ConstOp__15_s->xval)->realval < (*ConstOp__15_s->yval)->realval) {
				res = 11;
			} else if ((*ConstOp__15_s->xval)->realval > (*ConstOp__15_s->yval)->realval) {
				res = 13;
			} else {
				res = 9;
			}
			break;
		case 2: 
			if ((*ConstOp__15_s->xval)->intval != (*ConstOp__15_s->yval)->intval) {
				res = 10;
			} else {
				res = 9;
			}
			break;
		case 9: 
			if ((*ConstOp__15_s->xval)->setval != (*ConstOp__15_s->yval)->setval) {
				res = 10;
			} else {
				res = 9;
			}
			break;
		case 10: 
			if (__STRCMP(*(*ConstOp__15_s->xval)->ext, *(*ConstOp__15_s->yval)->ext) < 0) {
				res = 11;
			} else if (__STRCMP(*(*ConstOp__15_s->xval)->ext, *(*ConstOp__15_s->yval)->ext) > 0) {
				res = 13;
			} else {
				res = 9;
			}
			break;
		case 11: case 13: case 14: 
			if ((*ConstOp__15_s->xval)->intval != (*ConstOp__15_s->yval)->intval) {
				res = 10;
			} else {
				res = 9;
			}
			break;
		default: __CASECHK;
	}
	(*ConstOp__15_s->x)->typ = OPT_booltyp;
	return res;
}

static void OPB_ConstOp (INT16 op, OPT_Node x, OPT_Node y)
{
	INT16 f, g;
	OPT_Const xval, yval;
	INT32 xv, yv;
	BOOLEAN temp;
	struct ConstOp__15 _s;
	_s.x = &x;
	_s.f = &f;
	_s.xval = &xval;
	_s.yval = &yval;
	_s.lnk = ConstOp__15_s;
	ConstOp__15_s = &_s;
	f = x->typ->form;
	g = y->typ->form;
	xval = x->conval;
	yval = y->conval;
	if (f != g) {
		switch (f) {
			case 3: 
				if (g == 10) {
					OPB_CharToString(x);
				} else {
					OPB_err(100);
					y->typ = x->typ;
					__GUARDEQP(yval, OPT_ConstDesc) = *xval;
				}
				break;
			case 4: 
				if (__IN(g, 0x70, 32)) {
					x->typ = y->typ;
				} else if (g == 7) {
					x->typ = OPT_realtyp;
					xval->realval = xval->intval;
				} else if (g == 8) {
					x->typ = OPT_lrltyp;
					xval->realval = xval->intval;
				} else {
					OPB_err(100);
					y->typ = x->typ;
					__GUARDEQP(yval, OPT_ConstDesc) = *xval;
				}
				break;
			case 5: 
				if (g == 4) {
					y->typ = OPT_inttyp;
				} else if (__IN(g, 0x70, 32)) {
					x->typ = y->typ;
				} else if (g == 7) {
					x->typ = OPT_realtyp;
					xval->realval = xval->intval;
				} else if (g == 8) {
					x->typ = OPT_lrltyp;
					xval->realval = xval->intval;
				} else {
					OPB_err(100);
					y->typ = x->typ;
					__GUARDEQP(yval, OPT_ConstDesc) = *xval;
				}
				break;
			case 6: 
				if (__IN(g, 0x70, 32)) {
					y->typ = OPT_linttyp;
				} else if (g == 7) {
					x->typ = OPT_realtyp;
					xval->realval = xval->intval;
				} else if (g == 8) {
					x->typ = OPT_lrltyp;
					xval->realval = xval->intval;
				} else {
					OPB_err(100);
					y->typ = x->typ;
					__GUARDEQP(yval, OPT_ConstDesc) = *xval;
				}
				break;
			case 7: 
				if (__IN(g, 0x70, 32)) {
					y->typ = x->typ;
					yval->realval = yval->intval;
				} else if (g == 8) {
					x->typ = OPT_lrltyp;
				} else {
					OPB_err(100);
					y->typ = x->typ;
					__GUARDEQP(yval, OPT_ConstDesc) = *xval;
				}
				break;
			case 8: 
				if (__IN(g, 0x70, 32)) {
					y->typ = x->typ;
					yval->realval = yval->intval;
				} else if (g == 7) {
					y->typ = OPT_lrltyp;
				} else {
					OPB_err(100);
					y->typ = x->typ;
					__GUARDEQP(yval, OPT_ConstDesc) = *xval;
				}
				break;
			case 10: 
				if (g == 3) {
					OPB_CharToString(y);
					g = 10;
				} else {
					OPB_err(100);
					y->typ = x->typ;
					__GUARDEQP(yval, OPT_ConstDesc) = *xval;
				}
				break;
			case 11: 
				if (!__IN(g, 0x6000, 32)) {
					OPB_err(100);
				}
				break;
			case 13: 
				OPB_CheckPtr(&x, &y);
				break;
			case 14: 
				if (g != 11) {
					OPB_err(100);
				}
				break;
			default: 
				OPB_err(100);
				y->typ = x->typ;
				__GUARDEQP(yval, OPT_ConstDesc) = *xval;
				break;
		}
		f = x->typ->form;
	}
	switch (op) {
		case 1: 
			if (__IN(f, 0x70, 32)) {
				xv = xval->intval;
				yv = yval->intval;
				if (((((xv == 0 || yv == 0) || (((xv > 0 && yv > 0)) && yv <= __DIV(2147483647, xv))) || (((xv > 0 && yv < 0)) && yv >= __DIV((-2147483647-1), xv))) || (((xv < 0 && yv > 0)) && xv >= __DIV((-2147483647-1), yv))) || (((((((xv < 0 && yv < 0)) && xv != (-2147483647-1))) && yv != (-2147483647-1))) && -xv <= __DIV(2147483647, -yv))) {
					xval->intval = xv * yv;
					OPB_SetIntType(x);
				} else {
					OPB_err(204);
				}
			} else if (__IN(f, 0x0180, 32)) {
				temp = __ABS(yval->realval) <= (LONGREAL)1;
				if (temp || __ABS(xval->realval) <=   1.79769296342094e+308 / (LONGREAL)__ABS(yval->realval)) {
					xval->realval = xval->realval * yval->realval;
					OPB_CheckRealType(f, 204, xval);
				} else {
					OPB_err(204);
				}
			} else if (f == 9) {
				xval->setval = (xval->setval & yval->setval);
			} else if (f != 0) {
				OPB_err(101);
			}
			break;
		case 2: 
			if (__IN(f, 0x70, 32)) {
				if (yval->intval != 0) {
					xval->realval = xval->intval / (REAL)yval->intval;
					OPB_CheckRealType(7, 205, xval);
				} else {
					OPB_err(205);
					xval->realval = (LONGREAL)1;
				}
				x->typ = OPT_realtyp;
			} else if (__IN(f, 0x0180, 32)) {
				temp = __ABS(yval->realval) >= (LONGREAL)1;
				if (temp || __ABS(xval->realval) <=   1.79769296342094e+308 * __ABS(yval->realval)) {
					xval->realval = xval->realval / yval->realval;
					OPB_CheckRealType(f, 205, xval);
				} else {
					OPB_err(205);
				}
			} else if (f == 9) {
				xval->setval = xval->setval ^ yval->setval;
			} else if (f != 0) {
				OPB_err(102);
			}
			break;
		case 3: 
			if (__IN(f, 0x70, 32)) {
				if (yval->intval != 0) {
					xval->intval = __DIV(xval->intval, yval->intval);
					OPB_SetIntType(x);
				} else {
					OPB_err(205);
				}
			} else if (f != 0) {
				OPB_err(103);
			}
			break;
		case 4: 
			if (__IN(f, 0x70, 32)) {
				if (yval->intval != 0) {
					xval->intval = (int)__MOD(xval->intval, yval->intval);
					OPB_SetIntType(x);
				} else {
					OPB_err(205);
				}
			} else if (f != 0) {
				OPB_err(104);
			}
			break;
		case 5: 
			if (f == 2) {
				xval->intval = OPB_BoolToInt((OPB_IntToBool(xval->intval) && OPB_IntToBool(yval->intval)));
			} else {
				OPB_err(94);
			}
			break;
		case 6: 
			if (__IN(f, 0x70, 32)) {
				temp = (yval->intval >= 0 && xval->intval <= 2147483647 - yval->intval);
				if (temp || (yval->intval < 0 && xval->intval >= (-2147483647-1) - yval->intval)) {
					xval->intval += yval->intval;
					OPB_SetIntType(x);
				} else {
					OPB_err(206);
				}
			} else if (__IN(f, 0x0180, 32)) {
				temp = (yval->realval >= (LONGREAL)0 && xval->realval <=   1.79769296342094e+308 - yval->realval);
				if (temp || (yval->realval < (LONGREAL)0 && xval->realval >=  -1.79769296342094e+308 - yval->realval)) {
					xval->realval = xval->realval + yval->realval;
					OPB_CheckRealType(f, 206, xval);
				} else {
					OPB_err(206);
				}
			} else if (f == 9) {
				xval->setval = xval->setval | yval->setval;
			} else if (f != 0) {
				OPB_err(105);
			}
			break;
		case 7: 
			if (__IN(f, 0x70, 32)) {
				if ((yval->intval >= 0 && xval->intval >= (-2147483647-1) + yval->intval) || (yval->intval < 0 && xval->intval <= 2147483647 + yval->intval)) {
					xval->intval -= yval->intval;
					OPB_SetIntType(x);
				} else {
					OPB_err(207);
				}
			} else if (__IN(f, 0x0180, 32)) {
				temp = (yval->realval >= (LONGREAL)0 && xval->realval >=  -1.79769296342094e+308 + yval->realval);
				if (temp || (yval->realval < (LONGREAL)0 && xval->realval <=   1.79769296342094e+308 + yval->realval)) {
					xval->realval = xval->realval - yval->realval;
					OPB_CheckRealType(f, 207, xval);
				} else {
					OPB_err(207);
				}
			} else if (f == 9) {
				xval->setval = (xval->setval & ~yval->setval);
			} else if (f != 0) {
				OPB_err(106);
			}
			break;
		case 8: 
			if (f == 2) {
				xval->intval = OPB_BoolToInt(OPB_IntToBool(xval->intval) || OPB_IntToBool(yval->intval));
			} else {
				OPB_err(95);
			}
			break;
		case 9: 
			xval->intval = OPB_BoolToInt(ConstCmp__16() == 9);
			break;
		case 10: 
			xval->intval = OPB_BoolToInt(ConstCmp__16() != 9);
			break;
		case 11: 
			if (__IN(f, 0x2a04, 32)) {
				OPB_err(108);
			} else {
				xval->intval = OPB_BoolToInt(ConstCmp__16() == 11);
			}
			break;
		case 12: 
			if (__IN(f, 0x2a04, 32)) {
				OPB_err(108);
			} else {
				xval->intval = OPB_BoolToInt(ConstCmp__16() != 13);
			}
			break;
		case 13: 
			if (__IN(f, 0x2a04, 32)) {
				OPB_err(108);
			} else {
				xval->intval = OPB_BoolToInt(ConstCmp__16() == 13);
			}
			break;
		case 14: 
			if (__IN(f, 0x2a04, 32)) {
				OPB_err(108);
			} else {
				xval->intval = OPB_BoolToInt(ConstCmp__16() != 11);
			}
			break;
		default: __CASECHK;
	}
	ConstOp__15_s = _s.lnk;
}

static void OPB_Convert (OPT_Node *x, OPT_Struct typ)
{
	OPT_Node node;
	INT16 f, g;
	INT32 k;
	LONGREAL r;
	f = (*x)->typ->form;
	g = typ->form;
	if ((*x)->class == 7) {
		if (__IN(f, 0x70, 32)) {
			if (__IN(g, 0x70, 32)) {
				if (f > g) {
					OPB_SetIntType(*x);
					if ((INT16)(*x)->typ->form > g) {
						OPB_err(203);
						(*x)->conval->intval = 1;
					}
				}
			} else if (__IN(g, 0x0180, 32)) {
				(*x)->conval->realval = (*x)->conval->intval;
				(*x)->conval->intval = -1;
			} else {
				k = (*x)->conval->intval;
				if (0 > k || k > 255) {
					OPB_err(220);
				}
			}
		} else if (__IN(f, 0x0180, 32)) {
			if (__IN(g, 0x0180, 32)) {
				OPB_CheckRealType(g, 203, (*x)->conval);
			} else {
				r = (*x)->conval->realval;
				if (r <  -2.14748364800000e+009 || r >   2.14748364700000e+009) {
					OPB_err(203);
					r = (LONGREAL)1;
				}
				(*x)->conval->intval = (INT32)__ENTIER(r);
				OPB_SetIntType(*x);
			}
		}
		(*x)->obj = NIL;
	} else if (((((*x)->class == 11 && (*x)->subcl == 20)) && ((INT16)(*x)->left->typ->form < f || f > g))) {
		if ((*x)->left->typ == typ) {
			*x = (*x)->left;
		}
	} else {
		node = OPT_NewNode(11);
		node->subcl = 20;
		node->left = *x;
		*x = node;
	}
	(*x)->typ = typ;
}

static void OPB_Val (OPT_Node *x, OPT_Struct typ)
{
	OPT_Node t;
	INT16 f;
	REAL r;
	f = (*x)->typ->form;
	if (((*x)->class == 8 || (*x)->class == 9) || __IN(f, 0x1401, 32)) {
		OPB_err(126);
	}
	if (((*x)->class == 7 && typ->comp == 1)) {
		if ((typ->form == 7 && __IN(f, 0x70, 32))) {
			*x = OPB_NewRealConst(__VAL(REAL, (*x)->conval->intval), typ);
		} else if ((__IN(typ->form, 0x70, 32) && f == 7)) {
			r = (*x)->conval->realval;
			*x = OPB_NewIntConst(__VAL(INT32, r));
		} else if ((__IN(typ->form, 0x30, 32) && __IN(f, 0x70, 32))) {
			if (typ->form == 4) {
				*x = OPB_NewIntConst((INT8)((INT16)(*x)->conval->intval));
			} else if (typ->form == 5) {
				*x = OPB_NewIntConst((INT16)(*x)->conval->intval);
			}
		} else if ((__IN(typ->form, 0x70, 32) && f == 9)) {
			(*x)->conval->intval = (INT32)(*x)->conval->setval;
		} else if ((typ->form == 9 && __IN(f, 0x70, 32))) {
			(*x)->conval->setval = (UINT32)(*x)->conval->intval;
		} else {
			t = OPT_NewNode(11);
			t->subcl = 29;
			t->left = *x;
			*x = t;
		}
	} else if ((*x)->class >= 7) {
		t = OPT_NewNode(11);
		t->subcl = 29;
		t->left = *x;
		*x = t;
	} else {
		if (__IN(f, 0x0180, 32)) {
			if (__IN(typ->form, 0x0180, 32)) {
				(*x)->readonly = 0;
			} else {
				t = OPT_NewNode(11);
				t->subcl = 29;
				t->left = *x;
				*x = t;
			}
		} else if (__IN(typ->form, 0x0180, 32)) {
			t = OPT_NewNode(11);
			t->subcl = 29;
			t->left = *x;
			*x = t;
		} else if ((((typ->sysflag == 5 && typ->form == 14)) && f != 14)) {
			t = OPT_NewNode(11);
			t->subcl = 29;
			t->left = *x;
			*x = t;
		} else {
			(*x)->readonly = 0;
		}
	}
	(*x)->typ = typ;
}

static struct Op__43 {
	INT16 *f, *g;
	struct Op__43 *lnk;
} *Op__43_s;

static void NewOp__44 (INT8 op, OPT_Struct typ, OPT_Node *x, OPT_Node y);
static BOOLEAN strings__46 (OPT_Node *x, OPT_Node *y);

static void NewOp__44 (INT8 op, OPT_Struct typ, OPT_Node *x, OPT_Node y)
{
	OPT_Node node;
	node = OPT_NewNode(12);
	node->subcl = op;
	node->typ = typ;
	node->left = *x;
	node->right = y;
	*x = node;
}

static BOOLEAN strings__46 (OPT_Node *x, OPT_Node *y)
{
	BOOLEAN ok, xCharArr, yCharArr;
	xCharArr = (__IN((*x)->typ->comp, 0x3c, 32) && (*x)->typ->BaseTyp->form == 3) || *Op__43_s->f == 10;
	yCharArr = (__IN((*y)->typ->comp, 0x3c, 32) && (*y)->typ->BaseTyp->form == 3) || *Op__43_s->g == 10;
	if ((((xCharArr && *Op__43_s->g == 3)) && (*y)->class == 7)) {
		OPB_CharToString(*y);
		*Op__43_s->g = 10;
		yCharArr = 1;
	}
	if ((((yCharArr && *Op__43_s->f == 3)) && (*x)->class == 7)) {
		OPB_CharToString(*x);
		*Op__43_s->f = 10;
		xCharArr = 1;
	}
	ok = (xCharArr && yCharArr);
	if (ok) {
		if ((*Op__43_s->f == 10 && (*x)->conval->intval2 == 1)) {
			(*x)->typ = OPT_chartyp;
			(*x)->conval->intval = 0;
			OPB_Index(&*y, OPB_NewIntConst(0));
		} else if ((*Op__43_s->g == 10 && (*y)->conval->intval2 == 1)) {
			(*y)->typ = OPT_chartyp;
			(*y)->conval->intval = 0;
			OPB_Index(&*x, OPB_NewIntConst(0));
		}
	}
	return ok;
}

void OPB_Op (INT8 op, OPT_Node *x, OPT_Node y)
{
	INT16 f, g;
	OPT_Node t, z;
	OPT_Struct typ;
	BOOLEAN do_;
	INT32 val;
	struct Op__43 _s;
	_s.f = &f;
	_s.g = &g;
	_s.lnk = Op__43_s;
	Op__43_s = &_s;
	z = *x;
	if (((z->class == 8 || z->class == 9) || y->class == 8) || y->class == 9) {
		OPB_err(126);
	} else if ((z->class == 2 && z->obj->mode == 13) || (y->class == 2 && y->obj->mode == 13)) {
		OPB_err(100);
	} else if ((z->class == 7 && y->class == 7)) {
		OPB_ConstOp(op, z, y);
		z->obj = NIL;
	} else {
		if (z->typ != y->typ) {
			g = y->typ->form;
			switch (z->typ->form) {
				case 3: 
					if (z->class == 7) {
						OPB_CharToString(z);
					} else {
						OPB_err(100);
					}
					break;
				case 4: 
					if (__IN(g, 0x01f0, 32)) {
						OPB_Convert(&z, y->typ);
					} else {
						OPB_err(100);
					}
					break;
				case 5: 
					if (g == 4) {
						OPB_Convert(&y, z->typ);
					} else if (__IN(g, 0x01f0, 32)) {
						OPB_Convert(&z, y->typ);
					} else {
						OPB_err(100);
					}
					break;
				case 6: 
					if (__IN(g, 0x70, 32)) {
						OPB_Convert(&y, z->typ);
					} else if (__IN(g, 0x0180, 32)) {
						OPB_Convert(&z, y->typ);
					} else {
						OPB_err(100);
					}
					break;
				case 7: 
					if (__IN(g, 0x70, 32)) {
						OPB_Convert(&y, z->typ);
					} else if (__IN(g, 0x0180, 32)) {
						OPB_Convert(&z, y->typ);
					} else {
						OPB_err(100);
					}
					break;
				case 8: 
					if (__IN(g, 0x01f0, 32)) {
						OPB_Convert(&y, z->typ);
					} else if (__IN(g, 0x0180, 32)) {
						OPB_Convert(&y, z->typ);
					} else {
						OPB_err(100);
					}
					break;
				case 11: 
					if (!__IN(g, 0x6000, 32)) {
						OPB_err(100);
					}
					break;
				case 13: 
					OPB_CheckPtr(&z, &y);
					break;
				case 14: 
					if (g != 11) {
						OPB_err(100);
					}
					break;
				case 10: 
					break;
				case 15: 
					if (z->typ->comp == 6) {
						if ((((g == 13 && z->obj != NIL)) && __STRCMP(z->obj->name, "@SELF") == 0)) {
							OPB_err(170);
						} else {
							OPB_err(100);
						}
					}
					break;
				default: 
					OPB_err(100);
					break;
			}
		}
		typ = z->typ;
		f = typ->form;
		g = y->typ->form;
		switch (op) {
			case 1: 
				do_ = 1;
				if (__IN(f, 0x70, 32)) {
					if (z->class == 7) {
						val = z->conval->intval;
						if (val == 1) {
							do_ = 0;
							z = y;
						} else if (val == 0) {
							do_ = 0;
						} else if (OPB_log(val) == 1) {
							t = y;
							y = z;
							z = t;
							op = 17;
							y->typ = OPT_sinttyp;
							y->conval->intval = OPB_exp;
							y->obj = NIL;
						}
					} else if (y->class == 7) {
						val = y->conval->intval;
						if (val == 1) {
							do_ = 0;
						} else if (val == 0) {
							do_ = 0;
							z = y;
						} else if ((OPB_log(val) == 1 && !__IN(1, OPM_codeOptions, 32))) {
							op = 17;
							y->typ = OPT_sinttyp;
							y->conval->intval = OPB_exp;
							y->obj = NIL;
						}
					}
				} else if (!__IN(f, 0x0381, 32)) {
					OPB_err(105);
					typ = OPT_undftyp;
				}
				if (do_) {
					NewOp__44(op, typ, &z, y);
				}
				break;
			case 2: 
				if (__IN(f, 0x70, 32)) {
					if ((y->class == 7 && y->conval->intval == 0)) {
						OPB_err(205);
					}
					OPB_Convert(&z, OPT_realtyp);
					OPB_Convert(&y, OPT_realtyp);
					typ = OPT_realtyp;
				} else if (__IN(f, 0x0180, 32)) {
					if ((y->class == 7 && y->conval->realval == (LONGREAL)0)) {
						OPB_err(205);
					}
				} else if ((f != 9 && f != 0)) {
					OPB_err(102);
					typ = OPT_undftyp;
				}
				NewOp__44(op, typ, &z, y);
				break;
			case 3: 
				do_ = 1;
				if (__IN(f, 0x70, 32)) {
					if (y->class == 7) {
						val = y->conval->intval;
						if (val == 0) {
							OPB_err(205);
						} else if (val == 1) {
							do_ = 0;
						} else if (OPB_log(val) == 1) {
							op = 17;
							y->typ = OPT_sinttyp;
							y->conval->intval = -OPB_exp;
							y->obj = NIL;
						}
					}
				} else if (f != 0) {
					OPB_err(103);
					typ = OPT_undftyp;
				}
				if (do_) {
					NewOp__44(op, typ, &z, y);
				}
				break;
			case 4: 
				if (__IN(f, 0x70, 32)) {
					if (y->class == 7) {
						if (y->conval->intval == 0) {
							OPB_err(205);
						} else if (y->conval->intval == 1) {
							*x = OPT_NewNode(7);
							(*x)->typ = typ;
							(*x)->conval = OPT_NewConst();
							(*x)->conval->intval = 0;
							Op__43_s = _s.lnk;
							return;
						} else if (OPB_log(y->conval->intval) == 1) {
							op = 18;
							y->conval->intval = __ASH(-1, OPB_exp);
							y->obj = NIL;
						}
					}
				} else if (f != 0) {
					OPB_err(104);
					typ = OPT_undftyp;
				}
				NewOp__44(op, typ, &z, y);
				break;
			case 5: 
				if (f == 2) {
					if (z->class == 7) {
						if (OPB_IntToBool(z->conval->intval)) {
							z = y;
						}
					} else if ((y->class == 7 && OPB_IntToBool(y->conval->intval))) {
					} else {
						NewOp__44(op, typ, &z, y);
					}
				} else if (f != 0) {
					OPB_err(94);
					z->typ = OPT_undftyp;
				}
				break;
			case 6: 
				if (!__IN(f, 0x03f1, 32)) {
					OPB_err(105);
					typ = OPT_undftyp;
				}
				do_ = 1;
				if (__IN(f, 0x70, 32)) {
					if ((z->class == 7 && z->conval->intval == 0)) {
						do_ = 0;
						z = y;
					}
					if ((y->class == 7 && y->conval->intval == 0)) {
						do_ = 0;
					}
				}
				if (do_) {
					NewOp__44(op, typ, &z, y);
				}
				break;
			case 7: 
				if (!__IN(f, 0x03f1, 32)) {
					OPB_err(106);
					typ = OPT_undftyp;
				}
				if ((!__IN(f, 0x70, 32) || y->class != 7) || y->conval->intval != 0) {
					NewOp__44(op, typ, &z, y);
				}
				break;
			case 8: 
				if (f == 2) {
					if (z->class == 7) {
						if (!OPB_IntToBool(z->conval->intval)) {
							z = y;
						}
					} else if ((y->class == 7 && !OPB_IntToBool(y->conval->intval))) {
					} else {
						NewOp__44(op, typ, &z, y);
					}
				} else if (f != 0) {
					OPB_err(95);
					z->typ = OPT_undftyp;
				}
				break;
			case 9: case 10: 
				if (__IN(f, 0x6bff, 32) || strings__46(&z, &y)) {
					typ = OPT_booltyp;
				} else {
					OPB_err(107);
					typ = OPT_undftyp;
				}
				NewOp__44(op, typ, &z, y);
				break;
			case 11: case 12: case 13: case 14: 
				if (__IN(f, 0x01f9, 32) || strings__46(&z, &y)) {
					typ = OPT_booltyp;
				} else {
					OPB_err(108);
					typ = OPT_undftyp;
				}
				NewOp__44(op, typ, &z, y);
				break;
			default: __CASECHK;
		}
	}
	*x = z;
	Op__43_s = _s.lnk;
}

void OPB_SetRange (OPT_Node *x, OPT_Node y)
{
	INT32 k, l;
	if ((((*x)->class == 8 || (*x)->class == 9) || y->class == 8) || y->class == 9) {
		OPB_err(126);
	} else if ((__IN((*x)->typ->form, 0x70, 32) && __IN(y->typ->form, 0x70, 32))) {
		if ((*x)->class == 7) {
			k = (*x)->conval->intval;
			if (0 > k || k > 31) {
				OPB_err(202);
			}
		}
		if (y->class == 7) {
			l = y->conval->intval;
			if (0 > l || l > 31) {
				OPB_err(202);
			}
		}
		if (((*x)->class == 7 && y->class == 7)) {
			if (k <= l) {
				(*x)->conval->setval = __SETRNG(k, l, 32);
			} else {
				OPB_err(201);
				(*x)->conval->setval = __SETRNG(l, k, 32);
			}
			(*x)->obj = NIL;
		} else {
			OPB_BindNodes(10, OPT_settyp, &*x, y);
		}
	} else {
		OPB_err(93);
	}
	(*x)->typ = OPT_settyp;
}

void OPB_SetElem (OPT_Node *x)
{
	INT32 k;
	if ((*x)->class == 8 || (*x)->class == 9) {
		OPB_err(126);
	} else if (!__IN((*x)->typ->form, 0x70, 32)) {
		OPB_err(93);
	} else if ((*x)->class == 7) {
		k = (*x)->conval->intval;
		if ((0 <= k && k <= 31)) {
			(*x)->conval->setval = __SETOF(k,32);
		} else {
			OPB_err(202);
		}
		(*x)->obj = NIL;
	} else {
		OPB_Convert(&*x, OPT_settyp);
	}
	(*x)->typ = OPT_settyp;
}

static void OPB_CheckAssign (OPT_Struct x, OPT_Node ynode)
{
	INT16 f, g;
	OPT_Struct y, p, q;
	y = ynode->typ;
	f = x->form;
	g = y->form;
	if (ynode->class == 8 || (ynode->class == 9 && f != 14)) {
		OPB_err(126);
	} else if ((((ynode->class == 2 && ynode->obj->mode == 13)) && f != 14)) {
		OPB_err(30);
	}
	switch (f) {
		case 0: case 10: 
			break;
		case 1: 
			if (!__IN(g, 0x1a, 32)) {
				OPB_err(113);
			}
			break;
		case 2: case 3: case 4: case 9: case 16: 
			if (g != f) {
				OPB_err(113);
			}
			break;
		case 5: 
			if (!__IN(g, 0x30, 32)) {
				OPB_err(113);
			}
			break;
		case 6: 
			if (!__IN(g, 0x70, 32)) {
				OPB_err(113);
			}
			break;
		case 7: 
			if (!__IN(g, 0xf0, 32)) {
				OPB_err(113);
			}
			break;
		case 8: 
			if (!__IN(g, 0x01f0, 32)) {
				OPB_err(113);
			}
			break;
		case 13: 
			if ((x == y || g == 11) || (x == OPT_ptrtyp && g == 13)) {
			} else if (g == 13) {
				p = x->BaseTyp;
				q = y->BaseTyp;
				if ((p->comp == 6 && q->comp == 6)) {
					while ((((q != p && q != NIL)) && q != OPT_undftyp)) {
						q = q->BaseTyp;
					}
					if (q == NIL) {
						OPB_err(113);
					}
				} else {
					OPB_err(113);
				}
			} else if ((((y->comp == 6 && ynode->obj != NIL)) && __STRCMP(ynode->obj->name, "@SELF") == 0)) {
				OPB_err(170);
			} else {
				OPB_err(113);
			}
			break;
		case 14: 
			if (ynode->class == 9) {
				OPB_CheckProc(x, ynode->obj);
			} else if (x == y || g == 11) {
			} else if ((x->sysflag == 5 && ynode->class == 2)) {
				OPB_CheckProc(x, ynode->obj);
			} else {
				OPB_err(113);
			}
			break;
		case 12: case 11: 
			OPB_err(113);
			break;
		case 15: 
			OPT_MarkType(x);
			if (x->comp == 2) {
				if ((ynode->class == 7 && g == 3)) {
					OPB_CharToString(ynode);
					y = ynode->typ;
					g = 10;
				}
				if (x == y) {
				} else if ((ynode->typ->form == 13 && x == ynode->typ->BaseTyp)) {
				} else if ((g == 10 && x->BaseTyp == OPT_chartyp)) {
					if (ynode->conval->intval2 > x->n) {
						OPB_err(114);
					}
				} else {
					OPB_err(113);
				}
			} else if (__IN(x->comp, 0x18, 32)) {
				if (x != y) {
					OPB_err(113);
				}
			} else if (x->comp == 6) {
				if (x == y) {
				} else if (y->comp == 6) {
					q = y->BaseTyp;
					while ((((q != NIL && q != x)) && q != OPT_undftyp)) {
						q = q->BaseTyp;
					}
					if (q == NIL) {
						OPB_err(113);
					}
				} else {
					OPB_err(113);
				}
			} else {
				OPB_err(113);
			}
			break;
		default: __CASECHK;
	}
	if ((((((ynode->class == 7 && g < f)) && __IN(g, 0xf0, 32))) && __IN(f, 0x01e0, 32))) {
		OPB_Convert(&ynode, x);
	}
}

static void OPB_CheckLeaf (OPT_Node x, BOOLEAN dynArrToo)
{
	OPT_Object obj;
	if ((x->class == 11 && x->subcl == 29)) {
		x = x->left;
	}
	if (x->class == 5) {
		x = x->left;
	}
	if ((x->class == 0 && (dynArrToo || x->typ->comp != 5))) {
		obj = x->obj;
		while (obj != NIL) {
			obj->leaf = 0;
			obj = obj->scope;
		}
	}
}

void OPB_StPar0 (OPT_Node *par0, INT16 fctno)
{
	INT16 f;
	OPT_Struct t, ptr, typ;
	OPT_Node x;
	x = *par0;
	f = x->typ->form;
	switch (fctno) {
		case 0: case 37: 
			if ((__IN(f, 0x70, 32) && x->class == 7)) {
				if (fctno == 37 || (20 <= x->conval->intval && x->conval->intval <= 2147483647)) {
					OPB_BindNodes(28, OPT_notyp, &x, x);
				} else {
					OPB_err(218);
				}
			} else {
				OPB_err(69);
			}
			x->typ = OPT_notyp;
			break;
		case 44: 
			if (x->class != 8 || (x->typ->comp != 6 && (f != 13 || x->typ->BaseTyp->comp != 6))) {
				OPB_err(53);
			} else {
				OPB_MOp(34, &x);
			}
			break;
		case 1: 
			typ = OPT_notyp;
			OPB_InitPar = NIL;
			if (OPB_NotVar(x)) {
				OPB_err(112);
			} else if (f == 13 || x->typ->comp == 4) {
				if (x->readonly) {
					OPB_err(76);
				}
				f = x->typ->BaseTyp->comp;
				if (__IN(f, 0x74, 32) || x->typ->comp == 4) {
					if (x->typ->comp == 4) {
						typ = x->typ;
					} else if (f != 6) {
						typ = x->typ->BaseTyp;
					}
					t = x->typ;
					ptr = NIL;
					while (t->form == 13 || __IN(t->comp, 0x3c, 32)) {
						if (t->form == 13) {
							ptr = t;
						}
						t = t->BaseTyp;
					}
					if ((t->mno != 0 && t->comp == 6)) {
						if (t->strobj->vis != 0 || __IN(8, t->strobj->flag, 32)) {
						} else if ((((((ptr != NIL && ptr->BaseTyp == t)) && ptr->mno != 0)) && ptr->strobj->vis != 0) || __IN(8, ptr->strobj->flag, 32)) {
						} else {
							OPB_err(200);
						}
					}
					OPT_MarkType(x->typ);
					OPB_BindNodes(19, OPT_notyp, &x, NIL);
					x->subcl = (INT8)fctno;
					if ((f == 6 && x->left->typ->BaseTyp->strobj != NIL)) {
						t = x->left->typ->BaseTyp;
						while ((t != NIL && t->strobj->link2 == NIL)) {
							t = t->BaseTyp;
						}
						if (t != NIL) {
							OPB_InitPar = t->strobj->link2;
						} else {
							OPB_InitPar = NIL;
						}
						if (OPB_InitPar != NIL) {
							OPB_CopyAndSubst(&*par0, x->left);
							if (OPB_InitPar->link->typ->comp == 6) {
								OPB_DeRef(&*par0);
							}
							(*par0)->link = OPT_NewNode(9);
							(*par0)->link->obj = OPB_InitPar;
							(*par0)->link->typ = OPB_InitPar->typ;
							OPB_InitPar = OPB_InitPar->link->link;
							x->left->link = *par0;
						}
					}
				} else {
					OPB_err(111);
				}
			} else {
				OPB_err(111);
			}
			x->typ = typ;
			break;
		case 2: 
			OPB_MOp(21, &x);
			break;
		case 3: 
			OPB_MOp(22, &x);
			break;
		case 4: 
			if (x->class == 8 || x->class == 9) {
				OPB_err(126);
			} else if (__IN(f, 0x0a, 32)) {
				OPB_Convert(&x, OPT_inttyp);
			} else {
				OPB_err(111);
			}
			x->typ = OPT_inttyp;
			break;
		case 5: 
			if (x->class == 8 || x->class == 9) {
				OPB_err(126);
			} else if (__IN(f, 0x0180, 32)) {
				OPB_Convert(&x, OPT_linttyp);
			} else {
				OPB_err(111);
			}
			x->typ = OPT_linttyp;
			break;
		case 6: 
			OPB_MOp(23, &x);
			break;
		case 7: 
			if (x->class == 8) {
				switch (f) {
					case 2: 
						x = OPB_NewBoolConst(0);
						break;
					case 3: 
						x = OPB_NewIntConst(0);
						x->typ = OPT_chartyp;
						break;
					case 4: 
						x = OPB_NewIntConst(-128);
						break;
					case 5: 
						x = OPB_NewIntConst((-32767-1));
						break;
					case 6: 
						x = OPB_NewIntConst((-2147483647-1));
						break;
					case 9: 
						x = OPB_NewIntConst(0);
						x->typ = OPT_inttyp;
						break;
					case 7: 
						x = OPB_NewRealConst(OPM_MinReal, OPT_realtyp);
						break;
					case 8: 
						x = OPB_NewRealConst(OPM_MinLReal, OPT_lrltyp);
						break;
					default: 
						OPB_err(111);
						break;
				}
			} else {
				OPB_err(110);
			}
			break;
		case 8: 
			if (x->class == 8) {
				switch (f) {
					case 2: 
						x = OPB_NewBoolConst(1);
						break;
					case 3: 
						x = OPB_NewIntConst(255);
						x->typ = OPT_chartyp;
						break;
					case 4: 
						x = OPB_NewIntConst(127);
						break;
					case 5: 
						x = OPB_NewIntConst(32767);
						break;
					case 6: 
						x = OPB_NewIntConst(2147483647);
						break;
					case 9: 
						x = OPB_NewIntConst(31);
						x->typ = OPT_inttyp;
						break;
					case 7: 
						x = OPB_NewRealConst(OPM_MaxReal, OPT_realtyp);
						break;
					case 8: 
						x = OPB_NewRealConst(OPM_MaxLReal, OPT_lrltyp);
						break;
					default: 
						OPB_err(111);
						break;
				}
			} else {
				OPB_err(110);
			}
			break;
		case 9: 
			if (x->class == 8 || x->class == 9) {
				OPB_err(126);
			} else if (__IN(f, 0x73, 32)) {
				OPB_Convert(&x, OPT_chartyp);
			} else {
				OPB_err(111);
				x->typ = OPT_chartyp;
			}
			break;
		case 10: 
			if (x->class == 8 || x->class == 9) {
				OPB_err(126);
			} else if (f == 5) {
				OPB_Convert(&x, OPT_sinttyp);
			} else if (f == 6) {
				OPB_Convert(&x, OPT_inttyp);
			} else if (f == 8) {
				OPB_Convert(&x, OPT_realtyp);
			} else {
				OPB_err(111);
			}
			break;
		case 11: 
			if (x->class == 8 || x->class == 9) {
				OPB_err(126);
			} else if (f == 4) {
				OPB_Convert(&x, OPT_inttyp);
			} else if (f == 5) {
				OPB_Convert(&x, OPT_linttyp);
			} else if (f == 7) {
				OPB_Convert(&x, OPT_lrltyp);
			} else if (f == 3) {
				OPB_Convert(&x, OPT_linttyp);
			} else {
				OPB_err(111);
			}
			break;
		case 13: case 14: 
			if (OPB_NotVar(x)) {
				OPB_err(112);
			} else if (!__IN(f, 0x70, 32)) {
				OPB_err(111);
			} else if (x->readonly) {
				OPB_err(76);
			}
			break;
		case 15: case 16: 
			if (OPB_NotVar(x)) {
				OPB_err(112);
			} else if (x->typ != OPT_settyp) {
				OPB_err(111);
				x->typ = OPT_settyp;
			} else if (x->readonly) {
				OPB_err(76);
			}
			break;
		case 17: 
			if (x->class == 8 || x->class == 9) {
				OPB_err(126);
			}
			if (x->typ->form == 13) {
				OPB_DeRef(&x);
			}
			if (!__IN(x->typ->comp, 0x3c, 32)) {
				OPB_err(131);
			}
			break;
		case 18: 
			if ((x->class == 7 && f == 3)) {
				OPB_CharToString(x);
				f = 10;
			}
			if (x->typ->form == 13) {
				OPB_DeRef(&x);
			}
			if (x->class == 8 || x->class == 9) {
				OPB_err(126);
			} else if (((!__IN(x->typ->comp, 0x3c, 32) || x->typ->BaseTyp->form != 3) && f != 10)) {
				OPB_err(111);
			}
			break;
		case 19: 
			if (x->class == 8 || x->class == 9) {
				OPB_err(126);
			} else if (__IN(f, 0x70, 32)) {
				if (f != 6) {
					OPB_Convert(&x, OPT_linttyp);
				}
			} else {
				OPB_err(111);
				x->typ = OPT_linttyp;
			}
			break;
		case 20: 
			OPB_CheckLeaf(x, 0);
			if ((x->obj != NIL && x->obj->mode == 13)) {
				OPB_err(126);
			} else {
				OPB_MOp(24, &x);
			}
			break;
		case 12: 
			if ((f == 13 && __IN(x->typ->BaseTyp->comp, 0x34, 32))) {
				OPB_err(111);
			} else if (x->typ->comp == 4) {
				OPB_err(111);
			}
			if (x->class != 8) {
				OPB_err(110);
				x = OPB_NewIntConst(1);
			} else if ((__IN(f, 0x0163fe, 32) || x->typ->comp == 6) || x->typ->comp == 2) {
				(*OPB_typSize)(x->typ, 0);
				OPT_MarkType(x->typ);
				x = OPB_NewIntConst(x->typ->size);
			} else {
				OPB_err(111);
				x = OPB_NewIntConst(1);
			}
			break;
		case 21: 
			OPB_MOp(25, &x);
			break;
		case 22: case 23: 
			if (x->class == 8 || x->class == 9) {
				OPB_err(126);
			} else if (!__IN(f, 0x027a, 32)) {
				OPB_err(111);
			}
			break;
		case 24: case 25: case 28: case 31: case 38: 
		case 39: case 40: case 41: case 42: case 43: 
			if (x->class == 8 || x->class == 9) {
				OPB_err(126);
			} else if ((x->class == 7 && __IN(f, 0x30, 32))) {
				OPB_Convert(&x, OPT_linttyp);
			} else if ((f == 13 && __IN(x->typ->BaseTyp->comp, 0x34, 32))) {
				OPB_err(111);
				x->typ = OPT_linttyp;
			} else if (!__IN(f, 0x2040, 32)) {
				OPB_err(111);
				x->typ = OPT_linttyp;
			}
			if ((38 <= fctno && fctno <= 40)) {
				OPB_MOp((INT8)((fctno - 38) + 30), &x);
			}
			break;
		case 26: case 27: 
			if ((__IN(f, 0x70, 32) && x->class == 7)) {
				if (x->conval->intval < 0 || x->conval->intval > 31) {
					OPB_err(220);
				}
			} else {
				OPB_err(69);
			}
			break;
		case 29: 
			if (x->class != 8) {
				OPB_err(110);
			} else if (__IN(f, 0x1401, 32) || __IN(x->typ->comp, 0x28, 32)) {
				OPB_err(111);
			}
			break;
		case 30: 
			if (OPB_NotVar(x)) {
				OPB_err(112);
			} else if (f == 13) {
			} else {
				OPB_err(111);
			}
			break;
		case 32: 
			if (x->class == 8 || x->class == 9) {
				OPB_err(126);
				x = OPB_NewBoolConst(0);
			} else if (f != 2) {
				OPB_err(120);
				x = OPB_NewBoolConst(0);
			} else {
				OPB_MOp(33, &x);
			}
			break;
		case 35: case 36: 
			if (x->class == 8 || x->class == 9) {
				OPB_err(126);
			} else if ((x->class == 7 && f == 6)) {
				if (x->conval->intval < 0 || x->conval->intval > 65535) {
					OPM_err(203);
				}
				x->typ = OPT_inttyp;
			} else if (__IN(f, 0x50, 32)) {
				OPB_Convert(&x, OPT_inttyp);
			} else if (__IN(f, 0x20, 32)) {
			} else {
				OPB_err(111);
				x->typ = OPT_inttyp;
			}
			break;
		case 64: 
			if (f != 2) {
				OPB_err(120);
			}
			break;
		default: 
			OPB_err(64);
			break;
	}
	*par0 = x;
}

static struct StPar1__58 {
	struct StPar1__58 *lnk;
} *StPar1__58_s;

static OPT_Node NewOp__59 (INT8 class, INT8 subcl, OPT_Node left, OPT_Node right);

static OPT_Node NewOp__59 (INT8 class, INT8 subcl, OPT_Node left, OPT_Node right)
{
	OPT_Node node;
	node = OPT_NewNode(class);
	node->subcl = subcl;
	node->left = left;
	node->right = right;
	return node;
}

void OPB_StPar1 (OPT_Node *par0, OPT_Node x, INT8 fctno)
{
	INT16 f, L;
	OPT_Struct typ;
	OPT_Node p, t;
	INT32 i;
	struct StPar1__58 _s;
	_s.lnk = StPar1__58_s;
	StPar1__58_s = &_s;
	p = *par0;
	f = x->typ->form;
	switch (fctno) {
		case 13: case 14: 
			if (x->class == 8 || x->class == 9) {
				OPB_err(126);
				p->typ = OPT_notyp;
			} else {
				if (x->typ != p->typ) {
					if ((__IN(f, 0x70, 32) && f < (INT16)p->typ->form)) {
						OPB_Convert(&x, p->typ);
					} else {
						OPB_err(111);
					}
				}
				p = NewOp__59(19, fctno, p, x);
				p->typ = OPT_notyp;
			}
			break;
		case 15: case 16: 
			if (x->class == 8 || x->class == 9) {
				OPB_err(126);
			} else if (__IN(f, 0x70, 32)) {
				if ((x->class == 7 && (0 > x->conval->intval || x->conval->intval > 31))) {
					OPB_err(202);
				}
				p = NewOp__59(19, fctno, p, x);
			} else {
				OPB_err(111);
			}
			p->typ = OPT_notyp;
			break;
		case 17: 
			if (!__IN(f, 0x70, 32) || x->class != 7) {
				OPB_err(69);
			} else if (f == 4) {
				L = (INT16)x->conval->intval;
				typ = p->typ;
				while ((L > 0 && __IN(typ->comp, 0x3c, 32))) {
					typ = typ->BaseTyp;
					L -= 1;
				}
				if (L != 0 || !__IN(typ->comp, 0x3c, 32)) {
					OPB_err(132);
				} else {
					x->obj = NIL;
					if (__IN(typ->comp, 0x30, 32)) {
						while (p->class == 4) {
							p = p->left;
							x->conval->intval += 1;
						}
						p = NewOp__59(12, 19, p, x);
						p->typ = OPT_linttyp;
					} else if (typ->comp == 3) {
						p = OPB_NewLeaf(typ->link);
						p->typ = OPT_linttyp;
					} else {
						p = x;
						p->conval->intval = typ->n;
						OPB_SetIntType(p);
					}
				}
			} else {
				OPB_err(132);
			}
			break;
		case 18: 
			if (x->typ->form == 13) {
				OPB_DeRef(&x);
			}
			if (OPB_NotVar(x)) {
				OPB_err(112);
			} else if ((__IN(x->typ->comp, 0x3c, 32) && x->typ->BaseTyp->form == 3)) {
				if (x->readonly) {
					OPB_err(76);
				}
				t = x;
				x = p;
				p = t;
				p = NewOp__59(19, 18, p, x);
			} else {
				OPB_err(111);
			}
			p->typ = OPT_notyp;
			break;
		case 19: 
			if (x->class == 8 || x->class == 9) {
				OPB_err(126);
			} else if (__IN(f, 0x70, 32)) {
				if ((p->class == 7 && x->class == 7)) {
					if (-OPB_maxExp > x->conval->intval || x->conval->intval > OPB_maxExp) {
						OPB_err(208);
						p->conval->intval = 1;
					} else if (x->conval->intval >= 0) {
						if (__ABS(p->conval->intval) <= __DIV(2147483647, __ASH(1, x->conval->intval))) {
							p->conval->intval = p->conval->intval * __ASH(1, x->conval->intval);
						} else {
							OPB_err(208);
							p->conval->intval = 1;
						}
					} else {
						p->conval->intval = __ASH(p->conval->intval, x->conval->intval);
					}
					p->obj = NIL;
				} else if ((x->class == 7 && x->conval->intval == 0)) {
				} else {
					p = NewOp__59(12, 17, p, x);
					p->typ = OPT_linttyp;
				}
			} else {
				OPB_err(111);
			}
			break;
		case 1: 
			if (OPB_InitPar != NIL) {
				OPB_Param(&x, OPB_InitPar);
				OPB_InitPar = OPB_InitPar->link;
				x->link = p->left->link;
				p->left->link = x;
			} else if (x->class == 8 || x->class == 9) {
				OPB_err(126);
			} else if (__IN(p->typ->comp, 0x30, 32)) {
				if (__IN(f, 0x70, 32)) {
					if ((x->class == 7 && (x->conval->intval < 0 || x->conval->intval > 2147483647))) {
						OPB_err(63);
					}
				} else {
					OPB_err(111);
				}
				p->right = x;
				p->typ = p->typ->BaseTyp;
			} else {
				OPB_err(64);
			}
			break;
		case 22: case 23: 
			if (x->class == 8 || x->class == 9) {
				OPB_err(126);
			} else if (!__IN(f, 0x70, 32)) {
				OPB_err(111);
			} else {
				if (fctno == 22) {
					p = NewOp__59(12, 27, p, x);
				} else {
					p = NewOp__59(12, 28, p, x);
				}
				p->typ = p->left->typ;
			}
			break;
		case 24: case 25: case 35: case 36: 
			if (x->class == 8 || x->class == 9) {
				OPB_err(126);
			} else if (__IN(f, 0x6bff, 32)) {
				if ((fctno == 24 || fctno == 26) || fctno == 36) {
					if (OPB_NotVar(x)) {
						OPB_err(112);
					}
					t = x;
					x = p;
					p = t;
				} else if (x->class == 7) {
					OPB_err(-306);
				}
				p = NewOp__59(19, fctno, p, x);
			} else {
				OPB_err(111);
			}
			p->typ = OPT_notyp;
			break;
		case 41: 
			if (x->class == 8 || x->class == 9) {
				OPB_err(126);
			} else if (__IN(f, 0x7f, 32)) {
				if (__IN(f, 0x60, 32)) {
					OPB_Val(&x, OPT_sinttyp);
				}
				p = NewOp__59(19, 25, p, x);
			} else {
				OPB_err(111);
			}
			p->typ = OPT_notyp;
			break;
		case 42: 
			if (x->class == 8 || x->class == 9) {
				OPB_err(126);
			} else if (__IN(f, 0x71, 32)) {
				if (__IN(f, 0x50, 32)) {
					OPB_Convert(&x, OPT_inttyp);
				}
				p = NewOp__59(19, 25, p, x);
			} else {
				OPB_err(111);
			}
			p->typ = OPT_notyp;
			break;
		case 43: 
			if (x->class == 8 || x->class == 9) {
				OPB_err(126);
			} else if (__IN(f, 0x6a71, 32)) {
				if (__IN(f, 0x30, 32)) {
					OPB_Convert(&x, OPT_linttyp);
				}
				p = NewOp__59(19, 25, p, x);
			} else {
				OPB_err(111);
			}
			p->typ = OPT_notyp;
			break;
		case 26: case 27: 
			if (p->conval != NIL) {
				i = p->conval->intval;
				p->conval->intval = __MASK(i, -8);
			}
			if (x->class == 8 || x->class == 9) {
				OPB_err(126);
			} else if ((((0 <= i && i < 8)) && !__IN(f, 0x6aff, 32))) {
				OPB_err(111);
			} else if ((((8 <= i && i < 16)) && !__IN(f, 0x62c0, 32))) {
				OPB_err(111);
			} else if ((((16 <= i && i < 24)) && !__IN(f, 0x20, 32))) {
				OPB_err(111);
			} else if ((((24 <= i && i < 32)) && !__IN(f, 0x1e, 32))) {
				OPB_err(111);
			} else {
				if (fctno == 26) {
					if (OPB_NotVar(x)) {
						OPB_err(112);
					}
					t = x;
					x = p;
					p = t;
				} else if ((((0 <= i && i < 8)) && x->class == 7)) {
					OPB_err(-306);
				}
				p = NewOp__59(19, fctno, p, x);
			}
			p->typ = OPT_notyp;
			break;
		case 28: 
			if (x->class == 8 || x->class == 9) {
				OPB_err(126);
			} else if (__IN(f, 0x70, 32)) {
				p = NewOp__59(12, 26, p, x);
			} else {
				OPB_err(111);
			}
			p->typ = OPT_booltyp;
			break;
		case 29: 
			OPB_Val(&x, p->typ);
			p = x;
			break;
		case 30: 
			if ((p->typ->form == 13 && __IN(p->typ->BaseTyp->comp, 0x3c, 32))) {
				OPB_err(111);
			} else if (x->class == 8 || x->class == 9) {
				OPB_err(126);
			} else if (__IN(f, 0x70, 32)) {
				p = NewOp__59(19, 30, p, x);
			} else {
				OPB_err(111);
			}
			p->typ = OPT_notyp;
			break;
		case 31: 
			if (x->class == 8 || x->class == 9) {
				OPB_err(126);
			} else if ((x->class == 7 && __IN(f, 0x30, 32))) {
				OPB_Convert(&x, OPT_linttyp);
			} else if (!__IN(f, 0x2040, 32)) {
				OPB_err(111);
				x->typ = OPT_linttyp;
			}
			p->link = x;
			break;
		case 32: 
			if ((__IN(f, 0x70, 32) && x->class == 7)) {
				if ((20 <= x->conval->intval && x->conval->intval <= 2147483647)) {
					OPB_BindNodes(28, OPT_notyp, &x, x);
					x->conval = OPT_NewConst();
					x->conval->intval = OPM_errpos;
					OPB_Construct(15, &p, x);
					p->conval = OPT_NewConst();
					p->conval->intval = OPM_errpos;
					OPB_Construct(20, &p, NIL);
					OPB_OptIf(&p);
					if (p == NIL) {
					} else if (p->class == 28) {
						OPB_err(99);
					} else {
						p->subcl = 32;
					}
				} else {
					OPB_err(218);
				}
			} else {
				OPB_err(69);
			}
			break;
		default: 
			OPB_err(64);
			break;
	}
	*par0 = p;
	StPar1__58_s = _s.lnk;
}

void OPB_StParN (OPT_Node *par0, OPT_Node x, INT16 fctno, INT16 n)
{
	OPT_Node node;
	INT16 f;
	OPT_Node p;
	p = *par0;
	f = x->typ->form;
	if (fctno == 1) {
		if (OPB_InitPar != NIL) {
			OPB_Param(&x, OPB_InitPar);
			OPB_InitPar = OPB_InitPar->link;
			x->link = p->left->link;
			p->left->link = x;
		} else if (!__IN(p->typ->comp, 0x30, 32)) {
			OPB_err(64);
		} else if (x->class == 8 || x->class == 9) {
			OPB_err(126);
		} else if (__IN(f, 0x70, 32)) {
			if ((x->class == 7 && (x->conval->intval < 0 || x->conval->intval > 2147483647))) {
				OPB_err(63);
			}
			node = p->right;
			while (node->link != NIL) {
				node = node->link;
			}
			node->link = x;
			p->typ = p->typ->BaseTyp;
		} else {
			OPB_err(111);
		}
	} else if ((fctno == 31 && n == 2)) {
		if (x->class == 8 || x->class == 9) {
			OPB_err(126);
		} else if (__IN(f, 0x70, 32)) {
			node = OPT_NewNode(19);
			node->subcl = 31;
			node->right = p;
			node->left = p->link;
			p->link = x;
			p = node;
		} else {
			OPB_err(111);
		}
		p->typ = OPT_notyp;
	} else {
		OPB_err(64);
	}
	*par0 = p;
}

void OPB_StFct (OPT_Node *par0, INT8 fctno, INT16 parno)
{
	INT16 dim;
	OPT_Node x, p, r;
	OPT_Object obj;
	OPT_Struct typ;
	p = *par0;
	if (fctno <= 19 || fctno == 37) {
		if (fctno == 1) {
			if (parno < 1) {
				OPB_err(65);
			} else if (p->typ != OPT_notyp) {
				if (__IN(p->typ->comp, 0x30, 32)) {
					OPB_err(65);
				}
				p->typ = OPT_notyp;
			} else {
				if (OPB_InitPar != NIL) {
					OPB_InitPar = NIL;
					OPB_err(65);
				}
				x = NIL;
				if (p->left == NIL) {
					return;
				}
				if (p->left->link != NIL) {
					p = p->left->link;
					while (p != NIL) {
						r = p->link;
						p->link = x;
						x = p;
						p = r;
					}
					r = x->link;
					x->link = NIL;
					OPB_BindNodes(13, OPT_notyp, &x, r);
					x->obj = x->left->obj->link;
					p = *par0;
					p->left->link = x;
				}
				if ((((p->left != NIL && p->left->typ != NIL)) && p->left->typ->BaseTyp != NIL)) {
					typ = p->left->typ->BaseTyp;
				}
				r = NIL;
				while ((typ != NIL && typ->comp == 6)) {
					if ((typ->strobj != NIL && __IN(1, typ->strobj->conval->setval, 32))) {
						x = NIL;
						OPB_Construct(9, &x, NIL);
						x->obj = typ->strobj;
						x->link = r;
						r = x;
					}
					typ = typ->BaseTyp;
				}
				p->right = r;
			}
		} else if (fctno <= 12 || fctno == 37) {
			if (parno < 1) {
				OPB_err(65);
			}
		} else {
			if (((fctno == 13 || fctno == 14) && parno == 1)) {
				OPB_BindNodes(19, OPT_notyp, &p, OPB_NewIntConst(1));
				p->subcl = fctno;
				p->right->typ = p->left->typ;
			} else if ((fctno == 17 && parno == 1)) {
				if (__IN(p->typ->comp, 0x30, 32)) {
					dim = 0;
					while (p->class == 4) {
						p = p->left;
						dim += 1;
					}
					OPB_BindNodes(12, OPT_linttyp, &p, OPB_NewIntConst(dim));
					p->subcl = 19;
				} else if (p->typ->comp == 3) {
					p = OPB_NewLeaf(p->typ->link);
					p->typ = OPT_linttyp;
				} else {
					p = OPB_NewIntConst(p->typ->n);
				}
			} else if (parno < 2) {
				OPB_err(65);
			}
		}
	} else if (fctno == 64) {
		x = p;
		OPB_BindNodes(19, OPT_notyp, &x, x->link);
		x->left->link = NIL;
		x->subcl = 64;
		x->conval = OPT_NewConst();
		x->conval->intval = OPM_errpos;
		OPB_PrepCall(&p, &obj);
		OPB_Call(&p, NIL, obj);
		OPB_MOp(33, &p);
		OPB_Construct(15, &p, x);
		p->conval = OPT_NewConst();
		p->conval->intval = OPM_errpos;
		OPB_Construct(20, &p, NIL);
		OPB_OptIf(&p);
	} else if (fctno == 32) {
		if (parno == 1) {
			x = NIL;
			OPB_BindNodes(28, OPT_notyp, &x, OPB_NewIntConst(8));
			x->conval = OPT_NewConst();
			x->conval->intval = OPM_errpos;
			OPB_Construct(15, &p, x);
			p->conval = OPT_NewConst();
			p->conval->intval = OPM_errpos;
			OPB_Construct(20, &p, NIL);
			OPB_OptIf(&p);
			if (p == NIL) {
			} else if (p->class == 28) {
				OPB_err(99);
			} else {
				p->subcl = 32;
			}
		} else if (parno < 1) {
			OPB_err(65);
		}
	} else {
		if (fctno == 33 || fctno == 34) {
			p = NIL;
			OPB_Construct(19, &p, NIL);
			p->subcl = fctno;
		} else if (((((fctno != 33 && fctno != 34)) && parno < 1) || (((((((fctno != 33 && fctno != 34)) && fctno > 21)) && fctno < 38)) && parno < 2)) || (fctno == 31 && parno < 3)) {
			OPB_err(65);
		}
	}
	*par0 = p;
}

static void OPB_OpenArrParCheck (OPT_Struct ftyp, OPT_Struct atyp, BOOLEAN fvarpar)
{
	INT16 f;
	f = atyp->comp;
	ftyp = ftyp->BaseTyp;
	atyp = atyp->BaseTyp;
	if (ftyp == OPT_bytetyp) {
		if (!__IN(f, 0x3c, 32) || !__IN(atyp->form, 0x1e, 32)) {
			OPB_err(-301);
		}
	} else if (__IN(f, 0x3c, 32)) {
		if (ftyp->comp == 5) {
			OPB_OpenArrParCheck(ftyp, atyp, fvarpar);
		} else if (ftyp != atyp) {
			if ((ftyp->form == 13 && atyp->form == 13)) {
				ftyp = ftyp->BaseTyp;
				atyp = atyp->BaseTyp;
				if ((ftyp->comp == 5 && __IN(atyp->comp, 0x3c, 32))) {
					OPB_OpenArrParCheck(ftyp, atyp, fvarpar);
				} else if ((((!fvarpar && ftyp->comp == 6)) && atyp->comp == 6)) {
					while ((((ftyp != atyp && atyp != NIL)) && atyp != OPT_undftyp)) {
						atyp = atyp->BaseTyp;
					}
					if (atyp == NIL) {
						OPB_err(113);
					}
				} else {
					OPB_err(66);
				}
			} else {
				OPB_err(66);
			}
		}
	} else {
		OPB_err(67);
	}
}

static void OPB_CheckReceiver (OPT_Node *x, OPT_Object fp)
{
	if (fp->typ->form == 13) {
		if ((*x)->class == 3) {
			*x = (*x)->left;
		} else if ((*x)->typ->form != 13) {
			OPB_err(71);
		}
	}
}

void OPB_PrepCall (OPT_Node *x, OPT_Object *fpar)
{
	if (((*x)->obj != NIL && __IN((*x)->obj->mode, 0x22c0, 32))) {
		*fpar = (*x)->obj->link;
		if ((*x)->obj->mode == 13) {
			OPB_CheckReceiver(&(*x)->left, *fpar);
			*fpar = (*fpar)->link;
		}
	} else if (((((*x)->class != 8 && (*x)->typ != NIL)) && (*x)->typ->form == 14)) {
		*fpar = (*x)->typ->link;
	} else {
		OPB_err(121);
		*fpar = NIL;
		(*x)->typ = OPT_undftyp;
	}
}

void OPB_Param (OPT_Node *ap, OPT_Object fp)
{
	OPT_Struct q;
	if (fp->typ->form != 0) {
		if ((fp->typ->sysflag == 0 && (*ap)->typ->sysflag == 1)) {
			OPB_err(59);
		}
		if ((((fp->typ->comp == 5 && fp->typ->BaseTyp == OPT_bytetyp)) && (*ap)->typ->form == 13)) {
			OPB_err(113);
		} else if (((*ap)->typ->form == 11 && OPT_SYSimported)) {
			if (((fp->typ->form == 13 || fp->typ->form == 14) || fp->mode == 2) || fp->typ->sysflag == 1) {
			} else {
				OPB_err(113);
			}
		} else if (fp->mode == 2) {
			if (OPB_NotVar(*ap)) {
				OPB_err(122);
			} else {
				OPB_CheckLeaf(*ap, 0);
			}
			if ((*ap)->readonly) {
				OPB_err(76);
			}
			if (fp->typ->comp == 5) {
				OPB_OpenArrParCheck(fp->typ, (*ap)->typ, 1);
			} else if ((fp->typ->comp == 6 && (*ap)->typ->comp == 6)) {
				q = (*ap)->typ;
				OPT_MarkType(q);
				while ((((q != fp->typ && q != NIL)) && q != OPT_undftyp)) {
					q = q->BaseTyp;
				}
				if (q == NIL) {
					OPB_err(111);
				}
			} else if (((*ap)->typ != fp->typ && !((fp->typ->form == 1 && __IN((*ap)->typ->form, 0x18, 32))))) {
				OPB_err(123);
			} else if ((fp->typ->form == 13 && (*ap)->class == 5)) {
				OPB_err(123);
			}
		} else if (fp->typ->comp == 5) {
			if (((*ap)->class == 7 && (*ap)->typ->form == 3)) {
				OPB_CharToString(*ap);
			}
			if (((*ap)->typ->form == 10 && fp->typ->BaseTyp->form == 3)) {
			} else if (((*ap)->class >= 7 && (*ap)->class != 13)) {
				OPB_err(59);
			} else {
				OPB_OpenArrParCheck(fp->typ, (*ap)->typ, 0);
			}
		} else {
			OPB_CheckAssign(fp->typ, *ap);
		}
	}
}

void OPB_StaticLink (INT8 dlev)
{
	OPT_Object scope;
	scope = OPT_topScope;
	while (dlev > 0) {
		dlev -= 1;
		scope->link->conval->setval |= __SETOF(3,32);
		scope = scope->left;
	}
}

void OPB_Call (OPT_Node *x, OPT_Node apar, OPT_Object fp)
{
	OPT_Struct typ;
	OPT_Node p;
	INT8 lev;
	if ((*x)->class == 9) {
		typ = (*x)->typ;
		lev = (*x)->obj->mnolev;
		if (lev > 0) {
			OPB_StaticLink(OPT_topScope->mnolev - lev);
		}
		if ((*x)->obj->mode == 10) {
			OPB_err(121);
		}
	} else if (((*x)->class == 2 && (*x)->obj->mode == 13)) {
		typ = (*x)->typ;
		(*x)->class = 9;
		p = (*x)->left;
		(*x)->left = NIL;
		p->link = apar;
		apar = p;
		fp = (*x)->obj->link;
	} else {
		typ = (*x)->typ->BaseTyp;
	}
	OPB_BindNodes(13, typ, &*x, apar);
	(*x)->obj = fp;
	(*x)->subcl = 0;
}

void OPB_CopyAndSubst (OPT_Node *new, OPT_Node old)
{
	if (old == NIL) {
		*new = NIL;
		return;
	} else if ((((old->obj != NIL && old->obj->link2 != NIL)) && (old->obj->mode == 1 || old->obj->mode == 2))) {
		*new = OPB_NewLeaf(old->obj->link2);
		(*new)->conval = old->conval;
		if (((*new)->class == 31 && old->obj->link2->mnolev <= 0)) {
			OPB_err(261);
		}
	} else {
		*new = OPT_NewNode(old->class);
		__GUARDEQP(*new, OPT_NodeDesc) = *old;
	}
	if ((old->class == 29 && old->conval->intval == 0)) {
		(*new)->conval = OPT_NewConst();
		__GUARDEQP((*new)->conval, OPT_ConstDesc) = *old->conval;
		(*new)->conval->intval = OPM_errpos;
	}
	OPB_CopyAndSubst(&(*new)->left, old->left);
	OPB_CopyAndSubst(&(*new)->right, old->right);
	OPB_CopyAndSubst(&(*new)->link, old->link);
}

void OPB_Lock (OPT_Node *x, OPT_Object self, BOOLEAN excl)
{
	OPT_Node n;
	if (self != NIL) {
		OPB_BindNodes(19, OPT_notyp, &*x, OPB_NewLeaf(self));
		(*x)->subcl = 66;
		(*x)->obj = self;
		n = OPB_NewBoolConst(excl);
		(*x)->right->link = n;
	}
}

void OPB_Enter (OPT_Node *procdec, OPT_Node stat, OPT_Object proc)
{
	OPT_Node x;
	x = OPT_NewNode(18);
	x->typ = OPT_notyp;
	x->obj = proc;
	x->left = *procdec;
	x->right = stat;
	OPB_InitAppend(&x->right);
	*procdec = x;
}

void OPB_Return (OPT_Node *x, OPT_Object proc)
{
	OPT_Node node;
	if (proc == NIL) {
		if (*x != NIL) {
			OPB_err(124);
		}
	} else {
		if (*x != NIL) {
			if (proc->typ->comp == 5) {
				if ((*x)->typ->form == 13) {
					OPB_DeRef(&*x);
				}
				if (((*x)->class == 7 && (*x)->typ->form == 3)) {
					OPB_CharToString(*x);
				}
				if (((*x)->typ->form == 10 && proc->typ->BaseTyp->form == 3)) {
				} else if (((*x)->class >= 7 && (*x)->class != 13)) {
					OPB_err(59);
				} else {
					OPB_OpenArrParCheck(proc->typ, (*x)->typ, 0);
				}
			} else {
				OPB_CheckAssign(proc->typ, *x);
			}
		} else if (proc->typ != OPT_notyp) {
			OPB_err(124);
		}
	}
	node = OPT_NewNode(26);
	node->typ = OPT_notyp;
	node->obj = proc;
	node->left = *x;
	*x = node;
}

void OPB_Assign (OPT_Node *x, OPT_Node y)
{
	OPT_Node z;
	BOOLEAN struct_;
	struct_ = (*x)->typ->form == 15;
	if ((*x)->class >= 7) {
		OPB_err(56);
	}
	OPB_CheckAssign((*x)->typ, y);
	if ((*x)->readonly) {
		OPB_err(76);
	}
	OPT_MarkType((*x)->typ);
	if ((*x)->typ->comp == 6) {
		if ((*x)->class == 5) {
			z = (*x)->left;
		} else {
			z = *x;
		}
		if ((z->class == 3 && z->left->class == 5)) {
			z->left = z->left->left;
		}
		if (((*x)->typ->strobj != NIL && (z->class == 3 || z->class == 1))) {
			if ((*x)->typ->sysflag != 1) {
				OPB_BindNodes(6, (*x)->typ, &z, NIL);
			}
			*x = z;
		}
	} else if ((((((__IN((*x)->typ->comp, 0x0c, 32) && (*x)->typ->BaseTyp == OPT_chartyp)) && y->typ->form == 10)) && y->conval->intval2 == 1)) {
		y->typ = OPT_chartyp;
		y->conval->intval = 0;
		OPB_Index(&*x, OPB_NewIntConst(0));
	}
	OPB_BindNodes(19, OPT_notyp, &*x, y);
	(*x)->subcl = 0;
	if ((struct_ && y->class == 13)) {
		y->subcl = 1;
	}
}

void OPB_Inittd (OPT_Node *inittd, OPT_Node *last, OPT_Struct typ)
{
	OPT_Node node;
	node = OPT_NewNode(14);
	node->typ = typ;
	node->conval = OPT_NewConst();
	node->conval->intval = typ->txtpos;
	if (*inittd == NIL) {
		*inittd = node;
	} else {
		(*last)->link = node;
	}
	*last = node;
}

static void EnumPtrs(void (*P)(void*))
{
	P(OPB_InitPar);
}


export void *OPB__init(void)
{
	__DEFMOD;
	__MODULE_IMPORT(OPM);
	__MODULE_IMPORT(OPS);
	__MODULE_IMPORT(OPT);
	__REGMOD("OPB", EnumPtrs);
/* BEGIN */
	OPB_maxExp = OPB_log(1073741824);
	OPB_maxExp = OPB_exp;
	OPB_verify = NIL;
	__ENDMOD;
}
