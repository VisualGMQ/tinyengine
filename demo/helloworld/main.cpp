#include "gamestart.hpp"
#include "uiscene.hpp"

SCENE_CONFIG() {
    LOAD_SCENE(GameStart);
    LOAD_SCENE(UIScene);
    ENTER_SCENE(GameStart);
}