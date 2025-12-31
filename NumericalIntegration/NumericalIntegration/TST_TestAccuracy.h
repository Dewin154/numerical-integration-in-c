#pragma once

extern int TST_runTestPolynomial(const float (*function)(float x), float a, float b, const unsigned short arrayOfN[]);

extern int TST_runTestTrigonometric(const float (*function)(float x), float a, float b, const unsigned short arrayOfN[]);

extern int TST_getResults(float resultArray[]);

int TST_calculateIntegral(const float (*function)(float x), float a, float b, const unsigned short arrayOfN[]);

int TST_calculateAccuracyPolynomial(void);

int TST_calculateAccuracyTrigonometric(void);