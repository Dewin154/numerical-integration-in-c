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
01.01.01  2026-01-08  PO    Remove redundant function
01.02.00  2026-01-09  PO    Encapsulated variables in struct and added CON_Init
01.03.00  2026-01-10  PO    Add do while loop

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
#define CON_MINOR_VERSION 03
#define CON_PATCH_VERSION 00

/**********************************************************************************************************************
TYPEDEFS
**********************************************************************************************************************/

typedef struct {

    float (*pPolynomialFunction)(float x);
    float (*pTrigonometricFunction)(float x);

    float resultPolynomial;
    float resultTrigonometric;

    float a;
    float b;

    unsigned short n;
    unsigned short testSteps[3];

} t_CON_Config;

/**********************************************************************************************************************
GLOBAL VARIABLES
**********************************************************************************************************************/

static t_CON_Config CON_Config;

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
float polynomialFunction(float x)
{
    return (float)(4 * x * x * x * x) + (7 * x * x * x) - (4 * x) + 14;
}

/*********************************************************************************************************************/
/* Mathematical trigonometric function: f(x) = 18 * sin(x)
*
* param[in]    x     Input value
*
* retval       float calculated value f(x)
*
* author       Peter Okruhlica
**********************************************************************************************************************/
float trigonometricFunction(float x)
{
    return (float)(18 * sin(x));
}

/*********************************************************************************************************************/
/* Initializes the CON module configuration with default values.
*
* retval       E_OK    Initialization successful
*
* author       Peter Okruhlica
**********************************************************************************************************************/
int CON_Init(void)
{
    int iErr = E_OK;

    CON_Config.pPolynomialFunction = &polynomialFunction;
    CON_Config.pTrigonometricFunction = &trigonometricFunction;

    CON_Config.resultPolynomial = 2839480.0F;
    CON_Config.resultTrigonometric = 10.655F;

    CON_Config.a = 0.0F;
    CON_Config.b = 20.0F;

    CON_Config.n = 10;

    CON_Config.testSteps[0] = 10;
    CON_Config.testSteps[1] = 50;
    CON_Config.testSteps[2] = 100;

    return iErr;
}

/*********************************************************************************************************************/
/* brief        Main function of the application
*
* Initializes data, validates inputs and handles the user menu loop.
* Calls the APP module to perform calculations and displays the results.
*
* retval        E_OK    Program finished successfully
* retval        E_EXIT  Program terminated by user or error
*
* author        Peter Okruhlica
**********************************************************************************************************************/
int main(void)
{
    t_APP_ContainerResults APP_TestResults;
    t_APP_SingleResult APP_SingleResult;

    int userChoice;
    int iErr = E_OK;

    CON_Init();

    do
    {
        printf("------NUMERICAL INTEGRATION IN C------\n");
        printf("Polynomial Function: 4x^4 + 7x^3 - 4x + 14\n");
        printf("Trigonometric Function: 18 * sin(x)\n");
        printf("Predefined Intervall: [%f, %f]\n\n", CON_Config.a, CON_Config.b);
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
            iErr = APP_CalculateIntegral(CON_Config.pPolynomialFunction, CON_Config.a, CON_Config.b, CON_Config.n, &APP_SingleResult);

            if (iErr != E_OK)
            {
                printf("Error while calculating integral of polynomial function!\n\n");
            }
            else
            {
                printf("Results (N=%d):\n", CON_Config.n);
                printf("Rectangle: %.3f\n", APP_SingleResult.resultRectangle);
                printf("Trapezoid: %.3f\n", APP_SingleResult.resultTrapezoid);
                printf("Simpson:   %.3f\n\n", APP_SingleResult.resultSimpson);
            }
        }
        else if (userChoice == 2)
        {
            iErr = APP_CalculateIntegral(CON_Config.pTrigonometricFunction, CON_Config.a, CON_Config.b, CON_Config.n, &APP_SingleResult);

            if (iErr != E_OK)
            {
                printf("Error while calculating integral of trigonometric function!\n\n");
            }
            else
            {
                printf("Results (N=%d):\n", CON_Config.n);
                printf("Rectangle: %.3f\n", APP_SingleResult.resultRectangle);
                printf("Trapezoid: %.3f\n", APP_SingleResult.resultTrapezoid);
                printf("Simpson:   %.3f\n\n", APP_SingleResult.resultSimpson);
            }
        }
        else if (userChoice == 3)
        {
            iErr = APP_RunTestPolynomial(CON_Config.pPolynomialFunction, CON_Config.a, CON_Config.b, CON_Config.testSteps, &CON_Config.resultPolynomial, &APP_TestResults);

            if (iErr != E_OK)
            {
                printf("Error while running polynomial test!\n\n");
            }
            else
            {
                printf("--- Accuracy Results (Polynomial) ---\n");
                for (int i = 0; i < NUM_TEST_CASES; i++)
                {
                    printf("\nN = %d:\n", CON_Config.testSteps[i]);
                    printf("Rectangle: %.3f%%\n", APP_TestResults.rectangle.accuracy[i]);
                    printf("Trapezoid: %.3f%%\n", APP_TestResults.trapezoid.accuracy[i]);
                    printf("Simpson:   %.3f%%\n\n", APP_TestResults.simpson.accuracy[i]);
                }
            }
        }
        else if (userChoice == 4)
        {
            iErr = APP_RunTestTrigonometric(CON_Config.pTrigonometricFunction, CON_Config.a, CON_Config.b, CON_Config.testSteps, &CON_Config.resultTrigonometric, &APP_TestResults);

            if (iErr != E_OK)
            {
                printf("Error while running trigonometric test!\n\n");
            }
            else
            {
                printf("--- Accuracy Results (Trigonometric) ---\n");
                for (int i = 0; i < NUM_TEST_CASES; i++)
                {
                    printf("\nN = %d:\n", CON_Config.testSteps[i]);
                    printf("Rectangle: %.3f%%\n", APP_TestResults.rectangle.accuracy[i]);
                    printf("Trapezoid: %.3f%%\n", APP_TestResults.trapezoid.accuracy[i]);
                    printf("Simpson:   %.3f%%\n\n", APP_TestResults.simpson.accuracy[i]);
                }
            }
        }
        else if (userChoice == 5)
        {
            iErr = E_EXIT;
        }
        else 
        {
            iErr = E_EXIT; /* If invalid input, terminate program*/
        }

    } while (iErr >= 0);

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