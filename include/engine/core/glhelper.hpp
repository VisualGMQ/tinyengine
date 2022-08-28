#pragma once

#include "engine/core/log.hpp"
#include "engine/core/pch.hpp"

#define GL_CALL_MAX_LOOP 10000

namespace engine {

const char* GLGetErrorString(GLenum);
inline void GLClearError() {
    while (glGetError() != GL_NO_ERROR) {}
}

#define GL_CALL(statement) do { \
    engine::GLClearError(); \
    statement; \
    GLenum ___err_inner_use = glGetError(); \
    int loop = 0; \
    if (loop < GL_CALL_MAX_LOOP && ___err_inner_use != GL_NO_ERROR) { Loge("OpenGL Error: %s", engine::GLGetErrorString(___err_inner_use)); loop++; } \
} while(0)

}
