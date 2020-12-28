#include "Player.h"

namespace HillRaider
{
	// --------------------------------------------------
	//
	// --------------------------------------------------
	Player::Player(int iX, int iY, float iSpeed, int iWidth, int iHeight): Entity(iX, iY, iWidth, iHeight)
	{
		speed = iSpeed;
		inputManager = InputManager::GetInstance();
		playerSprite = new Image("assets/gameplay/player/player.png", x , y );
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
				if (inputManager->KeyPressed(InputManager::Keys::ENTER)) {
					lungeFlag = true;
					lungeCooldownFlag = true;
				}
			}
			else {
				if (lungeCooldownTimer >= lungeCooldown) {
					lungeCooldownFlag = false;
					lungeCooldownTimer = 0.f;
				}
				else {
					lungeCooldownTimer += deltaTime;
				}
			}
		}
		else {
			if (lungeDurationTimer >= lungeDuration) {
				registerHitFlag = true;
				lungeFlag = false;
				lungeDurationTimer = 0.f;
			}
			else {
				Lunge(deltaTime);
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

			if (registerHitFlag)
			{
				if (TestBoxCollision(attackHitbox, entity))
				{
					RagDoll* ragdoll = dynamic_cast<RagDoll*>(entity);
					if (ragdoll != nullptr) {
						ragdoll->TakeDamage();
					}
				}
				registerHitFlag = false;
			}
		}
	}

	// --------------------------------------------------
	//
	// --------------------------------------------------
	void Player::Render(Tmpl8::Surface* screen)
	{
		playerSprite->SetPosition(x - (playerSprite->GetWidth() / 2), y - (playerSprite->GetHeight() / 2));
		playerSprite->DrawImage(screen);
		hitbox->RenderHitbox(screen);
		attackHitbox->RenderHitbox(screen);
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
	Image* Player::GetSprite()
	{
		return playerSprite;
	}

	// --------------------------------------------------
	//
	// --------------------------------------------------
	Player::~Player()
	{
		if (playerSprite != nullptr) {
			delete playerSprite;
			playerSprite = nullptr;
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
				distanceMoved = (int)(speed * (deltaTime / 1000));
				y -= distanceMoved;
			}
			break;

		case MovementDirection::RIGHT:
			if (inputManager->KeyDown(InputManager::Keys::RIGHT)) {
				distanceMoved = (int)(speed * (deltaTime / 1000));
				x += distanceMoved;
			}
			break;

		case MovementDirection::DOWN:
			if (inputManager->KeyDown(InputManager::Keys::DOWN)) {
				distanceMoved = (int)(speed * (deltaTime / 1000));
				y += distanceMoved;
			}
			break;

		case MovementDirection::LEFT:
			if (inputManager->KeyDown(InputManager::Keys::LEFT)) {
				distanceMoved = (int)(speed * (deltaTime / 1000));
				x -= distanceMoved;
			}
			break;
		}
	}

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