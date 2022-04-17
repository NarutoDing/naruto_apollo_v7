/* -*- esdcan-c -*-
 * FILE NAME esdcan_pci.c
 *           copyright 2005 - 2020 by esd electronics gmbh
 *
 * BRIEF MODULE DESCRIPTION
 *           This file contains entries common to PCI devices
 *           for Linux/RTAI/IRIX
 *           for the esd CAN driver
 *
 *
 * Author:   Andreas Block
 *           andreas.block@esd-electronics.com
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
/*! \file esdcan_pci.c
    \brief Hotplugable PCI device support

    This file contains the PCI device initialization of the esdcan
    hotplug driver.
*/

#if LINUX_VERSION_CODE >= KERNEL_VERSION(2,6,30)
# define PCI_DRIVER_DATA_GET(pdev)      dev_get_drvdata(&pdev->dev)
# define PCI_DRIVER_DATA_SET(pdev, d)   dev_set_drvdata(&pdev->dev, d)
#elif LINUX_VERSION_CODE >= KERNEL_VERSION(2,6,0)
# define PCI_DRIVER_DATA_GET(pdev)      pdev->dev.driver_data
# define PCI_DRIVER_DATA_SET(pdev, d)   pdev->dev.driver_data = d
#else
# define PCI_DRIVER_DATA_GET(pdev)      pdev->driver_data
# define PCI_DRIVER_DATA_SET(pdev, d)   pdev->driver_data = d
#endif

/* Bolts not needed for PCI hotplug driver,
 *  but are used in common files
 *  (namely esdcan.c and esdcan_common.c) */
#define HOTPLUG_BOLT_SYSTEM_ENTRY(mod)
#define HOTPLUG_BOLT_SYSTEM_EXIT(mod)
#define HOTPLUG_BOLT_USER_ENTRY(mod)   0
#define HOTPLUG_BOLT_USER_EXIT(mod)
#define HOTPLUG_GLOBAL_LOCK
#define HOTPLUG_GLOBAL_UNLOCK

/*
 *  Forward declarations
 */
VOID can_detach_common( CAN_CARD *crd, INT32 crd_no ); /* implemented in esdcan.c */
static int OSIF__INIT esdcan_init(struct pci_dev *dev, const struct pci_device_id *pci_id);
static VOID OSIF__EXIT esdcan_exit(struct pci_dev *dev);

/*
 * Table of devices that work with this driver
 */
static struct pci_device_id esdcan_pci_tbl[] = {
        ESDCAN_IDS_PCI,
        {0,}
};

#if LINUX_VERSION_CODE > KERNEL_VERSION(2,6,9)
/* AB: Actually .owner came in with 2.6.9 in most distributions.
 *     Except Fedora 3, where it was introduced with 2.6.10 :( */
static struct pci_driver esdcan_pci_driver = {
# if LINUX_VERSION_CODE < KERNEL_VERSION(2,6,15) /* AB: kernel developers love consistence :( */
        .owner    = THIS_MODULE,
# endif
        .name     = ESDCAN_DRIVER_NAME,
        .id_table = esdcan_pci_tbl,
        .probe    = esdcan_init,
#if LINUX_VERSION_CODE <= KERNEL_VERSION(3,7,0)
        .remove   = __devexit_p(esdcan_exit),
#else
        .remove   = esdcan_exit, /* back to the roots */
#endif
};
#elif LINUX_VERSION_CODE >= KERNEL_VERSION(2,6,0)
static struct pci_driver esdcan_pci_driver = {
        .name     = ESDCAN_DRIVER_NAME,
        .id_table = esdcan_pci_tbl,
        .probe    = esdcan_init,
        .remove   = __devexit_p(esdcan_exit),
};
#else
static struct pci_driver esdcan_pci_driver = {
        name:     ESDCAN_DRIVER_NAME,
        id_table: esdcan_pci_tbl,
        probe:    esdcan_init,
        remove:   esdcan_exit,
};
#endif
#if LINUX_VERSION_CODE >= KERNEL_VERSION(2,6,0) /* AB TODO: since version 2.4.x???*/
MODULE_DEVICE_TABLE(pci, esdcan_pci_tbl);
#endif
/* Version Information */
#define DRIVER_VERSION LEVEL"."REVI"."BUILD
#define DRIVER_AUTHOR  "esd electronics gmbh, support@esd.eu"
#define DRIVER_DESC    "PCI-CAN-driver"

static int esdcan_pci_driver_registered = 0;
static int esdcan_pci_attached_cards = 0;

static void pci_bars_release(CAN_CARD *crd) {
        struct pci_dev *pciDev = crd->pciDev;
        int j;

        for ( j = 0; j < 8; j++ ) {
                /* UNMAP */
                if( NULL != crd->base[j] ) {
                        pci_iounmap(pciDev, crd->base[j]);
                }
                /* RELEASE */
                if ( 0 != crd->range[j] ) {
                        pci_release_region(pciDev, j);
                }
        }
}

int can_attach(struct pci_dev *pciDev, const struct pci_device_id *pci_id)
{
        UINT32      j;
        INT32       lastError = OSIF_SUCCESS;
        INT32       result;
        CAN_CARD   *crd;
        VOID       *vptr;
        CARD_IDENT *pCardIdent = 0;

        /* This shouldn't occurr in real life! */
        if ( NULL == cardFlavours ) {
                CAN_PRINT(("esd CAN driver: Severe problem with board layer! Card flavour missing!\n"));
                lastError = ENODEV;
                return lastError;
        }
        /* Determine flavour (needed to get name of card, etc...) */
        for ( pCardIdent = &cardFlavours[0]; NULL != pCardIdent->pci.irqs; pCardIdent++ ) {
                if ( (pciDev->vendor == pCardIdent->pci.ids.vendor) &&
                     (pciDev->device == pCardIdent->pci.ids.device) &&
                     (pciDev->subsystem_vendor == pCardIdent->pci.ids.subVendor) &&
                     (pciDev->subsystem_device == pCardIdent->pci.ids.subDevice) &&
                     ((! pCardIdent->pci.ids.class) || ((pciDev->class >> 8) == pCardIdent->pci.ids.class)) ) {
                        break;
                }
        }
        if ( NULL == pCardIdent->pci.irqs ) {
                CAN_PRINT(("esd CAN driver: This PCI-hardware is not supported by this driver.\n"));
                lastError = ENODEV;
                return lastError;
        }
        result = OSIF_MALLOC(sizeof(*crd), &vptr);
        if ( OSIF_SUCCESS != result ) {
                lastError = result;
                CAN_PRINT(("%s: Not enough memory for crd-struct\n",
                           pCardIdent->pci.name));
                return lastError;
        }
        crd = (CAN_CARD*)vptr;
        CAN_DBG((ESDCAN_ZONE_INI, "crd @%p\n",   crd ));
        OSIF_MEMSET( crd, 0, sizeof(*crd) );
        crd->pCardIdent = pCardIdent;
        crd->card_no = esdcan_pci_attached_cards;
        crd->features = CARD_FEATURES;
        CAN_DBG((ESDCAN_ZONE_INI, "PCI-Bus      : %d\n",   pciDev->bus->number ));
        CAN_DBG((ESDCAN_ZONE_INI, "PCI-Slot     : %d\n",   pciDev->devfn ));
        CAN_DBG((ESDCAN_ZONE_INI, "PCI-Ven.-ID  : %04x\n", pciDev->vendor));
        CAN_DBG((ESDCAN_ZONE_INI, "PCI-Dev.-ID  : %04x\n", pciDev->device));
        CAN_DBG((ESDCAN_ZONE_INI, "PCI-SubVen.ID: %04x\n", pciDev->subsystem_vendor));
        CAN_DBG((ESDCAN_ZONE_INI, "PCI-SubSys.ID: %04x\n", pciDev->subsystem_device));
        CAN_DBG((ESDCAN_ZONE_INI, "PCI-Class    : %04x\n", pciDev->class));
        CAN_DBG((ESDCAN_ZONE_INI, "PCI-Irq      : %d\n",   pciDev->irq));
        if ( pci_enable_device(pciDev) ) {
                result = EIO;
                goto release_1;
        }
        crd->pciDev = pciDev; /* used by pci405 and can_detach_common() */

        for ( j = 0; (j < 8) && (pCardIdent->pci.spaces[j] != 0xFFFFFFFF); j++ ) {
                unsigned long rsc_flags;

                if (0 == pCardIdent->pci.spaces[j]) continue;   /* Skip zero length spaces */

                /* CHECK */
                rsc_flags = pci_resource_flags(pciDev, j);
                if ( rsc_flags & IORESOURCE_MEM ) {     /* PCI Memory space */
                        /* Sanity check, if board layer expected memory space, too */
                        if ( pCardIdent->pci.spaces[j] & 0x00000001 ) {
                                CAN_DBG((ESDCAN_ZONE_INI,
                                         "%s: BAR%d: Config space says MEM space, "
                                         "board layer says IO space!!!\n",
                                         OSIF_FUNCTION, j));
                                result = ENOMEM;
                                break;
                        }
                } else if ( rsc_flags & IORESOURCE_IO ) {       /* PCI IO space */
                        /* Sanity check, if board layer expected IO space, too */
                        if ( 0 == (pCardIdent->pci.spaces[j] & 0x00000001)) {
                                CAN_DBG((ESDCAN_ZONE_INI,
                                         "%s: BAR%d: Config space says IO space, "
                                         "board layer says MEM space!!!\n",
                                         OSIF_FUNCTION, j));
                                result = ENOMEM;
                                break;
                        }
                }
                /* REQUEST */
                if ( 0 != pci_request_region(pciDev, j, pCardIdent->pci.name)) {
                        CAN_PRINT(("%s: Resource-Conflict: "
                                   "BAR%d %0lx - %0lx already occupied!\n",
                                   pCardIdent->pci.name,
                                   pci_resource_start(pciDev, j), pci_resource_end(pciDev, j)));
                        result = EBUSY;
                        break;
                }
                /* Note the shortest length of the range from board layer or PCI config space */
                crd->range[j] = pCardIdent->pci.spaces[j] & 0xFFFFFFFE;
                if ( crd->range[j] > pci_resource_len(pciDev, j) ) {
                        crd->range[j] = pci_resource_len(pciDev, j);
                }
                CAN_DBG((ESDCAN_ZONE_INI, "%s: BAR%d: range=0x%0x\n",
                         OSIF_FUNCTION, j, crd->range[j]));
                /* MAP: pci_iomap() handles MEM / IO distinction internally. */
                crd->base[j] = pci_iomap(pciDev, j, crd->range[j]);
                if ( NULL == crd->base[j] ) {
                        CAN_DBG((ESDCAN_ZONE_INI,
                                 "%s: BAR%d: Can't map PCI @0x%0lx\n",
                                 OSIF_FUNCTION,
                                 j,
                                 pci_resource_start(pciDev, j)));
                        result = ENOMEM;
                        break;
                } else {
                        CAN_DBG((ESDCAN_ZONE_INI,
                                 "%s: BAR%d: PCI @0x%0lx virtaddr=0x%p\n",
                                 OSIF_FUNCTION,
                                 j,
                                 pci_resource_start(pciDev, j),
                                 crd->base[j]));
                }
        }
        if ( OSIF_SUCCESS != result ) {
                lastError = result;
                goto release_2;
        }
#if defined(BOARD_BUSMASTER) && (LINUX_VERSION_CODE >= KERNEL_VERSION(2,6,12))
/* After a recent research even in Torvald's GIT tree, it is sure now that this function was available 
   since 2.6.12, probably way earlier */
        pci_set_master(pciDev);
#endif
#ifdef BOARD_MSI
#if LINUX_VERSION_CODE >= KERNEL_VERSION(2,6,1)
        if ((0 != (mode & DRIVER_PARAM_NO_MSI_MODE)) || pci_enable_msi(pciDev)) {
                crd->flagMsi = 0;
        } else {
                crd->flagMsi = 1;
        }
#else
        crd->flagMsi = 0;
#endif
#endif
        crd->irq[0] = pciDev->irq;
        result = can_attach_common(crd);
        if ( OSIF_SUCCESS != result ) {
                lastError = result;
                goto release_2;
        }
        PCI_DRIVER_DATA_SET(pciDev, crd);
        esdcan_pci_attached_cards++;
        return 0;

 release_2:
        CAN_DBG((ESDCAN_ZONE_INI, "%s: Release_2:\n", OSIF_FUNCTION));
        pci_bars_release(crd);

 release_1:
        CAN_DBG((ESDCAN_ZONE_INI, "%s: Release_1:\n", OSIF_FUNCTION));
#if defined(BOARD_MSI) && (LINUX_VERSION_CODE >= KERNEL_VERSION(2,6,1))
        if (crd->flagMsi) {
                pci_disable_msi(pciDev);
        }
#endif
#if defined(BOARD_BUSMASTER) && (LINUX_VERSION_CODE >= KERNEL_VERSION(2,6,29))
        pci_clear_master(pciDev);
#endif
        OSIF_FREE(crd);
        return lastError;
}


INT32 can_detach( struct pci_dev *pciDev )
{
        INT32     result = OSIF_SUCCESS;
        UINT32    card_no;
        CAN_CARD *crd;

        CAN_DBG((ESDCAN_ZONE_INIFU, "%s: enter\n", OSIF_FUNCTION));
        crd = PCI_DRIVER_DATA_GET(pciDev); /* crd-pointer is stored as driver's private data in pciDev */
        if (NULL == crd) {
                return 0;
        }
        card_no = crd->card_no;
        PCI_DRIVER_DATA_SET(pciDev, NULL);
        can_detach_common(crd, card_no);
#if defined(BOARD_MSI) && (LINUX_VERSION_CODE >= KERNEL_VERSION(2,6,1))
        if (crd->flagMsi) {
                pci_disable_msi(pciDev);
        }
#endif
#if defined(BOARD_BUSMASTER) && (LINUX_VERSION_CODE >= KERNEL_VERSION(2,6,29))
        pci_clear_master(pciDev);
#endif
        OSIF_FREE(crd);
        esdcan_pci_attached_cards--;
        CAN_DBG((ESDCAN_ZONE_INIFU, "%s: leave\n", OSIF_FUNCTION));
        return result;
}


/* Executed, when PCI card is plugged into the system
 * (this means actually, on driver load, by pci_register_driver())
 * Called ONCE FOR EVERY CAN-BOARD! */
static int OSIF__INIT esdcan_init(struct pci_dev *dev, const struct pci_device_id *pci_id)
{
        INT32 result = 0;

        CAN_DBG((ESDCAN_ZONE_INIFU, "%s: enter\n", OSIF_FUNCTION));
#ifdef LTT
        can_ltt0 = trace_create_event("CAN_LTT_0",
                                      NULL,
                                      CUSTOM_EVENT_FORMAT_TYPE_HEX,
                                      NULL);
#endif /* LTT */
        result = can_attach( dev, pci_id );
        if ( OSIF_SUCCESS != result ) {
                RETURN_TO_USER(result);
        }
        esdcan_show_card_info(PCI_DRIVER_DATA_GET(dev));
        CAN_DBG((ESDCAN_ZONE_INIFU, "%s: leave\n", OSIF_FUNCTION));
        RETURN_TO_USER(result);
}


/* Executed, when PCI card is unplugged
 * (this means actually, on driver unload, by pci_unregister_driver()) */
static VOID OSIF__EXIT esdcan_exit(struct pci_dev *dev)
{
        CAN_DBG((ESDCAN_ZONE_INIFU, "%s: enter, unloading esd CAN driver\n", OSIF_FUNCTION));
        can_detach(dev);
#ifdef LTT
        trace_destroy_event(can_ltt0);
#endif
        CAN_DPRINT((OSIF_ZONE_USR_INIT, "esd CAN driver: unloaded\n"));
        CAN_DBG((ESDCAN_ZONE_INIFU, "%s: leave\n", OSIF_FUNCTION));
}


/*! Executed when driver module is loaded */
OSIF_STATIC int __init esdcan_pci_init(VOID)
{
        INT32 result;

        CAN_DBG((ESDCAN_ZONE_INIFU, "%s: enter\n", OSIF_FUNCTION));
        CAN_DPRINT((OSIF_ZONE_USR_INIT, "esd CAN driver: init start\n"));
        esdcan_show_driver_info();
        esdcan_pci_driver_registered = 0;
        if (esdcan_register_ioctl32()) {
                CAN_DBG((ESDCAN_ZONE_INI, "%s: Failed to register 32-Bit IOCTLs!!!\n", OSIF_FUNCTION));
                result = OSIF_INVALID_PARAMETER;
                goto INIT_ERR_0;
        }
        if ( OSIF_ATTACH() ) {
                CAN_DBG((ESDCAN_ZONE_INI, "%s: osif_attach failed!!!\n", OSIF_FUNCTION));
                result = OSIF_INSUFFICIENT_RESOURCES;
                goto INIT_ERR_1;
        }
        /* register driver as PCI-driver */
        CAN_DBG((ESDCAN_ZONE_INI, "%s: Registering PCI driver...\n", OSIF_FUNCTION));
        result = pci_register_driver(&esdcan_pci_driver);
#if LINUX_VERSION_CODE > KERNEL_VERSION(2,6,8)
/* NOTE: Fedora Core 3 customers with kernel 2.6.9:
 *       For whatever reason Fedora chose not to use the patch, which fixes the problem
 *       with pci_register_driver return values. We don't support this kernel-version,
 *       please update to the next kernel-release (2.6.10 or following). */
        if ( result ) {
        /* Now: zero is success, everything else is considered an error */
                if ( result == 1 ) {
                        CAN_PRINT(("esd CAN driver: If you're a Fedora 3 user with kernel 2.6.9,\n"));
                        CAN_PRINT(("esd CAN driver: please update to kernel 2.6.10!\n"));
                }
#else
        if ( 0 > result ) {
        /* Older kernels were pretending to return a counter with initialized devices,
         *  actually pci-functions were sometimes cheating and returned always one!!!  */
#endif
                CAN_PRINT(("esd CAN driver: Initialization of PCI module failed (0x%08x)!\n", result));
                if ( 0 > result ) {
                        /* To prevent linux from actually registering the driver */
                        /* result is inverted on return */
                        result = -result;
                }
                goto INIT_ERR_2;
        }

        /* If we did not find any card, we cancel driver initialization,
         * in order to reduce user confusion */
        if ( 0 >= esdcan_pci_attached_cards ) {
                CAN_PRINT(("esd CAN driver: Version: 0x%08X\n", MAKE_VERSION(LEVEL, REVI, BUILD)));
                CAN_PRINT(("esd CAN driver: No esd CAN card found!\n"));
                result = OSIF_NET_NOT_FOUND;
                goto INIT_ERR_3;
        }
        /* register device for major-number */
        CAN_DBG((ESDCAN_ZONE_INI, "%s: Registering character device...\n", OSIF_FUNCTION));
        if ( 0 != register_chrdev( major, ESDCAN_DRIVER_NAME, &esdcan_fops ) ) {
                CAN_PRINT(("esd CAN driver: cannot register character device for major=%d\n", major));
                result = OSIF_EBUSY;
                goto INIT_ERR_3;
        }
        esdcan_proc_nodeinit_create();
        esdcan_pci_driver_registered = 1;
        esdcan_show_done_info();
        CAN_DBG((ESDCAN_ZONE_INIFU, "%s: leave\n", OSIF_FUNCTION));
        RETURN_TO_USER(0);

        INIT_ERR_3: /* No card found or failed to register driver for major number */
        pci_unregister_driver(&esdcan_pci_driver);
        INIT_ERR_2: /* Failed to register PCI driver */
        OSIF_DETACH();
        INIT_ERR_1: /* Failed to initialize OSIF layer */
        esdcan_unregister_ioctl32();
        INIT_ERR_0: /* Failed to register 32-Bit IOCTLs (on 64-Bit system) */
        RETURN_TO_USER(result);
}


/*! Executed when driver module is unloaded */
OSIF_STATIC VOID __exit esdcan_pci_exit(VOID)
{
        CAN_DBG((ESDCAN_ZONE_INIFU, "%s: enter\n", OSIF_FUNCTION));
        if ( 1 == esdcan_pci_driver_registered ) {
                unregister_chrdev( major, ESDCAN_DRIVER_NAME );
                pci_unregister_driver(&esdcan_pci_driver);
                esdcan_unregister_ioctl32();
                esdcan_proc_nodeinit_remove();
                esdcan_pci_driver_registered = 0;
                OSIF_DETACH();
        }
        CAN_DBG((ESDCAN_ZONE_INIFU, "%s: leave\n", OSIF_FUNCTION));
}

OSIF_MODULE_INIT(esdcan_pci_init);
OSIF_MODULE_EXIT(esdcan_pci_exit);
