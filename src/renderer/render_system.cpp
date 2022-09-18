#include "engine/renderer/render_system.hpp"
#include "engine/components/sprite.hpp"
#include "engine/components/transform2d.hpp"
#include "engine/renderer/renderer.hpp"

namespace engine {

Mat4 RenderSystem::Update(Entity* entity, const Mat4& parentTransform) {
    auto newTransform = parentTransform;
    if (auto transform2d = entity->GetComponent<Transform2DComponent>(); transform2d) {
        transform2d->TryUpdateTransform();
		newTransform = transform2d->GetTransform() * parentTransform;
    }

    if (auto sprite = entity->GetComponent<SpriteComponent>(); sprite && sprite->texture) {
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
                               newTransform);
    }
    return newTransform;
}

}