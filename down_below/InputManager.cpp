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
		delete instance;
		instance = nullptr;
	}

	// --------------------------------------------------
	// 
	// --------------------------------------------------
	void InputManager::UpdateKeysState()
	{
		for (int i = 0; i < (sizeof(previousKeyState) / sizeof(bool)); i++) {
			previousKeyState[i] = currentKeysState[i];
		}

		currentKeysState[ENTER] = GetAsyncKeyState(VK_RETURN);
		currentKeysState[ESCAPE] = GetAsyncKeyState(VK_ESCAPE);
		currentKeysState[UP] = GetAsyncKeyState(VK_UP);
		currentKeysState[RIGHT] = GetAsyncKeyState(VK_RIGHT);
		currentKeysState[DOWN] = GetAsyncKeyState(VK_DOWN);
		currentKeysState[LEFT] = GetAsyncKeyState(VK_LEFT);
	}

	// --------------------------------------------------
	// 
	// --------------------------------------------------
	bool InputManager::KeyDown(Keys key)
	{
		return currentKeysState[key];
	}
	
	// --------------------------------------------------
	// 
	// --------------------------------------------------
	bool InputManager::KeyUp(Keys key)
	{
		return !currentKeysState[key];
	}
	
	// --------------------------------------------------
	// 
	// --------------------------------------------------
	bool InputManager::KeyPressed(Keys key)
	{
		return !previousKeyState[key] && currentKeysState[key];
	}

	// --------------------------------------------------
	// 
	// --------------------------------------------------
	InputManager::~InputManager(){}
}