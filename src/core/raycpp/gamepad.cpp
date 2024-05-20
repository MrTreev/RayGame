#include "core/raycpp/gamepad.h"

void core::raycpp::Gamepad::set(int gamepadNumber) {
    number = gamepadNumber;
}

core::raycpp::Gamepad::Gamepad(int gamepadNumber) {
    set(gamepadNumber);
}

int core::raycpp::Gamepad::GetNumber() const {
    return number;
}

void core::raycpp::Gamepad::SetNumber(int value) {
    number = value;
}

core::raycpp::Gamepad& core::raycpp::Gamepad::operator=(const Gamepad& gamepad) {
    set(int(gamepad));
    return *this;
}

core::raycpp::Gamepad& core::raycpp::Gamepad::operator=(int gamepadNumber) {
    set(gamepadNumber);
    return *this;
}

bool core::raycpp::Gamepad::IsAvailable() const {
    return ::IsGamepadAvailable(number);
}

bool core::raycpp::Gamepad::IsAvailable(int number) {
    return ::IsGamepadAvailable(number);
}

std::string core::raycpp::Gamepad::GetName() const {
    return ::GetGamepadName(number);
}

bool core::raycpp::Gamepad::IsButtonPressed(int button) const {
    return ::IsGamepadButtonPressed(number, button);
}

bool core::raycpp::Gamepad::IsButtonDown(int button) const {
    return ::IsGamepadButtonDown(number, button);
}

bool core::raycpp::Gamepad::IsButtonReleased(int button) const {
    return ::IsGamepadButtonReleased(number, button);
}

bool core::raycpp::Gamepad::IsButtonUp(int button) const {
    return ::IsGamepadButtonUp(number, button);
}

int core::raycpp::Gamepad::GetButtonPressed() {
    return ::GetGamepadButtonPressed();
}

int core::raycpp::Gamepad::GetAxisCount() const {
    return ::GetGamepadAxisCount(number);
}

float core::raycpp::Gamepad::GetAxisMovement(int axis) const {
    return ::GetGamepadAxisMovement(number, axis);
}

int core::raycpp::Gamepad::SetMappings(const std::string& mappings) {
    return SetGamepadMappings(mappings.c_str());
}
