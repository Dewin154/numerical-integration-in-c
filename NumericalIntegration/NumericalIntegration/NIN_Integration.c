/**********************************************************************************************************************

***********************************************************************************************************************
*                                                                                                                     *
* Copyright (c) 2025, Your Company. All rights reserved!                                                              *
*                                                                                                                     *
* All rights exclusively reserved for Your Company, unless expressly otherwise agreed.                                *
*                                                                                                                     *
* Redistribution in source or any other form, with or without modification, is not permitted.                         *
*                                                                                                                     *
* You may use this code under the according license terms of Your Company. Please contact Your Company                *
* to get the appropriate terms and conditions.                                                                        *
*                                                                                                                     *
***********************************************************************************************************************

Component   NIN_Integration

Filename    NIN_Integration.c

brief       Implementation of 3 numerical integration functions

author      Peter Okruhlica

***********************************************************************************************************************
* Changes                                                                                                             *
***********************************************************************************************************************

Version   Date        Sign  Description
--------  ----------  ----  -----------
01.00.00  2025-12-19  PO    Initial check in
01.00.01  2025-12-24  PO    Prototype implementation of integration
01.01.00  2025-12-26  PO    Refining structure in context of embedded development
01.01.01  2025-12-28  PO    Adding unified comments
01.01.02  2026-01-02  PO    Remove dead code
01.01.03  2026-01-06  PO    Clean code, move validation of params to separate function

**********************************************************************************************************************/

/**********************************************************************************************************************
INCLUDES
**********************************************************************************************************************/

#include "NIN_Integration.h"
#include "NIN_Integration_cfg.h"
#include <stddef.h>  /* To check for NULL */

/**********************************************************************************************************************
MACROS
**********************************************************************************************************************/

#define NIN_MAJOR_VERSION 01
#define NIN_MINOR_VERSION 01
#define NIN_PATCH_VERSION 03

/**********************************************************************************************************************
PROTOTYPES
**********************************************************************************************************************/

static int validateParameters(const float (*function)(float x), float a, float b, unsigned short n, float* const pResult);

/**********************************************************************************************************************
FUNCTIONS
**********************************************************************************************************************/

/*********************************************************************************************************************/
/* Internal helper function to validate input parameters for integration methods
*
* param[in]    function  Pointer to the mathematical function f(x) to be integrated
* param[in]    a         Start of the integration interval
* param[in]    b         End of the integration interval
* param[in]    n         Number of steps (must be > 0 and <= MAX_ITERATIONS)
* param[in]    pResult   Pointer to the variable where the calculation result will be stored
*
* retval       E_OK                         Parameters are valid
* retval       E_INVALID_N                  Invalid number of iterations
* retval       E_TOO_MANY_ITERATIONS        Too many iterations
* retval       E_INVALID_INTERVAL           Interval is invalid (b <= a)
* retval       E_FUNCTION_NULL_POINTER      Function pointer is null
* retval       E_VARIABLE_NULL_POINTER      Variable pointer is null
*
* author       Peter Okruhlica
**********************************************************************************************************************/
static int validateParameters(const float (*function)(float x), float a, float b, unsigned short n, float* const pResult)
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

    return iErr;
}

/*********************************************************************************************************************/
/* Approximates the integral with rectangle method
*
* Upon calling this function, it first checks if all parameters are valid. If not, execution is stopped and corresponding
* error code is returned. If all parameters are valid, the function approximates the integral of the given function, its
* interval based on the number of interations with the rectangle method.
*
* param[in]    function  Pointer to the mathematical function f(x) to be integrated
* param[in]    a         Start of the integration interval
* param[in]    b         End of the integration interval
* param[in]    n         Number of steps (must be > 0 and <= MAX_ITERATIONS)
*
* param[out]   pResult   Pointer to the variable where the calculation result will be stored
*
*
* retval       E_OK                            Calculation successful
* retval       E_INVALID_N                     Invalid number of iterations was passed
* retval       E_TOO_MANY_ITERATIONS           Too many iterations were passed
* retval       E_INVALID_INTERVAL              Calculated integral is not valid
* retval       E_FUNCTION_NULL_POINTER         Function pointer is null
* retval       E_VARIABLE_NULL_POINTER         Variable pointer is null
* 
* author       Peter Okruhlica
**********************************************************************************************************************/
int NIN_Rectangle(const float (*function)(float x), float a, float b, unsigned short n, float* const pResult)
{
    int iErr = validateParameters(function, a, b, n, pResult);

    if (iErr == E_OK)
    {
        float intervalDifference = b - a;
        float hCoefficient = intervalDifference / n;
        float summation = 0;
        float result = 0;
        float rectangleStep = 0;

        for (int i = 0; i < n; i++)
        {
            rectangleStep = a + (i * hCoefficient);
            summation += function(rectangleStep);
        }

        result = summation * hCoefficient;
        *pResult = result;
    }

    return iErr;
}

/*********************************************************************************************************************/
/* Approximates the integral with trapezoid method
*
* Upon calling this function, it first checks if all parameters are valid. If not, execution is stopped and corresponding
* error code is returned. If all parameters are valid, the function approximates the integral of the given function, its
* interval based on the number of interations with the trapezoid method.
*
* param[in]    function  Pointer to the mathematical function f(x) to be integrated
* param[in]    a         Start of the integration interval
* param[in]    b         End of the integration interval
* param[in]    n         Number of steps (must be > 0 and <= MAX_ITERATIONS)
*
* param[out]   pResult   Pointer to the variable where the calculation result will be stored
*
*
* retval       E_OK                            Calculation successful
* retval       E_INVALID_N                     Invalid number of iterations was passed
* retval       E_TOO_MANY_ITERATIONS           Too many iterations were passed
* retval       E_INVALID_INTERVAL              Calculated integral is not valid
* retval       E_FUNCTION_NULL_POINTER         Function pointer is null
* retval       E_VARIABLE_NULL_POINTER         Variable pointer is null
*
* author       Peter Okruhlica
**********************************************************************************************************************/
int NIN_Trapezoid(const float (*function)(float x), float a, float b, unsigned short n, float* const pResult)
{
    int iErr = validateParameters(function, a, b, n, pResult);

    if (iErr == E_OK)
    {
        float intervalDifference = b - a;
        float hCoefficient = intervalDifference / n;
        float termCoefficient = hCoefficient / 2.0F;
        float functionLowerBound = function(a);
        float functionUpperBound = function(b);

        float summation = 0;
        float result = 0;
        float trapezoidStep = 0;

        for (int i = 1; i < n; i++)
        {
            trapezoidStep = a + (i * hCoefficient);
            summation += (2 * function(trapezoidStep)); 
        }

        result = functionLowerBound + summation + functionUpperBound;
        result = termCoefficient * result;
        *pResult = result;
    }

    return iErr;
}

/*********************************************************************************************************************/
/* Approximates the integral with simpson method
*
* Upon calling this function, it first checks if all parameters are valid. If not, execution is stopped and corresponding
* error code is returned. If all parameters are valid, the function approximates the integral of the given function, its
* interval based on the number of interations with the simpson method.
*
* param[in]    function  Pointer to the mathematical function f(x) to be integrated
* param[in]    a         Start of the integration interval
* param[in]    b         End of the integration interval
* param[in]    n         Number of steps (must be > 0 and <= MAX_ITERATIONS)
*
* param[out]   pResult   Pointer to the variable where the calculation result will be stored
*
*
* retval       E_OK                            Calculation successful
* retval       E_INVALID_N                     Invalid number of iterations was passed
* retval       E_TOO_MANY_ITERATIONS           Too many iterations were passed
* retval       E_INVALID_INTERVAL              Calculated integral is not valid
* retval       E_FUNCTION_NULL_POINTER         Function pointer is null
* retval       E_VARIABLE_NULL_POINTER         Variable pointer is null
*
* author       Peter Okruhlica
**********************************************************************************************************************/
int NIN_Simpson(const float (*function)(float x), float a, float b, unsigned short n, float* const pResult)
{
    int iErr = validateParameters(function, a, b, n, pResult);

    if (iErr == E_OK)
    {
        float intervalDifference = b - a;
        float hCoefficient = intervalDifference / n;
        float termCoefficient = hCoefficient / 3.0F;
        float functionLowerBound = function(a);
        float functionUpperBound = function(b);

        float firstSummation = 0;
        float secondSummation = 0;
        float result = 0;
        float simpsonStep = 0;

        int firstSummationBoundary = (n >> 1); /* (n / 2) */
        int secondSummationBoundary = (n >> 1) - 1; /* (n / 2) */

        for (int i = 1; i <= firstSummationBoundary; i++)
        {
            simpsonStep = a + (((i << 1) - 1) * hCoefficient); /* i << 1 == i * 2 */
            firstSummation += function(simpsonStep);
        }

        firstSummation = 4 * firstSummation;

        for (int i = 1; i <= secondSummationBoundary; i++)
        {
            simpsonStep = a + ((i << 1) * hCoefficient); /* i << 1 == i * 2 */
            secondSummation += function(simpsonStep);
        }

        secondSummation = 2 * secondSummation;

        result = functionLowerBound + firstSummation + secondSummation + functionUpperBound;
        result = termCoefficient * result;
        *pResult = result;
    }

    return iErr;
}

/*********************************************************************************************************************/
/* brief       Returns the current version of the NIN module.
*
* param[out]   major   Pointer to store the major version number
* param[out]   minor   Pointer to store the minor version number
* param[out]   patch   Pointer to store the patch version number
*
* retval       E_OK    Version retrieval successful
*
* author       Peter Okruhlica
**********************************************************************************************************************/
int NIN_GetVersion(unsigned char* major, unsigned char* minor, unsigned char* patch)
{
    int iErr = E_OK;

    *major = NIN_MAJOR_VERSION;
    *minor = NIN_MINOR_VERSION;
    *patch = NIN_PATCH_VERSION;

    return iErr;
}

/**********************************************************************************************************************
EOF
**********************************************************************************************************************/