#include <windows.h>
#include <stdio.h>
#include <conio.h>
#include <stdlib.h>
#include "NIN_Integration.h"


// 4x^4 + 7x^3 - 4x + 14
float function1(float x)
{
	return (float) (4 * x * x * x * x) + (7 * x * x * x) - (4 * x) + 14;
}


// 18 * sin x
float function2(float x)
{
	return (float) (18 * sin(x));
}


void main(void)
{
	float (*pFunc)(float x) = &function1;
	float result = 0;
	float* pResult = &result;
	int userChoice;
	int iErr = E_OK;

	printf("Type the number to choose the action:\n");
	printf("1. Calculate the integral\n");
	printf("2. Run the tests\n");
	printf("3. Terminate program\n");
	scanf_s("%d", &userChoice);

	if (userChoice == 1) 
	{
		/* result speichern und fehlerbehung machen */
		int calc = NIN_Rectangle(pFunc, 5, 12, 50, pResult);

		printf("\nResult of Rectangle is: %f", result);

		NIN_Trapezoid(pFunc, 5, 12, 50, pResult);

		printf("\nResult of Trapezoid is: %f", result);

		NIN_Simpson(pFunc, 5, 12, 50, pResult);

		printf("\nResult of Simpson is:   %f", result);

		return 1;
	} 
	else if (userChoice == 2)
	{
		return 2;
	}
	else 
	{
		return E_EXIT;
	}

}