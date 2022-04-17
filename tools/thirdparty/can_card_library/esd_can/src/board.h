/* -*- esdcan-c -*- */
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
/*! \file board.h
    \brief Card interface API

    This file contains the API for accessing the CAN driver's card layer.
    The functions are called by the nucleus modules.
*/

#ifndef __BOARD_H__
#define __BOARD_H__

#include <esdcan.h>
#ifdef VXBUS_GEN2
#include <hwif/vxBus.h>
#endif

#ifdef ESDDBG   /*!< Macro for debug prints, same in ALL board layer files... */
# define BOARD_DBG(fmt) OSIF_DPRINT(fmt)
#else
# define BOARD_DBG(fmt)
#endif

/* Zones to use with debug prints in boardrc.c */
#define RC_ZONE_FU          OSIF_ZONE_BOARD | OSIF_ZONE_FUNC
#define RC_ZONE_INIFU       OSIF_ZONE_BOARD | OSIF_ZONE_INIT|OSIF_ZONE_FUNC
#define RC_ZONE_INI         OSIF_ZONE_BOARD | OSIF_ZONE_INIT
#define RC_ZONE_IRQ         OSIF_ZONE_IRQ    /* DO NOT USE ANY MORE BITS (nto will thank you:) */
#define RC_ZONE_ALWAYS      0xFFFFFFFF
#define RC_ZONE_WARN        OSIF_ZONE_BOARD | OSIF_ZONE_WARN
#define RC_ZONE_USR_INIT    OSIF_ZONE_BOARD | OSIF_ZONE_USR_INIT
#define RC_ZONE             OSIF_ZONE_BOARD

/* Zones to use with debug prints in board.c */
#define BOARD_ZONE_INI      OSIF_ZONE_BOARD | OSIF_ZONE_INIT                    /* Driver init/deinit */
#define BOARD_ZONE_FU       OSIF_ZONE_BOARD | OSIF_ZONE_FUNC                    /* Function entry/exit */
#define BOARD_ZONE_INIFU    OSIF_ZONE_BOARD | OSIF_ZONE_INIT | OSIF_ZONE_FUNC
#define BOARD_ZONE_BAUD     OSIF_ZONE_BOARD | OSIF_ZONE_FUNC | OSIF_ZONE_BAUD   /* Function entry/exit in bitrate setting baud calculation... */
#define BOARD_ZONE_IRQ      OSIF_ZONE_IRQ                                       /* DO NOT USE ANY MORE BITS (nto will thank you:) */
#define BOARD_ZONE          OSIF_ZONE_BOARD

#ifndef CIF_TS2MS
#define CIF_TS2MS(ts, tsf)  do { UINT64 _ts=(UINT64)(ts),_tsf=(UINT64)(tsf);_ts *= 1000u; _ts+=_tsf-1u; OSIF_DIV64_64(_ts, _tsf); (ts)=_ts; } OSIF_ONCE /* round up */
#endif

    /* Copy a CAN_BITRATE structure without members baud and baud_req */
#define COPY_BAUD_INFO(dest, src)                 \
        (dest).valid = (src).valid;               \
        (dest).rate = (src).rate;                 \
        (dest).clock = (src).clock;               \
        (dest).ctrl_type = (src).ctrl_type;       \
        (dest).tq_pre_sp = (src).tq_pre_sp;       \
        (dest).tq_post_sp = (src).tq_post_sp;     \
        (dest).sjw = (src).sjw;                   \
        (dest).error = (src).error;               \
        (dest).flags = (src).flags;               \
        (dest).tq_pre_sp_d = (src).tq_pre_sp_d;   \
        (dest).tq_post_sp_d = (src).tq_post_sp_d; \
        (dest).sjw_d = (src).sjw_d;               \
        (dest).mode = (src).mode;                 \
        (dest).rate_d = (src).rate_d

    /* BTR values for nominal and data rate in controller specific format */
typedef struct {
    UINT32  arbBTR;
    UINT32  dataBTR;
} CIF_BAUD_X;

extern CARD_IDENT cardFlavours[];

extern INT32 cif_open( CAN_OCB *ocb, CAN_NODE *node, INT32 flags );
extern INT32 cif_close( CAN_OCB *ocb );
extern VOID  cif_node_initialize_tx_fifos(CAN_NODE *node);
extern INT32 cif_node_attach( CAN_NODE *node, UINT32 queue_size_rx);
extern INT32 cif_node_detach( CAN_NODE *node );
extern INT32 cif_id_filter( CAN_NODE *node, UINT32 cmd, UINT32 id, UINT32 *count );
extern INT32 OSIF_CALLTYPE cif_tx( CAN_NODE *node );
extern INT32 cif_tx_obj( CAN_NODE *node, UINT32 cmd, VOID *arg );
extern INT32 cif_tx_abort( CAN_NODE *node, CM *cm, INT32 status );
extern INT32 cif_baudrate_set( CAN_NODE *node, UINT32 baud );
extern INT32 cif_baudrate_nominal(const CAN_BAUDRATE_CFG *cfg, UINT16 flags, UINT32 *baud);
#if defined(BOARD_LIN)
extern INT32 OSIF_CALLTYPE cif_rx_lin( CAN_NODE *node);
#endif

/* can_node MUST be provided, ocb and waitContext might be NULL (should fail if ocb or waitContext needed then) */
extern INT32 cif_ioctl( CAN_NODE *can_node, CAN_OCB *ocb, VOID *waitContext, UINT32 cmd,
                        VOID *buf_in, UINT32 len_in, VOID *buf_out, UINT32 *len_out );

extern INT32 cif_timestamp( CAN_NODE *node, OSIF_TS *timestamp );

/* 1) implementation for soft timestamps is in board/<board>/board.c
   2) implementation for hard timestamps is in board/<board>/boardrc.c
      (this is very hardware specific !)
*/
extern INT32 cif_softts_get( VOID *dummy, OSIF_TS *ts );
extern INT32 cif_softts_freq_get( VOID *dummy, OSIF_TS_FREQ *ts_freq );

/* Enable/disable the interrupt (also implicitly called during attach/detach) */
extern INT32 OSIF_CALLTYPE can_board_enable_interrupt(CAN_CARD *crd);
extern INT32 OSIF_CALLTYPE can_board_disable_interrupt(CAN_CARD *crd);

INT32 OSIF_CALLTYPE can_board_attach_pre(CAN_CARD *crd);

#if defined(OSIF_PNP_OS)
INT32 OSIF_CALLTYPE can_board_attach( CAN_CARD *crd, OSIF_POWER_STATE targetState );
INT32 OSIF_CALLTYPE can_board_attach_final( CAN_CARD *crd, OSIF_POWER_STATE targetState );
INT32 OSIF_CALLTYPE can_board_detach( CAN_CARD *crd, OSIF_POWER_STATE targetState );
    /* CAN_BOARD_DETACH_FINAL may be defined in boardrc.h */
# ifndef CAN_BOARD_DETACH_FINAL
#  define CAN_BOARD_DETACH_FINAL(pCrd, targetState)    0
#  else
INT32 OSIF_CALLTYPE can_board_detach_final( CAN_CARD *crd, OSIF_POWER_STATE targetState );
# endif
#else
INT32 OSIF_CALLTYPE can_board_attach( CAN_CARD *crd );
INT32 OSIF_CALLTYPE can_board_attach_final( CAN_CARD *crd );
INT32 OSIF_CALLTYPE can_board_detach( CAN_CARD *crd );
    /* CAN_BOARD_DETACH_FINAL may be defined in boardrc.h */
#ifndef CAN_BOARD_DETACH_FINAL
# define CAN_BOARD_DETACH_FINAL(pCrd)    0
# else
INT32 OSIF_CALLTYPE can_board_detach_final( CAN_CARD *crd );
#endif
#endif /* of OSIF_PNP_OS */

#if defined (BOARD_USB)
VOID OSIF_CALLTYPE usb_write_tx_cm(const volatile UINT32 *pAddr, CM *pCm);
VOID OSIF_CALLTYPE usb_write_tx_ts_cm(const volatile UINT32 *pAddr, CM *pCm);
#endif

/*
 * Entries defined in the module 'baud.c'
 */ 
extern INT32 OSIF_CALLTYPE baud_cc_calc(CAN_NODE *node, UINT32 rate, CAN_BITRATE *baud_info);
extern INT32 OSIF_CALLTYPE baud_cc_get_info(CAN_NODE *node, UINT32 baud_req,
                                            CAN_BITRATE *baud_info);
extern INT32 OSIF_CALLTYPE baud_fd_get_info(CAN_NODE *can_node, CAN_BAUDRATE_X *baud,
                                            CIF_BAUD_X *cif_baud, CAN_BITRATE *baud_info);
extern VOID  OSIF_CALLTYPE baud_legacy_to_x(UINT32 baudLegacy, CAN_BAUDRATE_X *baud,
                                            CIF_BAUD_X *cif_baud);
extern INT32 OSIF_CALLTYPE baud_x_to_legacy(const CAN_BAUDRATE_X *baud, UINT32 *baudLegacy);

extern VOID  OSIF_CALLTYPE cif_timer_dpc(VOID* arg);
extern VOID  OSIF_CALLTYPE ctrl_dpc_can(VOID *can_node);
extern VOID  OSIF_CALLTYPE cif_dpc_timer(VOID* arg);
extern VOID  OSIF_CALLTYPE cif_timer_irq(CAN_CARD *pCrd);

/*
 * Commom entries implemented in module 'boardrc.c'
 */ 
UINT32 boardrc_fpga_type_get(VOID *pCrd);
VOID   boardrc_ts_set(VOID *pCanNode, OSIF_TS *pTs);
VOID   boardrc_tsfreq_get(VOID *pCanNode, OSIF_TS_FREQ *pFreq);
VOID   boardrc_corefreq_get(VOID *pCanNode, UINT32 *pFreq);
VOID   boardrc_timer_set(VOID *pCanCard, OSIF_TS *pTs);
VOID   boardrc_timer_get(VOID *pCanCard, OSIF_TS *pTs);

#endif /* __BOARD_H__ */
