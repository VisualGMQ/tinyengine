#include "engine/renderer/renderer.hpp"

namespace engine {

void Renderer::SetClearColor(const Color& color) {
    glClearColor(color.r, color.g, color.b, color.a);
}

void Renderer::Clear() {
    glClear(GL_COLOR_BUFFER_BIT);
}

}