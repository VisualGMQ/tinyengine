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
    engine::World* world = engine::World::Instance();

    auto windowEntity = world->CreateEntity("WindowEntity");
    auto uiwindow = world->CreateComponent<engine::UIWindow>();
    windowEntity->SetComponent(uiwindow);
    uiwindow->title = "Demo";
    uiwindow->rect.position.Set(50, 50);
    uiwindow->rect.size.Set(230, 250);
    uiwindow->flags = NK_WINDOW_BORDER | NK_WINDOW_MOVABLE | NK_WINDOW_SCALABLE |
                        NK_WINDOW_MINIMIZABLE | NK_WINDOW_TITLE;
    auto node = world->CreateComponent<engine::NodeComponent>();
    windowEntity->SetComponent(node);
    AttachUI(windowEntity);

    auto layout = world->CreateEntity("layout");
    auto rowLayout = world->CreateComponent<engine::UIDynamicRowLayout>();
    auto layoutNode = world->CreateComponent<engine::NodeComponent>();
    rowLayout->cols = 2;
    rowLayout->height = 50;
    layout->SetComponent(rowLayout);
    layout->SetComponent(layoutNode);

    node->Attach(layout);

    auto buttonEntity = world->CreateEntity("button");
    auto button = world->CreateComponent<engine::UIButton>();
    button->text = "button";
    buttonEntity->SetComponent(button);
    layoutNode->Attach(buttonEntity);

    auto checkboxEntity = world->CreateEntity("checkbox");
    auto checkbox = world->CreateComponent<engine::UICheckbox>();
    checkbox->text = "checkbox 1";
    checkbox->isSelected = false;
    checkbox->callback = [](engine::Entity* self) {
        Logt("clicked checkbox");
        auto& select = self->GetComponent<engine::UICheckbox>()->isSelected;
        select = !select;
    };
    checkboxEntity->SetComponent(checkbox);
    layoutNode->Attach(checkboxEntity);


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

    auto node3D = world->CreateEntity("3d node");
    node3D->SetBehavior(std::make_unique<Draw3DBehavior>());
    Attach3D(node3D);

    auto node2D = world->CreateEntity("2d node");
    node2D->SetBehavior(std::make_unique<Draw2DBehavior>());
    Attach2D(node2D);

    auto nodeSound = world->CreateEntity("sound node");
    nodeSound->SetBehavior(std::make_unique<SoundBehavior>());
    Attach(nodeSound);
}