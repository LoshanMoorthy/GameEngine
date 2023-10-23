#include <glad/glad.h>

#include "../global.h"
#include "render.h"
#include "render_internal.h"

// Initialize the rendering state
static Render_State_Internal state = {0};

// Initialize the rendering subsystem
void render_init(void) 
{
    // Set initial window dimensions
    global.render.width = 800;
    global.render.height = 600;

    // Create an SDL window and OpenGL context
    global.render.window = render_init_window(global.render.width, global.render.height);

    // Initialize shaders, quad, and color texture
    render_init_shaders(&state);
    render_init_quad(&state.vao_quad, &state.vbo_quad, &state.ebo_quad);
    render_init_color_texture(&state.texture_color);
}

// Prepare for rendering by clearing the color buffer
void render_begin(void) 
{
    // Set the clear color (background color) and clear the buffer
    glClearColor(0.08, 0.1, 0.1, 1);
    glClear(GL_COLOR_BUFFER_BIT);
}

// Finalize rendering by swapping the window buffer
void render_end(void) 
{
    // Swap the front and back buffers to display the rendered frame
    SDL_GL_SwapWindow(global.render.window);
}

// Render a colored quad with position, size, and color
void render_quad(vec2 pos, vec2 size, vec4 color) 
{
    // Use the default shader program
    glUseProgram(state.shader_default);

    // Create a model matrix for the quad
    mat4x4 model;
    mat4x4_identity(model);
    mat4x4_translate(model, pos[0], pos[1], 0);
    mat4x4_scale_aniso(model, model, size[0], size[1], 1);

    // Set the model matrix and color uniform in the shader
    glUniformMatrix4fv(glGetUniformLocation(state.shader_default, "model"), 1, GL_FALSE, &model[0][0]);
    glUniform4fv(glGetUniformLocation(state.shader_default, "color"), 1, color);

    // Bind the quad's vertex array object and draw
    glBindVertexArray(state.vao_quad);
    glBindTexture(GL_TEXTURE_2D, state.texture_color);
    glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, NULL);
    glBindVertexArray(0);
}