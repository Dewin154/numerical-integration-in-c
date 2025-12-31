#include <windows.h>
#include <stdio.h>
#include <conio.h>
#include <stdlib.h>
#include <math.h>
#include "NIN_Integration.h"
#include "TST_TestAccuracy.h"
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
	float a = 0;
	float b = 20;
	int n = 20; // TODO unsigned short führt zu Implicit conversion!

	const short array[3] = { 10, 50, 100 };


	float result = 0;
	float* pResult = &result;
	int userChoice;
	int iErr = E_OK;

	printf("------NUMERICAL INTEGRATION IN C------\n");
	printf("Type the number to choose the action:\n\n");
	printf("1. Calculate the integral of Polynomial Function\n");
	printf("2. Calculate the integral of Trigonometric Function\n");
	printf("3. Run the tests for Polynomial Function\n");
	printf("4. Run the tests for Trigonometric Function\n");
	printf("5. Terminate program\n");
	printf("--------------------------------------\n");
	scanf_s("%d", &userChoice);

	if (userChoice == 1) 
	{

	} 
	else if (userChoice == 2)
	{
		

	}
	else if (userChoice == 3)
	{
		TST_calculateAccuracyPolynomial();

	}
	else if (userChoice == 4)
	{
		TST_calculateAccuracyTrigonometric();

	}
	else 
	{
		return E_EXIT;
	}

}