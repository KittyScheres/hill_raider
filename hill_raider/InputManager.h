#pragma once

#include "keyBinding.h"
#include <Windows.h>

namespace HillRaider
{
	// --------------------------------------------------
	// This class contains methods for getting and checking
	// the keyboard inputs for the game.
	// --------------------------------------------------
	class InputManager
	{
	private:
		const unsigned short c_VALUE_MASK = 1;

	private:
		static InputManager* s_Instance;
		unsigned short m_CurrentKeysState = 0;
		unsigned short m_PreviousKeyState = 0;

	public:
		static InputManager* GetInstance();
		static void DestroyInstance();
		void UpdateKeysState();
		bool KeyDown(KeyBinding key);
		bool KeyUp(KeyBinding key);
		bool KeyPressed(KeyBinding key);
		bool KeyLetGo(KeyBinding key);

	private:
		InputManager() {};
		~InputManager() {};
	};
}