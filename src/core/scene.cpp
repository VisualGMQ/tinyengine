#include "engine/core/scene.hpp"

namespace engine {

Scene* SceneMgr::curScene_ = nullptr;
Scene* SceneMgr::oldScene_ = nullptr;
std::unordered_map<std::string, std::unique_ptr<Scene>> SceneMgr::scenes_;

Scene::Scene(const std::string& name): name_(name) {
    auto world = World::Instance();
    root_ = world->CreateEntity(name + " root");
    auto node = World::Instance()->CreateComponent<NodeComponent>();
    root_->SetComponent<NodeComponent>(node);

    node2d_ = world->CreateEntity(name + " 2d root");
    node2d_->SetComponent(world->CreateComponent<NodeComponent>());
    node2d_->SetComponent(world->CreateComponent<Node2DRoot>());

    node3d_ = world->CreateEntity(name + " 3d root");
    node3d_->SetComponent(world->CreateComponent<NodeComponent>());
    node3d_->SetComponent(world->CreateComponent<Node3DRoot>());

    nodeUI_ = world->CreateEntity(name + " ui root");
    nodeUI_ ->SetComponent(world->CreateComponent<NodeComponent>());
    nodeUI_->SetComponent(world->CreateComponent<NodeUIRoot>());

    Attach(node3d_);
    Attach(node2d_);
    Attach(nodeUI_);
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

void Scene::Attach2D(Entity* entity) {
    node2d_->GetComponent<NodeComponent>()->Attach(entity);
}

void Scene::Attach3D(Entity* entity) {
    node3d_->GetComponent<NodeComponent>()->Attach(entity);
}

void Scene::AttachUI(Entity* entity) {
    nodeUI_->GetComponent<NodeComponent>()->Attach(entity);
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