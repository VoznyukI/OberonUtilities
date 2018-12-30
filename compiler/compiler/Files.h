/* voc 2.1.0 [2017/09/06]. Bootstrapping compiler for address size 8, alignment 8. xtaSv */

#ifndef Files__h
#define Files__h

#include "SYSTEM.h"
#include "OFS.h"
#include "Platform.h"

typedef
	struct Files_FileDesc *Files_File;

typedef
	struct Files_BufDesc {
		Files_File f;
		BOOLEAN chg;
		INT32 org, size;
		SYSTEM_BYTE data[4096];
	} Files_BufDesc;

typedef
	Files_BufDesc *Files_Buffer;

typedef
	CHAR Files_FileName[101];

typedef
	struct Files_FileDesc {
		Files_FileName workName, registerName;
		BOOLEAN tempFile;
		Platform_FileIdentity identity;
		INT32 fd, len, pos;
		Files_Buffer bufs[4];
		INT16 swapper, state;
		struct Files_FileDesc *next;
	} Files_FileDesc;

typedef
	//struct Files_Rider {
	//	INT32 res;
	//	BOOLEAN eof;
	//	//char _prvt0[15]; //TODO
	//	char _prvt0[4]; // Files_Buffer buf;
	//	INT32 org, offset;
	//} Files_Rider;
	struct Files_Rider {
		INT32 res;
		BOOLEAN eof;
		Files_Buffer buf;
		INT32 org, offset;
	} Files_Rider;



import ADDRESS *Files_FileDesc__typ;
import ADDRESS *Files_Rider__typ;

import Files_File Files_Base (Files_Rider *r, ADDRESS *r__typ);
import void Files_Close (Files_File f);
import void Files_Delete (CHAR *name, ADDRESS name__len, INT16 *res);
import void Files_GetDate (Files_File f, INT32 *t, INT32 *d);
import void Files_GetName (Files_File f, CHAR *name, ADDRESS name__len);
import INT32 Files_Length (Files_File f);
import Files_File Files_New (CHAR *name, ADDRESS name__len);
import Files_File Files_Old (CHAR *name, ADDRESS name__len);
import INT32 Files_Pos (Files_Rider *r, ADDRESS *r__typ);
import void Files_Read (Files_Rider *r, ADDRESS *r__typ, SYSTEM_BYTE *x);
import void Files_ReadBool (Files_Rider *r, ADDRESS *r__typ, BOOLEAN *x);
import void Files_ReadBytes (Files_Rider *r, ADDRESS *r__typ, SYSTEM_BYTE *x, ADDRESS x__len, INT32 n);
import void Files_ReadInt (Files_Rider *r, ADDRESS *r__typ, INT16 *x);
import void Files_ReadLInt (Files_Rider *r, ADDRESS *r__typ, INT32 *x);
import void Files_ReadLReal (Files_Rider *r, ADDRESS *r__typ, LONGREAL *x);
import void Files_ReadNum (Files_Rider *r, ADDRESS *r__typ, INT32 *x);
import void Files_ReadReal (Files_Rider *r, ADDRESS *r__typ, REAL *x);
import void Files_ReadSet (Files_Rider *r, ADDRESS *r__typ, UINT32 *x);
import void Files_ReadString (Files_Rider *r, ADDRESS *r__typ, CHAR *x, ADDRESS x__len);
import void Files_Register (Files_File f);
import void Files_Rename (CHAR *old, ADDRESS old__len, CHAR *new, ADDRESS new__len, INT16 *res);
import void Files_Set (Files_Rider *r, ADDRESS *r__typ, Files_File f, INT32 pos);
//import void Files_SetDate (OFS_File f, INT32 t, INT32 d);
import void Files_Write (Files_Rider *r, ADDRESS *r__typ, SYSTEM_BYTE x);
import void Files_WriteBool (Files_Rider *R, ADDRESS *R__typ, BOOLEAN x);
import void Files_WriteBytes (Files_Rider *r, ADDRESS *r__typ, SYSTEM_BYTE *x, ADDRESS x__len, INT32 n);
import void Files_WriteInt (Files_Rider *R, ADDRESS *R__typ, INT16 x);
import void Files_WriteLInt (Files_Rider *r, ADDRESS *r__typ, INT32 x);
import void Files_WriteLReal (Files_Rider *r, ADDRESS *r__typ, LONGREAL x);
import void Files_WriteNum (Files_Rider *r, ADDRESS *r__typ, INT32 x);
import void Files_WriteReal (Files_Rider *R, ADDRESS *R__typ, REAL x);
import void Files_WriteSet (Files_Rider *R, ADDRESS *R__typ, UINT32 x);
import void Files_WriteString (Files_Rider *r, ADDRESS *r__typ, CHAR *x, ADDRESS x__len);
import void *Files__init(void);


#endif // Files
