#pragma once

#include <Windows.h>
#include "KeyBinding.h"

namespace HillRaider
{
	// --------------------------------------------------
	// This class contains methods for getting and checking
	// the keyboard inputs for the game.
	// --------------------------------------------------
	class InputManager
	{
	private:
		static InputManager* s_Instance;
		bool m_CurrentKeysState[8] { false, false, false, false, false, false, false, false };
		bool m_PreviousKeyState[8] { false, false, false, false, false, false, false, false };

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