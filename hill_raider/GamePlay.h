#pragma once

#include "state.h"
#include "gameCallback.h"
#include "gamePlayCallback.h"
#include "lose.h"
#include "win.h"
#include "inputManager.h"
#include "pauseScreen.h"
#include "ui.h"
#include "player.h"
#include "floor.h"
#include "gameData.h"
#include "aStar.h"
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