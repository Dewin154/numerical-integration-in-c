/**********************************************************************************************************************
***********************************************************************************************************************
*                                                                                                                     *
* Copyright (c) 2026, Your Company. All rights reserved!                                                              *
*                                                                                                                     *
* All rights exclusively reserved for Your Company, unless expressly otherwise agreed.                                *
*                                                                                                                     *
* Redistribution in source or any other form, with or without modification, is not permitted.                         *
*                                                                                                                     *
* You may use this code under the according license terms of Your Company. Please contact Your Company                *
* to get the appropriate terms and conditions.                                                                        *
*                                                                                                                     *
***********************************************************************************************************************

Component   Controller (CON)

Filename    CON_Controller.c

brief       Main entry point. Handles user interaction, input validation and control flow.

author      Peter Okruhlica

***********************************************************************************************************************
* Changes                                                                                                             *
***********************************************************************************************************************

Version   Date        Sign  Description
--------  ----------  ----  -----------
01.00.00  2025-12-31  PO    Initial implementation
01.01.00  2026-01-04  PO    Refactoring, added input validation and moved constants to main for better reusability

**********************************************************************************************************************/

/**********************************************************************************************************************
INCLUDES
**********************************************************************************************************************/

#include <windows.h>
#include <stdio.h>
#include <conio.h>
#include <stdlib.h>
#include <math.h>
#include "global.h"
#include "APP_Application.h"
#include "CON_Controller.h"

/**********************************************************************************************************************
MACROS
**********************************************************************************************************************/

#define CON_MAJOR_VERSION 01
#define CON_MINOR_VERSION 01
#define CON_PATCH_VERSION 00

/**********************************************************************************************************************
FUNCTIONS
**********************************************************************************************************************/

/*********************************************************************************************************************/
/* Mathematical polynomial function: f(x) = 4x^4 + 7x^3 - 4x + 14
*
* param[in]    x     Input value
*
* retval       float calculated value f(x)
*
* author       Peter Okruhlica
**********************************************************************************************************************/
float function1(float x)
{
    return (float)(4 * x * x * x * x) + (7 * x * x * x) - (4 * x) + 14;
}

/*********************************************************************************************************************/
/* Mathematical trigonometric function: f(x) = 18 * sin(x)
*
* param[in]    x     Input value (in radians)
*
* retval       float calculated value f(x)
*
* author       Peter Okruhlica
**********************************************************************************************************************/
float function2(float x)
{
    return (float)(18 * sin(x));
}

/*********************************************************************************************************************/
/* Validates the configuration parameters before the main execution starts.
*
* Checks if the interval is valid and if reference values are non-zero to prevent
* division by zero errors in the application module.
*
* param[in]    refPoly   Reference result for the polynomial function
* param[in]    refTri    Reference result for the trigonometric function
* param[in]    a         Start of integration interval
* param[in]    b         End of integration interval
*
* retval       E_OK               Input is valid
* retval       E_INVALID_INTERVAL Interval is invalid
* retval       E_NOT_OK           Reference values are invalid
*
* author       Peter Okruhlica
**********************************************************************************************************************/
static int CON_ValidateInput(float refPoly, float refTri, short a, short b)
{
    int iErr = E_OK;

    if (b <= a)
    {
        iErr = E_INVALID_INTERVAL;
    }

    if ((refPoly == 0.0F) || (refTri == 0.0F))
    {
        iErr = E_NOT_OK;
    }

    return iErr;
}

/*********************************************************************************************************************/
/* brief       Main function of the application
*
* Initializes data, validates inputs and handles the user menu loop.
* Calls the APP module to perform calculations and displays the results.
*
* retval       E_OK    Program finished successfully
* retval       E_EXIT  Program terminated by user or error
*
* author       Peter Okruhlica
**********************************************************************************************************************/
int main(void)
{
    t_APP_ContainerResults APP_TestResults;
    t_APP_SingleResult APP_SingleResult;

    float (*pPolynomialFunction) (float x) = &function1;
    float (*pTrigonometricFunction) (float x) = &function2;

    const float resultPolynomial = 2839480.0F;
    const float resultTrigonometric = 10.654F;

    const short a = 0;
    const short b = 20;

    const unsigned short n = 10;
    const unsigned short array[3] = { 10, 50, 100 };

    int userChoice;
    int iErr = E_OK;

    iErr = CON_ValidateInput(resultPolynomial, resultTrigonometric, a, b);

    if (iErr != E_OK)
    {
        printf("CRITICAL ERROR: Invalid Configuration Parameters\n");
    }
    else
    {
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
            iErr = APP_CalculateIntegral(pPolynomialFunction, a, b, n, &APP_SingleResult);

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
            iErr = APP_CalculateIntegral(pTrigonometricFunction, a, b, n, &APP_SingleResult);
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
            iErr = APP_RunTestPolynomial(pPolynomialFunction, a, b, array, &resultPolynomial, &APP_TestResults);
            if (iErr != E_OK)
            {
                printf("Error while running polynomial test!\n\n");
            }
            else
            {
                printf("--- Accuracy Results (Polynomial) ---\n");
                for (int i = 0; i < NUM_TEST_CASES; i++)
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
            iErr = APP_RunTestTrigonometric(pTrigonometricFunction, a, b, array, &resultTrigonometric, &APP_TestResults);

            if (iErr != E_OK)
            {
                printf("Error while running trigonometric test!\n\n");
            }
            else
            {
                printf("--- Accuracy Results (Trigonometric) ---\n");
                for (int i = 0; i < NUM_TEST_CASES; i++)
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
    }
    return iErr;
}

/*********************************************************************************************************************/
/* Returns the current version of the CON module.
*
* param[out]   major   Pointer to store the major version number
* param[out]   minor   Pointer to store the minor version number
* param[out]   patch   Pointer to store the patch version number
*
* retval       E_OK    Version retrieval successful
*
* author       Peter Okruhlica
**********************************************************************************************************************/
int CON_GetVersion(unsigned char* major, unsigned char* minor, unsigned char* patch)
{
    int iErr = E_OK;

    *major = CON_MAJOR_VERSION;
    *minor = CON_MINOR_VERSION;
    *patch = CON_PATCH_VERSION;

    return iErr;
}

/**********************************************************************************************************************
EOF
**********************************************************************************************************************/