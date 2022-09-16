#include "gamestart.hpp"
#include "testscene.hpp"

SCENE_CONFIG() {
    LOAD_SCENE(GameStart);
    LOAD_SCENE(TestScene);
    ENTER_SCENE(GameStart);
}