#include "2d_draw.hpp"

void Draw2DBehavior::OnInit() {
    tilesheet_.reset(new engine::TileSheet("tilesheet", 3, 13));
    tile1_ = tilesheet_->Get(0, 1);
    tile2_ = tilesheet_->Get(0, 2);
    tile3_ = tilesheet_->Get(0, 3);
    cppImage_.reset(new engine::Image(engine::TextureFactory::Find("test")));
    font_ = engine::FontFactory::Find("arial");
}

void Draw2DBehavior::OnUpdate() {
    engine::Renderer::SetDrawColor(engine::Color(0, 1, 0));
    engine::Renderer::DrawRect(engine::Rect(100, 100, 200, 300));
    engine::Renderer::SetDrawColor(engine::Color(0, 0, 1));
    engine::Renderer::FillRect(engine::Rect(100, 500, 200, 100));
    engine::Renderer::DrawLines({engine::Vec2(100, 100), engine::Vec2(200, 150), engine::Vec2(300, 400)});

    engine::Renderer::SetDrawColor(engine::Color(1, 1, 1));
    tile1_->SetPosition(engine::Vec2(300, 300));
    tile1_->Draw();
    tile2_->SetPosition(engine::Vec2(350, 300));
    tile2_->Draw();
    tile3_->SetPosition(engine::Vec2(400, 300));
    tile3_->Draw();

    engine::Renderer::SetDrawColor(engine::Color(1, 1, 1));
    cppImage_->SetPosition(engine::Vec2(400, 100));
    cppImage_->Draw();

    engine::Renderer::SetDrawColor(engine::Color(1, 1, 1));
    engine::Renderer::DrawText(font_, "VisualGMQ made for 1MGames", engine::Vec2(500, 0));
}

void Draw2DBehavior::OnQuit() {

}