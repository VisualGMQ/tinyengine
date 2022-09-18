#include "engine/ui/property.hpp"

namespace engine {

void UIProperty::Reset() {
    type = UIProperty::Int;
    min = 0;
    max = 100;
    ivalue = 50;
    incStep = 1;
    text = "property";
    incPerPixel = 1;
}

Entity* CreateUIProperty(const std::string& name, const std::string& text, UIProperty::CallbackType onValueChange, UIProperty::Type type, float min, float max, float value, float incStep, float incPerPixel, Entity* parent) {
    Entity* entity = World::Instance()->CreateEntity(name);
    auto property = World::Instance()->CreateComponent<UIProperty>();
    property->type = type;
    property->min = min;
    property->max = max;
    switch (type) {
        case UIProperty::Int: property->ivalue = value; break;
        case UIProperty::Float: property->fvalue = value; break;
        case UIProperty::Double: property->dvalue = value; break;
    }
    property->incStep = incStep;
    property->text = text;
    property->incPerPixel = incPerPixel;
    property->callback = onValueChange;
    entity->SetComponent(property);

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