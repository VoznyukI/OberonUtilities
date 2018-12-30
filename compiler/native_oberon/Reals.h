/* voc 2.1.0 [2017/09/06]. Bootstrapping compiler for address size 8, alignment 8. xtaSv */

#ifndef Reals__h
#define Reals__h

#include "SYSTEM.h"


import UINT32 Reals_DefaultFCR;


import INT32 Reals_Expo (REAL x);
import INT32 Reals_ExpoL (LONGREAL x);
import UINT32 Reals_FCR (void);
import INT32 Reals_Int (REAL x);
import void Reals_IntL (LONGREAL x, INT32 *h, INT32 *l);
import BOOLEAN Reals_IsNaN (REAL x);
import BOOLEAN Reals_IsNaNL (LONGREAL x);
import REAL Reals_NaN (INT32 l);
import INT32 Reals_NaNCode (REAL x);
import void Reals_NaNCodeL (LONGREAL x, INT32 *h, INT32 *l);
import LONGREAL Reals_NaNL (INT32 h, INT32 l);
import REAL Reals_Real (INT32 h);
import LONGREAL Reals_RealL (INT32 h, INT32 l);
import void Reals_SetExpo (INT32 e, REAL *x);
import void Reals_SetExpoL (INT32 e, LONGREAL *x);
import void Reals_SetFCR (UINT32 s);
import LONGREAL Reals_Ten (INT32 e);
import void *Reals__init(void);


#endif // Reals
