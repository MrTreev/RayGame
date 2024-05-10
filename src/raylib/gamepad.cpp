#include "raylib/gamepad.h"

void raylib::Gamepad::set(int gamepadNumber) {
    number = gamepadNumber;
}

raylib::Gamepad::Gamepad(int gamepadNumber) {
    set(gamepadNumber);
}

int raylib::Gamepad::GetNumber() const {
    return number;
}

void raylib::Gamepad::SetNumber(int value) {
    number = value;
}

raylib::Gamepad& raylib::Gamepad::operator=(const Gamepad& gamepad) {
    set(int(gamepad));
    return *this;
}

raylib::Gamepad& raylib::Gamepad::operator=(int gamepadNumber) {
    set(gamepadNumber);
    return *this;
}

bool raylib::Gamepad::IsAvailable() const {
    return ::IsGamepadAvailable(number);
}

bool raylib::Gamepad::IsAvailable(int number) {
    return ::IsGamepadAvailable(number);
}

std::string raylib::Gamepad::GetName() const {
    return ::GetGamepadName(number);
}

bool raylib::Gamepad::IsButtonPressed(int button) const {
    return ::IsGamepadButtonPressed(number, button);
}

bool raylib::Gamepad::IsButtonDown(int button) const {
    return ::IsGamepadButtonDown(number, button);
}

bool raylib::Gamepad::IsButtonReleased(int button) const {
    return ::IsGamepadButtonReleased(number, button);
}

bool raylib::Gamepad::IsButtonUp(int button) const {
    return ::IsGamepadButtonUp(number, button);
}

int raylib::Gamepad::GetButtonPressed() {
    return ::GetGamepadButtonPressed();
}

int raylib::Gamepad::GetAxisCount() const {
    return ::GetGamepadAxisCount(number);
}

float raylib::Gamepad::GetAxisMovement(int axis) const {
    return ::GetGamepadAxisMovement(number, axis);
}

int raylib::Gamepad::SetMappings(const std::string& mappings) {
    return SetGamepadMappings(mappings.c_str());
}
