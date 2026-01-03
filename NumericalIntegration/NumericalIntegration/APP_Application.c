#include "APP_Application.h"
#include "NIN_Integration.h"


int APP_calculateIntegral(const float (*function)(float x), float a, float b, unsigned short n, t_APP_SingleResult* pResult)
{
    int iErr = E_OK;

    /*Fehlerbehandlung!*/
    int iErrRect = NIN_Rectangle(function, a, b, n, &pResult->resultRectangle);
    int iErrTrap = NIN_Trapezoid(function, a, b, n, &pResult->resultTrapezoid);
    int iErrSimp = NIN_Simpson(function, a, b, n, &pResult->resultSimpson);

    return iErr;
    
}

int APP_runTestPolynomial(const float (*function)(float x), float a, float b, const unsigned short arrayOfN[], const float *resultPolynomial, t_APP_ContainerResults* pDest)
{
    NIN_Init();

    int iErr = E_OK;

    t_APP_SingleResult tempResult;

    for (int i = 0; i < 3; i++)
    {
        iErr = APP_calculateIntegral(function, a, b, arrayOfN[i], &tempResult);

        if (iErr != E_OK)
        {
            iErr = E_NOT_OK;
            break;
        }
        else 
        {
            pDest->rectangle.results[i] = tempResult.resultRectangle;
            pDest->trapezoid.results[i] = tempResult.resultTrapezoid;
            pDest->simpson.results[i] = tempResult.resultSimpson;

            /*Absichern! Division durch 0!!!*/
            pDest->rectangle.accuracy[i] = (pDest->rectangle.results[i] / *resultPolynomial) * 100.0F;
            pDest->trapezoid.accuracy[i] = (pDest->trapezoid.results[i] / *resultPolynomial) * 100.0F;
            pDest->simpson.accuracy[i] = (pDest->simpson.results[i] / *resultPolynomial) * 100.0F;
        }
    }
    return iErr;
}

int APP_runTestTrigonometric(const float (*function)(float x), float a, float b, const unsigned short arrayOfN[], const float* resultTrigonometric, t_APP_ContainerResults* pDest)
{
    NIN_Init();

    int iErr = E_OK;

    t_APP_SingleResult tempResult;

    for (int i = 0; i < 3; i++)
    {
        iErr = APP_calculateIntegral(function, a, b, arrayOfN[i], &tempResult);

        if (iErr != E_OK)
        {
            iErr = E_NOT_OK;
            break;
        }
        else
        {
            pDest->rectangle.results[i] = tempResult.resultRectangle;
            pDest->trapezoid.results[i] = tempResult.resultTrapezoid;
            pDest->simpson.results[i] = tempResult.resultSimpson;

            /*Absichern! Division durch 0!!!*/
            pDest->rectangle.accuracy[i] = (pDest->rectangle.results[i] / *resultTrigonometric) * 100.0F;
            pDest->trapezoid.accuracy[i] = (pDest->trapezoid.results[i] / *resultTrigonometric) * 100.0F;
            pDest->simpson.accuracy[i] = (pDest->simpson.results[i] / *resultTrigonometric) * 100.0F;
        }
    }
    return iErr;
}

