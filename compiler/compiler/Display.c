/* voc 2.1.0 [2017/09/06]. Bootstrapping compiler for address size 8, alignment 8. xtaSv */

#define SHORTINT INT8
#define INTEGER  INT16
#define LONGINT  INT32
#define SET      UINT32

#include "SYSTEM.h"
#include "Displays.h"
#include "Kernel.h"
#include "Modules.h"
#include "Objects.h"

struct Display__1 {
	CHAR buf[8192];
};

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
	struct Display_ListDesc *Display_List;

typedef
	struct Display__1 *Display_PatternPtr;

typedef
	struct Display_ListDesc {
		Display_List next;
		Display_PatternPtr pat;
	} Display_ListDesc;

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


export INT32 Display_Unit;
export INT16 Display_Left, Display_ColLeft, Display_Bottom, Display_UBottom, Display_Width, Display_Height;
export INT32 Display_arrow, Display_star, Display_cross, Display_downArrow, Display_hook, Display_grey0, Display_grey1, Display_grey2, Display_ticks, Display_solid;
export Display_MsgProc Display_Broadcast;
static INT32 Display_palette[256];
static INT32 Display_clipX1, Display_clipY1, Display_clipX2, Display_clipY2;
static Display_List Display_pattern;
static struct {
	ADDRESS len[1];
	CHAR data[1];
} *Display_buf;
static INT32 Display_height;

export ADDRESS *Display__1__typ;
export ADDRESS *Display_ListDesc__typ;
export ADDRESS *Display_FrameDesc__typ;
export ADDRESS *Display_FrameMsg__typ;
export ADDRESS *Display_ControlMsg__typ;
export ADDRESS *Display_ModifyMsg__typ;
export ADDRESS *Display_DisplayMsg__typ;
export ADDRESS *Display_LocateMsg__typ;
export ADDRESS *Display_SelectMsg__typ;
export ADDRESS *Display_ConsumeMsg__typ;

export void Display_AdjustClip (INT32 x, INT32 y, INT32 w, INT32 h);
static void Display_CreatePatterns (void);
export INT16 Display_Depth (INT32 x);
export void Display_GetClip (INT16 *x, INT16 *y, INT16 *w, INT16 *h);
export void Display_GetColor (INT32 col, INT16 *red, INT16 *green, INT16 *blue);
export void Display_GetDim (INT32 pat, INT16 *w, INT16 *h);
static void Display_LoadDriver (void);
export INT32 Display_Map (INT32 x);
export INT32 Display_NewPattern (INT32 w, INT32 h, UINT32 *image, ADDRESS image__len);
export INT32 Display_RGB (INT32 red, INT32 green, INT32 blue);
export void Display_ReplPattern (INT32 col, INT32 pat, INT32 x, INT32 y, INT32 w, INT32 h, INT32 mode);
export void Display_SetClip (INT32 x, INT32 y, INT32 w, INT32 h);
export void Display_SetColor (INT32 col, INT32 red, INT32 green, INT32 blue);
export void Display_SetMode (INT32 x, UINT32 s);
export BOOLEAN Display_TrueColor (INT32 x);


void Display_SetColor (INT32 col, INT32 red, INT32 green, INT32 blue)
{
	Display_palette[__X(__MASK(col, -256), 256)] = __ASHL(__ASHL(red, 8) + green, 8) + blue;
}

void Display_GetColor (INT32 col, INT16 *red, INT16 *green, INT16 *blue)
{
	if (col >= 0) {
		col = Display_palette[__X(__MASK(col, -256), 256)];
	}
	*red = (INT16)__MASK(__ASHR(col, 16), -256);
	*green = (INT16)__MASK(__ASHR(col, 8), -256);
	*blue = (INT16)__MASK(col, -256);
}

INT32 Display_RGB (INT32 red, INT32 green, INT32 blue)
{
	return (((-2147483647-1) + __ASHL(red, 16)) + __ASHL(green, 8)) + blue;
}

INT16 Display_Depth (INT32 x)
{
	return 8;
}

BOOLEAN Display_TrueColor (INT32 x)
{
	return 1;
}

void Display_GetClip (INT16 *x, INT16 *y, INT16 *w, INT16 *h)
{
	*x = (INT16)Display_clipX1;
	*y = (INT16)Display_clipY1;
	*w = (INT16)((Display_clipX2 - Display_clipX1) + 1);
	*h = (INT16)((Display_clipY2 - Display_clipY1) + 1);
}

void Display_SetClip (INT32 x, INT32 y, INT32 w, INT32 h)
{
	Display_clipX1 = x;
	Display_clipY1 = y;
	Display_clipX2 = (Display_clipX1 + w) - 1;
	Display_clipY2 = (Display_clipY1 + h) - 1;
}

void Display_AdjustClip (INT32 x, INT32 y, INT32 w, INT32 h)
{
	INT32 x2, y2;
	x2 = (x + w) - 1;
	y2 = (y + h) - 1;
	if (x > Display_clipX1) {
		Display_clipX1 = x;
	}
	if (y > Display_clipY1) {
		Display_clipY1 = y;
	}
	if (x2 < Display_clipX2) {
		Display_clipX2 = x2;
	}
	if (y2 < Display_clipY2) {
		Display_clipY2 = y2;
	}
}

void Display_ReplPattern (INT32 col, INT32 pat, INT32 x, INT32 y, INT32 w, INT32 h, INT32 mode)
{
}

void Display_GetDim (INT32 pat, INT16 *w, INT16 *h)
{
	CHAR ch;
	__GET(pat, ch, CHAR);
	*w = (INT16)ch;
	__GET(pat + 1, ch, CHAR);
	*h = (INT16)ch;
}

INT32 Display_NewPattern (INT32 w, INT32 h, UINT32 *image, ADDRESS image__len)
{
	INT32 len, src, dest, i;
	Display_PatternPtr p;
	Display_List pl;
	len = __ASHR(w + 7, 3);
	__SYSNEW(p, 4 + len * h);
	p->buf[0] = (CHAR)w;
	p->buf[1] = (CHAR)h;
	src = (ADDRESS)&image[0];
	dest = (ADDRESS)&p->buf[2];
	i = 0;
	while (i < h) {
		__MOVE(src, dest, len);
		src += 4;
		dest += len;
		i += 1;
	}
	__NEW(pl, Display_ListDesc);
	pl->pat = p;
	pl->next = Display_pattern;
	Display_pattern = pl;
	__ASSERT(((ADDRESS)&p->buf[0]) == (INT32)(ADDRESS)p, 0);
	return (ADDRESS)&p->buf[0];
}

static void Display_CreatePatterns (void)
{
	UINT32 image[16];
	image[0] = 0x2000;
	image[1] = 0x7000;
	image[2] = 0x3800;
	image[3] = 0x1c00;
	image[4] = 0x0e00;
	image[5] = 0x0700;
	image[6] = 0x0380;
	image[7] = 0x01c1;
	image[8] = 0xe3;
	image[9] = 0x77;
	image[10] = 0x3f;
	image[11] = 0x1f;
	image[12] = 0x3f;
	image[13] = 0x7f;
	image[14] = 0xff;
	Display_arrow = Display_NewPattern(15, 15, (void*)image, 16);
	image[0] = 0x0401;
	image[1] = 0x0202;
	image[2] = 0x0104;
	image[3] = 0x88;
	image[4] = 0x50;
	image[5] = 0x0;
	image[6] = 0x50;
	image[7] = 0x88;
	image[8] = 0x0104;
	image[9] = 0x0202;
	image[10] = 0x0401;
	Display_cross = Display_NewPattern(11, 11, (void*)image, 16);
	image[0] = 0x40;
	image[1] = 0xe0;
	image[2] = 0x01f0;
	image[3] = 0x03f8;
	image[4] = 0x07fc;
	image[5] = 0xe0;
	image[6] = 0xe0;
	image[7] = 0xe0;
	image[8] = 0xe0;
	image[9] = 0xe0;
	image[10] = 0xe0;
	image[11] = 0xe0;
	image[12] = 0xe0;
	image[13] = 0xe0;
	image[14] = 0x0;
	Display_downArrow = Display_NewPattern(11, 15, (void*)image, 16);
	image[0] = 0x1111;
	image[1] = 0x0;
	image[2] = 0x4444;
	image[3] = 0x0;
	image[4] = 0x1111;
	image[5] = 0x0;
	image[6] = 0x4444;
	image[7] = 0x0;
	image[8] = 0x1111;
	image[9] = 0x0;
	image[10] = 0x4444;
	image[11] = 0x0;
	image[12] = 0x1111;
	image[13] = 0x0;
	image[14] = 0x4444;
	image[15] = 0x0;
	Display_grey0 = Display_NewPattern(16, 16, (void*)image, 16);
	image[0] = 0x5555;
	image[1] = 0xaaaa;
	image[2] = 0x5555;
	image[3] = 0xaaaa;
	image[4] = 0x5555;
	image[5] = 0xaaaa;
	image[6] = 0x5555;
	image[7] = 0xaaaa;
	image[8] = 0x5555;
	image[9] = 0xaaaa;
	image[10] = 0x5555;
	image[11] = 0xaaaa;
	image[12] = 0x5555;
	image[13] = 0xaaaa;
	image[14] = 0x5555;
	image[15] = 0xaaaa;
	Display_grey1 = Display_NewPattern(16, 16, (void*)image, 16);
	image[0] = 0x3333;
	image[1] = 0x3333;
	image[2] = 0xcccc;
	image[3] = 0xcccc;
	image[4] = 0x3333;
	image[5] = 0x3333;
	image[6] = 0xcccc;
	image[7] = 0xcccc;
	image[8] = 0x3333;
	image[9] = 0x3333;
	image[10] = 0xcccc;
	image[11] = 0xcccc;
	image[12] = 0x3333;
	image[13] = 0x3333;
	image[14] = 0xcccc;
	image[15] = 0xcccc;
	Display_grey2 = Display_NewPattern(16, 16, (void*)image, 16);
	image[0] = 0x0f07;
	image[1] = 0x0787;
	image[2] = 0x03c7;
	image[3] = 0x01e7;
	image[4] = 0xf7;
	image[5] = 0x7f;
	image[6] = 0x3f;
	image[7] = 0x1f;
	image[8] = 0x0f;
	image[9] = 0x07;
	image[10] = 0x03;
	image[11] = 0x01;
	Display_hook = Display_NewPattern(12, 12, (void*)image, 16);
	image[0] = 0x80;
	image[1] = 0x80;
	image[2] = 0x1084;
	image[3] = 0x0888;
	image[4] = 0x0490;
	image[5] = 0x02a0;
	image[6] = 0x01c0;
	image[7] = 0x7f7f;
	image[8] = 0x01c0;
	image[9] = 0x02a0;
	image[10] = 0x0490;
	image[11] = 0x0888;
	image[12] = 0x1084;
	image[13] = 0x80;
	image[14] = 0x80;
	Display_star = Display_NewPattern(15, 15, (void*)image, 16);
	image[0] = 0x0;
	image[1] = 0x0;
	image[2] = 0x01;
	image[3] = 0x0;
	image[4] = 0x0;
	image[5] = 0x0;
	image[6] = 0x0;
	image[7] = 0x0;
	image[8] = 0x0;
	image[9] = 0x0;
	image[10] = 0x0;
	image[11] = 0x0;
	image[12] = 0x0;
	image[13] = 0x0;
	image[14] = 0x0;
	image[15] = 0x0;
	Display_ticks = Display_NewPattern(16, 16, (void*)image, 16);
	image[0] = 0xffffffff;
	image[1] = 0xffffffff;
	image[2] = 0xffffffff;
	image[3] = 0xffffffff;
	image[4] = 0xffffffff;
	image[5] = 0xffffffff;
	image[6] = 0xffffffff;
	image[7] = 0xffffffff;
	Display_solid = Display_NewPattern(16, 8, (void*)image, 16);
}

void Display_SetMode (INT32 x, UINT32 s)
{
	Display_Left = 0;
	Display_ColLeft = 0;
	Display_Bottom = 0;
}

INT32 Display_Map (INT32 x)
{
	return 0;
}

static void Display_LoadDriver (void)
{
	Kernel_Module m;
	Kernel_Proc c;
	CHAR name[32];
	Kernel_GetConfig((CHAR*)"DDriver", 8, (void*)name, 32);
	if (name[0] == 0x00) {
		__MOVE("DisplayPermedia2", name, 17);
	}
	m = Modules_ThisMod(name, 32);
	if (m != NIL) {
		c = Modules_ThisCommand(m, (CHAR*)"Install", 8);
		if (c != NIL) {
			(*c)();
		}
	} else {
		c = NIL;
	}
	if (c == NIL) {
		Kernel_WriteString((CHAR*)"Display: ", 10);
		Kernel_WriteString(Modules_resMsg, 256);
		Kernel_WriteLn();
	}
}

static void EnumPtrs(void (*P)(void*))
{
	P(Display_pattern);
	P(Display_buf);
}

__TDESC(Display__1, 1, 0) = {__TDFLDS("", 8192), {-4}};
__TDESC(Display_ListDesc, 1, 2) = {__TDFLDS("ListDesc", 8), {0, 4, -12}};
__TDESC(Display_FrameDesc, 1, 5) = {__TDFLDS("FrameDesc", 40), {4, 8, 12, 24, 28, -24}};
__TDESC(Display_FrameMsg, 1, 2) = {__TDFLDS("FrameMsg", 20), {4, 8, -12}};
__TDESC(Display_ControlMsg, 1, 2) = {__TDFLDS("ControlMsg", 20), {4, 8, -12}};
__TDESC(Display_ModifyMsg, 1, 2) = {__TDFLDS("ModifyMsg", 40), {4, 8, -12}};
__TDESC(Display_DisplayMsg, 1, 2) = {__TDFLDS("DisplayMsg", 32), {4, 8, -12}};
__TDESC(Display_LocateMsg, 1, 3) = {__TDFLDS("LocateMsg", 32), {4, 8, 20, -16}};
__TDESC(Display_SelectMsg, 1, 4) = {__TDFLDS("SelectMsg", 32), {4, 8, 24, 28, -20}};
__TDESC(Display_ConsumeMsg, 1, 3) = {__TDFLDS("ConsumeMsg", 28), {4, 8, 24, -16}};

export void *Display__init(void)
{
	__DEFMOD;
	__MODULE_IMPORT(Displays);
	__MODULE_IMPORT(Kernel);
	__MODULE_IMPORT(Modules);
	__MODULE_IMPORT(Objects);
	__REGMOD("Display", EnumPtrs);
	__INITYP(Display__1, Display__1, 0);
	__INITYP(Display_ListDesc, Display_ListDesc, 0);
	__INITYP(Display_FrameDesc, Objects_ObjDesc, 1);
	__INITYP(Display_FrameMsg, Objects_ObjMsg, 1);
	__INITYP(Display_ControlMsg, Display_FrameMsg, 2);
	__INITYP(Display_ModifyMsg, Display_FrameMsg, 2);
	__INITYP(Display_DisplayMsg, Display_FrameMsg, 2);
	__INITYP(Display_LocateMsg, Display_FrameMsg, 2);
	__INITYP(Display_SelectMsg, Display_FrameMsg, 2);
	__INITYP(Display_ConsumeMsg, Display_FrameMsg, 2);
/* BEGIN */
	Display_LoadDriver();
	Display_buf = __NEWARR(NIL, 1, 1, 1, 1, 8192);
	Display_pattern = NIL;
	Display_CreatePatterns();
	Display_SetMode(0, 0x0);
	__ENDMOD;
}
