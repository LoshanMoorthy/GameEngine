/**
   @brief Purpose of global.h:
   This header file defines the Global struct, which serves as a central repository
   for key game engine components. It encompasses rendering information, configuration
   settings, input states, and timing data, ensuring a centralized and accessible
   storage for essential game engine elements.
*/
#pragma once

#include "render/render.h"
#include "config.h"
#include "input.h"
#include "time.h"

typedef struct global
{
    Render_State render;
    Config_State config;
    Input_State input;
    Time_State time;
} Global;

extern Global global;