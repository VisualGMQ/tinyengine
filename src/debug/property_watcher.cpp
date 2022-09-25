#include "engine/debug/property_watcher.hpp"

namespace engine::debug {

#define WATCHER_WINDOW_NAME "Debug::PropertyWatcher::Window"
#define WATCHER_LAYOUT_NAME "Debug::PropertyWatcher::layout"
#define WATCHER_NODE2D_LABEL_NAME "Debug::PropertyWatcher::Node2DLabel"
#define WATCHER_POSX_NAME "Debug::PropertyWatcher::PosX"
#define WATCHER_POSY_NAME "Debug::PropertyWatcher::PosY"
#define WATCHER_ROTATION_NAME "Debug::PropertyWatcher::Rotation"
#define WATCHER_SCALEX_NAME "Debug::PropertyWatcer::ScaleX"
#define WATCHER_SCALEY_NAME "Debug::PropertyWatcer::ScaleY"
#define WATCHER_ZINDEX_NAME "Debug::PropertyWatcer::ZIndex"

Entity* PropertyWatcher::entity_ = nullptr;
Entity* PropertyWatcher::watchedEntity_ = nullptr;
PropertyWatcher::WatcherBehavior* PropertyWatcher::behavior_ = nullptr;

void PropertyWatcher::Attach2Scene() {
    auto world = engine::World::Instance();

    entity_ = world->CreateEntity("Debug::PropertyWatcher::Entity");
    entity_->SetBehavior(std::make_unique<PropertyWatcher::WatcherBehavior>());
    auto behavior = (WatcherBehavior*)entity_->GetBehavior();
    SceneMgr::CurrentScene()->Attach2D(entity_);

    auto window = engine::CreateUIWindow(WATCHER_WINDOW_NAME, "Property Watcher",
                                         NK_WINDOW_MINIMIZABLE|NK_WINDOW_MOVABLE|NK_WINDOW_SCALABLE,
                                         Rect(400, 100, 200, 400));
    auto layout = engine::CreateUIDynamicRowLayout(WATCHER_LAYOUT_NAME, 25, 1, window);
    auto windowSize = Video::GetWindowSize();
    engine::CreateUILabel(WATCHER_NODE2D_LABEL_NAME, "node2d", NK_TEXT_ALIGN_LEFT, layout);
    behavior->posX = engine::CreateUIProperty(WATCHER_POSX_NAME, "pos x",
                                              [](Entity*, UIProperty* self) {
                                                if (!watchedEntity_) return;
                                                auto node2d = watchedEntity_->GetComponent<Node2DComponent>();
                                                if (!node2d) return;
                                                node2d->position.x = self->Value();
                                              },
                                              engine::UIProperty::Type::Float, 0, windowSize.w,
                                              0, 1, 1,
                                              layout)->GetComponent<UIProperty>();
    behavior->posY = CreateUIProperty(WATCHER_POSY_NAME, "pos y",
                                      [](Entity*, UIProperty* self) {
                                          if (!watchedEntity_) return;
                                          auto node2d = watchedEntity_->GetComponent<Node2DComponent>();
                                          if (!node2d) return;
                                          node2d->position.y = self->Value();
                                      },
                                      engine::UIProperty::Type::Float, 0, windowSize.h,
                                      0, 1, 1,
                                      layout)->GetComponent<UIProperty>();
    behavior->rotation = CreateUIProperty(WATCHER_ROTATION_NAME, "rotation",
                                          [](Entity*, UIProperty* self) {
                                              if (!watchedEntity_) return;
                                              auto node2d = watchedEntity_->GetComponent<Node2DComponent>();
                                              if (!node2d) return;
                                              node2d->rotation = Radians(self->Value());
                                          },
                                          engine::UIProperty::Type::Float, 0, 360,
                                          0, 1, 1,
                                          layout)->GetComponent<UIProperty>();
    behavior->scaleX = CreateUIProperty(WATCHER_SCALEX_NAME, "scale x",
                                        [](Entity*, UIProperty* self) {
                                            if (!watchedEntity_) return;
                                            auto node2d = watchedEntity_->GetComponent<Node2DComponent>();
                                            if (!node2d) return;
                                            node2d->scale.x = self->Value();
                                        },
                                        engine::UIProperty::Type::Float, -100, 100,
                                        0, 1, 1,
                                        layout)->GetComponent<UIProperty>();
    behavior->scaleY = CreateUIProperty(WATCHER_SCALEY_NAME, "scale y",
                                        [](Entity*, UIProperty* self) {
                                            if (!watchedEntity_) return;
                                            auto node2d = watchedEntity_->GetComponent<Node2DComponent>();
                                            if (!node2d) return;
                                            node2d->scale.y = self->Value();
                                        },
                                        engine::UIProperty::Type::Float, -100, 100,
                                        0, 1, 1,
                                        layout)->GetComponent<UIProperty>();
    behavior->zIndex = CreateUIProperty(WATCHER_ZINDEX_NAME, "z index",
                                        [](Entity*, UIProperty* self) {
                                            if (!watchedEntity_) return;
                                            auto node2d = watchedEntity_->GetComponent<Node2DComponent>();
                                            if (!node2d) return;
                                            node2d->zIndex = self->Value();
                                        },
                                        engine::UIProperty::Type::Float, -1, 1,
                                        0, 0.01, 0.01,
                                        layout)->GetComponent<UIProperty>();

    SceneMgr::CurrentScene()->AttachUI(window);
}

void PropertyWatcher::SetWatchEntity(Entity* entity) {
    watchedEntity_ = entity;
    if (auto node = entity->GetComponent<Node2DComponent>(); node && behavior_) {
        behavior_->node2d = node;
    }
}

void PropertyWatcher::WatcherBehavior::OnInit() {
}

void PropertyWatcher::WatcherBehavior::OnQuit() {
}

void PropertyWatcher::WatcherBehavior::OnUpdate() {
    if (!watchedEntity_) return;

    auto node2d = watchedEntity_->GetComponent<Node2DComponent>();
    if (!node2d) return;

    posX->fvalue = node2d->position.x;
    posY->fvalue = node2d->position.y;
    scaleX->fvalue = node2d->scale.x;
    scaleY->fvalue = node2d->scale.y;
    rotation->fvalue = Degrees(node2d->rotation);
}

}
