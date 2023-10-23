/**
   @brief Purpose of global.h:
   This header file defines the Global struct, which encapsulates the core global state
   of the game engine, including rendering information. It ensures a centralized and
   accessible storage for essential game engine components.
*/
#pragma once

#include "render/render.h"

typedef struct global {
    Render_State render;
} Global;

extern Global global;