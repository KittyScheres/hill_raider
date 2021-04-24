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
		GameCallback* m_GameCallback = nullptr;
		InputManager* m_InputManager = nullptr;
		PauseScreen* m_PauseScreen = nullptr;
		Ui* m_Ui = nullptr;
		Player* m_Player = nullptr;
		Floor* m_Floor = nullptr;
		bool m_GamePaused = false;

	public:
		Gameplay(GameCallback* callback);
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