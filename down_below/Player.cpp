#include "Player.h"

namespace DownBelow
{
	// --------------------------------------------------
	//
	// --------------------------------------------------
	Player::Player(int iX, int iY, float iSpeed, int iWidth, int iHeight)
	{
		x = iX;
		y = iY;
		speed = iSpeed;
		width = iWidth;
		height = iHeight;
		inputManager = InputManager::GetInstance();
		playerSprite = new Image("assets/gameplay/player/player.png", x - (width / 2), y - (height / 2));
		hitbox = new Hitbox(x, y, width, height);
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
		switch (direction)
		{
		case MovementDirection::UP:
			if (inputManager->KeyDown(InputManager::Keys::UP)) {
				y -= (int)(speed * (deltaTime / 1000));
			}
			break;

		case MovementDirection::RIGHT:
			if (inputManager->KeyDown(InputManager::Keys::RIGHT)) {
				x += (int)(speed * (deltaTime / 1000));
			}
			break;

		case MovementDirection::DOWN:
			if (inputManager->KeyDown(InputManager::Keys::DOWN)) {
				y += (int)(speed * (deltaTime / 1000));
			}
			break;

		case MovementDirection::LEFT:
			if (inputManager->KeyDown(InputManager::Keys::LEFT)) {
				x -= (int)(speed * (deltaTime / 1000));
			}
			break;
		}
	}
	
	// --------------------------------------------------
	//
	// --------------------------------------------------
	void Player::LateUpdate()
	{

	}

	// --------------------------------------------------
	//
	// --------------------------------------------------
	void Player::Render(Tmpl8::Surface* screen)
	{
		playerSprite->DrawImage(screen);
	}

	// --------------------------------------------------
	//
	// --------------------------------------------------
	void Player::SetPosition(int iX, int iY) {
		x = iX;
		y = iY;
	}

	// --------------------------------------------------
	//
	// --------------------------------------------------
	int* Player::GetPosition()
	{
		int position[2] { x, y };
		return position;
	}

	// --------------------------------------------------
	//
	// --------------------------------------------------
	int Player::GetWidth()
	{
		return width;
	}

	// --------------------------------------------------
	//
	// --------------------------------------------------
	int Player::GetHeight()
	{
		return height;
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
	Hitbox* Player::GetHitbox()
	{
		return hitbox;
	}

	// --------------------------------------------------
	//
	// --------------------------------------------------
	Player::~Player()
	{
		delete playerSprite;
		playerSprite = nullptr;

		delete hitbox;
		hitbox = nullptr;

		inputManager = nullptr;
	}
}