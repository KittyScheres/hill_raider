#include "GamePlay.h"

namespace DownBelow
{
	// --------------------------------------------------
	//
	// --------------------------------------------------
	GamePlay::GamePlay(StateCallback* iCallback)
	{
		callback = iCallback;
		inputManager = InputManager::GetInstance();
		pauseScreen = new PauseScreen();
		ui = new Ui();
		player = new Player(0, 0, 325.f, 64, 64);
		floor = new Floor();
		GameData::GetInstance();
	}

	// --------------------------------------------------
	//
	// --------------------------------------------------
	void GamePlay::Update(float deltaTime)
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
		}
	}

	// --------------------------------------------------
	//
	// --------------------------------------------------
	void GamePlay::LateUpdate()
	{
		if (!gamePaused) {
			player->LateUpdate();

			int playerX = player->GetPosition()[0];
			int playerY = player->GetPosition()[1];

			switch (floor->GetCurrentRoom()->GetTileMap()->GetCollision(playerX, playerY)) {
			case 'w':
				floor->MoveToNextRoom(Floor::UP);
				player->SetPosition(7 * 64, 7 * 64);
				break;

			case 'd':
				floor->MoveToNextRoom(Floor::RIGHT);
				player->SetPosition(64, 5 * 64);
				break;

			case 's':
				floor->MoveToNextRoom(Floor::DOWN);
				player->SetPosition(7 * 64, 64);
				break;

			case 'a':
				floor->MoveToNextRoom(Floor::LEFT);
				player->SetPosition(13 * 64, 5 * 64);
				break;
			}
		}
	}

	// --------------------------------------------------
	//
	// --------------------------------------------------
	void GamePlay::Render(Tmpl8::Surface* screen)
	{
		if (gamePaused) {
			pauseScreen->Render(screen);
		}
		else {
			floor->Render(screen);
			player->Render(screen);
			ui->Render(screen);
		}
	}

	// --------------------------------------------------
	//
	// --------------------------------------------------
	GamePlay::~GamePlay()
	{
		callback = nullptr;
		inputManager = nullptr;

		delete pauseScreen;
		pauseScreen = nullptr;

		delete ui;
		ui = nullptr;

		delete player;
		player = nullptr;

		delete floor;
		floor = nullptr;

		GameData::DestroyInstance();
	}
}