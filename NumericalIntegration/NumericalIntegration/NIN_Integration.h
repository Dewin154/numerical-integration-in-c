#include <stdio.h>

extern int NIN_Rectangle(float (*function)(float x), short a, short b, short n, float* pResult);

extern int NIN_Trapezoid(float (*function)(float x), short a, short b, short n, float* pResult);

extern int NIN_Simpson(float (*function)(float x), short a, short b, short n, float* pResult);