/* voc 2.1.0 [2017/09/06]. Bootstrapping compiler for address size 8, alignment 8. xtaSv */

#define SHORTINT INT8
#define INTEGER  INT16
#define LONGINT  INT32
#define SET      UINT32

#include "SYSTEM.h"
#include "Kernel.h"

typedef
	struct OFS_RECORDVolume *OFS_Volume;

typedef
	void (*OFS_AllocProc)(OFS_Volume, INT32, INT32*);

typedef
	INT32 (*OFS_AvailableProc)(OFS_Volume);

typedef
	struct OFS_FileDesc *OFS_File;

typedef
	void (*OFS_CloseProc)(OFS_File);

typedef
	struct OFS_FileSystemDesc *OFS_FileSystem;

typedef
	void (*OFS_DeleteProc)(OFS_FileSystem, CHAR*, ADDRESS , INT32*, INT16*);

typedef
	void (*OFS_EntryHandler)(CHAR*, ADDRESS , INT32, INT32, INT32, UINT32*);

typedef
	void (*OFS_EnumerateProc)(OFS_FileSystem, CHAR*, ADDRESS , UINT32*, OFS_EntryHandler);

typedef
	struct OFS_FileDesc {
		OFS_File next;
		INT32 key;
		OFS_FileSystem fs;
	} OFS_FileDesc;

typedef
	INT32 (*OFS_FileKeyProc)(OFS_FileSystem, CHAR*, ADDRESS );

typedef
	CHAR OFS_FileName[144];

typedef
	CHAR OFS_Prefix[16];

typedef
	OFS_File (*OFS_NewOldProc)(OFS_FileSystem, CHAR*, ADDRESS );

typedef
	void (*OFS_RenameProc)(OFS_FileSystem, CHAR*, ADDRESS , CHAR*, ADDRESS , INT16*);

typedef
	void (*OFS_RegisterProc)(OFS_File, INT16*);

typedef
	INT32 (*OFS_LengthProc)(OFS_File);

typedef
	void (*OFS_GetDateProc)(OFS_File, INT32*, INT32*);

typedef
	void (*OFS_SetDateProc)(OFS_File, INT32, INT32);

typedef
	void (*OFS_GetNameProc)(OFS_File, CHAR*, ADDRESS );

typedef
	struct OFS_HintDesc *OFS_Hint;

typedef
	struct OFS_Rider {
		BOOLEAN eof;
		INT32 res, apos, bpos;
		OFS_Hint hint;
		OFS_File file;
		OFS_FileSystem fs;
	} OFS_Rider;

typedef
	void (*OFS_SetProc)(OFS_Rider*, ADDRESS *, OFS_File, INT32);

typedef
	INT32 (*OFS_PosProc)(OFS_Rider*, ADDRESS *);

typedef
	void (*OFS_ReadProc)(OFS_Rider*, ADDRESS *, SYSTEM_BYTE*);

typedef
	void (*OFS_WriteProc)(OFS_Rider*, ADDRESS *, SYSTEM_BYTE);

typedef
	void (*OFS_ReadWriteBytesProc)(OFS_Rider*, ADDRESS *, SYSTEM_BYTE*, ADDRESS , INT32);

typedef
	void (*OFS_FinalizeFSProc)(OFS_FileSystem);

typedef
	struct OFS_Message {
		char _prvt0[1];
	} OFS_Message;

typedef
	void (*OFS_HandleProc)(OFS_FileSystem, OFS_Message*, ADDRESS *, INT32*);

typedef
	void (*OFS_PurgeProc)(OFS_FileSystem, OFS_File);

typedef
	BOOLEAN (*OFS_RegisteredProc)(OFS_FileSystem, OFS_File);

typedef
	struct OFS_FileSystemDesc {
		OFS_FileSystem next, link;
		OFS_Prefix prefix;
		CHAR desc[32];
		OFS_Volume vol;
		OFS_FileKeyProc FileKey;
		OFS_NewOldProc New, Old;
		OFS_DeleteProc Delete;
		OFS_RenameProc Rename;
		OFS_EnumerateProc Enumerate;
		OFS_CloseProc Close;
		OFS_RegisterProc Register;
		OFS_LengthProc Length;
		OFS_GetDateProc GetDate;
		OFS_SetDateProc SetDate;
		OFS_GetNameProc GetName;
		OFS_SetProc Set;
		OFS_PosProc Pos;
		OFS_ReadProc Read;
		OFS_WriteProc Write;
		OFS_ReadWriteBytesProc ReadBytes, WriteBytes;
		OFS_FinalizeFSProc Finalize;
		OFS_HandleProc Handle;
		OFS_PurgeProc Purge;
		OFS_RegisteredProc Registered;
	} OFS_FileSystemDesc;

typedef
	void (*OFS_FinalizeVolProc)(OFS_Volume);

typedef
	void (*OFS_FreeMarkProc)(OFS_Volume, INT32);

typedef
	void (*OFS_GetPutProc)(OFS_Volume, INT32, SYSTEM_BYTE*, ADDRESS );

typedef
	struct OFS_HintDesc {
		char _prvt0[1];
	} OFS_HintDesc;

typedef
	CHAR OFS_LocalName[128];

typedef
	BOOLEAN (*OFS_MarkedProc)(OFS_Volume, INT32);

typedef
	void (*OFS_SyncProc)(OFS_Volume);

typedef
	struct OFS_RECORDVolume {
		struct {
			ADDRESS len[1];
			UINT32 data[1];
		} *map;
		INT32 used;
		CHAR name[32];
		INT32 blockSize, size;
		UINT32 flags;
		OFS_AllocProc AllocBlock;
		OFS_FreeMarkProc FreeBlock, MarkBlock;
		OFS_MarkedProc Marked;
		OFS_AvailableProc Available;
		OFS_GetPutProc GetBlock, PutBlock;
		OFS_FinalizeVolProc Finalize;
		OFS_SyncProc Sync;
	} OFS_RECORDVolume;


static CHAR OFS_par[256];
static INT32 OFS_pos;
export OFS_Volume OFS_NewVol;
static OFS_FileSystem OFS_fsroot, OFS_fsmount;
static OFS_File OFS_froot;

export ADDRESS *OFS_RECORDVolume__typ;
export ADDRESS *OFS_Rider__typ;
export ADDRESS *OFS_FileDesc__typ;
export ADDRESS *OFS_Message__typ;
export ADDRESS *OFS_FileSystemDesc__typ;
export ADDRESS *OFS_HintDesc__typ;

export void OFS_Add (OFS_FileSystem fs, CHAR *prefix, ADDRESS prefix__len);
export void OFS_AllocBlock (OFS_Volume vol, INT32 hint, INT32 *adr);
export void OFS_AppendInt (INT32 x, CHAR *to, ADDRESS to__len);
export void OFS_AppendStr (CHAR *from, ADDRESS from__len, CHAR *to, ADDRESS to__len);
export INT32 OFS_Available (OFS_Volume vol);
static void OFS_Collect (SYSTEM_PTR f);
export void OFS_Delete (CHAR *name, ADDRESS name__len, INT16 *res);
static void OFS_DeleteFS (OFS_FileSystem fs);
export void OFS_Enumerate (CHAR *mask, ADDRESS mask__len, UINT32 *flags, OFS_EntryHandler proc);
static void OFS_FSCleanup (void);
static void OFS_FileCleanup (SYSTEM_PTR f);
export void OFS_FinalizeVol (OFS_Volume vol);
export OFS_File OFS_FindOpenFile (OFS_FileSystem fs, INT32 key);
export OFS_FileSystem OFS_First (void);
export void OFS_FreeBlock (OFS_Volume vol, INT32 adr);
export BOOLEAN OFS_HasOpenFiles (OFS_FileSystem fs);
export void OFS_InitVol (OFS_Volume vol);
export void OFS_JoinName (CHAR *prefix, ADDRESS prefix__len, CHAR *name, ADDRESS name__len, CHAR *fullname, ADDRESS fullname__len);
export void OFS_MarkBlock (OFS_Volume vol, INT32 adr);
export BOOLEAN OFS_Marked (OFS_Volume vol, INT32 adr);
export OFS_File OFS_New (CHAR *name, ADDRESS name__len);
export OFS_FileSystem OFS_Next (OFS_FileSystem fs);
export OFS_File OFS_Old (CHAR *name, ADDRESS name__len);
static OFS_File OFS_Open (OFS_FileSystem fs, CHAR *fname, ADDRESS fname__len);
export void OFS_Promote (OFS_FileSystem fs);
export void OFS_ReadPar (CHAR *ch);
export void OFS_Register (OFS_File f);
export void OFS_Remove (OFS_FileSystem fs);
export void OFS_Rename (CHAR *old, ADDRESS old__len, CHAR *new, ADDRESS new__len, INT16 *res);
export void OFS_SetPar (CHAR *str, ADDRESS str__len);
export void OFS_SplitName (CHAR *fullname, ADDRESS fullname__len, CHAR *prefix, ADDRESS prefix__len, CHAR *name, ADDRESS name__len);
export void OFS_Sync (OFS_Volume vol);
export OFS_FileSystem OFS_This (CHAR *prefix, ADDRESS prefix__len);
static void OFS_WriteFS (OFS_FileSystem fs);


void OFS_AllocBlock (OFS_Volume vol, INT32 hint, INT32 *adr)
{
	if (__IN(0, vol->flags, 32)) {
		__HALT(21);
	}
	if ((__IN(2, vol->flags, 32) && vol->size - vol->used <= 32)) {
		__HALT(20);
	}
	__ASSERT(hint >= 0, 0);
	if (hint > vol->size) {
		hint = 0;
	}
	*adr = hint + 1;
	for (;;) {
		if (*adr > vol->size) {
			*adr = 0;
		}
		if (__IN(__MASK(*adr, -32), (vol->map->data)[__X(__ASHR(*adr, 5), vol->map->len[0])], 32)) {
			*adr += 1;
		} else {
			(vol->map->data)[__X(__ASHR(*adr, 5), vol->map->len[0])] |= __SETOF(__MASK(*adr, -32),32);
			break;
		}
		if (*adr == hint) {
			__HALT(20);
		}
	}
	vol->used += 1;
}

void OFS_FreeBlock (OFS_Volume vol, INT32 adr)
{
	if (adr < 1 || adr > vol->size) {
		__HALT(15);
	}
	if (__IN(0, vol->flags, 32)) {
		__HALT(21);
	}
	(vol->map->data)[__X(__ASHR(adr, 5), vol->map->len[0])] &= ~__SETOF(__MASK(adr, -32),32);
	vol->used -= 1;
}

void OFS_MarkBlock (OFS_Volume vol, INT32 adr)
{
	if (adr < 1 || adr > vol->size) {
		__HALT(15);
	}
	if (__IN(0, vol->flags, 32)) {
		__HALT(21);
	}
	(vol->map->data)[__X(__ASHR(adr, 5), vol->map->len[0])] |= __SETOF(__MASK(adr, -32),32);
	vol->used += 1;
}

BOOLEAN OFS_Marked (OFS_Volume vol, INT32 adr)
{
	if (adr < 1 || adr > vol->size) {
		__HALT(15);
	}
	if (__IN(0, vol->flags, 32)) {
		__HALT(21);
	}
	return __IN(__MASK(adr, -32), (vol->map->data)[__X(__ASHR(adr, 5), vol->map->len[0])], 32);
}

INT32 OFS_Available (OFS_Volume vol)
{
	return vol->size - vol->used;
}

void OFS_Sync (OFS_Volume vol)
{
}

void OFS_InitVol (OFS_Volume vol)
{
	INT32 maplen;
	if (!__IN(0, vol->flags, 32)) {
		maplen = __ASHR((vol->size + 1) + 31, 5);
		vol->map = __NEWARR(NIL, 4, 4, 1, 1, ((ADDRESS)(maplen)));
		while (maplen > 0) {
			maplen -= 1;
			(vol->map->data)[__X(maplen, vol->map->len[0])] = 0x0;
		}
		(vol->map->data)[0] |= __SETOF(0,32);
		vol->used = 0;
	} else {
		vol->used = vol->size;
	}
}

void OFS_FinalizeVol (OFS_Volume vol)
{
	vol->map = NIL;
	vol->AllocBlock = NIL;
	vol->FreeBlock = NIL;
	vol->MarkBlock = NIL;
	vol->Marked = NIL;
	vol->Available = NIL;
	vol->GetBlock = NIL;
	vol->PutBlock = NIL;
	vol->Sync = NIL;
	vol->Finalize = NIL;
}

void OFS_SetPar (CHAR *str, ADDRESS str__len)
{
	__DUP(str, str__len, CHAR);
	__COPY(str, OFS_par, 256);
	OFS_pos = 0;
	__DEL(str);
}

void OFS_ReadPar (CHAR *ch)
{
	*ch = OFS_par[__X(OFS_pos, 256)];
	if (*ch == 0x00) {
		OFS_pos = 0;
		OFS_par[0] = 0x00;
	} else {
		OFS_pos += 1;
	}
}

void OFS_SplitName (CHAR *fullname, ADDRESS fullname__len, CHAR *prefix, ADDRESS prefix__len, CHAR *name, ADDRESS name__len)
{
	INT32 i, j;
	__DUP(fullname, fullname__len, CHAR);
	i = 0;
	while ((fullname[__X(i, fullname__len)] != ':' && fullname[__X(i, fullname__len)] != 0x00)) {
		i += 1;
	}
	if (fullname[__X(i, fullname__len)] != ':' || i >= prefix__len) {
		__COPY("", prefix, prefix__len);
		__COPY(fullname, name, name__len);
	} else {
		j = 0;
		while (j != i) {
			prefix[__X(j, prefix__len)] = fullname[__X(j, fullname__len)];
			j += 1;
		}
		prefix[__X(j, prefix__len)] = 0x00;
		j = 0;
		do {
			i += 1;
			name[__X(j, name__len)] = fullname[__X(i, fullname__len)];
			j += 1;
		} while (!(fullname[__X(i, fullname__len)] == 0x00));
	}
	__DEL(fullname);
}

void OFS_JoinName (CHAR *prefix, ADDRESS prefix__len, CHAR *name, ADDRESS name__len, CHAR *fullname, ADDRESS fullname__len)
{
	INT32 i, j;
	__DUP(prefix, prefix__len, CHAR);
	__DUP(name, name__len, CHAR);
	i = 0;
	while (prefix[__X(i, prefix__len)] != 0x00) {
		fullname[__X(i, fullname__len)] = prefix[__X(i, prefix__len)];
		i += 1;
	}
	fullname[__X(i, fullname__len)] = ':';
	i += 1;
	j = 0;
	while (name[__X(j, name__len)] != 0x00) {
		fullname[__X(i, fullname__len)] = name[__X(j, name__len)];
		i += 1;
		j += 1;
	}
	fullname[__X(i, fullname__len)] = 0x00;
	__DEL(prefix);
	__DEL(name);
}

static void OFS_WriteFS (OFS_FileSystem fs)
{
}

void OFS_Add (OFS_FileSystem fs, CHAR *prefix, ADDRESS prefix__len)
{
	OFS_FileSystem p, c;
	__DUP(prefix, prefix__len, CHAR);
	__COPY(prefix, fs->prefix, 16);
	p = NIL;
	c = OFS_fsroot;
	while (c != NIL) {
		__ASSERT((c != fs && __STRCMP(c->prefix, fs->prefix) != 0), 0);
		p = c;
		c = c->next;
	}
	if (p == NIL) {
		OFS_fsroot = fs;
	} else {
		p->next = fs;
	}
	fs->next = NIL;
	fs->link = OFS_fsmount;
	OFS_fsmount = fs;
	__DEL(prefix);
}

static void OFS_DeleteFS (OFS_FileSystem fs)
{
	OFS_FileSystem p, c;
	p = NIL;
	c = OFS_fsroot;
	while (c != fs) {
		p = c;
		c = c->next;
	}
	if (p == NIL) {
		OFS_fsroot = c->next;
	} else {
		p->next = c->next;
	}
	c->next = NIL;
}

void OFS_Promote (OFS_FileSystem fs)
{
	OFS_DeleteFS(fs);
	fs->next = OFS_fsroot;
	OFS_fsroot = fs;
}

void OFS_Remove (OFS_FileSystem fs)
{
	OFS_File f;
	INT32 count;
	OFS_FileSystem p, c;
	f = OFS_froot->next;
	count = 0;
	while (f != NIL) {
		if (f->fs == fs) {
			count += 1;
			(*fs->Close)(f);
			f->fs = NIL;
		}
		f = f->next;
	}
	if (count != 0) {
		Kernel_WriteString((CHAR*)"OFS: ", 6);
		Kernel_WriteInt(count, 1);
		Kernel_WriteString((CHAR*)" open files", 12);
		if (fs->vol != NIL) {
			Kernel_WriteString((CHAR*)" on ", 5);
			Kernel_WriteString(fs->vol->name, 32);
		}
		Kernel_WriteLn();
	}
	(*fs->Finalize)(fs);
	OFS_DeleteFS(fs);
	p = NIL;
	c = OFS_fsmount;
	while (c != fs) {
		p = c;
		c = c->link;
	}
	if (p == NIL) {
		OFS_fsmount = c->link;
	} else {
		p->link = c->link;
	}
	c->link = NIL;
}

OFS_FileSystem OFS_This (CHAR *prefix, ADDRESS prefix__len)
{
	OFS_FileSystem fs;
	__DUP(prefix, prefix__len, CHAR);
	fs = OFS_fsroot;
	while ((fs != NIL && __STRCMP(fs->prefix, prefix) != 0)) {
		fs = fs->next;
	}
	__DEL(prefix);
	return fs;
}

OFS_FileSystem OFS_First (void)
{
	return OFS_fsroot;
}

OFS_FileSystem OFS_Next (OFS_FileSystem fs)
{
	return fs->next;
}

static void OFS_Collect (SYSTEM_PTR f)
{
	if (__ISP(f, OFS_FileDesc, 0)) {
		if (((((*(OFS_File*)&f)->fs != NIL && (*(OFS_File*)&f)->fs->Registered != NIL)) && (*(OFS_File*)&f)->fs->vol != NIL)) {
			if (!__IN(0, (*(OFS_File*)&f)->fs->vol->flags, 32)) {
				if (!(*(*(OFS_File*)&f)->fs->Registered)((*(OFS_File*)&f)->fs, (*(OFS_File*)&f))) {
					(*(*(OFS_File*)&f)->fs->Purge)((*(OFS_File*)&f)->fs, (*(OFS_File*)&f));
				}
			}
		}
	} else __WITHCHK;
}

static void OFS_FileCleanup (SYSTEM_PTR f)
{
	OFS_File p, c;
	if (__ISP(f, OFS_FileDesc, 0)) {
		p = OFS_froot;
		c = OFS_froot->next;
		while (c != NIL) {
			if (c == (*(OFS_File*)&f)) {
				p->next = c->next;
			} else {
				p = c;
			}
			c = c->next;
		}
	} else __WITHCHK;
}

static OFS_File OFS_Open (OFS_FileSystem fs, CHAR *fname, ADDRESS fname__len)
{
	OFS_File f;
	INT32 key;
	f = NIL;
	if ((fs != NIL && fname[0] != 0x00)) {
		key = (*fs->FileKey)(fs, fname, fname__len);
		if (key != 0) {
			f = OFS_froot->next;
			while ((f != NIL && (f->fs != fs || f->key != key))) {
				f = f->next;
			}
		}
		if (f == NIL) {
			f = (*fs->Old)(fs, fname, fname__len);
			if (f != NIL) {
				__ASSERT(f->key != 0, 0);
				f->next = OFS_froot->next;
				OFS_froot->next = f;
				Kernel_RegisterObject((void*)f, OFS_Collect, 0);
				Kernel_RegisterObject((void*)f, OFS_FileCleanup, 0);
			}
		}
	}
	return f;
}

OFS_File OFS_Old (CHAR *name, ADDRESS name__len)
{
	OFS_FileSystem fs;
	OFS_File f;
	OFS_Prefix prefix;
	OFS_LocalName fname;
	f = NIL;
	OFS_SplitName(name, name__len, (void*)prefix, 16, (void*)fname, 128);
	if (prefix[0] == 0x00) {
		fs = OFS_First();
		while ((fs != NIL && f == NIL)) {
			f = OFS_Open(fs, (void*)fname, 128);
			fs = OFS_Next(fs);
		}
	} else {
		f = OFS_Open(OFS_This(prefix, 16), (void*)fname, 128);
	}
	return f;
}

OFS_File OFS_New (CHAR *name, ADDRESS name__len)
{
	OFS_FileSystem fs;
	OFS_File f;
	OFS_Prefix prefix;
	OFS_LocalName fname;
	f = NIL;
	OFS_SplitName(name, name__len, (void*)prefix, 16, (void*)fname, 128);
	if (prefix[0] == 0x00) {
		fs = OFS_First();
		if (fname[0] == 0x00) {
			while ((fs != NIL && (fs->vol == NIL || ((fs->vol->flags & 0x05)) != 0x04))) {
				fs = OFS_Next(fs);
			}
			if (fs == NIL) {
				fs = OFS_First();
			}
		}
	} else {
		fs = OFS_This(prefix, 16);
	}
	if (fs != NIL) {
		if (fs->vol == NIL || !__IN(0, fs->vol->flags, 32)) {
			f = (*fs->New)(fs, fname, 128);
			if (f != NIL) {
				Kernel_RegisterObject((void*)f, OFS_Collect, 0);
			}
		}
	}
	return f;
}

void OFS_Delete (CHAR *name, ADDRESS name__len, INT16 *res)
{
	OFS_FileSystem fs;
	OFS_File p, c;
	INT32 key;
	OFS_Prefix prefix;
	OFS_LocalName fname;
	OFS_SplitName(name, name__len, (void*)prefix, 16, (void*)fname, 128);
	if (prefix[0] == 0x00) {
		fs = OFS_First();
	} else {
		fs = OFS_This(prefix, 16);
	}
	if (fs != NIL) {
		if (fs->vol == NIL || !__IN(0, fs->vol->flags, 32)) {
			(*fs->Delete)(fs, fname, 128, &key, &*res);
			if (key != 0) {
				p = OFS_froot;
				c = OFS_froot->next;
				while (c != NIL) {
					if ((c->fs == fs && c->key == key)) {
						p->next = c->next;
					} else {
						p = c;
					}
					c = c->next;
				}
			}
		} else {
			*res = 3;
		}
	} else {
		*res = 2;
	}
}

void OFS_Rename (CHAR *old, ADDRESS old__len, CHAR *new, ADDRESS new__len, INT16 *res)
{
	OFS_FileSystem ofs, nfs;
	OFS_Prefix pold, pnew;
	OFS_LocalName fold, fnew;
	OFS_SplitName(old, old__len, (void*)pold, 16, (void*)fold, 128);
	OFS_SplitName(new, new__len, (void*)pnew, 16, (void*)fnew, 128);
	if (pold[0] == 0x00) {
		ofs = OFS_First();
	} else {
		ofs = OFS_This(pold, 16);
	}
	if (pnew[0] == 0x00) {
		nfs = OFS_First();
	} else {
		nfs = OFS_This(pnew, 16);
	}
	if ((nfs != NIL && ofs == nfs)) {
		if (nfs->vol == NIL || !__IN(0, nfs->vol->flags, 32)) {
			(*nfs->Rename)(nfs, fold, 128, fnew, 128, &*res);
		} else {
			*res = 3;
		}
	} else {
		*res = 2;
	}
}

void OFS_Register (OFS_File f)
{
	INT16 res;
	if (f != NIL) {
		(*f->fs->Register)(f, &res);
		if (res == 0) {
			__ASSERT(f->key != 0, 0);
			f->next = OFS_froot->next;
			OFS_froot->next = f;
			Kernel_RegisterObject((void*)f, OFS_FileCleanup, 0);
		} else {
			if (res == 1) {
			} else {
				__HALT(17);
			}
		}
	}
}

void OFS_Enumerate (CHAR *mask, ADDRESS mask__len, UINT32 *flags, OFS_EntryHandler proc)
{
	OFS_FileSystem fs;
	OFS_Prefix prefix;
	OFS_LocalName fmask;
	OFS_SplitName(mask, mask__len, (void*)prefix, 16, (void*)fmask, 128);
	if (prefix[0] == 0x00) {
		fs = OFS_First();
		while (fs != NIL) {
			*flags &= ~__SETOF(15,32);
			(*fs->Enumerate)(fs, fmask, 128, &*flags, proc);
			fs = OFS_Next(fs);
		}
	} else {
		fs = OFS_This(prefix, 16);
		if (fs != NIL) {
			(*fs->Enumerate)(fs, fmask, 128, &*flags, proc);
		}
	}
}

OFS_File OFS_FindOpenFile (OFS_FileSystem fs, INT32 key)
{
	OFS_File f;
	f = OFS_froot;
	do {
		f = f->next;
	} while (!(f == NIL || (f->key == key && f->fs == fs)));
	return f;
}

BOOLEAN OFS_HasOpenFiles (OFS_FileSystem fs)
{
	OFS_File f;
	f = OFS_froot;
	do {
		f = f->next;
	} while (!(f == NIL || f->fs == fs));
	return f != NIL;
}

void OFS_AppendStr (CHAR *from, ADDRESS from__len, CHAR *to, ADDRESS to__len)
{
	INT32 i, j, m;
	__DUP(from, from__len, CHAR);
	j = 0;
	while (to[__X(j, to__len)] != 0x00) {
		j += 1;
	}
	m = to__len - 1;
	i = 0;
	while ((from[__X(i, from__len)] != 0x00 && j != m)) {
		to[__X(j, to__len)] = from[__X(i, from__len)];
		i += 1;
		j += 1;
	}
	to[__X(j, to__len)] = 0x00;
	__DEL(from);
}

void OFS_AppendInt (INT32 x, CHAR *to, ADDRESS to__len)
{
	INT32 i, m;
	i = 0;
	while (to[__X(i, to__len)] != 0x00) {
		i += 1;
	}
	if (x < 0) {
		to[__X(i, to__len)] = '-';
		i += 1;
		x = -x;
	}
	if (x != 0) {
		m = 1000000000;
		while (x < m) {
			m = __DIV(m, 10);
		}
		do {
			to[__X(i, to__len)] = (CHAR)(48 + (int)__MOD(__DIV(x, m), 10));
			i += 1;
			m = __DIV(m, 10);
		} while (!(m == 0));
	} else {
		to[__X(i, to__len)] = '0';
		i += 1;
	}
	to[__X(i, to__len)] = 0x00;
}

static void OFS_FSCleanup (void)
{
	while (OFS_fsmount != NIL) {
		OFS_Remove(OFS_fsmount);
	}
}

static void EnumPtrs(void (*P)(void*))
{
	P(OFS_NewVol);
	P(OFS_fsroot);
	P(OFS_fsmount);
	P(OFS_froot);
}

__TDESC(OFS_RECORDVolume, 1, 1) = {__TDFLDS("RECORDVolume", 88), {0, -8}};
__TDESC(OFS_Rider, 1, 3) = {__TDFLDS("Rider", 28), {16, 20, 24, -16}};
__TDESC(OFS_FileDesc, 1, 2) = {__TDFLDS("FileDesc", 12), {0, 8, -12}};
__TDESC(OFS_Message, 1, 0) = {__TDFLDS("Message", 1), {-4}};
__TDESC(OFS_FileSystemDesc, 1, 3) = {__TDFLDS("FileSystemDesc", 148), {0, 4, 56, -16}};
__TDESC(OFS_HintDesc, 1, 0) = {__TDFLDS("HintDesc", 1), {-4}};

export void *OFS__init(void)
{
	__DEFMOD;
	__MODULE_IMPORT(Kernel);
	__REGMOD("OFS", EnumPtrs);
	__INITYP(OFS_RECORDVolume, OFS_RECORDVolume, 0);
	__INITYP(OFS_Rider, OFS_Rider, 0);
	__INITYP(OFS_FileDesc, OFS_FileDesc, 0);
	__INITYP(OFS_Message, OFS_Message, 0);
	__INITYP(OFS_FileSystemDesc, OFS_FileSystemDesc, 0);
	__INITYP(OFS_HintDesc, OFS_HintDesc, 0);
/* BEGIN */
	OFS_pos = 0;
	OFS_par[0] = 0x00;
	OFS_fsroot = NIL;
	OFS_fsmount = NIL;
	__NEW(OFS_froot, OFS_FileDesc);
	OFS_froot->next = NIL;
	Kernel_InstallTermHandler(OFS_FSCleanup);
	__ENDMOD;
}
