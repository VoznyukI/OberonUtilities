/* voc 2.1.0 [2017/09/06]. Bootstrapping compiler for address size 8, alignment 8. xtaSv */

#define SHORTINT INT8
#define INTEGER  INT16
#define LONGINT  INT32
#define SET      UINT32

#include "SYSTEM.h"
#include "OPS.h"
#include "OPM.h"

//typedef
//	struct OPS_Tok *OPS_Token;

//typedef
//	struct OPS_Tok {
//		INT32 pos;
//		INT8 sym;
//		OPS_Token next;
//	} OPS_Tok;

struct OPS__1 {
	INT32 pos;
	INT8 sym;
	OPS_Token next;
	INT32 intval;
	INT16 typ;
};

struct OPS__4 {
	INT32 pos;
	INT8 sym;
	OPS_Token next;
	REAL realval;
};

struct OPS__2 {
	INT32 pos;
	INT8 sym;
	OPS_Token next;
	LONGREAL lrlval;
};

//typedef
//	CHAR OPS_String[256];

struct OPS__5 {
	INT32 pos;
	INT8 sym;
	OPS_Token next;
	OPS_String str;
	INT32 len;
};

//typedef
//	CHAR OPS_Name[32];

struct OPS__3 {
	INT32 pos;
	INT8 sym;
	OPS_Token next;
	OPS_Name name;
};

typedef
	void (*OPS_GetProc)(INT8*);

typedef
	struct OPS__1 *OPS_IntToken;

typedef
	struct OPS__2 *OPS_LRealToken;

typedef
	struct OPS__3 *OPS_NameToken;

typedef
	struct OPS__4 *OPS_RealToken;

typedef
	struct OPS__5 *OPS_StrToken;


export OPS_Name OPS_name;
export OPS_String OPS_str;
export INT16 OPS_numtyp;
export INT32 OPS_intval;
export REAL OPS_realval;
export LONGREAL OPS_lrlval;
export OPS_GetProc OPS_Get;
export CHAR OPS_ch;
static OPS_Token OPS_stream, OPS_last;

export ADDRESS *OPS_Tok__typ;
export ADDRESS *OPS__1__typ;
export ADDRESS *OPS__4__typ;
export ADDRESS *OPS__2__typ;
export ADDRESS *OPS__5__typ;
export ADDRESS *OPS__3__typ;

export BOOLEAN OPS_CheckCardinality (OPS_Name name, INT8 nofp);
export void OPS_CheckOperator (INT8 *id);
static void OPS_DefaultGet (INT8 *sym);
static void OPS_Identifier (INT8 *sym);
export void OPS_Init (void);
export void OPS_Number (void);
static void OPS_RecToken (INT8 sym);
export void OPS_StartPlaying (OPS_Token s);
export void OPS_StartRecording (INT8 sym);
export void OPS_StopRecording (OPS_Token *s);
static void OPS_Str (INT8 *sym);
static void OPS_StreamGet (INT8 *sym);
static void OPS_err (INT16 n);


static void OPS_err (INT16 n)
{
	OPM_err(n);
}

static void OPS_StreamGet (INT8 *sym)
{
	if ((OPS_stream != NIL && OPS_stream->next != NIL)) {
		OPS_stream = OPS_stream->next;
		*sym = OPS_stream->sym;
		OPM_errpos = OPS_stream->pos;
		if (__ISP(OPS_stream, OPS__1, 1)) {
			OPS_intval = __GUARDA(OPS_stream, OPS__1, 1)->intval;
			OPS_numtyp = __GUARDA(OPS_stream, OPS__1, 1)->typ;
		} else if (__ISP(OPS_stream, OPS__4, 1)) {
			OPS_realval = __GUARDA(OPS_stream, OPS__4, 1)->realval;
			OPS_numtyp = 3;
		} else if (__ISP(OPS_stream, OPS__2, 1)) {
			OPS_lrlval = __GUARDA(OPS_stream, OPS__2, 1)->lrlval;
			OPS_numtyp = 4;
		} else if (__ISP(OPS_stream, OPS__5, 1)) {
			__MOVE(__GUARDA(OPS_stream, OPS__5, 1)->str, OPS_str, 256);
			OPS_intval = __GUARDA(OPS_stream, OPS__5, 1)->len;
		} else if (__ISP(OPS_stream, OPS__3, 1)) {
			__MOVE(__GUARDA(OPS_stream, OPS__3, 1)->name, OPS_name, 32);
		} else if (((1 <= *sym && *sym <= 17) || *sym == 33) || *sym == 34) {
			__MOVE(__GUARDA(OPS_stream, OPS__3, 1)->name, OPS_name, 32);
		}
	} else {
		*sym = 68;
	}
}

static void OPS_RecToken (INT8 sym)
{
	OPS_Token s;
	OPS_RealToken r;
	OPS_LRealToken lr;
	OPS_IntToken i;
	OPS_StrToken st;
	OPS_NameToken nam;
	if (sym == 35) {
		if (OPS_numtyp == 3) {
			__NEW(r, OPS__4);
			r->realval = OPS_realval;
			s = (OPS_Token)r;
		} else if (OPS_numtyp == 4) {
			__NEW(lr, OPS__2);
			lr->lrlval = OPS_lrlval;
			s = (OPS_Token)lr;
		} else {
			__NEW(i, OPS__1);
			i->intval = OPS_intval;
			i->typ = OPS_numtyp;
			s = (OPS_Token)i;
		}
	} else if (sym == 39) {
		__NEW(st, OPS__5);
		__MOVE(OPS_str, st->str, 256);
		st->len = OPS_intval;
		s = (OPS_Token)st;
	} else if (sym == 40) {
		__NEW(nam, OPS__3);
		__MOVE(OPS_name, nam->name, 32);
		s = (OPS_Token)nam;
	} else if (((1 <= sym && sym <= 17) || sym == 33) || sym == 34) {
		__NEW(nam, OPS__3);
		__MOVE(OPS_name, nam->name, 32);
		s = (OPS_Token)nam;
	} else {
		__NEW(s, OPS_Tok);
	}
	s->pos = OPM_errpos;
	s->sym = sym;
	s->next = OPS_last->next;
	OPS_last->next = s;
	OPS_last = s;
}

void OPS_StartRecording (INT8 sym)
{
	__NEW(OPS_stream, OPS_Tok);
	OPS_last = OPS_stream;
	OPS_RecToken(sym);
}

void OPS_StopRecording (OPS_Token *s)
{
	*s = OPS_stream;
	OPS_stream = NIL;
	OPS_last = NIL;
}

void OPS_StartPlaying (OPS_Token s)
{
	OPS_stream = s;
	OPS_Get = OPS_StreamGet;
}

static void OPS_Str (INT8 *sym)
{
	INT16 i;
	CHAR och;
	i = 0;
	och = OPS_ch;
	for (;;) {
		OPM_Get(&OPS_ch);
		if (OPS_ch == och) {
			break;
		}
		if (OPS_ch < ' ') {
			OPS_err(3);
			break;
		}
		if (i == 255) {
			OPS_err(241);
			break;
		}
		OPS_str[__X(i, 256)] = OPS_ch;
		i += 1;
	}
	OPM_Get(&OPS_ch);
	OPS_str[__X(i, 256)] = 0x00;
	OPS_intval = i + 1;
	if (OPS_intval == 2) {
		*sym = 35;
		OPS_numtyp = 1;
		OPS_intval = (INT16)OPS_str[0];
	} else {
		*sym = 39;
	}
}

static void OPS_Identifier (INT8 *sym)
{
	INT16 i;
	i = 0;
	do {
		OPS_name[__X(i, 32)] = OPS_ch;
		i += 1;
		OPM_Get(&OPS_ch);
	} while (!(((OPS_ch < '0' || ('9' < OPS_ch && __CAP(OPS_ch) < 'A')) || 'Z' < __CAP(OPS_ch)) || i == 32));
	if (i == 32) {
		OPS_err(240);
		i -= 1;
	}
	OPS_name[__X(i, 32)] = 0x00;
	*sym = 40;
}

BOOLEAN OPS_CheckCardinality (OPS_Name name, INT8 nofp)
{
	switch (name[0]) {
		case '+': case '-': 
			return nofp == 1 || nofp == 2;
			break;
		case '~': 
			return (name[1] == 0x00 && nofp == 1);
			break;
		default: 
			return nofp == 2;
			break;
	}
	__RETCHK;
}

void OPS_CheckOperator (INT8 *id)
{
	CHAR ch0, ch1, ch2;
	*id = 126;
	__COPY(OPS_str, OPS_name, 32);
	ch0 = OPS_str[0];
	ch1 = OPS_str[1];
	ch2 = OPS_str[2];
	switch (ch0) {
		case '=': case '#': case '&': 
			if (ch1 == 0x00) {
				return;
			}
			break;
		case '<': case '>': 
			if (ch1 == 0x00 || (ch1 == '=' && ch2 == 0x00)) {
				return;
			}
			break;
		case 'I': 
			if ((ch1 == 'N' && ch2 == 0x00)) {
				return;
			}
			break;
		case 'D': 
			if (__STRCMP(OPS_str, "DIV") == 0) {
				return;
			}
			break;
		case 'M': 
			if (__STRCMP(OPS_str, "MOD") == 0) {
				return;
			}
			break;
		case 'O': 
			if (__STRCMP(OPS_str, "OR") == 0) {
				return;
			}
			break;
		case '+': case '-': case '*': case '/': 
			if (ch1 == 0x00 || (ch2 == 0x00 && ch1 == '*')) {
				return;
			}
			break;
		case '~': 
			if (ch1 == 0x00) {
				return;
			}
			break;
		case ':': 
			if (__STRCMP(OPS_str, ":=") == 0) {
				return;
			}
			break;
		default: 
			break;
	}
	*id = 0;
}

static struct Number__8 {
	struct Number__8 *lnk;
} *Number__8_s;

static INT16 Ord__9 (CHAR ch, BOOLEAN hex);
static LONGREAL Ten__11 (INT16 e);

static LONGREAL Ten__11 (INT16 e)
{
	LONGREAL x, p;
	x = (LONGREAL)1;
	p = (LONGREAL)10;
	while (e > 0) {
		if (__ODD(e)) {
			x = x * p;
		}
		e = __ASHR(e, 1);
		if (e > 0) {
			p = p * p;
		}
	}
	return x;
}

static INT16 Ord__9 (CHAR ch, BOOLEAN hex)
{
	if (ch <= '9') {
		return (INT16)ch - 48;
	} else if (hex) {
		return ((INT16)ch - 65) + 10;
	} else {
		OPS_err(2);
		return 0;
	}
	__RETCHK;
}

void OPS_Number (void)
{
	INT16 i, m, n, d, e;
	CHAR dig[24];
	LONGREAL f;
	CHAR expCh;
	BOOLEAN neg;
	struct Number__8 _s;
	_s.lnk = Number__8_s;
	Number__8_s = &_s;
	i = 0;
	m = 0;
	n = 0;
	d = 0;
	for (;;) {
		if (('0' <= OPS_ch && OPS_ch <= '9') || (((d == 0 && 'A' <= OPS_ch)) && OPS_ch <= 'F')) {
			if (m > 0 || OPS_ch != '0') {
				if (n < 24) {
					dig[__X(n, 24)] = OPS_ch;
					n += 1;
				}
				m += 1;
			}
			OPM_Get(&OPS_ch);
			i += 1;
		} else if (OPS_ch == '.') {
			OPM_Get(&OPS_ch);
			if (OPS_ch == '.') {
				OPS_ch = 0x7f;
				break;
			} else if (d == 0) {
				d = i;
			} else {
				OPS_err(2);
			}
		} else {
			break;
		}
	}
	if (d == 0) {
		if (n == m) {
			OPS_intval = 0;
			i = 0;
			if (OPS_ch == 'X') {
				OPM_Get(&OPS_ch);
				OPS_numtyp = 1;
				if (n <= 2) {
					while (i < n) {
						OPS_intval = __ASHL(OPS_intval, 4) + Ord__9(dig[__X(i, 24)], 1);
						i += 1;
					}
				} else {
					OPS_err(203);
				}
			} else if (OPS_ch == 'H') {
				OPM_Get(&OPS_ch);
				OPS_numtyp = 2;
				if (n <= 8) {
					if ((n == 8 && dig[0] > '7')) {
						OPS_intval = -1;
					}
					while (i < n) {
						OPS_intval = __ASHL(OPS_intval, 4) + Ord__9(dig[__X(i, 24)], 1);
						i += 1;
					}
				} else {
					OPS_err(203);
				}
			} else {
				OPS_numtyp = 2;
				while (i < n) {
					d = Ord__9(dig[__X(i, 24)], 0);
					i += 1;
					if (OPS_intval <= __DIV(2147483647 - d, 10)) {
						OPS_intval = OPS_intval * 10 + d;
					} else {
						OPS_err(203);
					}
				}
			}
		} else {
			OPS_err(203);
		}
	} else {
		f = (LONGREAL)0;
		e = 0;
		expCh = 'E';
		while (n > 0) {
			n -= 1;
			f = (Ord__9(dig[__X(n, 24)], 0) + f) / (LONGREAL)(LONGREAL)10;
		}
		if (OPS_ch == 'E' || OPS_ch == 'D') {
			expCh = OPS_ch;
			OPM_Get(&OPS_ch);
			neg = 0;
			if (OPS_ch == '-') {
				neg = 1;
				OPM_Get(&OPS_ch);
			} else if (OPS_ch == '+') {
				OPM_Get(&OPS_ch);
			}
			if (('0' <= OPS_ch && OPS_ch <= '9')) {
				do {
					n = Ord__9(OPS_ch, 0);
					OPM_Get(&OPS_ch);
					if (e <= __DIV(32767 - n, 10)) {
						e = e * 10 + n;
					} else {
						OPS_err(203);
					}
				} while (!(OPS_ch < '0' || '9' < OPS_ch));
				if (neg) {
					e = -e;
				}
			} else {
				OPS_err(2);
			}
		}
		e -= (i - d) - m;
		if (expCh == 'E') {
			OPS_numtyp = 3;
			if ((-37 < e && e <= 38)) {
				if (e < 0) {
					OPS_realval = (f / (LONGREAL)Ten__11(-e));
				} else {
					OPS_realval = (f * Ten__11(e));
				}
			} else {
				OPS_err(203);
			}
		} else {
			OPS_numtyp = 4;
			if ((-307 < e && e <= 308)) {
				if (e < 0) {
					OPS_lrlval = f / (LONGREAL)Ten__11(-e);
				} else {
					OPS_lrlval = f * Ten__11(e);
				}
			} else {
				OPS_err(203);
			}
		}
	}
	Number__8_s = _s.lnk;
}

static struct DefaultGet__3 {
	struct DefaultGet__3 *lnk;
} *DefaultGet__3_s;

static void Comment__4 (void);

static void Comment__4 (void)
{
	BOOLEAN dump;
	OPM_Get(&OPS_ch);
	if (OPS_ch == '@') {
		dump = 1;
		OPM_LogWLn();
	}
    dump = 1; // TODO
	for (;;) {
		for (;;) {
			while (OPS_ch == '(') {
				OPM_Get(&OPS_ch);
				if (OPS_ch == '*') {
					Comment__4();
				} else if (dump) {
					OPM_LogW('(');
				}
			}
			if (OPS_ch == '*') {
				OPM_Get(&OPS_ch);
				break;
			}
			if (OPS_ch == 0x00) {
				break;
			}
			if (dump) {
				OPM_LogW(OPS_ch);
			}
			OPM_Get(&OPS_ch);
		}
		if (OPS_ch == ')') {
			OPM_Get(&OPS_ch);
			break;
		}
		if (dump) {
			OPM_LogW('*');
		}
		if (OPS_ch == 0x00) {
			OPS_err(5);
			break;
		}
	}
}

static void OPS_DefaultGet (INT8 *sym)
{
	INT8 s;
	struct DefaultGet__3 _s;
	_s.lnk = DefaultGet__3_s;
	DefaultGet__3_s = &_s;
	while (OPS_ch <= ' ') {
		if (OPS_ch == 0x00) {
			*sym = 68;
			DefaultGet__3_s = _s.lnk;
			return;
		} else {
			OPM_Get(&OPS_ch);
		}
	}
	OPM_errpos = OPM_curpos - 1;
	switch (OPS_ch) {
		case '"': case '\'': 
			OPS_Str(&s);
			break;
		case '#': 
			s = 10;
			__MOVE("#", OPS_name, 2);
			OPM_Get(&OPS_ch);
			break;
		case '&': 
			s = 5;
			__MOVE("&", OPS_name, 2);
			OPM_Get(&OPS_ch);
			break;
		case '(': 
			OPM_Get(&OPS_ch);
			if (OPS_ch == '*') {
				Comment__4();
				(*OPS_Get)(&*sym);
				DefaultGet__3_s = _s.lnk;
				return;
			} else {
				s = 30;
			}
			break;
		case ')': 
			s = 22;
			OPM_Get(&OPS_ch);
			break;
		case '*': 
			__MOVE("*", OPS_name, 2);
			s = 1;
			OPM_Get(&OPS_ch);
			break;
		case '+': 
			__MOVE("+", OPS_name, 2);
			s = 6;
			OPM_Get(&OPS_ch);
			break;
		case ',': 
			s = 19;
			OPM_Get(&OPS_ch);
			break;
		case '-': 
			__MOVE("-", OPS_name, 2);
			s = 7;
			OPM_Get(&OPS_ch);
			break;
		case '.': 
			OPM_Get(&OPS_ch);
			if (OPS_ch == '.') {
				OPM_Get(&OPS_ch);
				s = 21;
			} else {
				s = 18;
			}
			break;
		case '/': 
			__MOVE("/", OPS_name, 2);
			OPM_Get(&OPS_ch);
			s = 2;
			break;
		case '0': case '1': case '2': case '3': case '4': 
		case '5': case '6': case '7': case '8': case '9': 
			OPS_Number();
			s = 35;
			break;
		case ':': 
			OPM_Get(&OPS_ch);
			if (OPS_ch == '=') {
				OPM_Get(&OPS_ch);
				s = 34;
				__MOVE(":=", OPS_name, 3);
			} else {
				s = 20;
			}
			break;
		case ';': 
			s = 41;
			OPM_Get(&OPS_ch);
			break;
		case '<': 
			OPM_Get(&OPS_ch);
			if (OPS_ch == '=') {
				OPM_Get(&OPS_ch);
				s = 12;
				__MOVE("<=", OPS_name, 3);
			} else {
				s = 11;
				__MOVE("<", OPS_name, 2);
			}
			break;
		case '=': 
			s = 9;
			__MOVE("=", OPS_name, 2);
			OPM_Get(&OPS_ch);
			break;
		case '>': 
			OPM_Get(&OPS_ch);
			if (OPS_ch == '=') {
				OPM_Get(&OPS_ch);
				s = 14;
				__MOVE(">=", OPS_name, 3);
			} else {
				s = 13;
				__MOVE(">", OPS_name, 2);
			}
			break;
		case 'A': 
			OPS_Identifier(&s);
			if (__STRCMP(OPS_name, "ARRAY") == 0) {
				s = 56;
			}
			break;
		case 'B': 
			OPS_Identifier(&s);
			if (__STRCMP(OPS_name, "BEGIN") == 0) {
				s = 60;
			} else if (__STRCMP(OPS_name, "BY") == 0) {
				s = 29;
			}
			break;
		case 'C': 
			OPS_Identifier(&s);
			if (__STRCMP(OPS_name, "CASE") == 0) {
				s = 48;
			} else if (__STRCMP(OPS_name, "CODE") == 0) {
				s = 61;
			} else if (__STRCMP(OPS_name, "CONST") == 0) {
				s = 62;
			}
			break;
		case 'D': 
			OPS_Identifier(&s);
			if (__STRCMP(OPS_name, "DO") == 0) {
				s = 27;
			} else if (__STRCMP(OPS_name, "DIV") == 0) {
				s = 3;
			}
			break;
		case 'E': 
			OPS_Identifier(&s);
			if (__STRCMP(OPS_name, "END") == 0) {
				s = 43;
			} else if (__STRCMP(OPS_name, "ELSE") == 0) {
				s = 44;
			} else if (__STRCMP(OPS_name, "ELSIF") == 0) {
				s = 45;
			} else if (__STRCMP(OPS_name, "EXIT") == 0) {
				s = 54;
			}
			break;
		case 'F': 
			OPS_Identifier(&s);
			if (__STRCMP(OPS_name, "FALSE") == 0) {
				s = 38;
			} else if (__STRCMP(OPS_name, "FOR") == 0) {
				s = 51;
			}
			break;
		case 'I': 
			OPS_Identifier(&s);
			if (__STRCMP(OPS_name, "IF") == 0) {
				s = 47;
			} else if (__STRCMP(OPS_name, "IN") == 0) {
				s = 15;
			} else if (__STRCMP(OPS_name, "IS") == 0) {
				s = 16;
			} else if (__STRCMP(OPS_name, "IMPORT") == 0) {
				s = 66;
			}
			break;
		case 'L': 
			OPS_Identifier(&s);
			if (__STRCMP(OPS_name, "LOOP") == 0) {
				s = 52;
			}
			break;
		case 'M': 
			OPS_Identifier(&s);
			if (__STRCMP(OPS_name, "MOD") == 0) {
				s = 4;
			} else if (__STRCMP(OPS_name, "MODULE") == 0) {
				s = 67;
			}
			break;
		case 'N': 
			OPS_Identifier(&s);
			if (__STRCMP(OPS_name, "NIL") == 0) {
				s = 36;
			}
			break;
		case 'O': 
			OPS_Identifier(&s);
			if (__STRCMP(OPS_name, "OR") == 0) {
				s = 8;
			} else if (__STRCMP(OPS_name, "OF") == 0) {
				s = 25;
			} else if (__STRCMP(OPS_name, "OBJECT") == 0) {
				s = 57;
			}
			break;
		case 'P': 
			OPS_Identifier(&s);
			if (__STRCMP(OPS_name, "PROCEDURE") == 0) {
				s = 65;
			} else if (__STRCMP(OPS_name, "POINTER") == 0) {
				s = 59;
			}
			break;
		case 'R': 
			OPS_Identifier(&s);
			if (__STRCMP(OPS_name, "RECORD") == 0) {
				s = 58;
			} else if (__STRCMP(OPS_name, "REPEAT") == 0) {
				s = 50;
			} else if (__STRCMP(OPS_name, "RETURN") == 0) {
				s = 55;
			}
			break;
		case 'T': 
			OPS_Identifier(&s);
			if (__STRCMP(OPS_name, "THEN") == 0) {
				s = 26;
			} else if (__STRCMP(OPS_name, "TO") == 0) {
				s = 28;
			} else if (__STRCMP(OPS_name, "TRUE") == 0) {
				s = 37;
			} else if (__STRCMP(OPS_name, "TYPE") == 0) {
				s = 63;
			}
			break;
		case 'U': 
			OPS_Identifier(&s);
			if (__STRCMP(OPS_name, "UNTIL") == 0) {
				s = 46;
			}
			break;
		case 'V': 
			OPS_Identifier(&s);
			if (__STRCMP(OPS_name, "VAR") == 0) {
				s = 64;
			}
			break;
		case 'W': 
			OPS_Identifier(&s);
			if (__STRCMP(OPS_name, "WHILE") == 0) {
				s = 49;
			} else if (__STRCMP(OPS_name, "WITH") == 0) {
				s = 53;
			}
			break;
		case 'G': case 'H': case 'J': case 'K': case 'Q': 
		case 'S': case 'X': case 'Y': case 'Z': 
			OPS_Identifier(&s);
			break;
		case '[': 
			s = 31;
			OPM_Get(&OPS_ch);
			break;
		case ']': 
			s = 23;
			OPM_Get(&OPS_ch);
			break;
		case '^': 
			s = 17;
			OPM_Get(&OPS_ch);
			break;
		case 'a': case 'b': case 'c': case 'd': case 'e': 
		case 'f': case 'g': case 'h': case 'i': case 'j': 
		case 'k': case 'l': case 'm': case 'n': case 'o': 
		case 'p': case 'q': case 'r': case 's': case 't': 
		case 'u': case 'v': case 'w': case 'x': case 'y': 
		case 'z': 
			OPS_Identifier(&s);
			break;
		case '{': 
			s = 32;
			OPM_Get(&OPS_ch);
			break;
		case '|': 
			s = 42;
			OPM_Get(&OPS_ch);
			break;
		case '}': 
			s = 24;
			OPM_Get(&OPS_ch);
			break;
		case '~': 
			s = 33;
			__MOVE("~", OPS_name, 2);
			OPM_Get(&OPS_ch);
			break;
		case 0x7f: 
			s = 21;
			OPM_Get(&OPS_ch);
			break;
		default: 
			s = 0;
			OPM_Get(&OPS_ch);
			break;
	}
	if (OPS_stream != NIL) {
		OPS_RecToken(s);
	}
	*sym = s;
	DefaultGet__3_s = _s.lnk;
}

void OPS_Init (void)
{
	OPS_ch = ' ';
	OPS_stream = NIL;
	OPS_last = NIL;
	OPS_Get = OPS_DefaultGet;
}

static void EnumPtrs(void (*P)(void*))
{
	P(OPS_stream);
	P(OPS_last);
}

__TDESC(OPS_Tok, 1, 1) = {__TDFLDS("Tok", 12), {8, -8}};
__TDESC(OPS__1, 1, 1) = {__TDFLDS("", 20), {8, -8}};
__TDESC(OPS__4, 1, 1) = {__TDFLDS("", 16), {8, -8}};
__TDESC(OPS__2, 1, 1) = {__TDFLDS("", 24), {8, -8}};
__TDESC(OPS__5, 1, 1) = {__TDFLDS("", 272), {8, -8}};
__TDESC(OPS__3, 1, 1) = {__TDFLDS("", 44), {8, -8}};

export void *OPS__init(void)
{
	__DEFMOD;
	__MODULE_IMPORT(OPM);
	__REGMOD("OPS", EnumPtrs);
	__REGCMD("Init", OPS_Init);
	__REGCMD("Number", OPS_Number);
	__INITYP(OPS_Tok, OPS_Tok, 0);
	__INITYP(OPS__1, OPS_Tok, 1);
	__INITYP(OPS__4, OPS_Tok, 1);
	__INITYP(OPS__2, OPS_Tok, 1);
	__INITYP(OPS__5, OPS_Tok, 1);
	__INITYP(OPS__3, OPS_Tok, 1);
/* BEGIN */
	OPS_Init();
	__ENDMOD;
}
