#include "game/gamestart.hpp"
#include "game/uiscene.hpp"

SCENE_CONFIG() {
    LOAD_SCENE(GameStart);
    LOAD_SCENE(UIScene);
    ENTER_SCENE(GameStart);
}
