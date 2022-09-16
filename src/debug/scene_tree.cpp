#include "engine/debug/scene_tree.hpp"

namespace engine::debug {

void UISceneTree::Update() {
    engine::World::Instance()->DestroyEntity(root);
    root = nullptr;
    auto sceneRoot = engine::SceneMgr::CurrentScene()->GetRootEntity();
    root = engine::World::Instance()->CreateEntity(sceneRoot->Name());
    auto treeNode = engine::World::Instance()->CreateComponent<UITree>();
    root->SetComponent(treeNode);
    doUpdate(sceneRoot, root);
}

void UISceneTree::doUpdate(engine::Entity* sceneNode, engine::Entity* parentNode) {
    if (!sceneNode) return;

    // TODO not finish    
}

}