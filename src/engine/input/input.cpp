#include "engine/input/input.hpp"

namespace engine {

bool Input::oldKeyState[KEY_NUM] = {0};
bool Input::keyState[KEY_NUM] = {0};
bool Input::oldBtnState[MOUSEBUTTON_NUM] = {0};
bool Input::btnState[MOUSEBUTTON_NUM] = {0};
Vec2 Input::position;

void Input::Init() {
    auto window = Context::GetWindow();
    glfwSetCursorPosCallback(window,
                             [](GLFWwindow* window, double xpos, double ypos){
                                position.x = xpos;  
                                position.y = ypos;
                             });  
    glfwSetKeyCallback(window,
                       [](GLFWwindow* window, int key, int scancode, int action, int mods){
                            if (action == GLFW_PRESS) {
                                keyState[key] = true;
                            }
                            if (action == GLFW_RELEASE) {
                                keyState[key] = false;
                            }
                       });
    glfwSetMouseButtonCallback(window,
                               [](GLFWwindow* window, int button, int action, int mods){
                                   if (action == GLFW_PRESS) {
                                       btnState[button] = true;
                                   }
                                   if (action == GLFW_RELEASE) {
                                       btnState[button] = false;
                                   }
                               });
}

void Input::Quit() { }


bool Input::IsKeyPressed(KeyCode code) {
    return !oldKeyState[code] && keyState[code];
}

bool Input::IsKeyPressing(KeyCode code) {
    return oldKeyState[code] && keyState[code];
}

bool Input::IsKeyReleased(KeyCode code) {
    return oldKeyState[code] && !keyState[code];
}

bool Input::IsKeyReleasing(KeyCode code) {
    return !oldKeyState[code] && !keyState[code];
}

bool Input::IsButtonPressed(MouseButton button) {
    return !oldBtnState[button] && btnState[button];
}

bool Input::IsButtonPressing(MouseButton button) {
    return oldBtnState[button] && btnState[button];
}

bool Input::IsButtonReleased(MouseButton button) {
    return oldBtnState[button] && !btnState[button];
}

bool Input::IsButtonReleasing(MouseButton button) {
    return !oldBtnState[button] && !btnState[button];
}

const Vec2& Input::MousePoition() {
    return position;
}

void Input::UpdateStates() {
    memcpy(oldBtnState, btnState, sizeof(oldBtnState));
    memcpy(oldKeyState, keyState, sizeof(oldKeyState));
}

}
