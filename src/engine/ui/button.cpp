#include "engine/ui/button.hpp"

namespace engine {

void UIButton::Reset() {
    text = "button";
    onClick = nullptr;
}

}