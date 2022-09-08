#include "engine/input/input.hpp"

namespace engine {

bool Input::oldKeyState_[KEY_NUM] = {0};
bool Input::keyState_[KEY_NUM] = {0};
bool Input::oldBtnState_[MOUSEBUTTON_NUM] = {0};
bool Input::btnState_[MOUSEBUTTON_NUM] = {0};
Vec2 Input::position_;
Vec2 Input::offset_;

void Input::Init() {
    auto window = Context::GetWindow();
    glfwSetCursorPosCallback(window,
                             [](GLFWwindow* window, double xpos, double ypos){
                                offset_.Set(xpos - position_.x, ypos - position_.y);
                                position_.x = xpos;  
                                position_.y = ypos;
                             });  
    glfwSetKeyCallback(window,
                       [](GLFWwindow* window, int key, int scancode, int action, int mods){
                            if (action == GLFW_PRESS) {
                                keyState_[key] = true;
                            }
                            if (action == GLFW_RELEASE) {
                                keyState_[key] = false;
                            }
                       });
    glfwSetMouseButtonCallback(window,
                               [](GLFWwindow* window, int button, int action, int mods){
                                   if (action == GLFW_PRESS) {
                                       btnState_[button] = true;
                                   }
                                   if (action == GLFW_RELEASE) {
                                       btnState_[button] = false;
                                   }
                               });
}

void Input::Quit() { }


bool Input::IsKeyPressed(KeyCode code) {
    return !oldKeyState_[code] && keyState_[code];
}

bool Input::IsKeyPressing(KeyCode code) {
    return oldKeyState_[code] && keyState_[code] || IsKeyPressed(code);
}

bool Input::IsKeyReleased(KeyCode code) {
    return oldKeyState_[code] && !keyState_[code];
}

bool Input::IsKeyReleasing(KeyCode code) {
    return !oldKeyState_[code] && !keyState_[code] || IsKeyReleased(code);
}

bool Input::IsButtonPressed(MouseButton button) {
    return !oldBtnState_[button] && btnState_[button];
}

bool Input::IsButtonPressing(MouseButton button) {
    return oldBtnState_[button] && btnState_[button] || IsButtonPressed(button);
}

bool Input::IsButtonReleased(MouseButton button) {
    return oldBtnState_[button] && !btnState_[button];
}

bool Input::IsButtonReleasing(MouseButton button) {
    return !oldBtnState_[button] && !btnState_[button] || IsButtonReleasing(button);
}

const Vec2& Input::MousePoition() {
    return position_;
}

const Vec2& Input::MouseRelative() {
    return offset_;
}

void Input::UpdateStates() {
    memcpy(oldBtnState_, btnState_, sizeof(oldBtnState_));
    memcpy(oldKeyState_, keyState_, sizeof(oldKeyState_));
    offset_.Set(0, 0);
}

}
