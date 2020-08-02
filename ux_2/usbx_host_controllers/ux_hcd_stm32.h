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


/**************************************************************************/ 
/*                                                                        */ 
/*  COMPONENT DEFINITION                                   RELEASE        */ 
/*                                                                        */ 
/*    ux_hcd_stm32.h                                      PORTABLE C      */ 
/*                                                           6.0          */
/*  AUTHOR                                                                */
/*                                                                        */
/*    Chaoqiong Xiao, Microsoft Corporation                               */
/*                                                                        */
/*  DESCRIPTION                                                           */
/*                                                                        */ 
/*    This file contains all the header and extern functions used by the  */
/*    USBX host the ATMEL STM32 Controller.                               */ 
/*                                                                        */ 
/*  RELEASE HISTORY                                                       */ 
/*                                                                        */ 
/*    DATE              NAME                      DESCRIPTION             */ 
/*                                                                        */ 
/*  05-19-2020     Chaoqiong Xiao           Initial Version 6.0           */
/*                                                                        */
/**************************************************************************/

#ifndef UX_HCD_STM32_H
#define UX_HCD_STM32_H

/* Define STM32 generic definitions.  */
#define UX_HCD_STM32_FS_MAX_PAYLOAD                             64
#define UX_HCD_STM32_FS_MAX_PACKET_COUNT                        64
#define UX_HCD_STM32_FS_MAX_PACKET_LIMIT                        256
#define UX_HCD_STM32_FS_NB_CHANNELS                             8
#define UX_HCD_STM32_FS_RX_FIFO_SIZE                            (256 / 4)
#define UX_HCD_STM32_FS_PTX_FIFO_SIZE                           (128 / 4)
#define UX_HCD_STM32_FS_NPTX_FIFO_SIZE                          (128 / 4)

#define UX_HCD_STM32_HS_MAX_PAYLOAD                             512
#define UX_HCD_STM32_HS_MAX_PACKET_COUNT                        512
#define UX_HCD_STM32_HS_MAX_PACKET_LIMIT                        1280
#define UX_HCD_STM32_HS_NB_CHANNELS                             12
#define UX_HCD_STM32_HS_RX_FIFO_SIZE                            (1024 / 4)
#define UX_HCD_STM32_HS_PTX_FIFO_SIZE                           (1024 / 4)
#define UX_HCD_STM32_HS_NPTX_FIFO_SIZE                          (1024 / 4)

#define UX_HCD_STM32_CONTROLLER_FS                              6
#define UX_HCD_STM32_CONTROLLER_HS                              7
#define UX_HCD_STM32_MAX_NB_CHANNELS                            12
#define UX_HCD_STM32_FRAME_DELAY                                4 
#define UX_HCD_STM32_COMMAND_RETRY                              3     
#define UX_HCD_STM32_PERIODIC_ENTRY_NB                          32    
#define UX_HCD_STM32_PERIODIC_ENTRY_MASK                        0x1f
#define UX_HCD_STM32_NB_ROOT_PORTS                              1
#define UX_HCD_STM32_PORT_ENABLE_TIMEOUT                        5
#define UX_HCD_STM32_NO_CHANNEL_ASSIGNED                        0xffffffff
#define UX_HCD_STM32_CONTROLLER_FLAG_DEVICE_ATTACHED            0x01
#define UX_HCD_STM32_CONTROLLER_FLAG_DEVICE_DETACHED            0x02
#define UX_HCD_STM32_CONTROLLER_FLAG_SOF                        0x04
#define UX_HCD_STM32_CONTROLLER_FLAG_TRANSFER_DONE              0x08
#define UX_HCD_STM32_CONTROLLER_FLAG_TRANSFER_ERROR             0x10
#define UX_HCD_STM32_CONTROLLER_LOW_SPEED_DEVICE                0x20
#define UX_HCD_STM32_CONTROLLER_FULL_SPEED_DEVICE               0x40
#define UX_HCD_STM32_CONTROLLER_HIGH_SPEED_DEVICE               0x80

#define UX_HCD_STM32_CONTROLLER_DELAY                           72

#define UX_HCD_STM32_FLUSH_RX_FIFO                              0x00000010
#define UX_HCD_STM32_FLUSH_TX_FIFO                              0x00000020
#define UX_HCD_STM32_FLUSH_FIFO_ALL                             0x00000010
#define UX_HCD_STM32_ENDPOINT_CHANNEL_SIZE                      0x00000020
#define UX_HCD_STM32_FIFO_CHANNEL_SIZE                          0x00001000
//#define UX_HCD_STM32_ASYNCH_NAK_COUNTER                       16
#define UX_HCD_STM32_ASYNCH_NAK_COUNTER                         1

/* Define STM32 USB host controller CSR registers equivalences.  */
                                                                                                                                                    
#define UX_HCD_STM32_OTG_FS_GOTGCTL                             0x00000000
#define UX_HCD_STM32_OTG_FS_GOTGINT                             0x00000004
#define UX_HCD_STM32_OTG_FS_GAHBCFG                             0x00000008
#define UX_HCD_STM32_OTG_FS_GUSBCFG                             0x0000000C
#define UX_HCD_STM32_OTG_FS_GRSTCTL                             0x00000010
#define UX_HCD_STM32_OTG_FS_GINTSTS                             0x00000014
#define UX_HCD_STM32_OTG_FS_GINTMSK                             0x00000018
#define UX_HCD_STM32_OTG_FS_GRXSTSR                             0x0000001C
#define UX_HCD_STM32_OTG_FS_GRXSTSP                             0x00000020
#define UX_HCD_STM32_OTG_FS_GRXFSIZ                             0x00000024
#define UX_HCD_STM32_OTG_FS_GNPTXFSIZ                           0x00000028
#define UX_HCD_STM32_OTG_FS_GNPTXSTS                            0x0000002C
#define UX_HCD_STM32_OTG_FS_GCCFG                               0x00000038
#define UX_HCD_STM32_OTG_FS_CID                                 0x0000003C
#define UX_HCD_STM32_OTG_FS_HPTXFSIZ                            0x00000100
#define UX_HCD_STM32_OTG_FS_DIEPTXF                             0x00000104
#define UX_HCD_STM32_OTG_FS_HCFG                                0x00000400
#define UX_HCD_STM32_OTG_FS_HFIR                                0x00000404
#define UX_HCD_STM32_OTG_FS_HFNUM                               0x00000408
#define UX_HCD_STM32_OTG_FS_HPTXSTS                             0x00000410
#define UX_HCD_STM32_OTG_FS_HAINT                               0x00000414
#define UX_HCD_STM32_OTG_FS_HAINTMSK                            0x00000418
#define UX_HCD_STM32_OTG_FS_HPRT                                0x00000440
#define UX_HCD_STM32_OTG_FS_HCCHAR                              0x00000500
#define UX_HCD_STM32_OTG_FS_HCINT                               0x00000508
#define UX_HCD_STM32_OTG_FS_HCINTMSK                            0x0000050C
#define UX_HCD_STM32_OTG_FS_HCTSIZ                              0x00000510
#define UX_HCD_STM32_OTG_FS_PCGCCTL                             0x00000E00
#define UX_HCD_STM32_OTG_FS_FIFO                                0x00001000

/* Define STM32 USB host controller GOTGCTL registers equivalences.  */
                                                                                                                                                    
#define UX_HCD_STM32_OTG_FS_GOTGCTL_SRQSCS                      0x00000001
#define UX_HCD_STM32_OTG_FS_GOTGCTL_SRQ                         0x00000002
#define UX_HCD_STM32_OTG_FS_GOTGCTL_HNGSCS                      0x00000100
#define UX_HCD_STM32_OTG_FS_GOTGCTL_HNPRQ                       0x00000200
#define UX_HCD_STM32_OTG_FS_GOTGCTL_HSHNPEN                     0x00000400
#define UX_HCD_STM32_OTG_FS_GOTGCTL_DHNPEN                      0x00000800
#define UX_HCD_STM32_OTG_FS_GOTGCTL_CIDSTS                      0x00010000
#define UX_HCD_STM32_OTG_FS_GOTGCTL_DBCT                        0x00020000
#define UX_HCD_STM32_OTG_FS_GOTGCTL_ASVLD                       0x00040000
#define UX_HCD_STM32_OTG_FS_GOTGCTL_BSVLD                       0x00080000

/* Define STM32 USB host controller GOTGINT register.  */
#define UX_HCD_STM32_OTG_FS_GOTGINT_SEDET                       0x00000002
#define UX_HCD_STM32_OTG_FS_GOTGINT_SRSSCHG                     0x00000100
#define UX_HCD_STM32_OTG_FS_GOTGINT_HNSSCHG                     0x00000200
#define UX_HCD_STM32_OTG_FS_GOTGINT_HNGDET                      0x00020000
#define UX_HCD_STM32_OTG_FS_GOTGINT_ADTOCHG                     0x00040000
#define UX_HCD_STM32_OTG_FS_GOTGINT_DBCDNE                      0x00080000
                                                                                                                                                   
/* Define STM32 USB host controller GAHBCFG register.  */
#define UX_HCD_STM32_OTG_FS_GAHBCFG_GINT                        0x00000001
#define UX_HCD_STM32_OTG_FS_GAHBCFG_TXFEVL                      0x00000100
#define UX_HCD_STM32_OTG_FS_GAHBCFG_PTXFEVL                     0x00000200

/* Define STM32 USB host controller GUSBCFG register.  */
#define UX_HCD_STM32_OTG_FS_GUSBCFG_TOCAL_MASK                  0x00000007
#define UX_HCD_STM32_OTG_FS_GUSBCFG_PHYIF                       0x00000008
#define UX_HCD_STM32_OTG_FS_GUSBCFG_ULPI_UTMI_SEL               0x00000010
#define UX_HCD_STM32_OTG_FS_GUSBCFG_FSINTF                      0x00000020
#define UX_HCD_STM32_OTG_FS_GUSBCFG_PHYSEL                      0x00000040
#define UX_HCD_STM32_OTG_FS_GUSBCFG_DDRSEL                      0x00000080
#define UX_HCD_STM32_OTG_FS_GUSBCFG_SRPCAP                      0x00000100
#define UX_HCD_STM32_OTG_FS_GUSBCFG_HNPCAP                      0x00000200
#define UX_HCD_STM32_OTG_FS_GUSBCFG_TRDT_16                     0x00001400
#define UX_HCD_STM32_OTG_FS_GUSBCFG_TRDT_8                      0x00002400
#define UX_HCD_STM32_OTG_FS_GUSBCFG_NPTXRWEN                    0x00004000
#define UX_HCD_STM32_OTG_FS_GUSBCFG_ULPIFSLS                    0x00020000
#define UX_HCD_STM32_OTG_FS_GUSBCFG_ULPIAR                      0x00040000
#define UX_HCD_STM32_OTG_FS_GUSBCFG_ULPICSM                     0x00080000
#define UX_HCD_STM32_OTG_FS_GUSBCFG_ULPIEVBUSD                  0x00100000
#define UX_HCD_STM32_OTG_FS_GUSBCFG_ULPIEVBUSI                  0x00200000
#define UX_HCD_STM32_OTG_FS_GUSBCFG_TSDPS                       0x00400000
#define UX_HCD_STM32_OTG_FS_GUSBCFG_PCCI                        0x00800000
#define UX_HCD_STM32_OTG_FS_GUSBCFG_PTCI                        0x01000000
#define UX_HCD_STM32_OTG_FS_GUSBCFG_ULPIIPD                     0x02000000
#define UX_HCD_STM32_OTG_FS_GUSBCFG_FHMOD                       0x20000000
#define UX_HCD_STM32_OTG_FS_GUSBCFG_FDMOD                       0x40000000
#define UX_HCD_STM32_OTG_FS_GUSBCFG_CTXPKT                      0x80000000

/* Define STM32 USB host controller GRSTCTL register.  */
#define UX_HCD_STM32_OTG_FS_GRSTCTL_CSRST                       0x00000001
#define UX_HCD_STM32_OTG_FS_GRSTCTL_HSRST                       0x00000002
#define UX_HCD_STM32_OTG_FS_GRSTCTL_FCRST                       0x00000004
#define UX_HCD_STM32_OTG_FS_GRSTCTL_RXFFLSH                     0x00000010
#define UX_HCD_STM32_OTG_FS_GRSTCTL_TXFFLSH                     0x00000020
#define UX_HCD_STM32_OTG_FS_GRSTCTL_TXFNUM_MASK                 0x000007C0
#define UX_HCD_STM32_OTG_FS_GRSTCTL_TXFNUM_SHIFT                0x00000006
#define UX_HCD_STM32_OTG_FS_GRSTCTL_TXFNUM_ALL                  0x00000200
#define UX_HCD_STM32_OTG_FS_GRSTCTL_AHBIDL                      0x80000000

/* Define STM32 USB host controller GINTSTS register.  */
#define UX_HCD_STM32_OTG_FS_GINTSTS_CMOD                        0x00000001
#define UX_HCD_STM32_OTG_FS_GINTSTS_MMIS                        0x00000002
#define UX_HCD_STM32_OTG_FS_GINTSTS_OTGINT                      0x00000004
#define UX_HCD_STM32_OTG_FS_GINTSTS_SOF                         0x00000008
#define UX_HCD_STM32_OTG_FS_GINTSTS_RFXLVL                      0x00000010
#define UX_HCD_STM32_OTG_FS_GINTSTS_NPTXFE                      0x00000020
#define UX_HCD_STM32_OTG_FS_GINTSTS_GINAKEFF                    0x00000040
#define UX_HCD_STM32_OTG_FS_GINTSTS_BOUNTNAKEFF                 0x00000080
#define UX_HCD_STM32_OTG_FS_GINTSTS_ESUSP                       0x00000400
#define UX_HCD_STM32_OTG_FS_GINTSTS_USBSUSP                     0x00000800
#define UX_HCD_STM32_OTG_FS_GINTSTS_USBRST                      0x00001000
#define UX_HCD_STM32_OTG_FS_GINTSTS_ENUMDNE                     0x00002000
#define UX_HCD_STM32_OTG_FS_GINTSTS_ISOODRP                     0x00004000
#define UX_HCD_STM32_OTG_FS_GINTSTS_EOPF                        0x00008000
#define UX_HCD_STM32_OTG_FS_GINTSTS_IEPINT                      0x00040000
#define UX_HCD_STM32_OTG_FS_GINTSTS_OEPINT                      0x00080000
#define UX_HCD_STM32_OTG_FS_GINTSTS_IISOIXFR                    0x00100000
#define UX_HCD_STM32_OTG_FS_GINTSTS_IPXFR                       0x00200000
#define UX_HCD_STM32_OTG_FS_GINTSTS_INCOMPISOOUT                0x00200000
#define UX_HCD_STM32_OTG_FS_GINTSTS_HPRTINT                     0x01000000
#define UX_HCD_STM32_OTG_FS_GINTSTS_HCINT                       0x02000000
#define UX_HCD_STM32_OTG_FS_GINTSTS_PTXFE                       0x04000000
#define UX_HCD_STM32_OTG_FS_GINTSTS_CIDSCHG                     0x10000000
#define UX_HCD_STM32_OTG_FS_GINTSTS_DISCINT                     0x20000000
#define UX_HCD_STM32_OTG_FS_GINTSTS_SRQINT                      0x40000000
#define UX_HCD_STM32_OTG_FS_GINTSTS_WKUINT                      0x80000000

/* Define STM32 USB host controller GINTMSK register.  */
#define UX_HCD_STM32_OTG_FS_GINTMSK_MMISM                       0x00000002
#define UX_HCD_STM32_OTG_FS_GINTMSK_OTGINT                      0x00000004
#define UX_HCD_STM32_OTG_FS_GINTMSK_SOFM                        0x00000008
#define UX_HCD_STM32_OTG_FS_GINTMSK_RFXLVLM                     0x00000010
#define UX_HCD_STM32_OTG_FS_GINTMSK_NPTXFEM                     0x00000020
#define UX_HCD_STM32_OTG_FS_GINTMSK_GINAKEFFM                   0x00000040
#define UX_HCD_STM32_OTG_FS_GINTMSK_GONAKEFFM                   0x00000080
#define UX_HCD_STM32_OTG_FS_GINTMSK_ESUSPM                      0x00000400
#define UX_HCD_STM32_OTG_FS_GINTMSK_USBSUSPM                    0x00000800
#define UX_HCD_STM32_OTG_FS_GINTMSK_USBRSTM                     0x00001000
#define UX_HCD_STM32_OTG_FS_GINTMSK_ENUMDNEM                    0x00002000
#define UX_HCD_STM32_OTG_FS_GINTMSK_ISOODRPM                    0x00004000
#define UX_HCD_STM32_OTG_FS_GINTMSK_EOPFM                       0x00008000
#define UX_HCD_STM32_OTG_FS_GINTMSK_IEPINT                      0x00040000
#define UX_HCD_STM32_OTG_FS_GINTMSK_OEPINT                      0x00080000
#define UX_HCD_STM32_OTG_FS_GINTMSK_IISOIXFRM                   0x00100000
#define UX_HCD_STM32_OTG_FS_GINTMSK_IPXFRM                      0x00200000
#define UX_HCD_STM32_OTG_FS_GINTMSK_IISOOXFRM                   0x00200000
#define UX_HCD_STM32_OTG_FS_GINTMSK_FSUSPM                      0x00400000
#define UX_HCD_STM32_OTG_FS_GINTMSK_PRTIM                       0x01000000
#define UX_HCD_STM32_OTG_FS_GINTMSK_HCIM                        0x02000000
#define UX_HCD_STM32_OTG_FS_GINTMSK_PTXFEM                      0x04000000
#define UX_HCD_STM32_OTG_FS_GINTMSK_CIDSCHGM                    0x10000000
#define UX_HCD_STM32_OTG_FS_GINTMSK_DISCINTM                    0x20000000
#define UX_HCD_STM32_OTG_FS_GINTMSK_SRQINTM                     0x40000000
#define UX_HCD_STM32_OTG_FS_GINTMSK_WKUINTM                     0x80000000

/* Define STM32 USB host controller GRXSTSP register.  */
#define UX_HCD_STM32_OTG_FS_GRXSTSP_EPNUM_MASK                  0x0000000F
#define UX_HCD_STM32_OTG_FS_GRXSTSP_EPNUM_SHIFT                 0x00000000
#define UX_HCD_STM32_OTG_FS_GRXSTSP_BCNT_MASK                   0x00007FF0
#define UX_HCD_STM32_OTG_FS_GRXSTSP_BCNT_SHIFT                  0x00000004
#define UX_HCD_STM32_OTG_FS_GRXSTSP_DPID_MASK                   0x00018000
#define UX_HCD_STM32_OTG_FS_GRXSTSP_DPID_SHIFT                  0x0000000F
#define UX_HCD_STM32_OTG_FS_GRXSTSP_PKTSTS_MASK                 0x001E0000
#define UX_HCD_STM32_OTG_FS_GRXSTSP_PKTSTS_SHIFT                0x00000011
#define UX_HCD_STM32_OTG_FS_GRXSTSP_PKTSTS_IN_RCVD              0x00000002
#define UX_HCD_STM32_OTG_FS_GRXSTSP_PKTSTS_IN_COMPLETE          0x00000003

/* Define STM32 USB host controller GNPTXSTS register.  */
#define UX_HCD_STM32_OTG_FS_GNPTXSTS_NPTXFSAV_MASK              0x0000FFFF
#define UX_HCD_STM32_OTG_FS_GNPTXSTS_NPTXFSAV_SHIFT             0x00000000
#define UX_HCD_STM32_OTG_FS_GNPTXSTS_NPTQFSAV_MASK              0x00FF0000
#define UX_HCD_STM32_OTG_FS_GNPTXSTS_NPTQFSAV_SHIFT             0x00000010

/* Define STM32 USB host controller GRXFSIZ register.  */
#define UX_HCD_STM32_OTG_FS_GRXFSIZ_RXFD_MASK                   0x0000FFFF

/* Define STM32 USB host controller GNPTXFSIZ register.  */
#define UX_HCD_STM32_OTG_FS_GNPTXFSIZ_NPTXFSA_MASK              0x0000FFFF
#define UX_HCD_STM32_OTG_FS_GNPTXFSIZ_NPTXFSD_MASK              0xFFFF0000
#define UX_HCD_STM32_OTG_FS_GNPTXFSIZ_NPTXFSD_SHIFT             0x00000010

/* Define STM32 USB host controller HCFG register.  */
#define UX_HCD_STM32_OTG_FS_HCFG_FSLSPCS_FSLS                   0x00000001
#define UX_HCD_STM32_OTG_FS_HCFG_FSLSPCS_LS_48MHZ               0x00000001
#define UX_HCD_STM32_OTG_FS_HCFG_FSLSPCS_LS_6MHZ                0x00000002
#define UX_HCD_STM32_OTG_FS_HCFG_FSLSS                          0x00000004

/* Define STM32 USB host controller HFIR register.  */
#define UX_HCD_STM32_OTG_FS_HFIR_FRIVL_MASK                     0x0000FFFF

/* Define STM32 USB host controller HFNUM register.  */
#define UX_HCD_STM32_OTG_FS_HFNUM_FRNUM_MASK                    0x0000FFFF
#define UX_HCD_STM32_OTG_FS_HFNUM_FTREM_MASK                    0xFFFF0000
#define UX_HCD_STM32_OTG_FS_HFNUM_FTREM_SHIFT                   16

/* Define STM32 USB host controller GNPTXSTS register.  */
#define UX_HCD_STM32_OTG_FS_HPTXSTS_PTXFSAVL_MASK               0x0000FFFF
#define UX_HCD_STM32_OTG_FS_HPTXSTS_PTXFSAVL_SHIFT              0x00000000
#define UX_HCD_STM32_OTG_FS_HPTXSTS_PTQFSAV_MASK                0x00FF0000
#define UX_HCD_STM32_OTG_FS_HPTXSTS_PTQFSAV_SHIFT               0x00000010

/* Define STM32 USB host controller HPRT register.  */
#define UX_HCD_STM32_OTG_FS_HPRT_PCSTS                          0x00000001
#define UX_HCD_STM32_OTG_FS_HPRT_PCDET                          0x00000002
#define UX_HCD_STM32_OTG_FS_HPRT_PENA                           0x00000004
#define UX_HCD_STM32_OTG_FS_HPRT_PENCHNG                        0x00000008
#define UX_HCD_STM32_OTG_FS_HPRT_POCA                           0x00000010
#define UX_HCD_STM32_OTG_FS_HPRT_POCCHNG                        0x00000020
#define UX_HCD_STM32_OTG_FS_HPRT_PRES                           0x00000040
#define UX_HCD_STM32_OTG_FS_HPRT_PSUSP                          0x00000080
#define UX_HCD_STM32_OTG_FS_HPRT_PRST                           0x00000100
#define UX_HCD_STM32_OTG_FS_HPRT_PLSTS_FSDP                     0x00000800
#define UX_HCD_STM32_OTG_FS_HPRT_PLSTS_LSDP                     0x00000C00
#define UX_HCD_STM32_OTG_FS_HPRT_PPWR                           0x00001000
#define UX_HCD_STM32_OTG_FS_HPRT_PSPD_SPEED_MASK                0x00060000
#define UX_HCD_STM32_OTG_FS_HPRT_PSPD_SPEED_HS                  0x00000000
#define UX_HCD_STM32_OTG_FS_HPRT_PSPD_SPEED_FS                  0x00020000
#define UX_HCD_STM32_OTG_FS_HPRT_PSPD_SPEED_LS                  0x00040000

/* Define STM32 USB host controller HCCHAR register.  */
#define UX_HCD_STM32_OTG_FS_HCCHAR_MPSIZ_MASK                   0x000007FF
#define UX_HCD_STM32_OTG_FS_HCCHAR_EPNUM_MASK                   0x0000000F
#define UX_HCD_STM32_OTG_FS_HCCHAR_EPNUM_SHIFT                  11
#define UX_HCD_STM32_OTG_FS_HCCHAR_EPDIR_IN                     0x00008000
#define UX_HCD_STM32_OTG_FS_HCCHAR_EPDIR_OUT                    0x00000000
#define UX_HCD_STM32_OTG_FS_HCCHAR_LSDEV                        0x00020000
#define UX_HCD_STM32_OTG_FS_HCCHAR_EPTYP_MASK                   0x000C0000
#define UX_HCD_STM32_OTG_FS_HCCHAR_EPTYP_CONTROL                0x00000000
#define UX_HCD_STM32_OTG_FS_HCCHAR_EPTYP_ISO                    0x00040000
#define UX_HCD_STM32_OTG_FS_HCCHAR_EPTYP_BULK                   0x00080000
#define UX_HCD_STM32_OTG_FS_HCCHAR_EPTYP_INTERRUPT              0x000C0000
#define UX_HCD_STM32_OTG_FS_HCCHAR_DAD_MASK                     0x1FC00000
#define UX_HCD_STM32_OTG_FS_HCCHAR_DAD_SHIFT                    22
#define UX_HCD_STM32_OTG_FS_HCCHAR_ODDFRM                       0x20000000
#define UX_HCD_STM32_OTG_FS_HCCHAR_CHDIS                        0x40000000
#define UX_HCD_STM32_OTG_FS_HCCHAR_CHENA                        0x80000000

/* Define STM32 USB host controller HCINT register.  */
#define UX_HCD_STM32_OTG_FS_HCINT_XFRC                          0x00000001
#define UX_HCD_STM32_OTG_FS_HCINT_CHH                           0x00000002
#define UX_HCD_STM32_OTG_FS_HCINT_STALL                         0x00000008
#define UX_HCD_STM32_OTG_FS_HCINT_NAK                           0x00000010
#define UX_HCD_STM32_OTG_FS_HCINT_ACK                           0x00000020
#define UX_HCD_STM32_OTG_FS_HCINT_NYET                          0x00000040
#define UX_HCD_STM32_OTG_FS_HCINT_TXERR                         0x00000080
#define UX_HCD_STM32_OTG_FS_HCINT_BBERR                         0x00000100
#define UX_HCD_STM32_OTG_FS_HCINT_FRMOR                         0x00000200
#define UX_HCD_STM32_OTG_FS_HCINT_DTERR                         0x00000400
#define UX_HCD_STM32_OTG_FS_HCINT_RXFLVL                        0x10000000
#define UX_HCD_STM32_OTG_FS_HCINT_DEFAULT                       0x000007FB

/* Define STM32 USB host controller HCINTMSK register.  */
#define UX_HCD_STM32_OTG_FS_HCINT_XFRCM                         0x00000001
#define UX_HCD_STM32_OTG_FS_HCINT_CHHM                          0x00000002
#define UX_HCD_STM32_OTG_FS_HCINT_STALLM                        0x00000008
#define UX_HCD_STM32_OTG_FS_HCINT_NAKM                          0x00000010
#define UX_HCD_STM32_OTG_FS_HCINT_ACKM                          0x00000020
#define UX_HCD_STM32_OTG_FS_HCINT_TXERRM                        0x00000080
#define UX_HCD_STM32_OTG_FS_HCINT_BBERRM                        0x00000100
#define UX_HCD_STM32_OTG_FS_HCINT_FRMORM                        0x00000200
#define UX_HCD_STM32_OTG_FS_HCINT_DTERRM                        0x00000400

/* Define STM32 USB host controller HCINTMSK register.  */
#define UX_HCD_STM32_OTG_FS_HCTSIZ_XFRSIZ_MASK                  0x0007FFFF
#define UX_HCD_STM32_OTG_FS_HCTSIZ_PKTCNT_MASK                  0x1FF80000
#define UX_HCD_STM32_OTG_FS_HCTSIZ_PKTCNT_SHIFT                 19
#define UX_HCD_STM32_OTG_FS_HCTSIZ_DPID_MASK                    0x60000000
#define UX_HCD_STM32_OTG_FS_HCTSIZ_DPID_DATA0                   0x00000000
#define UX_HCD_STM32_OTG_FS_HCTSIZ_DPID_DATA2                   0x20000000
#define UX_HCD_STM32_OTG_FS_HCTSIZ_DPID_DATA1                   0x40000000
#define UX_HCD_STM32_OTG_FS_HCTSIZ_DPID_SETUP                   0x60000000
#define UX_HCD_STM32_OTG_FS_HCTSIZ_DPID_MDATA                   0x60000000

/* Define STM32 USB host controller PCGCCTL register.  */
#define UX_HCD_STM32_OTG_FS_PCGCCTL_STPPCLK                     0x00000001
#define UX_HCD_STM32_OTG_FS_PCGCCTL_GATEHCLK                    0x00000002
#define UX_HCD_STM32_OTG_FS_PCGCCTL_PHYSUSP                     0x00000008

/* Define STM32 USB host controller GCCFG register.  */
#define UX_HCD_STM32_OTG_FS_GCCFG_PWRDWN                        0x00010000
#define UX_HCD_STM32_OTG_FS_GCCFG_I2CIFEN                       0x00020000
#define UX_HCD_STM32_OTG_FS_GCCFG_VBUSSENSINGA                  0x00040000
#define UX_HCD_STM32_OTG_FS_GCCFG_VBUSSENSINGB                  0x00080000

/* Define STM32 static definition.  */

#define UX_HCD_STM32_AVAILABLE_BANDWIDTH                        6000
#define UX_HCD_STM32_PORT_RESET_DELAY                           50  
#define UX_HCD_STM32_PORT_ENABLE_DELAY                          100
#define UX_HCD_STM32_PORT_POWER_STABILIZE_DELAY                 100

/* Define STM32 completion code errors.  */

#define UX_HCD_STM32_NO_ERROR                                   0x00

/* Define STM32 structure.  */

typedef struct UX_HCD_STM32_STRUCT
{

    struct UX_HCD_STRUCT                *ux_hcd_stm32_hcd_owner;
    struct UX_HCD_STM32_ED_STRUCT       *ux_hcd_stm32_ed_list;
    struct UX_HCD_STM32_TD_STRUCT       *ux_hcd_stm32_td_list;
    struct UX_HCD_STM32_ISO_TD_STRUCT   *ux_hcd_stm32_iso_td_list;
    struct UX_HCD_STM32_ED_STRUCT       *ux_hcd_stm32_asynch_head_ed;
    struct UX_HCD_STM32_ED_STRUCT       *ux_hcd_stm32_asynch_current_ed;
    struct UX_HCD_STM32_ED_STRUCT       *ux_hcd_stm32_periodic_current_ed;
    struct UX_HCD_STM32_ED_STRUCT       *ux_hcd_stm32_iso_head_ed;
    struct UX_HCD_STM32_ED_STRUCT       *ux_hcd_stm32_interrupt_ed_list[32];
    struct UX_HCD_STM32_ED_STRUCT       *ux_hcd_stm32_channels_ed[UX_HCD_STM32_MAX_NB_CHANNELS];
    ULONG                               ux_hcd_stm32_nb_channels;
    UINT                                ux_hcd_stm32_queue_empty;
    UINT                                ux_hcd_stm32_periodic_scheduler_active;
    UINT                                ux_hcd_stm32_interruptible;
    ULONG                               ux_hcd_stm32_interrupt_count;
    ULONG                               ux_hcd_stm32_controller_flag;
    ULONG                               ux_hcd_stm32_nb_root_hubs;
    ULONG                               ux_hcd_stm32_base;
    ULONG                               *ux_hcd_stm32_bdt;
    ULONG                               ux_hcd_stm32_ping_pong_mode;
    ULONG                               ux_hcd_stm32_host_channel_interrupt;
    ULONG                               ux_hcd_stm32_frame_number;
    struct UX_HCD_STM32_ED_STRUCT       *ux_hcd_stm32_scheduled_ed;
} UX_HCD_STM32;


/* Define STM32 ED structure.  */

typedef struct UX_HCD_STM32_ED_STRUCT
{

    struct UX_HCD_STM32_TD_STRUCT       *ux_stm32_ed_tail_td;
    struct UX_HCD_STM32_TD_STRUCT       *ux_stm32_ed_head_td;
    struct UX_HCD_STM32_ED_STRUCT       *ux_stm32_ed_next_ed;
    struct UX_HCD_STM32_ED_STRUCT       *ux_stm32_ed_previous_ed;
    ULONG                               ux_stm32_ed_status;
    struct UX_ENDPOINT_STRUCT           *ux_stm32_ed_endpoint;
    ULONG                               ux_stm32_ed_toggle;   
    ULONG                               ux_stm32_ed_frame;    
    ULONG                               ux_stm32_ed_channel;
    ULONG                               ux_stm32_ed_command_retry;
    ULONG                               ux_stm32_ed_channel_status;
    ULONG                               ux_stm32_ed_nak_counter;
} UX_HCD_STM32_ED;


/* Define STM32 ED bitmap.  */

#define UX_HCD_STM32_ED_STATIC                                  0x80000000
#define UX_HCD_STM32_ED_SKIP                                    0x40000000

#define UX_HCD_STM32_ED_CHANNEL_RESET                           0x00000000
#define UX_HCD_STM32_ED_CHANNEL_HALTED                          0x00000001


/* Define STM32 TD structure.  */

typedef struct UX_HCD_STM32_TD_STRUCT
{                                                

    UCHAR                               *ux_stm32_td_buffer;
    ULONG                               ux_stm32_td_length;
    struct UX_HCD_STM32_TD_STRUCT       *ux_stm32_td_next_td;
    struct UX_TRANSFER_STRUCT           *ux_stm32_td_transfer_request;
    struct UX_HCD_STM32_TD_STRUCT       *ux_stm32_td_next_td_transfer_request;
    struct UX_HCD_STM32_ED_STRUCT       *ux_stm32_td_ed;
    ULONG                               ux_stm32_td_actual_length;
    ULONG                               ux_stm32_td_status;
    ULONG                               ux_stm32_td_direction;
    ULONG                               ux_stm32_td_toggle;
} UX_HCD_STM32_TD;


/* Define STM32 TD bitmap.  */

#define UX_HCD_STM32_TD_PHASE_MASK                            0x00070000   
#define UX_HCD_STM32_TD_SETUP_PHASE                           0x00010000   
#define UX_HCD_STM32_TD_DATA_PHASE                            0x00020000   
#define UX_HCD_STM32_TD_STATUS_PHASE                          0x00040000   
#define UX_HCD_STM32_TD_OUT                                   0x00000800
#define UX_HCD_STM32_TD_IN                                    0x00001000   
#define UX_HCD_STM32_TD_ACK_PENDING                           0x00080000
#define UX_HCD_STM32_TD_TOGGLE_FROM_ED                        0x80000000


/* Define STM32 ISOCHRONOUS TD structure.  */

typedef struct UX_HCD_STM32_ISO_TD_STRUCT
{

    UCHAR                               *ux_stm32_iso_td_buffer;
    ULONG                               ux_stm32_iso_td_length;
    struct UX_HCD_STM32_ISO_TD_STRUCT   *ux_stm32_iso_td_next_td;
    struct UX_TRANSFER_STRUCT           *ux_stm32_iso_td_transfer_request;
    struct UX_HCD_STM32_ISO_TD_STRUCT   *ux_stm32_iso_td_next_td_transfer_request;
    struct UX_HCD_STM32_ED_STRUCT       *ux_stm32_iso_td_ed;
    ULONG                               ux_stm32_iso_td_actual_length;
    ULONG                               ux_stm32_iso_td_status;
    ULONG                               ux_stm32_iso_td_direction;
} UX_HCD_STM32_ISO_TD;


/* Define STM32 function prototypes.  */

VOID                _ux_hcd_stm32_asynch_queue_process(UX_HCD_STM32 *hcd_stm32, ULONG channel_index, ULONG channel_interrupt_source);
UINT                _ux_hcd_stm32_asynch_schedule(UX_HCD_STM32 *hcd_stm32);
UINT                _ux_hcd_stm32_asynchronous_endpoint_create(UX_HCD_STM32 *hcd_stm32, UX_ENDPOINT *endpoint);
UINT                _ux_hcd_stm32_asynchronous_endpoint_destroy(UX_HCD_STM32 *hcd_stm32, UX_ENDPOINT *endpoint);
UINT                _ux_hcd_stm32_controller_disable(UX_HCD_STM32 *hcd_stm32);
UX_HCD_STM32_ED *   _ux_hcd_stm32_ed_obtain(UX_HCD_STM32 *hcd_stm32);
VOID                _ux_hcd_stm32_ed_td_clean(UX_HCD_STM32_ED *ed);
UINT                _ux_hcd_stm32_endpoint_reset(UX_HCD_STM32 *hcd_stm32, UX_ENDPOINT *endpoint);
UINT                _ux_hcd_stm32_entry(UX_HCD *hcd, UINT function, VOID *parameter);
UINT                _ux_hcd_stm32_frame_number_get(UX_HCD_STM32 *hcd_stm32, ULONG *frame_number);
VOID                _ux_hcd_stm32_frame_number_set(UX_HCD_STM32 *hcd_stm32, ULONG frame_number);
ULONG               _ux_hcd_stm32_register_read(UX_HCD_STM32 *hcd_stm32, ULONG stm32_register);
VOID                _ux_hcd_stm32_register_write(UX_HCD_STM32 *hcd_stm32, ULONG stm32_register, ULONG register_value);
VOID                _ux_hcd_stm32_register_clear(UX_HCD_STM32 *hcd_stm32, ULONG stm32_register, ULONG value);
VOID                _ux_hcd_stm32_register_set(UX_HCD_STM32 *hcd_stm32, ULONG stm32_register, ULONG value);
UINT                _ux_hcd_stm32_initialize_fscore(UX_HCD *hcd);
UINT                _ux_hcd_stm32_initialize_hscore(UX_HCD *hcd);
UINT                _ux_hcd_stm32_interrupt_endpoint_create(UX_HCD_STM32 *hcd_stm32, UX_ENDPOINT *endpoint);
VOID                _ux_hcd_stm32_interrupt_handler(VOID);
VOID                _ux_hcd_stm32_iso_queue_process(UX_HCD_STM32 *hcd_stm32);
UINT                _ux_hcd_stm32_iso_schedule(UX_HCD_STM32 *hcd_stm32);
UINT                _ux_hcd_stm32_isochronous_endpoint_create(UX_HCD_STM32 *hcd_stm32, UX_ENDPOINT *endpoint);
UX_HCD_STM32_ISO_TD *  _ux_hcd_stm32_isochronous_td_obtain(UX_HCD_STM32 *hcd_stm32);
UX_HCD_STM32_ED *   _ux_hcd_stm32_least_traffic_list_get(UX_HCD_STM32 *hcd_stm32);
UINT                _ux_hcd_stm32_periodic_endpoint_destroy(UX_HCD_STM32 *hcd_stm32, UX_ENDPOINT *endpoint);
UINT                _ux_hcd_stm32_periodic_schedule(UX_HCD_STM32 *hcd_stm32);
UINT                _ux_hcd_stm32_periodic_tree_create(UX_HCD_STM32 *hcd_stm32);
UINT                _ux_hcd_stm32_port_disable(UX_HCD_STM32 *hcd_stm32, ULONG port_index);
UINT                _ux_hcd_stm32_port_enable(UX_HCD_STM32 *hcd_stm32, ULONG port_index);
UINT                _ux_hcd_stm32_port_reset(UX_HCD_STM32 *hcd_stm32, ULONG port_index);
UINT                _ux_hcd_stm32_port_resume(UX_HCD_STM32 *hcd_stm32, UINT port_index);
ULONG               _ux_hcd_stm32_port_status_get(UX_HCD_STM32 *hcd_stm32, ULONG port_index);
UINT                _ux_hcd_stm32_port_suspend(UX_HCD_STM32 *hcd_stm32, ULONG port_index);
UINT                _ux_hcd_stm32_power_down_port(UX_HCD_STM32 *hcd_stm32, ULONG port_index);
UINT                _ux_hcd_stm32_power_on_port(UX_HCD_STM32 *hcd_stm32, ULONG port_index);
VOID                _ux_hcd_stm32_power_root_hubs(UX_HCD_STM32 *hcd_stm32);
UX_HCD_STM32_TD *   _ux_hcd_stm32_regular_td_obtain(UX_HCD_STM32 *hcd_stm32);
UINT                _ux_hcd_stm32_request_bulk_transfer(UX_HCD_STM32 *hcd_stm32, UX_TRANSFER *transfer_request);
UINT                _ux_hcd_stm32_request_control_transfer(UX_HCD_STM32 *hcd_stm32, UX_TRANSFER *transfer_request);
UINT                _ux_hcd_stm32_request_interrupt_transfer(UX_HCD_STM32 *hcd_stm32, UX_TRANSFER *transfer_request);
UINT                _ux_hcd_stm32_request_isochronous_transfer(UX_HCD_STM32 *hcd_stm32, UX_TRANSFER *transfer_request);
UINT                _ux_hcd_stm32_request_transfer(UX_HCD_STM32 *hcd_stm32, UX_TRANSFER *transfer_request);
UINT                _ux_hcd_stm32_transfer_abort(UX_HCD_STM32 *hcd_stm32, UX_TRANSFER *transfer_request);
UINT                _ux_hcd_stm32_td_schedule(UX_HCD_STM32 *hcd_stm32, UX_HCD_STM32_ED *ed);
VOID                _ux_hcd_stm32_delay(ULONG usec);
VOID                _ux_hcd_stm32_channel_halt(UX_HCD_STM32 *hcd_stm32, UX_HCD_STM32_ED *ed);

#define ux_hcd_stm32_initialize_fscore               _ux_hcd_stm32_initialize_fscore
#define ux_hcd_stm32_initialize_hscore               _ux_hcd_stm32_initialize_hscore
#define ux_hcd_stm32_interrupt_handler               _ux_hcd_stm32_interrupt_handler


#endif

