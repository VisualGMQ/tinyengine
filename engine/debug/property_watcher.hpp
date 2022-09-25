#pragma once

#include "engine/ecs/component.hpp"
#include "engine/core/scene.hpp"
#include "engine/ui/tree.hpp"
#include "engine/ui/button.hpp"
#include "engine/ui/window.hpp"
#include "engine/ui/layout.hpp"
#include "engine/ui/property.hpp"
#include "engine/ui/label.hpp"
#include "engine/components/node.hpp"
#include "engine/ecs/behavior.hpp"
#include "engine/core/video.hpp"

namespace engine::debug {

class PropertyWatcher final {
public:
    static void Attach2Scene();
    static void SetWatchEntity(Entity* entity);
    static Entity* GetWatchedEntity() { return watchedEntity_; }

private:
    static Entity* entity_ ;
    static Entity* watchedEntity_;

    class WatcherBehavior: public Behavior {
    public:
        void OnInit() override;
        void OnQuit() override;
        void OnUpdate() override;

        Node2DComponent* node2d = nullptr;
        UIProperty* posX;
        UIProperty* posY;
        UIProperty* scaleX;
        UIProperty* scaleY;
        UIProperty* rotation;
        UIProperty* zIndex;
    };

    static WatcherBehavior* behavior_;
};

}
