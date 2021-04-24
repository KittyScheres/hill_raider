#pragma once

#include "Entity.h"
#include "EnemyAnt.h"
#include "FoodPointsPickup.h"
#include "Animation.h"
#include "InputManager.h"
#include "GameData.h"
#include "GamePlayCallback.h"

namespace HillRaider
{
	// --------------------------------------------------
	// This class is used to create and keep track of
	// player entities in the game.
	// --------------------------------------------------
	class Player : public Entity
	{
	private:
		const short c_AttackHitboxWidth = 20;
		const short c_AttackHitboxHeight = 10;
		const float c_TimePerframeWalkingAnimation = 30.f;
		const short c_LungeSpeedIncrease = 200;
		const float c_LungeTimePerFrameWalkingAnimation = 15.f;
		const float c_LungeDuration = 200.f;
		const float c_LungeCooldown = 2000.f;

	private:
		GameplayCallback* m_GameplayCallback = nullptr;
		InputManager* m_InputManager = nullptr;
		Animation* m_LegsAnimation = nullptr;
		Animation* m_BodyAnimation = nullptr;
		Hitbox* m_AttackHitbox = nullptr;
		float m_Speed = 220.f;
		short m_AttackHitboxOffset = (m_Height / 2) + (c_AttackHitboxHeight / 2);
		bool m_LungeFlag = false;
		bool m_LungeCooldownFlag = false;
		float m_LungeDurationTimer = 0.f;
		float m_LungeCooldownTimer = 0.f;

	public:
		Player(int x, int y);
		void Update(float deltaTime);
		void LateUpdate(TileMap* tileMap, std::list<Entity*> entityList);
		void Render(Tmpl8::Surface* screen);
		void TakeDamage();
		void SetGamePlayCallback(GameplayCallback* callback);
		void SetPosition(int x, int y);
		void SetDirection(Direction direction);
		Direction GetDirection();
		Animation* GetSprite();
		~Player();

	private:
		void CheckForMovementKeyPressed();
		void CheckForMovementKeyLetGo();
		void MovePlayer(float deltaTime);
		void Lunge(float deltaTime);
		void Heal();
		void ProcessTileMapCollision(TileMap* tileMap);
	};
}