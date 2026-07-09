#pragma once

#include "vortex/core/input/input_backend.hpp"

namespace vortex::core
{
    struct Impl;

    enum class InputAction
    {
        Up,
        Left,
        Jump,
        Down,
        Right,
        Quit
    };

    class InputManager
    {
    public:
        static InputManager &getInstance()
        {
            static InputManager instance;
            return instance;
        }

        void bindActionKey(InputAction action, input_backend::KeyCode key);

        bool isActionHeld(InputAction action) const;

        bool isActionPressed(InputAction action) const;

    private:
        InputManager();
        ~InputManager();

        Impl *m_impl;
    };
}
