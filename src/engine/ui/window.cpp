#include "engine/ui/window.hpp"

namespace engine {

void UIWindow::OnInit() {
    title.clear();
    isShowTitle = true;
    flags = 0;
    rect.position.Set(0, 0);
    rect.size.Set(200, 200);
}

}