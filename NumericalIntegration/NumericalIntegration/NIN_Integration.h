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

Filename    NIN_Integration.h

brief       Header file for the numerical integration module

author      Peter Okruhlica

***********************************************************************************************************************
* Changes                                                                                                             *
***********************************************************************************************************************

Version   Date        Sign  Description
--------  ----------  ----  -----------
01.00.00  2025-12-19  PO    Initial check in
01.00.01  2025-12-24  PO    Extending the file
01.00.02  2025-12-28  PO    Extending the file

**********************************************************************************************************************/

#ifndef _NIN_INTEGRATION_H_ /* Include Guard */
#define _NIN_INTEGRATION_H_

/**********************************************************************************************************************
INCLUDES
**********************************************************************************************************************/

#include "global.h"

/**********************************************************************************************************************
EXTERNAL FUNCTIONS
**********************************************************************************************************************/

extern int NIN_Rectangle(const float (*function)(float x), float a, float b, unsigned short n, float* const pResult);

extern int NIN_Trapezoid(const float (*function)(float x), float a, float b, unsigned short n, float* const pResult);

extern int NIN_Simpson(const float (*function)(float x), float a, float b, unsigned short n, float* const pResult);

extern int NIN_GetVersion(unsigned char* major, unsigned char* minor, unsigned char* patch);

#endif /* _NIN_INTEGRATION_H_ */

/**********************************************************************************************************************
EOF
**********************************************************************************************************************/