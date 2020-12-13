#include "InputManager.h"

namespace DownBelow
{
	InputManager* InputManager::instance = nullptr;

	// --------------------------------------------------
	// 
	// --------------------------------------------------
	InputManager::InputManager(){}

	// --------------------------------------------------
	// 
	// --------------------------------------------------
	InputManager* InputManager::GetInstance()
	{
		if (instance == nullptr) {
			instance = new InputManager();
		}

		return instance;
	}

	// --------------------------------------------------
	// 
	// --------------------------------------------------
	void InputManager::DestroyInstance()
	{
		if (instance != nullptr) {
			delete instance;
			instance = nullptr;
		}
	}

	// --------------------------------------------------
	// 
	// --------------------------------------------------
	void InputManager::UpdateKeysState()
	{
		for (int i = 0; i < (sizeof(previousKeyState) / sizeof(bool)); i++) {
			previousKeyState[i] = currentKeysState[i];
		}

		currentKeysState[(int)Keys::ENTER] = GetAsyncKeyState(VK_RETURN);
		currentKeysState[(int)Keys::ESCAPE] = GetAsyncKeyState(VK_ESCAPE);
		currentKeysState[(int)Keys::UP] = GetAsyncKeyState(VK_UP);
		currentKeysState[(int)Keys::RIGHT] = GetAsyncKeyState(VK_RIGHT);
		currentKeysState[(int)Keys::DOWN] = GetAsyncKeyState(VK_DOWN);
		currentKeysState[(int)Keys::LEFT] = GetAsyncKeyState(VK_LEFT);
	}

	// --------------------------------------------------
	// 
	// --------------------------------------------------
	bool InputManager::KeyDown(Keys key)
	{
		return currentKeysState[(int)key];
	}
	
	// --------------------------------------------------
	// 
	// --------------------------------------------------
	bool InputManager::KeyUp(Keys key)
	{
		return !currentKeysState[(int)key];
	}
	
	// --------------------------------------------------
	// 
	// --------------------------------------------------
	bool InputManager::KeyPressed(Keys key)
	{
		return !previousKeyState[(int)key] && currentKeysState[(int)key];
	}

	// --------------------------------------------------
	// 
	// --------------------------------------------------
	bool InputManager::KeyLetGo(Keys key) {
		return previousKeyState[(int)key] && !currentKeysState[(int)key];
	}

	// --------------------------------------------------
	// 
	// --------------------------------------------------
	InputManager::~InputManager(){}
}