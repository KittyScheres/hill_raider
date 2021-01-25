#pragma once

#include <Windows.h>

namespace HillRaider
{
	// --------------------------------------------------
	// This class contains methods for getting and checking
	// the keyboard inputs for the game.
	// --------------------------------------------------
	class InputManager
	{
	public:
		enum class Keys {ENTER = 0, ESCAPE, UP, RIGHT, DOWN, LEFT, SPACE, E};

	private:
		static InputManager* instance;
		bool currentKeysState[8] { false, false, false, false, false, false, false, false };
		bool previousKeyState[8] { false, false, false, false, false, false, false, false };

	public:
		static InputManager* GetInstance();
		static void DestroyInstance();
		void UpdateKeysState();
		bool KeyDown(Keys key);
		bool KeyUp(Keys key);
		bool KeyPressed(Keys key);
		bool KeyLetGo(Keys key);

	private:
		InputManager() {};
		~InputManager() {};
	};
}