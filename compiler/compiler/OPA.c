/* voc 2.1.0 [2017/09/06]. Bootstrapping compiler for address size 8, alignment 8. xtaSv */

#define SHORTINT INT8
#define INTEGER  INT16
#define LONGINT  INT32
#define SET      UINT32

#include "SYSTEM.h"
#include "Files.h"
#include "OPB.h"
#include "OPM.h"
#include "OPS.h"
#include "OPT.h"

struct OPA__1 {
	OPS_Name name;
	UINT32 flag;
};

typedef
	struct OPA_FixPntDesc *OPA_FixPnt;

typedef
	struct OPA_FixPntDesc {
		INT32 pc;
		OPT_Node node;
		INT32 pos;
		OPA_FixPnt next;
	} OPA_FixPntDesc;

typedef
	CHAR OPA_Mnemo[12];

typedef
	struct OPA_InstrDesc {
		OPA_Mnemo name;
		INT16 start, end;
		UINT32 target;
	} OPA_InstrDesc;

typedef
	struct OPA_ObjDesc *OPA_Object;

typedef
	struct OPA_ObjDesc {
		INT32 typ, val, size;
		OPS_Name name;
		OPA_Object left, right, next;
		OPA_FixPnt fix;
		OPT_Object obj;
	} OPA_ObjDesc;

typedef
	struct OPA_OpCode {
		INT16 op[3];
		INT16 op0, op1, opc, reg;
	} OPA_OpCode;

typedef
	struct OPA_Operand {
		INT32 mode, imm, disp;
		INT16 index, base, reg, seg, scale;
		OPA_Object obj;
	} OPA_Operand;


static OPA_Object OPA_root;
static struct {
	ADDRESS len[1];
	OPA_OpCode data[1];
} *OPA_OpTab;
static INT32 OPA_OpTabLen;
static struct {
	ADDRESS len[1];
	OPA_InstrDesc data[1];
} *OPA_InstrTab;
static INT32 OPA_InstrTabLen;
static INT8 OPA_SizeTab[17];
static struct OPA__1 OPA_TargetTab[32];
static INT32 OPA_TargetCount;
static BOOLEAN OPA_export, OPA_inline, OPA_FirstTime;
static UINT32 OPA_Target;
static INT32 OPA_pc, OPA_sym;
static OPS_Name OPA_ident;
static INT32 OPA_val;
static CHAR OPA_str[256];
static INT32 OPA_errpos;
static OPT_Node OPA_first, OPA_last, OPA_fixlist;

export ADDRESS *OPA_InstrDesc__typ;
export ADDRESS *OPA_OpCode__typ;
export ADDRESS *OPA_Operand__typ;
export ADDRESS *OPA_ObjDesc__typ;
export ADDRESS *OPA_FixPntDesc__typ;
export ADDRESS *OPA__1__typ;

static INT32 OPA_AND (INT32 a, INT32 b);
export void OPA_Assemble (OPT_Node *x, BOOLEAN exported, BOOLEAN inlined);
static void OPA_BodyInit (void);
static void OPA_Check (INT32 s);
static void OPA_CheckLabels (void);
static void OPA_Close (void);
static INT16 OPA_ConstSize (INT32 i, BOOLEAN signed_);
static OPA_Object OPA_ConvertObj (OPT_Object ob);
static INT32 OPA_Evaluate (OPA_Operand *op, ADDRESS *op__typ, INT32 mode);
static void OPA_Expression (INT32 *x);
static void OPA_FindInstruction (CHAR *name, ADDRESS name__len, INT32 *inx);
static void OPA_FixDisp (OPA_FixPnt *fix);
static void OPA_GenCode (INT32 ind, OPA_Operand *op, ADDRESS op__len);
static void OPA_Get (INT32 *sym);
static void OPA_GetBaseIndex (OPA_Operand *o, ADDRESS *o__typ, INT32 size);
static void OPA_GetIdent (OPS_Name name);
static void OPA_GetOperand (OPA_Operand *o, ADDRESS *o__typ);
static void OPA_HashFn (CHAR *name, ADDRESS name__len, INT32 *k, INT32 *n);
static void OPA_Init (void);
static void OPA_InsertFix (OPA_Object *obj, INT32 pc);
static void OPA_InsertReg (CHAR *name, ADDRESS name__len, INT32 t, INT32 v);
static void OPA_InsertTarget (CHAR *name, ADDRESS name__len, UINT32 flag);
static void OPA_InsertType (CHAR *name, ADDRESS name__len, INT32 s);
static BOOLEAN OPA_IsFRegMode (INT32 m, BOOLEAN strict);
static BOOLEAN OPA_IsImmMode (INT32 m);
static BOOLEAN OPA_IsMMMode (INT32 m);
static BOOLEAN OPA_IsMMode (INT32 m);
static BOOLEAN OPA_IsRMMode (INT32 m);
static BOOLEAN OPA_IsRegMode (INT32 m, BOOLEAN strict);
static BOOLEAN OPA_IsRegister (INT32 mode);
static BOOLEAN OPA_IsRelMode (INT32 m);
static BOOLEAN OPA_IsSRegMode (INT32 m, BOOLEAN strict);
static BOOLEAN OPA_IsSpecRegMode (INT32 m);
static INT32 OPA_Match (INT32 ind, OPA_Operand *op, ADDRESS op__len);
static void OPA_ModRM (INT32 *modrm, OPA_Operand *op, ADDRESS *op__typ, INT32 mode, INT32 regpos, BOOLEAN UseSpecReg);
static INT32 OPA_ModeSize (INT32 mode);
static BOOLEAN OPA_NeedModRM (INT32 mode, INT32 regpos);
static void OPA_NewNode (void);
static void OPA_ParseInstruction (void);
static void OPA_ParseLabel (void);
static void OPA_ParseTarget (void);
static void OPA_PutByte (INT32 b);
static void OPA_PutBytes (INT32 b, INT32 size);
static void OPA_Qualident (OPA_Object *obj);
static INT8 OPA_SIB (OPA_Operand op);
static void OPA_find (OPS_Name name, OPA_Object *obj);
static void OPA_insert (CHAR *name, ADDRESS name__len, OPA_Object *obj);
static void OPA_skipBlanks (void);


static INT32 OPA_AND (INT32 a, INT32 b)
{
	return (INT32)(((UINT32)a & (UINT32)b));
}

static INT32 OPA_ModeSize (INT32 mode)
{
	switch (mode) {
		case 48: case 51: case 52: case 96: case 9: 
		case 19: case 8: case 65: case 73: case 53: 
			return 1;
			break;
		case 49: case 97: case 17: case 18: case 16: 
		case 66: case 74: case 80: case 81: case 82: 
		case 83: case 84: case 85: case 86: 
			return 2;
			break;
		case 50: case 98: case 99: case 33: case 32: 
		case 67: case 75: case 69: 
			return 4;
			break;
		case 76: case 40: case 70: 
			return 8;
			break;
		case 77: 
			return 10;
			break;
		case 64: case 68: 
			return 0;
			break;
		default: 
			return 0;
			break;
	}
	__RETCHK;
}

static INT16 OPA_ConstSize (INT32 i, BOOLEAN signed_)
{
	if ((-128 <= i && 127 >= i) || (!signed_ && OPA_AND(i, 4294967040LL) == 0)) {
		return 1;
	} else if (((-32767-1) <= i && 32767 >= i) || (!signed_ && OPA_AND(i, 4294901760LL) == 0)) {
		return 2;
	} else {
		return 4;
	}
	__RETCHK;
}

static BOOLEAN OPA_IsRegMode (INT32 m, BOOLEAN strict)
{
	return ((m == 8 || m == 16) || m == 32) || (!strict && (((m == 9 || m == 17) || m == 33) || m == 18));
}

static BOOLEAN OPA_IsSRegMode (INT32 m, BOOLEAN strict)
{
	return m == 80 || ((((((!strict && m == 81) || m == 82) || m == 83) || m == 84) || m == 85) || m == 86);
}

static BOOLEAN OPA_IsSpecRegMode (INT32 m)
{
	return (m == 112 || m == 113) || m == 114;
}

static BOOLEAN OPA_IsMMode (INT32 m)
{
	return ((((m == 72 || m == 73) || m == 74) || m == 75) || m == 76) || m == 77;
}

static BOOLEAN OPA_IsRMMode (INT32 m)
{
	return ((m == 64 || m == 65) || m == 66) || m == 67;
}

static BOOLEAN OPA_IsMMMode (INT32 m)
{
	return (m == 68 || m == 69) || m == 70;
}

static BOOLEAN OPA_IsFRegMode (INT32 m, BOOLEAN strict)
{
	return m == 128 || (!strict && m == 129);
}

static BOOLEAN OPA_IsRegister (INT32 mode)
{
	return ((OPA_IsRegMode(mode, 1) || OPA_IsSRegMode(mode, 0)) || OPA_IsSpecRegMode(mode)) || mode == 40;
}

static BOOLEAN OPA_NeedModRM (INT32 mode, INT32 regpos)
{
	return ((OPA_IsRMMode(mode) || OPA_IsMMode(mode)) || OPA_IsMMMode(mode)) || (((regpos == 1 || regpos == 4) || regpos == 3) && OPA_IsRegister(mode));
}

static BOOLEAN OPA_IsImmMode (INT32 m)
{
	return (((m == 48 || m == 49) || m == 50) || m == 53) || m == 54;
}

static BOOLEAN OPA_IsRelMode (INT32 m)
{
	return (m == 96 || m == 97) || m == 98;
}

static INT32 OPA_Evaluate (OPA_Operand *op, ADDRESS *op__typ, INT32 mode)
{
	if (mode == (*op).mode) {
		return 4;
	} else if (OPA_IsRMMode(mode)) {
		if (OPA_IsMMode((*op).mode)) {
			if (OPA_ModeSize((*op).mode) == OPA_ModeSize(mode)) {
				return 4;
			} else if ((*op).mode == 64 || (*op).mode == 72) {
				return 1;
			}
		} else if ((OPA_IsRegMode((*op).mode, 0) && OPA_ModeSize((*op).mode) == OPA_ModeSize(mode))) {
			return 2;
		}
	} else if (OPA_IsRegMode(mode, 1)) {
		if (OPA_ModeSize((*op).mode) == OPA_ModeSize(mode)) {
			if (OPA_IsRegMode((*op).mode, 1)) {
				return 4;
			} else if (OPA_IsRegMode((*op).mode, 0)) {
				return 2;
			}
		}
	} else if (mode == 18) {
		if (((*op).mode == 16 && (*op).reg == 2)) {
			return 4;
		}
	} else if (mode == 19) {
		if (((*op).mode == 8 && (*op).reg == 1)) {
			return 4;
		}
	} else if (OPA_IsRegMode(mode, 0)) {
		return 0;
	} else if (OPA_IsImmMode(mode)) {
		if ((*op).mode == 54) {
			if (OPA_ModeSize(mode) > OPA_ConstSize((*op).imm, mode == 53)) {
				return 3;
			} else if (OPA_ModeSize(mode) == OPA_ConstSize((*op).imm, mode == 53)) {
				return 4;
			}
		} else if (OPA_IsImmMode((*op).mode)) {
			if (OPA_ModeSize(mode) > OPA_ModeSize((*op).mode)) {
				return 3;
			} else if (OPA_ModeSize(mode) == OPA_ModeSize((*op).mode)) {
				return 4;
			}
		}
	} else if (mode == 51) {
		if ((OPA_IsImmMode((*op).mode) && (*op).imm == 1)) {
			return 4;
		}
	} else if (mode == 52) {
		if ((OPA_IsImmMode((*op).mode) && (*op).imm == 3)) {
			return 4;
		}
	} else if (OPA_IsMMode(mode)) {
		if (OPA_IsMMode((*op).mode)) {
			if (OPA_ModeSize((*op).mode) == OPA_ModeSize(mode)) {
				return 4;
			} else if ((*op).mode == 72 || mode == 72) {
				return 1;
			}
		}
	} else if (mode == 80) {
		if (OPA_IsSRegMode((*op).mode, 0)) {
			return 4;
		}
	} else if (OPA_IsRelMode(mode)) {
		if ((mode == 98 && (*op).mode == 99)) {
			return 4;
		} else if (OPA_IsImmMode((*op).mode)) {
			if (OPA_ModeSize(mode) == OPA_ConstSize((*op).imm, 1)) {
				return 4;
			} else if (OPA_ModeSize(mode) > OPA_ConstSize((*op).imm, 1)) {
				return 3;
			}
		}
	} else if (mode == 128) {
		if (OPA_IsFRegMode((*op).mode, 1)) {
			return 4;
		} else if (OPA_IsFRegMode((*op).mode, 0)) {
			return 2;
		}
	} else if (mode == 70) {
		if ((*op).mode == 40 || (*op).mode == 76) {
			return 4;
		} else if ((*op).mode == 72) {
			return 2;
		}
	} else if (mode == 69) {
		if ((*op).mode == 40 || (*op).mode == 75) {
			return 4;
		} else if ((*op).mode == 72) {
			return 2;
		}
	}
	return 0;
}

static INT32 OPA_Match (INT32 ind, OPA_Operand *op, ADDRESS op__len)
{
	INT32 start, end, i, j, k, best;
	start = (OPA_InstrTab->data)[__X(ind, OPA_InstrTab->len[0])].start;
	end = (OPA_InstrTab->data)[__X(ind, OPA_InstrTab->len[0])].end;
	ind = -1;
	best = 0;
	while (start < end) {
		i = OPA_Evaluate(&op[0], OPA_Operand__typ, (OPA_OpTab->data)[__X(start, OPA_OpTab->len[0])].op[0]);
		if (i == 0) {
		} else {
			j = OPA_Evaluate(&op[__X(1, op__len)], OPA_Operand__typ, (OPA_OpTab->data)[__X(start, OPA_OpTab->len[0])].op[1]);
			if (j == 0) {
				i = 0;
			} else {
				k = OPA_Evaluate(&op[__X(2, op__len)], OPA_Operand__typ, (OPA_OpTab->data)[__X(start, OPA_OpTab->len[0])].op[2]);
				if ((i < j && i < k)) {
				} else if (j < k) {
					i = j;
				} else {
					i = k;
				}
			}
		}
		if (i != 0) {
			if (i == 4) {
				ind = start;
				return ind;
			} else if (i > best) {
				ind = start;
				best = i;
			} else if ((i == best && i == 1)) {
				OPM_Mark(512, OPA_errpos);
				ind = -1;
				return ind;
			}
		}
		start += 1;
	}
	if (ind == -1) {
		OPM_Mark(501, OPA_errpos);
	}
	return ind;
}

static void OPA_insert (CHAR *name, ADDRESS name__len, OPA_Object *obj)
{
	OPA_Object ob0, ob1;
	INT32 d;
	ob0 = OPA_root;
	ob1 = ob0->right;
	d = 1;
	for (;;) {
		if (ob1 == NIL) {
			__NEW(ob1, OPA_ObjDesc);
			__COPY(name, ob1->name, 32);
			ob1->typ = 1;
			ob1->left = NIL;
			ob1->right = NIL;
			ob1->fix = NIL;
			ob1->obj = NIL;
			ob1->next = OPA_root->next;
			OPA_root->next = ob1;
			ob1->val = OPM_errpos;
			if (d < 0) {
				ob0->left = ob1;
			} else {
				ob0->right = ob1;
			}
		} else if (__STRCMP(name, ob1->name) < 0) {
			d = -1;
			ob0 = ob1;
			ob1 = ob1->left;
		} else if (__STRCMP(name, ob1->name) > 0) {
			d = 1;
			ob0 = ob1;
			ob1 = ob1->right;
		} else {
			break;
		}
	}
	*obj = ob1;
}

static OPA_Object OPA_ConvertObj (OPT_Object ob)
{
	OPA_Object obj;
	if (ob != NIL) {
		__NEW(obj, OPA_ObjDesc);
		switch (ob->mode) {
			case 1: 
				obj->val = 1;
				obj->size = OPA_SizeTab[__X(ob->typ->form, 17)];
				if (ob->mnolev <= 0) {
					obj->typ = 7;
				} else {
					obj->typ = 5;
				}
				break;
			case 2: 
				obj->typ = 6;
				obj->val = 1;
				obj->size = 4;
				break;
			case 3: 
				obj->typ = 3;
				obj->val = ob->conval->intval;
				if (ob->typ->form > 6 || ob->typ->form == 2) {
					OPM_err(51);
				}
				break;
			case 5: 
				obj->typ = 4;
				obj->size = OPA_SizeTab[__X(ob->typ->form, 17)];
				OPM_err(514);
				break;
			case 11: 
				obj->typ = 11;
				break;
			default: 
				obj->typ = 3;
				obj->val = 0;
				OPM_err(514);
				break;
		}
		obj->obj = ob;
	}
	return obj;
}

static void OPA_find (OPS_Name name, OPA_Object *obj)
{
	OPA_Object ob0;
	OPT_Object ob;
	ob0 = OPA_root->right;
	while ((ob0 != NIL && __STRCMP(ob0->name, name) != 0)) {
		if (__STRCMP(name, ob0->name) < 0) {
			ob0 = ob0->left;
		} else {
			ob0 = ob0->right;
		}
	}
	*obj = ob0;
	if (*obj == NIL) {
		__COPY(name, OPS_name, 32);
		OPT_Find(&ob);
		if (ob != NIL) {
			*obj = OPA_ConvertObj(ob);
		} else {
			OPA_insert((void*)name, 32, &*obj);
		}
	}
}

static void OPA_HashFn (CHAR *name, ADDRESS name__len, INT32 *k, INT32 *n)
{
	INT32 i;
	if (*n == 0) {
		i = 0;
		*k = 0;
		while (name[__X(i, name__len)] != 0x00) {
			*k = (int)__MOD(__ASHL(*k, 4) + name[__X(i, name__len)], OPA_InstrTabLen);
			i += 1;
		}
		*n = 1;
	} else {
		*k = (int)__MOD(*k + *n, OPA_InstrTabLen);
		*n += 1;
	}
}

static void OPA_FindInstruction (CHAR *name, ADDRESS name__len, INT32 *inx)
{
	INT32 n;
	n = 0;
	do {
		OPA_HashFn((void*)name, name__len, &*inx, &n);
	} while (!((__STRCMP(name, (OPA_InstrTab->data)[__X(*inx, OPA_InstrTab->len[0])].name) == 0 || (OPA_InstrTab->data)[__X(*inx, OPA_InstrTab->len[0])].name[0] == 0x00) || n > OPA_InstrTabLen));
	if ((OPA_InstrTab->data)[__X(*inx, OPA_InstrTab->len[0])].name[0] == 0x00 || n > OPA_InstrTabLen) {
		*inx = -1;
	} else if (((OPA_InstrTab->data)[__X(*inx, OPA_InstrTab->len[0])].target | OPA_Target) != OPA_Target) {
		OPM_err(515);
	}
}

static void OPA_skipBlanks (void)
{
	while (OPS_ch == ' ' || OPS_ch == 0x09) {
		OPM_Get(&OPS_ch);
	}
	if (OPS_ch == ';') {
		while (OPS_ch != 0x0d) {
			OPM_Get(&OPS_ch);
		}
	}
}

static void OPA_GetIdent (OPS_Name name)
{
	INT32 i;
	i = 0;
	OPM_errpos = OPM_curpos - 1;
	do {
		if (i < 31) {
			name[__X(i, 32)] = OPS_ch;
			i += 1;
		}
		OPM_Get(&OPS_ch);
	} while (!(!(('A' <= __CAP(OPS_ch) && __CAP(OPS_ch) <= 'Z') || ('0' <= OPS_ch && OPS_ch <= '9'))));
	name[__X(i, 32)] = 0x00;
}

static struct Get__21 {
	struct Get__21 *lnk;
} *Get__21_s;

static void Comment__22 (void);
static void Str__24 (void);

static void Comment__22 (void)
{
	OPM_Get(&OPS_ch);
	for (;;) {
		for (;;) {
			while (OPS_ch == '(') {
				OPM_Get(&OPS_ch);
				if (OPS_ch == '*') {
					Comment__22();
				}
			}
			if (OPS_ch == '*') {
				OPM_Get(&OPS_ch);
				break;
			}
			if (OPS_ch == 0x00) {
				break;
			}
			OPM_Get(&OPS_ch);
		}
		if (OPS_ch == ')') {
			OPM_Get(&OPS_ch);
			break;
		}
		if (OPS_ch == 0x00) {
			OPM_Mark(5, OPM_errpos);
			break;
		}
	}
}

static void Str__24 (void)
{
	CHAR och;
	INT32 i;
	och = OPS_ch;
	i = 0;
	for (;;) {
		OPM_Get(&OPS_ch);
		if (OPS_ch == och) {
			break;
		} else if (OPS_ch < ' ') {
			OPM_err(3);
			break;
		} else if (i == 255) {
			OPM_err(241);
			break;
		}
		OPA_str[__X(i, 256)] = OPS_ch;
		i += 1;
	}
	OPM_Get(&OPS_ch);
	OPA_str[__X(i, 256)] = 0x00;
	OPA_val = i;
}

static void OPA_Get (INT32 *sym)
{
	struct Get__21 _s;
	_s.lnk = Get__21_s;
	Get__21_s = &_s;
	OPA_skipBlanks();
	OPM_errpos = OPM_curpos;
	switch (OPS_ch) {
		case 'A': case 'B': case 'C': case 'D': case 'E': 
		case 'F': case 'G': case 'H': case 'I': case 'J': 
		case 'K': case 'L': case 'M': case 'N': case 'O': 
		case 'P': case 'Q': case 'R': case 'S': case 'T': 
		case 'U': case 'V': case 'W': case 'X': case 'Y': 
		case 'Z': case 'a': case 'b': case 'c': case 'd': 
		case 'e': case 'f': case 'g': case 'h': case 'i': 
		case 'j': case 'k': case 'l': case 'm': case 'n': 
		case 'o': case 'p': case 'q': case 'r': case 's': 
		case 't': case 'u': case 'v': case 'w': case 'x': 
		case 'y': case 'z': 
			OPA_GetIdent(OPA_ident);
			if (OPS_ch == ':') {
				OPM_Get(&OPS_ch);
				*sym = 11;
			} else if (__STRCMP(OPA_ident, "END") == 0) {
				*sym = 10;
			} else {
				*sym = 1;
			}
			break;
		case '0': case '1': case '2': case '3': case '4': 
		case '5': case '6': case '7': case '8': case '9': 
			OPA_val = 0;
			*sym = 4;
			OPS_Number();
			__ASSERT(OPS_numtyp <= 2, 0);
			OPA_val = OPS_intval;
			break;
		case ';': 
			OPM_Get(&OPS_ch);
			*sym = 2;
			break;
		case '@': 
			OPM_Get(&OPS_ch);
			*sym = 3;
			break;
		case ',': 
			OPM_Get(&OPS_ch);
			*sym = 5;
			break;
		case '[': 
			OPM_Get(&OPS_ch);
			*sym = 6;
			break;
		case ']': 
			OPM_Get(&OPS_ch);
			*sym = 7;
			break;
		case '{': 
			OPM_Get(&OPS_ch);
			*sym = 20;
			break;
		case '}': 
			OPM_Get(&OPS_ch);
			*sym = 21;
			break;
		case 0x0d: 
			OPM_Get(&OPS_ch);
			*sym = 8;
			break;
		case '*': 
			OPM_Get(&OPS_ch);
			*sym = 9;
			break;
		case '/': 
			OPM_Get(&OPS_ch);
			*sym = 15;
			break;
		case '+': 
			OPM_Get(&OPS_ch);
			*sym = 13;
			break;
		case '-': 
			OPM_Get(&OPS_ch);
			*sym = 14;
			break;
		case '(': 
			OPM_Get(&OPS_ch);
			if (OPS_ch == '*') {
				Comment__22();
				OPA_Get(&*sym);
			} else {
				*sym = 16;
			}
			break;
		case ')': 
			OPM_Get(&OPS_ch);
			*sym = 17;
			break;
		case ':': 
			OPM_Get(&OPS_ch);
			*sym = 12;
			break;
		case '.': 
			OPM_Get(&OPS_ch);
			*sym = 19;
			break;
		case '"': case '\'': 
			Str__24();
			*sym = 18;
			break;
		default: 
			*sym = 0;
			OPM_Get(&OPS_ch);
			break;
	}
	Get__21_s = _s.lnk;
}

static void OPA_Check (INT32 s)
{
	if (OPA_sym != s) {
		OPM_err((INT16)s);
	}
	OPA_Get(&OPA_sym);
}

static void OPA_Qualident (OPA_Object *obj)
{
	INT32 i;
	OPT_Object o;
	*obj = NIL;
	if (OPA_sym == 1) {
		if (__STRCMP(OPA_ident, "SYSTEM") == 0) {
			if (!OPT_SYSimported) {
				OPM_err(135);
			}
			__MOVE("SYSTEM", OPS_name, 7);
			OPT_Find(&o);
			if (o != NIL) {
				o->flag |= __SETOF(1,32);
			}
			OPA_Get(&OPA_sym);
			if (OPA_sym == 19) {
				OPA_Get(&OPA_sym);
				if (OPA_sym == 1) {
					i = 0;
					while ((i < OPA_TargetCount && __STRCMP(OPA_TargetTab[__X(i, 32)].name, OPA_ident) != 0)) {
						i += 1;
					}
					if (i == OPA_TargetCount) {
						OPM_err(0);
					} else {
						__NEW(*obj, OPA_ObjDesc);
						(*obj)->typ = 3;
						(*obj)->val = i;
					}
				} else {
					OPM_err(0);
				}
				OPA_Get(&OPA_sym);
			} else {
				OPM_err(18);
			}
		} else {
			OPA_Get(&OPA_sym);
			OPA_find(OPA_ident, &*obj);
			if ((((*obj != NIL && OPA_sym == 19)) && (*obj)->typ == 11)) {
				OPA_Get(&OPA_sym);
				__MOVE(OPA_ident, OPS_name, 32);
				OPT_FindImport((*obj)->obj, &(*obj)->obj);
				*obj = OPA_ConvertObj((*obj)->obj);
			}
			if (*obj == NIL) {
				OPM_err(0);
			}
		}
	} else {
		OPM_err(40);
	}
}

static struct Expression__12 {
	struct Expression__12 *lnk;
} *Expression__12_s;

static void Factor__13 (INT32 *x);
static void Term__15 (INT32 *x);

static void Factor__13 (INT32 *x)
{
	if (OPA_sym == 4) {
		*x = OPA_val;
		OPA_Get(&OPA_sym);
	} else if (OPA_sym == 16) {
		OPA_Get(&OPA_sym);
		OPA_Expression(&*x);
		OPA_Check(17);
	} else {
		OPM_err(601);
	}
}

static void Term__15 (INT32 *x)
{
	INT32 y, op;
	Factor__13(&*x);
	while (OPA_sym == 9 || OPA_sym == 15) {
		op = OPA_sym;
		OPA_Get(&OPA_sym);
		Factor__13(&y);
		if (op == 9) {
			*x = *x * y;
		} else {
			*x = __DIV(*x, y);
		}
	}
}

static void OPA_Expression (INT32 *x)
{
	INT32 y, op;
	struct Expression__12 _s;
	_s.lnk = Expression__12_s;
	Expression__12_s = &_s;
	if (OPA_sym == 14) {
		op = OPA_sym;
		OPA_Get(&OPA_sym);
		Term__15(&*x);
		*x = -*x;
	} else {
		Term__15(&*x);
	}
	while (OPA_sym == 13 || OPA_sym == 14) {
		op = OPA_sym;
		OPA_Get(&OPA_sym);
		Term__15(&y);
		if (op == 13) {
			*x = *x + y;
		} else {
			*x = *x - y;
		}
	}
	Expression__12_s = _s.lnk;
}

static void OPA_GetBaseIndex (OPA_Operand *o, ADDRESS *o__typ, INT32 size)
{
	OPA_Object obj;
	switch (size) {
		case 0: 
			(*o).mode = 72;
			break;
		case 1: 
			(*o).mode = 73;
			break;
		case 2: 
			(*o).mode = 74;
			break;
		case 4: 
			(*o).mode = 75;
			break;
		case 8: 
			(*o).mode = 76;
			break;
		case 10: 
			(*o).mode = 77;
			break;
		default: __CASECHK;
	}
	(*o).disp = (*o).imm;
	(*o).imm = 0;
	while (OPA_sym == 6 || OPA_sym == 13) {
		OPA_Get(&OPA_sym);
		if (OPA_sym == 1) {
			OPA_find(OPA_ident, &obj);
		} else {
			obj = NIL;
		}
		if ((obj == NIL || !OPA_IsRegMode(obj->typ, 0)) || OPA_ModeSize(obj->typ) != 4) {
			OPM_err(506);
			return;
		}
		OPA_Get(&OPA_sym);
		if (OPA_sym == 9) {
			if ((*o).index != -1) {
				OPM_err(509);
				return;
			}
			(*o).index = (INT16)obj->val;
			OPA_Get(&OPA_sym);
			if (OPA_sym != 4 || (((((OPA_val != 1 && OPA_val != 2)) && OPA_val != 4)) && OPA_val != 8)) {
				OPM_err(508);
				return;
			}
			(*o).scale = (INT16)OPA_val;
			OPA_Get(&OPA_sym);
		} else if (OPA_sym == 7 || OPA_sym == 13) {
			if ((*o).base == -1) {
				(*o).base = (INT16)obj->val;
			} else if ((*o).index == -1) {
				(*o).index = (INT16)obj->val;
			} else {
				OPM_err(509);
			}
		} else {
			OPM_err(510);
			return;
		}
		if (OPA_sym == 7) {
			OPA_Get(&OPA_sym);
		}
	}
}

static void OPA_GetOperand (OPA_Operand *o, ADDRESS *o__typ)
{
	OPA_Object obj;
	INT32 size;
	(*o).reg = -1;
	(*o).disp = 0;
	(*o).base = -1;
	(*o).index = -1;
	(*o).imm = 0;
	(*o).seg = -1;
	(*o).scale = -1;
	(*o).obj = NIL;
	size = 0;
	if (OPA_sym == 1) {
		OPA_find(OPA_ident, &obj);
		if ((obj != NIL && obj->typ == 80)) {
			(*o).seg = (INT16)obj->val;
			OPA_Get(&OPA_sym);
			OPA_Check(12);
			if (OPA_sym == 1) {
				OPA_find(OPA_ident, &obj);
			}
		}
	}
	if ((((OPA_sym == 1 && obj != NIL)) && obj->typ == 4)) {
		size = (INT16)obj->size;
		OPA_Get(&OPA_sym);
		if (OPA_sym != 1 || __STRCMP(OPA_ident, "PTR") != 0) {
		} else {
			OPA_Get(&OPA_sym);
		}
		if (OPA_sym == 1) {
			OPA_find(OPA_ident, &obj);
		}
	}
	switch (OPA_sym) {
		case 3: 
			OPA_Get(&OPA_sym);
			if (OPA_sym != 4) {
				OPM_err(-601);
			}
			(*o).disp = OPA_val;
			(*o).mode = 72;
			OPA_Get(&OPA_sym);
			break;
		case 6: 
			OPA_GetBaseIndex(&*o, o__typ, size);
			break;
		case 1: case 4: case 14: 
			if (OPA_sym == 1) {
				if (obj == NIL) {
					OPM_err(500);
					return;
				}
				if (size == 0) {
					size = obj->size;
				}
				if (OPA_IsRegMode(obj->typ, 0)) {
					(*o).mode = obj->typ;
					(*o).reg = (INT16)obj->val;
					OPA_Get(&OPA_sym);
					return;
				} else if (OPA_IsSRegMode(obj->typ, 0)) {
					(*o).mode = obj->typ;
					(*o).reg = (INT16)obj->val;
					OPA_Get(&OPA_sym);
					return;
				} else if (OPA_IsSpecRegMode(obj->typ)) {
					if (!__IN(17, OPA_Target, 32)) {
						OPM_err(515);
					}
					if ((((!__IN(2, OPA_Target, 32) && obj->typ == 112)) && obj->val == 4)) {
						OPM_err(515);
					}
					(*o).mode = obj->typ;
					(*o).reg = (INT16)obj->val;
					OPA_Get(&OPA_sym);
					return;
				} else if (obj->typ == 40) {
					if (!__IN(18, OPA_Target, 32)) {
						OPM_err(515);
					}
					(*o).mode = obj->typ;
					(*o).reg = (INT16)obj->val;
					OPA_Get(&OPA_sym);
					return;
				} else if (OPA_IsFRegMode(obj->typ, 0)) {
					(*o).mode = obj->typ;
					OPA_Get(&OPA_sym);
					if (OPA_sym == 16) {
						OPA_Expression(&size);
						(*o).reg = (INT16)size;
					} else {
						(*o).reg = 0;
						(*o).mode = 129;
					}
					return;
				} else if (obj->typ == 0) {
					(*o).imm = obj->val;
					(*o).mode = 96;
					OPA_Get(&OPA_sym);
					return;
				} else if (obj->typ == 1) {
					(*o).obj = obj;
					(*o).mode = 99;
					OPA_Get(&OPA_sym);
					return;
				} else if (obj->typ == 3) {
					(*o).imm = obj->val;
					OPA_Get(&OPA_sym);
				} else if (obj->typ == 5 || obj->typ == 6) {
					if (OPA_inline) {
						OPM_err(518);
					}
					(*o).imm = obj->val;
					(*o).obj = obj;
					OPA_Get(&OPA_sym);
				} else if (obj->typ == 7) {
					(*o).disp = 305419896;
					(*o).obj = obj;
					switch (size) {
						case 1: 
							(*o).mode = 73;
							break;
						case 2: 
							(*o).mode = 74;
							break;
						case 4: 
							(*o).mode = 75;
							break;
						case 8: 
							(*o).mode = 76;
							break;
						case 10: 
							(*o).mode = 77;
							break;
						default: 
							(*o).mode = 75;
							break;
					}
					OPA_Get(&OPA_sym);
					return;
				} else {
					OPM_err(600);
					return;
				}
			} else {
				OPA_Expression(&(*o).imm);
			}
			switch (size) {
				case 1: 
					(*o).mode = 48;
					break;
				case 2: 
					(*o).mode = 49;
					break;
				case 4: 
					(*o).mode = 50;
					break;
				default: 
					(*o).mode = 54;
					break;
			}
			if (OPA_sym == 6) {
				OPA_GetBaseIndex(&*o, o__typ, size);
			}
			break;
		default: 
			(*o).mode = -1;
			OPM_err(511);
			break;
	}
}

static void OPA_CheckLabels (void)
{
	OPA_Object obj, obj1, obj2;
	obj1 = OPA_root->next;
	obj = NIL;
	while (obj1 != NIL) {
		obj2 = obj1->next;
		obj1->next = obj;
		obj = obj1;
		obj1 = obj2;
	}
	while (obj != NIL) {
		if (obj->typ == 1) {
			OPM_Mark(128, obj->val);
		}
		obj = obj->next;
	}
}

static void OPA_InsertFix (OPA_Object *obj, INT32 pc)
{
	OPA_FixPnt fix;
	OPT_Node x;
	switch ((*obj)->typ) {
		case 1: 
			__NEW(fix, OPA_FixPntDesc);
			fix->pc = pc;
			fix->node = OPA_last;
			fix->pos = (INT16)(*OPA_last->conval->ext)[0] - 3;
			fix->next = (*obj)->fix;
			(*obj)->fix = fix;
			break;
		case 5: case 6: case 7: 
			if ((OPA_export && OPA_inline)) {
				OPM_err(517);
			}
			x = OPT_NewNode(31);
			x->obj = (*obj)->obj;
			x->conval = OPT_NewConst();
			x->conval->intval = pc;
			x->conval->intval2 = OPM_errpos;
			x->link = OPA_fixlist;
			OPA_fixlist = x;
			break;
		default: 
			OPM_err(607);
			break;
	}
}

static void OPA_FixDisp (OPA_FixPnt *fix)
{
	INT32 pos, disp, _for__19;
	disp = OPA_pc - (*fix)->pc;
	_for__19 = (*fix)->pos + 3;
	pos = (*fix)->pos;
	while (pos <= _for__19) {
		(*(*fix)->node->conval->ext)[__X(pos, 256)] = (CHAR)disp;
		disp = __ASHR(disp, 8);
		pos += 1;
	}
}

static void OPA_NewNode (void)
{
	OPT_Node x;
	x = OPT_NewNode(30);
	x->conval = OPT_NewConst();
	x->conval->ext = OPT_NewExt();
	(*x->conval->ext)[0] = 0x00;
	x->conval->intval = OPM_errpos;
	OPB_Link(&OPA_first, &OPA_last, x);
}

static void OPA_PutByte (INT32 b)
{
	INT32 pos;
	pos = (INT16)(*OPA_last->conval->ext)[0] + 1;
	if (pos > 255) {
		OPA_NewNode();
		pos = 1;
	}
	(*OPA_last->conval->ext)[__X(pos, 256)] = (CHAR)b;
	(*OPA_last->conval->ext)[0] = (CHAR)pos;
	OPA_pc += 1;
}

static void OPA_PutBytes (INT32 b, INT32 size)
{
	INT32 pos;
	pos = (INT16)(*OPA_last->conval->ext)[0];
	if (pos > 255 - size) {
		OPA_NewNode();
		pos = 0;
	}
	while (size > 0) {
		pos += 1;
		(*OPA_last->conval->ext)[__X(pos, 256)] = (CHAR)b;
		b = __ASHR(b, 8);
		OPA_pc += 1;
		size -= 1;
	}
	(*OPA_last->conval->ext)[0] = (CHAR)pos;
}

static void OPA_ModRM (INT32 *modrm, OPA_Operand *op, ADDRESS *op__typ, INT32 mode, INT32 regpos, BOOLEAN UseSpecReg)
{
	INT32 mod;
	if ((((OPA_IsRegMode(mode, 1) && !UseSpecReg) || OPA_IsSRegMode(mode, 0)) || OPA_IsSpecRegMode(mode)) || mode == 40) {
		__ASSERT((*op).reg != -1, 0);
		if (regpos == 4) {
			__ASSERT(*modrm == 0, 0);
			*modrm = 192 + (*op).reg;
		} else if (regpos == 3) {
			__ASSERT(*modrm == 0, 0);
			*modrm = 192 + (*op).reg * 9;
		} else {
			*modrm = *modrm + __ASHL((*op).reg, 3);
		}
	} else if (OPA_NeedModRM(mode, -1) || (OPA_IsRegMode(mode, 1) && UseSpecReg)) {
		if ((*op).reg != -1) {
			*modrm = (*modrm + (*op).reg) + 192;
		} else {
			if (((*op).disp == 0 && !(((*op).base == 5 && (*op).index == -1)))) {
				mod = 0;
			} else if (OPA_ConstSize((*op).disp, 1) == 1) {
				mod = 1;
			} else if (((*op).base == -1 && (*op).index == -1)) {
				mod = 0;
			} else {
				mod = 2;
			}
			*modrm = *modrm + __ASHL(mod, 6);
			if ((*op).index != -1) {
				*modrm = *modrm + 4;
			} else if ((*op).base != -1) {
				*modrm = *modrm + (*op).base;
			} else {
				*modrm = *modrm + 5;
			}
		}
	} else {
		OPM_err(1000);
	}
}

static INT8 OPA_SIB (OPA_Operand op)
{
	INT32 val;
	if (op.index == 4) {
		OPM_err(501);
	} else if (op.index != -1) {
		val = op.base + __ASHL(op.index, 3);
		switch (op.scale) {
			case -1: case 1: 
				break;
			case 2: 
				val = val + 64;
				break;
			case 4: 
				val = val + 128;
				break;
			case 8: 
				val = val + 192;
				break;
			default: __CASECHK;
		}
	} else {
		val = op.base + 32;
	}
	return (INT8)((INT16)val);
}

static void OPA_GenCode (INT32 ind, OPA_Operand *op, ADDRESS op__len)
{
	INT32 i, instr, opi;
	OPA_Mnemo name;
	OPA_Object fixobj;
	BOOLEAN UseRM, UseImm, UseSpecReg, UseSegReg, UseDisp;
	INT32 seg, reg, modrm, sib, imm, immSize, disp;
	disp = 0;
	if (OPA_IsRelMode(op[0].mode)) {
		switch (OPA_ConstSize((op[0].imm - 2) - OPA_pc, 1)) {
			case 1: 
				op[0].mode = 96;
				break;
			case 2: case 4: 
				op[0].mode = 98;
				break;
			default: __CASECHK;
		}
	}
	__COPY((OPA_InstrTab->data)[__X(ind, OPA_InstrTab->len[0])].name, name, 12);
	instr = OPA_Match(ind, (void*)op, op__len);
	if (instr < 0) {
		return;
	}
	UseSpecReg = OPA_IsSpecRegMode((OPA_OpTab->data)[__X(instr, OPA_OpTab->len[0])].op[0]) || OPA_IsSpecRegMode((OPA_OpTab->data)[__X(instr, OPA_OpTab->len[0])].op[1]);
	UseSegReg = OPA_IsSRegMode((OPA_OpTab->data)[__X(instr, OPA_OpTab->len[0])].op[0], 0) || OPA_IsSRegMode((OPA_OpTab->data)[__X(instr, OPA_OpTab->len[0])].op[1], 0);
	if ((((((!UseSpecReg && !UseSegReg)) && name[0] != 'F')) && ((__STRCMP(name, "OUT") == 0 && OPA_ModeSize((OPA_OpTab->data)[__X(instr, OPA_OpTab->len[0])].op[1]) == 2) || (__STRCMP(name, "OUT") != 0 && OPA_ModeSize((OPA_OpTab->data)[__X(instr, OPA_OpTab->len[0])].op[0]) == 2)))) {
		if ((OPA_OpTab->data)[__X(instr, OPA_OpTab->len[0])].op[0] == 97 || ((__STRCMP(name, "LEA") == 0 || __STRCMP(name, "OUTS") == 0) && (OPA_OpTab->data)[__X(instr, OPA_OpTab->len[0])].op[1] == 66)) {
			OPA_PutByte(103);
		} else if ((((__STRCMP(name, "RET") != 0 && __STRCMP(name, "ARPL") != 0)) && __STRCMP(name, "STR") != 0)) {
			OPA_PutByte(102);
		}
	}
	if (__IN(18, (OPA_InstrTab->data)[__X(ind, OPA_InstrTab->len[0])].target, 32)) {
		OPA_PutByte(15);
	}
	seg = -1;
	reg = -1;
	modrm = 0;
	UseRM = 0;
	sib = -1;
	UseImm = 0;
	fixobj = NIL;
	UseDisp = 0;
	i = 0;
	while ((i < 3 && (OPA_OpTab->data)[__X(instr, OPA_OpTab->len[0])].op[__X(i, 3)] != -1)) {
		opi = (OPA_OpTab->data)[__X(instr, OPA_OpTab->len[0])].op[__X(i, 3)];
		if (op[__X(i, op__len)].seg != -1) {
			if (seg != -1) {
				OPM_err(504);
			} else {
				seg = op[__X(i, op__len)].seg;
			}
		}
		if (((OPA_OpTab->data)[__X(instr, OPA_OpTab->len[0])].reg == 2 && (OPA_IsRegMode(opi, 1) || OPA_IsFRegMode(opi, 1)))) {
			reg = op[__X(i, op__len)].reg;
		}
		if (OPA_NeedModRM(opi, (OPA_OpTab->data)[__X(instr, OPA_OpTab->len[0])].reg)) {
			OPA_ModRM(&modrm, &op[__X(i, op__len)], OPA_Operand__typ, opi, (OPA_OpTab->data)[__X(instr, OPA_OpTab->len[0])].reg, UseSpecReg);
			UseRM = 1;
			if (OPA_NeedModRM(opi, -1)) {
				disp = op[__X(i, op__len)].disp;
				fixobj = op[__X(i, op__len)].obj;
				UseDisp = disp != 0 || (op[__X(i, op__len)].base == 5 && op[__X(i, op__len)].index == -1);
			}
		}
		if (op[__X(i, op__len)].index != -1 || op[__X(i, op__len)].base == 4) {
			__ASSERT(sib == -1, 0);
			sib = OPA_SIB(op[__X(i, op__len)]);
		}
		if (OPA_IsImmMode(opi) || (OPA_IsRelMode(opi) && OPA_IsImmMode(op[__X(i, op__len)].mode))) {
			__ASSERT(!UseImm, 0);
			UseImm = 1;
			imm = op[__X(i, op__len)].imm;
			immSize = OPA_ModeSize(opi);
		}
		i += 1;
	}
	if (seg != -1) {
		OPA_PutByte(seg);
	}
	if (reg == -1) {
		reg = 0;
	}
	if ((OPA_OpTab->data)[__X(instr, OPA_OpTab->len[0])].op1 != -1) {
		OPA_PutByte((OPA_OpTab->data)[__X(instr, OPA_OpTab->len[0])].op0);
		OPA_PutByte((OPA_OpTab->data)[__X(instr, OPA_OpTab->len[0])].op1 + reg);
	} else {
		OPA_PutByte((OPA_OpTab->data)[__X(instr, OPA_OpTab->len[0])].op0 + reg);
	}
	if ((OPA_OpTab->data)[__X(instr, OPA_OpTab->len[0])].opc != -1) {
		__ASSERT(OPA_AND(modrm, 56) == 0, 0);
		modrm = modrm + __ASHL((OPA_OpTab->data)[__X(instr, OPA_OpTab->len[0])].opc, 3);
		UseRM = 1;
	}
	if (UseRM) {
		OPA_PutByte(modrm);
	}
	if (sib != -1) {
		OPA_PutByte(sib);
	}
	if (UseDisp) {
		if (fixobj != NIL) {
			OPA_InsertFix(&fixobj, OPA_pc);
		}
		if (OPA_ConstSize(disp, 1) == 1) {
			OPA_PutByte(disp);
		} else {
			OPA_PutBytes(disp, 4);
		}
	}
	if ((OPA_IsRelMode((OPA_OpTab->data)[__X(instr, OPA_OpTab->len[0])].op[0]) && !OPA_IsImmMode(op[0].mode))) {
		OPA_PutBytes((op[0].imm - OPA_pc) - OPA_ModeSize((OPA_OpTab->data)[__X(instr, OPA_OpTab->len[0])].op[0]), OPA_ModeSize((OPA_OpTab->data)[__X(instr, OPA_OpTab->len[0])].op[0]));
		if (op[0].mode == 99) {
			OPA_InsertFix(&op[0].obj, OPA_pc);
		}
	}
	if (UseImm) {
		OPA_PutBytes(imm, immSize);
	}
}

static void OPA_ParseLabel (void)
{
	OPA_Object obj;
	OPA_FixPnt fix;
	__ASSERT(OPA_sym == 11, 0);
	OPA_insert((void*)OPA_ident, 32, &obj);
	if (obj->typ == 1) {
		fix = obj->fix;
		while (fix != NIL) {
			OPA_FixDisp(&fix);
			fix = fix->next;
		}
		obj->typ = 0;
		obj->val = OPA_pc;
	} else {
		OPM_err(512);
	}
	OPA_Get(&OPA_sym);
}

static void OPA_ParseInstruction (void)
{
	INT32 ind, size, i;
	OPA_Operand op[3];
	OPS_Name name;
	INT32 _for__51;
	if ((__STRCMP(OPA_ident, "DB") == 0 || __STRCMP(OPA_ident, "DW") == 0) || __STRCMP(OPA_ident, "DD") == 0) {
		switch (OPA_ident[1]) {
			case 'B': 
				size = 1;
				break;
			case 'W': 
				size = 2;
				break;
			case 'D': 
				size = 4;
				break;
			default: __CASECHK;
		}
		OPA_Get(&OPA_sym);
		while (OPA_sym == 4 || OPA_sym == 18) {
			if ((OPA_sym == 18 && OPA_val == 1)) {
				OPA_PutBytes((INT16)OPA_str[0], size);
			} else if ((OPA_sym == 4 && OPA_ConstSize(OPA_val, 0) <= size)) {
				OPA_PutBytes(OPA_val, size);
			} else {
				OPM_err(203);
			}
			OPA_Get(&OPA_sym);
			if (OPA_sym == 5) {
				OPA_Get(&OPA_sym);
			} else {
				return;
			}
		}
	} else if (__STRCMP(OPA_ident, "DS") == 0) {
		OPA_Get(&OPA_sym);
		if (OPA_sym == 18) {
			_for__51 = OPA_val;
			i = 0;
			while (i <= _for__51) {
				OPA_PutBytes((INT16)OPA_str[__X(i, 256)], 1);
				i += 1;
			}
			OPA_Get(&OPA_sym);
		} else {
			OPM_err(513);
		}
	} else {
		i = 0;
		while (i <= 2) {
			op[__X(i, 3)].mode = -1;
			i += 1;
		}
		OPA_FindInstruction((void*)OPA_ident, 32, &ind);
		__COPY(OPA_ident, name, 32);
		OPA_errpos = OPM_errpos;
		OPA_Get(&OPA_sym);
		if (ind < 0) {
			OPM_err(502);
			return;
		}
		name[3] = 0x00;
		if (__STRCMP(name, "REP") == 0) {
			OPA_GenCode(ind, (void*)op, 3);
			if (OPA_sym == 8) {
				OPA_Get(&OPA_sym);
			}
			OPA_FindInstruction((void*)OPA_ident, 32, &ind);
			OPA_errpos = OPM_errpos;
			OPA_Get(&OPA_sym);
			if (ind < 0) {
				OPM_err(502);
				return;
			}
		}
		i = 0;
		if (OPA_sym != 8) {
			for (;;) {
				OPA_GetOperand(&op[__X(i, 3)], OPA_Operand__typ);
				i += 1;
				if (OPA_sym != 5) {
					break;
				}
				OPA_Get(&OPA_sym);
			}
		}
		OPA_GenCode(ind, (void*)op, 3);
	}
}

static void OPA_ParseTarget (void)
{
	OPA_Object obj;
	for (;;) {
		if (OPA_sym == 1) {
			OPA_Qualident(&obj);
			if (obj == NIL) {
				OPM_err(0);
			} else if (obj->typ == 3) {
				OPA_Target = OPA_Target | OPA_TargetTab[__X(obj->val, 32)].flag;
			} else {
				OPM_err(0);
			}
		} else {
			OPM_err(40);
		}
		if (OPA_sym == 21) {
			OPA_Get(&OPA_sym);
			break;
		} else if (OPA_sym == 5) {
			OPA_Get(&OPA_sym);
		} else if (OPA_sym != 1) {
			OPM_err(24);
			break;
		} else {
			OPM_err(19);
		}
	}
}

static void OPA_InsertReg (CHAR *name, ADDRESS name__len, INT32 t, INT32 v)
{
	OPA_Object obj;
	__DUP(name, name__len, CHAR);
	OPA_insert((void*)name, name__len, &obj);
	obj->typ = t;
	obj->val = v;
	obj->size = 0;
	__DEL(name);
}

static void OPA_InsertType (CHAR *name, ADDRESS name__len, INT32 s)
{
	OPA_Object obj;
	__DUP(name, name__len, CHAR);
	OPA_insert((void*)name, name__len, &obj);
	obj->typ = 4;
	obj->val = -1;
	obj->size = s;
	__DEL(name);
}

static void OPA_Init (void)
{
	OPA_root->next = NIL;
	OPA_root->left = NIL;
	OPA_root->right = NIL;
	OPA_InsertReg((CHAR*)"AL", 3, 9, 0);
	OPA_InsertReg((CHAR*)"AH", 3, 8, 4);
	OPA_InsertReg((CHAR*)"AX", 3, 17, 0);
	OPA_InsertReg((CHAR*)"EAX", 4, 33, 0);
	OPA_InsertReg((CHAR*)"BL", 3, 8, 3);
	OPA_InsertReg((CHAR*)"BH", 3, 8, 7);
	OPA_InsertReg((CHAR*)"BX", 3, 16, 3);
	OPA_InsertReg((CHAR*)"EBX", 4, 32, 3);
	OPA_InsertReg((CHAR*)"CL", 3, 8, 1);
	OPA_InsertReg((CHAR*)"CH", 3, 8, 5);
	OPA_InsertReg((CHAR*)"CX", 3, 16, 1);
	OPA_InsertReg((CHAR*)"ECX", 4, 32, 1);
	OPA_InsertReg((CHAR*)"DL", 3, 8, 2);
	OPA_InsertReg((CHAR*)"DH", 3, 8, 6);
	OPA_InsertReg((CHAR*)"DX", 3, 16, 2);
	OPA_InsertReg((CHAR*)"EDX", 4, 32, 2);
	OPA_InsertReg((CHAR*)"SP", 3, 16, 4);
	OPA_InsertReg((CHAR*)"ESP", 4, 32, 4);
	OPA_InsertReg((CHAR*)"BP", 3, 16, 5);
	OPA_InsertReg((CHAR*)"EBP", 4, 32, 5);
	OPA_InsertReg((CHAR*)"SI", 3, 16, 6);
	OPA_InsertReg((CHAR*)"ESI", 4, 32, 6);
	OPA_InsertReg((CHAR*)"DI", 3, 16, 7);
	OPA_InsertReg((CHAR*)"EDI", 4, 32, 7);
	OPA_InsertReg((CHAR*)"MM0", 4, 40, 0);
	OPA_InsertReg((CHAR*)"MM1", 4, 40, 1);
	OPA_InsertReg((CHAR*)"MM2", 4, 40, 2);
	OPA_InsertReg((CHAR*)"MM3", 4, 40, 3);
	OPA_InsertReg((CHAR*)"MM4", 4, 40, 4);
	OPA_InsertReg((CHAR*)"MM5", 4, 40, 5);
	OPA_InsertReg((CHAR*)"MM6", 4, 40, 6);
	OPA_InsertReg((CHAR*)"MM7", 4, 40, 7);
	OPA_InsertReg((CHAR*)"CS", 3, 81, 1);
	OPA_InsertReg((CHAR*)"SS", 3, 86, 2);
	OPA_InsertReg((CHAR*)"DS", 3, 82, 3);
	OPA_InsertReg((CHAR*)"ES", 3, 83, 0);
	OPA_InsertReg((CHAR*)"FS", 3, 84, 4);
	OPA_InsertReg((CHAR*)"GS", 3, 85, 5);
	OPA_InsertReg((CHAR*)"CR0", 4, 112, 0);
	OPA_InsertReg((CHAR*)"CR2", 4, 112, 2);
	OPA_InsertReg((CHAR*)"CR3", 4, 112, 3);
	OPA_InsertReg((CHAR*)"CR4", 4, 112, 4);
	OPA_InsertReg((CHAR*)"DR0", 4, 113, 0);
	OPA_InsertReg((CHAR*)"DR1", 4, 113, 1);
	OPA_InsertReg((CHAR*)"DR2", 4, 113, 2);
	OPA_InsertReg((CHAR*)"DR3", 4, 113, 3);
	OPA_InsertReg((CHAR*)"DR6", 4, 113, 6);
	OPA_InsertReg((CHAR*)"DR7", 4, 113, 7);
	OPA_InsertReg((CHAR*)"ST", 3, 128, 0);
	OPA_InsertType((CHAR*)"BYTE", 5, 1);
	OPA_InsertType((CHAR*)"WORD", 5, 2);
	OPA_InsertType((CHAR*)"DWORD", 6, 4);
	OPA_InsertType((CHAR*)"QWORD", 6, 8);
	OPA_InsertType((CHAR*)"TBYTE", 6, 10);
	OPA_pc = 0;
	OPA_Target = 0x0;
}

static void OPA_Close (void)
{
	OPA_root->right = NIL;
}

static void OPA_InsertTarget (CHAR *name, ADDRESS name__len, UINT32 flag)
{
	__DUP(name, name__len, CHAR);
	__COPY(name, OPA_TargetTab[__X(OPA_TargetCount, 32)].name, 32);
	OPA_TargetTab[__X(OPA_TargetCount, 32)].flag = flag;
	OPA_TargetCount += 1;
	__DEL(name);
}

static void OPA_BodyInit (void)
{
	INT16 s;
	INT32 i;
	Files_File f;
	Files_Rider r;
	INT32 _for__5, _for__4;
	OPM_LogWLn();
	OPM_LogWStr((CHAR*)"  using OP2-ASM add-on / prk", 29);
	__NEW(OPA_root, OPA_ObjDesc);
	OPA_root->left = NIL;
	OPA_root->right = NIL;
	OPA_root->next = NIL;
	f = Files_Old((CHAR*)"OPA.Data", 9);
	if (f != NIL) {
		Files_Set(&r, OFS_Rider__typ, f, 0);
		Files_ReadInt(&r, OFS_Rider__typ, &s);
		OPA_InstrTabLen = s;
		OPA_InstrTab = __NEWARR(NIL, 20, 4, 1, 1, ((ADDRESS)(OPA_InstrTabLen)));
		_for__5 = OPA_InstrTabLen - 1;
		i = 0;
		while (i <= _for__5) {
			Files_ReadString(&r, OFS_Rider__typ, (void*)(OPA_InstrTab->data)[__X(i, OPA_InstrTab->len[0])].name, 12);
			if ((OPA_InstrTab->data)[__X(i, OPA_InstrTab->len[0])].name[0] != 0x00) {
				Files_ReadInt(&r, OFS_Rider__typ, &(OPA_InstrTab->data)[__X(i, OPA_InstrTab->len[0])].start);
				Files_ReadInt(&r, OFS_Rider__typ, &(OPA_InstrTab->data)[__X(i, OPA_InstrTab->len[0])].end);
				Files_ReadSet(&r, OFS_Rider__typ, &(OPA_InstrTab->data)[__X(i, OPA_InstrTab->len[0])].target);
			}
			i += 1;
		}
		Files_ReadInt(&r, OFS_Rider__typ, &s);
		OPA_OpTabLen = s;
		OPA_OpTab = __NEWARR(NIL, 14, 2, 1, 1, ((ADDRESS)(OPA_OpTabLen)));
		_for__4 = OPA_OpTabLen - 1;
		i = 0;
		while (i <= _for__4) {
			Files_ReadInt(&r, OFS_Rider__typ, &(OPA_OpTab->data)[__X(i, OPA_OpTab->len[0])].op[0]);
			Files_ReadInt(&r, OFS_Rider__typ, &(OPA_OpTab->data)[__X(i, OPA_OpTab->len[0])].op[1]);
			Files_ReadInt(&r, OFS_Rider__typ, &(OPA_OpTab->data)[__X(i, OPA_OpTab->len[0])].op[2]);
			Files_ReadInt(&r, OFS_Rider__typ, &(OPA_OpTab->data)[__X(i, OPA_OpTab->len[0])].op0);
			Files_ReadInt(&r, OFS_Rider__typ, &(OPA_OpTab->data)[__X(i, OPA_OpTab->len[0])].op1);
			Files_ReadInt(&r, OFS_Rider__typ, &(OPA_OpTab->data)[__X(i, OPA_OpTab->len[0])].opc);
			Files_ReadInt(&r, OFS_Rider__typ, &(OPA_OpTab->data)[__X(i, OPA_OpTab->len[0])].reg);
			i += 1;
		}
		Files_Close(f);
	} else {
		OPM_LogWLn();
		OPM_LogWStr((CHAR*)"OPA.Data", 9);
		OPM_LogWStr((CHAR*)" not found, ASM not ready", 26);
	}
	OPA_SizeTab[0] = 0;
	OPA_SizeTab[1] = 1;
	OPA_SizeTab[2] = 1;
	OPA_SizeTab[3] = 1;
	OPA_SizeTab[4] = 1;
	OPA_SizeTab[5] = 2;
	OPA_SizeTab[6] = 4;
	OPA_SizeTab[7] = 4;
	OPA_SizeTab[8] = 8;
	OPA_SizeTab[9] = 4;
	OPA_SizeTab[10] = 4;
	OPA_SizeTab[11] = 4;
	OPA_SizeTab[12] = 0;
	OPA_SizeTab[13] = 4;
	OPA_SizeTab[14] = 4;
	OPA_SizeTab[15] = 0;
	OPA_SizeTab[16] = 8;
	OPA_TargetCount = 0;
	OPA_InsertTarget((CHAR*)"i386", 5, 0x01);
	OPA_InsertTarget((CHAR*)"i486", 5, 0x03);
	OPA_InsertTarget((CHAR*)"Pentium", 8, 0x07);
	OPA_InsertTarget((CHAR*)"PentiumPro", 11, 0x0f);
	OPA_InsertTarget((CHAR*)"FPU", 4, 0x010000);
	OPA_InsertTarget((CHAR*)"Privileged", 11, 0x020000);
	OPA_InsertTarget((CHAR*)"MMX", 4, 0x040000);
}

void OPA_Assemble (OPT_Node *x, BOOLEAN exported, BOOLEAN inlined)
{
	OPA_export = exported;
	OPA_inline = inlined;
	if (OPA_FirstTime) {
		OPA_BodyInit();
		OPA_FirstTime = 0;
	}
	OPA_Init();
	OPA_first = NIL;
	OPA_last = NIL;
	OPA_NewNode();
	OPA_fixlist = NIL;
	OPA_Get(&OPA_sym);
	if (OPA_sym == 20) {
		OPA_Get(&OPA_sym);
		OPA_ParseTarget();
	} else {
		OPA_Get(&OPA_sym);
		OPA_Target = 0x0;
	}
	if (OPA_Target == 0x0) {
		OPM_err(516);
		OPA_Target = 0xffffffff;
	}
	while ((OPA_sym != 10 && OPA_sym != 0)) {
		if (OPA_sym == 11) {
			OPA_ParseLabel();
		}
		if (OPA_sym == 1) {
			OPA_ParseInstruction();
		}
		while ((OPA_sym != 10 && OPA_sym != 8)) {
			OPA_Get(&OPA_sym);
			OPM_err(510);
		}
		OPA_Get(&OPA_sym);
	}
	if (OPM_noerr) {
		OPA_CheckLabels();
	}
	OPA_Close();
	OPB_Construct(29, &OPA_first, OPA_fixlist);
	*x = OPA_first;
	(*x)->conval = NIL;
}

static void EnumPtrs(void (*P)(void*))
{
	P(OPA_root);
	P(OPA_OpTab);
	P(OPA_InstrTab);
	P(OPA_first);
	P(OPA_last);
	P(OPA_fixlist);
}

__TDESC(OPA_InstrDesc, 1, 0) = {__TDFLDS("InstrDesc", 20), {-4}};
__TDESC(OPA_OpCode, 1, 0) = {__TDFLDS("OpCode", 14), {-4}};
__TDESC(OPA_Operand, 1, 1) = {__TDFLDS("Operand", 28), {24, -8}};
__TDESC(OPA_ObjDesc, 1, 5) = {__TDFLDS("ObjDesc", 64), {44, 48, 52, 56, 60, -24}};
__TDESC(OPA_FixPntDesc, 1, 2) = {__TDFLDS("FixPntDesc", 16), {4, 12, -12}};
__TDESC(OPA__1, 1, 0) = {__TDFLDS("", 36), {-4}};

export void *OPA__init(void)
{
	__DEFMOD;
	__MODULE_IMPORT(Files);
	__MODULE_IMPORT(OPB);
	__MODULE_IMPORT(OPM);
	__MODULE_IMPORT(OPS);
	__MODULE_IMPORT(OPT);
	__REGMOD("OPA", EnumPtrs);
	__INITYP(OPA_InstrDesc, OPA_InstrDesc, 0);
	__INITYP(OPA_OpCode, OPA_OpCode, 0);
	__INITYP(OPA_Operand, OPA_Operand, 0);
	__INITYP(OPA_ObjDesc, OPA_ObjDesc, 0);
	__INITYP(OPA_FixPntDesc, OPA_FixPntDesc, 0);
	__INITYP(OPA__1, OPA__1, 0);
/* BEGIN */
	OPA_FirstTime = 1;
	__ENDMOD;
}
