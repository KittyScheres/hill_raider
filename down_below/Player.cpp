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
		playerSprite = new Image("assets/player/player.png", x, y);
	}

	// --------------------------------------------------
	//
	// --------------------------------------------------
	void Player::Update(float deltaTime)
	{
		
		if (inputManager->KeyDown(InputManager::Keys::DOWN)) {
			y += (int)(speed * (deltaTime / 1000));
		}
		else if (inputManager->KeyDown(InputManager::Keys::UP)) {
			y -= (int)(speed * (deltaTime / 1000));
		}

		if (inputManager->KeyDown(InputManager::Keys::RIGHT)) {
			x += (int)(speed * (deltaTime / 1000));
		}
		else if (inputManager->KeyDown(InputManager::Keys::LEFT)) {
			x -= (int)(speed * (deltaTime / 1000));
		}

		playerSprite->SetPosition(x, y);
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
	Player::~Player()
	{
		delete playerSprite;
		playerSprite = nullptr;

		inputManager = nullptr;
	}
}