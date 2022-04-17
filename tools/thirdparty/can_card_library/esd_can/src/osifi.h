/* -*- esdcan-c -*-
 * FILE NAME osifi.h
 *
 * BRIEF MODULE DESCRIPTION
 *      OSIF operating system dependent wrapping header
 */
/************************************************************************
 *
 *  Copyright (c) 1996 - 2020 by esd electronics gmbh
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
 *  Germany                                support@esd.eu
 *
 *************************************************************************/
/*! \file osifi.h
    \brief OSIF operating system wrapping header

    This file contains the OSIF prototypes and user macros.
    Any driver should call the OSIF_<xxx> macros instead of the
    osif_<xxx> functions.
*/

#ifndef __OSIFI_H__
#define __OSIFI_H__

#include <linux/version.h>
#if (LINUX_VERSION_CODE <= KERNEL_VERSION(2,6,32))
# if (LINUX_VERSION_CODE >= KERNEL_VERSION(2,6,19))
#  include <linux/autoconf.h>
# else
#  include <linux/config.h>
# endif
#endif
#include <linux/errno.h>
#if LINUX_VERSION_CODE >= KERNEL_VERSION(2,6,27)
# include <linux/semaphore.h>
#else
# include <asm/semaphore.h>
#endif
#include <linux/wait.h>

#if LINUX_VERSION_CODE >= KERNEL_VERSION(2,6,18)
# include <linux/irqreturn.h>
#else
# include <linux/threads.h>      /* For NR_CPUS */
# include <linux/interrupt.h>
#endif

#if LINUX_VERSION_CODE >= KERNEL_VERSION(2,6,0)
# ifdef OSIF_CALLTYPE
#  undef OSIF_CALLTYPE
# endif
# if !defined(CONFIG_PPC) && !defined(CONFIG_ARM) && !defined(CONFIG_ARM64)
#  define OSIF_CALLTYPE __attribute__((regparm(0))) /* asmlinkage */
# else
#  define OSIF_CALLTYPE
# endif
# if defined(CONFIG_X86)
#  define OSIF_ARCH_X86
#  define OSIF_LITTLE_ENDIAN
# endif
# if defined(CONFIG_PPC)
#  define OSIF_ARCH_PPC
#  define OSIF_BIG_ENDIAN
# endif
# if defined(CONFIG_ARM) || defined(CONFIG_ARM64)
#  define OSIF_ARCH_ARM
#  define OSIF_LITTLE_ENDIAN
# endif
#endif

/* BL Note: Actually not a Linux induced version discrepancy,
            but code is only tested on versions higher 2.6.20 */
#if LINUX_VERSION_CODE >= KERNEL_VERSION(2,6,20)
# define OSIF_USE_PREEMPT_RT_IMPLEMENTATION
#endif

/*
 * Select the default (dummy) implementation for cache DMA abstraction.
 * Keep in mind that for Linux the functions always must be implemented
 * if you stop using the default (dummy) implementation.
 */
#define OSIF_CACHE_DMA_DEFAULTS 1

#include "sysdep.h"

#ifndef NULL
# define NULL ((void*)0)
#endif

#ifdef OSIF_BOARD_SPI
#include <osif_spi.h>
#endif

#ifdef __KERNEL__

#ifdef OSIF_BOARD_SPI
typedef struct _OSIF_SPIDEV OSIF_SPIDEV;

struct _OSIF_SPIDEV {
  // spi_funcs_t*   funcs; /* SPI master library function table */
  // struct spi_device* dev; /* SPI device handle */
  struct spi_candev *scdev;
  // int              devno; /* Device number on bus */
};
#endif

typedef struct __OSIF_MUTEX     *OSIF_MUTEX;

typedef struct __OSIF_SPINLOCK  *OSIF_BUSY_MUTEX, *OSIF_IRQ_MUTEX;

typedef struct __OSIF_DPC _OSIF_DPC, *OSIF_DPC;
struct __OSIF_DPC {
        OSIF_DPC            next;
        INT8                linked;
        INT8                running;
        INT8                destroy;
        INT8                reserved;
        VOID (OSIF_CALLTYPE *func)(VOID *);
        VOID                *arg;
};

typedef struct _OSIF_LINUX_TIMER  OSIF_LINUX_TIMER;

#define OSIF_TIMER_SYS_PART   /* no static extension of OSIF_TIMER struct */

#define OSIF_IRQ_HANDLER_CALLTYPE       OSIF_CALLTYPE
#define OSIF_IRQ_HANDLER_PARAMETER      void*
#define OSIF_IRQ_HANDLER(func,arg)      int (OSIF_IRQ_HANDLER_CALLTYPE func) ( void *arg )
#define OSIF_IRQ_HANDLER_P              int (OSIF_IRQ_HANDLER_CALLTYPE *) ( void *arg )
#if LINUX_VERSION_CODE >= KERNEL_VERSION(2,6,0)
# define OSIF_IRQ_HANDLED               (IRQ_HANDLED)
# define OSIF_IRQ_HANDLED_NOT           (IRQ_NONE)
#else
# define OSIF_IRQ_HANDLED               (1)  /* Equal to Linux2.6 IRQ_HANDLED */
# define OSIF_IRQ_HANDLED_NOT           (0)
#endif

#if LINUX_VERSION_CODE >= KERNEL_VERSION(2,6,0)
# define OSIF_IRQ_HANDLER_RETURN( arg ) return IRQ_RETVAL(arg)
#else
# define OSIF_IRQ_HANDLER_RETURN( arg ) return arg
#endif

typedef struct pci_dev *OSIF_PCIDEV;
#define OSIF_PCI_VADDR                  void *
#define OSIF_PCI_MADDR                  UINT32

/*
 *  Dear kernel 2.2.x user,
 *  we are not able to determine the exact version, when
 *  dma_addr_t was introduced into 2.2.x kernels.
 *  If the following typedef leads to an compiletime error,
 *  please comment the typedef.
 */
#if LINUX_VERSION_CODE < KERNEL_VERSION(2,4,0)
typedef u32 dma_addr_t;
#endif

typedef struct __OSIF_PCI_PADDR  _OSIF_PCI_PADDR, *OSIF_PCI_PADDR;

#if defined(__GNUC__) && defined(CONFIG_X86)
static inline void osif_io_out8(UINT8 *addr, UINT8 data)
{
        asm volatile("outb %0,%1" : : "a" (data), "dN" ((UINT16)(UINTPTR)addr));
}
static inline UINT8 osif_io_in8(UINT8 *addr)
{
        UINT8 data;
        asm volatile("inb %1,%0" : "=a" (data) : "dN" ((UINT16)(UINTPTR)addr));
        return data;
}
static inline void osif_io_out16(UINT16 *addr, UINT16 data)
{
        asm volatile("outw %0,%1" : : "a" (data), "dN" ((UINT16)(UINTPTR)addr));
}
static inline UINT16 osif_io_in16(UINT16 *addr)
{
        UINT16 data;
        asm volatile("inw %1,%0" : "=a" (data) : "dN" ((UINT16)(UINTPTR)addr));
        return data;
}
static inline void osif_io_out32(UINT32 *addr, UINT32 data)
{
        asm volatile("outl %0,%1" : : "a" (data), "dN" ((UINT16)(UINTPTR)addr));
}
static inline UINT32 osif_io_in32(UINT32 *addr)
{
        UINT32 data;
        asm volatile("inl %1,%0" : "=a" (data) : "dN" ((UINT16)(UINTPTR)addr));
        return data;
}
#else
extern void   OSIF_CALLTYPE osif_io_out8(UINT8 *addr, UINT8 data);
extern UINT8  OSIF_CALLTYPE osif_io_in8(UINT8 *addr);
extern void   OSIF_CALLTYPE osif_io_out16(UINT16 *addr, UINT16 data);
extern UINT16 OSIF_CALLTYPE osif_io_in16(UINT16 *addr);
extern void   OSIF_CALLTYPE osif_io_out32(UINT32 *addr, UINT32 data);
extern UINT32 OSIF_CALLTYPE osif_io_in32(UINT32 *addr);
#define OSIF_USE_IO_FUNCTIONS
#endif

#define osif_mem_out8( addr, data )  (*(volatile UINT8* )(addr)) = (data)
#define osif_mem_in8( addr )         (*(volatile UINT8* )(addr))
#define osif_mem_out16( addr, data ) (*(volatile UINT16*)(addr)) = (data)
#define osif_mem_in16( addr )        (*(volatile UINT16*)(addr))
#define osif_mem_out32( addr, data ) (*(volatile UINT32*)(addr)) = (data)
#define osif_mem_in32( addr )        (*(volatile UINT32*)(addr))

#if defined(__GNUC__) && defined(CONFIG_X86)
/* too bad we cannot use 486 assembler here, because nucleus is compiled without knowledge
   of the system it is later used on */
#if (__GNUC__ > 2)
#define osif_swap16(x) \
({ \
        register UINT16 __x; \
        asm ("xchg %b1,%h1" : "=Q" (__x) : "0" ((UINT16)x)); \
        __x; \
})
#else
#define osif_swap16(x) \
({ \
        register UINT16 __x; \
        asm ("xchg %b1,%h1" : "=q" (__x) : "0" ((UINT16)x)); \
        __x; \
})
#endif
#else    /* sorry, no inline assembler macros for you */
#define osif_swap16(x) \
({ \
        UINT16 __x = (x); \
        ((UINT16)( \
                (((UINT16)(__x) & (UINT16)0x00ffU) << 8) | \
                (((UINT16)(__x) & (UINT16)0xff00U) >> 8) )); \
})
#endif

#if defined(__GNUC__) && defined(CONFIG_X86)
#if !defined(CONFIG_X86_64)
#define osif_swap32(x) \
({ \
        register UINT32 __x; \
        asm ("xchg %b1,%h1; roll $16,%1; xchg %b1,%h1" : "=q" (__x) : "0" ((UINT32)x)); \
        __x; \
})
#else
#define osif_swap32(x) \
({ \
        register UINT32 __x; \
        asm ("bswap %1" : "=r" (__x) : "0" ((UINT32)x)); \
        __x; \
})
#endif
#else    /* sorry, no inline assembler macros for you */
#define osif_swap32(x) \
({ \
        UINT32 __x = (x); \
        ((UINT32)( \
                (((UINT32)(__x) & (UINT32)0x000000ffUL) << 24) | \
                (((UINT32)(__x) & (UINT32)0x0000ff00UL) <<  8) | \
                (((UINT32)(__x) & (UINT32)0x00ff0000UL) >>  8) | \
                (((UINT32)(__x) & (UINT32)0xff000000UL) >> 24) )); \
})
#endif

#if (__GNUC__ > 2) && defined(CONFIG_X86)
#if !defined(CONFIG_X86_64)
#define osif_swap64(x) \
({ \
        register UINT64 __x; \
        asm ("xchg %%ah,%%al; roll $16,%%eax; xchg %%ah,%%al; " \
             "xchg %%eax,%%edx; " \
             "xchg %%ah,%%al; roll $16,%%eax; xchg %%ah,%%al" : "=A" (__x) : "0" ((UINT64)x)); \
        __x; \
})
#else
#define osif_swap64(x) \
({ \
        register UINT64 __x; \
        asm ("bswap %1" : "=r" (__x) : "0" ((UINT64)x)); \
        __x; \
})
#endif
#else    /* sorry, no inline assembler macros for you */
#define osif_swap64(x) \
({ \
        UINT64 __x = (x); \
        ((UINT64)( \
                (((UINT64)(__x) & (UINT64)0x00000000000000ffULL) << (8*7)) | \
                (((UINT64)(__x) & (UINT64)0x000000000000ff00ULL) << (8*5)) | \
                (((UINT64)(__x) & (UINT64)0x0000000000ff0000ULL) << (8*3)) | \
                (((UINT64)(__x) & (UINT64)0x00000000ff000000ULL) << (8*1)) | \
                (((UINT64)(__x) & (UINT64)0x000000ff00000000ULL) >> (8*1)) | \
                (((UINT64)(__x) & (UINT64)0x0000ff0000000000ULL) >> (8*3)) | \
                (((UINT64)(__x) & (UINT64)0x00ff000000000000ULL) >> (8*5)) | \
                (((UINT64)(__x) & (UINT64)0xff00000000000000ULL) >> (8*7)) )); \
})
#endif

#ifdef OSIF_LITTLE_ENDIAN
#define osif_cpu2be16(x) osif_swap16(x)
#define osif_cpu2be32(x) osif_swap32(x)
#define osif_cpu2be64(x) osif_swap64(x)
#define osif_be162cpu(x) osif_swap16(x)
#define osif_be322cpu(x) osif_swap32(x)
#define osif_be642cpu(x) osif_swap64(x)
#define osif_cpu2le16(x) (x)
#define osif_cpu2le32(x) (x)
#define osif_cpu2le64(x) (x)
#define osif_le162cpu(x) (x)
#define osif_le322cpu(x) (x)
#define osif_le642cpu(x) (x)
#else
#define osif_cpu2be16(x) (x)
#define osif_cpu2be32(x) (x)
#define osif_cpu2be64(x) (x)
#define osif_be162cpu(x) (x)
#define osif_be322cpu(x) (x)
#define osif_be642cpu(x) (x)
#define osif_cpu2le16(x) osif_swap16(x)
#define osif_cpu2le32(x) osif_swap32(x)
#define osif_cpu2le64(x) osif_swap64(x)
#define osif_le162cpu(x) osif_swap16(x)
#define osif_le322cpu(x) osif_swap32(x)
#define osif_le642cpu(x) osif_swap64(x)
#endif

#define osif_strtoul(pc,pe,b)   simple_strtoul(pc,pe,b)

extern INT32 OSIF_CALLTYPE osif_attach( VOID );
extern INT32 OSIF_CALLTYPE osif_detach( VOID );


#ifdef OSIF_BOARD_SPI
extern INT32 osif_spi_attach(OSIF_SPIDEV *pDev, uint32_t spiClk);
extern INT32 osif_spi_detach(OSIF_SPIDEV *pDev);
extern INT32 osif_spi_xfer(OSIF_SPIDEV *pDev, OSIF_SPIMSG *pMsg);
#endif

extern INT32 OSIF_CALLTYPE osif_malloc(UINT32 size, VOID **p);
extern INT32 OSIF_CALLTYPE osif_free(VOID *ptr);
extern INT32 OSIF_CALLTYPE osif_memset(VOID *ptr, UINT32 val, UINT32 size);
extern INT32 OSIF_CALLTYPE osif_memcpy(VOID *dst, VOID *src, UINT32 size);
extern INT32 OSIF_CALLTYPE osif_memcmp(VOID *dst, VOID *src, UINT32 size);

extern VOID OSIF_CALLTYPE set_output_mask(UINT32 mask);

#ifdef OSIF_OS_RTAI
# ifdef BOARD_pci405fw
extern INT32 OSIF_CALLTYPE pci405_printk(const char *fmt, ...);
extern INT32 OSIF_CALLTYPE pci405_printk_init( VOID );
extern INT32 OSIF_CALLTYPE pci405_printk_cleanup( VOID );
#  define osif_print(fmt... ) pci405_printk( ## fmt )
# else
#  define osif_print(fmt... ) rt_printk( ## fmt )
# endif
#else
extern INT32 OSIF_CALLTYPE osif_print(const CHAR8 *fmt, ...);
#endif
extern INT32 OSIF_CALLTYPE osif_dprint(UINT32 output_mask, const CHAR8 *fmt, ...);

extern INT32 OSIF_CALLTYPE osif_snprintf(CHAR8 *str, INT32 size, const CHAR8 *format, ...);

extern INT32 OSIF_CALLTYPE osif_mutex_create(OSIF_MUTEX *m);
extern INT32 OSIF_CALLTYPE osif_mutex_destroy(OSIF_MUTEX *m);
extern INT32 OSIF_CALLTYPE osif_mutex_lock(OSIF_MUTEX *m);
extern INT32 OSIF_CALLTYPE osif_mutex_unlock(OSIF_MUTEX *m);

extern INT32 OSIF_CALLTYPE osif_irq_mutex_create(OSIF_IRQ_MUTEX *im);
extern INT32 OSIF_CALLTYPE osif_irq_mutex_destroy(OSIF_IRQ_MUTEX *im);
extern INT32 OSIF_CALLTYPE osif_irq_mutex_lock(OSIF_IRQ_MUTEX *im);
extern INT32 OSIF_CALLTYPE osif_irq_mutex_unlock(OSIF_IRQ_MUTEX *im);

extern INT32 OSIF_CALLTYPE osif_sleep(INT32 ms);
extern INT32 OSIF_CALLTYPE osif_usleep(INT32 us);

extern INT32 OSIF_CALLTYPE osif_dpc_create( OSIF_DPC  *dpc, VOID(OSIF_CALLTYPE *func)(VOID *), VOID *arg );
extern INT32 OSIF_CALLTYPE osif_dpc_destroy( OSIF_DPC *dpc );
extern INT32 OSIF_CALLTYPE osif_dpc_trigger( OSIF_DPC *dpc );

extern INT32 OSIF_CALLTYPE osif_timer_create( OSIF_TIMER *timer, VOID(OSIF_CALLTYPE *func)(VOID *), VOID *arg, VOID *pCanNode );
extern INT32 OSIF_CALLTYPE osif_timer_destroy( OSIF_TIMER *timer );
extern INT32 OSIF_CALLTYPE osif_timer_set( OSIF_TIMER *timer, UINT32 ms );
extern INT32 OSIF_CALLTYPE osif_timer_get( OSIF_TIMER *t, UINT32 *ms );

extern UINT64 OSIF_CALLTYPE osif_ticks( VOID );
extern UINT64 OSIF_CALLTYPE osif_tick_frequency( VOID );

extern INT32 OSIF_CALLTYPE osif_pci_malloc(OSIF_PCIDEV pcidev, OSIF_PCI_VADDR *vaddr,
                                           OSIF_PCI_PADDR *paddr, OSIF_PCI_MADDR *maddr, UINT32 size);
extern INT32 OSIF_CALLTYPE osif_pci_free(OSIF_PCIDEV pcidev, OSIF_PCI_VADDR vaddr,
                                         OSIF_PCI_PADDR *paddr, OSIF_PCI_MADDR maddr, UINT32 size);
extern UINT32 OSIF_CALLTYPE osif_pci_get_phy_addr(OSIF_PCI_PADDR paddr);

extern INT32 OSIF_CALLTYPE osif_pci_read_config_byte(OSIF_PCIDEV pcidev, INT32 offs, UINT8 *ptr);
extern INT32 OSIF_CALLTYPE osif_pci_read_config_word(OSIF_PCIDEV pcidev, INT32 offs, UINT16 *ptr);
extern INT32 OSIF_CALLTYPE osif_pci_read_config_long(OSIF_PCIDEV pcidev, INT32 offs, UINT32 *ptr);
extern INT32 OSIF_CALLTYPE osif_pci_write_config_byte(OSIF_PCIDEV pcidev, INT32 offs, UINT8 val);
extern INT32 OSIF_CALLTYPE osif_pci_write_config_word(OSIF_PCIDEV pcidev, INT32 offs, UINT16 val);
extern INT32 OSIF_CALLTYPE osif_pci_write_config_long(OSIF_PCIDEV pcidev, INT32 offs, UINT32 val);

extern INT32 OSIF_CALLTYPE osif_load_from_file( UINT8 *destaddr, UINT8 *filename );

extern VOID OSIF_CALLTYPE osif_ser_out(CHAR8 *str);

#define osif_div64_32(n, base) _osif_div64_32_(&(n), (base))
extern UINT32 OSIF_CALLTYPE _osif_div64_32_(UINT64 *n, UINT32 base);

/*
 * If we get a serial it is assumed that it has the format CCNNNNNN where
 * C is a character from 'A'to 'P' and N is a number from '0' to '9'
 * This is converted into an 32-bit integer with bit 31-28 as alphabetical
 * offset to 'A' of the first char in serial, bit 27-24 as alphabetical
 * offset to 'A' of the second char in serial and the remaining 24 bits
 * as serial. So we have an effective range from AA000000 to PPFFFFFF.
 */
extern INT32 OSIF_CALLTYPE osif_make_ntcan_serial(const CHAR8 *pszSerial, UINT32 *pulSerial);

/*
 * If OSIF_TICK_FREQ is not defined here, UINT64 osif_tick_frequency()
 * must be implemented in osif.c
 *
 * But now the OSIF_TICK_FREQ became dependent on the kernel version we must
 * implement an osif_tick_frequency() function to avoid compiling a kernel
 * version dependent constant value into the precompiled binaries.
*/

#define OSIF_READB(base, reg)             (*(volatile UINT8* )((base)+(reg)))
#define OSIF_WRITEB(base, reg, data)      (*(volatile UINT8* )((base)+(reg))) = (data)

#define OSIF_KERNEL
#endif /* __KERNEL__ */

#define OSIF_ERRNO_BASE             0x00000100  /* base for esd-codes */

#endif
