#include "InputManager.h"

#define VK_W              0x57
#define VK_D              0x44
#define VK_S              0x53
#define VK_A              0x41
#define VK_E			  0x45

namespace HillRaider
{
	InputManager* InputManager::s_Instance = nullptr;

	// --------------------------------------------------
	// This method returns the singelton instance of
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
	// and the current key state lists for the input manager.
	// --------------------------------------------------
	void InputManager::UpdateKeysState()
	{
		for (int i = 0; i < (sizeof(m_PreviousKeyState) / sizeof(bool)); i++) {
			m_PreviousKeyState[i] = m_CurrentKeysState[i];
		}

		m_CurrentKeysState[(int)Keys::ENTER] = GetAsyncKeyState(VK_RETURN);
		m_CurrentKeysState[(int)Keys::ESCAPE] = GetAsyncKeyState(VK_ESCAPE);
		m_CurrentKeysState[(int)Keys::UP] = (GetAsyncKeyState(VK_UP) || GetAsyncKeyState(VK_W));
		m_CurrentKeysState[(int)Keys::RIGHT] = (GetAsyncKeyState(VK_RIGHT) || GetAsyncKeyState(VK_D));
		m_CurrentKeysState[(int)Keys::DOWN] = (GetAsyncKeyState(VK_DOWN) || GetAsyncKeyState(VK_S));
		m_CurrentKeysState[(int)Keys::LEFT] = (GetAsyncKeyState(VK_LEFT) || GetAsyncKeyState(VK_A));
		m_CurrentKeysState[(int)Keys::SPACE] = GetAsyncKeyState(VK_SPACE);
		m_CurrentKeysState[(int)Keys::E] = GetAsyncKeyState(VK_E);
	}

	// --------------------------------------------------
	// This method is used to check if a key is being 
	// pressed.
	// --------------------------------------------------
	bool InputManager::KeyDown(Keys key)
	{
		return m_CurrentKeysState[(int)key];
	}
	
	// --------------------------------------------------
	// This method is used to check if a key is not being 
	// pressed
	// --------------------------------------------------
	bool InputManager::KeyUp(Keys key)
	{
		return !m_CurrentKeysState[(int)key];
	}
	
	// --------------------------------------------------
	// This mehtod is used to check if a key has just 
	// been pressed.
	// --------------------------------------------------
	bool InputManager::KeyPressed(Keys key)
	{
		return !m_PreviousKeyState[(int)key] && m_CurrentKeysState[(int)key];
	}

	// --------------------------------------------------
	// This method is used to check if a key has just
	// been let go off.
	// --------------------------------------------------
	bool InputManager::KeyLetGo(Keys key) {
		return m_PreviousKeyState[(int)key] && !m_CurrentKeysState[(int)key];
	}
}