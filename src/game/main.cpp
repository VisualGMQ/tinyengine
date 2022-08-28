#include "engine/core/log.hpp"
#include "engine/input/input.hpp"
#include "engine/renderer/renderer.hpp"
#include "engine/renderer/shader.hpp"
#include "engine/core/glhelper.hpp"

void GameInit(void) {
}

void GameLoop(void) {
    engine::Renderer::SetDrawColor(engine::Color(1, 0, 0, 1));
    engine::Renderer::DrawLine(engine::Vec2(0, 0), engine::Vec2(1024, 720));
    engine::Renderer::SetDrawColor(engine::Color(0, 1, 0, 1));
    engine::Renderer::DrawRect(engine::Rect(100, 100, 200, 300));
    engine::Renderer::SetDrawColor(engine::Color(0, 0, 1, 1));
    engine::Renderer::FillRect(engine::Rect(100, 500, 200, 300));
    engine::Renderer::DrawLines({engine::Vec2(100, 100), engine::Vec2(200, 150), engine::Vec2(300, 400)});
}

void GameQuit(void) {
}
