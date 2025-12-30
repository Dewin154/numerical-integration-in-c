#include <windows.h>
#include <stdio.h>
#include <conio.h>
#include <stdlib.h>
#include <math.h>
#include "NIN_Integration.h"
#include "TST_TestCases.h"
#include "APP_Application.h"


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


int main(void)
{
	float (*pPolynomialFunction) (float x) = &function1;
	float (*pTrigonometricFunction)(float x) = &function2;
	float a = -20;
	float b = 0;
	int n = 20; // TODO unsigned short führt zu Implicit conversion!


	float result = 0;
	float* pResult = &result;
	int userChoice;
	int iErr = E_OK;

	printf("Type the number to choose the action:\n");
	printf("1. Calculate the integral of Polynomial Function\n");
	printf("2. Calculate the integral of Trigonometric Function\n");
	printf("3. Run the tests\n");
	printf("4. Terminate program\n");
	scanf_s("%d", &userChoice);

	if (userChoice == 1) 
	{
		/* result speichern und fehlerbehebung machen */
		short rectangleErrCode = NIN_Rectangle(pTrigonometricFunction, a, b, n, pResult);

		printf("\nResult of Rectangle is: %f, ErrCode: %d", result, rectangleErrCode);

		result = 0;

		short trapezoidErrCode = NIN_Trapezoid(pTrigonometricFunction, a, b, n, pResult);

		printf("\nResult of Trapezoid is: %f, ErrCode: %d", result, trapezoidErrCode);

		result = 0;

		short simpsonErrCode = NIN_Simpson(pTrigonometricFunction, a, b, n, pResult);

		printf("\nResult of Simpson is:   %f, ErrCode: %d", result, simpsonErrCode);

		return 1;
	} 
	else if (userChoice == 2)
	{
		return 2;
	}
	else if (userChoice == 3)
	{
		return 3;
	}
	else 
	{
		return E_EXIT;
	}

}