/* voc 2.1.0 [2017/09/06]. Bootstrapping compiler for address size 8, alignment 8. xtaSv */

#define SHORTINT INT8
#define INTEGER  INT16
#define LONGINT  INT32
#define SET      UINT32

#include "SYSTEM.h"
#include "Files.h"
#include "Kernel.h"
#include "Modules.h"

typedef
	struct Objects_AliasDesc *Objects_Alias;

typedef
	CHAR Objects_Name[32];

typedef
	struct Objects_LibDesc *Objects_Library;

typedef
	struct Objects_AliasDesc {
		Objects_Alias next;
		Objects_Name name;
		Objects_Library lib;
	} Objects_AliasDesc;

typedef
	struct Objects_ArrayIndexDesc *Objects_ArrayIndex;

typedef
	struct Objects_IndexDesc {
		char _prvt0[1];
	} Objects_IndexDesc;

typedef
	struct Objects_ObjDesc *Objects_Object;

typedef
	struct {
		ADDRESS len[1];
		Objects_Object data[1];
	} *Objects_Block;

typedef
	struct Objects_ArrayIndexDesc { /* Objects_IndexDesc */
		Objects_Block index;
		INT32 org;
		INT16 size;
	} Objects_ArrayIndexDesc;

typedef
	struct Objects_ObjMsg {
		INT32 stamp;
		Objects_Object dlink;
	} Objects_ObjMsg;

typedef
	struct Objects_AttrMsg { /* Objects_ObjMsg */
		INT32 stamp;
		Objects_Object dlink;
		INT16 id;
		void (*Enum)(CHAR*, ADDRESS );
		Objects_Name name;
		INT16 res, class;
		INT32 i;
		REAL x;
		LONGREAL y;
		CHAR c;
		BOOLEAN b;
		CHAR s[64];
	} Objects_AttrMsg;

typedef
	struct Objects_BindMsg { /* Objects_ObjMsg */
		INT32 stamp;
		Objects_Object dlink;
		Objects_Library lib;
	} Objects_BindMsg;

typedef
	struct Objects_CopyMsg { /* Objects_ObjMsg */
		INT32 stamp;
		Objects_Object dlink;
		INT16 id;
		Objects_Object obj;
	} Objects_CopyMsg;

typedef
	struct Objects_DictionaryDesc *Objects_Dictionary;

typedef
	struct Objects_DictionaryDesc {
		char _prvt0[1];
	} Objects_DictionaryDesc;

typedef
	struct Objects_DummyDesc *Objects_Dummy;

typedef
	void (*Objects_Handler)(Objects_Object, Objects_ObjMsg*, ADDRESS *);

typedef
	struct Objects_ObjDesc {
		INT32 stamp;
		Objects_Object dlink, slink;
		Objects_Library lib;
		INT16 ref;
		Objects_Handler handle;
	} Objects_ObjDesc;

typedef
	struct Objects_DummyDesc { /* Objects_ObjDesc */
		INT32 stamp;
		Objects_Object dlink, slink;
		Objects_Library lib;
		INT16 ref;
		Objects_Handler handle;
		Objects_Name GName;
		INT32 len;
		struct {
			ADDRESS len[1];
			CHAR data[1];
		} *blk;
	} Objects_DummyDesc;

typedef
	struct Objects_EntryDesc *Objects_Entry;

typedef
	struct Objects_EntryDesc {
		Objects_Entry next;
		INT16 key;
		Objects_Name name;
	} Objects_EntryDesc;

typedef
	void (*Objects_EnumProc)(Objects_Library);

typedef
	struct Objects_FileMsg { /* Objects_ObjMsg */
		INT32 stamp;
		Objects_Object dlink;
		INT16 id;
		INT32 len;
		OFS_Rider R;
	} Objects_FileMsg;

typedef
	struct Objects_FindMsg { /* Objects_ObjMsg */
		INT32 stamp;
		Objects_Object dlink;
		Objects_Name name;
		Objects_Object obj;
	} Objects_FindMsg;

typedef
	CHAR Objects_GenName[64];

typedef
	Objects_IndexDesc *Objects_Index;

typedef
	struct Objects_LibDesc {
		Objects_Library next;
		Objects_Index ind;
		OFS_File f;
		OFS_Rider R;
		Objects_Name name;
		Objects_Dictionary dict;
		INT16 maxref;
		struct {
			ADDRESS len[1];
			Objects_GenName data[1];
		} *GName;
		void (*GenRef)(Objects_Library, INT16*);
		void (*GetObj)(Objects_Library, INT16, Objects_Object*);
		void (*PutObj)(Objects_Library, INT16, Objects_Object);
		void (*FreeObj)(Objects_Library, INT16);
		void (*Load)(Objects_Library);
		void (*Store)(Objects_Library);
	} Objects_LibDesc;

typedef
	struct Objects_LinkMsg { /* Objects_ObjMsg */
		INT32 stamp;
		Objects_Object dlink;
		INT16 id;
		void (*Enum)(CHAR*, ADDRESS );
		Objects_Name name;
		INT16 res;
		Objects_Object obj;
	} Objects_LinkMsg;

typedef
	struct Objects_ListDictDesc *Objects_ListDict;

typedef
	struct Objects_ListDictDesc { /* Objects_DictionaryDesc */
		INT16 key;
		Objects_Entry first;
	} Objects_ListDictDesc;

typedef
	Objects_Library (*Objects_NewProc)(void);

typedef
	struct Objects_RunRec {
		INT16 beg, end;
	} Objects_RunRec;


export CHAR Objects_LibBlockId;
static Objects_Library Objects_FirstLib;
static Objects_Object Objects_NoObj;
export Objects_Object Objects_NewObj;
static INT32 Objects_stamp;
static INT16 Objects_nofreg;
static CHAR Objects_LibExt[8][8];
static Objects_NewProc Objects_LibNew[8];
static Objects_Alias Objects_FirstAlias;

export ADDRESS *Objects_ObjMsg__typ;
export ADDRESS *Objects_ObjDesc__typ;
export ADDRESS *Objects_AttrMsg__typ;
export ADDRESS *Objects_LinkMsg__typ;
export ADDRESS *Objects_CopyMsg__typ;
export ADDRESS *Objects_BindMsg__typ;
export ADDRESS *Objects_FileMsg__typ;
export ADDRESS *Objects_FindMsg__typ;
export ADDRESS *Objects_DummyDesc__typ;
export ADDRESS *Objects_IndexDesc__typ;
export ADDRESS *Objects_DictionaryDesc__typ;
export ADDRESS *Objects_ArrayIndexDesc__typ;
export ADDRESS *Objects_EntryDesc__typ;
export ADDRESS *Objects_ListDictDesc__typ;
export ADDRESS *Objects_LibDesc__typ;
export ADDRESS *Objects_RunRec__typ;
export ADDRESS *Objects_AliasDesc__typ;

static void Objects_Cleanup (SYSTEM_PTR L);
export void Objects_Enumerate (Objects_EnumProc P);
export void Objects_FreeLibrary (CHAR *name, ADDRESS name__len);
static void Objects_FreeObj (Objects_Library L, INT16 ref);
static void Objects_GenRef (Objects_Library L, INT16 *ref);
export void Objects_GetKey (Objects_Dictionary *D, CHAR *name, ADDRESS name__len, INT16 *key);
export void Objects_GetName (Objects_Dictionary *D, INT16 key, CHAR *name, ADDRESS name__len);
static void Objects_GetObj (Objects_Library L, INT16 ref, Objects_Object *obj);
export void Objects_GetRef (Objects_Dictionary *D, CHAR *name, ADDRESS name__len, INT16 *ref);
static void Objects_HandleDummy (Objects_Object obj, Objects_ObjMsg *M, ADDRESS *M__typ);
static void Objects_LoadFileLib (Objects_Library L);
export void Objects_LoadLibrary (Objects_Library L, OFS_File f, INT32 pos, INT32 *len);
static BOOLEAN Objects_Match (CHAR *s, ADDRESS s__len, CHAR *ext, ADDRESS ext__len, INT16 *len);
static void Objects_NewDummy (CHAR *GName, ADDRESS GName__len);
static Objects_Library Objects_NewLibrary (void);
static void Objects_OldLoadLibrary (Objects_Library L, OFS_File f, INT32 pos, INT32 *len);
export void Objects_OpenLibrary (Objects_Library L);
export void Objects_PutName (Objects_Dictionary *D, INT16 key, CHAR *name, ADDRESS name__len);
static void Objects_PutObj (Objects_Library L, INT16 ref, Objects_Object obj);
static void Objects_ReadName (OFS_Rider *R, ADDRESS *R__typ, CHAR *name, ADDRESS name__len);
export void Objects_Register (CHAR *ext, ADDRESS ext__len, Objects_NewProc new);
static void Objects_SplitName (CHAR *name, ADDRESS name__len, CHAR *MName, ADDRESS MName__len, CHAR *PName, ADDRESS PName__len);
export void Objects_Stamp (Objects_ObjMsg *M, ADDRESS *M__typ);
static void Objects_StoreFileLib (Objects_Library L);
export void Objects_StoreLibrary (Objects_Library L, OFS_File f, INT32 pos, INT32 *len);
export Objects_Library Objects_ThisLibrary (CHAR *name, ADDRESS name__len);


void Objects_Stamp (Objects_ObjMsg *M, ADDRESS *M__typ)
{
	(*M).stamp = Objects_stamp;
	if (Objects_stamp != 2147483647) {
		Objects_stamp += 1;
	} else {
		Objects_stamp = (-2147483647-1);
	}
}

static void Objects_Cleanup (SYSTEM_PTR L)
{
	Objects_Library p0, p;
	Objects_Alias a0, a;
	if (__ISP(L, Objects_LibDesc, 0)) {
		p0 = Objects_FirstLib;
		p = p0->next;
		while ((p != NIL && p != (*(Objects_Library*)&L))) {
			p0 = p;
			p = p->next;
		}
		if (p == (*(Objects_Library*)&L)) {
			p0->next = p->next;
		}
		a0 = Objects_FirstAlias;
		a = a0->next;
		while ((a != NIL && a->lib != (*(Objects_Library*)&L))) {
			a0 = a;
			a = a->next;
		}
		if (a != NIL) {
			a0->next = a->next;
		}
	} else __WITHCHK;
}

static BOOLEAN Objects_Match (CHAR *s, ADDRESS s__len, CHAR *ext, ADDRESS ext__len, INT16 *len)
{
	INT16 i, j;
	i = 0;
	while (ext[__X(i, ext__len)] != 0x00) {
		i += 1;
	}
	*len = i;
	j = 0;
	while (s[__X(j, s__len)] != 0x00) {
		j += 1;
	}
	do {
		i -= 1;
		j -= 1;
	} while (!((i < 0 || j < 0) || ext[__X(i, ext__len)] != s[__X(j, s__len)]));
	return i < 0;
}

Objects_Library Objects_ThisLibrary (CHAR *name, ADDRESS name__len)
{
	Objects_Library L;
	INT16 len, n, n0, t;
	Objects_NewProc proc;
	Objects_Alias A;
	__DUP(name, name__len, CHAR);
	A = Objects_FirstAlias->next;
	while ((A != NIL && __STRCMP(name, A->name) != 0)) {
		A = A->next;
	}
	if (A != NIL) {
		L = A->lib;
	} else {
		L = Objects_FirstLib->next;
		while ((L != NIL && __STRCMP(name, L->name) != 0)) {
			L = L->next;
		}
		if (L == NIL) {
			n = Objects_nofreg;
			n0 = 0;
			len = -1;
			while (n0 != Objects_nofreg) {
				if ((Objects_Match((void*)name, name__len, (void*)Objects_LibExt[__X(n0, 8)], 8, &t) && t >= len)) {
					n = n0;
					len = t;
				}
				n0 += 1;
			}
			if (n != Objects_nofreg) {
				proc = Objects_LibNew[__X(n, 8)];
				L = (*proc)();
				__COPY(name, L->name, 32);
				(*L->Load)(L);
				Kernel_RegisterObject((void*)L, Objects_Cleanup, 0);
				if (__STRCMP(name, L->name) == 0) {
					L->next = Objects_FirstLib->next;
					Objects_FirstLib->next = L;
				} else {
					__NEW(A, Objects_AliasDesc);
					__COPY(name, A->name, 32);
					A->lib = L;
					A->next = Objects_FirstAlias->next;
					Objects_FirstAlias->next = A;
				}
			}
		}
	}
	__DEL(name);
	return L;
}

void Objects_FreeLibrary (CHAR *name, ADDRESS name__len)
{
	Objects_Library L;
	__DUP(name, name__len, CHAR);
	L = Objects_FirstLib->next;
	while (L != NIL) {
		if (__STRCMP(name, L->name) == 0) {
			Objects_Cleanup((void*)L);
		}
		L = L->next;
	}
	__DEL(name);
}

void Objects_Enumerate (Objects_EnumProc P)
{
	Objects_Library L;
	L = Objects_FirstLib->next;
	while (L != NIL) {
		(*P)(L);
		L = L->next;
	}
}

void Objects_Register (CHAR *ext, ADDRESS ext__len, Objects_NewProc new)
{
	INT16 n, len;
	Objects_Library L;
	__DUP(ext, ext__len, CHAR);
	n = 0;
	while ((n != Objects_nofreg && __STRCMP(ext, Objects_LibExt[__X(n, 8)]) != 0)) {
		n += 1;
	}
	if (n != Objects_nofreg) {
		Objects_LibNew[__X(n, 8)] = new;
	} else {
		__COPY(ext, Objects_LibExt[__X(Objects_nofreg, 8)], 8);
		Objects_LibNew[__X(Objects_nofreg, 8)] = new;
		Objects_nofreg += 1;
	}
	L = Objects_FirstLib->next;
	while (L != NIL) {
		if (Objects_Match((void*)L->name, 32, (void*)ext, ext__len, &len)) {
			Objects_Cleanup((void*)L);
		}
		L = L->next;
	}
	__DEL(ext);
}

static void Objects_ReadName (OFS_Rider *R, ADDRESS *R__typ, CHAR *name, ADDRESS name__len)
{
	INT16 i;
	CHAR ch;
	i = 0;
	Files_Read(&*R, R__typ, (void*)&ch);
	while ((ch != '.' && ch != 0x00)) {
		name[__X(i, name__len)] = ch;
		i += 1;
		Files_Read(&*R, R__typ, (void*)&ch);
	}
	name[__X(i, name__len)] = '.';
	i += 1;
	Files_Read(&*R, R__typ, (void*)&ch);
	while (ch != 0x00) {
		name[__X(i, name__len)] = ch;
		i += 1;
		Files_Read(&*R, R__typ, (void*)&ch);
	}
	name[__X(i, name__len)] = 0x00;
}

static void Objects_SplitName (CHAR *name, ADDRESS name__len, CHAR *MName, ADDRESS MName__len, CHAR *PName, ADDRESS PName__len)
{
	INT16 i, j;
	i = 0;
	while (name[__X(i, name__len)] != '.') {
		MName[__X(i, MName__len)] = name[__X(i, name__len)];
		i += 1;
	}
	MName[__X(i, MName__len)] = 0x00;
	i += 1;
	j = 0;
	while (name[__X(i, name__len)] != 0x00) {
		PName[__X(j, PName__len)] = name[__X(i, name__len)];
		i += 1;
		j += 1;
	}
	PName[__X(j, PName__len)] = 0x00;
}

static void Objects_HandleDummy (Objects_Object obj, Objects_ObjMsg *M, ADDRESS *M__typ)
{
	Objects_Dummy dum;
	if (__ISP(obj, Objects_DummyDesc, 1)) {
		if (__IS(M__typ, Objects_AttrMsg, 1)) {
			if (__IS(M__typ, Objects_AttrMsg, 1)) {
				Objects_AttrMsg *M__ = (void*)M;
				if (((*M__).id == 1 && __STRCMP((*M__).name, "Gen") == 0)) {
					__COPY((*(Objects_Dummy*)&obj)->GName, (*M__).s, 64);
				}
			} else __WITHCHK;
		} else if (__IS(M__typ, Objects_CopyMsg, 1)) {
			if (__IS(M__typ, Objects_CopyMsg, 1)) {
				Objects_CopyMsg *M__ = (void*)M;
				if ((*M__).stamp == (*(Objects_Dummy*)&obj)->stamp) {
					(*M__).obj = (*(Objects_Dummy*)&obj)->dlink;
				} else {
					__NEW(dum, Objects_DummyDesc);
					(*(Objects_Dummy*)&obj)->stamp = (*M__).stamp;
					(*(Objects_Dummy*)&obj)->dlink = (Objects_Object)dum;
					dum->handle = (*(Objects_Dummy*)&obj)->handle;
					__COPY((*(Objects_Dummy*)&obj)->GName, dum->GName, 32);
					dum->len = (*(Objects_Dummy*)&obj)->len;
					dum->blk = (*(Objects_Dummy*)&obj)->blk;
					(*M__).obj = (Objects_Object)dum;
				}
			} else __WITHCHK;
		} else if (__IS(M__typ, Objects_FileMsg, 1)) {
			if (__IS(M__typ, Objects_FileMsg, 1)) {
				Objects_FileMsg *M__ = (void*)M;
				if ((*M__).id == 0) {
					(*(Objects_Dummy*)&obj)->len = (*M__).len;
					(*(Objects_Dummy*)&obj)->blk = __NEWARR(NIL, 1, 1, 1, 1, ((ADDRESS)((*(Objects_Dummy*)&obj)->len)));
					Files_ReadBytes(&(*M__).R, OFS_Rider__typ, (void*)(*(Objects_Dummy*)&obj)->blk->data, (*(Objects_Dummy*)&obj)->blk->len[0] * 1, (*(Objects_Dummy*)&obj)->len);
				} else if ((*M__).id == 1) {
					Files_WriteBytes(&(*M__).R, OFS_Rider__typ, (void*)(*(Objects_Dummy*)&obj)->blk->data, (*(Objects_Dummy*)&obj)->blk->len[0] * 1, (*(Objects_Dummy*)&obj)->len);
				}
			} else __WITHCHK;
		}
	} else __WITHCHK;
}

static void Objects_NewDummy (CHAR *GName, ADDRESS GName__len)
{
	Objects_Dummy dum;
	__NEW(dum, Objects_DummyDesc);
	dum->handle = Objects_HandleDummy;
	__COPY(GName, dum->GName, 32);
	Objects_NewObj = (Objects_Object)dum;
}

static void Objects_GetObj (Objects_Library L, INT16 ref, Objects_Object *obj)
{
	INT32 objOrg;
	Objects_ArrayIndex ind;
	CHAR MName[32], PName[32];
	INT16 n;
	Kernel_Module Mod;
	Kernel_Proc Cmd;
	Objects_FileMsg M;
	ind = __GUARDP(L->ind, Objects_ArrayIndexDesc, 1);
	if (ref < 0 || ref >= ind->size) {
		*obj = NIL;
		return;
	}
	*obj = (ind->index->data)[__X(ref, ind->index->len[0])];
	if (*obj == NIL) {
		if (L->f != NIL) {
			Files_Set(&L->R, OFS_Rider__typ, L->f, ind->org + __ASHL(ref, 2));
			Files_ReadLInt(&L->R, OFS_Rider__typ, &objOrg);
			if (objOrg > ind->org) {
				Objects_NewObj = NIL;
				Files_Set(&L->R, OFS_Rider__typ, L->f, objOrg);
				Files_ReadInt(&L->R, OFS_Rider__typ, &n);
				Objects_SplitName((void*)(L->GName->data)[__X(n, L->GName->len[0])], 64, (void*)MName, 32, (void*)PName, 32);
				Mod = Modules_ThisMod(MName, 32);
				if (Modules_res == 0) {
					Cmd = Modules_ThisCommand(Mod, PName, 32);
					if (Modules_res == 0) {
						(*Cmd)();
					} else {
						Objects_NewDummy((void*)(L->GName->data)[__X(n, L->GName->len[0])], 64);
					}
				} else {
					Objects_NewDummy((void*)(L->GName->data)[__X(n, L->GName->len[0])], 64);
				}
				*obj = Objects_NewObj;
				if (*obj != NIL) {
					(*obj)->lib = L;
					(*obj)->ref = ref;
					(ind->index->data)[__X(ref, ind->index->len[0])] = *obj;
					M.id = 0;
					Objects_Stamp((void*)&M, Objects_FileMsg__typ);
					Files_ReadLInt(&L->R, OFS_Rider__typ, &M.len);
					Files_Set(&M.R, OFS_Rider__typ, L->f, Files_Pos(&L->R, OFS_Rider__typ));
					if (M.len > 0) {
						(*(*obj)->handle)(*obj, (void*)&M, Objects_FileMsg__typ);
					}
				} else {
					(ind->index->data)[__X(ref, ind->index->len[0])] = Objects_NoObj;
				}
			} else {
				(ind->index->data)[__X(ref, ind->index->len[0])] = Objects_NoObj;
			}
		} else {
			(ind->index->data)[__X(ref, ind->index->len[0])] = Objects_NoObj;
		}
	} else if (*obj == Objects_NoObj) {
		*obj = NIL;
	}
}

static void Objects_PutObj (Objects_Library L, INT16 ref, Objects_Object obj)
{
	Objects_Block index;
	Objects_ArrayIndex ind;
	INT32 i;
	INT16 size;
	INT32 _for__22;
	if (ref < 0 || obj == NIL) {
		return;
	}
	ind = __GUARDP(L->ind, Objects_ArrayIndexDesc, 1);
	if (ref >= ind->size) {
		size = __ASHL(__ASHR(ref, 6) + 1, 6);
		index = __NEWARR(POINTER__typ, 4, 4, 1, 1, ((ADDRESS)(size)));
		if (ind->index != NIL) {
			__MOVE((ADDRESS)ind->index->data, (ADDRESS)index->data, __ASHL(ind->size, 2));
		}
		_for__22 = size - 1;
		i = ind->size;
		while (i <= _for__22) {
			(index->data)[__X(i, index->len[0])] = Objects_NoObj;
			i += 1;
		}
		ind->size = size;
		ind->index = index;
	}
	(ind->index->data)[__X(ref, ind->index->len[0])] = obj;
	obj->lib = L;
	obj->ref = ref;
	if (ref >= L->maxref) {
		L->maxref = ref + 1;
	}
}

static void Objects_FreeObj (Objects_Library L, INT16 ref)
{
	if ((ref >= 0 && ref < __GUARDP(L->ind, Objects_ArrayIndexDesc, 1)->size)) {
		(__GUARDP(L->ind, Objects_ArrayIndexDesc, 1)->index->data)[__X(ref, __GUARDP(L->ind, Objects_ArrayIndexDesc, 1)->index->len[0])] = Objects_NoObj;
	}
}

static void Objects_GenRef (Objects_Library L, INT16 *ref)
{
	*ref = L->maxref;
	L->maxref += 1;
}

static void Objects_OldLoadLibrary (Objects_Library L, OFS_File f, INT32 pos, INT32 *len)
{
	OFS_Rider R, S;
	Kernel_Module Mod;
	Kernel_Proc Cmd;
	INT16 NofRuns, key, N, i, k, m;
	INT32 clen, dlen;
	INT8 type, n;
	CHAR ch;
	Objects_Entry entry;
	Objects_Object obj;
	Objects_FileMsg M;
	Objects_Name MName, PName;
	Objects_Name GName[64];
	Objects_RunRec run[64];
	Objects_ArrayIndex ind;
	Objects_ListDict dict;
	ind = __GUARDP(L->ind, Objects_ArrayIndexDesc, 1);
	dict = __GUARDP(L->dict, Objects_ListDictDesc, 1);
	Files_Set(&R, OFS_Rider__typ, f, pos);
	Files_Read(&R, OFS_Rider__typ, (void*)&type);
	Files_ReadLInt(&R, OFS_Rider__typ, &clen);
	Files_Set(&S, OFS_Rider__typ, f, (pos + 1) + clen);
	Files_ReadLInt(&S, OFS_Rider__typ, &dlen);
	Files_ReadInt(&S, OFS_Rider__typ, &key);
	while (key != (-32767-1)) {
		__NEW(entry, Objects_EntryDesc);
		Files_ReadString(&S, OFS_Rider__typ, (void*)entry->name, 32);
		entry->key = key;
		entry->next = dict->first;
		dict->first = entry;
		if (key < dict->key) {
			dict->key = key;
		}
		Files_ReadInt(&S, OFS_Rider__typ, &key);
	}
	if (type >= 0) {
		Files_Read(&R, OFS_Rider__typ, (void*)&ch);
		Files_Read(&R, OFS_Rider__typ, (void*)&ch);
		Files_ReadInt(&R, OFS_Rider__typ, &i);
		Files_ReadInt(&R, OFS_Rider__typ, &i);
		Files_ReadInt(&R, OFS_Rider__typ, &i);
		Files_ReadInt(&R, OFS_Rider__typ, &i);
		Files_ReadInt(&R, OFS_Rider__typ, &i);
	}
	Files_ReadInt(&R, OFS_Rider__typ, &NofRuns);
	k = 0;
	while (k != NofRuns) {
		Files_ReadInt(&R, OFS_Rider__typ, &run[__X(k, 64)].beg);
		Files_ReadInt(&R, OFS_Rider__typ, &run[__X(k, 64)].end);
		k += 1;
	}
	N = 0;
	k = 0;
	m = 0;
	while (k < NofRuns) {
		m = run[__X(k, 64)].beg;
		while (m < run[__X(k, 64)].end) {
			Files_Read(&R, OFS_Rider__typ, (void*)&n);
			if ((INT16)n == N) {
				Objects_ReadName(&R, OFS_Rider__typ, (void*)GName[__X(N, 64)], 32);
				N += 1;
			}
			Objects_SplitName((void*)GName[__X(n, 64)], 32, (void*)MName, 32, (void*)PName, 32);
			Mod = Modules_ThisMod(MName, 32);
			if (Modules_res == 0) {
				Cmd = Modules_ThisCommand(Mod, PName, 32);
				if (Modules_res == 0) {
					(*Cmd)();
				} else {
					Objects_NewDummy((void*)GName[__X(n, 64)], 32);
				}
			} else {
				Objects_NewDummy((void*)GName[__X(n, 64)], 32);
			}
			Objects_PutObj(L, m, Objects_NewObj);
			Objects_NewObj->lib = L;
			Objects_NewObj->ref = m;
			m += 1;
		}
		k += 1;
	}
	L->maxref = m;
	M.id = 0;
	Objects_Stamp((void*)&M, Objects_FileMsg__typ);
	Files_Set(&M.R, OFS_Rider__typ, f, Files_Pos(&R, OFS_Rider__typ));
	k = 0;
	m = 0;
	while (k < NofRuns) {
		m = run[__X(k, 64)].beg;
		while (m < run[__X(k, 64)].end) {
			Files_ReadLInt(&M.R, OFS_Rider__typ, &M.len);
			pos = Files_Pos(&M.R, OFS_Rider__typ) + M.len;
			if (M.len != 0) {
				obj = (ind->index->data)[__X(m, ind->index->len[0])];
				(*obj->handle)(obj, (void*)&M, Objects_FileMsg__typ);
			}
			if (Files_Pos(&M.R, OFS_Rider__typ) < pos) {
				Files_Set(&M.R, OFS_Rider__typ, f, pos);
			} else if (Files_Pos(&M.R, OFS_Rider__typ) > pos) {
				__HALT(99);
			}
			m += 1;
		}
		k += 1;
	}
	*len = (1 + clen) + dlen;
}

void Objects_LoadLibrary (Objects_Library L, OFS_File f, INT32 pos, INT32 *len)
{
	Objects_ArrayIndex ind;
	Objects_ListDict dict;
	INT32 i, version, dorg, gorg;
	INT16 key, n, N;
	Objects_Entry entry;
	OFS_Rider R;
	INT32 _for__14;
	INT16 _for__13;
	ind = __GUARDP(L->ind, Objects_ArrayIndexDesc, 1);
	Files_Set(&R, OFS_Rider__typ, f, pos);
	Files_ReadLInt(&R, OFS_Rider__typ, &version);
	if (version == 1380272450) {
		Files_ReadLInt(&R, OFS_Rider__typ, &gorg);
		Files_ReadLInt(&R, OFS_Rider__typ, &dorg);
		Files_ReadInt(&R, OFS_Rider__typ, &L->maxref);
		ind->size = L->maxref;
		ind->org = Files_Pos(&R, OFS_Rider__typ);
		if (L->maxref > 0) {
			ind->index = __NEWARR(POINTER__typ, 4, 4, 1, 1, ((ADDRESS)(L->maxref)));
		}
		_for__14 = L->maxref - 1;
		i = 0;
		while (i <= _for__14) {
			(ind->index->data)[__X(i, ind->index->len[0])] = NIL;
			i += 1;
		}
		Files_Set(&R, OFS_Rider__typ, f, gorg);
		Files_ReadInt(&R, OFS_Rider__typ, &N);
		if (N > 0) {
			L->GName = __NEWARR(NIL, 1, 1, 2, 1, ((ADDRESS)(N)), 64);
			_for__13 = N - 1;
			n = 0;
			while (n <= _for__13) {
				Files_ReadString(&R, OFS_Rider__typ, (void*)(L->GName->data)[__X(n, L->GName->len[0])], 64);
				n += 1;
			}
		} else {
			L->GName = NIL;
		}
		dict = __GUARDP(L->dict, Objects_ListDictDesc, 1);
		Files_Set(&R, OFS_Rider__typ, f, dorg);
		Files_ReadInt(&R, OFS_Rider__typ, &key);
		while ((key != (-32767-1) && !R.eof)) {
			__NEW(entry, Objects_EntryDesc);
			Files_ReadString(&R, OFS_Rider__typ, (void*)entry->name, 32);
			entry->key = key;
			entry->next = dict->first;
			dict->first = entry;
			if (key < dict->key) {
				dict->key = key;
			}
			Files_ReadInt(&R, OFS_Rider__typ, &key);
		}
		L->f = f;
		Files_Set(&L->R, OFS_Rider__typ, f, ind->org);
		*len = Files_Pos(&R, OFS_Rider__typ) - pos;
	} else {
		ind->org = 0;
		ind->size = 0;
		ind->index = NIL;
		L->f = NIL;
		Files_Set(&L->R, OFS_Rider__typ, NIL, 0);
		Objects_OldLoadLibrary(L, f, pos, &*len);
	}
}

void Objects_StoreLibrary (Objects_Library L, OFS_File f, INT32 pos, INT32 *len)
{
	Objects_Object obj;
	Objects_ArrayIndex ind;
	INT32 i, olen, org, indorg;
	INT16 m, n, N;
	Objects_Entry entry;
	CHAR ch;
	Objects_GenName GName[64];
	OFS_Rider R, indR;
	Objects_FileMsg M;
	Objects_AttrMsg A;
	INT32 _for__30;
	INT16 _for__29;
	ind = __GUARDP(L->ind, Objects_ArrayIndexDesc, 1);
	Files_Set(&R, OFS_Rider__typ, f, pos);
	Files_Write(&R, OFS_Rider__typ, Objects_LibBlockId);
	Files_WriteLInt(&R, OFS_Rider__typ, 1380272450);
	Files_WriteLInt(&R, OFS_Rider__typ, -1);
	Files_WriteLInt(&R, OFS_Rider__typ, -1);
	Files_WriteInt(&R, OFS_Rider__typ, L->maxref);
	indorg = Files_Pos(&R, OFS_Rider__typ);
	Files_Set(&indR, OFS_Rider__typ, f, indorg);
	if (L->maxref > 0) {
		Files_WriteBytes(&R, OFS_Rider__typ, (void*)ind->index->data, ind->index->len[0] * 4, __ASHL(L->maxref, 2));
	}
	A.id = 1;
	__MOVE("Gen", A.name, 4);
	N = 0;
	M.id = 1;
	Objects_Stamp((void*)&M, Objects_FileMsg__typ);
	_for__30 = L->maxref - 1;
	i = 0;
	while (i <= _for__30) {
		obj = (ind->index->data)[__X(i, ind->index->len[0])];
		if (obj == NIL) {
			Files_Set(&L->R, OFS_Rider__typ, L->f, ind->org + __ASHL(i, 2));
			Files_ReadLInt(&L->R, OFS_Rider__typ, &org);
			if (org >= 0) {
				Files_Set(&L->R, OFS_Rider__typ, L->f, org);
				Files_ReadInt(&L->R, OFS_Rider__typ, &m);
				Files_ReadLInt(&L->R, OFS_Rider__typ, &olen);
				__COPY((L->GName->data)[__X(m, L->GName->len[0])], GName[__X(N, 64)], 64);
				n = 0;
				while (__STRCMP(GName[__X(n, 64)], GName[__X(N, 64)]) != 0) {
					n += 1;
				}
				if (n == N) {
					N += 1;
				}
				Files_WriteLInt(&indR, OFS_Rider__typ, Files_Pos(&R, OFS_Rider__typ));
				Files_WriteInt(&R, OFS_Rider__typ, n);
				Files_WriteLInt(&R, OFS_Rider__typ, olen);
				while (olen > 0) {
					Files_Read(&L->R, OFS_Rider__typ, (void*)&ch);
					Files_Write(&R, OFS_Rider__typ, ch);
					olen -= 1;
				}
			} else {
				Files_WriteLInt(&indR, OFS_Rider__typ, -1);
			}
		} else if (obj != Objects_NoObj) {
			A.res = -1;
			(*obj->handle)(obj, (void*)&A, Objects_AttrMsg__typ);
			__COPY(A.s, GName[__X(N, 64)], 64);
			n = 0;
			while (__STRCMP(GName[__X(n, 64)], GName[__X(N, 64)]) != 0) {
				n += 1;
			}
			if (n == N) {
				N += 1;
			}
			Files_WriteLInt(&indR, OFS_Rider__typ, Files_Pos(&R, OFS_Rider__typ));
			Files_WriteInt(&R, OFS_Rider__typ, n);
			Files_Set(&M.R, OFS_Rider__typ, f, Files_Pos(&R, OFS_Rider__typ));
			Files_WriteLInt(&M.R, OFS_Rider__typ, 0);
			(*obj->handle)(obj, (void*)&M, Objects_FileMsg__typ);
			olen = (Files_Pos(&M.R, OFS_Rider__typ) - Files_Pos(&R, OFS_Rider__typ)) - 4;
			Files_WriteLInt(&R, OFS_Rider__typ, olen);
			Files_Set(&R, OFS_Rider__typ, f, Files_Pos(&M.R, OFS_Rider__typ));
		} else {
			Files_WriteLInt(&indR, OFS_Rider__typ, -1);
		}
		i += 1;
	}
	i = Files_Pos(&R, OFS_Rider__typ);
	Files_Set(&R, OFS_Rider__typ, f, pos + 5);
	Files_WriteLInt(&R, OFS_Rider__typ, i);
	Files_Set(&R, OFS_Rider__typ, f, i);
	Files_WriteInt(&R, OFS_Rider__typ, N);
	if (N > 0) {
		L->GName = __NEWARR(NIL, 1, 1, 2, 1, ((ADDRESS)(N)), 64);
		_for__29 = N - 1;
		n = 0;
		while (n <= _for__29) {
			Files_WriteString(&R, OFS_Rider__typ, GName[__X(n, 64)], 64);
			__COPY(GName[__X(n, 64)], (L->GName->data)[__X(n, L->GName->len[0])], 64);
			n += 1;
		}
	}
	i = Files_Pos(&R, OFS_Rider__typ);
	Files_Set(&R, OFS_Rider__typ, f, pos + 9);
	Files_WriteLInt(&R, OFS_Rider__typ, i);
	Files_Set(&R, OFS_Rider__typ, f, i);
	entry = __GUARDP(L->dict, Objects_ListDictDesc, 1)->first;
	while (entry != NIL) {
		Files_WriteInt(&R, OFS_Rider__typ, entry->key);
		i = 0;
		Files_WriteString(&R, OFS_Rider__typ, entry->name, 32);
		entry = entry->next;
	}
	Files_WriteInt(&R, OFS_Rider__typ, (-32767-1));
	*len = Files_Pos(&R, OFS_Rider__typ) - pos;
	L->f = f;
	ind->org = indorg;
	Files_Set(&L->R, OFS_Rider__typ, L->f, ind->org);
}

static void Objects_LoadFileLib (Objects_Library L)
{
	OFS_File f;
	OFS_Rider R;
	INT32 len;
	CHAR id;
	f = Files_Old(L->name, 32);
	if (f != NIL) {
		Files_Set(&R, OFS_Rider__typ, f, 0);
		Files_Read(&R, OFS_Rider__typ, (void*)&id);
		if (id == Objects_LibBlockId) {
			Objects_LoadLibrary(L, f, 1, &len);
		} else {
			L->f = NIL;
			__GUARDP(L->ind, Objects_ArrayIndexDesc, 1)->size = 0;
			__GUARDP(L->ind, Objects_ArrayIndexDesc, 1)->index = NIL;
		}
	}
}

static void Objects_StoreFileLib (Objects_Library L)
{
	OFS_File f;
	INT32 len;
	f = Files_New(L->name, 32);
	if (f != NIL) {
		Objects_StoreLibrary(L, f, 0, &len);
		Files_Register(f);
	}
}

void Objects_OpenLibrary (Objects_Library L)
{
	Objects_ArrayIndex ind;
	Objects_ListDict dict;
	L->Load = Objects_LoadFileLib;
	L->Store = Objects_StoreFileLib;
	L->GenRef = Objects_GenRef;
	L->GetObj = Objects_GetObj;
	L->PutObj = Objects_PutObj;
	L->FreeObj = Objects_FreeObj;
	__NEW(ind, Objects_ArrayIndexDesc);
	ind->org = 0;
	ind->size = 0;
	ind->index = NIL;
	L->ind = (Objects_Index)ind;
	__NEW(dict, Objects_ListDictDesc);
	dict->first = NIL;
	dict->key = 0;
	L->dict = (Objects_Dictionary)dict;
	L->maxref = 0;
}

static Objects_Library Objects_NewLibrary (void)
{
	Objects_Library L;
	__NEW(L, Objects_LibDesc);
	Objects_OpenLibrary(L);
	return L;
}

void Objects_GetRef (Objects_Dictionary *D, CHAR *name, ADDRESS name__len, INT16 *ref)
{
	Objects_Entry cur;
	__DUP(name, name__len, CHAR);
	if (__ISP(*D, Objects_ListDictDesc, 1)) {
		cur = __GUARDP(*D, Objects_ListDictDesc, 1)->first;
		while ((cur != NIL && (cur->key < 0 || __STRCMP(cur->name, name) != 0))) {
			cur = cur->next;
		}
		if (cur == NIL) {
			*ref = (-32767-1);
		} else {
			*ref = cur->key;
		}
	} else {
		*ref = (-32767-1);
	}
	__DEL(name);
}

void Objects_GetKey (Objects_Dictionary *D, CHAR *name, ADDRESS name__len, INT16 *key)
{
	Objects_Entry cur;
	__DUP(name, name__len, CHAR);
	if (__ISP(*D, Objects_ListDictDesc, 1)) {
	} else {
		*key = (-32767-1);
	}
	__DEL(name);
}

void Objects_GetName (Objects_Dictionary *D, INT16 key, CHAR *name, ADDRESS name__len)
{
	Objects_Entry cur;
	if (__ISP(*D, Objects_ListDictDesc, 1)) {
		cur = __GUARDP(*D, Objects_ListDictDesc, 1)->first;
		while ((cur != NIL && cur->key != key)) {
			cur = cur->next;
		}
		if (cur == NIL) {
			name[0] = 0x00;
		} else {
			__COPY(cur->name, name, name__len);
		}
	} else {
		name[0] = 0x00;
	}
}

void Objects_PutName (Objects_Dictionary *D, INT16 key, CHAR *name, ADDRESS name__len)
{
	Objects_Entry cur;
	__DUP(name, name__len, CHAR);
	if (__ISP(*D, Objects_ListDictDesc, 1)) {
		if (key >= 0) {
		}
	}
	__DEL(name);
}

static void EnumPtrs(void (*P)(void*))
{
	P(Objects_FirstLib);
	P(Objects_NoObj);
	P(Objects_NewObj);
	P(Objects_FirstAlias);
}

__TDESC(Objects_ObjMsg, 1, 1) = {__TDFLDS("ObjMsg", 8), {4, -8}};
__TDESC(Objects_ObjDesc, 1, 3) = {__TDFLDS("ObjDesc", 24), {4, 8, 12, -16}};
__TDESC(Objects_AttrMsg, 1, 1) = {__TDFLDS("AttrMsg", 144), {4, -8}};
__TDESC(Objects_LinkMsg, 1, 2) = {__TDFLDS("LinkMsg", 56), {4, 52, -12}};
__TDESC(Objects_CopyMsg, 1, 2) = {__TDFLDS("CopyMsg", 16), {4, 12, -12}};
__TDESC(Objects_BindMsg, 1, 2) = {__TDFLDS("BindMsg", 12), {4, 8, -12}};
__TDESC(Objects_FileMsg, 1, 4) = {__TDFLDS("FileMsg", 44), {4, 32, 36, 40, -20}};
__TDESC(Objects_FindMsg, 1, 2) = {__TDFLDS("FindMsg", 44), {4, 40, -12}};
__TDESC(Objects_DummyDesc, 1, 4) = {__TDFLDS("DummyDesc", 64), {4, 8, 12, 60, -20}};
__TDESC(Objects_IndexDesc, 1, 0) = {__TDFLDS("IndexDesc", 1), {-4}};
__TDESC(Objects_DictionaryDesc, 1, 0) = {__TDFLDS("DictionaryDesc", 1), {-4}};
__TDESC(Objects_ArrayIndexDesc, 1, 1) = {__TDFLDS("ArrayIndexDesc", 12), {0, -8}};
__TDESC(Objects_EntryDesc, 1, 1) = {__TDFLDS("EntryDesc", 40), {0, -8}};
__TDESC(Objects_ListDictDesc, 1, 1) = {__TDFLDS("ListDictDesc", 8), {4, -8}};
__TDESC(Objects_LibDesc, 1, 8) = {__TDFLDS("LibDesc", 108), {0, 4, 8, 28, 32, 36, 72, 80, -36}};
__TDESC(Objects_RunRec, 1, 0) = {__TDFLDS("RunRec", 4), {-4}};
__TDESC(Objects_AliasDesc, 1, 2) = {__TDFLDS("AliasDesc", 40), {0, 36, -12}};

export void *Objects__init(void)
{
	__DEFMOD;
	__MODULE_IMPORT(Files);
	__MODULE_IMPORT(Kernel);
	__MODULE_IMPORT(Modules);
	__REGMOD("Objects", EnumPtrs);
	__INITYP(Objects_ObjMsg, Objects_ObjMsg, 0);
	__INITYP(Objects_ObjDesc, Objects_ObjDesc, 0);
	__INITYP(Objects_AttrMsg, Objects_ObjMsg, 1);
	__INITYP(Objects_LinkMsg, Objects_ObjMsg, 1);
	__INITYP(Objects_CopyMsg, Objects_ObjMsg, 1);
	__INITYP(Objects_BindMsg, Objects_ObjMsg, 1);
	__INITYP(Objects_FileMsg, Objects_ObjMsg, 1);
	__INITYP(Objects_FindMsg, Objects_ObjMsg, 1);
	__INITYP(Objects_DummyDesc, Objects_ObjDesc, 1);
	__INITYP(Objects_IndexDesc, Objects_IndexDesc, 0);
	__INITYP(Objects_DictionaryDesc, Objects_DictionaryDesc, 0);
	__INITYP(Objects_ArrayIndexDesc, Objects_IndexDesc, 1);
	__INITYP(Objects_EntryDesc, Objects_EntryDesc, 0);
	__INITYP(Objects_ListDictDesc, Objects_DictionaryDesc, 1);
	__INITYP(Objects_LibDesc, Objects_LibDesc, 0);
	__INITYP(Objects_RunRec, Objects_RunRec, 0);
	__INITYP(Objects_AliasDesc, Objects_AliasDesc, 0);
/* BEGIN */
	Objects_LibBlockId = 0xdb;
	__NEW(Objects_FirstLib, Objects_LibDesc);
	Objects_FirstLib->next = NIL;
	__NEW(Objects_FirstAlias, Objects_AliasDesc);
	Objects_FirstAlias->next = NIL;
	Objects_stamp = (-2147483647-1);
	__NEW(Objects_NoObj, Objects_ObjDesc);
	Objects_nofreg = 0;
	Objects_Register((CHAR*)"Lib", 4, Objects_NewLibrary);
	__ENDMOD;
}
