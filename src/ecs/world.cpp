#include "engine/ecs/world.hpp"
#include "engine/ecs/component.hpp"
#include "engine/ecs/entity.hpp"
#include "engine/core/scene.hpp"
#include "engine/ui/ui_system.hpp"
#include "engine/components/node.hpp"
#include "engine/renderer/render_system.hpp"
#include "engine/components/sprite.hpp"
#include "engine/physics/physics_system.hpp"
#include "engine/debug/collider_outline.hpp"
#include "engine/core/init_config.hpp"

namespace engine {

std::unique_ptr<World> World::instance_;

World::World() {
    uiSystem_ = new UISystem(this);
    AddSystem<PhysicsSystem>();
    CollideSystem* collideSystem = (CollideSystem*)AddSystem<CollideSystem>();
    AddSystem<ColliderCollectSystem>(collideSystem);
    AddSystem<RenderSystem>();
    if (InitConfig::Instance().IsDrawColliderOutline()) {
        AddSystem<debug::ColliderOutlineSystem>();
    }
}

World::~World() {
    delete uiSystem_;
}

World* World::Instance() {
    if (!instance_) {
        instance_ = std::make_unique<World>();
    }
    return instance_.get();
}

void World::Init() {
}

void World::Quit() {
    instance_.reset();
}

Entity* World::CreateEntity(const std::string& name) {
    if (entityTrashes_.empty()) {
        entities_.push_back(std::make_unique<Entity>(this, entityID_++, name));
        return entities_.back().get();
    } else {
        std::unique_ptr<Entity> entity = std::move(entityTrashes_.top());
        entity->components_.clear();
        entity->id_ = entityID_++;
        entity->name_ = name;
        entity->shouldBeCleanUp_ = false;
        entities_.push_back(std::move(entity));
        entityTrashes_.pop();
        return entities_.back().get();
    }
}

void World::DestroyEntity(EntityID id) {
    auto it = entities_.begin();
    while (it != entities_.end() && (*it)->ID() != id) {
        it++;
    }
    if (it != entities_.end()) {
        destroyEntity(it);
    }
}

void World::DestroyEntity(Entity* entity) {
    if (!entity) return;

    auto it = entities_.begin();
    while (it != entities_.end() && (*it)->ID() != entity->ID()) {
        it++;
    }
    if (it != entities_.end()) {
        destroyEntity(it);
    }
}

void World::destroyEntity(const std::vector<std::unique_ptr<Entity>>::const_iterator& it) {
    (*it)->shouldBeCleanUp_ = true;
}

void World::RemoveComponent(Component* component) {
    if(!component) return;

    for (auto& [id, info] : components_) {
        auto it = info.components.begin(); 
        while (it != info.components.end() && (*it)->ID() != component->ID()) {
            it++;
        }
        if (it != info.components.end()) {
            info.componentTrashes_.push(std::move(*it));
            info.componentTrashes_.top()->Reset();
            info.components.erase(it);
        }
    }
}

void World::TryInitEntities() {
    auto scene = SceneMgr::CurrentScene();
    if (!scene) return;
    auto node = scene->GetRootEntity()->GetComponent<NodeComponent>();

    for (auto& entity : node->children) {
        initEntity(entity);
    }
}

void World::initEntity(Entity* entity) {
    if (auto behavior = entity->GetBehavior(); behavior != nullptr) {
        if (!behavior->IsInited()) {
            behavior->OnInit();
            behavior->Inited();
        }
    }

    if (auto node = entity->GetComponent<NodeComponent>(); node != nullptr) {
        for (auto& ent : node->children) {
            initEntity(ent);
        }
    }
    if (auto node = entity->GetComponent<Node2DComponent>(); node != nullptr) {
        for (auto& ent : node->children) {
            initEntity(ent);
        }
    }
}

void World::Update() {
    auto scene = SceneMgr::CurrentScene();
    if (!scene) return;
    auto node = scene->GetRootEntity()->GetComponent<NodeComponent>();

    for (auto& entity : node->children) {
        updateEntity(entity);
    }
 
    for (auto& entity : node->children) {
        if (entity->GetComponent<NodeUIRoot>()) {
            updateUIEntity(entity);
        }
    }

    for (auto& system : PerFrameSystems()) {
        system->Update();
    }

    auto& eventDispatcher = Event::GetDispatcher();
    if (!eventDispatcher.IsEventedTriggedOnUI()) {
        for (auto& entity : node->children) {
            if (!entity->GetComponent<NodeUIRoot>()) {
                dispatchEvent2Entity(entity);
            }
        }
    }
}

void World::updateEntity(Entity* entity) {
    if (!entity || !entity->IsActive()) return;

    if (auto node = entity->GetComponent<Node2DRoot>(); node && node->IsActive()) {
        Renderer::Begin2D();
    }
    if (auto node = entity->GetComponent<Node3DRoot>(); node && node->IsActive()) {
        Renderer::Begin3D();
    }

    auto& systems = World::Instance()->EntityUpdateSystems();
    if (auto behavior = entity->GetBehavior(); behavior != nullptr) {
        behavior->OnUpdate();
    }
    for (auto& system : systems) {
        if (system->GetType() == System::Type::UpdateEachEntity) {
           system->Update(entity);
        }
    }

    if (auto node = entity->GetComponent<NodeComponent>(); node != nullptr) {
        for (auto& ent : node->children) {
            updateEntity(ent);
        }
    }
    if (auto node = entity->GetComponent<Node2DComponent>(); node != nullptr) {
        for (auto& ent : node->children) {
            updateEntity(ent);
        }
    }
}

void World::updateUIEntity(Entity* entity) {
    if (!entity || !entity->IsActive()) return;

    auto windowState = uiSystem_->BeginContainer(entity);
    uiSystem_->Update(entity);

    if (!windowState.has_value() || windowState.value() == true) {
        if (auto node = entity->GetComponent<NodeComponent>(); node != nullptr) {
            for (auto& ent : node->children) {
                updateUIEntity(ent);
            }
        }
        if (auto node = entity->GetComponent<Node2DComponent>(); node != nullptr) {
            for (auto& ent : node->children) {
                updateUIEntity(ent);
            }
        }
    }
    if (windowState.has_value()) {
        uiSystem_->EndContainer(entity, windowState.value());
    }
}

void World::dispatchEvent2Entity(Entity* entity) {
    if (!entity || !entity->IsActive()) return;

    if (entity->GetBehavior()) {
        Event::GetDispatcher().Dispatch(entity->GetBehavior());
    }
    if (auto node = entity->GetComponent<NodeComponent>(); node) {
        for (auto& child : node->children) {
            dispatchEvent2Entity(child);
        }
    }
    if (auto node = entity->GetComponent<Node2DComponent>(); node) {
        for (auto& child : node->children) {
            dispatchEvent2Entity(child);
        }
    }
}

void World::CleanUp() {
    size_t idx = 0;
    while (idx < entities_.size()) {
        if (entities_[idx]->shouldBeCleanUp_) {
            for (auto& component : entities_[idx]->components_) {
                RemoveComponent(component.second);
            }
            entities_[idx]->components_.clear();
            if (entities_[idx]->behavior_) {
                entities_[idx]->behavior_->OnQuit();
            }
            entities_.erase(entities_.begin() + idx);
        } else {
            idx++;
        }
    }
}

void World::RemoveSystem(System* system) {
    if (!system) return;

    if (system->GetType() ==  System::Type::UpdateOncePerFrame) {
        removePerFrameSystem((PerFrameSystem*) system);
    } else {
        removeEntityUpdateSystem((EntityUpdateSystem*) system);
    }

}

void World::removePerFrameSystem(PerFrameSystem* system) {
    auto it = perFrameSystems_.begin();
    while (it != perFrameSystems_.end() && it->get() != system) {
        it ++;
    }
    if (it != perFrameSystems_.end()) {
        perFrameSystems_.erase(it);
    }

}

void World::removeEntityUpdateSystem(EntityUpdateSystem* system) {
    auto it = updateEntitySystems_.begin();
    while (it != updateEntitySystems_.end() && it->get() != system) {
        it ++;
    }
    if (it != updateEntitySystems_.end()) {
        updateEntitySystems_.erase(it);
    }
}

void World::Shutdown() {
    for (auto it = entities_.begin(); it != entities_.end(); it++) {
        destroyEntity(it);
    }
    CleanUp();
}

}
