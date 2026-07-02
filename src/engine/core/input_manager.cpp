#include "input_manager.hpp"
#include "raylib.h"
#include <unordered_map>

struct Impl
{
    std::unordered_map<InputAction, int> m_keyBindings_;
};

InputManager::InputManager()
{
    p_Impl = new Impl;

    BindActionKey(InputAction::UP, KEY_W);
    BindActionKey(InputAction::RIGHT, KEY_D);
    BindActionKey(InputAction::DOWN, KEY_S);
    BindActionKey(InputAction::LEFT, KEY_A);
    BindActionKey(InputAction::JUMP, KEY_SPACE);
    BindActionKey(InputAction::QUIT, KEY_ESCAPE);
}

InputManager::~InputManager()
{
    delete p_Impl;
}

void InputManager::BindActionKey(InputAction action, int key)
{
    p_Impl->m_keyBindings_[action] = key;
}

bool InputManager::IsActionHeld(InputAction action) const
{
    auto it = p_Impl->m_keyBindings_.find(action);
    if (it != p_Impl->m_keyBindings_.end())
    {
        return IsKeyDown(it->second);
    }
    return false;
}

bool InputManager::IsActionPressed(InputAction action) const
{
    auto it = p_Impl->m_keyBindings_.find(action);
    if (it != p_Impl->m_keyBindings_.end())
    {
        return IsKeyPressed(it->second);
    }
    return false;
}