#include "inputManager.h"

#define VK_W 0x57 // w key
#define VK_D 0x44 // d key
#define VK_S 0x53 // s key
#define VK_A 0x41 // a key
#define VK_E 0x45 // e key

namespace HillRaider
{
	InputManager* InputManager::s_Instance = nullptr;

	// --------------------------------------------------
	// This method returns the singleton instance of
	// the input manager class.
	// --------------------------------------------------
	InputManager* InputManager::GetInstance()
	{
		if (s_Instance == nullptr) {
			s_Instance = new InputManager();
		}

		return s_Instance;
	}

	// --------------------------------------------------
	// This method destroys the singleton instance of 
	// the input manager class.
	// --------------------------------------------------
	void InputManager::DestroyInstance()
	{
		if (s_Instance != nullptr) {
			delete s_Instance;
			s_Instance = nullptr;
		}
	}

	// --------------------------------------------------
	// This method is used to update the previous key state
	// and the current key state for the input manager.
	// --------------------------------------------------
	void InputManager::UpdateKeysState()
	{
		// Update the previous key state
		m_PreviousKeyState = m_CurrentKeysState;

		// Update the current key state
		m_CurrentKeysState = GetAsyncKeyState(VK_E);
		m_CurrentKeysState = (m_CurrentKeysState << 1) + GetAsyncKeyState(VK_SPACE);
		m_CurrentKeysState = (m_CurrentKeysState << 1) + (unsigned short)(GetAsyncKeyState(VK_LEFT) || GetAsyncKeyState(VK_A));
		m_CurrentKeysState = (m_CurrentKeysState << 1) + (unsigned short)(GetAsyncKeyState(VK_DOWN) || GetAsyncKeyState(VK_S));
		m_CurrentKeysState = (m_CurrentKeysState << 1) + (unsigned short)(GetAsyncKeyState(VK_RIGHT) || GetAsyncKeyState(VK_D));
		m_CurrentKeysState = (m_CurrentKeysState << 1) + (unsigned short)(GetAsyncKeyState(VK_UP) || GetAsyncKeyState(VK_W));
		m_CurrentKeysState = (m_CurrentKeysState << 1) + GetAsyncKeyState(VK_ESCAPE);
		m_CurrentKeysState = (m_CurrentKeysState << 1) + GetAsyncKeyState(VK_RETURN);
	}

	// --------------------------------------------------
	// This method is used to check if a key is being 
	// pressed.
	// --------------------------------------------------
	bool InputManager::KeyDown(KeyBinding key)
	{
		return (bool)((m_CurrentKeysState >> (unsigned short)key) & c_VALUE_MASK);
	}
	
	// --------------------------------------------------
	// This method is used to check if a key is not being 
	// pressed.
	// --------------------------------------------------
	bool InputManager::KeyUp(KeyBinding key)
	{
		return !(bool)((m_CurrentKeysState >> (unsigned short)key) & c_VALUE_MASK);
	}
	
	// --------------------------------------------------
	// This method is used to check if a key has just 
	// been pressed.
	// --------------------------------------------------
	bool InputManager::KeyPressed(KeyBinding key)
	{
		return !(bool)((m_PreviousKeyState >> (unsigned short)key) & c_VALUE_MASK) && (bool)((m_CurrentKeysState >> (unsigned short)key) & c_VALUE_MASK);
	}

	// --------------------------------------------------
	// This method is used to check if a key has just
	// been let go of.
	// --------------------------------------------------
	bool InputManager::KeyLetGo(KeyBinding key) {
		return (bool)((m_PreviousKeyState >> (unsigned short)key) & c_VALUE_MASK) && !(bool)((m_CurrentKeysState >> (unsigned short)key) & c_VALUE_MASK);
	}
}