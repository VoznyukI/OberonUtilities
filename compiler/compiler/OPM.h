/* voc 2.1.0 [2017/09/06]. Bootstrapping compiler for address size 8, alignment 8. xtaSv */

#ifndef OPM__h
#define OPM__h

#include "SYSTEM.h"
#include "Texts.h"


import REAL OPM_MinReal, OPM_MaxReal;
import LONGREAL OPM_MinLReal, OPM_MaxLReal;
import BOOLEAN OPM_noerr;
import INT32 OPM_curpos, OPM_errpos, OPM_breakpos, OPM_breakpc;
import CHAR OPM_outputPath[32];
import CHAR OPM_outputPrefix[32];
import UINT32 OPM_codeOptions, OPM_parserOptions;
import CHAR OPM_errName[32];
import CHAR OPM_extension[8];


import void OPM_Begin (CHAR *modName, ADDRESS modName__len);
import void OPM_Close (void);
import void OPM_CloseObj (void);
import void OPM_EndObj (void);
import void OPM_EndSym (void);
import void OPM_FPrint (INT32 *fp, INT32 val);
import void OPM_FPrintLReal (INT32 *fp, LONGREAL lr);
import void OPM_FPrintReal (INT32 *fp, REAL real);
import void OPM_FPrintSet (INT32 *fp, UINT32 set);
import void OPM_Get (CHAR *ch);
import void OPM_Init (UINT32 codeOpt, UINT32 parserOpt, Texts_Reader source, Texts_Text log);
import void OPM_LogW (CHAR ch);
import void OPM_LogWHex (INT32 i);
import void OPM_LogWLn (void);
import void OPM_LogWNum (INT32 i, INT32 len);
import void OPM_LogWStr (CHAR *s, ADDRESS s__len);
import void OPM_Mark (INT16 n, INT32 pos);
import INT32 OPM_ObjAllocInt (void);
import void OPM_ObjFillInt (INT32 pos, INT16 int_);
import void OPM_ObjW (CHAR ch);
import void OPM_ObjWBytes (SYSTEM_BYTE *bytes, ADDRESS bytes__len, INT32 n);
import void OPM_ObjWInt (INT16 i);
import void OPM_ObjWLInt (INT32 i);
import void OPM_ObjWNum (INT32 i);
import void OPM_ObjWString (CHAR *s, ADDRESS s__len);
import void OPM_OpenSym (OFS_Rider *R, ADDRESS *R__typ, CHAR *name, ADDRESS name__len, BOOLEAN self, BOOLEAN *done);
import void OPM_RefW (CHAR ch);
import void OPM_RefWNum (INT32 i);
import void OPM_SymW (CHAR b);
import void OPM_SymWCh (CHAR ch);
import void OPM_SymWInt (INT32 k);
import void OPM_SymWLInt (INT32 k);
import void OPM_SymWLReal (LONGREAL lr);
import void OPM_SymWMod (CHAR *name, ADDRESS name__len);
import void OPM_SymWNum (INT32 i);
import INT32 OPM_SymWPos (void);
import void OPM_SymWReal (REAL r);
import void OPM_SymWSet (UINT32 s);
import void OPM_SymWString (CHAR *s, ADDRESS s__len);
import void OPM_SymWTag (INT16 k);
import void OPM_err (INT16 n);
import void *OPM__init(void);


#endif // OPM
