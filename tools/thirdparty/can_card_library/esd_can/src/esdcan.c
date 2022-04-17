/* -*- esdcan-c -*-
 * FILE NAME esdcan.c
 *           copyright 2002 - 2020 by esd electronics gmbh
 *
 * BRIEF MODULE DESCRIPTION
 *           This file contains the Linux / RTAI-Linux entries for
 *           the esd CAN driver
 *
 *
 * Author:   Matthias Fuchs
 *           matthias.fuchs@esd.eu
 *
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
 *  Germany                                sales@esd.eu
 *
 *************************************************************************/
/*! \file esdcan.c
    \brief Linux driver entries

    This file contains the Linux entries for
    the esd CAN driver.
*/
#include <linux/version.h>
#if (LINUX_VERSION_CODE <= KERNEL_VERSION(2,6,32))
# if (LINUX_VERSION_CODE >= KERNEL_VERSION(2,6,19))
#  include <linux/autoconf.h>
# else /* #if (LINUX_VERSION_CODE >= KERNEL_VERSION(2,6,19)) */
#  include <linux/config.h>
# endif /* #if (LINUX_VERSION_CODE >= KERNEL_VERSION(2,6,19)) */
#endif /* #if (LINUX_VERSION_CODE <= KERNEL_VERSION(2,6,32)) */
#ifdef DISTR_SUSE
# undef CONFIG_MODVERSIONS
#endif /* #ifdef DISTR_SUSE */
#ifdef CONFIG_MODVERSIONS
# if LINUX_VERSION_CODE >= KERNEL_VERSION(2,6,0)
#  include <config/modversions.h>
# else /* #if LINUX_VERSION_CODE >= KERNEL_VERSION(2,6,0) */
#  include <linux/modversions.h>
# endif /* #if LINUX_VERSION_CODE >= KERNEL_VERSION(2,6,0) */
# ifndef MODVERSIONS
#  define MODVERSIONS
# endif /* #ifndef MODVERSIONS */
#endif /* #ifdef CONFIG_MODVERSIONS */
#include <linux/kernel.h>
#include <linux/module.h>
#include <linux/types.h>
#include <linux/init.h>
#include <linux/pci.h>
#include <linux/proc_fs.h>
#include <linux/interrupt.h>
#include <linux/poll.h>
#if LINUX_VERSION_CODE >= KERNEL_VERSION(2,6,0)
# include <linux/moduleparam.h>
# if LINUX_VERSION_CODE <= KERNEL_VERSION(2,6,21)
#  include <linux/ioctl32.h>
# endif /* #if LINUX_VERSION_CODE <= KERNEL_VERSION(2,6,21) */
#endif /* #if LINUX_VERSION_CODE >= KERNEL_VERSION(2,6,0) */
#if LINUX_VERSION_CODE < KERNEL_VERSION(2,4,0)
# include <linux/ioport.h>
#endif /* #if LINUX_VERSION_CODE < KERNEL_VERSION(2,4,0) */
#ifndef OSIF_OS_RTAI
# if (LINUX_VERSION_CODE >= KERNEL_VERSION(2,6,18))
#   include <linux/uaccess.h>
# else
#   include <asm/uaccess.h>
# endif
#endif /* #ifndef OSIF_OS_RTAI */
#ifdef LTT
# warning "Tracing enabled"
# include <linux/trace.h>
#endif /* #ifdef LTT */

#include <linux/sched.h>

#include <nucleus.h>

#if LINUX_VERSION_CODE >= KERNEL_VERSION(2,4,0)
# if defined(BOARD_PCI)
#  define ESDCAN_PCI_HOTPLUG
#  undef BOARD_PCI /* Disable legacy PCI support */
# endif /* #if defined(BOARD_PCI) */
#endif /* #if LINUX_VERSION_CODE >= KERNEL_VERSION(2,4,0) */

#if defined(BOARD_USB) || defined(ESDCAN_PCI_HOTPLUG)
# define ESDCAN_HOTPLUG_DRIVER
#endif /* #if defined(BOARD_USB) || defined(ESDCAN_PCI_HOTPLUG) */

#if defined (BOARD_USB)
# if LINUX_VERSION_CODE > KERNEL_VERSION(2,4,0)
#  include <linux/usb.h>
# endif /* #if LINUX_VERSION_CODE > KERNEL_VERSION(2,4,0) */
#endif /* #if defined (BOARD_USB) */

#if defined (BOARD_VME)
#  include <linux/vme.h>
#  define ESDCAN_HOTPLUG_DRIVER
#endif /* #if defined (BOARD_VME) */

#ifdef ESDDBG
# define CAN_DEBUG
#endif /* #ifdef ESDDBG */

#ifdef CAN_DEBUG
# define CAN_DBG(fmt)       OSIF_DPRINT(fmt)  /*!< Macro for debug prints */
# define CAN_IRQ_DBG(fmt)   OSIF_DPRINT(fmt)  /*!< Macro for debug prints on interrupt-level */
#else /* #ifdef CAN_DEBUG */
# define CAN_DBG(fmt)                         /**< Empty expression */
# define CAN_IRQ_DBG(fmt)                     /**< Empty expression */
#endif /* #ifdef CAN_DEBUG */
#define CAN_PRINT(fmt)      OSIF_PRINT(fmt)   /**< Makro for output to the general user (NOT surpressed in release version) */
#define CAN_DPRINT(fmt)     OSIF_DPRINT(fmt)  /**< Makro for output to the general user (filtered by verbose level)         */
#define CAN_IRQ_PRINT(fmt)  OSIF_DPRINT(fmt)  /**< Makro for output to the general user on interrupt level (NOT surpressed in release version) */

#define ESDCAN_ZONE_INIFU    OSIF_ZONE_ESDCAN|OSIF_ZONE_INIT|OSIF_ZONE_FUNC
#define ESDCAN_ZONE_INI      OSIF_ZONE_ESDCAN|OSIF_ZONE_INIT
#define ESDCAN_ZONE_FU       OSIF_ZONE_ESDCAN|OSIF_ZONE_FUNC
#define ESDCAN_ZONE          OSIF_ZONE_ESDCAN
#define ESDCAN_ZONE_IRQ      OSIF_ZONE_IRQ    /* DO NOT USE ANY MORE BITS (nto will thank you:) */
#define ESDCAN_ZONE_ALWAYS   0xFFFFFFFF
#define ESDCAN_ZONE_WARN     OSIF_ZONE_ESDCAN|OSIF_ZONE_WARN

#ifdef LTT
INT32 can_ltt0;
UINT8 can_ltt0_byte;
#endif /* #ifdef LTT */

/* module parameter verbose: default changes regarding to debug flag */
#ifndef CAN_DEBUG
/*
 *  The released driver writes load- and unload-messages to syslog,
 *  if the user hasn't specified a verbose level.
 */
uint verbose = 0x00000001;
#else /* #ifndef CAN_DEBUG */
/*
 *  The debug-version of the driver writes all "release-version"-output
 *  and warning- and error-messages, if the developer doesn't specify
 *  otherwise.
 */
/* uint verbose = 0xF8F00001; */ /* AB setting */
/* uint verbose = 0xF7FFFFFF; */ /* AB all but IRQ  */
/* uint verbose = (0xF7FFFFFF & (~OSIF_ZONE_FILTER)); */ /* AB all but IRQ and NUC (filter) */
/* uint verbose= (OSIF_ZONE_CTRL|OSIF_ZONE_BACKEND); */
uint verbose = 0xC00000FF;
#endif /* #ifndef CAN_DEBUG */

unsigned int major = MAJOR_LINUX; /* MAJOR_LINUX is set in .cfg files */

static VOID esdcan_show_card_info( CAN_CARD *crd );
#if !defined(ESDCAN_HOTPLUG_DRIVER) && !defined(BOARD_SPI)
static VOID esdcan_show_card_info_all( VOID );
#endif
static VOID esdcan_show_driver_info( VOID );
static VOID esdcan_show_done_info( VOID );
INT32 can_attach_common(CAN_CARD *crd);

CAN_NODE *nodes[MAX_CARDS * NODES_PER_CARD];  /* index: minor */

int mode = 0;

int errorinfo = 1;
int pcimsg = 1;
int clock = 0;
int txtswin = TX_TS_WIN_DEF;

#if LINUX_VERSION_CODE >= KERNEL_VERSION(2,6,0)
/* common module parameter */
module_param(major, uint, 0);
MODULE_PARM_DESC(major, "major number to be used for the CAN card");
module_param(mode, int, 0);      /* e.g. LOM */
MODULE_PARM_DESC(mode, "activate certain driver modes, e.g. LOM");
module_param(verbose, uint, 0);  /* mask for output selection */
MODULE_PARM_DESC(verbose, "change verbose level of driver");
module_param(errorinfo, int, 0); /* flag for extended error info */
MODULE_PARM_DESC(errorinfo, "enable/disable extended error info (default: on)");
unsigned int  compat32 = 1;
module_param(compat32, int, 0);  /* setting this to zero disables 32-bit compatibility on 64-bit systems */
MODULE_PARM_DESC(compat32, "disable 32-Bit compatibility on 64-Bit systems");
#if defined(BOARD_PCI) || defined(ESDCAN_PCI_HOTPLUG)
module_param(pcimsg, int, 0);    /* enable/disable pcimsg interface on firmware drivers */
MODULE_PARM_DESC(pcimsg, "enable/disable pcimsg interface on firmware drivers (default: on)");
#endif /* defined(BOARD_PCI) || defined(ESDCAN_PCI_HOTPLUG) */
module_param(clock, int, 0);     /* override TS tick frequency */
MODULE_PARM_DESC(clock, "LEAVE THIS ONE ALONE, works with special hardware, only");
#ifdef NUC_TX_TS
module_param(txtswin, int, 0);   /* override TX TS window size (ms) */
MODULE_PARM_DESC(txtswin, "override default TX-TS-window size (in ms)");
#endif /* #ifdef NUC_TX_TS */
#else /* #if LINUX_VERSION_CODE >= KERNEL_VERSION(2,6,0) */
/* common module parameter */
MODULE_PARM(major, "1i");
MODULE_PARM(mode, "1i");      /* e.g. LOM */
MODULE_PARM(verbose, "1i");   /* mask for output selection */
MODULE_PARM(errorinfo, "1i"); /* enable/disable extended error info (default: on) */
#if defined(BOARD_PCI) || defined(ESDCAN_PCI_HOTPLUG)
MODULE_PARM(pcimsg, "1i");    /* enable/disable pcimsg interface on firmware drivers */
#endif /* defined(BOARD_PCI) || defined(ESDCAN_PCI_HOTPLUG) */
MODULE_PARM(clock, "1i");     /* override TS tick frequency */
#ifdef NUC_TX_TS
MODULE_PARM(txtswin, "1i");   /* override TX TS window size (ms) */
#endif /* #ifdef NUC_TX_TS */
#endif /* #if LINUX_VERSION_CODE >= KERNEL_VERSION(2,6,0) */

#if LINUX_VERSION_CODE >= KERNEL_VERSION(2,6,0)
# define INODE2CANNODE(inode) (iminor(inode))
#else /* #if LINUX_VERSION_CODE >= KERNEL_VERSION(2,6,0) */
# define INODE2CANNODE(inode) (MINOR(inode->i_rdev) & 0xff)
#endif /* #if LINUX_VERSION_CODE >= KERNEL_VERSION(2,6,0) */

/* BL: Actually came into kernel.org with 2.6.18,
 *     from 2.6.25 it is mandatory (old defines removed)
 *     In 2.6.22 "deprecated warnings" came in */
# if (LINUX_VERSION_CODE >= KERNEL_VERSION(2,6,22))
#  if defined(ESDCAN_SPECIAL_IRQ_FLAGS) /* see e.g. mcp2515/cpuca8/boardrc.h */
#    define ESDCAN_IRQ_FLAGS ESDCAN_SPECIAL_IRQ_FLAGS
#  else /* #if defined(ESDCAN_SPECIAL_IRQ_FLAGS) */
#    define ESDCAN_IRQ_FLAGS IRQF_SHARED
#  endif /* #if defined(ESDCAN_SPECIAL_IRQ_FLAGS) */
# else /* #if (LINUX_VERSION_CODE >= KERNEL_VERSION(2,6,22)) */
#  define ESDCAN_IRQ_FLAGS   SA_SHIRQ | SA_INTERRUPT
# endif /* #if (LINUX_VERSION_CODE >= KERNEL_VERSION(2,6,22)) */

#ifdef OSIF_OS_LINUX
#define ESDCAN_IOCTL_PROTO \
        static int esdcan_ioctl(struct inode *inode, struct file *file, unsigned int cmd, unsigned long arg)
# if (PLATFORM_64BIT) && (LINUX_VERSION_CODE > KERNEL_VERSION(2,6,10))
static long esdcan_compat_ioctl(struct file *file, unsigned int cmd, unsigned long arg);
# endif /* #if (PLATFORM_64BIT) && (LINUX_VERSION_CODE > KERNEL_VERSION(2,6,10)) */
# if LINUX_VERSION_CODE > KERNEL_VERSION(2,6,10)
static long esdcan_unlocked_ioctl(struct file *file, unsigned int cmd, unsigned long arg);
# endif /* #if LINUX_VERSION_CODE > KERNEL_VERSION(2,6,10) */
#endif /* OSIF_OS_LINUX */

#ifdef OSIF_OS_RTAI
#define ESDCAN_IOCTL_PROTO \
        INT32 esdcan_ctrl(INT32 hnd, UINT32 cmd, UINT32 arg)
#endif /* OSIF_OS_RTAI */

static unsigned int esdcan_poll(struct file *pFile, struct poll_table_struct *pPollTable);
static int esdcan_open(struct inode *inode, struct file *file);
static int esdcan_release(struct inode *inode, struct file *file);
ESDCAN_IOCTL_PROTO;

void esdcan_unregister_ioctl32(void);
int32_t esdcan_register_ioctl32(void);

#define RETURN_TO_USER(ret) return(-ret)

#ifndef OSIF_OS_RTAI
struct file_operations esdcan_fops =
{
#if LINUX_VERSION_CODE < KERNEL_VERSION(2,4,0)
        NULL,
        NULL,
        NULL,
        NULL,
        NULL,  /* no support of poll/select planned for 2.2.x */
        esdcan_ioctl,
        NULL,
        esdcan_open,
        NULL,
        esdcan_release,
        NULL,
        NULL,
        NULL,
        NULL,
        NULL
#elif LINUX_VERSION_CODE < KERNEL_VERSION(2,6,0)
        owner:   THIS_MODULE,
/*      poll:    esdcan_poll, */ /* no support for poll/select on 2.4.x, yet */
        ioctl:   esdcan_ioctl,
        open:    esdcan_open,
        release: esdcan_release,
#else /* LINUX_VERSION_CODE < KERNEL_VERSION(2,4,0) */
        .owner =   THIS_MODULE,
        .poll =    esdcan_poll,
# if LINUX_VERSION_CODE < KERNEL_VERSION(2,6,36)
        .ioctl =   esdcan_ioctl,
# endif /* #if LINUX_VERSION_CODE < KERNEL_VERSION(2,6,36) */
# if (PLATFORM_64BIT) && (LINUX_VERSION_CODE > KERNEL_VERSION(2,6,10))
        .compat_ioctl = esdcan_compat_ioctl,
# endif /* #if (PLATFORM_64BIT) && (LINUX_VERSION_CODE > KERNEL_VERSION(2,6,10)) */
# if LINUX_VERSION_CODE > KERNEL_VERSION(2,6,10)
        .unlocked_ioctl = esdcan_unlocked_ioctl,
# endif /* #if LINUX_VERSION_CODE > KERNEL_VERSION(2,6,10) */
        .open =    esdcan_open,
        .release = esdcan_release,
#endif /* LINUX_VERSION_CODE < KERNEL_VERSION(2,4,0) */
};
#endif /* OSIF_OS_RTAI */

#define PROCFN_LEN 30
#define PROC_NODEINIT
#if (defined PROC_NODEINIT) && ( LINUX_VERSION_CODE >= KERNEL_VERSION(2,4,0) ) && CONFIG_PROC_FS
#if LINUX_VERSION_CODE >= KERNEL_VERSION(2,6,0)
#include <linux/namei.h>
#else /* #if LINUX_VERSION_CODE >= KERNEL_VERSION(2,6,0) */
#include <linux/fs.h>
#endif /* #if LINUX_VERSION_CODE >= KERNEL_VERSION(2,6,0) */

static UINT8 procfn_nodeinit[PROCFN_LEN];
static UINT8 procfn_cardpath[PROCFN_LEN];

#if LINUX_VERSION_CODE < KERNEL_VERSION(2,4,25)
int path_lookup(const char *path, unsigned flags, struct nameidata *nd)
{
        int error = 0;
        if (path_init(path, flags, nd))
                error = path_walk(path, nd);
        return error;
}
#endif

static int esdcan_path_check(const char *name) {
#if LINUX_VERSION_CODE >= KERNEL_VERSION(2,6,39)
        struct path p;
        return kern_path(name, 0, &p);
#else /* #if LINUX_VERSION_CODE >= KERNEL_VERSION(2,6,39) */
        struct nameidata nd;
        return path_lookup(name, 0, &nd);
#endif /* #if LINUX_VERSION_CODE >= KERNEL_VERSION(2,6,39) */
}

#if LINUX_VERSION_CODE >= KERNEL_VERSION(3,8,0)
/* The new way:
   Provide struct file_operations or struct proc_ops table to proc_create().
*/

#include <linux/seq_file.h>
static int esdcan_proc_show(struct seq_file *m, void *v)
{
        int n, num = 0;

        seq_printf(m, "#!/bin/sh\n");
        for (n = 0; n < MAX_CARDS * NODES_PER_CARD; n++) {
                CAN_NODE *node = nodes[n];
                if ( node ) {
                        num++;
                        seq_printf(m,"net_num=$((${1}+%d))\n", node->net_no);
                        seq_printf(m,"test -e /dev/can${net_num} || mknod -m 666 /dev/can${net_num} c %d %d\n",
                                        major, node->net_no);
                }
        }
        if ( !num ) {
                seq_printf(m,"echo \"No CAN card found!\"\n");
        }
        return 0;
}

static int esdcan_proc_open(struct inode *inode, struct file *file)
{
        return single_open(file, esdcan_proc_show, NULL);
}

#if LINUX_VERSION_CODE >= KERNEL_VERSION(5,6,0)
/* Kernel 5.6 introduced a new structure proc_ops that is now the 4th argument
 * for proc_create(). */
static const struct proc_ops esdcan_proc_ops = {
        .proc_open      = esdcan_proc_open,
        .proc_read      = seq_read,
        .proc_lseek     = seq_lseek,
        .proc_release   = single_release,
};
#else   /* #if LINUX_VERSION_CODE >= KERNEL_VERSION(5,6,0) */
/* On older kernels a structure file_operations is used as the 4th argument
 * for proc_create(). */
static const struct file_operations esdcan_proc_ops = {
        .owner          = THIS_MODULE,
        .open           = esdcan_proc_open,
        .read           = seq_read,
        .llseek         = seq_lseek,
        .release        = single_release,
};
#endif  /* #if LINUX_VERSION_CODE >= KERNEL_VERSION(5,6,0) */

#define ESDCAN_USE_PROC_CREATE

#else /* #if LINUX_VERSION_CODE >= KERNEL_VERSION(3,8,0) */
/* The old way:
   Provide the following function to create_proc_read_entry().
*/

int can_read_proc_nodeinit(char *buf, char **start, off_t offset, int count, int *eof, void *data)
{
        CAN_NODE **nodes = (CAN_NODE**)data;
        INT32      len = 0, num = 0, result;
        int        n;
        char      *tmp_buf;
        const int  BUFSIZE = 4096;

        CAN_DBG((ESDCAN_ZONE_INI, "%s: buf: 0x%08X, start: 0x%08X, offs: %d, count: %d, eof: %d\n",
                 OSIF_FUNCTION, buf, start, offset, count, *eof));
        result = OSIF_MALLOC(BUFSIZE, &tmp_buf);
        if(OSIF_SUCCESS != result) {
                *eof = 1;
                return 0;
        }
        len += snprintf(tmp_buf+len, BUFSIZE-len, "#!/bin/sh\n");
        for (n = 0; n < MAX_CARDS * NODES_PER_CARD; n++) {
                CAN_NODE *node = nodes[n];
                if ( node ) {
                        if ( 80 >= (BUFSIZE-len) ) {
                                /* shouldn't happen */
                                CAN_DBG((ESDCAN_ZONE_INI, "%s: Not enough memory for inode script!\n",
                                         OSIF_FUNCTION));
                                break;
                        }
                        num++;
                        len += snprintf(tmp_buf+len, BUFSIZE-len,
                                        "net_num=$((${1}+%d))\n", node->net_no);
                        len += snprintf(tmp_buf+len, BUFSIZE-len,
                                        "test -e /dev/can${net_num} || mknod -m 666 /dev/can${net_num} c %d %d\n",
                                        major, node->net_no);
                }
        }
        if ( !num ) {
                len += snprintf(tmp_buf+len, BUFSIZE-len,
                                "echo \"No CAN card found!\"\n");
        }
        CAN_DBG((ESDCAN_ZONE_INI, "%s: complete script len: %d\n",
                 OSIF_FUNCTION, len));
        if ((offset+count) >= len) {
                *eof = 1;
                len -= offset;
        } else {
                len = count;
        }
        OSIF_MEMCPY(buf+offset, tmp_buf+offset, len);
        OSIF_FREE(tmp_buf);
        CAN_DBG((ESDCAN_ZONE_INI, "%s: len: %d, eof: %d\n",
                 OSIF_FUNCTION, len, *eof));
        return offset+len;
}
#endif /* #if LINUX_VERSION_CODE >= KERNEL_VERSION(3,8,0) */

void esdcan_proc_nodeinit_create(void)
{
        int   err;
        char  sPath[PROCFN_LEN+6];

        OSIF_SNPRINTF((procfn_nodeinit, PROCFN_LEN, "bus/can/%s/inodes", ESDCAN_DRIVER_NAME));
        OSIF_SNPRINTF((procfn_cardpath, PROCFN_LEN, "bus/can/%s"       , ESDCAN_DRIVER_NAME));
        CAN_DBG((ESDCAN_ZONE_INI, "%s: creating proc entry (%s)\n",
                 OSIF_FUNCTION, procfn_nodeinit));
        /* create /proc/bus/can */
        err = esdcan_path_check("/proc/bus/can");
        if (err) {
                struct proc_dir_entry *ent;
                ent=proc_mkdir("bus/can", NULL);
                if (ent==NULL) {
                    CAN_PRINT(("%s: error creating proc entry (%s)\n", OSIF_FUNCTION, "bus/can"));
                    procfn_nodeinit[0]=0;
                    procfn_cardpath[0]=0;
                    return;
                }
        }
        /* create /proc/bus/can/<DRIVER_NAME> */
        OSIF_SNPRINTF((sPath, PROCFN_LEN+6,"/proc/%s", procfn_cardpath));
        err = esdcan_path_check(sPath);
        if (err) {
                struct proc_dir_entry *ent;
                ent=proc_mkdir(procfn_cardpath, NULL);
                if (ent==NULL) {
                        CAN_PRINT(("%s: error creating proc entry (%s)\n", OSIF_FUNCTION, procfn_cardpath));
                        procfn_nodeinit[0]=0;
                        procfn_cardpath[0]=0;
                        return;
                }
        }
        /* create /proc/bus/can/<DRIVER_NAME>/inodes */
#ifdef ESDCAN_USE_PROC_CREATE
        if (!proc_create( procfn_nodeinit,
                                     S_IFREG | S_IRUGO | S_IXUSR, /* read all, execute user */
                                     NULL /* parent dir */,
                                     &esdcan_proc_ops)) {
#else /* #ifdef ESDCAN_USE_PROC_CREATE */
        if (!create_proc_read_entry( procfn_nodeinit,
                                     0x16D /* default mode */,
                                     NULL /* parent dir */,
                                     can_read_proc_nodeinit,
                                     (VOID*)nodes /* arg */)) {
#endif /* #ifdef ESDCAN_USE_PROC_CREATE */
                CAN_PRINT(("%s: error creating proc entry (%s)\n", OSIF_FUNCTION, procfn_nodeinit));
                procfn_nodeinit[0]=0;
        }
}

void esdcan_proc_nodeinit_remove(void)
{
        if (procfn_nodeinit[0]) {
                CAN_DBG((ESDCAN_ZONE_INI, "%s: removing proc entry %s\n",
                         OSIF_FUNCTION, procfn_nodeinit));
                remove_proc_entry(procfn_nodeinit, NULL);
                procfn_nodeinit[0]=0;
        }
        if (procfn_cardpath[0]) {
                CAN_DBG((ESDCAN_ZONE_INI, "%s: removing proc entry %s\n",
                         OSIF_FUNCTION, procfn_cardpath));
                remove_proc_entry(procfn_cardpath, NULL);
                procfn_cardpath[0]=0;
        }
}
#else /* #if (defined PROC_NODEINIT) && ( LINUX_VERSION_CODE >= KERNEL_VERSION(2,4,0) ) && CONFIG_PROC_FS */
void esdcan_proc_nodeinit_create(void) {}
void esdcan_proc_nodeinit_remove(void) {}
#endif /* #if (defined PROC_NODEINIT) && ( LINUX_VERSION_CODE >= KERNEL_VERSION(2,4,0) ) && CONFIG_PROC_FS */

#if (PLATFORM_64BIT) && (LINUX_VERSION_CODE <= KERNEL_VERSION(2,6,10))
static int esdcan_ioctl_32(unsigned int fd, unsigned int cmd, unsigned long arg, struct file *file);

void esdcan_unregister_ioctl32(void)
{
        if (compat32) {
                UNREGISTER_IOCTL_32(IOCTL_ESDCAN_CREATE);
                UNREGISTER_IOCTL_32(IOCTL_ESDCAN_ID_RANGE_ADD);
                UNREGISTER_IOCTL_32(IOCTL_ESDCAN_ID_RANGE_DEL);
                UNREGISTER_IOCTL_32(IOCTL_ESDCAN_SET_BAUD);
                UNREGISTER_IOCTL_32(IOCTL_ESDCAN_SET_TIMEOUT);
                UNREGISTER_IOCTL_32(IOCTL_ESDCAN_SEND);
                UNREGISTER_IOCTL_32(IOCTL_ESDCAN_TAKE);
                UNREGISTER_IOCTL_32(IOCTL_ESDCAN_DEBUG);
                UNREGISTER_IOCTL_32(IOCTL_ESDCAN_GET_BAUD);
                UNREGISTER_IOCTL_COMPAT(IOCTL_ESDCAN_DESTROY);
                UNREGISTER_IOCTL_32(IOCTL_ESDCAN_DESTROY_DEPRECATED);
                UNREGISTER_IOCTL_32(IOCTL_ESDCAN_TX_ABORT);
                UNREGISTER_IOCTL_32(IOCTL_ESDCAN_RX_ABORT);
                UNREGISTER_IOCTL_32(IOCTL_ESDCAN_TX_OBJ_CREATE);
                UNREGISTER_IOCTL_32(IOCTL_ESDCAN_TX_OBJ_UPDATE);
                UNREGISTER_IOCTL_32(IOCTL_ESDCAN_TX_OBJ_AUTOANSWER_OFF);
                UNREGISTER_IOCTL_32(IOCTL_ESDCAN_TX_OBJ_DESTROY);
                UNREGISTER_IOCTL_32(IOCTL_ESDCAN_RX_OBJ);
                UNREGISTER_IOCTL_32(IOCTL_ESDCAN_READ);
                UNREGISTER_IOCTL_32(IOCTL_ESDCAN_WRITE);
                UNREGISTER_IOCTL_32(IOCTL_ESDCAN_UPDATE);
                UNREGISTER_IOCTL_COMPAT(IOCTL_ESDCAN_FLUSH_RX_FIFO);
                UNREGISTER_IOCTL_32(IOCTL_ESDCAN_FLUSH_RX_FIFO_DEPRECATED);
                UNREGISTER_IOCTL_32(IOCTL_ESDCAN_GET_RX_MESSAGES);
                UNREGISTER_IOCTL_32(IOCTL_ESDCAN_GET_RX_TIMEOUT);
                UNREGISTER_IOCTL_32(IOCTL_ESDCAN_GET_TX_TIMEOUT);
                UNREGISTER_IOCTL_32(IOCTL_ESDCAN_GET_TIMESTAMP_FREQ);
                UNREGISTER_IOCTL_32(IOCTL_ESDCAN_GET_TIMESTAMP);
                UNREGISTER_IOCTL_32(IOCTL_ESDCAN_GET_TICKS_FREQ);
                UNREGISTER_IOCTL_32(IOCTL_ESDCAN_GET_TICKS);
                UNREGISTER_IOCTL_32(IOCTL_ESDCAN_SEND_T);
                UNREGISTER_IOCTL_32(IOCTL_ESDCAN_WRITE_T);
                UNREGISTER_IOCTL_32(IOCTL_ESDCAN_TAKE_T);
                UNREGISTER_IOCTL_32(IOCTL_ESDCAN_READ_T);
                UNREGISTER_IOCTL_COMPAT(IOCTL_ESDCAN_PURGE_TX_FIFO);
                UNREGISTER_IOCTL_32(IOCTL_ESDCAN_PURGE_TX_FIFO_DEPRECATED);
                UNREGISTER_IOCTL_32(IOCTL_ESDCAN_TX_OBJ_AUTOANSWER_ON);
                UNREGISTER_IOCTL_32(IOCTL_ESDCAN_SET_RX_TIMEOUT);
                UNREGISTER_IOCTL_32(IOCTL_ESDCAN_SET_TX_TIMEOUT);
                UNREGISTER_IOCTL_32(IOCTL_ESDCAN_GET_FEATURES);
                UNREGISTER_IOCTL_32(IOCTL_ESDCAN_TX_OBJ_SCHEDULE);
                UNREGISTER_IOCTL_COMPAT(IOCTL_ESDCAN_TX_OBJ_SCHEDULE_START);
                UNREGISTER_IOCTL_COMPAT(IOCTL_ESDCAN_TX_OBJ_SCHEDULE_STOP);
                UNREGISTER_IOCTL_32(IOCTL_ESDCAN_SET_20B_HND_FILTER);
                UNREGISTER_IOCTL_32(IOCTL_ESDCAN_GET_SERIAL);
                UNREGISTER_IOCTL_COMPAT(IOCTL_ESDCAN_SET_ALT_RTR_ID);
                UNREGISTER_IOCTL_32(IOCTL_ESDCAN_SET_BUSLOAD_INTERVAL);
                UNREGISTER_IOCTL_32(IOCTL_ESDCAN_GET_BUSLOAD_INTERVAL);
                UNREGISTER_IOCTL_32(IOCTL_ESDCAN_GET_BITRATE_DETAILS);
                UNREGISTER_IOCTL_32(IOCTL_ESDCAN_GET_BUS_STATISTIC);
                UNREGISTER_IOCTL_COMPAT(IOCTL_ESDCAN_RESET_BUS_STATISTIC);
                UNREGISTER_IOCTL_32(IOCTL_ESDCAN_GET_ERROR_COUNTER);
                UNREGISTER_IOCTL_32(IOCTL_ESDCAN_SER_REG_READ);
                UNREGISTER_IOCTL_32(IOCTL_ESDCAN_SER_REG_WRITE);
                UNREGISTER_IOCTL_COMPAT(IOCTL_ESDCAN_RESET_CAN_ERROR_CNT);
                UNREGISTER_IOCTL_32(IOCTL_ESDCAN_ID_REGION_ADD);
                UNREGISTER_IOCTL_32(IOCTL_ESDCAN_ID_REGION_DEL);

                UNREGISTER_IOCTL_32(IOCTL_ESDCAN_SET_TX_TS_WIN);
                UNREGISTER_IOCTL_32(IOCTL_ESDCAN_GET_TX_TS_WIN);
                UNREGISTER_IOCTL_32(IOCTL_ESDCAN_SET_TX_TS_TIMEOUT);
                UNREGISTER_IOCTL_32(IOCTL_ESDCAN_GET_TX_TS_TIMEOUT);

                UNREGISTER_IOCTL_32(IOCTL_ESDCAN_SET_HND_FILTER);

                UNREGISTER_IOCTL_32(IOCTL_ESDCAN_GET_TX_MESSAGES);

                UNREGISTER_IOCTL_32(IOCTL_ESDCAN_SEND_X);
                UNREGISTER_IOCTL_32(IOCTL_ESDCAN_WRITE_X);
                UNREGISTER_IOCTL_32(IOCTL_ESDCAN_TAKE_X);
                UNREGISTER_IOCTL_32(IOCTL_ESDCAN_READ_X);
                UNREGISTER_IOCTL_32(IOCTL_ESDCAN_SET_BAUD_X);
                UNREGISTER_IOCTL_32(IOCTL_ESDCAN_GET_BAUD_X);

                UNREGISTER_IOCTL_32(IOCTL_ESDCAN_EEI_CREATE);
                UNREGISTER_IOCTL_32(IOCTL_ESDCAN_EEI_DESTROY);
                UNREGISTER_IOCTL_32(IOCTL_ESDCAN_EEI_STATUS);
                UNREGISTER_IOCTL_32(IOCTL_ESDCAN_EEI_CONFIGURE);
                UNREGISTER_IOCTL_32(IOCTL_ESDCAN_EEI_START);
                UNREGISTER_IOCTL_32(IOCTL_ESDCAN_EEI_STOP);
                UNREGISTER_IOCTL_32(IOCTL_ESDCAN_EEI_TRIGGER_NOW);

                UNREGISTER_IOCTL_32(IOCTL_ESDCAN_TX_OBJ_CREATE_T);
                UNREGISTER_IOCTL_32(IOCTL_ESDCAN_TX_OBJ_UPDATE_T);
                UNREGISTER_IOCTL_32(IOCTL_ESDCAN_TX_OBJ_AUTOANSWER_OFF_T);
                UNREGISTER_IOCTL_32(IOCTL_ESDCAN_TX_OBJ_AUTOANSWER_ON_T);
                UNREGISTER_IOCTL_32(IOCTL_ESDCAN_TX_OBJ_DESTROY_T);
                UNREGISTER_IOCTL_32(IOCTL_ESDCAN_TX_OBJ_CREATE_X);
                UNREGISTER_IOCTL_32(IOCTL_ESDCAN_TX_OBJ_UPDATE_X);
                UNREGISTER_IOCTL_32(IOCTL_ESDCAN_TX_OBJ_AUTOANSWER_OFF_X);
                UNREGISTER_IOCTL_32(IOCTL_ESDCAN_TX_OBJ_AUTOANSWER_ON_X);
                UNREGISTER_IOCTL_32(IOCTL_ESDCAN_TX_OBJ_DESTROY_X);

                UNREGISTER_IOCTL_32(IOCTL_ESDCAN_GET_INFO);

                UNREGISTER_IOCTL_32(IOCTL_ESDCAN_SET_FD_TDC);
                UNREGISTER_IOCTL_32(IOCTL_ESDCAN_GET_FD_TDC);

                UNREGISTER_IOCTL_32(IOCTL_LIN_MASTER_SEL);

                UNREGISTER_IOCTL_32(IOCTL_ESDCAN_TX_OBJ_AUTOANSWER_ONCE);
                UNREGISTER_IOCTL_32(IOCTL_ESDCAN_TX_OBJ_AUTOANSWER_ONCE_T);
                UNREGISTER_IOCTL_32(IOCTL_ESDCAN_TX_OBJ_AUTOANSWER_ONCE_X);

                UNREGISTER_IOCTL_32(IOCTL_ESDCAN_GET_HW_TIMESTAMP);
                UNREGISTER_IOCTL_32(IOCTL_ESDCAN_GET_HW_TIMESTAMP_EX);

                /* special ioctl (from candev driver) for driver version detection */
                UNREGISTER_IOCTL_COMPAT(IOCTL_CAN_SET_QUEUESIZE);
        }
}

int32_t esdcan_register_ioctl32(void)
{
        int32_t result = 0;

        if (compat32) {
                /* register 32-bit ioctls */
                REGISTER_IOCTL_32(IOCTL_ESDCAN_CREATE, result);
                REGISTER_IOCTL_32(IOCTL_ESDCAN_ID_RANGE_ADD, result);
                REGISTER_IOCTL_32(IOCTL_ESDCAN_ID_RANGE_DEL, result);
                REGISTER_IOCTL_32(IOCTL_ESDCAN_SET_BAUD, result);
                REGISTER_IOCTL_32(IOCTL_ESDCAN_SET_TIMEOUT, result);
                REGISTER_IOCTL_32(IOCTL_ESDCAN_SEND, result);
                REGISTER_IOCTL_32(IOCTL_ESDCAN_TAKE, result);
                REGISTER_IOCTL_32(IOCTL_ESDCAN_DEBUG, result);
                REGISTER_IOCTL_32(IOCTL_ESDCAN_GET_BAUD, result);
                REGISTER_IOCTL_COMPAT(IOCTL_ESDCAN_DESTROY, result);
                REGISTER_IOCTL_32(IOCTL_ESDCAN_DESTROY_DEPRECATED, result);
                REGISTER_IOCTL_32(IOCTL_ESDCAN_TX_ABORT, result);
                REGISTER_IOCTL_32(IOCTL_ESDCAN_RX_ABORT, result);
                REGISTER_IOCTL_32(IOCTL_ESDCAN_TX_OBJ_CREATE, result);
                REGISTER_IOCTL_32(IOCTL_ESDCAN_TX_OBJ_UPDATE, result);
                REGISTER_IOCTL_32(IOCTL_ESDCAN_TX_OBJ_AUTOANSWER_OFF, result);
                REGISTER_IOCTL_32(IOCTL_ESDCAN_TX_OBJ_DESTROY, result);
                REGISTER_IOCTL_32(IOCTL_ESDCAN_RX_OBJ, result);
                REGISTER_IOCTL_32(IOCTL_ESDCAN_READ, result);
                REGISTER_IOCTL_32(IOCTL_ESDCAN_WRITE, result);
                REGISTER_IOCTL_32(IOCTL_ESDCAN_UPDATE, result);
                REGISTER_IOCTL_COMPAT(IOCTL_ESDCAN_FLUSH_RX_FIFO, result);
                REGISTER_IOCTL_32(IOCTL_ESDCAN_FLUSH_RX_FIFO_DEPRECATED, result);
                REGISTER_IOCTL_32(IOCTL_ESDCAN_GET_RX_MESSAGES, result);
                REGISTER_IOCTL_32(IOCTL_ESDCAN_GET_RX_TIMEOUT, result);
                REGISTER_IOCTL_32(IOCTL_ESDCAN_GET_TX_TIMEOUT, result);
                REGISTER_IOCTL_32(IOCTL_ESDCAN_GET_TIMESTAMP_FREQ, result);
                REGISTER_IOCTL_32(IOCTL_ESDCAN_GET_TIMESTAMP, result);
                REGISTER_IOCTL_32(IOCTL_ESDCAN_GET_TICKS_FREQ, result);
                REGISTER_IOCTL_32(IOCTL_ESDCAN_GET_TICKS, result);
                REGISTER_IOCTL_32(IOCTL_ESDCAN_SEND_T, result);
                REGISTER_IOCTL_32(IOCTL_ESDCAN_WRITE_T, result);
                REGISTER_IOCTL_32(IOCTL_ESDCAN_TAKE_T, result);
                REGISTER_IOCTL_32(IOCTL_ESDCAN_READ_T, result);
                REGISTER_IOCTL_COMPAT(IOCTL_ESDCAN_PURGE_TX_FIFO, result);
                REGISTER_IOCTL_32(IOCTL_ESDCAN_PURGE_TX_FIFO_DEPRECATED, result);
                REGISTER_IOCTL_32(IOCTL_ESDCAN_TX_OBJ_AUTOANSWER_ON, result);
                REGISTER_IOCTL_32(IOCTL_ESDCAN_SET_RX_TIMEOUT, result);
                REGISTER_IOCTL_32(IOCTL_ESDCAN_SET_TX_TIMEOUT, result);
                REGISTER_IOCTL_32(IOCTL_ESDCAN_GET_FEATURES, result);
                REGISTER_IOCTL_32(IOCTL_ESDCAN_TX_OBJ_SCHEDULE, result);
                REGISTER_IOCTL_COMPAT(IOCTL_ESDCAN_TX_OBJ_SCHEDULE_START, result);
                REGISTER_IOCTL_COMPAT(IOCTL_ESDCAN_TX_OBJ_SCHEDULE_STOP, result);
                REGISTER_IOCTL_32(IOCTL_ESDCAN_SET_20B_HND_FILTER, result);
                REGISTER_IOCTL_32(IOCTL_ESDCAN_GET_SERIAL, result);
                REGISTER_IOCTL_COMPAT(IOCTL_ESDCAN_SET_ALT_RTR_ID, result);
                REGISTER_IOCTL_32(IOCTL_ESDCAN_SET_BUSLOAD_INTERVAL, result);
                REGISTER_IOCTL_32(IOCTL_ESDCAN_GET_BUSLOAD_INTERVAL, result);
                REGISTER_IOCTL_32(IOCTL_ESDCAN_GET_BITRATE_DETAILS, result);
                REGISTER_IOCTL_32(IOCTL_ESDCAN_GET_BUS_STATISTIC, result);
                REGISTER_IOCTL_COMPAT(IOCTL_ESDCAN_RESET_BUS_STATISTIC, result);
                REGISTER_IOCTL_32(IOCTL_ESDCAN_GET_ERROR_COUNTER, result);
                REGISTER_IOCTL_32(IOCTL_ESDCAN_SER_REG_READ, result);
                REGISTER_IOCTL_32(IOCTL_ESDCAN_SER_REG_WRITE, result);
                REGISTER_IOCTL_COMPAT(IOCTL_ESDCAN_RESET_CAN_ERROR_CNT, result);
                REGISTER_IOCTL_32(IOCTL_ESDCAN_ID_REGION_ADD, result);
                REGISTER_IOCTL_32(IOCTL_ESDCAN_ID_REGION_DEL, result);

                REGISTER_IOCTL_32(IOCTL_ESDCAN_SET_TX_TS_WIN, result);
                REGISTER_IOCTL_32(IOCTL_ESDCAN_GET_TX_TS_WIN, result);
                REGISTER_IOCTL_32(IOCTL_ESDCAN_SET_TX_TS_TIMEOUT, result);
                REGISTER_IOCTL_32(IOCTL_ESDCAN_GET_TX_TS_TIMEOUT, result);

                REGISTER_IOCTL_32(IOCTL_ESDCAN_SET_HND_FILTER, result);

                REGISTER_IOCTL_32(IOCTL_ESDCAN_GET_TX_MESSAGES, result);

                REGISTER_IOCTL_32(IOCTL_ESDCAN_SEND_X, result);
                REGISTER_IOCTL_32(IOCTL_ESDCAN_WRITE_X, result);
                REGISTER_IOCTL_32(IOCTL_ESDCAN_TAKE_X, result);
                REGISTER_IOCTL_32(IOCTL_ESDCAN_READ_X, result);
                REGISTER_IOCTL_32(IOCTL_ESDCAN_SET_BAUD_X, result);
                REGISTER_IOCTL_32(IOCTL_ESDCAN_GET_BAUD_X, result);

                REGISTER_IOCTL_32(IOCTL_ESDCAN_EEI_CREATE, result);
                REGISTER_IOCTL_32(IOCTL_ESDCAN_EEI_DESTROY, result);
                REGISTER_IOCTL_32(IOCTL_ESDCAN_EEI_STATUS, result);
                REGISTER_IOCTL_32(IOCTL_ESDCAN_EEI_CONFIGURE, result);
                REGISTER_IOCTL_32(IOCTL_ESDCAN_EEI_START, result);
                REGISTER_IOCTL_32(IOCTL_ESDCAN_EEI_STOP, result);
                REGISTER_IOCTL_32(IOCTL_ESDCAN_EEI_TRIGGER_NOW, result);

                REGISTER_IOCTL_32(IOCTL_ESDCAN_TX_OBJ_CREATE_T, result);
                REGISTER_IOCTL_32(IOCTL_ESDCAN_TX_OBJ_UPDATE_T, result);
                REGISTER_IOCTL_32(IOCTL_ESDCAN_TX_OBJ_AUTOANSWER_OFF_T, result);
                REGISTER_IOCTL_32(IOCTL_ESDCAN_TX_OBJ_AUTOANSWER_ON_T, result);
                REGISTER_IOCTL_32(IOCTL_ESDCAN_TX_OBJ_DESTROY_T, result);
                REGISTER_IOCTL_32(IOCTL_ESDCAN_TX_OBJ_CREATE_X, result);
                REGISTER_IOCTL_32(IOCTL_ESDCAN_TX_OBJ_UPDATE_X, result);
                REGISTER_IOCTL_32(IOCTL_ESDCAN_TX_OBJ_AUTOANSWER_OFF_X, result);
                REGISTER_IOCTL_32(IOCTL_ESDCAN_TX_OBJ_AUTOANSWER_ON_X, result);
                REGISTER_IOCTL_32(IOCTL_ESDCAN_TX_OBJ_DESTROY_X, result);

                REGISTER_IOCTL_32(IOCTL_ESDCAN_GET_INFO, result);

                REGISTER_IOCTL_32(IOCTL_ESDCAN_SET_FD_TDC, result);
                REGISTER_IOCTL_32(IOCTL_ESDCAN_GET_FD_TDC, result);

                REGISTER_IOCTL_32(IOCTL_LIN_MASTER_SEL, result);

                REGISTER_IOCTL_32(IOCTL_ESDCAN_TX_OBJ_AUTOANSWER_ONCE, result);
                REGISTER_IOCTL_32(IOCTL_ESDCAN_TX_OBJ_AUTOANSWER_ONCE_T, result);
                REGISTER_IOCTL_32(IOCTL_ESDCAN_TX_OBJ_AUTOANSWER_ONCE_X, result);

                REGISTER_IOCTL_32(IOCTL_ESDCAN_GET_HW_TIMESTAMP, result);
                REGISTER_IOCTL_32(IOCTL_ESDCAN_GET_HW_TIMESTAMP_EX, result);

                /* special ioctl (from candev driver) for driver version detection */
                REGISTER_IOCTL_COMPAT(IOCTL_CAN_SET_QUEUESIZE, result);
                if ( 0 != result ) {
                        CAN_PRINT(("esd CAN driver: An ioctl collides with an ioctl of another!\n"));
                        CAN_PRINT(("esd CAN driver: driver on your system!\n"));
                        CAN_PRINT(("esd CAN driver: Since this is a problem of the 32-bit compatibility\n"));
                        CAN_PRINT(("esd CAN driver: layer of linux, you can still load the driver with\n"));
                        CAN_PRINT(("esd CAN driver: module parameter \"compat32=0\", but you won't be\n"));
                        CAN_PRINT(("esd CAN driver: able to use 32-bit applications.\n"));
                        esdcan_unregister_ioctl32();
                }
        }
        return result;
}
#else /* #if (PLATFORM_64BIT) && (LINUX_VERSION_CODE <= KERNEL_VERSION(2,6,10)) */
int32_t esdcan_register_ioctl32(void) {return 0;}
void esdcan_unregister_ioctl32(void) {}
#endif /* #if (PLATFORM_64BIT) && (LINUX_VERSION_CODE <= KERNEL_VERSION(2,6,10)) */

/*
 *  The following includes contain system-specific code, which helps to reduce code
 *  duplication and ifdefs for different hardware.
 */
#if defined (BOARD_USB)
# if defined(OSIF_OS_LINUX)
#  include "esdcan_usb.c"
# else /* #if defined(OSIF_OS_LINUX) */
#  error "Currently USB is implemented for Linux, only!"
# endif /* #if defined(OSIF_OS_LINUX) */
#elif defined(ESDCAN_PCI_HOTPLUG)
# include "esdcan_pci.c"
#elif defined(BOARD_SPI)
# include "esdcan_spi.c"
#elif defined(BOARD_RAW)
# include "esdcan_raw.c"
#elif defined(BOARD_PCI)
# include "esdcan_pci_legacy.c"
#elif defined(BOARD_VME)
# include "esdcan_vme.c"
#elif defined(BOARD_SOFT)
# include "esdcan_soft.c"
#else /* #if defined (BOARD_USB) */
# error "Board type not properly defined!!!"
#endif /* #if defined (BOARD_USB) */

#if LINUX_VERSION_CODE >= KERNEL_VERSION(2,6,19)
static irqreturn_t irq_stub( int irq, void *arg )
{
        return ((CARD_IRQ*)arg)->handler(((CARD_IRQ*)arg)->context);
}
#elif LINUX_VERSION_CODE >= KERNEL_VERSION(2,6,0)
static irqreturn_t irq_stub( int irq, void *arg, struct pt_regs* regs )
{
        return ((CARD_IRQ*)arg)->handler(((CARD_IRQ*)arg)->context);
}
#else
static void irq_stub( int irq, void *arg, struct pt_regs* regs )
{
        ((CARD_IRQ*)arg)->handler(((CARD_IRQ*)arg)->context);
        return;
}
#endif

#include "esdcan_common.c" /* include common part of unix system layer */

#ifdef OSIF_OS_LINUX
static int esdcan_open(struct inode *inode, struct file *file)
{
        CAN_DBG((ESDCAN_ZONE_FU, "%s: pre LOCK\n", OSIF_FUNCTION));
        HOTPLUG_GLOBAL_LOCK;
# if LINUX_VERSION_CODE < KERNEL_VERSION(2,6,0)
        MOD_INC_USE_COUNT;
# endif /* # if LINUX_VERSION_CODE < KERNEL_VERSION(2,6,0) */
        CAN_DBG((ESDCAN_ZONE_FU, "%s: enter\n", OSIF_FUNCTION));
        file->private_data = 0;
        HOTPLUG_GLOBAL_UNLOCK;
        CAN_DBG((ESDCAN_ZONE_FU, "%s: leave\n", OSIF_FUNCTION));
        RETURN_TO_USER(OSIF_SUCCESS);
}
#endif /* #ifdef OSIF_OS_LINUX */

#ifdef OSIF_OS_LINUX
static int esdcan_release(struct inode *inode, struct file *file)
{
        INT32 result = OSIF_SUCCESS;
        CAN_OCB *ocb = (CAN_OCB*)file->private_data;

        CAN_DBG((ESDCAN_ZONE_FU, "%s: enter\n", OSIF_FUNCTION));
        if (ocb) {
                CAN_NODE *node = ocb->node;

                if ( 0 != HOTPLUG_BOLT_USER_ENTRY( ((CAN_CARD*)node->crd)->p_mod ) ) { /* BL: seems no good, needs rework */
                        CAN_DBG((ESDCAN_ZONE_FU, "%s: release needs abort!!!\n", OSIF_FUNCTION));
                        RETURN_TO_USER(result);
                }
                OSIF_MUTEX_LOCK(&node->lock);
                file->private_data = 0;
                if (!(ocb->close_state & CLOSE_STATE_HANDLE_CLOSED)) {
                        result = ocb_destroy(ocb);
                }
                OSIF_FREE(ocb->rx.cmbuf);
                OSIF_FREE(ocb);
                OSIF_MUTEX_UNLOCK(&node->lock);
                HOTPLUG_BOLT_USER_EXIT( ((CAN_CARD*)node->crd)->p_mod );
        }
# if LINUX_VERSION_CODE < KERNEL_VERSION(2,6,0)
        MOD_DEC_USE_COUNT;
# endif /* # if LINUX_VERSION_CODE < KERNEL_VERSION(2,6,0) */
        CAN_DBG((ESDCAN_ZONE_FU, "%s: leave\n", OSIF_FUNCTION));
        RETURN_TO_USER(result);
}
#endif /* OSIF_OS_LINUX */

INT32 can_attach_common(CAN_CARD *crd)
{
        VOID       *vptr;
        INT32       idx_node, idx_irq;
        INT32       result = OSIF_SUCCESS, lastError = OSIF_SUCCESS;
        CARD_IDENT *pCardIdent;

        CAN_DBG((ESDCAN_ZONE_INI, "%s: enter (crd=%p)\n", OSIF_FUNCTION, crd));
        if (MAX_CARDS <= crd->card_no) {
                CAN_PRINT(("esd CAN driver: ERROR - Maximum number of supported cards (%d) reached. Card ignored!\n", MAX_CARDS));
                lastError = OSIF_NOT_SUPPORTED;
                goto common_attach_0;
        }
        for(idx_node = 0; idx_node < NODES_PER_CARD; idx_node++) {
                CAN_NODE *node;

                result = OSIF_MALLOC(sizeof(*node), &vptr);
                if(OSIF_SUCCESS != result) {
                        break;
                }
                node = (CAN_NODE*)vptr;
                OSIF_MEMSET(node, 0, sizeof(*node));
                node->crd     = crd;
                node->mode    = mode;  /* insmod parameter */
                node->net_no  = crd->card_no*NODES_PER_CARD + idx_node;
                node->node_no = idx_node;
                init_waitqueue_head(&node->wqRxNotify);
                if (clock != 0) {
                        node->ctrl_clock = clock;
                }
                node->tx_ts_win = txtswin;
                OSIF_MUTEX_CREATE(&node->lock);
                OSIF_IRQ_MUTEX_CREATE(&node->lock_irq);
                crd->node[idx_node] = node;
        }
        if( OSIF_SUCCESS != result ) {
                lastError = result;
                goto common_attach_1;
        }
        result = can_board_attach(crd);
        if( OSIF_SUCCESS != result ) {
                lastError = result;
                if( OSIF_ERESTART == result ) {
                        CAN_PRINT(("esd CAN driver: !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!\n"));
                        CAN_PRINT(("esd CAN driver: !!!!!      Bootloader update necessary.          !!!!!\n"));
                        CAN_PRINT(("esd CAN driver: !!!!!    Load a driver with version < 3.9.7      !!!!!\n"));
                        CAN_PRINT(("esd CAN driver: !!!!!   to automatically update the bootloader.  !!!!!\n"));
                        CAN_PRINT(("esd CAN driver: !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!\n"));
                }
                goto common_attach_1;   /* AB TODO: this leads to an undestroyed crd->lock_irq !!! */
        }
        pCardIdent = crd->pCardIdent;
        for(idx_irq = 0;
            (idx_irq < 8) &&
            (pCardIdent->all.irqs[idx_irq].handler != (VOID*)(~0x0));
            idx_irq++) {
                if (NULL == pCardIdent->all.irqs[idx_irq].handler) {
                        continue;
                }
/* BL TODO: timestamps on baudrate change events
Idea: force affinity to the same CPU as DPC thread
set_ioapic_affinity
irq_desc[irq].handler->set_affinity(irq, new_value)
UINT32 cpus = num_online_cpus();
cpumask_t mask;
cpus_clear(mask);
cpus -= 1;
cpu_set(cpus, mask);
long sched_setaffinity(pid_t pid, cpumask_t new_mask)
 */
                crd->irqs[idx_irq] = pCardIdent->all.irqs[idx_irq];
                if (0 != request_irq(crd->irq[idx_irq],
                                     (void*)irq_stub,
                                     ESDCAN_IRQ_FLAGS,
                                     pCardIdent->all.name,
                                     &crd->irqs[idx_irq])) {
                        crd->irqs[idx_irq].handler = NULL;
                        crd->irqs[idx_irq].context = NULL;
                        result = CANIO_EBUSY;
                        CAN_DBG((ESDCAN_ZONE_INI,
                                 "%s: IRQ request FAILURE: IRQ: %d, Stub: %p, Param: %p\n",
                                 OSIF_FUNCTION,
                                 crd->irq[idx_irq],
                                 (void*)irq_stub,
                                 &crd->irqs[idx_irq]));
                        break;
                }
                CAN_DBG((ESDCAN_ZONE_INI, "%s: irq requested: IRQ: %d, Stub: %p, Param: %p\n",
                         OSIF_FUNCTION,
                         crd->irq[idx_irq],
                         (void*)irq_stub,
                         &crd->irqs[idx_irq]));
        }
        if( OSIF_SUCCESS != result ) {
                lastError = result;
                goto common_attach_2;
        }
        crd->num_nodes = 0;
        for( idx_node = 0; idx_node < NODES_PER_CARD; idx_node++ ) {
                CAN_NODE *node = crd->node[idx_node];
                if(NULL == node) {
                        continue;
                }
                node->features |= crd->features;
                CAN_DBG((ESDCAN_ZONE_INI, "%s: calling nuc_node_attach\n", OSIF_FUNCTION));
                result = nuc_node_attach( node, 0 );
                if (OSIF_SUCCESS != result) {
                        CAN_DBG((ESDCAN_ZONE_INI, "%s: nuc_node_attach failed (%d)\n", OSIF_FUNCTION, result));
                        OSIF_IRQ_MUTEX_DESTROY( &node->lock_irq );
                        OSIF_MUTEX_DESTROY( &node->lock );
                        OSIF_FREE( node );

                        crd->node[idx_node] = NULL;
                }
                nodes[crd->card_no*NODES_PER_CARD + idx_node] = crd->node[idx_node];
                if ( NULL == crd->node[idx_node]) {
                        continue;
                }
                CAN_DBG((ESDCAN_ZONE_INI, "%s: Node attached (features=%08x)\n", OSIF_FUNCTION, node->features));
                ++crd->num_nodes;
        }
        if( 0 == crd->num_nodes ) {
                CAN_DBG((ESDCAN_ZONE_INI, "%s: no node working\n", OSIF_FUNCTION));
                lastError = result;
                goto common_attach_3;
        }
        result = can_board_attach_final(crd);
        if( OSIF_SUCCESS != result ) {
                lastError = result;
                goto common_attach_3;
        }
        CAN_DBG((ESDCAN_ZONE_INI, "%s: leave (result=%d)\n", OSIF_FUNCTION, result));
        return result;

 common_attach_3:
        CAN_DBG((ESDCAN_ZONE_INI,
                 "%s: common_attach_3: can_board_attach_final or nuc_node_attach failed\n",
                 OSIF_FUNCTION));
        for( idx_node = 0; idx_node < NODES_PER_CARD; idx_node++ ) {
                CAN_NODE *node = crd->node[idx_node];
                if ( NULL == node ) {
                        continue;
                }
                nodes[crd->card_no * NODES_PER_CARD + idx_node] = NULL;
                nuc_node_detach( node );
        }

 common_attach_2:
        CAN_DBG((ESDCAN_ZONE_INI,
                 "%s: common_attach_2: Failed to request IRQ\n",
                 OSIF_FUNCTION));
        for( idx_irq = 0;
             (idx_irq < 8) &&
             (pCardIdent->all.irqs[idx_irq].handler != (VOID*)(-1));
             idx_irq++ ) {
                if( NULL != crd->irqs[idx_irq].context ) {
                        free_irq(crd->irq[idx_irq], &crd->irqs[idx_irq]);
                }
        }
        can_board_detach(crd);

 common_attach_1:
        CAN_DBG((ESDCAN_ZONE_INI,
                 "%s: common_attach_1: Allocation of node-struct or can_board_attach failed\n",
                 OSIF_FUNCTION));
        for( idx_node-- /* current idx did't get the mem */;
             idx_node >= 0;
             idx_node--) {
                CAN_NODE *node = crd->node[idx_node];
                if ( NULL == node ) {
                        continue;
                }
                OSIF_IRQ_MUTEX_DESTROY(&node->lock_irq);
                OSIF_MUTEX_DESTROY(&node->lock);
                OSIF_FREE(node);
        }
common_attach_0:
        CAN_DBG((ESDCAN_ZONE_INI, "%s: leave (error=%d)\n", OSIF_FUNCTION, lastError));
        return lastError;
}

VOID can_detach_common( CAN_CARD *crd, INT32 crd_no )
{
        UINT32      j;
        CARD_IDENT *pCardIdent = crd->pCardIdent;

        CAN_DBG((ESDCAN_ZONE_INI, "%s: enter\n", OSIF_FUNCTION));
        can_board_detach(crd);
        for ( j = 0; (j < 8) && ((VOID *)(~0x0) != pCardIdent->all.irqs[j].handler); j++ ) {
                if ( NULL != crd->irqs[j].context ) {
                        free_irq(crd->irq[j], &crd->irqs[j]);
                        CAN_DBG((ESDCAN_ZONE_INI, "%s:%d: free irq IRQ: %d\n",
                                 OSIF_FUNCTION, j, crd->irq[j]));
                }
        }
        for ( j = 0; j < NODES_PER_CARD; j++ ) {
                CAN_NODE *node = crd->node[j];
                if ( NULL == node ) {
                        continue;
                }
                nodes[crd_no * NODES_PER_CARD + j] = NULL;
                nuc_node_detach( node );
                OSIF_IRQ_MUTEX_DESTROY( &node->lock_irq);
                OSIF_MUTEX_DESTROY( &node->lock);
                OSIF_FREE(node);
        }
        (void)CAN_BOARD_DETACH_FINAL(crd);
#ifdef ESDCAN_PCI_HOTPLUG
        /* Use release code from esdcan_pci.c. */
        pci_bars_release(crd);

#else /* !ESDCAN_PCI_HOTPLUG */
# ifndef BOARD_SPI
        for ( j = 0; (j < 8) && (0xFFFFFFFF != pCardIdent->all.spaces[j]); j++ ) {
            if( 0 != (pCardIdent->all.spaces[j] & 0x00000001) ) { /* if io-space */
#  if LINUX_VERSION_CODE >= KERNEL_VERSION(2,4,0)
                release_region((UINTPTR)crd->base[j], crd->range[j]);
#  else /* #if LINUX_VERSION_CODE >= KERNEL_VERSION(2,4,0) */
#   warning "AB TODO: Still need mechanism to release mem-regions in 2.2.x kernels!!!"
#  endif /* #if LINUX_VERSION_CODE >= KERNEL_VERSION(2,4,0) */
            } else {
#  if !(defined(CONFIG_OF_DEVICE) || defined(CONFIG_OF_FLATTREE))
                iounmap(crd->base[j]);
#  endif /* !(CONFIG_OF_DEVICE || CONFIG_OF_FLATTREE)*/
            }
        }
# endif /* !BOARD_SPI */
#endif /* ESDCAN_PCI_HOTPLUG */
        CAN_DBG((ESDCAN_ZONE_INI, "%s: leave\n", OSIF_FUNCTION));
        return;
}

static VOID esdcan_show_card_info( CAN_CARD *crd )
{
        char    msg_buf[96];
        INT32   i, n, pos;

        if ( (crd->version_firmware.level != 0) ||
             (crd->version_firmware.revision != 0) ||
             (crd->version_firmware.build != 0) ) {
                CAN_DPRINT((OSIF_ZONE_USR_INIT,
                            "esd CAN driver: Firmware-version = %1X.%1X.%02X (hex)\n",
                            crd->version_firmware.level,
                            crd->version_firmware.revision,
                            crd->version_firmware.build));
        }
        if ( (crd->version_hardware.level != 0) ||
             (crd->version_hardware.revision != 0) ||
             (crd->version_hardware.build != 0) ) {
                        CAN_DPRINT((OSIF_ZONE_USR_INIT,
                                    "esd CAN driver: Hardware-version = %1X.%1X.%02X (hex)\n",
                                    crd->version_hardware.level,
                                    crd->version_hardware.revision,
                                    crd->version_hardware.build));
        } else {
                CAN_DPRINT((OSIF_ZONE_USR_INIT, "esd CAN driver: Hardware-version = 1.0.00\n"));
        }
        /* Print the list of minor numbers and the card number in a single kprintf call to guarantee a
         * single output line in the kernel log! */
        pos = OSIF_SNPRINTF((msg_buf, sizeof msg_buf, "esd CAN driver: Card = %d Minor(s) =", crd->card_no));
        for ( i = 0, n = 0; NODES_PER_CARD > i; i++ ) {
                if ( NULL == crd->node[i] ) {
                        continue;
                }
                pos += OSIF_SNPRINTF((msg_buf+pos, sizeof msg_buf -pos, "%s%d",
                                      n++ ? ", " : " ", crd->card_no * NODES_PER_CARD + i));
        }
        CAN_DPRINT((OSIF_ZONE_USR_INIT, "%s\n", msg_buf));
        return;
}

/*!
 *  \brief This function prints all information, that might be useful to the user
 *  at the time the driver is loaded. Use this function in init-functions (such as
 *  esdcan_init())
 */
static VOID esdcan_show_driver_info( VOID )
{
#define BUILD_DATE_SIZE 32
        CHAR8   user_build_date[BUILD_DATE_SIZE];

        user_build_date[0] = '?';
        user_build_date[1] = '\0';
        nuc_build_date_get(user_build_date, BUILD_DATE_SIZE);

        CAN_DPRINT((OSIF_ZONE_USR_INIT,
                    "esd CAN driver: %s\n", ESDCAN_DRIVER_NAME));
        CAN_DPRINT((OSIF_ZONE_USR_INIT,
                    "esd CAN driver: mode=0x%08x, major=%d, verbose=0x%08x\n",
                    mode, major, verbose));
        CAN_DPRINT((OSIF_ZONE_USR_INIT,
                    "esd CAN driver: Version %d.%d.%d\n", LEVEL, REVI, BUILD));
#if defined(ESDCAN_SPLIT_BUILD)
        CAN_DPRINT((OSIF_ZONE_USR_INIT,
                    "esd CAN driver: Build (esd %s; customer "__DATE__", "__TIME__")\n",
                           user_build_date));
#else
        CAN_DPRINT((OSIF_ZONE_USR_INIT,
                    "esd CAN driver: Build (esd %s)\n", user_build_date));
#endif
#undef BUILD_DATE_SIZE
}

/*
 * This function shows "load done" and a debug warning in CAN_DEBUG mode. It should be
 * called when the driver is successfully loaded from an init function such as
 * esdcan_init().
 */
static VOID esdcan_show_done_info( VOID )
{
        CAN_DPRINT((OSIF_ZONE_USR_INIT, "esd CAN driver: successfully loaded\n"));
#if defined(CAN_DEBUG)
        CAN_PRINT(("esd CAN driver: !!! DEBUG VERSION !!!\n"));
        CAN_PRINT(("Please note:\n"));
        CAN_PRINT(("You're using a debug version of the esd CAN driver.\n"));
        CAN_PRINT(("This version is NOT intended for productive use.\n"));
        CAN_PRINT(("The activated debug code might have bad influence\n"));
        CAN_PRINT(("on performance and system load.\n"));
        CAN_PRINT(("If you received this driver from somebody else than\n"));
        CAN_PRINT(("esd support, please report to \"support@esd.eu\".\n"));
        CAN_PRINT(("Thank you!\n"));
#endif /* #if defined(CAN_DEBUG) */
        return;
}

#if !defined(ESDCAN_HOTPLUG_DRIVER) && !defined(BOARD_SPI)
static VOID esdcan_show_card_info_all( VOID )
{
        UINT32 i;

        for ( i = 0; i < MAX_CARDS; i++ ) {
                CAN_CARD *crd;

                HOTPLUG_BOLT_SYSTEM_ENTRY(modules[i]);
                crd = GET_CARD_POINTER(i);
                if ( NULL == crd ) {
                        HOTPLUG_BOLT_SYSTEM_EXIT(modules[i]);
                        continue;
                }
                esdcan_show_card_info(crd);
                HOTPLUG_BOLT_SYSTEM_EXIT(modules[i]);
                CAN_DPRINT((OSIF_ZONE_USR_INIT, "\n"));
        }
        return;
}

INT32 can_detach_legacy( VOID )
{
        INT32 result = OSIF_SUCCESS;
        UINT32 i;

        CAN_DBG((ESDCAN_ZONE_INIFU, "%s: enter\n", OSIF_FUNCTION));
        for( i = 0; i < MAX_CARDS; i ++) {
                CAN_CARD *crd = GET_CARD_POINTER(i);
                if ( NULL == crd ) {
                        continue;
                }
                GET_CARD_POINTER(i) = NULL;
                can_detach_common(crd, i);
                OSIF_FREE( crd );
        }
        CAN_DBG((ESDCAN_ZONE_INIFU, "%s: leave\n", OSIF_FUNCTION));
        return result;
}

/*! Executed ONCE when driver module is loaded */
int OSIF__INIT esdcan_init_legacy(void)
{
        INT32 result = 0;

        CAN_DBG((ESDCAN_ZONE_INIFU, "%s: enter\n", OSIF_FUNCTION));
        CAN_DPRINT((OSIF_ZONE_USR_INIT, "esd CAN driver: init start\n"));
        esdcan_show_driver_info();
# ifdef LTT
        can_ltt0 = trace_create_event("CAN_LTT_0",
                                      NULL,
                                      CUSTOM_EVENT_FORMAT_TYPE_HEX,
                                      NULL);
# endif /* LTT */
        if (esdcan_register_ioctl32()) {
                RETURN_TO_USER(OSIF_INVALID_PARAMETER);
        }
        if ( OSIF_ATTACH() ) {
                CAN_DBG((ESDCAN_ZONE_INI, "%s: osif_attach failed!!!\n", OSIF_FUNCTION));
                esdcan_unregister_ioctl32();
                RETURN_TO_USER(OSIF_INSUFFICIENT_RESOURCES);
        }
        result = can_attach();
        if ( result != OSIF_SUCCESS ) {
                OSIF_DETACH();
                esdcan_unregister_ioctl32();
                RETURN_TO_USER(result);
        }
        esdcan_show_card_info_all();
# ifndef OSIF_OS_RTAI
        /* register device */
        if ( 0 != register_chrdev( major, ESDCAN_DRIVER_NAME, &esdcan_fops ) ) {
                CAN_PRINT(("esd CAN driver: cannot register character device for major=%d\n", major));
                CAN_DETACH;
                OSIF_DETACH();
                esdcan_unregister_ioctl32();
                RETURN_TO_USER(EBUSY);
        }
# endif /* OSIF_OS_RTAI */
        esdcan_proc_nodeinit_create();
        esdcan_show_done_info();
        CAN_DBG((ESDCAN_ZONE_INIFU, "%s: leave\n", OSIF_FUNCTION));
        RETURN_TO_USER(result);
}

/*! Executed when driver module is unloaded */
void OSIF__EXIT esdcan_exit_legacy(void)
{
        CAN_DBG((ESDCAN_ZONE_INIFU, "%s: enter, unloading esd CAN driver\n", OSIF_FUNCTION));
        unregister_chrdev(major, ESDCAN_DRIVER_NAME);
        esdcan_unregister_ioctl32();
        CAN_DETACH;
# ifdef LTT
        trace_destroy_event(can_ltt0);
# endif /* #ifdef LTT */
        esdcan_proc_nodeinit_remove();
        OSIF_DETACH();
        CAN_DPRINT((OSIF_ZONE_USR_INIT, "esd CAN driver: unloaded\n"));
        CAN_DBG((ESDCAN_ZONE_INIFU, "%s: leave\n", OSIF_FUNCTION));
}

OSIF_MODULE_INIT(esdcan_init_legacy);
OSIF_MODULE_EXIT(esdcan_exit_legacy);
#endif /* !defined(ESDCAN_HOTPLUG_DRIVER) && !defined(BOARD_SPI) */

MODULE_AUTHOR("esd electronics gmbh, support@esd.eu");
MODULE_DESCRIPTION("esd CAN driver");
MODULE_LICENSE("Proprietary");

#ifdef OSIF_OS_RTAI
EXPORT_SYMBOL(esdcan_read);
EXPORT_SYMBOL(esdcan_write);
EXPORT_SYMBOL(esdcan_ctrl);
#else /* #ifdef OSIF_OS_RTAI */
# if LINUX_VERSION_CODE < KERNEL_VERSION(2,6,0)
EXPORT_NO_SYMBOLS;
# endif /* #if LINUX_VERSION_CODE < KERNEL_VERSION(2,6,0) */
#endif /* #ifdef OSIF_OS_RTAI */


OSIF_RCSID("$Id: esdcan.c 16773 2020-07-09 17:45:39Z stefanm $");

/*---------------------------------------------------------------------------*/
/*                                 EOF                                       */
/*---------------------------------------------------------------------------*/
