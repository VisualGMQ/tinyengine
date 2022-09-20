#include "2d_draw.hpp"

void Draw2DBehavior::OnInit() {
    font_ = engine::FontFactory::Find("arial");
}

void Draw2DBehavior::OnUpdate() {
    engine::Renderer::SetDrawColor(engine::Color(0, 1, 0));
    engine::Renderer::DrawRect(engine::Rect(100, 100, 200, 300));
    engine::Renderer::SetDrawColor(engine::Color(0, 0, 1));
    engine::Renderer::FillRect(engine::Rect(100, 500, 200, 100));
    engine::Renderer::DrawLines({engine::Vec2(100, 100), engine::Vec2(200, 150), engine::Vec2(300, 400)});

    engine::Renderer::SetDrawColor(engine::Color(1, 1, 1));
    engine::Renderer::DrawText(font_, "VisualGMQ made for 1MGames", engine::Vec2(500, 0));
}

void Draw2DBehavior::OnQuit() {

}