/* voc 2.1.0 [2017/09/06]. Bootstrapping compiler for address size 8, alignment 8. xtaSv */

#ifndef Display__h
#define Display__h

#include "SYSTEM.h"
#include "Objects.h"

typedef
	struct Display_FrameDesc *Display_Frame;

typedef
	struct Display_FrameMsg { /* Objects_ObjMsg */
		INT32 stamp;
		Objects_Object dlink;
		Display_Frame F;
		INT16 x, y, res;
	} Display_FrameMsg;

typedef
	struct Display_ConsumeMsg { /* Display_FrameMsg */
		INT32 stamp;
		Objects_Object dlink;
		Display_Frame F;
		INT16 x, y, res;
		INT16 id, u, v;
		Objects_Object obj;
	} Display_ConsumeMsg;

typedef
	struct Display_ControlMsg { /* Display_FrameMsg */
		INT32 stamp;
		Objects_Object dlink;
		Display_Frame F;
		INT16 x, y, res;
		INT16 id;
	} Display_ControlMsg;

typedef
	struct Display_DisplayMsg { /* Display_FrameMsg */
		INT32 stamp;
		Objects_Object dlink;
		Display_Frame F;
		INT16 x, y, res;
		INT16 device, id, u, v, w, h;
	} Display_DisplayMsg;

typedef
	struct Display_FrameDesc { /* Objects_ObjDesc */
		INT32 stamp;
		Objects_Object dlink, slink;
		Objects_Library lib;
		INT16 ref;
		Objects_Handler handle;
		Display_Frame next, dsc;
		INT16 X, Y, W, H;
	} Display_FrameDesc;

typedef
	struct Display_LocateMsg { /* Display_FrameMsg */
		INT32 stamp;
		Objects_Object dlink;
		Display_Frame F;
		INT16 x, y, res;
		Display_Frame loc;
		INT16 X, Y, u, v;
	} Display_LocateMsg;

typedef
	struct Display_ModifyMsg { /* Display_FrameMsg */
		INT32 stamp;
		Objects_Object dlink;
		Display_Frame F;
		INT16 x, y, res;
		INT16 id, mode, dX, dY, dW, dH, X, Y, W, H;
	} Display_ModifyMsg;

typedef
	void (*Display_MsgProc)(Display_FrameMsg*, ADDRESS *);

typedef
	struct Display_SelectMsg { /* Display_FrameMsg */
		INT32 stamp;
		Objects_Object dlink;
		Display_Frame F;
		INT16 x, y, res;
		INT16 id;
		INT32 time;
		Display_Frame sel;
		Objects_Object obj;
	} Display_SelectMsg;


import INT32 Display_Unit;
import INT16 Display_Left, Display_ColLeft, Display_Bottom, Display_UBottom, Display_Width, Display_Height;
import INT32 Display_arrow, Display_star, Display_cross, Display_downArrow, Display_hook, Display_grey0, Display_grey1, Display_grey2, Display_ticks, Display_solid;
import Display_MsgProc Display_Broadcast;

import ADDRESS *Display_FrameDesc__typ;
import ADDRESS *Display_FrameMsg__typ;
import ADDRESS *Display_ControlMsg__typ;
import ADDRESS *Display_ModifyMsg__typ;
import ADDRESS *Display_DisplayMsg__typ;
import ADDRESS *Display_LocateMsg__typ;
import ADDRESS *Display_SelectMsg__typ;
import ADDRESS *Display_ConsumeMsg__typ;

import void Display_AdjustClip (INT32 x, INT32 y, INT32 w, INT32 h);
import INT16 Display_Depth (INT32 x);
import void Display_GetClip (INT16 *x, INT16 *y, INT16 *w, INT16 *h);
import void Display_GetColor (INT32 col, INT16 *red, INT16 *green, INT16 *blue);
import void Display_GetDim (INT32 pat, INT16 *w, INT16 *h);
import INT32 Display_Map (INT32 x);
import INT32 Display_NewPattern (INT32 w, INT32 h, UINT32 *image, ADDRESS image__len);
import INT32 Display_RGB (INT32 red, INT32 green, INT32 blue);
import void Display_ReplPattern (INT32 col, INT32 pat, INT32 x, INT32 y, INT32 w, INT32 h, INT32 mode);
import void Display_SetClip (INT32 x, INT32 y, INT32 w, INT32 h);
import void Display_SetColor (INT32 col, INT32 red, INT32 green, INT32 blue);
import void Display_SetMode (INT32 x, UINT32 s);
import BOOLEAN Display_TrueColor (INT32 x);
import void *Display__init(void);


#endif // Display
