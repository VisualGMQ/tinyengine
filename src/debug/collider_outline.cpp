#include "engine/debug/collider_outline.hpp"

namespace engine::debug {

void ColliderOutlineSystem::Update(Entity* entity) {
    if (!entity) return;
    if (auto box = entity->GetComponent<BoxColliderComponent>(); box) {
        if (auto node2d = entity->GetComponent<Node2DComponent>(); node2d) {
            Renderer::SetDrawColor(Color(0, 1, 0));
            Renderer::DrawRect(Rect(node2d->position.x - box->halfWidth + box->offset.x,
                                    node2d->position.y - box->halfHeight + box->offset.y,
                                    box->halfWidth * 2, box->halfHeight * 2), 1.0f);
        }
    }
}

}