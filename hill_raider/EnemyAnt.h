#pragma once

#include "RoomCallback.h"
#include "Entity.h"
#include "Player.h"
#include "Animation.h"
#include "AStar.h"
#include <random>

namespace HillRaider
{
	// --------------------------------------------------
	// This class is used to create and keep track of 
	// enemy ant entities in the game.
	// --------------------------------------------------
	class EnemyAnt : public Entity
	{
	private:
		const short attackHitboxWidth = 20;
		const short attackHitboxHeight = 10;
		const short lineScanWidth = 10;
		const short lineScanHeight = 90;
		const float timePerframeWalkingAnimation = 30.f;
		const short lungeSpeedIncrease = 200;
		const float lungeTimePerFrameWalkingAnimation = 20.f;
		const float makeDecisionCooldown = 1000.f;
		const float lungeDuration = 300.f;
		const float lungeCooldown = 2000.f;

	private:
		RoomCallback* roomCallback = nullptr;
		Animation* legsAnimation = nullptr;
		Animation* bodyAnimation = nullptr;
		Hitbox* attackHitbox = nullptr;
		Hitbox* lineScan = nullptr;
		float speed = 160.f;
		int ragdollHealt = 2;
		short attackHitboxOffset = (height / 2) + (attackHitboxHeight / 2);
		short lineScanOffset = (height / 2) + (lineScanHeight / 2);
		bool makeDecisionFlag = false;
		bool lungeFlag = false;
		bool lungeCooldownFlag = false;
		float makeDecisionTimer = 0.f;
		float lungeDurationTimer = 0.f;
		float lungeCooldownTimer = 0.f;

	public:
		EnemyAnt(int iX, int iY);
		void Update(float deltaTime);
		void LateUpdate(TileMap* tileMap, std::list<Entity*> entityList);
		void Render(Tmpl8::Surface* screen);
		void TakeDamage();
		void SetRoomCallback(RoomCallback* callback);
		void SetPosition(int iX, int iY);
		void SetDirection(Direction iDirection);
		Direction GetDirection();
		Animation* GetSprite();
		~EnemyAnt();

	private:
		void UpdateDirection(bool bypassCheck = false);
		void MoveEnemyAnt(float deltaTime);
		void Lunge(float deltaTime);
		void GetAntUnstuck(Entity* entity);
		void ProcessTileMapCollision(TileMap* tileMap);
	};
}