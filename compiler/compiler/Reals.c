/* voc 2.1.0 [2017/09/06]. Bootstrapping compiler for address size 8, alignment 8. xtaSv */

#define SHORTINT INT8
#define INTEGER  INT16
#define LONGINT  INT32
#define SET      UINT32

#include "SYSTEM.h"
#include "Kernel.h"


export UINT32 Reals_DefaultFCR;
static LONGREAL Reals_tene[23];
static LONGREAL Reals_ten[27];
static UINT32 Reals_eq[20], Reals_gr[20];
static INT16 Reals_H, Reals_L;


export INT32 Reals_Expo (REAL x);
export INT32 Reals_ExpoL (LONGREAL x);
export UINT32 Reals_FCR (void);
static void Reals_InitHL (void);
export INT32 Reals_Int (REAL x);
export void Reals_IntL (LONGREAL x, INT32 *h, INT32 *l);
export BOOLEAN Reals_IsNaN (REAL x);
export BOOLEAN Reals_IsNaNL (LONGREAL x);
export REAL Reals_NaN (INT32 l);
export INT32 Reals_NaNCode (REAL x);
export void Reals_NaNCodeL (LONGREAL x, INT32 *h, INT32 *l);
export LONGREAL Reals_NaNL (INT32 h, INT32 l);
export REAL Reals_Real (INT32 h);
export LONGREAL Reals_RealL (INT32 h, INT32 l);
static void Reals_RealX (INT32 h, INT32 l, INT32 adr);
export void Reals_SetExpo (INT32 e, REAL *x);
export void Reals_SetExpoL (INT32 e, LONGREAL *x);
export void Reals_SetFCR (UINT32 s);
export LONGREAL Reals_Ten (INT32 e);
static UINT32 Reals_fcr (void);
static void Reals_setfcr (UINT32 s);


INT32 Reals_Expo (REAL x)
{
	return __MASK(__ASHR(__VAL(INT32, x), 23), -256);
}

INT32 Reals_ExpoL (LONGREAL x)
{
	INT32 i;
	__GET((ADDRESS)&x + Reals_H, i, INT32);
	return __MASK(__ASHR(i, 20), -2048);
}

void Reals_SetExpo (INT32 e, REAL *x)
{
	INT32 i;
	__GET((ADDRESS)x, i, INT32);
	i = __ASHL(__ASHL(__ASHR(i, 31), 8) + __MASK(e, -256), 23) + __MASK(i, -8388608);
	__PUT((ADDRESS)x, i, INT32);
}

void Reals_SetExpoL (INT32 e, LONGREAL *x)
{
	INT32 i;
	__GET((ADDRESS)x + Reals_H, i, INT32);
	i = __ASHL(__ASHL(__ASHR(i, 31), 11) + __MASK(e, -2048), 20) + __MASK(i, -1048576);
	__PUT((ADDRESS)x + Reals_H, i, INT32);
}

REAL Reals_Real (INT32 h)
{
	REAL x;
	__PUT((ADDRESS)&x, h, INT32);
	return x;
}

LONGREAL Reals_RealL (INT32 h, INT32 l)
{
	LONGREAL x;
	__PUT((ADDRESS)&x + Reals_H, h, INT32);
	__PUT((ADDRESS)&x + Reals_L, l, INT32);
	return x;
}

INT32 Reals_Int (REAL x)
{
	INT32 i;
	__PUT((ADDRESS)&i, x, REAL);
	return i;
}

void Reals_IntL (LONGREAL x, INT32 *h, INT32 *l)
{
	__GET((ADDRESS)&x + Reals_H, *h, INT32);
	__GET((ADDRESS)&x + Reals_L, *l, INT32);
}

LONGREAL Reals_Ten (INT32 e)
{
	INT32 E;
	LONGREAL r;
	if (e < -307) {
		return (LONGREAL)0;
	} else if (308 < e) {
		return Reals_RealL(2146435072, 0);
	}
	e += 307;
	r = Reals_ten[__X(__DIV(e, 23), 27)] * Reals_tene[__X((int)__MOD(e, 23), 23)];
	if (__IN(__MASK(e, -32), Reals_eq[__X(__ASHR(e, 5), 20)], 32)) {
		return r;
	} else {
		E = Reals_ExpoL(r);
		Reals_SetExpoL(1075, &r);
		if (__IN(__MASK(e, -32), Reals_gr[__X(__ASHR(e, 5), 20)], 32)) {
			r = r - (LONGREAL)1;
		} else {
			r = r + (LONGREAL)1;
		}
		Reals_SetExpoL(E, &r);
		return r;
	}
	__RETCHK;
}

INT32 Reals_NaNCode (REAL x)
{
	if (__MASK(__ASHR(__VAL(INT32, x), 23), -256) == 255) {
		return __MASK(__VAL(INT32, x), -8388608);
	} else {
		return -1;
	}
	__RETCHK;
}

void Reals_NaNCodeL (LONGREAL x, INT32 *h, INT32 *l)
{
	__GET((ADDRESS)&x + Reals_H, *h, INT32);
	__GET((ADDRESS)&x + Reals_L, *l, INT32);
	if (__MASK(__ASHR(*h, 20), -2048) == 2047) {
		*h = __MASK(*h, -1048576);
	} else {
		*h = -1;
		*l = -1;
	}
}

BOOLEAN Reals_IsNaN (REAL x)
{
	return __MASK(__ASHR(__VAL(INT32, x), 23), -256) == 255;
}

BOOLEAN Reals_IsNaNL (LONGREAL x)
{
	INT32 h;
	__GET((ADDRESS)&x + Reals_H, h, INT32);
	return __MASK(__ASHR(h, 20), -2048) == 2047;
}

REAL Reals_NaN (INT32 l)
{
	REAL x;
	__PUT((ADDRESS)&x, __MASK(l, -8388608) + 2139095040, INT32);
	return x;
}

LONGREAL Reals_NaNL (INT32 h, INT32 l)
{
	LONGREAL x;
	h = __MASK(h, -1048576) + 2146435072;
	__PUT((ADDRESS)&x + Reals_H, h, INT32);
	__PUT((ADDRESS)&x + Reals_L, l, INT32);
	return x;
}

static UINT32 Reals_fcr (void)
{
	__RETCHK;
}

UINT32 Reals_FCR (void)
{
	if (Kernel_copro) {
		return Reals_fcr();
	} else {
		return Reals_DefaultFCR;
	}
	__RETCHK;
}

static void Reals_setfcr (UINT32 s)
{
}

void Reals_SetFCR (UINT32 s)
{
	if (Kernel_copro) {
		Reals_setfcr(s);
	}
}

static void Reals_RealX (INT32 h, INT32 l, INT32 adr)
{
	__PUT(adr + Reals_H, h, INT32);
	__PUT(adr + Reals_L, l, INT32);
}

static void Reals_InitHL (void)
{
	INT32 i;
	INT16 dmy;
	BOOLEAN littleEndian;
	Reals_DefaultFCR = (Reals_FCR() & ~0x0c0d) | 0x033f;
	Reals_SetFCR(Reals_DefaultFCR);
	dmy = 1;
	i = (ADDRESS)&dmy;
	__GET(i, littleEndian, BOOLEAN);
	if (littleEndian) {
		Reals_H = 4;
		Reals_L = 0;
	} else {
		Reals_H = 0;
		Reals_L = 4;
	}
}


export void *Reals__init(void)
{
	__DEFMOD;
	__MODULE_IMPORT(Kernel);
	__REGMOD("Reals", 0);
/* BEGIN */
	Reals_InitHL();
	Reals_RealX(1072693248, 0, (ADDRESS)&Reals_tene[0]);
	Reals_RealX(1076101120, 0, (ADDRESS)&Reals_tene[1]);
	Reals_RealX(1079574528, 0, (ADDRESS)&Reals_tene[2]);
	Reals_RealX(1083129856, 0, (ADDRESS)&Reals_tene[3]);
	Reals_RealX(1086556160, 0, (ADDRESS)&Reals_tene[4]);
	Reals_RealX(1090021888, 0, (ADDRESS)&Reals_tene[5]);
	Reals_RealX(1093567616, 0, (ADDRESS)&Reals_tene[6]);
	Reals_RealX(1097011920, 0, (ADDRESS)&Reals_tene[7]);
	Reals_RealX(1100470148, 0, (ADDRESS)&Reals_tene[8]);
	Reals_RealX(1104006501, 0, (ADDRESS)&Reals_tene[9]);
	Reals_RealX(1107468383, 536870912, (ADDRESS)&Reals_tene[10]);
	Reals_RealX(1110919286, 3892314112LL, (ADDRESS)&Reals_tene[11]);
	Reals_RealX(1114446484, 2717908992LL, (ADDRESS)&Reals_tene[12]);
	Reals_RealX(1117925532, 3846176768LL, (ADDRESS)&Reals_tene[13]);
	Reals_RealX(1121369284, 512753664, (ADDRESS)&Reals_tene[14]);
	Reals_RealX(1124887541, 640942080, (ADDRESS)&Reals_tene[15]);
	Reals_RealX(1128383353, 937459712, (ADDRESS)&Reals_tene[16]);
	Reals_RealX(1131820119, 2245566464LL, (ADDRESS)&Reals_tene[17]);
	Reals_RealX(1135329645, 1733216256, (ADDRESS)&Reals_tene[18]);
	Reals_RealX(1138841828, 1620131072, (ADDRESS)&Reals_tene[19]);
	Reals_RealX(1142271773, 2025163840, (ADDRESS)&Reals_tene[20]);
	Reals_RealX(1145772772, 3605196624LL, (ADDRESS)&Reals_tene[21]);
	Reals_RealX(1149300943, 105764242, (ADDRESS)&Reals_tene[22]);
	Reals_RealX(3275288, 742442509, (ADDRESS)&Reals_ten[0]);
	Reals_RealX(83348178, 1038626171, (ADDRESS)&Reals_ten[1]);
	Reals_RealX(163544354, 2200091381LL, (ADDRESS)&Reals_ten[2]);
	Reals_RealX(243586665, 1528380408, (ADDRESS)&Reals_ten[3]);
	Reals_RealX(323720200, 4009666617LL, (ADDRESS)&Reals_ten[4]);
	Reals_RealX(403849200, 1860863098, (ADDRESS)&Reals_ten[5]);
	Reals_RealX(483927874, 2445674075LL, (ADDRESS)&Reals_ten[6]);
	Reals_RealX(564131705, 4247952569LL, (ADDRESS)&Reals_ten[7]);
	Reals_RealX(644163422, 3638096748LL, (ADDRESS)&Reals_ten[8]);
	Reals_RealX(724303662, 3834512688LL, (ADDRESS)&Reals_ten[9]);
	Reals_RealX(804423384, 247566556, (ADDRESS)&Reals_ten[10]);
	Reals_RealX(884507930, 190090916, (ADDRESS)&Reals_ten[11]);
	Reals_RealX(964704726, 1703504000, (ADDRESS)&Reals_ten[12]);
	Reals_RealX(1044740494, 3794832442LL, (ADDRESS)&Reals_ten[13]);
	Reals_RealX(1124887541, 640942080, (ADDRESS)&Reals_ten[14]);
	Reals_RealX(1204997843, 706126257, (ADDRESS)&Reals_ten[15]);
	Reals_RealX(1285088350, 502509589, (ADDRESS)&Reals_ten[16]);
	Reals_RealX(1365276897, 298014061, (ADDRESS)&Reals_ten[17]);
	Reals_RealX(1445317886, 1026938894, (ADDRESS)&Reals_ten[18]);
	Reals_RealX(1525471842, 89861534, (ADDRESS)&Reals_ten[19]);
	Reals_RealX(1605572581, 4013601575LL, (ADDRESS)&Reals_ten[20]);
	Reals_RealX(1685669140, 1378923384, (ADDRESS)&Reals_ten[21]);
	Reals_RealX(1765849312, 2896973487LL, (ADDRESS)&Reals_ten[22]);
	Reals_RealX(1845895601, 3263873548LL, (ADDRESS)&Reals_ten[23]);
	Reals_RealX(1926056571, 3959042475LL, (ADDRESS)&Reals_ten[24]);
	Reals_RealX(2006147604, 2629644838LL, (ADDRESS)&Reals_ten[25]);
	Reals_RealX(2086250306, 1176012790, (ADDRESS)&Reals_ten[26]);
	Reals_eq[0] = 0x96810239;
	Reals_eq[1] = 0xfbbeff64;
	Reals_eq[2] = 0x1fffffff;
	Reals_eq[3] = 0xf85fcbef;
	Reals_eq[4] = 0xfffcfcc1;
	Reals_eq[5] = 0xfffbffe3;
	Reals_eq[6] = 0xf7b5c5b3;
	Reals_eq[7] = 0xf58f7ffb;
	Reals_eq[8] = 0x273f4f7f;
	Reals_eq[9] = 0xfffffe56;
	Reals_eq[10] = 0x7fffffff;
	Reals_eq[11] = 0x78f9f5ff;
	Reals_eq[12] = 0xecbfd7bf;
	Reals_eq[13] = 0xf9b7eeff;
	Reals_eq[14] = 0xffffffcf;
	Reals_eq[15] = 0x17ffbbff;
	Reals_eq[16] = 0xff4f2816;
	Reals_eq[17] = 0xbebccbfe;
	Reals_eq[18] = 0x3ddb7b75;
	Reals_eq[19] = 0xfc;
	Reals_gr[0] = 0x69000000;
	Reals_gr[1] = 0x9b;
	Reals_gr[2] = 0xe0000000;
	Reals_gr[3] = 0x07a03410;
	Reals_gr[4] = 0x03033e;
	Reals_gr[5] = 0x04001c;
	Reals_gr[6] = 0x084a3a4c;
	Reals_gr[7] = 0x04;
	Reals_gr[8] = 0xd8c0b080;
	Reals_gr[9] = 0x01a9;
	Reals_gr[10] = 0x0;
	Reals_gr[11] = 0x0;
	Reals_gr[12] = 0x13402800;
	Reals_gr[13] = 0x06400000;
	Reals_gr[14] = 0x30;
	Reals_gr[15] = 0xe8004400;
	Reals_gr[16] = 0xb0d7e9;
	Reals_gr[17] = 0x41433401;
	Reals_gr[18] = 0x0;
	Reals_gr[19] = 0x0;
	__ENDMOD;
}
