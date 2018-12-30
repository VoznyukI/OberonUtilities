/* voc 2.1.0 [2017/09/06]. Bootstrapping compiler for address size 8, alignment 8. xtaSv */

#ifndef Texts__h
#define Texts__h

#include "SYSTEM.h"
#include "Display.h"
#include "Files.h"
#include "Fonts.h"
#include "Objects.h"
#include "Reals.h"

typedef
	struct Texts_PieceDesc *Texts_Piece;

typedef
	struct Texts_TextDesc *Texts_Text;

typedef
	struct Texts_PieceDesc {
		Files_File f;
		INT32 off, len;
		Objects_Object obj;
		Objects_Library lib;
		INT16 ref;
		INT8 col, voff;
		Texts_Piece prev, next;
	} Texts_PieceDesc;

///
typedef
	//struct Texts_BufDesc {
	//	INT32 len;
	//	char _prvt0[8];
	//} Texts_BufDesc;
	struct Texts_BufDesc {
		INT32 len;
		Texts_Piece header, last;
	} Texts_BufDesc;

typedef
	Texts_BufDesc *Texts_Buffer;

typedef
//	struct Texts_Finder {
//		BOOLEAN eot;
//		INT32 pos;
//		char _prvt0[8];
//	} Texts_Finder;
	struct Texts_Finder {
		BOOLEAN eot;
		INT32 pos;
		Texts_Text T;
		Texts_Piece ref;
	} Texts_Finder;

typedef
	//struct Texts_Reader {
	//	char _prvt0[120];
	//	Objects_Library lib;
	//	INT8 col, voff;
	//	BOOLEAN eot;
	//} Texts_Reader;
	struct Texts_Reader {
		Texts_Piece ref;
		Texts_Text T;
		INT32 org, off;
		Files_Rider R; //OFS_Rider R;
		INT32 stamp;
		CHAR buf[64];
		INT32 bufpos, buflen;
		Objects_Library lib;
		INT8 col, voff;
		BOOLEAN eot;
	} Texts_Reader;

typedef
	//struct Texts_Scanner { /* Texts_Reader */
	//	char _prvt0[120];
	//	Objects_Library lib;
	//	INT8 col, voff;
	//	BOOLEAN eot;
	//	CHAR nextCh;
	//	INT16 line, class;
	//	INT32 i;
	//	REAL x;
	//	LONGREAL y;
	//	CHAR c;
	//	INT8 len;
	//	CHAR s[64];
	//	Objects_Object obj;
	//} Texts_Scanner;
	struct Texts_Scanner { /* Texts_Reader */
		Texts_Piece ref;
		Texts_Text T;
		INT32 org, off;
		Files_Rider R; //OFS_Rider R;
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
	//struct Texts_TextDesc { /* Objects_ObjDesc */
	//	INT32 stamp;
	//	Objects_Object dlink, slink;
	//	Objects_Library lib;
	//	INT16 ref;
	//	Objects_Handler handle;
	//	INT32 len;
	//	char _prvt0[16];
	//} Texts_TextDesc;
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
	//struct Texts_Writer {
	//	//char _prvt0[28];
	//	char _prvt0[17];
	//	Texts_Buffer buf;
	//	Objects_Library lib;
	//	INT8 col, voff;
	//} Texts_Writer;
	struct Texts_Writer {
		Files_Rider R;
		Texts_Buffer buf;
		Objects_Library lib;
		INT8 col, voff;
	} Texts_Writer;


import CHAR Texts_TextBlockId;

import ADDRESS *Texts_TextDesc__typ;
import ADDRESS *Texts_UpdateMsg__typ;
import ADDRESS *Texts_Finder__typ;
import ADDRESS *Texts_Reader__typ;
import ADDRESS *Texts_Scanner__typ;
import ADDRESS *Texts_BufDesc__typ;
import ADDRESS *Texts_Writer__typ;

import void Texts_Append (Texts_Text T, Texts_Buffer B);
import void Texts_ChangeLooks (Texts_Text T, INT32 beg, INT32 end, UINT32 sel, Objects_Library lib, INT8 col, INT8 voff);
import void Texts_Copy (Texts_Buffer SB, Texts_Buffer DB);
import void Texts_Delete (Texts_Text T, INT32 beg, INT32 end);
import void Texts_FindObj (Texts_Finder *F, ADDRESS *F__typ, Objects_Object *obj);
import void Texts_Handle (Objects_Object obj, Objects_ObjMsg *M, ADDRESS *M__typ);
import void Texts_Insert (Texts_Text T, INT32 pos, Texts_Buffer B);
import void Texts_Load (Texts_Text T, Files_File f, INT32 pos, INT32 *len);
import void Texts_LoadAscii (Texts_Text T, Files_File f);
import void Texts_New (void);
import void Texts_Open (Texts_Text T, CHAR *name, ADDRESS name__len);
import void Texts_OpenBuf (Texts_Buffer B);
import void Texts_OpenFinder (Texts_Finder *F, ADDRESS *F__typ, Texts_Text T, INT32 pos);
import void Texts_OpenReader (Texts_Reader *R, ADDRESS *R__typ, Texts_Text T, INT32 pos);
import void Texts_OpenScanner (Texts_Scanner *S, ADDRESS *S__typ, Texts_Text T, INT32 pos);
import void Texts_OpenWriter (Texts_Writer *W, ADDRESS *W__typ);
import INT32 Texts_Pos (Texts_Reader *R, ADDRESS *R__typ);
import void Texts_Read (Texts_Reader *R, ADDRESS *R__typ, CHAR *ch);
import void Texts_Recall (Texts_Buffer *B);
import void Texts_Replace (Texts_Text T, INT32 beg, INT32 end, Texts_Buffer B);
import void Texts_Save (Texts_Text T, INT32 beg, INT32 end, Texts_Buffer B);
import void Texts_Scan (Texts_Scanner *S, ADDRESS *S__typ);
import void Texts_SetColor (Texts_Writer *W, ADDRESS *W__typ, INT8 col);
import void Texts_SetFont (Texts_Writer *W, ADDRESS *W__typ, Objects_Library fnt);
import void Texts_SetOffset (Texts_Writer *W, ADDRESS *W__typ, INT8 voff);
import void Texts_Store (Texts_Text T, Files_File f, INT32 pos, INT32 *len);

import void Texts_Write (Texts_Writer *W, ADDRESS *W__typ, CHAR ch);
import void Texts_WriteDate (Texts_Writer *W, ADDRESS *W__typ, INT32 t, INT32 d);
import void Texts_WriteHex (Texts_Writer *W, ADDRESS *W__typ, INT32 x);
import void Texts_WriteInt (Texts_Writer *W, ADDRESS *W__typ, INT32 x, INT32 n);
import void Texts_WriteLn (Texts_Writer *W, ADDRESS *W__typ);
import void Texts_WriteLongReal (Texts_Writer *W, ADDRESS *W__typ, LONGREAL x, INT32 n);
import void Texts_WriteLongRealFix (Texts_Writer *W, ADDRESS *W__typ, LONGREAL x, INT32 n, INT32 f, INT32 D);
import void Texts_WriteLongRealHex (Texts_Writer *W, ADDRESS *W__typ, LONGREAL x);
import void Texts_WriteObj (Texts_Writer *W, ADDRESS *W__typ, Objects_Object obj);
import void Texts_WriteReal (Texts_Writer *W, ADDRESS *W__typ, REAL x, INT32 n);
import void Texts_WriteRealFix (Texts_Writer *W, ADDRESS *W__typ, REAL x, INT32 n, INT32 f, INT32 E);
import void Texts_WriteRealHex (Texts_Writer *W, ADDRESS *W__typ, REAL x);
import void Texts_WriteSet (Texts_Writer *W, ADDRESS *W__typ, UINT32 s);
import void Texts_WriteString (Texts_Writer *W, ADDRESS *W__typ, CHAR *s, ADDRESS s__len);
import void *Texts__init(void);


#endif // Texts
