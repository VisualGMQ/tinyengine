#include "engine/debug/scene_tree.hpp"

namespace engine::debug {

#define DebugSceneTreeWindowName "Debug::SceneTreeWindow"

void doUpdate(engine::Entity* sceneNode, engine::Entity* parentNode) {
    if (!sceneNode) return;

    if (sceneNode->Name() == DebugSceneTreeWindowName) {
        engine::CreateUITreeNode("tree node", sceneNode->Name(), NK_MINIMIZED, parentNode);
        return;
    }

    auto node = sceneNode->GetComponent<NodeComponent>();
    Entity* n = nullptr;
    if (node && !node->children.empty()) {
        n = engine::CreateUITreeTab("tree tab", sceneNode->Name(), NK_MINIMIZED, parentNode);
    } else {
        n = engine::CreateUITreeNode("tree node", sceneNode->Name(), NK_MINIMIZED, parentNode);
    }

    if ( node) {
        for (auto& child : node->children) {
            doUpdate(child, n);
        }
    }
}

void update(Entity* root) {
    if (!root) return;

    if (auto node = root->GetComponent<NodeComponent>(); node) {
        for (auto& child : node->children) {
            World::Instance()->DestroyEntity(child);
        }
        node->children.clear();
    } else {
        node = World::Instance()->CreateComponent<NodeComponent>();
        root->SetComponent(node);
    }
    auto sceneRoot = engine::SceneMgr::CurrentScene()->GetRootEntity();

    if (auto node = sceneRoot->GetComponent<NodeComponent>(); node) {
        for (auto& child : node->children) {
            doUpdate(child, root);
        }
    }
}

Entity* createDebugSceneTree() {
    auto window = engine::CreateUIWindow(DebugSceneTreeWindowName, "scene tree",
                                         NK_WINDOW_TITLE|NK_WINDOW_MOVABLE|NK_WINDOW_SCALABLE,
                                         engine::Rect(300, 50, 230, 300));
    auto windowLayout = engine::CreateUIDynamicRowLayout("layout", 20, 1, window);

    auto root = engine::CreateUITreeTab("debug scene tree root", SceneMgr::CurrentScene()->GetRootEntity()->Name(), NK_MINIMIZED, nullptr);

    engine::CreateUIButton("refresh button", "Refresh",
    [](Entity*, UIButton*, void* param) {
        update((engine::Entity*)param);
    }, (void*)root, windowLayout);

    windowLayout->GetComponent<NodeComponent>()->Attach(root);

    return window;
}

void DebugAttachSceneTree() {
    SceneMgr::CurrentScene()->AttachUI(createDebugSceneTree());
}

}