#include "GamePlay.h"

namespace HillRaider
{
	// --------------------------------------------------
	// This constructor is used to initialize the components
	// for the gameplay state.
	// --------------------------------------------------
	Gameplay::Gameplay(GameCallback* iCallback)
	{
		callback = iCallback;
		pauseScreen = new PauseScreen(callback);
		player = new Player((64 * 7) + 32, (64 * 4) + 32);
		player->SetGamePlayCallback(this);
		floor = new Floor();
		ui = new Ui();
	}

	// --------------------------------------------------
	// This method is used to setup the singleton components
	// for the gameplay state which might have been destroyed
	// on the state change.
	// --------------------------------------------------
	void Gameplay::SetupSingletons()
	{
		GameData::GetInstance();
		AStar::GetIntance()->SetEndGoal(player);
		inputManager = InputManager::GetInstance();
	}

	// --------------------------------------------------
	// This method is used to update the components for
	// the gameplay state.
	// --------------------------------------------------
	void Gameplay::Update(float deltaTime)
	{
		if (gamePaused) {
			if (inputManager->KeyPressed(InputManager::Keys::ESCAPE)) {
				gamePaused = false;
				pauseScreen->GamePause();
			}

			pauseScreen->Update(deltaTime);
		}
		else {
			if (inputManager->KeyPressed(InputManager::Keys::ESCAPE)) {
				gamePaused = true;
			}

			player->Update(deltaTime);
			floor->GetCurrentRoom()->Update(deltaTime);
		}
	}

	// --------------------------------------------------
	// This method is used to execute the collision checks
	// for the components for the gameplay state.
	// --------------------------------------------------
	void Gameplay::LateUpdate()
	{
		if (!gamePaused) {
			floor->GetCurrentRoom()->LateUpdate(player);
		}

		if (GameData::GetInstance()->playerHealth <= 0) {
			callback->SetNextState(new Lose(callback));
		}
	}

	// --------------------------------------------------
	// This method is used to draw the components for the
	// gameplay state on to the screen.
	// --------------------------------------------------
	void Gameplay::Render(Tmpl8::Surface* screen)
	{
		if (gamePaused) {
			pauseScreen->Render(screen);
		}
		else {
			floor->GetCurrentRoom()->Render(screen);
			player->Render(screen);
			ui->Render(screen);
		}
	}

	// --------------------------------------------------
	// This method is used to check if the room has been
	// cleared.
	// --------------------------------------------------
	bool Gameplay::HasRoomBeenCleared() {
		return floor->GetCurrentRoom()->RoomCleared();
	}

	// --------------------------------------------------
	// This method is used to move the player to a
	// new room.
	// --------------------------------------------------
	void Gameplay::MovePlayerToNextRoom(Direction direction) {
		floor->MoveToNextRoom(direction);
	}

	// --------------------------------------------------
	// This method is called when the player has met the
	// the win condition of the game.
	// --------------------------------------------------
	void Gameplay::PlayerHasWonTheGame() {
		callback->SetNextState(new Win(callback, GameData::GetInstance()->playerPoints));
	}

	// --------------------------------------------------
	// This destructor is used to safely free the memory
	// of the components for the gameplay state.
	// --------------------------------------------------
	Gameplay::~Gameplay()
	{
		callback = nullptr;
		inputManager = nullptr;

		if (pauseScreen != nullptr) {
			delete pauseScreen;
			pauseScreen = nullptr;
		}

		if (ui != nullptr) {
			delete ui;
			ui = nullptr;
		}

		if (player != nullptr) {
			delete player;
			player = nullptr;
		}

		if (floor != nullptr) {
			delete floor;
			floor = nullptr;
		}

		AStar::DestroyInstance();
		GameData::DestroyInstance();
	}
}