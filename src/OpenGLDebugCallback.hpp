#pragma once

#include "OpenGLHeaders.hpp"

namespace pong {

    void gl_debug_callback(GLenum source,
                           GLenum type,
                           GLuint id,
                           GLenum severity,
                           GLsizei length,
                           const GLchar* message,
                           const void* userParam);

}
