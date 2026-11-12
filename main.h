#ifndef __MAIN_H__
#define __MAIN_H__

#define  MY_ADDR_LEN        8
#define LABEL_LEN           12
#define TXT_LEN             40
#define TIME_ZONE_OFFS      2
#define UNIT_LABEL_LEN      10
#define MEASURE_LABEL_LEN   16


#define PIRPANA
// #define LILLA_ASTRID
// #define VILLA_ASTRID

#define SerialRfm       Serial1

#include "io.h"
#include "atask.h"

#define LABEL_LEN           12
#define TXT_LEN             40
#define TIME_ZONE_OFFS      2
#define UNIT_LABEL_LEN      10
#define MEASURE_LABEL_LEN   16

#define __APP__   "T2611-Pico-Alarm-Dong"

typedef struct
{
    uint32_t next_io_tick;
    uint32_t next_super_tick;
    char my_addr[MY_ADDR_LEN];
    struct tm timeinfo;
} main_ctrl_st;

typedef struct date_time
{
    uint16_t  year;
    uint8_t   month;
    uint8_t   day;
    uint8_t   hour;
    uint8_t   minute;
    uint8_t   second;
 } date_time_st;


 
#endif