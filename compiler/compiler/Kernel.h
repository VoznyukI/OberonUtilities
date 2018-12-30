/* voc 2.1.0 [2017/09/06]. Bootstrapping compiler for address size 8, alignment 8. xtaSv */

#ifndef Kernel__h
#define Kernel__h

#include "SYSTEM.h"

typedef
	struct {
		ADDRESS len[1];
		INT32 data[1];
	} *Kernel_ArrayPtr;

typedef
	CHAR Kernel_Name[32];

typedef
	struct Kernel_Cmd {
		Kernel_Name name;
		INT32 adr;
	} Kernel_Cmd;

typedef
	struct Kernel_ExportDesc *Kernel_ExportPtr;

typedef
	struct Kernel_ExportDesc {
		INT32 fp, adr;
		INT16 nofExp;
		struct {
			ADDRESS len[1];
			Kernel_ExportPtr data[1];
		} *dsc;
	} Kernel_ExportDesc;

typedef
	void (*Kernel_Finalizer)(SYSTEM_PTR);

typedef
	struct Kernel_MilliTimer {
		INT32 target;
	} Kernel_MilliTimer;

typedef
	struct Kernel_ModuleDesc *Kernel_Module;

typedef
	void (*Kernel_Proc)(void);

typedef
	struct Kernel_ModuleDesc {
		Kernel_Module next;
		Kernel_Name name;
		BOOLEAN init, trapped;
		INT32 refcnt, sb;
		struct {
			ADDRESS len[1];
			INT32 data[1];
		} *entries;
		struct {
			ADDRESS len[1];
			Kernel_Cmd data[1];
		} *cmds;
		struct {
			ADDRESS len[1];
			INT32 data[1];
		} *ptrTab, *tdescs;
		struct {
			ADDRESS len[1];
			Kernel_Module data[1];
		} *imports;
		struct {
			ADDRESS len[1];
			CHAR data[1];
		} *data, *code, *refs;
		INT32 publics, privates;
		INT16 nofimp;
		Kernel_ArrayPtr import_;
		INT16 nofstrc;
		Kernel_ArrayPtr struct_;
		INT16 nofreimp;
		Kernel_ArrayPtr reimp;
		Kernel_ExportDesc export_;
		Kernel_Proc term;
	} Kernel_ModuleDesc;

typedef
	void (*Kernel_TrapHandler)(INT32, INT32, INT32, INT32);


import CHAR Kernel_version[32];
import Kernel_Module Kernel_modules;
import INT32 Kernel_StackOrg, Kernel_bt, Kernel_tspeed;
import INT16 Kernel_tbase;
import BOOLEAN Kernel_break, Kernel_copro, Kernel_inGC;
import Kernel_Proc Kernel_EnableGC, Kernel_DisableGC, Kernel_timer;
import INT32 Kernel_runtime[3];
import BOOLEAN Kernel_traceConsole;
import INT32 Kernel_shutdown;

import ADDRESS *Kernel_Cmd__typ;
import ADDRESS *Kernel_ExportDesc__typ;
import ADDRESS *Kernel_ModuleDesc__typ;
import ADDRESS *Kernel_MilliTimer__typ;

import INT32 Kernel_Available (void);
import void Kernel_DisposeDMA (INT32 size, INT32 adr);
import BOOLEAN Kernel_Expired (Kernel_MilliTimer *t, ADDRESS *t__typ);
import void Kernel_FinalizeModule (Kernel_Module m);
import void Kernel_GC (void);
import void Kernel_GetClock (INT32 *time, INT32 *date);
import void Kernel_GetConfig (CHAR *name, ADDRESS name__len, CHAR *val, ADDRESS val__len);
import void Kernel_GetInit (INT32 n, INT32 *val);
import void Kernel_GetLog (CHAR *val, ADDRESS val__len);
import void Kernel_GetMarkedLog (CHAR *val, ADDRESS val__len);
import Kernel_Module Kernel_GetMod (INT32 pc);
import INT32 Kernel_GetTimer (void);
import void Kernel_Idle (INT32 code);
import void Kernel_InstallIP (Kernel_Proc p, INT16 i);
import void Kernel_InstallLoop (Kernel_Proc p);
import void Kernel_InstallTermHandler (Kernel_Proc h);
import void Kernel_InstallTrap (Kernel_TrapHandler p);
import INT32 Kernel_LargestAvailable (void);
import void Kernel_MapPhysical (INT32 physAdr, INT32 size, INT32 *virtAdr);
import void Kernel_NewDMA (INT32 size, INT32 *adr, INT32 *phys);
import void Kernel_RegisterObject (SYSTEM_PTR obj, Kernel_Finalizer fin, BOOLEAN basic);
import void Kernel_RemoveIP (Kernel_Proc p, INT16 i);
import void Kernel_SetClock (INT32 time, INT32 date);
import void Kernel_SetLogMark (void);
import void Kernel_SetTimer (Kernel_MilliTimer *t, ADDRESS *t__typ, INT32 ms);
import void Kernel_Shutdown (INT32 code);
import INT32 Kernel_Used (void);
import void Kernel_WriteChar (CHAR c);
import void Kernel_WriteHex (INT32 x, INT32 w);
import void Kernel_WriteInt (INT32 x, INT32 w);
import void Kernel_WriteLn (void);
import void Kernel_WriteMemory (INT32 adr, INT32 size);
import void Kernel_WriteString (CHAR *s, ADDRESS s__len);
import void *Kernel__init(void);


#endif // Kernel
