/**********************************************************************************************************************
* Filename:    main.c
* Description: Application to test the NIN_Integration module
**********************************************************************************************************************/

#include <windows.h>
#include <stdio.h>
#include <conio.h>
#include <stdlib.h>
#include <math.h>    /* Wichtig fuer sin() */

#include "global.h"
#include "NIN_Integration.h"

/* --- Mathematische Test-Funktionen --- */

/* Polynom: 4x^4 + 7x^3 - 4x + 14 */
float FunctionPolynomial(float x)
{
    return (float)((4 * pow(x, 4)) + (7 * pow(x, 3)) - (4 * x) + 14);
}

/* Trigonometrie: 18 * sin(x) */
float FunctionTrig(float x)
{
    return (float)(18 * sin(x));
}

/* Einfache Parabel fuer Unit Test: x^2 */
float FunctionSquare(float x)
{
    return (float)(x * x);
}

/* --- Main Program --- */

void main(void)
{
    /* Variablen */
    float (*pFunc)(float x) = &FunctionPolynomial; /* Standardmaessig Polynom */
    float result = 0.0f;
    int userChoice = 0;
    int iErr = E_OK;

    unsigned char ucMaj, ucMin, ucPatch;

    /* 1. Modul Initialisieren (WICHTIG wegen statischer Struktur!) */
    NIN_Init();

    /* Version anzeigen */
    NIN_GetVersion(&ucMaj, &ucMin, &ucPatch);
    printf("NIN Module Version: %02d.%02d.%02d\n", ucMaj, ucMin, ucPatch);
    printf("----------------------------------------\n");

    /* Menü */
    printf("Select Action:\n");
    printf("1. Calculate Integral (Polynomial, 5 to 12, n=50)\n");
    printf("2. Run Unit Test (x^2 check)\n");
    printf("3. Terminate program\n");
    printf("Choice: ");

    /* scanf_s ist sicherer fuer Visual Studio */
    scanf_s("%d", &userChoice);
    printf("\n");

    if (userChoice == 1)
    {
        printf("--- Calculating Polynomial ---\n");

        /* A) Rectangle */
        iErr = NIN_Rectangle(pFunc, 5.0f, 12.0f, 50, &result);
        if (iErr == E_OK)
        {
            printf("Rectangle Result: %f\n", result);
        }
        else
        {
            printf("Rectangle Error: %d\n", iErr);
        }

        /* B) Trapezoid */
        iErr = NIN_Trapezoid(pFunc, 5.0f, 12.0f, 50, &result);
        if (iErr == E_OK)
        {
            printf("Trapezoid Result: %f\n", result);
        }
        else
        {
            printf("Trapezoid Error: %d\n", iErr);
        }

        /* C) Simpson */
        iErr = NIN_Simpson(pFunc, 5.0f, 12.0f, 50, &result);
        if (iErr == E_OK)
        {
            printf("Simpson   Result: %f\n", result);
        }
        else
        {
            printf("Simpson   Error: %d\n", iErr);
        }
    }
    else if (userChoice == 2)
    {
        /* Automatischer Test mit bekanntem Ergebnis */
        printf("--- Running Unit Test (x^2, [0,10]) ---\n");
        printf("Expected: ~333.3333\n");

        /* Hier nutzen wir die FunctionSquare */
        NIN_Simpson(FunctionSquare, 0.0f, 10.0f, 100, &result);
        printf("Simpson Result: %f\n", result);

        if (result > 333.3f && result < 333.4f)
        {
            printf("-> TEST PASSED\n");
        }
        else
        {
            printf("-> TEST FAILED\n");
        }
    }
    else
    {
        printf("Exiting...\n");
    }

    printf("\nPress any key to exit...\n");

    /* Loop aus der PDF Vorgabe, damit Konsole offen bleibt */
    while (!_kbhit())
    {
        Sleep(1);
    }
}