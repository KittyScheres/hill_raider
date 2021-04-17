#pragma once

#include "State.h"
#include "GameCallback.h"
#include "GamePlayCallback.h"
#include "Lose.h"
#include "Win.h"
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
	// --------------------------------------------------
	// The gameplay state class is used to initialize and keep
	// track off everything for the gameplay of the game.
	// --------------------------------------------------
	class Gameplay: public State, public GameplayCallback
	{
	private:
		GameCallback* callback = nullptr;
		InputManager* inputManager = nullptr;
		PauseScreen* pauseScreen = nullptr;
		Ui* ui = nullptr;
		Player* player = nullptr;
		Floor* floor = nullptr;
		bool gamePaused = false;

	public:
		Gameplay(GameCallback* iCallback);
		void SetupSingletons();
		void Update(float deltaTime);
		void LateUpdate();
		void Render(Tmpl8::Surface* screen);
		bool HasRoomBeenCleared();
		void MovePlayerToNextRoom(Direction direction);
		void PlayerHasWonTheGame();
		~Gameplay();
	};
}