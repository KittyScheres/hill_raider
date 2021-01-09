#include "Player.h"

namespace HillRaider
{
	// --------------------------------------------------
	//
	// --------------------------------------------------
	Player::Player(int iX, int iY): Entity(iX, iY, 28, 62)
	{
		inputManager = InputManager::GetInstance();
		legsAnimation = new Animation("assets/entities/black_ant_legs.png", 4, 4, timePerframeWalkingAnimation, iX, iY, true);
		bodyAnimation = new Animation("assets/entities/black_ant_body.png", 4, 4, 75.f, iX, iY, false);
		attackHitbox = new Hitbox(x, y + attackHitboxOffset, attackHitboxWidth, attackHitboxHeight);
	}

	// --------------------------------------------------
	//
	// --------------------------------------------------
	void Player::Update(float deltaTime)
	{
		if (!lungeFlag) {
			CheckForKeyPressed();
			CheckForKeyLetGo();
			MovePlayer(deltaTime);
			
			if (!lungeCooldownFlag) {
				if (inputManager->KeyPressed(InputManager::Keys::SPACE)) {
					legsAnimation->SetTimePerFrame(lungeTimePerFrameWalkingAnimation);
					lungeFlag = true;
					lungeCooldownFlag = true;
				}
			}
			else {
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
	//
	// --------------------------------------------------
	void Player::LateUpdate(std::list<Entity*> entityList)
	{
		for (Entity* entity : entityList) {
			if (TestBoxCollision(hitbox, entity)) {
				ApplyEntityCollision(entity);
				SetPosition(x, y);
			}

			if (lungeFlag) {
				if (TestBoxCollision(attackHitbox, entity)) {
					EnemyAnt* enemyAnt = dynamic_cast<EnemyAnt*>(entity);
					if (enemyAnt != nullptr) {
						enemyAnt->TakeDamage();
						lungeFlag = false;
						lungeDurationTimer = 0.f;
					}
				}
			}
		}
	}

	// --------------------------------------------------
	//
	// --------------------------------------------------
	void Player::Render(Tmpl8::Surface* screen)
	{
		legsAnimation->SetPosition(x - (bodyAnimation->GetWidth() / 2), y - (bodyAnimation->GetHeight() / 2));
		bodyAnimation->SetPosition(x - (bodyAnimation->GetWidth() / 2), y - (bodyAnimation->GetHeight() / 2));
		
		legsAnimation->DrawAnimation(screen);
		bodyAnimation->DrawAnimation(screen);
	}

	// --------------------------------------------------
	//
	// --------------------------------------------------
	void Player::TakeDamage() {
		--GameData::GetInstance()->playerHealth;
	}

	// --------------------------------------------------
	//
	// --------------------------------------------------
	void Player::SetPosition(int iX, int iY) {
		x = iX;
		y = iY;
		hitbox->SetPosition(x, y);

		switch (direction)
		{
		case Entity::MovementDirection::UP :
		case Entity::MovementDirection::DOWN :
			attackHitbox->SetPosition(x, y + attackHitboxOffset);
			break;

		case Entity::MovementDirection::LEFT :
		case Entity::MovementDirection::RIGHT :
			attackHitbox->SetPosition(x + attackHitboxOffset, y);
			break;
		}
	}

	// --------------------------------------------------
	//
	// --------------------------------------------------
	void Player::SetDirection(Entity::MovementDirection iDirection) {
		direction = iDirection;

		legsAnimation->SetCurrentYFrame((int)direction);
		bodyAnimation->SetCurrentYFrame((int)direction);

		switch (direction)
		{
		case Entity::MovementDirection::UP:
			attackHitboxOffset = -std::abs(attackHitboxOffset);
			hitbox->SetWidth(width);
			hitbox->SetHeight(height);
			attackHitbox->SetWidth(attackHitboxWidth);
			attackHitbox->SetHeight(attackHitboxHeight);
			break;
		
		case Entity::MovementDirection::RIGHT:
			attackHitboxOffset = std::abs(attackHitboxOffset);
			hitbox->SetWidth(height);
			hitbox->SetHeight(width);
			attackHitbox->SetWidth(attackHitboxHeight);
			attackHitbox->SetHeight(attackHitboxWidth);
			break;

		case Entity::MovementDirection::DOWN:
			attackHitboxOffset = std::abs(attackHitboxOffset);
			hitbox->SetWidth(width);
			hitbox->SetHeight(height);
			attackHitbox->SetWidth(attackHitboxWidth);
			attackHitbox->SetHeight(attackHitboxHeight);
			break;

		case Entity::MovementDirection::LEFT:
			attackHitboxOffset = -std::abs(attackHitboxOffset);
			hitbox->SetWidth(height);
			hitbox->SetHeight(width);
			attackHitbox->SetWidth(attackHitboxHeight);
			attackHitbox->SetHeight(attackHitboxWidth);
			break;
		}
	}

	// --------------------------------------------------
	//
	// --------------------------------------------------
	Entity::MovementDirection Player::GetDirection() {
		return direction;
	}

	// --------------------------------------------------
	//
	// --------------------------------------------------
	Animation* Player::GetSprite()
	{
		return bodyAnimation;
	}

	// --------------------------------------------------
	//
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

		if (hitbox != nullptr) {
			delete hitbox;
			hitbox = nullptr;
		}

		if (attackHitbox != nullptr) {
			delete attackHitbox;
			attackHitbox = nullptr;
		}

		inputManager = nullptr;
	}

	// --------------------------------------------------
	//
	// --------------------------------------------------
	void Player::CheckForKeyPressed()
	{
		if (inputManager->KeyPressed(InputManager::Keys::UP)) {
			SetDirection(MovementDirection::UP);
		}

		if (inputManager->KeyPressed(InputManager::Keys::RIGHT)) {
			SetDirection(MovementDirection::RIGHT);
		}

		if (inputManager->KeyPressed(InputManager::Keys::DOWN)) {
			SetDirection(MovementDirection::DOWN);
		}

		if (inputManager->KeyPressed(InputManager::Keys::LEFT)) {
			SetDirection(MovementDirection::LEFT);
		}
	}

	// --------------------------------------------------
	//
	// --------------------------------------------------
	void Player::CheckForKeyLetGo()
	{
		switch (direction)
		{
		case MovementDirection::UP:
			if (inputManager->KeyLetGo(InputManager::Keys::UP)) {
				if (inputManager->KeyDown(InputManager::Keys::RIGHT)) {
					SetDirection(MovementDirection::RIGHT);
				}
				else if (inputManager->KeyDown(InputManager::Keys::DOWN)) {
					SetDirection(MovementDirection::DOWN);
				}
				else if (inputManager->KeyDown(InputManager::Keys::LEFT)) {
					SetDirection(MovementDirection::LEFT);
				}
			}
			break;

		case MovementDirection::RIGHT:
			if (inputManager->KeyLetGo(InputManager::Keys::RIGHT)) {
				if (inputManager->KeyDown(InputManager::Keys::DOWN)) {
					SetDirection(MovementDirection::DOWN);
				}
				else if (inputManager->KeyDown(InputManager::Keys::LEFT)) {
					SetDirection(MovementDirection::LEFT);
				}
				else if (inputManager->KeyDown(InputManager::Keys::UP)) {
					SetDirection(MovementDirection::UP);
				}
			}
			break;

		case MovementDirection::DOWN:
			if (inputManager->KeyLetGo(InputManager::Keys::DOWN)) {
				if (inputManager->KeyDown(InputManager::Keys::LEFT)) {
					SetDirection(MovementDirection::LEFT);
				}
				else if (inputManager->KeyDown(InputManager::Keys::UP)) {
					SetDirection(MovementDirection::UP);
				}
				else if (inputManager->KeyDown(InputManager::Keys::RIGHT)) {
					SetDirection(MovementDirection::RIGHT);
				}
			}
			break;

		case MovementDirection::LEFT:
			if (inputManager->KeyLetGo(InputManager::Keys::LEFT)) {
				if (inputManager->KeyDown(InputManager::Keys::UP)) {
					SetDirection(direction = MovementDirection::UP);
				}
				else if (inputManager->KeyDown(InputManager::Keys::RIGHT)) {
					SetDirection(direction = MovementDirection::RIGHT);
				}
				else if (inputManager->KeyDown(InputManager::Keys::DOWN)) {
					SetDirection(direction = MovementDirection::DOWN);
				}
			}
			break;
		}
	}

	// --------------------------------------------------
	//
	// --------------------------------------------------
	void Player::MovePlayer(float deltaTime)
	{
		distanceMoved = 0;

		switch (direction)
		{
		case MovementDirection::UP:
			if (inputManager->KeyDown(InputManager::Keys::UP)) {
				legsAnimation->UpdateAnimation(deltaTime);
				distanceMoved = (int)(speed * (deltaTime / 1000));
				y -= distanceMoved;
			}
			break;

		case MovementDirection::RIGHT:
			if (inputManager->KeyDown(InputManager::Keys::RIGHT)) {
				legsAnimation->UpdateAnimation(deltaTime);
				distanceMoved = (int)(speed * (deltaTime / 1000));
				x += distanceMoved;
			}
			break;

		case MovementDirection::DOWN:
			if (inputManager->KeyDown(InputManager::Keys::DOWN)) {
				legsAnimation->UpdateAnimation(deltaTime);
				distanceMoved = (int)(speed * (deltaTime / 1000));
				y += distanceMoved;
			}
			break;

		case MovementDirection::LEFT:
			if (inputManager->KeyDown(InputManager::Keys::LEFT)) {
				legsAnimation->UpdateAnimation(deltaTime);
				distanceMoved = (int)(speed * (deltaTime / 1000));
				x -= distanceMoved;
			}
			break;
		}
	}

	// --------------------------------------------------
	//
	// --------------------------------------------------
	void Player::Lunge(float deltaTime)
	{
		distanceMoved = 0;

		switch (direction)
		{
		case MovementDirection::UP:
			distanceMoved = (int)((speed + lungeSpeedIncrease) * (deltaTime / 1000));
			y -= distanceMoved;
			break;

		case MovementDirection::RIGHT:
			distanceMoved = (int)((speed + lungeSpeedIncrease) * (deltaTime / 1000));
			x += distanceMoved;
			break;

		case MovementDirection::DOWN:
			distanceMoved = (int)((speed + lungeSpeedIncrease) * (deltaTime / 1000));
			y += distanceMoved;
			break;

		case MovementDirection::LEFT:
			distanceMoved = (int)((speed + lungeSpeedIncrease) * (deltaTime / 1000));
			x -= distanceMoved;
			break;
		}
	}
}