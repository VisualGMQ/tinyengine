#include "engine/ui/checkbox.hpp"

namespace engine {

void UICheckbox::Reset() {
    text = "checkbox";
    isSelected = true;
    callback = nullptr;
}

}