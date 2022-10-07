#include "gamestart.hpp"
#include "2d_draw.hpp"
#include "3d_draw.hpp"
#include "sound_play.hpp"

void GameStart::OnInit() {
    auto camera = engine::Renderer::GetPerspCamera();
    camera->MoveFront(-100);
    engine::Renderer::GetPerspCamera()->MoveTo(engine::Vec3(0, 1, 1));

    loadResources();
    initUI();
    initOtherNode();
}

void GameStart::initUI() {
    auto window = engine::CreateUIWindow("window", "demo",
                                         NK_WINDOW_TITLE|NK_WINDOW_MOVABLE|NK_WINDOW_SCALABLE,
                                         engine::Rect(50, 50, 230, 300));
    AttachUI(window);

    auto windowLayout = engine::CreateUIDynamicRowLayout("window layout", 50, 2, window);

    engine::CreateUIButton("button", "button", nullptr, nullptr, windowLayout);
    engine::CreateUICheckbox("checkbox", "checkbox", nullptr, windowLayout);
    engine::CreateUIEdit("edit", NK_EDIT_FIELD, 1023, nk_filter_ascii, windowLayout);
    engine::CreateUIText("edit", "text", NK_TEXT_ALIGN_LEFT, windowLayout);
    engine::CreateUIProperty("value", "int value",
                             nullptr,
                             engine::UIProperty::Type::Int,
                             0, 100, 20,
                             1, 1, windowLayout);

    auto tree = engine::CreateUITreeTab("scene tree", "root tree", NK_MINIMIZED, windowLayout);
    engine::CreateUITreeNode("node1", "node1", NK_MINIMIZED, tree);
    engine::CreateUITreeNode("node2", "node2", NK_MINIMIZED, tree);
    auto texture = engine::TextureFactory::Find("tilesheet");
    engine::CreateUIRowLayout("row layout", NK_DYNAMIC, texture->Height(), {1}, windowLayout);
    engine::CreateUIImage("image",
                          texture,
                          texture->Width(), texture->Height(),
                          engine::Rect(0, 0, texture->Width(), texture->Height()),
                          engine::Color(1, 1, 1),
                          windowLayout);
}

void GameStart::loadResources() {
    engine::TextureFactory::Create("./resources/tilesheet.png", "tilesheet");
    engine::TextureFactory::Create("./resources/test.jpg", "test");
    engine::SoundFactory::Load("resources/test1.wav", "test1");
    engine::SoundFactory::Load("resources/test2.wav", "test2");
    font_ = engine::FontFactory::Create("C:/windows/fonts/arial.ttf", "arial", 20);
}

void GameStart::initOtherNode() {
    auto world = engine::World::Instance();

    auto node3D = world->CreateEntity<engine::NodeComponent>("3d node");
    node3D->SetBehavior(std::make_unique<Draw3DBehavior>());
    Attach3D(node3D);

    auto node2D = world->CreateEntity<engine::Node2DComponent>("2d node");
    node2D->SetBehavior(std::make_unique<Draw2DBehavior>());
    Attach2D(node2D);

    auto nodeSound = world->CreateEntity<engine::NodeComponent>("sound node");
    nodeSound->SetBehavior(std::make_unique<SoundBehavior>());
    Attach(nodeSound);
    
    auto image = world->CreateEntity<engine::SpriteComponent, engine::Node2DComponent>("image");
    auto sprite = image->GetComponent<engine::SpriteComponent>();
    auto node = image->GetComponent<engine::Node2DComponent>();
    auto tilesheet = engine::TileSheetFactory::Create("tilesheet", engine::TextureFactory::Find("tilesheet"), 3, 13);
    auto tile = tilesheet->Get(0, 0);
    sprite->image.texture = tile.texture;
    sprite->image.region = tilesheet->Get(0, 0).region;
    sprite->offset.Set(tilesheet->TileSize().w / 2.0, tilesheet->TileSize().h / 2.0);
    node->position.Set(600, 100);
    Attach2D(image);
}
