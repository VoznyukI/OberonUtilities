/* voc 2.1.0 [2017/09/06]. Bootstrapping compiler for address size 8, alignment 8. xtaSv */

#define SHORTINT INT8
#define INTEGER  INT16
#define LONGINT  INT32
#define SET      UINT32

#include "SYSTEM.h"
#include "Files.h"
#include "Fonts.h"
#include "Oberon.h"
#include "Texts.h"

struct OPM__1 {
	INT32 L, H;
};


export REAL OPM_MinReal, OPM_MaxReal;
export LONGREAL OPM_MinLReal, OPM_MaxLReal;
export BOOLEAN OPM_noerr;
export INT32 OPM_curpos, OPM_errpos, OPM_breakpos, OPM_breakpc;
static UINT32 OPM_errors[29];
export CHAR OPM_outputPath[32];
export CHAR OPM_outputPrefix[32];
export UINT32 OPM_codeOptions, OPM_parserOptions;
export CHAR OPM_errName[32];
static BOOLEAN OPM_first;
export CHAR OPM_extension[8];
static struct OPM__1 OPM_LRealPat;
static INT32 OPM_lastpos, OPM_pat, OPM_refpatch;
static Texts_Reader OPM_inR;
static Texts_Text OPM_Log;
static Texts_Writer OPM_W;
static OFS_Rider OPM_oldSymF, OPM_newSymF, OPM_ObjF, OPM_RefF, OPM_ModF;
static OFS_File OPM_RefFile, OPM_ObjFile, OPM_ModFile, OPM_oldSymFile, OPM_newSymFile;

export ADDRESS *OPM__1__typ;

export void OPM_Begin (CHAR *modName, ADDRESS modName__len);
export void OPM_Close (void);
export void OPM_CloseObj (void);
static void OPM_Commit (OFS_File F);
export void OPM_EndObj (void);
export void OPM_EndSym (void);
static void OPM_ErrorMsg (INT16 n);
export void OPM_FPrint (INT32 *fp, INT32 val);
export void OPM_FPrintLReal (INT32 *fp, LONGREAL lr);
export void OPM_FPrintReal (INT32 *fp, REAL real);
export void OPM_FPrintSet (INT32 *fp, UINT32 set);
export void OPM_Get (CHAR *ch);
export void OPM_Init (UINT32 codeOpt, UINT32 parserOpt, Texts_Reader source, Texts_Text log);
export void OPM_LogW (CHAR ch);
export void OPM_LogWHex (INT32 i);
export void OPM_LogWLn (void);
export void OPM_LogWNum (INT32 i, INT32 len);
export void OPM_LogWStr (CHAR *s, ADDRESS s__len);
static void OPM_MakeFileName (CHAR *path, ADDRESS path__len, CHAR *prefix, ADDRESS prefix__len, CHAR *modName, ADDRESS modName__len, CHAR *fileName, ADDRESS fileName__len, CHAR *ext, ADDRESS ext__len);
export void OPM_Mark (INT16 n, INT32 pos);
export INT32 OPM_ObjAllocInt (void);
export void OPM_ObjFillInt (INT32 pos, INT16 int_);
export void OPM_ObjW (CHAR ch);
export void OPM_ObjWBytes (SYSTEM_BYTE *bytes, ADDRESS bytes__len, INT32 n);
export void OPM_ObjWInt (INT16 i);
export void OPM_ObjWLInt (INT32 i);
export void OPM_ObjWNum (INT32 i);
export void OPM_ObjWString (CHAR *s, ADDRESS s__len);
export void OPM_OpenSym (OFS_Rider *R, ADDRESS *R__typ, CHAR *name, ADDRESS name__len, BOOLEAN self, BOOLEAN *done);
export void OPM_RefW (CHAR ch);
export void OPM_RefWNum (INT32 i);
export void OPM_SymW (CHAR b);
export void OPM_SymWCh (CHAR ch);
export void OPM_SymWInt (INT32 k);
export void OPM_SymWLInt (INT32 k);
export void OPM_SymWLReal (LONGREAL lr);
export void OPM_SymWMod (CHAR *name, ADDRESS name__len);
export void OPM_SymWNum (INT32 i);
export INT32 OPM_SymWPos (void);
export void OPM_SymWReal (REAL r);
export void OPM_SymWSet (UINT32 s);
export void OPM_SymWString (CHAR *s, ADDRESS s__len);
export void OPM_SymWTag (INT16 k);
static void OPM_WString (OFS_Rider *R, ADDRESS *R__typ, CHAR *s, ADDRESS s__len);
export void OPM_err (INT16 n);


void OPM_Init (UINT32 codeOpt, UINT32 parserOpt, Texts_Reader source, Texts_Text log)
{
	INT8 i;
	OPM_inR = source;
	OPM_Log = log;
	OPM_codeOptions = codeOpt;
	OPM_parserOptions = parserOpt;
	OPM_noerr = 1;
	OPM_curpos = Texts_Pos(&OPM_inR, Texts_Reader__typ);
	OPM_errpos = OPM_curpos;
	OPM_lastpos = OPM_curpos - 10;
	i = 0;
	while (i <= 28) {
		OPM_errors[__X(i, 29)] = 0x0;
		i += 1;
	}
	Oberon_Collect();
}

void OPM_Close (void)
{
	Files_Set(&OPM_oldSymF, OFS_Rider__typ, NIL, 0);
	Files_Set(&OPM_newSymF, OFS_Rider__typ, NIL, 0);
	Files_Set(&OPM_ObjF, OFS_Rider__typ, NIL, 0);
	Files_Set(&OPM_RefF, OFS_Rider__typ, NIL, 0);
	OPM_oldSymFile = NIL;
	OPM_newSymFile = NIL;
	OPM_ObjFile = NIL;
	OPM_RefFile = NIL;
}

void OPM_Get (CHAR *ch)
{
	do {
		Texts_Read(&OPM_inR, Texts_Reader__typ, &*ch);
		OPM_curpos += 1;
	} while (!(OPM_inR.eot || (OPM_inR.lib != NIL && __ISP(OPM_inR.lib, Fonts_FontDesc, 1))));
}

static void OPM_MakeFileName (CHAR *path, ADDRESS path__len, CHAR *prefix, ADDRESS prefix__len, CHAR *modName, ADDRESS modName__len, CHAR *fileName, ADDRESS fileName__len, CHAR *ext, ADDRESS ext__len)
{
	INT16 i, j;
	CHAR ch;
	__DUP(ext, ext__len, CHAR);
	i = 0;
	ch = path[0];
	while (ch != 0x00) {
		fileName[__X(i, fileName__len)] = ch;
		i += 1;
		ch = path[__X(i, path__len)];
	}
	j = 0;
	ch = prefix[0];
	while (ch != 0x00) {
		fileName[__X(i, fileName__len)] = ch;
		i += 1;
		j += 1;
		ch = prefix[__X(j, prefix__len)];
	}
	j = 0;
	ch = modName[0];
	while (ch != 0x00) {
		fileName[__X(i, fileName__len)] = ch;
		i += 1;
		j += 1;
		ch = modName[__X(j, modName__len)];
	}
	j = -1;
	do {
		j += 1;
		fileName[__X(i, fileName__len)] = ext[__X(j, ext__len)];
		i += 1;
	} while (!(ext[__X(j, ext__len)] == 0x00));
	__DEL(ext);
}

void OPM_FPrint (INT32 *fp, INT32 val)
{
	*fp = (INT32)((UINT32)__ROTL(*fp, 7, 32) ^ (UINT32)val);
}

void OPM_FPrintSet (INT32 *fp, UINT32 set)
{
	OPM_FPrint(&*fp, (INT32)set);
}

void OPM_FPrintReal (INT32 *fp, REAL real)
{
	OPM_FPrint(&*fp, __VAL(INT32, real));
}

void OPM_FPrintLReal (INT32 *fp, LONGREAL lr)
{
	INT32 l, h;
	__GET((ADDRESS)&lr + 4, l, INT32);
	__GET((ADDRESS)&lr, h, INT32);
	OPM_FPrint(&*fp, l);
	OPM_FPrint(&*fp, h);
}

static void OPM_WString (OFS_Rider *R, ADDRESS *R__typ, CHAR *s, ADDRESS s__len)
{
	INT16 i;
	CHAR ch;
	i = 0;
	ch = s[__X(i, s__len)];
	if (ch == 0x00) {
		Files_Write(&*R, R__typ, 0x00);
		return;
	}
	while ((ch != 0x00 && ch < 0x7f)) {
		i += 1;
		ch = s[__X(i, s__len)];
	}
	if (i > 1) {
		Files_WriteBytes(&*R, R__typ, (void*)s, s__len * 1, i - 1);
	}
	if (ch == 0x00) {
		Files_Write(&*R, R__typ, (CHAR)((INT16)s[__X(i - 1, s__len)] + 128));
	} else {
		if (i > 0) {
			Files_Write(&*R, R__typ, s[__X(i - 1, s__len)]);
		}
		Files_Write(&*R, R__typ, 0x7f);
		do {
			Files_Write(&*R, R__typ, ch);
			i += 1;
			ch = s[__X(i, s__len)];
		} while (!(ch == 0x00));
		Files_Write(&*R, R__typ, 0x00);
	}
}

void OPM_LogW (CHAR ch)
{
	Texts_Write(&OPM_W, Texts_Writer__typ, ch);
	Texts_Append(OPM_Log, OPM_W.buf);
}

void OPM_LogWStr (CHAR *s, ADDRESS s__len)
{
	__DUP(s, s__len, CHAR);
	Texts_WriteString(&OPM_W, Texts_Writer__typ, s, s__len);
	Texts_Append(OPM_Log, OPM_W.buf);
	__DEL(s);
}

void OPM_LogWNum (INT32 i, INT32 len)
{
	Texts_WriteInt(&OPM_W, Texts_Writer__typ, i, len);
	Texts_Append(OPM_Log, OPM_W.buf);
}

void OPM_LogWHex (INT32 i)
{
	Texts_WriteHex(&OPM_W, Texts_Writer__typ, i);
	Texts_Write(&OPM_W, Texts_Writer__typ, 'H');
	Texts_Append(OPM_Log, OPM_W.buf);
}

void OPM_LogWLn (void)
{
	Texts_WriteLn(&OPM_W, Texts_Writer__typ);
	Texts_Append(OPM_Log, OPM_W.buf);
}

static void OPM_ErrorMsg (INT16 n)
{
	Texts_Scanner s;
	CHAR ch;
	CHAR e[127];
	INT8 i;
	if (n >= 928 || !__IN(__MASK(n, -32), OPM_errors[__X(__ASHR(n, 5), 29)], 32)) {
		if (n < 928) {
			OPM_errors[__X(__ASHR(n, 5), 29)] |= __SETOF(__MASK(n, -32),32);
		}
		Oberon_OpenScanner(&s, Texts_Scanner__typ, (CHAR*)"OP2.Errors", 11);
		if (s.class != 0) {
			do {
				Texts_Scan(&s, Texts_Scanner__typ);
			} while (!(s.eot || (s.class == 3 && s.i == 0)));
			while ((!s.eot && (s.class != 3 || s.i != n))) {
				Texts_Scan(&s, Texts_Scanner__typ);
			}
			if (!s.eot) {
				Texts_Read((void*)&s, Texts_Scanner__typ, &ch);
				Texts_Write(&OPM_W, Texts_Writer__typ, 0x09);
				i = 0;
				while ((!s.eot && ch != 0x0d)) {
					e[__X(i, 127)] = ch;
					i += 1;
					Texts_Read((void*)&s, Texts_Scanner__typ, &ch);
				}
				e[__X(i, 127)] = 0x00;
				OPM_LogWStr(e, 127);
			}
		} else {
			if (OPM_first) {
				OPM_LogWStr((CHAR*)"Oberon.Text - OP2.Errors not found", 35);
				OPM_LogWLn();
				OPM_first = 0;
			}
		}
	}
}

void OPM_Mark (INT16 n, INT32 pos)
{
	if (n >= 0) {
		OPM_noerr = 0;
		if (((pos < OPM_lastpos || OPM_lastpos + 9 < pos) || (n >= 450 && n <= 460)) || n == 155) {
			OPM_lastpos = pos;
			OPM_LogWLn();
			OPM_LogW(0x09);
			OPM_LogW(0x09);
			if (n < 450 || n > 460) {
				OPM_LogWStr((CHAR*)"pos", 4);
				OPM_LogWNum(pos, 7);
				if (n == 255) {
					OPM_LogWStr((CHAR*)"  pc ", 6);
					OPM_LogWHex(OPM_breakpc);
					OPM_breakpos = pos;
				} else if (n == 254) {
					OPM_LogWStr((CHAR*)"  pc not found", 15);
				} else {
					OPM_LogWStr((CHAR*)"  err", 6);
					OPM_LogWNum(n, 4);
					OPM_ErrorMsg(n);
				}
			} else {
				OPM_LogWStr(OPM_errName, 32);
				if (n == 450) {
					OPM_LogWStr((CHAR*)" is no longer visible", 22);
				} else if (n == 451) {
					OPM_LogWStr((CHAR*)" is new", 8);
				} else if (n == 452) {
					OPM_LogWStr((CHAR*)" is redefined", 14);
				}
			}
		}
	} else if (__IN(12, OPM_parserOptions, 32)) {
		OPM_LogWLn();
		OPM_LogW(0x09);
		OPM_LogW(0x09);
		OPM_LogWStr((CHAR*)"pos", 4);
		OPM_LogWNum(pos, 7);
		OPM_LogWStr((CHAR*)"  warning", 10);
		OPM_LogWNum(-n, 4);
		OPM_ErrorMsg(-n);
	}
}

void OPM_err (INT16 n)
{
	OPM_Mark(n, OPM_errpos);
}

void OPM_SymW (CHAR b)
{
	Files_Write(&OPM_newSymF, OFS_Rider__typ, b);
}

void OPM_SymWCh (CHAR ch)
{
	Files_Write(&OPM_newSymF, OFS_Rider__typ, ch);
}

void OPM_SymWTag (INT16 k)
{
	Files_Write(&OPM_newSymF, OFS_Rider__typ, (CHAR)k);
}

void OPM_SymWInt (INT32 k)
{
	Files_WriteInt(&OPM_newSymF, OFS_Rider__typ, (INT16)k);
}

void OPM_SymWLInt (INT32 k)
{
	Files_WriteLInt(&OPM_newSymF, OFS_Rider__typ, k);
}

void OPM_SymWNum (INT32 i)
{
	Files_WriteNum(&OPM_newSymF, OFS_Rider__typ, i);
}

INT32 OPM_SymWPos (void)
{
	return Files_Pos(&OPM_newSymF, OFS_Rider__typ) + Files_Pos(&OPM_ModF, OFS_Rider__typ);
}

void OPM_SymWMod (CHAR *name, ADDRESS name__len)
{
	OPM_WString(&OPM_ModF, OFS_Rider__typ, (void*)name, name__len);
}

void OPM_SymWSet (UINT32 s)
{
	Files_WriteNum(&OPM_newSymF, OFS_Rider__typ, (INT32)s);
}

void OPM_SymWReal (REAL r)
{
	Files_WriteReal(&OPM_newSymF, OFS_Rider__typ, r);
}

void OPM_SymWLReal (LONGREAL lr)
{
	Files_WriteLReal(&OPM_newSymF, OFS_Rider__typ, lr);
}

void OPM_SymWString (CHAR *s, ADDRESS s__len)
{
	OPM_WString(&OPM_newSymF, OFS_Rider__typ, (void*)s, s__len);
}

void OPM_RefW (CHAR ch)
{
	Files_Write(&OPM_RefF, OFS_Rider__typ, ch);
}

void OPM_RefWNum (INT32 i)
{
	Files_WriteNum(&OPM_RefF, OFS_Rider__typ, i);
}

void OPM_ObjW (CHAR ch)
{
	Files_Write(&OPM_ObjF, OFS_Rider__typ, ch);
}

void OPM_ObjWInt (INT16 i)
{
	Files_WriteInt(&OPM_ObjF, OFS_Rider__typ, i);
}

void OPM_ObjWLInt (INT32 i)
{
	Files_WriteLInt(&OPM_ObjF, OFS_Rider__typ, i);
}

void OPM_ObjWBytes (SYSTEM_BYTE *bytes, ADDRESS bytes__len, INT32 n)
{
	Files_WriteBytes(&OPM_ObjF, OFS_Rider__typ, (void*)bytes, bytes__len * 1, n);
}

void OPM_ObjWNum (INT32 i)
{
	Files_WriteNum(&OPM_ObjF, OFS_Rider__typ, i);
}

void OPM_ObjWString (CHAR *s, ADDRESS s__len)
{
	OPM_WString(&OPM_ObjF, OFS_Rider__typ, (void*)s, s__len);
}

INT32 OPM_ObjAllocInt (void)
{
	INT32 pos;
	pos = Files_Pos(&OPM_ObjF, OFS_Rider__typ);
	Files_WriteInt(&OPM_ObjF, OFS_Rider__typ, 0);
	return pos;
}

void OPM_ObjFillInt (INT32 pos, INT16 int_)
{
	INT32 savepos;
	savepos = Files_Pos(&OPM_ObjF, OFS_Rider__typ);
	Files_Set(&OPM_ObjF, OFS_Rider__typ, OPM_ObjFile, pos);
	Files_WriteBytes(&OPM_ObjF, OFS_Rider__typ, (void*)&int_, 2, 2);
	Files_Set(&OPM_ObjF, OFS_Rider__typ, OPM_ObjFile, savepos);
}

void OPM_OpenSym (OFS_Rider *R, ADDRESS *R__typ, CHAR *name, ADDRESS name__len, BOOLEAN self, BOOLEAN *done)
{
	CHAR fileName[512];
	CHAR ch, ch1;
	INT32 symSize;
	OFS_File F;
	CHAR empty[1];
	UINT32 flags;
	empty[0] = 0x00;
	OPM_MakeFileName((void*)OPM_outputPath, 32, (void*)empty, 1, (void*)name, name__len, (void*)fileName, 512, OPM_extension, 8);
	*done = 0;
	F = Files_Old(fileName, 512);
	if (F != NIL) {
		*done = 1;
		Files_Set(&*R, R__typ, F, 0);
		Files_Read(&*R, R__typ, (void*)&ch);
		if (ch == 0xbb) {
			Files_Read(&*R, R__typ, (void*)&ch1);
			Files_ReadNum(&*R, R__typ, &symSize);
			if (ch1 == 0xb0) {
				Files_ReadSet(&*R, R__typ, &flags);
				if (__IN(30, flags, 32)) {
					OPM_err(151);
					*done = 0;
				}
			} else if (ch1 != 0xaf) {
				OPM_err(151);
				*done = 0;
			}
		} else {
			*done = 0;
		}
	}
}

void OPM_Begin (CHAR *modName, ADDRESS modName__len)
{
	CHAR ObjFName[512];
	OPM_MakeFileName((void*)OPM_outputPath, 32, (void*)OPM_outputPrefix, 32, (void*)modName, modName__len, (void*)ObjFName, 512, OPM_extension, 8);
	OPM_ObjFile = Files_New(ObjFName, 512);
	if (OPM_ObjFile == NIL) {
		OPM_err(153);
		return;
	}
	Files_Set(&OPM_ObjF, OFS_Rider__typ, OPM_ObjFile, 0);
	Files_Write(&OPM_ObjF, OFS_Rider__typ, 0xbb);
	OPM_ModFile = Files_New((CHAR*)"", 1);
	Files_Set(&OPM_ModF, OFS_Rider__typ, OPM_ModFile, 0);
	OPM_newSymFile = Files_New((CHAR*)"", 1);
	Files_Set(&OPM_newSymF, OFS_Rider__typ, OPM_newSymFile, 0);
	OPM_RefFile = Files_New((CHAR*)"", 1);
	Files_Set(&OPM_RefF, OFS_Rider__typ, OPM_RefFile, 0);
	Files_Write(&OPM_ObjF, OFS_Rider__typ, 0xaf);
}

static void OPM_Commit (OFS_File F)
{
	CHAR ch;
	OFS_Rider R;
	Files_Set(&R, OFS_Rider__typ, F, 0);
	Files_Read(&R, OFS_Rider__typ, (void*)&ch);
	while (!R.eof) {
		Files_Write(&OPM_ObjF, OFS_Rider__typ, ch);
		Files_Read(&R, OFS_Rider__typ, (void*)&ch);
	}
}

void OPM_EndSym (void)
{
	INT32 sfsize;
	Files_Write(&OPM_ModF, OFS_Rider__typ, 0x00);
	sfsize = Files_Length(OPM_newSymFile) + Files_Length(OPM_ModFile);
	Files_WriteNum(&OPM_ObjF, OFS_Rider__typ, sfsize);
	OPM_Commit(OPM_ModFile);
	OPM_Commit(OPM_newSymFile);
	OPM_refpatch = Files_Pos(&OPM_ObjF, OFS_Rider__typ);
	OPM_ObjWInt(0);
	OPM_ObjWInt(0);
}

void OPM_EndObj (void)
{
	INT32 refsize;
	refsize = Files_Length(OPM_RefFile);
	OPM_ObjW(0x8d);
	OPM_Commit(OPM_RefFile);
	Files_Set(&OPM_ObjF, OFS_Rider__typ, OPM_ObjFile, OPM_refpatch);
	OPM_ObjWBytes((void*)&refsize, 4, 4);
	Files_Register(OPM_ObjFile);
}

void OPM_CloseObj (void)
{
	INT32 refsize;
	CHAR ch;
	OFS_Rider ref;
	refsize = Files_Length(OPM_RefFile);
	Files_Set(&ref, OFS_Rider__typ, OPM_RefFile, 0);
	Files_Read(&ref, OFS_Rider__typ, (void*)&ch);
	while (!ref.eof) {
		OPM_ObjW(ch);
		Files_Read(&ref, OFS_Rider__typ, (void*)&ch);
	}
	Files_Set(&OPM_ObjF, OFS_Rider__typ, OPM_ObjFile, OPM_refpatch);
	OPM_ObjWBytes((void*)&refsize, 4, 4);
	Files_Register(OPM_ObjFile);
}

static void EnumPtrs(void (*P)(void*))
{
	__ENUMR(&OPM_inR, Texts_Reader__typ, 128, 1, P);
	P(OPM_Log);
	__ENUMR(&OPM_W, Texts_Writer__typ, 40, 1, P);
	__ENUMR(&OPM_oldSymF, OFS_Rider__typ, 28, 1, P);
	__ENUMR(&OPM_newSymF, OFS_Rider__typ, 28, 1, P);
	__ENUMR(&OPM_ObjF, OFS_Rider__typ, 28, 1, P);
	__ENUMR(&OPM_RefF, OFS_Rider__typ, 28, 1, P);
	__ENUMR(&OPM_ModF, OFS_Rider__typ, 28, 1, P);
	P(OPM_RefFile);
	P(OPM_ObjFile);
	P(OPM_ModFile);
	P(OPM_oldSymFile);
	P(OPM_newSymFile);
}

__TDESC(OPM__1, 1, 0) = {__TDFLDS("", 8), {-4}};

export void *OPM__init(void)
{
	__DEFMOD;
	__MODULE_IMPORT(Files);
	__MODULE_IMPORT(Fonts);
	__MODULE_IMPORT(Oberon);
	__MODULE_IMPORT(Texts);
	__REGMOD("OPM", EnumPtrs);
	__REGCMD("Close", OPM_Close);
	__REGCMD("CloseObj", OPM_CloseObj);
	__REGCMD("EndObj", OPM_EndObj);
	__REGCMD("EndSym", OPM_EndSym);
	__REGCMD("LogWLn", OPM_LogWLn);
	__INITYP(OPM__1, OPM__1, 0);
/* BEGIN */
	OPM_pat = 4286578687LL;
	__MOVE((ADDRESS)&OPM_pat, (ADDRESS)&OPM_MinReal, 4);
	OPM_pat = 2139095039;
	__MOVE((ADDRESS)&OPM_pat, (ADDRESS)&OPM_MaxReal, 4);
	OPM_LRealPat.L = 4294967295LL;
	OPM_LRealPat.H = 4293918719LL;
	__MOVE((ADDRESS)&OPM_LRealPat, (ADDRESS)&OPM_MinLReal, 8);
	OPM_LRealPat.L = 4294967295LL;
	OPM_LRealPat.H = 2146435071;
	__MOVE((ADDRESS)&OPM_LRealPat, (ADDRESS)&OPM_MaxLReal, 8);
	Texts_OpenWriter(&OPM_W, Texts_Writer__typ);
	OPM_Log = Oberon_Log;
	OPM_outputPath[0] = 0x00;
	OPM_outputPrefix[0] = 0x00;
	OPM_first = 1;
	__ENDMOD;
}
