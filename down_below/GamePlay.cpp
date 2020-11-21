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

		GameData::DestroyInstance();
	}
}