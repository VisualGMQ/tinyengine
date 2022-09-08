#include "engine/ui/layout.hpp"

namespace engine {

void UIStaticRowLayout::Reset() {
    height = 30;
    itemWidth = 50;
    cols = 1;
}

void UIDynamicRowLayout::Reset() {
    height = 30;
    cols = 1;
}

}