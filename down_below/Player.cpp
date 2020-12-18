#include "Player.h"

namespace DownBelow
{
	// --------------------------------------------------
	//
	// --------------------------------------------------
	Player::Player(int iX, int iY, float iSpeed, int iWidth, int iHeight): Entity(iX, iY, iWidth, iHeight)
	{
		speed = iSpeed;
		inputManager = InputManager::GetInstance();
		playerSprite = new Image("assets/gameplay/player/player.png", x , y );
		attackHitbox = new Hitbox(x, y - attackHitboxOffset, 20, 10);
	}

	// --------------------------------------------------
	//
	// --------------------------------------------------
	void Player::Update(float deltaTime)
	{
		attackFlag = false;

		CheckForKeyPressed();
		CheckForKeyLetGo();
		MovePlayer(deltaTime);
		SetPosition(x, y);
		if (inputManager->KeyPressed(InputManager::Keys::ENTER)) {
			attackFlag = true;
		}
	}
	
	// --------------------------------------------------
	//
	// --------------------------------------------------
	void Player::LateUpdate(std::vector<Entity*> entityList)
	{
		for (Entity* entity : entityList) {
			if (TestBoxCollision(hitbox, entity)) {
				ApplyEntityCollision(entity);
				SetPosition(x, y);
			}

			if (attackFlag && TestBoxCollision(attackHitbox, entity)) {
				RagDoll* ragdoll = dynamic_cast<RagDoll*>(entity);
				if (ragdoll != nullptr) {
					ragdoll->TakeDamage();
				}
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

		if (direction == Entity::MovementDirection::LEFT || direction == Entity::MovementDirection::RIGHT) {
			attackHitbox->SetPosition(x + attackHitboxOffset, y);
		}
		else {
			attackHitbox->SetPosition(x, y + attackHitboxOffset);
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
			if (attackHitboxOffset > 0) {
				attackHitboxOffset = -attackHitboxOffset;
			}
			hitbox->SetWidth(width);
			hitbox->SetHeight(height);
			attackHitbox->SetWidth(attackHitboxWidth);
			attackHitbox->SetHeight(attackHitboxHeight);
			break;
		
		case Entity::MovementDirection::RIGHT:
			if (attackHitboxOffset < 0) {
				attackHitboxOffset = -attackHitboxOffset;
			}
			hitbox->SetWidth(height);
			hitbox->SetHeight(width);
			attackHitbox->SetWidth(attackHitboxHeight);
			attackHitbox->SetHeight(attackHitboxWidth);
			break;

		case Entity::MovementDirection::DOWN:
			if (attackHitboxOffset < 0) {
				attackHitboxOffset = -attackHitboxOffset;
			}
			hitbox->SetWidth(width);
			hitbox->SetHeight(height);
			attackHitbox->SetWidth(attackHitboxWidth);
			attackHitbox->SetHeight(attackHitboxHeight);
			break;

		case Entity::MovementDirection::LEFT:
			if (attackHitboxOffset > 0) {
				attackHitboxOffset = -attackHitboxOffset;
			}
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
}