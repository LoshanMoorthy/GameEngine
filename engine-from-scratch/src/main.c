#include <stdio.h>
#include <stdbool.h>
#include <glad/glad.h>
#define SDL_MAIN_HANDLED
#include <SDL2/SDL.h>

#include "engine/global.h"

int main(int argc, char **argv[])
{
    // Initialize rendering
    render_init();
    bool should_quit = false;

    // Main game loop
    while (!should_quit)
    {
        SDL_Event event;

        // Check for and handle SDL events
        while (SDL_PollEvent(&event))
        {
            switch(event.type) 
            {
                case SDL_QUIT:
                    // The user closed the window, so exit the game loop
                    should_quit = true;
                    break;
                default:
                    // Handle other types of events, if needed
                    break;
            }
        }

        // Begin rendering a frame
        render_begin();

        // TODO: Render a white quad at the center of the screen
        render_quad(
            (vec2){global.render.width * 0.5, global.render.height * 0.5},  // Position
            (vec2){50, 50},                                                // Size
            (vec4){0, 1, 0, 1}                                            // Color
        );

        // End rendering the frame
        render_end();
    }

    return 0;
}
