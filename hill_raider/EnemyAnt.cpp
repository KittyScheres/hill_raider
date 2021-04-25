#include "enemyAnt.h"

namespace HillRaider
{
	// --------------------------------------------------
	// This contructor is used to setup the properties
	// for an enemy ant entity.
	// --------------------------------------------------
	EnemyAnt::EnemyAnt(int x, int y): Entity(x, y, 28, 62)
	{
		m_LegsAnimation = new Animation("assets/entities/red_ant_legs.png", 4, 4, c_TimePerframeWalkingAnimation, x, y, true);
		m_BodyAnimation = new Animation("assets/entities/red_ant_body.png", 4, 4, 75.f, x, y, false);
		m_AttackHitbox = new Hitbox(x, y + m_AttackHitboxOffset, c_AttackHitboxWidth, c_AttackHitboxHeight);
		m_LineScan = new Hitbox(x, y + m_LineScanOffset, c_LineScanWidth, c_LineScanHeight);
	}

	// --------------------------------------------------
	// This method is used to update an enemy ant entity.
	// --------------------------------------------------
	void EnemyAnt::Update(float deltaTime)
	{
		// Is the enemy ant attacking?
		if (!m_LungeFlag) {
			// Update the enemy ant's movement
			UpdateDirection();
			MoveEnemyAnt(deltaTime);

			// Attack decision timer
			if (!m_MakeDecisionFlag) {
				if (m_MakeDecisionTimer >= c_MakeDecisionCooldown) {
					m_MakeDecisionFlag = true;
					m_MakeDecisionTimer = 0.f;
				}
				else {
					m_MakeDecisionTimer += deltaTime;
				}
			}

			// Attack cooldown timer
			if (m_LungeCooldownFlag) {
				if (m_LungeCooldownTimer >= c_LungeCooldown) {
					m_LungeCooldownFlag = false;
					m_LungeCooldownTimer = 0.f;
					m_BodyAnimation->SetCurrentXFrame(0);
				}
				else {
					m_LungeCooldownTimer += deltaTime;
					m_BodyAnimation->UpdateAnimation(deltaTime);
				}
			}
		}
		else {
			//is attacking
			Lunge(deltaTime);

			// Attack duration timer
			if (m_LungeDurationTimer >= c_LungeDuration) {
				m_LegsAnimation->SetTimePerFrame(c_TimePerframeWalkingAnimation);
				m_LungeFlag = false;
				m_LungeDurationTimer = 0.f;
			}
			else {
				m_LungeDurationTimer += deltaTime;
			}
		}

		m_LegsAnimation->UpdateAnimation(deltaTime);
		SetPosition(m_X, m_Y);
	}

	// --------------------------------------------------
	// This method is used to process the collisions between
	// an enemy ant entity and other entities.
	// --------------------------------------------------
	void EnemyAnt::LateUpdate(TileMap* tileMap, std::list<Entity*> entityList)
	{
		float smallestDistance = 10000.f;
		bool playerInLineOfSide = false;

		ProcessTileMapCollision(tileMap);

		for (auto entity : entityList) {
			// Entity on entity collision
			if (TestBoxCollision(m_Hitbox, entity)) {
				ApplyEntityCollision(entity);
				GetAntUnstuck(entity);
			}

			// Entity on attack hitbox collision
			if (m_LungeFlag) {
				Player* player = dynamic_cast<Player*>(entity);
				if (player != nullptr && TestBoxCollision(m_AttackHitbox, entity)) {
					player->TakeDamage();
					m_LungeFlag = false;
					m_LungeDurationTimer = 0.f;
				}
			}

			// Entity on attack range collision
			if (m_MakeDecisionFlag && !m_LungeCooldownFlag) {
				if (TestBoxCollision(m_LineScan, entity)) {
					int distanceVectorX = entity->GetPosition()[0] - m_X;
					int distanceVectorY = entity->GetPosition()[1] - m_Y;
					float distance = sqrtf((float)(distanceVectorX * distanceVectorX) + (float)(distanceVectorY * distanceVectorY));
					if (dynamic_cast<Player*>(entity) != nullptr && distance < smallestDistance) {
						playerInLineOfSide = true;
						smallestDistance = distance;
					}
					else if (distance < smallestDistance) {
						playerInLineOfSide = false;
						smallestDistance = distance;
					}
				}
			}
		}
		
		// Attack decision
		if (playerInLineOfSide) {
			if ((rand() & 1) == 0) {
				m_LegsAnimation->SetTimePerFrame(c_LungeTimePerFrameWalkingAnimation);
				m_LungeFlag = true;
				m_LungeCooldownFlag = true;
			}
			m_MakeDecisionFlag = false;
		}
	}

	// --------------------------------------------------
	// This method is used to draw an enemy ant entity
	// onto the screen.
	// --------------------------------------------------
	void EnemyAnt::Render(Tmpl8::Surface* screen)
	{
		m_LegsAnimation->SetPosition(m_X - (m_BodyAnimation->GetWidth()) / 2, m_Y - (m_BodyAnimation->GetHeight() / 2));
		m_BodyAnimation->SetPosition(m_X - (m_BodyAnimation->GetWidth()) / 2, m_Y - (m_BodyAnimation->GetHeight() / 2));
		
		m_LegsAnimation->DrawAnimation(screen);
		m_BodyAnimation->DrawAnimation(screen);
	}

	// --------------------------------------------------
	// This method is used to make an enemy ant entity take
	// damage.
	// --------------------------------------------------
	void EnemyAnt::TakeDamage() {
		m_MakeDecisionFlag = false;
		m_MakeDecisionTimer = 0.f;

		m_LungeFlag = false;
		m_LungeCooldownFlag = false;
		m_LungeDurationTimer = 0.f;
		m_LegsAnimation->SetTimePerFrame(c_TimePerframeWalkingAnimation);

		if (--m_RagdollHealth <= 0) {
			m_RoomCallback->RemoveEntity(this);
		}
	}

	// --------------------------------------------------
	// This method is used to set the room callback for
	// an enemy ant entity.
	// --------------------------------------------------
	void EnemyAnt::SetRoomCallback(RoomCallback* callback)
	{
		m_RoomCallback = callback;
	}

	// --------------------------------------------------
	// This method is used to set the position of an enemy
	// ant entity.
	// --------------------------------------------------
	void EnemyAnt::SetPosition(int x, int y)
	{
		m_X = x;
		m_Y = y;
		m_Hitbox->SetPosition(x, y);

		switch (m_Direction)
		{
		case Direction::UP:
		case Direction::DOWN:
			m_AttackHitbox->SetPosition(m_X, y + m_AttackHitboxOffset);
			m_LineScan->SetPosition(m_X, y + m_LineScanOffset);
			break;

		case Direction::LEFT:
		case Direction::RIGHT:
			m_AttackHitbox->SetPosition(m_X + m_AttackHitboxOffset, m_Y);
			m_LineScan->SetPosition(m_X + m_LineScanOffset, m_Y);
			break;
		}
	}

	// --------------------------------------------------
	// This method is used to set the direction of an 
	// enemy ant entity.
	// --------------------------------------------------
	void EnemyAnt::SetDirection(Direction direction)
	{
		m_Direction = direction;

		m_LegsAnimation->SetCurrentYFrame((int)m_Direction);
		m_BodyAnimation->SetCurrentYFrame((int)m_Direction);

		switch (m_Direction)
		{
		// Make the enemy ant face up
		case Direction::UP:
			m_AttackHitboxOffset = -std::abs(m_AttackHitboxOffset);
			m_LineScanOffset = -std::abs(m_LineScanOffset);
			m_Hitbox->SetWidth(m_Width);
			m_Hitbox->SetHeight(m_Height);
			m_AttackHitbox->SetWidth(c_AttackHitboxWidth);
			m_AttackHitbox->SetHeight(c_AttackHitboxHeight);
			m_LineScan->SetWidth(c_LineScanWidth);
			m_LineScan->SetHeight(c_LineScanHeight);
			break;

		// Make the enemy ant face right
		case Direction::RIGHT:
			m_AttackHitboxOffset = std::abs(m_AttackHitboxOffset);
			m_LineScanOffset = std::abs(m_LineScanOffset);
			m_Hitbox->SetWidth(m_Height);
			m_Hitbox->SetHeight(m_Width);
			m_AttackHitbox->SetWidth(c_AttackHitboxHeight);
			m_AttackHitbox->SetHeight(c_AttackHitboxWidth);
			m_LineScan->SetWidth(c_LineScanHeight);
			m_LineScan->SetHeight(c_LineScanWidth);
			break;

		// Make the enemy ant face down
		case Direction::DOWN:
			m_AttackHitboxOffset = std::abs(m_AttackHitboxOffset);
			m_LineScanOffset = std::abs(m_LineScanOffset);
			m_Hitbox->SetWidth(m_Width);
			m_Hitbox->SetHeight(m_Height);
			m_AttackHitbox->SetWidth(c_AttackHitboxWidth);
			m_AttackHitbox->SetHeight(c_AttackHitboxHeight);
			m_LineScan->SetWidth(c_LineScanWidth);
			m_LineScan->SetHeight(c_LineScanHeight);
			break;

		// Make the enemy ant face left
		case Direction::LEFT:
			m_AttackHitboxOffset = -std::abs(m_AttackHitboxOffset);
			m_LineScanOffset = -std::abs(m_LineScanOffset);
			m_Hitbox->SetWidth(m_Height);
			m_Hitbox->SetHeight(m_Width);
			m_AttackHitbox->SetWidth(c_AttackHitboxHeight);
			m_AttackHitbox->SetHeight(c_AttackHitboxWidth);
			m_LineScan->SetWidth(c_LineScanHeight);
			m_LineScan->SetHeight(c_LineScanWidth);
			break;
		}
	}

	// --------------------------------------------------
	// This method is used to get the direction of an enemy
	// ant entity.
	// --------------------------------------------------
	Direction EnemyAnt::GetDirection()
	{
		return m_Direction;
	}

	// --------------------------------------------------
	// This method is used to get the sprite of an enemy
	// ant entity.
	// --------------------------------------------------
	Animation* EnemyAnt::GetSprite()
	{
		return m_BodyAnimation;
	}

	// --------------------------------------------------
	// This destructor is used to safely free the memory 
	// of the properties of an enemy ant entity.
	// --------------------------------------------------
	EnemyAnt::~EnemyAnt()
	{
		if (m_LegsAnimation != nullptr) {
			delete m_LegsAnimation;
			m_LegsAnimation = nullptr;
		}

		if (m_BodyAnimation != nullptr) {
			delete m_BodyAnimation;
			m_BodyAnimation = nullptr;
		}

		if (m_AttackHitbox != nullptr) {
			delete m_AttackHitbox;
			m_AttackHitbox = nullptr;
		}

		if (m_LineScan != nullptr) {
			delete m_LineScan;
			m_LineScan = nullptr;
		}
	}

	// --------------------------------------------------
	// This method is used to update the current movement
	// direction of an enemy ant according to the output
	// of the a* pathfinding algorithm.
	// --------------------------------------------------
	void EnemyAnt::UpdateDirection(bool bypassCheck)
	{
		std::vector<AStarNode*> path;

		// Execute a* pathfinding to get the new direction for the enemy ant
		switch (m_Direction)
		{
		case Direction::UP:
			path = AStar::GetIntance()->FindPath(this, std::vector<int>{m_X, m_Y + m_Hitbox->GetHalfHeight()}, std::vector<int>{m_X, m_Y - m_Hitbox->GetHalfHeight()}, bypassCheck);
			break;

		case Direction::RIGHT:
			path = AStar::GetIntance()->FindPath(this, std::vector<int>{m_X - m_Hitbox->GetHalfWidth(), m_Y}, std::vector<int>{m_X + m_Hitbox->GetHalfWidth(), m_Y}, bypassCheck);
			break;

		case Direction::DOWN:
			path = AStar::GetIntance()->FindPath(this, std::vector<int>{m_X, m_Y - m_Hitbox->GetHalfHeight()}, std::vector<int>{m_X, m_Y + m_Hitbox->GetHalfHeight()}, bypassCheck);
			break;

		case Direction::LEFT:
			path = AStar::GetIntance()->FindPath(this, std::vector<int>{m_X + m_Hitbox->GetHalfWidth(), m_Y}, std::vector<int>{m_X - m_Hitbox->GetHalfWidth(), m_Y}, bypassCheck);
			break;
		}

		// Check if new path has been found
		if (path.size() > 1) {
			std::vector<int> directionVector{ path[1]->GetGridX() - path[0]->GetGridX(), path[1]->GetGridY() - path[0]->GetGridY() };

			// Apply new direction to the enemy ant
			if (directionVector == std::vector<int>{0, -1}) {
				SetDirection(Direction::UP);
			}
			else if (directionVector == std::vector<int>{1, 0}) {
				SetDirection(Direction::RIGHT);
			}
			else if (directionVector == std::vector<int>{0, 1}) {
				SetDirection(Direction::DOWN);
			}
			else if (directionVector == std::vector<int>{-1, 0}) {
				SetDirection(Direction::LEFT);
			}
		}
	}

	// --------------------------------------------------
	// This method is used to move an enemy ant entity
	// in the current movement direction.
	// --------------------------------------------------
	void EnemyAnt::MoveEnemyAnt(float deltaTime)
	{
		m_DistanceMoved = 0;

		switch (m_Direction)
		{
		case Direction::UP:
			m_DistanceMoved = (int)(m_Speed * (deltaTime / 1000.f));
			m_Y -= m_DistanceMoved;
			break;
			
		case Direction::RIGHT:
			m_DistanceMoved = (int)(m_Speed * (deltaTime / 1000.f));
			m_X += m_DistanceMoved;
			break;

		case Direction::DOWN:
			m_DistanceMoved = (int)(m_Speed * (deltaTime / 1000.f));
			m_Y += m_DistanceMoved;
			break;

		case Direction::LEFT:
			m_DistanceMoved = (int)(m_Speed * (deltaTime / 1000.f));
			m_X -= m_DistanceMoved;
			break;
		}
	}

	// --------------------------------------------------
	// This method is used to make an enemy ant entity 
	// move in the current direction with increased 
	// movement speed.
	// --------------------------------------------------
	void EnemyAnt::Lunge(float deltaTime)
	{
		m_DistanceMoved = 0;

		switch (m_Direction)
		{
		case Direction::UP:
			m_DistanceMoved = (int)((m_Speed + c_LungeSpeedIncrease) * (deltaTime / 1000.f));
			m_Y -= m_DistanceMoved;
			break;

		case Direction::RIGHT:
			m_DistanceMoved = (int)((m_Speed + c_LungeSpeedIncrease) * (deltaTime / 1000.f));
			m_X += m_DistanceMoved;
			break;

		case Direction::DOWN:
			m_DistanceMoved = (int)((m_Speed + c_LungeSpeedIncrease) * (deltaTime / 1000.f));
			m_Y += m_DistanceMoved;
			break;

		case Direction::LEFT:
			m_DistanceMoved = (int)((m_Speed + c_LungeSpeedIncrease) * (deltaTime / 1000.f));
			m_X -= m_DistanceMoved;
			break;
		}
	}

	// --------------------------------------------------
	// This method is used to update the movement direction
	// of an enemy ant entity to attempt to get
	// it unstuck.
	// --------------------------------------------------
	void EnemyAnt::GetAntUnstuck(Entity* entity) {
		Player* player = dynamic_cast<Player*>(entity);
		if (player == nullptr) {
			UpdateDirection(true);
		}
	}

	// --------------------------------------------------
	// This method is used to process tile map collision
	// for an enemy ant.
	// --------------------------------------------------
	void EnemyAnt::ProcessTileMapCollision(TileMap* tileMap) {
		char tileMapCollisionChar = ' ';
		short hitboxPointIndex = -1;
		CheckTileMapCollision(hitboxPointIndex, tileMapCollisionChar, tileMap);

		if (tileMapCollisionChar != ' ') {
			switch (m_Direction)
			{
			case Direction::UP:
			case Direction::DOWN:
				ApplyVerticalTileMapCollision(hitboxPointIndex, m_Hitbox->GetBoxPoints()[hitboxPointIndex][1]);
				break;

			case Direction::LEFT:
			case Direction::RIGHT:
				ApplyHorizontalTileMapCollision(hitboxPointIndex, m_Hitbox->GetBoxPoints()[hitboxPointIndex][0]);
				break;
			}
		}
	}
}