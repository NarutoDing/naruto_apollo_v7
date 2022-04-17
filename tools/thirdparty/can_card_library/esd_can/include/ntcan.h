/**************************************************************************
*                                                                         *
* ntcan.h -- NTCAN-API procedure declarations and constant definitions    *
*                                                                         *
* Copyright (c) 1997 - 2020, esd electronics gmbh. All rights reserved.   *
*                                                                         *
**************************************************************************/
#pragma once

#ifndef _NTCAN_H_
#define _NTCAN_H_

/* ******************************************** */
/* ----------- Revision information ----------- */
/* Automatically inserted, don't edit template! */
/* SVN File $Revision: 16772 $ */
/* Released with libntcan.so.4.2.3 */
/* ------------  end template ------------      */
/* ******************************************** */

   /*
    * For VS2005 and later we use intrinsics but some VS versions fail
    * if the include of <intrin.h> is inside an extern "C" declaration
    */
#if defined(_MSC_VER) && (_MSC_VER >= 1400) && !defined(__BUILDMACHINE__)
# include <intrin.h>
#endif

#ifdef __cplusplus
extern "C" {
#endif

#if defined(_WIN32)
    /* Include for Windows, RTX/RTX64, RTOS-32 or LabVIEW */
# include <windows.h>
#define NTCAN_BOOL  BOOL
# if defined(__LABVIEW__)
#  include <visa.h>
#  include <ansi_c.h>
#  include <utility.h>
#  undef TRUE   // TODO Check this!!!!
#  undef FALSE
#  define TRUE  0
#  define FALSE -1
# endif /* of __LABVIEW__ */
# if defined(__MINGW32__) || (defined(_MSC_VER) && (_MSC_VER >= 1800))
#  include <stdint.h>      /* Include stdint.h if available */
# endif
# if !defined(EXPORT)
#  define EXPORT __declspec (dllexport)    /* Macro to export from DLL */
# endif
# if !defined(CALLTYPE)
#  define CALLTYPE __cdecl
# endif
# if defined(_MSC_VER) && !defined(NTCAN_NO_AUTOLINK)
#  if defined(UNDER_RTSS)
    /* RTX / RTX64 */
#   pragma comment(lib,"ntcan_rtss.lib")  /* Import LIB as COFF (32-/64-bit) */
#  elif defined(RTOS32)
    /* RTOS32 */
#  else
#   pragma comment(lib,"ntcan.lib")       /* Import LIB as COFF (32-/64-bit) */
#  endif
# elif defined(__BORLANDC__) && !defined(NTCAN_NO_AUTOLINK)
#  if defined(__BORLANDC__) && defined(__clang__)
#   pragma comment(lib,"ntcan")           /* Import LIB as OMF (32-bit) or ELF (64-bit) */
#  else
#   pragma comment(lib,"ntcan.lib")       /* Import LIB as OMF (32-bit) */
#  endif
# endif /* of _MSC_VER */
# if !defined(UNDER_RTSS) && !defined(RTOS32) && !defined(__LABVIEW__)
#  if (__GNUC__ >= 7)   /* Silence -Wcast-function-type by an intermediate cast */
#   define NTCAN_DLSYM(hnd, name)    (void *)GetProcAddress(hnd, name)
#  else
#   define NTCAN_DLSYM(hnd, name)    GetProcAddress(hnd, name)
#  endif
# endif
#elif defined (__QNX__) || defined(__linux__)
    /* Includes for QNX Neutrino and Linux */
# include <errno.h>
# include <stdint.h>
# include <dlfcn.h>
# define NTCAN_BOOL int32_t
# define NTCAN_DLSYM(hnd, name)     dlsym(hnd, name)
#elif defined(__Lynx__)
    /* Includes for LynxOS */
# include <errno.h>
# include <stdint.h>
#elif defined(__VXWORKS__)
# include <vxWorks.h>
# include <errno.h>
#else
# error "Unsupported NTCAN platform"
#endif /* of _WIN32 */

/*
 * Define empty EXPORT and CALLTYPE macros if not defined platform specific
 */
#ifndef EXPORT
# define EXPORT
#endif

#ifndef CALLTYPE
# define CALLTYPE
#endif

/*
 * Macros for compiler warnings if obsolete API functions are used.
 * You can prevent the warnings by defining _NTCAN_OBSOLETE_NO_WARNINGS before
 * the NTCAN header is included.
 */
#if defined(_MSC_VER) && _MSC_VER >= 1300
# if _MSC_FULL_VER >= 140050320
#  define _NTCAN_DEPRECATE_TEXT(_Text) __declspec(deprecated(_Text))
# else
#  define _NTCAN_DEPRECATE_TEXT(_Text) __declspec(deprecated)
# endif
# ifndef _NTCAN_OBSOLETE
#  define _NTCAN_OBSOLETE(_NewItem) \
         _NTCAN_DEPRECATE_TEXT("This function has been superceded by newer" \
                               "library functionality. Consider using "     \
                               "#_NewItem instead. See API manual for details.")
# endif /* of !defined(_NTCAN_OBSOLETE) */
#endif /* of if defined(_MSC_VER) && _MSC_VER >= 1300 */

#if ((__GNUC__ > 2) || (__GNUC__ > 2) && (__GNUC_MINOR__ >= 1))
# define _NTCAN_GCCATTR_DEPRECATED __attribute__((deprecated))
#endif

#ifdef _NTCAN_OBSOLETE_NO_WARNINGS
# undef _NTCAN_OBSOLETE
# undef _NTCAN_GCCATTR_DEPRECATED
#endif

#ifndef _NTCAN_OBSOLETE
# define _NTCAN_OBSOLETE(_NewItem)
#endif

#ifndef _NTCAN_GCCATTR_DEPRECATED
# define _NTCAN_GCCATTR_DEPRECATED
#endif

/*
 * Define NTCAN_INLINE as compiler specific keyword to inline code
 */
#if defined(_MSC_VER)
# define NTCAN_INLINE static __inline      /* MSC */
#elif defined (__GNUC__)
# define NTCAN_INLINE static __inline__    /* MINGW, GCC */
#else
# define NTCAN_INLINE
#endif

/*
 ******************************************************************************
 *                             NTCAN DEFINES                                  *
 ******************************************************************************
 */
#define NTCAN_EV_BASE                   0x40000000
#define NTCAN_EV_USER                   0x40000080
#define NTCAN_EV_LAST                   0x400000FF

#define NTCAN_EV_CAN_ERROR              NTCAN_EV_BASE
#define NTCAN_EV_BAUD_CHANGE            (NTCAN_EV_BASE + 0x1)
#define NTCAN_EV_CAN_ERROR_EXT          (NTCAN_EV_BASE + 0x2)
#define NTCAN_EV_BUSLOAD                (NTCAN_EV_BASE + 0x3)

/*
 * Handle specific flags in canOpen()
 */
#define NTCAN_MODE_NO_RTR               0x00000010  /* Ignore RTR frames      */
#define NTCAN_MODE_NO_DATA              0x00000020  /* Ignore data frames     */
#define NTCAN_MODE_NO_INTERACTION       0x00000100  /* No interaction         */
#define NTCAN_MODE_MARK_INTERACTION     0x00000200  /* Mark interaction       */
#define NTCAN_MODE_LOCAL_ECHO           0x00000400  /* Local echo             */
#define NTCAN_MODE_TIMESTAMPED_TX       0x00020000  /* Timestamped TX         */
#define NTCAN_MODE_FD                   0x00040000  /* Enable CAN-FD support  */
#define NTCAN_MODE_LIN                  0x08000000  /* MARK as LIN handle     */
#define NTCAN_MODE_OBJECT               0x10000000  /* Open in Rx object mode */
#define NTCAN_MODE_OVERLAPPED           0x20000000  /* Overlapped I/O (Win)   */

/* Queue size defines/limits in canOpen() */
#if defined(__linux__) || defined (__VXWORKS__) || defined(__LABVIEW__)
# define NTCAN_MAX_TX_QUEUESIZE         2047
# define NTCAN_MAX_RX_QUEUESIZE         2047
#elif defined (_WIN32)
# define NTCAN_MAX_TX_QUEUESIZE         16383
# define NTCAN_MAX_RX_QUEUESIZE         16383
#else
# define NTCAN_MAX_TX_QUEUESIZE         0x4000
# define NTCAN_MAX_RX_QUEUESIZE         0x4000
#endif
#define NTCAN_NO_QUEUE                  -1

/* Logical net numbers from 0..255 in canOpen() for parameter 'net' */
#define NTCAN_MAX_NETS                  255

/* Flags in can-ids */
#define NTCAN_20B_BASE                  0x20000000

/* Flags in CMSG / CMSG_T / CMSG_X member 'len'  */
#define NTCAN_RTR                       0x10     /* CAN message is RTR       */
                                                 /*  -> NTCAN_FD bit not set */
#define NTCAN_NO_BRS                    0x10     /* CAN message without BRS  */
                                                 /*  -> NTCAN_FD bit set     */
#define NTCAN_NO_DATA                   0x20     /* No updated data          */
                                                 /*  -> Object mode handle   */
#define NTCAN_INTERACTION               0x20     /* Interaction data         */
                                                 /*  -> FIFO mode handle     */
#define NTCAN_FD                        0x80     /* Frame is CAN-FD message  */

/* Value for CMSG_X, CMSG_T, CMSG_X member 'esi'  */
#define NTCAN_ESI_FD_ERROR_PASSIVE      0xFF     /* Tx node is Error Passive  */

/* Defines for canSetBaudrate() / canGetBaudrate() */
#define NTCAN_USER_BAUDRATE             0x80000000  /* Configure BTR register     */
#define NTCAN_LISTEN_ONLY_MODE          0x40000000  /* Configure listen only mode */
#define NTCAN_USER_BAUDRATE_NUM         0x20000000  /* Numerical baudrate         */
#define NTCAN_SELF_TEST_MODE            0x10000000  /* Configure self test mode   */
#define NTCAN_AUTOBAUD                  0x00FFFFFE  /* Auto baudrate detection    */
#define NTCAN_BAUD_FD                   0x00FFFFFD  /* CAN FD baudrate            */
#define NTCAN_NO_BAUDRATE               0x7FFFFFFF  /* No baudrate configured     */

/*
 * Predefined CiA-recommended baudrates for canSetBaudrate() / canGetBaudrate()
 * of the ESD baudrate table
 */
#define NTCAN_BAUD_1000                0x00
#define NTCAN_BAUD_800                 0x0E
#define NTCAN_BAUD_500                 0x02
#define NTCAN_BAUD_250                 0x04
#define NTCAN_BAUD_125                 0x06
#define NTCAN_BAUD_100                 0x07
#define NTCAN_BAUD_50                  0x09
#define NTCAN_BAUD_20                  0x0B
#define NTCAN_BAUD_10                  0x0D

/*
 * Predefined CAN bit rates for the data phase of CAN FD communication
 */
#define NTCAN_BAUD_10000               0x15
#define NTCAN_BAUD_8000                0x14
#define NTCAN_BAUD_5000                0x13
#define NTCAN_BAUD_4000                0x12
#define NTCAN_BAUD_2000                0x11

/*
 * Board status returned in CAN_IF_STATUS and NTCAN_INFO
 */
#define NTCAN_BSTATUS_OK                0x0000
#define NTCAN_BSTATUS_NEED_FW_UPDATE    0x0001
#define NTCAN_BSTATUS_HW_ERROR          0x0002

/*
 * Flags for scheduling mode
 */
#define NTCAN_SCHED_FLAG_EN            0x00000000 /* ID is enabled          */
#define NTCAN_SCHED_FLAG_DIS           0x00000002 /* ID is disabled         */
#define NTCAN_SCHED_FLAG_REL           0x00000000 /* Start time is relative */
#define NTCAN_SCHED_FLAG_ABS           0x00000001 /* Start time is absolute */
#define NTCAN_SCHED_FLAG_INC8          0x00000100 /*  8 Bit incrementer     */
#define NTCAN_SCHED_FLAG_INC16         0x00000200 /* 16 Bit incrementer     */
#define NTCAN_SCHED_FLAG_INC32         0x00000300 /* 32 Bit incrementer     */
#define NTCAN_SCHED_FLAG_DEC8          0x00000400 /*  8 Bit decrementer     */
#define NTCAN_SCHED_FLAG_DEC16         0x00000500 /* 16 Bit decrementer     */
#define NTCAN_SCHED_FLAG_DEC32         0x00000600 /* 32 Bit decrementer     */
#define NTCAN_SCHED_FLAG_OFS0          0x00000000 /* Counter at offset 0    */
#define NTCAN_SCHED_FLAG_OFS1          0x00001000 /* Counter at offset 1    */
#define NTCAN_SCHED_FLAG_OFS2          0x00002000 /* Counter at offset 2    */
#define NTCAN_SCHED_FLAG_OFS3          0x00003000 /* Counter at offset 3    */
#define NTCAN_SCHED_FLAG_OFS4          0x00004000 /* Counter at offset 4    */
#define NTCAN_SCHED_FLAG_OFS5          0x00005000 /* Counter at offset 5    */
#define NTCAN_SCHED_FLAG_OFS6          0x00006000 /* Counter at offset 6    */
#define NTCAN_SCHED_FLAG_OFS7          0x00007000 /* Counter at offset 7    */

/*
 * CAN controller types returned with:
 *     canIoctl(NTCAN_IOCTL_GET_CTRL_STATUS)
 *     canIoctl(NTCAN_IOCTL_GET_BITRATE_DETAILS)
 *     canIoctl(NTCAN_IOCTL_GET_INFO)
 */
#define NTCAN_CANCTL_SJA1000     0x00  /* NXP SJA1000 / 82C200               */
#define NTCAN_CANCTL_I82527      0x01  /* Intel I82527                       */
#define NTCAN_CANCTL_FUJI        0x02  /* Fujitsu MBxxxxx MCU                */
#define NTCAN_CANCTL_LPC         0x03  /* NXP LPC2xxx / LPC17xx MCU          */
#define NTCAN_CANCTL_MSCAN       0x04  /* Freescale MCU (MSCAN)              */
#define NTCAN_CANCTL_ATSAM       0x05  /* Atmel ARM CPU                      */
#define NTCAN_CANCTL_ESDACC      0x06  /* esd Advanced CAN Core              */
#define NTCAN_CANCTL_STM32       0x07  /* ST STM32Fxxx MCU (bxCAN)           */
#define NTCAN_CANCTL_CC770       0x08  /* Bosch CC770 (82527 compatible)     */
#define NTCAN_CANCTL_SPEAR       0x09  /* ST SPEAr320 (C_CAN)                */
#define NTCAN_CANCTL_FLEXCAN     0x0A  /* Freescale iMX MCU (FlexCAN)        */
#define NTCAN_CANCTL_SITARA      0x0B  /* TI AM335x (Sitara) MCU (D_CAN)     */
#define NTCAN_CANCTL_MCP2515     0x0C  /* Microchip MCP2515                  */
#define NTCAN_CANCTL_MCAN        0x0D  /* Bosch IP Core (M_CAN)              */

/*
 * CAN transceiver types returned with canIoctl(NTCAN_IOCTL_GET_INFO)
 */
#define NTCAN_TRX_PCA82C251      0x00  /* NXP PCA82C251                      */
#define NTCAN_TRX_SN65HVD251     0x01  /* TI SN65HVD251                      */
#define NTCAN_TRX_SN65HVD265     0x02  /* TI SN65HVD265                      */
#define NTCAN_TRX_MCP2561FD      0x03  /* Microchip MCP2561FD                */
#define NTCAN_TRX_TCAN1051G      0x04  /* TI TCAN1051G                       */

/* CAN baudrate flags
 * (returned by canIoctl(NTCAN_IOCTL_GET_BITRATE_DETAILS),
 *  see NTCAN_BITRATE structure (flags)) */
#define NTCAN_BITRATE_FLAG_SAM  0x00000001 /* Triple sampling */

/*
 * CAN FD Transmit Delay Compensation (TDC) values for NTCAN_IOCTL_XXX_FD_TDC
 */
 #define NTCAN_TDC_MODE_AUTO        0
 #define NTCAN_TDC_MODE_MANUAL      1
 #define NTCAN_TDC_MODE_RESERVED    2
 #define NTCAN_TDC_MODE_OFF         3

/*
 * Error class in the Error Code Capture (ECC) of struct EV_CAN_ERROR_EXT
 * for SJA1000 and ESDACC based hardware.
 */
#define NTCAN_ECC_CLASS_BIT_ERROR           0x00    /* Only TX      */
#define NTCAN_ECC_CLASS_FORM_ERROR          0x40    /* Form error   */
#define NTCAN_ECC_CLASS_STUFF_ERROR         0x80    /* Stuff error  */
#define NTCAN_ECC_CLASS_OTHER_ERROR         0xC0    /* CRC Error    */

/*
 * I/O direction in the Error Code Capture (ECC) of struct EV_CAN_ERROR_EXT
 * for SJA1000 and ESDACC based hardware.
 */
#define NTCAN_ECC_DIR_RX                    0x20    /* Rx error      */
#define NTCAN_ECC_DIR_TX                    0x00    /* Tx error      */

/*
 * Error details in the Error Code Capture (ECC) of struct EV_CAN_ERROR_EXT
 * usually the position in the bit stream of the CAN frame for SJA1000 and
 * ESDACC based hardware.
 */
#define NTCAN_ECC_DETAIL_SOF                0x03
#define NTCAN_ECC_DETAIL_ID28_TO_ID21       0x02
#define NTCAN_ECC_DETAIL_SRTR               0x04
#define NTCAN_ECC_DETAIL_IDE                0x05
#define NTCAN_ECC_DETAIL_ID20_TO_ID18       0x06
#define NTCAN_ECC_DETAIL_ID17_TO_ID13       0x07
#define NTCAN_ECC_DETAIL_CRC                0x08
#define NTCAN_ECC_DETAIL_RES0               0x09
#define NTCAN_ECC_DETAIL_DATA               0x0A
#define NTCAN_ECC_DETAIL_DLC                0x0B
#define NTCAN_ECC_DETAIL_RTR                0x0C
#define NTCAN_ECC_DETAIL_RES1               0x0D
#define NTCAN_ECC_DETAIL_ID4_TO_ID0         0x0E
#define NTCAN_ECC_DETAIL_ID12_TO_ID5        0x0F
#define NTCAN_ECC_DETAIL_ACTIVE_ERR_FLAG    0x11
#define NTCAN_ECC_DETAIL_INTERMISSION       0x12
#define NTCAN_ECC_DETAIL_TOLERATE_DOM_BITS  0x13
#define NTCAN_ECC_DETAIL_FD_STUFF_COUNT     0x14
#define NTCAN_ECC_DETAIL_PASSIVE_ERR_FLAG   0x16
#define NTCAN_ECC_DETAIL_ERROR_DELIM        0x17
#define NTCAN_ECC_DETAIL_CRC_DELIM          0x18
#define NTCAN_ECC_DETAIL_ACK_SLOT           0x19
#define NTCAN_ECC_DETAIL_EOF                0x1A
#define NTCAN_ECC_DETAIL_ACK_DELIM          0x1B
#define NTCAN_ECC_DETAIL_OVERLOAD           0x1C
#define NTCAN_ECC_DETAIL_FD_RES0            0x1D
#define NTCAN_ECC_DETAIL_FD_BRS             0x1E
#define NTCAN_ECC_DETAIL_FD_ESI             0x1F


/*
 ******************************************************************************
 *                             NTCAN RETURN CODES                             *
 ******************************************************************************
 */

#if defined(_WIN32)
    /* Windows, RTX/RTX64 or RTOS-32 */
# define NTCAN_ERRNO_BASE               0xE0000000

# define NTCAN_SUCCESS                  ERROR_SUCCESS
# define NTCAN_INVALID_PARAMETER        ERROR_INVALID_PARAMETER
# define NTCAN_INVALID_HANDLE           ERROR_INVALID_HANDLE
# define NTCAN_IO_INCOMPLETE            ERROR_IO_INCOMPLETE
# define NTCAN_IO_PENDING               ERROR_IO_PENDING
# define NTCAN_NET_NOT_FOUND            ERROR_FILE_NOT_FOUND
# define NTCAN_INSUFFICIENT_RESOURCES   ERROR_NO_SYSTEM_RESOURCES
# define NTCAN_OPERATION_ABORTED        ERROR_OPERATION_ABORTED
# define NTCAN_WRONG_DEVICE_STATE       ERROR_NOT_READY
# define NTCAN_HANDLE_FORCED_CLOSE      ERROR_HANDLE_EOF
# define NTCAN_NOT_IMPLEMENTED          ERROR_INVALID_FUNCTION
# define NTCAN_NOT_SUPPORTED            ERROR_NOT_SUPPORTED
#elif defined (__LABVIEW__)
    /* LabVIEW */
# define NTCAN_ERRNO_BASE               0x01000000

# define NTCAN_SUCCESS                  VI_SUCCCESS
#define NTCAN_INVALID_PARAMETER         VI_ERROR_INV_PARAMETER
#define NTCAN_INVALID_HANDLE            VI_ERROR_INV_HNDLR_REF
#define NTCAN_IO_INCOMPLETE             VI_ERROR_IO
#define NTCAN_IO_PENDING                VI_ERROR_IO
#define NTCAN_NET_NOT_FOUND             VI_ERROR_FILE_ACCESS
#define NTCAN_INSUFFICIENT_RESOURCES    VI_ERROR_RSRC_NFOUND
#define NTCAN_OPERATION_ABORTED         VI_ERROR_TMO
  /* #define NTCAN_WRONG_DEVICE_STATE   not reasonable under LabVIEW */
#define NTCAN_HANDLE_FORCED_CLOSE       VI_ERROR_HNDLR_NINSTALLED
#define NTCAN_NOT_IMPLEMENTED           VI_ERROR_NIMPL_OPER
#define NTCAN_NOT_SUPPORTED             VI_ERROR_NSUP_OPER
#elif defined (__QNX__)
    /* QNX Neutrino */
# define NTCAN_ERRNO_BASE               0x00000100
# define NTCAN_SUCCESS                  0
# define NTCAN_INVALID_PARAMETER        EINVAL
# define NTCAN_INVALID_HANDLE           EBADF
  /* #define NTCAN_IO_INCOMPLETE          not reasonable under QNX */
  /* #define NTCAN_IO_PENDING             not reasonable under QNX */
# define NTCAN_NET_NOT_FOUND            ENOENT
# define NTCAN_INSUFFICIENT_RESOURCES   ENOMEM
# define NTCAN_OPERATION_ABORTED        EINTR
# define NTCAN_NOT_IMPLEMENTED          ENOTTY /* Converted from ENOSYS in driver */
# define NTCAN_NOT_SUPPORTED            ENOTSUP
#elif defined (__linux__)
    /* Linux */
# define NTCAN_ERRNO_BASE               0x00000100

# define NTCAN_SUCCESS                  0
# define NTCAN_INVALID_PARAMETER        EINVAL
# define NTCAN_INVALID_HANDLE           EBADFD
  /* #define NTCAN_IO_INCOMPLETE          not reasonable under Linux */
  /* #define NTCAN_IO_PENDING             not reasonable under Linux */
# define NTCAN_NET_NOT_FOUND            ENODEV
# define NTCAN_INSUFFICIENT_RESOURCES   ENOMEM
# define NTCAN_OPERATION_ABORTED        EINTR
# define NTCAN_NOT_IMPLEMENTED          ENOSYS
#elif defined(__Lynx__)
    /* LynxOS */
# define NTCAN_ERRNO_BASE               0x000001000

# define NTCAN_SUCCESS                  0
# define NTCAN_INVALID_PARAMETER        EINVAL
# define NTCAN_INVALID_HANDLE           EBADF
  /* #define NTCAN_IO_INCOMPLETE          not reasonable under LynxOS */
  /* #define NTCAN_IO_PENDING             not reasonable under LynxOS */
# define NTCAN_NET_NOT_FOUND            ENOENT
# define NTCAN_INSUFFICIENT_RESOURCES   ENOMEM
# define NTCAN_OPERATION_ABORTED        EINTR
# define NTCAN_WRONG_DEVICE_STATE       EPIPE
# define NTCAN_HANDLE_FORCED_CLOSE      ENOSPC
# define NTCAN_NOT_IMPLEMENTED          ENOTTY
# define NTCAN_NOT_SUPPORTED            ENOSYS
#elif defined(__VXWORKS__)
    /* VxWorks */
# define NTCAN_ERRNO_BASE               0x00001000

# define NTCAN_INVALID_PARAMETER        EINVAL
# define NTCAN_INVALID_HANDLE           EBADF
  /* #define NTCAN_IO_INCOMPLETE          not reasonable under VxWorks */
  /* #define NTCAN_IO_PENDING             not reasonable under VxWorks */
# define NTCAN_NET_NOT_FOUND            ENODEV
# define NTCAN_INSUFFICIENT_RESOURCES   ENOMEM
# define NTCAN_OPERATION_ABORTED        ECANCELED
# define NTCAN_NOT_IMPLEMENTED          ENOSYS
# define NTCAN_NOT_SUPPORTED            ENOTSUP

#endif /* of _WIN32 */

    /* Return values mapped to NTCAN specific error codes */
#define NTCAN_RX_TIMEOUT                (NTCAN_ERRNO_BASE + 1)
#define NTCAN_TX_TIMEOUT                (NTCAN_ERRNO_BASE + 2)
/* #define NTCAN_RESERVED               (NTCAN_ERRNO_BASE + 3) */
#define NTCAN_TX_ERROR                  (NTCAN_ERRNO_BASE + 4)
#define NTCAN_CONTR_OFF_BUS             (NTCAN_ERRNO_BASE + 5)
#define NTCAN_CONTR_BUSY                (NTCAN_ERRNO_BASE + 6)
#define NTCAN_CONTR_WARN                (NTCAN_ERRNO_BASE + 7)
/* #define NTCAN_OLDDATA                (NTCAN_ERRNO_BASE + 8) is obsolete and never returned by drivers 3.x ff. */
#define NTCAN_NO_ID_ENABLED             (NTCAN_ERRNO_BASE + 9)
#define NTCAN_ID_ALREADY_ENABLED        (NTCAN_ERRNO_BASE + 10)
#define NTCAN_ID_NOT_ENABLED            (NTCAN_ERRNO_BASE + 11)
/* #define NTCAN_RESERVED               (NTCAN_ERRNO_BASE + 12) */
#define NTCAN_INVALID_FIRMWARE          (NTCAN_ERRNO_BASE + 13)
#define NTCAN_MESSAGE_LOST              (NTCAN_ERRNO_BASE + 14)
#define NTCAN_INVALID_HARDWARE          (NTCAN_ERRNO_BASE + 15)
#define NTCAN_PENDING_WRITE             (NTCAN_ERRNO_BASE + 16)
#define NTCAN_PENDING_READ              (NTCAN_ERRNO_BASE + 17)
#define NTCAN_INVALID_DRIVER            (NTCAN_ERRNO_BASE + 18)
#ifndef NTCAN_WRONG_DEVICE_STATE
# define NTCAN_WRONG_DEVICE_STATE       (NTCAN_ERRNO_BASE + 19)
#endif
#ifndef NTCAN_HANDLE_FORCED_CLOSE
# define NTCAN_HANDLE_FORCED_CLOSE      (NTCAN_ERRNO_BASE + 20)
#endif
#ifndef NTCAN_NOT_SUPPORTED
# define NTCAN_NOT_SUPPORTED            (NTCAN_ERRNO_BASE + 21)
#endif
#define NTCAN_CONTR_ERR_PASSIVE         (NTCAN_ERRNO_BASE + 22)
#define NTCAN_ERROR_NO_BAUDRATE         (NTCAN_ERRNO_BASE + 23)
#define NTCAN_ERROR_LOM                 (NTCAN_ERRNO_BASE + 24)
#define NTCAN_NO_CAN_CAPABILITY         (NTCAN_ERRNO_BASE + 25)
#define NTCAN_NO_LIN_CAPABILITY         (NTCAN_ERRNO_BASE + 26)

#define NTCAN_SOCK_CONN_TIMEOUT         (NTCAN_ERRNO_BASE + 0x80)
#define NTCAN_SOCK_CMD_TIMEOUT          (NTCAN_ERRNO_BASE + 0x81)
#define NTCAN_SOCK_HOST_NOT_FOUND       (NTCAN_ERRNO_BASE + 0x82)

/*
 ******************************************************************************
 *                             NTCAN MACROS                                   *
 ******************************************************************************
 */

    /* Macros to decode the 32-bit boardstatus of CAN_IF_STATUS */
#define NTCAN_GET_CTRL_TYPE(boardstatus)     (((boardstatus) >> 24) & 0xFF)
#define NTCAN_GET_BOARD_STATUS(boardstatus)  ((boardstatus) & 0xFFFF)

    /* Macros for parameter len of CMSG / CMSG_T / CMSG_X structure */
#define NTCAN_DLC(len)               ((len) & 0x0F)
#define NTCAN_DLC_AND_TYPE(len)      ((len) & (0x0F | NTCAN_RTR))
#define NTCAN_IS_RTR(len)            (((len) & (NTCAN_FD | NTCAN_RTR)) == NTCAN_RTR)
#define NTCAN_IS_INTERACTION(len)    ((len) & NTCAN_INTERACTION)
#define NTCAN_IS_FD(len)             ((len) & NTCAN_FD)
#define NTCAN_IS_FD_WITHOUT_BRS(len) (((len) & (NTCAN_FD | NTCAN_NO_BRS)) == \
                                               (NTCAN_FD | NTCAN_NO_BRS))
#define NTCAN_LEN_TO_DATASIZE(len)    _canLenToDataSize((uint8_t)(len))

#define NTCAN_DATASIZE_TO_DLC(dataSize) _canDataSizeToDLC((dataSize))

    /* Macros for parameter id of CMSG / CMSG_T / CMSG_X structure */
#define NTCAN_ID(id)                 ((id) & 0x1FFFFFFF)
#define NTCAN_IS_EFF(id)             ((id) & NTCAN_20B_BASE)
#define NTCAN_IS_EVENT(id)           ((id) & NTCAN_EV_BASE)

    /* Macros to build/decode the 32-bit CAN FD TDC IOCTL values */
#define NTCAN_GET_TDC_VALUE(val)    ((val) & 0x3F)
#define NTCAN_GET_TDC_OFFSET(val)   (((val) >> 16) & 0x3F)
#define NTCAN_GET_TDC_MODE(val)     (((val) >> 30) & 0x3)

#define NTCAN_SET_TDC(mode, offset) ((((mode) & 0x3) << 30) | \
                                     (((offset) & 0x3F) << 16))

    /* Macros to split ECC byte of struct EV_CAN_ERROR_EXT */
#define NTCAN_ECC_ERROR_CODE(ecc)           ((ecc) & 0xC0)
#define NTCAN_ECC_ERROR_DIRECTION(ecc)      ((ecc) & 0x20)
#define NTCAN_ECC_ERROR_DETAIL(ecc)         ((ecc) & 0x1F)

    /* Windows: Define POSIX data types if no <stdint.h> header was included */
#if ! defined(_STDINT_H ) && ! defined(_STDINT_H_INCLUDED) && ! defined(_STDINT)
# ifndef _WIN64
typedef unsigned char     uint8_t;
typedef signed   char     int8_t;
typedef unsigned short    uint16_t;
typedef signed   short    int16_t;
typedef unsigned int      uint32_t;
typedef signed   int      int32_t;
# else
typedef unsigned __int8   uint8_t;
typedef signed __int8     int8_t;
typedef unsigned __int16  uint16_t;
typedef signed __int16    int16_t;
typedef unsigned __int32  uint32_t;
typedef signed __int32    int32_t;
# endif /* of _WIN64 */
typedef unsigned __int64  uint64_t;
typedef signed __int64    int64_t;
#endif /* of _STDINT_H */

#if defined(__VXWORKS__)
    /*
     * uint64_t and int64_t are undefined before VxWorks 5.5.x
     *
     * Use the presence of UINT64_MAX to check if these types are already
     * defined in another header.
     */
# if !defined(_WRS_VXWORKS_MAJOR) && !defined(_WRS_VXWORKS_5_X)
#  if !defined (UINT64_MAX)
#   define UINT64_MAX  18446744073709551615ULL
#   if !defined (INT64_MAX)
#    define INT64_MAX  9223372036854775807LL
#   endif
typedef long long             int64_t;
typedef unsigned long long    uint64_t;
#  endif /* of !defined (UINT64_MAX) */
# endif /* of !defined(_WRS_VXWORKS_MAJOR) && !defined(_WRS_VXWORKS_5_X) */
#endif /* of __VXWORKS__ */

/*
 ******************************************************************************
 *                       NTCAN SIMPLE DATA TYPES                              *
 ******************************************************************************
 */
#if defined(_WIN32)
typedef DWORD             NTCAN_RESULT;
typedef HANDLE            NTCAN_HANDLE;
#define NTCAN_NO_HANDLE   ((NTCAN_HANDLE)INVALID_HANDLE_VALUE)
#else
typedef void              OVERLAPPED;
typedef int32_t           NTCAN_RESULT;
typedef int32_t           NTCAN_HANDLE;
#define NTCAN_NO_HANDLE   ((NTCAN_HANDLE)-1)
#endif


    /*
     *  Dear ntcan-user,
     *  we regret, that we were forced to change the name of our handle type.
     *  This had to be done to keep "inter-system" compatibility of your
     *  application sources, after a change in VxWorks 6.0. Please replace all
     *  occurrences of HANDLE with NTCAN_HANDLE in your application's source
     *  code.
     */
#if !defined(_WIN32) && !defined(NTCAN_CLEAN_NAMESPACE)
typedef int32_t HANDLE _NTCAN_GCCATTR_DEPRECATED;
#endif

/*
 ******************************************************************************
 *                     NTCAN COMPOUND DATA TYPES                              *
 ******************************************************************************
 */

#pragma pack(1)

typedef struct
{
    int32_t  id;          /* CAN-ID (11-/29-bit) or Event-ID        [Tx, Rx] */
    uint8_t  len;         /* Bit 0-3 = Data Length Code             [Tx, Rx] */
                          /* Bit 4   = RTR (Classical CAN)          [Tx, Rx] */
                          /*         = No_BRS (CAN FD)              [Tx, Rx] */
                          /* Bit 5   = No_Data (Object Mode)        [    Rx] */
                          /*         = Interaction Data (FIFO Mode)          */
                          /* Bit 6   = Reserved                     [Tx, Rx] */
                          /* Bit 7   = Type(CAN FD / Classical CAN) [Tx, Rx] */
    uint8_t  msg_lost;    /* Counter for lost Rx messages           [    Rx] */
    uint8_t  reserved[1]; /* Reserved for future use (set to 0)              */
    uint8_t  esi;         /* Error State Indicator (CAN FD)         [    Rx] */
    uint8_t  data[8];     /* 8 data-bytes                           [Tx, Rx] */
} CMSG;

typedef struct
{
    int32_t  id;          /* CAN-ID (11-/29-bit) or Event-ID        [Tx, Rx] */
    uint8_t  len;         /* Bit 0-3 = Data Length Code             [Tx, Rx] */
                          /* Bit 4   = RTR (Classical CAN)          [Tx, Rx] */
                          /*         = No_BRS (CAN FD)              [Tx, Rx] */
                          /* Bit 5   = No_Data (Object Mode)        [    Rx] */
                          /*         = Interaction Data (FIFO Mode)          */
                          /* Bit 6   = Reserved                     [Tx, Rx] */
                          /* Bit 7   = Type(CAN FD / Classical CAN) [Tx, Rx] */
    uint8_t  msg_lost;    /* Counter for lost Rx messages           [    Rx] */
    uint8_t  reserved[1]; /* Reserved for future use (set to 0)              */
    uint8_t  esi;         /* Error State Indicator (CAN FD)         [    Rx] */
    uint8_t  data[8];     /* 8 data-bytes                           [Tx, Rx] */
    uint64_t timestamp;   /* time stamp of this message             [Tx, Rx] */
} CMSG_T;

typedef struct
{
    int32_t  id;          /* CAN-ID (11-/29-bit) or Event-ID        [Tx, Rx] */
    uint8_t  len;         /* Bit 0-3 = Data Length Code             [Tx, Rx] */
                          /* Bit 4   = RTR (Classical CAN)          [Tx, Rx] */
                          /*         = No_BRS (CAN FD)              [Tx, Rx] */
                          /* Bit 5   = No_Data (Object Mode)        [    Rx] */
                          /*         = Interaction Data (FIFO Mode)          */
                          /* Bit 6   = Reserved                     [Tx, Rx] */
                          /* Bit 7   = Type(CAN FD / Classical CAN) [Tx, Rx] */
    uint8_t  msg_lost;    /* Counter for lost Rx messages           [    Rx] */
    uint8_t  reserved[1]; /* Reserved for future use (set to 0)              */
    uint8_t  esi;         /* Error State Indicator (CAN FD)         [    Rx] */
    uint8_t  data[64];    /* 64 data bytes                          [Tx, Rx] */
    uint64_t timestamp;   /* Timestamp of this message              [Tx, Rx] */
} CMSG_X;

typedef struct
{
    uint8_t     reserved1;      /* Reserved for future use                   */
    uint8_t     can_status;     /* CAN controller status                     */
    uint8_t     dma_stall;      /* DMA stall counter (HW dependent)          */
    uint8_t     ctrl_overrun;   /* Controller overruns                       */
    uint8_t     reserved3;      /* Reserved for future use                   */
    uint8_t     fifo_overrun;   /* Driver FIFO overruns                      */
} EV_CAN_ERROR;

typedef struct
{
    uint32_t    baud;           /* New NTCAN baudrate value                  */
    uint32_t    num_baud;       /* New numerical baudrate value (optional)   */
} EV_CAN_BAUD_CHANGE;

typedef union
{
    struct {
        uint8_t     status;     /* (SJA1000) CAN controller status           */
        uint8_t     ecc;        /* Error Capture Register                    */
        uint8_t     rec;        /* Rx Error Counter                          */
        uint8_t     tec;        /* Tx Error Counter                          */
    } sja1000;
    struct {
        uint8_t     status;     /* (ESDACC) CAN controller status            */
        uint8_t     ecc;        /* Error Capture Register                    */
        uint8_t     rec;        /* Rx Error Counter                          */
        uint8_t     tec;        /* Tx Error Counter                          */
        uint8_t     txstatus;   /* (ESDACC) CAN controller TX status         */
    } esdacc;
} EV_CAN_ERROR_EXT;

typedef struct
{
  int32_t       evid;          /* event-id: possible range:EV_BASE...EV_LAST */
  uint8_t       len;           /* length of message: 0-8                     */
  uint8_t       reserved[3];   /* reserved                                   */
  union
  {
    uint8_t            c[8];
    uint16_t           s[4];
    uint32_t           l[2];
    uint64_t           q;
    EV_CAN_ERROR       error;
    EV_CAN_BAUD_CHANGE baud_change;
    EV_CAN_ERROR_EXT   error_ext;
  } evdata;
} EVMSG;

typedef struct
{
  int32_t       evid;          /* event-id: possible range:EV_BASE...EV_LAST */
  uint8_t       len;           /* length of message: 0-8                     */
  uint8_t       reserved[3];   /* reserved                                   */
  union
  {
    uint8_t            c[8];
    uint16_t           s[4];
    uint32_t           l[2];
    uint64_t           q;
    EV_CAN_ERROR       error;
    EV_CAN_BAUD_CHANGE baud_change;
    EV_CAN_ERROR_EXT   error_ext;
  } evdata;
  uint64_t      timestamp;      /* time stamp of this message                */
} EVMSG_T;

typedef struct
{
    int32_t       evid;        /* Event-ID: possible range:EV_BASE...EV_LAST */
    uint8_t       len;         /* Length of message: 0..8 (0..64 for CAN-FD) */
    uint8_t       reserved[3]; /* Reserved                                   */
    union
    {
        uint8_t                 c[64];
        uint16_t                s[32];
        uint32_t                l[16];
        uint64_t                q[8];
        EV_CAN_ERROR            error;
        EV_CAN_BAUD_CHANGE      baud_change;
        EV_CAN_ERROR_EXT        error_ext;
    } evdata;
    uint64_t      timestamp;      /* time stamp of this message                */
} EVMSG_X;

typedef struct
{
  uint16_t hardware;           /* Hardware version                          */
  uint16_t firmware;           /* Firmware version (0 = N/A)                */
  uint16_t driver;             /* Driver version                            */
  uint16_t dll;                /* NTCAN library version                     */
  uint32_t boardstatus;        /* Hardware status                           */
  uint8_t  boardid[14];        /* Board ID string                           */
  uint16_t features;           /* Device/driver capability flags            */
} CAN_IF_STATUS;

typedef struct
{
  uint16_t hardware;           /* Hardware version                      */
  uint16_t firmware;           /* Firmware / FPGA version (0 = N/A)     */
  uint16_t driver;             /* Driver version                        */
  uint16_t dll;                /* NTCAN library version                 */
  uint32_t features;           /* Device/driver capability flags        */
  uint32_t serial;             /* Serial # (0 = N/A)                    */
  uint64_t timestamp_freq;     /* Timestamp frequency (in Hz, 1 = N/A)  */
  uint32_t ctrl_clock;         /* Frequency of CAN controller (in Hz)   */
  uint8_t  ctrl_type;          /* Controller type (NTCAN_CANCTL_XXX)    */
  uint8_t  base_net;           /* Base net number                       */
  uint8_t  ports;              /* Number of physical ports              */
  uint8_t  transceiver;        /* Transceiver type (NTCAN_TRX_XXX)      */
  uint16_t boardstatus;        /* Hardware status                       */
  uint16_t firmware2;          /* Second firmware version (0 = N/A)     */
  char     boardid[32];        /* Board ID string                       */
  char     serial_string[16];  /* Serial # as string                    */
  char     drv_build_info[64]; /* Build info of driver                  */
  char     lib_build_info[64]; /* Build info of library                 */
  uint16_t open_handle;        /* Number of open handle                 */
  uint8_t  reserved2[42];      /* Reserved for future use               */
} NTCAN_INFO;

typedef struct {
  uint32_t           std_data;            /* # of std CAN messages    */
  uint32_t           std_rtr;             /* # of std RTR requests    */
  uint32_t           ext_data;            /* # of ext CAN messages    */
  uint32_t           ext_rtr;             /* # of ext RTR requests    */
} NTCAN_FRAME_COUNT;

typedef struct
{
  uint64_t           timestamp;           /* Timestamp                     */
  NTCAN_FRAME_COUNT  rcv_count;           /* # of received frames          */
  NTCAN_FRAME_COUNT  xmit_count;          /* # of transmitted frames       */
  uint32_t           ctrl_ovr;            /* # of controller overruns      */
  uint32_t           fifo_ovr;            /* # of FIFO overflows           */
  uint32_t           err_frames;          /* # of error frames             */
  uint32_t           rcv_byte_count;      /* # of received bytes           */
  uint32_t           xmit_byte_count;     /* # of transmitted bytes        */
  uint32_t           aborted_frames;      /* # of aborted frames           */
  uint32_t           rcv_count_fd;        /* # of received FD frames       */
  uint32_t           xmit_count_fd;       /* # of transmitted FD frames    */
  uint64_t           bit_count;           /* # of received bits            */
} NTCAN_BUS_STATISTIC;

typedef struct
{
  uint8_t            rcv_err_counter;     /* Receive error counter         */
  uint8_t            xmit_err_counter;    /* Transmit error counter        */
  uint8_t            status;              /* CAN controller status         */
  uint8_t            type;                /* CAN controller type           */
} NTCAN_CTRL_STATE;

typedef struct
{
    uint32_t  baud;         /* value configured by user via canSetBaudrate()        */
                            /*  or NTCAN_BAUD_FD if canSetBaudrateX() was used      */
    uint32_t  valid;        /* validity of all _following_ infos                    */
                            /* (-1 = invalid, NTCAN_SUCCESS, NTCAN_NOT_IMPLEMENTED) */
    uint32_t  rate;         /* CAN nominal/arbitration bitrate in Bit/s             */
    uint32_t  clock;        /* Clock frequency of CAN controller                    */
    uint8_t   ctrl_type;    /* NTCAN_CANCTL_XXX defines                             */
    uint8_t   tq_pre_sp;    /* Number of time quantas before samplep. (SYNC + TSEG1)*/
    uint8_t   tq_post_sp;   /* Number of time quantas after samplepoint (TSEG2)     */
    uint8_t   sjw;          /* Synchronization jump width in time quantas (SJW)     */
    uint32_t  error;        /* Actual deviation of configured baudrate in (% * 100) */
    uint32_t  flags;        /* Baudrate flags (possibly ctrl. specific, e.g. SAM)   */
    uint32_t  rate_d;       /* CAN data phase bit rate in bit/s                     */
    uint8_t   tq_pre_sp_d;  /* Number of time quantas before samplepoint (DTSEG1)   */
    uint8_t   tq_post_sp_d; /* Number of time quantas past samplepoint (DTSEG2)     */
    uint8_t   sjw_d;        /* Syncronization jump width in time quantas (DSJW)     */
    uint8_t   mode;         /* NTCAN_BAUDRATE_MODE_XXX defines                      */
    uint32_t  reserved[1];  /* for future use                                       */
} NTCAN_BITRATE;

typedef struct
{
    uint32_t acr;           /* Acceptance Code Register */
    uint32_t amr;           /* Acceptance Mask Register */
    uint32_t idArea;        /* Filter type */
} NTCAN_FILTER_MASK;

/* Supported values for idArea in NTCAN_FILTER_MASK */
#define NTCAN_IDS_REGION_20A    0       /* Filter for 11-bit CAN frames */
#define NTCAN_IDS_REGION_20B    1       /* Filter for 29-bit CAN frames */
#define NTCAN_IDS_REGION_EV     2       /* Filter for NTCAN events      */

typedef struct
{
  int32_t  id;
  int32_t  flags;
  uint64_t time_start;
  uint64_t time_interval;
  uint32_t count_start; /* Start value for counting.                          */
  uint32_t count_stop;  /* Stop value for counting. After reaching this value,
                           the counter is loaded with the count_start value.  */
} CSCHED;

typedef struct
{
  uint64_t           timestamp;         /* Timestamp (for busload)          */
  uint64_t           timestamp_freq;    /* Timestamp frequency (for busload)*/
  uint32_t           num_baudrate;      /* Numerical baudrate (for busload) */
  uint32_t           flags;             /* Flags                            */
  uint64_t           busload_oldts;     /* <---+-- used internally, set to  */
  uint64_t           busload_oldbits;   /* <---+   zero on first call       */
  uint8_t            ctrl_type;         /* Controller type (for ext_error)  */
  uint8_t            reserved[7];       /* Reserved (7 bytes)               */
  uint32_t           reserved2[4];      /* Reserved (16 bytes)              */
} NTCAN_FORMATEVENT_PARAMS;

typedef struct {
    union {
        uint32_t idx;              /* esd bit rate table index              */
        uint32_t rate;             /* Numerical bit rate                    */
        uint32_t btr_ctrl;         /* BTR register (CAN Controller layout)  */
        struct {
            uint16_t brp;          /* Bit rate pre-scaler                   */
            uint16_t tseg1;        /* TSEG1 register                        */
            uint16_t tseg2;        /* TSEG2 register                        */
            uint16_t sjw;          /* SJW register                          */
        } btr;
    } u;
} NTCAN_BAUDRATE_CFG;

    /* Mode of NTCAN_BAUDRATE_X */
#define NTCAN_BAUDRATE_MODE_DISABLE          0      /* Remove from bus        */
#define NTCAN_BAUDRATE_MODE_INDEX            1      /* ESD (CiA) bit rate idx */
#define NTCAN_BAUDRATE_MODE_BTR_CTRL         2      /* BTR values (Controller)*/
#define NTCAN_BAUDRATE_MODE_BTR_CANONICAL    3      /* BTR values (Canonical) */
#define NTCAN_BAUDRATE_MODE_NUM              4      /* Numerical bit rate     */
#define NTCAN_BAUDRATE_MODE_AUTOBAUD         5      /* Autobaud               */

    /* Flags of NTCAN_BAUDRATE_X */
#define NTCAN_BAUDRATE_FLAG_FD     0x0001        /* Enable CAN FD Mode        */
#define NTCAN_BAUDRATE_FLAG_LOM    0x0002        /* Enable Listen Only mode   */
#define NTCAN_BAUDRATE_FLAG_STM    0x0004        /* Enable Self test mode     */
#define NTCAN_BAUDRATE_FLAG_TRS    0x0008        /* Enable Triple Sampling    */

typedef struct {
    uint16_t            mode;           /* Mode word                          */
    uint16_t            flags;          /* Control flags                      */
    uint32_t            reserved;       /* Reserved (set to 0)                */
    NTCAN_BAUDRATE_CFG  arb;            /* Bit rate during arbitration phase  */
    NTCAN_BAUDRATE_CFG  data;           /* Bit rate during data phase         */
} NTCAN_BAUDRATE_X;

#pragma pack()

/*
 * Interface/Driver feature flags
 */
#define NTCAN_FEATURE_FULL_CAN         (1<<0)  /* Full CAN controller                */
#define NTCAN_FEATURE_CAN_20B          (1<<1)  /* CAN 2.OB support                   */
#define NTCAN_FEATURE_DEVICE_NET       (1<<2)  /* Device net adapter                 */
#define NTCAN_FEATURE_CYCLIC_TX        (1<<3)  /* Cyclic Tx support                  */
#define NTCAN_FEATURE_TIMESTAMPED_TX   (1<<3)  /* SAME AS CYCLIC_TX, timestamped TX support */
#define NTCAN_FEATURE_RX_OBJECT_MODE   (1<<4)  /* Rx object mode support             */
#define NTCAN_FEATURE_TIMESTAMP        (1<<5)  /* Timestamp support                  */
#define NTCAN_FEATURE_LISTEN_ONLY_MODE (1<<6)  /* Listen-only-mode support           */
#define NTCAN_FEATURE_SMART_DISCONNECT (1<<7)  /* Go-from-bus-after-last-close       */
#define NTCAN_FEATURE_LOCAL_ECHO       (1<<8)  /* Interaction w. local echo          */
#define NTCAN_FEATURE_SMART_ID_FILTER  (1<<9)  /* Adaptive ID filter                 */
#define NTCAN_FEATURE_SCHEDULING       (1<<10) /* Scheduling feature                 */
#define NTCAN_FEATURE_DIAGNOSTIC       (1<<11) /* CAN bus diagnostic support         */
#define NTCAN_FEATURE_ERROR_INJECTION  (1<<12) /* esdACC error injection support     */
#define NTCAN_FEATURE_IRIGB            (1<<13) /* IRIG-B support                     */
#define NTCAN_FEATURE_PXI              (1<<14) /* Board supports backplane clock and */
                                               /* start trigger for timestamp        */
#define NTCAN_FEATURE_CAN_FD           (1<<15) /* CAN-FD support                     */
#define NTCAN_FEATURE_SELF_TEST        (1<<16) /* Self-test mode support             */
#define NTCAN_FEATURE_TRIPLE_SAMPLING  (1<<17) /* Triple sampling support            */
#define NTCAN_FEATURE_LIN              (1<<27) /* feature flag for LIN               */

/* Bus states delivered by status-event (NTCAN_EV_CAN_ERROR) and
*  canIoctl(NTCAN_IOCTL_GET_CTRL_STATUS)
*/
#define NTCAN_BUSSTATE_OK           0x00
#define NTCAN_BUSSTATE_WARN         0x40
#define NTCAN_BUSSTATE_ERRPASSIVE   0x80
#define NTCAN_BUSSTATE_BUSOFF       0xC0

/*
 * IOCTL codes for canIoctl()
 */
#define NTCAN_IOCTL_FLUSH_RX_FIFO         0x0001   /* Flush Rx FIFO           */
#define NTCAN_IOCTL_GET_RX_MSG_COUNT      0x0002   /* Ret # CMSG in Rx FIFO   */
#define NTCAN_IOCTL_GET_RX_TIMEOUT        0x0003   /* Ret configured Rx tout  */
#define NTCAN_IOCTL_GET_TX_TIMEOUT        0x0004   /* Ret configured Tx tout  */
#define NTCAN_IOCTL_SET_20B_HND_FILTER    0x0005   /* Set 2.0B filter mask    */
#define NTCAN_IOCTL_GET_SERIAL            0x0006   /* Get HW serial number    */
#define NTCAN_IOCTL_GET_TIMESTAMP_FREQ    0x0007   /* Get timestamp frequency in Hz  */
#define NTCAN_IOCTL_GET_TIMESTAMP         0x0008   /* Get timestamp counter   */
#define NTCAN_IOCTL_ABORT_RX              0x0009   /* Abort pending Rx I/O    */
#define NTCAN_IOCTL_ABORT_TX              0x000A   /* Abort pending Tx I/O    */
#define NTCAN_IOCTL_SET_RX_TIMEOUT        0x000B   /* Change Rx timeout       */
#define NTCAN_IOCTL_SET_TX_TIMEOUT        0x000C   /* Change Tx timeout       */
#define NTCAN_IOCTL_TX_OBJ_CREATE         0x000D   /* Create obj, arg->CMSG          */
#define NTCAN_IOCTL_TX_OBJ_AUTOANSWER_ON  0x000E   /* Switch autoanswer on,arg->CMSG */
#define NTCAN_IOCTL_TX_OBJ_AUTOANSWER_OFF 0x000F   /* Switch autoanswer off,arg->CMSG*/
#define NTCAN_IOCTL_TX_OBJ_UPDATE         0x0010   /* update  obj, arg->CMSG         */
#define NTCAN_IOCTL_TX_OBJ_DESTROY        0x0011   /* Destroy obj, arg->CMSG         */
#define NTCAN_IOCTL_TX_OBJ_DESTROY_X      0x0012   /* Destroy obj, arg->CMSG_X       */
#define NTCAN_IOCTL_TX_OBJ_SCHEDULE_START 0x0013   /* Start scheduling for handle    */
#define NTCAN_IOCTL_TX_OBJ_SCHEDULE_STOP  0x0014   /* Stop scheduling for handle     */
#define NTCAN_IOCTL_TX_OBJ_SCHEDULE       0x0015   /* Set sched. for obj,arg->CSCHED */
#define NTCAN_IOCTL_SET_BUSLOAD_INTERVAL  0x0016   /* Set busload event interval (ms)*/
#define NTCAN_IOCTL_GET_BUSLOAD_INTERVAL  0x0017   /* Get busload event interval (ms)*/
#define NTCAN_IOCTL_GET_BUS_STATISTIC     0x0018   /* Get CAN bus statistic          */
#define NTCAN_IOCTL_GET_CTRL_STATUS       0x0019   /* Get Controller status          */
#define NTCAN_IOCTL_GET_BITRATE_DETAILS   0x001A   /* Get detailed baudrate info     */
#define NTCAN_IOCTL_GET_NATIVE_HANDLE     0x001B   /* Get native (OS) handle         */
#define NTCAN_IOCTL_SET_HND_FILTER        0x001C   /* Set hnd filter mask            */
#define NTCAN_IOCTL_GET_INFO              0x001D   /* Get NTCAN_INFO structure       */
#define NTCAN_IOCTL_TX_OBJ_CREATE_X       0x001E   /* Create obj, arg->CMSG_X        */
#define NTCAN_IOCTL_TX_OBJ_UPDATE_X       0x001F   /* update obj, arg->CMSG_X        */

    /* ESDACC Error Injection (EEI) related IOCTLs */
#define NTCAN_IOCTL_EEI_CREATE            0x0020   /* Allocate EEI unit              */
#define NTCAN_IOCTL_EEI_DESTROY           0x0021   /* Free EEI unit                  */
#define NTCAN_IOCTL_EEI_STATUS            0x0022   /* Get status of EEI unit         */
#define NTCAN_IOCTL_EEI_CONFIGURE         0x0023   /* Configure EEI unit             */
#define NTCAN_IOCTL_EEI_START             0x0024   /* Arm EEI unit                   */
#define NTCAN_IOCTL_EEI_STOP              0x0025   /* Halt EEI unit                  */
#define NTCAN_IOCTL_EEI_TRIGGER_NOW       0x0026   /* Manually trigger EEI unit      */

    /* Timestamped Tx related IOCTLs */
#define NTCAN_IOCTL_SET_TX_TS_WIN         0x0030   /* Configure window for timestamped TX  */
                                                   /*   0: off (use normal FIFO),          */
                                                   /*  >0: size in ms, max depends on      */
                                                   /*      hardware ((2^32 - 1) ticks)     */
#define NTCAN_IOCTL_GET_TX_TS_WIN         0x0031   /* Get window for timestamped TX in ms  */
#define NTCAN_IOCTL_SET_TX_TS_TIMEOUT     0x0032   /* Set frame timeout for timestamped TX */
                                                   /*   0: no timeout,                     */
                                                   /*  >0: timeout in ms                   */
#define NTCAN_IOCTL_GET_TX_TS_TIMEOUT     0x0033   /* Get frame timeout for timestamped TX */
#define NTCAN_IOCTL_GET_TX_MSG_COUNT      0x0034   /* Ret # CMSG in Tx FIFO                */

#define NTCAN_IOCTL_RESET_CTRL_EC         0x801B   /* Reset Tx/Rx error counters of controller*/


    /* CAN-FD related IOCTLs */
#define NTCAN_IOCTL_GET_FD_TDC            0x0040   /* Get TDC configuration          */
#define NTCAN_IOCTL_SET_FD_TDC            0x0041   /* Set TDC configuration          */

#define NTCAN_IOCTL_LIN_MASTER_SEL        0x0042  /* Set LIN Master selector         */
#define NTCAN_IOCTL_TX_OBJ_AUTOANSWER_ONCE 0x0043 /* Auto answer once after update   */

/*
 *    Types for canFormatError()
 */
#define NTCAN_ERROR_FORMAT_LONG           0x0000   /* Error text as string        */
#define NTCAN_ERROR_FORMAT_SHORT          0x0001   /* Error code as string        */
/*
 *    Flags for canFormatEvent() (flags in NTCAN_FORMATEVENT_PARAMS)
 */
#define NTCAN_FORMATEVENT_SHORT           0x0001   /* Create a shorter description   */
/* NTCAN_FORMATEVENT_SHORT may be used to determine whether canFormatEvent is available */

/*
 * Error injection defines
 */
/* status in NTCAN_EEI_STATUS */
#define EEI_STATUS_OFF              0x0
#define EEI_STATUS_WAIT_TRIGGER     0x1
#define EEI_STATUS_SENDING          0x2
#define EEI_STATUS_FINISHED         0x3

/* mode_trigger in NTCAN_EEI_UNIT */
#define EEI_TRIGGER_MATCH           0
#define EEI_TRIGGER_ARBITRATION     1
#define EEI_TRIGGER_TIMESTAMP       2
#define EEI_TRIGGER_FIELD_POSITION  3
#define EEI_TRIGGER_EXTERNAL_INPUT  4

/* mode_trigger_option in NTCAN_EEI_UNIT */
#define EEI_TRIGGER_ARBITRATION_OPTION_ABORT_ON_ERROR   1 /* ARBITRATION MODE ONLY               */
#define EEI_TRIGGER_MATCH_OPTION_DESTUFFED              1 /* MATCH MODE ONLY                     */
#define EEI_TRIGGER_TIMESTAMP_OPTION_BUSFREE            1 /* TIMESTAMP MODE ONLY                 */

/*
 * mode_repeat in NTCAN_EEI_UNIT
 */
#define EEI_MODE_REPEAT_ENABLE                0x1
#define EEI_MODE_REPEAT_USE_NUMBER_OF_REPEAT  0x2

/* mode_triggerarm_delay and mode_triggeraction_delay in NTCAN_EEI_UNIT */
#define EEI_TRIGGERDELAY_NONE       0 /* no delay */
#define EEI_TRIGGERDELAY_BITTIMES   1 /* delay specified in bittimes at selected baudrate */

/*
 * Error injection structures
 */
typedef union {
        uint8_t  c[20];
        uint16_t s[10];
        uint32_t l[5];
} CAN_FRAME_STREAM;

typedef struct _NTCAN_EEI_UNIT {
        uint32_t  handle;                       /* Handle for ErrorInjection Unit       */

        uint8_t   mode_trigger;                 /* Trigger mode                         */
        uint8_t   mode_trigger_option;          /* Options to trigger                   */
        uint8_t   mode_triggerarm_delay;        /* Enable delayed arming of trigger unit*/
        uint8_t   mode_triggeraction_delay;     /* Enable delayed TX out                */
        uint8_t   mode_repeat;                  /* Enable repeat                        */
        uint8_t   mode_trigger_now;             /* Trigger with next TX point           */
        uint8_t   mode_ext_trigger_option;      /* Switch between trigger and sending   */
        uint8_t   mode_send_async;              /* Send without timing synchronization  */
        uint8_t   reserved1[4];

        uint64_t  timestamp_send;               /* Timestamp for Trigger Timestamp      */
        CAN_FRAME_STREAM trigger_pattern;       /* Trigger for mode Pattern Match       */
        CAN_FRAME_STREAM trigger_mask;          /* Mask to trigger Pattern              */
        uint8_t   trigger_ecc;                  /* ECC for Trigger Field Position       */
        uint8_t   reserved2[3];
        uint32_t  external_trigger_mask;        /* Enable Mask for external Trigger     */
        uint32_t  reserved3[16];

        CAN_FRAME_STREAM tx_pattern;            /* TX pattern                           */
        uint32_t  tx_pattern_len;               /* Length of TX pattern                 */
        uint32_t  triggerarm_delay;             /* Delay for mode triggerarm delay      */
        uint32_t  triggeraction_delay;          /* Delay for mode trigger delay         */
        uint32_t  number_of_repeat;             /* Number of repeats in mode repeat (0 = forever) */
        uint32_t  reserved4;
        CAN_FRAME_STREAM tx_pattern_recessive;  /* Recessive TX pattern (USB400 Addon)  */
        uint32_t  reserved5[9];
} NTCAN_EEI_UNIT;

typedef struct _NTCAN_EEI_STATUS {
        uint32_t  handle;                       /* Handle for ErrorInjection Unit       */

        uint8_t   status;                       /* Status form Unit                     */
        uint8_t   unit_index;                   /* Error Injection Unit ID              */
        uint8_t   units_total;                  /* Max Error Units in esdacc core       */
        uint8_t   units_free;                   /* Free Error Units in esdacc core      */
        uint64_t  trigger_timestamp;            /* Timestamp of trigger time            */
        uint16_t  trigger_cnt;                  /* Count of trigger in Repeat mode      */
        uint16_t  reserved0;
        uint32_t  reserved1[27];
} NTCAN_EEI_STATUS;

typedef struct _CMSG_FRAME {
        CAN_FRAME_STREAM can_frame;             /* Complete Can Frame             */
        CAN_FRAME_STREAM stuff_bits;            /* Mask of Stuff bits             */
        uint16_t  crc;                          /* CRC of CAN Frame               */
        uint8_t   length;                       /* Length of Can Frame in Bit     */

        uint8_t   pos_id11;                     /* Position of Identifier 11 Bit  */
        uint8_t   pos_id18;                     /* Position of Identifier 18 Bit  */
        uint8_t   pos_rtr;                      /* Position of RTR Bit            */
        uint8_t   pos_crtl;                     /* Position of Control Field      */
        uint8_t   pos_dlc;                      /* Position of DLC Bits           */
        uint8_t   pos_data[8];                  /* Position of Data Field         */
        uint8_t   pos_crc;                      /* Position of CRC Field          */
        uint8_t   pos_crc_del;                  /* Position of CRC delimiter      */
        uint8_t   pos_ack;                      /* Position of ACK Field          */
        uint8_t   pos_eof;                      /* Position of End of Frame       */
        uint8_t   pos_ifs;                      /* Position of Inter Frame Space  */
        uint8_t   reserved[3];
} CMSG_FRAME;

/*
 ******************************************************************************
 *                           INLINE FUNCTIONS                                 *
 ******************************************************************************
 */

    /*
     * Use _rotl8() intrinisc for VS2005 and later or C++ Builder 10.2 and
     * later. Otherwise define inline version
     */
#if (defined(_MSC_VER) && (_MSC_VER >= 1400)) ||               \
    (defined(__BORLANDC__) && (__BORLANDC__ >= 0x0730))
uint8_t _rotl8(uint8_t value, uint8_t shift);
# pragma intrinsic(_rotl8)
#define _ntcan_rotl8(value, shift)   _rotl8(value, shift)
#else
 NTCAN_INLINE uint8_t _ntcan_rotl8(uint8_t value, uint8_t shift)
{
    return (value << shift) | (value >> (8 - shift));
}
#endif /* defined(_MSC_VER) .... */

NTCAN_INLINE uint8_t _canLenToDataSize(uint8_t len) {
    static const uint8_t ucLenNtcan[] = {
        0, 0, 1, 1,  2,  2, 3,  3, 4,  4, 5,  5, 6,  6, 7,  7,
        8, 8, 8, 12, 8, 16, 8, 20, 8, 24, 8, 32, 8, 48, 8, 64,
        0, 0, 0, 1,  0,  2, 0,  3, 0,  4, 0,  5, 0,  6, 0,  7,
        0, 8, 0, 12, 0, 16, 0, 20, 0, 24, 0, 32, 0, 48, 0, 64
    }; /*lint !e1534 Static variable in inline function */

    return(ucLenNtcan[_ntcan_rotl8(len, 1) & 0x3F]);
}

NTCAN_INLINE uint8_t _canDataSizeToDLC(uint8_t dataSize) {
    static const uint8_t ucLenNtcan[] = {
        0,  1,  2,  3,  4,  5,  6,  7,  8,  9,  9,  9,  9,  10, 10, 10,
        10, 11, 11, 11, 11, 12, 12, 12, 12, 13, 13, 13, 13, 13, 13, 13,
        13, 14, 14, 14, 14, 14, 14, 14, 14, 14, 14, 14, 14, 14, 14, 14,
        14, 15, 15, 15, 15, 15, 15, 15, 15, 15, 15, 15, 15, 15, 15, 15,
        15
    }; /*lint !e1534 Static variable in inline function */

    if(dataSize > 64) {
        dataSize = 64;
    }

    return(ucLenNtcan[dataSize]);
}


/*
 *                    NTCAN-API exported by the library
 *
 * Some parameter are passed as a pointer to a value where the application has
 * to initialize this parameter before calling the function and the parameter
 * may be changed after return. These parameters are described with IN and OUT
 * seen from the application point of view. The OUT value has to be initialized
 * by the application before the function is called, the IN value can be checked
 * by the application after return of this call.
 *
 */
EXPORT NTCAN_RESULT CALLTYPE canSetBaudrate(
                NTCAN_HANDLE   handle,      /* Handle                        */
                uint32_t       baud );      /* Baudrate                      */
/*...........................................................................*/
EXPORT NTCAN_RESULT CALLTYPE canGetBaudrate(
                NTCAN_HANDLE   handle,      /* Handle                        */
                uint32_t       *baud );     /* OUT: N/A                      */
                                            /* IN:  Baudrate                 */
/*...........................................................................*/
EXPORT NTCAN_RESULT CALLTYPE canOpen(
                int          net,          /* net number                     */
                uint32_t     flags,        /* mode flags                     */
                int32_t      txqueuesize,  /* nr of entries in message queue */
                int32_t      rxqueuesize,  /* nr of entries in message queue */
                int32_t      txtimeout,    /* tx-timeout in milliseconds     */
                int32_t      rxtimeout,    /* rx-timeout in milliseconds     */
                NTCAN_HANDLE *handle );    /* OUT: N/A                       */
                                           /* IN: Handle                     */
/*...........................................................................*/
EXPORT NTCAN_RESULT CALLTYPE canClose(
                NTCAN_HANDLE  handle );  /* Handle                           */
/*...........................................................................*/
EXPORT NTCAN_RESULT CALLTYPE canSetBaudrateX(
                NTCAN_HANDLE       handle,   /* Handle                       */
                NTCAN_BAUDRATE_X  *baud );   /* Bitrate configuration        */
/*...........................................................................*/
EXPORT NTCAN_RESULT CALLTYPE canGetBaudrateX(
                NTCAN_HANDLE        handle,   /* Handle                      */
                NTCAN_BAUDRATE_X   *baud );   /* OUT: N/A                    */
                                              /* IN:  Bitrate configuration  */
/*...........................................................................*/
EXPORT NTCAN_RESULT CALLTYPE canIdAdd(
                NTCAN_HANDLE  handle,    /* Handle                           */
                int32_t       id  );     /* CAN message identifier           */
/*...........................................................................*/
EXPORT NTCAN_RESULT CALLTYPE canIdRegionAdd(
                NTCAN_HANDLE  handle,    /* Handle                           */
                int32_t       idStart,   /* 1st CAN message identifier       */
                int32_t       *idCnt );  /* Number of CAN message identifier */
/*...........................................................................*/
EXPORT NTCAN_RESULT CALLTYPE canIdDelete(
                NTCAN_HANDLE  handle,    /* Handle                           */
                int32_t       id  );     /* CAN message identifier           */
/*...........................................................................*/
EXPORT NTCAN_RESULT CALLTYPE canIdRegionDelete(
                NTCAN_HANDLE  handle,    /* Handle                           */
                int32_t       idStart,   /* 1st CAN message identifier       */
                int32_t       *idCnt );  /* Number of CAN message identifier */
/*...........................................................................*/
EXPORT NTCAN_RESULT CALLTYPE canTake(
                NTCAN_HANDLE  handle,    /* Handle                           */
                CMSG          *cmsg,     /* Ptr to application buffer        */
                int32_t       *len );    /* OUT: Size of CMSG-Buffer         */
                                         /* IN:  Number of received messages */
/*...........................................................................*/
EXPORT NTCAN_RESULT CALLTYPE canRead(
                NTCAN_HANDLE  handle,    /* Handle                           */
                CMSG          *cmsg,     /* Ptr to application buffer        */
                int32_t       *len,      /* OUT: Size of CMSG-Buffer         */
                                         /* IN:  Number of received messages */
                OVERLAPPED    *ovrlppd); /* NULL or overlapped-structure     */
/*...........................................................................*/
EXPORT NTCAN_RESULT CALLTYPE canSend(
                NTCAN_HANDLE  handle,    /* Handle                           */
                CMSG          *cmsg,     /* Ptr to application buffer        */
                int32_t       *len );    /* OUT: # of messages to transmit   */
                                         /* IN:  # of transmitted messages   */
/*...........................................................................*/
EXPORT NTCAN_RESULT CALLTYPE canWrite(
                NTCAN_HANDLE  handle,    /* Handle                           */
                CMSG          *cmsg,     /* Ptr to application buffer        */
                int32_t       *len,      /* OUT: # of messages to transmit   */
                                         /* IN:  # of transmitted messages   */
                OVERLAPPED    *ovrlppd); /* NULL or overlapped structure     */
/*...........................................................................*/
_NTCAN_OBSOLETE(canRead) EXPORT NTCAN_RESULT CALLTYPE canReadEvent(
                NTCAN_HANDLE  handle,    /* Handle                           */
                EVMSG         *evmsg,    /* ptr to event-msg-buffer          */
                OVERLAPPED    *ovrlppd) _NTCAN_GCCATTR_DEPRECATED; /* NULL or overlapped structure     */
/*...........................................................................*/
_NTCAN_OBSOLETE(canSend) EXPORT NTCAN_RESULT CALLTYPE canSendEvent(
                NTCAN_HANDLE  handle,    /* Handle                           */
                EVMSG         *evmsg ) _NTCAN_GCCATTR_DEPRECATED;  /* ptr to event-msg-buffer          */

/*...........................................................................*/
EXPORT NTCAN_RESULT CALLTYPE canStatus(
                NTCAN_HANDLE  handle,    /* Handle                           */
                CAN_IF_STATUS *cstat );  /* Ptr to can-status-buffer         */
/*...........................................................................*/
EXPORT NTCAN_RESULT CALLTYPE canIoctl(
                NTCAN_HANDLE  handle,    /* Handle                           */
                uint32_t      ulCmd,     /* Command specifier                */
                void *        pArg );    /* Ptr to command specific argument */
/*...........................................................................*/
EXPORT NTCAN_RESULT CALLTYPE canTakeT(
                NTCAN_HANDLE  handle,    /* Handle                           */
                CMSG_T        *cmsg_t,   /* Ptr to application buffer        */
                int32_t       *len );    /* OUT: Size of CMSG_T-Buffer       */
                                         /* IN:  Number of received messages */
/*...........................................................................*/
EXPORT NTCAN_RESULT CALLTYPE canReadT(
                NTCAN_HANDLE  handle,    /* Handle                           */
                CMSG_T        *cmsg_t,   /* Ptr to application buffer        */
                int32_t       *len,      /* OUT: Size of CMSG_T-Buffer       */
                                         /* IN:  Number of received messages */
                OVERLAPPED    *ovrlppd); /* NULL or overlapped-structure     */
/*...........................................................................*/
EXPORT NTCAN_RESULT CALLTYPE canSendT(
                NTCAN_HANDLE  handle,    /* Handle                           */
                CMSG_T        *cmsg_t,   /* Ptr to application buffer        */
                int32_t       *len );    /* OUT: # of messages to transmit   */
                                         /* IN:  # of transmitted messages   */
/*...........................................................................*/
EXPORT NTCAN_RESULT CALLTYPE canWriteT(
                NTCAN_HANDLE  handle,    /* handle                           */
                CMSG_T        *cmsg_t,   /* ptr to data-buffer               */
                int32_t       *len,      /* OUT: # of messages to transmit   */
                                         /* IN:  # of transmitted messages   */
                OVERLAPPED    *ovrlppd); /* NULL or overlapped structure     */
/*...........................................................................*/
EXPORT NTCAN_RESULT CALLTYPE canTakeX(
                NTCAN_HANDLE  handle,    /* Handle                           */
                CMSG_X        *cmsg_x,   /* Ptr to application buffer        */
                int32_t       *len );    /* OUT: Size of CMSG_X-Buffer       */
                                         /* IN:  Number of received messages */
/*...........................................................................*/
EXPORT NTCAN_RESULT CALLTYPE canReadX(
                NTCAN_HANDLE  handle,    /* Handle                           */
                CMSG_X        *cmsg_x,   /* Ptr to application buffer        */
                int32_t       *len,      /* OUT: Size of CMSG_X-Buffer       */
                                         /* IN:  Number of received messages */
                OVERLAPPED    *ovrlppd); /* NULL or overlapped-structure     */
/*...........................................................................*/
EXPORT NTCAN_RESULT CALLTYPE canSendX(
                NTCAN_HANDLE  handle,    /* Handle                           */
                CMSG_X        *cmsg_x,   /* Ptr to application buffer        */
                int32_t       *len );    /* OUT: # of messages to transmit   */
                                         /* IN:  # of transmitted messages   */
/*...........................................................................*/
EXPORT NTCAN_RESULT CALLTYPE canWriteX(
                NTCAN_HANDLE  handle,    /* handle                           */
                CMSG_X        *cmsg_x,   /* ptr to data-buffer               */
                int32_t       *len,      /* OUT: # of messages to transmit   */
                                         /* IN:  # of transmitted messages   */
                OVERLAPPED    *ovrlppd); /* NULL or overlapped structure     */
/*...........................................................................*/
EXPORT NTCAN_RESULT CALLTYPE canFormatError(
                NTCAN_RESULT  error,     /* Error code                       */
                uint32_t      type,      /* Error message type               */
                char          *pBuf,     /* Pointer to destination buffer    */
                uint32_t      bufsize);  /* Size of the buffer above         */
/*...........................................................................*/
EXPORT NTCAN_RESULT CALLTYPE canFormatEvent(
                EVMSG         *event,    /* Event message                    */
                NTCAN_FORMATEVENT_PARAMS *para, /* Parameters                */
                char          *pBuf,     /* Pointer to destination buffer    */
                uint32_t      bufsize);  /* Size of the buffer above         */
/*...........................................................................*/
EXPORT NTCAN_RESULT CALLTYPE canFormatFrame(
                CMSG          *msg,      /* CAN message                      */
                CMSG_FRAME    *frame,    /* CAN Frame + Information          */
                uint32_t      eccExt);   /* ECC Errors + Features            */
/*...........................................................................*/
#if (defined(_WIN32) || defined(__linux__)) && !defined(UNDER_RTSS) && !defined(RTOS32)
EXPORT NTCAN_RESULT CALLTYPE canGetOverlappedResult(
                NTCAN_HANDLE  handle,    /* Handle                           */
                OVERLAPPED    *ovrlppd,  /* IN: Win32 overlapped structure   */
                int32_t       *len,      /* OUT:Number of transmitted        */
                                         /*     or received messages         */
                NTCAN_BOOL    bWait );   /* FALSE =>do not wait, else wait   */
/*...........................................................................*/
EXPORT NTCAN_RESULT CALLTYPE canGetOverlappedResultT(
                NTCAN_HANDLE  handle,    /* Handle                           */
                OVERLAPPED    *ovrlppd,  /* IN: Win32 overlapped structure   */
                int32_t       *len,      /* OUT:Number of transmitted        */
                                         /*     or received messages         */
                NTCAN_BOOL    bWait );   /* FALSE =>do not wait, else wait   */
/*...........................................................................*/
EXPORT NTCAN_RESULT CALLTYPE canGetOverlappedResultX(
                NTCAN_HANDLE  handle,    /* Handle                           */
                OVERLAPPED    *ovrlppd,  /* IN: Win32 overlapped structure   */
                int32_t       *len,      /* OUT:Number of transmitted        */
                                         /*     or received messages         */
                NTCAN_BOOL    bWait );   /* FALSE =>do not wait, else wait   */
#else
# define canGetOverlappedResult(hnd, ovr, len, bWait)    NTCAN_NOT_IMPLEMENTED
# define canGetOverlappedResultT(hnd, ovr, len, bWait)   NTCAN_NOT_IMPLEMENTED
# define canGetOverlappedResultX(hnd, ovr, len, bWait)   NTCAN_NOT_IMPLEMENTED
#endif /* of defined(_WIN32) && !defined(UNDER_RTSS) && !defined(RTOS32) */

#if defined(NTCAN_DLSYM)
/*
 * Function pointer to ease loading the shared NTCAN library
 */
typedef NTCAN_RESULT (CALLTYPE *PFN_CAN_SET_BAUDRATE)(NTCAN_HANDLE handle,
                                                      uint32_t     baud);
typedef NTCAN_RESULT (CALLTYPE *PFN_CAN_GET_BAUDRATE)(NTCAN_HANDLE handle,
                                                      uint32_t     *baud);
typedef NTCAN_RESULT (CALLTYPE *PFN_CAN_OPEN)(int          net,
                                              uint32_t     flags,
                                              int32_t      txqueuesize,
                                              int32_t      rxqueuesize,
                                              int32_t      txtimeout,
                                              int32_t      rxtimeout,
                                              NTCAN_HANDLE *handle );
typedef NTCAN_RESULT (CALLTYPE *PFN_CAN_SET_BAUDRATE_X)(NTCAN_HANDLE handle,
                                                        NTCAN_BAUDRATE_X  *baud);
typedef NTCAN_RESULT (CALLTYPE *PFN_CAN_GET_BAUDRATE_X)(NTCAN_HANDLE handle,
                                                        NTCAN_BAUDRATE_X  *baud);
typedef NTCAN_RESULT (CALLTYPE *PFN_CAN_CLOSE)(NTCAN_HANDLE handle);
typedef NTCAN_RESULT (CALLTYPE *PFN_CAN_ID_ADD)(NTCAN_HANDLE handle,
                                                int32_t      id);
typedef NTCAN_RESULT (CALLTYPE *PFN_CAN_ID_DELETE)(NTCAN_HANDLE handle,
                                                   int32_t id);
typedef NTCAN_RESULT (CALLTYPE *PFN_CAN_SEND)(NTCAN_HANDLE handle,
                                              CMSG         *cmsg,
                                              int32_t      *len);
typedef NTCAN_RESULT (CALLTYPE *PFN_CAN_WRITE)(NTCAN_HANDLE handle,
                                               CMSG         *cmsg,
                                               int32_t      *len,
                                               OVERLAPPED   *ovrlppd);
typedef NTCAN_RESULT (CALLTYPE *PFN_CAN_TAKE)(NTCAN_HANDLE handle,
                                              CMSG         *cmsg,
                                              int32_t      *len);
typedef NTCAN_RESULT (CALLTYPE *PFN_CAN_READ)(NTCAN_HANDLE handle,
                                              CMSG         *cmsg,
                                              int32_t      *len,
                                              OVERLAPPED   *ovrlppd);
typedef NTCAN_RESULT (CALLTYPE *PFN_CAN_READ_EVENT)(NTCAN_HANDLE handle,
                                                    EVMSG        *cmsg,
                                                    OVERLAPPED   *ovrlppd);
typedef NTCAN_RESULT (CALLTYPE *PFN_CAN_SEND_EVENT)(NTCAN_HANDLE handle,
                                                    EVMSG        *cmsg);
typedef NTCAN_RESULT (CALLTYPE *PFN_CAN_STATUS)(NTCAN_HANDLE  handle,
                                                CAN_IF_STATUS *cstat);
typedef NTCAN_RESULT (CALLTYPE *PFN_CAN_IOCTL)(NTCAN_HANDLE handle,
                                               uint32_t     ulCmd,
                                               void         *pArg );
typedef NTCAN_RESULT (CALLTYPE *PFN_CAN_TAKE_T)(NTCAN_HANDLE handle,
                                                CMSG_T       *cmsg_t,
                                                int32_t      *len);
typedef NTCAN_RESULT (CALLTYPE *PFN_CAN_READ_T)(NTCAN_HANDLE handle,
                                                CMSG_T       *cmsg_t,
                                                int32_t      *len,
                                                OVERLAPPED   *ovrlppd);
typedef NTCAN_RESULT (CALLTYPE *PFN_CAN_SEND_T)(NTCAN_HANDLE handle,
                                                CMSG_T       *cmsg_t,
                                                int32_t      *len);
typedef NTCAN_RESULT (CALLTYPE *PFN_CAN_WRITE_T)(NTCAN_HANDLE handle,
                                                 CMSG_T       *cmsg_t,
                                                 int32_t      *len,
                                                 OVERLAPPED   *ovrlppd);
typedef NTCAN_RESULT (CALLTYPE *PFN_CAN_TAKE_X)(NTCAN_HANDLE handle,
                                                CMSG_X       *cmsg_x,
                                                int32_t      *len);
typedef NTCAN_RESULT (CALLTYPE *PFN_CAN_READ_X)(NTCAN_HANDLE handle,
                                                CMSG_X       *cmsg_x,
                                                int32_t      *len,
                                                OVERLAPPED   *ovrlppd);
typedef NTCAN_RESULT (CALLTYPE *PFN_CAN_SEND_X)(NTCAN_HANDLE handle,
                                                CMSG_X       *cmsg_x,
                                                int32_t      *len);
typedef NTCAN_RESULT (CALLTYPE *PFN_CAN_WRITE_X)(NTCAN_HANDLE handle,
                                                 CMSG_X       *cmsg_x,
                                                 int32_t      *len,
                                                 OVERLAPPED   *ovrlppd);
typedef NTCAN_RESULT (CALLTYPE *PFN_CAN_FORMAT_ERROR)(NTCAN_RESULT  error,
                                                      uint32_t      type,
                                                      char          *pBuf,
                                                      uint32_t      bufsize);
typedef NTCAN_RESULT (CALLTYPE *PFN_CAN_FORMAT_EVENT)(EVMSG         *event,
                                                      NTCAN_FORMATEVENT_PARAMS *para,
                                                      char          *pBuf,
                                                      uint32_t      bufsize);
typedef NTCAN_RESULT (CALLTYPE *PFN_CAN_FORMAT_FRAME)(CMSG        *msg,
                                                      CMSG_FRAME  *frame,
                                                      uint32_t    eccExt);
#if (defined(_WIN32) || defined(__linux__)) && !defined(UNDER_RTSS) && !defined(RTOS32)
typedef NTCAN_RESULT (CALLTYPE *PFN_CAN_GET_OVERLAPPED_RESULT)(NTCAN_HANDLE handle,
                                                               OVERLAPPED   *ovrlppd,
                                                               int32_t      *len,
                                                               NTCAN_BOOL   bWait);

typedef NTCAN_RESULT (CALLTYPE *PFN_CAN_GET_OVERLAPPED_RESULT_T)(NTCAN_HANDLE handle,
                                                                 OVERLAPPED   *ovrlppd,
                                                                 int32_t      *len,
                                                                 NTCAN_BOOL   bWait);

typedef NTCAN_RESULT (CALLTYPE *PFN_CAN_GET_OVERLAPPED_RESULT_X)(NTCAN_HANDLE handle,
                                                                 OVERLAPPED   *ovrlppd,
                                                                 int32_t      *len,
                                                                 NTCAN_BOOL   bWait);
#else
typedef NTCAN_RESULT (CALLTYPE *PFN_CAN_GET_OVERLAPPED_RESULT)(NTCAN_HANDLE handle,
                                                               OVERLAPPED   *ovrlppd,
                                                               int32_t      *len,
                                                               int          bWait);

typedef NTCAN_RESULT (CALLTYPE *PFN_CAN_GET_OVERLAPPED_RESULT_T)(NTCAN_HANDLE handle,
                                                                 OVERLAPPED   *ovrlppd,
                                                                 int32_t      *len,
                                                                 int          bWait);

typedef NTCAN_RESULT (CALLTYPE *PFN_CAN_GET_OVERLAPPED_RESULT_X)(NTCAN_HANDLE handle,
                                                                 OVERLAPPED   *ovrlppd,
                                                                 int32_t      *len,
                                                                 int          bWait);
#endif /* of defined(_WIN32) && !defined(UNDER_RTSS) && !defined(RTOS32) */


/*
 * Macros to ease loading the shared NTCAN library dynamically
 */
#define FUNCPTR_CAN_SET_BAUDRATE(hnd) \
    (PFN_CAN_SET_BAUDRATE)NTCAN_DLSYM(hnd, "canSetBaudrate")
#define FUNCPTR_CAN_GET_BAUDRATE(hnd) \
    (PFN_CAN_GET_BAUDRATE)NTCAN_DLSYM(hnd, "canGetBaudrate")
#define FUNCPTR_CAN_OPEN(hnd) \
    (PFN_CAN_OPEN)NTCAN_DLSYM(hnd, "canOpen")
#define FUNCPTR_CAN_CLOSE(hnd) \
    (PFN_CAN_CLOSE)NTCAN_DLSYM(hnd, "canClose")
#define FUNCPTR_CAN_SET_BAUDRATE_X(hnd) \
    (PFN_CAN_SET_BAUDRATE_X)NTCAN_DLSYM(hnd, "canSetBaudrateX")
#define FUNCPTR_CAN_GET_BAUDRATE_X(hnd) \
    (PFN_CAN_GET_BAUDRATE_X)NTCAN_DLSYM(hnd, "canGetBaudrateX")
#define FUNCPTR_CAN_ID_ADD(hnd) \
    (PFN_CAN_ID_ADD)NTCAN_DLSYM(hnd, "canIdAdd")
#define FUNCPTR_CAN_ID_DELETE(hnd) \
    (PFN_CAN_ID_DELETE)NTCAN_DLSYM(hnd, "canIdDelete")
#define FUNCPTR_CAN_SEND(hnd) \
    (PFN_CAN_SEND)NTCAN_DLSYM(hnd, "canSend")
#define FUNCPTR_CAN_WRITE(hnd) \
    (PFN_CAN_WRITE)NTCAN_DLSYM(hnd, "canWrite")
#define FUNCPTR_CAN_TAKE(hnd) \
    (PFN_CAN_TAKE)NTCAN_DLSYM(hnd, "canTake")
#define FUNCPTR_CAN_READ(hnd) \
    (PFN_CAN_READ)NTCAN_DLSYM(hnd, "canRead")
#define FUNCPTR_CAN_SEND_EVENT(hnd) \
    (PFN_CAN_SEND_EVENT)NTCAN_DLSYM(hnd, "canSendEvent")
#define FUNCPTR_CAN_READ_EVENT(hnd) \
    (PFN_CAN_READ_EVENT)NTCAN_DLSYM(hnd, "canReadEvent")
#define FUNCPTR_CAN_STATUS(hnd) \
    (PFN_CAN_STATUS)NTCAN_DLSYM(hnd, "canStatus")
#define FUNCPTR_CAN_IOCTL(hnd) \
    (PFN_CAN_IOCTL)NTCAN_DLSYM(hnd, "canIoctl")
#define FUNCPTR_CAN_SEND_T(hnd) \
    (PFN_CAN_SEND_T)NTCAN_DLSYM(hnd, "canSendT")
#define FUNCPTR_CAN_WRITE_T(hnd) \
    (PFN_CAN_WRITE_T)NTCAN_DLSYM(hnd, "canWriteT")
#define FUNCPTR_CAN_TAKE_T(hnd) \
    (PFN_CAN_TAKE_T)NTCAN_DLSYM(hnd, "canTakeT")
#define FUNCPTR_CAN_READ_T(hnd) \
    (PFN_CAN_READ_T)NTCAN_DLSYM(hnd, "canReadT")
#define FUNCPTR_CAN_SEND_X(hnd) \
    (PFN_CAN_SEND_X)NTCAN_DLSYM(hnd, "canSendX")
#define FUNCPTR_CAN_WRITE_X(hnd) \
    (PFN_CAN_WRITE_X)NTCAN_DLSYM(hnd, "canWriteX")
#define FUNCPTR_CAN_TAKE_X(hnd) \
    (PFN_CAN_TAKE_X)NTCAN_DLSYM(hnd, "canTakeX")
#define FUNCPTR_CAN_READ_X(hnd) \
    (PFN_CAN_READ_X)NTCAN_DLSYM(hnd, "canReadX")
#define FUNCPTR_CAN_FORMAT_ERROR(hnd) \
    (PFN_CAN_FORMAT_ERROR)NTCAN_DLSYM(hnd, "canFormatError")
#define FUNCPTR_CAN_FORMAT_EVENT(hnd) \
    (PFN_CAN_FORMAT_EVENT)NTCAN_DLSYM(hnd, "canFormatEvent")
#define FUNCPTR_CAN_FORMAT_FRAME(hnd) \
    (PFN_CAN_FORMAT_FRAME)NTCAN_DLSYM(hnd, "canFormatFrame")
#if (defined(_WIN32) || defined(__linux__)) && !defined(UNDER_RTSS) && !defined(RTOS32)
# define FUNCPTR_CAN_GET_OVERLAPPED_RESULT(hnd) \
    (PFN_CAN_GET_OVERLAPPED_RESULT)NTCAN_DLSYM(hnd, "canGetOverlappedResult")
# define FUNCPTR_CAN_GET_OVERLAPPED_RESULT_T(hnd) \
    (PFN_CAN_GET_OVERLAPPED_RESULT_T)NTCAN_DLSYM(hnd, "canGetOverlappedResultT")
# define FUNCPTR_CAN_GET_OVERLAPPED_RESULT_X(hnd) \
    (PFN_CAN_GET_OVERLAPPED_RESULT_T)NTCAN_DLSYM(hnd, "canGetOverlappedResultX")
#else
# define FUNCPTR_CAN_GET_OVERLAPPED_RESULT(hnd)         NULL
# define FUNCPTR_CAN_GET_OVERLAPPED_RESULT_T(hnd)       NULL
# define FUNCPTR_CAN_GET_OVERLAPPED_RESULT_X(hnd)       NULL
#endif /* of defined(_WIN32) && !defined(UNDER_RTSS) && !defined(RTOS32) */

#endif /* of defined(NTCAN_DLSYM) */

#ifdef __cplusplus
}
#endif

#endif /* _NTCAN_H_ */

