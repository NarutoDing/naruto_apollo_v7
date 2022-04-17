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

#ifndef __NUCLEUS_H__
#define __NUCLEUS_H__

/* Forward declare pointers to structures only used by the nucleus internally to
 * have them available for the declaration of upper level structures in
 * <esdcan.h> and <board.h>.
 */
typedef struct _NUC_OCB         NUC_OCB;
typedef struct _NUC_NODE        NUC_NODE;

#include <esdcan.h>
#include <board.h>

#ifndef OSIF_KERNEL
#error "This file may be used in the kernel-context, only! Not for application-use!!!"
#endif

/* #define NUC_CHECK_LINKS */                 /* for debugging only, degrades performance significantly */

#ifndef NUC_NODE_RX_QUEUE_SIZE
#define NUC_NODE_RX_QUEUE_SIZE    1024        /* default very big rx queue inside node */
#endif

#define RX_LOOKUP_MAX_COUNT       4

#define NUC_TX_OBJ_CREATE         0
#define NUC_TX_OBJ_AUTOANSWER_ON  1
#define NUC_TX_OBJ_AUTOANSWER_OFF 2
#define NUC_TX_OBJ_UPDATE         3
#define NUC_TX_OBJ_DESTROY        4
#define NUC_TX_OBJ_SCHEDULE       5
#define NUC_TX_OBJ_SCHEDULE_START 6
#define NUC_TX_OBJ_SCHEDULE_STOP  7
#define NUC_TX_OBJ_AUTOANSWER_ONCE 8

#define NUC_RX_OBJ_CREATE    0
#define NUC_RX_OBJ_TAKE      1
#define NUC_RX_OBJ_DESTROY   2

#define NUC_STAT_CM_RX        0
#define NUC_STAT_CM_TX        1
#define NUC_STAT_CTRL_OVERR   2
#define NUC_STAT_FIFO_OVERR   3
#define NUC_STAT_ERROR_FRAME  4
#define NUC_STAT_ABORT        5

#define NUC_BIT_RATE_NOMINAL        0
#define NUC_BIT_RATE_DATA_PHASE     1


    /* Macros to operate on linked list (type definition in osif.h) */
#define INIT_LNK(lnk, _base) (lnk)->next=NULL; (lnk)->prev=NULL; (lnk)->base = (_base)
#define INIT_LNK_ROOT(lnk) (lnk)->next=(lnk); (lnk)->prev=(lnk)
#define GET_LNK_FIRST(root) ((root) == (root)->next ? NULL : (root)->next)
#define GET_LNK_NEXT(lnk, root) ((root) == (lnk)->next ? NULL : (lnk)->next)
#define GET_LNK_LAST(root) ((root) == (root)->prev ? NULL : (root)->prev)
#define GET_LNK_PREV(lnk, root) ((root) == (lnk)->prev ? NULL : (lnk)->prev)
        /*lint -emacro(522, ASK_LNK_CHANGED) (Operator '?' lacks side-effects) */
#define ASK_LNK_CHANGED(root) (root)->base == NULL ? 0 : ((root)->base = NULL, 1)
#define SET_LNK_CHANGED(root) (root)->base = (VOID *)(UINTPTR)1

extern UINT32 baud_table[17]; /* BL TODO: ugly, assuming size of array */

typedef struct _NUC_CALLBACKS   NUC_CALLBACKS;
struct _NUC_CALLBACKS {
        INT32 (OSIF_CALLTYPE *close_done)( CAN_OCB *ocb );
        INT32 (OSIF_CALLTYPE *tx_done)( CAN_OCB *ocb, INT32 result, UINT32 cm_count );
        INT32 (OSIF_CALLTYPE *tx_get)( CAN_OCB *ocb, CM *cm );
        INT32 (OSIF_CALLTYPE *tx_obj_get)( CAN_OCB *ocb, CM *cm );
        INT32 (OSIF_CALLTYPE *tx_obj_sched_get)( CAN_OCB *ocb, CMSCHED *sched );
        INT32 (OSIF_CALLTYPE *rx_done)( CAN_OCB *ocb, INT32 result, UINT32 cm_count );
        INT32 (OSIF_CALLTYPE *rx_put)( CAN_OCB *ocb, CM *cm );
        INT32 (OSIF_CALLTYPE *rx_obj_put)( CAN_OCB *ocb, CM *cm, UINT32 *next_id );
        INT32 (OSIF_CALLTYPE *ioctl_done)( CAN_OCB *ocb, VOID *waitContext, UINT32 cmd, INT32 result, UINT32 len_out );
/*      INT32 (*err_put)( CAN_NODE *can_node, INT32 err ); */
        INT32 (OSIF_CALLTYPE *rx_notify)( CAN_OCB *ocb );
};


/*
 * Any nucleus function follows our coding convention to return a result.
 * Many functions either return always success or they are used in most
 * of all cases with ignored return value. We suppress the lint message (534)
 * which indicates this to prevent 'polluting' the code with (void) casts.
 */  
/*lint -ecall(534, nuc_tx_abort, nuc_rx_abort, nuc_tx_messages)      */
/*lint -ecall(534, nuc_tx_done, nuc_tx_done_cm, nuc_tx_done_trigger) */ 
/*lint -ecall(534, nuc_rx_put, nuc_rx_put_cm, nuc_rx_put_trigger)    */ 
/*lint -ecall(534, nuc_ioctl_done, nuc_link_obj, nuc_unlink_obj)     */ 

/*
 * nucleus helper routines to oerate on linked lists (type definition in osif.h)
 */
extern INT32 OSIF_CALLTYPE nuc_link_obj(LNK *obj, LNK *root);
extern INT32 OSIF_CALLTYPE nuc_unlink_obj(LNK *obj );

/*
 * nucleus interface for OS module
 */
extern INT32 OSIF_CALLTYPE nuc_open( CAN_OCB      *ocb,
                                     CAN_NODE     *node,
                                     NUC_CALLBACKS *cm,
                                     UINT32       flags,
                                     UINT32       queue_size_tx,
                                     UINT32       queue_size_rx );
                                     
extern INT32 OSIF_CALLTYPE nuc_close( CAN_OCB *ocb );
extern INT32 OSIF_CALLTYPE nuc_tx_abort( CAN_OCB *ocb, INT32 status, UINT64 host_hnd );
extern INT32 OSIF_CALLTYPE nuc_rx_abort( CAN_OCB *ocb, INT32 status );
extern INT32 OSIF_CALLTYPE nuc_rx_purge( CAN_OCB *ocb );
extern INT32 OSIF_CALLTYPE nuc_rx_messages( CAN_OCB *ocb, UINT32 *count );
extern INT32 OSIF_CALLTYPE nuc_tx_messages( CAN_OCB *ocb, UINT32 *count );
extern INT32 OSIF_CALLTYPE nuc_deferred_tx_messages( CAN_OCB *ocb, UINT32 *count );


extern INT32 OSIF_CALLTYPE nuc_ioctl( CAN_OCB *can_ocb, VOID *waitContext, UINT32 cmd,
                                      VOID *buf_in, UINT32 len_in, VOID *buf_out, UINT32 *len_out );

extern INT32 OSIF_CALLTYPE nuc_rx( CAN_OCB *ocb,  UINT32 timeout, UINT32 *count );
extern INT32 OSIF_CALLTYPE nuc_rx_obj( CAN_OCB *ocb, UINT32 *count, UINT32 id );
extern INT32 OSIF_CALLTYPE nuc_tx( CAN_OCB *ocb,  UINT32 timeout, UINT32 *count );
extern INT32 OSIF_CALLTYPE nuc_tx_obj( CAN_OCB *ocb, UINT32 cmd, UINT32 *count );
extern INT32 OSIF_CALLTYPE nuc_tx_obj_schedule_stop( CAN_NODE *can_node );

extern INT32 OSIF_CALLTYPE nuc_node_attach( CAN_NODE *node, UINT32 queue_size_rx );
extern INT32 OSIF_CALLTYPE nuc_node_detach( CAN_NODE *node );

extern VOID  OSIF_CALLTYPE nuc_baudrate_disable( CAN_NODE *can_node );
extern VOID  OSIF_CALLTYPE nuc_baudrate_set_info( CAN_NODE *can_node, CAN_BITRATE *baud_info );

extern VOID OSIF_CALLTYPE nuc_baudrate_change_event( CAN_NODE *can_node, OSIF_TS *timestamp,
                                                     UINT32 bitRateType );

extern INT32 OSIF_CALLTYPE nuc_id_filter_mask( CAN_OCB *can_ocb, UINT32 amr, UINT32 acr, UINT32 idArea );
extern INT32 OSIF_CALLTYPE nuc_id_filter( CAN_OCB *ocb, UINT32 cmd, UINT32 id, UINT32 *count );

extern INT32 OSIF_CALLTYPE nuc_id_filter_restore(CAN_NODE *can_node);

extern CAN_OCB* OSIF_CALLTYPE nuc_ocb_get( CAN_NODE *can_node, CAN_OCB *ocb );

#if defined(OSIF_OS_LINUX)
extern VOID OSIF_CALLTYPE nuc_build_date_get(CHAR8 *info_buf, INT32 info_sz);
#endif

/*
 * nucleus interface for CIF module
 */

extern VOID  OSIF_CALLTYPE nuc_tx_get( CAN_NODE *node, CM **cm );
extern VOID  OSIF_CALLTYPE nuc_tx_ts_get( CAN_NODE *node, CM **cm );
extern INT32 OSIF_CALLTYPE nuc_tx_done( CAN_NODE *node, INT32 status, CM *cm );
extern INT32 OSIF_CALLTYPE nuc_tx_done_cm( CAN_NODE *node, INT32 status, CM *cm );
extern INT32 OSIF_CALLTYPE nuc_tx_done_trigger( CAN_NODE *node );

extern INT32 OSIF_CALLTYPE nuc_rx_put( CAN_NODE *node,  CM **cm );
extern INT32 OSIF_CALLTYPE nuc_rx_put_cm( CAN_NODE *node,  CM **cm );
extern INT32 OSIF_CALLTYPE nuc_rx_put_trigger( CAN_NODE *node );


/* extern INT32 OSIF_CALLTYPE nuc_err_put( CAN_NODE *node, INT32 error ); */
extern VOID  OSIF_CALLTYPE nuc_tx_abort_board( INT32 status, CM *cm );
extern INT32 OSIF_CALLTYPE nuc_ioctl_done( CAN_OCB *can_ocb, VOID *waitContext, UINT32  cmd, INT32 status, INT32 len_out );

extern INT32 OSIF_CALLTYPE nuc_busload_start( CAN_NODE *node );
extern VOID  OSIF_CALLTYPE nuc_busload_stop( CAN_NODE *node );

#ifdef BUS_STATISTICS
extern VOID  OSIF_CALLTYPE nuc_count_cm( CAN_NODE *node, CM *cm, INT32 type );
#else
# define nuc_count_cm(mnode, cm, type)
#endif

#ifdef NUC_CHECK_LINKS
int nuc_check_links(CAN_OCB *can_ocb);
#else
# define nuc_check_links(can_ocb)
#endif

#endif
