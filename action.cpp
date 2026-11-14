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
    ACTION_SHORT_BEEP, 
    ACTION_MEDIUM_BEEP, 
    ACTION_LONG_BEEP,
    ACTION_BEEP_400HZ,
    ACTION_BEEP_600HZ,
    ACTION_BEEP_800HZ,
    ACTION_BEEP_1000HZ,
    ACTION_BEEP_400_405HZ,
    ACTION_BEEP_300_301HZ,
    ACTION_BEEP_440HZ,
    ACTION_X,
    ACTION_BIG_BEN, 
    ACTION_RING, 
    ACTION_NBR_OF
} action_indx_et;



typedef struct
{
    // action_indx_et  action[HOME_NBR_OF];
    uint32_t duration;
    float freq1;
    float freq2;
    float freq3;
} tone_param_st;
typedef struct 
{
    char            name[EVENT_NAME_LEN];
    uint16_t        counter;
    uint8_t         state;
    tone_param_st   tone[HOME_NBR_OF];
    //action_indx_et  action[HOME_NBR_OF];
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
        .tone =
        { // State             duration Freq1       Freq2       Freq3
            [HOME_AWAY]     = {10000,   800.0,      801.0,      3.0},
            [HOME_INDOOR]   = {1000,    900.0,      902.0,      0.0},
            [HOME_OUTDOOR]  = {5000,    600.0,      620.0,      10.0},
            [HOME_SLEEP]    = {1000,    800.0,      0.0,        0.0},
            [HOME_MUTE]     = {0,       800.0,      0.0,        0.0},
        }
    },
    {
        .name = "Piha_1",    
        .counter = 0, 
        .state = 0,
        .tone =
        { // State             duration Freq1       Freq2       Freq3
            [HOME_AWAY]     = {10000,   800.0,      801.0,      4.0},
            [HOME_INDOOR]   = {1000,    900.0,      902.0,      0.0},
            [HOME_OUTDOOR]  = {5000,    600.0,      620.0,      10.0},
            [HOME_SLEEP]    = {1000,    800.0,      0.0,        0.0},
            [HOME_MUTE]     = {0,       800.0,      0.0,        0.0},
        }
    },
    {
        .name = "Terassi",    
        .counter = 0, 
        .state = 0,
        .tone =
        { // State             duration Freq1       Freq2       Freq3
            [HOME_AWAY]     = {10000,   800.0,      801.0,      6.0},
            [HOME_INDOOR]   = {1000,    700.0,      702.0,      0.0},
            [HOME_OUTDOOR]  = {5000,    600.0,      620.0,      10.0},
            [HOME_SLEEP]    = {1000,    800.0,      0.0,        0.0},
            [HOME_MUTE]     = {0,       800.0,      0.0,        0.0},
        }
    },
    {
        .name = "PIR_3",    
        .counter = 0, 
        .state = 0,
        .tone =
        { // State             duration Freq1       Freq2       Freq3
            [HOME_AWAY]     = {10000,   800.0,      801.0,      10.0},
            [HOME_INDOOR]   = {1000,    600.0,      602.0,      0.0},
            [HOME_OUTDOOR]  = {5000,    600.0,      620.0,      10.0},
            [HOME_SLEEP]    = {1000,    800.0,      0.0,        0.0},
            [HOME_MUTE]     = {0,       800.0,      0.0,        0.0},
        }
    },
};

typedef struct 
{
    uint8_t nbr_of_events;
    home_state_et home_state;
} action_ctrl_st;

action_ctrl_st action_ctrl = {};

int action_find_event(const char *namep);


void action_initialize(void)
{
    action_ctrl.nbr_of_events = sizeof(event) / sizeof(event[0]);
}

void action_set_home_state(home_state_et home_state)
{
    action_ctrl.home_state = home_state;
}

void action_new_event(char *namep)
{
    int ev = action_find_event(namep);

    if ((ev >= 0) && (ev < action_ctrl.nbr_of_events))
    {
        event[ev].counter++;
        Serial.printf("Event %s found at index %d\n",
                      event[ev].name, ev);

        uint32_t duration = event[ev].tone[action_ctrl.home_state].duration;     
        float freq1 = event[ev].tone[action_ctrl.home_state].freq1;     
        float freq2 = event[ev].tone[action_ctrl.home_state].freq2;     
        float freq3 = event[ev].tone[action_ctrl.home_state].freq3; 
        Serial.printf("Tone: %d, %f %f %f\n", duration, freq1, freq2, freq3);    
        dingdong_play_tone(duration, freq1, freq2, freq3);

        // switch(ev)
        // {
        //     case 0:
        //         //dingdong_play_wav(WAV_BIG_BEN);
        //         dingdong_play_tone(2000, 800, 805);
        //         break;
        //     case 1:
        //         //dingdong_play_wav(WAV_SENSOR_BEEP);
        //         dingdong_play_tone(500, 1200, 2000);
        //         break;
        //     case 2:
        //         //dingdong_play_wav(WAV_DIAL_CALL);
        //         dingdong_play_tone(200, 100, 150);
        //         break;
        //     case 3:
        //         // dingdong_play_wav(WAV_PHONE_RINGING);
        //         dingdong_play_tone(5000, 300, 301);
        //         break;
        //     default:
        //         break;
        // }
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

