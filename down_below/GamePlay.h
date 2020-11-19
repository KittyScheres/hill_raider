#pragma once

#include "State.h"
#include "StateCallback.h"
#include "InputManager.h"
#include "PauseScreen.h"
#include "GameData.h"

namespace DownBelow
{
	class GamePlay: public State
	{
	private:
		StateCallback* callback = nullptr;
		InputManager* inputManager = nullptr;
		bool gamePaused = false;
		PauseScreen* pauseScreen = nullptr;

	public:
		GamePlay(StateCallback* iCallback);
		void Update(float deltaTime);
		void LateUpdate();
		void Render(Tmpl8::Surface* screen);
		~GamePlay();
	};
}