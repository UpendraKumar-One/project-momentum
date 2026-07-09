#include "vortex/core/input/input_backend.hpp"
#include "raylib.h"

namespace vortex::core::input_backend
{
    static int translateToRaylibKey(KeyCode key)
    {
        switch (key)
        {
        case KeyCode::Unknown: return 0;
        case KeyCode::A: return KEY_A;
        case KeyCode::B: return KEY_B;
        case KeyCode::C: return KEY_C;
        case KeyCode::D: return KEY_D;
        case KeyCode::E: return KEY_E;
        case KeyCode::F: return KEY_F;
        case KeyCode::G: return KEY_G;
        case KeyCode::H: return KEY_H;
        case KeyCode::I: return KEY_I;
        case KeyCode::J: return KEY_J;
        case KeyCode::K: return KEY_K;
        case KeyCode::L: return KEY_L;
        case KeyCode::M: return KEY_M;
        case KeyCode::N: return KEY_N;
        case KeyCode::O: return KEY_O;
        case KeyCode::P: return KEY_P;
        case KeyCode::Q: return KEY_Q;
        case KeyCode::R: return KEY_R;
        case KeyCode::S: return KEY_S;
        case KeyCode::T: return KEY_T;
        case KeyCode::U: return KEY_U;
        case KeyCode::V: return KEY_V;
        case KeyCode::W: return KEY_W;
        case KeyCode::X: return KEY_X;
        case KeyCode::Y: return KEY_Y;
        case KeyCode::Z: return KEY_Z;
        case KeyCode::Num0: return KEY_ZERO;
        case KeyCode::Num1: return KEY_ONE;
        case KeyCode::Num2: return KEY_TWO;
        case KeyCode::Num3: return KEY_THREE;
        case KeyCode::Num4: return KEY_FOUR;
        case KeyCode::Num5: return KEY_FIVE;
        case KeyCode::Num6: return KEY_SIX;
        case KeyCode::Num7: return KEY_SEVEN;
        case KeyCode::Num8: return KEY_EIGHT;
        case KeyCode::Num9: return KEY_NINE;
        case KeyCode::F1: return KEY_F1;
        case KeyCode::F2: return KEY_F2;
        case KeyCode::F3: return KEY_F3;
        case KeyCode::F4: return KEY_F4;
        case KeyCode::F5: return KEY_F5;
        case KeyCode::F6: return KEY_F6;
        case KeyCode::F7: return KEY_F7;
        case KeyCode::F8: return KEY_F8;
        case KeyCode::F9: return KEY_F9;
        case KeyCode::F10: return KEY_F10;
        case KeyCode::F11: return KEY_F11;
        case KeyCode::F12: return KEY_F12;
        case KeyCode::Space: return KEY_SPACE;
        case KeyCode::Esc: return KEY_ESCAPE;
        case KeyCode::Enter: return KEY_ENTER;
        case KeyCode::Tab: return KEY_TAB;
        case KeyCode::Backspace: return KEY_BACKSPACE;
        case KeyCode::Insert: return KEY_INSERT;
        case KeyCode::DeleteKey: return KEY_DELETE;
        case KeyCode::ArrowRight: return KEY_RIGHT;
        case KeyCode::ArrowLeft: return KEY_LEFT;
        case KeyCode::ArrowDown: return KEY_DOWN;
        case KeyCode::ArrowUp: return KEY_UP;
        case KeyCode::PageUp: return KEY_PAGE_UP;
        case KeyCode::PageDown: return KEY_PAGE_DOWN;
        case KeyCode::Home: return KEY_HOME;
        case KeyCode::End: return KEY_END;
        case KeyCode::CapsLock: return KEY_CAPS_LOCK;
        case KeyCode::ScrollLock: return KEY_SCROLL_LOCK;
        case KeyCode::NumLock: return KEY_NUM_LOCK;
        case KeyCode::PrintScreen: return KEY_PRINT_SCREEN;
        case KeyCode::PauseKey: return KEY_PAUSE;
        case KeyCode::LeftShift: return KEY_LEFT_SHIFT;
        case KeyCode::LeftControl: return KEY_LEFT_CONTROL;
        case KeyCode::LeftAlt: return KEY_LEFT_ALT;
        case KeyCode::LeftSuper: return KEY_LEFT_SUPER;
        case KeyCode::RightShift: return KEY_RIGHT_SHIFT;
        case KeyCode::RightControl: return KEY_RIGHT_CONTROL;
        case KeyCode::RightAlt: return KEY_RIGHT_ALT;
        case KeyCode::RightSuper: return KEY_RIGHT_SUPER;
        case KeyCode::Numpad0: return KEY_KP_0;
        case KeyCode::Numpad1: return KEY_KP_1;
        case KeyCode::Numpad2: return KEY_KP_2;
        case KeyCode::Numpad3: return KEY_KP_3;
        case KeyCode::Numpad4: return KEY_KP_4;
        case KeyCode::Numpad5: return KEY_KP_5;
        case KeyCode::Numpad6: return KEY_KP_6;
        case KeyCode::Numpad7: return KEY_KP_7;
        case KeyCode::Numpad8: return KEY_KP_8;
        case KeyCode::Numpad9: return KEY_KP_9;
        case KeyCode::NumpadDecimal: return KEY_KP_DECIMAL;
        case KeyCode::NumpadDivide: return KEY_KP_DIVIDE;
        case KeyCode::NumpadMultiply: return KEY_KP_MULTIPLY;
        case KeyCode::NumpadSubtract: return KEY_KP_SUBTRACT;
        case KeyCode::NumpadAdd: return KEY_KP_ADD;
        case KeyCode::NumpadEnter: return KEY_KP_ENTER;
        case KeyCode::NumpadEqual: return KEY_KP_EQUAL;
        case KeyCode::Apostrophe: return KEY_APOSTROPHE;
        case KeyCode::Comma: return KEY_COMMA;
        case KeyCode::Hyphen: return KEY_MINUS;
        case KeyCode::Plus: return KEY_EQUAL;
        case KeyCode::Period: return KEY_PERIOD;
        case KeyCode::ForwardSlash: return KEY_SLASH;
        case KeyCode::Semicolon: return KEY_SEMICOLON;
        case KeyCode::Equal: return KEY_EQUAL;
        case KeyCode::LeftBracket: return KEY_LEFT_BRACKET;
        case KeyCode::Backslash: return KEY_BACKSLASH;
        case KeyCode::RightBracket: return KEY_RIGHT_BRACKET;
        case KeyCode::Tilde: return KEY_GRAVE;
        default: return 0;
        }
    }

    bool isHardwareKeyPressed(KeyCode key)
    {
        return IsKeyPressed(translateToRaylibKey(key));
    }

    bool isHardwareKeyDown(KeyCode key)
    {
        return IsKeyDown(translateToRaylibKey(key));
    }
}