#include "TST_TestAccuracy.h"
#include "NIN_Integration.h"

/*Prototype Implementation*/

typedef struct {
	float results[3];
    float accuracy[3];
} t_TST_RectangleResults;

typedef struct {
	float results[3];
    float accuracy[3];
} t_TST_TrapezoidResults;

typedef struct {
	float results[3];
    float accuracy[3];
} t_TST_SimpsonResults;

static t_TST_RectangleResults TST_RectangleResults;
static t_TST_TrapezoidResults TST_TrapezoidResults;
static t_TST_SimpsonResults TST_SimpsonResults;

const float resultPolynomial = 2839480.0F;
const float resultTrigonometric = 10.6545F;


int TST_runTestPolynomial(const float (*function)(float x), float a, float b, const unsigned short arrayOfN[])
{
    NIN_Init();

    TST_calculateIntegral(function, a, b, arrayOfN);

    TST_calculateAccuracyPolynomial();

    return 0;
}

int TST_runTestTrigonometric(const float (*function)(float x), float a, float b, const unsigned short arrayOfN[])
{
    NIN_Init();

    TST_calculateIntegral(function, a, b, arrayOfN);

    TST_calculateAccuracyTrigonometric();

    return 0;
}

//                                                                                              TODO muss abgesichert werden
int TST_calculateIntegral(const float (*function)(float x), float a, float b, const unsigned short arrayOfN[])
{
    for (int i = 0; i < 3; i++)
    {
        NIN_Rectangle(function, a, b, arrayOfN[i], &TST_RectangleResults.results[i]);
        NIN_Trapezoid(function, a, b, arrayOfN[i], &TST_TrapezoidResults.results[i]);
        NIN_Simpson(function, a, b, arrayOfN[i], &TST_SimpsonResults.results[i]);
    }

    return 0;
}

int TST_calculateAccuracyPolynomial(void)
{
    for (int i = 0; i < 3; i++)
    {
        TST_RectangleResults.accuracy[i] = TST_RectangleResults.results[i] / resultPolynomial;
        TST_TrapezoidResults.accuracy[i] = TST_TrapezoidResults.results[i] / resultPolynomial;
        TST_SimpsonResults.accuracy[i] = TST_SimpsonResults.results[i] / resultPolynomial;
    }

	return 0;
}

int TST_calculateAccuracyTrigonometric(void)
{
    for (int i = 0; i < 3; i++)
    {
        TST_RectangleResults.accuracy[i] = TST_RectangleResults.results[i] / resultTrigonometric;
        TST_TrapezoidResults.accuracy[i] = TST_TrapezoidResults.results[i]  / resultTrigonometric;
        TST_SimpsonResults.accuracy[i] = TST_SimpsonResults.results[i]/ resultTrigonometric;
    }

    return 0;
}

int TST_getResults(float *resultStruct)
{
    return 0;
}