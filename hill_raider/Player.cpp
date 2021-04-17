#include "Player.h"

namespace HillRaider
{
	// --------------------------------------------------
	// This constructor is used to setup the properties 
	// for a player entity.
	// --------------------------------------------------
	Player::Player(int iX, int iY): Entity(iX, iY, 28, 62)
	{
		inputManager = InputManager::GetInstance();
		legsAnimation = new Animation("assets/entities/black_ant_legs.png", 4, 4, timePerframeWalkingAnimation, iX, iY, true);
		bodyAnimation = new Animation("assets/entities/black_ant_body.png", 4, 4, 75.f, iX, iY, false);
		attackHitbox = new Hitbox(x, y + attackHitboxOffset, attackHitboxWidth, attackHitboxHeight);
	}

	// --------------------------------------------------
	// This method is used to update a player entity.
	// --------------------------------------------------
	void Player::Update(float deltaTime)
	{
		if (inputManager->KeyPressed(InputManager::Keys::E)) {
			Heal();
		}

		if (!lungeFlag) {
			CheckForMovementKeyPressed();
			CheckForMovementKeyLetGo();
			MovePlayer(deltaTime);
			
			if (!lungeCooldownFlag) {
				if (inputManager->KeyPressed(InputManager::Keys::SPACE)) {
					legsAnimation->SetTimePerFrame(lungeTimePerFrameWalkingAnimation);
					lungeFlag = true;
					lungeCooldownFlag = true;
				}
			}
			else {
				//attack cooldown timer
				if (lungeCooldownTimer >= lungeCooldown) {
					lungeCooldownFlag = false;
					lungeCooldownTimer = 0.f;
					bodyAnimation->SetCurrentXFrame(0);
				}
				else {
					lungeCooldownTimer += deltaTime;
					bodyAnimation->UpdateAnimation(deltaTime);
				}
			}
		}
		else {
			//is attacking
			legsAnimation->UpdateAnimation(deltaTime);
			Lunge(deltaTime);

			if (lungeDurationTimer >= lungeDuration) {
				legsAnimation->SetTimePerFrame(timePerframeWalkingAnimation);
				lungeFlag = false;
				lungeDurationTimer = 0.f;
			}
			else {
				lungeDurationTimer += deltaTime;
			}
		}

		SetPosition(x, y);
	}
	
	// --------------------------------------------------
	// This method is used to process the collisions between
	// a player entity and other entities.
	// --------------------------------------------------
	void Player::LateUpdate(TileMap* tileMap, std::list<Entity*> entityList)
	{
		ProcessTileMapCollision(tileMap);

		for (Entity* entity : entityList) {
			FoodPointsPickup* foodPointPickup = dynamic_cast<FoodPointsPickup*>(entity);

			//entity on entity collision
			if (foodPointPickup == nullptr) {
				if (TestBoxCollision(hitbox, entity)) {
					ApplyEntityCollision(entity);
					SetPosition(x, y);
				}
			}

			//entity on attack hitbox collision
			if (lungeFlag && foodPointPickup == nullptr) {
				if (TestBoxCollision(attackHitbox, entity)) {
					EnemyAnt* enemyAnt = dynamic_cast<EnemyAnt*>(entity);
					if (enemyAnt != nullptr) {
						enemyAnt->TakeDamage();
						lungeFlag = false;
						lungeDurationTimer = 0.f;
					}
				}
			}

			//entity on food points pickup entity collision
			if (foodPointPickup != nullptr) {
				if (TestBoxCollision(hitbox, entity)) {
					GameData* gameDataInstance = GameData::GetInstance();
					gameDataInstance->playerPoints += foodPointPickup->GetPoints();
					if (gameDataInstance->playerPoints > gameDataInstance->MAX_POINTS) {
						gameDataInstance->playerPoints -= gameDataInstance->playerPoints % gameDataInstance->MAX_POINTS;
					}
					foodPointPickup->RemoveFoodPointsPickup();
				}
			}
		}
	}

	// --------------------------------------------------
	// This method is used to draw a player entity on
	// to the screen.
	// --------------------------------------------------
	void Player::Render(Tmpl8::Surface* screen)
	{
		legsAnimation->SetPosition(x - (bodyAnimation->GetWidth() / 2), y - (bodyAnimation->GetHeight() / 2));
		bodyAnimation->SetPosition(x - (bodyAnimation->GetWidth() / 2), y - (bodyAnimation->GetHeight() / 2));
		
		legsAnimation->DrawAnimation(screen);
		bodyAnimation->DrawAnimation(screen);
	}

	// --------------------------------------------------
	// This method is called to make a player entity take
	// damage.
	// --------------------------------------------------
	void Player::TakeDamage() {
		--GameData::GetInstance()->playerHealth;
	}

	// --------------------------------------------------
	// This method is used to set the gameplay callback
	// for the player.
	// --------------------------------------------------
	void Player::SetGamePlayCallback(GameplayCallback* callback) {
		gameplayCallback = callback;
	}

	// --------------------------------------------------
	// This method is used to set the position of a player
	// entity.
	// --------------------------------------------------
	void Player::SetPosition(int iX, int iY) {
		x = iX;
		y = iY;
		hitbox->SetPosition(x, y);

		switch (direction)
		{
		case Direction::UP :
		case Direction::DOWN :
			attackHitbox->SetPosition(x, y + attackHitboxOffset);
			break;

		case Direction::LEFT :
		case Direction::RIGHT :
			attackHitbox->SetPosition(x + attackHitboxOffset, y);
			break;
		}
	}

	// --------------------------------------------------
	// This method is used to set the direction a player
	// entity is facing.
	// --------------------------------------------------
	void Player::SetDirection(Direction iDirection) {
		direction = iDirection;

		legsAnimation->SetCurrentYFrame((int)direction);
		bodyAnimation->SetCurrentYFrame((int)direction);

		switch (direction)
		{
		case Direction::UP:
			attackHitboxOffset = -std::abs(attackHitboxOffset);
			hitbox->SetWidth(width);
			hitbox->SetHeight(height);
			attackHitbox->SetWidth(attackHitboxWidth);
			attackHitbox->SetHeight(attackHitboxHeight);
			break;
		
		case Direction::RIGHT:
			attackHitboxOffset = std::abs(attackHitboxOffset);
			hitbox->SetWidth(height);
			hitbox->SetHeight(width);
			attackHitbox->SetWidth(attackHitboxHeight);
			attackHitbox->SetHeight(attackHitboxWidth);
			break;

		case Direction::DOWN:
			attackHitboxOffset = std::abs(attackHitboxOffset);
			hitbox->SetWidth(width);
			hitbox->SetHeight(height);
			attackHitbox->SetWidth(attackHitboxWidth);
			attackHitbox->SetHeight(attackHitboxHeight);
			break;

		case Direction::LEFT:
			attackHitboxOffset = -std::abs(attackHitboxOffset);
			hitbox->SetWidth(height);
			hitbox->SetHeight(width);
			attackHitbox->SetWidth(attackHitboxHeight);
			attackHitbox->SetHeight(attackHitboxWidth);
			break;
		}
	}

	// --------------------------------------------------
	// This methos is used to get the direction a player
	// entity.
	// --------------------------------------------------
	Direction Player::GetDirection() {
		return direction;
	}

	// --------------------------------------------------
	// This method is used to get the sprite of a player
	// entity.
	// --------------------------------------------------
	Animation* Player::GetSprite()
	{
		return bodyAnimation;
	}

	// --------------------------------------------------
	// This destructor is used to safely free the memory
	// of the propeties of a player entity.
	// --------------------------------------------------
	Player::~Player()
	{
		if (legsAnimation != nullptr) {
			delete legsAnimation;
			legsAnimation = nullptr;
		}

		if (bodyAnimation != nullptr) {
			delete bodyAnimation;
			bodyAnimation = nullptr;
		}

		if (attackHitbox != nullptr) {
			delete attackHitbox;
			attackHitbox = nullptr;
		}

		gameplayCallback = nullptr;
		inputManager = nullptr;
	}

	// --------------------------------------------------
	// This method is used to check if a new direction key
	// has been pressed.
	// --------------------------------------------------
	void Player::CheckForMovementKeyPressed()
	{
		if (inputManager->KeyPressed(InputManager::Keys::UP)) {
			SetDirection(Direction::UP);
		}

		if (inputManager->KeyPressed(InputManager::Keys::RIGHT)) {
			SetDirection(Direction::RIGHT);
		}

		if (inputManager->KeyPressed(InputManager::Keys::DOWN)) {
			SetDirection(Direction::DOWN);
		}

		if (inputManager->KeyPressed(InputManager::Keys::LEFT)) {
			SetDirection(Direction::LEFT);
		}
	}

	// --------------------------------------------------
	// This method is used to check if the direction key 
	// of the current direction has been let go of.
	// --------------------------------------------------
	void Player::CheckForMovementKeyLetGo()
	{
		switch (direction)
		{
		case Direction::UP:
			if (inputManager->KeyLetGo(InputManager::Keys::UP)) {
				if (inputManager->KeyDown(InputManager::Keys::RIGHT)) {
					SetDirection(Direction::RIGHT);
				}
				else if (inputManager->KeyDown(InputManager::Keys::DOWN)) {
					SetDirection(Direction::DOWN);
				}
				else if (inputManager->KeyDown(InputManager::Keys::LEFT)) {
					SetDirection(Direction::LEFT);
				}
			}
			break;

		case Direction::RIGHT:
			if (inputManager->KeyLetGo(InputManager::Keys::RIGHT)) {
				if (inputManager->KeyDown(InputManager::Keys::DOWN)) {
					SetDirection(Direction::DOWN);
				}
				else if (inputManager->KeyDown(InputManager::Keys::LEFT)) {
					SetDirection(Direction::LEFT);
				}
				else if (inputManager->KeyDown(InputManager::Keys::UP)) {
					SetDirection(Direction::UP);
				}
			}
			break;

		case Direction::DOWN:
			if (inputManager->KeyLetGo(InputManager::Keys::DOWN)) {
				if (inputManager->KeyDown(InputManager::Keys::LEFT)) {
					SetDirection(Direction::LEFT);
				}
				else if (inputManager->KeyDown(InputManager::Keys::UP)) {
					SetDirection(Direction::UP);
				}
				else if (inputManager->KeyDown(InputManager::Keys::RIGHT)) {
					SetDirection(Direction::RIGHT);
				}
			}
			break;

		case Direction::LEFT:
			if (inputManager->KeyLetGo(InputManager::Keys::LEFT)) {
				if (inputManager->KeyDown(InputManager::Keys::UP)) {
					SetDirection(direction = Direction::UP);
				}
				else if (inputManager->KeyDown(InputManager::Keys::RIGHT)) {
					SetDirection(direction = Direction::RIGHT);
				}
				else if (inputManager->KeyDown(InputManager::Keys::DOWN)) {
					SetDirection(direction = Direction::DOWN);
				}
			}
			break;
		}
	}

	// --------------------------------------------------
	// This method is used to move a player entity in the
	// current direction.
	// --------------------------------------------------
	void Player::MovePlayer(float deltaTime)
	{
		distanceMoved = 0;

		switch (direction)
		{
		case Direction::UP:
			if (inputManager->KeyDown(InputManager::Keys::UP)) {
				legsAnimation->UpdateAnimation(deltaTime);
				distanceMoved = (int)(speed * (deltaTime / 1000));
				y -= distanceMoved;
			}
			break;

		case Direction::RIGHT:
			if (inputManager->KeyDown(InputManager::Keys::RIGHT)) {
				legsAnimation->UpdateAnimation(deltaTime);
				distanceMoved = (int)(speed * (deltaTime / 1000));
				x += distanceMoved;
			}
			break;

		case Direction::DOWN:
			if (inputManager->KeyDown(InputManager::Keys::DOWN)) {
				legsAnimation->UpdateAnimation(deltaTime);
				distanceMoved = (int)(speed * (deltaTime / 1000));
				y += distanceMoved;
			}
			break;

		case Direction::LEFT:
			if (inputManager->KeyDown(InputManager::Keys::LEFT)) {
				legsAnimation->UpdateAnimation(deltaTime);
				distanceMoved = (int)(speed * (deltaTime / 1000));
				x -= distanceMoved;
			}
			break;
		}
	}

	// --------------------------------------------------
	// This method is used to move a player entity in 
	// the current direction with an increade movement
	// speed.
	// --------------------------------------------------
	void Player::Lunge(float deltaTime)
	{
		distanceMoved = 0;

		switch (direction)
		{
		case Direction::UP:
			distanceMoved = (int)((speed + lungeSpeedIncrease) * (deltaTime / 1000));
			y -= distanceMoved;
			break;

		case Direction::RIGHT:
			distanceMoved = (int)((speed + lungeSpeedIncrease) * (deltaTime / 1000));
			x += distanceMoved;
			break;

		case Direction::DOWN:
			distanceMoved = (int)((speed + lungeSpeedIncrease) * (deltaTime / 1000));
			y += distanceMoved;
			break;

		case Direction::LEFT:
			distanceMoved = (int)((speed + lungeSpeedIncrease) * (deltaTime / 1000));
			x -= distanceMoved;
			break;
		}
	}

	// --------------------------------------------------
	// This method is used heal the player when the 
	// conditions have been met.
	// --------------------------------------------------
	void Player::Heal()
	{
		GameData* gameDataInstance = GameData::GetInstance();
		if (gameDataInstance->playerHealth < gameDataInstance->MAX_HEALTH && gameDataInstance->playerPoints >= gameDataInstance->POINTS_FOR_HEALTH) {
			++gameDataInstance->playerHealth;
			gameDataInstance->playerPoints -= gameDataInstance->POINTS_FOR_HEALTH;
		}
	}

	// --------------------------------------------------
	// This method is used to process tile map collision
	// for the player.
	// --------------------------------------------------
	void Player::ProcessTileMapCollision(TileMap* tileMap) {
		char tileMapCollisionChar = ' ';
		short hitboxPointIndex = -1;
		CheckTileMapCollision(hitboxPointIndex, tileMapCollisionChar, tileMap);
		
		switch (tileMapCollisionChar)
		{
		case 'w':
			if (gameplayCallback->HasRoomBeenCleared()) {
				gameplayCallback->MovePlayerToNextRoom(Direction::UP);
				SetPosition((7 * 64) + (GetSprite()->GetWidth() / 2), (7 * 64) + (GetSprite()->GetHeight() / 2));
			}
			else {
				ApplyVerticalTileMapCollision(hitboxPointIndex, hitbox->GetBoxPoints()[hitboxPointIndex][1]);
			}
			break;

		case 'd':
			if (gameplayCallback->HasRoomBeenCleared()) {
				gameplayCallback->MovePlayerToNextRoom(Direction::RIGHT);
				SetPosition(64 + (GetSprite()->GetWidth() / 2), (4 * 64) + (GetSprite()->GetHeight() / 2));
			}
			else {
				ApplyHorizontalTileMapCollision(hitboxPointIndex, hitbox->GetBoxPoints()[hitboxPointIndex][0]);
			}
			break;

		case 's':
			if (gameplayCallback->HasRoomBeenCleared()) {
				gameplayCallback->MovePlayerToNextRoom(Direction::DOWN);
				SetPosition((7 * 64) + (GetSprite()->GetWidth() / 2), 64 + (GetSprite()->GetHeight() / 2));
			}
			else {
				ApplyVerticalTileMapCollision(hitboxPointIndex, hitbox->GetBoxPoints()[hitboxPointIndex][1]);
			}
			break;

		case 'a':
			if (gameplayCallback->HasRoomBeenCleared()) {
				gameplayCallback->MovePlayerToNextRoom(Direction::LEFT);
				SetPosition((13 * 64) + (GetSprite()->GetWidth() / 2), (4 * 64) + (GetSprite()->GetHeight() / 2));
			}
			else {
				ApplyHorizontalTileMapCollision(hitboxPointIndex, hitbox->GetBoxPoints()[hitboxPointIndex][0]);
			}
			break;

		case 't':
		case 'g':
			if (gameplayCallback->HasRoomBeenCleared()) {
				gameplayCallback->PlayerHasWonTheGame();
			}
			else {
				ApplyVerticalTileMapCollision(hitboxPointIndex, hitbox->GetBoxPoints()[hitboxPointIndex][1]);
			}
			break;

		case 'h':
		case 'f':
			if (gameplayCallback->HasRoomBeenCleared()) {
				gameplayCallback->PlayerHasWonTheGame();
			}
			else {
				ApplyHorizontalTileMapCollision(hitboxPointIndex, hitbox->GetBoxPoints()[hitboxPointIndex][0]);
			}
			break;

		case 'x':
			switch (direction)
			{
			case Direction::UP:
			case Direction::DOWN:
				ApplyVerticalTileMapCollision(hitboxPointIndex, hitbox->GetBoxPoints()[hitboxPointIndex][1]);
				break;

			case Direction::LEFT:
			case Direction::RIGHT:
				ApplyHorizontalTileMapCollision(hitboxPointIndex, hitbox->GetBoxPoints()[hitboxPointIndex][0]);
				break;
			}
			break;
		}
	}
}