/* voc 2.1.0 [2017/09/06]. Bootstrapping compiler for address size 8, alignment 8. xtaSv */

#ifndef OFS__h
#define OFS__h

#include "SYSTEM.h"

typedef
	struct OFS_RECORDVolume *OFS_Volume;

typedef
	void (*OFS_AllocProc)(OFS_Volume, INT32, INT32*);

typedef
	INT32 (*OFS_AvailableProc)(OFS_Volume);

typedef
	struct OFS_FileDesc *OFS_File;

typedef
	void (*OFS_CloseProc)(OFS_File);

typedef
	struct OFS_FileSystemDesc *OFS_FileSystem;

typedef
	void (*OFS_DeleteProc)(OFS_FileSystem, CHAR*, ADDRESS , INT32*, INT16*);

typedef
	void (*OFS_EntryHandler)(CHAR*, ADDRESS , INT32, INT32, INT32, UINT32*);

typedef
	void (*OFS_EnumerateProc)(OFS_FileSystem, CHAR*, ADDRESS , UINT32*, OFS_EntryHandler);

typedef
	struct OFS_FileDesc {
		char _prvt0[4];
		INT32 key;
		OFS_FileSystem fs;
	} OFS_FileDesc;

typedef
	INT32 (*OFS_FileKeyProc)(OFS_FileSystem, CHAR*, ADDRESS );

typedef
	CHAR OFS_FileName[144];

typedef
	CHAR OFS_Prefix[16];

typedef
	OFS_File (*OFS_NewOldProc)(OFS_FileSystem, CHAR*, ADDRESS );

typedef
	void (*OFS_RenameProc)(OFS_FileSystem, CHAR*, ADDRESS , CHAR*, ADDRESS , INT16*);

typedef
	void (*OFS_RegisterProc)(OFS_File, INT16*);

typedef
	INT32 (*OFS_LengthProc)(OFS_File);

typedef
	void (*OFS_GetDateProc)(OFS_File, INT32*, INT32*);

typedef
	void (*OFS_SetDateProc)(OFS_File, INT32, INT32);

typedef
	void (*OFS_GetNameProc)(OFS_File, CHAR*, ADDRESS );

typedef
	struct OFS_HintDesc *OFS_Hint;

typedef
	struct OFS_Rider {
		BOOLEAN eof;
		INT32 res, apos, bpos;
		OFS_Hint hint;
		OFS_File file;
		OFS_FileSystem fs;
	} OFS_Rider;

typedef
	void (*OFS_SetProc)(OFS_Rider*, ADDRESS *, OFS_File, INT32);

typedef
	INT32 (*OFS_PosProc)(OFS_Rider*, ADDRESS *);

typedef
	void (*OFS_ReadProc)(OFS_Rider*, ADDRESS *, SYSTEM_BYTE*);

typedef
	void (*OFS_WriteProc)(OFS_Rider*, ADDRESS *, SYSTEM_BYTE);

typedef
	void (*OFS_ReadWriteBytesProc)(OFS_Rider*, ADDRESS *, SYSTEM_BYTE*, ADDRESS , INT32);

typedef
	void (*OFS_FinalizeFSProc)(OFS_FileSystem);

typedef
	struct OFS_Message {
		char _prvt0[1];
	} OFS_Message;

typedef
	void (*OFS_HandleProc)(OFS_FileSystem, OFS_Message*, ADDRESS *, INT32*);

typedef
	void (*OFS_PurgeProc)(OFS_FileSystem, OFS_File);

typedef
	BOOLEAN (*OFS_RegisteredProc)(OFS_FileSystem, OFS_File);

typedef
	struct OFS_FileSystemDesc {
		INT32 _prvt0;
		char _prvt1[4];
		OFS_Prefix prefix;
		CHAR desc[32];
		OFS_Volume vol;
		OFS_FileKeyProc FileKey;
		OFS_NewOldProc New, Old;
		OFS_DeleteProc Delete;
		OFS_RenameProc Rename;
		OFS_EnumerateProc Enumerate;
		OFS_CloseProc Close;
		OFS_RegisterProc Register;
		OFS_LengthProc Length;
		OFS_GetDateProc GetDate;
		OFS_SetDateProc SetDate;
		OFS_GetNameProc GetName;
		OFS_SetProc Set;
		OFS_PosProc Pos;
		OFS_ReadProc Read;
		OFS_WriteProc Write;
		OFS_ReadWriteBytesProc ReadBytes, WriteBytes;
		OFS_FinalizeFSProc Finalize;
		OFS_HandleProc Handle;
		OFS_PurgeProc Purge;
		OFS_RegisteredProc Registered;
	} OFS_FileSystemDesc;

typedef
	void (*OFS_FinalizeVolProc)(OFS_Volume);

typedef
	void (*OFS_FreeMarkProc)(OFS_Volume, INT32);

typedef
	void (*OFS_GetPutProc)(OFS_Volume, INT32, SYSTEM_BYTE*, ADDRESS );

typedef
	struct OFS_HintDesc {
		char _prvt0[1];
	} OFS_HintDesc;

typedef
	CHAR OFS_LocalName[128];

typedef
	BOOLEAN (*OFS_MarkedProc)(OFS_Volume, INT32);

typedef
	void (*OFS_SyncProc)(OFS_Volume);

typedef
	struct OFS_RECORDVolume {
		INT32 _prvt0;
		char _prvt1[4];
		CHAR name[32];
		INT32 blockSize, size;
		UINT32 flags;
		OFS_AllocProc AllocBlock;
		OFS_FreeMarkProc FreeBlock, MarkBlock;
		OFS_MarkedProc Marked;
		OFS_AvailableProc Available;
		OFS_GetPutProc GetBlock, PutBlock;
		OFS_FinalizeVolProc Finalize;
		OFS_SyncProc Sync;
	} OFS_RECORDVolume;


import OFS_Volume OFS_NewVol;

import ADDRESS *OFS_RECORDVolume__typ;
import ADDRESS *OFS_Rider__typ;
import ADDRESS *OFS_FileDesc__typ;
import ADDRESS *OFS_Message__typ;
import ADDRESS *OFS_FileSystemDesc__typ;
import ADDRESS *OFS_HintDesc__typ;

import void OFS_Add (OFS_FileSystem fs, CHAR *prefix, ADDRESS prefix__len);
import void OFS_AllocBlock (OFS_Volume vol, INT32 hint, INT32 *adr);
import void OFS_AppendInt (INT32 x, CHAR *to, ADDRESS to__len);
import void OFS_AppendStr (CHAR *from, ADDRESS from__len, CHAR *to, ADDRESS to__len);
import INT32 OFS_Available (OFS_Volume vol);
import void OFS_Delete (CHAR *name, ADDRESS name__len, INT16 *res);
import void OFS_Enumerate (CHAR *mask, ADDRESS mask__len, UINT32 *flags, OFS_EntryHandler proc);
import void OFS_FinalizeVol (OFS_Volume vol);
import OFS_File OFS_FindOpenFile (OFS_FileSystem fs, INT32 key);
import OFS_FileSystem OFS_First (void);
import void OFS_FreeBlock (OFS_Volume vol, INT32 adr);
import BOOLEAN OFS_HasOpenFiles (OFS_FileSystem fs);
import void OFS_InitVol (OFS_Volume vol);
import void OFS_JoinName (CHAR *prefix, ADDRESS prefix__len, CHAR *name, ADDRESS name__len, CHAR *fullname, ADDRESS fullname__len);
import void OFS_MarkBlock (OFS_Volume vol, INT32 adr);
import BOOLEAN OFS_Marked (OFS_Volume vol, INT32 adr);
import OFS_File OFS_New (CHAR *name, ADDRESS name__len);
import OFS_FileSystem OFS_Next (OFS_FileSystem fs);
import OFS_File OFS_Old (CHAR *name, ADDRESS name__len);
import void OFS_Promote (OFS_FileSystem fs);
import void OFS_ReadPar (CHAR *ch);
import void OFS_Register (OFS_File f);
import void OFS_Remove (OFS_FileSystem fs);
import void OFS_Rename (CHAR *old, ADDRESS old__len, CHAR *new, ADDRESS new__len, INT16 *res);
import void OFS_SetPar (CHAR *str, ADDRESS str__len);
import void OFS_SplitName (CHAR *fullname, ADDRESS fullname__len, CHAR *prefix, ADDRESS prefix__len, CHAR *name, ADDRESS name__len);
import void OFS_Sync (OFS_Volume vol);
import OFS_FileSystem OFS_This (CHAR *prefix, ADDRESS prefix__len);
import void *OFS__init(void);


#endif // OFS
