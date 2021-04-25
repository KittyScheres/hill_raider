#pragma once

#include "roomCallback.h"
#include "entity.h"
#include "player.h"
#include "animation.h"
#include "aStar.h"
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
		const short c_AttackHitboxWidth = 20;
		const short c_AttackHitboxHeight = 10;
		const short c_LineScanWidth = 10;
		const short c_LineScanHeight = 90;
		const float c_TimePerframeWalkingAnimation = 30.f;
		const short c_LungeSpeedIncrease = 200;
		const float c_LungeTimePerFrameWalkingAnimation = 20.f;
		const float c_MakeDecisionCooldown = 1000.f;
		const float c_LungeDuration = 300.f;
		const float c_LungeCooldown = 2000.f;

	private:
		RoomCallback* m_RoomCallback = nullptr;
		Animation* m_LegsAnimation = nullptr;
		Animation* m_BodyAnimation = nullptr;
		Hitbox* m_AttackHitbox = nullptr;
		Hitbox* m_LineScan = nullptr;
		float m_Speed = 170.f;
		int m_RagdollHealth = 2;
		short m_AttackHitboxOffset = (m_Height / 2) + (c_AttackHitboxHeight / 2);
		short m_LineScanOffset = (m_Height / 2) + (c_LineScanHeight / 2);
		bool m_MakeDecisionFlag = false;
		bool m_LungeFlag = false;
		bool m_LungeCooldownFlag = false;
		float m_MakeDecisionTimer = 0.f;
		float m_LungeDurationTimer = 0.f;
		float m_LungeCooldownTimer = 0.f;

	public:
		EnemyAnt(int x, int y);
		void Update(float deltaTime);
		void LateUpdate(TileMap* tileMap, std::list<Entity*> entityList);
		void Render(Tmpl8::Surface* screen);
		void TakeDamage();
		void SetRoomCallback(RoomCallback* callback);
		void SetPosition(int x, int y);
		void SetDirection(Direction direction);
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