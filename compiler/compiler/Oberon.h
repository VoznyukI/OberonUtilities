/* voc 2.1.0 [2017/09/06]. Bootstrapping compiler for address size 8, alignment 8. xtaSv */

#ifndef Oberon__h
#define Oberon__h

#include "SYSTEM.h"
#include "Display.h"
#include "Fonts.h"
#include "Objects.h"
#include "Texts.h"

typedef
	struct Oberon_CaretMsg { /* Display_FrameMsg */
		INT32 stamp;
		Objects_Object dlink;
		Display_Frame F;
		INT16 x, y, res;
		INT16 id;
		Display_Frame car;
		Texts_Text text;
		INT32 pos;
	} Oberon_CaretMsg;

typedef
	struct Oberon_ConsumeMsg { /* Display_FrameMsg */
		INT32 stamp;
		Objects_Object dlink;
		Display_Frame F;
		INT16 x, y, res;
		Texts_Text text;
		INT32 beg, end;
	} Oberon_ConsumeMsg;

typedef
	struct Oberon_ControlMsg { /* Display_FrameMsg */
		INT32 stamp;
		Objects_Object dlink;
		Display_Frame F;
		INT16 x, y, res;
		INT16 id, X, Y;
	} Oberon_ControlMsg;

typedef
	void (*Oberon_Painter)(INT16, INT16);

typedef
	struct Oberon_Marker {
		Oberon_Painter Fade, Draw;
	} Oberon_Marker;

typedef
	struct Oberon_Cursor {
		Oberon_Marker marker;
		BOOLEAN on;
		INT16 X, Y;
	} Oberon_Cursor;

typedef
	struct Oberon_TaskDesc *Oberon_Task;

typedef
	void (*Oberon_Handler)(Oberon_Task);

typedef
	struct Oberon_InputMsg { /* Display_FrameMsg */
		INT32 stamp;
		Objects_Object dlink;
		Display_Frame F;
		INT16 x, y, res;
		INT16 id;
		UINT32 keys;
		INT16 X, Y;
		CHAR ch;
		Fonts_Font fnt;
		INT8 col, voff;
	} Oberon_InputMsg;

typedef
	struct Oberon_ParRec *Oberon_ParList;

typedef
	struct Oberon_ParRec {
		Display_Frame frame;
		Objects_Object obj;
		Texts_Text text;
		INT32 pos;
	} Oberon_ParRec;

typedef
	struct Oberon_RecallMsg { /* Display_FrameMsg */
		INT32 stamp;
		Objects_Object dlink;
		Display_Frame F;
		INT16 x, y, res;
	} Oberon_RecallMsg;

typedef
	struct Oberon_SelectMsg { /* Display_FrameMsg */
		INT32 stamp;
		Objects_Object dlink;
		Display_Frame F;
		INT16 x, y, res;
		INT16 id;
		INT32 time;
		Display_Frame sel;
		Texts_Text text;
		INT32 beg, end;
	} Oberon_SelectMsg;

typedef
	struct Oberon_TaskDesc {
		Oberon_Task next;
		INT32 time;
		BOOLEAN safe;
		Oberon_Handler handle;
	} Oberon_TaskDesc;


import Oberon_Marker Oberon_Arrow, Oberon_Star;
import Oberon_Cursor Oberon_Mouse, Oberon_Pointer;
import Texts_Text Oberon_Log;
import Oberon_ParList Oberon_Par;
import Fonts_Font Oberon_CurFnt;
import INT8 Oberon_CurCol, Oberon_CurOff;
import CHAR Oberon_OptionChar;
import void (*Oberon_OpenText)(CHAR*, ADDRESS , Texts_Text, INT16, INT16);
import Oberon_Task Oberon_NextTask;
import BOOLEAN Oberon_New;

import ADDRESS *Oberon_Marker__typ;
import ADDRESS *Oberon_Cursor__typ;
import ADDRESS *Oberon_ParRec__typ;
import ADDRESS *Oberon_ControlMsg__typ;
import ADDRESS *Oberon_InputMsg__typ;
import ADDRESS *Oberon_CaretMsg__typ;
import ADDRESS *Oberon_SelectMsg__typ;
import ADDRESS *Oberon_ConsumeMsg__typ;
import ADDRESS *Oberon_RecallMsg__typ;
import ADDRESS *Oberon_TaskDesc__typ;

import void Oberon_Call (CHAR *name, ADDRESS name__len, Oberon_ParList par, BOOLEAN new, INT16 *res);
import void Oberon_Collect (void);
import void Oberon_DrawCursor (Oberon_Cursor *c, ADDRESS *c__typ, Oberon_Marker *m, ADDRESS *m__typ, INT16 X, INT16 Y);
import void Oberon_FadeCursor (Oberon_Cursor *c, ADDRESS *c__typ);
import void Oberon_GetClock (INT32 *t, INT32 *d);
import void Oberon_GetSelection (Texts_Text *text, INT32 *beg, INT32 *end, INT32 *time);
import Display_Frame Oberon_MarkedFrame (void);
import Texts_Text Oberon_MarkedText (void);
import void Oberon_OpenCursor (Oberon_Cursor *c, ADDRESS *c__typ);
import void Oberon_OpenScanner (Texts_Scanner *S, ADDRESS *S__typ, CHAR *name, ADDRESS name__len);
import void Oberon_SetClock (INT32 t, INT32 d);
import INT32 Oberon_Time (void);
import void *Oberon__init(void);


#endif // Oberon
