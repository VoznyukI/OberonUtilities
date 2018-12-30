/* voc 2.1.0 [2017/09/06]. Bootstrapping compiler for address size 8, alignment 8. xtaSv */

#define SHORTINT INT8
#define INTEGER  INT16
#define LONGINT  INT32
#define SET      UINT32

#include "SYSTEM.h"
#include "Display.h"
#include "Files.h"
#include "Fonts.h"
#include "Kernel.h"
#include "Modules.h"
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
		BOOLEAN safe, active;
		Oberon_Handler handle;
	} Oberon_TaskDesc;


export Oberon_Marker Oberon_Arrow, Oberon_Star;
export Oberon_Cursor Oberon_Mouse, Oberon_Pointer;
export Texts_Text Oberon_Log;
export Oberon_ParList Oberon_Par;
export Fonts_Font Oberon_CurFnt;
export INT8 Oberon_CurCol, Oberon_CurOff;
export CHAR Oberon_OptionChar;
export void (*Oberon_OpenText)(CHAR*, ADDRESS , Texts_Text, INT16, INT16);
static Oberon_Task Oberon_CurTask;
export Oberon_Task Oberon_NextTask;
export BOOLEAN Oberon_New;
static INT16 Oberon_DW, Oberon_DH, Oberon_CL, Oberon_W0, Oberon_H0, Oberon_H1, Oberon_H2, Oberon_H3;
static Oberon_Task Oberon_GCTask;
static CHAR (*Oberon_PalTab)[768];
static BOOLEAN Oberon_ScreenOn;
static INT8 Oberon_FillerColor;
static Texts_Text Oberon_conftext;
static INT32 Oberon_conftime, Oberon_confdate;

export ADDRESS *Oberon_Marker__typ;
export ADDRESS *Oberon_Cursor__typ;
export ADDRESS *Oberon_ParRec__typ;
export ADDRESS *Oberon_ControlMsg__typ;
export ADDRESS *Oberon_InputMsg__typ;
export ADDRESS *Oberon_CaretMsg__typ;
export ADDRESS *Oberon_SelectMsg__typ;
export ADDRESS *Oberon_ConsumeMsg__typ;
export ADDRESS *Oberon_RecallMsg__typ;
export ADDRESS *Oberon_TaskDesc__typ;

export void Oberon_Call (CHAR *name, ADDRESS name__len, Oberon_ParList par, BOOLEAN new, INT16 *res);
export void Oberon_Collect (void);
export void Oberon_DrawCursor (Oberon_Cursor *c, ADDRESS *c__typ, Oberon_Marker *m, ADDRESS *m__typ, INT16 X, INT16 Y);
export void Oberon_FadeCursor (Oberon_Cursor *c, ADDRESS *c__typ);
static void Oberon_FlipArrow (INT16 X, INT16 Y);
static void Oberon_FlipStar (INT16 X, INT16 Y);
export void Oberon_GetClock (INT32 *t, INT32 *d);
export void Oberon_GetSelection (Texts_Text *text, INT32 *beg, INT32 *end, INT32 *time);
static void Oberon_Init (void);
export Display_Frame Oberon_MarkedFrame (void);
export Texts_Text Oberon_MarkedText (void);
export void Oberon_OpenCursor (Oberon_Cursor *c, ADDRESS *c__typ);
export void Oberon_OpenScanner (Texts_Scanner *S, ADDRESS *S__typ, CHAR *name, ADDRESS name__len);
export void Oberon_SetClock (INT32 t, INT32 d);
static void Oberon_SkipGroup (Texts_Scanner *S, ADDRESS *S__typ);
export INT32 Oberon_Time (void);


void Oberon_GetClock (INT32 *t, INT32 *d)
{
	Kernel_GetClock(&*t, &*d);
}

void Oberon_SetClock (INT32 t, INT32 d)
{
	Kernel_SetClock(t, d);
}

INT32 Oberon_Time (void)
{
	__RETCHK;
}

static void Oberon_FlipArrow (INT16 X, INT16 Y)
{
	INT16 cx, cy, cw, ch;
}

static void Oberon_FlipStar (INT16 X, INT16 Y)
{
	if (X < Oberon_CL) {
		if (X < 7) {
			X = 7;
		} else if (X > Oberon_DW - 8) {
			X = Oberon_DW - 8;
		}
	} else {
		if (X < Oberon_CL + 7) {
			X = Oberon_CL + 7;
		} else if (X > (Oberon_CL + Oberon_DW) - 8) {
			X = (Oberon_CL + Oberon_DW) - 8;
		}
	}
	if (Y < 7) {
		Y = 7;
	} else if (Y > Oberon_DH - 8) {
		Y = Oberon_DH - 8;
	}
}

void Oberon_OpenCursor (Oberon_Cursor *c, ADDRESS *c__typ)
{
	(*c).on = 0;
	(*c).X = 0;
	(*c).Y = 0;
}

void Oberon_FadeCursor (Oberon_Cursor *c, ADDRESS *c__typ)
{
	if ((*c).on) {
		(*(*c).marker.Fade)((*c).X, (*c).Y);
		(*c).on = 0;
	}
}

void Oberon_DrawCursor (Oberon_Cursor *c, ADDRESS *c__typ, Oberon_Marker *m, ADDRESS *m__typ, INT16 X, INT16 Y)
{
	if (((*c).on && ((X != (*c).X || Y != (*c).Y) || (*m).Draw != (*c).marker.Draw))) {
		(*(*c).marker.Fade)((*c).X, (*c).Y);
		(*c).on = 0;
	}
	if (!(*c).on) {
		(*(*m).Draw)(X, Y);
		(*c).marker = *m;
		(*c).X = X;
		(*c).Y = Y;
		(*c).on = 1;
	}
}

Display_Frame Oberon_MarkedFrame (void)
{
	Display_LocateMsg L;
	L.loc = NIL;
	L.X = Oberon_Pointer.X;
	L.Y = Oberon_Pointer.Y;
	L.F = NIL;
	(*Display_Broadcast)((void*)&L, Display_LocateMsg__typ);
	return L.loc;
}

Texts_Text Oberon_MarkedText (void)
{
	Display_Frame F, V;
	Objects_LinkMsg L;
	Texts_Text T;
	T = NIL;
	F = Oberon_MarkedFrame();
	if (F == NIL) {
		if ((V != NIL && V->dsc != NIL)) {
			F = V->dsc->next;
		}
	}
	if (F != NIL) {
		L.id = 1;
		__MOVE("Model", L.name, 6);
		L.obj = NIL;
		L.res = -1;
		(*F->handle)((void*)F, (void*)&L, Objects_LinkMsg__typ);
		if ((L.obj != NIL && __ISP(L.obj, Texts_TextDesc, 1))) {
			T = __GUARDP(L.obj, Texts_TextDesc, 1);
		}
	}
	return T;
}

void Oberon_Call (CHAR *name, ADDRESS name__len, Oberon_ParList par, BOOLEAN new, INT16 *res)
{
	Kernel_Module Mod;
	Kernel_Proc P;
	INT32 i, j;
	__DUP(name, name__len, CHAR);
	*res = 1;
	i = 0;
	j = 0;
	while (name[__X(j, name__len)] != 0x00) {
		if (name[__X(j, name__len)] == '.') {
			i = j;
		}
		j += 1;
	}
	if (i == 0) {
		i = j;
		name[__X(j + 1, name__len)] = 0x00;
	}
	name[__X(i, name__len)] = 0x00;
	if (new) {
		Modules_Free(name, name__len, 0);
		if (Modules_res == 0 || Modules_res == 6) {
			Mod = Modules_ThisMod(name, name__len);
		}
	} else {
		Mod = Modules_ThisMod(name, name__len);
	}
	if (Modules_res == 0) {
		i += 1;
		j = i;
		while (name[__X(j, name__len)] != 0x00) {
			name[__X(j - i, name__len)] = name[__X(j, name__len)];
			j += 1;
		}
		name[__X(j - i, name__len)] = 0x00;
		P = Modules_ThisCommand(Mod, name, name__len);
		if (Modules_res == 0) {
			Oberon_Par = par;
			if (par->frame != NIL) {
			}
			(*P)();
			*res = 0;
		} else {
			*res = Modules_res;
		}
	} else {
		*res = Modules_res;
	}
	__DEL(name);
}

void Oberon_GetSelection (Texts_Text *text, INT32 *beg, INT32 *end, INT32 *time)
{
	Oberon_SelectMsg M;
	M.F = NIL;
	M.id = 0;
	M.time = -1;
	M.text = NIL;
	(*Display_Broadcast)((void*)&M, Oberon_SelectMsg__typ);
	*text = M.text;
	*beg = M.beg;
	*end = M.end;
	*time = M.time;
}

void Oberon_Collect (void)
{
	Kernel_GC();
}

static void Oberon_SkipGroup (Texts_Scanner *S, ADDRESS *S__typ)
{
	INT16 openBraces;
	openBraces = 1;
	do {
		Texts_Scan(&*S, S__typ);
		if ((*S).class == 6) {
			if ((*S).c == '{') {
				openBraces += 1;
			} else if ((*S).c == '}') {
				openBraces -= 1;
			}
		}
	} while (!((*S).eot || openBraces == 0));
}

void Oberon_OpenScanner (Texts_Scanner *S, ADDRESS *S__typ, CHAR *name, ADDRESS name__len)
{
	INT16 i, j;
	BOOLEAN done, eos;
	CHAR part[32];
	OFS_File f;
	INT32 t, d;
	__DUP(name, name__len, CHAR);
	f = Files_Old((CHAR*)"Oberon.Text", 12);
	if (f == NIL) {
		t = 0;
		d = 0;
	} else {
		Files_GetDate(f, &t, &d);
	}
	if (t != Oberon_conftime || d != Oberon_confdate) {
		Oberon_conftime = t;
		Oberon_confdate = d;
		Texts_Open(Oberon_conftext, (CHAR*)"Oberon.Text", 12);
	}
	Texts_OpenScanner(&*S, S__typ, Oberon_conftext, 0);
	Texts_Scan(&*S, S__typ);
	done = 1;
	while ((((name[0] != 0x00 && !(*S).eot)) && done)) {
		i = 0;
		while ((name[__X(i, name__len)] != 0x00 && name[__X(i, name__len)] != '.')) {
			part[__X(i, 32)] = name[__X(i, name__len)];
			i += 1;
		}
		part[__X(i, 32)] = 0x00;
		if (name[__X(i, name__len)] == '.') {
			i += 1;
		}
		j = 0;
		while (name[__X(i, name__len)] != 0x00) {
			name[__X(j, name__len)] = name[__X(i, name__len)];
			i += 1;
			j += 1;
		}
		name[__X(j, name__len)] = 0x00;
		done = 0;
		eos = 0;
		do {
			if (__IN((*S).class, 0x06, 32)) {
				Texts_Scan(&*S, S__typ);
				if (!(*S).eot) {
					if (((*S).class == 6 && (*S).c == '=')) {
						if (__STRCMP((*S).s, part) == 0) {
							Texts_Scan(&*S, S__typ);
							if ((((!(*S).eot && (*S).class == 6)) && (*S).c == '{')) {
								Texts_Scan(&*S, S__typ);
							}
							done = 1;
						} else {
							Texts_Scan(&*S, S__typ);
							if ((((!(*S).eot && (*S).class == 6)) && (*S).c == '{')) {
								Oberon_SkipGroup(&*S, S__typ);
							}
							if (!(*S).eot) {
								Texts_Scan(&*S, S__typ);
							} else {
								eos = 1;
							}
						}
					} else {
						eos = 1;
					}
				} else {
					eos = 1;
				}
			} else if (((*S).class == 6 && (*S).c == '{')) {
				Oberon_SkipGroup(&*S, S__typ);
				if (!(*S).eot) {
					Texts_Scan(&*S, S__typ);
				} else {
					eos = 1;
				}
			} else {
				eos = 1;
			}
		} while (!(done || eos));
	}
	if (!done || Oberon_conftext->len == 0) {
		(*S).class = 0;
	}
	__DEL(name);
}

static void Oberon_Init (void)
{
	CHAR s[8];
	Kernel_GetConfig((CHAR*)"Color", 6, (void*)s, 8);
	if (s[0] != '0') {
		Oberon_FillerColor = 12;
	} else {
		Oberon_FillerColor = 0;
	}
	Kernel_GetConfig((CHAR*)"MB", 3, (void*)s, 8);
	Oberon_New = __STRCMP(s, "3") != 0;
}

static void EnumPtrs(void (*P)(void*))
{
	P(Oberon_Log);
	P(Oberon_Par);
	P(Oberon_CurFnt);
	P(Oberon_CurTask);
	P(Oberon_NextTask);
	P(Oberon_GCTask);
	P(Oberon_PalTab);
	P(Oberon_conftext);
}

__TDESC(Oberon_Marker, 1, 0) = {__TDFLDS("Marker", 8), {-4}};
__TDESC(Oberon_Cursor, 1, 0) = {__TDFLDS("Cursor", 16), {-4}};
__TDESC(Oberon_ParRec, 1, 3) = {__TDFLDS("ParRec", 16), {0, 4, 8, -16}};
__TDESC(Oberon_ControlMsg, 1, 2) = {__TDFLDS("ControlMsg", 24), {4, 8, -12}};
__TDESC(Oberon_InputMsg, 1, 3) = {__TDFLDS("InputMsg", 40), {4, 8, 32, -16}};
__TDESC(Oberon_CaretMsg, 1, 4) = {__TDFLDS("CaretMsg", 32), {4, 8, 20, 24, -20}};
__TDESC(Oberon_SelectMsg, 1, 4) = {__TDFLDS("SelectMsg", 40), {4, 8, 24, 28, -20}};
__TDESC(Oberon_ConsumeMsg, 1, 3) = {__TDFLDS("ConsumeMsg", 32), {4, 8, 20, -16}};
__TDESC(Oberon_RecallMsg, 1, 2) = {__TDFLDS("RecallMsg", 20), {4, 8, -12}};
__TDESC(Oberon_TaskDesc, 1, 1) = {__TDFLDS("TaskDesc", 16), {0, -8}};

export void *Oberon__init(void)
{
	__DEFMOD;
	__MODULE_IMPORT(Display);
	__MODULE_IMPORT(Files);
	__MODULE_IMPORT(Fonts);
	__MODULE_IMPORT(Kernel);
	__MODULE_IMPORT(Modules);
	__MODULE_IMPORT(Objects);
	__MODULE_IMPORT(Texts);
	__REGMOD("Oberon", EnumPtrs);
	__REGCMD("Collect", Oberon_Collect);
	__INITYP(Oberon_Marker, Oberon_Marker, 0);
	__INITYP(Oberon_Cursor, Oberon_Cursor, 0);
	__INITYP(Oberon_ParRec, Oberon_ParRec, 0);
	__INITYP(Oberon_ControlMsg, Display_FrameMsg, 2);
	__INITYP(Oberon_InputMsg, Display_FrameMsg, 2);
	__INITYP(Oberon_CaretMsg, Display_FrameMsg, 2);
	__INITYP(Oberon_SelectMsg, Display_FrameMsg, 2);
	__INITYP(Oberon_ConsumeMsg, Display_FrameMsg, 2);
	__INITYP(Oberon_RecallMsg, Display_FrameMsg, 2);
	__INITYP(Oberon_TaskDesc, Oberon_TaskDesc, 0);
/* BEGIN */
	Oberon_Init();
	Oberon_OptionChar = '\\';
	Oberon_OpenText = NIL;
	Oberon_CurTask = NIL;
	Oberon_Arrow.Fade = Oberon_FlipArrow;
	Oberon_Arrow.Draw = Oberon_FlipArrow;
	Oberon_Star.Fade = Oberon_FlipStar;
	Oberon_Star.Draw = Oberon_FlipStar;
	Oberon_H3 = Oberon_DH - __DIV(Oberon_DH, 3);
	Oberon_H2 = Oberon_H3 - __ASHR(Oberon_H3, 1);
	Oberon_H1 = __DIV(Oberon_DH, 5);
	Oberon_H0 = __DIV(Oberon_DH, 10);
	Oberon_W0 = __ASHR(Oberon_DW, 3) * 5;
	if (Oberon_W0 < 400) {
		Oberon_W0 = 0;
	}
	Fonts_Default = Fonts_This((CHAR*)"Oberon10.Scn.Fnt", 17);
	Oberon_CurFnt = Fonts_Default;
	Oberon_CurCol = 15;
	Oberon_CurOff = 0;
	Oberon_conftime = -1;
	Oberon_confdate = -1;
	__NEW(Oberon_conftext, Texts_TextDesc);
	__ENDMOD;
}
