#include "vortex/core/containers/hash_map.hpp"
#include "vortex/core/input_manager.hpp"

namespace vortex::core
{
    struct Impl
    {
        containers::HashMap<InputAction, input_backend::KeyCode> m_keyBindings;
    };

    InputManager::InputManager()
    {
        m_impl = new Impl;

        bindActionKey(InputAction::Up, input_backend::KeyCode::W);
        bindActionKey(InputAction::Right, input_backend::KeyCode::D);
        bindActionKey(InputAction::Down, input_backend::KeyCode::S);
        bindActionKey(InputAction::Left, input_backend::KeyCode::A);
        bindActionKey(InputAction::Jump, input_backend::KeyCode::Space);
        bindActionKey(InputAction::Quit, input_backend::KeyCode::Esc);
    }

    InputManager::~InputManager()
    {
        delete m_impl;
    }

    void InputManager::bindActionKey(InputAction action, input_backend::KeyCode key)
    {
        m_impl->m_keyBindings[action] = key;
    }

    bool InputManager::isActionHeld(InputAction action) const
    {
        auto it = m_impl->m_keyBindings.find(action);
        if (it != m_impl->m_keyBindings.end())
        {
            return input_backend::isHardwareKeyDown(it->second);
        }
        return false;
    }

    bool InputManager::isActionPressed(InputAction action) const
    {
        auto it = m_impl->m_keyBindings.find(action);
        if (it != m_impl->m_keyBindings.end())
        {
            return input_backend::isHardwareKeyPressed(it->second);
        }
        return false;
    }
}
