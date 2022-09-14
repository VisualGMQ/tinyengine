#include "engine/core/scene.hpp"

namespace engine {

Scene* SceneMgr::curScene_ = nullptr;
Scene* SceneMgr::oldScene_ = nullptr;
std::unordered_map<std::string, std::unique_ptr<Scene>> SceneMgr::scenes_;

Scene::Scene(const std::string& name): name_(name) {
    root_ = World::Instance()->CreateEntity(name + " root");
    root_->SetComponent<NodeComponent>(World::Instance()->CreateComponent<NodeComponent>());
}

void SceneMgr::Init() {}

void SceneMgr::Quit() {
    if (curScene_) {
        curScene_->OnQuit();
    }
}

void Scene::Attach(Entity* entity) {
    auto node = root_->GetComponent<NodeComponent>();
    node->children.push_back(entity);
}

void SceneMgr::ChangeScene(const std::string& name) {
    auto it = scenes_.find(name);
    oldScene_ = curScene_;
    if (it == scenes_.end()) {
        Logw("scene {} not exists", name.c_str());
        curScene_ = nullptr;
    } else {
        curScene_ = it->second.get();
        curScene_->OnInit();
    }
}

void SceneMgr::QuitOldScene() {
    if (oldScene_) {
        oldScene_->OnQuit();
    } else {
        return;
    }

    static std::queue<Entity*> entityQueue;
    while (entityQueue.size() > 0) entityQueue.pop();

    if (auto node = oldScene_->root_->GetComponent<NodeComponent>(); node != nullptr) {
        for (auto& entity : node->children) {
            entityQueue.push(entity);
        }
        node->children.clear();
    } else {
        return;
    }

    if (entityQueue.empty()) return;

    Entity* entity = entityQueue.front();
    entityQueue.pop();
    while (!entityQueue.empty()) {
        if (auto node = entity->GetComponent<NodeComponent>(); node != nullptr && !node->children.empty()) {
            for (auto& entity : node->children) {
                entityQueue.push(entity);
            }
        }
        World::Instance()->DestroyEntity(entity);
        entity = entityQueue.front();
        entityQueue.pop();
    }
    World::Instance()->DestroyEntity(entity);
}

}