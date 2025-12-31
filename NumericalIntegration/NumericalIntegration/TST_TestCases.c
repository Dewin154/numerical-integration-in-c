#include "TST_TestCases.h"
#include "NIN_Integration.h"
#include <stdio.h>

/*Prototype Implementation*/

typedef struct {
	float results[3];
} t_TST_RectangleResults;

typedef struct {
	float results[3];
} t_TST_TrapezoidResults;

typedef struct {
	float results[3];
} t_TST_SimpsonResults;

static t_TST_RectangleResults TST_RectangleResults;
static t_TST_TrapezoidResults TST_TrapezoidResults;
static t_TST_SimpsonResults TST_SimpsonResults;

const float resultPolynomial = 2839480.0F;
const float resultTrigonometric = 10.6545F;

//                                                                                              TODO muss abgesichert werden
int TST_calculateIntegral(const float (*function)(float x), float a, float b, const unsigned short arrayOfN[3])
{
    NIN_Init();

    for (int i = 0; i < 3; i++)
    {
        /* --- RECTANGLE --- */
        /* Wir übergeben die Adresse des i-ten Elements im Array */
        NIN_Rectangle(function, a, b, arrayOfN[i], &TST_RectangleResults.results[i]);

        /* --- TRAPEZOID --- */
        NIN_Trapezoid(function, a, b, arrayOfN[i], &TST_TrapezoidResults.results[i]);

        /* --- SIMPSON --- */
        NIN_Simpson(function, a, b, arrayOfN[i], &TST_SimpsonResults.results[i]);

        /* Debug Ausgabe (falls hier gewünscht) */
printf("N=%d -> Rect: %f, Trap: %f, Simp: %f\n",
           arrayOfN[i],
           TST_RectangleResults.results[i],
           TST_TrapezoidResults.results[i],
           TST_SimpsonResults.results[i]);
        
    }

    printf("%d", arrayOfN[3]);


	return 0;
}


int TST_calculateAccuracy(float *arrayOfResults[9])
{


	return 0;
}