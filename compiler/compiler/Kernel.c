/* voc 2.1.0 [2017/09/06]. Bootstrapping compiler for address size 8, alignment 8. xtaSv */

#define SHORTINT INT8
#define INTEGER  INT16
#define LONGINT  INT32
#define SET      UINT32

#include "SYSTEM.h"

typedef
	struct Kernel_TypeDesc *Kernel_Tag;

struct Kernel__2 {
	Kernel_Tag tag;
	INT32 z0, z1, z2, z3, z4, z5, z6, z7;
};

struct Kernel__1 {
	INT32 physAdr, size, virtAdr;
};

struct Kernel__1 {
	UINT32 ptroff;
};

typedef
	CHAR Kernel_Name[32];

struct Kernel__2 {
	INT32 filler[4];
	Kernel_Name name;
};

typedef
	struct {
		ADDRESS len[1];
		INT32 data[1];
	} *Kernel_ArrayPtr;

typedef
	struct Kernel_Block *Kernel_BlockPtr;

typedef
	struct Kernel_Block {
		Kernel_BlockPtr lastElemToMark, currElem, firstElem;
	} Kernel_Block;

typedef
	struct Kernel_Blockm4 {
		Kernel_Tag tag;
		INT32 lastElemToMark, currElem, firstElem;
	} Kernel_Blockm4;

typedef
	Kernel_Blockm4 *Kernel_Blockm4Ptr;

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
	struct Kernel_FinObjNode *Kernel_FinObj;

typedef
	void (*Kernel_Finalizer)(SYSTEM_PTR);

typedef
	struct Kernel_FinObjNode {
		Kernel_FinObj next;
		INT32 obj;
		BOOLEAN marked;
		Kernel_Finalizer fin;
	} Kernel_FinObjNode;

typedef
	struct Kernel_FreeBlock {
		Kernel_Tag tag;
		INT32 size, next;
	} Kernel_FreeBlock;

typedef
	Kernel_FreeBlock *Kernel_FreeBlockPtr;

typedef
	struct Kernel_SegmentDescriptor {
		INT16 limit0to15, base0to15;
		CHAR base16to23, accessByte, granularityByte, base24to31;
	} Kernel_SegmentDescriptor;

typedef
	Kernel_SegmentDescriptor Kernel_GDT[9];

typedef
	struct Kernel_GateDescriptor {
		INT16 offsetBits0to15, selector, gateType, offsetBits16to31;
	} Kernel_GateDescriptor;

typedef
	Kernel_GateDescriptor Kernel_IDT[48];

typedef
	struct Kernel__2 *Kernel_InitPtr;

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
	struct Kernel_PtrElemDesc {
		SYSTEM_PTR a;
	} Kernel_PtrElemDesc;

typedef
	struct Kernel_TSSDesc {
		INT16 Link, pad0;
		INT32 ESP0;
		INT16 ESS0, pad1;
		INT32 ESP1;
		INT16 ESS1, pad2;
		INT32 ESP2;
		INT16 ESS2, pad3;
		INT32 CR3, EIP;
		UINT32 EFLAGS;
		INT32 EAX, ECX, EDX, EBX, ESP, EBP, ESI, EDI;
		INT16 ES, pad4, CS, pad5, SS, pad6, DS, pad7, FS, pad8, GS, pad9, LDT, pad10, TaskAttributes, IOBitmapOffset;
		UINT32 IOBitmap[2049];
	} Kernel_TSSDesc;

typedef
	void (*Kernel_TrapHandler)(INT32, INT32, INT32, INT32);

typedef
	struct Kernel_TypeDesc {
		INT32 size, ptroff;
	} Kernel_TypeDesc;

typedef
	struct Kernel_V86Regs {
		INT32 EDI, ESI, EBP, fillerESP, EBX, EDX, ECX, EAX, int_, errCode, EIP, CS;
		UINT32 EFLAGS;
		INT32 ESP, SS, ES, DS, FS, GS;
	} Kernel_V86Regs;

typedef
	CHAR Kernel_Vendor[13];


export CHAR Kernel_version[32];
export Kernel_Module Kernel_modules;
export INT32 Kernel_StackOrg, Kernel_bt, Kernel_tspeed;
export INT16 Kernel_tbase;
export BOOLEAN Kernel_break, Kernel_copro, Kernel_inGC;
export Kernel_Proc Kernel_EnableGC, Kernel_DisableGC, Kernel_timer;
export INT32 Kernel_runtime[3];
export BOOLEAN Kernel_traceConsole;
export INT32 Kernel_shutdown;
static INT32 Kernel_tlpt;
static INT16 Kernel_bioslpt[3];
static INT32 Kernel_memTop, Kernel_heapTop, Kernel_firstBlock, Kernel_endBlock;
static INT32 Kernel_A[10];
static Kernel_BlockPtr Kernel_reserve;
static Kernel_InitPtr Kernel_sysres, Kernel_initres;
static INT32 Kernel_ptrElemTag;
static INT32 Kernel_candidates[1024];
static INT16 Kernel_nofcand;
static BOOLEAN Kernel_firstTry, Kernel_GCstack;
static Kernel_FinObj Kernel_FinObjs;
static UINT32 Kernel_traceheap;
static INT32 Kernel_dma0, Kernel_dma1, Kernel_dmafree, Kernel_GClevel;
static Kernel_TrapHandler Kernel_handler0, Kernel_handler;
static Kernel_Proc Kernel_loop;
static Kernel_IDT Kernel_idt;
static Kernel_GDT Kernel_gdt;
static Kernel_TSSDesc Kernel_ktss;
static CHAR Kernel_glue[48][12];
static Kernel_Proc Kernel_intHandler[48][4];
static INT32 Kernel_intHandlerAdr;
static Kernel_Proc Kernel_defaultHandler;
static INT32 Kernel_kernelpd, Kernel_v86pd;
static BOOLEAN Kernel_handlingtrap, Kernel_oldcopro;
static INT32 Kernel_trapCR[5];
static INT32 Kernel_trapDR[8];
static UINT32 Kernel_trapfpu[7];
static INT32 Kernel_mapPtr;
static struct Kernel__1 Kernel_mapcache[4];
static INT32 Kernel_vregadr, Kernel_vframe, Kernel_traceBufAdr, Kernel_traceBufSize, Kernel_traceHead, Kernel_traceTail, Kernel_traceMark;
static INT16 Kernel_second, Kernel_minute, Kernel_hour, Kernel_day, Kernel_month, Kernel_year;
static INT32 Kernel_clockmissed, Kernel_clockmode, Kernel_clockints, Kernel_ticks, Kernel_configadr, Kernel_pspeed, Kernel_pageheap, Kernel_pageheap0, Kernel_pageheap1, Kernel_displayPos;
static INT32 Kernel_kpar[2];
static INT32 Kernel_apmofs;
static BOOLEAN Kernel_powersave;
static INT32 Kernel_cpuversion, Kernel_cpufeatures;
static Kernel_Vendor Kernel_cpuvendor;
static INT8 Kernel_cpu;

export ADDRESS *Kernel_Cmd__typ;
export ADDRESS *Kernel_ExportDesc__typ;
export ADDRESS *Kernel_ModuleDesc__typ;
export ADDRESS *Kernel_TypeDesc__typ;
export ADDRESS *Kernel_FreeBlock__typ;
export ADDRESS *Kernel_Block__typ;
export ADDRESS *Kernel_Blockm4__typ;
export ADDRESS *Kernel__2__typ;
export ADDRESS *Kernel_PtrElemDesc__typ;
export ADDRESS *Kernel_FinObjNode__typ;
export ADDRESS *Kernel_GateDescriptor__typ;
export ADDRESS *Kernel_SegmentDescriptor__typ;
export ADDRESS *Kernel_TSSDesc__typ;
export ADDRESS *Kernel_V86Regs__typ;
export ADDRESS *Kernel_MilliTimer__typ;
export ADDRESS *Kernel__1__typ;
export ADDRESS *Kernel__1__typ;
export ADDRESS *Kernel__2__typ;

static BOOLEAN Kernel_APM (INT32 *gdtofs, INT32 *apmofs);
static void Kernel_APMPowerOff (void);
static void Kernel_AllocatePage (INT32 *p);
export INT32 Kernel_Available (void);
static INT32 Kernel_BCD2 (INT16 x);
static void Kernel_Bits (CHAR *s, ADDRESS s__len, UINT32 x, INT32 ofs, INT32 n);
static void Kernel_CLTS (void);
static void Kernel_CPUID (Kernel_Vendor vendor, INT32 *version, INT32 *features);
static INT32 Kernel_CR0 (void);
static INT32 Kernel_CR2 (void);
static INT32 Kernel_CR3 (void);
static INT32 Kernel_CR4 (void);
static void Kernel_Call15 (void);
static void Kernel_Candidate (INT32 p);
static CHAR Kernel_Cap (CHAR ch);
static void Kernel_CheckCandidates (void);
static void Kernel_CheckFinObjs (void);
static void Kernel_CheckMemory (void);
static void Kernel_ClockHandler (void);
static void Kernel_Copy4 (INT32 src, INT32 dst, INT32 size4);
static INT32 Kernel_DR0 (void);
static INT32 Kernel_DR1 (void);
static INT32 Kernel_DR2 (void);
static INT32 Kernel_DR3 (void);
static INT32 Kernel_DR6 (void);
static INT32 Kernel_DR7 (void);
static INT32 Kernel_DS (void);
static void Kernel_DefaultDisableGC (void);
static void Kernel_DefaultEnableGC (void);
static BOOLEAN Kernel_Detect486 (void);
static BOOLEAN Kernel_Detect586 (void);
static BOOLEAN Kernel_DetectCoprocessor (void);
static void Kernel_DisableEmulation (void);
static void Kernel_DisableMathTaskEx (void);
export void Kernel_DisposeDMA (INT32 size, INT32 adr);
static INT32 Kernel_ES (void);
static void Kernel_EnableEmulation (void);
static void Kernel_EnableMM (INT32 pd);
static void Kernel_ExceptionHandler (void);
export BOOLEAN Kernel_Expired (Kernel_MilliTimer *t, ADDRESS *t__typ);
static INT32 Kernel_FS (void);
static void Kernel_Fill4 (INT32 dst, INT32 size4, INT32 filler);
export void Kernel_FinalizeModule (Kernel_Module m);
static void Kernel_FinalizeObjs (void);
export void Kernel_GC (void);
static INT32 Kernel_GS (void);
static INT16 Kernel_GetCMOS (INT8 i);
export void Kernel_GetClock (INT32 *time, INT32 *date);
export void Kernel_GetConfig (CHAR *name, ADDRESS name__len, CHAR *val, ADDRESS val__len);
static UINT32 Kernel_GetFlags (void);
export void Kernel_GetInit (INT32 n, INT32 *val);
export void Kernel_GetLog (CHAR *val, ADDRESS val__len);
export void Kernel_GetMarkedLog (CHAR *val, ADDRESS val__len);
export Kernel_Module Kernel_GetMod (INT32 pc);
export INT32 Kernel_GetTimer (void);
static void Kernel_GoFrom0To3 (INT32 ss, INT32 sp, INT32 cs, Kernel_Proc ip);
static void Kernel_HLT (void);
export void Kernel_Idle (INT32 code);
static void Kernel_InitClock (void);
static void Kernel_InitHeap (void);
static void Kernel_InitInterrupts (void);
static void Kernel_InitMemory (void);
static void Kernel_InitProcessor (void);
static void Kernel_InitRuntime (void);
static void Kernel_InitTimer (void);
static void Kernel_InitTracing (INT32 *top);
static void Kernel_InitTrapHandling (void);
export void Kernel_InstallIP (Kernel_Proc p, INT16 i);
export void Kernel_InstallLoop (Kernel_Proc p);
export void Kernel_InstallTermHandler (Kernel_Proc h);
export void Kernel_InstallTrap (Kernel_TrapHandler p);
static void Kernel_InterruptHandler (void);
static BOOLEAN Kernel_IsRAM (INT32 adr);
export INT32 Kernel_LargestAvailable (void);
static void Kernel_LoadGDT (INT32 base, INT32 size);
static void Kernel_LoadIDT (INT32 base, INT32 size);
static void Kernel_LoadSegRegs (INT32 data);
static void Kernel_MapMem (INT32 pd, INT32 virtAdr, INT32 size, INT32 phys);
static void Kernel_MapPage (INT32 pd, INT32 virt, INT32 phys);
export void Kernel_MapPhysical (INT32 physAdr, INT32 size, INT32 *virtAdr);
static INT32 Kernel_MappedPage (INT32 pd, INT32 virt);
static void Kernel_Mark (Kernel_BlockPtr block);
static void Kernel_NMIHandler (void);
static void Kernel_NewArr (INT32 *p, Kernel_Tag eltag, INT32 nofelem, INT32 nofdim);
static Kernel_InitPtr Kernel_NewBlock (INT32 size);
export void Kernel_NewDMA (INT32 size, INT32 *adr, INT32 *phys);
static void Kernel_NewRec (INT32 *p, Kernel_Tag tag);
static void Kernel_NewSys (INT32 *p, INT32 size);
static void Kernel_PutCMOS (INT8 i, CHAR val);
static void Kernel_ReadBootTable (void);
static void Kernel_ReadClock (void);
static void Kernel_ReadMSR (INT32 msr, INT32 lowadr, INT32 highadr);
static void Kernel_Reboot (void);
export void Kernel_RegisterObject (SYSTEM_PTR obj, Kernel_Finalizer fin, BOOLEAN basic);
export void Kernel_RemoveIP (Kernel_Proc p, INT16 i);
static INT32 Kernel_SS (void);
export void Kernel_SetClock (INT32 time, INT32 date);
static void Kernel_SetFlags (UINT32 flags);
export void Kernel_SetLogMark (void);
static void Kernel_SetTR (INT32 tr);
export void Kernel_SetTimer (Kernel_MilliTimer *t, ADDRESS *t__typ, INT32 ms);
static void Kernel_Setup486Flags (void);
static void Kernel_Setup586Flags (void);
static void Kernel_SetupFPU (void);
static void Kernel_SetupFlags (void);
static void Kernel_ShowInt (INT32 bp, CHAR *msg, ADDRESS msg__len);
static void Kernel_ShowState (INT32 error, INT32 fp, INT32 pc, INT32 pf);
export void Kernel_Shutdown (INT32 code);
static void Kernel_StoreFPEnv (INT32 adr);
static INT32 Kernel_StrToInt (CHAR *s, ADDRESS s__len);
static void Kernel_Sweep (void);
static void Kernel_SwitchToLevel3 (INT32 ss, INT32 sp, INT32 cs);
static void Kernel_TimerHandler (void);
static INT16 Kernel_ToBCD (INT32 x);
static void Kernel_Unexpected (void);
export INT32 Kernel_Used (void);
static void Kernel_V86Exit (void);
static void Kernel_V86IntHandler (void);
static void Kernel_V86Switch (void);
static void Kernel_Wait (void);
export void Kernel_WriteChar (CHAR c);
static void Kernel_WriteFlags (INT32 f);
export void Kernel_WriteHex (INT32 x, INT32 w);
export void Kernel_WriteInt (INT32 x, INT32 w);
export void Kernel_WriteLn (void);
static void Kernel_WriteMSR (INT32 msr, UINT32 low, UINT32 high);
export void Kernel_WriteMemory (INT32 adr, INT32 size);
export void Kernel_WriteString (CHAR *s, ADDRESS s__len);
static void Kernel_WriteType (INT32 t);


static UINT32 Kernel_GetFlags (void)
{
	__RETCHK;
}

static void Kernel_SetFlags (UINT32 flags)
{
}

static void Kernel_Copy4 (INT32 src, INT32 dst, INT32 size4)
{
}

static void Kernel_Fill4 (INT32 dst, INT32 size4, INT32 filler)
{
}

void Kernel_WriteChar (CHAR c)
{
	UINT32 status, flags;
	INT32 adr;
	flags = Kernel_GetFlags();
	__CLI();
	if (Kernel_traceConsole) {
		if (c == 0x0d) {
			if ((int)__MOD(Kernel_displayPos, 160) != 0) {
				Kernel_displayPos -= (int)__MOD(Kernel_displayPos, 160);
			}
		} else if (c == 0x0a) {
			Kernel_displayPos += 160;
		} else {
			__PUT(753664 + Kernel_displayPos, (INT16)(1792 + (INT16)c), INT16);
			Kernel_displayPos += 2;
		}
		if (Kernel_displayPos >= 4000) {
			Kernel_displayPos -= 160;
			Kernel_Copy4(753824, 753664, 960);
			Kernel_Fill4(757504, 40, 119539488);
		}
		__PORTOUT(980, 0x0e, CHAR);
		__PORTOUT(981, (CHAR)__ASHR(__ASHR(Kernel_displayPos, 1), 8), CHAR);
		__PORTOUT(980, 0x0f, CHAR);
		__PORTOUT(981, (CHAR)__MASK(__ASHR(Kernel_displayPos, 1), -256), CHAR);
	}
	if (Kernel_tspeed > 0) {
		if (Kernel_tspeed != Kernel_pspeed) {
			__PORTOUT(Kernel_tbase + 3, 0x80, CHAR);
			__PORTOUT(Kernel_tbase + 1, (CHAR)__ASHR(__DIV(115200, Kernel_tspeed), 8), CHAR);
			__PORTOUT(Kernel_tbase, (CHAR)__DIV(115200, Kernel_tspeed), CHAR);
			__PORTOUT(Kernel_tbase + 3, 0x03, CHAR);
			__PORTOUT(Kernel_tbase + 4, 0x03, CHAR);
			__PORTOUT(Kernel_tbase + 1, 0x00, CHAR);
			Kernel_pspeed = Kernel_tspeed;
		}
		do {
			__PORTIN(Kernel_tbase + 5, __VAL(CHAR, status), CHAR);
		} while (!(((status & 0x60)) == 0x60));
		__PORTOUT(Kernel_tbase, c, CHAR);
	}
	if (Kernel_traceBufAdr != 0) {
		adr = (int)__MOD(Kernel_traceTail + 1, Kernel_traceBufSize);
		if (adr != Kernel_traceHead) {
			__PUT(Kernel_traceBufAdr + Kernel_traceTail, c, CHAR);
			Kernel_traceTail = adr;
		}
	}
	if (Kernel_tlpt > 0) {
		do {
			__PORTIN(Kernel_tlpt + 1, __VAL(CHAR, status), CHAR);
			__PORTIN(Kernel_tlpt + 1, __VAL(CHAR, status), CHAR);
		} while (!__IN(7, status, 32));
		__PORTOUT(Kernel_tlpt, c, CHAR);
		__PORTOUT(Kernel_tlpt + 2, 0x0d, CHAR);
		__PORTOUT(Kernel_tlpt + 2, 0x0d, CHAR);
		__PORTOUT(Kernel_tlpt + 2, 0x0c, CHAR);
	}
	Kernel_SetFlags(flags);
}

void Kernel_WriteString (CHAR *s, ADDRESS s__len)
{
	INT16 i;
	__DUP(s, s__len, CHAR);
	i = 0;
	while (s[__X(i, s__len)] != 0x00) {
		Kernel_WriteChar(s[__X(i, s__len)]);
		i += 1;
	}
	__DEL(s);
}

void Kernel_WriteLn (void)
{
	Kernel_WriteChar(0x0d);
	Kernel_WriteChar(0x0a);
}

void Kernel_WriteInt (INT32 x, INT32 w)
{
	INT32 i, x0;
	CHAR a[12];
	CHAR s[2];
	if (x < 0) {
		if (x == (-2147483647-1)) {
			Kernel_WriteString((CHAR*)"-2147483648", 12);
			return;
		} else {
			w -= 1;
			x0 = -x;
		}
	} else {
		x0 = x;
	}
	i = 0;
	do {
		a[__X(i, 12)] = (CHAR)((int)__MOD(x0, 10) + 48);
		x0 = __DIV(x0, 10);
		i += 1;
	} while (!(x0 == 0));
	s[0] = ' ';
	s[1] = 0x00;
	while (w > i) {
		Kernel_WriteString(s, 2);
		w -= 1;
	}
	s[0] = '-';
	if (x < 0) {
		Kernel_WriteString(s, 2);
	}
	do {
		i -= 1;
		s[0] = a[__X(i, 12)];
		Kernel_WriteString(s, 2);
	} while (!(i == 0));
}

void Kernel_WriteHex (INT32 x, INT32 w)
{
	CHAR buf[10];
	INT32 i, j, _for__130;
	if (w >= 0) {
		j = 8;
	} else {
		j = 2;
		w = -w;
	}
	_for__130 = w;
	i = j + 1;
	while (i <= _for__130) {
		Kernel_WriteChar(' ');
		i += 1;
	}
	i = j - 1;
	while (i >= 0) {
		buf[__X(i, 10)] = (CHAR)(__MASK(x, -16) + 48);
		if (buf[__X(i, 10)] > '9') {
			buf[__X(i, 10)] = (CHAR)((((INT16)buf[__X(i, 10)] - 48) + 65) - 10);
		}
		x = __ASHR(x, 4);
		i += -1;
	}
	buf[__X(j, 10)] = 0x00;
	Kernel_WriteString(buf, 10);
}

void Kernel_WriteMemory (INT32 adr, INT32 size)
{
	INT32 i, j;
	CHAR buf[4];
	INT32 _for__137, _for__136, _for__135;
	buf[1] = 0x00;
	size = (adr + size) - 1;
	_for__137 = size;
	i = adr;
	while (i <= _for__137) {
		Kernel_WriteHex(i, 9);
		_for__136 = i + 15;
		j = i;
		while (j <= _for__136) {
			if (j <= size) {
				__GET(j, buf[0], CHAR);
				Kernel_WriteHex(__VAL(INT8, buf[0]), -3);
			} else {
				__MOVE("   ", buf, 4);
				Kernel_WriteString(buf, 4);
				buf[1] = 0x00;
			}
			j += 1;
		}
		buf[0] = ' ';
		Kernel_WriteString(buf, 4);
		_for__135 = i + 15;
		j = i;
		while (j <= _for__135) {
			if (j <= size) {
				__GET(j, buf[0], CHAR);
				if (buf[0] < ' ' || buf[0] >= 0x7f) {
					buf[0] = '.';
				}
				Kernel_WriteString(buf, 4);
			}
			j += 1;
		}
		Kernel_WriteLn();
		i += 16;
	}
}

static void Kernel_Bits (CHAR *s, ADDRESS s__len, UINT32 x, INT32 ofs, INT32 n)
{
	__DUP(s, s__len, CHAR);
	Kernel_WriteString(s, s__len);
	Kernel_WriteChar('=');
	do {
		n -= 1;
		if (__IN(ofs + n, x, 32)) {
			Kernel_WriteChar('1');
		} else {
			Kernel_WriteChar('0');
		}
	} while (!(n == 0));
	__DEL(s);
}

static void Kernel_WriteFlags (INT32 f)
{
	UINT32 s, t;
	s = (UINT32)f;
	Kernel_WriteHex(f, 8);
	Kernel_WriteString((CHAR*)" (", 3);
	t = (((((__LSHR(s, 6, 32) & 0x20) | (__LSHL(s, 4, 32) & 0x10)) | (__LSHL(s, 1, 32) & 0x08)) | (__LSHR(s, 2, 32) & 0x04)) | (__LSHR(s, 5, 32) & 0x02)) | (__LSHR(s, 7, 32) & 0x01);
	Kernel_Bits((CHAR*)"OCPAZS", 7, t, 0, 6);
	Kernel_Bits((CHAR*)" IT", 4, s, 8, 2);
	Kernel_Bits((CHAR*)" D", 3, s, 10, 1);
	Kernel_Bits((CHAR*)" IOPL", 6, s, 12, 2);
	Kernel_Bits((CHAR*)" NT", 4, s, 14, 1);
	Kernel_Bits((CHAR*)" AC,VM,RF", 10, s, 16, 3);
	Kernel_WriteChar(')');
}

static void Kernel_Wait (void)
{
}

static void Kernel_Reboot (void)
{
}

Kernel_Module Kernel_GetMod (INT32 pc)
{
	Kernel_Module m;
	INT32 base;
	m = Kernel_modules;
	while (m != NIL) {
		base = (ADDRESS)&(m->code->data)[0];
		if ((base <= pc && pc <= base)) {
			return m;
		} else if ((((ADDRESS)&(m->data->data)[0]) <= pc && pc <= (ADDRESS)&(m->data->data)[0])) {
			return m;
		} else {
			m = m->next;
		}
	}
	return NIL;
}

static void Kernel_ShowInt (INT32 bp, CHAR *msg, ADDRESS msg__len)
{
	INT32 pc;
	Kernel_Module m;
	__DUP(msg, msg__len, CHAR);
	__GET(bp + 48, pc, INT32);
	Kernel_WriteString(msg, msg__len);
	m = Kernel_GetMod(pc);
	if (m != NIL) {
		Kernel_WriteString(m->name, 32);
		Kernel_WriteString((CHAR*)"  PC = ", 8);
		Kernel_WriteInt(pc - (ADDRESS)&(m->code->data)[0], 1);
	} else {
		Kernel_WriteString((CHAR*)"unknown module", 15);
	}
	Kernel_WriteLn();
	__DEL(msg);
}

static void Kernel_SetupFPU (void)
{
}

static void Kernel_GoFrom0To3 (INT32 ss, INT32 sp, INT32 cs, Kernel_Proc ip)
{
}

static INT32 Kernel_CR0 (void)
{
	return 0;
}

static INT32 Kernel_CR2 (void)
{
	return 0;
}

static INT32 Kernel_CR3 (void)
{
	return 0;
}

static INT32 Kernel_CR4 (void)
{
	return 0;
}

static INT32 Kernel_DR0 (void)
{
	return 0;
}

static INT32 Kernel_DR1 (void)
{
	return 0;
}

static INT32 Kernel_DR2 (void)
{
	return 0;
}

static INT32 Kernel_DR3 (void)
{
	return 0;
}

static INT32 Kernel_DR6 (void)
{
	return 0;
}

static INT32 Kernel_DR7 (void)
{
	return 0;
}

static INT32 Kernel_DS (void)
{
	return 0;
}

static INT32 Kernel_ES (void)
{
	return 0;
}

static INT32 Kernel_FS (void)
{
	return 0;
}

static INT32 Kernel_GS (void)
{
	return 0;
}

static INT32 Kernel_SS (void)
{
	return 0;
}

static void Kernel_StoreFPEnv (INT32 adr)
{
}

static void Kernel_CLTS (void)
{
}

static void Kernel_ExceptionHandler (void)
{
	INT32 bp, err, fp, pc, cs, osp;
	UINT32 flags;
	Kernel_trapCR[0] = Kernel_CR0();
	Kernel_trapCR[2] = Kernel_CR2();
	Kernel_trapCR[3] = Kernel_CR3();
	if (Kernel_cpu >= 5) {
		Kernel_trapCR[4] = Kernel_CR4();
	}
	Kernel_trapDR[0] = Kernel_DR0();
	Kernel_trapDR[1] = Kernel_DR1();
	Kernel_trapDR[2] = Kernel_DR2();
	Kernel_trapDR[3] = Kernel_DR3();
	Kernel_trapDR[6] = Kernel_DR6();
	Kernel_trapDR[7] = Kernel_DR7();
	Kernel_CLTS();
	__STI();
	__GETREG(5, bp, INT32);
	__GET(bp + 48, pc, INT32);
	__GET(bp + 52, cs, INT32);
	__GET(bp + 56, flags, UINT32);
	__GET(bp + 40, err, INT32);
	if ((Kernel_oldcopro && err == 45)) {
		__PORTOUT(240, 0x00, CHAR);
		__CLI();
		__PORTOUT(160, ' ', CHAR);
		__PORTOUT(32, ' ', CHAR);
		__STI();
		err = 16;
	}
	err = -err;
	if (err == -3) {
		pc -= 1;
		if (__IN(17, flags, 32)) {
		} else if (__MASK(cs, -4) == 0) {
			__GET(bp + 60, err, INT32);
		} else {
			__GET(bp + 60, fp, INT32);
			__GET(fp, err, INT32);
			if (err == 32767) {
				__PUT(bp + 60, fp + 4, INT32);
			}
		}
	} else if (err == -4) {
		pc -= 1;
	} else if (err == -14) {
		if (pc == 0) {
			if ((!__IN(17, flags, 32) && __MASK(cs, -4) != 0)) {
				__GET(bp + 60, osp, INT32);
				__GET(osp, pc, INT32);
			}
		}
	} else if (err == -16) {
		if (Kernel_copro) {
			Kernel_StoreFPEnv((ADDRESS)&Kernel_trapfpu[0]);
			__GET((ADDRESS)&Kernel_trapfpu[3], pc, INT32);
			if (__IN(2, Kernel_trapfpu[1], 32)) {
				err = -32;
			} else if (__IN(3, Kernel_trapfpu[1], 32)) {
				err = -33;
			} else if (__IN(0, Kernel_trapfpu[1], 32)) {
				err = -34;
			} else if (__IN(6, Kernel_trapfpu[1], 32)) {
				err = -35;
			} else if (__IN(1, Kernel_trapfpu[1], 32)) {
				err = -36;
			} else if (__IN(4, Kernel_trapfpu[1], 32)) {
				err = -37;
			} else if (__IN(5, Kernel_trapfpu[1], 32)) {
				err = -38;
			}
		}
	}
	if (Kernel_copro) {
		Kernel_SetupFPU();
	}
	__GET(bp + 16, fp, INT32);
	if (Kernel_handler0 != NIL) {
		(*Kernel_handler0)(err, fp, pc, Kernel_trapCR[2]);
	}
	if (Kernel_handler != NIL) {
		(*Kernel_handler)(err, fp, pc, Kernel_trapCR[2]);
	}
	if (!((err == 32767 && __MASK(cs, -4) != 0))) {
		if ((Kernel_loop != NIL && !Kernel_inGC)) {
			Kernel_GoFrom0To3(35, Kernel_StackOrg, 27, Kernel_loop);
		} else {
			Kernel_WriteString((CHAR*)"Trap in kernel, err=", 21);
			Kernel_WriteInt(err, 1);
			if (Kernel_tlpt > 0) {
				Kernel_WriteChar(0x0c);
			}
			for (;;) {
			}
		}
	}
}

static void Kernel_NMIHandler (void)
{
	INT32 bp;
	__GETREG(5, bp, INT32);
	Kernel_ShowInt(bp, (CHAR*)"NMI in ", 8);
	for (;;) {
	}
}

static void Kernel_Unexpected (void)
{
	INT32 bp;
	CHAR int_, isr, irr;
	__GETREG(5, bp, INT32);
	__GET(bp + 40, int_, CHAR);
	if (((INT16)int_ >= 32 && (INT16)int_ <= 47)) {
		if ((INT16)int_ >= 40) {
			__PORTOUT(160, 0x0b, CHAR);
			__PORTIN(160, isr, CHAR);
			__PORTOUT(160, 0x0a, CHAR);
			__PORTIN(160, irr, CHAR);
		} else {
			__PORTOUT(32, 0x0b, CHAR);
			__PORTIN(32, isr, CHAR);
			__PORTOUT(32, 0x0a, CHAR);
			__PORTIN(32, irr, CHAR);
		}
		Kernel_WriteString((CHAR*)"xi", 3);
		Kernel_WriteHex((INT16)int_, -2);
		Kernel_WriteHex((INT16)isr, -2);
		Kernel_WriteHex((INT16)irr, -2);
	} else if (int_ == 0x0f) {
		Kernel_WriteString((CHAR*)"xi", 3);
		Kernel_WriteHex((INT16)int_, -2);
	} else {
		__HALT(99);
	}
}

void Kernel_InstallTrap (Kernel_TrapHandler p)
{
	Kernel_handler = p;
}

void Kernel_InstallLoop (Kernel_Proc p)
{
	Kernel_loop = p;
}

void Kernel_InstallIP (Kernel_Proc p, INT16 i)
{
	UINT32 mask;
	INT8 j;
	if (i == 34) {
		i = 41;
	}
	if (Kernel_intHandler[__X(i, 48)][0] == Kernel_defaultHandler) {
		Kernel_intHandler[__X(i, 48)][0] = p;
	} else {
		j = 1;
		while (Kernel_intHandler[__X(i, 48)][__X(j, 4)] != NIL) {
			j += 1;
		}
		__ASSERT(j < 3, 0);
		Kernel_intHandler[__X(i, 48)][__X(j + 1, 4)] = NIL;
		Kernel_intHandler[__X(i, 48)][__X(j, 4)] = p;
	}
	if ((i >= 32 && i <= 39)) {
		__PORTIN(33, __VAL(CHAR, mask), CHAR);
		mask &= ~__SETOF(i - 32,32);
		__PORTOUT(33, __VAL(CHAR, mask), CHAR);
	} else if ((i >= 40 && i <= 47)) {
		__PORTIN(161, __VAL(CHAR, mask), CHAR);
		mask &= ~__SETOF(i - 40,32);
		__PORTOUT(161, __VAL(CHAR, mask), CHAR);
	}
}

void Kernel_RemoveIP (Kernel_Proc p, INT16 i)
{
	UINT32 mask;
	INT8 j;
	if (p != NIL) {
		j = 0;
		while ((Kernel_intHandler[__X(i, 48)][__X(j, 4)] != p && Kernel_intHandler[__X(i, 48)][__X(j, 4)] != NIL)) {
			j += 1;
		}
		__ASSERT(Kernel_intHandler[__X(i, 48)][__X(j, 4)] == p, 0);
	} else {
		__ASSERT(Kernel_intHandler[__X(i, 48)][1] == NIL, 0);
		j = 0;
	}
	mask = Kernel_GetFlags();
	__CLI();
	do {
		j += 1;
		Kernel_intHandler[__X(i, 48)][__X(j - 1, 4)] = Kernel_intHandler[__X(i, 48)][__X(j, 4)];
	} while (!(Kernel_intHandler[__X(i, 48)][__X(j, 4)] == NIL));
	if (Kernel_intHandler[__X(i, 48)][0] == NIL) {
		Kernel_intHandler[__X(i, 48)][0] = Kernel_defaultHandler;
	} else {
		i = -1;
	}
	Kernel_SetFlags(mask);
	if ((i >= 32 && i <= 39)) {
		__PORTIN(33, __VAL(CHAR, mask), CHAR);
		mask |= __SETOF(i - 32,32);
		__PORTOUT(33, __VAL(CHAR, mask), CHAR);
	} else if ((i >= 40 && i <= 47)) {
		__PORTIN(161, __VAL(CHAR, mask), CHAR);
		mask |= __SETOF(i - 40,32);
		__PORTOUT(161, __VAL(CHAR, mask), CHAR);
	}
}

INT32 Kernel_Available (void)
{
	INT32 i, avail;
	Kernel_FreeBlockPtr ptr;
	avail = 0;
	i = 0;
	while (i <= 9) {
		ptr = (Kernel_FreeBlockPtr)(ADDRESS)Kernel_A[__X(i, 10)];
		while (ptr != NIL) {
			avail += ptr->size;
			ptr = (Kernel_FreeBlockPtr)(ADDRESS)ptr->next;
		}
		i += 1;
	}
	return avail;
}

INT32 Kernel_LargestAvailable (void)
{
	INT32 i, max;
	Kernel_FreeBlockPtr ptr;
	i = 9;
	max = 0;
	while ((i >= 0 && max == 0)) {
		ptr = (Kernel_FreeBlockPtr)(ADDRESS)Kernel_A[__X(i, 10)];
		while (ptr != NIL) {
			if (ptr->size > max) {
				max = ptr->size;
			}
			ptr = (Kernel_FreeBlockPtr)(ADDRESS)ptr->next;
		}
		i -= 1;
	}
	return max;
}

INT32 Kernel_Used (void)
{
	return (Kernel_heapTop - 393216) - Kernel_Available();
}

typedef
	struct Kernel__1 *Tag0__84;

static void Kernel_Mark (Kernel_BlockPtr block)
{
	Kernel_BlockPtr father, field, currElem;
	INT32 offset;
	Tag0__84 tag, downtag, marked;
	UINT32 arraybit;
	__GET((INT32)(ADDRESS)block - 4, tag, Tag0__84);
	if (!__IN(3, (UINT32)(ADDRESS)block, 32)) {
		marked = (Tag0__84)(ADDRESS)((UINT32)(ADDRESS)tag | 0x01);
		if (tag != marked) {
			__PUT((INT32)(ADDRESS)block - 4, marked, Tag0__84);
			__GET((INT32)(((UINT32)(ADDRESS)tag & ~0x02)) - 4, marked, Tag0__84);
			(UINT32)(ADDRESS)marked &= ~__SETOF(0,32);
			__GET((INT32)(ADDRESS)marked - 4, arraybit, UINT32);
			arraybit |= __SETOF(0,32);
			__PUT((INT32)(ADDRESS)marked - 4, arraybit, UINT32);
			arraybit = ((UINT32)(ADDRESS)tag & 0x02);
			if (arraybit != 0x0) {
				currElem = block->firstElem;
				tag = (Tag0__84)(ADDRESS)(((UINT32)(ADDRESS)tag & ~arraybit));
			} else {
				currElem = block;
			}
			father = NIL;
			for (;;) {
				(INT32)(ADDRESS)tag += 4;
				offset = (INT32)((tag->ptroff & ~0x02));
				if (offset < 0) {
					(INT32)(ADDRESS)tag += offset;
					if ((arraybit != 0x0 && currElem != block->lastElemToMark)) {
						(INT32)(ADDRESS)currElem += (INT32)((tag->ptroff & ~0x02));
					} else {
						__PUT((INT32)(ADDRESS)block - 4, ((UINT32)(ADDRESS)tag | arraybit) | 0x01, UINT32);
						if (father == NIL) {
							break;
						}
						__GET((INT32)(ADDRESS)father - 4, tag, Tag0__84);
						arraybit = ((UINT32)(ADDRESS)tag & 0x02);
						tag = (Tag0__84)(ADDRESS)(((UINT32)(ADDRESS)tag & ~0x03));
						if (arraybit != 0x0) {
							currElem = father->currElem;
						} else {
							currElem = father;
						}
						offset = (INT32)(ADDRESS)currElem + (INT32)((tag->ptroff & ~0x02));
						__GET(offset, field, Kernel_BlockPtr);
						__PUT(offset, block, Kernel_BlockPtr);
						block = father;
						father = field;
					}
				} else {
					offset = (INT32)(ADDRESS)currElem + offset;
					__GET(offset, field, Kernel_BlockPtr);
					if (field != NIL) {
						__GET((INT32)(ADDRESS)field - 4, downtag, Tag0__84);
						if (((0x08 & (UINT32)(ADDRESS)field)) == 0x0) {
							marked = (Tag0__84)(ADDRESS)((UINT32)(ADDRESS)downtag | 0x01);
							if (downtag != marked) {
								__PUT((INT32)(ADDRESS)field - 4, marked, Tag0__84);
								__PUT((INT32)(ADDRESS)block - 4, ((UINT32)(ADDRESS)tag | arraybit) | 0x01, UINT32);
								if (arraybit != 0x0) {
									block->currElem = currElem;
								}
								__GET((INT32)(((UINT32)(ADDRESS)downtag & ~0x02)) - 4, marked, Tag0__84);
								(UINT32)(ADDRESS)marked &= ~__SETOF(0,32);
								__GET((INT32)(ADDRESS)marked - 4, arraybit, UINT32);
								arraybit |= __SETOF(0,32);
								__PUT((INT32)(ADDRESS)marked - 4, arraybit, UINT32);
								arraybit = ((UINT32)(ADDRESS)downtag & 0x02);
								if (arraybit != 0x0) {
									currElem = field->firstElem;
								} else {
									currElem = field;
								}
								__PUT(offset, father, Kernel_BlockPtr);
								father = block;
								block = field;
								tag = (Tag0__84)(ADDRESS)(((UINT32)(ADDRESS)downtag & ~arraybit));
							}
						} else {
							__GET((INT32)(((UINT32)(ADDRESS)downtag & ~0x02)) - 4, marked, Tag0__84);
							(UINT32)(ADDRESS)marked &= ~__SETOF(0,32);
							__GET((INT32)(ADDRESS)marked - 4, downtag, Tag0__84);
							(UINT32)(ADDRESS)downtag |= __SETOF(0,32);
							__PUT((INT32)(ADDRESS)marked - 4, downtag, Tag0__84);
						}
					}
				}
			}
		}
	} else {
		__GET((INT32)(((UINT32)(ADDRESS)tag & ~0x02)) - 4, tag, Tag0__84);
		(UINT32)(ADDRESS)tag &= ~__SETOF(0,32);
		__GET((INT32)(ADDRESS)tag - 4, arraybit, UINT32);
		arraybit |= __SETOF(0,32);
		__PUT((INT32)(ADDRESS)tag - 4, arraybit, UINT32);
	}
}

static void Kernel_CheckFinObjs (void)
{
	Kernel_FinObj n;
	INT32 tag;
	n = Kernel_FinObjs;
	while (n != NIL) {
		__GET(n->obj - 4, tag, INT32);
		n->marked = __IN(0, (UINT32)tag, 32);
		n = n->next;
	}
	n = Kernel_FinObjs;
	while (n != NIL) {
		if (!n->marked) {
			Kernel_Mark((Kernel_BlockPtr)(ADDRESS)n->obj);
		}
		n = n->next;
	}
}

static void Kernel_WriteType (INT32 t)
{
	INT32 m;
	CHAR name[32];
	__GET(t - 4, t, INT32);
	__GET(t + 48, m, INT32);
	__MOVE(m + 4, (ADDRESS)&name[0], 32);
	Kernel_WriteString(name, 32);
	Kernel_WriteChar('.');
	__MOVE(t + 16, (ADDRESS)&name[0], 32);
	if (name[0] == 0x00) {
		Kernel_WriteString((CHAR*)"<anon>", 7);
	} else {
		Kernel_WriteString(name, 32);
	}
}

static void Kernel_Sweep (void)
{
	Kernel_Blockm4Ptr p, end;
	Kernel_FreeBlockPtr lastp;
	Kernel_Tag tag, notmarked, tdesc;
	INT32 size, lastsize, i;
	INT32 lastA[10];
	INT32 t, live, dead, lsize, ssize;
	i = 0;
	while (i <= 9) {
		Kernel_A[__X(i, 10)] = 0;
		lastA[__X(i, 10)] = (ADDRESS)&Kernel_A[__X(i, 10)];
		i += 1;
	}
	p = (Kernel_Blockm4Ptr)(ADDRESS)Kernel_firstBlock;
	end = (Kernel_Blockm4Ptr)(ADDRESS)Kernel_endBlock;
	lastsize = 0;
	live = 0;
	dead = 0;
	lsize = 0;
	while (p != end) {
		tag = (Kernel_Tag)(ADDRESS)(((UINT32)(ADDRESS)p->tag & ~0x04));
		notmarked = (Kernel_Tag)(ADDRESS)(((UINT32)(ADDRESS)tag & ~0x01));
		tdesc = (Kernel_Tag)(ADDRESS)(((UINT32)(ADDRESS)notmarked & ~0x02));
		if (notmarked != tdesc) {
			size = (p->lastElemToMark + tdesc->size) - (INT32)(ADDRESS)p;
		} else {
			size = tdesc->size + 4;
		}
		ssize = size;
		size = (INT32)(((UINT32)((size + 32) - 1) & ~(UINT32)31));
		if (tag == notmarked) {
			if (((Kernel_traceheap & 0x09f8)) != 0x0) {
				if (__IN(11, Kernel_traceheap, 32)) {
					dead += 1;
				}
				if (notmarked != tdesc) {
					if (__IN(4, Kernel_traceheap, 32)) {
						Kernel_WriteString((CHAR*)"[DA ", 5);
						Kernel_WriteHex((INT32)(ADDRESS)p + 4, 8);
						__GET((ADDRESS)&p->lastElemToMark + 12, t, INT32);
						Kernel_WriteChar(' ');
						Kernel_WriteInt(t, 1);
						Kernel_WriteChar(' ');
						Kernel_WriteType((INT32)(ADDRESS)tdesc);
						Kernel_WriteString((CHAR*)"] ", 3);
					}
				} else if ((INT32)(ADDRESS)tdesc == (INT32)(ADDRESS)p + 4) {
					if (((Kernel_traceheap & 0x0120)) != 0x0) {
						if (__IN(2, (UINT32)(ADDRESS)p->tag, 32)) {
							if (__IN(8, Kernel_traceheap, 32)) {
								Kernel_WriteString((CHAR*)"[FB ", 5);
								Kernel_WriteHex((INT32)(ADDRESS)p, 8);
								__GET((ADDRESS)&p->lastElemToMark, t, INT32);
								Kernel_WriteChar(' ');
								Kernel_WriteInt(t, 1);
								Kernel_WriteString((CHAR*)"] ", 3);
							}
						} else {
							if (__IN(5, Kernel_traceheap, 32)) {
								Kernel_WriteString((CHAR*)"[DS ", 5);
								Kernel_WriteHex((INT32)(ADDRESS)p, 8);
								__GET((ADDRESS)&p->lastElemToMark, t, INT32);
								Kernel_WriteChar(' ');
								Kernel_WriteInt(t, 1);
								Kernel_WriteString((CHAR*)"] ", 3);
							}
						}
					}
				} else {
					if (__IN(3, Kernel_traceheap, 32)) {
						Kernel_WriteString((CHAR*)"[DR ", 5);
						Kernel_WriteHex((INT32)(ADDRESS)p + 4, 8);
						Kernel_WriteHex((INT32)(ADDRESS)tdesc, 9);
						Kernel_WriteChar(' ');
						Kernel_WriteType((INT32)(ADDRESS)tdesc);
						Kernel_WriteString((CHAR*)"] ", 3);
					}
				}
			}
			if (lastsize == 0) {
				lastp = (Kernel_FreeBlockPtr)(ADDRESS)p;
			}
			lastsize += size;
		} else {
			if ((__IN(11, Kernel_traceheap, 32) && (INT32)(ADDRESS)p != (INT32)(ADDRESS)Kernel_sysres - 28)) {
				live += 1;
				lsize += ssize;
			}
			p->tag = notmarked;
			if (lastsize > 0) {
				lastp->size = lastsize - 4;
				lastp->tag = (Kernel_Tag)(ADDRESS)((UINT32)((ADDRESS)&lastp->size) | 0x04);
				i = __ASHR(lastsize, 5);
				if (i > 9) {
					i = 9;
				}
				lastp->next = 0;
				__PUT(lastA[__X(i, 10)], lastp, Kernel_FreeBlockPtr);
				lastA[__X(i, 10)] = (ADDRESS)&lastp->next;
				lastsize = 0;
			}
		}
		(INT32)(ADDRESS)p += size;
	}
	if (lastsize > 0) {
		lastp->size = lastsize - 4;
		lastp->tag = (Kernel_Tag)(ADDRESS)((UINT32)((ADDRESS)&lastp->size) | 0x04);
		i = __ASHR(lastsize, 5);
		if (i > 9) {
			i = 9;
		}
		lastp->next = 0;
		__PUT(lastA[__X(i, 10)], lastp, Kernel_FreeBlockPtr);
		lastA[__X(i, 10)] = (ADDRESS)&lastp->next;
	}
	if (__IN(11, Kernel_traceheap, 32)) {
		Kernel_WriteString((CHAR*)"[", 2);
		Kernel_WriteInt(live, 1);
		Kernel_WriteString((CHAR*)" live (", 8);
		if (lsize != 0) {
			Kernel_WriteInt(__DIV(lsize, live), 1);
		}
		Kernel_WriteString((CHAR*)"), ", 4);
		Kernel_WriteInt(dead, 1);
		Kernel_WriteString((CHAR*)" dead]", 7);
	}
}

static void Kernel_CheckCandidates (void)
{
	INT32 i, j, h, p;
	Kernel_Blockm4Ptr block;
	Kernel_Tag tag, notmarked, tdesc;
	h = 1;
	do {
		h = h * 3 + 1;
	} while (!(h > Kernel_nofcand));
	do {
		h = __DIV(h, 3);
		i = h;
		while (i < Kernel_nofcand) {
			p = Kernel_candidates[__X(i, 1024)];
			j = i;
			while ((j >= h && Kernel_candidates[__X(j - h, 1024)] > p)) {
				Kernel_candidates[__X(j, 1024)] = Kernel_candidates[__X(j - h, 1024)];
				j = j - h;
			}
			Kernel_candidates[__X(j, 1024)] = p;
			i += 1;
		}
	} while (!(h == 1));
	block = (Kernel_Blockm4Ptr)(ADDRESS)Kernel_firstBlock;
	i = 0;
	p = Kernel_candidates[__X(i, 1024)];
	for (;;) {
		if (p <= (INT32)(ADDRESS)block + 4) {
			if (p == (INT32)(ADDRESS)block + 4) {
				Kernel_Mark((Kernel_BlockPtr)(ADDRESS)p);
			}
			i += 1;
			if (i == Kernel_nofcand) {
				break;
			}
			p = Kernel_candidates[__X(i, 1024)];
		} else if (p <= (INT32)(ADDRESS)block + 28) {
			if (p == (INT32)(ADDRESS)block + 28) {
				Kernel_Mark((Kernel_BlockPtr)(ADDRESS)((INT32)(ADDRESS)block + 4));
			}
			i += 1;
			if (i == Kernel_nofcand) {
				break;
			}
			p = Kernel_candidates[__X(i, 1024)];
		} else {
			tag = block->tag;
			notmarked = (Kernel_Tag)(ADDRESS)(((UINT32)(ADDRESS)tag & ~0x05));
			tdesc = (Kernel_Tag)(ADDRESS)(((UINT32)(ADDRESS)notmarked & ~0x02));
			if (notmarked != tdesc) {
				h = (block->lastElemToMark + tdesc->size) - (INT32)(ADDRESS)block;
			} else {
				h = tdesc->size + 4;
			}
			(INT32)(ADDRESS)block += (INT32)(((UINT32)((h + 32) - 1) & ~(UINT32)31));
			if (block == (Kernel_Blockm4Ptr)(ADDRESS)Kernel_endBlock) {
				break;
			}
		}
	}
	Kernel_nofcand = 0;
}

static void Kernel_Candidate (INT32 p)
{
	INT32 tag, tag0;
	if ((p > Kernel_firstBlock && p < Kernel_endBlock)) {
		if (__MASK(p, -32) == 0) {
			__GET(p - 4, tag, INT32);
			if (__IN(__MASK(tag, -8), 0x05, 32)) {
				Kernel_candidates[__X(Kernel_nofcand, 1024)] = p;
				Kernel_nofcand += 1;
			}
		} else if (__MASK(p, -16) == 8) {
			__GET(p - 4, tag, INT32);
			if ((((__MASK(tag, -32) == 0 && tag > Kernel_firstBlock)) && tag < Kernel_endBlock)) {
				__GET(tag - 4, tag0, INT32);
				if (tag0 == tag) {
					Kernel_candidates[__X(Kernel_nofcand, 1024)] = p;
					Kernel_nofcand += 1;
				}
			}
		}
	}
}

static void Kernel_FinalizeObjs (void)
{
	Kernel_FinObj n, prev;
	n = Kernel_FinObjs;
	while (n != NIL) {
		if (!n->marked) {
			if (n == Kernel_FinObjs) {
				Kernel_FinObjs = Kernel_FinObjs->next;
			} else {
				prev->next = n->next;
			}
			if (__IN(6, Kernel_traceheap, 32)) {
				Kernel_WriteString((CHAR*)"[Fin", 5);
				Kernel_WriteHex(n->obj, 9);
				Kernel_WriteString((CHAR*)"] ", 3);
			}
			(*n->fin)((SYSTEM_PTR)(ADDRESS)n->obj);
		} else {
			prev = n;
		}
		n = n->next;
	}
}

void Kernel_GC (void)
{
	Kernel_Module m;
	INT32 i, p, sp, ptradr;
	Kernel_BlockPtr ptr;
	INT32 avail, largest, t0, tf0, tf1, st;
	Kernel_inGC = 1;
	if (((Kernel_traceheap & 0xffff)) != 0x0) {
		Kernel_WriteString((CHAR*)"(GC", 4);
		if (__IN(10, Kernel_traceheap, 32)) {
			avail = Kernel_Available();
			largest = Kernel_LargestAvailable();
		}
		st = Kernel_ticks;
	}
	m = Kernel_modules;
	while (m != NIL) {
		Kernel_Mark((Kernel_BlockPtr)(ADDRESS)m);
		if (i > 0) {
			ptradr = (ADDRESS)&(m->ptrTab->data)[0];
		}
		while (i > 0) {
			__GET(ptradr, p, INT32);
			__GET(p, ptr, Kernel_BlockPtr);
			if (ptr != NIL) {
				Kernel_Mark(ptr);
			}
			i -= 1;
			ptradr += 4;
		}
		if (i > 0) {
			ptradr = (ADDRESS)&(m->tdescs->data)[0];
		}
		while (i > 0) {
			__GET(ptradr, ptr, Kernel_BlockPtr);
			Kernel_Mark(ptr);
			i -= 1;
			ptradr += 4;
		}
		m = m->next;
	}
	if (Kernel_GCstack) {
		__GETREG(4, sp, INT32);
		__ASSERT(sp <= Kernel_StackOrg, 0);
		Kernel_nofcand = 0;
		while (sp < Kernel_StackOrg) {
			__GET(sp, p, INT32);
			Kernel_Candidate(p);
			sp += 4;
		}
		if (Kernel_nofcand > 0) {
			Kernel_CheckCandidates();
		}
	}
	Kernel_CheckFinObjs();
	Kernel_Sweep();
	if ((Kernel_reserve == NIL && Kernel_firstTry)) {
		if (Kernel_LargestAvailable() >= 65528) {
			Kernel_NewSys(&p, 65528);
			Kernel_reserve = (Kernel_BlockPtr)(ADDRESS)p;
		}
	}
	if (__IN(7, Kernel_traceheap, 32)) {
		t0 = (ADDRESS)&Kernel_A[9];
		Kernel_WriteString((CHAR*)"[FP", 4);
		for (;;) {
			__GET(t0, t0, INT32);
			if (t0 == 0) {
				break;
			}
			tf0 = t0 + 12;
			__GET(t0 + 4, tf1, INT32);
			tf1 = (tf1 - 8) + tf0;
			tf0 += __MASK(-tf0, -4096);
			tf1 -= __MASK(tf1, -4096);
			if (tf0 < tf1) {
				Kernel_WriteHex(tf0, 9);
				Kernel_WriteChar(' ');
				Kernel_WriteInt(__ASHR(tf1 - tf0, 12), 1);
			}
			t0 = t0 + 8;
		}
		Kernel_WriteString((CHAR*)" PF] ", 6);
	}
	Kernel_inGC = 0;
	Kernel_FinalizeObjs();
	if (((Kernel_traceheap & 0xffff)) != 0x0) {
		st = Kernel_ticks - st;
		if (__IN(10, Kernel_traceheap, 32)) {
			avail = Kernel_Available() - avail;
			largest = Kernel_LargestAvailable() - largest;
			Kernel_WriteInt(avail, 1);
			Kernel_WriteString((CHAR*)" +", 3);
			Kernel_WriteInt(largest, 1);
		}
		Kernel_WriteChar(' ');
		Kernel_WriteInt(__DIV(st * 1000, 1000), 1);
		Kernel_WriteString((CHAR*)"ms", 3);
		Kernel_WriteString((CHAR*)" CG)", 5);
		Kernel_WriteLn();
	}
	if (Kernel_break) {
		Kernel_break = 0;
		__HALT(13);
	}
}

static Kernel_InitPtr Kernel_NewBlock (INT32 size)
{
	INT32 i, rest, adr, AN;
	Kernel_InitPtr ptr;
	Kernel_FreeBlockPtr restptr;
	if (Kernel_break) {
		Kernel_break = 0;
		__HALT(13);
	}
	if (size < 0) {
		__HALT(14);
	}
	i = __ASHR(size, 5);
	if (i > 9) {
		i = 9;
	}
	adr = ((ADDRESS)&Kernel_A[0]) + __ASHL(i, 2);
	AN = (ADDRESS)&Kernel_A[9];
	for (;;) {
		__GET(adr, ptr, Kernel_InitPtr);
		if (adr == AN) {
			for (;;) {
				if (ptr == NIL) {
					if (Kernel_firstTry) {
						Kernel_GC();
						Kernel_firstTry = 0;
						ptr = Kernel_NewBlock(size);
						Kernel_firstTry = 1;
						return ptr;
					} else {
						Kernel_reserve = NIL;
						Kernel_GC();
						Kernel_firstTry = 1;
						__HALT(14);
					}
				}
				if (ptr->z0 + 4 >= size) {
					break;
				}
				adr = (ADDRESS)&ptr->z1;
				__GET(adr, ptr, Kernel_InitPtr);
			}
			break;
		}
		if (ptr != NIL) {
			break;
		}
		adr += 4;
	}
	__PUT(adr, ptr->z1, INT32);
	rest = (ptr->z0 + 4) - size;
	restptr = (Kernel_FreeBlockPtr)(ADDRESS)((INT32)(ADDRESS)ptr + size);
	if (rest > 0) {
		i = __ASHR(rest, 5);
		if (i > 9) {
			i = 9;
		}
		restptr->tag = (Kernel_Tag)(ADDRESS)((UINT32)((ADDRESS)&restptr->size) | 0x04);
		restptr->size = rest - 4;
		restptr->next = Kernel_A[__X(i, 10)];
		Kernel_A[__X(i, 10)] = (INT32)(ADDRESS)restptr;
	}
	return ptr;
}

static void Kernel_NewRec (INT32 *p, Kernel_Tag tag)
{
	INT32 size;
	Kernel_InitPtr ptr, init;
	__ASSERT(__MASK((INT32)(ADDRESS)tag, -8) == 0, 0);
	if (tag == NIL) {
		tag = (Kernel_Tag)(ADDRESS)Kernel_ptrElemTag;
	}
	size = (INT32)(((UINT32)(tag->size + 35) & ~(UINT32)31));
	ptr = Kernel_NewBlock(size);
	if (__IN(0, Kernel_traceheap, 32)) {
		Kernel_WriteString((CHAR*)"[NR ", 5);
		Kernel_WriteType((INT32)(ADDRESS)tag);
	}
	init = (Kernel_InitPtr)(ADDRESS)(((INT32)(ADDRESS)ptr + size) - 32);
	init->z0 = 0;
	init->z1 = 0;
	init->z2 = 0;
	init->z3 = 0;
	init->z4 = 0;
	init->z5 = 0;
	init->z6 = 0;
	while (init != ptr) {
		(INT32)(ADDRESS)init -= 32;
		init->z0 = 0;
		init->z1 = 0;
		init->z2 = 0;
		init->z3 = 0;
		init->z4 = 0;
		init->z5 = 0;
		init->z6 = 0;
		init->z7 = 0;
	}
	ptr->tag = tag;
	*p = (INT32)(ADDRESS)ptr + 4;
	if (__IN(0, Kernel_traceheap, 32)) {
		Kernel_WriteHex((INT32)*p, 9);
		Kernel_WriteString((CHAR*)"] ", 3);
	}
}

static void Kernel_NewSys (INT32 *p, INT32 size)
{
	Kernel_InitPtr ptr, init;
	if (__IN(2, Kernel_traceheap, 32)) {
		Kernel_WriteString((CHAR*)"[NS ", 5);
		Kernel_WriteInt(size, 1);
	}
	size = (INT32)(((UINT32)(size + 59) & ~(UINT32)31));
	ptr = Kernel_NewBlock(size);
	init = (Kernel_InitPtr)(ADDRESS)(((INT32)(ADDRESS)ptr + size) - 32);
	while (init != ptr) {
		init->tag = NIL;
		init->z0 = 0;
		init->z1 = 0;
		init->z2 = 0;
		init->z3 = 0;
		init->z4 = 0;
		init->z5 = 0;
		init->z6 = 0;
		(INT32)(ADDRESS)init -= 32;
	}
	ptr->tag = (Kernel_Tag)(ADDRESS)((ADDRESS)&ptr->z0);
	ptr->z0 = size - 4;
	ptr->z1 = -4;
	init->z2 = 0;
	init->z3 = 0;
	init->z4 = 0;
	ptr->z5 = (ADDRESS)&ptr->z0;
	init->z6 = 0;
	*p = (INT32)(ADDRESS)ptr + 28;
	if (__IN(2, Kernel_traceheap, 32)) {
		Kernel_WriteHex((INT32)*p, 9);
		Kernel_WriteString((CHAR*)"] ", 3);
	}
}

static void Kernel_NewArr (INT32 *p, Kernel_Tag eltag, INT32 nofelem, INT32 nofdim)
{
	INT32 size, firstElem, elSize, arrSize, vectSize;
	Kernel_InitPtr ptr, init;
	__ASSERT(__MASK((INT32)(ADDRESS)eltag, -4) == 0, 0);
	if (__IN(1, Kernel_traceheap, 32)) {
		Kernel_WriteString((CHAR*)"[NA ", 5);
		Kernel_WriteInt(nofelem, 1);
		Kernel_WriteChar(' ');
		Kernel_WriteInt(nofdim, 1);
	}
	if (eltag == NIL) {
		eltag = (Kernel_Tag)(ADDRESS)Kernel_ptrElemTag;
	}
	elSize = eltag->size;
	arrSize = nofelem * elSize;
	if (arrSize == 0) {
		Kernel_NewSys(&*p, __ASHL(nofdim, 2) + 12);
		return;
	}
	__ASSERT(arrSize > 0, 0);
	vectSize = (INT32)((UINT32)__ASHL(nofdim, 2) | (UINT32)4);
	if (eltag->ptroff == -4) {
		Kernel_NewSys(&*p, (arrSize + vectSize) + 12);
		__PUT(*p, ((UINT32)((arrSize + vectSize) + 15) & ~(UINT32)3), UINT32);
		return;
	}
	size = (INT32)(((UINT32)((arrSize + vectSize) + 47) & ~(UINT32)31));
	ptr = Kernel_NewBlock(size);
	init = (Kernel_InitPtr)(ADDRESS)(((INT32)(ADDRESS)ptr + size) - 32);
	while (init != ptr) {
		init->tag = NIL;
		init->z0 = 0;
		init->z1 = 0;
		init->z2 = 0;
		init->z3 = 0;
		init->z4 = 0;
		init->z5 = 0;
		init->z6 = 0;
		(INT32)(ADDRESS)init -= 32;
	}
	ptr->tag = (Kernel_Tag)(ADDRESS)((UINT32)(ADDRESS)eltag | 0x02);
	firstElem = ((ADDRESS)&ptr->z3) + vectSize;
	ptr->z0 = (firstElem + arrSize) - elSize;
	ptr->z2 = firstElem;
	ptr->z3 = 0;
	ptr->z4 = 0;
	ptr->z5 = 0;
	ptr->z6 = 0;
	*p = (INT32)(ADDRESS)ptr + 4;
	if (__IN(1, Kernel_traceheap, 32)) {
		Kernel_WriteHex((INT32)*p, 9);
		Kernel_WriteString((CHAR*)"] ", 3);
	}
}

void Kernel_NewDMA (INT32 size, INT32 *adr, INT32 *phys)
{
	INT32 p, s, min, prev;
	if (size >= 0) {
		if (__IN(9, Kernel_traceheap, 32)) {
			Kernel_WriteString((CHAR*)"[ND ", 5);
			Kernel_WriteInt(size, 1);
		}
		size += __MASK(-size, -4);
		__ASSERT((size > 0 && size <= 65536), 0);
		prev = (ADDRESS)&Kernel_dmafree;
		min = 2147483647;
		for (;;) {
			__GET(prev, p, INT32);
			if (p == 0) {
				break;
			}
			__GET(p, s, INT32);
			if ((s >= size && s < min)) {
				*adr = p;
				*phys = prev;
				min = s;
			}
			prev = p + 4;
		}
		if (min == 2147483647) {
			__HALT(14);
		}
		__GET(*adr, s, INT32);
		if (s == size) {
			__GET(*adr + 4, p, INT32);
			__PUT(*phys, p, INT32);
		} else {
			s -= size;
			__PUT(*adr, s, INT32);
			*adr += s;
		}
		*phys = *adr;
		if (__IN(9, Kernel_traceheap, 32)) {
			Kernel_WriteHex(*adr, 9);
			Kernel_WriteString((CHAR*)"] ", 3);
		}
	} else {
		Kernel_DisposeDMA(-size, *adr);
	}
}

void Kernel_DisposeDMA (INT32 size, INT32 adr)
{
	INT32 p, s, prev;
	if (__IN(9, Kernel_traceheap, 32)) {
		Kernel_WriteString((CHAR*)"[ND ", 5);
		Kernel_WriteInt(size, 1);
		Kernel_WriteHex(adr, 9);
		Kernel_WriteString((CHAR*)"] ", 3);
	}
	size += __MASK(-size, -4);
	__ASSERT((((((size > 0 && size <= 65536)) && adr >= Kernel_dma0)) && adr + size <= Kernel_dma1), 0);
	prev = (ADDRESS)&Kernel_dmafree;
	for (;;) {
		__GET(prev, p, INT32);
		if (p == 0) {
			break;
		}
		__GET(p, s, INT32);
		if ((p + s == adr && __MASK(adr, -65536) != 0)) {
			s += size;
			__PUT(p, s, INT32);
			return;
		} else if ((adr + size == p && __MASK(p, -65536) != 0)) {
			__PUT(adr, size + s, INT32);
			__GET(p + 4, p, INT32);
			__PUT(adr + 4, p, INT32);
			__PUT(prev, adr, INT32);
			return;
		}
		prev = p + 4;
	}
	__PUT(adr, size, INT32);
	__PUT(adr + 4, Kernel_dmafree, INT32);
	Kernel_dmafree = adr;
}

static void Kernel_AllocatePage (INT32 *p)
{
	if (Kernel_pageheap == Kernel_pageheap1) {
		Kernel_WriteString((CHAR*)"Kernel.AllocatePage: Out of pages", 34);
		Kernel_WriteLn();
		__HALT(99);
	}
	Kernel_pageheap -= 4096;
	*p = Kernel_pageheap;
}

static void Kernel_MapPage (INT32 pd, INT32 virt, INT32 phys)
{
	INT32 i, t, pt;
	__ASSERT(__MASK(virt, -4096) == 0, 0);
	__ASSERT(__MASK(pd, -4096) == 0, 0);
	i = __MASK(__ASHR(virt, 22), -1024);
	__GET(pd + __ASHL(i, 2), t, INT32);
	if (__ODD(t)) {
		pt = t - __MASK(t, -4096);
	} else {
		Kernel_AllocatePage(&pt);
		Kernel_Fill4(pt, 1024, 0);
		__PUT(pd + __ASHL(i, 2), pt + 7, INT32);
	}
	__PUT(pt + __ASHL(__MASK(__ASHR(virt, 12), -1024), 2), phys, INT32);
}

static INT32 Kernel_MappedPage (INT32 pd, INT32 virt)
{
	INT32 i, t, pt;
	__ASSERT(__MASK(virt, -4096) == 0, 0);
	__ASSERT(__MASK(pd, -4096) == 0, 0);
	i = __MASK(__ASHR(virt, 22), -1024);
	__GET(pd + __ASHL(i, 2), t, INT32);
	if (__ODD(t)) {
		pt = t - __MASK(t, -4096);
		__GET(pt + __ASHL(__MASK(__ASHR(virt, 12), -1024), 2), t, INT32);
		return t;
	} else {
		return 0;
	}
	__RETCHK;
}

static void Kernel_MapMem (INT32 pd, INT32 virtAdr, INT32 size, INT32 phys)
{
	__ASSERT((__MASK(virtAdr, -4096) == 0 && __MASK(size, -4096) == 0), 0);
	while (size != 0) {
		if (__ODD(Kernel_MappedPage(pd, virtAdr))) {
			__HALT(99);
		}
		Kernel_MapPage(pd, virtAdr, phys);
		virtAdr += 4096;
		phys += 4096;
		size -= 4096;
	}
}

void Kernel_MapPhysical (INT32 physAdr, INT32 size, INT32 *virtAdr)
{
	INT32 i, free;
	__ASSERT((__MASK(physAdr, -4096) == 0 && __MASK(size, -4096) == 0), 0);
	if ((physAdr >= 655360 && physAdr + size <= 1048576)) {
		*virtAdr = physAdr;
	} else {
		free = -1;
		i = 0;
		while (i <= 3) {
			if (Kernel_mapcache[__X(i, 4)].size != 0) {
				if ((physAdr == Kernel_mapcache[__X(i, 4)].physAdr && size == Kernel_mapcache[__X(i, 4)].size)) {
					*virtAdr = Kernel_mapcache[__X(i, 4)].virtAdr;
					return;
				}
			} else {
				if (free == -1) {
					free = i;
				}
			}
			i += 1;
		}
		*virtAdr = Kernel_mapPtr - size;
		Kernel_MapMem(Kernel_kernelpd, *virtAdr, size, physAdr + 7);
		Kernel_mapPtr = *virtAdr;
		if (free != -1) {
			Kernel_mapcache[__X(free, 4)].physAdr = physAdr;
			Kernel_mapcache[__X(free, 4)].size = size;
			Kernel_mapcache[__X(free, 4)].virtAdr = *virtAdr;
		}
	}
}

void Kernel_RegisterObject (SYSTEM_PTR obj, Kernel_Finalizer fin, BOOLEAN basic)
{
	Kernel_FinObj n;
	if (__IN(6, Kernel_traceheap, 32)) {
		Kernel_WriteString((CHAR*)"[RegObj", 8);
		Kernel_WriteHex((INT32)(ADDRESS)obj, 9);
		Kernel_WriteString((CHAR*)"] ", 3);
	}
	__ASSERT(obj != NIL, 0);
	__NEW(n, Kernel_FinObjNode);
	n->next = Kernel_FinObjs;
	n->obj = (INT32)(ADDRESS)obj;
	n->marked = 0;
	n->fin = fin;
	Kernel_FinObjs = n;
}

void Kernel_InstallTermHandler (Kernel_Proc h)
{
	INT32 codebase, handlerAdr;
	Kernel_Module m;
	BOOLEAN found;
	m = Kernel_modules;
	handlerAdr = (INT32)(ADDRESS)h;
	found = 0;
	while ((m != NIL && !found)) {
		codebase = (ADDRESS)&(m->code->data)[0];
		if ((codebase <= handlerAdr && handlerAdr <= codebase)) {
			found = 1;
		} else {
			m = m->next;
		}
	}
	if (found) {
		m->term = h;
	}
}

void Kernel_FinalizeModule (Kernel_Module m)
{
	Kernel_Proc h;
	INT32 beg, end;
	Kernel_FinObj n, prev;
	beg = (ADDRESS)&(m->code->data)[0];
	end = beg;
	n = Kernel_FinObjs;
	while (n != NIL) {
		if ((beg <= (INT32)(ADDRESS)n->fin && (INT32)(ADDRESS)n->fin <= end)) {
			if (n == Kernel_FinObjs) {
				Kernel_FinObjs = Kernel_FinObjs->next;
			} else {
				prev->next = n->next;
			}
			if (__IN(6, Kernel_traceheap, 32)) {
				Kernel_WriteString((CHAR*)"[Fin", 5);
				Kernel_WriteHex(n->obj, 9);
				Kernel_WriteString((CHAR*)"] ", 3);
			}
			(*n->fin)((SYSTEM_PTR)(ADDRESS)n->obj);
		} else {
			prev = n;
		}
		n = n->next;
	}
	if (m->term != NIL) {
		if (__IN(16, Kernel_traceheap, 32)) {
			Kernel_WriteString((CHAR*)"Calling TermHandler ", 21);
			Kernel_WriteString(m->name, 32);
			Kernel_WriteLn();
		}
		h = m->term;
		m->term = NIL;
		(*h)();
	}
}

static INT32 Kernel_StrToInt (CHAR *s, ADDRESS s__len)
{
	INT8 i, j;
	INT32 v, sgn, m;
	__DUP(s, s__len, CHAR);
	j = 0;
	while (s[__X(j, s__len)] != 0x00) {
		j += 1;
	}
	if ((j > 0 && __CAP(s[__X(j - 1, s__len)]) == 'H')) {
		m = 16;
		j -= 1;
	} else {
		m = 10;
	}
	v = 0;
	i = 0;
	if (s[__X(i, s__len)] == '-') {
		sgn = -1;
		i += 1;
	} else {
		sgn = 1;
	}
	while (i < j) {
		if ((s[__X(i, s__len)] >= '0' && s[__X(i, s__len)] <= '9')) {
			v = v * m + ((INT16)s[__X(i, s__len)] - 48);
		} else if ((__CAP(s[__X(i, s__len)]) >= 'A' && __CAP(s[__X(i, s__len)]) <= 'F')) {
			v = v * m + (((INT16)__CAP(s[__X(i, s__len)]) - 65) + 10);
		} else {
			sgn = 0;
			j = i;
		}
		i += 1;
	}
	__DEL(s);
	return sgn * v;
}

static INT16 Kernel_GetCMOS (INT8 i)
{
	CHAR c;
	__VAL(UINT32, i) |= __SETOF(7,32);
	__CLI();
	__PORTOUT(112, i, INT8);
	Kernel_Wait();
	__PORTIN(113, c, CHAR);
	__PORTOUT(112, 0x00, CHAR);
	__STI();
	return (INT16)c;
}

static void Kernel_PutCMOS (INT8 i, CHAR val)
{
	__VAL(UINT32, i) |= __SETOF(7,32);
	__CLI();
	__PORTOUT(112, i, INT8);
	Kernel_Wait();
	__PORTOUT(113, val, CHAR);
	__PORTOUT(112, 0x00, CHAR);
	__STI();
}

static void Kernel_ReadClock (void)
{
	Kernel_second = Kernel_GetCMOS(0);
	Kernel_minute = Kernel_GetCMOS(2);
	Kernel_hour = Kernel_GetCMOS(4);
	Kernel_day = Kernel_GetCMOS(7);
	Kernel_month = Kernel_GetCMOS(8);
	Kernel_year = Kernel_GetCMOS(9);
}

static void Kernel_ClockHandler (void)
{
	__STI();
	Kernel_clockints += 1;
	if (Kernel_clockmode == 0) {
		if (__IN(4, (UINT32)(Kernel_GetCMOS(12)), 32)) {
			Kernel_ReadClock();
		} else {
			Kernel_clockmissed += 1;
		}
	} else {
		Kernel_ReadClock();
	}
}

static void Kernel_InitClock (void)
{
	INT32 t;
	CHAR s[8];
	Kernel_second = -1;
	Kernel_GetConfig((CHAR*)"ClockMode", 10, (void*)s, 8);
	Kernel_clockmode = Kernel_StrToInt(s, 8);
	if (Kernel_clockmode != 1) {
		Kernel_InstallIP(Kernel_ClockHandler, 40);
		Kernel_PutCMOS(11, 0x12);
		t = Kernel_ticks;
		do {
		} while (!(Kernel_second != -1 || Kernel_ticks - t > 3000));
	}
	if (Kernel_second == -1) {
		Kernel_second = 0;
		Kernel_minute = 0;
		Kernel_hour = 0;
		Kernel_day = 0;
		Kernel_month = 0;
		Kernel_year = 0;
		if (Kernel_clockmode != 1) {
			Kernel_RemoveIP(Kernel_ClockHandler, 40);
		}
		Kernel_clockmode = 1;
	}
}

static INT32 Kernel_BCD2 (INT16 x)
{
	return __ASHR(x, 4) * 10 + __MASK(x, -16);
}

static INT16 Kernel_ToBCD (INT32 x)
{
	return (INT16)(__ASHL(__DIV(x, 10), 4) + (int)__MOD(x, 10));
}

void Kernel_GetClock (INT32 *time, INT32 *date)
{
	INT16 h, m, s, y, o, d;
	if (Kernel_clockmode == 1) {
		__CLI();
		do {
			do {
			} while (!(!__IN(7, (UINT32)(Kernel_GetCMOS(10)), 32)));
			Kernel_ReadClock();
			h = Kernel_hour;
			m = Kernel_minute;
			s = Kernel_second;
			y = Kernel_year;
			o = Kernel_month;
			d = Kernel_day;
			Kernel_ReadClock();
		} while (!((((((((((h == Kernel_hour && m == Kernel_minute)) && s == Kernel_second)) && y == Kernel_year)) && o == Kernel_month)) && d == Kernel_day)));
		__STI();
	} else {
		__CLI();
		h = Kernel_hour;
		m = Kernel_minute;
		s = Kernel_second;
		y = Kernel_year;
		o = Kernel_month;
		d = Kernel_day;
		__STI();
	}
	*time = __ASHL(__ASHL(Kernel_BCD2(h), 6) + Kernel_BCD2(m), 6) + Kernel_BCD2(s);
	y = (INT16)Kernel_BCD2(y);
	if (y < 90) {
		y += 100;
	}
	*date = __ASHL(__ASHL(y, 4) + Kernel_BCD2(o), 5) + Kernel_BCD2(d);
}

void Kernel_SetClock (INT32 time, INT32 date)
{
	Kernel_PutCMOS(11, 0x82);
	Kernel_second = Kernel_ToBCD(__MASK(time, -64));
	time = __ASHR(time, 6);
	Kernel_minute = Kernel_ToBCD(__MASK(time, -64));
	Kernel_hour = Kernel_ToBCD(__ASHR(time, 6));
	Kernel_day = Kernel_ToBCD(__MASK(date, -32));
	date = __ASHR(date, 5);
	Kernel_month = Kernel_ToBCD(__MASK(date, -16));
	Kernel_year = Kernel_ToBCD((int)__MOD(__ASHR(date, 4), 100));
	Kernel_PutCMOS(0, (CHAR)Kernel_second);
	Kernel_PutCMOS(2, (CHAR)Kernel_minute);
	Kernel_PutCMOS(4, (CHAR)Kernel_hour);
	Kernel_PutCMOS(7, (CHAR)Kernel_day);
	Kernel_PutCMOS(8, (CHAR)Kernel_month);
	Kernel_PutCMOS(9, (CHAR)Kernel_year);
	Kernel_PutCMOS(11, 0x12);
}

INT32 Kernel_GetTimer (void)
{
	return Kernel_ticks;
}

void Kernel_SetTimer (Kernel_MilliTimer *t, ADDRESS *t__typ, INT32 ms)
{
	if (ms < 5) {
		ms += 1;
	}
	(*t).target = Kernel_ticks + ms;
}

BOOLEAN Kernel_Expired (Kernel_MilliTimer *t, ADDRESS *t__typ)
{
	return Kernel_ticks - (*t).target >= 0;
}

static CHAR Kernel_Cap (CHAR ch)
{
	if ((ch >= 'a' && ch <= 'z')) {
		return __CAP(ch);
	} else {
		return ch;
	}
	__RETCHK;
}

void Kernel_GetConfig (CHAR *name, ADDRESS name__len, CHAR *val, ADDRESS val__len)
{
	INT32 i, src;
	CHAR ch;
	__DUP(name, name__len, CHAR);
	if (name[0] == '=') {
		__HALT(99);
	} else {
		src = Kernel_configadr;
		if (src != 0) {
			i = 0;
			while (name[__X(i, name__len)] != 0x00) {
				name[__X(i, name__len)] = Kernel_Cap(name[__X(i, name__len)]);
				i += 1;
			}
			for (;;) {
				__GET(src, ch, CHAR);
				if (ch == 0x00) {
					break;
				}
				i = 0;
				for (;;) {
					__GET(src, ch, CHAR);
					if (Kernel_Cap(ch) != name[__X(i, name__len)] || name[__X(i, name__len)] == 0x00) {
						break;
					}
					i += 1;
					src += 1;
				}
				if ((ch == 0x00 && name[__X(i, name__len)] == 0x00)) {
					i = 0;
					do {
						src += 1;
						__GET(src, ch, CHAR);
						val[__X(i, val__len)] = ch;
						i += 1;
					} while (!(ch == 0x00));
					val[__X(i, val__len)] = 0x00;
					__DEL(name);
					return;
				} else {
					while (ch != 0x00) {
						src += 1;
						__GET(src, ch, CHAR);
					}
					src += 1;
					do {
						__GET(src, ch, CHAR);
						src += 1;
					} while (!(ch == 0x00));
				}
			}
		}
		val[0] = 0x00;
	}
	__DEL(name);
}

void Kernel_GetLog (CHAR *val, ADDRESS val__len)
{
	INT32 i, max;
	BOOLEAN pass;
	i = 0;
	if (Kernel_traceBufAdr != 0) {
		pass = 0;
		while ((i < max && Kernel_traceHead != Kernel_traceTail)) {
			__GET(Kernel_traceBufAdr + Kernel_traceHead, val[__X(i, val__len)], CHAR);
			if (Kernel_traceHead == Kernel_traceMark) {
				pass = 1;
			}
			Kernel_traceHead = (int)__MOD(Kernel_traceHead + 1, Kernel_traceBufSize);
			i += 1;
		}
		if (pass) {
			Kernel_traceMark = Kernel_traceHead;
		}
	}
	val[__X(i, val__len)] = 0x00;
}

void Kernel_SetLogMark (void)
{
	Kernel_traceMark = Kernel_traceTail;
}

void Kernel_GetMarkedLog (CHAR *val, ADDRESS val__len)
{
	INT32 i, max;
	i = 0;
	if (Kernel_traceBufAdr != 0) {
		while ((i < max && Kernel_traceMark != Kernel_traceTail)) {
			__GET(Kernel_traceBufAdr + Kernel_traceMark, val[__X(i, val__len)], CHAR);
			Kernel_traceMark = (int)__MOD(Kernel_traceMark + 1, Kernel_traceBufSize);
			i += 1;
		}
	}
	val[__X(i, val__len)] = 0x00;
}

void Kernel_GetInit (INT32 n, INT32 *val)
{
	*val = Kernel_kpar[__X(n, 2)];
}

static void Kernel_DefaultEnableGC (void)
{
	Kernel_GClevel += 1;
}

static void Kernel_DefaultDisableGC (void)
{
	Kernel_GClevel -= 1;
}

static void Kernel_InitHeap (void)
{
	INT32 pt, i, t, stacksize, size, dmasize;
	Kernel_FreeBlockPtr f;
	Kernel_Module m;
	UINT32 set;
	struct Kernel__2 *td;
	INT32 high0, high1, low0, low1, free0, free1, prev;
	CHAR c;
	CHAR s[10];
	Kernel_Blockm4Ptr p;
	Kernel_Tag tag, tdesc;
	INT32 _for__61;
	Kernel_inGC = 0;
	Kernel_break = 0;
	Kernel_FinObjs = NIL;
	m = Kernel_modules;
	__ASSERT(m != NIL, 0);
	m = Kernel_modules;
	while (__STRCMP(m->name, "Kernel") != 0) {
		m = m->next;
	}
	Kernel_ptrElemTag = 0;
	do {
		if (__STRCMP(td->name, "PtrElemDesc") == 0) {
			Kernel_ptrElemTag = t;
		}
	} while (!(Kernel_ptrElemTag != 0));
	Kernel_GetConfig((CHAR*)"StackSize", 10, (void*)s, 10);
	stacksize = Kernel_StrToInt(s, 10);
	stacksize -= __MASK(stacksize, -4);
	if (stacksize <= 0) {
		stacksize = 131072;
	} else if (stacksize < 32768) {
		stacksize = 32768;
	}
	Kernel_GetConfig((CHAR*)"DMASize", 8, (void*)s, 10);
	dmasize = Kernel_StrToInt(s, 10);
	if (dmasize <= 0) {
		dmasize = 32768;
	} else if (dmasize < 8) {
		dmasize = 8;
	}
	dmasize += __MASK(-dmasize, -4096);
	Kernel_GetConfig((CHAR*)"PageHeap", 9, (void*)s, 10);
	Kernel_pageheap1 = __ASHL(Kernel_StrToInt(s, 10), 10);
	if (Kernel_pageheap1 == 0) {
		Kernel_pageheap1 = 16384;
	}
	Kernel_pageheap1 += __MASK(-Kernel_pageheap1, -4096);
	Kernel_WriteInt(__ASHR(Kernel_pageheap0 - Kernel_pageheap, 12), 1);
	Kernel_WriteString((CHAR*)" pages allocated, ", 19);
	Kernel_WriteInt(__ASHR(Kernel_pageheap1, 12), 1);
	Kernel_WriteString((CHAR*)" pages reserved", 16);
	Kernel_WriteLn();
	Kernel_pageheap1 = Kernel_pageheap - Kernel_pageheap1;
	Kernel_dma1 = Kernel_pageheap1;
	Kernel_dma0 = Kernel_dma1 - dmasize;
	if (__ASHR(Kernel_dma0, 16) != __ASHR(Kernel_dma1, 16)) {
		Kernel_dma0 -= __MASK(Kernel_dma1, -65536);
	}
	if (__MASK(Kernel_dma0, -65536) > 65528) {
		Kernel_dma0 -= 8;
	}
	free0 = Kernel_dma0;
	prev = (ADDRESS)&Kernel_dmafree;
	for (;;) {
		free1 = free0 + (65536 - __MASK(free0, -65536));
		if (free1 > Kernel_dma1) {
			free1 = Kernel_dma1;
		}
		if (free0 == free1) {
			break;
		}
		if (__IN(9, Kernel_traceheap, 32)) {
			Kernel_WriteHex(free0, 8);
			Kernel_WriteHex(free1, 10);
			Kernel_WriteInt(free1 - free0, 8);
			Kernel_WriteLn();
		}
		__PUT(free0, free1 - free0, INT32);
		__PUT(prev, free0, INT32);
		prev = free0 + 4;
		free0 = free1;
	}
	__PUT(prev, 0, INT32);
	__ASSERT((Kernel_dma0 < 4194304 && Kernel_dma1 < 4194304), 0);
	__GET(Kernel_v86pd, pt, INT32);
	pt -= __MASK(pt, -4096);
	_for__61 = __ASHR(Kernel_dma1, 12) - 1;
	i = __ASHR(Kernel_dma0, 12);
	while (i <= _for__61) {
		__GET(pt + __ASHL(i, 2), set, UINT32);
		__PUT(pt + __ASHL(i, 2), set | 0x02, UINT32);
		i += 1;
	}
	high0 = (INT32)(((UINT32)((((1048576 + stacksize) + 4) + 32) - 1) & ~(UINT32)31)) - 4;
	high1 = (INT32)(((UINT32)(Kernel_heapTop - 1) & ~(UINT32)31)) - 4;
	Kernel_StackOrg = high0;
	__GET(4118, low0, INT32);
	__ASSERT(__MASK(low0, -32) == 28, 0);
	low1 = ((INT32)(((UINT32)Kernel_dma0 & ~(UINT32)31)) - 4) - 32;
	__ASSERT(low1 - 64 >= low0, 0);
	if (((Kernel_traceheap & 0xffff)) != 0x0) {
		Kernel_WriteHex(low0, 8);
		Kernel_WriteHex(low1, 10);
		Kernel_WriteHex(Kernel_dma0, 10);
		Kernel_WriteHex(Kernel_dma1, 10);
		Kernel_WriteHex(Kernel_StackOrg, 10);
		Kernel_WriteHex(high0, 10);
		Kernel_WriteHex(high1, 10);
		Kernel_WriteLn();
	}
	__ASSERT(high1 > 1052672, 0);
	Kernel_Fill4(low0, __ASHR(low1 - low0, 2), 0);
	Kernel_Fill4(1048576, __ASHR(high1 - 1048576, 2), 0);
	Kernel_firstBlock = 4156;
	Kernel_endBlock = high1;
	p = (Kernel_Blockm4Ptr)(ADDRESS)Kernel_firstBlock;
	while (p->tag != NIL) {
		tag = p->tag;
		Kernel_initres = (Kernel_InitPtr)(ADDRESS)((INT32)(ADDRESS)p + 28);
		tdesc = (Kernel_Tag)(ADDRESS)(((((UINT32)(ADDRESS)tag & ~0x02)) & ~0x01));
		if (((0x02 & (UINT32)(ADDRESS)tag)) != 0x0) {
			size = (p->lastElemToMark + tdesc->size) - (INT32)(ADDRESS)p;
		} else {
			size = tdesc->size + 4;
		}
		size = (INT32)(((UINT32)((size + 32) - 1) & ~(UINT32)31));
		(INT32)(ADDRESS)p += size;
	}
	__GET(Kernel_initres, c, CHAR);
	__ASSERT(c == 0xe8, 0);
	f = (Kernel_FreeBlockPtr)(ADDRESS)high0;
	f->tag = (Kernel_Tag)(ADDRESS)((UINT32)((ADDRESS)&f->size) | 0x04);
	f->size = (high1 - high0) - 4;
	f->next = 0;
	f = (Kernel_FreeBlockPtr)(ADDRESS)low0;
	f->tag = (Kernel_Tag)(ADDRESS)((UINT32)((ADDRESS)&f->size) | 0x04);
	f->size = (low1 - low0) - 4;
	f->next = high0;
	Kernel_sysres = (Kernel_InitPtr)(ADDRESS)low1;
	Kernel_sysres->tag = (Kernel_Tag)(ADDRESS)((UINT32)((ADDRESS)&Kernel_sysres->z0) | 0x01);
	Kernel_sysres->z0 = (high0 - low1) - 4;
	Kernel_sysres->z1 = -4;
	Kernel_sysres->z5 = (ADDRESS)&Kernel_sysres->z0;
	Kernel_sysres = (Kernel_InitPtr)(ADDRESS)(low1 + 28);
	Kernel_reserve = NIL;
	Kernel_firstTry = 1;
	Kernel_GClevel = 1;
	Kernel_GCstack = 0;
	Kernel_GC();
	Kernel_GClevel = 0;
	Kernel_GCstack = 1;
	Kernel_EnableGC = Kernel_DefaultEnableGC;
	Kernel_DisableGC = Kernel_DefaultDisableGC;
}

static BOOLEAN Kernel_IsRAM (INT32 adr)
{
	INT32 save, x;
	BOOLEAN ok;
	ok = 0;
	__GET(adr, save, INT32);
	__PUT(adr, 3203383518LL, INT64);
	x = 2857762560LL;
	__GET(adr, x, INT32);
	if ((INT64)x == 3203383518LL) {
		__PUT(adr, 2857762560LL, INT64);
		x = 3203383518LL;
		__GET(adr, x, INT32);
		ok = (INT64)x == 2857762560LL;
	}
	__PUT(adr, save, INT32);
	return ok;
}

static void Kernel_CheckMemory (void)
{
	CHAR s[16];
	INT32 adr;
	Kernel_GetConfig((CHAR*)"ExtMemSize", 11, (void*)s, 16);
	if (s[0] != 0x00) {
		Kernel_memTop = 1048576 + __ASHL(Kernel_StrToInt(s, 16), 20);
	} else {
		if (Kernel_memTop >= 66060288) {
			adr = Kernel_memTop - 4;
			while (Kernel_IsRAM(adr)) {
				Kernel_memTop = adr + 4;
				adr += 1048576;
			}
		}
		if (Kernel_memTop > 135266304) {
			Kernel_memTop = 135266304;
		}
	}
}

static void Kernel_ReadBootTable (void)
{
	INT32 p, type, addr, size;
	Kernel_memTop = 0;
	Kernel_pageheap = 0;
	Kernel_configadr = 0;
	p = Kernel_bt;
	for (;;) {
		__GET(p, type, INT32);
		if (type == -1) {
			break;
		} else if (type == 3) {
			__GET(p + 8, addr, INT32);
			Kernel_pageheap = addr - __MASK(addr, -4096);
		} else if (type == 4) {
			__GET(p + 8, addr, INT32);
			__GET(p + 12, size, INT32);
			if (addr == 1048576) {
				Kernel_memTop = 1048576 + size;
			}
		} else if (type == 8) {
			Kernel_configadr = p + 8;
		}
		__GET(p + 4, size, INT32);
		p += size;
	}
	while (Kernel_memTop == 0 || Kernel_pageheap == 0) {
	}
	p = 0;
	while (p <= 2) {
		__GET(1032 + __ASHL(p, 1), Kernel_bioslpt[__X(p, 3)], INT16);
		p += 1;
	}
}

static struct ShowState__109 {
	INT32 *bp;
	struct ShowState__109 *lnk;
} *ShowState__109_s;

static void Val__110 (CHAR *s, ADDRESS s__len, INT32 ofs);
static void Var__112 (CHAR *s, ADDRESS s__len, INT32 var);

static void Val__110 (CHAR *s, ADDRESS s__len, INT32 ofs)
{
	__DUP(s, s__len, CHAR);
	__GET(*ShowState__109_s->bp + ofs, ofs, INT32);
	Kernel_WriteChar(' ');
	Kernel_WriteString(s, s__len);
	Kernel_WriteChar('=');
	Kernel_WriteHex(ofs, 8);
	__DEL(s);
}

static void Var__112 (CHAR *s, ADDRESS s__len, INT32 var)
{
	__DUP(s, s__len, CHAR);
	Kernel_WriteChar(' ');
	Kernel_WriteString(s, s__len);
	Kernel_WriteChar('=');
	Kernel_WriteHex(var, 8);
	__DEL(s);
}

static void Kernel_ShowState (INT32 error, INT32 fp, INT32 pc, INT32 pf)
{
	INT32 x, bp, esp, cs, ds, es, fs, gs, ss;
	Kernel_Module m;
	UINT32 flags, set;
	struct ShowState__109 _s;
	_s.bp = &bp;
	_s.lnk = ShowState__109_s;
	ShowState__109_s = &_s;
	if (Kernel_handlingtrap) {
		Kernel_WriteString((CHAR*)" [Recursive TRAP]", 18);
		Kernel_WriteLn();
	} else {
		Kernel_handlingtrap = 1;
		__GETREG(5, bp, INT32);
		__GET(bp, bp, INT32);
		Kernel_WriteLn();
		Kernel_WriteString((CHAR*)"TRAP ", 6);
		Kernel_WriteInt(error, 1);
		__GET(bp + 52, cs, INT32);
		__GET(bp + 56, flags, UINT32);
		if (__IN(17, flags, 32)) {
			Kernel_WriteString((CHAR*)", V86", 6);
			__GET(bp + 80, gs, INT32);
			__GET(bp + 76, fs, INT32);
			__GET(bp + 72, ds, INT32);
			__GET(bp + 68, es, INT32);
			__GET(bp + 64, ss, INT32);
			__GET(bp + 60, esp, INT32);
		} else if (__MASK(cs, -4) == 0) {
			Kernel_WriteString((CHAR*)", level 0", 10);
			ds = Kernel_DS();
			es = Kernel_ES();
			fs = Kernel_FS();
			gs = Kernel_GS();
			ss = Kernel_SS();
			__GET(bp + 20, esp, INT32);
			esp += 16;
		} else {
			ds = Kernel_DS();
			es = Kernel_ES();
			fs = Kernel_FS();
			gs = Kernel_GS();
			__GET(bp + 64, ss, INT32);
			__GET(bp + 60, esp, INT32);
		}
		Kernel_WriteChar(' ');
		Kernel_WriteString(Kernel_version, 32);
		Kernel_WriteLn();
		set = Kernel_GetFlags();
		Var__112((CHAR*)"CS:", 4, cs);
		Var__112((CHAR*)"DS:", 4, ds);
		Var__112((CHAR*)"ES:", 4, es);
		Var__112((CHAR*)"SS:", 4, ss);
		Var__112((CHAR*)"CR0", 4, Kernel_trapCR[0]);
		Var__112((CHAR*)"FPS", 4, (INT32)((Kernel_trapfpu[1] & 0xffff) | __LSHL(Kernel_trapfpu[2], 16, 32)));
		Kernel_WriteLn();
		Var__112((CHAR*)"EIP", 4, pc);
		Val__110((CHAR*)"ESI", 4, 12);
		Val__110((CHAR*)"EDI", 4, 8);
		Var__112((CHAR*)"ESP", 4, esp);
		Var__112((CHAR*)"CR2", 4, Kernel_trapCR[2]);
		Var__112((CHAR*)"SBT", 4, Kernel_StackOrg);
		Kernel_WriteLn();
		Val__110((CHAR*)"EAX", 4, 36);
		Val__110((CHAR*)"EBX", 4, 24);
		Val__110((CHAR*)"ECX", 4, 32);
		Val__110((CHAR*)"EDX", 4, 28);
		Var__112((CHAR*)"CR3", 4, Kernel_trapCR[3]);
		Var__112((CHAR*)"KFL", 4, (INT32)set);
		Kernel_WriteLn();
		Val__110((CHAR*)"EBP", 4, 16);
		Var__112((CHAR*)"FS:", 4, fs);
		Var__112((CHAR*)"GS:", 4, gs);
		Val__110((CHAR*)"ERR", 4, 44);
		Var__112((CHAR*)"CR4", 4, Kernel_trapCR[4]);
		Var__112((CHAR*)"TCK", 4, Kernel_ticks);
		Kernel_WriteLn();
		if (__VAL(CHAR, Kernel_trapDR[7]) != 0x00) {
			Var__112((CHAR*)"DR0", 4, Kernel_trapDR[0]);
			Var__112((CHAR*)"DR1", 4, Kernel_trapDR[1]);
			Var__112((CHAR*)"DR2", 4, Kernel_trapDR[2]);
			Var__112((CHAR*)"DR3", 4, Kernel_trapDR[3]);
			Var__112((CHAR*)"DR6", 4, Kernel_trapDR[6]);
			Var__112((CHAR*)"DR7", 4, Kernel_trapDR[7]);
			Kernel_WriteLn();
		}
		Kernel_WriteString((CHAR*)" EFLAGS=", 9);
		Kernel_WriteFlags((INT32)flags);
		Kernel_WriteLn();
		if (error == -6) {
			Kernel_WriteMemory(pc, 16);
		}
		if (!__IN(17, flags, 32)) {
			x = 0;
			for (;;) {
				m = Kernel_GetMod(pc);
				if (m == NIL) {
					Kernel_WriteString((CHAR*)"Unknown EIP=", 13);
					Kernel_WriteHex(pc, 8);
					if (x != 0) {
						break;
					}
				} else {
					Kernel_WriteString(m->name, 32);
					Kernel_WriteString((CHAR*)" PC=", 5);
					Kernel_WriteInt(pc - (ADDRESS)&(m->code->data)[0], 1);
				}
				__GET(fp + 4, pc, INT32);
				__GET(fp, fp, INT32);
				if (fp >= Kernel_StackOrg) {
					break;
				}
				Kernel_WriteString((CHAR*)", ", 3);
				x += 1;
				if (x == 10) {
					Kernel_WriteString((CHAR*)"...", 4);
					break;
				}
			}
			Kernel_WriteLn();
		}
	}
	Kernel_handlingtrap = 0;
	ShowState__109_s = _s.lnk;
}

static void Kernel_InitTrapHandling (void)
{
	INT8 i;
	Kernel_Proc int_;
	int_ = Kernel_ExceptionHandler;
	Kernel_handler0 = Kernel_ShowState;
	Kernel_handler = NIL;
	Kernel_handlingtrap = 0;
	Kernel_loop = NIL;
	i = 0;
	while (i <= 31) {
		if (i == 2) {
			Kernel_InstallIP(Kernel_NMIHandler, i);
		} else if (i == 15) {
		} else {
			Kernel_InstallIP(int_, i);
		}
		i += 1;
	}
	if (Kernel_oldcopro) {
		Kernel_InstallIP(int_, 45);
	}
}

static BOOLEAN Kernel_Detect486 (void)
{
	return 1;
}

static BOOLEAN Kernel_Detect586 (void)
{
	return 1;
}

static BOOLEAN Kernel_DetectCoprocessor (void)
{
	return 1;
}

static void Kernel_SetupFlags (void)
{
}

static void Kernel_Setup486Flags (void)
{
}

static void Kernel_Setup586Flags (void)
{
}

static void Kernel_DisableMathTaskEx (void)
{
}

static void Kernel_EnableEmulation (void)
{
}

static void Kernel_DisableEmulation (void)
{
}

static void Kernel_LoadIDT (INT32 base, INT32 size)
{
}

static void Kernel_LoadGDT (INT32 base, INT32 size)
{
}

static void Kernel_LoadSegRegs (INT32 data)
{
}

static void Kernel_SetTR (INT32 tr)
{
}

static void Kernel_CPUID (Kernel_Vendor vendor, INT32 *version, INT32 *features)
{
}

static BOOLEAN Kernel_APM (INT32 *gdtofs, INT32 *apmofs)
{
	INT32 gdtptr[2];
	return 1;
}

static void Kernel_APMPowerOff (void)
{
	INT16 adr[3];
}

static void Kernel_InitProcessor (void)
{
	UINT32 mask;
	CHAR s[16];
	INT32 gdtofs;
	Kernel_SetupFlags();
	Kernel_GetConfig((CHAR*)"CPU", 4, (void*)s, 16);
	Kernel_cpuversion = 0;
	if (__STRCMP(s, "3") == 0) {
		Kernel_cpu = 3;
	} else if (__STRCMP(s, "4") == 0) {
		Kernel_cpu = 4;
	} else if (__STRCMP(s, "5") == 0) {
		Kernel_cpu = 5;
	} else {
		if (Kernel_Detect486()) {
			if (Kernel_Detect586()) {
				Kernel_CPUID(Kernel_cpuvendor, &Kernel_cpuversion, &Kernel_cpufeatures);
				Kernel_cpu = (INT8)((INT16)__MASK(__ASHR(Kernel_cpuversion, 8), -16));
			} else {
				Kernel_cpu = 4;
			}
		} else {
			Kernel_cpu = 3;
		}
	}
	if (Kernel_cpuversion == 0) {
		Kernel_cpuversion = Kernel_cpu;
	}
	if (Kernel_cpu >= 4) {
		Kernel_Setup486Flags();
	}
	if (Kernel_cpu >= 5) {
		Kernel_Setup586Flags();
	}
	Kernel_GetConfig((CHAR*)"Copro", 6, (void*)s, 16);
	if (__STRCMP(s, "0") == 0) {
		Kernel_copro = 0;
	} else if (s[0] == 0x00) {
		Kernel_copro = Kernel_DetectCoprocessor();
	} else {
		Kernel_copro = 1;
	}
	Kernel_oldcopro = (Kernel_copro && Kernel_cpu < 4);
	Kernel_DisableMathTaskEx();
	if (Kernel_copro) {
		Kernel_DisableEmulation();
		Kernel_SetupFPU();
	} else {
		Kernel_EnableEmulation();
	}
	__PORTOUT(32, 0x11, CHAR);
	__PORTOUT(33, ' ', CHAR);
	__PORTOUT(33, 0x04, CHAR);
	__PORTOUT(33, 0x01, CHAR);
	__PORTOUT(33, 0xff, CHAR);
	__PORTOUT(160, 0x11, CHAR);
	__PORTOUT(161, '(', CHAR);
	__PORTOUT(161, 0x02, CHAR);
	__PORTOUT(161, 0x01, CHAR);
	__PORTOUT(161, 0xff, CHAR);
	__PORTIN(33, __VAL(CHAR, mask), CHAR);
	mask &= ~__SETOF(2,32);
	__PORTOUT(33, __VAL(CHAR, mask), CHAR);
	Kernel_Fill4((ADDRESS)&Kernel_ktss, 2075, 0);
	Kernel_ktss.ESP0 = 1064960;
	Kernel_ktss.ESS0 = 16;
	Kernel_ktss.IOBitmapOffset = (INT16)((ADDRESS)Kernel_ktss.IOBitmap - (ADDRESS)&Kernel_ktss.Link);
	gdtofs = 0;
	Kernel_apmofs = -1;
	Kernel_GetConfig((CHAR*)"APM", 4, (void*)s, 16);
	if (__STRCMP(s, "0") != 0) {
		if (Kernel_APM(&gdtofs, &Kernel_apmofs)) {
		}
	}
	Kernel_GetConfig((CHAR*)"PowerSave", 10, (void*)s, 16);
	Kernel_powersave = s[0] != '0';
	__PUT((ADDRESS)&Kernel_gdt[0], 0, INT32);
	__PUT((ADDRESS)&Kernel_gdt[0] + 4, 0, INT32);
	__PUT((ADDRESS)&Kernel_gdt[1], 65535, INT32);
	__PUT((ADDRESS)&Kernel_gdt[1] + 4, 13605376, INT32);
	__PUT((ADDRESS)&Kernel_gdt[2], 65535, INT32);
	__PUT((ADDRESS)&Kernel_gdt[2] + 4, 13603328, INT32);
	__PUT((ADDRESS)&Kernel_gdt[3], 65535, INT32);
	__PUT((ADDRESS)&Kernel_gdt[3] + 4, 13606400, INT32);
	__PUT((ADDRESS)&Kernel_gdt[4], 65535, INT32);
	__PUT((ADDRESS)&Kernel_gdt[4] + 4, 13627904, INT32);
	Kernel_gdt[5].limit0to15 = 8299;
	Kernel_gdt[5].base0to15 = (INT16)((INT16)((ADDRESS)&Kernel_ktss));
	Kernel_gdt[5].base16to23 = (CHAR)__ASHR((ADDRESS)&Kernel_ktss, 16);
	Kernel_gdt[5].base24to31 = (CHAR)__ASHR((ADDRESS)&Kernel_ktss, 24);
	Kernel_gdt[5].accessByte = 0x89;
	Kernel_gdt[5].granularityByte = 0x00;
	if (Kernel_apmofs != -1) {
		__MOVE(gdtofs + 24, (ADDRESS)&Kernel_gdt[6], 24);
	}
	Kernel_LoadGDT((ADDRESS)&Kernel_gdt[0], 71);
	Kernel_LoadSegRegs(32);
	Kernel_SetTR(40);
}

static void Kernel_V86Exit (void)
{
}

static void Kernel_V86Switch (void)
{
}

static void Kernel_ReadMSR (INT32 msr, INT32 lowadr, INT32 highadr)
{
}

static void Kernel_WriteMSR (INT32 msr, UINT32 low, UINT32 high)
{
}

static void Kernel_HLT (void)
{
}

static void Kernel_V86IntHandler (void)
{
	UINT32 s;
	INT32 func, bp, reg;
	UINT32 low, high;
	__STI();
	__GETREG(5, bp, INT32);
	__GET(bp + 56, s, UINT32);
	__ASSERT(!__IN(17, s, 32), 0);
	__GET(bp + 52, s, UINT32);
	__ASSERT(((s & 0x03)) == 0x03, 0);
	__GET(bp + 36, func, INT32);
	switch (func) {
		case 0: 
			__GET(bp + 24, Kernel_vregadr, INT32);
			__GET(Kernel_vregadr + 48, s, UINT32);
			s = ((s & 0x0cd5) | (Kernel_GetFlags() & 0xfffff02a)) | 0x020000;
			__PUT(Kernel_vregadr + 48, s, UINT32);
			__CLI();
			Kernel_ktss.ESP0 = 1056768;
			Kernel_V86Switch();
			Kernel_ktss.ESP0 = 1064960;
			__STI();
			break;
		case 2: 
			__GET(bp + 32, reg, INT32);
			Kernel_ReadMSR(reg, bp + 36, bp + 28);
			break;
		case 3: 
			__GET(bp + 32, reg, INT32);
			__GET(bp + 28, high, UINT32);
			__GET(bp + 24, low, UINT32);
			Kernel_WriteMSR(reg, low, high);
			break;
		case 4: 
			Kernel_HLT();
			break;
		default: __CASECHK;
	}
}

static void Kernel_InterruptHandler (void)
{
}

static void Kernel_InitInterrupts (void)
{
	INT32 a;
	INT8 o, i, j;
	Kernel_Proc p;
	p = Kernel_InterruptHandler;
	Kernel_defaultHandler = Kernel_Unexpected;
	Kernel_intHandlerAdr = (ADDRESS)&Kernel_intHandler[0][0];
	i = 0;
	while (i <= 47) {
		Kernel_intHandler[__X(i, 48)][0] = Kernel_defaultHandler;
		Kernel_intHandler[__X(i, 48)][1] = NIL;
		o = 0;
		Kernel_glue[__X(i, 48)][__X(o, 12)] = 'j';
		o += 1;
		Kernel_glue[__X(i, 48)][__X(o, 12)] = 0x00;
		o += 1;
		Kernel_glue[__X(i, 48)][__X(o, 12)] = 'j';
		o += 1;
		Kernel_glue[__X(i, 48)][__X(o, 12)] = (CHAR)i;
		o += 1;
		a = ((INT32)(ADDRESS)p + 3) - ((ADDRESS)&Kernel_glue[__X(i, 48)][__X(o, 12)] + 5);
		Kernel_glue[__X(i, 48)][__X(o, 12)] = 0xe9;
		o += 1;
		__PUT((ADDRESS)&Kernel_glue[__X(i, 48)][__X(o, 12)], a, INT32);
		if (i > 31 || !__IN(i, 0x027d00, 32)) {
			a = (ADDRESS)&Kernel_glue[__X(i, 48)][0];
		} else {
			a = (ADDRESS)&Kernel_glue[__X(i, 48)][2];
		}
		Kernel_idt[__X(i, 48)].offsetBits0to15 = (INT16)__MASK(a, -65536);
		Kernel_idt[__X(i, 48)].selector = 8;
		Kernel_idt[__X(i, 48)].gateType = 1;
		Kernel_idt[__X(i, 48)].offsetBits16to31 = (INT16)__ASHR(a, 16);
		i += 1;
	}
	Kernel_LoadIDT((ADDRESS)&Kernel_idt[0], 383);
	__STI();
}

static void Kernel_EnableMM (INT32 pd)
{
}

static void Kernel_InitMemory (void)
{
	INT32 i, j, m, n, phys, pt;
	CHAR s[32];
	UINT32 t;
	i = 0;
	while (i <= 3) {
		Kernel_mapcache[__X(i, 4)].size = 0;
		i += 1;
	}
	Kernel_AllocatePage(&Kernel_kernelpd);
	__ASSERT(Kernel_kernelpd != 0, 0);
	phys = 0;
	i = 0;
	m = __ASHR((Kernel_memTop + 4194304) - 1, 22);
	while (i != m) {
		Kernel_AllocatePage(&pt);
		__ASSERT(pt != 0, 0);
		j = 0;
		n = 1024;
		while (j != n) {
			if (phys >= Kernel_memTop) {
				n = j;
			} else {
				__PUT(pt + __ASHL(j, 2), phys + 7, INT32);
				phys += 4096;
				j += 1;
			}
		}
		while (j != 1024) {
			__PUT(pt + __ASHL(j, 2), 0, INT32);
			j += 1;
		}
		__PUT(Kernel_kernelpd + __ASHL(i, 2), pt + 7, INT32);
		i += 1;
	}
	while (i != 1024) {
		__PUT(Kernel_kernelpd + __ASHL(i, 2), 0, INT32);
		i += 1;
	}
	Kernel_mapPtr = 3758096384LL;
	i = 0;
	while (i != 10) {
		__MOVE("MapAdrX", s, 8);
		s[6] = (CHAR)(48 + i);
		Kernel_GetConfig(s, 32, (void*)s, 32);
		m = Kernel_StrToInt(s, 32);
		__MOVE("MapLenX", s, 8);
		s[6] = (CHAR)(48 + i);
		Kernel_GetConfig(s, 32, (void*)s, 32);
		n = Kernel_StrToInt(s, 32);
		if ((m != 0 && n != 0)) {
			Kernel_MapMem(Kernel_kernelpd, m, n, m + 7);
			i += 1;
		} else {
			i = 10;
		}
	}
	Kernel_GetConfig((CHAR*)"MapVesa", 8, (void*)s, 32);
	if (__STRCMP(s, "1") == 0) {
		__ASSERT(__MASK(Kernel_kpar[1], -4096) == 0, 0);
		Kernel_MapMem(Kernel_kernelpd, 3758096384LL, 4194304, Kernel_kpar[1] + 7);
		Kernel_kpar[1] = 3758096384LL;
	}
	Kernel_AllocatePage(&Kernel_v86pd);
	__ASSERT(Kernel_v86pd != 0, 0);
	Kernel_Copy4(Kernel_kernelpd, Kernel_v86pd, 1024);
	Kernel_AllocatePage(&pt);
	__ASSERT(pt != 0, 0);
	__GET(Kernel_kernelpd, phys, INT32);
	phys -= __MASK(phys, -4096);
	Kernel_Copy4(phys, pt, 1024);
	__PUT(Kernel_v86pd, pt + 7, INT32);
	i = 1;
	while (i <= 159) {
		__GET(pt + __ASHL(i, 2), t, UINT32);
		__PUT(pt + __ASHL(i, 2), (t & ~0x02), UINT32);
		i += 1;
	}
	__GET(Kernel_kernelpd, pt, INT32);
	pt -= 7;
	__PUT(pt, 0, INT32);
	i = 240;
	while (i <= 255) {
		__GET(pt + __ASHL(i, 2), t, UINT32);
		__PUT(pt + __ASHL(i, 2), (t & ~0x02), UINT32);
		i += 1;
	}
	i = 256;
	while (i <= 259) {
		__GET(pt + __ASHL(i, 2), t, UINT32);
		__PUT(pt + __ASHL(i, 2), (t & ~0x02), UINT32);
		i += 1;
	}
	__PUT(1138, 4660, INT16);
	Kernel_ktss.CR3 = Kernel_kernelpd;
	Kernel_EnableMM(Kernel_kernelpd);
}

static void Kernel_Call15 (void)
{
}

void Kernel_Shutdown (INT32 code)
{
	Kernel_Module m;
	INT32 t;
	Kernel_shutdown = code;
	m = Kernel_modules;
	while (m != NIL) {
		Kernel_FinalizeModule(m);
		m = m->next;
	}
	if (code == 2) {
		__CLI();
		__PORTOUT(112, 0x8f, CHAR);
		Kernel_Wait();
		__PORTOUT(113, 0x00, CHAR);
		Kernel_Wait();
		__PORTOUT(112, 0x0d, CHAR);
		Kernel_Wait();
		__PORTOUT(100, 0xfe, CHAR);
		code = 1000;
		while (code != 0) {
			code -= 1;
		}
		Kernel_Reboot();
	} else if ((code == 1 && Kernel_apmofs != -1)) {
		t = Kernel_ticks;
		do {
		} while (!(Kernel_ticks - t > 1000));
		Kernel_InstallIP(Kernel_APMPowerOff, 15);
		Kernel_Call15();
	}
	__CLI();
	for (;;) {
	}
}

void Kernel_Idle (INT32 code)
{
}

static void Kernel_TimerHandler (void)
{
}

static void Kernel_InitTimer (void)
{
	Kernel_ticks = 0;
	__PORTOUT(67, '4', CHAR);
	Kernel_Wait();
	__PORTOUT(64, (CHAR)1193, CHAR);
	Kernel_Wait();
	__PORTOUT(64, (CHAR)4, CHAR);
	Kernel_InstallIP(Kernel_TimerHandler, 32);
}

static void Kernel_InitTracing (INT32 *top)
{
	CHAR s[32];
	CHAR ch;
	Kernel_GetConfig((CHAR*)"TraceSize", 10, (void*)s, 32);
	Kernel_traceBufSize = Kernel_StrToInt(s, 32);
	if (Kernel_traceBufSize <= 0) {
		Kernel_traceBufSize = 2048;
	}
	*top -= Kernel_traceBufSize;
	Kernel_traceBufAdr = *top;
	Kernel_GetConfig((CHAR*)"TraceConsole", 13, (void*)s, 32);
	Kernel_traceConsole = s[0] == '1';
	Kernel_GetConfig((CHAR*)"Init", 5, (void*)s, 32);
	if (__STRCMP(s, "9090") == 0) {
		Kernel_traceConsole = 1;
	}
	if (Kernel_traceConsole) {
		Kernel_Fill4(753664, 1000, 119539488);
	}
	Kernel_traceHead = 0;
	Kernel_traceTail = 0;
	Kernel_traceMark = 0;
	Kernel_GetConfig((CHAR*)"TracePort", 10, (void*)s, 32);
	Kernel_tbase = (INT16)Kernel_StrToInt(s, 32);
	switch (Kernel_tbase) {
		case 1: 
			Kernel_tbase = 1016;
			break;
		case 2: 
			Kernel_tbase = 760;
			break;
		case 3: 
			Kernel_tbase = 1000;
			break;
		case 4: 
			Kernel_tbase = 744;
			break;
		default: 
			break;
	}
	Kernel_GetConfig((CHAR*)"TraceBPS", 9, (void*)s, 32);
	Kernel_tspeed = Kernel_StrToInt(s, 32);
	if ((Kernel_tspeed != 0 && Kernel_tbase == 0)) {
		Kernel_tbase = 1016;
	} else if ((Kernel_tspeed == 0 && Kernel_tbase != 0)) {
		Kernel_tspeed = 19200;
	}
	if (Kernel_tspeed > 0) {
		__PORTIN(Kernel_tbase + 4, ch, CHAR);
		if ((((UINT32)(ch) & 0xe0)) != 0x0) {
			Kernel_tspeed = 0;
			Kernel_tbase = 0;
		}
	}
	Kernel_GetConfig((CHAR*)"TracePrinter", 13, (void*)s, 32);
	Kernel_tlpt = Kernel_StrToInt(s, 32);
	if ((Kernel_tlpt >= 1 && Kernel_tlpt <= 3)) {
		Kernel_tlpt = Kernel_bioslpt[__X(Kernel_tlpt - 1, 3)];
	}
	Kernel_GetConfig((CHAR*)"TraceHeap", 10, (void*)s, 32);
	Kernel_traceheap = (UINT32)Kernel_StrToInt(s, 32);
}

static void Kernel_InitRuntime (void)
{
	void (*newRec)(INT32*, Kernel_Tag);
	void (*newSys)(INT32*, INT32);
	void (*newArr)(INT32*, Kernel_Tag, INT32, INT32);
	newRec = Kernel_NewRec;
	newSys = Kernel_NewSys;
	newArr = Kernel_NewArr;
	Kernel_runtime[0] = (INT32)(ADDRESS)newRec;
	Kernel_runtime[1] = (INT32)(ADDRESS)newSys;
	Kernel_runtime[2] = (INT32)(ADDRESS)newArr;
	Kernel_RemoveIP(NIL, 28);
	Kernel_InstallIP(Kernel_V86IntHandler, 28);
	Kernel_RemoveIP(NIL, 29);
	Kernel_InstallIP(Kernel_V86Exit, 29);
}

static void Kernel_SwitchToLevel3 (INT32 ss, INT32 sp, INT32 cs)
{
}

static void EnumPtrs(void (*P)(void*))
{
	P(Kernel_modules);
	P(Kernel_reserve);
	P(Kernel_sysres);
	P(Kernel_initres);
	P(Kernel_FinObjs);
}

__TDESC(Kernel_Cmd, 1, 0) = {__TDFLDS("Cmd", 36), {-4}};
__TDESC(Kernel_ExportDesc, 1, 1) = {__TDFLDS("ExportDesc", 16), {12, -8}};
__TDESC(Kernel_ModuleDesc, 1, 13) = {__TDFLDS("ModuleDesc", 132), {0, 48, 52, 56, 60, 64, 68, 72, 76, 92, 100, 108, 124, -56}};
__TDESC(Kernel_TypeDesc, 1, 0) = {__TDFLDS("TypeDesc", 8), {-4}};
__TDESC(Kernel_FreeBlock, 1, 1) = {__TDFLDS("FreeBlock", 12), {0, -8}};
__TDESC(Kernel_Block, 1, 3) = {__TDFLDS("Block", 12), {0, 4, 8, -16}};
__TDESC(Kernel_Blockm4, 1, 1) = {__TDFLDS("Blockm4", 16), {0, -8}};
__TDESC(Kernel__2, 1, 1) = {__TDFLDS("", 36), {0, -8}};
__TDESC(Kernel_PtrElemDesc, 1, 1) = {__TDFLDS("PtrElemDesc", 4), {0, -8}};
__TDESC(Kernel_FinObjNode, 1, 1) = {__TDFLDS("FinObjNode", 16), {0, -8}};
__TDESC(Kernel_GateDescriptor, 1, 0) = {__TDFLDS("GateDescriptor", 8), {-4}};
__TDESC(Kernel_SegmentDescriptor, 1, 0) = {__TDFLDS("SegmentDescriptor", 8), {-4}};
__TDESC(Kernel_TSSDesc, 1, 0) = {__TDFLDS("TSSDesc", 8300), {-4}};
__TDESC(Kernel_V86Regs, 1, 0) = {__TDFLDS("V86Regs", 76), {-4}};
__TDESC(Kernel_MilliTimer, 1, 0) = {__TDFLDS("MilliTimer", 4), {-4}};
__TDESC(Kernel__1, 1, 0) = {__TDFLDS("", 12), {-4}};
__TDESC(Kernel__1, 1, 0) = {__TDFLDS("", 4), {-4}};
__TDESC(Kernel__2, 1, 0) = {__TDFLDS("", 48), {-4}};

export void *Kernel__init(void)
{
	__DEFMOD;
	__REGMOD("Kernel", EnumPtrs);
	__REGCMD("GC", Kernel_GC);
	__REGCMD("SetLogMark", Kernel_SetLogMark);
	__REGCMD("WriteLn", Kernel_WriteLn);
	__INITYP(Kernel_Cmd, Kernel_Cmd, 0);
	__INITYP(Kernel_ExportDesc, Kernel_ExportDesc, 0);
	__INITYP(Kernel_ModuleDesc, Kernel_ModuleDesc, 0);
	__INITYP(Kernel_TypeDesc, Kernel_TypeDesc, 0);
	__INITYP(Kernel_FreeBlock, Kernel_FreeBlock, 0);
	__INITYP(Kernel_Block, Kernel_Block, 0);
	__INITYP(Kernel_Blockm4, Kernel_Blockm4, 0);
	__INITYP(Kernel__2, Kernel__2, 0);
	__INITYP(Kernel_PtrElemDesc, Kernel_PtrElemDesc, 0);
	__INITYP(Kernel_FinObjNode, Kernel_FinObjNode, 0);
	__INITYP(Kernel_GateDescriptor, Kernel_GateDescriptor, 0);
	__INITYP(Kernel_SegmentDescriptor, Kernel_SegmentDescriptor, 0);
	__INITYP(Kernel_TSSDesc, Kernel_TSSDesc, 0);
	__INITYP(Kernel_V86Regs, Kernel_V86Regs, 0);
	__INITYP(Kernel_MilliTimer, Kernel_MilliTimer, 0);
	__INITYP(Kernel__1, Kernel__1, 0);
	__INITYP(Kernel__1, Kernel__1, 0);
	__INITYP(Kernel__2, Kernel__2, 0);
/* BEGIN */
	__GETREG(0, Kernel_bt, INT32);
	__GETREG(6, Kernel_kpar[0], INT32);
	__GETREG(7, Kernel_kpar[1], INT32);
	Kernel_tspeed = 0;
	Kernel_pspeed = 0;
	Kernel_displayPos = 0;
	Kernel_traceBufAdr = 0;
	Kernel_timer = NIL;
	Kernel_traceConsole = 0;
	Kernel_shutdown = 0;
	Kernel_tlpt = 0;
	Kernel_ReadBootTable();
	Kernel_CheckMemory();
	Kernel_pageheap0 = Kernel_pageheap;
	Kernel_pageheap1 = 0;
	Kernel_heapTop = Kernel_memTop;
	Kernel_InitTracing(&Kernel_heapTop);
	__MOVE("PC Native 05.01.2003", Kernel_version, 21);
	Kernel_WriteString((CHAR*)"ETH Oberon / ", 14);
	Kernel_WriteString(Kernel_version, 32);
	Kernel_WriteLn();
	Kernel_InitProcessor();
	Kernel_InitInterrupts();
	Kernel_InitTrapHandling();
	Kernel_InitMemory();
	Kernel_InitHeap();
	Kernel_SwitchToLevel3(35, Kernel_StackOrg, 27);
	Kernel_InitTimer();
	Kernel_InitClock();
	Kernel_InitRuntime();
	__ENDMOD;
}
