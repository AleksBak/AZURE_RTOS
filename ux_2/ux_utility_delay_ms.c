/**************************************************************************/
/*                                                                        */
/*       Copyright (c) Microsoft Corporation. All rights reserved.        */
/*                                                                        */
/*       This software is licensed under the Microsoft Software License   */
/*       Terms for Microsoft Azure RTOS. Full text of the license can be  */
/*       found in the LICENSE file at https://aka.ms/AzureRTOS_EULA       */
/*       and in the root directory of this software.                      */
/*                                                                        */
/**************************************************************************/

/**************************************************************************/
/**************************************************************************/
/**                                                                       */
/** USBX Component                                                        */
/**                                                                       */
/**   Host Stack                                                          */
/**                                                                       */
/**************************************************************************/
/**************************************************************************/

#define UX_SOURCE_CODE

/* Include necessary system files.  */
#include "ux_api.h"

/**************************************************************************/
/*                                                                        */
/*  FUNCTION                                               RELEASE        */
/*                                                                        */
/*    _ux_utility_delay_ms                                PORTABLE C      */
/*                                                           6.0          */
/*  AUTHOR                                                                */
/*                                                                        */
/*    Chaoqiong Xiao, Microsoft Corporation                               */
/*                                                                        */
/*  DESCRIPTION                                                           */
/*                                                                        */
/*    This function causes the calling thread to sleep for the            */
/*    specified number of milliseconds                                    */
/*                                                                        */
/*  INPUT                                                                 */
/*                                                                        */
/*    ms_wait                               Number of milliseconds to     */
/*                                            wait for                    */
/*                                                                        */
/*  OUTPUT                                                                */
/*                                                                        */
/*    None                                                                */
/*                                                                        */
/*  CALLS                                                                 */
/*                                                                        */
/*    tx_thread_sleep                       ThreadX sleep function        */
/*                                                                        */
/*  CALLED BY                                                             */
/*                                                                        */
/*    USBX Components                                                     */
/*                                                                        */
/*  RELEASE HISTORY                                                       */
/*                                                                        */
/*    DATE              NAME                      DESCRIPTION             */
/*                                                                        */
/*  05-19-2020     Chaoqiong Xiao           Initial Version 6.0           */
/*                                                                        */
/**************************************************************************/
VOID _ux_utility_delay_ms(ULONG ms_wait)
{
	/* translate ms into ticks. */
	ULONG ticks = (ms_wait * UX_PERIODIC_RATE) / 1000;

	/* For safety add 1 to ticks. */
	ticks++;

	/* Call ThreadX sleep function. */
	tx_thread_sleep(ticks);

	/* Return completion status. */
	return;
}
