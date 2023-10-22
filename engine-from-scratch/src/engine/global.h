/**
   @brief Purpose of global.h:
   This header file defines the Global struct, which encapsulates the core global state
   of the game engine, including rendering information. It ensures a centralized and
   accessible storage for essential game engine components.
*/
#ifndef GLOBAL_H
#define GLOBAL_H

#include "render/render.h"

typedef struct global
{
    Render_state render;
} Global;

extern Global global;

#endif