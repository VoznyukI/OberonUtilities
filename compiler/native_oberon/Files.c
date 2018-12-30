/* voc 2.1.0 [2017/09/06]. Bootstrapping compiler for address size 8, alignment 8. xtaSv */

#define SHORTINT INT8
#define INTEGER  INT16
#define LONGINT  INT32
#define SET      UINT32

#include "SYSTEM.h"
#include "OFS.h"

typedef
	SYSTEM_BYTE Files_Bytes4[4];

typedef
	SYSTEM_BYTE Files_Bytes8[8];




export OFS_File Files_Base (OFS_Rider *r, ADDRESS *r__typ);
export void Files_Close (OFS_File f);
export void Files_Delete (CHAR *name, ADDRESS name__len, INT16 *res);
export void Files_GetDate (OFS_File f, INT32 *t, INT32 *d);
export void Files_GetName (OFS_File f, CHAR *name, ADDRESS name__len);
export INT32 Files_Length (OFS_File f);
export OFS_File Files_New (CHAR *name, ADDRESS name__len);
export OFS_File Files_Old (CHAR *name, ADDRESS name__len);
export INT32 Files_Pos (OFS_Rider *r, ADDRESS *r__typ);
export void Files_Read (OFS_Rider *r, ADDRESS *r__typ, SYSTEM_BYTE *x);
export void Files_ReadBool (OFS_Rider *r, ADDRESS *r__typ, BOOLEAN *x);
export void Files_ReadBytes (OFS_Rider *r, ADDRESS *r__typ, SYSTEM_BYTE *x, ADDRESS x__len, INT32 n);
export void Files_ReadInt (OFS_Rider *r, ADDRESS *r__typ, INT16 *x);
export void Files_ReadLInt (OFS_Rider *r, ADDRESS *r__typ, INT32 *x);
export void Files_ReadLReal (OFS_Rider *r, ADDRESS *r__typ, LONGREAL *x);
export void Files_ReadNum (OFS_Rider *r, ADDRESS *r__typ, INT32 *x);
export void Files_ReadReal (OFS_Rider *r, ADDRESS *r__typ, REAL *x);
export void Files_ReadSet (OFS_Rider *r, ADDRESS *r__typ, UINT32 *x);
export void Files_ReadString (OFS_Rider *r, ADDRESS *r__typ, CHAR *x, ADDRESS x__len);
export void Files_Register (OFS_File f);
export void Files_Rename (CHAR *old, ADDRESS old__len, CHAR *new, ADDRESS new__len, INT16 *res);
export void Files_Set (OFS_Rider *r, ADDRESS *r__typ, OFS_File f, INT32 pos);
export void Files_SetDate (OFS_File f, INT32 t, INT32 d);
export void Files_Write (OFS_Rider *r, ADDRESS *r__typ, SYSTEM_BYTE x);
export void Files_WriteBool (OFS_Rider *r, ADDRESS *r__typ, BOOLEAN x);
export void Files_WriteBytes (OFS_Rider *r, ADDRESS *r__typ, SYSTEM_BYTE *x, ADDRESS x__len, INT32 n);
export void Files_WriteInt (OFS_Rider *r, ADDRESS *r__typ, INT16 x);
export void Files_WriteLInt (OFS_Rider *r, ADDRESS *r__typ, INT32 x);
export void Files_WriteLReal (OFS_Rider *r, ADDRESS *r__typ, LONGREAL x);
export void Files_WriteNum (OFS_Rider *r, ADDRESS *r__typ, INT32 x);
export void Files_WriteReal (OFS_Rider *r, ADDRESS *r__typ, REAL x);
export void Files_WriteSet (OFS_Rider *r, ADDRESS *r__typ, UINT32 x);
export void Files_WriteString (OFS_Rider *r, ADDRESS *r__typ, CHAR *x, ADDRESS x__len);


OFS_File Files_New (CHAR *name, ADDRESS name__len)
{
	__DUP(name, name__len, CHAR);
	__DEL(name);
	return OFS_New((void*)name, name__len);
}

OFS_File Files_Old (CHAR *name, ADDRESS name__len)
{
	__DUP(name, name__len, CHAR);
	__DEL(name);
	return OFS_Old((void*)name, name__len);
}

void Files_Register (OFS_File f)
{
	OFS_Register(f);
}

void Files_Close (OFS_File f)
{
	if (f != NIL) {
		(*f->fs->Close)(f);
	}
}

INT32 Files_Length (OFS_File f)
{
	return (*f->fs->Length)(f);
}

void Files_GetDate (OFS_File f, INT32 *t, INT32 *d)
{
	(*f->fs->GetDate)(f, &*t, &*d);
}

void Files_SetDate (OFS_File f, INT32 t, INT32 d)
{
	(*f->fs->SetDate)(f, t, d);
}

void Files_Set (OFS_Rider *r, ADDRESS *r__typ, OFS_File f, INT32 pos)
{
	if (f != NIL) {
		(*f->fs->Set)(&*r, r__typ, f, pos);
	} else {
		(*r).hint = NIL;
		(*r).file = NIL;
		(*r).fs = NIL;
	}
}

INT32 Files_Pos (OFS_Rider *r, ADDRESS *r__typ)
{
	return (*(*r).fs->Pos)(&*r, r__typ);
}

OFS_File Files_Base (OFS_Rider *r, ADDRESS *r__typ)
{
	return (*r).file;
}

void Files_Read (OFS_Rider *r, ADDRESS *r__typ, SYSTEM_BYTE *x)
{
	(*(*r).fs->Read)(&*r, r__typ, &*x);
}

void Files_ReadBytes (OFS_Rider *r, ADDRESS *r__typ, SYSTEM_BYTE *x, ADDRESS x__len, INT32 n)
{
	(*(*r).fs->ReadBytes)(&*r, r__typ, (void*)x, x__len * 1, n);
}

void Files_ReadInt (OFS_Rider *r, ADDRESS *r__typ, INT16 *x)
{
	INT8 x0, x1;
	(*(*r).fs->Read)(&*r, r__typ, (void*)&x0);
	(*(*r).fs->Read)(&*r, r__typ, (void*)&x1);
	*x = __ASHL((INT16)x1, 8) + __MASK((INT16)x0, -256);
}

void Files_ReadLInt (OFS_Rider *r, ADDRESS *r__typ, INT32 *x)
{
	(*(*r).fs->ReadBytes)(&*r, r__typ, (Files_Bytes4*)(*x), 4, 4);
}

void Files_ReadSet (OFS_Rider *r, ADDRESS *r__typ, UINT32 *x)
{
	(*(*r).fs->ReadBytes)(&*r, r__typ, (Files_Bytes4*)(*x), 4, 4);
}

void Files_ReadBool (OFS_Rider *r, ADDRESS *r__typ, BOOLEAN *x)
{
	INT8 s;
	(*(*r).fs->Read)(&*r, r__typ, (void*)&s);
	*x = s != 0;
}

void Files_ReadReal (OFS_Rider *r, ADDRESS *r__typ, REAL *x)
{
	(*(*r).fs->ReadBytes)(&*r, r__typ, (Files_Bytes4*)(*x), 4, 4);
}

void Files_ReadLReal (OFS_Rider *r, ADDRESS *r__typ, LONGREAL *x)
{
	(*(*r).fs->ReadBytes)(&*r, r__typ, (Files_Bytes8*)(*x), 8, 8);
}

void Files_ReadString (OFS_Rider *r, ADDRESS *r__typ, CHAR *x, ADDRESS x__len)
{
	INT16 i;
	CHAR ch;
	i = 0;
	for (;;) {
		(*(*r).fs->Read)(&*r, r__typ, (void*)&ch);
		x[__X(i, x__len)] = ch;
		i += 1;
		if (ch == 0x00) {
			break;
		}
		if (i == x__len) {
			x[__X(i - 1, x__len)] = 0x00;
			do {
				(*(*r).fs->Read)(&*r, r__typ, (void*)&ch);
			} while (!(ch == 0x00));
			break;
		}
	}
}

void Files_ReadNum (OFS_Rider *r, ADDRESS *r__typ, INT32 *x)
{
	CHAR ch;
	INT16 n;
	INT32 y;
	n = 0;
	y = 0;
	(*(*r).fs->Read)(&*r, r__typ, (void*)&ch);
	while (ch >= 0x80) {
		y += __LSH(ch - 128, n, 32);
		n += 7;
		(*(*r).fs->Read)(&*r, r__typ, (void*)&ch);
	}
	*x = __ASH(__LSHL(ch, 25, 32), n - 25) + y;
}

void Files_Write (OFS_Rider *r, ADDRESS *r__typ, SYSTEM_BYTE x)
{
	(*(*r).fs->Write)(&*r, r__typ, x);
}

void Files_WriteBytes (OFS_Rider *r, ADDRESS *r__typ, SYSTEM_BYTE *x, ADDRESS x__len, INT32 n)
{
	(*(*r).fs->WriteBytes)(&*r, r__typ, (void*)x, x__len * 1, n);
}

void Files_WriteInt (OFS_Rider *r, ADDRESS *r__typ, INT16 x)
{
	(*(*r).fs->Write)(&*r, r__typ, (INT8)x);
	(*(*r).fs->Write)(&*r, r__typ, (INT8)__ASHR(x, 8));
}

void Files_WriteLInt (OFS_Rider *r, ADDRESS *r__typ, INT32 x)
{
	(*(*r).fs->WriteBytes)(&*r, r__typ, (Files_Bytes4*)x, 4, 4);
}

void Files_WriteSet (OFS_Rider *r, ADDRESS *r__typ, UINT32 x)
{
	(*(*r).fs->WriteBytes)(&*r, r__typ, (Files_Bytes4*)x, 4, 4);
}

void Files_WriteBool (OFS_Rider *r, ADDRESS *r__typ, BOOLEAN x)
{
	if (x) {
		(*(*r).fs->Write)(&*r, r__typ, 1);
	} else {
		(*(*r).fs->Write)(&*r, r__typ, 0);
	}
}

void Files_WriteReal (OFS_Rider *r, ADDRESS *r__typ, REAL x)
{
	(*(*r).fs->WriteBytes)(&*r, r__typ, (Files_Bytes4*)x, 4, 4);
}

void Files_WriteLReal (OFS_Rider *r, ADDRESS *r__typ, LONGREAL x)
{
	(*(*r).fs->WriteBytes)(&*r, r__typ, (Files_Bytes8*)x, 8, 8);
}

void Files_WriteString (OFS_Rider *r, ADDRESS *r__typ, CHAR *x, ADDRESS x__len)
{
	INT16 i;
	CHAR ch;
	__DUP(x, x__len, CHAR);
	i = 0;
	for (;;) {
		ch = x[__X(i, x__len)];
		(*(*r).fs->Write)(&*r, r__typ, ch);
		i += 1;
		if (ch == 0x00) {
			break;
		}
		if (i == x__len) {
			(*(*r).fs->Write)(&*r, r__typ, 0x00);
			break;
		}
	}
	__DEL(x);
}

void Files_WriteNum (OFS_Rider *r, ADDRESS *r__typ, INT32 x)
{
	while (x < -64 || x > 63) {
		(*(*r).fs->Write)(&*r, r__typ, (CHAR)(__MASK(x, -128) + 128));
		x = __ASHR(x, 7);
	}
	(*(*r).fs->Write)(&*r, r__typ, (CHAR)__MASK(x, -128));
}

void Files_Delete (CHAR *name, ADDRESS name__len, INT16 *res)
{
	__DUP(name, name__len, CHAR);
	OFS_Delete((void*)name, name__len, &*res);
	__DEL(name);
}

void Files_Rename (CHAR *old, ADDRESS old__len, CHAR *new, ADDRESS new__len, INT16 *res)
{
	__DUP(old, old__len, CHAR);
	__DUP(new, new__len, CHAR);
	OFS_Rename((void*)old, old__len, (void*)new, new__len, &*res);
	__DEL(old);
	__DEL(new);
}

void Files_GetName (OFS_File f, CHAR *name, ADDRESS name__len)
{
	OFS_LocalName fname;
	(*f->fs->GetName)(f, (void*)fname, 128);
	OFS_JoinName(f->fs->prefix, 16, fname, 128, (void*)name, name__len);
}


export void *Files__init(void)
{
	__DEFMOD;
	__MODULE_IMPORT(OFS);
	__REGMOD("Files", 0);
/* BEGIN */
	__ENDMOD;
}
