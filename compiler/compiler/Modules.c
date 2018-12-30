/* voc 2.1.0 [2017/09/06]. Bootstrapping compiler for address size 8, alignment 8. xtaSv */

#define SHORTINT INT8
#define INTEGER  INT16
#define LONGINT  INT32
#define SET      UINT32

#include "SYSTEM.h"
#include "Files.h"
#include "Kernel.h"

struct Modules__2 {
	CHAR mod, entry;
	INT32 link;
};

struct Modules__1 {
	CHAR mod;
	INT16 entry, nofFixups;
	struct {
		ADDRESS len[1];
		INT32 data[1];
	} *offset;
};

struct Modules__11 {
	INT32 word[32000];
};

typedef
	struct Modules__11 *TDesc__45;

struct Modules__3 {
	BOOLEAN initialized;
	TDesc__45 tdesc;
	INT16 entry, root, nofMeth, nofInhMeth, baseMod;
	INT32 baseEntry;
};

struct Modules__22 {
	INT32 len[1];
	INT32 data[1];
};

typedef
	struct {
		ADDRESS len[1];
		struct Modules__1 data[1];
	} *Modules_DataLinkTab;

typedef
	struct Modules_Header {
		INT16 nofEntries, nofCmds, nofPtrs, nofTds, nofImps, nofLinks, nofDataLinks;
		INT32 codeSize, dataSize, refSize, conSize;
	} Modules_Header;

typedef
	struct {
		ADDRESS len[1];
		struct Modules__2 data[1];
	} *Modules_LinkTab;


export INT16 Modules_res;
export CHAR Modules_resMsg[256];
export CHAR Modules_extension[8];
static INT32 Modules_resMsgLen;
static Kernel_Name Modules_imported, Modules_importing;
static CHAR Modules_disp[16];
static BOOLEAN Modules_trace;

export ADDRESS *Modules_Header__typ;
export ADDRESS *Modules__2__typ;
export ADDRESS *Modules__1__typ;
export ADDRESS *Modules__11__typ;
export ADDRESS *Modules__3__typ;
export ADDRESS *Modules__22__typ;

static INT32 Modules_And (INT32 x, INT32 y);
static void Modules_Ch (CHAR ch);
static void Modules_Clear (void);
static void Modules_Delete (Kernel_Module m);
static void Modules_ErrMsg (INT16 res);
export Kernel_Module Modules_FindMod (CHAR *name, ADDRESS name__len);
export void Modules_Free (CHAR *name, ADDRESS name__len, BOOLEAN all);
export void Modules_InstallTermHandler (Kernel_Proc h);
static INT32 Modules_LSW (INT32 x);
static void Modules_Ln (void);
static void Modules_Load (CHAR *name, ADDRESS name__len, Kernel_Module *m);
static void Modules_LoadModule (Files_Rider *R, ADDRESS *R__typ, Kernel_Module *m);
static INT32 Modules_MSW (INT32 x);
static void Modules_ReadString (Files_Rider *R, ADDRESS *R__typ, CHAR *string, ADDRESS string__len);
static void Modules_ReadUnsigned (Files_Rider *R, ADDRESS *R__typ, INT32 *u);
static void Modules_Str (CHAR *s, ADDRESS s__len);
export Kernel_Proc Modules_ThisCommand (Kernel_Module mod, CHAR *name, ADDRESS name__len);
export Kernel_Module Modules_ThisMod (CHAR *name, ADDRESS name__len);

extern void Heap_InitHeap();

void Modules_Init(INT32 argc, ADDRESS argv)
{
	//Modules_MainStackFrame = argv;
	//Modules_ArgCount = __VAL(INT16, argc);
	//__GET(argv, Modules_ArgVector, INT32);
	
    //Modules_InitHeap(); 
    Heap_InitHeap();

	//Modules_ModulesInit();
}

static INT32 Modules_LSW (INT32 x)
{
	return (INT32)(((UINT32)x & 0xffff));
}

static INT32 Modules_MSW (INT32 x)
{
	return __LSHR(x, 16, 32);
}

static void Modules_ReadUnsigned (Files_Rider *R, ADDRESS *R__typ, INT32 *u)
{
	CHAR low, high;
	Files_Read(&*R, R__typ, (void*)&low);
	Files_Read(&*R, R__typ, (void*)&high);
	*u = __ASHL(high, 8) + low;
}

static void Modules_Ch (CHAR ch)
{
	if (Modules_resMsgLen != 255) {
		Modules_resMsg[__X(Modules_resMsgLen, 256)] = ch;
		Modules_resMsgLen += 1;
		Modules_resMsg[__X(Modules_resMsgLen, 256)] = 0x00;
	}
}

static void Modules_Str (CHAR *s, ADDRESS s__len)
{
	INT32 i;
	__DUP(s, s__len, CHAR);
	i = 0;
	while (s[__X(i, s__len)] != 0x00) {
		Modules_Ch(s[__X(i, s__len)]);
		i += 1;
	}
	__DEL(s);
}

static void Modules_Ln (void)
{
	Modules_Ch(0x0d);
}

static void Modules_Clear (void)
{
	Modules_resMsg[0] = 0x00;
	Modules_resMsgLen = 0;
}

static void Modules_ErrMsg (INT16 res)
{
	if (res != 0) {
		Modules_Clear();
		Modules_Str(Modules_importing, 32);
		if (res == 1 || res == 6) {
			Modules_Str((CHAR*)" not found", 11);
		} else if (res == 2) {
			Modules_Str((CHAR*)" not an obj-file", 17);
		} else if (res == 4) {
			Modules_Str((CHAR*)" corrupted obj file", 20);
		} else if (res == 7) {
			Modules_Str((CHAR*)" not enough space", 18);
		} else if (res == 8) {
			Modules_Str((CHAR*)" reference count not zero", 26);
		} else if (res == 9) {
			Modules_Str((CHAR*)" cyclic import", 15);
		} else if (res == 16) {
			Modules_Str((CHAR*)" imports incompatible version of ", 34);
			Modules_Str(Modules_imported, 32);
		} else if (res == 5) {
			Modules_Clear();
			Modules_Str(Modules_imported, 32);
			Modules_Ch('.');
			Modules_Str(Modules_importing, 32);
			Modules_Str((CHAR*)" command not found", 19);
		} else {
			Modules_Str((CHAR*)" unknown error code", 20);
		}
		Kernel_WriteString((CHAR*)"Modules: ", 10);
		Kernel_WriteString(Modules_resMsg, 256);
		Kernel_WriteLn();
	}
}

Kernel_Module Modules_FindMod (CHAR *name, ADDRESS name__len)
{
	Kernel_Module m;
	__DUP(name, name__len, CHAR);
	m = Kernel_modules;
	while ((m != NIL && __STRCMP(m->name, name) != 0)) {
		m = m->next;
	}
	__DEL(name);
	return m;
}

static INT32 Modules_And (INT32 x, INT32 y)
{
	return (INT32)(((UINT32)x & (UINT32)y));
}

static void Modules_ReadString (Files_Rider *R, ADDRESS *R__typ, CHAR *string, ADDRESS string__len)
{
	INT16 i;
	CHAR ch;
	i = 0;
	for (;;) {
		Files_Read(&*R, R__typ, (void*)&ch);
		if (ch == 0x00) {
			string[__X(i, string__len)] = 0x00;
			return;
		} else if (ch > 0x7f) {
			string[__X(i, string__len)] = (CHAR)((INT16)ch - 128);
			string[__X(i + 1, string__len)] = 0x00;
			return;
		} else {
			string[__X(i, string__len)] = ch;
			i += 1;
		}
	}
}

static struct LoadModule__12 {
	Files_Rider *R;
	ADDRESS *R__typ;
	Kernel_Module *m;
	Modules_DataLinkTab *dataLinks;
	Modules_Header *head;
	struct {
		ADDRESS len[1];
		struct Modules__3 data[1];
	} **types;
	struct LoadModule__12 *lnk;
} *LoadModule__12_s;

static void BuildModuleBlock__15 (Kernel_Module m, Modules_Header h);
static void CheckUseBlock__17 (Files_Rider *R, ADDRESS *R__typ, Kernel_Module M);
static BOOLEAN Expect__23 (CHAR tag);
static void FindTDescAdr__25 (Kernel_Module M, INT32 fp, INT32 *adr);
static void Fixup__27 (Kernel_Module m, Modules_LinkTab link);
static void FixupCall__29 (INT32 code, INT32 link, INT32 fixval);
static void FixupVar__31 (INT32 code, INT32 link, INT32 fixval);
static void InitType__33 (INT32 i);
static void InitTypes__35 (void);
static void LoadExpBlock__37 (Files_Rider *R, ADDRESS *R__typ, Kernel_Module M);
static void ReadTypes__42 (Files_Rider *R, ADDRESS *R__typ);

static void FixupCall__29 (INT32 code, INT32 link, INT32 fixval)
{
	INT32 instr, nextlink, jmp;
	do {
		__GET(code + link, instr, INT32);
		nextlink = Modules_MSW(instr);
		__GET((code + link) - 1, jmp, INT32);
		if (__MASK(Modules_LSW(jmp), -256) == 232) {
			__PUT(code + link, fixval - ((code + link) + 4), INT32);
		} else {
			__PUT(code + link, fixval, INT32);
		}
		link = nextlink;
	} while (!(link == 65535));
}

static void FixupVar__31 (INT32 code, INT32 link, INT32 fixval)
{
	INT16 nofFixups;
	INT32 i, val;
	nofFixups = ((*LoadModule__12_s->dataLinks)->data)[__X(link, (*LoadModule__12_s->dataLinks)->len[0])].nofFixups;
	i = 0;
	while (i < nofFixups) {
		__GET(code + (((*LoadModule__12_s->dataLinks)->data)[__X(link, (*LoadModule__12_s->dataLinks)->len[0])].offset->data)[__X(i, ((*LoadModule__12_s->dataLinks)->data)[__X(link, (*LoadModule__12_s->dataLinks)->len[0])].offset->len[0])], val, INT32);
		__PUT(code + (((*LoadModule__12_s->dataLinks)->data)[__X(link, (*LoadModule__12_s->dataLinks)->len[0])].offset->data)[__X(i, ((*LoadModule__12_s->dataLinks)->data)[__X(link, (*LoadModule__12_s->dataLinks)->len[0])].offset->len[0])], val + fixval, INT32);
		i += 1;
	}
}

static void Fixup__27 (Kernel_Module m, Modules_LinkTab link)
{
	INT32 i, val, offs;
	INT16 modNo, nofFixups;
	INT32 codebase;
	CHAR Error[32];
	INT32 Num;
	codebase = (ADDRESS)&(m->code->data)[0];
	modNo = (INT16)((*LoadModule__12_s->dataLinks)->data)[0].mod;
	nofFixups = ((*LoadModule__12_s->dataLinks)->data)[0].nofFixups;
	if (((*LoadModule__12_s->head).nofDataLinks > 0 && modNo == 0)) {
		i = 0;
		while (i < nofFixups) {
			__GET(codebase + (((*LoadModule__12_s->dataLinks)->data)[0].offset->data)[__X(i, ((*LoadModule__12_s->dataLinks)->data)[0].offset->len[0])], val, INT32);
			__PUT(codebase + (((*LoadModule__12_s->dataLinks)->data)[0].offset->data)[__X(i, ((*LoadModule__12_s->dataLinks)->data)[0].offset->len[0])], val + m->sb, INT32);
			i += 1;
		}
	}
	i = 0;
	while (i < (*LoadModule__12_s->head).nofLinks) {
		if ((INT16)(link->data)[__X(i, link->len[0])].mod == 0) {
			switch ((INT16)(link->data)[__X(i, link->len[0])].entry) {
				case 255: 
					offs = (link->data)[__X(i, link->len[0])].link;
					while (offs != 65535) {
						__GET(m->sb + offs, val, INT32);
						__PUT(m->sb + offs, codebase + Modules_LSW(val), INT32);
						offs = Modules_MSW(val);
					}
					break;
				case 254: 
					offs = (link->data)[__X(i, link->len[0])].link;
					while (offs != 65535) {
						__GET(codebase + offs, val, INT32);
						__PUT(codebase + offs, (m->entries->data)[__XF(Modules_LSW(val), m->entries->len[0])], INT32);
						offs = Modules_MSW(val);
					}
					break;
				case 253: 
					offs = (link->data)[__X(i, link->len[0])].link;
					while (offs != 65535) {
						__GET(codebase + offs, val, INT32);
						__PUT(codebase + offs, Kernel_runtime[0] - ((codebase + offs) + 4), INT32);
						offs = Modules_MSW(val);
					}
					break;
				case 252: 
					offs = (link->data)[__X(i, link->len[0])].link;
					while (offs != 65535) {
						__GET(codebase + offs, val, INT32);
						__PUT(codebase + offs, Kernel_runtime[1] - ((codebase + offs) + 4), INT32);
						offs = Modules_MSW(val);
					}
					break;
				case 251: 
					offs = (link->data)[__X(i, link->len[0])].link;
					while (offs != 65535) {
						__GET(codebase + offs, val, INT32);
						__PUT(codebase + offs, Kernel_runtime[2] - ((codebase + offs) + 4), INT32);
						offs = Modules_MSW(val);
					}
					break;
				default: 
					__MOVE("Unsupported kernel procedure", Error, 29);
					Num = (INT16)(link->data)[__X(i, link->len[0])].entry;
					__HALT(98);
					break;
			}
		} else {
			__HALT(99);
		}
		i += 1;
	}
}

static struct LoadExpBlock__37__38 {
	Files_Rider *R;
	ADDRESS *R__typ;
	struct {
		ADDRESS len[1];
		INT32 data[1];
	} **struct_, **old;
	INT32 *nofStr;
	Kernel_ExportPtr *exp;
	struct LoadExpBlock__37__38 *lnk;
} *LoadExpBlock__37__38_s;

static void LoadScope__39 (Kernel_ExportDesc *scope, ADDRESS *scope__typ, INT16 level, INT32 adr);

static void LoadScope__39 (Kernel_ExportDesc *scope, ADDRESS *scope__typ, INT16 level, INT32 adr)
{
	INT16 no, no2;
	INT32 fp, off, _for__42, _for__41;
	Files_ReadBytes(&*LoadExpBlock__37__38_s->R, LoadExpBlock__37__38_s->R__typ, (void*)&(*scope).nofExp, 2, 2);
	no = 0;
	no2 = 0;
	if ((*scope).nofExp != 0) {
		(*scope).dsc = __NEWARR(POINTER__typ, 4, 4, 1, 1, ((ADDRESS)((*scope).nofExp)));
		_for__42 = (*scope).nofExp - 1;
		off = 0;
		while (off <= _for__42) {
			__NEW(((*scope).dsc->data)[__X(off, (*scope).dsc->len[0])], Kernel_ExportDesc);
			off += 1;
		}
		((*scope).dsc->data)[0]->adr = adr;
	}
	if (level == 1) {
		*LoadExpBlock__37__38_s->nofStr += 1;
        //if ((*LoadExpBlock__37__38_s->struct_)->len[ 0 ] == 1) {
//		if (*LoadExpBlock__37__38_s->nofStr == 1) { //TODO
		if ( *LoadExpBlock__37__38_s->nofStr == (*LoadExpBlock__37__38_s->struct_)->len[ 0 ] ) {
//    IF nofStr = 1 (* LEN(struct) *)  THEN
			*LoadExpBlock__37__38_s->old = *LoadExpBlock__37__38_s->struct_;
			*LoadExpBlock__37__38_s->struct_ = __NEWARR(NIL, 4, 4, 1, 1, ((ADDRESS)((__ASHL(*LoadExpBlock__37__38_s->nofStr, 1)))));
			_for__41 = *LoadExpBlock__37__38_s->nofStr - 1;
			off = 0;
			while (off <= _for__41) {
				((*LoadExpBlock__37__38_s->struct_)->data)[__X(off, (*LoadExpBlock__37__38_s->struct_)->len[0])] = ((*LoadExpBlock__37__38_s->old)->data)[__X(off, (*LoadExpBlock__37__38_s->old)->len[0])];
				off += 1;
			}
		}
		((*LoadExpBlock__37__38_s->struct_)->data)[__X(*LoadExpBlock__37__38_s->nofStr, (*LoadExpBlock__37__38_s->struct_)->len[0])] = (ADDRESS)scope;
	}
	Files_ReadNum(&*LoadExpBlock__37__38_s->R, LoadExpBlock__37__38_s->R__typ, &fp);
	while (fp != 0) {
		if (fp == 1) {
			Files_ReadNum(&*LoadExpBlock__37__38_s->R, LoadExpBlock__37__38_s->R__typ, &off);
			if (off < 0) {
				*LoadExpBlock__37__38_s->exp = (Kernel_ExportPtr)(ADDRESS)((*LoadExpBlock__37__38_s->struct_)->data)[__X(-off, (*LoadExpBlock__37__38_s->struct_)->len[0])];
				((*scope).dsc->data)[__X(no2, (*scope).dsc->len[0])]->nofExp = (*LoadExpBlock__37__38_s->exp)->nofExp;
				((*scope).dsc->data)[__X(no2, (*scope).dsc->len[0])]->dsc = (*LoadExpBlock__37__38_s->exp)->dsc;
			} else {
                //TODO see Modules.Mod
				LoadScope__39(&*((*scope).dsc->data)[__X(no2, (*scope).dsc->len[0])], __TYPEOF(((*scope).dsc->data)[__X(no2, (*scope).dsc->len[0])]), 1, off);
			}
		} else {
			if (level == 0) {
				Files_ReadNum(&*LoadExpBlock__37__38_s->R, LoadExpBlock__37__38_s->R__typ, &((*scope).dsc->data)[__X(no, (*scope).dsc->len[0])]->adr);
			}
			((*scope).dsc->data)[__X(no, (*scope).dsc->len[0])]->fp = fp;
			no2 = no;
			no += 1;
		}
		Files_ReadNum(&*LoadExpBlock__37__38_s->R, LoadExpBlock__37__38_s->R__typ, &fp);
	}
}

static void LoadExpBlock__37 (Files_Rider *R, ADDRESS *R__typ, Kernel_Module M)
{
	struct {
		ADDRESS len[1];
		INT32 data[1];
	} *struct_, *old;
	INT32 nofStr;
	Kernel_ExportPtr exp;
	struct LoadExpBlock__37__38 _s;
	_s.R = R; _s.R__typ = R__typ;
	_s.struct_ = &struct_;
	_s.old = &old;
	_s.nofStr = &nofStr;
	_s.exp = &exp;
	_s.lnk = LoadExpBlock__37__38_s;
	LoadExpBlock__37__38_s = &_s;
	struct_ = __NEWARR(NIL, 4, 4, 1, 1, 64);
	nofStr = 0;
	LoadScope__39(&M->export_, Kernel_ExportDesc__typ, 0, 0);
	LoadExpBlock__37__38_s = _s.lnk;
}

static struct CheckUseBlock__17__18 {
	Files_Rider *R;
	ADDRESS *R__typ;
	Kernel_Module *M;
	Kernel_Module *mod;
	Kernel_Name *name;
	struct CheckUseBlock__17__18 *lnk;
} *CheckUseBlock__17__18_s;

static void CheckScope__19 (Kernel_ExportDesc scope, INT16 level);
static void Err__21 (void);

static void Err__21 (void)
{
	if (Modules_res == 0) {
		__COPY((*CheckUseBlock__17__18_s->mod)->name, Modules_imported, 32);
		Modules_res = 16;
		Modules_ErrMsg(Modules_res);
	} else {
		Modules_Ch(0x09);
	}
}

static void CheckScope__19 (Kernel_ExportDesc scope, INT16 level)
{
	INT32 fp, link, i, tdadr;
	Kernel_ExportPtr tadr;
	BOOLEAN tmpErr;
	tmpErr = level == -1;
	i = 0;
	Files_ReadNum(&*CheckUseBlock__17__18_s->R, CheckUseBlock__17__18_s->R__typ, &fp);
	while (fp != 0) {
		if (fp == 1) {
			Files_ReadNum(&*CheckUseBlock__17__18_s->R, CheckUseBlock__17__18_s->R__typ, &link);
			if (tmpErr) {
				CheckScope__19(*(scope.dsc->data)[__X(i, scope.dsc->len[0])], -1); //TODO see Modules.Mod
			} else {
				if ((scope.dsc->data)[__X(i, scope.dsc->len[0])]->dsc != NIL) {
					if (link != 0) {
						tadr = (Kernel_ExportPtr)(ADDRESS)((ADDRESS)&((scope.dsc->data)[__X(i, scope.dsc->len[0])]->dsc->data)[0]);
						__GET((*CheckUseBlock__17__18_s->mod)->sb + tadr->adr, tdadr, INT32);
						__PUT((*CheckUseBlock__17__18_s->M)->sb - link, tdadr, INT32);
					}
				}
				CheckScope__19(*(scope.dsc->data)[__X(i, scope.dsc->len[0])], 1); //TODO see Modules.Mod
			}
		} else {
			Modules_ReadString(&*CheckUseBlock__17__18_s->R, CheckUseBlock__17__18_s->R__typ, (void*)*CheckUseBlock__17__18_s->name, 32);
			if (level >= 0) {
				tmpErr = 0;
				if (level == 0) {
					Files_ReadNum(&*CheckUseBlock__17__18_s->R, CheckUseBlock__17__18_s->R__typ, &link);
				}
				i = 0;
				while ((i < scope.nofExp && (scope.dsc->data)[__X(i, scope.dsc->len[0])]->fp != fp)) {
					i += 1;
				}
				if (i >= scope.nofExp) {
					Err__21();
					tmpErr = 1;
					Modules_Ln();
					Modules_Ch(0x09);
					if (__STRCMP(*CheckUseBlock__17__18_s->name, "@") == 0) {
						Modules_Str((CHAR*)"RECORD ", 8);
					} else {
						Modules_Str(*CheckUseBlock__17__18_s->name, 32);
					}
					Modules_Str((CHAR*)" incompatible", 14);
					i -= 1;
				} else if ((level == 0 && link != 0)) {
					if (Modules_And(link, 2147483648LL) == 0) {
						FixupVar__31((ADDRESS)&((*CheckUseBlock__17__18_s->M)->code->data)[0], link, (*CheckUseBlock__17__18_s->mod)->sb + (scope.dsc->data)[__X(i, scope.dsc->len[0])]->adr);
					} else {
						FixupCall__29((ADDRESS)&((*CheckUseBlock__17__18_s->M)->code->data)[0], (INT64)link - 2147483648LL, (scope.dsc->data)[__X(i, scope.dsc->len[0])]->adr + (ADDRESS)&((*CheckUseBlock__17__18_s->mod)->code->data)[0]);
					}
				}
			}
		}
		Files_ReadNum(&*CheckUseBlock__17__18_s->R, CheckUseBlock__17__18_s->R__typ, &fp);
	}
}

static void CheckUseBlock__17 (Files_Rider *R, ADDRESS *R__typ, Kernel_Module M)
{
	Kernel_Module mod;
	Kernel_Name name;
	struct CheckUseBlock__17__18 _s;
	_s.R = R; _s.R__typ = R__typ;
	_s.M = &M;
	_s.mod = &mod;
	_s.name = (void*)name;
	_s.lnk = CheckUseBlock__17__18_s;
	CheckUseBlock__17__18_s = &_s;
	Modules_ReadString(&*R, R__typ, (void*)name, 32);
	while ((name[0] != 0x00 && Modules_res == 0)) {
		Modules_Load(name, 32, &mod);
		if (Modules_res == 0) {
			CheckScope__19(mod->export_, 0);
		}
		Modules_ReadString(&*R, R__typ, (void*)name, 32);
	}
	CheckUseBlock__17__18_s = _s.lnk;
}

static BOOLEAN Expect__23 (CHAR tag)
{
	CHAR ch;
	Files_Read(&*LoadModule__12_s->R, LoadModule__12_s->R__typ, (void*)&ch);
	if (ch != tag) {
		Modules_res = 4;
		Modules_ErrMsg(Modules_res);
		return 0;
	} else {
		return 1;
	}
	__RETCHK;
}

static void FindTDescAdr__25 (Kernel_Module M, INT32 fp, INT32 *adr)
{
	INT16 i;
	i = 0;
	while ((i < M->export_.nofExp && (M->export_.dsc->data)[__X(i, M->export_.dsc->len[0])]->fp != fp)) {
		i += 1;
	}
	if (i < M->export_.nofExp) {
		*adr = ((M->export_.dsc->data)[__X(i, M->export_.dsc->len[0])]->dsc->data)[0]->adr;
	} else {
		__HALT(99);
	}
}

static void ReadTypes__42 (Files_Rider *R, ADDRESS *R__typ)
{
	INT32 i, j, k, tdsize, recordSize;
	INT16 tdEntry, nofMethods, nofNewMeths, mthNo, nofPointers, root, entryNo;
	TDesc__45 td;
	Kernel_Name name;
	CHAR ch;
	INT32 _for__44;
	if ((*LoadModule__12_s->m)->tdescs->len[0] != 0) {
		*LoadModule__12_s->types = __NEWARR(Modules__3__typ, 24, 4, 1, 1, ((ADDRESS)(((*LoadModule__12_s->m)->tdescs->len[0]))));
		_for__44 = (*LoadModule__12_s->m)->tdescs->len[0] - 1;
		i = 0;
		while (i <= _for__44) {
			((*LoadModule__12_s->types)->data)[__X(i, (*LoadModule__12_s->types)->len[0])].initialized = 0;
			Files_ReadLInt(&*R, R__typ, &recordSize);
			Files_ReadInt(&*R, R__typ, &tdEntry);
			((*LoadModule__12_s->types)->data)[__X(i, (*LoadModule__12_s->types)->len[0])].entry = tdEntry;
			Files_ReadInt(&*R, R__typ, &((*LoadModule__12_s->types)->data)[__X(i, (*LoadModule__12_s->types)->len[0])].baseMod);
			Files_ReadLInt(&*R, R__typ, &((*LoadModule__12_s->types)->data)[__X(i, (*LoadModule__12_s->types)->len[0])].baseEntry);
			Files_ReadInt(&*R, R__typ, &nofMethods);
			((*LoadModule__12_s->types)->data)[__X(i, (*LoadModule__12_s->types)->len[0])].nofMeth = nofMethods;
			Files_ReadInt(&*R, R__typ, &((*LoadModule__12_s->types)->data)[__X(i, (*LoadModule__12_s->types)->len[0])].nofInhMeth);
			Files_ReadInt(&*R, R__typ, &nofNewMeths);
			Files_ReadInt(&*R, R__typ, &nofPointers);
			Files_ReadString(&*R, R__typ, (void*)name, 32);
			root = ((13 + nofMethods) + 16) + 1;
			root += __MASK(-root + 2, -4);
			((*LoadModule__12_s->types)->data)[__X(i, (*LoadModule__12_s->types)->len[0])].root = root;
			tdsize = __ASHL(((root + 1) + nofPointers) + 1, 2);
			__SYSNEW(td, tdsize - 24);
			(INT32)(ADDRESS)td -= 24;
			((*LoadModule__12_s->types)->data)[__X(i, (*LoadModule__12_s->types)->len[0])].tdesc = td;
			td->word[0] = tdsize;
			td->word[1] = -4;
			td->word[2] = (ADDRESS)&td->word[__X(root, 32000)];
			td->word[3] = 0;
			k = (ADDRESS)&td->word[4];
			j = 0;
			do {
				ch = name[__X(j, 32)];
				__PUT(k, ch, CHAR);
				j += 1;
				k += 1;
			} while (!(ch == 0x00));
			td->word[12] = (ADDRESS)&**LoadModule__12_s->m;
			j = 0;
			while (j < nofNewMeths) {
				Files_ReadInt(&*R, R__typ, &mthNo);
				Files_ReadInt(&*R, R__typ, &entryNo);
				td->word[__X((root + -18) - mthNo, 32000)] = ((*LoadModule__12_s->m)->entries->data)[__X(entryNo, (*LoadModule__12_s->m)->entries->len[0])];
				j += 1;
			}
			__ASSERT((ADDRESS)&td->word[0] != 0, 0);
			td->word[__X(root - 1, 32000)] = (ADDRESS)&td->word[0];
			td->word[__X(root, 32000)] = recordSize;
			__PUT((*LoadModule__12_s->m)->sb + tdEntry, (ADDRESS)&td->word[__X(root, 32000)], INT32);
			((*LoadModule__12_s->m)->tdescs->data)[__X(i, (*LoadModule__12_s->m)->tdescs->len[0])] = (ADDRESS)&td->word[__X(root, 32000)];
			j = 0;
			while (j < nofPointers) {
				Files_ReadLInt(&*R, R__typ, &td->word[__X((root + 1) + j, 32000)]);
				j += 1;
			}
			td->word[__X((root + 1) + nofPointers, 32000)] = -__ASHL(nofPointers + 1, 2);
			i += 1;
		}
	}
}

static void InitType__33 (INT32 i)
{
	INT32 t, baseType, tag, entry;
	INT16 extlev, n, root, baseModNo;
	TDesc__45 td;
	Kernel_Module baseMod;
	if (!((*LoadModule__12_s->types)->data)[__X(i, (*LoadModule__12_s->types)->len[0])].initialized) {
		td = ((*LoadModule__12_s->types)->data)[__X(i, (*LoadModule__12_s->types)->len[0])].tdesc;
		baseModNo = ((*LoadModule__12_s->types)->data)[__X(i, (*LoadModule__12_s->types)->len[0])].baseMod;
		extlev = 0;
		root = ((*LoadModule__12_s->types)->data)[__X(i, (*LoadModule__12_s->types)->len[0])].root;
		if (baseModNo != -1) {
			if (baseModNo == 0) {
				t = 0;
				while ((t < (*LoadModule__12_s->m)->tdescs->len[0] && ((*LoadModule__12_s->types)->data)[__X(t, (*LoadModule__12_s->types)->len[0])].entry != ((*LoadModule__12_s->types)->data)[__X(i, (*LoadModule__12_s->types)->len[0])].baseEntry)) {
					t += 1;
				}
				InitType__33(t);
			}
			if (baseModNo > 0) {
				baseMod = ((*LoadModule__12_s->m)->imports->data)[__X(baseModNo - 1, (*LoadModule__12_s->m)->imports->len[0])];
				FindTDescAdr__25(baseMod, ((*LoadModule__12_s->types)->data)[__X(i, (*LoadModule__12_s->types)->len[0])].baseEntry, &((*LoadModule__12_s->types)->data)[__X(i, (*LoadModule__12_s->types)->len[0])].baseEntry);
			} else {
				baseMod = *LoadModule__12_s->m;
			}
			__GET(baseMod->sb + ((*LoadModule__12_s->types)->data)[__X(i, (*LoadModule__12_s->types)->len[0])].baseEntry, baseType, INT32);
			__GET(baseType + -2, tag, INT32);
			while (tag != 0) {
				td->word[__X((root + -2) - extlev, 32000)] = tag;
				extlev += 1;
				__GET(baseType + __ASHL(-2 - extlev, 2), tag, INT32);
			}
			n = ((*LoadModule__12_s->types)->data)[__X(i, (*LoadModule__12_s->types)->len[0])].nofInhMeth;
			while (n > 0) {
				n -= 1;
				entry = td->word[__X((root + -18) - n, 32000)];
				if (entry == 0) {
					__GET(baseType + __ASHL(-18 - n, 2), td->word[__X((root + -18) - n, 32000)], INT32);
				}
			}
		}
		td->word[3] = extlev;
		td->word[__X((root + -2) - extlev, 32000)] = (ADDRESS)&td->word[__X(root, 32000)];
		((*LoadModule__12_s->types)->data)[__X(i, (*LoadModule__12_s->types)->len[0])].initialized = 1;
	}
}

static void InitTypes__35 (void)
{
	INT32 i;
	i = 0;
	while (i < (*LoadModule__12_s->m)->tdescs->len[0]) {
		InitType__33(i);
		i += 1;
	}
}

static void BuildModuleBlock__15 (Kernel_Module m, Modules_Header h)
{
	INT32 t, size, gvarSize;
	struct Modules__22 *arrPtr;
	size = __ASHL(((((((__ASHR(__ASHL(h.nofEntries, 2) + 35, 4) + __ASHR(h.nofCmds * 36 + 35, 4)) + __ASHR(__ASHL(h.nofPtrs, 2) + 35, 4)) + __ASHR(__ASHL(h.nofTds, 2) + 35, 4)) + __ASHR(__ASHL(h.nofImps, 2) + 35, 4)) + __ASHR(((h.dataSize + __MASK(-h.dataSize, -8)) + h.conSize) + 35, 4)) + __ASHR(h.codeSize + 35, 4)) + __ASHR(h.refSize + 35, 4), 4);
	__SYSNEW(arrPtr, size);
	//__GET((INT32)(ADDRESS)arrPtr, t, INT32);
	//__PUT((ADDRESS)&m->entries, (ADDRESS)arrPtr + 4, INT32);
	//arrPtr->len[0] = h.nofEntries;

	__PUT((ADDRESS)&m->entries, (ADDRESS)arrPtr, INT32);
    //m->entries = (ADDRESS)arrPtr;
	//__PUT((ADDRESS)&(m->entries->data[ 0 ]), (ADDRESS)arrPtr + 4, INT32);
    //m->entries->data[ 0 ] = (ADDRESS)arrPtr + 8;
        m->entries->len[ 0 ] = h.nofEntries;

	(INT32)(ADDRESS)arrPtr += __ASHL(__ASHR(__ASHL(h.nofEntries, 2) + 35, 4), 4);

	//__PUT((INT32)(ADDRESS)arrPtr, t, INT32);
	//__PUT((ADDRESS)&m->cmds, (ADDRESS)arrPtr + 4, INT32);
	__PUT((ADDRESS)&m->cmds, (ADDRESS)arrPtr, INT32);
	//__PUT((ADDRESS)&m->cmds->data[ 0 ], (ADDRESS)arrPtr + 4, INT32);
	m->cmds->len[0] = h.nofCmds;

	(INT32)(ADDRESS)arrPtr += __ASHL(__ASHR(h.nofCmds * 36 + 35, 4), 4);

	//__PUT((INT32)(ADDRESS)arrPtr, t, INT32);
	//__PUT((ADDRESS)&m->ptrTab, (ADDRESS)arrPtr + 4, INT32);
	//arrPtr->len[0] = h.nofPtrs;
	__PUT((ADDRESS)&m->ptrTab, (ADDRESS)arrPtr, INT32);
	//__PUT((ADDRESS)&m->ptrTab->data[ 0 ], (ADDRESS)arrPtr + 4, INT32);
	m->ptrTab->len[0] = h.nofPtrs;

	(INT32)(ADDRESS)arrPtr += __ASHL(__ASHR(__ASHL(h.nofPtrs, 2) + 35, 4), 4);
	
	//__PUT((INT32)(ADDRESS)arrPtr, t, INT32);
	//__PUT((ADDRESS)&m->tdescs, (ADDRESS)arrPtr + 4, INT32);
	//arrPtr->len[0] = h.nofTds;
	__PUT((ADDRESS)&m->tdescs, (ADDRESS)arrPtr, INT32);
	//__PUT((ADDRESS)&m->tdescs->data[ 0 ], (ADDRESS)arrPtr + 4, INT32);
	m->tdescs->len[0] = h.nofTds;

	(INT32)(ADDRESS)arrPtr += __ASHL(__ASHR(__ASHL(h.nofTds, 2) + 35, 4), 4);

	//__PUT((INT32)(ADDRESS)arrPtr, t, INT32);
	//__PUT((ADDRESS)&m->imports, (ADDRESS)arrPtr + 4, INT32);
	//arrPtr->len[0] = h.nofImps;
	__PUT((ADDRESS)&m->imports, (ADDRESS)arrPtr, INT32);
	//__PUT((ADDRESS)&m->imports->data[ 0 ], (ADDRESS)arrPtr + 4, INT32);
	m->imports->len[0] = h.nofImps;

	(INT32)(ADDRESS)arrPtr += __ASHL(__ASHR(__ASHL(h.nofImps, 2) + 35, 4), 4);

	//__PUT((INT32)(ADDRESS)arrPtr, t, INT32);
	//__PUT((ADDRESS)&m->data, (ADDRESS)arrPtr + 4, INT32);
    //m->data->data[ 0 ] = (ADDRESS)arrPtr;
	__PUT((ADDRESS)&m->data, (ADDRESS)arrPtr, INT32);
	//__PUT((ADDRESS)&m->data->data[ 0 ], (ADDRESS)arrPtr + 4, INT32);

	gvarSize = h.dataSize + __MASK(-h.dataSize, -8);
	m->sb = ((ADDRESS)arrPtr->data) + gvarSize; //TODO test it
	//arrPtr->len[0] = gvarSize + h.conSize;
	m->data->len[0] = gvarSize + h.conSize;

	(INT32)(ADDRESS)arrPtr += __ASHL(__ASHR((gvarSize + h.conSize) + 35, 4), 4);

 //   __PUT((INT32)(ADDRESS)arrPtr, t, INT32);
	//__PUT((ADDRESS)&m->code, (ADDRESS)arrPtr + 4, INT32);
	//arrPtr->len[0] = h.codeSize;
	__PUT((ADDRESS)&m->code, (ADDRESS)arrPtr, INT32);
	//__PUT((ADDRESS)&m->code->data[ 0 ], (ADDRESS)arrPtr + 4, INT32);
	m->code->len[0] = h.codeSize;

	(INT32)(ADDRESS)arrPtr += __ASHL(__ASHR(h.codeSize + 35, 4), 4);

 //   __PUT((INT32)(ADDRESS)arrPtr, t, INT32);
	//__PUT((ADDRESS)&m->refs, (ADDRESS)arrPtr + 4, INT32);
	//arrPtr->len[0] = h.refSize;
	__PUT((ADDRESS)&m->refs, (ADDRESS)arrPtr, INT32);
	//__PUT((ADDRESS)&m->refs->data[ 0 ], (ADDRESS)arrPtr + 4, INT32);
	m->refs->len[0] = h.refSize;
}

static void Modules_LoadModule (Files_Rider *R, ADDRESS *R__typ, Kernel_Module *m)
{
	CHAR ch;
	INT32 i, mno, j, symSize, e, k, t;
	Kernel_Module imp;
	Kernel_Proc body;
	Modules_LinkTab linkTab;
	Modules_DataLinkTab dataLinks;
	Modules_Header head;
	struct {
		ADDRESS len[1];
		struct Modules__3 data[1];
	} *types;
	struct {
		ADDRESS len[1];
		Kernel_Name data[1];
	} *mods;
	INT32 _for__14, _for__13;
	struct LoadModule__12 _s;
	_s.R = R; _s.R__typ = R__typ;
	_s.m = m;
	_s.dataLinks = &dataLinks;
	_s.head = &head;
	_s.types = &types;
	_s.lnk = LoadModule__12_s;
	LoadModule__12_s = &_s;

    return; //TODO

	Modules_res = 0;
	Modules_Clear();
	__NEW(*m, Kernel_ModuleDesc);
	(*m)->init = 0;
	(*m)->refcnt = 0;
	(*m)->term = NIL;
	Files_ReadNum(&*R, R__typ, &symSize);
	Files_Set(&*R, R__typ, Files_Base(&*R, R__typ), Files_Pos(&*R, R__typ) + symSize);
	Files_ReadLInt(&*R, R__typ, &head.refSize);
	Files_ReadInt(&*R, R__typ, &head.nofEntries);
	Files_ReadInt(&*R, R__typ, &head.nofCmds);
	Files_ReadInt(&*R, R__typ, &head.nofPtrs);
	Files_ReadInt(&*R, R__typ, &head.nofTds);
	Files_ReadInt(&*R, R__typ, &head.nofImps);
	Files_ReadInt(&*R, R__typ, &head.nofDataLinks);
	Files_ReadInt(&*R, R__typ, &head.nofLinks);
	Files_ReadLInt(&*R, R__typ, &head.dataSize);
	Modules_ReadUnsigned(&*R, R__typ, &head.conSize);
	Modules_ReadUnsigned(&*R, R__typ, &head.codeSize);
	Files_ReadString(&*R, R__typ, (void*)(*m)->name, 32);
	__MOVE((*m)->name, Modules_importing, 32);
	(*m)->nofimp = -1;
	BuildModuleBlock__15(*m, head);
	if (Modules_res != 0) {
		*m = NIL;
		LoadModule__12_s = _s.lnk;
		return;
	}
	if (Modules_trace) {
		Kernel_WriteHex((ADDRESS)&((*m)->code->data)[0], 8);
		Kernel_WriteChar(' ');
		Kernel_WriteString((*m)->name, 32);
		Kernel_WriteLn();
	}
	if (!Expect__23(0x82)) {
		LoadModule__12_s = _s.lnk;
		return;
	}
	i = 0;
	t = (ADDRESS)&((*m)->code->data)[0];
	while (i < head.nofEntries) {
		Modules_ReadUnsigned(&*R, R__typ, &e);
		((*m)->entries->data)[__X(i, (*m)->entries->len[0])] = t + e;
		i += 1;
	}
	if (!Expect__23(0x83)) {
		LoadModule__12_s = _s.lnk;
		return;
	}
	i = 0;
	while (i < head.nofCmds) {
		Files_ReadString(&*R, R__typ, (void*)((*m)->cmds->data)[__X(i, (*m)->cmds->len[0])].name, 32);
		Modules_ReadUnsigned(&*R, R__typ, &e);
		((*m)->cmds->data)[__X(i, (*m)->cmds->len[0])].adr = t + e;
		i += 1;
	}
	if (!Expect__23(0x84)) {
		LoadModule__12_s = _s.lnk;
		return;
	}
	i = 0;
	t = (*m)->sb;
	while (i < head.nofPtrs) {
		Files_ReadLInt(&*R, R__typ, &k);
		((*m)->ptrTab->data)[__X(i, (*m)->ptrTab->len[0])] = t + k;
		i += 1;
	}
	if (!Expect__23(0x85)) {
		LoadModule__12_s = _s.lnk;
		return;
	}
		
    mno = 0; //TODO

	if (head.nofImps != 0) {
		mods = __NEWARR(NIL, 1, 1, 2, 1, ((ADDRESS)(head.nofImps)), 32);
		mno = 0;
		while ((mno < head.nofImps && Modules_res == 0)) {
			Modules_ReadString(&*R, R__typ, (void*)(mods->data)[__X(mno, mods->len[0])], 32);
			Modules_Load((mods->data)[__X(mno, mods->len[0])], 32, &imp);
			if (Modules_res != 0) {
				LoadModule__12_s = _s.lnk;
				return;
			}
			((*m)->imports->data)[__X(mno, (*m)->imports->len[0])] = imp;
			mno += 1;
		}
	}
	__COPY((*m)->name, Modules_importing, 32);
	if (!Expect__23(0x8d)) {
		LoadModule__12_s = _s.lnk;
		return;
	}
	if (head.nofDataLinks != 0) {
		dataLinks = __NEWARR(Modules__1__typ, 12, 4, 1, 1, ((ADDRESS)(head.nofDataLinks)));
		_for__14 = head.nofDataLinks - 1;
		i = 0;
		while (i <= _for__14) {
			Files_Read(&*R, R__typ, (void*)&(dataLinks->data)[__X(i, dataLinks->len[0])].mod);
			Files_ReadInt(&*R, R__typ, &(dataLinks->data)[__X(i, dataLinks->len[0])].entry);
			Files_ReadInt(&*R, R__typ, &(dataLinks->data)[__X(i, dataLinks->len[0])].nofFixups);
			if ((dataLinks->data)[__X(i, dataLinks->len[0])].nofFixups > 0) {
				(dataLinks->data)[__X(i, dataLinks->len[0])].offset = __NEWARR(NIL, 4, 4, 1, 1, ((ADDRESS)((dataLinks->data)[__X(i, dataLinks->len[0])].nofFixups)));
				j = 0;
				while (j < (dataLinks->data)[__X(i, dataLinks->len[0])].nofFixups) {
					Modules_ReadUnsigned(&*R, R__typ, &((dataLinks->data)[__X(i, dataLinks->len[0])].offset->data)[__X(j, (dataLinks->data)[__X(i, dataLinks->len[0])].offset->len[0])]);
					j += 1;
				}
			} else {
				(dataLinks->data)[__X(i, dataLinks->len[0])].offset = NIL;
			}
			i += 1;
		}
	}
	if (!Expect__23(0x86)) {
		LoadModule__12_s = _s.lnk;
		return;
	}
	if (head.nofLinks != 0) {
		linkTab = __NEWARR(NIL, 8, 4, 1, 1, ((ADDRESS)(head.nofLinks)));
		_for__13 = head.nofLinks - 1;
		i = 0;
		while (i <= _for__13) {
			Files_Read(&*R, R__typ, (void*)&(linkTab->data)[__X(i, linkTab->len[0])].mod);
			Files_Read(&*R, R__typ, (void*)&(linkTab->data)[__X(i, linkTab->len[0])].entry);
			Modules_ReadUnsigned(&*R, R__typ, &(linkTab->data)[__X(i, linkTab->len[0])].link);
			i += 1;
		}
	}
	if (!Expect__23(0x87)) {
		LoadModule__12_s = _s.lnk;
		return;
	}
	i = 0;
	t = (*m)->sb;
	while (i < head.conSize) {
		Files_Read(&*R, R__typ, (void*)&ch);
		__PUT(t, ch, CHAR);
		t += 1;
		i += 1;
	}
	if (!Expect__23(0x88)) {
		LoadModule__12_s = _s.lnk;
		return;
	}
	LoadExpBlock__37(&*R, R__typ, *m);
	if (!Expect__23(0x89)) {
		LoadModule__12_s = _s.lnk;
		return;
	}
	Files_ReadBytes(&*R, R__typ, (void*)(*m)->code->data, (*m)->code->len[0] * 1, head.codeSize);
	if (!Expect__23(0x8a)) {
		LoadModule__12_s = _s.lnk;
		return;
	}

    return; //TODO
	CheckUseBlock__17(&*R, R__typ, *m);
	if (Modules_res != 0) {
		LoadModule__12_s = _s.lnk;
		return;
	}
	if (!Expect__23(0x8b)) {
		LoadModule__12_s = _s.lnk;
		return;
	}
	ReadTypes__42(&*R, R__typ);
	if (Modules_res != 0) {
		LoadModule__12_s = _s.lnk;
		return;
	}
	if (!Expect__23(0x8c)) {
		LoadModule__12_s = _s.lnk;
		return;
	}
	Files_ReadBytes(&*R, R__typ, (void*)(*m)->refs->data, (*m)->refs->len[0] * 1, head.refSize);
	if (Modules_res == 0) {
		imp = Modules_FindMod((*m)->name, 32);
		if (imp != NIL) {
			*m = imp;
			LoadModule__12_s = _s.lnk;
			return;
		}
		while (mno > 0) {
			mno -= 1;
			imp = ((*m)->imports->data)[__X(mno, (*m)->imports->len[0])];
			imp->refcnt += 1;
		}
		__PUT((*m)->sb, (INT32)(ADDRESS)*m, INT32);
		//Fixup__27(*m, linkTab);
		InitTypes__35();
		(*m)->next = Kernel_modules;
		Kernel_modules = *m;
		(*m)->init = 1;
		//__PUT((ADDRESS)&body, (ADDRESS)&((*m)->code->data)[0], INT32);
		//(*body)(); //TODO
		Modules_res = 0;
	} else {
		*m = NIL;
	}
	LoadModule__12_s = _s.lnk;
}

static void Modules_Load (CHAR *name, ADDRESS name__len, Kernel_Module *m)
{
	Files_File f;
	Files_Rider R;
	INT16 i, j;
	CHAR fname[64];
	CHAR tag;
	__DUP(name, name__len, CHAR);
	*m = Modules_FindMod(name, name__len);
	Modules_res = 0;
	Modules_Clear();
	if (*m == NIL) {
		i = 0;
		if (__STRCMP(name, "Display") == 0) {
			while (Modules_disp[__X(i, 16)] != 0x00) {
				fname[__X(i, 64)] = Modules_disp[__X(i, 16)];
				i += 1;
			}
		}
		j = 0;
		while (name[__X(j, name__len)] != 0x00) {
			fname[__X(i, 64)] = name[__X(j, name__len)];
			i += 1;
			j += 1;
		}
		j = 0;
		while (Modules_extension[__X(j, 8)] != 0x00) {
			fname[__X(i, 64)] = Modules_extension[__X(j, 8)];
			i += 1;
			j += 1;
		}
		fname[__X(i, 64)] = 0x00;
		f = Files_Old(fname, 64);
		if (f == NIL) {
			__COPY(fname, Modules_importing, 32);
			Modules_res = 1;
			Modules_ErrMsg(Modules_res);
			__DEL(name);
			return;
		}
		Files_Set(&R, OFS_Rider__typ, f, 0);
		Files_Read(&R, OFS_Rider__typ, (void*)&tag);
		if (tag == 0xbb) {
			Files_Read(&R, OFS_Rider__typ, (void*)&tag);
			if (tag == 0xaf) {
				Modules_LoadModule(&R, OFS_Rider__typ, &*m);
			} else {
				__COPY(name, Modules_importing, 32);
				Modules_res = 2;
				Modules_ErrMsg(Modules_res);
			}
		} else {
			__COPY(name, Modules_importing, 32);
			Modules_res = 2;
			Modules_ErrMsg(Modules_res);
		}
	} else if (!(*m)->init) {
		__COPY(name, Modules_importing, 32);
		Modules_res = 9;
		Modules_ErrMsg(Modules_res);
	}
	__DEL(name);
}

Kernel_Module Modules_ThisMod (CHAR *name, ADDRESS name__len)
{
	Kernel_Module mod;
	__DUP(name, name__len, CHAR);
	Modules_Load(name, name__len, &mod);
	__DEL(name);
	return mod;
}

Kernel_Proc Modules_ThisCommand (Kernel_Module mod, CHAR *name, ADDRESS name__len)
{
	INT32 i;
	__DUP(name, name__len, CHAR);
	if (mod != NIL) {
//i := 0; (* LEN(mod.cmds); *)
//		i = 0;
        i = mod->cmds->len[ 0 ];
		while (i > 0) {
			i -= 1;
			if (__STRCMP((mod->cmds->data)[__X(i, mod->cmds->len[0])].name, name) == 0) {
				Modules_res = 0;
				Modules_Clear();
				__DEL(name);
				return (Kernel_Proc)(ADDRESS)(mod->cmds->data)[__X(i, mod->cmds->len[0])].adr;
			}
		}
		__COPY(mod->name, Modules_imported, 32);
		__COPY(name, Modules_importing, 32);
		Modules_res = 5;
		Modules_ErrMsg(Modules_res);
	}
	__DEL(name);
	return NIL;
}

static void Modules_Delete (Kernel_Module m)
{
	Kernel_Module m1;
	m1 = Kernel_modules;
	if (m == m1) {
		Kernel_modules = m->next;
	} else {
		while (m1->next != m) {
			m1 = m1->next;
		}
		m1->next = m->next;
	}
}

void Modules_Free (CHAR *name, ADDRESS name__len, BOOLEAN all)
{
	Kernel_Module m, m1;
	INT32 i, j;
	__DUP(name, name__len, CHAR);
	Modules_res = 0;
	Modules_Clear();
	m = Modules_FindMod(name, name__len);
	if (m == NIL) {
		__COPY(name, Modules_importing, 32);
		Modules_res = 6;
		Modules_ErrMsg(Modules_res);
	} else if (m->refcnt != 0) {
		__MOVE(m->name, Modules_importing, 32);
		Modules_res = 8;
		Modules_ErrMsg(Modules_res);
	} else {
		Kernel_FinalizeModule(m);
//i := 0; (* LEN(m.imports); *)
//		i = 0;
        i = m->imports->len[ 0 ];
		while (i > 0) {
			i -= 1;
			m1 = (m->imports->data)[__X(i, m->imports->len[0])];
			m1->refcnt -= 1;
		}
		if (all) {
//		IF all THEN i := 0; (* LEN(m.imports); *)
///			i = 0;
            i = m->imports->len[ 0 ];
			while (i > 0) {
				i -= 1;
				m1 = (m->imports->data)[__X(i, m->imports->len[0])];
				Modules_Free(m1->name, 32, 1);
			}
			Modules_res = 0;
			Modules_Clear();
		}
		Modules_Delete(m);
		i = (INT32)(ADDRESS)m->entries;
		__GET(i - 4, j, INT32);
		__GET(j, j, INT32);
		j = (i + j) - 24;
		while (i < j) {
			__PUT(i, 3435973836LL, INT64);
			i += 4;
		}
	}
	__DEL(name);
}

void Modules_InstallTermHandler (Kernel_Proc h)
{
	Kernel_InstallTermHandler(h);
}

__TDESC(Modules_Header, 1, 0) = {__TDFLDS("Header", 32), {-4}};
__TDESC(Modules__2, 1, 0) = {__TDFLDS("", 8), {-4}};
__TDESC(Modules__1, 1, 1) = {__TDFLDS("", 12), {8, -8}};
__TDESC(Modules__11, 1, 0) = {__TDFLDS("", 128000), {-4}};
__TDESC(Modules__3, 1, 1) = {__TDFLDS("", 24), {4, -8}};
__TDESC(Modules__22, 1, 0) = {__TDFLDS("", 8), {-4}};

export void *Modules__init(void)
{
	__DEFMOD;
	__MODULE_IMPORT(Files);
	__MODULE_IMPORT(Kernel);
	__REGMOD("Modules", 0);
	__INITYP(Modules_Header, Modules_Header, 0);
	__INITYP(Modules__2, Modules__2, 0);
	__INITYP(Modules__1, Modules__1, 0);
	__INITYP(Modules__11, Modules__11, 0);
	__INITYP(Modules__3, Modules__3, 0);
	__INITYP(Modules__22, Modules__22, 0);
/* BEGIN */
	Kernel_GetConfig((CHAR*)"ModExt", 7, (void*)Modules_extension, 8);
	if (Modules_extension[0] == 0x00) {
		__MOVE(".Obj", Modules_extension, 5);
	}
	Kernel_GetConfig((CHAR*)"TraceModules", 13, (void*)Modules_disp, 16);
	Modules_trace = Modules_disp[0] == '1';
	Kernel_GetConfig((CHAR*)"Init", 5, (void*)Modules_disp, 16);
	if (__STRCMP(Modules_disp, "9090") == 0) {
		__MOVE("Empty.", Modules_disp, 7);
	} else {
		Kernel_GetConfig((CHAR*)"Display", 8, (void*)Modules_disp, 16);
	}
	__ENDMOD;
}
