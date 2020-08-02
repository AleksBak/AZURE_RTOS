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
/*    ux_dcd_stm32.h                                      PORTABLE C      */
/*                                                           6.0          */
/*  AUTHOR                                                                */
/*                                                                        */
/*    Chaoqiong Xiao, Microsoft Corporation                               */
/*                                                                        */
/*  DESCRIPTION                                                           */
/*                                                                        */
/*    This file defines the USB OTG device equivalences for the STM32     */
/*    controller.                                                         */
/*                                                                        */
/*  RELEASE HISTORY                                                       */
/*                                                                        */
/*    DATE              NAME                      DESCRIPTION             */
/*                                                                        */
/*  05-19-2020     Chaoqiong Xiao           Initial Version 6.0           */
/*                                                                        */
/**************************************************************************/

#ifndef UX_DCD_STM32_H
#define UX_DCD_STM32_H

/* Define STM32 generic equivalences. */
#define UX_DCD_STM32_SLAVE_CONTROLLER                           0x80
#define UX_DCD_STM32_MAX_ED                                     4
#define UX_DCD_STM32_IN_FIFO                                    3
#define UX_DCD_STM32_DATA_FIFO_OFFSET                           0x00001000
#define UX_DCD_STM32_DATA_FIFO_SIZE                             0x00001000

/* Define FIFO sizes in 4-byte resolution. */
#define UX_DCD_STM32_RX_FIFO_SIZE                               (512 / 4)
#define UX_DCD_STM32_TX_FIFO_SIZE                               (512 / 4)
#define UX_DCD_STM32_NP_TX_FIFO_SIZE                            (384 / 4)
#define UX_DCD_STM32_ENDPOINT_TX_FIFO_SIZE_HS                   (384 / 4)
#define UX_DCD_STM32_ENDPOINT_TX_FIFO_SIZE_FS                   (128 / 4)

#define UX_DCD_STM32_FLUSH_RX_FIFO                              0x00000010
#define UX_DCD_STM32_FLUSH_TX_FIFO                              0x00000020
#define UX_DCD_STM32_FLUSH_FIFO_ALL                             0x00000010
#define UX_DCD_STM32_ENDPOINT_SPACE_SIZE                        0x00000020
#define UX_DCD_STM32_ENDPOINT_CHANNEL_SIZE                      0x00000020

#define UX_DCD_STM32_CONTROLLER_DELAY                           72

/* Define STM32 USB device controller CSR registers equivalences. */
#ifdef STM32F429I_DISCO_USBX
#define UX_DCD_STM32_OTG_FS_FULL_SPEED                          0x40040000
#else
#define UX_DCD_STM32_OTG_FS_FULL_SPEED                          0x50000000
#endif
#define UX_DCD_STM32_OTG_FS_HIGH_SPEED                          0x40040000

#define UX_DCD_STM32_OTG_FS_OTGCTL                              0x00000000
#define UX_DCD_STM32_OTG_FS_GOTGINT                             0x00000004
#define UX_DCD_STM32_OTG_FS_GAHBCFG                             0x00000008
#define UX_DCD_STM32_OTG_FS_GUSBCFG                             0x0000000C
#define UX_DCD_STM32_OTG_FS_GRSTCTL                             0x00000010
#define UX_DCD_STM32_OTG_FS_GINTSTS                             0x00000014
#define UX_DCD_STM32_OTG_FS_GINTMSK                             0x00000018
#define UX_DCD_STM32_OTG_FS_GRXSTSR                             0x0000001C
#define UX_DCD_STM32_OTG_FS_GRXSTSP                             0x00000020
#define UX_DCD_STM32_OTG_FS_GRXFSIZ                             0x00000024
#define UX_DCD_STM32_OTG_FS_GNPTXFSIZ                           0x00000028
#define UX_DCD_STM32_OTG_FS_GNPTXSTS                            0x0000002C
#define UX_DCD_STM32_OTG_FS_GCCFG                               0x00000038
#define UX_DCD_STM32_OTG_FS_CID                                 0x0000003C
#define UX_DCD_STM32_OTG_FS_HPTXFSIZ                            0x00000100
#define UX_DCD_STM32_OTG_FS_DIEPTXF                             0x00000104
#define UX_DCD_STM32_OTG_FS_DCFG                                0x00000800
#define UX_DCD_STM32_OTG_FS_DCTL                                0x00000804
#define UX_DCD_STM32_OTG_FS_DSTS                                0x00000808
#define UX_DCD_STM32_OTG_FS_DIEPMSK                             0x00000810
#define UX_DCD_STM32_OTG_FS_DOEPMSK                             0x00000814
#define UX_DCD_STM32_OTG_FS_DAINT                               0x00000818
#define UX_DCD_STM32_OTG_FS_DAINTMSK                            0x0000081C
#define UX_DCD_STM32_OTG_FS_DVBUSDIS                            0x00000828
#define UX_DCD_STM32_OTG_FS_DVBUSPULSE                          0x0000082C
#define UX_DCD_STM32_OTG_FS_DIEPEMPMSK                          0x00000834
#define UX_DCD_STM32_OTG_FS_DIEPCTL                             0x00000900	/* OTG_HS Device Control IN EP0 control register */
#define UX_DCD_STM32_OTG_FS_DIEPINT                             0x00000908	/* OTG_HS Device EPx interrupt register (x=1..5) */
#define UX_DCD_STM32_OTG_FS_DIEPTSIZ                            0x00000910
#define UX_DCD_STM32_OTG_FS_DTXFSTS                             0x00000918
#define UX_DCD_STM32_OTG_FS_DOEPCTL                             0x00000B00
#define UX_DCD_STM32_OTG_FS_DOEPINT                             0x00000B08
#define UX_DCD_STM32_OTG_FS_DOEPTSIZ                            0x00000B10
#define UX_DCD_STM32_OTG_FS_PCGCCTL                             0x00000E00

/* Define STM32 USB device controller OTGCTL registers equivalences. */
#define UX_DCD_STM32_OTG_FS_OTGCTL_SRQSCS                       0x00000001
#define UX_DCD_STM32_OTG_FS_OTGCTL_SRQ                          0x00000002
#define UX_DCD_STM32_OTG_FS_OTGCTL_HNGSCS                       0x00000100
#define UX_DCD_STM32_OTG_FS_OTGCTL_HNPRQ                        0x00000200
#define UX_DCD_STM32_OTG_FS_OTGCTL_HSHNPEN                      0x00000400
#define UX_DCD_STM32_OTG_FS_OTGCTL_DHNPEN                       0x00000800
#define UX_DCD_STM32_OTG_FS_OTGCTL_CIDSTS                       0x00010000
#define UX_DCD_STM32_OTG_FS_OTGCTL_DBCT                         0x00020000
#define UX_DCD_STM32_OTG_FS_OTGCTL_ASVLD                        0x00040000
#define UX_DCD_STM32_OTG_FS_OTGCTL_BSVLD                        0x00080000

/* Define STM32 USB device controller GOTGINT register. */
#define UX_DCD_STM32_OTG_FS_GOTGINT_SEDET                       0x00000002
#define UX_DCD_STM32_OTG_FS_GOTGINT_SRSSCHG                     0x00000100
#define UX_DCD_STM32_OTG_FS_GOTGINT_HNSSCHG                     0x00000200
#define UX_DCD_STM32_OTG_FS_GOTGINT_HNGDET                      0x00020000
#define UX_DCD_STM32_OTG_FS_GOTGINT_ADTOCHG                     0x00040000
#define UX_DCD_STM32_OTG_FS_GOTGINT_DBCDNE                      0x00080000

/* Define STM32 USB device controller GAHBCFG register. */
#define UX_DCD_STM32_OTG_FS_GAHBCFG_GINT                        0x00000001
#define UX_DCD_STM32_OTG_FS_GAHBCFG_TXFEVL                      0x00000100
#define UX_DCD_STM32_OTG_FS_GAHBCFG_PTXFEVL                     0x00000200

/* Define STM32 USB device controller GUSBCFG register. */
#define UX_DCD_STM32_OTG_FS_GUSBCFG_TOCAL_MASK                  0x00000007
#define UX_DCD_STM32_OTG_FS_GUSBCFG_PHYIF                       0x00000008
#define UX_DCD_STM32_OTG_FS_GUSBCFG_ULPI_UTMI_SEL               0x00000010
#define UX_DCD_STM32_OTG_FS_GUSBCFG_FSINTF                      0x00000020
#define UX_DCD_STM32_OTG_FS_GUSBCFG_PHYSEL                      0x00000040
#define UX_DCD_STM32_OTG_FS_GUSBCFG_DDRSEL                      0x00000080
#define UX_DCD_STM32_OTG_FS_GUSBCFG_SRPCAP                      0x00000100
#define UX_DCD_STM32_OTG_FS_GUSBCFG_HNPCAP                      0x00000200
#define UX_DCD_STM32_OTG_FS_GUSBCFG_TRDT_16                     0x00001400
#define UX_DCD_STM32_OTG_FS_GUSBCFG_TRDT_8                      0x00002400
#define UX_DCD_STM32_OTG_FS_GUSBCFG_TRDT_MASK                   0x00003C00
#define UX_DCD_STM32_OTG_FS_GUSBCFG_NPTXRWEN                    0x00004000
#define UX_DCD_STM32_OTG_FS_GUSBCFG_FHMOD                       0x20000000
#define UX_DCD_STM32_OTG_FS_GUSBCFG_FDMOD                       0x40000000
#define UX_DCD_STM32_OTG_FS_GUSBCFG_CTXPKT                      0x80000000

/* Define STM32 USB device controller GRSTCTL register. */
#define UX_DCD_STM32_OTG_FS_GRSTCTL_CSRST                       0x00000001
#define UX_DCD_STM32_OTG_FS_GRSTCTL_HSRST                       0x00000002
#define UX_DCD_STM32_OTG_FS_GRSTCTL_FCRST                       0x00000004
#define UX_DCD_STM32_OTG_FS_GRSTCTL_RXFFLSH                     0x00000010
#define UX_DCD_STM32_OTG_FS_GRSTCTL_TXFFLSH                     0x00000020
#define UX_DCD_STM32_OTG_FS_GRSTCTL_TXFNUM_MASK                 0x000007C0
#define UX_DCD_STM32_OTG_FS_GRSTCTL_TXFNUM_SHIFT                0x00000006
#define UX_DCD_STM32_OTG_FS_GRSTCTL_AHBIDL                      0x80000000

/* Define STM32 USB device controller GINTSTS register. */
#define UX_DCD_STM32_OTG_FS_GINTSTS_CMOD                        0x00000001
#define UX_DCD_STM32_OTG_FS_GINTSTS_MMIS                        0x00000002
#define UX_DCD_STM32_OTG_FS_GINTSTS_OTGINT                      0x00000004
#define UX_DCD_STM32_OTG_FS_GINTSTS_SOF                         0x00000008
#define UX_DCD_STM32_OTG_FS_GINTSTS_RFXLVL                      0x00000010
#define UX_DCD_STM32_OTG_FS_GINTSTS_NPTXFE                      0x00000020
#define UX_DCD_STM32_OTG_FS_GINTSTS_GINAKEFF                    0x00000040
#define UX_DCD_STM32_OTG_FS_GINTSTS_BOUNTNAKEFF                 0x00000080
#define UX_DCD_STM32_OTG_FS_GINTSTS_ESUSP                       0x00000400
/** USB_OTG_GINTSTS_USBSUSP				*/
#define UX_DCD_STM32_OTG_FS_GINTSTS_USBSUSP                     0x00000800
/** USB_OTG_GINTSTS_USBRST				*/
#define UX_DCD_STM32_OTG_FS_GINTSTS_USBRST                      0x00001000
/** USB_OTG_GINTSTS_ENUMDNE				*/
#define UX_DCD_STM32_OTG_FS_GINTSTS_ENUMDNE                     0x00002000
/** USB_OTG_GINTSTS_ISOODRP				*/
#define UX_DCD_STM32_OTG_FS_GINTSTS_ISOODRP                     0x00004000
/** USB_OTG_GINTSTS_EOPF				*/
#define UX_DCD_STM32_OTG_FS_GINTSTS_EOPF                        0x00008000
/** USB_OTG_GINTSTS_IEPINT				*/
#define UX_DCD_STM32_OTG_FS_GINTSTS_IEPINT                      0x00040000
/** USB_OTG_GINTSTS_OEPINT				*/
#define UX_DCD_STM32_OTG_FS_GINTSTS_OEPINT                      0x00080000
/** USB_OTG_GINTSTS_IISOIXFR			*/
#define UX_DCD_STM32_OTG_FS_GINTSTS_IISOIXFR                    0x00100000
/** -	*/
#define UX_DCD_STM32_OTG_FS_GINTSTS_IPXFR                       0x00200000
/** USB_OTG_GINTSTS_PXFR_INCOMPISOOUT	*/
#define UX_DCD_STM32_OTG_FS_GINTSTS_INCOMPISOOUT                0x00200000
/** USB_OTG_GINTSTS_HPRTINT				*/
#define UX_DCD_STM32_OTG_FS_GINTSTS_HPRTINT                     0x01000000
/** USB_OTG_GINTSTS_HCINT				*/
#define UX_DCD_STM32_OTG_FS_GINTSTS_HCINT                       0x02000000
/** USB_OTG_GINTSTS_PTXFE				*/
#define UX_DCD_STM32_OTG_FS_GINTSTS_PTXFE                       0x04000000
/** USB_OTG_GINTSTS_CIDSCHG				*/
#define UX_DCD_STM32_OTG_FS_GINTSTS_CIDSCHG                     0x10000000
/** USB_OTG_GINTSTS_DISCINT				*/
#define UX_DCD_STM32_OTG_FS_GINTSTS_DISCINT                     0x20000000
/** USB_OTG_GINTSTS_SRQINT				*/
#define UX_DCD_STM32_OTG_FS_GINTSTS_SRQINT                      0x40000000
/** USB_OTG_GINTSTS_WKUINT				*/
#define UX_DCD_STM32_OTG_FS_GINTSTS_WKUINT                      0x80000000

/* Define STM32 USB device controller GINTMSK register. */
#define UX_DCD_STM32_OTG_FS_GINTMSK_MMISM                       0x00000002
#define UX_DCD_STM32_OTG_FS_GINTMSK_OTGINT                      0x00000004
#define UX_DCD_STM32_OTG_FS_GINTMSK_SOFM                        0x00000008
#define UX_DCD_STM32_OTG_FS_GINTMSK_RFXLVLM                     0x00000010
#define UX_DCD_STM32_OTG_FS_GINTMSK_NPTXFEM                     0x00000020
#define UX_DCD_STM32_OTG_FS_GINTMSK_GINAKEFFM                   0x00000040
#define UX_DCD_STM32_OTG_FS_GINTMSK_GONAKEFFM                   0x00000080
#define UX_DCD_STM32_OTG_FS_GINTMSK_ESUSPM                      0x00000400
#define UX_DCD_STM32_OTG_FS_GINTMSK_USBSUSPM                    0x00000800
#define UX_DCD_STM32_OTG_FS_GINTMSK_USBRSTM                     0x00001000
#define UX_DCD_STM32_OTG_FS_GINTMSK_ENUMDNEM                    0x00002000
#define UX_DCD_STM32_OTG_FS_GINTMSK_ISOODRPM                    0x00004000
#define UX_DCD_STM32_OTG_FS_GINTMSK_EOPFM                       0x00008000
#define UX_DCD_STM32_OTG_FS_GINTMSK_IEPINTM                     0x00040000
#define UX_DCD_STM32_OTG_FS_GINTMSK_OEPINTM                     0x00080000
#define UX_DCD_STM32_OTG_FS_GINTMSK_IISOIXFRM                   0x00100000
#define UX_DCD_STM32_OTG_FS_GINTMSK_IPXFRM                      0x00200000
#define UX_DCD_STM32_OTG_FS_GINTMSK_IISOOXFRM                   0x00200000
#define UX_DCD_STM32_OTG_FS_GINTMSK_FSUSPM                      0x00400000
#define UX_DCD_STM32_OTG_FS_GINTMSK_PRTIM                       0x01000000
#define UX_DCD_STM32_OTG_FS_GINTMSK_HCIM                        0x02000000
#define UX_DCD_STM32_OTG_FS_GINTMSK_PTXFEM                      0x04000000
#define UX_DCD_STM32_OTG_FS_GINTMSK_CIDSCHGM                    0x10000000
#define UX_DCD_STM32_OTG_FS_GINTMSK_DISCINTM                    0x20000000
#define UX_DCD_STM32_OTG_FS_GINTMSK_SRQINTM                     0x40000000
#define UX_DCD_STM32_OTG_FS_GINTMSK_WKUINTM                     0x80000000

/* Define STM32 USB device controller GRXSTSP register. */
#define UX_DCD_STM32_OTG_FS_GRXSTSP_EPNUM_MASK                  0x0000000F
#define UX_DCD_STM32_OTG_FS_GRXSTSP_EPNUM_SHIFT                 0x00000000
#define UX_DCD_STM32_OTG_FS_GRXSTSP_BCNT_MASK                   0x00007FF0
#define UX_DCD_STM32_OTG_FS_GRXSTSP_BCNT_SHIFT                  0x00000004
#define UX_DCD_STM32_OTG_FS_GRXSTSP_DPID_MASK                   0x00018000
#define UX_DCD_STM32_OTG_FS_GRXSTSP_DPID_SHIFT                  0x0000000F
#define UX_DCD_STM32_OTG_FS_GRXSTSP_PKTSTS_MASK                 0x001E0000
#define UX_DCD_STM32_OTG_FS_GRXSTSP_PKTSTS_SHIFT                0x00000011
#define UX_DCD_STM32_OTG_FS_GRXSTSP_PKTSTS_OUT_RCVD             0x00000002
#define UX_DCD_STM32_OTG_FS_GRXSTSP_PKTSTS_SETUP_RCVD           0x00000006

/* Define STM32 USB device controller GRXFSIZ register. */
#define UX_DCD_STM32_OTG_FS_GRXFSIZ_RXFD_MASK                   0x0000FFFF

/* Define STM32 USB device controller GNPTXFSIZ register. */
#define UX_DCD_STM32_OTG_FS_GNPTXFSIZ_NPTXFSA_MASK              0x0000FFFF
#define UX_DCD_STM32_OTG_FS_GNPTXFSIZ_NPTXFSD_MASK              0xFFFF0000
#define UX_DCD_STM32_OTG_FS_GNPTXFSIZ_NPTXFSD_SHIFT             0x00000010

/* Define STM32 USB device controller DIEPTXF register. */
#define UX_DCD_STM32_OTG_FS_DIEPTXF_INEPTXSA_MASK               0x0000FFFF
#define UX_DCD_STM32_OTG_FS_DIEPTXF_INEPTXSD_MASK               0xFFFF0000
#define UX_DCD_STM32_OTG_FS_DIEPTXF_INEPTXSD_SHIFT              0x00000010

/* Define STM32 USB device controller DCFG register. */
#define UX_DCD_STM32_OTG_FS_DCFG_DSPD_MASK                      0x00000003
#define UX_DCD_STM32_OTG_FS_DCFG_DSPD_FULL_SPEED                0x00000003
#define UX_DCD_STM32_OTG_FS_DCFG_NZLSOHSK                       0x00000004
#define UX_DCD_STM32_OTG_FS_DCFG_DAD_MASK                       0x000007F0
#define UX_DCD_STM32_OTG_FS_DCFG_DAD_SHIFT                      0x00000004
#define UX_DCD_STM32_OTG_FS_DCFG_PFVIL_MASK                     0x00001800

/* Define STM32 USB device controller DCTL register. */
#define UX_DCD_STM32_OTG_FS_DCTL_RWUSIG                         0x00000001
#define UX_DCD_STM32_OTG_FS_DCTL_SDIS                           0x00000002
#define UX_DCD_STM32_OTG_FS_DCTL_GINSTS                         0x00000004
#define UX_DCD_STM32_OTG_FS_DCTL_GONSTS                         0x00000008
#define UX_DCD_STM32_OTG_FS_DCTL_TCTL_MASK                      0x00000070
#define UX_DCD_STM32_OTG_FS_DCTL_SGINAK                         0x00000080
#define UX_DCD_STM32_OTG_FS_DCTL_CGINAK                         0x00000100
#define UX_DCD_STM32_OTG_FS_DCTL_SGONAK                         0x00000200
#define UX_DCD_STM32_OTG_FS_DCTL_CGONAK                         0x00000400
#define UX_DCD_STM32_OTG_FS_DCTL_POPRGDNE                       0x00000800

/* Define STM32 USB device controller DSTS register. */
#define UX_DCD_STM32_OTG_FS_DSTS_SUSPSTS                        0x00000001
#define UX_DCD_STM32_OTG_FS_DSTS_ENUMSPD_MASK                   0x00000006
#define UX_DCD_STM32_OTG_FS_DSTS_ENUMSPD_FS                     0x00000006
#define UX_DCD_STM32_OTG_FS_DSTS_ENUMSPD_HS                     0x00000000
#define UX_DCD_STM32_OTG_FS_DSTS_ERR                            0x00000004

/* Define STM32 USB device controller DIEPMSK register. */
#define UX_DCD_STM32_OTG_FS_DIEPMSK_XFRCM                       0x00000001
#define UX_DCD_STM32_OTG_FS_DIEPMSK_EPDM                        0x00000002
#define UX_DCD_STM32_OTG_FS_DIEPMSK_TOM                         0x00000008
#define UX_DCD_STM32_OTG_FS_DIEPMSK_ITTXFEMSK                   0x00000010
#define UX_DCD_STM32_OTG_FS_DIEPMSK_INEPNMM                     0x00000020
#define UX_DCD_STM32_OTG_FS_DIEPMSK_INEPNEM                     0x00000040
#define UX_DCD_STM32_OTG_FS_DIEPMSK_TXFURM                      0x00000100
#define UX_DCD_STM32_OTG_FS_DIEPMSK_BIM                         0x00000200

/* Define STM32 USB device controller DOEPMSK register. */
#define UX_DCD_STM32_OTG_FS_DOEPMSK_XFRCM                       0x00000001
#define UX_DCD_STM32_OTG_FS_DOEPMSK_EPDM                        0x00000002
#define UX_DCD_STM32_OTG_FS_DOEPMSK_STUPM                       0x00000008
#define UX_DCD_STM32_OTG_FS_DOEPMSK_OTEPDM                      0x00000010
#define UX_DCD_STM32_OTG_FS_DOEPMSK_B2BSTUP                     0x00000040
#define UX_DCD_STM32_OTG_FS_DOEPMSK_OPEM                        0x00000100
#define UX_DCD_STM32_OTG_FS_DOEPMSK_BIM                         0x00000200

/* Define STM32 USB device controller DAINT register. */
#define UX_DCD_STM32_OTG_FS_DAINT_IEPINT_MASK                   0x0000FFFF
#define UX_DCD_STM32_OTG_FS_DAINT_IEPINT_SHIFT                  0x00000000
#define UX_DCD_STM32_OTG_FS_DAINT_OEPINT_MASK                   0xFFFF0000
#define UX_DCD_STM32_OTG_FS_DAINT_OEPINT_SHIFT                  0x00000010

/* Define STM32 USB device controller DAINTMSK register. */
#define UX_DCD_STM32_OTG_FS_DAINTMSK_IEPM_MASK                  0x0000FFFF
#define UX_DCD_STM32_OTG_FS_DAINTMSK_IEPM_SHIFT                 0x00000000
#define UX_DCD_STM32_OTG_FS_DAINTMSK_OEPM_MASK                  0xFFFF0000
#define UX_DCD_STM32_OTG_FS_DAINTMSK_OEPM_SHIFT                 0x00000010

/* Define STM32 USB device controller DIEPCTL0 register. */
#define UX_DCD_STM32_OTG_FS_DIEPCTL0_MPSIZ_MASK                 0x00000003
#define UX_DCD_STM32_OTG_FS_DIEPCTL0_MPSIZ_64                   0x00000000
#define UX_DCD_STM32_OTG_FS_DIEPCTL0_MPSIZ_32                   0x00000001
#define UX_DCD_STM32_OTG_FS_DIEPCTL0_MPSIZ_16                   0x00000002
#define UX_DCD_STM32_OTG_FS_DIEPCTL0_MPSIZ_8                    0x00000003
#define UX_DCD_STM32_OTG_FS_DIEPCTL0_USBAEP                     0x00008000
#define UX_DCD_STM32_OTG_FS_DIEPCTL0_NAKSTS                     0x00020000
#define UX_DCD_STM32_OTG_FS_DIEPCTL0_STALL                      0x00200000
#define UX_DCD_STM32_OTG_FS_DIEPCTL0_TXFNUM_MASK                0x03C00000
#define UX_DCD_STM32_OTG_FS_DIEPCTL0_TXFNUM_SHIFT               0x00000015
#define UX_DCD_STM32_OTG_FS_DIEPCTL0_CNAK                       0x04000000
#define UX_DCD_STM32_OTG_FS_DIEPCTL0_SNAK                       0x08000000
#define UX_DCD_STM32_OTG_FS_DIEPCTL0_EPDIS                      0x40000000
#define UX_DCD_STM32_OTG_FS_DIEPCTL0_EPENA                      0x80000000

/* OTG Device EPx control register (DIEPCTLx, where x = 1..5). */
#define UX_DCD_STM32_OTG_FS_DIEPCTL_MPSIZ_MASK                  0x000007FF
#define UX_DCD_STM32_OTG_FS_DIEPCTL_USBAEP                      0x00008000
#define UX_DCD_STM32_OTG_FS_DIEPCTL_EONUM                       0x00010000
#define UX_DCD_STM32_OTG_FS_DIEPCTL_DPID                        0x00010000
#define UX_DCD_STM32_OTG_FS_DIEPCTL_NAKSTS                      0x00020000
#define UX_DCD_STM32_OTG_FS_DIEPCTL_EPTYP_MASK                  0x000C0000
#define UX_DCD_STM32_OTG_FS_DIEPCTL_EPTYP_ISO                   0x00040000
#define UX_DCD_STM32_OTG_FS_DIEPCTL_EPTYP_BULK                  0x00080000
#define UX_DCD_STM32_OTG_FS_DIEPCTL_EPTYP_INTERRUPT             0x000C0000
#define UX_DCD_STM32_OTG_FS_DIEPCTL_STALL                       0x00200000
#define UX_DCD_STM32_OTG_FS_DIEPCTL_TXFNUM_MASK                 0x03C00000	/* Bits 25:26 (mask) - TXFNUM - TxFIFO NUMber */
#define UX_DCD_STM32_OTG_FS_DIEPCTL_TXFNUM_SHIFT                0x00000016
#define UX_DCD_STM32_OTG_FS_DIEPCTL_CNAK                        0x04000000	/* Bit 26 - SNAK - Clear NAK */
#define UX_DCD_STM32_OTG_FS_DIEPCTL_SNAK                        0x08000000	/* Bit 27 - SNAK - Set NAK */
#define UX_DCD_STM32_OTG_FS_DIEPCTL_SD0PID                      0x10000000	/* Bit 28 - SD0PID - Set DATA0 PID */
#define UX_DCD_STM32_OTG_FS_DIEPCTL_EPDIS                       0x40000000	/* Bit 30 - EPDIS - EndPoint DISable */
#define UX_DCD_STM32_OTG_FS_DIEPCTL_EPENA                       0x80000000	/* Bit 31 - EPENA - EndPoint ENAble */

/* OTG_HS Device Control OUT EP0 control register (DOEPCTL0). */
#define UX_DCD_STM32_OTG_FS_DOEPCTL0_MPSIZ_MASK                 0x00000003
#define UX_DCD_STM32_OTG_FS_DOEPCTL0_MPSIZ_64                   0x00000000
#define UX_DCD_STM32_OTG_FS_DOEPCTL0_MPSIZ_32                   0x00000001
#define UX_DCD_STM32_OTG_FS_DOEPCTL0_MPSIZ_16                   0x00000002
#define UX_DCD_STM32_OTG_FS_DOEPCTL0_MPSIZ_8                    0x00000003
#define UX_DCD_STM32_OTG_FS_DOEPCTL0_USBAEP                     0x00008000
#define UX_DCD_STM32_OTG_FS_DOEPCTL0_NAKSTS                     0x00020000
#define UX_DCD_STM32_OTG_FS_DOEPCTL0_SNPM                       0x00100000
#define UX_DCD_STM32_OTG_FS_DOEPCTL0_STALL                      0x00200000
#define UX_DCD_STM32_OTG_FS_DOEPCTL0_CNAK                       0x04000000
#define UX_DCD_STM32_OTG_FS_DOEPCTL0_SNAK                       0x08000000
#define UX_DCD_STM32_OTG_FS_DOEPCTL0_EPDIS                      0x40000000
#define UX_DCD_STM32_OTG_FS_DOEPCTL0_EPENA                      0x80000000

/* Define STM32 USB device controller DOEPCTL register. */
#define UX_DCD_STM32_OTG_FS_DOEPCTL_MPSIZ_MASK                  0x000007FF
#define UX_DCD_STM32_OTG_FS_DOEPCTL_USBAEP                      0x00008000
#define UX_DCD_STM32_OTG_FS_DOEPCTL_EONUM                       0x00010000
#define UX_DCD_STM32_OTG_FS_DOEPCTL_DPID                        0x00010000
#define UX_DCD_STM32_OTG_FS_DOEPCTL_NAKSTS                      0x00020000
#define UX_DCD_STM32_OTG_FS_DOEPCTL_EPTYP_MASK                  0x000C0000
#define UX_DCD_STM32_OTG_FS_DOEPCTL_EPTYP_ISO                   0x00040000
#define UX_DCD_STM32_OTG_FS_DOEPCTL_EPTYP_BULK                  0x00080000
#define UX_DCD_STM32_OTG_FS_DOEPCTL_EPTYP_INTERRUPT             0x000C0000
#define UX_DCD_STM32_OTG_FS_DOEPCTL_STALL                       0x00200000
#define UX_DCD_STM32_OTG_FS_DOEPCTL_TXFNUM_MASK                 0x03C00000
#define UX_DCD_STM32_OTG_FS_DOEPCTL_TXFNUM_SHIFT                0x00000015
#define UX_DCD_STM32_OTG_FS_DOEPCTL_CNAK                        0x04000000
#define UX_DCD_STM32_OTG_FS_DOEPCTL_SNAK                        0x08000000
#define UX_DCD_STM32_OTG_FS_DOEPCTL_SDOPID                      0x10000000
#define UX_DCD_STM32_OTG_FS_DOEPCTL_SEVNFRM                     0x10000000
#define UX_DCD_STM32_OTG_FS_DOEPCTL_SODDFRM                     0x20000000
#define UX_DCD_STM32_OTG_FS_DOEPCTL_EPDIS                       0x40000000
#define UX_DCD_STM32_OTG_FS_DOEPCTL_EPENA                       0x80000000

/* Define STM32 USB device controller DIEPINT register. */
/** USB_OTG_DIEPINT_XFRC	*/
#define UX_DCD_STM32_OTG_FS_DIEPINT_XFRC                        0x00000001
/** USB_OTG_DIEPINT_EPDISD	*/
#define UX_DCD_STM32_OTG_FS_DIEPINT_EPDISD                      0x00000002
/** USB_OTG_DIEPINT_TOC		*/
#define UX_DCD_STM32_OTG_FS_DIEPINT_TOC                         0x00000008
/** USB_OTG_DIEPINT_ITTXFE	*/
#define UX_DCD_STM32_OTG_FS_DIEPINT_ITTXFE                      0x00000010
/** USB_OTG_DIEPINT_INEPNE	*/
#define UX_DCD_STM32_OTG_FS_DIEPINT_INEPNE                      0x00000040
/** USB_OTG_DIEPINT_TXFE	*/
#define UX_DCD_STM32_OTG_FS_DIEPINT_TXFE                        0x00000080
/** */
#define UX_DCD_STM32_OTG_FS_DIEPINT_ALL                         0x000000DD

/* Define STM32 USB device controller DIEPTSIZ register. */
#define UX_DCD_STM32_OTG_FS_DIEPTSIZ_XFRSIZ_MASK                0x0000007F
#define UX_DCD_STM32_OTG_FS_DIEPTSIZ_PKTCNT_SHIFT               19

/* Define STM32 USB device controller DOEPINT register. */
/** USB_OTG_DOEPINT_XFRC	*/
#define UX_DCD_STM32_OTG_FS_DOEPINT_XFRC                        0x00000001
/** USB_OTG_DOEPINT_EPDISD	*/
#define UX_DCD_STM32_OTG_FS_DOEPINT_EPDISD                      0x00000002
/** USB_OTG_DOEPINT_STUP	*/
#define UX_DCD_STM32_OTG_FS_DOEPINT_STUP                        0x00000008
/** USB_OTG_DOEPINT_OTEPDIS	*/
#define UX_DCD_STM32_OTG_FS_DOEPINT_OTEPDIS                     0x00000010
/** USB_OTG_DOEPINT_B2BSTUP	*/
#define UX_DCD_STM32_OTG_FS_DOEPINT_B2BSTUP                     0x00000040
/** */
#define UX_DCD_STM32_OTG_FS_DOEPINT_ALL                         0x0000005D

/* Define STM32 USB device controller DOEPTSIZ register. */
#define UX_DCD_STM32_OTG_FS_DOEPTSIZ_XFRSIZ_MASK                0x0000007F
#define UX_DCD_STM32_OTG_FS_DOEPTSIZ_PKTCNT_SHIFT               19
#define UX_DCD_STM32_OTG_FS_DOEPTSIZ_STUPCNT_MASK               0x60000000
#define UX_DCD_STM32_OTG_FS_DOEPTSIZ_STUPCNT_SHIFT              29
#define UX_DCD_STM32_OTG_FS_DOEPTSIZ_STUPCNT_DEFAULT            3

/* Define STM32 USB device controller PCGCCTL register. */
/** USB_OTG_PCGCCTL_STOPCLK	*/
#define UX_DCD_STM32_OTG_FS_PCGCCTL_STPPCLK                     0x00000001
/** USB_OTG_PCGCCTL_GATECLK	*/
#define UX_DCD_STM32_OTG_FS_PCGCCTL_GATEHCLK                    0x00000002
/** USB_OTG_PCGCCTL_PHYSUSP	*/
#define UX_DCD_STM32_OTG_FS_PCGCCTL_PHYSUSP                     0x00000008

/* Define STM32 USB device controller GCCFG register. */
#define UX_DCD_STM32_OTG_FS_GCCFG_PWRDWN                        0x00010000
#define UX_DCD_STM32_OTG_FS_GCCFG_I2CIFEN                       0x00020000
#define UX_DCD_STM32_OTG_FS_GCCFG_VBUSSENSINGA                  0x00040000
#define UX_DCD_STM32_OTG_FS_GCCFG_VBUSSENSINGB                  0x00080000
#define UX_DCD_STM32_OTG_FS_GCCFG_VBDEN                         0x00200000

/* Define USB STM32 physical endpoint status definition. */
#define UX_DCD_STM32_ED_STATUS_UNUSED                            0
#define UX_DCD_STM32_ED_STATUS_USED                              1
#define UX_DCD_STM32_ED_STATUS_TRANSFER                          2
#define UX_DCD_STM32_ED_STATUS_STALLED                           4

/* Define USB STM32 physical endpoint state machine definition. */
#define UX_DCD_STM32_ED_STATE_IDLE                               0
#define UX_DCD_STM32_ED_STATE_DATA_TX                            1
#define UX_DCD_STM32_ED_STATE_DATA_RX                            2
#define UX_DCD_STM32_ED_STATE_STATUS_TX                          3
#define UX_DCD_STM32_ED_STATE_STATUS_RX                          4

/* Define USB STM32 endpoint transfer status definition. */
#define UX_DCD_STM32_ED_TRANSFER_STATUS_IDLE                     0
#define UX_DCD_STM32_ED_TRANSFER_STATUS_SETUP                    1
#define UX_DCD_STM32_ED_TRANSFER_STATUS_IN_COMPLETION            2
#define UX_DCD_STM32_ED_TRANSFER_STATUS_OUT_COMPLETION           3

/* Define USB STM32 physical endpoint structure. */
typedef struct UX_DCD_STM32_ED_STRUCT
{
	ULONG ux_dcd_stm32_ed_status;
	ULONG ux_dcd_stm32_ed_state;
	ULONG ux_dcd_stm32_ed_index;
	ULONG ux_dcd_stm32_ed_payload_length;
	ULONG ux_dcd_stm32_ed_transfer_status;
	ULONG ux_dcd_stm32_ed_ping_pong;
	ULONG ux_dcd_stm32_ed_type;
	ULONG ux_dcd_stm32_ed_direction;
	struct UX_SLAVE_ENDPOINT_STRUCT* ux_dcd_stm32_ed_endpoint;
} UX_DCD_STM32_ED;

/* Define USB STM32 DCD structure definition. */
typedef struct UX_DCD_STM32_STRUCT
{
	struct UX_SLAVE_DCD_STRUCT* ux_dcd_stm32_dcd_owner;
	struct UX_DCD_STM32_ED_STRUCT ux_dcd_stm32_ed[UX_DCD_STM32_MAX_ED];
	ULONG ux_dcd_stm32_base;
	ULONG ux_dcd_stm32_debug;
} UX_DCD_STM32;

/* Define USB STM32 DCD prototypes. */
UINT _ux_dcd_stm32_address_set(UX_DCD_STM32* dcd_stm32, ULONG address);
ULONG _ux_dcd_stm32_endpoint_register_address_get(UX_DCD_STM32_ED* ed);
UINT _ux_dcd_stm32_endpoint_create(UX_DCD_STM32* dcd_stm32, UX_SLAVE_ENDPOINT* endpoint);
UINT _ux_dcd_stm32_endpoint_destroy(UX_DCD_STM32* dcd_stm32, UX_SLAVE_ENDPOINT* endpoint);
UINT _ux_dcd_stm32_endpoint_reset(UX_DCD_STM32* dcd_stm32, UX_SLAVE_ENDPOINT* endpoint);
UINT _ux_dcd_stm32_endpoint_stall(UX_DCD_STM32* dcd_stm32, UX_SLAVE_ENDPOINT* endpoint);
UINT _ux_dcd_stm32_endpoint_status(UX_DCD_STM32* dcd_stm32, ULONG endpoint_index);

UINT _ux_dcd_stm32_frame_number_get(UX_DCD_STM32* dcd_stm32, ULONG* frame_number);

UINT _ux_dcd_stm32_function(UX_SLAVE_DCD* dcd, UINT function, VOID* parameter);
UINT _ux_dcd_stm32_initialize_complete(VOID);
VOID _ux_dcd_stm32_interrupt_handler(VOID);

VOID _ux_dcd_stm32_register_clear(UX_DCD_STM32* dcd_stm32, ULONG stm32_register, ULONG value);
ULONG _ux_dcd_stm32_register_read(UX_DCD_STM32* dcd_stm32, ULONG stm32_register);
VOID _ux_dcd_stm32_register_set(UX_DCD_STM32* dcd_stm32, ULONG stm32_register, ULONG value);
VOID _ux_dcd_stm32_register_write(UX_DCD_STM32* dcd_stm32, ULONG stm32_register, ULONG value);
UINT _ux_dcd_stm32_state_change(UX_DCD_STM32* dcd_stm32, ULONG state);

UINT _ux_dcd_stm32_transfer_callback(UX_DCD_STM32* dcd_stm32, UX_SLAVE_TRANSFER* transfer_request);
UINT _ux_dcd_stm32_transfer_request(UX_DCD_STM32* dcd_stm32, UX_SLAVE_TRANSFER* transfer_request);

UINT _ux_dcd_stm32_fifo_read(UX_DCD_STM32* dcd_stm32, ULONG endpoint_index, UCHAR* data_pointer,
		ULONG fifo_length);
UINT _ux_dcd_stm32_fifo_write(UX_DCD_STM32* dcd_stm32, ULONG endpoint_index, UCHAR* data_pointer,
		ULONG fifo_length, ULONG last_packet_flag);
UINT _ux_dcd_stm32_fifo_flush(UX_DCD_STM32* dcd_stm32, ULONG fifo_type, ULONG fifo_index);

UINT _ux_dcd_stm32_initialize(ULONG dcd_io, ULONG parameter);
VOID _ux_dcd_stm32_delay(ULONG usec);

#define ux_dcd_stm32_initialize                      _ux_dcd_stm32_initialize
#define ux_dcd_stm32_interrupt_handler               _ux_dcd_stm32_interrupt_handler

#endif
