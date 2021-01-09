#include "GamePlay.h"

namespace HillRaider
{
	// --------------------------------------------------
	//
	// --------------------------------------------------
	GamePlay::GamePlay(GameCallback* iCallback)
	{
		callback = iCallback;
		pauseScreen = new PauseScreen(callback);
		player = new Player((64 * 7) + 32, (64 * 4) + 32);
		floor = new Floor();
		ui = new Ui();
	}

	// --------------------------------------------------
	//
	// --------------------------------------------------
	void GamePlay::SetupSingletons()
	{
		GameData::GetInstance();
		AStar::GetIntance()->SetEndGoal(player);
		inputManager = InputManager::GetInstance();
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
			floor->GetCurrentRoom()->Update(deltaTime);
		}
	}

	// --------------------------------------------------
	//
	// --------------------------------------------------
	void GamePlay::LateUpdate()
	{
		if (!gamePaused) {
			// check and apply entity collision
			floor->GetCurrentRoom()->RoomCheckEntityCollision(player);
			
			// check and apply tile map collision
			CheckTileMapCollision(player->GetHitbox()->GetBoxPoints());
			floor->GetCurrentRoom()->RoomCheckTileMapCollsion();
		}

		if (GameData::GetInstance()->playerHealth <= 0) {
			callback->SetNextState(new StartMenu(callback));
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
			floor->GetCurrentRoom()->Render(screen);
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

	// --------------------------------------------------
	//
	// --------------------------------------------------
	void GamePlay::CheckTileMapCollision(std::vector<std::vector<int>> hitbox) {
		char collisionChar = ' ';
		short index = 0;

		for (int i = 0; i < 4; i++) {
			if (floor->GetCurrentRoom()->GetTileMap()->GetCollision(hitbox[i][0], hitbox[i][1]) != ' ' && collisionChar != 'x') {
				collisionChar = floor->GetCurrentRoom()->GetTileMap()->GetCollision(hitbox[i][0], hitbox[i][1]);
				index = i;
			}
		}

		switch (collisionChar) {
		case 'w':
			if (floor->GetCurrentRoom()->RoomCleared()) {
				floor->MoveToNextRoom(Floor::MoveDirection::UP);
				player->SetPosition((7 * 64) + (player->GetSprite()->GetWidth() / 2), (7 * 64) + (player->GetSprite()->GetHeight() / 2));
			}
			else{
				ApplyVerticalTileMapCollision(index, hitbox[index][1]);
			}
			break;

		case 'd':
			if (floor->GetCurrentRoom()->RoomCleared()) {
				floor->MoveToNextRoom(Floor::MoveDirection::RIGHT);
				player->SetPosition(64 + (player->GetSprite()->GetWidth() / 2), (4 * 64) + (player->GetSprite()->GetHeight() / 2));
			}
			else {
				ApplyHorizontalTileMapCollision(index, hitbox[index][0]);
			}
			break;

		case 's':
			if (floor->GetCurrentRoom()->RoomCleared()) {
				floor->MoveToNextRoom(Floor::MoveDirection::DOWN);
				player->SetPosition((7 * 64) + (player->GetSprite()->GetWidth() / 2), 64 + (player->GetSprite()->GetHeight() / 2));
			}
			else {
				ApplyVerticalTileMapCollision(index, hitbox[index][1]);
			}
			break;

		case 'a':
			if (floor->GetCurrentRoom()->RoomCleared()) {
				floor->MoveToNextRoom(Floor::MoveDirection::LEFT);
				player->SetPosition((13 * 64) + (player->GetSprite()->GetWidth() / 2), (4 * 64) + (player->GetSprite()->GetHeight() / 2));
			}
			else {
				ApplyHorizontalTileMapCollision(index, hitbox[index][0]);
			}
			break;

		case 'x':
			switch (player->GetDirection())
			{
			case Entity::MovementDirection::UP:
			case Entity::MovementDirection::DOWN:
				ApplyVerticalTileMapCollision(index, hitbox[index][1]);
				break;

			case Entity::MovementDirection::LEFT:
			case Entity::MovementDirection::RIGHT:
				ApplyHorizontalTileMapCollision(index, hitbox[index][0]);
				break;
			}
			break;
		}
	}

	// --------------------------------------------------
	//
	// --------------------------------------------------
	void GamePlay::ApplyVerticalTileMapCollision(int hitboxPointIndex, int hitboxPointYPos)
	{
		switch (hitboxPointIndex & 2)
		{
		case 0:
			player->SetPosition(player->GetPosition()[0], player->GetPosition()[1] + (64 - (hitboxPointYPos & 63)));
			break;

		case 2:
			player->SetPosition(player->GetPosition()[0], player->GetPosition()[1] - (hitboxPointYPos & 63));
			break;
		}

	}

	// --------------------------------------------------
	//
	// --------------------------------------------------
	void GamePlay::ApplyHorizontalTileMapCollision(int hitboxPointIndex, int hitboxPointXPos)
	{
		switch (hitboxPointIndex & 1)
		{
		case 0:
			player->SetPosition(player->GetPosition()[0] + (64 - (hitboxPointXPos & 63)), player->GetPosition()[1]);
			break;

		case 1:
			player->SetPosition(player->GetPosition()[0] - (hitboxPointXPos & 63), player->GetPosition()[1]);
			break;
		}
	}
}