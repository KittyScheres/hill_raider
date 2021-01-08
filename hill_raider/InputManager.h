#pragma once

#include <Windows.h>

namespace HillRaider
{
	class InputManager
	{
	public:
		enum class Keys {ENTER = 0, ESCAPE, UP, RIGHT, DOWN, LEFT, SPACE};

	private:
		static InputManager* instance;
		bool currentKeysState[7] { false, false, false, false, false, false, false };
		bool previousKeyState[7] { false, false, false, false, false, false, false };

	public:
		static InputManager* GetInstance();
		static void DestroyInstance();
		void UpdateKeysState();
		bool KeyDown(Keys key);
		bool KeyUp(Keys key);
		bool KeyPressed(Keys key);
		bool KeyLetGo(Keys key);

	private:
		InputManager();
		~InputManager();
	};
}