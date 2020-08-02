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
/**   STM32 Controller Driver                                             */
/**                                                                       */
/**************************************************************************/
/**************************************************************************/

/* Include necessary system files.  */

#define UX_SOURCE_CODE

#include "ux_api.h"
#include "ux_hcd_stm32.h"
#include "ux_host_stack.h"

/**************************************************************************/
/*                                                                        */
/*  FUNCTION                                               RELEASE        */
/*                                                                        */
/*    _ux_hcd_stm32_interrupt_handler                     PORTABLE C      */
/*                                                           6.0          */
/*  AUTHOR                                                                */
/*                                                                        */
/*    Chaoqiong Xiao, Microsoft Corporation                               */
/*                                                                        */
/*  DESCRIPTION                                                           */
/*                                                                        */
/*     This function is the interrupt handler for the STM32 interrupts.   */
/*     Normally an interrupt occurs from the controller when there is     */
/*     either a EOF signal and there has been transfers within the frame  */
/*     or when there is a change on one of the downstream ports.          */
/*                                                                        */
/*     All we need to do in the ISR is scan the controllers to find out   */
/*     which one has issued a IRQ. If there is work to do for this        */
/*     controller we need to wake up the corresponding thread to take     */
/*     care of the job.                                                   */
/*                                                                        */
/*  INPUT                                                                 */
/*                                                                        */
/*    None                                                                */
/*                                                                        */
/*  OUTPUT                                                                */
/*                                                                        */
/*    None                                                                */
/*                                                                        */
/*  CALLS                                                                 */
/*                                                                        */
/*    _ux_hcd_stm32_register_read             Read STM32 HCOR register    */
/*    _ux_hcd_stm32_register_write            Write STM32 HCOR register   */
/*    _ux_utility_semaphore_put               Put producer semaphore      */
/*                                                                        */
/*  CALLED BY                                                             */
/*                                                                        */
/*    ThreadX Interrupt Handler                                           */
/*                                                                        */
/*  RELEASE HISTORY                                                       */
/*                                                                        */
/*    DATE              NAME                      DESCRIPTION             */
/*                                                                        */
/*  05-19-2020     Chaoqiong Xiao           Initial Version 6.0           */
/*                                                                        */
/**************************************************************************/
VOID _ux_hcd_stm32_interrupt_handler(VOID)
{
	UINT hcd_index;
	UX_HCD* hcd;
	UX_HCD_STM32* hcd_stm32;
	ULONG interrupt_pending_register;
	ULONG interrupt_enable_register;
	ULONG port_status;
	ULONG port_status_modify;
	ULONG host_channel_interrupt;
	ULONG host_channel_interrupt_status;
	ULONG channel_index;
	ULONG stm32_grxstp_register;

	/* We need to parse the controller driver table to find all controllers that
	 are registered as STM32.  */
	for (hcd_index = 0; hcd_index < _ux_system_host->ux_system_host_registered_hcd; hcd_index++)
	{
		/* Check type of controller.  */
		if (_ux_system_host->ux_system_host_hcd_array[hcd_index].ux_hcd_controller_type
				== UX_HCD_STM32_CONTROLLER_FS ||
				_ux_system_host->ux_system_host_hcd_array[hcd_index].ux_hcd_controller_type
						== UX_HCD_STM32_CONTROLLER_HS)
		{
			/* Get the pointers to the generic HCD and STM32 specific areas.  */
			hcd = &_ux_system_host->ux_system_host_hcd_array[hcd_index];
			hcd_stm32 = (UX_HCD_STM32*)hcd->ux_hcd_controller_hardware;

			/* Increase the interrupt count. This indicates the controller is still alive.  */
			hcd_stm32->ux_hcd_stm32_interrupt_count++;

			/* Check if the controller is operational, if not, skip it.  */
			if (hcd->ux_hcd_status == UX_HCD_STATUS_OPERATIONAL)
			{
				/* Do a verification if the controller can be interrupted.  */
				if (hcd_stm32->ux_hcd_stm32_interruptible == UX_TRUE)
				{
					hcd->ux_hcd_status = UX_HCD_STATUS_DEAD;
					_ux_utility_semaphore_put(&_ux_system_host->ux_system_host_hcd_semaphore);
				}

				/* Read the interrupt enable and interrupt pending registers.  */
				interrupt_pending_register = _ux_hcd_stm32_register_read(hcd_stm32,
						UX_HCD_STM32_OTG_FS_GINTSTS);
				interrupt_enable_register = _ux_hcd_stm32_register_read(hcd_stm32,
						UX_HCD_STM32_OTG_FS_GINTMSK);

				/* Examine the source of interrupts.  Is it SOF ? */
				if ((interrupt_enable_register & UX_HCD_STM32_OTG_FS_GINTSTS_SOF)
						&& (interrupt_pending_register & UX_HCD_STM32_OTG_FS_GINTMSK_SOFM))
				{
					/* Clear SOF interrupt pending.  */
					_ux_hcd_stm32_register_write(hcd_stm32, UX_HCD_STM32_OTG_FS_GINTSTS,
							UX_HCD_STM32_OTG_FS_GINTSTS_SOF);

					/* We have a SOF signal, we should find out what happened during the last frame and see if
					 there is anything to do in the next frame. */
					if ((hcd_stm32->ux_hcd_stm32_queue_empty == UX_FALSE) ||
							(hcd_stm32->ux_hcd_stm32_periodic_scheduler_active != 0))
					{
						/* Wake up the scheduler but we cannot safely mark the queue empty yet.
						 * This will be done when we find that the scheduling queue is empty.  */

						if ((hcd_stm32->ux_hcd_stm32_controller_flag
								& UX_HCD_STM32_CONTROLLER_FLAG_SOF) == 0)
						{
							hcd_stm32->ux_hcd_stm32_controller_flag |=
									UX_HCD_STM32_CONTROLLER_FLAG_SOF;
							hcd->ux_hcd_thread_signal++;
							_ux_utility_semaphore_put(
									&_ux_system_host->ux_system_host_hcd_semaphore);
						}
					}
				}

				/* Check if we have a Port Change signal.  */
				if ((interrupt_enable_register & UX_HCD_STM32_OTG_FS_GINTSTS_HPRTINT) &&
						(interrupt_pending_register & UX_HCD_STM32_OTG_FS_GINTSTS_HPRTINT))
				{
					/* Clear the pending interrupt. */
					_ux_hcd_stm32_register_write(hcd_stm32, UX_HCD_STM32_OTG_FS_GINTSTS,
							UX_HCD_STM32_OTG_FS_GINTSTS_HPRTINT);

					/* Read the HPRT register to identify the source of the port status change.  */
					port_status = _ux_hcd_stm32_register_read(hcd_stm32, UX_HCD_STM32_OTG_FS_HPRT);

					/* Save the port status for modification bits.  */
					port_status_modify = port_status;

					/* Take out bits to be modified.  */
					port_status_modify &= ~(UX_HCD_STM32_OTG_FS_HPRT_PENA
							| UX_HCD_STM32_OTG_FS_HPRT_PCDET | UX_HCD_STM32_OTG_FS_HPRT_PENCHNG
							| UX_HCD_STM32_OTG_FS_HPRT_POCCHNG);

					/* Check if there is a device insertion.  */
					if (port_status & UX_HCD_STM32_OTG_FS_HPRT_PCDET)
					{
						/* Clear the PCDET field.  */
						port_status_modify |= UX_HCD_STM32_OTG_FS_HPRT_PCDET;
						_ux_hcd_stm32_register_write(hcd_stm32, UX_HCD_STM32_OTG_FS_HPRT,
								port_status_modify);

						/* Check if device is connected or not.  */
						if (port_status & UX_HCD_STM32_OTG_FS_HPRT_PCSTS)
						{
							/* Make sure there was no device attached before.  */
							if ((hcd_stm32->ux_hcd_stm32_controller_flag
									& UX_HCD_STM32_CONTROLLER_FLAG_DEVICE_ATTACHED) == 0)
							{
								/* Something happened on the root hub port. Signal it to the root hub     thread.  */
								hcd->ux_hcd_root_hub_signal[0]++;

								/* We only wake up the root hub thread if there has been device insertion when no
								 device was attached previously.  */
								_ux_utility_semaphore_put(
										&_ux_system_host->ux_system_host_enum_semaphore);

								/* The controller has issued a ATTACH Root HUB signal.  */
								hcd_stm32->ux_hcd_stm32_controller_flag |=
										UX_HCD_STM32_CONTROLLER_FLAG_DEVICE_ATTACHED;
								hcd_stm32->ux_hcd_stm32_controller_flag &=
										~UX_HCD_STM32_CONTROLLER_FLAG_DEVICE_DETACHED;

								/* Clear the DETACH signal that may have happened in conjunction with the port change.  */
								interrupt_pending_register &= ~UX_HCD_STM32_OTG_FS_GINTSTS_DISCINT;
							}
						}
					}

					/* Check if there is a Port Enable Change. If we have a PE change and
					 * there is no device, it is a device extraction. */
					if (port_status & UX_HCD_STM32_OTG_FS_HPRT_PENCHNG)
					{
						/* Clear the PENCHNG field.  */
						port_status_modify |= UX_HCD_STM32_OTG_FS_HPRT_PENCHNG;
						_ux_hcd_stm32_register_write(hcd_stm32, UX_HCD_STM32_OTG_FS_HPRT,
								port_status_modify);
					}

					/* Check if there is a Overcurrent situation.  */
					if (port_status & UX_HCD_STM32_OTG_FS_HPRT_POCCHNG)
					{
						/* Clear the Overcurrent field.  */
						port_status_modify |= UX_HCD_STM32_OTG_FS_HPRT_POCCHNG;
						_ux_hcd_stm32_register_write(hcd_stm32, UX_HCD_STM32_OTG_FS_HPRT,
								port_status_modify);
					}
				}

				/* Check if we have a Disconnect  signal.  */
				if ((interrupt_enable_register & UX_HCD_STM32_OTG_FS_GINTMSK_DISCINTM) &&
						(interrupt_pending_register & UX_HCD_STM32_OTG_FS_GINTSTS_DISCINT))
				{
					/* Clear the pending interrupt. */
					_ux_hcd_stm32_register_write(hcd_stm32, UX_HCD_STM32_OTG_FS_GINTSTS,
							UX_HCD_STM32_OTG_FS_GINTSTS_DISCINT);

					/* Check if device is connected or not.  If the device is no longer present, proceed. */
					if ((port_status & UX_HCD_STM32_OTG_FS_HPRT_PCSTS) == 0)
					{
						/* Make sure there was a device attached before.  */
						if ((hcd_stm32->ux_hcd_stm32_controller_flag
								& UX_HCD_STM32_CONTROLLER_FLAG_DEVICE_ATTACHED) == 1)
						{
							/* Something happened on the root hub port. Signal it to the root hub thread.  */
							hcd->ux_hcd_root_hub_signal[0]++;

							/* We only wake up the root hub thread if there has been device extraction when a
							 device was attached previously.  */
							_ux_utility_semaphore_put(
									&_ux_system_host->ux_system_host_enum_semaphore);

							/* The controller has issued a DETACH Root HUB signal.  */
							hcd_stm32->ux_hcd_stm32_controller_flag |=
									UX_HCD_STM32_CONTROLLER_FLAG_DEVICE_DETACHED;
							hcd_stm32->ux_hcd_stm32_controller_flag &=
									~UX_HCD_STM32_CONTROLLER_FLAG_DEVICE_ATTACHED;
						}
					}
				}

				/* Check the source of the interrupt. Is RX FIFO non Empty interrupt ? Meaning we have a packet on a IN token.
				 Reading the FIFO will trigger a Transfer complete interrupt.  */
				if ((interrupt_enable_register & UX_HCD_STM32_OTG_FS_GINTSTS_RFXLVL)
						&& (interrupt_pending_register & UX_HCD_STM32_OTG_FS_GINTMSK_RFXLVLM))
				{
					/* Mask this interrupt for now.  */
					_ux_hcd_stm32_register_clear(hcd_stm32, UX_HCD_STM32_OTG_FS_GINTMSK,
							UX_HCD_STM32_OTG_FS_GINTMSK_RFXLVLM);

					/* Get the GRXSTSP register. This tells us on what endpoint the INT happened.  We use the READ register here, not the POP ! */
					stm32_grxstp_register = _ux_hcd_stm32_register_read(hcd_stm32,
							UX_HCD_STM32_OTG_FS_GRXSTSR);

					/* Calculate the endpoint index.  */
					channel_index = stm32_grxstp_register & UX_HCD_STM32_OTG_FS_GRXSTSP_EPNUM_MASK;

					/* Process the call inside the ISR.  */
					_ux_hcd_stm32_asynch_queue_process(hcd_stm32, channel_index,
							UX_HCD_STM32_OTG_FS_HCINT_RXFLVL);

					/* Reenable this interrupt.  */
					_ux_hcd_stm32_register_set(hcd_stm32, UX_HCD_STM32_OTG_FS_GINTMSK,
							UX_HCD_STM32_OTG_FS_GINTMSK_RFXLVLM);
				}

				/* Check if we have a pending interrupt on one of the channels.  */
				if ((interrupt_enable_register & UX_HCD_STM32_OTG_FS_GINTMSK_HCIM)
						&& (interrupt_pending_register & UX_HCD_STM32_OTG_FS_GINTSTS_HCINT))
				{
					/* Read the Host Channel Interrupt register.
					 Save it in the stm32 structure. It needs to be cleared here to prevent interrupts from firing again.
					 Clearing is done when the application sets the interrupt bits in the Host Channel x interrupt registers.  */
					host_channel_interrupt = _ux_hcd_stm32_register_read(hcd_stm32,
							UX_HCD_STM32_OTG_FS_HAINT);

					/* Parse all the interrupts in the register to find which ones woke us up.  */
					for (channel_index = 0; channel_index < hcd_stm32->ux_hcd_stm32_nb_channels;
							channel_index++)
					{
						/* Check the current channel interrupt.  */
						if (host_channel_interrupt & (1 << channel_index))
						{
							/* This channel is busy.  Read its corresponding HCINT register.  */
							host_channel_interrupt_status = _ux_hcd_stm32_register_read(hcd_stm32,
									UX_HCD_STM32_OTG_FS_HCINT +
									(channel_index * UX_HCD_STM32_ENDPOINT_CHANNEL_SIZE));

							/* Now we can reset the host channel bits, this will clear
							 * the interrupt in HAINT.  */
							_ux_hcd_stm32_register_write(hcd_stm32, UX_HCD_STM32_OTG_FS_HCINT +
									(channel_index * UX_HCD_STM32_ENDPOINT_CHANNEL_SIZE),
									host_channel_interrupt_status);

							/* Process the completion of the transaction inside the ISR.  */
							_ux_hcd_stm32_asynch_queue_process(hcd_stm32, channel_index,
									host_channel_interrupt_status);
						}
					}
				}
			}
		}
	}
}
