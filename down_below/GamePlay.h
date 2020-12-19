#pragma once

#include "State.h"
#include "StateCallback.h"
#include "InputManager.h"
#include "PauseScreen.h"
#include "Ui.h"
#include "Player.h"
#include "Floor.h"
#include "GameData.h"
#include "AStar.h"
#include <vector>

namespace HillRaider
{
	class GamePlay: public State
	{
	private:
		StateCallback* callback = nullptr;
		InputManager* inputManager = nullptr;
		bool gamePaused = false;
		PauseScreen* pauseScreen = nullptr;
		Ui* ui = nullptr;
		Player* player = nullptr;
		Floor* floor = nullptr;

	public:
		GamePlay(StateCallback* iCallback);
		void Update(float deltaTime);
		void LateUpdate();
		void Render(Tmpl8::Surface* screen);
		~GamePlay();
	private:
		void CheckTileMapCollision(std::vector<std::vector<int>> hitbox);
	};
}