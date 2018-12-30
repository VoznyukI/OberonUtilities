/* voc 2.1.0 [2017/09/06]. Bootstrapping compiler for address size 8, alignment 8. xtaSv */

#ifndef Fonts__h
#define Fonts__h

#include "SYSTEM.h"
#include "Objects.h"

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
		Objects_Library next;
		Objects_Index ind;
		Files_File f;
		Files_Rider R;
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

		INT8 type;
		INT16 height, minX, maxX, minY, maxY;
	} Fonts_FontDesc;


import CHAR Fonts_FontId;
import Fonts_Font Fonts_Default;

import ADDRESS *Fonts_CharDesc__typ;
import ADDRESS *Fonts_FontDesc__typ;

import void Fonts_GetChar (Fonts_Font F, CHAR ch, INT16 *dx, INT16 *x, INT16 *y, INT16 *w, INT16 *h, INT32 *pat);
import Fonts_Font Fonts_This (CHAR *name, ADDRESS name__len);
import void *Fonts__init(void);


#endif // Fonts
