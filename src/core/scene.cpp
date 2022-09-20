#include "engine/core/scene.hpp"

namespace engine {

Scene* SceneMgr::curScene_ = nullptr;
Scene* SceneMgr::oldScene_ = nullptr;
std::unordered_map<std::string, std::unique_ptr<Scene>> SceneMgr::scenes_;

Scene::Scene(const std::string& name): name_(name) {
}

void Scene::beforeInit() {
    auto world = World::Instance();
    root_ = world->CreateEntity(name_ + " root");
    auto node = World::Instance()->CreateComponent<NodeComponent>();
    root_->SetComponent<NodeComponent>(node);

    node2d_ = world->CreateEntity(name_ + " 2d root");
    node2d_->SetComponent(world->CreateComponent<NodeComponent>());
    node2d_->SetComponent(world->CreateComponent<Node2DRoot>());

    node3d_ = world->CreateEntity(name_ + " 3d root");
    node3d_->SetComponent(world->CreateComponent<NodeComponent>());
    node3d_->SetComponent(world->CreateComponent<Node3DRoot>());

    nodeUI_ = world->CreateEntity(name_ + " ui root");
    nodeUI_ ->SetComponent(world->CreateComponent<NodeComponent>());
    nodeUI_->SetComponent(world->CreateComponent<NodeUIRoot>());

    Attach(node3d_);
    Attach(node2d_);
    Attach(nodeUI_);
}

void Scene::beforeQuit() {
    if (root_) {
        World::Instance()->DestroyEntity(root_);
        root_ = nullptr;
    }
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
        curScene_->beforeInit();
        curScene_->OnInit();
        if (InitConfig::Instance().IsUseSceneTree()) {
            debug::DebugAttachSceneTree();
        }
    }
}

void SceneMgr::QuitOldScene() {
    if (oldScene_) {
        oldScene_->beforeQuit();
        oldScene_->OnQuit();
    } else {
        return;
    }

    static std::queue<Entity*> entityQueue;
    while (entityQueue.size() > 0) entityQueue.pop();

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

Entity* doFindEntity(Entity* entity, const std::string& name) {
    if (!entity) return nullptr;
    if (entity->Name() == name) {
        return entity;
    }
    if (auto node = entity->GetComponent<NodeComponent>(); node) {
        for (auto& child : node->children) {
            auto result = doFindEntity(child, name);
            if (result) return result;
        }
    }
    if (auto node = entity->GetComponent<Node2DComponent>(); node) {
        for (auto& child : node->children) {
            auto result = doFindEntity(child, name);
            if (result) return result;
        }
    }
    return nullptr;
}

Entity* Scene::FindEntity(const std::string& name) {
    return doFindEntity(root_, name);
}

void doFindEntities(Entity* entity, const std::string& name, std::vector<Entity*>& result) {
    if (!entity) return;

    if (entity->Name() == name) {
        result.push_back(entity);
    }
    if (auto node = entity->GetComponent<NodeComponent>(); node) {
        for (auto& child : node->children) {
            doFindEntities(child, name, result);
        }
    }
    if (auto node = entity->GetComponent<Node2DComponent>(); node) {
        for (auto& child : node->children) {
            doFindEntities(child, name, result);
        }
    }
}

std::vector<Entity*> Scene::FindEntities(const std::string& name) {
    std::vector<Entity*> result;
    doFindEntities(root_, name, result);
    return result;
}

}