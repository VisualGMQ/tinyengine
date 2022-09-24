#include "engine/ui/image.hpp"

namespace engine {

void UIImage::Reset() {
    texture = nullptr;
    w = 0;
    h = 0;
    region.position.Set(0, 0);
    region.size.Set(0, 0);
}

Entity* CreateUIImage(const std::string& name, Texture* texture, int w, int h, const Rect& region, const Color& color, Entity* parent) {
    Entity* entity = World::Instance()->CreateEntity(name);
    auto image = World::Instance()->CreateComponent<UIImage>();
    image->w = w;
    image->h = h;
    image->texture = texture;
    image->region = region;
    image->color = color;
    entity->SetComponent(image);

    if (parent) {
        auto node = parent->GetComponent<NodeComponent>();
        if (!node) {
            node = World::Instance()->CreateComponent<NodeComponent>();
            parent->SetComponent(node);
        }
        node->Attach(entity);
    }
    return entity;
}

}