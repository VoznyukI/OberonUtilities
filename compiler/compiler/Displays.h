/* voc 2.1.0 [2017/09/06]. Bootstrapping compiler for address size 8, alignment 8. xtaSv */

#ifndef Displays__h
#define Displays__h

#include "SYSTEM.h"
#include "Displays.h"
#include "Kernel.h"
#include "Modules.h"
#include "Objects.h"


import INT32 Displays_width, Displays_height, Displays_offscreen, Displays_format, Displays_unit;


import INT32 Displays_ColorToIndex (INT32 col);
import void Displays_Copy (INT32 sx, INT32 sy, INT32 w, INT32 h, INT32 dx, INT32 dy);
import void Displays_Dot (INT32 col, INT32 x, INT32 y);
import void Displays_Fill (INT32 col, INT32 x, INT32 y, INT32 w, INT32 h);
import INT32 Displays_IndexToColor (INT32 index);
import void Displays_InitFrameBuffer (INT32 adr, INT32 size);
import void Displays_Mask (CHAR *buf, ADDRESS buf__len, INT32 bitofs, INT32 stride, INT32 fg, INT32 bg, INT32 x, INT32 y, INT32 w, INT32 h);
import void Displays_Transfer (CHAR *buf, ADDRESS buf__len, INT32 ofs, INT32 stride, INT32 x, INT32 y, INT32 w, INT32 h, INT32 op);
import void *Displays__init(void);


#endif // Displays
