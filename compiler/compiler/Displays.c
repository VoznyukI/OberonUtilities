/* voc 2.1.0 [2017/09/06]. Bootstrapping compiler for address size 8, alignment 8. xtaSv */

#define SHORTINT INT8
#define INTEGER  INT16
#define LONGINT  INT32
#define SET      UINT32

#include "SYSTEM.h"


export INT32 Displays_width, Displays_height, Displays_offscreen, Displays_format, Displays_unit;
static INT32 Displays_fblow, Displays_fbhigh, Displays_fbstride;
static struct {
	ADDRESS len[1];
	CHAR data[1];
} *Displays_buf;


export INT32 Displays_ColorToIndex (INT32 col);
export void Displays_Copy (INT32 sx, INT32 sy, INT32 w, INT32 h, INT32 dx, INT32 dy);
export void Displays_Dot (INT32 col, INT32 x, INT32 y);
export void Displays_Fill (INT32 col, INT32 x, INT32 y, INT32 w, INT32 h);
export INT32 Displays_IndexToColor (INT32 index);
export void Displays_InitFrameBuffer (INT32 adr, INT32 size);
export void Displays_Mask (CHAR *buf, ADDRESS buf__len, INT32 bitofs, INT32 stride, INT32 fg, INT32 bg, INT32 x, INT32 y, INT32 w, INT32 h);
export void Displays_Transfer (CHAR *buf, ADDRESS buf__len, INT32 ofs, INT32 stride, INT32 x, INT32 y, INT32 w, INT32 h, INT32 op);


void Displays_Transfer (CHAR *buf, ADDRESS buf__len, INT32 ofs, INT32 stride, INT32 x, INT32 y, INT32 w, INT32 h, INT32 op)
{
	INT32 bufadr, buflow, bufhigh, dispadr;
	if (w > 0) {
		__ASSERT(Displays_fblow != 0, 0);
		w = w * Displays_format;
		bufadr = (ADDRESS)&buf[__X(ofs, buf__len)];
		dispadr = Displays_fblow + (y * Displays_width + x) * Displays_format;
		switch (op) {
			case 1: 
				while (h > 0) {
					__ASSERT((dispadr >= Displays_fblow && dispadr + w <= Displays_fbhigh), 0);
					__MOVE(bufadr, dispadr, w);
					bufadr += stride;
					dispadr += Displays_fbstride;
					h -= 1;
				}
				break;
			case 0: 
				buflow = (ADDRESS)&buf[0];
				bufhigh = buflow + buf__len;
				while (h > 0) {
					__ASSERT((bufadr >= buflow && bufadr + w <= bufhigh), 0);
					__MOVE(dispadr, bufadr, w);
					bufadr += stride;
					dispadr += Displays_fbstride;
					h -= 1;
				}
				break;
			default: 
				break;
		}
	}
}

void Displays_Fill (INT32 col, INT32 x, INT32 y, INT32 w, INT32 h)
{
}

typedef
	CHAR Buf__4[4];

void Displays_Dot (INT32 col, INT32 x, INT32 y)
{
	UINT32 t, c;
	if (col >= 0) {
		switch (Displays_format) {
			case 1: 
				c = (UINT32)Displays_ColorToIndex(col);
				break;
			case 2: 
				c = (((UINT32)__ASHR(col, 8) & 0xf800) | ((UINT32)__ASHR(col, 5) & 0x07e0)) | ((UINT32)__ASHR(col, 3) & 0x1f);
				break;
			case 3: case 4: 
				c = (UINT32)__MASK(col, -16777216);
				break;
			default: __CASECHK;
		}
		if (__ASHL(col, 1) < 0) {
			if (c == 0x0) {
				c = 0xffffffff;
			}
			Displays_Transfer((Buf__4*)t, 4, 0, Displays_format, x, y, 1, 1, 0);
			c = t ^ c;
		}
		Displays_Transfer((Buf__4*)c, 4, 0, Displays_format, x, y, 1, 1, 1);
	}
}

typedef
	CHAR Buf__9[4];

void Displays_Mask (CHAR *buf, ADDRESS buf__len, INT32 bitofs, INT32 stride, INT32 fg, INT32 bg, INT32 x, INT32 y, INT32 w, INT32 h)
{
	INT32 p, i;
	UINT32 s, fgc, bgc, t;
	if ((w > 0 && h > 0)) {
		switch (Displays_format) {
			case 1: 
				if (fg >= 0) {
					fgc = (UINT32)Displays_ColorToIndex(fg);
				}
				if (bg >= 0) {
					bgc = (UINT32)Displays_ColorToIndex(bg);
				}
				break;
			case 2: 
				fgc = (((UINT32)__ASHR(fg, 8) & 0xf800) | ((UINT32)__ASHR(fg, 5) & 0x07e0)) | ((UINT32)__ASHR(fg, 3) & 0x1f);
				bgc = (((UINT32)__ASHR(bg, 8) & 0xf800) | ((UINT32)__ASHR(bg, 5) & 0x07e0)) | ((UINT32)__ASHR(bg, 3) & 0x1f);
				break;
			case 3: case 4: 
				fgc = (UINT32)__MASK(fg, -16777216);
				bgc = (UINT32)__MASK(bg, -16777216);
				break;
			default: __CASECHK;
		}
		if ((__ASHL(fg, 1) < 0 && fgc == 0x0)) {
			fgc = 0xffffffff;
		}
		if ((__ASHL(bg, 1) < 0 && bgc == 0x0)) {
			bgc = 0xffffffff;
		}
		p = ((ADDRESS)&buf[0]) + __ASHL(__ASHR(bitofs, 5), 2);
		bitofs = __MASK(bitofs, -32);
		stride = __ASHL(stride, 3);
		for (;;) {
			__GET(p, s, UINT32);
			i = bitofs;
			for (;;) {
				if (__IN(__MASK(i, -32), s, 32)) {
					if (fg >= 0) {
						if (__ASHL(fg, 1) < 0) {
							Displays_Transfer((Buf__9*)t, 4, 0, Displays_format, (x + i) - bitofs, y, 1, 1, 0);
							t = t ^ fgc;
						} else {
							t = fgc;
						}
						Displays_Transfer((Buf__9*)t, 4, 0, Displays_format, (x + i) - bitofs, y, 1, 1, 1);
					}
				} else {
					if (bg >= 0) {
						if (__ASHL(bg, 1) < 0) {
							Displays_Transfer((Buf__9*)t, 4, 0, Displays_format, (x + i) - bitofs, y, 1, 1, 0);
							t = t ^ bgc;
						} else {
							t = bgc;
						}
						Displays_Transfer((Buf__9*)t, 4, 0, Displays_format, (x + i) - bitofs, y, 1, 1, 1);
					}
				}
				i += 1;
				if (i - bitofs == w) {
					break;
				}
				if (__MASK(i, -32) == 0) {
					__GET(p + __ASHR(i, 3), s, UINT32);
				}
			}
			h -= 1;
			if (h == 0) {
				break;
			}
			y += 1;
			bitofs += stride;
			if (bitofs >= 32 || bitofs < 0) {
				p += __ASHL(__ASHR(bitofs, 5), 2);
				bitofs = __MASK(bitofs, -32);
			}
		}
	}
}

void Displays_Copy (INT32 sx, INT32 sy, INT32 w, INT32 h, INT32 dx, INT32 dy)
{
}

INT32 Displays_ColorToIndex (INT32 col)
{
	return (INT32)((((UINT32)__ASHR(col, 16) & 0xe0) | ((UINT32)__ASHR(col, 11) & 0x1c)) | ((UINT32)__ASHR(col, 6) & 0x03));
}

INT32 Displays_IndexToColor (INT32 index)
{
	return (__ASHL((INT32)(((UINT32)index & 0xe0)), 16) + __ASHL((INT32)(((UINT32)index & 0x1c)), 11)) + __ASHL((INT32)(((UINT32)index & 0x03)), 6);
}

void Displays_InitFrameBuffer (INT32 adr, INT32 size)
{
	__ASSERT((Displays_width * (Displays_height + Displays_offscreen)) * Displays_format <= size, 0);
	Displays_fblow = adr;
	Displays_fbhigh = Displays_fblow + size;
	Displays_fbstride = Displays_width * Displays_format;
	__ASSERT(__ASHR(Displays_fblow, 31) == __ASHR(Displays_fbhigh, 31), 100);
}

static void EnumPtrs(void (*P)(void*))
{
	P(Displays_buf);
}


export void *Displays__init(void)
{
	__DEFMOD;
	__REGMOD("Displays", EnumPtrs);
/* BEGIN */
	Displays_buf = NIL;
	__ENDMOD;
}
