/**
   @brief Purpose of time.h:
   This header file defines the Time_State struct, which encapsulates various time-related
   information essential for game engine operation. It includes data such as delta time,
   timestamps, frame timing, and frame rate, facilitating precise time management within
   the engine.
*/

#pragma once

#include "types.h"

typedef struct time_state
{
    f32 delta;
    f32 now;
    f32 last;

    f32 frame_last;
    f32 frame_delay;
    f32 frame_time;

    u32 frame_rate;
    u32 frame_count;
} Time_State;

void time_init(u32 frame_rate);
void time_update(void);
void time_update_late(void);