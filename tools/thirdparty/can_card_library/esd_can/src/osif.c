/* -*- esdcan-c -*-
 * FILE NAME osif.c
 *
 * BRIEF MODULE DESCRIPTION
 *           OSIF implementation for Linux
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
/*! \file osif.c
    \brief OSIF implementation

    This file contains the implementation of all osif functions.
*/

/*---------------------------------------------------------------------------*/
/*                               INCLUDES                                    */
/*---------------------------------------------------------------------------*/
#include <linux/version.h>
#if (LINUX_VERSION_CODE <= KERNEL_VERSION(2,6,32))
# if (LINUX_VERSION_CODE >= KERNEL_VERSION(2,6,19))
#  include <linux/autoconf.h>
# else
#  include <linux/config.h>
# endif
#endif
#ifdef DISTR_SUSE
# undef CONFIG_MODVERSIONS
#endif
#ifdef CONFIG_MODVERSIONS
# if LINUX_VERSION_CODE >= KERNEL_VERSION(2,6,0)
#  include <config/modversions.h>
# else
#  include <linux/modversions.h>
# endif
# ifndef MODVERSIONS
#  define MODVERSIONS
# endif
#endif
#include <linux/kernel.h>
#include <linux/slab.h>
#include <linux/vmalloc.h>
#include <linux/init.h>
# if (LINUX_VERSION_CODE >= KERNEL_VERSION(2,6,18))
#   include <linux/uaccess.h>
# else
#   include <asm/uaccess.h>
# endif
#include <linux/io.h>
#include <linux/interrupt.h>
#include <linux/time.h>
#include <linux/pci.h>
#include <linux/types.h>
#include <linux/timer.h>
#include <linux/delay.h>
#ifdef LTT
# include <linux/trace.h>
#endif
#include <linux/errno.h>

#if LINUX_VERSION_CODE >= KERNEL_VERSION(2,6,0)
# include <linux/interrupt.h>
#endif

#if ( (LINUX_VERSION_CODE < KERNEL_VERSION(2,4,8)) && (LINUX_VERSION_CODE >= KERNEL_VERSION(2,4,0)) )
# if LINUX_VERSION_CODE > KERNEL_VERSION(2,6,22)
#  include <linux/fs.h>
# endif
#endif

#ifdef BOARD_mcp2515
/* Unfortunately we don't have defined BOARD_SPI in osif.c,      */
/* so we temporarily introduce an OSIF_BOARD_SPI define here ... */
# define OSIF_BOARD_SPI 1
#endif

#include <linux/sched.h>
#ifndef MAX_USER_RT_PRIO
#if LINUX_VERSION_CODE >= KERNEL_VERSION(2,6,0) /* for old kernels without MAX_USER_RT_PRIO there is no rt.h */
#include <linux/sched/rt.h> /* maybe it's hidden here now (newer kernels...) */
#endif
#endif

#include <osif.h>

#ifdef OSIF_PROVIDES_VSNPRINTF
  /* needed for vsnprintf */
# include <asm/div64.h>
# include <linux/ctype.h>
#endif

#ifdef OSIF_USE_PREEMPT_RT_IMPLEMENTATION
# include <linux/kthread.h>
#endif

/*---------------------------------------------------------------------------*/
/*                                DEFINES                                    */
/*---------------------------------------------------------------------------*/
#ifdef ESDDBG
# define OSIF_DEBUG                       /*!< enables debug output for osif functions */
#endif

#ifdef OSIF_DEBUG
# define OSIF_DBG(fmt)          OSIF_DPRINT(fmt) /*!< Macro for debug prints */
#else
# define OSIF_DBG(fmt)
#endif

#ifdef KBUILD_MODNAME
#       define  K_DPC_NAME      "k" KBUILD_MODNAME
#else
#       define  K_DPC_NAME      "dpc thread"
#endif

/*---------------------------------------------------------------------------*/
/*                                TYPEDEFS                                   */
/*---------------------------------------------------------------------------*/

#ifdef OSIF_USE_PREEMPT_RT_IMPLEMENTATION
struct __OSIF_MUTEX {
        struct mutex lock;
};

#ifdef CONFIG_DEBUG_MUTEXES
#include <linux/atomic.h>
#define OSIF_MAX_DEBUG_MUTEXES 128
static atomic_t osif_debug_mutexes_cnt;
static struct lock_class_key osif_debug_mutexes_keys[OSIF_MAX_DEBUG_MUTEXES];
#endif

#else
struct __OSIF_MUTEX {
        struct semaphore sema;
};
#endif  /* #ifdef OSIF_USE_PREEMPT_RT_IMPLEMENTATION */

struct __OSIF_SPINLOCK {
        spinlock_t spinlock;
        UINTPTR    flags;
        UINT32     magic;
};

struct _OSIF_LINUX_TIMER {
        struct timer_list   timer;
        OSIF_DPC            dpc;
};

struct __OSIF_PCI_PADDR {
        UINT32              addr32;
        dma_addr_t          sys_dma_addr;
};

static struct {
        OSIF_DPC                 first;
        spinlock_t               spinlock;
        INT32                    thread_running;
        INT32                    destroy;
#ifdef OSIF_USE_PREEMPT_RT_IMPLEMENTATION
        wait_queue_head_t        wqDpcNotify;
        atomic_t                 trig;
        struct task_struct      *tsk;
#else
        struct semaphore         sema_notify;
        struct semaphore         sema_trigger;
#endif
} dpc_root;

OSIF_CALLBACKS  osif_callbacks = {
        osif_timer_create,
        osif_timer_destroy,
        osif_timer_set,
        osif_timer_get,
};

#if LINUX_VERSION_CODE >= KERNEL_VERSION(2,4,0)
DECLARE_COMPLETION(dpcThreadCompletion);
#endif

/*---------------------------------------------------------------------------*/
/*                 DEFINITION OF LOCAL DATA                                  */
/*---------------------------------------------------------------------------*/


/*---------------------------------------------------------------------------*/
/*                 DECLARATION OF LOCAL FUNCTIONS                            */
/*---------------------------------------------------------------------------*/
static INT32 osif_dpc_root_create(VOID);
static INT32 osif_dpc_root_destroy(VOID);


/*---------------------------------------------------------------------------*/
/*                 DEFINITION OF GLOBAL DATA                                 */
/*---------------------------------------------------------------------------*/

extern UINT32 verbose;  /* has to be declared in OS-level-sources (esdcan.c), should be set by module-parameter */

INT32  osif_div64_sft = 0; /* see extern declaration osif.h */


/*---------------------------------------------------------------------------*/
/*                 DEFINITION OF EXPORTED FUNCTIONS                          */
/*---------------------------------------------------------------------------*/

#if defined(OSIF_BOARD_SPI)
int osif_spi_xfer(OSIF_SPIDEV *pDev, OSIF_SPIMSG *pMsg)
{
  int ret;

#if 0
        {
                int i;

                printk("%s:l=%d  in=", __FUNCTION__, pMsg->nBytes);
                for(i =0; i < pMsg->nBytes; i++) {
                        printk("%02x ", pMsg->io[i]);
                }
                printk("\n");
        }
#endif
        ret = pDev->scdev->pdsd->sync_xfer(pDev->scdev, pMsg);
        if (ret) {
                osif_print("%s: spi transfer failed: ret=%d\n", __FUNCTION__, ret);
                return ret;
        }
#if 0
        {
                int i;

                printk("%s:l=%d out=", __FUNCTION__, pMsg->nBytes);
                for(i =0; i < pMsg->nBytes; i++) {
                        printk("%02x ", pMsg->io[i]);
                }
                printk("\n");
        }
#endif
        return(OSIF_SUCCESS);
}
#endif /* OSIF_BOARD_SPI */

INT32 OSIF_CALLTYPE osif_attach()
{
        INT32 result;

        OSIF_DBG((OSIF_ZONE_OSIF, "%s: enter\n", OSIF_FUNCTION));
        result = osif_dpc_root_create();
        OSIF_DIV64_SFT_FIXUP();
        OSIF_DBG((OSIF_ZONE_OSIF, "%s: leave\n", OSIF_FUNCTION));
        return result;
}

INT32 OSIF_CALLTYPE osif_detach()
{
        INT32 result;

        OSIF_DBG((OSIF_ZONE_OSIF, "%s: enter\n", OSIF_FUNCTION));
        result = osif_dpc_root_destroy();
        OSIF_DBG((OSIF_ZONE_OSIF, "%s: leave\n", OSIF_FUNCTION));
        return result;
}

/*! Allocate \a size bytes of memory. A pointer to the new allocated memory is
  returned through \a **p.
*/
#define OSIF_MEM_IS_NOTUSED 0x00000000
#define OSIF_MEM_IS_KMEM    0x11111111
#define OSIF_MEM_IS_VMEM    0x22222222
INT32 OSIF_CALLTYPE osif_malloc(UINT32 size, VOID **p)
{
        VOID    *ptr;

        OSIF_DBG((OSIF_ZONE_OSIF, "%s: enter, size=%08x\n", OSIF_FUNCTION,size));
        ptr = kmalloc(size + sizeof(UINT32), GFP_KERNEL);
        if (!ptr) {
                OSIF_DBG((OSIF_ZONE_OSIF, "%s: kmalloc for %d bytes failed, using vmalloc\n", OSIF_FUNCTION, size));
                ptr = vmalloc(size + sizeof(UINT32));
                if (!ptr) {
                        *p = NULL;
                        OSIF_DBG((OSIF_ZONE_OSIF, "%s: OSIF_MALLOC failed !!!!\n", OSIF_FUNCTION));
                        return OSIF_INSUFFICIENT_RESOURCES;
                } else {
                        *(UINT32*)ptr = OSIF_MEM_IS_VMEM;
                }
        } else {
                *(UINT32*)ptr = OSIF_MEM_IS_KMEM;
        }
        *p = (VOID*)((UINT8*)ptr + sizeof(UINT32));
        OSIF_DBG((OSIF_ZONE_OSIF, "%s: leave\n", OSIF_FUNCTION));
        return OSIF_SUCCESS;
}

/*! Free memory that has been allocated by osif_malloc. \a ptr points to the
  pointer returned by osif_malloc().
*/
INT32 OSIF_CALLTYPE osif_free(VOID *ptr)
{
        UINT32 *pFree = (UINT32*)((UINT8*)ptr - sizeof(UINT32));

        if (ptr) {
                if (*pFree == OSIF_MEM_IS_KMEM) {
                        OSIF_DBG((OSIF_ZONE_OSIF, "%s: using kfree\n", OSIF_FUNCTION));
                        *pFree = OSIF_MEM_IS_NOTUSED;
                        kfree(pFree);
                } else if (*pFree == OSIF_MEM_IS_VMEM) {
                        OSIF_DBG((OSIF_ZONE_OSIF, "%s: using vfree\n", OSIF_FUNCTION));
                        *pFree = OSIF_MEM_IS_NOTUSED;
                        vfree(pFree);
                } else {
                        OSIF_DBG((OSIF_ZONE_OSIF, "%s: Either unknown mem type or forbidden free!!!\n", OSIF_FUNCTION));
                }
        }
        return OSIF_SUCCESS;
}

/*! Initialize a memory region pointed by \a ptr to a constant value \a val.
  \a size is the size of the region.
*/
INT32 OSIF_CALLTYPE osif_memset(VOID *ptr, UINT32 val, UINT32 size)
{
        if (ptr) {
                memset(ptr, (char)val, size);
        }
        return OSIF_SUCCESS;
}

INT32 OSIF_CALLTYPE osif_memcpy(VOID *dst, VOID *src, UINT32 size)
{
        memcpy(dst, src, size);
        return OSIF_SUCCESS;
}

INT32 OSIF_CALLTYPE osif_memcmp(VOID *dst, VOID *src, UINT32 size)
{
        return memcmp(dst, src, size);
}

INT32 OSIF_CALLTYPE osif_pci_read_config_byte(OSIF_PCIDEV pcidev, INT32 offs, UINT8 *ptr)
{
#ifdef CONFIG_PCI
        pci_read_config_byte(pcidev, offs, ptr);
#endif
        return OSIF_SUCCESS;
}

INT32 OSIF_CALLTYPE osif_pci_read_config_word(OSIF_PCIDEV pcidev, INT32 offs, UINT16 *ptr)
{
#ifdef CONFIG_PCI
        pci_read_config_word(pcidev, offs, ptr);
#endif
        return OSIF_SUCCESS;
}

INT32 OSIF_CALLTYPE osif_pci_read_config_long(OSIF_PCIDEV pcidev, INT32 offs, UINT32 *ptr)
{
#ifdef CONFIG_PCI
        pci_read_config_dword(pcidev, offs, (u32 *)ptr);
#endif
        return OSIF_SUCCESS;
}

INT32 OSIF_CALLTYPE osif_pci_write_config_byte(OSIF_PCIDEV pcidev, INT32 offs, UINT8 val)
{
#ifdef CONFIG_PCI
        pci_write_config_byte(pcidev, offs, val);
#endif
        return OSIF_SUCCESS;
}

INT32 OSIF_CALLTYPE osif_pci_write_config_word(OSIF_PCIDEV pcidev, INT32 offs, UINT16 val)
{
#ifdef CONFIG_PCI
        pci_write_config_word(pcidev, offs, val);
#endif
        return OSIF_SUCCESS;
}

INT32 OSIF_CALLTYPE osif_pci_write_config_long(OSIF_PCIDEV pcidev, INT32 offs, UINT32 val)
{
#ifdef CONFIG_PCI
        pci_write_config_dword(pcidev, offs, val);
#endif
        return OSIF_SUCCESS;
}

#if LINUX_VERSION_CODE < KERNEL_VERSION(2,4,0)
static inline void *pci_alloc_consistent(struct pci_dev *hwdev, size_t size,
                                         dma_addr_t *dma_handle)
{
        void *virt_ptr;

        virt_ptr = kmalloc(size, GFP_KERNEL);
        *dma_handle = virt_to_bus(virt_ptr);
        return virt_ptr;
}
#define pci_free_consistent(cookie, size, ptr, dma_ptr) kfree(ptr)
#endif

INT32 OSIF_CALLTYPE osif_pci_malloc(OSIF_PCIDEV pcidev, OSIF_PCI_VADDR *vaddr,
                                    OSIF_PCI_PADDR *paddr, OSIF_PCI_MADDR *maddr, UINT32 size)
{
        OSIF_DBG((OSIF_ZONE_OSIF, "%s: enter\n", OSIF_FUNCTION));
        *paddr = vmalloc( sizeof( **paddr ) );
        if ( NULL == *paddr) {
                return OSIF_INSUFFICIENT_RESOURCES;
        }
#if  (LINUX_VERSION_CODE >= KERNEL_VERSION(2,6,11))
/* LXR today reachs only back to 2.6.11 where pci_set_consistent_dma_mask() was available, probably way earlier */
#if !defined(DMA_BIT_MASK)      /* First defined in 2.6.24 */
        #define DMA_BIT_MASK(n)	(((n) == 64) ? ~0ULL : ((1ULL<<(n))-1))
#endif
        if (pci_set_consistent_dma_mask(pcidev, DMA_BIT_MASK(32))) {
               OSIF_PRINT(("esd CAN driver: No 32-Bit bus master buffer available.\n"));
               return OSIF_INSUFFICIENT_RESOURCES;
        }
#endif
        *vaddr = pci_alloc_consistent( pcidev, size, &((*paddr)->sys_dma_addr) );
        if ( NULL == *vaddr ) {
                vfree( *paddr );
                return OSIF_INSUFFICIENT_RESOURCES;
        }
        (*paddr)->addr32 = (UINT32)((*paddr)->sys_dma_addr);
        if ((dma_addr_t)((*paddr)->addr32) != (*paddr)->sys_dma_addr) {
                OSIF_PRINT(("esd CAN driver: Bus master addr conflict: dma 0x%llx(%u), addr32 0x%lx(%u)\n",
                            (unsigned long long)((*paddr)->sys_dma_addr), sizeof (*paddr)->sys_dma_addr,
                            (*paddr)->addr32, sizeof (*paddr)->addr32));
        }
        OSIF_DBG((OSIF_ZONE_OSIF, "%s: leave\n", OSIF_FUNCTION));
        return OSIF_SUCCESS;
}

INT32 OSIF_CALLTYPE osif_pci_free(OSIF_PCIDEV pcidev, OSIF_PCI_VADDR vaddr,
                                  OSIF_PCI_PADDR *paddr, OSIF_PCI_MADDR maddr, UINT32 size)
{
        OSIF_DBG((OSIF_ZONE_OSIF, "%s: enter\n", OSIF_FUNCTION));
        pci_free_consistent(pcidev, size, vaddr, (*paddr)->sys_dma_addr );
        vfree( *paddr );
        OSIF_DBG((OSIF_ZONE_OSIF, "%s: leave\n", OSIF_FUNCTION));
        return OSIF_SUCCESS;
}

UINT32 OSIF_CALLTYPE osif_pci_get_phy_addr(OSIF_PCI_PADDR paddr)
{
        return paddr->addr32;
}

#ifdef OSIF_PROVIDES_VSNPRINTF
#warning "Using internal vsnprintf() implementation"
#define ZEROPAD 1               /* pad with zero */
#define SIGN    2               /* unsigned/signed long */
#define PLUS    4               /* show plus */
#define SPACE   8               /* space if plus */
#define LEFT    16              /* left justified */
#define SPECIAL 32              /* 0x */
#define LARGE   64              /* use 'ABCDEF' instead of 'abcdef' */
/*!
 *  \brief Needed for vsnprintf()
 */
static INT32 skip_atoi(const CHAR8 **s)
{
        INT32 i = 0;

        while (isdigit(**s))
                i = i*10 + *((*s)++) - '0';
        return i;
}

/*!
 *  \brief Needed for vsnprintf()
 */
static CHAR8* number(CHAR8* buf, CHAR8* end, UINT64 num, INT32 base, INT32 size, INT32 precision, INT32 type)
{
        CHAR8        c, sign, tmp[66];
        const CHAR8 *digits;
        const CHAR8  small_digits[] = "0123456789abcdefghijklmnopqrstuvwxyz";
        const CHAR8  large_digits[] = "0123456789ABCDEFGHIJKLMNOPQRSTUVWXYZ";
        INT32        i;

        digits = (type & LARGE) ? large_digits : small_digits;
        if (type & LEFT) {
                type &= ~ZEROPAD;
        }
        if (base < 2 || base > 36) {
                return 0;
        }
        c = (type & ZEROPAD) ? '0' : ' ';
        sign = 0;
        if (type & SIGN) {
                if ((INT64)num < 0) {
                        sign = '-';
                        num = -(INT64)num;
                        size--;
                } else if (type & PLUS) {
                        sign = '+';
                        size--;
                } else if (type & SPACE) {
                        sign = ' ';
                        size--;
                }
        }
        if (type & SPECIAL) {
                if (base == 16)
                        size -= 2;
                else if (base == 8)
                        size--;
        }
        i = 0;
        if (num == 0) {
                tmp[i++]='0';
        } else {
                while (num != 0) {
                        tmp[i++] = digits[do_div(num,base)];
                }
        }
        if (i > precision) {
                precision = i;
        }
        size -= precision;
        if (!(type&(ZEROPAD+LEFT))) {
                while(size-->0) {
                        if (buf <= end) {
                                *buf = ' ';
                        }
                        ++buf;
                }
        }
        if (sign) {
                if (buf <= end) {
                        *buf = sign;
                }
                ++buf;
        }
        if (type & SPECIAL) {
                if (base==8) {
                        if (buf <= end) {
                                *buf = '0';
                        }
                        ++buf;
                } else if (base==16) {
                        if (buf <= end) {
                                *buf = '0';
                        }
                        ++buf;
                        if (buf <= end) {
                                *buf = digits[33];
                        }
                        ++buf;
                }
        }
        if (!(type & LEFT)) {
                while (size-- > 0) {
                        if (buf <= end) {
                                *buf = c;
                        }
                        ++buf;
                }
        }
        while (i < precision--) {
                if (buf <= end) {
                        *buf = '0';
                }
                ++buf;
        }
        while (i-- > 0) {
                if (buf <= end) {
                        *buf = tmp[i];
                }
                ++buf;
        }
        while (size-- > 0) {
                if (buf <= end) {
                        *buf = ' ';
                }
                ++buf;
        }
        return buf;
}

/*!
 * \brief Format a string and place it in a buffer
 *
 * \param buf The buffer to place the result into
 * \param size The size of the buffer, including the trailing null space
 * \param fmt The format string to use
 * \param args Arguments for the format string
 *
 *  This function was copied directly out of the 2.4.18.SuSE-kernel.
 *  Since kernels pre 2.4.6 don't support this function, we need to
 *  provide it on our own.
 */
INT32 OSIF_CALLTYPE osif_vsnprintf(CHAR8 *buf, size_t size, const CHAR8 *fmt, va_list args)
{
        INT32        len;
        UINT64       num;
        INT32        i, base;
        CHAR8       *str, *end, c;
        const CHAR8 *s;
        INT32 flags;            /* flags to number() */
        INT32 field_width;      /* width of output field */
        INT32 precision;        /* min. # of digits for integers; max
                                   number of chars for from string */
        INT32 qualifier;        /* 'h', 'l', or 'L' for integer fields */
                                /* 'z' support added 23/7/1999 S.H.    */
                                /* 'z' changed to 'Z' --davidm 1/25/99 */

        str = buf;
        end = buf + size - 1;
        if (end < buf - 1) {
                end = ((void *) (-1));
                size = end - buf + 1;
        }
        for (; *fmt ; ++fmt) {
                if (*fmt != '%') {
                        if (str <= end) {
                                *str = *fmt;
                        }
                        ++str;
                        continue;
                }
                /* process flags */
                flags = 0;
                repeat:
                        ++fmt;          /* this also skips first '%' */
                        switch (*fmt) {
                        case '-': flags |= LEFT; goto repeat;
                        case '+': flags |= PLUS; goto repeat;
                        case ' ': flags |= SPACE; goto repeat;
                        case '#': flags |= SPECIAL; goto repeat;
                        case '0': flags |= ZEROPAD; goto repeat;
                        }
                /* get field width */
                field_width = -1;
                if (isdigit(*fmt)) {
                        field_width = skip_atoi(&fmt);
                } else if (*fmt == '*') {
                        ++fmt;
                        /* it's the next argument */
                        field_width = va_arg(args, INT32);
                        if (field_width < 0) {
                                field_width = -field_width;
                                flags |= LEFT;
                        }
                }
                /* get the precision */
                precision = -1;
                if (*fmt == '.') {
                        ++fmt;
                        if (isdigit(*fmt)) {
                                precision = skip_atoi(&fmt);
                        } else if (*fmt == '*') {
                                ++fmt;
                                /* it's the next argument */
                                precision = va_arg(args, INT32);
                        }
                        if (precision < 0) {
                                precision = 0;
                        }
                }
                /* get the conversion qualifier */
                qualifier = -1;
                if (*fmt == 'h' || *fmt == 'l' || *fmt == 'L' || *fmt =='Z') {
                        qualifier = *fmt;
                        ++fmt;
                        if (qualifier == 'l' && *fmt == 'l') {
                                qualifier = 'L';
                                ++fmt;
                        }
                }
                /* default base */
                base = 10;
                switch (*fmt) {
                        case 'c':
                                if (!(flags & LEFT)) {
                                        while (--field_width > 0) {
                                                if (str <= end) {
                                                        *str = ' ';
                                                }
                                                ++str;
                                        }
                                }
                                c = (CHAR8)va_arg(args, INT32);
                                if (str <= end) {
                                        *str = c;
                                }
                                ++str;
                                while (--field_width > 0) {
                                        if (str <= end) {
                                                *str = ' ';
                                        }
                                        ++str;
                                }
                                continue;

                        case 's':
                                s = va_arg(args, CHAR8*);
                                if (!s)
                                        s = "<NULL>";
                                len = strnlen(s, precision);
                                if (!(flags & LEFT)) {
                                        while (len < field_width--) {
                                                if (str <= end) {
                                                        *str = ' ';
                                                }
                                                ++str;
                                        }
                                }
                                for (i = 0; i < len; ++i) {
                                        if (str <= end) {
                                                *str = *s;
                                        }
                                        ++str; ++s;
                                }
                                while (len < field_width--) {
                                        if (str <= end) {
                                                *str = ' ';
                                        }
                                        ++str;
                                }
                                continue;

                        case 'p':
                                if (field_width == -1) {
                                        field_width = 2*sizeof(void*);
                                        flags |= ZEROPAD;
                                }
                                str = number(str, end, (UINTPTR)va_arg(args, void*),
                                             16, field_width, precision, flags);
                                continue;

                        case 'n':
                                /* FIXME:
                                * What does C99 say about the overflow case here? */
                                if (qualifier == 'l') {
                                        INT32 *ip = va_arg(args, INT32*);
                                        *ip = (str - buf);
                                } else if (qualifier == 'Z') {
                                        size_t *ip = va_arg(args, size_t*);
                                        *ip = (str - buf);
                                } else {
                                        INT32 *ip = va_arg(args, INT32*);
                                        *ip = (str - buf);
                                }
                                continue;

                        case '%':
                                if (str <= end) {
                                        *str = '%';
                                }
                                ++str;
                                continue;

                                /* integer number formats - set up the flags and "break" */
                        case 'o':
                                base = 8;
                                break;

                        case 'X':
                                flags |= LARGE; /* fallthrough */
                        case 'x':
                                base = 16;
                                break;

                        case 'd':
                        case 'i':
                                flags |= SIGN;
                        case 'u':
                                break;

                        default:
                                if (str <= end) {
                                        *str = '%';
                                }
                                ++str;
                                if (*fmt) {
                                        if (str <= end) {
                                                *str = *fmt;
                                        }
                                        ++str;
                                } else {
                                        --fmt;
                                }
                                continue;
                }
                if (qualifier == 'L')
                        num = va_arg(args, INT64);
                else if (qualifier == 'l') {
                        num = va_arg(args, UINT32);
                        if (flags & SIGN) {
                                num = (INT32) num;
                        }
                } else if (qualifier == 'Z') {
                        num = va_arg(args, size_t);
                } else if (qualifier == 'h') {
                        num = (UINT16)va_arg(args, INT32);
                        if (flags & SIGN) {
                                num = (INT16) num;
                        }
                } else {
                        num = va_arg(args, UINT32);
                        if (flags & SIGN) {
                                num = (INT32) num;
                        }
                }
                str = number(str, end, num, base, field_width, precision, flags);
        }
        if (str <= end) {
                *str = '\0';
        } else if (size > 0) {
                /* don't write out a null byte if the buf size is zero */
                *end = '\0';
        }
        /* the trailing null byte doesn't count towards the total
         * ++str;
         */
        return str-buf;
}
#endif  /* ifdef OSIF_PROVIDES_VSNPRINTF */

/*! This function prints a formated text string.
*/
INT32 OSIF_CALLTYPE osif_print(const CHAR8 *fmt, ...)
{
        va_list arglist;
        INT32   len;

#ifdef OSIF_USE_VPRINTK
        va_start(arglist, fmt);
        len = vprintk(fmt, arglist);
        va_end(arglist);
#else
        CHAR8   output[400];

        va_start(arglist, fmt);
        len = OSIF_VSNPRINTF(output, 400, fmt, arglist);
        va_end(arglist);
        printk("%s", output);
#endif
        return len;
}

/*! This function prints a formated text string, only, if one of the bits
 *  specified in output_mask was set at module-load-time (global variable verbose).
 */
INT32 OSIF_CALLTYPE osif_dprint(UINT32 output_mask, const CHAR8 *fmt, ...)
{
        va_list arglist;
        INT32   len = 0;
        UINT32  verbose_flags = verbose;

#ifndef ESDDBG
        verbose_flags &= 0x000000FF;
#endif
        if ( (verbose_flags & output_mask) == output_mask ) {
#ifdef OSIF_USE_VPRINTK
                va_start(arglist, fmt);
                len = vprintk(fmt, arglist);
                va_end(arglist);
#else
                CHAR8   output[400];

                va_start(arglist, fmt);
                len = OSIF_VSNPRINTF(output, 400, fmt, arglist);
                va_end(arglist);
                printk("%s", output);
#endif
        }
        return len;
}

INT32 OSIF_CALLTYPE osif_snprintf(CHAR8 *str, INT32 size, const CHAR8 *format, ...)
{
        va_list arglist;
        INT32   len;

        va_start(arglist, format);
        len = OSIF_VSNPRINTF(str, size, format, arglist);
        va_end(arglist);
        return len;
}

/*! Sleep for a given number (\a ms) of milli seconds.
*/
INT32 OSIF_CALLTYPE osif_sleep( INT32 ms )
{
# if LINUX_VERSION_CODE >= KERNEL_VERSION(2,6,0)
        wait_queue_head_t wq;
        INT32  result = OSIF_SUCCESS;
        UINT32 timeout = ((ms*HZ)+999)/1000;

        init_waitqueue_head(&wq);
        result = wait_event_interruptible_timeout(wq, (timeout == 0), timeout);
        if (result == -ERESTARTSYS) {
                OSIF_DBG((OSIF_ZONE_OSIF, "%s: Sleep cancelled by SIGTERM!", OSIF_FUNCTION));
        }
#else
        OSIF_DECL_WAIT_QUEUE(p);
        interruptible_sleep_on_timeout( &p, ((ms*HZ)+999)/1000);
#endif
        return OSIF_SUCCESS;
}

/*! (Possibly busy-) sleep for a given number (\a us) of microseconds.
*/
INT32 OSIF_CALLTYPE osif_usleep( INT32 us )
{
        udelay(us);
        return OSIF_SUCCESS;
}


/*
** mutex entries
*/
INT32 OSIF_CALLTYPE osif_mutex_create(OSIF_MUTEX *m)
{
        *m = vmalloc(sizeof(**m));
        if(NULL == *m) {
                return OSIF_INSUFFICIENT_RESOURCES;
        }
        memset(*m, 0x00, sizeof(**m));
#ifdef OSIF_USE_PREEMPT_RT_IMPLEMENTATION
#ifdef CONFIG_DEBUG_MUTEXES
        {
                int nr = atomic_inc_return(&osif_debug_mutexes_cnt)-1;
                if (nr >= OSIF_MAX_DEBUG_MUTEXES) {
                        vfree(*m);
                        *m = NULL;
                        return OSIF_INSUFFICIENT_RESOURCES;
                }
                __mutex_init(&((*m)->lock), "osif_mutex", &osif_debug_mutexes_keys[nr]);
        }
#else
        mutex_init(&((*m)->lock));
#endif
#else
        sema_init(&((*m)->sema), 1);
#endif
        return OSIF_SUCCESS;
}

INT32 OSIF_CALLTYPE osif_mutex_destroy(OSIF_MUTEX *m)
{
        vfree(*m);
        *m = NULL;
        return OSIF_SUCCESS;
}

INT32 OSIF_CALLTYPE osif_mutex_lock(OSIF_MUTEX *m)
{
#ifdef OSIF_USE_PREEMPT_RT_IMPLEMENTATION
        mutex_lock(&((*m)->lock));
#else
        down(&((*m)->sema));
#endif
        return OSIF_SUCCESS;
}

INT32 OSIF_CALLTYPE osif_mutex_unlock(OSIF_MUTEX *m)
{
#ifdef OSIF_USE_PREEMPT_RT_IMPLEMENTATION
        mutex_unlock(&((*m)->lock));
#else
        up(&((*m)->sema));
#endif
        return OSIF_SUCCESS;
}

/*
 * mutexes for synchronisation against the irq-level
 */
INT32 OSIF_CALLTYPE osif_irq_mutex_create(OSIF_IRQ_MUTEX *im)
{
        *im = vmalloc(sizeof(**im));
        if(NULL == *im) {
                return OSIF_INSUFFICIENT_RESOURCES;
        }
#if LINUX_VERSION_CODE >= KERNEL_VERSION(2,6,18)
        spin_lock_init(&(((*im)->spinlock)));
#else
        (*im)->spinlock = SPIN_LOCK_UNLOCKED;
#endif
#ifdef OSIF_DEBUG
        (*im)->magic = 0x0;
#endif
        return OSIF_SUCCESS;
}

INT32 OSIF_CALLTYPE osif_irq_mutex_destroy(OSIF_IRQ_MUTEX *im)
{
        vfree(*im);
        *im = NULL;
        return OSIF_SUCCESS;
}

/*
 *  Call this entry, if you are not inside in an irq handler
 */
INT32 OSIF_CALLTYPE osif_irq_mutex_lock(OSIF_IRQ_MUTEX *im)
{
#ifdef OSIF_DEBUG
        struct task_struct *tsk = current;
#endif
        UINTPTR flags;
        spin_lock_irqsave(&((*im)->spinlock), flags);
        (*im)->flags = flags;
#ifdef OSIF_DEBUG
        (*im)->magic = tsk->pid | 0x80000000; /* MSB=1 marks entry */
#endif
        return OSIF_SUCCESS;
}

/*
 *  Call this entry, if you are not inside an irq handler
 */
INT32 OSIF_CALLTYPE osif_irq_mutex_unlock(OSIF_IRQ_MUTEX *im)
{
        UINTPTR flags = (*im)->flags;
#ifdef OSIF_DEBUG
        struct task_struct *tsk = current;
        (*im)->magic = tsk->pid; /* MSB=0 marks exit (assuming pid's smaller than 0x7FFFFFFF) */
#endif
        spin_unlock_irqrestore(&((*im)->spinlock), flags);
        return OSIF_SUCCESS;
}


/* --------------------------------------------------------------------------------
 *      kernel thread that handles all our OSIF_DPC jobs
 */
static int osif_dpc_thread( void *context )
{
#if LINUX_VERSION_CODE < KERNEL_VERSION(2,6,0)
        struct task_struct *tsk = current;
#endif

#if LINUX_VERSION_CODE >= KERNEL_VERSION(2,6,0)
        /* Code for Linux version range: 2.4.0 <= LXV < 2.6.0 */
        OSIF_DBG((OSIF_ZONE_OSIF, "%s: enter\n", OSIF_FUNCTION));

#if LINUX_VERSION_CODE < KERNEL_VERSION(3,4,0)
        daemonize(K_DPC_NAME);  /* Call wasn't really needed but didn't harm before 3.4. */
#endif
#ifdef OSIF_BOARD_SPI
        {
                extern int esdcan_spi_connector_set_cur_tsk_sched(int policy, const unsigned int prio);
                esdcan_spi_connector_set_cur_tsk_sched(SCHED_FIFO, MAX_USER_RT_PRIO-1);
        }
#endif /* ifdef OSIF_BOARD_SPI */
# if 0

/* BL TODO: set affinity to CPU, which executes interrupts (to get accurate timestamps...)
long sched_setaffinity(pid_t pid, cpumask_t new_mask)
long sched_getaffinity(pid_t pid, cpumask_t *mask)
 */
        /* Rescheduling of this kernel thread could be done with the following call
         * if we were allowed to use that GPL only function. Therefore the user has
         * to use 'chrt' or 'renice' to set a scheduling policy and priority suitable
         * for his setup.
         */
        {
                struct sched_param param = { .sched_priority = MAX_USER_RT_PRIO/2, };
                sched_setscheduler(current, SCHED_FIFO, &param);
        }
# endif

#elif LINUX_VERSION_CODE >= KERNEL_VERSION(2,4,0)
        /* Code for Linux version range: 2.4.0 <= LXV < 2.6.0 */
        OSIF_DBG((OSIF_ZONE_OSIF, "%s: enter tsk=%p\n", OSIF_FUNCTION, tsk));
        daemonize();
        /* todo: do we need this ? */ /*  tsk->pgrp = 1; */
        sigfillset(&tsk->blocked); /* block all signals */
        strcpy(tsk->comm, K_DPC_NAME);
        /* mf test-only */
        tsk->policy = 1; /* SCHED_FIFO */
        tsk->rt_priority = 98; /* max */
        tsk->need_resched = 1;

#else
        /* Code for Linux version range: LXV < 2.4.0 */
        OSIF_DBG((OSIF_ZONE_OSIF, "%s: enter tsk=%p\n", OSIF_FUNCTION, tsk));
        tsk->session = 1;
        tsk->pgrp = 1;
        strcpy(tsk->comm, K_DPC_NAME);
        spin_lock_irq(&tsk->sigmask_lock);
        sigfillset(&tsk->blocked);             /* block all signals */
        recalc_sigpending(tsk);
        spin_unlock_irq(&tsk->sigmask_lock);
        /* BL TODO: check if realtime priorities can be realized
                    with kernels below 2.4.0 */
#endif

        OSIF_DBG((OSIF_ZONE_OSIF, "%s: can dpc running\n", OSIF_FUNCTION));
        /* notify that backend thread is running */
        dpc_root.thread_running = 1;
#ifdef OSIF_USE_PREEMPT_RT_IMPLEMENTATION
        wake_up(&dpc_root.wqDpcNotify);
        __set_current_state(TASK_RUNNING);
#else
        up(&dpc_root.sema_notify);
#endif
        while (!dpc_root.destroy) {
#ifdef OSIF_USE_PREEMPT_RT_IMPLEMENTATION
                atomic_add_unless(&dpc_root.trig, -1, 0);  /* BL: In with 2.6.15 */
                smp_mb();
#else
                if (down_interruptible(&dpc_root.sema_trigger)<0) {
                        continue;
                }
                if (dpc_root.destroy) {
                        break;
                }
#endif
                /* call dpc function */
                OSIF_DBG((OSIF_ZONE_OSIF, "%s: dpc triggered\n", OSIF_FUNCTION));
                spin_lock_irq( &dpc_root.spinlock );
                while( NULL != dpc_root.first ) {
                        OSIF_DPC dpc;
                        dpc = dpc_root.first;
                        dpc_root.first = dpc->next;    /* link out          */
                        dpc->linked = 0;               /* mark: linked out  */
                        dpc->running = 1;              /* mark: running     */
                        spin_unlock_irq( &dpc_root.spinlock );
                        dpc->func(dpc->arg);
                        spin_lock_irq( &dpc_root.spinlock );
                        dpc->running = 0;              /* mark: not running */
                }
#ifdef OSIF_USE_PREEMPT_RT_IMPLEMENTATION
                set_current_state(TASK_INTERRUPTIBLE);
                if (!atomic_read(&dpc_root.trig)) {
                        spin_unlock_irq( &dpc_root.spinlock );
                        schedule();
                } else {
                        spin_unlock_irq( &dpc_root.spinlock );
                }
                __set_current_state(TASK_RUNNING);
#else
                spin_unlock_irq( &dpc_root.spinlock );
#endif
        }
        /* notify that backend thread is exiting */
        dpc_root.thread_running = 0;
#ifdef OSIF_USE_PREEMPT_RT_IMPLEMENTATION
        wake_up(&dpc_root.wqDpcNotify);
#else
        up(&dpc_root.sema_notify);
#endif
        OSIF_DBG((OSIF_ZONE_OSIF, "%s: leave\n", OSIF_FUNCTION));
#if LINUX_VERSION_CODE >= KERNEL_VERSION(2,4,0)
        complete_and_exit(&dpcThreadCompletion, 0);
#endif
        return 0;  /* This will never reached, if kernel >= 2.4.0 */
}

static INT32 osif_dpc_root_create( VOID )
{
#ifndef OSIF_USE_PREEMPT_RT_IMPLEMENTATION
        INT32 threadId;
#endif

        OSIF_DBG((OSIF_ZONE_OSIF, "%s: enter\n", OSIF_FUNCTION));
        dpc_root.thread_running = 0;
#if LINUX_VERSION_CODE >= KERNEL_VERSION(2,6,18)
        spin_lock_init(&dpc_root.spinlock);
#else
        dpc_root.spinlock = SPIN_LOCK_UNLOCKED;
#endif
#ifdef OSIF_USE_PREEMPT_RT_IMPLEMENTATION
        init_waitqueue_head(&dpc_root.wqDpcNotify);
        dpc_root.tsk = kthread_run(osif_dpc_thread, NULL, K_DPC_NAME);
        if (IS_ERR(dpc_root.tsk)) {
                return OSIF_EIO;
        }
        if (!wait_event_timeout(dpc_root.wqDpcNotify, (1 == dpc_root.thread_running), 100)) { /* wait for DPC thread to start */
                return OSIF_INSUFFICIENT_RESOURCES;
        }
#else
        sema_init( &dpc_root.sema_trigger, 0 );
        sema_init( &dpc_root.sema_notify, 0 );
        threadId = kernel_thread(osif_dpc_thread, 0, 0);
        if ( 0 == threadId ) {
                return CANIO_EIO;
        }
        down( &dpc_root.sema_notify );
        if ( 0 == dpc_root.thread_running ) {
                return OSIF_INSUFFICIENT_RESOURCES;
        }
#endif
        OSIF_DBG((OSIF_ZONE_OSIF, "%s: leave\n", OSIF_FUNCTION));
        return OSIF_SUCCESS;
}

static INT32 osif_dpc_root_destroy( VOID )
{
        OSIF_DBG((OSIF_ZONE_OSIF, "%s: enter\n", OSIF_FUNCTION));
        dpc_root.destroy = 1;
#ifdef OSIF_USE_PREEMPT_RT_IMPLEMENTATION
        wake_up_process(dpc_root.tsk);
        wait_event_timeout(dpc_root.wqDpcNotify, (0 == dpc_root.thread_running), 100);
#else
        up(&dpc_root.sema_trigger);
        down(&dpc_root.sema_notify);
#endif
#if LINUX_VERSION_CODE >= KERNEL_VERSION(2,4,0)
        wait_for_completion(&dpcThreadCompletion);
#endif
        dpc_root.destroy = 0;
        return OSIF_SUCCESS;
}

INT32 OSIF_CALLTYPE osif_dpc_create( OSIF_DPC *dpc, VOID (OSIF_CALLTYPE *func)(VOID *), VOID *arg )
{
        INT32 result;

        OSIF_DBG((OSIF_ZONE_OSIF, "%s: enter\n", OSIF_FUNCTION));
        result = OSIF_MALLOC( sizeof(**dpc), (VOID*)dpc );
        if ( OSIF_SUCCESS != result ) {
                return result;
        }
        OSIF_MEMSET( *dpc, 0, sizeof(**dpc) );
        (*dpc)->func = func;
        (*dpc)->arg  = arg;
        OSIF_DBG((OSIF_ZONE_OSIF, "%s: leave\n", OSIF_FUNCTION));
        return OSIF_SUCCESS;
}

INT32 OSIF_CALLTYPE osif_dpc_destroy( OSIF_DPC *dpc )
{
        OSIF_DPC  dpc2;
        UINTPTR   flags;

        OSIF_DBG((OSIF_ZONE_OSIF, "%s: enter\n", OSIF_FUNCTION));
        if (NULL == *dpc) {
                return CANIO_EFAULT;
        }
        spin_lock_irqsave( &dpc_root.spinlock, flags );
        (*dpc)->destroy = 1;                       /* now triggers will ret ENOENT */
        if(*dpc == dpc_root.first) {
                dpc_root.first = (*dpc)->next;     /* link out         */
                (*dpc)->next = NULL;               /* mark: linked out */
        } else {
                dpc2 = dpc_root.first;
                while( NULL != dpc2 ) {
                        if(*dpc == dpc2->next) {
                                dpc2->next = (*dpc)->next;         /* link out */
                                (*dpc)->next = NULL;               /* mark: linked out   */
                                break;
                        }
                        dpc2 = dpc2->next;                      /* move up */
                }
        }
        /* if it was linked, it is now unlinked and ready for removal */
        /* if it was unlinked, it could just run... */
        while( 0 != (*dpc)->running ) {
                spin_unlock_irqrestore( &dpc_root.spinlock, flags );
                OSIF_SLEEP(300);
                spin_lock_irqsave( &dpc_root.spinlock, flags );
        }
        spin_unlock_irqrestore( &dpc_root.spinlock, flags );
        OSIF_FREE(*dpc);
        *dpc = NULL;
        OSIF_DBG((OSIF_ZONE_OSIF, "%s: leave\n", OSIF_FUNCTION));
        return OSIF_SUCCESS;
}

INT32 OSIF_CALLTYPE osif_dpc_trigger( OSIF_DPC *dpc )
{
        UINTPTR flags;

        OSIF_DBG((OSIF_ZONE_OSIF, "%s: enter, dpc=%p\n", OSIF_FUNCTION,(UINTPTR)dpc ));
        if (NULL == *dpc) {
                return CANIO_EFAULT;
        }
        spin_lock_irqsave( &dpc_root.spinlock, flags );
        if( 0 != (*dpc)->destroy ) {
                spin_unlock_irqrestore( &dpc_root.spinlock, flags );
                return CANIO_ENOENT;
        }
        if( 0 == (*dpc)->linked ) {
                if( NULL == dpc_root.first) {
                        dpc_root.first = *dpc;
                } else {
                        OSIF_DPC dpc2;

                        dpc2 = dpc_root.first;
                        while( NULL != dpc2->next ) {
                                dpc2 = dpc2->next;
                        }
                        dpc2->next = *dpc;
                }
                (*dpc)->next = NULL;     /* mark end of chain */
                (*dpc)->linked = 1;      /* mark linked */
                spin_unlock_irqrestore( &dpc_root.spinlock, flags );
#ifdef OSIF_USE_PREEMPT_RT_IMPLEMENTATION
                atomic_inc(&dpc_root.trig); /* BL TODO: check, if usable with all kernel.org kernels...!!! */
                smp_mb();
                wake_up_process(dpc_root.tsk);
#else
                up(&dpc_root.sema_trigger);
#endif
        } else {
                spin_unlock_irqrestore( &dpc_root.spinlock, flags );
        }
        OSIF_DBG((OSIF_ZONE_OSIF, "%s: leave\n", OSIF_FUNCTION));
        return OSIF_SUCCESS;
}

/*
** this timer stub runs on soft-irq-level and triggers a dpc for the user timer handler
*/
#if (LINUX_VERSION_CODE >= KERNEL_VERSION(4,15,0))
static void timer_stub(struct timer_list *pLxTimerList)
{
        OSIF_LINUX_TIMER *pLxTimer = from_timer(pLxTimer, pLxTimerList, timer);
        OSIF_DPC_TRIGGER( &pLxTimer->dpc );
}
#else
static void timer_stub(unsigned long uLongLxTimer)
{
        OSIF_LINUX_TIMER *pLxTimer = (OSIF_LINUX_TIMER *)uLongLxTimer;
        OSIF_DPC_TRIGGER( &pLxTimer->dpc );
}
#endif

/*! \fn osif_timer_create( OSIF_TIMER **timer, VOID(OSIF_CALLTYPE *func)(VOID *), VOID *arg, VOID *pCanNode );
 *  \brief Create a timer object.
 *  \param timer a pointer to the created timer structure is returned through this parameter.
 *  \param func func(arg) will be called when timer expires.
 *  \param arg is passed as argument to the timer handler \a func.
 *  The created timer is initially disabled after creation.
 */
INT32 OSIF_CALLTYPE osif_timer_create( OSIF_TIMER *t, VOID (OSIF_CALLTYPE *func)(VOID *), VOID *arg, VOID *pCanNode )
{
        OSIF_LINUX_TIMER *pLxTimer;
        INT32             result;

        OSIF_DBG((OSIF_ZONE_OSIF, "%s: enter\n", OSIF_FUNCTION));
        result = OSIF_MALLOC(sizeof(*pLxTimer), &pLxTimer);
        if (result != OSIF_SUCCESS) {
                return result;
        }
        t->pTimerExt = (VOID*)pLxTimer;
#if (LINUX_VERSION_CODE >= KERNEL_VERSION(4,15,0))
        timer_setup(&(pLxTimer->timer), timer_stub, 0);
#else
        init_timer(&(pLxTimer->timer));
        pLxTimer->timer.function = timer_stub;
        pLxTimer->timer.data     = (UINTPTR)pLxTimer;
#endif
        pLxTimer->timer.expires  = 0;
        OSIF_DPC_CREATE(&pLxTimer->dpc, func, arg);
        OSIF_DBG((OSIF_ZONE_OSIF, "%s: leave\n", OSIF_FUNCTION));
        return OSIF_SUCCESS;
}

/*! \fn osif_timer_destroy( OSIF_TIMER *timer );
 *  \brief Destroy a timer object.
 *  \param timer a pointer to the timer structure.
 */
INT32 OSIF_CALLTYPE osif_timer_destroy( OSIF_TIMER *t )
{
        OSIF_LINUX_TIMER *pLxTimer;

        OSIF_DBG((OSIF_ZONE_OSIF, "%s: enter\n", OSIF_FUNCTION));
        if (NULL == t->pTimerExt) {
                return CANIO_ERROR;
        }
        pLxTimer = (OSIF_LINUX_TIMER*)t->pTimerExt;
        t->pTimerExt = NULL;
        del_timer(&pLxTimer->timer);
        OSIF_DPC_DESTROY(&pLxTimer->dpc);
        OSIF_FREE(pLxTimer);
        OSIF_DBG((OSIF_ZONE_OSIF, "%s: leave\n", OSIF_FUNCTION));
        return OSIF_SUCCESS;
}

/*! \fn osif_timer_set( OSIF_TIMER *timer, UINT32 ms );
 *  \brief Set the expiration time for a timer.
 *  \param timer is a pointer to the timer that should be modified
 *  \param ms new expiration time for this timer in ms. A value of 0
 *  disables the timer.
 */
INT32 OSIF_CALLTYPE osif_timer_set( OSIF_TIMER *t, UINT32 ms )
{
        OSIF_LINUX_TIMER *pLxTimer = (OSIF_LINUX_TIMER*)t->pTimerExt;

        OSIF_DBG((OSIF_ZONE_OSIF, "%s: enter (ms = %d)\n", OSIF_FUNCTION, ms));
        if (ms) {
                if (HZ == 1000) {
                        mod_timer(&(pLxTimer->timer), jiffies + ms);
                } else {
                        mod_timer(&(pLxTimer->timer), jiffies + (((ms * HZ) + 500) / 1000)); /* round correctly */
                }
        } else {
                del_timer(&(pLxTimer->timer));
        }
        OSIF_DBG((OSIF_ZONE_OSIF, "%s: leave\n", OSIF_FUNCTION));
        return OSIF_SUCCESS;
}

INT32 OSIF_CALLTYPE osif_timer_get( OSIF_TIMER *t, UINT32 *ms )
{
        OSIF_DBG((OSIF_ZONE_OSIF, "%s: enter\n", OSIF_FUNCTION));
        if (ms) {
                *ms = jiffies * 1000 / HZ;
        }
        OSIF_DBG((OSIF_ZONE_OSIF, "%s: leave (ms=%d)\n", OSIF_FUNCTION, *ms));
        return OSIF_SUCCESS;
}

/* Defined in "board".cfg,
 *   if the driver is running in a Linux host system
 *   (is not an embedded driver) */
#if defined(HOST_DRIVER) || defined(OSIF_ARCH_ARM)

/* Being kernel version dependent with the osif_ticks() function forces us into
 * the must to implement OSIF_TICK_FREQ as a function too!
 */
# if (LINUX_VERSION_CODE >= KERNEL_VERSION(4,15,0))
UINT64 OSIF_CALLTYPE osif_ticks( VOID )
{
        struct timespec64 ts;
        /* I wanted to use ktime_get_ns() to get ns directly to spend as less CPU cycles as possible.
         * But this is a GPL only symbol and can't be used here. Therefore the kernel time now is
         * converted from ns to timespec64 and back to ns again!
         */
        ktime_get_real_ts64(&ts);
        return ((UINT64)ts.tv_sec * NSEC_PER_SEC) + (UINT64)ts.tv_nsec;
}

UINT64 OSIF_CALLTYPE osif_tick_frequency( VOID )
{
        return NSEC_PER_SEC;
}

# else
UINT64 OSIF_CALLTYPE osif_ticks( VOID )
{
        struct timeval tv;
        do_gettimeofday(&tv);
        return ((UINT64)tv.tv_sec * USEC_PER_SEC) + (UINT64)tv.tv_usec;
}

UINT64 OSIF_CALLTYPE osif_tick_frequency( VOID )
{
        return USEC_PER_SEC;
}
# endif


#else
# ifdef OSIF_ARCH_PPC
UINT64 __attribute__((__unused__)) osif_ticks( VOID )
{
        unsigned __lo;
        unsigned __hi;
        unsigned __tmp;

        __asm__ __volatile__(
                "1:;"
                "  mftbu        %0;"
                "  mftb         %1;"
                "  mftbu        %2;"
                "  cmplw        %0,%2;"
                "bne- 1b;"
                : "=r" (__hi), "=r" (__lo), "=r" (__tmp)
        );
        return (UINT64) __hi << 32 | (UINT64) __lo;
}

# if LINUX_VERSION_CODE >= KERNEL_VERSION(2,6,0)
#   if (defined(BOARD_mecp52))
#    include <asm-ppc/ppcboot.h>  /* AB: needed for mpc5200 ports? */
#   endif
/*extern bd_t __res;*/
# endif  /* LINUX_VERSION_CODE >= KERNEL_VERSION(2,6,0) */

#if defined(CONFIG_OF_DEVICE) || defined(CONFIG_OF_FLATTREE)
# include <asm/time.h>
#endif
UINT64 OSIF_CALLTYPE osif_tick_frequency()
{
#if defined(CONFIG_OF_DEVICE) || defined(CONFIG_OF_FLATTREE)
        return tb_ticks_per_sec;
#elif defined (BOARD_pmc440) || defined (BOARD_pmc440fw)
        return (UINT64)(533334400); /* TODO: get CPU frequency from somewhere in kernel */

#elif defined (BOARD_mecp52) || defined (BOARD_mecp512x) /* BL TODO: dirty!!! fix it fix it fix it!!! */
        return (UINT64)(33000000); /* TODO: get CPU frequency from somewhere in kernel */

#elif defined(BOARD_cpci750)
        return (UINT64)(33333000); /* TODO: get CPU frequency from somewhere in kernel */

#else
#   if LINUX_VERSION_CODE >= KERNEL_VERSION(2,6,0)
        bd_t *bd = (bd_t *)&__res;
#   else
        bd_t *bd = (bd_t *)__res; /* we find 'unsigned char __res[]' in old kernels */
#   endif  /* LINUX_VERSION_CODE >= KERNEL_VERSION(2,6,0) */
        OSIF_DBG((OSIF_ZONE_OSIF, "%s: cpu freq = %d\n", OSIF_FUNCTION, bd->bi_procfreq));
        return (UINT64)(bd->bi_procfreq);
#endif
}
# endif  /* #ifdef OSIF_ARCH_PPC */
#if 0
# ifdef OSIF_ARCH_ARM
UINT64 OSIF_CALLTYPE osif_ticks( VOID )
{
        return 1;
}
UINT64 OSIF_CALLTYPE osif_tick_frequency( VOID )
{
        return 1;
}
# endif
#endif
#endif  /* #ifdef HOST_DRIVER */

UINT32 OSIF_CALLTYPE _osif_div64_32_(UINT64 *n, UINT32 base)
{
        UINT64 rem = *n;
        UINT64 b = base;
        UINT64 res, d = 1;
        UINT32 high = rem >> 32;

        /* Reduce the thing a bit first */
        res = 0;
        if (high >= base) {
                high /= base;
                res = (UINT64) high << 32;
                rem -= (UINT64) (high*base) << 32;
        }
        while ((INT64)b > 0 && b < rem) {
                b <<= 1;
                d <<= 1;
        }
        do {
                if (rem >= b) {
                        rem -= b;
                        res += d;
                }
                b >>= 1;
                d >>= 1;
        } while (d);
        *n = res;
        return rem;
}

VOID OSIF_CALLTYPE osif_ser_out( CHAR8 *str )
{
        UINT32 i;

        /* disable serial interrupt */
        outb( (unsigned char)0, 0x3F9 );
        /* output of string */
        for (i = 0; i < strlen(str); i++) {
                while ( !(inb(0x3F8+5) & 0x20) );
                outb( str[i], 0x3F8 );
        }
        while ( !(inb(0x3F8+5) & 0x20) );
        /* reenable serial interrupt */
/*        outb(0x3F9, 0x??); */ /* AB TODO */
        return;
}

#ifdef OSIF_USE_IO_FUNCTIONS
/*! \fn osif_io_out8(void *addr, UINT8 data);
 *  \brief Write access to I/O-space (8 bit wide)
 *  \param addr target address
 *  \param data this data is written to target address
 */
void OSIF_CALLTYPE osif_io_out8(UINT8 *addr, UINT8 data)
{
#if defined(OSIF_ARCH_ARM)
        writeb((UINT8)data, (void *)(addr));
#else
        outb((UINT8)data, (UINTPTR)(addr));
#endif
}

/*! \fn osif_io_in8(void *addr);
 *  \brief Read access to I/O-space (8 bit wide)
 *  \param addr target address
 *  \return data from target address
 */
UINT8 OSIF_CALLTYPE osif_io_in8(UINT8 *addr)
{
#if defined(OSIF_ARCH_ARM)
        return readb((void *)addr);
#else
        return inb((UINTPTR)addr);
#endif
}

/*! \fn osif_io_out16(void *addr, UINT16 data);
 *  \brief Write access to I/O-space (16 bit wide)
 *  \param addr target address
 *  \param data this data is written to target address
 */
void OSIF_CALLTYPE osif_io_out16(UINT16 *addr, UINT16 data)
{
#if defined(OSIF_ARCH_ARM)
        writew((UINT16)data, (void *)(addr));
#else
        outw((UINT16)data, (UINTPTR)(addr));
#endif
}

/*! \fn osif_io_in16(void *addr);
 *  \brief Read access to I/O-space (16 bit wide)
 *  \param addr target address
 *  \return data from target address
 */
UINT16 OSIF_CALLTYPE osif_io_in16(UINT16 *addr)
{
#if defined(OSIF_ARCH_ARM)
        return readw((void *)addr);
#else
        return inw((UINTPTR)addr);
#endif
}

/*! \fn osif_io_out32(void *addr, UINT32 data);
 *  \brief Write access to I/O-space (32 bit wide)
 *  \param addr target address
 *  \param data this data is written to target address
 */
void OSIF_CALLTYPE osif_io_out32(UINT32 *addr, UINT32 data)
{
#if defined(OSIF_ARCH_ARM)
        writel((UINT32)data, (void *)(addr));
#else
        outl((UINT32)data, (UINTPTR)(addr));
#endif
}

/*! \fn osif_io_in32(void *addr);
 *  \brief Read access to I/O-space (32 bit wide)
 *  \param addr target address
 *  \return data from target address
 */
UINT32 OSIF_CALLTYPE osif_io_in32(UINT32 *addr)
{
#if defined(OSIF_ARCH_ARM)
        return readl((void *)addr);
#else
        return inl((UINTPTR)addr);
#endif
}
#endif

/* -------------------------------------------------------------------- */
#if defined(ESDCAN_SPLIT_BUILD)
/* -------------------------------------------------------------------- */
/*      This stuff is only needed if creating the esdcan driver in a    */
/*      split build. I. e. compiling OSIF and other OS dependent stuff  */
/*      on the user's target machine against the pre-compiled core      */
/*      object files of the driver.                                     */
/* -------------------------------------------------------------------- */

#if defined(ESDCAN_USES_STACKPROTECTOR) && ! defined(ESDCAN_KERNEL_HAS_STACKPROTECTOR)
/* -------------------------------------------------------------------- */
/*      Stack Protector Surrogate                                       */
/*      This must be compiled in if the user's kernel is not compiled   */
/*      with stack protector support and the driver's core objects have */
/*      been compiled with stack protector.                             */
/*      Don't care for __stack_chk_guard variable atm.                  */
/* -------------------------------------------------------------------- */

/*
 * Called when gcc's -fstack-protector* feature is used, and
 * gcc detects corruption of the on-stack canary value
 */
void __stack_chk_fail(void)
{
	panic("stack-protector: esdcan stack is corrupted in: %pB",
		__builtin_return_address(0));
}

#endif  /* defined(ESDCAN_USES_STACKPROTECTOR) && ! defined(ESDCAN_KERNEL_HAS_STACKPROTECTOR) */
#endif  /* defined(ESDCAN_SPLIT_BUILD) */
/* -------------------------------------------------------------------- */

/************************************************************************/
/*                     UTILITY CODE                                     */
/************************************************************************/
INT32 OSIF_CALLTYPE osif_make_ntcan_serial(const CHAR8* pszSerial,
                                           UINT32 *pulSerial)
{
        INT32 lTemp;

        *pulSerial = 0;
        if(pszSerial[0] >= 'A' && pszSerial[0] <= 'P' &&
           pszSerial[1] >= 'A' && pszSerial[1] <= 'P')  {
                lTemp = ((pszSerial[0] - 'A') << 28) | ((pszSerial[1] - 'A') << 24);
                *pulSerial = simple_strtoul(&pszSerial[2], NULL, 10);
                *pulSerial |= (UINT32)lTemp;
        }
        return OSIF_SUCCESS;
}

OSIF_RCSID("$Id: osif.c 16810 2020-07-17 19:12:09Z stefanm $");

/***************************************************************************/
/*                                 EOF                                     */
/***************************************************************************/
