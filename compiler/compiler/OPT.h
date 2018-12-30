/* voc 2.1.0 [2017/09/06]. Bootstrapping compiler for address size 8, alignment 8. xtaSv */

#ifndef OPT__h
#define OPT__h

#include "SYSTEM.h"
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


import OPT_Object OPT_topScope, OPT_objects;
import OPT_Struct OPT_undftyp, OPT_bytetyp, OPT_booltyp, OPT_chartyp, OPT_sinttyp, OPT_inttyp, OPT_linttyp, OPT_hinttyp, OPT_realtyp, OPT_lrltyp, OPT_settyp, OPT_stringtyp, OPT_niltyp, OPT_notyp, OPT_ptrtyp;
import BOOLEAN OPT_SYSimported;
import INT8 OPT_nofmod;
import OPT_ModArr OPT_modules;
import INT16 OPT_modNo;
import void (*OPT_typSize)(OPT_Struct, BOOLEAN);
import OPT_Struct OPT_ToBeFixed;

import ADDRESS *OPT_ConstDesc__typ;
import ADDRESS *OPT_ObjDesc__typ;
import ADDRESS *OPT_ModDesc__typ;
import ADDRESS *OPT_StrDesc__typ;
import ADDRESS *OPT_NodeDesc__typ;

import void OPT_Close (void);
import void OPT_CloseScope (void);
import void OPT_Contextualize (OPT_Object *sentinel);
import void OPT_Export (OPS_Name modName, BOOLEAN *newsf, BOOLEAN *extsf);
import void OPT_FPrintObj (OPT_Object obj);
import void OPT_FPrintTyp (OPT_Struct typ);
import void OPT_Find (OPT_Object *res);
import void OPT_FindField (CHAR *name, ADDRESS name__len, OPT_Struct typ, OPT_Object *res, BOOLEAN mark);
import void OPT_FindImport (OPT_Object mod, OPT_Object *res);
import void OPT_FindInScope (CHAR *name, ADDRESS name__len, OPT_Object scope, OPT_Object *res);
import void OPT_Import (OPS_Name aliasName, OPS_Name impName, OPS_Name selfName);
import void OPT_Init (OPS_Name name);
import void OPT_Insert (CHAR *name, ADDRESS name__len, OPT_Object *obj);
import void OPT_MarkObj (OPT_Object obj);
import void OPT_MarkType (OPT_Struct typ);
import OPT_Const OPT_NewConst (void);
import OPT_ConstExt OPT_NewExt (void);
import OPT_Node OPT_NewNode (INT8 class);
import OPT_Object OPT_NewObj (void);
import OPT_Struct OPT_NewStr (INT8 form, INT8 comp);
import void OPT_OpenScope (INT8 level, OPT_Object owner);
import void OPT_OutMod (OPT_Module mod);
import void OPT_OutScope (OPT_Object scope, BOOLEAN public);
import void OPT_QualResolve (OPT_Object *obj, OPT_Node *x, OPT_Node *y, INT8 *distance, BOOLEAN *wrn);
import OPT_Object OPT_Resolve (CHAR *name, ADDRESS name__len, OPT_Node *x, OPT_Node *y);
import void OPT_TraverseObjects (OPT_Object top);
import void *OPT__init(void);


#endif // OPT
