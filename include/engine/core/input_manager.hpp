#pragma once

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

    void BindActionKey(InputAction action, int key);

    bool IsActionHeld(InputAction action) const;

    bool IsActionPressed(InputAction action) const;

private:
    InputManager();
    ~InputManager();

    Impl *p_Impl;
};