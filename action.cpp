#include <string.h>
#include <stdlib.h>
#include <ctype.h>
#include <Arduino.h>
#include <time.h>
#include "main.h"
#include "msg.h"
#include "action.h"
#include "dingdong.h"
#include "atask.h"

#define    EVENT_NAME_LEN   10

typedef enum
{
    ACTION_UNDEFINED = 0,
    ACTION_TINY_BEEP, 
    ACTION_BEEP, 
    ACTION_BIG_BEN, 
    ACTION_RING, 
    ACTION_NBR_OF
} action_indx_et;

typedef enum
{
    HOME_AWAY = 0,
    HOME_INDOOR,
    HOME_OUTDOOR,
    HOME_SLEEP,
    HOME_NBR_OF,
} home_state_et;

typedef struct 
{
    char            name[EVENT_NAME_LEN];
    uint16_t        counter;
    uint8_t         state;
    action_indx_et  action[HOME_NBR_OF];
} event_st;

// typedef struct
// {
// } action_st;


event_st event[] =
{
    {
        .name = "Katos",    
        .counter = 0, 
        .state = 0,
        .action =
        {
            [HOME_AWAY] = ACTION_RING,
            [HOME_INDOOR] = ACTION_TINY_BEEP,
            [HOME_OUTDOOR] = ACTION_BEEP,
            [HOME_SLEEP] = ACTION_TINY_BEEP,
        }
    },
    {
        .name = "PIR_1",    
        .counter = 0, 
        .state = 0,
        .action =
        {
            [HOME_AWAY] = ACTION_RING,
            [HOME_INDOOR] = ACTION_TINY_BEEP,
            [HOME_OUTDOOR] = ACTION_BEEP,
            [HOME_SLEEP] = ACTION_TINY_BEEP,
        }
    },
    {
        .name = "PIR_2",    
        .counter = 0, 
        .state = 0,
        .action =
        {
            [HOME_AWAY] = ACTION_RING,
            [HOME_INDOOR] = ACTION_TINY_BEEP,
            [HOME_OUTDOOR] = ACTION_BEEP,
            [HOME_SLEEP] = ACTION_TINY_BEEP,
        }
    },
    {
        .name = "PIR_3",    
        .counter = 0, 
        .state = 0,
        .action =
        {
            [HOME_AWAY] = ACTION_RING,
            [HOME_INDOOR] = ACTION_TINY_BEEP,
            [HOME_OUTDOOR] = ACTION_BEEP,
            [HOME_SLEEP] = ACTION_TINY_BEEP,
        }
    },
};

typedef struct 
{
    uint8_t nbr_of_events;
} action_ctrl_st;

action_ctrl_st action_ctrl = {};

int action_find_event(const char *namep);


void action_initialize(void)
{
    action_ctrl.nbr_of_events = sizeof(event) / sizeof(event[0]);
}

void action_new_event(char *namep)
{
    int ev = action_find_event(namep);

    if (ev >= 0)
    {
        event[ev].counter++;
        Serial.printf("Event %s found at index %d\n",
                      event[ev].name, ev);
        switch(ev)
        {
            case 0:
                dingdong_play_wav(WAV_BIG_BEN);
                break;
            case 1:
                dingdong_play_wav(WAV_SENSOR_BEEP);
                break;
            case 2:
                dingdong_play_wav(WAV_DIAL_CALL);
                break;
            case 3:
                // dingdong_play_wav(WAV_PHONE_RINGING);
                dingdong_play_tone(1, 300, 500);
                break;
            default:
                break;
        }
    }
    else
    {
        Serial.printf("Unknown event %s\n", namep);
    }
}


    // WAV_BIG_BEN = 0,
    // WAV_SENSOR_BEEP,
    // WAV_DIAL_CALL,
    // WAV_OLD_CHURCH,
    // WAV_PHONE_RINGING,
    // WAV_ROTARY_PHONE_HIGH,
    // WAV_ROTARY_PHONE_LOW,

int action_find_event(const char *namep)
{
    for (uint8_t i = 0; i < action_ctrl.nbr_of_events; i++)
    {
        if (strcmp(event[i].name, namep) == 0)
        {
            return i;   // Found
        }
    }

    return -1;          // Not found
}

