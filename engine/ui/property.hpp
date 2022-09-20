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

/// @brief Create a Property bar
/// @param name name of property
/// @param text display text of property(please make sure there are no same text in others, because nuklear use this to distinguish two Properties(or add a '#' at start))
/// @param onValueChange a callback void(Entity*, UIProperty*) will be called when value changed
/// @param UIProperty::Type type of property
/// @param min min value
/// @param max max value
/// @param value current value 
/// @param incStep the increase step when you click side button
/// @param incPerPixel the increase value when you slide the bar
/// @param parent 
/// @return 
Entity* CreateUIProperty(const std::string& name, const std::string& text, UIProperty::CallbackType onValueChange, UIProperty::Type, float min, float max, float value, float incStep, float incPerPixel, Entity* parent);

}