#pragma once

#include "vortex/core/input/input_backend.hpp"

namespace Vortex::Core
{
    struct Impl;

    enum class InputAction
    {
        UP,
        LEFT,
        JUMP,
        DOWN,
        RIGHT,
        QUIT
    };

    class InputManager
    {
    public:
        static InputManager &GetInstance()
        {
            static InputManager instance;
            return instance;
        }

        void BindActionKey(InputAction action, InputBackend::KeyCode key);

        bool IsActionHeld(InputAction action) const;

        bool IsActionPressed(InputAction action) const;

    private:
        InputManager();
        ~InputManager();

        Impl *p_Impl;
    };
}