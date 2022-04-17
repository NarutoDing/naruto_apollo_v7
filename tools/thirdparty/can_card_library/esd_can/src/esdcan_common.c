/* -*- esdcan-c -*-
 * FILE NAME esdcan_common.c
 *           copyright 2002 - 2020 by esd electronic system design gmbh
 *
 * BRIEF MODULE DESCRIPTION
 *           This file contains the common entries
 *           for Linux/IRIX
 *           for the esd CAN driver
 *
 *
 * Author:   Matthias Fuchs
 *           matthias.fuchs@esd-electronics.com
 *
 */
/************************************************************************
 *
 *            Copyright (c) 2002 - 2020 by esd electronics gmbh
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
/*! \file esdcan_common.c
    \brief common driver entries

    This file contains the common entries for the es CAN driver.
*/

#if LINUX_VERSION_CODE < KERNEL_VERSION(3,19,0)
# define file_inode(x) (x->f_dentry->d_inode)
#elif LINUX_VERSION_CODE < KERNEL_VERSION(4,0,0)
# define file_inode(x) (x->f_path.dentry->d_inode)
#endif

/* block attempts to access cards with wrong firmware or hardware version */
#define CAN_ACTION_CHECK(ocb, result, action)                                                     \
       if ( (ocb->node->status) & (CANIO_STATUS_WRONG_HARDWARE | CANIO_STATUS_WRONG_FIRMWARE) ) { \
               if ( (ocb->node->status) & CANIO_STATUS_WRONG_HARDWARE ) {                         \
                       result = OSIF_INVALID_HARDWARE;                                            \
               } else {                                                                           \
                       result = OSIF_INVALID_FIRMWARE;                                            \
               }                                                                                  \
               action;                                                                            \
       }

INT32 OSIF_CALLTYPE esdcan_close_done( CAN_OCB *ocb )
{
        CAN_DBG((ESDCAN_ZONE_FU, "%s: enter (ocb = %p)\n", OSIF_FUNCTION, ocb));
#ifdef OSIF_USE_PREEMPT_RT_IMPLEMENTATION
        ocb->close_state |= CLOSE_STATE_CLOSE_DONE;
        wake_up(&ocb->wqCloseDelay);
#else
        up(&ocb->sema_close);
#endif
        CAN_DBG((ESDCAN_ZONE_FU, "%s: leave\n", OSIF_FUNCTION));
        return OSIF_SUCCESS;
}

INT32 OSIF_CALLTYPE esdcan_tx_done( CAN_OCB *ocb, INT32 result, UINT32 cm_count )
{
        CAN_DBG((ESDCAN_ZONE_FU, "%s: enter, result=%d, cm_count=%d\n", OSIF_FUNCTION, result, cm_count));
        ocb->tx.result = result;
#ifdef OSIF_USE_PREEMPT_RT_IMPLEMENTATION
        if (ocb->tx.state & TX_STATE_PENDING_SEND) {
                /* asynchronous TX done, nobody's waiting, but yet needed as canSend() left without resetting state */
                ocb->tx.cm_count = 0;
                ocb->tx.state = 0;
        } else if (ocb->tx.state & TX_STATE_SIGNAL_INTERRUPT) {
                ocb->tx.cm_count = cm_count;
                ocb->tx.state &= ~TX_STATE_SIGNAL_INTERRUPT;
                wake_up(&ocb->wqTx);
        } else if (ocb->tx.state & TX_STATE_PENDING_WRITE) {
                /* synchronous TX finished normally */
                ocb->tx.cm_count = cm_count;
                if (cm_count == 0) {
                        ocb->tx.state |= TX_STATE_ABORT;
                }
                wake_up_interruptible(&ocb->wqTx);
        } else {
                OSIF_PRINT(("%s: spurious tx_done? tx.state=0x%x\n", ESDCAN_DRIVER_NAME, (unsigned int)ocb->tx.state));
        }
#else
        if ( ocb->tx.state & TX_STATE_PENDING_SEND ) {
                ocb->tx.cm_count = 0;
                ocb->tx.state = 0;
        } else if (ocb->tx.state & TX_STATE_ABORTING) {
                ocb->tx.cm_count = cm_count;
                up( &ocb->sema_tx_abort );
        } else if (ocb->tx.state & TX_STATE_PENDING_WRITE) {
                ocb->tx.cm_count = cm_count;
                up( &ocb->sema_tx );
        } else {
                OSIF_PRINT(("%s: spurious tx_done? tx.state=0x%x\n", ESDCAN_DRIVER_NAME, (unsigned int)ocb->tx.state));
        }
#endif
        CAN_DBG((ESDCAN_ZONE_FU, "%s: leave\n", OSIF_FUNCTION));
        return OSIF_SUCCESS;
}

INT32 OSIF_CALLTYPE esdcan_tx_get( CAN_OCB *ocb, CM *cm ) {
        CAN_DBG((ESDCAN_ZONE_FU, "%s: enter (tx.cm_size=%d)\n", OSIF_FUNCTION, ocb->tx.cm_size));
        /* copy the first CAN_MSG/CM from user space to cm */
#ifndef BOARD_CAN_FD
        if (sizeof(CAN_MSG_X) == ocb->tx.cm_size) {
                /* we need to copy a CAN_MSG_X into a CAN_MSG_T */
                CAN_MSG_X tmp_x;
                if (copy_from_user(&tmp_x, ocb->tx.user_buf, sizeof(CAN_MSG_X))) {
                        CAN_DBG((ESDCAN_ZONE_FU, "%s: copy_from_user failed (ocb=%x)\n", OSIF_FUNCTION, ocb));
                        return OSIF_EFAULT;
                }
                memcpy(cm,&tmp_x,sizeof(CAN_MSG));
                cm->timestamp.tick = tmp_x.timestamp;
                goto esdcan_tx_get_done;
        }
#endif


        if (copy_from_user(cm, ocb->tx.user_buf, ocb->tx.cm_size)) {
                CAN_DBG((ESDCAN_ZONE_FU, "%s: copy_from_user failed (ocb=%x)\n", OSIF_FUNCTION, ocb));
                return OSIF_EFAULT;
        }
        if (sizeof(CAN_MSG) == ocb->tx.cm_size) {
                cm->timestamp.tick = 0LL;
#ifdef BOARD_CAN_FD
        } else if (sizeof(CAN_MSG_T) == ocb->tx.cm_size) {
                /* we have just copied a CAN_MSG_T into a CAN_MSG_X, fix the timestamp */
                cm->timestamp.tick = ((CAN_MSG_T *)cm)->timestamp;
#endif
        }
#ifndef BOARD_CAN_FD
esdcan_tx_get_done:
#endif
        ocb->tx.user_buf += ocb->tx.cm_size;
        CAN_DBG((ESDCAN_ZONE_FU, "%s: leave (id= %x len=%x)\n", OSIF_FUNCTION, cm->id, cm->len));
        return OSIF_SUCCESS;
}


INT32 OSIF_CALLTYPE esdcan_tx_obj_get( CAN_OCB *ocb, CM *cm )
{
        /* Copy the first CAN_MSG* from user space to a driver internal CM. */
        CAN_DBG((ESDCAN_ZONE_FU, "%s: enter (tx.cm_size=%d)\n", OSIF_FUNCTION, ocb->tx.cm_size));
#ifndef BOARD_CAN_FD
        if (sizeof(CAN_MSG_X) == ocb->tx.cm_size) {
                /* we need to copy a CAN_MSG_X into a CAN_MSG_T */
                CAN_MSG_X tmp_x;
                if (copy_from_user(&tmp_x, ocb->tx.user_buf, sizeof(CAN_MSG_X))) {
                        CAN_DBG((ESDCAN_ZONE_FU, "%s: copy_from_user(CAN_MSG_X) failed (ocb=%x)\n", OSIF_FUNCTION, ocb));
                        return OSIF_EFAULT;
                }
                memcpy(cm, &tmp_x, sizeof(CAN_MSG));
                cm->timestamp.tick = tmp_x.timestamp;
                goto esdcan_tx_obj_get_done;
        }
#endif

        if (copy_from_user(cm, ocb->tx.user_buf, ocb->tx.cm_size)) {
                CAN_DBG((ESDCAN_ZONE_FU, "%s: copy_from_user(%d) failed (ocb=%x)\n",
                         OSIF_FUNCTION, ocb->tx.cm_size, ocb));
                return OSIF_EFAULT;
        }
        if (sizeof(CAN_MSG) == ocb->tx.cm_size) {
                cm->timestamp.tick = 0ULL;
#ifdef BOARD_CAN_FD
        } else if (sizeof(CAN_MSG_T) == ocb->tx.cm_size) {
                /* we have just copied a CAN_MSG_T into a CAN_MSG_X, fix the timestamp */
                cm->timestamp.tick = ((CAN_MSG_T *)cm)->timestamp;
#endif
        }
#ifndef BOARD_CAN_FD
esdcan_tx_obj_get_done:
#endif
        ocb->tx.user_buf += ocb->tx.cm_size;
        CAN_DBG((ESDCAN_ZONE_FU, "%s: leave\n", OSIF_FUNCTION));
        return OSIF_SUCCESS;
}


INT32 OSIF_CALLTYPE esdcan_tx_obj_sched_get( CAN_OCB *ocb, CMSCHED *sched)
{
        CAN_DBG((ESDCAN_ZONE_FU, "%s: enter\n", OSIF_FUNCTION));
        /* copy the first 16 bytes (CAN_MSG) from user space to cm */
        if (copy_from_user(sched, ocb->tx.user_buf, sizeof(CMSCHED))) {
                return OSIF_EFAULT;
        }
        ocb->tx.user_buf += sizeof(CMSCHED);
        CAN_DBG((ESDCAN_ZONE_FU, "%s: leave\n", OSIF_FUNCTION));
        return OSIF_SUCCESS;
}


INT32 OSIF_CALLTYPE esdcan_rx_done( CAN_OCB *ocb, INT32 result, UINT32 cm_count )
{
        CAN_DBG((ESDCAN_ZONE_FU, "%s: enter, result=%d, cm_count=%d\n", OSIF_FUNCTION, result, cm_count));
        ocb->rx.result = result;
        ocb->rx.cm_count = cm_count;

#ifdef OSIF_USE_PREEMPT_RT_IMPLEMENTATION
        if (ocb->rx.state & RX_STATE_PENDING_TAKE) {
                ocb->rx.state = 0;  /* actually redundant */
        } else if (ocb->rx.state & RX_STATE_SIGNAL_INTERRUPT) {
                /* This was triggered by "interrupted by signal" branch in esdcan_read_common */
                ocb->rx.state &= ~RX_STATE_SIGNAL_INTERRUPT;
                wake_up(&ocb->wqRx);
        } else if (ocb->rx.state & RX_STATE_PENDING_READ) {
                /* Wake pending canRead() */
                if (ocb->rx.cm_count == 0) {
                        /* timeout occurred */
                        ocb->rx.state |= RX_STATE_ABORT; /* set only to wake esdcan_read_common, with no frames received */
                }
                wake_up_interruptible(&ocb->wqRx);
        } else {
                OSIF_PRINT(("%s: spurious rx_done? rx.state=0x%x\n", ESDCAN_DRIVER_NAME, (unsigned int)ocb->rx.state));
        }
#else
        if ( ocb->rx.state & RX_STATE_PENDING_TAKE ) {
                ocb->rx.state = 0;
        } else if (ocb->rx.state & RX_STATE_PENDING_READ) {
                /* Wake pending canRead() (normal branch, if RX works without interruption) */
                up( &ocb->sema_rx );
        } else {
                OSIF_PRINT(("%s: spurious rx_done? rx.state=0x%x\n", ESDCAN_DRIVER_NAME, (unsigned int)ocb->rx.state));
        }
#endif
        CAN_DBG((ESDCAN_ZONE_FU, "%s: leave\n", OSIF_FUNCTION));
        return OSIF_SUCCESS;
}

/*! \fn esdcan_rx_put( CAN_OCB *ocb, CM *cm );
 *  \brief copy received CM into ocb's rx buffer
 *  \param ocb open control block for this driver instance
 *  \cm pointer to a CM structure that contains the recieved CAN message.
 *  Only the first part containing a CAN_MSG is copied to the \a rx.cmbuf of the ocb structure.
 *  \return OSIF_SUCCESS
 */
INT32 OSIF_CALLTYPE esdcan_rx_put( CAN_OCB *ocb, CM *cm )
{
        CAN_DBG((ESDCAN_ZONE_FU, "%s: enter\n", OSIF_FUNCTION));
        /* Attention: we only copy the CAN_MSG_[TX] part (16 bytes) of the CM into the receive buffer */
        OSIF_MEMCPY(ocb->rx.cmbuf_in++, cm, sizeof(*ocb->rx.cmbuf_in));
        CAN_DBG((ESDCAN_ZONE_FU, "%s: leave\n", OSIF_FUNCTION));
        return OSIF_SUCCESS;
}

INT32 OSIF_CALLTYPE esdcan_rx_obj_put( CAN_OCB *ocb, CM *cm, UINT32 *next_id )
{
        CAN_DBG((ESDCAN_ZONE_FU, "%s: enter\n", OSIF_FUNCTION));
        OSIF_MEMCPY(ocb->rx.cmbuf_in++, cm, sizeof(*ocb->rx.cmbuf_in));
        ocb->rx.user_buf += ocb->rx.cm_size;
        if (next_id) {
                UINT32 id = CANIO_ID_INVALID;

                if (get_user(id, &((CAN_MSG*)ocb->rx.user_buf)->id)) {
                        return OSIF_EFAULT;
                }
                *next_id = id;
        }
        CAN_DBG((ESDCAN_ZONE_FU, "%s: leave\n", OSIF_FUNCTION));
        return OSIF_SUCCESS;
}

INT32 OSIF_CALLTYPE esdcan_rx_notify( CAN_OCB *ocb )
{
#if LINUX_VERSION_CODE >= KERNEL_VERSION(2,6,0)
        wake_up_interruptible(&ocb->node->wqRxNotify); /* wake select */
#endif
        return OSIF_SUCCESS;
}

typedef struct {
        INT32 status;
        wait_queue_head_t wq;
} IOCTL_WAIT_CONTEXT;

INT32 OSIF_CALLTYPE esdcan_ioctl_done( CAN_OCB *ocb, VOID *waitContext, UINT32 cmd, INT32 status, UINT32 len_out )
{
        IOCTL_WAIT_CONTEXT *wait = (IOCTL_WAIT_CONTEXT *)waitContext;

        CAN_DBG((OSIF_ZONE_IRQ, "%s: enter (waitContext = %p)\n", OSIF_FUNCTION, waitContext));
        wait->status = status;
        wake_up(&wait->wq);
        CAN_DBG((OSIF_ZONE_IRQ, "%s: leave\n", OSIF_FUNCTION));
        return OSIF_SUCCESS;
}


NUC_CALLBACKS esdcan_callbacks = {
        esdcan_close_done,
        esdcan_tx_done,
        esdcan_tx_get,
        esdcan_tx_obj_get,
        esdcan_tx_obj_sched_get,
        esdcan_rx_done,
        esdcan_rx_put,
        esdcan_rx_obj_put,
        esdcan_ioctl_done,
        esdcan_rx_notify
};


static INT32 id_filter( CAN_OCB *ocb, CAN_NODE *node, UINT32 cmd, UINT32 id_start, UINT32 *count )
{
        INT32  result = OSIF_SUCCESS;
        UINT32 count_to_do;
        UINT32 count_done;

        if (id_start & CANIO_ID_20B_BASE) {
                count_to_do = CANIO_IDS_20B;
                result = nuc_id_filter(ocb, cmd, CANIO_ID_20B_BASE, &count_to_do);
                if (result == OSIF_SUCCESS) {
                        nuc_id_filter_mask(ocb, id_start, ocb->filter20b.amr, CANIO_IDS_REGION_20B);
                        ocb->filter20b.acr = id_start;
                } else {
                        *count = 0;
                }
        } else {
                count_to_do = *count;
                count_done = 0;
                do {
                        result = nuc_id_filter(ocb, cmd, id_start + count_done, &count_to_do);
                        CAN_DBG((ESDCAN_ZONE, "%s: nuc_id_filter returns %x\n", OSIF_FUNCTION, result));
                        count_done += count_to_do;
                        count_to_do = *count - count_done;
                        if (OSIF_EAGAIN == result) {
                                OSIF_MUTEX_UNLOCK(&node->lock);
                                OSIF_SLEEP(1);
                                OSIF_MUTEX_LOCK(&node->lock);
                        }
                }
                while ( (result == OSIF_EAGAIN) && (count_done < *count) );
                *count = count_done;
        }
        return result;
}


/* only allocate ocb... */
static INT32 ocb_create( INT32 net_no, CAN_OCB **newocb )
{
        INT32    result = OSIF_SUCCESS;
        CAN_OCB *ocb;
        VOID    *vptr;

        CAN_DBG((ESDCAN_ZONE_FU, "%s:ocb_create: enter\n", OSIF_FUNCTION));
        /* check if node is available */
        if ( (net_no >= (MAX_CARDS * NODES_PER_CARD)) || (NULL == nodes[net_no]) ) {
                CAN_DBG((ESDCAN_ZONE_FU, "%s: node %d not available\n", OSIF_FUNCTION,net_no));
                return OSIF_NET_NOT_FOUND;
        }
#if defined (BOARD_USB)
        if (USB_OK != ((USB_MODULE*)((CAN_CARD*)nodes[net_no]->crd)->p_mod)->usb_status) {
                CAN_DBG((ESDCAN_ZONE_FU, "%s: node %d not available (usb not ready)\n", OSIF_FUNCTION, net_no));
                return OSIF_NET_NOT_FOUND;
        }
#endif
        /* allocate an OCB */
        CAN_DBG((ESDCAN_ZONE, "%s: allocate OCB\n", OSIF_FUNCTION));
        result = OSIF_MALLOC(sizeof(CAN_OCB),&vptr);
        if (result != OSIF_SUCCESS) {
                return result;
        }
        ocb = (CAN_OCB*)vptr;
        OSIF_MEMSET(ocb, 0, sizeof(CAN_OCB));
#ifdef OSIF_USE_PREEMPT_RT_IMPLEMENTATION
        init_waitqueue_head(&ocb->wqRx);
        init_waitqueue_head(&ocb->wqTx);
        init_waitqueue_head(&ocb->wqCloseDelay);
#else
        sema_init(&ocb->sema_rx, 0);
        sema_init(&ocb->sema_tx, 0);
        sema_init(&ocb->sema_tx_abort, 0);
        sema_init(&ocb->sema_close, 0);
#endif
        ocb->minor = net_no; /* TODO rename minor -> net_no */
        ocb->node = nodes[ocb->minor];
        *newocb = ocb;
        CAN_DBG((ESDCAN_ZONE_FU, "%s:ocb_create: leave, ocb=%p\n", OSIF_FUNCTION, ocb));
        return result;
}


/* now do the main action... */
static INT32 ocb_create2( CAN_OCB *ocb, INT32 net_no, CAN_INIT_ARG *can_init )
{
        INT32   result = OSIF_SUCCESS;
        UINT32  queue_size_rx, queue_size_tx;
        UINT32  cmd;

        CAN_DBG((ESDCAN_ZONE_FU, "%s:ocb_create: enter\n", OSIF_FUNCTION));
        /* check if node is available */
        if ( (net_no >= (MAX_CARDS * NODES_PER_CARD)) || (NULL == nodes[net_no]) ) {
                CAN_DBG((ESDCAN_ZONE_FU, "%s: node %d not available\n", OSIF_FUNCTION, net_no));
                return OSIF_NET_NOT_FOUND;
        }
#if defined (BOARD_USB)
        if (USB_OK != ((USB_MODULE*)((CAN_CARD*)nodes[net_no]->crd)->p_mod)->usb_status) {
                CAN_DBG((ESDCAN_ZONE_FU, "%s: node %d not available (usb not ready)\n", OSIF_FUNCTION,net_no));
                return OSIF_NET_NOT_FOUND;
        }
#endif
        queue_size_rx = can_init->queue_size_rx;
        queue_size_tx = can_init->queue_size_tx;
        /* patch queue sizes to at least 1 / check on -1 for CANopen */
        if ( (queue_size_tx == 0) || (queue_size_tx == ~0x0) ) {
                queue_size_tx = 1;
        }
        if ( (queue_size_rx == 0) || (queue_size_rx == ~0x0) ) {
                queue_size_rx = 1;
        }
        /* range check for queue sizes */
        if ( (queue_size_tx > CANIO_MAX_TX_QUEUESIZE) ||
             (queue_size_rx > CANIO_MAX_RX_QUEUESIZE) ) {
                return OSIF_INVALID_PARAMETER;
        }
        ocb->mode = can_init->mode;
        /* TODO: use open_count !!!! */
        if (can_init->mode & FEATURE_LOM) {  /* If LOM is set this way, it can never be reset except by unloading the driver */
                if (ocb->node->features & FEATURE_LOM) {
                        ocb->node->mode |= FEATURE_LOM;
                } else {
                        CAN_DBG((ESDCAN_ZONE, "%s: LOM not support by this node\n", OSIF_FUNCTION));
                        OSIF_FREE(ocb);
                        return OSIF_INVALID_PARAMETER;
                }
        }
        /* Calculate command for ID-filter */
	cmd = 0;
	if (!(ocb->mode & CANIO_MODE_OBJECT)) {
                cmd |= (ocb->mode & CANIO_MODE_NO_RTR) ? 0 : FILTER_RTR;
                cmd |= (ocb->mode & CANIO_MODE_NO_DATA) ? 0 : FILTER_DATA;
#ifdef BOARD_CAN_FD
                if(ocb->mode & CANIO_MODE_FD) {
                        cmd |= (ocb->mode & CANIO_MODE_NO_DATA) ? 0 : FILTER_DATA_FD;
                }
#endif
        }
        if (ocb->node->features & FEATURE_FULL_CAN) {
                cmd &= ~FILTER_RTR;
        }
        /*
         * BL: RTR needs to be enabled on full CAN-controller, when the
         * handle is opened with the NO_DATA-flag (compatibility with candev-driver)
         */
        if ( (ocb->node->features & FEATURE_FULL_CAN) &&
             (ocb->mode & CANIO_MODE_NO_DATA) &&
             !(ocb->mode & CANIO_MODE_AUTO_ANSWER) ) {
                cmd |= FILTER_RTR;
        }
        ocb->filter_cmd = cmd;
        ocb->filter20b.amr = 0xFFFFFFFF;
        /* rx buffer */
        CAN_DBG((ESDCAN_ZONE, "%s: requesting rx buffer\n", OSIF_FUNCTION));
        result = OSIF_MALLOC((UINT32)(sizeof(*ocb->rx.cmbuf) * queue_size_rx), &ocb->rx.cmbuf);
        if (result != OSIF_SUCCESS) {
                OSIF_FREE(ocb);
                return result;
        }
        CAN_DBG((ESDCAN_ZONE, "%s: calling nuc_open@%p\n", OSIF_FUNCTION, nuc_open));
        OSIF_MUTEX_LOCK(&ocb->node->lock);
        result = nuc_open(ocb,
                          ocb->node,
                          &esdcan_callbacks,
                          ocb->mode,
                          queue_size_tx,
                          queue_size_rx);
        OSIF_MUTEX_UNLOCK(&ocb->node->lock);
        if (result != OSIF_SUCCESS) {
                OSIF_FREE(ocb->rx.cmbuf);
                OSIF_FREE(ocb);
                return result;
        }
        CAN_DBG((ESDCAN_ZONE_FU, "%s:ocb_create: leave, ocb=%p\n", OSIF_FUNCTION, ocb));
        return result;
}


INT32 ocb_destroy( CAN_OCB *ocb )
{
        INT32 result;

        CAN_DBG((ESDCAN_ZONE_FU, "%s:ocb_destroy: enter\n", OSIF_FUNCTION));
        ocb->close_state |= CLOSE_STATE_HANDLE_CLOSED;
#ifdef OSIF_USE_PREEMPT_RT_IMPLEMENTATION
        /*
         * We need to wait for esdcan_close_done to be called by nucleus.
         * Additionally while closing the ocb, the nucleus might have aborted
         * a RX and/or a TX job. Since we have no control, when these jobs
         * will exit the driver, we mark this ocb as CLOSING, until the jobs
         * have left the driver.
         * Freeing of ocb ressources is done in final close().
         */
        if (ocb->rx.state) {
                ocb->rx.state |= RX_STATE_CLOSING;
        }
        if (ocb->tx.state) {
                ocb->tx.state |= TX_STATE_CLOSING;
        }
        CAN_DBG((ESDCAN_ZONE, "%s: calling nuc_close\n", OSIF_FUNCTION));
        result = nuc_close(ocb);
        CAN_DBG((ESDCAN_ZONE, "%s: nuc_close returned %d\n", OSIF_FUNCTION, result));
        CAN_DBG((ESDCAN_ZONE, "%s: waiting on wqCloseDelay...\n", OSIF_FUNCTION));
        OSIF_MUTEX_UNLOCK(&ocb->node->lock);
#if 1
        wait_event(ocb->wqCloseDelay, (ocb->close_state & CLOSE_STATE_CLOSE_DONE) &&
                                      (!(ocb->tx.state & TX_STATE_CLOSING)) &&
                                      (!(ocb->rx.state & RX_STATE_CLOSING)));
#else
        /* use this code to debug "hanging" close conditions */
        for(;;) {
            if (wait_event_timeout(ocb->wqCloseDelay, (ocb->close_state & CLOSE_STATE_CLOSE_DONE) &&
                                      (!(ocb->tx.state & TX_STATE_CLOSING)) &&
                                      (!(ocb->rx.state & RX_STATE_CLOSING)),1000)==0) {
                UINT32 txcnt;
                static UINT32 errcnt;
                nuc_tx_messages(ocb,&txcnt);
                OSIF_PRINT(("%s: wait_event_timeout!!! close_state=0x%x rx.state=0x%x tx.state=0x%x txcnt=%u\n",
                    OSIF_FUNCTION,
                    (unsigned int)ocb->close_state,
                    (unsigned int)ocb->rx.state,
                    (unsigned int)ocb->tx.state,
                    (unsigned int)txcnt
                ));
                errcnt++;
                if ((errcnt>=10)&&(txcnt==0)) {
                    errcnt=0;
                    OSIF_PRINT(("%s: dirty: exiting wait_event_timeout loop!!!\n",OSIF_FUNCTION));
                    break;
                }
            } else {
                break;
            }
        }
#endif
        OSIF_MUTEX_LOCK(&ocb->node->lock);
        CAN_DBG((ESDCAN_ZONE, "%s: close conditions fulfilled, close continues\n", OSIF_FUNCTION));
#else
        CAN_DBG((ESDCAN_ZONE, "%s: calling nuc_close\n", OSIF_FUNCTION));
        result = nuc_close(ocb);
        CAN_DBG((ESDCAN_ZONE, "%s: nuc_close returned %d\n", OSIF_FUNCTION,result));
        /* waiting for aborts to finish */
        CAN_DBG((ESDCAN_ZONE, "%s: waiting for sema_close...\n", OSIF_FUNCTION));
        OSIF_MUTEX_UNLOCK(&ocb->node->lock);
        down(&ocb->sema_close);
        OSIF_MUTEX_LOCK(&ocb->node->lock);
        CAN_DBG((ESDCAN_ZONE, "%s: sema_close signaled\n", OSIF_FUNCTION));
        /* While closing the ocb, nucleus might have aborted a RX job
         * since we have no control, when this reader will exit the driver,
         * we mark this OCB as ABORTING */
        if ( ocb->rx.state ) {
                /* do not destroy when there is a reader */
                ocb->rx.state |= RX_STATE_CLOSING;
        }
#endif
        CAN_DBG((ESDCAN_ZONE_FU, "%s:ocb_destroy: leave\n", OSIF_FUNCTION));
        return result;
}

#ifdef OSIF_USE_PREEMPT_RT_IMPLEMENTATION
/* returns error codes negative and received messages positive */
int esdcan_read_common( CAN_OCB *ocb, void *buf, UINT32 cm_count, UINT32 objSize )
{
        INT32 result;
        INT32 ret;
        INT32 flagInterruptedBySignal = 0;
        INT32 flagOcbClosing = 0;

        CAN_DBG((ESDCAN_ZONE_FU, "%s: enter, ocb=%p, cm_count=%d\n", OSIF_FUNCTION, ocb, cm_count));
        CAN_ACTION_CHECK(ocb, result, return -result);
        /* return if any read or take is pending */
        if (ocb->rx.state) {
                return -OSIF_PENDING_READ;
        }
        /* no other process is allowed to enter read from now on */
        ocb->rx.state = RX_STATE_PENDING_READ;
        ocb->rx.result = 0;
        /* reset rx buffer pointer */
        ocb->rx.user_buf = buf;
        CAN_DBG((ESDCAN_ZONE, "%s: rx_user_buf=%p\n", OSIF_FUNCTION, buf));
        ocb->rx.cm_size = objSize;
        ocb->rx.cmbuf_in = ocb->rx.cmbuf;
        ocb->rx.cm_count = 0;
        /* trigger rx for cm_count cm */
        ret = nuc_rx(ocb, ocb->rx.tout, &cm_count);
        if (ret != OSIF_SUCCESS) {
                ocb->rx.state = 0;
                return -ret;
        }
        /* wait for rx finished (interruptible) */
        OSIF_MUTEX_UNLOCK(&ocb->node->lock);
        if ( wait_event_interruptible( ocb->wqRx,
                                       ( (ocb->rx.cm_count > 0) ||                  /* Successfull end of canRead() */
                                         (ocb->rx.state & RX_STATE_ABORT) ||        /* Set by esdcan_rx_done, e.g. on timeout */
                                         (ocb->rx.state & RX_STATE_CLOSING) ) ) ) {
                /* Interrupted by signal, we might abort here */
                OSIF_MUTEX_LOCK(&ocb->node->lock);
                if ( (ocb->rx.cm_count == 0) &&
                     (!(ocb->rx.state & RX_STATE_ABORT)) &&
                     (!(ocb->rx.state & RX_STATE_CLOSING)) ) {
                        flagInterruptedBySignal = 1;
                        ocb->rx.state |= RX_STATE_SIGNAL_INTERRUPT;  /* Set only in this branch, nuc_rx_abort guarantees one more call of esdcan_rx_done */
                        nuc_rx_abort(ocb, OSIF_OPERATION_ABORTED); /* call of esdcan_rx_done() is guaranteed */
                        OSIF_MUTEX_UNLOCK(&ocb->node->lock);
                        wait_event(ocb->wqRx, (!(ocb->rx.state & RX_STATE_SIGNAL_INTERRUPT)));
                } else {
                        OSIF_MUTEX_UNLOCK(&ocb->node->lock);
                }
        }
        OSIF_MUTEX_LOCK(&ocb->node->lock);
        ret = ocb->rx.cm_count;
        ocb->rx.cm_count = 0;
        if (ocb->rx.state & RX_STATE_CLOSING) {
                flagOcbClosing = 1;
        }
        ocb->rx.state = 0;
        if (0 == ret) {
                /* return if rx failed */
                CAN_DBG((ESDCAN_ZONE, "%s: rx failed (%d)\n", OSIF_FUNCTION, -(INT32)ocb->rx.result));
                if (flagOcbClosing) {
                        /* Delayed close needs to be woken */
                        /* The ocb is in process of closing and is (amongst others) waiting
                         * for this job to leave the driver */
                        wake_up(&ocb->wqCloseDelay);
                        CAN_DBG((ESDCAN_ZONE, "%s: RX delayed cleanup\n", OSIF_FUNCTION));
                        return -EINTR;
                }
                if (flagInterruptedBySignal) {
                        /* Interrupted by signal, system will reenter this read */
                        return -ERESTARTSYS;
                } else {
                        /* No messages, return rx.result stored by "interruptor",
                         * in most cases RX timeout  */
                        return -(INT32)ocb->rx.result;
                }
        }
        if (flagOcbClosing) {
                wake_up(&ocb->wqCloseDelay);
        }
        /* If we are here, canRead finishes successfully with RX messages */
        {
                UINT8     *dest = buf;
#ifdef BOARD_CAN_FD
                CAN_MSG_X *src;
#else
                CAN_MSG_T *src;
#endif
                INT32      i;
                src = ocb->rx.cmbuf;
                for (i = 0; i < ret; i++) {
#ifdef BOARD_CAN_FD
                        /* FD-enabled driver, src is CAN_MSG_X */
                        if ((ocb->rx.cm_size==sizeof(CAN_MSG))||(ocb->rx.cm_size==sizeof(CAN_MSG_X))) {
                                if (copy_to_user(dest, src, ocb->rx.cm_size)) {
                                        return -OSIF_EFAULT;
                                }
                        } else {
                                /* Need to copy CAN_MSG_X data from cmbuf to user-supplied CAN_MSG_T buffer */
                                /* Make a local copy, to call copy_to_user() only ONCE */
                                CAN_MSG_T tmp_t;

                                memcpy(&tmp_t,src,sizeof(CAN_MSG));
                                tmp_t.timestamp = src->timestamp;
                                if (copy_to_user(dest, &tmp_t, sizeof(CAN_MSG_T))) {
                                        return -OSIF_EFAULT;
                                }
                        }
#else
                        /* non-FD driver, src is CAN_MSG_T */
                        if (ocb->rx.cm_size==sizeof(CAN_MSG_X)) {
                                CAN_MSG_X tmp_x;

                                memcpy(&tmp_x,src,sizeof(CAN_MSG));
                                memset(&tmp_x.buf.c[8],0,64-8); /* don't give away kernel stack data to user */
                                tmp_x.timestamp=src->timestamp;
                                if (copy_to_user(dest, &tmp_x, sizeof(CAN_MSG_X))) {
                                        return -OSIF_EFAULT;
                                }
                        } else {
                                if (copy_to_user(dest, src, ocb->rx.cm_size)) {
                                        return -OSIF_EFAULT;
                                }
                        }
#endif
                        CAN_DBG((ESDCAN_ZONE, "%s: ts=%lx.%lx\n", OSIF_FUNCTION,
                                 ((OSIF_TS)src->timestamp).h.HighPart, ((OSIF_TS)src->timestamp).h.LowPart));
                        src++;
                        dest += ocb->rx.cm_size;
                }
        }
        CAN_DBG((ESDCAN_ZONE_FU, "%s:IOCTL_read: leave, copied %d CM(SG)s\n", OSIF_FUNCTION, ret));
        return (int)ret; /* return count and not count*size */
}
#else
/* returns error codes negative and received messages positive */
int esdcan_read_common( CAN_OCB *ocb, void *buf, UINT32 cm_count, UINT32 objSize )
{
        INT32 result;
        INT32 ret;
        INT32 flagAbort = 0;

        CAN_DBG((ESDCAN_ZONE_FU, "%s: enter, ocb=%p, cm_count=%d\n", OSIF_FUNCTION, ocb, cm_count));
        CAN_ACTION_CHECK(ocb, result, return -result);
        /* return if any read or take is pending */
        if (ocb->rx.state) {
                return -OSIF_PENDING_READ;
        }
        /* no other process is allowed to enter read from now on */
        ocb->rx.state = RX_STATE_PENDING_READ;
        ocb->rx.result = 0;
        /* reset rx buffer pointer */
        ocb->rx.user_buf = buf;
        CAN_DBG((ESDCAN_ZONE, "%s: rx_user_buf=%p\n", OSIF_FUNCTION, buf));
        ocb->rx.cm_size = objSize;
        ocb->rx.cmbuf_in = ocb->rx.cmbuf;
        ocb->rx.cm_count = 0;
        sema_init(&ocb->sema_rx, 0);
        /* trigger rx for cm_count cm */
        ret = nuc_rx(ocb, ocb->rx.tout, &cm_count);
        if (ret != OSIF_SUCCESS) {
                ocb->rx.state = 0;
                return -ret;
        }
        /* wait for rx finished (interruptible) */
        OSIF_MUTEX_UNLOCK(&ocb->node->lock);
        ret = down_interruptible(&ocb->sema_rx);
        OSIF_MUTEX_LOCK(&ocb->node->lock);
        if (ret != OSIF_SUCCESS) {
                if (ocb->rx.state & RX_STATE_CLOSING) {
                        /* The ocb got closed already, freeing of OCB ressources
                           is done in final close() */
                        CAN_DBG((ESDCAN_ZONE, "%s: RX delayed cleanup\n", OSIF_FUNCTION));
                        return -EINTR; /* system error code, never reaches user, thus no OSIF_ */
                } else if (ocb->rx.cm_count == 0) {
                        /* Interrupted by signal, we'll abort here */
                        ocb->rx.state |= RX_STATE_ABORTING;
                        flagAbort = 1;
                        nuc_rx_abort(ocb, OSIF_OPERATION_ABORTED); /* call of esdcan_rx_done() is guaranteed */
                        OSIF_MUTEX_UNLOCK(&ocb->node->lock);
                        down(&ocb->sema_rx);
                        OSIF_MUTEX_LOCK(&ocb->node->lock);
                }
        }
        /* return when rx failed */
        ret = ocb->rx.cm_count;
        if (ret == 0) {
                CAN_DBG((ESDCAN_ZONE, "%s: rx failed (%d)\n", OSIF_FUNCTION, -(INT32)ocb->rx.result));
                ocb->rx.state = 0;
                if (flagAbort) {
                        return -ERESTARTSYS;
                } else {
                        return -(INT32)ocb->rx.result;
                }
        }
        {      /* read with(out) timestamps */
                UINT8     *dest = buf;
#ifdef BOARD_CAN_FD
                CAN_MSG_X *src;
#else
                CAN_MSG_T *src;
#endif
                INT32      i;
                src = ocb->rx.cmbuf;
                for (i = 0; i < ret; i++) {
#ifdef BOARD_CAN_FD
                        /* FD-enabled driver, src is CAN_MSG_X */
                        if ((ocb->rx.cm_size==sizeof(CAN_MSG))||(ocb->rx.cm_size==sizeof(CAN_MSG_X))) {
                                if (copy_to_user(dest, src, ocb->rx.cm_size)) {
                                        return -OSIF_EFAULT;
                                }
                        } else {
                                /* Need to copy CAN_MSG_X data from cmbuf to user-supplied CAN_MSG_T buffer */
                                /* Make a local copy, to call copy_to_user() only ONCE */
                                CAN_MSG_T tmp_t;

                                memcpy(&tmp_t,src,sizeof(CAN_MSG));
                                tmp_t.timestamp=src->timestamp;
                                if (copy_to_user(dest, &tmp_t, sizeof(CAN_MSG_T))) {
                                        return -OSIF_EFAULT;
                                }
                        }
#else
                        /* non-FD driver, src is CAN_MSG_T */
                        if (ocb->rx.cm_size==sizeof(CAN_MSG_X)) {
                                CAN_MSG_X tmp_x;

                                memcpy(&tmp_x,src,sizeof(CAN_MSG));
                                memset(&tmp_x.buf.c[8],0,64-8); /* don't give away kernel stack data to user */
                                tmp_x.timestamp=src->timestamp;
                                if (copy_to_user(dest, &tmp_x, sizeof(CAN_MSG_X))) {
                                        return -OSIF_EFAULT;
                                }
                        } else {
                                if (copy_to_user(dest, src, ocb->rx.cm_size)) {
                                        return -OSIF_EFAULT;
                                }
                        }
#endif
                        CAN_DBG((ESDCAN_ZONE, "%s: ts=%lx.%lx\n", OSIF_FUNCTION,
                                 ((OSIF_TS)src->timestamp).h.HighPart, ((OSIF_TS)src->timestamp).h.LowPart));
                        src++;
                        dest += ocb->rx.cm_size;
                }
                ocb->rx.cm_count = 0;
        }
        ocb->rx.state = 0;
        CAN_DBG((ESDCAN_ZONE_FU, "%s:IOCTL_read: leave, copied %d CM(SG)s\n", OSIF_FUNCTION, ocb->rx.cm_count ));
        return (int)ret; /* return count and not count*size */
}
#endif

#ifdef OSIF_USE_PREEMPT_RT_IMPLEMENTATION
/* Returns error codes negative and transmitted messages positive */
int esdcan_write_common( CAN_OCB *ocb, void *buf, UINT32 cm_count, UINT32 objSize )
{
        INT32   result;
        INT32   old_job_tx_pending = 0;
        INT32   tx_len;
        INT32   flagInterruptedBySignal = 0;
        INT32   flagOcbClosing = 0;
        INT32   old_state;

        CAN_DBG((ESDCAN_ZONE_FU, "%s: enter cm_count=%d\n", OSIF_FUNCTION, cm_count));
        if (0 == cm_count) {
                CAN_DBG((ESDCAN_ZONE_FU, "%s: leave (OSIF_INVALID_PARAMETER)\n", OSIF_FUNCTION));
                return -OSIF_INVALID_PARAMETER; /* BL TODO: change error-code??? */
        }
        /* block attempts to access cards with wrong firmware */
        CAN_ACTION_CHECK(ocb, result, return -result);
        if (ocb->tx.state & (TX_STATE_PENDING_WRITE | TX_STATE_ABORT)) {
                CAN_DBG((ESDCAN_ZONE_FU, "%s: leave (PENDING_WRITE)\n", OSIF_FUNCTION));
                return -OSIF_PENDING_WRITE;
        } else if (ocb->tx.state & TX_STATE_PENDING_SEND) {
                UINT32 dtx;

                if (nuc_deferred_tx_messages(ocb, &dtx) != OSIF_SUCCESS) {
                        /* nuc_deferred_tx_messages should never fail, but anyway, you may try again */
                        return -ERESTARTSYS; /* system error code, never reaches user, thus no OSIF_ */
                }
                if (dtx) {
                        return -OSIF_PENDING_WRITE;
                }
                if (nuc_tx_messages(ocb, (UINT32*)&old_job_tx_pending) != OSIF_SUCCESS) {
                        /* nuc_tx_messages should never fail, but anyway, you may try again */
                        return -ERESTARTSYS; /* system error code, never reaches user, thus no OSIF_ */
                }
        }
        ocb->tx.user_buf = buf;
        ocb->tx.cm_size = objSize;

        /* need to save old state in case it is TX_STATE_PENDING_SEND, because if nuc_tx fails, we must not
           clear the old TX_STATE_PENDING_SEND but leave it as is. */
        old_state = ocb->tx.state;
        /* need to set tx.state before nuc_tx call because nuc_tx might call esdcan_tx_done synchronously */
        ocb->tx.state = TX_STATE_PENDING_WRITE;

        /* trigger tx job, copy_from_user is done in our context from nuc_tx() */
        result = nuc_tx(ocb, ocb->tx.tout, &cm_count);
        if ( (result != OSIF_SUCCESS) && (cm_count == 0) ) {
                ocb->tx.state = old_state; /* restore old tx.state */
                CAN_DBG((ESDCAN_ZONE_FU, "%s: leave (nuc_tx, err = %d, cm_count = %d)\n",
                         OSIF_FUNCTION, result, cm_count));
                return -result;
        }
        /* wait until job is finished or error occured */
        OSIF_MUTEX_UNLOCK(&ocb->node->lock);
        if (wait_event_interruptible(ocb->wqTx,
                                     ( (0 < (ocb->tx.cm_count - old_job_tx_pending)) ||
                                       (ocb->tx.state & TX_STATE_ABORT) ||
                                       (ocb->tx.state & TX_STATE_CLOSING) ) ) ) {
                OSIF_MUTEX_LOCK(&ocb->node->lock);
                if ( (0 == (ocb->tx.cm_count - old_job_tx_pending)) &&
                     (!(ocb->tx.state & TX_STATE_ABORT)) &&
                     (!(ocb->tx.state & TX_STATE_CLOSING)) ) {
                        flagInterruptedBySignal = 1;
                        ocb->tx.state |= TX_STATE_SIGNAL_INTERRUPT;
                        nuc_tx_abort(ocb, OSIF_OPERATION_ABORTED, 0);
                        OSIF_MUTEX_UNLOCK(&ocb->node->lock);
                        wait_event(ocb->wqTx, (!(ocb->tx.state & TX_STATE_SIGNAL_INTERRUPT))); /* wait for esdcan_tx_done */
                } else {
                        OSIF_MUTEX_UNLOCK(&ocb->node->lock);
                }
        }
        OSIF_MUTEX_LOCK(&ocb->node->lock);
        tx_len = ocb->tx.cm_count - old_job_tx_pending;
        ocb->tx.cm_count = 0;
        if (ocb->tx.state & TX_STATE_CLOSING) {
                flagOcbClosing = 1;
        }
        ocb->tx.state = 0;
        /* check errors */
        if (0 >= tx_len) {
                if (flagOcbClosing) {
                        /* Delayed close needs to be woken */
                        /* The ocb is in process of closing and is (amongst others) waiting
                         * for this job to leave the driver */
                        wake_up(&ocb->wqCloseDelay);
                        CAN_DBG((ESDCAN_ZONE, "%s: TX delayed cleanup\n", OSIF_FUNCTION));
                        return -EINTR;
                }
                if (flagInterruptedBySignal) {
                        CAN_DBG((ESDCAN_ZONE_FU, "%s: leave (ERESTARTSYS, tx.cm_count = %d, old_job_tx_pending = %d)\n",
                                 OSIF_FUNCTION, (int)ocb->tx.cm_count, (int)old_job_tx_pending));
                        return -ERESTARTSYS;
                } else {
                        CAN_DBG((ESDCAN_ZONE_FU, "%s: leave (result: %ld, tx.cm_count = %d, old_job_tx_pending = %d)\n",
                                 OSIF_FUNCTION, -(ocb->tx.result), (int)ocb->tx.cm_count, (int)old_job_tx_pending));
                        return -(ocb->tx.result);
                }
        }
        if (flagOcbClosing) {
                wake_up(&ocb->wqCloseDelay);
        }
        CAN_DBG((ESDCAN_ZONE, "%s: copied %d bytes\n",
                 OSIF_FUNCTION, ocb->tx.cm_count * sizeof(CAN_MSG)));
        CAN_DBG((ESDCAN_ZONE_FU, "%s: leave (success, tx.cm_count = %d, tx_len = %d)\n",
                 OSIF_FUNCTION, (int)ocb->tx.cm_count, (int)tx_len));
        return (int)tx_len; /* return count and not count*size */
}
#else
/* Returns error codes negative and transmitted messages positive */
int esdcan_write_common( CAN_OCB *ocb, void *buf, UINT32 cm_count, UINT32 objSize )
{
        INT32   result, ret;
        INT32   old_job_tx_pending = 0;
        INT32   tx_len;
        INT32   flagAbort = 0;
        INT32   old_state;

        CAN_DBG((ESDCAN_ZONE_FU, "%s: enter cm_count=%d\n", OSIF_FUNCTION, cm_count));

        if ( cm_count == 0 ) {
                CAN_DBG((ESDCAN_ZONE_FU, "%s: leave (OSIF_INVALID_PARAMETER)\n", OSIF_FUNCTION));
                return -OSIF_INVALID_PARAMETER; /* AB TODO: change error-code??? */
        }

        /* block attempts to access cards with wrong firmware */
        CAN_ACTION_CHECK(ocb, result, return -result);

        if ( ocb->tx.state & (TX_STATE_PENDING_WRITE | TX_STATE_ABORTING) ) {
                CAN_DBG((ESDCAN_ZONE_FU, "%s: leave (PENDING_WRITE)\n", OSIF_FUNCTION));
                return -OSIF_PENDING_WRITE;
        } else if ( ocb->tx.state & TX_STATE_PENDING_SEND ) {
                UINT32 dtx;
                if (nuc_deferred_tx_messages(ocb, &dtx) != OSIF_SUCCESS) {
                        /* nuc_deferred_tx_messages should never fail, but anyway, you may try again */
                        return -ERESTARTSYS; /* system error code, never reaches user, thus no OSIF_ */
                }
                if (dtx) {
                        return -OSIF_PENDING_WRITE;
                }
                if (nuc_tx_messages(ocb, (UINT32*)&old_job_tx_pending) != OSIF_SUCCESS) {
                        /* nuc_tx_messages should never fail, but anyway, you may try again */
                        return -ERESTARTSYS; /* system error code, never reaches user, thus no OSIF_ */
                }
        }
        ocb->tx.user_buf = buf;
        ocb->tx.cm_size = objSize;
        sema_init(&ocb->sema_tx, 0);

        /* need to save old state in case it is TX_STATE_PENDING_SEND, because if nuc_tx fails, we must not
           clear the old TX_STATE_PENDING_SEND but leave it as is. */
        old_state = ocb->tx.state;
        /* need to set tx.state before nuc_tx call because nuc_tx might call esdcan_tx_done synchronously */
        ocb->tx.state = TX_STATE_PENDING_WRITE;

        /* trigger tx job, copy_from_user is done in our context from nuc_tx() */
        result = nuc_tx(ocb, ocb->tx.tout, &cm_count);
        if ( (result != OSIF_SUCCESS) && (cm_count == 0) ) {
                ocb->tx.state = old_state; /* restore old tx.state */
                CAN_DBG((ESDCAN_ZONE_FU, "%s: leave (nuc_tx, err = %d, cm_count = %d)\n",
                         OSIF_FUNCTION, result, cm_count));
                return -result;
        }

        /* wait until job is finished or error occured */
        OSIF_MUTEX_UNLOCK(&ocb->node->lock);
        ret = down_interruptible(&ocb->sema_tx);
        OSIF_MUTEX_LOCK(&ocb->node->lock);
        /* Check, if the job was finished between wakeup and mutex lock */
        tx_len = ocb->tx.cm_count;
        tx_len -= old_job_tx_pending;
        if ( (ret != OSIF_SUCCESS) &&
             (tx_len <= 0) ) {
                ocb->tx.state |= TX_STATE_ABORTING;
                flagAbort = 1;
                nuc_tx_abort(ocb, OSIF_OPERATION_ABORTED, 0);
                OSIF_MUTEX_UNLOCK(&ocb->node->lock);
                down(&ocb->sema_tx_abort); /* wait for esdcan_tx_done */
                OSIF_MUTEX_LOCK(&ocb->node->lock);
        }
        tx_len = ocb->tx.cm_count;
        tx_len -= old_job_tx_pending;
        ocb->tx.cm_count = 0;
        ocb->tx.state = 0;
        /* check errors */
        if (tx_len <= 0) {
                if (flagAbort) {
                        CAN_DBG((ESDCAN_ZONE_FU, "%s: leave (ERESTARTSYS, tx.cm_count = %d, old_job_tx_pending = %d)\n",
                                 OSIF_FUNCTION, (int)ocb->tx.cm_count, (int)old_job_tx_pending));
                        return -ERESTARTSYS;
                } else {
                        CAN_DBG((ESDCAN_ZONE_FU, "%s: leave (result: %ld, tx.cm_count = %d, old_job_tx_pending = %d)\n",
                                 OSIF_FUNCTION, -(ocb->tx.result), (int)ocb->tx.cm_count, (int)old_job_tx_pending));
                        return -(ocb->tx.result);
                }
        }
        CAN_DBG((ESDCAN_ZONE, "%s: copied %d bytes\n",
                 OSIF_FUNCTION, ocb->tx.cm_count * sizeof(CAN_MSG)));
        CAN_DBG((ESDCAN_ZONE_FU, "%s: leave (success, tx.cm_count = %d, tx_len = %d)\n",
                 OSIF_FUNCTION, (int)ocb->tx.cm_count, (int)tx_len));
        return (int)tx_len; /* return count and not count*size */
}
#endif

#ifdef OSIF_OS_LINUX /* AB: This won't work on IRIX */
static int my_nuc_ioctl( CAN_OCB *ocb, UINT32 cmd,
                         VOID *buf_in, UINT32 len_in, VOID *buf_out, UINT32 *len_out )
{
        INT32              status;
        IOCTL_WAIT_CONTEXT wait;

#if LINUX_VERSION_CODE >= KERNEL_VERSION(2,6,0)
        DEFINE_WAIT(waitQ);
#endif
        CAN_DBG((ESDCAN_ZONE_FU, "%s: enter cmd=%08lx\n", OSIF_FUNCTION, cmd));
        init_waitqueue_head(&wait.wq);
        status = nuc_ioctl(ocb, &wait, cmd, buf_in, len_in, buf_out, len_out);
        if (OSIF_EBUSY == status) {
                CAN_NODE *node = ocb->node;

                /* Must wait here */
                OSIF_MUTEX_UNLOCK(&node->lock);
#if LINUX_VERSION_CODE >= KERNEL_VERSION(2,6,0)
                /* BL: sleep_on is deprecated since 2.6.10 */
                prepare_to_wait(&wait.wq, &waitQ, TASK_UNINTERRUPTIBLE);
                schedule();
                finish_wait(&wait.wq, &waitQ);
#else
                sleep_on(&wait.wq);
#endif
                OSIF_MUTEX_LOCK(&node->lock);
                status = wait.status;
        }
        CAN_DBG((ESDCAN_ZONE_FU, "%s: leave (status=%d)\n", OSIF_FUNCTION, status));
        return status;
}
#endif

static int esdcan_ioctl_internal(struct inode *inode, struct file *file,
                                 unsigned int cmd, IOCTL_ARG *ioArg,
                                 CAN_OCB *ocb )
{
        INT32      result = OSIF_SUCCESS;
        CAN_NODE  *node;
        UINT32     objSize;

        /* if private_data == 0 -> only allow CAN_CREATE */
        if (!ocb) {
                CAN_DBG((ESDCAN_ZONE_FU,
                         "%s: create path: cmd: 0x%X, IOCTL_ESDCAN_CREATE: 0x%0X\n",
                         OSIF_FUNCTION, cmd, IOCTL_ESDCAN_CREATE));
                if (cmd == IOCTL_ESDCAN_CREATE) {
                        CAN_INIT_ARG can_init;
#ifdef OSIF_OS_LINUX
                        INT32 net_no = INODE2CANNODE(inode);
#endif /* OSIF_OS_LINUX */
#ifdef OSIF_OS_IRIX
                        INT32 net_no = file->node->net_no;
                        ocb = file->ocb; /* set ocb (on irix ocb_create already called) */
#endif /* OSIF_OS_IRIX */

                        CAN_DBG((ESDCAN_ZONE, "%s: IOCTL_ESDCAN_CREATE, net_no=%d\n", OSIF_FUNCTION, net_no));
                        if (copy_from_user(&can_init, (VOID*)ioArg->buffer, sizeof(CAN_INIT_ARG))) {
                                HOTPLUG_GLOBAL_UNLOCK;
                                return OSIF_EFAULT;
                        }
#ifdef OSIF_OS_LINUX
                        result = ocb_create(net_no, &ocb);
                        if (result != OSIF_SUCCESS) {
                                HOTPLUG_GLOBAL_UNLOCK;
                                return (int)result;
                        }
#endif /* OSIF_OS_LINUX */
                        result = ocb_create2(ocb, net_no, &can_init);
                        if (result != OSIF_SUCCESS) {
                                HOTPLUG_GLOBAL_UNLOCK;
                                return (int)result;
                        }
                        file->private_data = ocb; /* mark as ready */
#ifdef OSIF_OS_LINUX
                        /*
                         *  BL: storing pointer to file-struct in ocb, in order
                         *      to be able to clear file->private_data on
                         *      USB-surprise-removal
                         */
                        ocb->file = file;
#endif /* OSIF_OS_LINUX */
                        nuc_check_links(ocb);
                        HOTPLUG_GLOBAL_UNLOCK;
                        return OSIF_SUCCESS;
                } else {
                        CAN_DBG((ESDCAN_ZONE_FU,
                                 "%s: determine lib path: cmd: 0x%X, IOCTL_CAN_SET_QUEUESIZE: 0x%0X\n",
                                 OSIF_FUNCTION, cmd, IOCTL_CAN_SET_QUEUESIZE));

                        HOTPLUG_GLOBAL_UNLOCK;
                        /*
                         *  Normally we've discovered, that an old "candev"-ntcan-library (major 1)
                         *  is trying to access the new driver. Unfortunately this case does happen
                         *  with "surprise"-removed USB-modules, too (although ntcan-library has a
                         *  correct version). Since there're no modules out there, which use the old
                         *  candev-driver and thus all USB-modules should be delivered with a new
                         *  library, we deliver another error-code depending on the IOCTL-command
                         *  in case of the USB-module.
                         */
#if defined (BOARD_USB)
                        if (cmd == IOCTL_CAN_SET_QUEUESIZE) {
                                return OSIF_INVALID_DRIVER;
                        } else {
                                return OSIF_WRONG_DEVICE_STATE;
                        }
#else
                        return OSIF_INVALID_DRIVER;
#endif
                }
        }
        HOTPLUG_GLOBAL_UNLOCK;
        node = ocb->node;
        if (-1 == HOTPLUG_BOLT_USER_ENTRY(((CAN_CARD*)node->crd)->p_mod)) {
                CAN_DBG((ESDCAN_ZONE, "%s: bolt_user_entry returned -1\n", OSIF_FUNCTION));
                return OSIF_EIO;
        }
        OSIF_MUTEX_LOCK(&node->lock);
        if (ocb->close_state & CLOSE_STATE_HANDLE_CLOSED) {
                ioArg->size = 0;
                OSIF_MUTEX_UNLOCK(&node->lock);
                return OSIF_INVALID_HANDLE;
        }
        switch(cmd) {
        case IOCTL_ESDCAN_DESTROY:
        case IOCTL_ESDCAN_DESTROY_DEPRECATED:
                CAN_DBG((ESDCAN_ZONE, "%s: IOCTL_ESDCAN_DESTROY, minor=%d\n", OSIF_FUNCTION, ocb->minor));
#if defined (OSIF_OS_IRIX)
                file->private_data = 0; /* mark ocb as no more valid! */
#endif /* defined (OSIF_OS_IRIX) */
                result = ocb_destroy(ocb);
                break;

        case IOCTL_ESDCAN_SEND_T:
                CAN_DBG((ESDCAN_ZONE, "%s:IOCTL_ESDCAN_SEND_T: cm_count=%d\n", OSIF_FUNCTION, ioArg->size));
                objSize = sizeof(CAN_MSG_T);
                goto IOCTL_ESDCAN_SEND_00;
        case IOCTL_ESDCAN_SEND_X:
                CAN_DBG((ESDCAN_ZONE, "%s:IOCTL_ESDCAN_SEND_X: cm_count=%d\n", OSIF_FUNCTION, ioArg->size));
                objSize = sizeof(CAN_MSG_X);
                goto IOCTL_ESDCAN_SEND_00;
        case IOCTL_ESDCAN_SEND:
                CAN_DBG((ESDCAN_ZONE, "%s:IOCTL_ESDCAN_SEND: cm_count=%d\n", OSIF_FUNCTION, ioArg->size));
                objSize = sizeof(CAN_MSG);
        IOCTL_ESDCAN_SEND_00:
        {
                UINT32 cm_count;
                INT32  old_state;

                /* block attempts to access cards with wrong firmware */
                CAN_ACTION_CHECK(ocb, result, break);
                /* entering not allowed when a write is pending */
                if (ocb->tx.state & TX_STATE_PENDING_WRITE) {
                        result = OSIF_PENDING_WRITE;
                        break;
                }
                ocb->tx.user_buf = (VOID*)ioArg->buffer;
                ocb->tx.cm_size = objSize;
                cm_count = ioArg->size;
                CAN_DBG((ESDCAN_ZONE, "%s: cm_count=%d\n", OSIF_FUNCTION, cm_count));

                /* need to save old state in case it is TX_STATE_PENDING_SEND, because if nuc_tx fails, we must not
                   clear the old TX_STATE_PENDING_SEND but leave it as is. */
                old_state = ocb->tx.state;
                /* need to set tx.state before nuc_tx call because nuc_tx might call esdcan_tx_done synchronously */
                ocb->tx.state = TX_STATE_PENDING_SEND;

                /* trigger tx job, copy_from_user is done in our context from nuc_tx() */
                result = nuc_tx(ocb, 0, &cm_count);
                /* check errors */
                if ( (result != OSIF_SUCCESS) && (cm_count == 0) ) {
                        ocb->tx.state = old_state; /* restore old tx.state */
                        break;
                }
                CAN_DBG((ESDCAN_ZONE, "%s: copied %d bytes\n", OSIF_FUNCTION, cm_count * sizeof(CAN_MSG)));
                result = OSIF_SUCCESS;
                ioArg->size = cm_count; /* return count and not count*size */
                break;
        }
        case IOCTL_ESDCAN_TAKE_T:
                CAN_DBG((ESDCAN_ZONE, "%s: IOCTL_ESDCAN_TAKE_T\n", OSIF_FUNCTION));
                objSize = sizeof(CAN_MSG_T);
                goto    IOCTL_ESDCAN_TAKE_00;
        case IOCTL_ESDCAN_TAKE_X:
                CAN_DBG((ESDCAN_ZONE, "%s: IOCTL_ESDCAN_TAKE_X\n", OSIF_FUNCTION));
                objSize = sizeof(CAN_MSG_X);
                goto    IOCTL_ESDCAN_TAKE_00;
        case IOCTL_ESDCAN_TAKE:
                CAN_DBG((ESDCAN_ZONE, "%s: IOCTL_ESDCAN_TAKE\n", OSIF_FUNCTION));
                objSize = sizeof(CAN_MSG);
        IOCTL_ESDCAN_TAKE_00:
        {
                INT32 cm_count;

                /* block attempts to access cards with wrong firmware */
                CAN_ACTION_CHECK(ocb, result, break);
                /* only one process may take/read at a time */
                if (ocb->rx.state) {
                        result = OSIF_PENDING_READ;
                        break;
                }
                ocb->rx.state = RX_STATE_PENDING_TAKE;
                /* reset rx buffer pointer */
                ocb->rx.user_buf = (VOID*)ioArg->buffer;
                ocb->rx.cm_size = objSize;
                ocb->rx.cmbuf_in = ocb->rx.cmbuf;
                ocb->rx.cm_count = 0;
                cm_count = (UINT32)(ioArg->size & (CANIO_MAX_RX_QUEUESIZE-1));
                ioArg->size = 0;
                CAN_DBG((ESDCAN_ZONE, "%s: cm_count=%d\n", OSIF_FUNCTION, cm_count));
                if (ocb->mode & CANIO_MODE_OBJECT) {
                        UINT32 id;

                        if (get_user(id, &((CAN_MSG*)ocb->rx.user_buf)->id)) {
                                ocb->rx.state = 0;
                                result = OSIF_EFAULT;
                                break;
                        }
                        /* TODO: Michael: RX object mode also needs a ## !!! */
                        result = nuc_rx_obj(ocb, (UINT32*)&cm_count, id);
                        if (result != OSIF_SUCCESS) {
                                ocb->rx.state = 0;
                                break;
                        }
                        ocb->rx.cm_count = cm_count; /* non object mode does this in rx_done */
                } else {
                        /* trigger rx for cm_count cm */
                        result = nuc_rx(ocb, 0, (UINT32*)&cm_count);
                        if (result != OSIF_SUCCESS) {
                                ocb->rx.state = 0;
                                break;
                        }
                }
                /* return if rx failed */
                if (0 == ocb->rx.cm_count) {
                        nuc_rx_abort(ocb, OSIF_SUCCESS); /* return OSIF_SUCCESS and _not_ OSIF_EIO! */
                        if (0 == ocb->rx.cm_count) {
                                ocb->rx.state = 0;
                                result = (int)ocb->rx.result;
                                break;
                        }
                }
                {       /* read with(out) timestamps */
                        UINT8     *dest = (UINT8*)ioArg->buffer;
#ifdef BOARD_CAN_FD
                        CAN_MSG_X *src;
#else
                        CAN_MSG_T *src;
#endif
                        INT32      i;
                        src = ocb->rx.cmbuf;
                        for (i = 0; i < ocb->rx.cm_count; i++) {
#ifdef BOARD_CAN_FD
                                if ((ocb->rx.cm_size==sizeof(CAN_MSG))||(ocb->rx.cm_size==sizeof(CAN_MSG_X))) {
                                        if (copy_to_user(dest, src, ocb->rx.cm_size)) {
                                                return -OSIF_EFAULT;
                                        }
                                } else {
                                        /* Need to copy CAN_MSG_X data from cmbuf to user-supplied CAN_MSG_T buffer */
                                        /* Make local copy, then call copy_to_user ONCE */
                                        CAN_MSG_T tmp_t;

                                        memcpy(&tmp_t,src,sizeof(CAN_MSG));
                                        tmp_t.timestamp=src->timestamp;
                                        if (copy_to_user(dest, &tmp_t, sizeof(CAN_MSG_T))) {
                                                return -OSIF_EFAULT;
                                        }
                                }
#else
                                /* non-FD driver, src is CAN_MSG_T */
                                if (ocb->rx.cm_size==sizeof(CAN_MSG_X)) {
                                        CAN_MSG_X tmp_x;

                                        memcpy(&tmp_x,src,sizeof(CAN_MSG));
                                        memset(&tmp_x.buf.c[8],0,64-8); /* don't give away kernel stack data to user */
                                        tmp_x.timestamp=src->timestamp;
                                        if (copy_to_user(dest, &tmp_x, sizeof(CAN_MSG_X))) {
                                                return -OSIF_EFAULT;
                                        }
                                } else {
                                        if (copy_to_user(dest, src, ocb->rx.cm_size)) {
                                                return -OSIF_EFAULT;
                                        }
                                }
#endif
                                src++;
                                dest += ocb->rx.cm_size;
                        }
                }
                ocb->rx.state = 0;
                CAN_DBG((ESDCAN_ZONE, "%s: leave, copied %d CM(SG)s\n", OSIF_FUNCTION, ocb->rx.cm_count));
                ioArg->size = ocb->rx.cm_count; /* return count and not count*size */
                ocb->rx.cm_count = 0; /* important to clear, for next read call */
                break;
        }
        case IOCTL_ESDCAN_WRITE_T:
                CAN_DBG((ESDCAN_ZONE, "%s:IOCTL_ESDCAN_WRITE_T: cm_count=%d\n", OSIF_FUNCTION, ioArg->size));
                objSize = sizeof(CAN_MSG_T);
                goto IOCTL_ESDCAN_WRITE_00;
        case IOCTL_ESDCAN_WRITE_X:
                CAN_DBG((ESDCAN_ZONE, "%s:IOCTL_ESDCAN_WRITE_X: cm_count=%d\n", OSIF_FUNCTION, ioArg->size));
                objSize = sizeof(CAN_MSG_X);
                goto IOCTL_ESDCAN_WRITE_00;
        case IOCTL_ESDCAN_WRITE:
                CAN_DBG((ESDCAN_ZONE, "%s:IOCTL_ESDCAN_WRITE: cm_count=%d\n", OSIF_FUNCTION, ioArg->size));
                objSize = sizeof(CAN_MSG);
        IOCTL_ESDCAN_WRITE_00:
                result = esdcan_write_common(ocb, (VOID*)ioArg->buffer, ioArg->size, objSize);
                if (0 > result) {
                        result = -result;
                } else {
                        ioArg->size = result;
                        result = OSIF_SUCCESS;
                }
                break;

        case IOCTL_ESDCAN_READ_T:
                CAN_DBG((ESDCAN_ZONE, "%s:IOCTL_ESDCAN_READ_T: cm_count=%d\n", OSIF_FUNCTION, ioArg->size));
                objSize = sizeof(CAN_MSG_T);
                goto IOCTL_ESDCAN_READ_00;
        case IOCTL_ESDCAN_READ_X:
                CAN_DBG((ESDCAN_ZONE, "%s:IOCTL_ESDCAN_READ_X: cm_count=%d\n", OSIF_FUNCTION, ioArg->size));
                objSize = sizeof(CAN_MSG_X);
                goto IOCTL_ESDCAN_READ_00;
        case IOCTL_ESDCAN_READ:
                CAN_DBG((ESDCAN_ZONE, "%s:IOCTL_ESDCAN_READ: cm_count=%d\n", OSIF_FUNCTION, ioArg->size));
                objSize = sizeof(CAN_MSG);
        IOCTL_ESDCAN_READ_00:
                result = esdcan_read_common(ocb, (VOID*)ioArg->buffer, ioArg->size, objSize);
                if (0 > result) {
                        result = -result;
                } else {
                        ioArg->size = result;
                        result = OSIF_SUCCESS;
                }
                break;
        case IOCTL_ESDCAN_PURGE_TX_FIFO:
        case IOCTL_ESDCAN_PURGE_TX_FIFO_DEPRECATED:
        case IOCTL_ESDCAN_TX_ABORT:
                CAN_DBG((ESDCAN_ZONE, "%s: IOCTL_ESDCAN_TX_ABORT\n", OSIF_FUNCTION));
                result = nuc_tx_abort(ocb, OSIF_OPERATION_ABORTED, 0);
                break;
        case IOCTL_ESDCAN_FLUSH_RX_FIFO:
        case IOCTL_ESDCAN_FLUSH_RX_FIFO_DEPRECATED:
                CAN_DBG((ESDCAN_ZONE, "%s: IOCTL_ESDCAN_PURGE_RX_FIFO\n", OSIF_FUNCTION));
                result = nuc_rx_purge(ocb);
                break;
        case IOCTL_ESDCAN_RX_ABORT:
                CAN_DBG((ESDCAN_ZONE, "%s: IOCTL_ESDCAN_RX_ABORT\n", OSIF_FUNCTION));
                result = nuc_rx_abort(ocb, OSIF_OPERATION_ABORTED);
                break;
        case IOCTL_ESDCAN_RX_OBJ:
                CAN_DBG((ESDCAN_ZONE, "%s: IOCTL_ESDCAN_RX_OBJ: TODO !!!!\n", OSIF_FUNCTION));
                /* TODO */
                result = OSIF_NOT_IMPLEMENTED;
                break;


        case IOCTL_ESDCAN_TX_OBJ_CREATE:
                cmd = NUC_TX_OBJ_CREATE;
                ocb->tx.cm_size = sizeof(CAN_MSG);
                goto IOCTL_ESDCAN_TX_OBJ;
        case IOCTL_ESDCAN_TX_OBJ_CREATE_T:
                cmd = NUC_TX_OBJ_CREATE;
                ocb->tx.cm_size = sizeof(CAN_MSG_T);
                goto IOCTL_ESDCAN_TX_OBJ;
        case IOCTL_ESDCAN_TX_OBJ_CREATE_X:
                cmd = NUC_TX_OBJ_CREATE;
                ocb->tx.cm_size = sizeof(CAN_MSG_X);
                goto IOCTL_ESDCAN_TX_OBJ;

        case IOCTL_ESDCAN_TX_OBJ_AUTOANSWER_ON:
                cmd = NUC_TX_OBJ_AUTOANSWER_ON;
                ocb->tx.cm_size = sizeof(CAN_MSG);
                goto IOCTL_ESDCAN_TX_OBJ;
        case IOCTL_ESDCAN_TX_OBJ_AUTOANSWER_ON_T:
                cmd = NUC_TX_OBJ_AUTOANSWER_ON;
                ocb->tx.cm_size = sizeof(CAN_MSG_T);
                goto IOCTL_ESDCAN_TX_OBJ;
        case IOCTL_ESDCAN_TX_OBJ_AUTOANSWER_ON_X:
                cmd = NUC_TX_OBJ_AUTOANSWER_ON;
                ocb->tx.cm_size = sizeof(CAN_MSG_X);
                goto IOCTL_ESDCAN_TX_OBJ;

        case IOCTL_ESDCAN_TX_OBJ_AUTOANSWER_ONCE:
                cmd = NUC_TX_OBJ_AUTOANSWER_ONCE;
                ocb->tx.cm_size = sizeof(CAN_MSG);
                goto IOCTL_ESDCAN_TX_OBJ;
        case IOCTL_ESDCAN_TX_OBJ_AUTOANSWER_ONCE_T:
                cmd = NUC_TX_OBJ_AUTOANSWER_ONCE;
                ocb->tx.cm_size = sizeof(CAN_MSG_T);
                goto IOCTL_ESDCAN_TX_OBJ;
        case IOCTL_ESDCAN_TX_OBJ_AUTOANSWER_ONCE_X:
                cmd = NUC_TX_OBJ_AUTOANSWER_ONCE;
                ocb->tx.cm_size = sizeof(CAN_MSG_X);
                goto IOCTL_ESDCAN_TX_OBJ;

        case IOCTL_ESDCAN_TX_OBJ_AUTOANSWER_OFF:
                cmd = NUC_TX_OBJ_AUTOANSWER_OFF;
                ocb->tx.cm_size = sizeof(CAN_MSG);
                goto IOCTL_ESDCAN_TX_OBJ;
        case IOCTL_ESDCAN_TX_OBJ_AUTOANSWER_OFF_T:
                cmd = NUC_TX_OBJ_AUTOANSWER_OFF;
                ocb->tx.cm_size = sizeof(CAN_MSG_T);
                goto IOCTL_ESDCAN_TX_OBJ;
        case IOCTL_ESDCAN_TX_OBJ_AUTOANSWER_OFF_X:
                cmd = NUC_TX_OBJ_AUTOANSWER_OFF;
                ocb->tx.cm_size = sizeof(CAN_MSG_X);
                goto IOCTL_ESDCAN_TX_OBJ;

        case IOCTL_ESDCAN_TX_OBJ_UPDATE:
                cmd = NUC_TX_OBJ_UPDATE;
                ocb->tx.cm_size = sizeof(CAN_MSG);
                goto IOCTL_ESDCAN_TX_OBJ;
        case IOCTL_ESDCAN_TX_OBJ_UPDATE_T:
                cmd = NUC_TX_OBJ_UPDATE;
                ocb->tx.cm_size = sizeof(CAN_MSG_T);
                goto IOCTL_ESDCAN_TX_OBJ;
        case IOCTL_ESDCAN_TX_OBJ_UPDATE_X:
                cmd = NUC_TX_OBJ_UPDATE;
                ocb->tx.cm_size = sizeof(CAN_MSG_X);
                goto IOCTL_ESDCAN_TX_OBJ;

        case IOCTL_ESDCAN_TX_OBJ_DESTROY:
                cmd = NUC_TX_OBJ_DESTROY;
                ocb->tx.cm_size = sizeof(CAN_MSG);
                goto IOCTL_ESDCAN_TX_OBJ;
        case IOCTL_ESDCAN_TX_OBJ_DESTROY_T:
                cmd = NUC_TX_OBJ_DESTROY;
                ocb->tx.cm_size = sizeof(CAN_MSG_T);
                goto IOCTL_ESDCAN_TX_OBJ;
        case IOCTL_ESDCAN_TX_OBJ_DESTROY_X:
                cmd = NUC_TX_OBJ_DESTROY;
                ocb->tx.cm_size = sizeof(CAN_MSG_X);
                goto IOCTL_ESDCAN_TX_OBJ;

        case IOCTL_ESDCAN_TX_OBJ_SCHEDULE:
                cmd = NUC_TX_OBJ_SCHEDULE;
                ocb->tx.cm_size = sizeof(CAN_SCHED);
                goto IOCTL_ESDCAN_TX_OBJ;
        case IOCTL_ESDCAN_TX_OBJ_SCHEDULE_START:
                cmd = NUC_TX_OBJ_SCHEDULE_START;
                ocb->tx.cm_size = 0;
                goto IOCTL_ESDCAN_TX_OBJ;
        case IOCTL_ESDCAN_TX_OBJ_SCHEDULE_STOP:
                cmd = NUC_TX_OBJ_SCHEDULE_STOP;
                ocb->tx.cm_size = 0;

        IOCTL_ESDCAN_TX_OBJ:
        {
                UINT32 cm_count = 1;

                CAN_DBG((ESDCAN_ZONE, "%s: IOCTL_ESDCAN_TX_OBJ_xxx\n", OSIF_FUNCTION));
                /* block attempts to access cards with wrong firmware */
                CAN_ACTION_CHECK(ocb, result, break);
                ocb->tx.user_buf = (VOID*)ioArg->buffer;
                result = nuc_tx_obj(ocb, cmd, &cm_count);
                break;
        }
        case IOCTL_ESDCAN_ID_RANGE_ADD:
        {
                CAN_ID_RANGE_ARG id_range;
                UINT32           count;

                CAN_DBG((ESDCAN_ZONE, "%s: IOCTL_ESDCAN_ID_RANGE_ADD\n", OSIF_FUNCTION));
                /* block attempts to access cards with wrong firmware */
                CAN_ACTION_CHECK(ocb, result, break);
                if ( copy_from_user(&id_range, (VOID*)ioArg->buffer, sizeof(CAN_ID_RANGE_ARG)) ) {
                        result = OSIF_EFAULT;
                        break;
                }
                count = id_range.id_stop - id_range.id_start + 1;
                result = id_filter(ocb, node, FILTER_ON | ocb->filter_cmd, id_range.id_start, &count);
                if (result != OSIF_SUCCESS) {
                        id_filter(ocb, node,  FILTER_OFF | ocb->filter_cmd, id_range.id_start, &count);
                }
                break;
        }
        case IOCTL_ESDCAN_ID_RANGE_DEL:
        {
                CAN_ID_RANGE_ARG id_range;
                UINT32           count;

                CAN_DBG((ESDCAN_ZONE, "%s: IOCTL_ESDCAN_ID_RANGE_DEL\n", OSIF_FUNCTION));
                /* block attempts to access cards with wrong firmware */
                CAN_ACTION_CHECK(ocb, result, break);
                if (copy_from_user(&id_range, (VOID*)ioArg->buffer, sizeof(CAN_ID_RANGE_ARG))) {
                        result = OSIF_EFAULT;
                        break;
                }
                count = id_range.id_stop - id_range.id_start + 1;
                result = id_filter(ocb, node, FILTER_OFF | ocb->filter_cmd, id_range.id_start, &count);
                break;
        }
        case IOCTL_ESDCAN_ID_REGION_ADD:
        {
                CAN_ID_REGION_ARG id_region;
                UINT32  filter_cmd = ocb->filter_cmd;
                UINT32  id1st;

                CAN_ACTION_CHECK(ocb, result, break);
                if (copy_from_user(&id_region, (VOID*)ioArg->buffer, sizeof(CAN_ID_REGION_ARG))) {
                        result = OSIF_EFAULT;
                        break;
                }
                CAN_DBG((ESDCAN_ZONE, "%s: IOCTL_ESDCAN_ID_REGION_ADD\n", OSIF_FUNCTION));
                id1st  = id_region.id1st;
                if (ocb->mode & CANIO_MODE_LIN) {
                        filter_cmd = (id1st >> 16) & 0x3;
                        id1st &= CANIO_LIN_ID_LAST;
                }
                result = nuc_id_filter(ocb, (FILTER_ON | filter_cmd), id1st, &id_region.cnt);
                if (id_region.cnt) {
                        result = OSIF_SUCCESS;
                }
                if (copy_to_user((VOID*)ioArg->buffer, &id_region, sizeof(CAN_ID_REGION_ARG))) {
                        result = OSIF_EFAULT;
                }
                break;
        }
        case IOCTL_ESDCAN_ID_REGION_DEL:
        {
                CAN_ID_REGION_ARG id_region;
                UINT32  filter_cmd = ocb->filter_cmd;
                UINT32  id1st;

                CAN_ACTION_CHECK(ocb, result, break);
                if (copy_from_user(&id_region, (VOID*)ioArg->buffer, sizeof(CAN_ID_REGION_ARG))) {
                        result = OSIF_EFAULT;
                        break;
                }
                CAN_DBG((ESDCAN_ZONE, "%s: IOCTL_ESDCAN_ID_REGION_DEL\n", OSIF_FUNCTION));
                id1st  = id_region.id1st;
                if (ocb->mode & CANIO_MODE_LIN) {
                        filter_cmd = (id1st >> 16) & 0x3;
                        id1st &= ~0x30000;
                }
                result = nuc_id_filter(ocb, (FILTER_OFF | filter_cmd), id1st, &id_region.cnt);
                if (id_region.cnt) {
                        result = OSIF_SUCCESS;
                }
                if (copy_to_user((VOID*)ioArg->buffer, &id_region, sizeof(CAN_ID_REGION_ARG))) {
                        result = OSIF_EFAULT;
                }
                break;
        }

        case IOCTL_ESDCAN_SET_BAUD:
                cmd = ESDCAN_CTL_BAUDRATE_SET;
                goto IOCTL_32_W;
        case IOCTL_ESDCAN_GET_BAUD:
                cmd = ESDCAN_CTL_BAUDRATE_GET;
                goto IOCTL_32_R;

        case IOCTL_ESDCAN_SET_BAUD_X:
        {
                CAN_BAUDRATE_X  baud_x;
                INT32           buflen = sizeof baud_x;

                CAN_ACTION_CHECK(ocb, result, break);
                if (copy_from_user(&baud_x, (VOID*)ioArg->buffer, buflen)) {
                        result = OSIF_EFAULT;
                        break;
                }
                CAN_DBG((ESDCAN_ZONE, "%s: IOCTL_ESDCAN_SET_BAUD_X\n", OSIF_FUNCTION));
                result = my_nuc_ioctl(ocb, ESDCAN_CTL_BAUDRATE_X_SET,
                                      &baud_x, buflen, NULL, NULL);
                break;
        }

        case IOCTL_ESDCAN_GET_BAUD_X:
        {
                CAN_BAUDRATE_X  baud_x;
                INT32           outbuflen = sizeof baud_x;

                CAN_ACTION_CHECK(ocb, result, break);
                CAN_DBG((ESDCAN_ZONE, "%s: IOCTL_ESDCAN_GET_BAUD_X\n", OSIF_FUNCTION));
                result = my_nuc_ioctl(ocb, ESDCAN_CTL_BAUDRATE_X_GET,
                                      NULL, 0, &baud_x, &outbuflen);
                if (copy_to_user((VOID*)ioArg->buffer, &baud_x, outbuflen)) {
                        result = OSIF_EFAULT;
                }
                break;
        }

        case IOCTL_ESDCAN_SET_TIMEOUT:
        {
                CAN_TIMEOUT_ARG timeout;

                CAN_DBG((ESDCAN_ZONE, "%s: IOCTL_ESDCAN_SET_TIMEOUT\n", OSIF_FUNCTION));
                /* Do NOT block attempts to access cards with wrong firmware, because
                 * we need canOpen() for the updater to work which calls this IOCTL
                 * implicitly. */
                if (copy_from_user(&timeout, (VOID*)ioArg->buffer, sizeof(CAN_TIMEOUT_ARG))) {
                        result = OSIF_EFAULT;
                        break;
                }
                if ( (timeout.rxtout > CANIO_MAX_RX_TIMEOUT) || (timeout.txtout > CANIO_MAX_TX_TIMEOUT) ) {
                        result = OSIF_INVALID_PARAMETER;
                        break;
                }
                ocb->rx.tout = timeout.rxtout;
                ocb->tx.tout = timeout.txtout;
                break;
        }
        case IOCTL_ESDCAN_GET_RX_MESSAGES:
        {
                UINT32 msgs = 0;

                CAN_DBG((ESDCAN_ZONE, "%s: IOCTL_ESDCAN_GET_RX_MESSAGES\n", OSIF_FUNCTION));
                /* block attempts to access cards with wrong firmware */
                CAN_ACTION_CHECK(ocb, result, break);
                CAN_DBG((ESDCAN_ZONE, "%s: calling nuc_rx_messages\n", OSIF_FUNCTION));
                result = nuc_rx_messages( ocb, &msgs );
                if (put_user(msgs, (UINT32*)ioArg->buffer)) {
                        result = OSIF_EFAULT;
                        break;
                }
                CAN_DBG((ESDCAN_ZONE, "%s: IOCTL_ESDCAN_GET_RX_MESSAGES (rx_msgs = %d)\n", OSIF_FUNCTION, msgs));
                break;
        }
        case IOCTL_ESDCAN_GET_RX_TIMEOUT:
                CAN_DBG((ESDCAN_ZONE, "%s: IOCTL_ESDCAN_GET_RX_TIMEOUT\n", OSIF_FUNCTION));
                /* block attempts to access cards with wrong firmware */
                CAN_ACTION_CHECK(ocb, result, break);
                if (put_user(ocb->rx.tout, (UINT32*)ioArg->buffer)) {
                        result = OSIF_EFAULT;
                        break;
                }
                CAN_DBG((ESDCAN_ZONE, "%s: IOCTL_ESDCAN_GET_RX_TIMEOUT (rx.tout = %d)\n", OSIF_FUNCTION, ocb->rx.tout));
                break;

        case IOCTL_ESDCAN_GET_TX_TIMEOUT:
                CAN_DBG((ESDCAN_ZONE, "%s: IOCTL_ESDCAN_GET_TX_TIMEOUT\n", OSIF_FUNCTION));
                /* block attempts to access cards with wrong firmware */
                CAN_ACTION_CHECK(ocb, result, break);
                if (put_user(ocb->tx.tout, (UINT32*)ioArg->buffer)) {
                        result = OSIF_EFAULT;
                        break;
                }
                CAN_DBG((ESDCAN_ZONE, "%s: IOCTL_ESDCAN_GET_TX_TIMEOUT (tx.tout = %d)\n", OSIF_FUNCTION, ocb->tx.tout));
                break;

        case IOCTL_ESDCAN_GET_TIMESTAMP_FREQ:
        case IOCTL_ESDCAN_GET_TIMESTAMP:
        {
                OSIF_TS ts;
                INT32   outbuflen = sizeof(OSIF_TS);

                CAN_DBG((ESDCAN_ZONE, "%s: IOCTL_ESDCAN_GET_TIMESTAMP_...\n", OSIF_FUNCTION));
                /* block attempts to access cards with wrong firmware */
                CAN_ACTION_CHECK(ocb, result, break);
                result =  my_nuc_ioctl(ocb, (cmd == IOCTL_ESDCAN_GET_TIMESTAMP_FREQ) ? ESDCAN_CTL_TIMEST_FREQ_GET : ESDCAN_CTL_TIMESTAMP_GET,
                                       NULL, 0, &ts, &outbuflen);
                CAN_DBG((ESDCAN_ZONE, "%s: IOCTL_ESDCAN_GET_TIMESTAMP_... result=%d, ts=0x%llX\n",
                         OSIF_FUNCTION, result, ts.tick));
                if (result != OSIF_SUCCESS) {
                        break;
                }
                if (copy_to_user((VOID*)ioArg->buffer, &ts, sizeof(OSIF_TS))) {
                        result = OSIF_EFAULT;
                }
                break;
        }
        case IOCTL_ESDCAN_GET_HW_TIMESTAMP_EX:
        case IOCTL_ESDCAN_GET_HW_TIMESTAMP:
        {
                CAN_HW_TIMESTAMP    hw_ts;
                INT32   outbuflen = sizeof hw_ts;

                CAN_DBG((ESDCAN_ZONE, "%s: IOCTL_ESDCAN_GET_HW_TIMESTAMP_...\n", OSIF_FUNCTION));
                /* block attempts to access cards with wrong firmware */
                CAN_ACTION_CHECK(ocb, result, break);
                result =  my_nuc_ioctl(ocb, (cmd == IOCTL_ESDCAN_GET_HW_TIMESTAMP) ? ESDCAN_CTL_HW_TIMESTAMP_GET : ESDCAN_CTL_HW_TIMESTAMP_GET_EX,
                                       NULL, 0, &hw_ts, &outbuflen);
                CAN_DBG((ESDCAN_ZONE, "%s: IOCTL_ESDCAN_GET_HW_TIMESTAMP_... result=%d, hw_ts=0x%llX\n",
                         OSIF_FUNCTION, result, hw_ts.ts[1]));  /* Print the real HW time stamp only */
                if (result != OSIF_SUCCESS) {
                        break;
                }
                if (copy_to_user((VOID*)ioArg->buffer, &hw_ts, outbuflen)) {
                        result = OSIF_EFAULT;
                }
                break;
        }
        case IOCTL_ESDCAN_DEBUG:
        {
                CAN_DEBUG_ARG can_debug;

                CAN_DBG((ESDCAN_ZONE, "%s: IOCTL_ESDCAN_DEBUG\n", OSIF_FUNCTION));
                if ( copy_from_user( &can_debug, (VOID*)ioArg->buffer, sizeof(can_debug) ) ) {
                        result = OSIF_EFAULT;
                        break;
                }
                switch (can_debug.cmd) {
                case CAN_DEBUG_VER:
                {
                        CAN_CARD *crd = (CAN_CARD*)node->crd;
                        can_debug.p.ver.drv_ver = MAKE_VERSION(LEVEL, REVI, BUILD);
                        can_debug.p.ver.firm_ver = MAKE_VERSION(crd->version_firmware.level,
                                                                crd->version_firmware.revision,
                                                                crd->version_firmware.build);
                        can_debug.p.ver.hard_ver = MAKE_VERSION(crd->version_hardware.level,
                                                                crd->version_hardware.revision,
                                                                crd->version_hardware.build);
                        can_debug.p.ver.board_stat = crd->board_status; /* Will provide real FW/HW status from all supporting boards. */
                        OSIF_SNPRINTF(((CHAR8*)can_debug.p.ver.firm_info,
                                       sizeof(can_debug.p.ver.firm_info),
                                       "%s", crd->pCardIdent->all.name));
                        can_debug.p.ver.features = (UINT16)(ocb->node->features);
                        can_debug.p.ver.ctrl_type = node->ctrl_type;
                        OSIF_MEMSET(can_debug.p.ver.reserved, 0, sizeof(can_debug.p.ver.reserved));
                        break;
                }
                default:
                {
                        INT32 outbuflen = sizeof(can_debug);
                        result = my_nuc_ioctl(ocb, ESDCAN_CTL_DEBUG,
                                              &can_debug, sizeof(can_debug), &can_debug, &outbuflen);
                }
                }
                if (copy_to_user((VOID*)ioArg->buffer, &can_debug, sizeof(can_debug))) {
                        result = OSIF_EFAULT;
                }
                break;
        }
        case IOCTL_ESDCAN_GET_INFO:
        {
                CAN_INFO        info;
                INT32           outbuflen = sizeof(info);
                CAN_CARD        *crd = (CAN_CARD*)node->crd;

                CAN_DBG((ESDCAN_ZONE, "%s: IOCTL_ESDCAN_GET_INFO\n", OSIF_FUNCTION));
                /* Do NOT block attempts to access cards with wrong firmware. The
                 * information should always be readable. */
                if ( copy_from_user( &info, (VOID*)ioArg->buffer, sizeof(info) ) ) {
                        result = OSIF_EFAULT;
                        break;
                }
                result = my_nuc_ioctl(ocb, ESDCAN_CTL_CAN_INFO,
                                      &info, sizeof(info), &info, &outbuflen);

                /* info.base_net   = ;  the driver doesn't know this! Keep previous data. */
                info.ports      = crd->num_nodes;
                info.boardstatus= crd->board_status;
                info.osif_ts_freq= OSIF_TICK_FREQ;
                info.driver     = MAKE_VERSION(LEVEL, REVI, BUILD);
                info.firmware   = MAKE_VERSION(crd->version_firmware.level,
                                               crd->version_firmware.revision,
                                               crd->version_firmware.build);
                info.firmware2  = MAKE_VERSION(crd->version_firmware2.level,
                                               crd->version_firmware2.revision,
                                               crd->version_firmware2.build);
                info.hardware   = MAKE_VERSION(crd->version_hardware.level,
                                               crd->version_hardware.revision,
                                               crd->version_hardware.build);

                /* The board layer should have set the serial number. */
                info.serial     = crd->serial;
                /* If the board layer didn't set the <serial_string> then use the
                 * default decode algorithm for the <serial> number. */
                if ('\0' == info.serial_string[0]) {
                        if (0 != info.serial) {
                                OSIF_SNPRINTF((info.serial_string,
                                               sizeof(info.serial_string),
                                               "%c%c%06ld",
                                               'A' + ((info.serial >> 28) & 0x0F),
                                               'A' + ((info.serial >> 24) & 0x0F),
                                               info.serial & 0x00FFFFFF));
                        } else {
                                /* This means no valid serial number => "N/A" */
                                OSIF_SNPRINTF((info.serial_string,
                                               sizeof(info.serial_string), "N/A"));
                        }
                }

                OSIF_SNPRINTF((info.boardid, sizeof(info.boardid),
                               "%s", crd->pCardIdent->all.name));

                if (copy_to_user((VOID*)ioArg->buffer, &info, sizeof(info))) {
                        result = OSIF_EFAULT;
                }
                break;
        }
        case IOCTL_ESDCAN_SET_20B_HND_FILTER:
        {
                UINT32 amr;

                CAN_DBG((ESDCAN_ZONE, "%s: IOCTL_CAN_SET_20B_FILTER\n", OSIF_FUNCTION));
                /* block attempts to access cards with wrong firmware */
                CAN_ACTION_CHECK(ocb, result, break);
                if (get_user(amr, (UINT32*)ioArg->buffer)) {
                        result = OSIF_EFAULT;
                        break;
                }
                result = nuc_id_filter_mask(ocb, ocb->filter20b.acr, amr, CANIO_IDS_REGION_20B);
                if (OSIF_SUCCESS == result) {
                        ocb->filter20b.amr = amr;
                }
                break;
        }
        case IOCTL_ESDCAN_SET_HND_FILTER:
        {
                CAN_FILTER_MASK  filterMask;
                UINT32           buflen = sizeof(filterMask);

                CAN_DBG((OSIF_ZONE_ESDCAN, "%s: IOCTL_CAN_SET_FILTER\n", OSIF_FUNCTION));
                CAN_ACTION_CHECK(ocb, result, break);
                if (copy_from_user(&filterMask, (VOID*)ioArg->buffer, buflen)) {
                        result = OSIF_EFAULT;
                        break;
                }
                result = nuc_id_filter_mask( ocb, filterMask.acr, filterMask.amr, filterMask.idArea );
                break;
        }
        case IOCTL_ESDCAN_SET_RX_TIMEOUT:
        case IOCTL_ESDCAN_SET_TX_TIMEOUT:
        {
                UINT32 tout;

                CAN_DBG((ESDCAN_ZONE, "%s: IOCTL_ESDCAN_SET_RX/TX_TIMEOUT\n", OSIF_FUNCTION));
                /* block attempts to access cards with wrong firmware */
                CAN_ACTION_CHECK(ocb, result, break);
                if (get_user(tout, (UINT32*)ioArg->buffer)) {
                        result = OSIF_EFAULT;
                        break;
                }
                if (IOCTL_ESDCAN_SET_TX_TIMEOUT == cmd) {
                        ocb->tx.tout = tout;
                } else {
                        ocb->rx.tout = tout;
                }
                break;
        }
        case IOCTL_ESDCAN_GET_SERIAL:
        {
                CAN_CARD *crd = (CAN_CARD*)node->crd;

                CAN_DBG((ESDCAN_ZONE, "%s: IOCTL_ESDCAN_GET_SERIAL\n", OSIF_FUNCTION));
                /* block attempts to access cards with wrong firmware */
                CAN_ACTION_CHECK(ocb, result, break);
                if (put_user(crd->serial, (UINT32*)ioArg->buffer)) {
                        result = OSIF_EFAULT;
                }
                break;
        }
        case IOCTL_ESDCAN_GET_FEATURES:
                CAN_DBG((ESDCAN_ZONE, "%s: IOCTL_ESDCAN_GET_FEATURES\n", OSIF_FUNCTION));
                /* block attempts to access cards with wrong firmware */
                CAN_ACTION_CHECK(ocb, result, break);
                if (put_user(node->features, (UINT32*)ioArg->buffer)) {
                        result = OSIF_EFAULT;
                }
                break;

        case IOCTL_ESDCAN_UPDATE:         /* candev legacy ioctl, not needed anymore, replaced by IOCTL_ESDCAN_TX_OBJ_UPDATE */
        case IOCTL_ESDCAN_SET_MODE:       /* candev legacy ioctl, not needed for esdcan */
        case IOCTL_ESDCAN_GET_TICKS_FREQ: /* legacy ioctl, not needed anymore */
        case IOCTL_ESDCAN_GET_TICKS:      /* legacy ioctl, not needed anymore */
        case IOCTL_ESDCAN_SET_ALT_RTR_ID: /* deprecated customer specific extension */
                result = OSIF_NOT_IMPLEMENTED; /* ...and never will be */
                break;
        case IOCTL_ESDCAN_SET_BUSLOAD_INTERVAL:
                cmd = ESDCAN_CTL_BUSLOAD_INTERVAL_SET;
                goto IOCTL_32_W;
        case IOCTL_ESDCAN_GET_BUSLOAD_INTERVAL:
                cmd = ESDCAN_CTL_BUSLOAD_INTERVAL_GET;
                goto IOCTL_32_R;

        case IOCTL_ESDCAN_GET_BUS_STATISTIC:
        {
                CAN_BUS_STAT    stat;
                UINT32          outbuflen = sizeof(CAN_BUS_STAT);

                /* block attempts to access cards with wrong firmware */
                CAN_ACTION_CHECK(ocb, result, break);
                result = my_nuc_ioctl(ocb, ESDCAN_CTL_BUS_STATISTIC_GET,
                                      NULL, 0, &stat, &outbuflen);
                CAN_DBG((ESDCAN_ZONE, "%s: IOCTL_ESDCAN_GET_BUS_STATISTIC result=%d\n",
                         OSIF_FUNCTION, result));
                if (result != OSIF_SUCCESS) {
                        break;
                }

                if (copy_to_user((VOID*)ioArg->buffer, &stat, sizeof(CAN_BUS_STAT) )) {
                        result = OSIF_EFAULT;
                }
                break;
        }
        case IOCTL_ESDCAN_RESET_BUS_STATISTIC:
                cmd = ESDCAN_CTL_BUS_STATISTIC_RESET;
                goto IOCTL_CMD;
        case IOCTL_ESDCAN_GET_ERROR_COUNTER:
                cmd = ESDCAN_CTL_ERROR_COUNTER_GET;
                goto IOCTL_32_R;

        case IOCTL_ESDCAN_GET_BITRATE_DETAILS:
        {
                CAN_BITRATE  btrInfo;
                UINT32       outbuflen = sizeof(btrInfo);

                /* block attempts to access cards with wrong firmware */
                CAN_ACTION_CHECK(ocb, result, break);
                result = my_nuc_ioctl(ocb, ESDCAN_CTL_BITRATE_DETAILS_GET,
                                      NULL, 0, &btrInfo, &outbuflen);
                CAN_DBG((ESDCAN_ZONE, "%s: ESDCAN_CTL_BITRATE_DETAILS_GET result=%d, errCnt=0x%08X\n",
                         OSIF_FUNCTION, result));
                if (result != OSIF_SUCCESS) {
                        break;
                }
                if (copy_to_user((VOID*)ioArg->buffer, &btrInfo, sizeof(btrInfo))) {
                        result = OSIF_EFAULT;
                }
                break;
        }
        case IOCTL_ESDCAN_SER_REG_READ:
                cmd = ESDCAN_CTL_SER_REG_READ;
                goto IOCTL_ESDCAN_SER_REG_COMMON;
        case IOCTL_ESDCAN_SER_REG_WRITE:
                cmd = ESDCAN_CTL_SER_REG_WRITE;
IOCTL_ESDCAN_SER_REG_COMMON:
        {
                SERIAL_ARG   uartTuple;
                UINT32       buflen = sizeof(uartTuple);

                /* block attempts to access cards with wrong firmware */
                CAN_ACTION_CHECK(ocb, result, break);
                if (copy_from_user(&uartTuple, (VOID*)ioArg->buffer, buflen)) {
                        result = OSIF_EFAULT;
                        break;
                }
                result = my_nuc_ioctl(ocb, cmd,
                                      &uartTuple, buflen, &uartTuple, &buflen);
                CAN_DBG((ESDCAN_ZONE, "%s: IOCTL_ESDCAN_SER_REG_COMMON cmd=%d result=%d\n",
                         OSIF_FUNCTION, cmd, result));
                if (result != OSIF_SUCCESS) {
                        break;
                }
                if (copy_to_user((VOID*)ioArg->buffer, &uartTuple, buflen)) {
                        result = OSIF_EFAULT;
                }
                break;
        }
        case IOCTL_ESDCAN_RESET_CAN_ERROR_CNT:
                cmd = ESDCAN_CTL_RESET_CAN_ERROR_CNT;
                goto IOCTL_CMD;

        case IOCTL_ESDCAN_EEI_CREATE:
        {
                UINT32  eeihandle;
                INT32   outbuflen = sizeof(UINT32);

                CAN_DBG((ESDCAN_ZONE, "%s: IOCTL_ESDCAN_EEI_CREATE...\n", OSIF_FUNCTION));
                /* block attempts to access cards with wrong firmware */
                CAN_ACTION_CHECK(ocb, result, break);
                result =  my_nuc_ioctl(ocb, ESDCAN_CTL_EEI_CREATE, NULL, 0, &eeihandle, &outbuflen);
                if (result != OSIF_SUCCESS) {
                        break;
                }
                if (copy_to_user((VOID*)ioArg->buffer, &eeihandle, sizeof(UINT32))) {
                        result = OSIF_EFAULT;
                }
                break;
        }
        case IOCTL_ESDCAN_EEI_DESTROY:
                cmd = ESDCAN_CTL_EEI_DESTROY;
                goto IOCTL_32_W;
        case IOCTL_ESDCAN_EEI_STATUS:
        {
                EEI_STATUS eeistatus;
                INT32 outbuflen = sizeof(EEI_STATUS);

                /* block attempts to access cards with wrong firmware */
                CAN_ACTION_CHECK(ocb, result, break);
                if (copy_from_user(&eeistatus, (VOID*)ioArg->buffer, sizeof(EEI_STATUS))) {
                        result = OSIF_EFAULT;
                        break;
                }
                result = my_nuc_ioctl(ocb, ESDCAN_CTL_EEI_STATUS, &eeistatus, sizeof(EEI_STATUS), &eeistatus, &outbuflen);
                if (result != OSIF_SUCCESS) {
                        break;
                }
                if (copy_to_user((VOID*)ioArg->buffer, &eeistatus, sizeof(EEI_STATUS))) {
                        result = OSIF_EFAULT;
                }
                break;
        }
        case IOCTL_ESDCAN_EEI_CONFIGURE:
        {
                EEI_UNIT eeiunit;

                /* block attempts to access cards with wrong firmware */
                CAN_ACTION_CHECK(ocb, result, break);
                if (copy_from_user(&eeiunit, (VOID*)ioArg->buffer, sizeof(EEI_UNIT))) {
                        result = OSIF_EFAULT;
                        break;
                }
                result = my_nuc_ioctl(ocb, ESDCAN_CTL_EEI_CONFIGURE, &eeiunit, sizeof(EEI_UNIT), NULL, NULL);
                break;
        }
        case IOCTL_ESDCAN_EEI_START:
                cmd = ESDCAN_CTL_EEI_START;
                goto IOCTL_32_W;
        case IOCTL_ESDCAN_EEI_STOP:
                cmd = ESDCAN_CTL_EEI_STOP;
                goto IOCTL_32_W;
        case IOCTL_ESDCAN_EEI_TRIGGER_NOW:
                cmd = ESDCAN_CTL_EEI_TRIGGER_NOW;
                goto IOCTL_32_W;

        case IOCTL_ESDCAN_SET_TX_TS_WIN:
                cmd = ESDCAN_CTL_TX_TS_WIN_SET;
                goto IOCTL_32_W;
        case IOCTL_ESDCAN_GET_TX_TS_WIN:
                cmd = ESDCAN_CTL_TX_TS_WIN_GET;
                goto IOCTL_32_R;
        case IOCTL_ESDCAN_SET_TX_TS_TIMEOUT:
                cmd = ESDCAN_CTL_TX_TS_TIMEOUT_SET;
                goto IOCTL_32_W;
        case IOCTL_ESDCAN_GET_TX_TS_TIMEOUT:
                cmd = ESDCAN_CTL_TX_TS_TIMEOUT_GET;
                goto IOCTL_32_R;
        case IOCTL_ESDCAN_GET_TX_MESSAGES:
                cmd = ESDCAN_CTL_CAN_GET_TX_MESSAGES;
                goto IOCTL_32_R;

        case IOCTL_ESDCAN_SET_FD_TDC:
                cmd = ESDCAN_CTL_CAN_TDC_SET;
                goto IOCTL_32_W;
        case IOCTL_ESDCAN_GET_FD_TDC:
                cmd = ESDCAN_CTL_CAN_TDC_GET;
                goto IOCTL_32_R;

#if defined(BOARD_LIN)
        case IOCTL_LIN_MASTER_SEL:
                cmd = ESDCAN_CTL_LIN_MASTER_SEL;
                goto IOCTL_32_W;
#endif


        IOCTL_CMD:
        {
                /* block attempts to access cards with wrong firmware */
                CAN_ACTION_CHECK(ocb, result, break);
                result = my_nuc_ioctl(ocb, cmd, NULL, 0, NULL, NULL);
                CAN_DBG((ESDCAN_ZONE, "%s: IOCTL_CMD ocb=0x%08X, node=0x%08X, cmd=%d result=%d\n",
                         OSIF_FUNCTION, ocb, node, cmd, result));
                break;
        }

        IOCTL_32_R:
        {
                UINT32  value;
                UINT32  buflen = sizeof(value);

                /* block attempts to access cards with wrong firmware */
                CAN_ACTION_CHECK(ocb, result, break);
                result = my_nuc_ioctl(ocb, cmd, NULL, 0, &value, &buflen);
                CAN_DBG((ESDCAN_ZONE, "%s: IOCTL_32_R ocb=0x%08X, node=0x%08X, cmd=%d result=%d\n",
                         OSIF_FUNCTION, ocb, node, cmd, result));
                if ( (result != OSIF_SUCCESS) ||
                     (buflen != sizeof(value)) ) {
                        break;
                }
                if (put_user(value, (UINT32*)ioArg->buffer)) {
                        result = OSIF_EFAULT;
                }
                break;
        }

        IOCTL_32_W:
        {
                UINT32  value;

                /* block attempts to access cards with wrong firmware */
                CAN_ACTION_CHECK(ocb, result, break);
                if (get_user(value, (UINT32*)ioArg->buffer)) {
                        result = OSIF_EFAULT;
                        break;
                }
                result = my_nuc_ioctl(ocb, cmd, &value, sizeof(value), NULL, NULL);
                CAN_DBG((ESDCAN_ZONE, "%s: IOCTL_32_W ocb=0x%08X, node=0x%08X, cmd=%d result=%d\n",
                         OSIF_FUNCTION, ocb, node, cmd, result));
                break;
        }
#if 0 /* currently not used */
        IOCTL_32_RW:
        {
                UINT32  value;
                UINT32  buflen = sizeof(value);

                /* block attempts to access cards with wrong firmware */
                CAN_ACTION_CHECK(ocb, result, break);
                if (get_user(value, (UINT32*)ioArg->buffer)) {
                        result = OSIF_EFAULT;
                        break;
                }
                result = my_nuc_ioctl(ocb, cmd, &value, buflen, &value, &buflen);
                CAN_DBG((ESDCAN_ZONE, "%s: IOCTL_32_RW ocb=0x%08X, node=0x%08X, cmd=%d result=%d\n",
                         OSIF_FUNCTION, ocb, node, cmd, result));
                if ( (result != OSIF_SUCCESS) ||
                     (buflen != sizeof(value)) ) {
                        break;
                }
                if (put_user(value, (UINT32*)ioArg->buffer)) {
                        result = OSIF_EFAULT;
                }
                break;
        }
#endif
        default:
                CAN_DBG((ESDCAN_ZONE, "%s: IOCTL(%08x) not supported\n", OSIF_FUNCTION, cmd));
                result = OSIF_NOT_SUPPORTED;
        } /* switch */
        nuc_check_links(ocb);
        OSIF_MUTEX_UNLOCK(&node->lock);
        HOTPLUG_BOLT_USER_EXIT(((CAN_CARD*)node->crd)->p_mod);
        return result;
}

#if PLATFORM_64BIT
# if LINUX_VERSION_CODE <= KERNEL_VERSION(2,6,10)
static int esdcan_ioctl_32(unsigned int fd, unsigned int cmd, unsigned long arg, struct file *file)
{
        struct inode *inode;
        INT32         result = OSIF_SUCCESS;
        IOCTL_ARG     ioArg;
        IOCTL_ARG_32  ioArg32;
        CAN_OCB      *ocb;

        CAN_DBG((ESDCAN_ZONE_FU, "%s: enter\n", OSIF_FUNCTION));
        /* Patch ioctl-cmd to ioctl-command in 64-Bit driver
         * This function is called for IOCTLs with parameters, only. */
        cmd = ((cmd & (~0x00040000)) | 0x00080000);
        inode = file->f_dentry->d_inode;
        HOTPLUG_GLOBAL_LOCK;
        ocb = (CAN_OCB*)file->private_data;
        CAN_DBG((ESDCAN_ZONE, "%s: params: ioctl=%x, ocb=%p, arg=%p\n", OSIF_FUNCTION, cmd, ocb, arg));
        if (NULL != (IOCTL_ARG_32*)arg) {
                if (copy_from_user(&ioArg32, (IOCTL_ARG_32*)arg, sizeof(ioArg32))) {
                        HOTPLUG_GLOBAL_UNLOCK;
                        CAN_DBG((ESDCAN_ZONE, "%s: leave (cfu failed)\n", OSIF_FUNCTION));
                        RETURN_TO_USER(OSIF_EFAULT);
                }
                ioArg.buffer = (void*)((unsigned long)ioArg32.buffer);
                ioArg.size = ioArg32.size;
        }
        result = esdcan_ioctl_internal(inode, file, cmd, &ioArg, ocb);
        if ( ( IOCTL_ESDCAN_CREATE != cmd ) &&
             ( NULL != ocb ) ) {
                if (result == OSIF_SUCCESS) {
                        ioArg32.buffer = (uint32_t)((unsigned long)ioArg.buffer);
                        ioArg32.size = ioArg.size;
                        if (NULL != (IOCTL_ARG_32*)arg) {
                                /* result of esdcan_ioctl_internal is aliased! */
                                if (copy_to_user((IOCTL_ARG_32*)arg, &ioArg32,  sizeof(ioArg32))) {
                                        result = OSIF_EFAULT;
                                }
                        }
                }
        }
        CAN_DBG((ESDCAN_ZONE_FU,
                 "%s: leave (result=%d)\n", OSIF_FUNCTION, result));
        RETURN_TO_USER(result);
}
# else
static long esdcan_compat_ioctl(struct file *file, unsigned int cmd, unsigned long arg)
{
        struct inode *inode;
        INT32         result = OSIF_SUCCESS;
        IOCTL_ARG     ioArg;
        IOCTL_ARG_32  ioArg32;
        CAN_OCB      *ocb;

        CAN_DBG((ESDCAN_ZONE_FU,
                 "%s: enter (cmd=0x%X, arg=%p)\n",
                 OSIF_FUNCTION, cmd, arg));
        inode = file_inode(file);
        HOTPLUG_GLOBAL_LOCK;
        /* Patch ioctl-cmd to ioctl-command in 64-Bit driver */
        if (IOCTL_CAN_SET_QUEUESIZE != cmd) { /* Don't change IOCTL from old library (needed for differentiation) */
                if ( (cmd & IOCSIZE_MASK) == 0x00040000 ) { /* Don't change IOCTL's without parameter */
                        cmd = ((cmd & (~0x00040000)) | 0x00080000);
                }
        }
        ocb = (CAN_OCB*)file->private_data;
        CAN_DBG((ESDCAN_ZONE, "%s: params (ioctl=%x, ocb=%p, arg=%p)\n", OSIF_FUNCTION, cmd, ocb, arg));
        if (NULL != (IOCTL_ARG_32*)arg) {
                if (copy_from_user(&ioArg32, (IOCTL_ARG_32*)arg, sizeof(ioArg32))) {
                        HOTPLUG_GLOBAL_UNLOCK;
                        CAN_DBG((ESDCAN_ZONE, "%s: leave (cfu failed)\n", OSIF_FUNCTION));
                        RETURN_TO_USER(OSIF_EFAULT);
                }
                ioArg.buffer = (void*)((unsigned long)ioArg32.buffer);
                ioArg.size = ioArg32.size;
        }
        result = esdcan_ioctl_internal(inode, file, cmd, &ioArg, ocb);
        if ( ( IOCTL_ESDCAN_CREATE != cmd ) &&
             ( NULL != ocb ) ) {
                if (result == OSIF_SUCCESS) {
                        ioArg32.buffer = (uint32_t)((unsigned long)ioArg.buffer);
                        ioArg32.size = ioArg.size;
                        if (NULL != (IOCTL_ARG_32*)arg) {
                                /* result of esdcan_ioctl_internal is aliased! */
                                if (copy_to_user((IOCTL_ARG_32*)arg, &ioArg32,  sizeof(ioArg32))) {
                                        result = OSIF_EFAULT;
                                }
                        }
                }
        }
        CAN_DBG((ESDCAN_ZONE_FU,
                 "%s: leave (result=%d)\n", OSIF_FUNCTION, result));
        RETURN_TO_USER(result);
}
# endif
#endif

#if LINUX_VERSION_CODE > KERNEL_VERSION(2,6,10)
static long esdcan_unlocked_ioctl(struct file *file, unsigned int cmd, unsigned long arg)
{
        struct inode *inode;
        long          result = OSIF_SUCCESS;

        CAN_DBG((ESDCAN_ZONE_FU,
                 "%s: enter (cmd=0x%X, arg=%p)\n",
                 OSIF_FUNCTION, cmd, arg));
        inode = file_inode(file);
        result = esdcan_ioctl(inode, file, cmd, arg);
        CAN_DBG((ESDCAN_ZONE_FU,
                 "%s: leave (result=%d)\n", OSIF_FUNCTION, result));
        return result; /* returns to user, but result is already inverted in esdcan_ioctl() */
}
#endif


/*! \fn static int esdcan_ioctl(struct inode *inode, struct file *file, unsigned int cmd, unsigned long arg);
 *  \brief ioctl entry for driver
 *  \param inode pointer to inode structure
 *  \param file pointer to file structure (contains private_data pointer)
 *  \param cmd ioctl command (see esdcanio.h for IOCTL_x defines)
 *  \param ioctl argument (this is usually a user space pointer)
 *  \return Linux or CAN error code
 */
ESDCAN_IOCTL_PROTO
{
        IOCTL_ARG        ioArg;
        INT32            result = OSIF_SUCCESS;
        CAN_OCB         *ocb;
#ifdef OSIF_OS_IRIX
        vertex_hdl_t     vhdl_dev, vhdl;
        void            *drvarg;
        CAN_HANDLE_INFO *file; /* call this variable "file" because of linux */
#endif /* OSIF_OS_IRIX */

        CAN_DBG((ESDCAN_ZONE_FU, "%s: enter\n", OSIF_FUNCTION));
        HOTPLUG_GLOBAL_LOCK;
#ifdef OSIF_OS_IRIX
        /*  Get the vertex handle and pointer to dev-structure */
        vhdl_dev = dev_to_vhdl(devp);
        if (vhdl_dev == NULL) {
                CAN_PRINT((":CAN: dev_to_vhdl returns NULL"));
                HOTPLUG_GLOBAL_UNLOCK;
                RETURN_TO_USER(OSIF_EIO);
        }
        CAN_DBG((ESDCAN_ZONE, "%s:CAN: vhdl_dev=%x", OSIF_FUNCTION, vhdl_dev));
        file = (CAN_HANDLE_INFO*)device_info_get(vhdl_dev);
#endif /* OSIF_OS_IRIX */
        ocb = (CAN_OCB*)file->private_data;
        CAN_DBG((ESDCAN_ZONE, "%s: enter (ioctl=%x, ocb=%p, arg=%p)\n", OSIF_FUNCTION, cmd, ocb, arg));
        if (NULL != (IOCTL_ARG*)arg) {
                if (copy_from_user(&ioArg, (IOCTL_ARG*)arg, sizeof(ioArg))) {
                        HOTPLUG_GLOBAL_UNLOCK;
                        CAN_DBG((ESDCAN_ZONE, "%s: leave (cfu failed)\n", OSIF_FUNCTION));
                        RETURN_TO_USER(OSIF_EFAULT);
                }
        }
        result = esdcan_ioctl_internal(inode, file, cmd, &ioArg, ocb);
        if ( ( IOCTL_ESDCAN_CREATE != cmd ) &&
             ( NULL != ocb ) ) {
                if (result == OSIF_SUCCESS) {
#ifdef OSIF_OS_IRIX
                        *rvalp = 0;
#endif
                        if (NULL != (IOCTL_ARG*)arg) {
                                /* result of esdcan_ioctl_internal is aliased! */
                                if (copy_to_user((IOCTL_ARG*)arg, &ioArg, sizeof(ioArg))) {
                                        result = OSIF_EFAULT;
                                }
                        }
                }
        }
        CAN_DBG((ESDCAN_ZONE_FU,
                 "%s: leave (result=%d)\n", OSIF_FUNCTION, result));
        RETURN_TO_USER(result);
}


static unsigned int esdcan_poll(struct file *pFile, struct poll_table_struct *pPollTable)
{
        CAN_OCB        *ocb;
        CAN_NODE       *node;
        unsigned int    mask = 0;
        UINT32          num;

        ocb = (CAN_OCB*)pFile->private_data;
        node = ocb->node;
        OSIF_MUTEX_LOCK(&node->lock);
        if (ocb->close_state & CLOSE_STATE_HANDLE_CLOSED) {
                OSIF_MUTEX_UNLOCK(&node->lock);
                return OSIF_INVALID_HANDLE;
        }
        poll_wait(pFile, &node->wqRxNotify, pPollTable);
        nuc_rx_messages(ocb, &num);
        if (num) {
                mask |= POLLIN | POLLRDNORM;
        }
        OSIF_MUTEX_UNLOCK(&node->lock);
        return mask;
}
