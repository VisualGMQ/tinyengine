#include "engine/ui/window.hpp"

namespace engine {

void UIWindow::Reset() {
    title.clear();
    flags = 0;
    rect.position.Set(0, 0);
    rect.size.Set(200, 200);
}

}