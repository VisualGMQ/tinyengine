#pragma once

#include "engine/core/pch.hpp"
#include "engine/components/node.hpp"
#include "engine/ecs/entity.hpp"

namespace engine {

class Scene {
public:
    friend class SceneMgr;

    Scene(const std::string& name);
    virtual ~Scene() = default;

    const std::string& Name() const { return name_; }
    Entity* GetRootEntity() const { return root_; }
    void Attach(Entity*);

    virtual void OnInit() = 0;
    virtual void OnUpdate() = 0;
    virtual void OnQuit() = 0;

private:
    std::string name_;
    Entity* root_;
};


class SceneMgr final {
public:
    static void Init();
    static void Quit();
    template <typename T>
    static void LoadScene(const std::string& name);
    static void ChangeScene(const std::string& name);
    static Scene* CurrentScene() { return curScene_; }
    static void QuitOldScene();

private:
    static Scene* curScene_;
    static Scene* oldScene_;
    static std::unordered_map<std::string, std::unique_ptr<Scene>> scenes_;
};

template <typename T>
void SceneMgr::LoadScene(const std::string& name) {
    auto it = scenes_.find(name);
    if (it == scenes_.end()) {
        scenes_[name] = std::make_unique<T>(name);
    } else {
        Logw("scene {} already loaded", name.c_str());
    }
}

#define SCENE_CONFIG() void GameInit(void)
#define LOAD_SCENE(scene) engine::SceneMgr::LoadScene<scene>(#scene)
#define ENTER_SCENE(scene) engine::SceneMgr::ChangeScene(#scene)

}