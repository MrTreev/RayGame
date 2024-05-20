#pragma once

namespace core::raycpp {

using Key = enum: int {
    // Alphanumeric keys
    APOSTROPHE    = 39, // Key: '
    COMMA         = 44, // Key: ,
    MINUS         = 45, // Key: -
    PERIOD        = 46, // Key: .
    SLASH         = 47, // Key: /
    ZERO          = 48, // Key: 0
    ONE           = 49, // Key: 1
    TWO           = 50, // Key: 2
    THREE         = 51, // Key: 3
    FOUR          = 52, // Key: 4
    FIVE          = 53, // Key: 5
    SIX           = 54, // Key: 6
    SEVEN         = 55, // Key: 7
    EIGHT         = 56, // Key: 8
    NINE          = 57, // Key: 9
    SEMICOLON     = 59, // Key: ;
    EQUAL         = 61, // Key: =
    A             = 65, // Key: A | a
    B             = 66, // Key: B | b
    C             = 67, // Key: C | c
    D             = 68, // Key: D | d
    E             = 69, // Key: E | e
    F             = 70, // Key: F | f
    G             = 71, // Key: G | g
    H             = 72, // Key: H | h
    I             = 73, // Key: I | i
    J             = 74, // Key: J | j
    K             = 75, // Key: K | k
    L             = 76, // Key: L | l
    M             = 77, // Key: M | m
    N             = 78, // Key: N | n
    O             = 79, // Key: O | o
    P             = 80, // Key: P | p
    Q             = 81, // Key: Q | q
    R             = 82, // Key: R | r
    S             = 83, // Key: S | s
    T             = 84, // Key: T | t
    U             = 85, // Key: U | u
    V             = 86, // Key: V | v
    W             = 87, // Key: W | w
    X             = 88, // Key: X | x
    Y             = 89, // Key: Y | y
    Z             = 90, // Key: Z | z
    LEFT_BRACKET  = 91, // Key: [
    BACKSLASH     = 92, // Key: '\'
    RIGHT_BRACKET = 93, // Key: ]
    GRAVE         = 96, // Key: `
    // Function keys
    SPACE         = 32,  // Key: Space
    ESCAPE        = 256, // Key: Esc
    ENTER         = 257, // Key: Enter
    TAB           = 258, // Key: Tab
    BACKSPACE     = 259, // Key: Backspace
    INSERT        = 260, // Key: Ins
    DELETE        = 261, // Key: Del
    RIGHT         = 262, // Key: Cursor right
    LEFT          = 263, // Key: Cursor left
    DOWN          = 264, // Key: Cursor down
    UP            = 265, // Key: Cursor up
    PAGE_UP       = 266, // Key: Page up
    PAGE_DOWN     = 267, // Key: Page down
    HOME          = 268, // Key: Home
    END           = 269, // Key: End
    CAPS_LOCK     = 280, // Key: Caps lock
    SCROLL_LOCK   = 281, // Key: Scroll down
    NUM_LOCK      = 282, // Key: Num lock
    PRINT_SCREEN  = 283, // Key: Print screen
    PAUSE         = 284, // Key: Pause
    F1            = 290, // Key: F1
    F2            = 291, // Key: F2
    F3            = 292, // Key: F3
    F4            = 293, // Key: F4
    F5            = 294, // Key: F5
    F6            = 295, // Key: F6
    F7            = 296, // Key: F7
    F8            = 297, // Key: F8
    F9            = 298, // Key: F9
    F10           = 299, // Key: F10
    F11           = 300, // Key: F11
    F12           = 301, // Key: F12
    LEFT_SHIFT    = 340, // Key: Shift left
    LEFT_CONTROL  = 341, // Key: Control left
    LEFT_ALT      = 342, // Key: Alt left
    LEFT_SUPER    = 343, // Key: Super left
    RIGHT_SHIFT   = 344, // Key: Shift right
    RIGHT_CONTROL = 345, // Key: Control right
    RIGHT_ALT     = 346, // Key: Alt right
    RIGHT_SUPER   = 347, // Key: Super right
    KB_MENU       = 348, // Key: KB menu
    // Keypad keys
    KP_0          = 320, // Key: Keypad 0
    KP_1          = 321, // Key: Keypad 1
    KP_2          = 322, // Key: Keypad 2
    KP_3          = 323, // Key: Keypad 3
    KP_4          = 324, // Key: Keypad 4
    KP_5          = 325, // Key: Keypad 5
    KP_6          = 326, // Key: Keypad 6
    KP_7          = 327, // Key: Keypad 7
    KP_8          = 328, // Key: Keypad 8
    KP_9          = 329, // Key: Keypad 9
    KP_DECIMAL    = 330, // Key: Keypad .
    KP_DIVIDE     = 331, // Key: Keypad /
    KP_MULTIPLY   = 332, // Key: Keypad *
    KP_SUBTRACT   = 333, // Key: Keypad -
    KP_ADD        = 334, // Key: Keypad +
    KP_ENTER      = 335, // Key: Keypad Enter
    KP_EQUAL      = 336, // Key: Keypad =
    // Android key buttons
    BACK          = 4,  // Key: Android back button
    MENU          = 82, // Key: Android menu button
    VOLUME_UP     = 24, // Key: Android volume up button
    VOLUME_DOWN   = 25, // Key: Android volume down button
};

namespace mouse {

using Button = enum {
    LEFT    = 0, // left
    RIGHT   = 1, // right
    MIDDLE  = 2, // middle (pressed wheel)
    SIDE    = 3, // side (advanced mouse device)
    EXTRA   = 4, // extra (advanced mouse device)
    FORWARD = 5, // forward (advanced mouse device)
    BACK    = 6, // back (advanced mouse device)
};

using Cursor = enum {
    MOUSE_CURSOR_DEFAULT       = 0,  // Default pointer shape
    MOUSE_CURSOR_ARROW         = 1,  // Arrow shape
    MOUSE_CURSOR_IBEAM         = 2,  // Text writing cursor shape
    MOUSE_CURSOR_CROSSHAIR     = 3,  // Cross shape
    MOUSE_CURSOR_POINTING_HAND = 4,  // Pointing hand cursor
    MOUSE_CURSOR_RESIZE_EW     = 5,  // Horizontal resize/move arrow shape
    MOUSE_CURSOR_RESIZE_NS     = 6,  // Vertical resize/move arrow shape
    MOUSE_CURSOR_RESIZE_NWSE   = 7,  // Top-left to bottom-right diagonal
    MOUSE_CURSOR_RESIZE_NESW   = 8,  // The top-right to bottom-left diagonal
    MOUSE_CURSOR_RESIZE_ALL    = 9,  // The omnidirectional resize cursor shape
    MOUSE_CURSOR_NOT_ALLOWED   = 10, // The operation-not-allowed shape
};

} // namespace mouse

namespace gamepad {

using Button = enum {
    GAMEPAD_BUTTON_UNKNOWN = 0,      // Unknown button
    GAMEPAD_BUTTON_LEFT_FACE_UP,     // left DPAD up button
    GAMEPAD_BUTTON_LEFT_FACE_RIGHT,  // left DPAD right button
    GAMEPAD_BUTTON_LEFT_FACE_DOWN,   // left DPAD down button
    GAMEPAD_BUTTON_LEFT_FACE_LEFT,   // left DPAD left button
    GAMEPAD_BUTTON_RIGHT_FACE_UP,    // right button up
                                     // (i.e. PS3: Triangle, Xbox: Y)
    GAMEPAD_BUTTON_RIGHT_FACE_RIGHT, // right button right
                                     // (i.e. PS3: Square, Xbox: X)
    GAMEPAD_BUTTON_RIGHT_FACE_DOWN,  // right button down
                                     // (i.e. PS3: Cross, Xbox: A)
    GAMEPAD_BUTTON_RIGHT_FACE_LEFT,  // right button left
                                     // (i.e. PS3: Circle, Xbox: B)
    GAMEPAD_BUTTON_LEFT_TRIGGER_1,   // top/back trigger left (first),
                                     // it could be a trailing button
    GAMEPAD_BUTTON_LEFT_TRIGGER_2,   // top/back trigger left (second),
                                     // it could be a trailing button
    GAMEPAD_BUTTON_RIGHT_TRIGGER_1,  // top/back trigger right (one),
                                     // it could be a trailing button
    GAMEPAD_BUTTON_RIGHT_TRIGGER_2,  // top/back trigger right (second),
                                     // it could be a trailing button
    GAMEPAD_BUTTON_MIDDLE_LEFT,      // center buttons, left one
                                     // (i.e. PS3: Select)
    GAMEPAD_BUTTON_MIDDLE,           // center buttons, middle one
                                     // (i.e. PS3: PS, Xbox: XBOX)
    GAMEPAD_BUTTON_MIDDLE_RIGHT,     // center buttons, right one
                                     // (i.e. PS3: Start)
    GAMEPAD_BUTTON_LEFT_THUMB,       // joystick pressed button left
    GAMEPAD_BUTTON_RIGHT_THUMB       // joystick pressed button right
};

using Axis = enum {
    GAMEPAD_AXIS_LEFT_X        = 0, // left stick X axis
    GAMEPAD_AXIS_LEFT_Y        = 1, // left stick Y axis
    GAMEPAD_AXIS_RIGHT_X       = 2, // right stick X axis
    GAMEPAD_AXIS_RIGHT_Y       = 3, // right stick Y axis
    GAMEPAD_AXIS_LEFT_TRIGGER  = 4, // back trigger left, pressure: [1..-1]
    GAMEPAD_AXIS_RIGHT_TRIGGER = 5  // back trigger right, pressure: [1..-1]
};

} // namespace gamepad

} // namespace core::raycpp
