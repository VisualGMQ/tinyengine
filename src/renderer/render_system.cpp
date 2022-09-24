#include "engine/renderer/render_system.hpp"
#include "engine/components/sprite.hpp"
#include "engine/renderer/renderer.hpp"
#include "engine/components/node.hpp"

namespace engine {

Mat4 RenderSystem::Update(Entity* entity, const Mat4& parentTransform) {
    auto curTransform = IdentityMat4;
    if (auto node2d = entity->GetComponent<Node2DComponent>(); node2d && node2d->IsActive()) {
        node2d->TryUpdateTransform();
        curTransform = node2d->GetTransform();
    }

    if (auto sprite = entity->GetComponent<SpriteComponent>(); sprite && sprite->IsActive() && sprite->texture) {
        auto region = sprite->region;
        Size size = sprite->size;
        if (size.w == 0 || size.h == 0) {
            if (sprite->region.size == Vec2(0, 0)) {
				size.w = sprite->texture->Width();
				size.h = sprite->texture->Height();
                region.size = size;
            } else {
                size = sprite->region.size;
            }
        }
        if (sprite->flip & Flip::Vertical) {
            size.w *= -1;
        }
        if (sprite->flip & Flip::Horizontal) {
            size.h *= -1;
        }
        Renderer::SetDrawColor(sprite->color);
        Renderer::DrawTexture(*sprite->texture,
                               sprite->region.size == Vec2(0, 0) ? nullptr : &sprite->region,
                               size,
                               parentTransform * curTransform * CreateTranslate(Vec3(sprite->offset.x, sprite->offset.y, 0)));
    }
    return parentTransform * curTransform;
}

}