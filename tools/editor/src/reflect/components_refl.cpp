#include "components_refl.hpp"
#include "engine/components/node.hpp"
#include "engine/components/sprite.hpp"

using namespace engine;

namespace editor {

void ReflAllClass() {
    // NodeComponent
    REFL_BEGIN()
        REFL_REGIST_CLASS(NodeComponent)
        REFL_REGIST_DATA("children", &NodeComponent::children)
        REFL_REGIST_FUNC("Reset", &NodeComponent::Reset)
        REFL_REGIST_FUNC("Attach", &NodeComponent::Attach)
        REFL_REGIST_FUNC("Parent", &NodeComponent::Parent)
        REFL_REGIST_BASE(Component)
    REFL_END()

    // Node2DComponent
    REFL_BEGIN()
        REFL_REGIST_CLASS(Node2DComponent)
        REFL_REGIST_FUNC("Reset", &Node2DComponent::Reset)
        REFL_REGIST_DATA("position", &Node2DComponent::position)
        REFL_REGIST_DATA("scale", &Node2DComponent::scale)
        REFL_REGIST_DATA("rotation", &Node2DComponent::rotation)
        REFL_REGIST_BASE(Component)
    REFL_END()

    // Node2DRoot
    REFL_BEGIN()
        REFL_REGIST_CLASS(Node2DRoot)
        REFL_REGIST_FUNC("Reset", &Node2DRoot::Reset)
        REFL_REGIST_BASE(Component)
    REFL_END()

    // Node3DRoot
    REFL_BEGIN()
        REFL_REGIST_CLASS(Node3DRoot)
        REFL_REGIST_FUNC("Reset", &Node3DRoot::Reset)
        REFL_REGIST_BASE(Component)
    REFL_END()

    // NodeUIRoot
    REFL_BEGIN()
        REFL_REGIST_CLASS(NodeUIRoot)
        REFL_REGIST_FUNC("Reset", &NodeUIRoot::Reset)
        REFL_REGIST_BASE(Component)
    REFL_END()

    // Sprite
    REFL_BEGIN()
        REFL_REGIST_CLASS(SpriteComponent)
        REFL_REGIST_FUNC("Reset", &SpriteComponent::Reset)
        REFL_REGIST_DATA("color", &SpriteComponent::color)
        REFL_REGIST_DATA("region", &SpriteComponent::region)
        REFL_REGIST_DATA("flip", &SpriteComponent::flip)
        REFL_REGIST_DATA("offset", &SpriteComponent::offset)
        REFL_REGIST_DATA("size", &SpriteComponent::size)
        REFL_REGIST_BASE(Component)
    REFL_END()
}

}