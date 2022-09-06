#include "engine/ecs/world.hpp"
#include "engine/ecs/component.hpp"
#include "engine/ecs/entity.hpp"
#include "engine/core/scene.hpp"

namespace engine {

std::unique_ptr<World> World::instance_;

World* World::Instance() {
    if (!instance_) {
        instance_ = std::make_unique<World>();
    }
    return instance_.get();
}

void World::Init() { }

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
    auto it = entities_.begin();
    while (it != entities_.end() && (*it)->ID() != entity->ID()) {
        it++;
    }
    if (it != entities_.end()) {
        destroyEntity(it);
    }
}

void World::destroyEntity(const std::vector<std::unique_ptr<Entity>>::const_iterator& it) {
    auto& entity = *it;
    entity->shouldBeCleanUp_ = true;
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
}

void World::Update() {
    auto scene = SceneMgr::CurrentScene();
    if (!scene) return;
    auto node = scene->GetRootEntity()->GetComponent<NodeComponent>();

    for (auto& entity : node->children) {
        updateEntity(entity);
    }
}

void World::updateEntity(Entity* entity) {
    if (!entity) return;

    auto& systems = World::Instance()->Systems();
    if (auto behavior = entity->GetBehavior(); behavior != nullptr) {
        behavior->OnUpdate();
    }
    for (auto& system : systems) {
        system->Update(entity);
    }

    if (auto node = entity->GetComponent<NodeComponent>(); node != nullptr) {
        for (auto& ent : node->children) {
            updateEntity(ent);
        }
    }
}


void World::CleanUp() {
    size_t idx = 0;
    while (idx < entities_.size()) {
        if (entities_[idx]->shouldBeCleanUp_) {
            for (auto& component : entities_[idx]->components_) {
                component.second->OnQuit();
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
    auto it = systems_.begin();
    while (it != systems_.end() && it->get() != system) {
        it ++;
    }
    if (it != systems_.end()) {
        systems_.erase(it);
    }
}

void World::Shutdown() {
    for (auto it = entities_.begin(); it != entities_.end(); it++) {
        destroyEntity(it);
    }
    CleanUp();
}

}
