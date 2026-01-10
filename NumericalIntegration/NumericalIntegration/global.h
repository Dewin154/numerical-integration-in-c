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

Component   Global

Filename    global.h

brief       Header file for global things

author      Peter Okruhlica

***********************************************************************************************************************
* Changes                                                                                                             *
***********************************************************************************************************************

Version   Date        Sign  Description
--------  ----------  ----  -----------
01.00.00  2025-12-26  PO    Initial check in
01.00.01  2026-01-04  PO    Add NUM_TEST_CASES

**********************************************************************************************************************/

#ifndef _GLOBAL_H_ /* Include Guard */
#define _GLOBAL_H_

#define E_OK					(0)
#define E_NOT_OK				(-1)
#define E_INVALID_N				(-2)
#define E_INVALID_INTERVAL		(-3)
#define E_TOO_MANY_ITERATIONS	(-4)
#define E_FUNCTION_NULL_POINTER	(-5)
#define E_VARIABLE_NULL_POINTER (-6)
#define E_STRUCT_NULL_POINTER	(-7)
#define E_EXIT					(-10)

#define NUM_TEST_CASES			(3)

#endif /* _GLOBAL_H_ */

/**********************************************************************************************************************
EOF
**********************************************************************************************************************/
