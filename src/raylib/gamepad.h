#pragma once

#include "raylib/raylib.h"
#include <string>

namespace raylib {
class Gamepad {
private:
    int number;

public:
    explicit Gamepad(int gamepadNumber = 0);
    int GetNumber() const;
    void SetNumber(int value);
    Gamepad& operator=(const Gamepad& gamepad);
    Gamepad& operator=(int gamepadNumber);
    bool IsAvailable() const;
    static bool IsAvailable(int number);
    std::string GetName() const;
    bool IsButtonPressed(int button) const;
    bool IsButtonDown(int button) const;
    bool IsButtonReleased(int button) const;
    bool IsButtonUp(int button) const;
    static int GetButtonPressed();
    int GetAxisCount() const;
    float GetAxisMovement(int axis) const;
    static int SetMappings(const std::string& mappings);

    explicit operator int() const {
        return number;
    }

    explicit operator std::string() const {
        return GetName();
    }

protected:
    void set(int gamepadNumber);
};
} // namespace raylib
