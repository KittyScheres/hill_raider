#pragma once

#include "State.h"
#include "GameCallback.h"
#include "StartMenu.h"
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
		GameCallback* callback = nullptr;
		InputManager* inputManager = nullptr;
		bool gamePaused = false;
		PauseScreen* pauseScreen = nullptr;
		Ui* ui = nullptr;
		Player* player = nullptr;
		Floor* floor = nullptr;

	public:
		GamePlay(GameCallback* iCallback);
		void SetupSingletons();
		void Update(float deltaTime);
		void LateUpdate();
		void Render(Tmpl8::Surface* screen);
		~GamePlay();
	private:
		void CheckTileMapCollision(std::vector<std::vector<int>> hitbox);
		void ApplyVerticalTileMapCollision(int hitboxPointIndex , int hitboxPointYPos);
		void ApplyHorizontalTileMapCollision(int hitboxPointIndex, int hitboxPointXPos);
	};
}