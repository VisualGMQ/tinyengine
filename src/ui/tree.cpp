#include "engine/ui/tree.hpp"

namespace engine {

int UITree::curId_ = 0;

void UITree::Reset() {
    type = NK_TREE_TAB;
    state = NK_MINIMIZED;
    text = "tree node";
}

}