#pragma once

#include "engine/ecs/component.hpp"
#include "engine/ecs/world.hpp"
#include "engine/components/node.hpp"
#include "nuklear.h"

namespace engine {

class UIProperty: public Component {
public:
    using CallbackType = std::function<void(Entity*, UIProperty*)>;

    enum Type {
        Int,
        Float,
        Double,
    };

    UIProperty(ComponentID id) : Component(id) { Reset(); }

    void Reset() override;
    double Value() { 
        switch (type) {
            case Int: return ivalue;
            case Float: return fvalue;
            case Double: return dvalue;
        }
        return 0;
    }

    Type type;
    float min;
    float max;
    float incStep;
    float incPerPixel;
    union {
        int ivalue;
        float fvalue;
        double dvalue;
    };
    std::string text;
    CallbackType callback;

    double oldValue;
};

Entity* CreateUIProperty(const std::string& name, const std::string& text, UIProperty::CallbackType onValueChange, UIProperty::Type, float min, float max, float value, float incStep, float incPerPixel, Entity* parent);

}