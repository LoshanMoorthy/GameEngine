#include <glad/glad.h>
#include <SDL2/SDL.h>

#include "../util.h"
#include "../global.h"
#include "render.h"
#include "render_internal.h"

// Function to initialize an SDL window with an OpenGL context
SDL_Window *render_init_window(u32 width, u32 height)
{
    // TODO: Create a window - Done
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 3);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 3);

    if (SDL_Init(SDL_INIT_VIDEO) < 0)
    {
        ERROR_EXIT("Could not initialize SDL: %s\n", SDL_GetError());
    }

    // Create an SDL window
    SDL_Window *window = SDL_CreateWindow(
        "Game",
        SDL_WINDOWPOS_CENTERED,
        SDL_WINDOWPOS_CENTERED,
        800,
        600,
        SDL_WINDOW_OPENGL
    );

    if (!window)
    {
        ERROR_EXIT("Failed to initialize window: %s\n", SDL_GetError());
    }

    // Create an OpenGL context for the window
    SDL_GL_CreateContext(window);

    // Load OpenGL function pointers with GLAD
    if (!gladLoadGLLoader((GLADloadproc)SDL_GL_GetProcAddress))
    {
        ERROR_EXIT("Failed to load OpenGL functions: %s\n", SDL_GetError());
    }

    puts("OpenGL Loaded");
    printf("Vendor:     %s\n", glGetString(GL_VENDOR));
    printf("Renderer:   %s\n", glGetString(GL_RENDERER));
    printf("Version:    %s\n", glGetString(GL_VERSION));

    return window;
}

// Function to initialize shaders and projection matrix for rendering
void render_init_shaders(Render_State_Internal *state)
{
    // Create the default shader program
    state->shader_default = render_shader_create("./shaders/default.vert", "./shaders/default.frag");

    // Create an orthographic projection matrix based on window dimensions
    mat4x4_ortho(state->projection, 0, global.render.width, 0, global.render.height, -2, 2);

    // Use the default shader program for rendering
    glUseProgram(state->shader_default);

    // Set the projection matrix uniform in the shader
    glUniformMatrix4fv(
        glGetUniformLocation(state->shader_default, "projection"),
        1,              // Count (1 matrix)
        GL_FALSE,        // Transpose (no)
        &state->projection[0][0] // Pointer to the matrix data
    );
}

// Function to initialize a color texture
void render_init_color_texture(u32 *texture)
{
    // Generate a texture object
    glGenTextures(1, texture);
    // Bind the texture to the GL_TEXTURE_2D target
    glBindTexture(GL_TEXTURE_2D, *texture);

    // Define a solid white texture (1x1 pixel)
    u8 solid_white[4] = {255, 255, 255, 255};
    // Upload the texture data to the GPU
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, 1, 1, 0, GL_RGBA, GL_UNSIGNED_BYTE, solid_white);

    // Unbind the texture
    glBindTexture(GL_TEXTURE_2D, 0);
}

// Function to initialize a vertex array object, vertex buffer object, and element buffer object for rendering a quad
void render_init_quad(u32 *vao, u32 *vbo, u32 *ebo)
{
    // TODO: Initialize vertex and index buffers for a quad - Done
    f32 vertices[] =
    {
        0.5,  0.5, 0, 0, 0,
        0.5, -0.5, 0, 0, 1,
       -0.5, -0.5, 0, 1, 1,
       -0.5,  0.5, 0, 1, 0
    };

    u32 indices[] =
    {
        0, 1, 3,
        1, 2, 3
    };

    // Generate and bind OpenGL objects for the quad
    glGenVertexArrays(1, vao);
    glGenBuffers(1, vbo);
    glGenBuffers(1, ebo);

    glBindVertexArray(*vao);

    glBindBuffer(GL_ARRAY_BUFFER, *vbo);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, *ebo);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

    // Specify vertex attributes
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(f32), NULL);
    glEnableVertexAttribArray(0);

    glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(f32), (void*)(3 * sizeof(f32)));
    glad_glEnableVertexAttribArray(1);
}