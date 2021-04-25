#include "gamePlay.h"

namespace HillRaider
{
	// --------------------------------------------------
	// This constructor is used to initialize the components
	// of the gameplay state.
	// --------------------------------------------------
	Gameplay::Gameplay(GameCallback* callback)
	{
		m_GameCallback = callback;
		m_PauseScreen = new PauseScreen(m_GameCallback);
		m_Player = new Player((64 * 7) + 32, (64 * 4) + 32);
		m_Player->SetGamePlayCallback(this);
		m_Floor = new Floor();
		m_Ui = new Ui();
	}

	// --------------------------------------------------
	// This method is used to set up the singleton components
	// of the gameplay state which might have been destroyed
	// in the state change.
	// --------------------------------------------------
	void Gameplay::SetupSingletons()
	{
		GameData::GetInstance();
		AStar::GetIntance()->SetEndGoal(m_Player);
		m_InputManager = InputManager::GetInstance();
	}

	// --------------------------------------------------
	// This method is used to update the components of
	// the gameplay state.
	// --------------------------------------------------
	void Gameplay::Update(float deltaTime)
	{
		// Is the game paused?
		if (m_GamePaused) {
			// Check if the game needs to be unpaused
			if (m_InputManager->KeyPressed(KeyBinding::ESCAPE)) {
				m_GamePaused = false;
				m_PauseScreen->GamePause();
			}

			m_PauseScreen->Update(deltaTime);
		}
		else {
			// Check if the game needs to be paused
			if (m_InputManager->KeyPressed(KeyBinding::ESCAPE)) {
				m_GamePaused = true;
			}

			m_Player->Update(deltaTime);
			m_Floor->GetCurrentRoom()->Update(deltaTime);
		}
	}

	// --------------------------------------------------
	// This method is used to execute the collision checks
	// for the components of the gameplay state.
	// --------------------------------------------------
	void Gameplay::LateUpdate()
	{
		if (!m_GamePaused) {
			// Apply collision detection for the entities
			m_Floor->GetCurrentRoom()->LateUpdate(m_Player);
		}

		// Check if the player has died
		if (GameData::GetInstance()->m_PlayerHealth <= 0) {
			m_GameCallback->SetNextState(new Lose(m_GameCallback));
		}
	}

	// --------------------------------------------------
	// This method is used to draw the components of the
	// gameplay state onto the screen.
	// --------------------------------------------------
	void Gameplay::Render(Tmpl8::Surface* screen)
	{
		if (m_GamePaused) {
			m_PauseScreen->Render(screen);
		}
		else {
			m_Floor->GetCurrentRoom()->Render(screen);
			m_Player->Render(screen);
			m_Ui->Render(screen);
		}
	}

	// --------------------------------------------------
	// This method is used to check if the room has been
	// cleared.
	// --------------------------------------------------
	bool Gameplay::HasRoomBeenCleared() {
		return m_Floor->GetCurrentRoom()->RoomCleared();
	}

	// --------------------------------------------------
	// This method is used to move the player to a
	// new room.
	// --------------------------------------------------
	void Gameplay::MovePlayerToNextRoom(Direction direction) {
		m_Floor->MoveToNextRoom(direction);
	}

	// --------------------------------------------------
	// This method is called when the player has met the
	// the win condition of the game.
	// --------------------------------------------------
	void Gameplay::PlayerHasWonTheGame() {
		m_GameCallback->SetNextState(new Win(m_GameCallback, GameData::GetInstance()->m_PlayerPoints));
	}

	// --------------------------------------------------
	// This destructor is used to safely free the memory
	// of the components of the gameplay state.
	// --------------------------------------------------
	Gameplay::~Gameplay()
	{
		m_GameCallback = nullptr;
		m_InputManager = nullptr;

		if (m_PauseScreen != nullptr) {
			delete m_PauseScreen;
			m_PauseScreen = nullptr;
		}

		if (m_Ui != nullptr) {
			delete m_Ui;
			m_Ui = nullptr;
		}

		if (m_Player != nullptr) {
			delete m_Player;
			m_Player = nullptr;
		}

		if (m_Floor != nullptr) {
			delete m_Floor;
			m_Floor = nullptr;
		}

		AStar::DestroyInstance();
		GameData::DestroyInstance();
	}
}