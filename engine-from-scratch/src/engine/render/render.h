/**
   @brief Purpose of render.h:
   This header file defines the `Render_state` struct,
   along with functions for initializing, managing, 
   and rendering graphical elements within the game engine. 
   It serves as the core rendering module, providing necessary 
   functionality for rendering graphics and objects.
*/
#pragma once

#include <SDL2/SDL.h>
#include <linmath.h>

#include "../types.h"

typedef struct render_state 
{
    SDL_Window *window;
    f32 width;
    f32 height;
} Render_State;

void render_init(void);
void render_begin(void);
void render_end(void);
void render_quad(vec2 pos, vec2 size, vec4 color);
