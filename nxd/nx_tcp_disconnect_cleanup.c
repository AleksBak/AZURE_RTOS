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
/** NetX Component                                                        */
/**                                                                       */
/**   Transmission Control Protocol (TCP)                                 */
/**                                                                       */
/**************************************************************************/
/**************************************************************************/

#define NX_SOURCE_CODE


/* Include necessary system files.  */

#include "nx_api.h"
#include "tx_thread.h"
#include "tx_timer.h"
#include "nx_ip.h"
#include "nx_tcp.h"


/**************************************************************************/
/*                                                                        */
/*  FUNCTION                                               RELEASE        */
/*                                                                        */
/*    _nx_tcp_disconnect_cleanup                          PORTABLE C      */
/*                                                           6.0          */
/*  AUTHOR                                                                */
/*                                                                        */
/*    Yuxin Zhou, Microsoft Corporation                                   */
/*                                                                        */
/*  DESCRIPTION                                                           */
/*                                                                        */
/*    This function processes TCP disconnect timeout and thread terminate */
/*    actions that require the TCP socket data structures to be cleaned   */
/*    up.                                                                 */
/*                                                                        */
/*  INPUT                                                                 */
/*                                                                        */
/*    thread_ptr                            Pointer to suspended thread's */
/*                                            control block               */
/*                                                                        */
/*  OUTPUT                                                                */
/*                                                                        */
/*    None                                                                */
/*                                                                        */
/*  CALLS                                                                 */
/*                                                                        */
/*    tx_event_flags_set                    Set event flag                */
/*    _tx_thread_system_resume              Resume thread service         */
/*                                                                        */
/*  CALLED BY                                                             */
/*                                                                        */
/*    _nx_tcp_deferred_cleanup_check        Deferred cleanup processing   */
/*    _nx_tcp_socket_connection_reset       Connection reset processing   */
/*    _nx_tcp_socket_disconnect             Socket disconnect             */
/*    _tx_thread_timeout                    Thread timeout processing     */
/*    _tx_thread_terminate                  Thread terminate processing   */
/*                                                                        */
/*  RELEASE HISTORY                                                       */
/*                                                                        */
/*    DATE              NAME                      DESCRIPTION             */
/*                                                                        */
/*  05-19-2020     Yuxin Zhou               Initial Version 6.0           */
/*                                                                        */
/**************************************************************************/
VOID  _nx_tcp_disconnect_cleanup(TX_THREAD *thread_ptr NX_CLEANUP_PARAMETER)
{

TX_INTERRUPT_SAVE_AREA

NX_IP         *ip_ptr;
NX_TCP_SOCKET *socket_ptr;  /* Working socket pointer  */

    NX_CLEANUP_EXTENSION

    /* Disable interrupts.  */
    TX_DISABLE

    /* Setup pointer to TCP socket control block.  */
    socket_ptr =  (NX_TCP_SOCKET *)thread_ptr -> tx_thread_suspend_control_block;

    /* Determine if the socket pointer is valid.  */
    if ((!socket_ptr) || (socket_ptr -> nx_tcp_socket_id != NX_TCP_ID))
    {

        /* Restore interrupts.  */
        TX_RESTORE

        return;
    }

    /* Determine if the cleanup is still required.  */
    if (!(thread_ptr -> tx_thread_suspend_cleanup))
    {

        /* Restore interrupts.  */
        TX_RESTORE

        return;
    }

    /* Determine if the caller is an ISR or the system timer thread.  */
#ifndef TX_TIMER_PROCESS_IN_ISR
    if ((TX_THREAD_GET_SYSTEM_STATE()) || (_tx_thread_current_ptr == &_tx_timer_thread))
#else
    if (TX_THREAD_GET_SYSTEM_STATE())
#endif
    {

        /* Yes, defer the processing to the NetX IP thread.  */

        /* Yes, change the suspend cleanup routine to indicate the cleanup is deferred.  */
        thread_ptr -> tx_thread_suspend_cleanup =  _nx_tcp_cleanup_deferred;

        /* Pickup the IP pointer.  */
        ip_ptr =  socket_ptr -> nx_tcp_socket_ip_ptr;

        /* Restore interrupts.  */
        TX_RESTORE

        /* Set the deferred cleanup flag for the IP thread.  */
        tx_event_flags_set(&(ip_ptr -> nx_ip_events), NX_IP_TCP_CLEANUP_DEFERRED, TX_OR);

        /* Return to caller.  */
        return;
    }
    else
    {

        /* Yes, we still have thread suspension!  */

        /* Clear the suspension cleanup flag.  */
        thread_ptr -> tx_thread_suspend_cleanup =  TX_NULL;

        /* Clear the suspension pointer.   */
        socket_ptr -> nx_tcp_socket_disconnect_suspended_thread =  NX_NULL;

        /* Now we need to determine if this cleanup is from a terminate, timeout,
           or from a wait abort.  */
        if (thread_ptr -> tx_thread_state == TX_TCP_IP)
        {

            /* Thread still suspended on the TCP socket.  Setup return error status and
               resume the thread.  */

            /* Setup return status.  */
            thread_ptr -> tx_thread_suspend_status =  NX_DISCONNECT_FAILED;

            /* Temporarily disable preemption.  */
            _tx_thread_preempt_disable++;

            /* Restore interrupts.  */
            TX_RESTORE

            /* Resume the thread!  Check for preemption even though we are executing
               from the system timer thread right now which normally executes at the
               highest priority.  */
            _tx_thread_system_resume(thread_ptr);

            /* Finished, just return.  */
            return;
        }
    }

    /* Restore interrupts.  */
    TX_RESTORE
}

