#include "engine/renderer/render_system.hpp"
#include "engine/components/sprite.hpp"
#include "engine/renderer/renderer.hpp"
#include "engine/components/node.hpp"

namespace engine {

Mat4 RenderSystem::Update(Entity* entity, const Mat4& parentTransform) {
    auto curTransform = IdentityMat4;
    float zIndex = 0;
    if (auto node2d = entity->GetComponent<Node2DComponent>(); node2d && node2d->IsActive()) {
        node2d->DetectDirt();
        node2d->TryUpdateTransform();
        curTransform = node2d->GetTransform();
        zIndex = node2d->zIndex;
    }

    if (auto sprite = entity->GetComponent<SpriteComponent>(); sprite && sprite->IsActive() && sprite->image.texture) {
        auto region = sprite->image.region;
        Size size = sprite->size;
        if (size.w == 0 || size.h == 0) {
            if (sprite->image.region.size == Vec2(0, 0)) {
				size.w = sprite->image.texture->Width();
				size.h = sprite->image.texture->Height();
                region.size = size;
            } else {
                size = sprite->image.region.size;
            }
        }
        if (sprite->flip & Flip::Vertical) {
            size.w *= -1;
        }
        if (sprite->flip & Flip::Horizontal) {
            size.h *= -1;
        }
        Renderer::SetDrawColor(sprite->color);
        Renderer::SetKeyColor(sprite->keycolor);
        Renderer::DrawTexture(*sprite->image.texture,
                               sprite->image.region.size == Vec2(0, 0) ? nullptr : &sprite->image.region,
                               size,
                               parentTransform * curTransform * CreateTranslate(Vec3(sprite->offset.x, sprite->offset.y, 0)),
                               zIndex);
    }
    return parentTransform * curTransform;
}

}
