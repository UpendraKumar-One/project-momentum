#include "vortex/core/containers/hash_map.hpp"
#include "vortex/core/input/input_manager.hpp"

using namespace Vortex::Core;

struct Vortex::Core::Impl
{
    Vortex::Containers::HashMap<InputAction, InputBackend::KeyCode> m_keyBindings_;
};

InputManager::InputManager()
{
    p_Impl = new Impl;

    BindActionKey(InputAction::UP, InputBackend::KeyCode::W);
    BindActionKey(InputAction::RIGHT, InputBackend::KeyCode::D);
    BindActionKey(InputAction::DOWN, InputBackend::KeyCode::S);
    BindActionKey(InputAction::LEFT, InputBackend::KeyCode::A);
    BindActionKey(InputAction::JUMP, InputBackend::KeyCode::SPACE);
    BindActionKey(InputAction::QUIT, InputBackend::KeyCode::ESC);
}

InputManager::~InputManager()
{
    delete p_Impl;
}

void InputManager::BindActionKey(InputAction action, InputBackend::KeyCode key)
{
    p_Impl->m_keyBindings_[action] = key;
}

bool InputManager::IsActionHeld(InputAction action) const
{
    auto it = p_Impl->m_keyBindings_.find(action);
    if (it != p_Impl->m_keyBindings_.end())
    {
        return InputBackend::IsHardwareKeyDown(it->second);
    }
    return false;
}

bool InputManager::IsActionPressed(InputAction action) const
{
    auto it = p_Impl->m_keyBindings_.find(action);
    if (it != p_Impl->m_keyBindings_.end())
    {
        return InputBackend::IsHardwareKeyPressed(it->second);
    }
    return false;
}