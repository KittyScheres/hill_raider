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
		player = new Player(64, 64, 325.f, 10, 10);
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

			std::vector<std::vector<int>> hitbox = player->GetHitbox()->GetBoxPoints();

			for (int i = 0; i < 4; i++) {
				if (floor->GetCurrentRoom()->GetTileMap()->GetCollision(hitbox[i][0], hitbox[i][1]) != ' ') {
					switch (floor->GetCurrentRoom()->GetTileMap()->GetCollision(hitbox[i][0], hitbox[i][1])) {
					case 'w':
						floor->MoveToNextRoom(Floor::UP);
						player->SetPosition((7 * 64) + (player->GetSprite()->GetWidth() / 2), (7 * 64) + (player->GetSprite()->GetHeight() / 2));
						break;

					case 'd':
						floor->MoveToNextRoom(Floor::RIGHT);
						player->SetPosition(64 + (player->GetSprite()->GetWidth() / 2), (4 * 64) + (player->GetSprite()->GetHeight() / 2));
						break;

					case 's':
						floor->MoveToNextRoom(Floor::DOWN);
						player->SetPosition((7 * 64) + (player->GetSprite()->GetWidth() / 2), 64 + (player->GetSprite()->GetHeight() / 2));
						break;

					case 'a':
						floor->MoveToNextRoom(Floor::LEFT);
						player->SetPosition((13 * 64) + (player->GetSprite()->GetWidth() / 2), (4 * 64) + (player->GetSprite()->GetHeight() / 2));
						break;
					}
					break;
				}
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