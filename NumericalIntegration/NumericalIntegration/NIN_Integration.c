#include "NIN_Integration.h"



// prototype
int NIN_Rectangle(const float (*function)(float x), float a, float b, short n, float *pResult)
{
	int iErr = E_OK;
	float intervalDifference = b - a;

	if (n == 0) 
    {
		iErr = E_INVALID_N;
	}
	else if (n > MAX_ITERATIONS)
	{
		iErr = E_TOO_MANY_ITERATIONS;
	}
	else if (intervalDifference <= 0) 
	{
		iErr = E_INVALID_INTERVAL;
	}
	else if (function == NULL)
	{
		iErr = E_FUNCTION_NULL_POINTER;
	}
	else if (pResult == NULL) 
	{
		iErr = E_VARIABLE_NULL_POINTER;
	}
	else 
	{
		float hCoefficient = intervalDifference / n;
		float summation = 0;
		float result = 0;
		float rectangleStep = 0;

		for (int i = 0; i < n; i++)
		{
			rectangleStep = a + (i * hCoefficient);
			summation = summation + function(rectangleStep);
		}

		result = summation * hCoefficient;
		*pResult = result;
	}
	
	return iErr;
}

// prototype
int NIN_Trapezoid(const float (*function)(float x), float a, float b, short n, float *pResult)
{
    int iErr = E_OK;
    float intervalDifference = b - a;

    if (n == 0) 
    {
        iErr = E_INVALID_N;
    }
    else if (n > MAX_ITERATIONS)
    {
        iErr = E_TOO_MANY_ITERATIONS;
    }
    else if (intervalDifference <= 0)
    {
        iErr = E_INVALID_INTERVAL;
    }
    else if (function == NULL)
    {
        iErr = E_FUNCTION_NULL_POINTER;
    }
    else if (pResult == NULL) 
    {
        iErr = E_VARIABLE_NULL_POINTER;
    }
    else 
    {
        float hCoefficient = intervalDifference / n;
        float termCoefficient = hCoefficient / 2;
        float functionLowerBound = function(a);
        float functionUpperBound = function(b);

        float summation = 0;
        float result = 0;
        float trapezoidStep = 0;

        for (int i = 1; i < n; i++)
        {
            trapezoidStep = a + (i * hCoefficient);
            summation = summation + (2 * function(trapezoidStep));
        }

        result = functionLowerBound + summation + functionUpperBound;
        result = termCoefficient * result;
        *pResult = result;
    }
    
    return iErr;
}

// prototype
int NIN_Simpson(const float (*function)(float x), float a, float b, short n, float* pResult)
{
    int iErr = E_OK;
    float intervalDifference = b - a;

    if (n == 0) 
    {
        iErr = E_INVALID_N;
    }
    else if (n > MAX_ITERATIONS)
    {
        iErr = E_TOO_MANY_ITERATIONS;
    }
    else if (intervalDifference <= 0) 
    {
        iErr = E_INVALID_INTERVAL;
    }
    else if (function == NULL)
    {
        iErr = E_FUNCTION_NULL_POINTER;
    }
    else if (pResult == NULL)
    {
        iErr = E_VARIABLE_NULL_POINTER;
    }
    else
    {
        float hCoefficient = intervalDifference / n;
        float termCoefficient = hCoefficient / 3.0f;
        float functionLowerBound = function(a);
        float functionUpperBound = function(b);

        float firstSummation = 0;
        float secondSummation = 0;
        float result = 0;
        float simpsonStep = 0;

        int firstSummationBoundary = n / 2;
        int secondSummationBoundary = (n / 2) - 1;

        for (int i = 1; i <= firstSummationBoundary; i++)
        {
            simpsonStep = a + (2 * i - 1) * hCoefficient;
            firstSummation = firstSummation + function(simpsonStep);
        }

        firstSummation = 4 * firstSummation;

        for (int i = 1; i <= secondSummationBoundary; i++)
        {
            simpsonStep = a + (2 * i) * hCoefficient;
            secondSummation = secondSummation + function(simpsonStep);
        }

        secondSummation = 2 * secondSummation;

        result = functionLowerBound + firstSummation + secondSummation + functionUpperBound;
        result = termCoefficient * result;
        *pResult = result;
    }

    return iErr;
}
