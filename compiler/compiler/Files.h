/* voc 2.1.0 [2017/09/06]. Bootstrapping compiler for address size 8, alignment 8. xtaSv */

#ifndef Files__h
#define Files__h

#include "SYSTEM.h"
#include "OFS.h"




import OFS_File Files_Base (OFS_Rider *r, ADDRESS *r__typ);
import void Files_Close (OFS_File f);
import void Files_Delete (CHAR *name, ADDRESS name__len, INT16 *res);
import void Files_GetDate (OFS_File f, INT32 *t, INT32 *d);
import void Files_GetName (OFS_File f, CHAR *name, ADDRESS name__len);
import INT32 Files_Length (OFS_File f);
import OFS_File Files_New (CHAR *name, ADDRESS name__len);
import OFS_File Files_Old (CHAR *name, ADDRESS name__len);
import INT32 Files_Pos (OFS_Rider *r, ADDRESS *r__typ);
import void Files_Read (OFS_Rider *r, ADDRESS *r__typ, SYSTEM_BYTE *x);
import void Files_ReadBool (OFS_Rider *r, ADDRESS *r__typ, BOOLEAN *x);
import void Files_ReadBytes (OFS_Rider *r, ADDRESS *r__typ, SYSTEM_BYTE *x, ADDRESS x__len, INT32 n);
import void Files_ReadInt (OFS_Rider *r, ADDRESS *r__typ, INT16 *x);
import void Files_ReadLInt (OFS_Rider *r, ADDRESS *r__typ, INT32 *x);
import void Files_ReadLReal (OFS_Rider *r, ADDRESS *r__typ, LONGREAL *x);
import void Files_ReadNum (OFS_Rider *r, ADDRESS *r__typ, INT32 *x);
import void Files_ReadReal (OFS_Rider *r, ADDRESS *r__typ, REAL *x);
import void Files_ReadSet (OFS_Rider *r, ADDRESS *r__typ, UINT32 *x);
import void Files_ReadString (OFS_Rider *r, ADDRESS *r__typ, CHAR *x, ADDRESS x__len);
import void Files_Register (OFS_File f);
import void Files_Rename (CHAR *old, ADDRESS old__len, CHAR *new, ADDRESS new__len, INT16 *res);
import void Files_Set (OFS_Rider *r, ADDRESS *r__typ, OFS_File f, INT32 pos);
import void Files_SetDate (OFS_File f, INT32 t, INT32 d);
import void Files_Write (OFS_Rider *r, ADDRESS *r__typ, SYSTEM_BYTE x);
import void Files_WriteBool (OFS_Rider *r, ADDRESS *r__typ, BOOLEAN x);
import void Files_WriteBytes (OFS_Rider *r, ADDRESS *r__typ, SYSTEM_BYTE *x, ADDRESS x__len, INT32 n);
import void Files_WriteInt (OFS_Rider *r, ADDRESS *r__typ, INT16 x);
import void Files_WriteLInt (OFS_Rider *r, ADDRESS *r__typ, INT32 x);
import void Files_WriteLReal (OFS_Rider *r, ADDRESS *r__typ, LONGREAL x);
import void Files_WriteNum (OFS_Rider *r, ADDRESS *r__typ, INT32 x);
import void Files_WriteReal (OFS_Rider *r, ADDRESS *r__typ, REAL x);
import void Files_WriteSet (OFS_Rider *r, ADDRESS *r__typ, UINT32 x);
import void Files_WriteString (OFS_Rider *r, ADDRESS *r__typ, CHAR *x, ADDRESS x__len);
import void *Files__init(void);


#endif // Files
