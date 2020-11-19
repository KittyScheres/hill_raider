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
		}
	}

	// --------------------------------------------------
	//
	// --------------------------------------------------
	void GamePlay::LateUpdate()
	{
		if (!gamePaused) {
			
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

		GameData::DestroyInstance();
	}
}