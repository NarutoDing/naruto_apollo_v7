/* -*- esdcan-c -*-
 * FILE NAME cm.h
 *           copyright 2002-2017 by esd electronics gmbh
 *
 * BRIEF MODULE DESCRIPTION
 *
 */
/************************************************************************
 *
 *  Copyright (c) 1996 - 2017 by esd electronics gmbh
 *
 *  This software is copyrighted by and is the sole property of
 *  esd gmbh.  All rights, title, ownership, or other interests
 *  in the software remain the property of esd gmbh. This
 *  software may only be used in accordance with the corresponding
 *  license agreement.  Any unauthorized use, duplication, transmission,
 *  distribution, or disclosure of this software is expressly forbidden.
 *
 *  This Copyright notice may not be removed or modified without prior
 *  written consent of esd gmbh.
 *
 *  esd gmbh, reserves the right to modify this software without notice.
 *
 *  esd electronics gmbh                   Tel. +49-511-37298-0
 *  Vahrenwalder Strasse 207               Fax. +49-511-37298-68
 *  30165 Hannover                         http://www.esd.eu
 *  Germany                                sales@esd.eu
 *
 *************************************************************************/
/*! \file cm.h
 *  \brief Contains common CAN-message-structure (CM) and defines such as
 *  feature-flags, mode-flags. These defines are visible to the user,
 *  nevertheless: Dear user, please, use the defines in ntcan.h!
 *
 */

#ifndef __CM_H__
#define __CM_H__

#ifndef OSIF_KERNEL
#error "This file may be used in the kernel-context, only! Not for application-use!!!"
#endif

    /* Check if <boardrc.h> is included with the presence of the CARD_FEATURES macro */
#if !defined(CARD_FEATURES)
# error "Header <boardrc.h> has to be included BEFORE <cm.h> !!"
#endif

/* calculate the data length from a given frame length value */
#ifdef BOARD_CAN_FD
# define CM_LEN_MASK 0x9f
#else
# define CM_LEN_MASK 0x1f
#endif

/* command-flags for nuc_id_filter                                           */
#define FILTER_ON         0x00000000      /* enable flag                     */
#define FILTER_OFF        0x80000000      /* disable flag                    */

#define FILTER_DATA       0x00000001      /* enabled for queued data input   */
#define FILTER_RTR        0x00000002      /* enabled for queued rtr input    */
#define FILTER_OBJ        0x00000004      /* enabled for object data input   */
#define FILTER_OBJ_RTR    0x00000008      /* enabled for object rtr input    */
#define FILTER_DATA_FD    0x00000010      /* enabled for queued fd data input*/

#ifdef BOARD_CAN_FD
#define FILTER_ALL (FILTER_DATA | FILTER_RTR | FILTER_OBJ | FILTER_OBJ_RTR | FILTER_DATA_FD)
#else
#define FILTER_ALL (FILTER_DATA | FILTER_RTR | FILTER_OBJ | FILTER_OBJ_RTR)
#endif

/* Following is defined for the board files but DEPRECATED */
/* DEPRECATED BEGIN */
#define FILTER_DATA_ENABLE    FILTER_DATA
#define FILTER_RTR_ENABLE     FILTER_RTR
#define FILTER_OBJ_ENABLE     FILTER_OBJ
#define FILTER_OBJ_RTR_ENABLE FILTER_OBJ_RTR
#define FILTER_DISABLE        0x00000000
/* DEPRECATED END */

/* Driver flags (aka driver start parameter) used in node->mode */
#define DRIVER_PARAM_LOM                FEATURE_LOM
#define DRIVER_PARAM_SMART_DISCONNECT   FEATURE_SMART_DISCONNECT
#define DRIVER_PARAM_SMART_SUSPEND      0x01000000
#define DRIVER_PARAM_ESDACC_AUTOBAUD    0x02000000
#define DRIVER_PARAM_PCIE402_FORCE      0x04000000
#define DRIVER_PARAM_PXI_TRIG_INVERT    0x08000000
#define DRIVER_PARAM_ESDACC_TS_SOURCE   0x10000000
#define DRIVER_PARAM_I20_NO_FAST_MODE   0x20000000
#define DRIVER_PARAM_ESDACC_TS_MODE     0x20000000
#define DRIVER_PARAM_PLX_FIFO_MODE      0x40000000
#define DRIVER_PARAM_NO_MSI_MODE        0x40000000

/* Driver internal IOCTL codes */
#define ESDCAN_CTL_TIMESTAMP_GET         1
#define ESDCAN_CTL_TIMEST_FREQ_GET       2
#define ESDCAN_CTL_BAUDRATE_GET          3
#define ESDCAN_CTL_BAUDRATE_SET          4
#define ESDCAN_CTL_ID_FILTER             5
#define ESDCAN_CTL_BAUDRATE_AUTO         6
#define ESDCAN_CTL_BAUDRATE_BTR          7
#define ESDCAN_CTL_BUSLOAD_INTERVAL_GET  8
#define ESDCAN_CTL_BUSLOAD_INTERVAL_SET  9
#define ESDCAN_CTL_DEBUG                10
#define ESDCAN_CTL_BUS_STATISTIC_GET    11
#define ESDCAN_CTL_BUS_STATISTIC_RESET  12
#define ESDCAN_CTL_ERROR_COUNTER_GET    13
#define ESDCAN_CTL_BITRATE_DETAILS_GET  14
#define ESDCAN_CTL_SER_REG_READ         15
#define ESDCAN_CTL_SER_REG_WRITE        16
#define ESDCAN_CTL_RESET_CAN_ERROR_CNT  17
#define ESDCAN_CTL_EEI_CREATE           18
#define ESDCAN_CTL_EEI_DESTROY          19
#define ESDCAN_CTL_EEI_STATUS           20
#define ESDCAN_CTL_EEI_CONFIGURE        21
#define ESDCAN_CTL_EEI_START            22
#define ESDCAN_CTL_EEI_STOP             23
#define ESDCAN_CTL_EEI_TRIGGER_NOW      24
#define ESDCAN_CTL_TX_TS_WIN_SET        25
#define ESDCAN_CTL_TX_TS_WIN_GET        26
#define ESDCAN_CTL_TX_TS_TIMEOUT_SET    27
#define ESDCAN_CTL_TX_TS_TIMEOUT_GET    28
#define ESDCAN_CTL_BAUDRATE_X_GET       29
#define ESDCAN_CTL_BAUDRATE_X_SET       30
#define ESDCAN_CTL_CAN_INFO             31
#define ESDCAN_CTL_CAN_TDC_GET          32
#define ESDCAN_CTL_CAN_TDC_SET          33
#define ESDCAN_CTL_LIN_MASTER_SEL       34 
#define ESDCAN_CTL_HW_TIMESTAMP_GET     35
#define ESDCAN_CTL_HW_TIMESTAMP_GET_EX  36
#define ESDCAN_CTL_CAN_GET_TX_MESSAGES  37

typedef	union {
        UINT64 ul64[1];
        UINT32 ul32[2];
        VOID*  ptr;
} HOST_HND;


typedef struct _CMSCHED CMSCHED;
struct _CMSCHED
{
        UINT32  id;
        INT32   flags;
        OSIF_TS timeStart;
        OSIF_TS timeInterval;
        UINT32  countStart; /* Start value for counting*/
        UINT32  countStop;  /* Stop value for counting. After reaching this
                               value, the counter is loaded with the countStart value. */
};

typedef struct _CM CM;
struct _CM {
        UINT32        id;             /* can-id                                   */
        UINT8         len;            /* length of message: 0-8                   */
        UINT8         msg_lost;       /* count of lost rx-messages                */
        UINT8         reserved[1];    /* reserved                                 */
        UINT8         ecc;            /* ECC (marks "broken" frames)              */
#ifdef BOARD_CAN_FD
        UINT8         data[64];       /* 64 data-bytes                            */
#else
        UINT8         data[8];        /* 8 data-bytes                             */
#endif
        OSIF_TS       timestamp;      /* 64 bit timestamp                         */
        HOST_HND      host_hnd;
};

typedef struct _VERSION96 {
        UINT32        level;
        UINT32        revision;
        UINT32        build;
} VERSION96;

typedef struct _CARD_IRQ {
        OSIF_IRQ_HANDLER( *handler, context);
        VOID *context;
} CARD_IRQ;

/* Use this to terminate cardFlavours arrays */
#define CARD_IDENT_TERMINATE {{ NULL, NULL, NULL, {0, 0, 0, 0, 0, 0, 0} }}
/* Do not use these any more, just use the one above */
/* #define CARD_IDENT_PCI_TERMINATE {{ NULL, NULL, NULL, {0, 0, 0, 0, 0, 0, 0} }}       */
/* #define CARD_IDENT_RAW_TERMINATE {{ NULL, NULL, NULL }}                              */
/* fj todo remove usage of CARD_IDENT_USB_TERMINATE */
#define CARD_IDENT_USB_TERMINATE {{ NULL, NULL, NULL, {0, 0} }}

#define CARD_MAX_USB_ENDPOINTS      4       /* Devices may have up to 4 endpoints */

typedef union _CARD_IDENT {
        struct {
                CARD_IRQ    *irqs;
                UINT32      *spaces;
                const CHAR8 *name;
                struct {
                        UINT32   vendor;
                        UINT32   device;
                        UINT32   subVendor;
                        UINT32   subDevice;
                        UINT32   class;     /* For future use, init with 0    */
                        UINT32   classMask; /* For future use, init with 0    */
                        UINTPTR  misc;      /* For future use, init with NULL */
                } ids;
        } pci;
        struct {
                CARD_IRQ    *irqs;
                UINT32      *spaces;
                const CHAR8 *name;
        } raw;
        struct {
                CARD_IRQ    *irqs;
                UINT32      *spaces;
                const CHAR8 *name;
                struct {
                        UINT32   vendor;
                        UINT32   device;
                        UINT32   numEndpoints;
                        UINT32   endpoint[CARD_MAX_USB_ENDPOINTS];
                } desc;
        } usb;
        struct { /* This part needs to be identical for all kinds of boards */
                CARD_IRQ    *irqs;
                UINT32      *spaces;
                const CHAR8 *name;
        } all;
} CARD_IDENT;

#define MAKE_VERSION(l,r,b) (UINT16)(((l) << 12) | ((r) << 8) | ((b) << 0))

#endif  /* #ifndef __CM_H__ */
