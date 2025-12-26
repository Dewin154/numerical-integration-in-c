#include "NIN_Integration.h"



// prototype
NIN_Rectangle(const float (*function)(float x), short a, short b, short n, float *pResult)
{
	int iErr = E_OK;
	float coeff = b - a;

	if (n == 0) {
		iErr = E_INVALID_N;
	}
	else if (coeff == 0) {
		iErr = E_INVALID_INTERVAL;
	}
	else 
	{
		float coeff_done = coeff / n;
		float summation = 0;
		float result = 0;

		for (int i = 0; i < n; i++)
		{
			float rectangle_step = a + (i * coeff_done);
			result = result + function(rectangle_step);
		}

		result = result * coeff_done;
		*pResult = result;
	}
	
	return iErr;
}

// prototype
NIN_Trapezoid(const float (*function)(float x), short a, short b, short n, float* pResult)
{
	float coeff = b - a;
	coeff = coeff / n;
	float coeff_done = coeff / 2.0;
	float functionLowerBound = function(a);
	float functionUpperBound = function(b);

	float summation = 0;
	float result = 0;

	for (int i = 1; i < n; i++)
	{
		float trapezoid_step = a + (i * coeff);
		summation = summation + (2 * function(trapezoid_step));
	}

	result = functionLowerBound + summation + functionUpperBound;
	result = coeff_done * result;
	*pResult = result;

}

// prototype
NIN_Simpson(const float (*function)(float x), short a, short b, short n, float* pResult)
{
	float coeff = b - a;
	coeff = coeff / n;
	float coeff_done = coeff / 3.0;
	float functionLowerBound = function(a);
	float functionUpperBound = function(b);

	float firstSummation = 0;
	float secondSummation = 0;
	float result = 0;


	for (int i = 1; i <= n / 2; i++)
	{
		float simpson_step = a + (2 * i - 1) * coeff;
		firstSummation = firstSummation + function(simpson_step);
	}

	firstSummation = 4 * firstSummation;

	for (int i = 1; i <= (n / 2) - 1; i++)
	{
		float simpson_step = (a + (2 * i) * coeff);
		secondSummation = secondSummation + function(simpson_step);
	}

	secondSummation = 2 * secondSummation;

	result = functionLowerBound + firstSummation + secondSummation + functionUpperBound;
	result = coeff_done * result;

	*pResult = result;

}

// Makro für abs() definieren da integrale nicht negativ sind