/* voc 2.1.0 [2017/09/06]. Bootstrapping compiler for address size 8, alignment 8. xtaSv */

#define SHORTINT INT8
#define INTEGER  INT16
#define LONGINT  INT32
#define SET      UINT32

#include "SYSTEM.h"
#include "Display.h"
#include "Files.h"
#include "Kernel.h"
#include "Objects.h"

typedef
	struct Fonts_BoxRec {
		INT16 dx, x, y, w, h;
	} Fonts_BoxRec;

typedef
	struct Fonts_CharDesc *Fonts_Char;

typedef
	struct Fonts_CharDesc { /* Objects_ObjDesc */
		INT32 stamp;
		Objects_Object dlink, slink;
		Objects_Library lib;
		INT16 ref;
		Objects_Handler handle;
		INT16 dx, x, y, w, h;
		INT32 pat;
	} Fonts_CharDesc;

typedef
	struct Fonts_FontDesc *Fonts_Font;

typedef
	struct Fonts_FontDesc { /* Objects_LibDesc */
		char _prvt0[4];
		Objects_Index ind;
		char _prvt1[32];
		Objects_Name name;
		Objects_Dictionary dict;
		INT16 maxref;
		char _prvt2[4];
		void (*GenRef)(Objects_Library, INT16*);
		void (*GetObj)(Objects_Library, INT16, Objects_Object*);
		void (*PutObj)(Objects_Library, INT16, Objects_Object);
		void (*FreeObj)(Objects_Library, INT16);
		void (*Load)(Objects_Library);
		void (*Store)(Objects_Library);
		INT8 type;
		INT16 height, minX, maxX, minY, maxY;
	} Fonts_FontDesc;

typedef
	struct Fonts_RunRec {
		INT16 beg, end;
	} Fonts_RunRec;


export CHAR Fonts_FontId;
export Fonts_Font Fonts_Default;
static Fonts_Char Fonts_theChar;
static BOOLEAN Fonts_conv;

export ADDRESS *Fonts_CharDesc__typ;
export ADDRESS *Fonts_FontDesc__typ;
export ADDRESS *Fonts_RunRec__typ;
export ADDRESS *Fonts_BoxRec__typ;

export void Fonts_GetChar (Fonts_Font F, CHAR ch, INT16 *dx, INT16 *x, INT16 *y, INT16 *w, INT16 *h, INT32 *pat);
static void Fonts_GetCharObj (Objects_Library L, INT16 ref, Objects_Object *obj);
static void Fonts_Init (void);
static void Fonts_Internalize (Fonts_Font F, OFS_Rider *R, ADDRESS *R__typ, INT8 type);
static void Fonts_Load (Objects_Library L);
static Objects_Library Fonts_New (void);
static void Fonts_Put1 (INT32 *a, INT16 x);
static void Fonts_Put2 (INT32 *a, INT32 x);
static void Fonts_Put4 (INT32 *a, INT32 x);
static void Fonts_ReadInt (OFS_Rider *R, ADDRESS *R__typ, INT16 *x);
static void Fonts_Substitute (Fonts_Font F);
export Fonts_Font Fonts_This (CHAR *name, ADDRESS name__len);


static void Fonts_Put1 (INT32 *a, INT16 x)
{
	INT8 y;
	y = (INT8)x;
	__PUT(*a, y, INT8);
	*a += 1;
}

static void Fonts_Put2 (INT32 *a, INT32 x)
{
	INT16 y;
	y = (INT16)x;
	__PUT(*a, y, INT16);
	*a = *a + 2;
}

static void Fonts_Put4 (INT32 *a, INT32 x)
{
	__PUT(*a, x, INT32);
	*a = *a + 4;
}

static void Fonts_ReadInt (OFS_Rider *R, ADDRESS *R__typ, INT16 *x)
{
	CHAR c0;
	INT8 s1;
	Files_Read(&*R, R__typ, (void*)&c0);
	Files_Read(&*R, R__typ, (void*)&s1);
	*x = s1;
	*x = __ASHL(*x, 8) + (INT16)c0;
}

static void Fonts_GetCharObj (Objects_Library L, INT16 ref, Objects_Object *obj)
{
}

void Fonts_GetChar (Fonts_Font F, CHAR ch, INT16 *dx, INT16 *x, INT16 *y, INT16 *w, INT16 *h, INT32 *pat)
{
	Objects_Object obj;
	(*F->GetObj)((void*)F, (INT16)ch, &obj);
	if (__ISP(obj, Fonts_CharDesc, 1)) {
		*dx = (*(Fonts_Char*)&obj)->dx;
		*x = (*(Fonts_Char*)&obj)->x;
		*y = (*(Fonts_Char*)&obj)->y;
		*w = (*(Fonts_Char*)&obj)->w;
		*h = (*(Fonts_Char*)&obj)->h;
		*pat = (*(Fonts_Char*)&obj)->pat;
	} else __WITHCHK;
}

static void Fonts_Internalize (Fonts_Font F, OFS_Rider *R, ADDRESS *R__typ, INT8 type)
{
	CHAR ch;
	INT16 NofRuns, NofBoxes, i, k, l, m;
	INT32 NofBytes, RasterBase, A, a;
	Fonts_RunRec run[32];
	Fonts_BoxRec box[256];
	F->type = type;
	Files_Read(&*R, R__typ, (void*)&ch);
	Files_Read(&*R, R__typ, (void*)&ch);
	Fonts_ReadInt(&*R, R__typ, &F->height);
	Fonts_ReadInt(&*R, R__typ, &F->minX);
	Fonts_ReadInt(&*R, R__typ, &F->maxX);
	Fonts_ReadInt(&*R, R__typ, &F->minY);
	Fonts_ReadInt(&*R, R__typ, &F->maxY);
	Fonts_ReadInt(&*R, R__typ, &NofRuns);
	NofBoxes = 0;
	k = 0;
	while (k != NofRuns) {
		Fonts_ReadInt(&*R, R__typ, &run[__X(k, 32)].beg);
		Fonts_ReadInt(&*R, R__typ, &run[__X(k, 32)].end);
		NofBoxes = (NofBoxes + run[__X(k, 32)].end) - run[__X(k, 32)].beg;
		k += 1;
	}
	l = 0;
	while (l != NofBoxes) {
		Fonts_ReadInt(&*R, R__typ, &box[__X(l, 256)].dx);
		Fonts_ReadInt(&*R, R__typ, &box[__X(l, 256)].x);
		Fonts_ReadInt(&*R, R__typ, &box[__X(l, 256)].y);
		Fonts_ReadInt(&*R, R__typ, &box[__X(l, 256)].w);
		Fonts_ReadInt(&*R, R__typ, &box[__X(l, 256)].h);
		l += 1;
	}
	if (type == 0) {
		NofBytes = 1053;
		l = 0;
		while (l != NofBoxes) {
			NofBytes = (NofBytes + 5) + (__ASHR(box[__X(l, 256)].w + 7, 3) * box[__X(l, 256)].h);
			l += 1;
		}
		__SYSNEW(F->ind, NofBytes);
		RasterBase = (INT32)(ADDRESS)F->ind;
		A = RasterBase;
		a = A + 1024;
		Fonts_Put1(&a, 12);
		Fonts_Put1(&a, 0);
		Fonts_Put1(&a, -3);
		Fonts_Put1(&a, 12);
		Fonts_Put1(&a, 12);
		Fonts_Put2(&a, 4095);
		Fonts_Put2(&a, 2049);
		Fonts_Put2(&a, 2049);
		Fonts_Put2(&a, 2049);
		Fonts_Put2(&a, 2049);
		Fonts_Put2(&a, 2049);
		Fonts_Put2(&a, 2049);
		Fonts_Put2(&a, 2049);
		Fonts_Put2(&a, 2049);
		Fonts_Put2(&a, 2049);
		Fonts_Put2(&a, 2049);
		Fonts_Put2(&a, 4095);
		k = 0;
		l = 0;
		m = 0;
		while (k < NofRuns) {
			while (m < run[__X(k, 32)].beg) {
				Fonts_Put4(&A, (RasterBase + 1024) + 3);
				m += 1;
			}
			while (m < run[__X(k, 32)].end) {
				Fonts_Put4(&A, a + 3);
				Fonts_Put1(&a, box[__X(l, 256)].dx);
				Fonts_Put1(&a, box[__X(l, 256)].x);
				Fonts_Put1(&a, box[__X(l, 256)].y);
				Fonts_Put1(&a, box[__X(l, 256)].w);
				Fonts_Put1(&a, box[__X(l, 256)].h);
				i = __ASHR(box[__X(l, 256)].w + 7, 3) * box[__X(l, 256)].h;
				while (i != 0) {
					Files_Read(&*R, R__typ, (void*)&ch);
					Fonts_Put1(&a, (INT16)ch);
					i -= 1;
				}
				l += 1;
				m += 1;
			}
			k += 1;
		}
		while (m < 256) {
			Fonts_Put4(&A, (RasterBase + 1024) + 3);
			m += 1;
		}
	} else {
		__SYSNEW(F->ind, 1029 + NofBoxes * 5);
		RasterBase = (INT32)(ADDRESS)F->ind;
		A = RasterBase;
		a = A + 1024;
		Fonts_Put1(&a, 12);
		Fonts_Put1(&a, 0);
		Fonts_Put1(&a, -3);
		Fonts_Put1(&a, 12);
		Fonts_Put1(&a, 12);
		k = 0;
		l = 0;
		m = 0;
		while (k < NofRuns) {
			while (m < run[__X(k, 32)].beg) {
				Fonts_Put4(&A, (RasterBase + 1024) + 3);
				m += 1;
			}
			while (m < run[__X(k, 32)].end) {
				Fonts_Put4(&A, a + 3);
				Fonts_Put1(&a, box[__X(l, 256)].dx);
				Fonts_Put1(&a, box[__X(l, 256)].x);
				Fonts_Put1(&a, box[__X(l, 256)].y);
				Fonts_Put1(&a, box[__X(l, 256)].w);
				Fonts_Put1(&a, box[__X(l, 256)].h);
				l += 1;
				m += 1;
			}
			k += 1;
		}
		while (m < 256) {
			Fonts_Put4(&A, (RasterBase + 1024) + 3);
			m += 1;
		}
	}
}

static void Fonts_Substitute (Fonts_Font F)
{
	F->type = -1;
	F->height = Fonts_Default->height;
	F->minX = Fonts_Default->minX;
	F->maxX = Fonts_Default->maxX;
	F->minY = Fonts_Default->minY;
	F->maxY = Fonts_Default->maxY;
	F->ind = Fonts_Default->ind;
	Kernel_WriteString((CHAR*)"Missing: ", 10);
	Kernel_WriteString(F->name, 32);
	Kernel_WriteLn();
}

static void Fonts_Load (Objects_Library L)
{
	OFS_File f;
	OFS_Rider R;
	CHAR id;
	INT32 i, j;
	Objects_Name name;
	if (__ISP(L, Fonts_FontDesc, 1)) {
		f = Files_Old((*(Fonts_Font*)&L)->name, 32);
		if (f == NIL) {
			__COPY((*(Fonts_Font*)&L)->name, name, 32);
			name[7] = 0x00;
			if (__STRCMP(name, "Default") == 0) {
				__COPY(Fonts_Default->name, name, 32);
				i = 0;
				while ((name[__X(i, 32)] != 0x00 && (name[__X(i, 32)] < '0' || name[__X(i, 32)] > '9'))) {
					i += 1;
				}
				j = 7;
				while ((*(Fonts_Font*)&L)->name[__X(j, 32)] != 0x00) {
					name[__X(i, 32)] = (*(Fonts_Font*)&L)->name[__X(j, 32)];
					i += 1;
					j += 1;
				}
				name[__X(i, 32)] = 0x00;
				__COPY(name, (*(Fonts_Font*)&L)->name, 32);
				f = Files_Old(name, 32);
			} else {
				name[6] = 0x00;
				if ((Fonts_conv && __STRCMP(name, "Syntax") == 0)) {
					__MOVE(Fonts_Default->name, name, 32);
					j = 0;
					while ((name[__X(j, 32)] != 0x00 && (name[__X(j, 32)] < '0' || name[__X(j, 32)] > '9'))) {
						j += 1;
					}
					i = 6;
					while (((*(Fonts_Font*)&L)->name[__X(i, 32)] >= '0' && (*(Fonts_Font*)&L)->name[__X(i, 32)] <= '9')) {
						name[__X(j, 32)] = (*(Fonts_Font*)&L)->name[__X(i, 32)];
						i += 1;
						j += 1;
					}
					if ((*(Fonts_Font*)&L)->name[__X(i, 32)] == 'm') {
						name[__X(j, 32)] = 'b';
						i += 1;
						j += 1;
					}
					while ((*(Fonts_Font*)&L)->name[__X(i, 32)] != 0x00) {
						name[__X(j, 32)] = (*(Fonts_Font*)&L)->name[__X(i, 32)];
						i += 1;
						j += 1;
					}
					name[__X(j, 32)] = 0x00;
					__COPY(name, (*(Fonts_Font*)&L)->name, 32);
					f = Files_Old(name, 32);
				}
			}
		}
		if (f != NIL) {
			Files_Set(&R, OFS_Rider__typ, f, 0);
			Files_Read(&R, OFS_Rider__typ, (void*)&id);
			if (id == Fonts_FontId) {
				Files_Read(&R, OFS_Rider__typ, (void*)&(*(Fonts_Font*)&L)->type);
				if ((*(Fonts_Font*)&L)->type == 1 || (*(Fonts_Font*)&L)->type == 0) {
					Fonts_Internalize((*(Fonts_Font*)&L), &R, OFS_Rider__typ, (*(Fonts_Font*)&L)->type);
				} else {
					Fonts_Substitute((*(Fonts_Font*)&L));
				}
			} else {
				Fonts_Substitute((*(Fonts_Font*)&L));
			}
		} else {
			__COPY((*(Fonts_Font*)&L)->name, name, 32);
			i = 0;
			while (name[__X(i, 32)] != 0x00) {
				i += 1;
			}
			if ((((((i >= 8 && name[__X(i - 8, 32)] == '.')) && name[__X(i - 7, 32)] == 'M')) && name[__X(i - 6, 32)] == 'd')) {
				name[__X(i - 7, 32)] = 'P';
				name[__X(i - 6, 32)] = 'r';
				f = Files_Old(name, 32);
				if (f != NIL) {
					Files_Set(&R, OFS_Rider__typ, f, 0);
					Files_Read(&R, OFS_Rider__typ, (void*)&id);
					if (id == Fonts_FontId) {
						Files_Read(&R, OFS_Rider__typ, (void*)&(*(Fonts_Font*)&L)->type);
						if ((*(Fonts_Font*)&L)->type == 1 || (*(Fonts_Font*)&L)->type == 0) {
							Fonts_Internalize((*(Fonts_Font*)&L), &R, OFS_Rider__typ, 1);
						} else {
							Fonts_Substitute((*(Fonts_Font*)&L));
						}
					} else {
						Fonts_Substitute((*(Fonts_Font*)&L));
					}
				} else {
					Fonts_Substitute((*(Fonts_Font*)&L));
				}
			} else {
				Fonts_Substitute((*(Fonts_Font*)&L));
			}
		}
	} else __WITHCHK;
}

Fonts_Font Fonts_This (CHAR *name, ADDRESS name__len)
{
	Objects_Library L;
	__DUP(name, name__len, CHAR);
	L = Objects_ThisLibrary(name, name__len);
	if ((L != NIL && __ISP(L, Fonts_FontDesc, 1))) {
		__DEL(name);
		return __GUARDP(L, Fonts_FontDesc, 1);
	} else {
		__DEL(name);
		return NIL;
	}
	__RETCHK;
}

static Objects_Library Fonts_New (void)
{
	Fonts_Font F;
	__NEW(F, Fonts_FontDesc);
	F->Load = Fonts_Load;
	F->GetObj = Fonts_GetCharObj;
	return (void*)F;
}

static void Fonts_Init (void)
{
	CHAR s[8];
	Fonts_FontId = Objects_LibBlockId;
	__NEW(Fonts_theChar, Fonts_CharDesc);
	Kernel_GetConfig((CHAR*)"FontConv", 9, (void*)s, 8);
	Fonts_conv = s[0] != '0';
	Objects_Register((CHAR*)"Fnt", 4, Fonts_New);
}

static void EnumPtrs(void (*P)(void*))
{
	P(Fonts_Default);
	P(Fonts_theChar);
}

__TDESC(Fonts_CharDesc, 1, 3) = {__TDFLDS("CharDesc", 40), {4, 8, 12, -16}};
__TDESC(Fonts_FontDesc, 1, 8) = {__TDFLDS("FontDesc", 120), {0, 4, 8, 28, 32, 36, 72, 80, -36}};
__TDESC(Fonts_RunRec, 1, 0) = {__TDFLDS("RunRec", 4), {-4}};
__TDESC(Fonts_BoxRec, 1, 0) = {__TDFLDS("BoxRec", 10), {-4}};

export void *Fonts__init(void)
{
	__DEFMOD;
	__MODULE_IMPORT(Display);
	__MODULE_IMPORT(Files);
	__MODULE_IMPORT(Kernel);
	__MODULE_IMPORT(Objects);
	__REGMOD("Fonts", EnumPtrs);
	__INITYP(Fonts_CharDesc, Objects_ObjDesc, 1);
	__INITYP(Fonts_FontDesc, Objects_LibDesc, 1);
	__INITYP(Fonts_RunRec, Fonts_RunRec, 0);
	__INITYP(Fonts_BoxRec, Fonts_BoxRec, 0);
/* BEGIN */
	Fonts_Init();
	__ENDMOD;
}
