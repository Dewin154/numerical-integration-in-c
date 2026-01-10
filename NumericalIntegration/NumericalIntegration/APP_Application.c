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

Component   Application (APP)

Filename    APP_Application.c

brief       Implementation of application logic, test runners and accuracy calculation.

author      Peter Okruhlica

***********************************************************************************************************************
* Changes                                                                                                             *
***********************************************************************************************************************

Version   Date        Sign  Description
--------  ----------  ----  -----------
01.00.00  2025-12-31  PO    Initial check in, prototype TST module and architecture change
01.00.01  2026-01-02  PO    Heavy refactoring of error handling and structure usage
01.01.00  2026-01-03  PO    Moved constants to CON Module to improve reusability
01.01.01  2026-01-10  PO    Implemented input parameter validation according to coding guidelines

**********************************************************************************************************************/

/**********************************************************************************************************************
INCLUDES
**********************************************************************************************************************/

#include "APP_Application.h"
#include "NIN_Integration.h"
#include <stddef.h>  /* To check for NULL */

/**********************************************************************************************************************
MACROS
**********************************************************************************************************************/
#define APP_MAJOR_VERSION 01
#define APP_MINOR_VERSION 01
#define APP_PATCH_VERSION 01

#define HUNDERT_PERCENT   (100.0F)

/**********************************************************************************************************************
FUNCTIONS
**********************************************************************************************************************/

/*********************************************************************************************************************/
/* Calculates the integral using all three methods (Rectangle, Trapezoid, Simpson).
*
* Calls the core NIN module functions and stores the results in the provided structure.
* Returns the first error encountered during calculation.
*
* param[in]    function  Pointer to the mathematical function to be integrated
* param[in]    a         Start of the integration interval
* param[in]    b         End of the integration interval
* param[in]    n         Number of steps
*
* param[out]   pResult   Pointer to the structure where results will be stored
*
* retval       E_OK                      All calculations successful
* retval       E_FUNCTION_NULL_POINTER   Function pointer is null
* retval       E_VARIABLE_NULL_POINTER   Result pointer is null
* retval       < 0                       Error code from NIN module
*
* author       Peter Okruhlica
**********************************************************************************************************************/
int APP_CalculateIntegral(const float (*function)(float x), float a, float b, unsigned short n, t_APP_SingleResult* pResult)
{
    int iErr = E_OK;

    if (function == NULL)
    {
        iErr = E_FUNCTION_NULL_POINTER;
    }
    else if (pResult == NULL)
    {
        iErr = E_VARIABLE_NULL_POINTER;
    }
    else
    {
        int iErrRect = NIN_Rectangle(function, a, b, n, &pResult->resultRectangle);
        int iErrTrap = NIN_Trapezoid(function, a, b, n, &pResult->resultTrapezoid);
        int iErrSimp = NIN_Simpson(function, a, b, n, &pResult->resultSimpson);

        if (iErrRect != E_OK)
        {
            iErr = iErrRect;
        }
        else if (iErrTrap != E_OK)
        {
            iErr = iErrTrap;
        }
        else if (iErrSimp != E_OK)
        {
            iErr = iErrSimp;
        }
    }

    return iErr;
}

/*********************************************************************************************************************/
/* Runs a test sequence for the polynomial function.
*
* Iterates through defined test cases, calculates integrals, and computes accuracy
* based on the provided reference value.
*
* param[in]    function          Pointer to the polynomial function
* param[in]    a                 Start of interval
* param[in]    b                 End of interval
* param[in]    arrayOfN          Array containing different step counts N
* param[in]    resultPolynomial  Pointer to the analytical reference result
*
* param[out]   pTestContainerResults     Pointer to the container for results and accuracy
*
* retval       E_OK                      Test run successful
* retval       E_FUNCTION_NULL_POINTER   Function pointer is null
* retval       E_VARIABLE_NULL_POINTER   One of the array/result pointers is null
* retval       < 0                       Error code from NIN module
*
* author       Peter Okruhlica
**********************************************************************************************************************/
int APP_RunTestPolynomial(const float (*function)(float x), float a, float b, const unsigned short* const arrayOfN, const float* const resultPolynomial, t_APP_ContainerResults* pTestContainerResults)
{
    int iErr = E_OK;

    if (function == NULL)
    {
        iErr = E_FUNCTION_NULL_POINTER;
    }
    else if ((arrayOfN == NULL) || (resultPolynomial == NULL) || (pTestContainerResults == NULL))
    {
        iErr = E_VARIABLE_NULL_POINTER;
    }
    else
    {
        t_APP_SingleResult tempResult;

        for (int i = 0; i < NUM_TEST_CASES; i++)
        {
            iErr = APP_CalculateIntegral(function, a, b, arrayOfN[i], &tempResult);

            if (iErr != E_OK)
            {
                break;
            }
            else
            {
                pTestContainerResults->rectangle.results[i] = tempResult.resultRectangle;
                pTestContainerResults->trapezoid.results[i] = tempResult.resultTrapezoid;
                pTestContainerResults->simpson.results[i] = tempResult.resultSimpson;

                if (*resultPolynomial != 0.0F)
                {
                    pTestContainerResults->rectangle.accuracy[i] = (pTestContainerResults->rectangle.results[i] / *resultPolynomial) * HUNDERT_PERCENT;
                    pTestContainerResults->trapezoid.accuracy[i] = (pTestContainerResults->trapezoid.results[i] / *resultPolynomial) * HUNDERT_PERCENT;
                    pTestContainerResults->simpson.accuracy[i] = (pTestContainerResults->simpson.results[i] / *resultPolynomial) * HUNDERT_PERCENT;
                }
                else
                {
                    pTestContainerResults->rectangle.accuracy[i] = 0.0F;
                    pTestContainerResults->trapezoid.accuracy[i] = 0.0F;
                    pTestContainerResults->simpson.accuracy[i] = 0.0F;
                }
            }
        }
    }
    return iErr;
}

/*********************************************************************************************************************/
/* Runs a test sequence for the trigonometric function.
*
* Iterates through defined test cases, calculates integrals, and computes accuracy
* based on the provided reference value.
*
* param[in]    function             Pointer to the trigonometric function
* param[in]    a                    Start of interval
* param[in]    b                    End of interval
* param[in]    arrayOfN             Array containing different step counts N
* param[in]    resultTrigonometric  Pointer to the analytical reference result
*
* param[out]   pTestContainerResults     Pointer to the container for results and accuracy
*
* retval       E_OK                      Test run successful
* retval       E_FUNCTION_NULL_POINTER   Function pointer is null
* retval       E_VARIABLE_NULL_POINTER   One of the array/result pointers is null
* retval       < 0                       Error code from NIN module
*
* author       Peter Okruhlica
**********************************************************************************************************************/
int APP_RunTestTrigonometric(const float (*function)(float x), float a, float b, const unsigned short* const arrayOfN, const float* const resultTrigonometric, t_APP_ContainerResults* pTestContainerResults)
{
    int iErr = E_OK;

    if (function == NULL)
    {
        iErr = E_FUNCTION_NULL_POINTER;
    }
    else if ((arrayOfN == NULL) || (resultTrigonometric == NULL) || (pTestContainerResults == NULL))
    {
        iErr = E_VARIABLE_NULL_POINTER;
    }
    else
    {
        t_APP_SingleResult tempResult;

        for (int i = 0; i < NUM_TEST_CASES; i++)
        {
            iErr = APP_CalculateIntegral(function, a, b, arrayOfN[i], &tempResult);

            if (iErr != E_OK)
            {
                iErr = E_NOT_OK;
                break;
            }
            else
            {
                pTestContainerResults->rectangle.results[i] = tempResult.resultRectangle;
                pTestContainerResults->trapezoid.results[i] = tempResult.resultTrapezoid;
                pTestContainerResults->simpson.results[i] = tempResult.resultSimpson;

                if (*resultTrigonometric != 0.0F)
                {
                    pTestContainerResults->rectangle.accuracy[i] = (pTestContainerResults->rectangle.results[i] / *resultTrigonometric) * HUNDERT_PERCENT;
                    pTestContainerResults->trapezoid.accuracy[i] = (pTestContainerResults->trapezoid.results[i] / *resultTrigonometric) * HUNDERT_PERCENT;
                    pTestContainerResults->simpson.accuracy[i] = (pTestContainerResults->simpson.results[i] / *resultTrigonometric) * HUNDERT_PERCENT;
                }
                else
                {
                    pTestContainerResults->rectangle.accuracy[i] = 0.0F;
                    pTestContainerResults->trapezoid.accuracy[i] = 0.0F;
                    pTestContainerResults->simpson.accuracy[i] = 0.0F;
                }
            }
        }
    }
    return iErr;
}

/*********************************************************************************************************************/
/* brief       Returns the current version of the APP module.
*
* param[out]   major   Pointer to store the major version number
* param[out]   minor   Pointer to store the minor version number
* param[out]   patch   Pointer to store the patch version number
*
* retval       E_OK    Version retrieval successful
*
* author       Peter Okruhlica
**********************************************************************************************************************/
int APP_GetVersion(unsigned char* major, unsigned char* minor, unsigned char* patch)
{
    int iErr = E_OK;
    *major = APP_MAJOR_VERSION;
    *minor = APP_MINOR_VERSION;
    *patch = APP_PATCH_VERSION;

    return iErr;
}
/**********************************************************************************************************************
EOF
**********************************************************************************************************************/