#ifndef _NIN_INTEGRATION_H_ /* Include Guard */
#define _NIN_INTEGRATION_H_

#include <stdio.h>
#include "global.h"

#define MAX_ITERATIONS (1000)

extern int NIN_Rectangle(float (*function)(float x), float a, float b, short n, float* pResult);

extern int NIN_Trapezoid(float (*function)(float x), float a, float b, short n, float* pResult);

extern int NIN_Simpson(float (*function)(float x), float a, float b, short n, float* pResult);


#endif