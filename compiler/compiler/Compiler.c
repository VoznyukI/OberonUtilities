/* voc 2.1.0 [2017/09/06]. Bootstrapping compiler for address size 8, alignment 8. xtamSMv */

#define SHORTINT INT8
#define INTEGER  INT16
#define LONGINT  INT32
#define SET      UINT32

#include "SYSTEM.h"
#include "Display.h"
#include "Modules.h"
#include "OPB.h"
#include "OPC.h"
#include "OPL.h"
#include "OPM.h"
#include "OPO.h"
#include "OPP.h"
#include "OPS.h"
#include "OPT.h"
#include "OPV.h"
#include "Oberon.h"
#include "Texts.h"

#include <stdio.h>

static Texts_Writer Compiler_W;


export void Compiler_Compile (CHAR *file_name, ADDRESS name__len, CHAR *options_name, ADDRESS options__len);
export void Compiler_CompileFile (CHAR *name, ADDRESS name__len, CHAR *opt, ADDRESS opt__len, BOOLEAN *error);
static void Compiler_CompileText (Texts_Text t, INT32 pos, Display_Frame frame, CHAR *opt, ADDRESS opt__len, BOOLEAN *error);
static INT32 Compiler_GetBreakPC (void);
static void Compiler_GetOptions (Texts_Scanner *S, ADDRESS *S__typ, CHAR *opts, ADDRESS opts__len);
static BOOLEAN Compiler_InOptions (CHAR *opt, ADDRESS opt__len, CHAR ch);
static void Compiler_Locate (Display_Frame F, Texts_Text T, INT32 pos);
export void Compiler_Module (Texts_Reader source, CHAR *name, ADDRESS name__len, CHAR *options, ADDRESS options__len, INT32 breakpc, Texts_Text log, BOOLEAN *error);
static void Compiler_ParseOptions (CHAR *name, ADDRESS name__len, CHAR *options, ADDRESS options__len, CHAR *path, ADDRESS path__len, CHAR *pref, ADDRESS pref__len, CHAR *extension, ADDRESS extension__len, UINT32 *codeOpt, UINT32 *parserOpt);
static void Compiler_SignOn (void);
static void Compiler_WriteMsg (Texts_Reader source, Texts_Text log);


static void Compiler_SignOn (void)
{
	Texts_WriteString(&Compiler_W, Texts_Writer__typ, (CHAR*)"Oberon Portable Compiler / nw, rc, nm, tk, prk", 47);
	Texts_WriteLn(&Compiler_W, Texts_Writer__typ);
	Texts_WriteString(&Compiler_W, Texts_Writer__typ, OPP_SignOnMessage, 80);
	Texts_WriteLn(&Compiler_W, Texts_Writer__typ);
	Texts_Append(Oberon_Log, Compiler_W.buf);
}

static void Compiler_GetOptions (Texts_Scanner *S, ADDRESS *S__typ, CHAR *opts, ADDRESS opts__len)
{
	INT32 i;
	CHAR ch;
	while (((*S).class == 6 && (*S).c == Oberon_OptionChar)) {
		i = 0;
		while (opts[__X(i, opts__len)] != 0x00) {
			i += 1;
		}
		ch = (*S).nextCh;
		while (ch > ' ') {
			opts[__X(i, opts__len)] = ch;
			i += 1;
			Texts_Read((void*)&*S, S__typ, &ch);
		}
		opts[__X(i, opts__len)] = ' ';
		i += 1;
		opts[__X(i, opts__len)] = 0x00;
		(*S).nextCh = ch;
		Texts_Scan(&*S, S__typ);
	}
}

static BOOLEAN Compiler_InOptions (CHAR *opt, ADDRESS opt__len, CHAR ch)
{
	INT32 i;
	i = 0;
	while ((opt[__X(i, opt__len)] != 0x00 && opt[__X(i, opt__len)] != ch)) {
		if (opt[__X(i, opt__len)] == '.' || opt[__X(i, opt__len)] == 'P') {
			do {
				i += 1;
			} while (!(opt[__X(i, opt__len)] == 0x00 || opt[__X(i, opt__len)] == ' '));
		} else {
			i += 1;
		}
	}
	return opt[__X(i, opt__len)] == ch;
}

static void Compiler_Locate (Display_Frame F, Texts_Text T, INT32 pos)
{
	Oberon_CaretMsg M;
	Oberon_ControlMsg N;
	if (pos < 0) {
		pos = 0;
	} else if (pos > T->len) {
		pos = T->len;
	}
	N.F = NIL;
	N.id = 1;
	Oberon_FadeCursor(&Oberon_Pointer, Oberon_Cursor__typ);
	M.id = 1;
	M.F = F;
	M.car = F;
	M.text = T;
	M.pos = pos;
	(*Display_Broadcast)((void*)&M, Oberon_CaretMsg__typ);
}

static INT32 Compiler_GetBreakPC (void)
{
	Texts_Scanner S;
	Texts_Text t;
	INT32 beg, end, time;
	Oberon_GetSelection(&t, &beg, &end, &time);
	if (time >= 0) {
		Texts_OpenScanner(&S, Texts_Scanner__typ, t, beg);
		Texts_Scan(&S, Texts_Scanner__typ);
		end = S.line;
		while ((S.class != 3 && S.line == end)) {
			Texts_Scan(&S, Texts_Scanner__typ);
		}
	}
	if (time < 0 || S.class != 3) {
		Texts_WriteString(&Compiler_W, Texts_Writer__typ, (CHAR*)"  pc not selected", 18);
		Texts_WriteLn(&Compiler_W, Texts_Writer__typ);
		Texts_Append(Oberon_Log, Compiler_W.buf);
		return -1;
	} else {
		return S.i;
	}
	__RETCHK;
}

static void Compiler_ParseOptions (CHAR *name, ADDRESS name__len, CHAR *options, ADDRESS options__len, CHAR *path, ADDRESS path__len, CHAR *pref, ADDRESS pref__len, CHAR *extension, ADDRESS extension__len, UINT32 *codeOpt, UINT32 *parserOpt)
{
	INT32 i, j, k;
	CHAR ch;
	*codeOpt = 0x100069;
	*parserOpt = 0x0;
	i = 0;
	path[0] = 0x00;
	pref[0] = 0x00;
	__COPY(Modules_extension, extension, extension__len);
	for (;;) {
		ch = options[__X(i, options__len)];
		i += 1;
		if (ch == 0x00) {
			break;
		} else if (ch == 'x') {
			*codeOpt = *codeOpt ^ 0x01;
		} else if (ch == 'v') {
			*codeOpt = *codeOpt ^ 0x02;
		} else if (ch == 't') {
			*codeOpt = *codeOpt ^ 0x08;
		} else if (ch == 'p') {
			*codeOpt = *codeOpt ^ 0x20;
		} else if (ch == 'a') {
			*codeOpt = *codeOpt ^ 0x40;
		} else if (ch == 'z') {
			*codeOpt = *codeOpt ^ 0x100000;
		} else if (ch == 'q') {
			*codeOpt = *codeOpt ^ 0x400000;
		} else if (ch == 's') {
			*parserOpt = *parserOpt ^ 0x0400;
		} else if (ch == 'S') {
			*parserOpt = *parserOpt ^ 0x0100;
		} else if (ch == 'n') {
			*parserOpt = *parserOpt ^ 0x0200;
		} else if (ch == 'e') {
			*parserOpt = *parserOpt ^ 0x0800;
		} else if (ch == 'f') {
			*parserOpt = *parserOpt ^ 0x80;
		} else if (ch == 'w') {
			*parserOpt = *parserOpt ^ 0x1000;
		} else if (ch == 'X') {
			*parserOpt = *parserOpt | 0x040000;
		} else if (ch == '2') {
			*parserOpt = *parserOpt ^ 0x080000;
		} else if (ch == '1') {
			*parserOpt = *parserOpt ^ 0x200000;
		} else if (ch == 'T') {
			*parserOpt = *parserOpt ^ 0x01000000;
		} else if (ch == '.') {
			j = 0;
			while ((ch != 0x00 && ch != ' ')) {
				extension[__X(j, extension__len)] = ch;
				ch = options[__X(i, options__len)];
				j += 1;
				i += 1;
			}
			extension[__X(j, extension__len)] = 0x00;
		} else if (ch == 'P') {
			ch = options[__X(i, options__len)];
			i += 1;
			k = 0;
			while ((ch != 0x00 && ch != ' ')) {
				path[__X(k, path__len)] = ch;
				k += 1;
				ch = options[__X(i, options__len)];
				i += 1;
			}
			path[__X(k, path__len)] = 0x00;
		} else if (ch == 'O') {
			ch = options[__X(i, options__len)];
			i += 1;
			k = 0;
			while ((ch != 0x00 && ch != ' ')) {
				pref[__X(k, pref__len)] = ch;
				k += 1;
				ch = options[__X(i, options__len)];
				i += 1;
			}
			pref[__X(k, pref__len)] = 0x00;
		}
	}
	if (__IN(18, *parserOpt, 32)) {
		i = -1;
		do {
			i += 1;
			pref[__X(i, pref__len)] = name[__X(i, name__len)];
		} while (!(name[__X(i, name__len)] == 0x00 || name[__X(i, name__len)] == '.'));
		if (name[__X(i, name__len)] != '.') {
			i = 0;
		} else {
			i += 1;
		}
		pref[__X(i, pref__len)] = 0x00;
	}
}

static void Compiler_WriteMsg (Texts_Reader source, Texts_Text log)
{
	INT8 sym;
	Texts_WriteString(&Compiler_W, Texts_Writer__typ, (CHAR*)" compiling ", 12);
	OPM_Init(0x0, 0x0, source, log);
	(*OPS_Get)(&sym);
	if (sym == 67) {
		(*OPS_Get)(&sym);
		if (sym == 40) {
			Texts_WriteString(&Compiler_W, Texts_Writer__typ, OPM_outputPath, 32);
			Texts_WriteString(&Compiler_W, Texts_Writer__typ, OPM_outputPrefix, 32);
			(*OPS_Get)(&sym);
			Texts_WriteString(&Compiler_W, Texts_Writer__typ, OPS_name, 32);
			while (sym == 18) {
				Texts_Write(&Compiler_W, Texts_Writer__typ, '.');
				(*OPS_Get)(&sym);
				if (sym == 40) {
					Texts_WriteString(&Compiler_W, Texts_Writer__typ, OPS_name, 32);
					(*OPS_Get)(&sym);
				}
			}
			if (__STRCMP(OPM_extension, Modules_extension) != 0) {
				Texts_WriteString(&Compiler_W, Texts_Writer__typ, OPM_extension, 8);
			} else if ((OPM_outputPath[0] == 0x00 && OPM_outputPrefix[0] == 0x00)) {
				if (Modules_FindMod(OPS_name, 32) != NIL) {
					Texts_WriteString(&Compiler_W, Texts_Writer__typ, (CHAR*)" (in use) ", 11);
				}
			}
		}
	}
	Texts_Append(log, Compiler_W.buf);
}

void Compiler_Module (Texts_Reader source, CHAR *name, ADDRESS name__len, CHAR *options, ADDRESS options__len, INT32 breakpc, Texts_Text log, BOOLEAN *error)
{
	UINT32 codeOpt, parserOpt;
	BOOLEAN extSF, newSF;
	OPT_Node p;
	OPS_Name modName;
	__DUP(name, name__len, CHAR);
	__DUP(options, options__len, CHAR);
	Compiler_ParseOptions((void*)name, name__len, (void*)options, options__len, (void*)OPM_outputPath, 32, (void*)OPM_outputPrefix, 32, (void*)OPM_extension, 8, &codeOpt, &parserOpt);
	Compiler_WriteMsg(source, log);
	OPM_Init(codeOpt, parserOpt, source, log);
	OPS_ch = ' ';
	OPB_typSize = OPV_TypSize;
	OPV_Init(breakpc);
	newSF = __IN(10, parserOpt, 32);
	extSF = __IN(11, parserOpt, 32);
	OPP_Module(&p, modName);
	if (OPM_noerr) {
		OPL_Init();
		OPM_errpos = 0;
		OPM_Begin((void*)modName, 32);
		if (OPM_noerr) {
			OPT_Export(modName, &newSF, &extSF);
			OPV_AdrAndSize(OPT_topScope);
			if (newSF) {
				OPM_LogWStr((CHAR*)" new symbol file", 17);
			} else if (extSF) {
				OPM_LogWStr((CHAR*)" extended symbol file", 22);
			}
			if (OPM_noerr) {
				OPM_errpos = 0;
				OPC_Init();
				OPV_Module(p);
				if (OPM_noerr) {
					OPL_OutCode((void*)modName, 32);
					if (OPM_noerr) {
						OPM_LogWStr((CHAR*)"   ", 4);
						OPM_LogWNum(OPO_pc, 1);
					}
				}
			}
			OPL_Close();
		}
	}
	OPT_CloseScope();
	OPT_Close();
	OPM_LogWLn();
	*error = !OPM_noerr;
	__MOVE("!", OPM_outputPath, 2);
	__MOVE("!", OPM_outputPrefix, 2);
	__DEL(name);
	__DEL(options);
}

static void Compiler_CompileText (Texts_Text t, INT32 pos, Display_Frame frame, CHAR *opt, ADDRESS opt__len, BOOLEAN *error)
{
	BOOLEAN f;
	INT32 pc;
	Texts_Reader r;
	__DUP(opt, opt__len, CHAR);
	if (t != NIL) {
		Texts_OpenReader(&r, Texts_Reader__typ, t, pos);
		f = Compiler_InOptions((void*)opt, opt__len, 'f');
		if (f) {
			pc = Compiler_GetBreakPC();
			if (pc == -1) {
				__DEL(opt);
				return;
			}
		}
		OPS_Init();
		Compiler_Module(r, (CHAR*)"", 1, opt, opt__len, pc, Oberon_Log, &*error);
		if ((f && frame != NIL)) {
			Compiler_Locate(frame, t, OPM_breakpos);
		}
	} else {
		Texts_WriteString(&Compiler_W, Texts_Writer__typ, (CHAR*)"No text marked", 15);
		Texts_WriteLn(&Compiler_W, Texts_Writer__typ);
		Texts_Append(Oberon_Log, Compiler_W.buf);
		*error = 1;
	}
	__DEL(opt);
}

void Compiler_CompileFile (CHAR *name, ADDRESS name__len, CHAR *opt, ADDRESS opt__len, BOOLEAN *error)
{
	Texts_Text t;
	Texts_Reader r;
	INT32 pc;
	__DUP(name, name__len, CHAR);
	__DUP(opt, opt__len, CHAR);
	__NEW(t, Texts_TextDesc);

    pc = 0; //TODO

	Texts_Open(t, name, name__len);
	if (t->len != 0) {
		Texts_OpenReader(&r, Texts_Reader__typ, t, 0);
		if (Compiler_InOptions((void*)opt, opt__len, 'f')) {
			pc = Compiler_GetBreakPC();
			if (pc == -1) {
				__DEL(name);
				__DEL(opt);
				return;
			}
		}
		Texts_WriteString(&Compiler_W, Texts_Writer__typ, name, name__len);
		OPS_Init();
		Compiler_Module(r, name, name__len, opt, opt__len, pc, Oberon_Log, &*error);
	} else {
		Texts_WriteString(&Compiler_W, Texts_Writer__typ, name, name__len);
		Texts_WriteString(&Compiler_W, Texts_Writer__typ, (CHAR*)" not found", 11);
		Texts_WriteLn(&Compiler_W, Texts_Writer__typ);
		Texts_Append(Oberon_Log, Compiler_W.buf);
		*error = 1;
	}
	__DEL(name);
	__DEL(opt);
}

void Compiler_Compile (CHAR *file_name, ADDRESS name__len, CHAR *options_name, ADDRESS options__len)
{
    Texts_Text text;
    Texts_Writer text_W;

	Texts_Scanner S;
	CHAR globalOpt[32], localOpt[32];
	Texts_Text t;
	INT32 pos, end, time;
	Display_Frame frame;
	CHAR name[64];
	BOOLEAN error;
	error = 0;

	__NEW(text, Texts_TextDesc);
	Texts_Open(text, (CHAR*)"", 1);

    Texts_OpenWriter(&text_W, Texts_Writer__typ);

	Texts_WriteString(&text_W, Texts_Writer__typ, file_name, name__len);

    Texts_WriteLn(&text_W, Texts_Writer__typ);

	Texts_Append(text, text_W.buf);

    Texts_OpenScanner( &S, Texts_Scanner__typ, text, 0 );

	Texts_Scan(&S, Texts_Scanner__typ);
	globalOpt[0] = 0x00;
	Compiler_GetOptions(&S, Texts_Scanner__typ, (void*)globalOpt, 32);
	if ((S.class == 6 && (S.c == '*' || S.c == '@'))) {
		if (S.c == '*') {
			t = Oberon_MarkedText();
			pos = 0;
			frame = Oberon_MarkedFrame();
		} else {
			Oberon_GetSelection(&t, &pos, &end, &time);
			frame = NIL;
			if (time < 0) {
				return;
			}
		}
		Texts_Scan(&S, Texts_Scanner__typ);
		Compiler_GetOptions(&S, Texts_Scanner__typ, (void*)globalOpt, 32);
		Compiler_CompileText(t, pos, frame, globalOpt, 32, &error);
	} else if ((S.class == 6 && S.c == '^') || S.class == 1) {
		if (S.c == '^') {
			Oberon_GetSelection(&t, &pos, &end, &time);
			Texts_OpenScanner(&S, Texts_Scanner__typ, t, pos);
			Texts_Scan(&S, Texts_Scanner__typ);
		} else {
			end = 2147483647;
		}
		while ((((S.class == 1 && Texts_Pos((void*)&S, Texts_Scanner__typ) - S.len <= end)) && !error)) {
			__COPY(S.s, name, 64);
			__COPY(globalOpt, localOpt, 32);
			Texts_Scan(&S, Texts_Scanner__typ);
			Compiler_CompileFile(name, 64, options_name, 32, &error);
		}
	}
}

static void EnumPtrs(void (*P)(void*))
{
	__ENUMR(&Compiler_W, Texts_Writer__typ, 40, 1, P);
}


export int main(int argc, char **argv)
{
    char* name; // TODO
    int i;
    char* options;
    int j;
    INT32 len;
    Files_File f;
    CHAR* fname = (CHAR*)"System.Log";

	__INIT(argc, argv);
	__MODULE_IMPORT(Display);
	__MODULE_IMPORT(Modules);
	//__MODULE_IMPORT(OPB);
	//__MODULE_IMPORT(OPC);
	//__MODULE_IMPORT(OPL);
	//__MODULE_IMPORT(OPM);
	//__MODULE_IMPORT(OPO);
	//__MODULE_IMPORT(OPP);
	//__MODULE_IMPORT(OPS);
	//__MODULE_IMPORT(OPT);
	//__MODULE_IMPORT(OPV);
	__MODULE_IMPORT(Oberon);
	__MODULE_IMPORT(Texts);
	__MODULE_IMPORT(OPB);
	__MODULE_IMPORT(OPC);
	__MODULE_IMPORT(OPL);
	__MODULE_IMPORT(OPM);
	__MODULE_IMPORT(OPO);
	__MODULE_IMPORT(OPP);
	__MODULE_IMPORT(OPS);
	__MODULE_IMPORT(OPT);
	__MODULE_IMPORT(OPV);
	__REGMAIN("Compiler", EnumPtrs);
	__REGCMD("Compile", Compiler_Compile);
/* BEGIN */

	Texts_OpenWriter(&Compiler_W, Texts_Writer__typ);
	Compiler_SignOn();

    //TODO

    if ( argc < 2 )
        return;
    
    name = argv[ 1 ];
    for ( i = 0; ; ++i )
    {
        if ( 0 == name[ i ] )
            break;
    }

    j = 0;
    options = "";
    if ( argc > 2 )
    {    
        options = argv[ 2 ];
        for ( j = 0; ; ++j )
        {
            if ( 0 == options[ j ] )
                break;
        }
    }

    printf("Compile file: %s\n", name);

    Compiler_Compile( (CHAR*)name, i + 1, (CHAR*)options, j + 1 );

    //TODO
    f = Files_New( fname, 11);
    Texts_Store( Oberon_Log, f, 0, &len);
    Files_Register(f);

	__FINI;
}
