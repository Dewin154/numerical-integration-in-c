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

Component   Application (APP)

Filename    APP_Application.h

brief       Header file for the application module. Defines result structures and interfaces.

author      Peter Okruhlica

***********************************************************************************************************************
* Changes                                                                                                             *
***********************************************************************************************************************

Version   Date        Sign  Description
--------  ----------  ----  -----------
01.00.00  2025-12-31  PO    Initial check in, prototype TST module and architecture change
01.00.01  2026-01-02  PO    Heavy refactoring of error handling and structure usage
01.01.00  2026-01-03  PO    Moved constants to CON Module to improve reusability

**********************************************************************************************************************/

#ifndef _APP_APPLICATION_H_ /* Include Guard */
#define _APP_APPLICATION_H_

/**********************************************************************************************************************
TYPEDEFS
**********************************************************************************************************************/

typedef struct {
    float results[3];
    float accuracy[3];
} t_APP_RectangleResults;

typedef struct {
    float results[3];
    float accuracy[3];
} t_APP_TrapezoidResults;

typedef struct {
    float results[3];
    float accuracy[3];
} t_APP_SimpsonResults;

typedef struct {
    t_APP_RectangleResults rectangle;
    t_APP_TrapezoidResults trapezoid;
    t_APP_SimpsonResults simpson;
} t_APP_ContainerResults;

typedef struct {
    float resultRectangle;
    float resultTrapezoid;
    float resultSimpson;
} t_APP_SingleResult;

/**********************************************************************************************************************
EXTERNAL FUNCTIONS
**********************************************************************************************************************/

extern int APP_RunTestPolynomial(const float (*function)(float x), float a, float b, const unsigned short* const arrayOfN, const float* const resultPolynomial, t_APP_ContainerResults* pDest);

extern int APP_RunTestTrigonometric(const float (*function)(float x), float a, float b, const unsigned short* const arrayOfN, const float* const resultTrigonometric, t_APP_ContainerResults* pDest);

extern int APP_CalculateIntegral(const float (*function)(float x), float a, float b, unsigned short n, t_APP_SingleResult* pResult);

extern int APP_GetVersion(unsigned char* major, unsigned char* minor, unsigned char* patch);

#endif /* _APP_APPLICATION_H_ */

/**********************************************************************************************************************
EOF
**********************************************************************************************************************/