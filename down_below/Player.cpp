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
	}

	// --------------------------------------------------
	//
	// --------------------------------------------------
	void Player::Update(float deltaTime)
	{
		CheckForKeyPressed();
		CheckForKeyLetGo();
		MovePlayer(deltaTime);
		playerSprite->SetPosition(x - (playerSprite->GetWidth() / 2), y - (playerSprite->GetHeight() / 2));
		hitbox->SetPosition(x, y);
	}
	
	// --------------------------------------------------
	//
	// --------------------------------------------------
	void Player::LateUpdate(std::vector<Entity*> entityList)
	{
		for (auto entity : entityList) {
			if (TestBoxCollision(entity)) {
				ApplyEntityCollision(entity);
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

		inputManager = nullptr;
	}

	// --------------------------------------------------
	//
	// --------------------------------------------------
	void Player::CheckForKeyPressed()
	{
		if (inputManager->KeyPressed(InputManager::Keys::UP)) {
			direction = MovementDirection::UP;
		}

		if (inputManager->KeyPressed(InputManager::Keys::RIGHT)) {
			direction = MovementDirection::RIGHT;
		}

		if (inputManager->KeyPressed(InputManager::Keys::DOWN)) {
			direction = MovementDirection::DOWN;
		}

		if (inputManager->KeyPressed(InputManager::Keys::LEFT)) {
			direction = MovementDirection::LEFT;
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
					direction = MovementDirection::RIGHT;
				}
				else if (inputManager->KeyDown(InputManager::Keys::DOWN)) {
					direction = MovementDirection::DOWN;
				}
				else if (inputManager->KeyDown(InputManager::Keys::LEFT)) {
					direction = MovementDirection::LEFT;
				}
			}
			break;

		case MovementDirection::RIGHT:
			if (inputManager->KeyLetGo(InputManager::Keys::RIGHT)) {
				if (inputManager->KeyDown(InputManager::Keys::DOWN)) {
					direction = MovementDirection::DOWN;
				}
				else if (inputManager->KeyDown(InputManager::Keys::LEFT)) {
					direction = MovementDirection::LEFT;
				}
				else if (inputManager->KeyDown(InputManager::Keys::UP)) {
					direction = MovementDirection::UP;
				}
			}
			break;

		case MovementDirection::DOWN:
			if (inputManager->KeyLetGo(InputManager::Keys::DOWN)) {
				if (inputManager->KeyDown(InputManager::Keys::LEFT)) {
					direction = MovementDirection::LEFT;
				}
				else if (inputManager->KeyDown(InputManager::Keys::UP)) {
					direction = MovementDirection::UP;
				}
				else if (inputManager->KeyDown(InputManager::Keys::RIGHT)) {
					direction = MovementDirection::RIGHT;
				}
			}
			break;

		case MovementDirection::LEFT:
			if (inputManager->KeyLetGo(InputManager::Keys::LEFT)) {
				if (inputManager->KeyDown(InputManager::Keys::UP)) {
					direction = MovementDirection::UP;
				}
				else if (inputManager->KeyDown(InputManager::Keys::RIGHT)) {
					direction = MovementDirection::RIGHT;
				}
				else if (inputManager->KeyDown(InputManager::Keys::DOWN)) {
					direction = MovementDirection::DOWN;
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