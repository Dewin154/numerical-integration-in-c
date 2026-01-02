#include <windows.h>
#include <stdio.h>
#include <conio.h>
#include <stdlib.h>
#include <math.h>
#include "global.h"
#include "APP_Application.h"


// 4x^4 + 7x^3 - 4x + 14
float function1(float x)
{
	return (float)(4 * x * x * x * x) + (7 * x * x * x) - (4 * x) + 14;
}


// 18 * sin x
float function2(float x)
{
	return (float)(18 * sin(x));
}


int main(void)
{
	t_APP_ContainerResults APP_TestResults;
	t_APP_SingleResult APP_SingleResult;

	float (*pPolynomialFunction) (float x) = &function1;
	float (*pTrigonometricFunction)(float x) = &function2;
	const short a = 0;
	const short b = 20;

	const unsigned short n = 10;
	const unsigned short array[3] = { 10, 50, 100 };

	int userChoice;
	int iErr = E_OK;

	printf("------NUMERICAL INTEGRATION IN C------\n");
	printf("Polynomial Function: 4x^4 + 7x^3 - 4x + 14\n");
	printf("Trigonometric Function: 18 * sin(x)\n");
	printf("Predefined Intervall: [%d, %d]\n\n", a, b);
	printf("Type the number to choose the action:\n\n");
	printf("1. Calculate the integral of Polynomial Function\n");
	printf("2. Calculate the integral of Trigonometric Function\n");
	printf("3. Run the tests for Polynomial Function\n");
	printf("4. Run the tests for Trigonometric Function\n");
	printf("5. Terminate program\n");
	printf("--------------------------------------\n");
	scanf_s("%d", &userChoice);
	printf("\n");

	if (userChoice == 1)
	{
		iErr = APP_calculateIntegral(pPolynomialFunction, a, b, n, &APP_SingleResult);
		
		if (iErr != E_OK) 
		{
			printf("Error while calculating integral of polynomial function!\n\n");
		}
		else
		{
			printf("Results (N=%d):\n", n);
			printf("Rectangle: %.3f\n", APP_SingleResult.resultRectangle);
			printf("Trapezoid: %.3f\n", APP_SingleResult.resultTrapezoid);
			printf("Simpson:   %.3f\n", APP_SingleResult.resultSimpson);
		}
	}
	else if (userChoice == 2)
	{
		iErr = APP_calculateIntegral(pTrigonometricFunction, a, b, n, &APP_SingleResult);

		if (iErr != E_OK)
		{
			printf("Error while calculating integral of trigonometric function!\n\n");
		}
		else 
		{
			printf("Results (N=%d):\n", n);
			printf("Rectangle: %.3f\n", APP_SingleResult.resultRectangle);
			printf("Trapezoid: %.3f\n", APP_SingleResult.resultTrapezoid);
			printf("Simpson:   %.3f\n", APP_SingleResult.resultSimpson);
		}
	}
	else if (userChoice == 3)
	{
		iErr = APP_runTestPolynomial(pPolynomialFunction, a, b, array, &APP_TestResults);

		if (iErr != E_OK)
		{
			printf("Error while running polynomial test!\n\n");
		}
		else
		{
			printf("--- Accuracy Results (Polynomial) ---\n");
			
			for (int i = 0; i < 3; i++)
			{
				printf("\nN = %d:\n", array[i]);
				printf("Rectangle: %.3f%%\n", APP_TestResults.rectangle.accuracy[i]);
				printf("Trapezoid: %.3f%%\n", APP_TestResults.trapezoid.accuracy[i]);
				printf("Simpson:   %.3f%%\n", APP_TestResults.simpson.accuracy[i]);
			}
		}
	}
	else if (userChoice == 4)
	{
		iErr = APP_runTestTrigonometric(pTrigonometricFunction, a, b, array, &APP_TestResults);

		if (iErr != E_OK)
		{
			printf("Error while running trigonometric test!\n\n");
		}
		else
		{
			printf("--- Accuracy Results (Trigonometric) ---\n");
			for (int i = 0; i < 3; i++)
			{
				printf("\nN = %d:\n", array[i]);
				printf("Rectangle: %.3f%%\n", APP_TestResults.rectangle.accuracy[i]);
				printf("Trapezoid: %.3f%%\n", APP_TestResults.trapezoid.accuracy[i]);
				printf("Simpson:   %.3f%%\n", APP_TestResults.simpson.accuracy[i]);
			}
		}
	}
	else
	{
		iErr = E_EXIT;
	}

	return iErr;
}