/* voc 2.1.0 [2017/09/06]. Bootstrapping compiler for address size 8, alignment 8. xtaSv */

#ifndef Objects__h
#define Objects__h

#include "SYSTEM.h"
#include "Files.h"
#include "Kernel.h"
#include "Modules.h"

typedef
	struct Objects_ObjDesc *Objects_Object;

typedef
	struct Objects_ObjMsg {
		INT32 stamp;
		Objects_Object dlink;
	} Objects_ObjMsg;

typedef
	CHAR Objects_Name[32];

typedef
	struct Objects_AttrMsg { /* Objects_ObjMsg */
		INT32 stamp;
		Objects_Object dlink;
		INT16 id;
		void (*Enum)(CHAR*, ADDRESS );
		Objects_Name name;
		INT16 res, class;
		INT32 i;
		REAL x;
		LONGREAL y;
		CHAR c;
		BOOLEAN b;
		CHAR s[64];
	} Objects_AttrMsg;

typedef
	struct Objects_LibDesc *Objects_Library;

typedef
	struct Objects_BindMsg { /* Objects_ObjMsg */
		INT32 stamp;
		Objects_Object dlink;
		Objects_Library lib;
	} Objects_BindMsg;

typedef
	struct Objects_CopyMsg { /* Objects_ObjMsg */
		INT32 stamp;
		Objects_Object dlink;
		INT16 id;
		Objects_Object obj;
	} Objects_CopyMsg;

typedef
	struct Objects_DictionaryDesc *Objects_Dictionary;

typedef
	struct Objects_DictionaryDesc {
		char _prvt0[1];
	} Objects_DictionaryDesc;

typedef
	struct Objects_DummyDesc *Objects_Dummy;

typedef
	void (*Objects_Handler)(Objects_Object, Objects_ObjMsg*, ADDRESS *);

typedef
	struct Objects_ObjDesc {
		INT32 stamp;
		Objects_Object dlink, slink;
		Objects_Library lib;
		INT16 ref;
		Objects_Handler handle;
	} Objects_ObjDesc;

typedef
	struct Objects_DummyDesc { /* Objects_ObjDesc */
		INT32 stamp;
		Objects_Object dlink, slink;
		Objects_Library lib;
		INT16 ref;
		Objects_Handler handle;
		Objects_Name GName;
		INT32 len;
		struct {
			ADDRESS len[1];
			CHAR data[1];
		} *blk;
	} Objects_DummyDesc;

typedef
	void (*Objects_EnumProc)(Objects_Library);

typedef
	struct Objects_FileMsg { /* Objects_ObjMsg */
		INT32 stamp;
		Objects_Object dlink;
		INT16 id;
		INT32 len;
		Files_Rider R;
	} Objects_FileMsg;

typedef
	struct Objects_FindMsg { /* Objects_ObjMsg */
		INT32 stamp;
		Objects_Object dlink;
		Objects_Name name;
		Objects_Object obj;
	} Objects_FindMsg;

typedef
	struct Objects_IndexDesc *Objects_Index;

typedef
	struct Objects_IndexDesc {
		char _prvt0[1];
	} Objects_IndexDesc;

typedef
	CHAR Objects_GenName[64];

typedef
	struct Objects_LibDesc {
		Objects_Library next;
		Objects_Index ind;
		Files_File f;
		Files_Rider R;
		Objects_Name name;
		Objects_Dictionary dict;
		INT16 maxref;
		struct {
			ADDRESS len[1];
			Objects_GenName data[1];
		} *GName;
		void (*GenRef)(Objects_Library, INT16*);
		void (*GetObj)(Objects_Library, INT16, Objects_Object*);
		void (*PutObj)(Objects_Library, INT16, Objects_Object);
		void (*FreeObj)(Objects_Library, INT16);
		void (*Load)(Objects_Library);
		void (*Store)(Objects_Library);
	} Objects_LibDesc;

typedef
	struct Objects_LinkMsg { /* Objects_ObjMsg */
		INT32 stamp;
		Objects_Object dlink;
		INT16 id;
		void (*Enum)(CHAR*, ADDRESS );
		Objects_Name name;
		INT16 res;
		Objects_Object obj;
	} Objects_LinkMsg;

typedef
	Objects_Library (*Objects_NewProc)(void);


import CHAR Objects_LibBlockId;
import Objects_Object Objects_NewObj;

import ADDRESS *Objects_ObjMsg__typ;
import ADDRESS *Objects_ObjDesc__typ;
import ADDRESS *Objects_AttrMsg__typ;
import ADDRESS *Objects_LinkMsg__typ;
import ADDRESS *Objects_CopyMsg__typ;
import ADDRESS *Objects_BindMsg__typ;
import ADDRESS *Objects_FileMsg__typ;
import ADDRESS *Objects_FindMsg__typ;
import ADDRESS *Objects_DummyDesc__typ;
import ADDRESS *Objects_IndexDesc__typ;
import ADDRESS *Objects_DictionaryDesc__typ;
import ADDRESS *Objects_LibDesc__typ;

import void Objects_Enumerate (Objects_EnumProc P);
import void Objects_FreeLibrary (CHAR *name, ADDRESS name__len);
import void Objects_GetKey (Objects_Dictionary *D, CHAR *name, ADDRESS name__len, INT16 *key);
import void Objects_GetName (Objects_Dictionary *D, INT16 key, CHAR *name, ADDRESS name__len);
import void Objects_GetRef (Objects_Dictionary *D, CHAR *name, ADDRESS name__len, INT16 *ref);
import void Objects_LoadLibrary (Objects_Library L, Files_File f, INT32 pos, INT32 *len);
import void Objects_OpenLibrary (Objects_Library L);
import void Objects_PutName (Objects_Dictionary *D, INT16 key, CHAR *name, ADDRESS name__len);
import void Objects_Register (CHAR *ext, ADDRESS ext__len, Objects_NewProc new);
import void Objects_Stamp (Objects_ObjMsg *M, ADDRESS *M__typ);
import void Objects_StoreLibrary (Objects_Library L, Files_File f, INT32 pos, INT32 *len);
import Objects_Library Objects_ThisLibrary (CHAR *name, ADDRESS name__len);
import void *Objects__init(void);


#endif // Objects
