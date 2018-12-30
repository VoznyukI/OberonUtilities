/* voc 2.1.0 [2017/09/06]. Bootstrapping compiler for address size 8, alignment 8. xtaSv */

#define SHORTINT INT8
#define INTEGER  INT16
#define LONGINT  INT32
#define SET      UINT32

#include "SYSTEM.h"
#include "Display.h"
#include "Files.h"
#include "Fonts.h"
#include "Objects.h"
#include "Reals.h"

typedef
	struct Texts_PieceDesc *Texts_Piece;

typedef
	struct Texts_BufDesc {
		INT32 len;
		Texts_Piece header, last;
	} Texts_BufDesc;

typedef
	Texts_BufDesc *Texts_Buffer;

typedef
	struct Texts_TextDesc *Texts_Text;

typedef
	struct Texts_Finder {
		BOOLEAN eot;
		INT32 pos;
		Texts_Text T;
		Texts_Piece ref;
	} Texts_Finder;

typedef
	struct Texts_PieceDesc {
		OFS_File f;
		INT32 off, len;
		Objects_Object obj;
		Objects_Library lib;
		INT16 ref;
		INT8 col, voff;
		Texts_Piece prev, next;
	} Texts_PieceDesc;

typedef
	struct Texts_Reader {
		Texts_Piece ref;
		Texts_Text T;
		INT32 org, off;
		OFS_Rider R;
		INT32 stamp;
		CHAR buf[64];
		INT32 bufpos, buflen;
		Objects_Library lib;
		INT8 col, voff;
		BOOLEAN eot;
	} Texts_Reader;

typedef
	struct Texts_Scanner { /* Texts_Reader */
		Texts_Piece ref;
		Texts_Text T;
		INT32 org, off;
		OFS_Rider R;
		INT32 stamp;
		CHAR buf[64];
		INT32 bufpos, buflen;
		Objects_Library lib;
		INT8 col, voff;
		BOOLEAN eot;
		CHAR nextCh;
		INT16 line, class;
		INT32 i;
		REAL x;
		LONGREAL y;
		CHAR c;
		INT8 len;
		CHAR s[64];
		Objects_Object obj;
	} Texts_Scanner;

typedef
	struct Texts_TextDesc { /* Objects_ObjDesc */
		INT32 stamp;
		Objects_Object dlink, slink;
		Objects_Library lib;
		INT16 ref;
		Objects_Handler handle;
		INT32 len;
		Objects_Library obs;
		Texts_Piece trailer;
		INT32 org;
		Texts_Piece pce;
	} Texts_TextDesc;

typedef
	struct Texts_UpdateMsg { /* Display_FrameMsg */
		INT32 stamp;
		Objects_Object dlink;
		Display_Frame F;
		INT16 x, y, res;
		Texts_Text text;
		INT32 beg, end, len;
	} Texts_UpdateMsg;

typedef
	struct Texts_Writer {
		OFS_Rider R;
		Texts_Buffer buf;
		Objects_Library lib;
		INT8 col, voff;
	} Texts_Writer;


export CHAR Texts_TextBlockId;
static CHAR Texts_DocBlockId, Texts_NoSpex, Texts_NoSpex2, Texts_TextSpex;
static OFS_File Texts_Wfile;
static OFS_Rider Texts_R;
static Texts_Buffer Texts_DelBuf;
static Objects_Handler Texts_H;
static BOOLEAN Texts_nameChars[256];
static Objects_Library Texts_obs;

export ADDRESS *Texts_PieceDesc__typ;
export ADDRESS *Texts_TextDesc__typ;
export ADDRESS *Texts_UpdateMsg__typ;
export ADDRESS *Texts_Finder__typ;
export ADDRESS *Texts_Reader__typ;
export ADDRESS *Texts_Scanner__typ;
export ADDRESS *Texts_BufDesc__typ;
export ADDRESS *Texts_Writer__typ;
static ADDRESS *ObjsBlockDesc__33__typ;

export void Texts_Append (Texts_Text T, Texts_Buffer B);
export void Texts_ChangeLooks (Texts_Text T, INT32 beg, INT32 end, UINT32 sel, Objects_Library lib, INT8 col, INT8 voff);
export void Texts_Copy (Texts_Buffer SB, Texts_Buffer DB);
export void Texts_Delete (Texts_Text T, INT32 beg, INT32 end);
export void Texts_FindObj (Texts_Finder *F, ADDRESS *F__typ, Objects_Object *obj);
static void Texts_FindPiece (Texts_Text T, INT32 pos, INT32 *org, Texts_Piece *p);
static void Texts_GenNew (Texts_Text T);
export void Texts_Handle (Objects_Object obj, Objects_ObjMsg *M, ADDRESS *M__typ);
static void Texts_InitScan (void);
export void Texts_Insert (Texts_Text T, INT32 pos, Texts_Buffer B);
export void Texts_Load (Texts_Text T, OFS_File f, INT32 pos, INT32 *len);
export void Texts_LoadAscii (Texts_Text T, OFS_File f);
export void Texts_New (void);
export void Texts_Open (Texts_Text T, CHAR *name, ADDRESS name__len);
export void Texts_OpenBuf (Texts_Buffer B);
export void Texts_OpenFinder (Texts_Finder *F, ADDRESS *F__typ, Texts_Text T, INT32 pos);
export void Texts_OpenReader (Texts_Reader *R, ADDRESS *R__typ, Texts_Text T, INT32 pos);
export void Texts_OpenScanner (Texts_Scanner *S, ADDRESS *S__typ, Texts_Text T, INT32 pos);
export void Texts_OpenWriter (Texts_Writer *W, ADDRESS *W__typ);
export INT32 Texts_Pos (Texts_Reader *R, ADDRESS *R__typ);
export void Texts_Read (Texts_Reader *R, ADDRESS *R__typ, CHAR *ch);
static void Texts_ReadDocHeader (OFS_Rider *R, ADDRESS *R__typ, CHAR *ch);
export void Texts_Recall (Texts_Buffer *B);
export void Texts_Replace (Texts_Text T, INT32 beg, INT32 end, Texts_Buffer B);
export void Texts_Save (Texts_Text T, INT32 beg, INT32 end, Texts_Buffer B);
export void Texts_Scan (Texts_Scanner *S, ADDRESS *S__typ);
export void Texts_SetColor (Texts_Writer *W, ADDRESS *W__typ, INT8 col);
export void Texts_SetFont (Texts_Writer *W, ADDRESS *W__typ, Objects_Library fnt);
export void Texts_SetOffset (Texts_Writer *W, ADDRESS *W__typ, INT8 voff);
static void Texts_SplitPiece (Texts_Piece p, INT32 off, Texts_Piece *pr);
export void Texts_Store (Texts_Text T, OFS_File f, INT32 pos, INT32 *len);
static void Texts_SyncPiece (Texts_Text T, Texts_Piece p);
export void Texts_Write (Texts_Writer *W, ADDRESS *W__typ, CHAR ch);
export void Texts_WriteDate (Texts_Writer *W, ADDRESS *W__typ, INT32 t, INT32 d);
export void Texts_WriteHex (Texts_Writer *W, ADDRESS *W__typ, INT32 x);
export void Texts_WriteInt (Texts_Writer *W, ADDRESS *W__typ, INT32 x, INT32 n);
export void Texts_WriteLn (Texts_Writer *W, ADDRESS *W__typ);
export void Texts_WriteLongReal (Texts_Writer *W, ADDRESS *W__typ, LONGREAL x, INT32 n);
export void Texts_WriteLongRealFix (Texts_Writer *W, ADDRESS *W__typ, LONGREAL x, INT32 n, INT32 f, INT32 D);
export void Texts_WriteLongRealHex (Texts_Writer *W, ADDRESS *W__typ, LONGREAL x);
export void Texts_WriteObj (Texts_Writer *W, ADDRESS *W__typ, Objects_Object obj);
export void Texts_WriteReal (Texts_Writer *W, ADDRESS *W__typ, REAL x, INT32 n);
export void Texts_WriteRealFix (Texts_Writer *W, ADDRESS *W__typ, REAL x, INT32 n, INT32 f, INT32 E);
export void Texts_WriteRealHex (Texts_Writer *W, ADDRESS *W__typ, REAL x);
export void Texts_WriteSet (Texts_Writer *W, ADDRESS *W__typ, UINT32 s);
export void Texts_WriteString (Texts_Writer *W, ADDRESS *W__typ, CHAR *s, ADDRESS s__len);


void Texts_LoadAscii (Texts_Text T, OFS_File f)
{
	Texts_Piece Q, q;
	INT32 len;
	len = Files_Length(f);
	__NEW(Q, Texts_PieceDesc);
	Q->f = Texts_Wfile;
	Q->off = 0;
	Q->len = 1;
	Q->ref = (-32767-1);
	Q->lib = NIL;
	Q->col = 127;
	Q->voff = 0;
	__NEW(q, Texts_PieceDesc);
	q->f = f;
	q->off = 0;
	q->len = len;
	q->ref = (-32767-1);
	q->lib = (Objects_Library)Fonts_Default;
	q->col = 15;
	q->voff = 0;
	Q->next = q;
	q->prev = Q;
	q->next = Q;
	Q->prev = q;
	T->handle = Texts_H;
	T->obs = NIL;
	T->trailer = Q;
	T->len = len;
	T->org = -1;
	T->pce = T->trailer;
}

static void Texts_ReadDocHeader (OFS_Rider *R, ADDRESS *R__typ, CHAR *ch)
{
	INT32 len;
	INT16 x, y, w, h;
	CHAR name[32];
	Files_Read(&*R, R__typ, (void*)&*ch);
	Files_ReadString(&*R, R__typ, (void*)name, 32);
	Files_ReadInt(&*R, R__typ, &x);
	Files_ReadInt(&*R, R__typ, &y);
	Files_ReadInt(&*R, R__typ, &w);
	Files_ReadInt(&*R, R__typ, &h);
	Files_Read(&*R, R__typ, (void*)&*ch);
	if (*ch == 0xf7) {
		Files_Read(&*R, R__typ, (void*)&*ch);
		if (*ch == 0x08) {
			Files_ReadLInt(&*R, R__typ, &len);
			Files_Set(&*R, R__typ, Files_Base(&*R, R__typ), Files_Pos(&*R, R__typ) + len);
			Files_Read(&*R, R__typ, (void*)&*ch);
		}
	}
}

void Texts_Load (Texts_Text T, OFS_File f, INT32 pos, INT32 *len)
{
	OFS_Rider R, S;
	Texts_Piece Q, q, p;
	INT32 hlen, tlen, flen, off;
	INT8 N, lib;
	CHAR type, ref, tag;
	CHAR LName[32];
	Objects_Library Dict[32];
	INT16 i;
	__NEW(Q, Texts_PieceDesc);
	Q->f = Texts_Wfile;
	Q->off = 0;
	Q->len = 1;
	Q->ref = (-32767-1);
	Q->lib = NIL;
	Q->col = 127;
	Q->voff = 0;
	p = Q;
	Files_Set(&R, OFS_Rider__typ, f, pos);
	Files_Read(&R, OFS_Rider__typ, (void*)&type);
	Files_ReadLInt(&R, OFS_Rider__typ, &hlen);
	Files_Set(&S, OFS_Rider__typ, f, ((pos - 1) + hlen) - 4);
	Files_ReadLInt(&S, OFS_Rider__typ, &tlen);
	if (type == Texts_TextSpex || type == 0xf0) {
		T->obs = NIL;
		flen = 0;
	} else {
		__NEW(T->obs, Objects_LibDesc);
		Objects_OpenLibrary(T->obs);
		Files_Set(&S, OFS_Rider__typ, f, ((pos - 1) + hlen) + tlen);
		Files_Read(&S, OFS_Rider__typ, (void*)&tag);
		if (tag == Objects_LibBlockId) {
			Objects_LoadLibrary(T->obs, f, (((pos - 1) + hlen) + tlen) + 1, &flen);
		}
		flen += 1;
	}
	Dict[0] = T->obs;
	N = 1;
	off = (pos - 1) + hlen;
	while (Files_Pos(&R, OFS_Rider__typ) < ((pos - 1) + hlen) - 5) {
		Files_Read(&R, OFS_Rider__typ, (void*)&lib);
		if (lib == N) {
			Files_ReadString(&R, OFS_Rider__typ, (void*)LName, 32);
			Dict[__X(N, 32)] = Objects_ThisLibrary(LName, 32);
			N += 1;
		}
		__NEW(q, Texts_PieceDesc);
		q->lib = Dict[__X(lib, 32)];
		q->obj = NIL;
		if (!__ISP(q->lib, Fonts_FontDesc, 1)) {
			Files_Set(&S, OFS_Rider__typ, f, off);
			Files_Read(&S, OFS_Rider__typ, (void*)&ref);
			q->ref = (INT16)ref;
		} else {
			q->ref = (-32767-1);
		}
		Files_Read(&R, OFS_Rider__typ, (void*)&q->col);
		Files_Read(&R, OFS_Rider__typ, (void*)&q->voff);
		Files_ReadLInt(&R, OFS_Rider__typ, &q->len);
		if (q->len < 0) {
			Texts_LoadAscii(T, f);
			return;
		}
		q->f = f;
		q->off = off;
		off = off + q->len;
		p->next = q;
		q->prev = p;
		p = q;
	}
	p->next = Q;
	Q->prev = p;
	T->handle = Texts_H;
	T->trailer = Q;
	T->len = tlen;
	T->org = -1;
	T->pce = T->trailer;
	if (type == Texts_NoSpex2) {
		i = 0;
		while (i <= 31) {
			Dict[__X(i, 32)] = NIL;
			i += 1;
		}
		Files_Set(&R, OFS_Rider__typ, f, (((pos - 1) + hlen) + tlen) + flen);
		p = T->trailer->next;
		while (p != T->trailer) {
			if (p->lib == T->obs) {
				Files_ReadInt(&R, OFS_Rider__typ, &i);
				flen += 2;
				if (Dict[__X(__ASHR(i, 8), 32)] == NIL) {
					__NEW(Dict[__X(__ASHR(i, 8), 32)], Objects_LibDesc);
					Objects_OpenLibrary(Dict[__X(__ASHR(i, 8), 32)]);
				}
				p->obj = NIL;
				p->ref = i;
				p->lib = Dict[__X(__ASHR(i, 8), 32)];
			}
			p = p->next;
		}
	}
	*len = ((hlen - 1) + tlen) + flen;
}

static void Texts_SyncPiece (Texts_Text T, Texts_Piece p)
{
	OFS_Rider R;
	CHAR ch;
	if ((((p->ref >= 0 && p->obj == NIL)) && !__ISP(p->lib, Fonts_FontDesc, 1))) {
		(*T->obs->GetObj)(T->obs, p->ref, &p->obj);
		Files_Set(&R, OFS_Rider__typ, p->f, p->off);
		Files_Read(&R, OFS_Rider__typ, (void*)&ch);
		(*p->lib->PutObj)(p->lib, (INT16)ch, p->obj);
	}
}

typedef
	struct ObjsBlockDesc__33 *ObjsBlock__32;

typedef
	struct ObjsBlockDesc__33 {
		Objects_Object objs[256];
		ObjsBlock__32 next;
	} ObjsBlockDesc__33;

void Texts_Store (Texts_Text T, OFS_File f, INT32 pos, INT32 *len)
{
	Texts_Piece p, q;
	OFS_Rider R, W;
	INT32 hlen, flen, rlen, m;
	INT16 id, i;
	INT8 N, n;
	CHAR type, ch;
	Objects_Object obj;
	Objects_BindMsg M;
	Objects_Name Dict[32];
	ObjsBlock__32 allObjs, curObjs, objs;
	Files_Set(&W, OFS_Rider__typ, f, pos);
	Files_Write(&W, OFS_Rider__typ, Texts_TextBlockId);
	Files_Write(&W, OFS_Rider__typ, 0x00);
	Files_WriteLInt(&W, OFS_Rider__typ, 0);
	Dict[0][0] = 0x00;
	N = 1;
	p = T->trailer->next;
	while (p != T->trailer) {
		rlen = p->len;
		q = p->next;
		if (__ISP(p->lib, Fonts_FontDesc, 1)) {
			while ((((((q != T->trailer && q->lib == p->lib)) && q->col == p->col)) && q->voff == p->voff)) {
				rlen = rlen + q->len;
				q = q->next;
			}
		}
		__MOVE(p->lib->name, Dict[__X(N, 32)], 32);
		n = 0;
		while (__STRCMP(Dict[__X(n, 32)], p->lib->name) != 0) {
			n += 1;
		}
		Files_Write(&W, OFS_Rider__typ, n);
		if (n == N) {
			Files_WriteString(&W, OFS_Rider__typ, p->lib->name, 32);
			N += 1;
		}
		Files_Write(&W, OFS_Rider__typ, p->col);
		Files_Write(&W, OFS_Rider__typ, p->voff);
		Files_WriteLInt(&W, OFS_Rider__typ, rlen);
		p = q;
	}
	Files_Write(&W, OFS_Rider__typ, 0x00);
	Files_WriteLInt(&W, OFS_Rider__typ, T->len);
	__NEW(allObjs, ObjsBlockDesc__33);
	allObjs->next = NIL;
	curObjs = allObjs;
	hlen = Files_Pos(&W, OFS_Rider__typ) - pos;
	id = 0;
	p = T->trailer->next;
	while (p != T->trailer) {
		Files_Set(&R, OFS_Rider__typ, p->f, p->off);
		m = p->len;
		while (m != 0) {
			Files_Read(&R, OFS_Rider__typ, (void*)&ch);
			if (p->lib->name[0] == 0x00) {
				Texts_SyncPiece(T, p);
				(*p->lib->GetObj)(p->lib, (INT16)ch, &obj);
				p->obj = obj;
				curObjs->objs[__X(__MASK(id, -256), 256)] = obj;
				i = 0;
				objs = allObjs;
				while (objs->objs[__X(__MASK(i, -256), 256)] != obj) {
					i += 1;
					if (__MASK(i, -256) == 0) {
						objs = objs->next;
					}
				}
				if (i == id) {
					id += 1;
					if (__MASK(id, -256) == 0) {
						__NEW(curObjs->next, ObjsBlockDesc__33);
						p->ref = id;
						curObjs = curObjs->next;
						curObjs->next = NIL;
					}
				}
				ch = (CHAR)i;
			}
			Files_Write(&W, OFS_Rider__typ, ch);
			m -= 1;
		}
		p = p->next;
	}
	if (id > 0) {
		if (id > 255) {
			type = Texts_NoSpex2;
		} else {
			type = Texts_NoSpex;
		}
		__NEW(T->obs, Objects_LibDesc);
		Objects_OpenLibrary(T->obs);
		i = 0;
		objs = allObjs;
		do {
			(*T->obs->PutObj)(T->obs, i, objs->objs[__X(__MASK(i, -256), 256)]);
			i += 1;
			if (__MASK(i, -256) == 0) {
				objs = objs->next;
			}
		} while (!(i == id));
		M.lib = T->obs;
		i = 0;
		objs = allObjs;
		do {
			(*objs->objs[__X(__MASK(i, -256), 256)]->handle)(objs->objs[__X(__MASK(i, -256), 256)], (void*)&M, Objects_BindMsg__typ);
			i += 1;
			if (__MASK(i, -256) == 0) {
				objs = objs->next;
			}
		} while (!(i == id));
		Objects_StoreLibrary(T->obs, f, (pos + hlen) + T->len, &flen);
		if (type == Texts_NoSpex2) {
			Files_Set(&W, OFS_Rider__typ, f, ((pos + hlen) + T->len) + flen);
			p = T->trailer->next;
			while (p != T->trailer) {
				if (p->lib->name[0] == 0x00) {
					i = 0;
					objs = allObjs;
					while (objs->objs[__X(__MASK(i, -256), 256)] != p->obj) {
						i += 1;
						if (__MASK(i, -256) == 0) {
							objs = objs->next;
						}
					}
					Files_WriteInt(&W, OFS_Rider__typ, i);
					flen += 2;
				}
				p = p->next;
			}
		}
	} else {
		type = Texts_TextSpex;
		flen = 0;
	}
	Files_Set(&W, OFS_Rider__typ, f, pos + 1);
	Files_Write(&W, OFS_Rider__typ, type);
	Files_WriteLInt(&W, OFS_Rider__typ, hlen);
	*len = (hlen + T->len) + flen;
}

static void Texts_GenNew (Texts_Text T)
{
	Texts_Piece Q;
	__NEW(Q, Texts_PieceDesc);
	Q->f = Texts_Wfile;
	Q->off = 0;
	Q->len = 1;
	Q->ref = (-32767-1);
	Q->lib = NIL;
	Q->col = 127;
	Q->voff = 0;
	Q->next = Q;
	Q->prev = Q;
	T->handle = Texts_H;
	T->obs = NIL;
	T->trailer = Q;
	T->len = 0;
	T->org = -1;
	T->pce = T->trailer;
}

void Texts_Open (Texts_Text T, CHAR *name, ADDRESS name__len)
{
	OFS_File f;
	OFS_Rider R;
	INT32 len;
	CHAR ch;
	__DUP(name, name__len, CHAR);
	Texts_obs = NIL;
	f = Files_Old(name, name__len);
	if (f != NIL) {
		Files_Set(&R, OFS_Rider__typ, f, 0);
		Files_Read(&R, OFS_Rider__typ, (void*)&ch);
		if (ch == Texts_DocBlockId) {
			Texts_ReadDocHeader(&R, OFS_Rider__typ, &ch);
		}
		if (ch == Texts_TextBlockId || ch == 0x01) {
			Texts_Load(T, f, Files_Pos(&R, OFS_Rider__typ), &len);
		} else {
			Texts_LoadAscii(T, f);
		}
	} else {
		Texts_GenNew(T);
	}
	__DEL(name);
}

void Texts_New (void)
{
	Texts_Text T;
	__NEW(T, Texts_TextDesc);
	T->handle = Texts_H;
	Texts_GenNew(T);
	Objects_NewObj = (Objects_Object)T;
}

static void Texts_FindPiece (Texts_Text T, INT32 pos, INT32 *org, Texts_Piece *p)
{
	INT32 n;
	if (pos < T->org) {
		T->org = -1;
		T->pce = T->trailer;
	}
	*org = T->org;
	*p = T->pce;
	n = 0;
	while (pos >= *org + (*p)->len) {
		*org = *org + (*p)->len;
		*p = (*p)->next;
		n += 1;
	}
	if (n > 50) {
		T->org = *org;
		T->pce = *p;
	}
}

static void Texts_SplitPiece (Texts_Piece p, INT32 off, Texts_Piece *pr)
{
	Texts_Piece q;
	if (off > 0) {
		__NEW(q, Texts_PieceDesc);
		q->ref = (-32767-1);
		q->lib = p->lib;
		q->col = p->col;
		q->voff = p->voff;
		q->len = p->len - off;
		q->f = p->f;
		q->off = p->off + off;
		p->len = off;
		q->next = p->next;
		p->next = q;
		q->prev = p;
		q->next->prev = q;
		*pr = q;
	} else {
		*pr = p;
	}
}

void Texts_Insert (Texts_Text T, INT32 pos, Texts_Buffer B)
{
	Texts_Piece pl, pr, p, qb, qe;
	INT32 org;
	Texts_UpdateMsg M;
	Texts_FindPiece(T, pos, &org, &p);
	Texts_SplitPiece(p, pos - org, &pr);
	if (T->org >= org) {
		T->org = org - p->prev->len;
		T->pce = p->prev;
	}
	pl = pr->prev;
	qb = B->header->next;
	if ((((((((((((qb != NIL && qb->f == pl->f)) && qb->off == pl->off + pl->len)) && __ISP(pl->lib, Fonts_FontDesc, 1))) && pl->lib == qb->lib)) && pl->col == qb->col)) && pl->voff == qb->voff)) {
		pl->len = pl->len + qb->len;
		qb = qb->next;
	}
	if (qb != NIL) {
		qe = B->last;
		qb->prev = pl;
		pl->next = qb;
		qe->next = pr;
		pr->prev = qe;
	}
	T->len = T->len + B->len;
	M.text = T;
	M.F = NIL;
	M.beg = pos;
	M.end = pos;
	M.len = B->len;
	B->last = B->header;
	B->last->next = NIL;
	B->len = 0;
	T->stamp = M.stamp;
}

void Texts_Append (Texts_Text T, Texts_Buffer B)
{
	Texts_Insert(T, T->len, B);
}

void Texts_Delete (Texts_Text T, INT32 beg, INT32 end)
{
	Texts_Piece pb, pe, pbr, per;
	INT32 orgb, orge;
	Texts_UpdateMsg M;
	if (beg < end) {
		Texts_FindPiece(T, beg, &orgb, &pb);
		Texts_SplitPiece(pb, beg - orgb, &pbr);
		Texts_FindPiece(T, end, &orge, &pe);
		Texts_SplitPiece(pe, end - orge, &per);
		if (T->org >= orgb) {
			T->org = orgb - pb->prev->len;
			T->pce = pb->prev;
		}
		Texts_DelBuf->header->next = pbr;
		Texts_DelBuf->last = per->prev;
		Texts_DelBuf->last->next = NIL;
		Texts_DelBuf->len = end - beg;
		per->prev = pbr->prev;
		pbr->prev->next = per;
		T->len = (T->len - end) + beg;
		M.text = T;
		M.F = NIL;
		M.beg = beg;
		M.end = end;
		M.len = 0;
		T->stamp = M.stamp;
	}
}

void Texts_Replace (Texts_Text T, INT32 beg, INT32 end, Texts_Buffer B)
{
	Texts_UpdateMsg M;
	Texts_Piece pb, pe, pbr, per, pl, qb, qe;
	INT32 orgb, orge;
	if (beg < end) {
		Texts_FindPiece(T, beg, &orgb, &pb);
		Texts_SplitPiece(pb, beg - orgb, &pbr);
		Texts_FindPiece(T, end, &orge, &pe);
		Texts_SplitPiece(pe, end - orge, &per);
		if (T->org >= orgb) {
			T->org = orgb - pb->prev->len;
			T->pce = pb->prev;
		}
		Texts_DelBuf->header->next = pbr;
		Texts_DelBuf->last = per->prev;
		Texts_DelBuf->last->next = NIL;
		Texts_DelBuf->len = end - beg;
		per->prev = pbr->prev;
		pbr->prev->next = per;
		pl = pbr->prev;
		qb = B->header->next;
		if ((((((((((((qb != NIL && qb->f == pl->f)) && qb->off == pl->off + pl->len)) && __ISP(pl->lib, Fonts_FontDesc, 1))) && pl->lib == qb->lib)) && pl->col == qb->col)) && pl->voff == qb->voff)) {
			pl->len = pl->len + qb->len;
			qb = qb->next;
		}
		if (qb != NIL) {
			qe = B->last;
			qb->prev = pl;
			pl->next = qb;
			qe->next = per;
			per->prev = qe;
		}
		T->len = ((T->len - end) + beg) + B->len;
		M.text = T;
		M.F = NIL;
		M.beg = beg;
		M.end = end;
		M.len = B->len;
		B->last = B->header;
		B->last->next = NIL;
		B->len = 0;
		T->stamp = M.stamp;
	}
}

void Texts_ChangeLooks (Texts_Text T, INT32 beg, INT32 end, UINT32 sel, Objects_Library lib, INT8 col, INT8 voff)
{
	Texts_Piece pb, pe, p;
	INT32 org;
	Texts_UpdateMsg M;
	Objects_AttrMsg A;
	if (beg < end) {
		Texts_FindPiece(T, beg, &org, &p);
		Texts_SplitPiece(p, beg - org, &pb);
		Texts_FindPiece(T, end, &org, &p);
		Texts_SplitPiece(p, end - org, &pe);
		p = pb;
		do {
			if ((__IN(0, sel, 32) && __ISP(p->lib, Fonts_FontDesc, 1))) {
				p->lib = lib;
			} else if (!__ISP(p->lib, Fonts_FontDesc, 1)) {
				Texts_SyncPiece(T, p);
				if ((p->obj != NIL && p->obj->handle != NIL)) {
					if (__IN(1, sel, 32)) {
						A.id = 1;
						__MOVE("Color", A.name, 6);
						A.class = 0;
						A.res = -1;
						(*p->obj->handle)(p->obj, (void*)&A, Objects_AttrMsg__typ);
						if (A.res == 0) {
							A.id = 2;
							A.class = 3;
							A.i = __MASK((INT16)col, -256);
							(*p->obj->handle)(p->obj, (void*)&A, Objects_AttrMsg__typ);
						}
					}
					if ((((__IN(0, sel, 32) && lib != NIL)) && __ISP(lib, Fonts_FontDesc, 1))) {
						A.id = 1;
						__MOVE("Font", A.name, 5);
						A.class = 0;
						A.res = -1;
						(*p->obj->handle)(p->obj, (void*)&A, Objects_AttrMsg__typ);
						if (A.res == 0) {
							A.id = 2;
							A.class = 2;
							__COPY(__GUARDP(lib, Fonts_FontDesc, 1)->name, A.s, 64);
							(*p->obj->handle)(p->obj, (void*)&A, Objects_AttrMsg__typ);
						}
					}
				}
			}
			if (__IN(1, sel, 32)) {
				p->col = col;
			}
			if (__IN(2, sel, 32)) {
				p->voff = voff;
			}
			p = p->next;
		} while (!(p == pe));
		M.text = T;
		M.F = NIL;
		M.beg = beg;
		M.end = end;
		M.len = end - beg;
		T->stamp = M.stamp;
	}
}

void Texts_OpenBuf (Texts_Buffer B)
{
	__NEW(B->header, Texts_PieceDesc);
	B->header->ref = (-32767-1);
	B->last = B->header;
	B->len = 0;
}

void Texts_Save (Texts_Text T, INT32 beg, INT32 end, Texts_Buffer B)
{
	Texts_Piece p, q, qb, qe;
	INT32 org;
	if (beg < end) {
		Texts_FindPiece(T, beg, &org, &p);
		Texts_SyncPiece(T, p);
		__NEW(qb, Texts_PieceDesc);
		__GUARDEQP(qb, Texts_PieceDesc) = *p;
		qb->ref = (-32767-1);
		qb->len = qb->len - (beg - org);
		qb->off = qb->off + (beg - org);
		qe = qb;
		while (end > org + p->len) {
			org = org + p->len;
			p = p->next;
			Texts_SyncPiece(T, p);
			__NEW(q, Texts_PieceDesc);
			__GUARDEQP(q, Texts_PieceDesc) = *p;
			q->ref = (-32767-1);
			qe->next = q;
			q->prev = qe;
			qe = q;
		}
		qe->next = NIL;
		qe->len = qe->len - ((org + p->len) - end);
		B->last->next = qb;
		qb->prev = B->last;
		B->last = qe;
		B->len = B->len + (end - beg);
	}
}

void Texts_Copy (Texts_Buffer SB, Texts_Buffer DB)
{
	Texts_Piece Q, q, p;
	p = SB->header;
	Q = DB->last;
	while (p != SB->last) {
		p = p->next;
		__NEW(q, Texts_PieceDesc);
		q->ref = (-32767-1);
		__GUARDEQP(q, Texts_PieceDesc) = *p;
		Q->next = q;
		q->prev = Q;
		Q = q;
	}
	DB->last = Q;
	DB->len = DB->len + SB->len;
}

void Texts_Recall (Texts_Buffer *B)
{
	Texts_Copy(Texts_DelBuf, *B);
}

void Texts_Handle (Objects_Object obj, Objects_ObjMsg *M, ADDRESS *M__typ)
{
	Texts_Text T;
	Texts_Buffer B;
	INT32 len;
	INT16 id;
	CHAR ch;
	if (__ISP(obj, Texts_TextDesc, 1)) {
		if (__IS(M__typ, Objects_AttrMsg, 1)) {
			if (__IS(M__typ, Objects_AttrMsg, 1)) {
				Objects_AttrMsg *M__ = (void*)M;
				if (__STRCMP((*M__).name, "Gen") == 0) {
					(*M__).class = 2;
					__MOVE("Texts.New", (*M__).s, 10);
					(*M__).res = 0;
				}
			} else __WITHCHK;
		} else if (__IS(M__typ, Objects_CopyMsg, 1)) {
			if (__IS(M__typ, Objects_CopyMsg, 1)) {
				Objects_CopyMsg *M__ = (void*)M;
				__NEW(B, Texts_BufDesc);
				Texts_OpenBuf(B);
				Texts_Save((*(Texts_Text*)&obj), 0, (*(Texts_Text*)&obj)->len, B);
				__NEW(T, Texts_TextDesc);
				T->handle = (*(Texts_Text*)&obj)->handle;
				Texts_GenNew(T);
				Texts_Insert(T, 0, B);
				(*M__).obj = (Objects_Object)T;
			} else __WITHCHK;
		} else if (__IS(M__typ, Objects_BindMsg, 1)) {
			if (__IS(M__typ, Objects_BindMsg, 1)) {
				Objects_BindMsg *M__ = (void*)M;
				if ((*(Texts_Text*)&obj)->lib == NIL || ((*(Texts_Text*)&obj)->lib->name[0] == 0x00 && (*(Texts_Text*)&obj)->lib != (*M__).lib)) {
					(*(*M__).lib->GenRef)((*M__).lib, &id);
					(*(*M__).lib->PutObj)((*M__).lib, id, (void*)(*(Texts_Text*)&obj));
				}
			} else __WITHCHK;
		} else if (__IS(M__typ, Objects_FileMsg, 1)) {
			if (__IS(M__typ, Objects_FileMsg, 1)) {
				Objects_FileMsg *M__ = (void*)M;
				if ((*M__).id == 0) {
					Files_Read(&(*M__).R, OFS_Rider__typ, (void*)&ch);
					if (ch == Texts_DocBlockId) {
						Texts_ReadDocHeader(&Texts_R, OFS_Rider__typ, &ch);
					}
					if (ch == Texts_TextBlockId || ch == 0x01) {
						Texts_Load((*(Texts_Text*)&obj), Files_Base(&(*M__).R, OFS_Rider__typ), Files_Pos(&(*M__).R, OFS_Rider__typ), &len);
						Files_Set(&(*M__).R, OFS_Rider__typ, Files_Base(&(*M__).R, OFS_Rider__typ), Files_Pos(&(*M__).R, OFS_Rider__typ) + len);
					}
				} else {
					Texts_Store((*(Texts_Text*)&obj), Files_Base(&(*M__).R, OFS_Rider__typ), Files_Pos(&(*M__).R, OFS_Rider__typ), &len);
					Files_Set(&(*M__).R, OFS_Rider__typ, Files_Base(&(*M__).R, OFS_Rider__typ), Files_Pos(&(*M__).R, OFS_Rider__typ) + len);
				}
			} else __WITHCHK;
		}
	} else __WITHCHK;
}

void Texts_OpenFinder (Texts_Finder *F, ADDRESS *F__typ, Texts_Text T, INT32 pos)
{
	Texts_Piece p;
	INT32 org;
	Texts_FindPiece(T, pos, &org, &p);
	(*F).T = T;
	while ((p->f != Texts_Wfile && __ISP(p->lib, Fonts_FontDesc, 1))) {
		org = org + p->len;
		p = p->next;
	}
	(*F).pos = org;
	(*F).ref = p;
	(*F).eot = 0;
}

void Texts_FindObj (Texts_Finder *F, ADDRESS *F__typ, Objects_Object *obj)
{
	Texts_Piece p;
	INT32 org;
	*obj = (*F).ref->obj;
	if (*obj == NIL) {
		Texts_SyncPiece((*F).T, (*F).ref);
		*obj = (*F).ref->obj;
	}
	if ((*F).ref->f == Texts_Wfile) {
		(*F).eot = 1;
	}
	org = (*F).pos;
	p = (*F).ref;
	do {
		org = org + p->len;
		p = p->next;
	} while (!(p->f == Texts_Wfile || !__ISP(p->lib, Fonts_FontDesc, 1)));
	(*F).pos = org;
	(*F).ref = p;
}

void Texts_OpenReader (Texts_Reader *R, ADDRESS *R__typ, Texts_Text T, INT32 pos)
{
	Texts_Piece p;
	INT32 org;
	Texts_FindPiece(T, pos, &org, &p);
	(*R).T = T;
	(*R).lib = NIL;
	(*R).stamp = T->stamp;
	(*R).bufpos = 0;
	(*R).buflen = 0;
	(*R).ref = p;
	(*R).org = org;
	(*R).off = pos - org;
	(*R).lib = p->lib;
	(*R).col = p->col;
	(*R).voff = p->voff;
	if (p->ref >= 0) {
		Texts_SyncPiece(T, p);
	}
	Files_Set(&(*R).R, OFS_Rider__typ, p->f, p->off + (*R).off);
	(*R).eot = p->f == Texts_Wfile;
}

void Texts_Read (Texts_Reader *R, ADDRESS *R__typ, CHAR *ch)
{
	Texts_Piece ref;
	if ((*R).stamp != (*R).T->stamp || (*R).bufpos >= (*R).buflen) {
		if ((*R).stamp == (*R).T->stamp) {
			ref = (*R).ref;
			(*R).bufpos = 0;
			(*R).buflen = ref->len - (*R).off;
			if ((*R).buflen <= 0) {
				(*R).org = (*R).org + ref->len;
				(*R).off = 0;
				ref = ref->next;
				(*R).ref = ref;
				(*R).lib = ref->lib;
				(*R).col = ref->col;
				(*R).voff = ref->voff;
				if (ref->ref >= 0) {
					Texts_SyncPiece((*R).T, ref);
				}
				Files_Set(&(*R).R, OFS_Rider__typ, ref->f, ref->off);
				(*R).buflen = ref->len;
				if (ref->f == Texts_Wfile) {
					(*R).eot = 1;
				}
			}
			if ((*R).buflen > 64) {
				(*R).buflen = 64;
			}
			Files_ReadBytes(&(*R).R, OFS_Rider__typ, (void*)(*R).buf, 64, (*R).buflen);
		} else {
			Texts_OpenReader(&*R, R__typ, (*R).T, (*R).org + (*R).off);
			Texts_Read(&*R, R__typ, &*ch);
			return;
		}
	}
	*ch = (*R).buf[__X((*R).bufpos, 64)];
	(*R).bufpos += 1;
	(*R).off += 1;
}

INT32 Texts_Pos (Texts_Reader *R, ADDRESS *R__typ)
{
	return (*R).org + (*R).off;
}

void Texts_OpenScanner (Texts_Scanner *S, ADDRESS *S__typ, Texts_Text T, INT32 pos)
{
	Texts_OpenReader((void*)&*S, S__typ, T, pos);
	(*S).line = 0;
	(*S).class = 0;
	Texts_Read((void*)&*S, S__typ, &(*S).nextCh);
}

void Texts_Scan (Texts_Scanner *S, ADDRESS *S__typ)
{
	CHAR ch, E;
	BOOLEAN neg, negE, hex, sign;
	INT32 i, j, h, e, k, k1, k2, k3;
	LONGREAL y;
	CHAR d[32];
	ch = (*S).nextCh;
	i = 0;
	for (;;) {
		if ((*S).lib == NIL || !__ISP((*S).lib, Fonts_FontDesc, 1)) {
			break;
		} else if (ch == 0x0d) {
			(*S).line += 1;
		} else if ((((ch != ' ' && ch != 0x09)) && ch != 0x0a)) {
			break;
		}
		Texts_Read((void*)&*S, S__typ, &ch);
	}
	if ((*S).lib == NIL) {
		(*S).class = 0;
		(*S).eot = 1;
		Texts_Read((void*)&*S, S__typ, &ch);
	} else if (!__ISP((*S).lib, Fonts_FontDesc, 1)) {
		(*S).class = 7;
		(*(*S).lib->GetObj)((*S).lib, (INT16)ch, &(*S).obj);
		Texts_Read((void*)&*S, S__typ, &ch);
	} else if ((('A' <= __CAP(ch) && __CAP(ch) <= 'Z') || ch == '.') || ch == '/') {
		do {
			(*S).s[__X(i, 64)] = ch;
			i += 1;
			Texts_Read((void*)&*S, S__typ, &ch);
		} while (!((!Texts_nameChars[__X((INT16)ch, 256)] || !__ISP((*S).lib, Fonts_FontDesc, 1)) || i == 63));
		(*S).s[__X(i, 64)] = 0x00;
		if ((i == 1 && (__CAP((*S).s[0]) < 'A' || __CAP((*S).s[0]) > 'Z'))) {
			(*S).c = (*S).s[0];
			(*S).class = 6;
		} else {
			(*S).len = (INT8)((INT16)i);
			(*S).class = 1;
		}
	} else if (ch == '"') {
		Texts_Read((void*)&*S, S__typ, &ch);
		while ((((((ch != '"' && ch >= ' ')) && __ISP((*S).lib, Fonts_FontDesc, 1))) && i != 63)) {
			(*S).s[__X(i, 64)] = ch;
			i += 1;
			Texts_Read((void*)&*S, S__typ, &ch);
		}
		while ((((ch != '"' && ch >= ' ')) && __ISP((*S).lib, Fonts_FontDesc, 1))) {
			Texts_Read((void*)&*S, S__typ, &ch);
		}
		(*S).s[__X(i, 64)] = 0x00;
		(*S).len = (INT8)((INT16)i);
		Texts_Read((void*)&*S, S__typ, &ch);
		(*S).class = 2;
	} else {
		if (ch == '-') {
			sign = 1;
			neg = 1;
			Texts_Read((void*)&*S, S__typ, &ch);
		} else if (ch == '+') {
			sign = 1;
			neg = 0;
			Texts_Read((void*)&*S, S__typ, &ch);
		} else {
			sign = 0;
			neg = 0;
		}
		if (((('0' <= ch && ch <= '9')) && __ISP((*S).lib, Fonts_FontDesc, 1))) {
			hex = 0;
			j = 0;
			for (;;) {
				d[__X(i, 32)] = ch;
				i += 1;
				Texts_Read((void*)&*S, S__typ, &ch);
				if ((ch < '0' || !__ISP((*S).lib, Fonts_FontDesc, 1)) || i >= 32) {
					break;
				}
				if ('9' < ch) {
					if (('A' <= ch && ch <= 'F')) {
						hex = 1;
						ch = (CHAR)((INT16)ch - 7);
					} else if (('a' <= ch && ch <= 'f')) {
						hex = 1;
						ch = (CHAR)((INT16)ch - 39);
					} else {
						break;
					}
				}
			}
			if ((ch == 'H' && __ISP((*S).lib, Fonts_FontDesc, 1))) {
				Texts_Read((void*)&*S, S__typ, &ch);
				(*S).class = 3;
				if (i - j > 8) {
					j = i - 8;
				}
				k = (INT16)d[__X(j, 32)] - 48;
				j += 1;
				if ((i - j == 7 && k >= 8)) {
					k -= 16;
				}
				while (j < i) {
					k = __ASHL(k, 4) + ((INT16)d[__X(j, 32)] - 48);
					j += 1;
				}
				if (neg) {
					(*S).i = -k;
				} else {
					(*S).i = k;
				}
			} else if ((ch == '.' && __ISP((*S).lib, Fonts_FontDesc, 1))) {
				Texts_Read((void*)&*S, S__typ, &ch);
				h = i;
				while (((((('0' <= ch && ch <= '9')) && __ISP((*S).lib, Fonts_FontDesc, 1))) && i < 32)) {
					d[__X(i, 32)] = ch;
					i += 1;
					Texts_Read((void*)&*S, S__typ, &ch);
				}
				while (__MASK(i, -8) != 0) {
					d[__X(i, 32)] = '0';
					i += 1;
				}
				j = 0;
				k = 0;
				k1 = 0;
				k2 = 0;
				k3 = 0;
				while (j < 8) {
					k = (k * 10 + d[__X(j, 32)]) - 48;
					j += 1;
				}
				if (8 < i) {
					while (j < 16) {
						k1 = (k1 * 10 + d[__X(j, 32)]) - 48;
						j += 1;
					}
				}
				if (16 < i) {
					while (j < 24) {
						k2 = (k2 * 10 + d[__X(j, 32)]) - 48;
						j += 1;
					}
				}
				if (24 < i) {
					while (j < 32) {
						k3 = (k3 * 10 + d[__X(j, 32)]) - 48;
						j += 1;
					}
				}
				e = 0;
				E = ch;
				if (((E == 'D' || E == 'E') && __ISP((*S).lib, Fonts_FontDesc, 1))) {
					Texts_Read((void*)&*S, S__typ, &ch);
					if ((ch == '-' && __ISP((*S).lib, Fonts_FontDesc, 1))) {
						negE = 1;
						Texts_Read((void*)&*S, S__typ, &ch);
					} else {
						negE = 0;
						if ((ch == '+' && __ISP((*S).lib, Fonts_FontDesc, 1))) {
							Texts_Read((void*)&*S, S__typ, &ch);
						}
					}
					while (((('0' <= ch && ch <= '9')) && __ISP((*S).lib, Fonts_FontDesc, 1))) {
						e = (e * 10 + ch) - 48;
						Texts_Read((void*)&*S, S__typ, &ch);
					}
					if (negE) {
						e = -e;
					}
				}
				y = k3 * Reals_Ten(-32) + k2 * Reals_Ten(-24);
				y = y + k1 * Reals_Ten(-16);
				if (__ABS(e + h) < 308) {
					y = (y + k * Reals_Ten(-8)) / (LONGREAL)Reals_Ten(-e - h);
				} else {
					y = (y + k * Reals_Ten(-8)) * Reals_Ten(h);
					if (e <= 276 || (e <= 308 && y <   1.79769296342094e+308 / (LONGREAL)Reals_Ten(e))) {
						y = y * Reals_Ten(e);
					} else {
						y =   1.79769296342094e+308;
					}
				}
				if (E == 'D') {
					if (y ==   1.79769296342094e+308) {
						(*S).class = 0;
					} else {
						(*S).class = 5;
						if (neg) {
							(*S).y = -y;
						} else {
							(*S).y = y;
						}
						if (Reals_ExpoL((*S).y) == 0) {
							(*S).y = (LONGREAL)0;
						}
					}
				} else if (  3.40282346000000e+038 < y) {
					(*S).class = 0;
				} else {
					(*S).class = 4;
					if (neg) {
						(*S).x = (-y);
					} else {
						(*S).x = y;
					}
					if (Reals_Expo((*S).x) == 0) {
						(*S).x = (REAL)0;
					}
				}
				if (hex) {
					(*S).class = 0;
				}
			} else {
				(*S).class = 3;
				k = 0;
				while ((j != i && (k < 214748364 || (k == 214748364 && (INT16)d[__X(j, 32)] - 48 <= 7)))) {
					k = k * 10 + ((INT16)d[__X(j, 32)] - 48);
					j += 1;
				}
				if (j != i) {
					(*S).class = 0;
				} else {
					if (neg) {
						(*S).i = -k;
					} else {
						(*S).i = k;
					}
					if (hex) {
						(*S).class = 0;
					} else {
						(*S).class = 3;
					}
				}
			}
		} else {
			(*S).class = 6;
			if (sign) {
				if (neg) {
					(*S).c = '-';
				} else {
					(*S).c = '+';
				}
			} else {
				(*S).c = ch;
				Texts_Read((void*)&*S, S__typ, &ch);
			}
		}
	}
	(*S).nextCh = ch;
}

void Texts_OpenWriter (Texts_Writer *W, ADDRESS *W__typ)
{
	__NEW((*W).buf, Texts_BufDesc);
	Texts_OpenBuf((*W).buf);
	(*W).lib = (Objects_Library)Fonts_Default;
	(*W).col = 15;
	(*W).voff = 0;
	Files_Set(&(*W).R, OFS_Rider__typ, Files_New((CHAR*)"", 1), 0);
}

void Texts_SetFont (Texts_Writer *W, ADDRESS *W__typ, Objects_Library fnt)
{
	(*W).lib = fnt;
}

void Texts_SetColor (Texts_Writer *W, ADDRESS *W__typ, INT8 col)
{
	(*W).col = col;
}

void Texts_SetOffset (Texts_Writer *W, ADDRESS *W__typ, INT8 voff)
{
	(*W).voff = voff;
}

void Texts_Write (Texts_Writer *W, ADDRESS *W__typ, CHAR ch)
{
	Texts_Piece p, q;
	p = (*W).buf->last;
	if ((((!__ISP((*W).lib, Fonts_FontDesc, 1) || (*W).lib != p->lib) || (*W).col != p->col) || (*W).voff != p->voff) || Files_Base(&(*W).R, OFS_Rider__typ) != p->f) {
		__NEW(q, Texts_PieceDesc);
		q->ref = (-32767-1);
		if (!__ISP((*W).lib, Fonts_FontDesc, 1)) {
			(*(*W).lib->GetObj)((*W).lib, (INT16)ch, &q->obj);
		}
		q->f = Files_Base(&(*W).R, OFS_Rider__typ);
		q->off = Files_Pos(&(*W).R, OFS_Rider__typ);
		q->len = 0;
		q->lib = (*W).lib;
		q->col = (*W).col;
		q->voff = (*W).voff;
		q->next = NIL;
		p->next = q;
		q->prev = p;
		p = q;
		(*W).buf->last = p;
	}
	Files_Write(&(*W).R, OFS_Rider__typ, ch);
	p->len += 1;
	(*W).buf->len += 1;
}

void Texts_WriteLn (Texts_Writer *W, ADDRESS *W__typ)
{
	Texts_Write(&*W, W__typ, 0x0d);
}

void Texts_WriteString (Texts_Writer *W, ADDRESS *W__typ, CHAR *s, ADDRESS s__len)
{
	INT32 i;
	__DUP(s, s__len, CHAR);
	i = 0;
	while (s[__X(i, s__len)] != 0x00) {
		Texts_Write(&*W, W__typ, s[__X(i, s__len)]);
		i += 1;
	}
	__DEL(s);
}

void Texts_WriteInt (Texts_Writer *W, ADDRESS *W__typ, INT32 x, INT32 n)
{
	INT32 i, x0;
	CHAR a[10];
	i = 0;
	if (x < 0) {
		if (x == (-2147483647-1)) {
			Texts_WriteString(&*W, W__typ, (CHAR*)" -2147483648", 13);
			return;
		} else {
			n -= 1;
			x0 = -x;
		}
	} else {
		x0 = x;
	}
	do {
		a[__X(i, 10)] = (CHAR)((int)__MOD(x0, 10) + 48);
		x0 = __DIV(x0, 10);
		i += 1;
	} while (!(x0 == 0));
	while (n > i) {
		Texts_Write(&*W, W__typ, ' ');
		n -= 1;
	}
	if (x < 0) {
		Texts_Write(&*W, W__typ, '-');
	}
	do {
		i -= 1;
		Texts_Write(&*W, W__typ, a[__X(i, 10)]);
	} while (!(i == 0));
}

void Texts_WriteHex (Texts_Writer *W, ADDRESS *W__typ, INT32 x)
{
	INT32 i, y;
	CHAR a[10];
	i = 0;
	Texts_Write(&*W, W__typ, ' ');
	do {
		y = __MASK(x, -16);
		if (y < 10) {
			a[__X(i, 10)] = (CHAR)(y + 48);
		} else {
			a[__X(i, 10)] = (CHAR)(y + 55);
		}
		x = __ASHR(x, 4);
		i += 1;
	} while (!(i == 8));
	do {
		i -= 1;
		Texts_Write(&*W, W__typ, a[__X(i, 10)]);
	} while (!(i == 0));
}

void Texts_WriteRealHex (Texts_Writer *W, ADDRESS *W__typ, REAL x)
{
	Texts_WriteHex(&*W, W__typ, Reals_Int(x));
}

void Texts_WriteLongRealHex (Texts_Writer *W, ADDRESS *W__typ, LONGREAL x)
{
	INT32 h, l;
	Reals_IntL(x, &h, &l);
	Texts_WriteHex(&*W, W__typ, h);
	Texts_WriteHex(&*W, W__typ, l);
}

void Texts_WriteReal (Texts_Writer *W, ADDRESS *W__typ, REAL x, INT32 n)
{
	INT32 e, h, i;
	LONGREAL y;
	REAL z;
	CHAR d[8];
	e = Reals_Expo(x);
	if (e == 255) {
		while (n > 8) {
			Texts_Write(&*W, W__typ, ' ');
			n -= 1;
		}
		h = Reals_NaNCode(x);
		if (h != 0) {
			Texts_WriteString(&*W, W__typ, (CHAR*)"     NaN", 9);
		} else if (x < (REAL)0) {
			Texts_WriteString(&*W, W__typ, (CHAR*)"    -INF", 9);
		} else {
			Texts_WriteString(&*W, W__typ, (CHAR*)"      INF", 10);
		}
	} else {
		if (n <= 8) {
			n = 1;
		} else {
			n -= 7;
		}
		do {
			Texts_Write(&*W, W__typ, ' ');
			n -= 1;
		} while (!(n <= 7));
		if ((e != 0 && x < (REAL)0)) {
			Texts_Write(&*W, W__typ, '-');
			x = -x;
		} else {
			Texts_Write(&*W, W__typ, ' ');
		}
		if (e == 0) {
			h = 0;
		} else {
			e = __DIV((e - 127) * 301, 1000);
			if (e < 38) {
				z = Reals_Ten(e + 1);
				if (x >= z) {
					y = x / (LONGREAL)z;
					e += 1;
				} else {
					y = x * Reals_Ten(-e);
				}
			} else {
				y = x * Reals_Ten(-38);
			}
			if (y >= (LONGREAL)10) {
				y = y * Reals_Ten(-1) +   5.00000000000000e-001 / (LONGREAL)Reals_Ten(n);
				e += 1;
			} else {
				y = y +   5.00000000000000e-001 / (LONGREAL)Reals_Ten(n);
				if (y >= (LONGREAL)10) {
					y = y * Reals_Ten(-1);
					e += 1;
				}
			}
			y = y * Reals_Ten(7);
			h = (INT32)__ENTIER(y);
		}
		i = 7;
		while (i >= 0) {
			d[__X(i, 8)] = (CHAR)((int)__MOD(h, 10) + 48);
			h = __DIV(h, 10);
			i -= 1;
		}
		Texts_Write(&*W, W__typ, d[0]);
		Texts_Write(&*W, W__typ, '.');
		i = 1;
		while (i <= n) {
			Texts_Write(&*W, W__typ, d[__X(i, 8)]);
			i += 1;
		}
		if (e < 0) {
			Texts_WriteString(&*W, W__typ, (CHAR*)"E-", 3);
			e = -e;
		} else {
			Texts_WriteString(&*W, W__typ, (CHAR*)"E+", 3);
		}
		Texts_Write(&*W, W__typ, (CHAR)(__DIV(e, 10) + 48));
		Texts_Write(&*W, W__typ, (CHAR)((int)__MOD(e, 10) + 48));
	}
}

void Texts_WriteRealFix (Texts_Writer *W, ADDRESS *W__typ, REAL x, INT32 n, INT32 f, INT32 E)
{
	INT32 e, h, i;
	LONGREAL r, y;
	REAL z;
	CHAR s;
	CHAR d[8];
	e = Reals_Expo(x);
	if (e == 255 || __ABS(E) > 38) {
		while (n > 8) {
			Texts_Write(&*W, W__typ, ' ');
			n -= 1;
		}
		h = Reals_NaNCode(x);
		if (h != 0) {
			Texts_WriteString(&*W, W__typ, (CHAR*)"     NaN", 9);
		} else if (x < (REAL)0) {
			Texts_WriteString(&*W, W__typ, (CHAR*)"    -INF", 9);
		} else {
			Texts_WriteString(&*W, W__typ, (CHAR*)"      INF", 10);
		}
	} else {
		if (E == 0) {
			n -= 2;
		} else {
			n -= 6;
		}
		if (f < 0) {
			f = 0;
		}
		if (n < f + 2) {
			n = f + 2;
		}
		n -= f;
		if ((e != 0 && x < (REAL)0)) {
			s = '-';
			x = -x;
		} else {
			s = ' ';
		}
		if (e == 0) {
			h = 0;
			e -= E - 1;
		} else {
			e = __DIV((e - 127) * 301, 1000);
			if (e < 38) {
				z = Reals_Ten(e + 1);
				if (x >= z) {
					y = x / (LONGREAL)z;
					e += 1;
				} else {
					y = x * Reals_Ten(-e);
				}
			} else {
				y = x * Reals_Ten(-38);
			}
			e -= E - 1;
			i = -(e + f);
			if (i <= 0) {
				r = (LONGREAL)5 * Reals_Ten(i);
			} else {
				r = (LONGREAL)0;
			}
			if (y >= (LONGREAL)10) {
				y = y * Reals_Ten(-1) + r;
				e += 1;
			} else {
				y = y + r;
				if (y >= (LONGREAL)10) {
					y = y * Reals_Ten(-1);
					e += 1;
				}
			}
			y = y * Reals_Ten(7);
			h = (INT32)__ENTIER(y);
		}
		i = 7;
		while (i >= 0) {
			d[__X(i, 8)] = (CHAR)((int)__MOD(h, 10) + 48);
			h = __DIV(h, 10);
			i -= 1;
		}
		if (n <= e) {
			n = e + 1;
		}
		if (e > 0) {
			while (n > e) {
				Texts_Write(&*W, W__typ, ' ');
				n -= 1;
			}
			Texts_Write(&*W, W__typ, s);
			e = 0;
			while (n > 0) {
				n -= 1;
				if (e < 8) {
					Texts_Write(&*W, W__typ, d[__X(e, 8)]);
					e += 1;
				} else {
					Texts_Write(&*W, W__typ, '0');
				}
			}
			Texts_Write(&*W, W__typ, '.');
		} else {
			while (n > 1) {
				Texts_Write(&*W, W__typ, ' ');
				n -= 1;
			}
			Texts_Write(&*W, W__typ, s);
			Texts_Write(&*W, W__typ, '0');
			Texts_Write(&*W, W__typ, '.');
			while ((0 < f && e < 0)) {
				Texts_Write(&*W, W__typ, '0');
				f -= 1;
				e += 1;
			}
		}
		while (f > 0) {
			f -= 1;
			if (e < 8) {
				Texts_Write(&*W, W__typ, d[__X(e, 8)]);
				e += 1;
			} else {
				Texts_Write(&*W, W__typ, '0');
			}
		}
		if (E != 0) {
			if (E < 0) {
				Texts_WriteString(&*W, W__typ, (CHAR*)"E-", 3);
				E = -E;
			} else {
				Texts_WriteString(&*W, W__typ, (CHAR*)"E+", 3);
			}
			Texts_Write(&*W, W__typ, (CHAR)(__DIV(E, 10) + 48));
			Texts_Write(&*W, W__typ, (CHAR)((int)__MOD(E, 10) + 48));
		}
	}
}

void Texts_WriteLongReal (Texts_Writer *W, ADDRESS *W__typ, LONGREAL x, INT32 n)
{
	INT32 e, h, l, i;
	LONGREAL z;
	CHAR d[16];
	e = Reals_ExpoL(x);
	if (e == 2047) {
		while (n > 9) {
			Texts_Write(&*W, W__typ, ' ');
			n -= 1;
		}
		Reals_NaNCodeL(x, &h, &l);
		if (h != 0 || l != 0) {
			Texts_WriteString(&*W, W__typ, (CHAR*)"      NaN", 10);
		} else if (x < (LONGREAL)0) {
			Texts_WriteString(&*W, W__typ, (CHAR*)"     -INF", 10);
		} else {
			Texts_WriteString(&*W, W__typ, (CHAR*)"      INF", 10);
		}
	} else {
		if (n <= 9) {
			n = 1;
		} else {
			n -= 8;
		}
		do {
			Texts_Write(&*W, W__typ, ' ');
			n -= 1;
		} while (!(n <= 15));
		if ((e != 0 && x < (LONGREAL)0)) {
			Texts_Write(&*W, W__typ, '-');
			x = -x;
		} else {
			Texts_Write(&*W, W__typ, ' ');
		}
		if (e == 0) {
			h = 0;
			l = 0;
		} else {
			e = __DIV((e - 1023) * 301029, 1000000);
			z = Reals_Ten(e + 1);
			if (x >= z) {
				x = x / z;
				e += 1;
			} else {
				x = x * Reals_Ten(-e);
			}
			if (x >= (LONGREAL)10) {
				x = x * Reals_Ten(-1) +   5.00000000000000e-001 / (LONGREAL)Reals_Ten(n);
				e += 1;
			} else {
				x = x +   5.00000000000000e-001 / (LONGREAL)Reals_Ten(n);
				if (x >= (LONGREAL)10) {
					x = x * Reals_Ten(-1);
					e += 1;
				}
			}
			x = x * Reals_Ten(7);
			h = (INT32)__ENTIER(x);
			x = (x - h) * Reals_Ten(8);
			l = (INT32)__ENTIER(x);
		}
		i = 15;
		while (i > 7) {
			d[__X(i, 16)] = (CHAR)((int)__MOD(l, 10) + 48);
			l = __DIV(l, 10);
			i -= 1;
		}
		while (i >= 0) {
			d[__X(i, 16)] = (CHAR)((int)__MOD(h, 10) + 48);
			h = __DIV(h, 10);
			i -= 1;
		}
		Texts_Write(&*W, W__typ, d[0]);
		Texts_Write(&*W, W__typ, '.');
		i = 1;
		while (i <= n) {
			Texts_Write(&*W, W__typ, d[__X(i, 16)]);
			i += 1;
		}
		if (e < 0) {
			Texts_WriteString(&*W, W__typ, (CHAR*)"D-", 3);
			e = -e;
		} else {
			Texts_WriteString(&*W, W__typ, (CHAR*)"D+", 3);
		}
		Texts_Write(&*W, W__typ, (CHAR)(__DIV(e, 100) + 48));
		e = (int)__MOD(e, 100);
		Texts_Write(&*W, W__typ, (CHAR)(__DIV(e, 10) + 48));
		Texts_Write(&*W, W__typ, (CHAR)((int)__MOD(e, 10) + 48));
	}
}

void Texts_WriteLongRealFix (Texts_Writer *W, ADDRESS *W__typ, LONGREAL x, INT32 n, INT32 f, INT32 D)
{
	INT32 e, h, l, i;
	LONGREAL r, z;
	CHAR d[16];
	CHAR s;
	e = Reals_ExpoL(x);
	if (e == 2047 || __ABS(D) > 308) {
		while (n > 9) {
			Texts_Write(&*W, W__typ, ' ');
			n -= 1;
		}
		Reals_NaNCodeL(x, &h, &l);
		if (h != 0 || l != 0) {
			Texts_WriteString(&*W, W__typ, (CHAR*)"      NaN", 10);
		} else if (x < (LONGREAL)0) {
			Texts_WriteString(&*W, W__typ, (CHAR*)"     -INF", 10);
		} else {
			Texts_WriteString(&*W, W__typ, (CHAR*)"      INF", 10);
		}
	} else {
		if (D == 0) {
			n -= 2;
		} else {
			n -= 7;
		}
		if (n < 2) {
			n = 2;
		}
		if (f < 0) {
			f = 0;
		}
		if (n < f + 2) {
			n = f + 2;
		}
		n -= f;
		if ((e != 0 && x < (LONGREAL)0)) {
			s = '-';
			x = -x;
		} else {
			s = ' ';
		}
		if (e == 0) {
			h = 0;
			l = 0;
			e -= D - 1;
		} else {
			e = __DIV((e - 1023) * 301029, 1000000);
			z = Reals_Ten(e + 1);
			if (x >= z) {
				x = x / z;
				e += 1;
			} else {
				x = x * Reals_Ten(-e);
			}
			e -= D - 1;
			i = -(e + f);
			if (i <= 0) {
				r = (LONGREAL)5 * Reals_Ten(i);
			} else {
				r = (LONGREAL)0;
			}
			if (x >= (LONGREAL)10) {
				x = x * Reals_Ten(-1) + r;
				e += 1;
			} else {
				x = x + r;
				if (x >= (LONGREAL)10) {
					x = x * Reals_Ten(-1);
					e += 1;
				}
			}
			x = x * Reals_Ten(7);
			h = (INT32)__ENTIER(x);
			x = (x - h) * Reals_Ten(8);
			l = (INT32)__ENTIER(x);
		}
		i = 15;
		while (i > 7) {
			d[__X(i, 16)] = (CHAR)((int)__MOD(l, 10) + 48);
			l = __DIV(l, 10);
			i -= 1;
		}
		while (i >= 0) {
			d[__X(i, 16)] = (CHAR)((int)__MOD(h, 10) + 48);
			h = __DIV(h, 10);
			i -= 1;
		}
		if (n <= e) {
			n = e + 1;
		}
		if (e > 0) {
			while (n > e) {
				Texts_Write(&*W, W__typ, ' ');
				n -= 1;
			}
			Texts_Write(&*W, W__typ, s);
			e = 0;
			while (n > 0) {
				n -= 1;
				if (e < 16) {
					Texts_Write(&*W, W__typ, d[__X(e, 16)]);
					e += 1;
				} else {
					Texts_Write(&*W, W__typ, '0');
				}
			}
			Texts_Write(&*W, W__typ, '.');
		} else {
			while (n > 1) {
				Texts_Write(&*W, W__typ, ' ');
				n -= 1;
			}
			Texts_Write(&*W, W__typ, s);
			Texts_Write(&*W, W__typ, '0');
			Texts_Write(&*W, W__typ, '.');
			while ((0 < f && e < 0)) {
				Texts_Write(&*W, W__typ, '0');
				f -= 1;
				e += 1;
			}
		}
		while (f > 0) {
			f -= 1;
			if (e < 16) {
				Texts_Write(&*W, W__typ, d[__X(e, 16)]);
				e += 1;
			} else {
				Texts_Write(&*W, W__typ, '0');
			}
		}
		if (D != 0) {
			if (D < 0) {
				Texts_WriteString(&*W, W__typ, (CHAR*)"D-", 3);
				D = -D;
			} else {
				Texts_WriteString(&*W, W__typ, (CHAR*)"D+", 3);
			}
			Texts_Write(&*W, W__typ, (CHAR)(__DIV(D, 100) + 48));
			D = (int)__MOD(D, 100);
			Texts_Write(&*W, W__typ, (CHAR)(__DIV(D, 10) + 48));
			Texts_Write(&*W, W__typ, (CHAR)((int)__MOD(D, 10) + 48));
		}
	}
}

static struct WriteDate__36 {
	Texts_Writer *W;
	ADDRESS *W__typ;
	struct WriteDate__36 *lnk;
} *WriteDate__36_s;

static void WritePair__37 (CHAR ch, INT32 x);

static void WritePair__37 (CHAR ch, INT32 x)
{
	Texts_Write(&*WriteDate__36_s->W, WriteDate__36_s->W__typ, ch);
	Texts_Write(&*WriteDate__36_s->W, WriteDate__36_s->W__typ, (CHAR)(__DIV(x, 10) + 48));
	Texts_Write(&*WriteDate__36_s->W, WriteDate__36_s->W__typ, (CHAR)((int)__MOD(x, 10) + 48));
}

void Texts_WriteDate (Texts_Writer *W, ADDRESS *W__typ, INT32 t, INT32 d)
{
	struct WriteDate__36 _s;
	_s.W = W; _s.W__typ = W__typ;
	_s.lnk = WriteDate__36_s;
	WriteDate__36_s = &_s;
	WritePair__37(' ', __MASK(d, -32));
	WritePair__37('.', __MASK(__ASHR(d, 5), -16));
	Texts_Write(&*W, W__typ, '.');
	Texts_WriteInt(&*W, W__typ, 1900 + __ASHR(d, 9), 1);
	WritePair__37(' ', __MASK(__ASHR(t, 12), -32));
	WritePair__37(':', __MASK(__ASHR(t, 6), -64));
	WritePair__37(':', __MASK(t, -64));
	WriteDate__36_s = _s.lnk;
}

void Texts_WriteSet (Texts_Writer *W, ADDRESS *W__typ, UINT32 s)
{
	INT32 i, last;
	BOOLEAN dots;
	Texts_Write(&*W, W__typ, '{');
	last = (-2147483647-1);
	i = 0;
	while (i <= 31) {
		if (__IN(i, s, 32)) {
			if (last == i - 1) {
				if (dots) {
					Texts_WriteString(&*W, W__typ, (CHAR*)" .. ", 5);
					dots = 0;
				}
				if (i == 31 || !__IN(i + 1, s, 32)) {
					Texts_WriteInt(&*W, W__typ, i, 0);
				}
			} else {
				if (last >= 0) {
					Texts_WriteString(&*W, W__typ, (CHAR*)", ", 3);
				}
				Texts_WriteInt(&*W, W__typ, i, 0);
				dots = 1;
			}
			last = i;
		}
		i += 1;
	}
	Texts_Write(&*W, W__typ, '}');
}

void Texts_WriteObj (Texts_Writer *W, ADDRESS *W__typ, Objects_Object obj)
{
	Objects_Library lib;
	if ((obj->lib == NIL || obj->ref < 0) || obj->lib->name[0] == 0x00) {
		if (Texts_obs == NIL) {
			__NEW(Texts_obs, Objects_LibDesc);
			Objects_OpenLibrary(Texts_obs);
		}
		(*Texts_obs->GenRef)(Texts_obs, &obj->ref);
		if (obj->ref >= 256) {
			__NEW(Texts_obs, Objects_LibDesc);
			Objects_OpenLibrary(Texts_obs);
			(*Texts_obs->GenRef)(Texts_obs, &obj->ref);
		}
		(*Texts_obs->PutObj)(Texts_obs, obj->ref, obj);
	}
	__ASSERT(obj->ref < 256, 0);
	lib = (*W).lib;
	Texts_SetFont(&*W, W__typ, obj->lib);
	Texts_Write(&*W, W__typ, (CHAR)obj->ref);
	Texts_SetFont(&*W, W__typ, lib);
}

static void Texts_InitScan (void)
{
	INT32 i;
	i = 0;
	while (i <= 255) {
		Texts_nameChars[__X(i, 256)] = 0;
		i += 1;
	}
	i = 128;
	while (i <= 150) {
		Texts_nameChars[__X(i, 256)] = 1;
		i += 1;
	}
	i = 48;
	while (i <= 57) {
		Texts_nameChars[__X(i, 256)] = 1;
		i += 1;
	}
	i = 65;
	while (i <= 90) {
		Texts_nameChars[__X(i, 256)] = 1;
		i += 1;
	}
	i = 97;
	while (i <= 122) {
		Texts_nameChars[__X(i, 256)] = 1;
		i += 1;
	}
	Texts_nameChars[64] = 1;
	Texts_nameChars[46] = 1;
	Texts_nameChars[47] = 1;
	Texts_nameChars[58] = 1;
	Texts_nameChars[95] = 1;
}

static void EnumPtrs(void (*P)(void*))
{
	P(Texts_Wfile);
	__ENUMR(&Texts_R, OFS_Rider__typ, 28, 1, P);
	P(Texts_DelBuf);
	P(Texts_obs);
}

__TDESC(Texts_PieceDesc, 1, 5) = {__TDFLDS("PieceDesc", 32), {0, 12, 16, 24, 28, -24}};
__TDESC(Texts_TextDesc, 1, 6) = {__TDFLDS("TextDesc", 44), {4, 8, 12, 28, 32, 40, -28}};
__TDESC(Texts_UpdateMsg, 1, 3) = {__TDFLDS("UpdateMsg", 36), {4, 8, 20, -16}};
__TDESC(Texts_Finder, 1, 2) = {__TDFLDS("Finder", 16), {8, 12, -12}};
__TDESC(Texts_Reader, 1, 6) = {__TDFLDS("Reader", 128), {0, 4, 32, 36, 40, 120, -28}};
__TDESC(Texts_Scanner, 1, 7) = {__TDFLDS("Scanner", 224), {0, 4, 32, 36, 40, 120, 220, -32}};
__TDESC(Texts_BufDesc, 1, 2) = {__TDFLDS("BufDesc", 12), {4, 8, -12}};
__TDESC(Texts_Writer, 1, 5) = {__TDFLDS("Writer", 40), {16, 20, 24, 28, 32, -24}};
__TDESC(ObjsBlockDesc__33, 1, 257) = {__TDFLDS("ObjsBlockDesc__33", 1028), {0, 4, 8, 12, 16, 20, 24, 28, 32, 36, 40, 44, 48, 52, 56, 60, 
	64, 68, 72, 76, 80, 84, 88, 92, 96, 100, 104, 108, 112, 116, 120, 124, 
	128, 132, 136, 140, 144, 148, 152, 156, 160, 164, 168, 172, 176, 180, 184, 188, 
	192, 196, 200, 204, 208, 212, 216, 220, 224, 228, 232, 236, 240, 244, 248, 252, 
	256, 260, 264, 268, 272, 276, 280, 284, 288, 292, 296, 300, 304, 308, 312, 316, 
	320, 324, 328, 332, 336, 340, 344, 348, 352, 356, 360, 364, 368, 372, 376, 380, 
	384, 388, 392, 396, 400, 404, 408, 412, 416, 420, 424, 428, 432, 436, 440, 444, 
	448, 452, 456, 460, 464, 468, 472, 476, 480, 484, 488, 492, 496, 500, 504, 508, 
	512, 516, 520, 524, 528, 532, 536, 540, 544, 548, 552, 556, 560, 564, 568, 572, 
	576, 580, 584, 588, 592, 596, 600, 604, 608, 612, 616, 620, 624, 628, 632, 636, 
	640, 644, 648, 652, 656, 660, 664, 668, 672, 676, 680, 684, 688, 692, 696, 700, 
	704, 708, 712, 716, 720, 724, 728, 732, 736, 740, 744, 748, 752, 756, 760, 764, 
	768, 772, 776, 780, 784, 788, 792, 796, 800, 804, 808, 812, 816, 820, 824, 828, 
	832, 836, 840, 844, 848, 852, 856, 860, 864, 868, 872, 876, 880, 884, 888, 892, 
	896, 900, 904, 908, 912, 916, 920, 924, 928, 932, 936, 940, 944, 948, 952, 956, 
	960, 964, 968, 972, 976, 980, 984, 988, 992, 996, 1000, 1004, 1008, 1012, 1016, 1020, 
	1024, -1032}};

export void *Texts__init(void)
{
	__DEFMOD;
	__MODULE_IMPORT(Display);
	__MODULE_IMPORT(Files);
	__MODULE_IMPORT(Fonts);
	__MODULE_IMPORT(Objects);
	__MODULE_IMPORT(Reals);
	__REGMOD("Texts", EnumPtrs);
	__REGCMD("New", Texts_New);
	__INITYP(Texts_PieceDesc, Texts_PieceDesc, 0);
	__INITYP(Texts_TextDesc, Objects_ObjDesc, 1);
	__INITYP(Texts_UpdateMsg, Display_FrameMsg, 2);
	__INITYP(Texts_Finder, Texts_Finder, 0);
	__INITYP(Texts_Reader, Texts_Reader, 0);
	__INITYP(Texts_Scanner, Texts_Reader, 1);
	__INITYP(Texts_BufDesc, Texts_BufDesc, 0);
	__INITYP(Texts_Writer, Texts_Writer, 0);
	__INITYP(ObjsBlockDesc__33, ObjsBlockDesc__33, 0);
/* BEGIN */
	Texts_TextBlockId = 0xf0;
	Texts_DocBlockId = 0xf7;
	Texts_NoSpex = 0x00;
	Texts_TextSpex = 0x01;
	Texts_NoSpex2 = 0x02;
	Texts_H = Texts_Handle;
	Texts_Wfile = Files_New((CHAR*)"", 1);
	Files_Set(&Texts_R, OFS_Rider__typ, Texts_Wfile, 0);
	Files_Write(&Texts_R, OFS_Rider__typ, 0x00);
	__NEW(Texts_DelBuf, Texts_BufDesc);
	Texts_OpenBuf(Texts_DelBuf);
	Texts_InitScan();
	Texts_obs = NIL;
	__ENDMOD;
}
