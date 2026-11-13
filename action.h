#ifndef __ACTION_H__
#define __ACTION_H__

typedef enum
{
    HOME_AWAY = 0,
    HOME_INDOOR,
    HOME_OUTDOOR,
    HOME_SLEEP,
    HOME_MUTE,
    HOME_NBR_OF,
} home_state_et;

void action_initialize(void);

void action_set_home_state(home_state_et home_state);

void action_new_event(char *namep);

#endif