#pragma once

#include <Windows.h>

namespace DownBelow
{
	class InputManager
	{
	public:
		enum class Keys {ENTER = 0, ESCAPE, UP, RIGHT, DOWN, LEFT};

	private:
		static InputManager* instance;
		bool currentKeysState[6] { false, false, false, false, false, false };
		bool previousKeyState[6]{ false, false, false, false, false, false };

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