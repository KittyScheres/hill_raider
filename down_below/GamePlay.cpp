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
		player = new Player(64 * 8, 64 * 5, 325.f, 40, 40);
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
			std::vector<std::vector<int>> hitbox = player->GetHitbox()->GetBoxPoints();
			CheckTileMapCollision(hitbox);
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

	// --------------------------------------------------
	//
	// --------------------------------------------------
	void GamePlay::CheckTileMapCollision(std::vector<std::vector<int>> hitbox) {
		char collisionChar = ' ';
		int pointX = 0;
		int pointY = 0;

		for (int i = 0; i < 4; i++) {
			if (floor->GetCurrentRoom()->GetTileMap()->GetCollision(hitbox[i][0], hitbox[i][1]) != ' ' && collisionChar != 'x') {
				collisionChar = floor->GetCurrentRoom()->GetTileMap()->GetCollision(hitbox[i][0], hitbox[i][1]);
				pointX = hitbox[i][0];
				pointY = hitbox[i][1];
			}
		}

		switch (collisionChar) {
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

		case 'x':
			switch (player->GetDirection())
			{
			case Player::MovementDirection::UP:
				player->SetPosition(player->GetPosition()[0], player->GetPosition()[1] + (64 - ((pointY % 64) - 1)));
				break;

			case Player::MovementDirection::RIGHT:
				player->SetPosition(player->GetPosition()[0] - ((pointX % 64) + 1), player->GetPosition()[1]);
				break;

			case Player::MovementDirection::DOWN:
				player->SetPosition(player->GetPosition()[0], player->GetPosition()[1] - ((pointY % 64) + 1));
				break;

			case Player::MovementDirection::LEFT:
				player->SetPosition(player->GetPosition()[0] + (64 - ((pointX % 64) - 1)), player->GetPosition()[1]);
				break;
			}
			break;
		}
	}
}