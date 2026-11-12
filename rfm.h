#ifndef __RFM_H__
#define __RFM_H__

#define RFM_MAX_MSG_LEN     200

#include "msg.h"

typedef struct 
{
    msg_st  rx;
    msg_st  tx;
} rfm_st;

void rfm_initialize(void);

void rfm_rx_task(void);

#endif