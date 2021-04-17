#include "EnemyAnt.h"

namespace HillRaider
{
	// --------------------------------------------------
	// This contructor is used to setup the properties
	// for an enemy ant entity.
	// --------------------------------------------------
	EnemyAnt::EnemyAnt(int iX, int iY): Entity(iX, iY, 28, 62)
	{
		legsAnimation = new Animation("assets/entities/red_ant_legs.png", 4, 4, timePerframeWalkingAnimation, iX, iY, true);
		bodyAnimation = new Animation("assets/entities/red_ant_body.png", 4, 4, 75.f, iX, iY, false);
		attackHitbox = new Hitbox(x, y + attackHitboxOffset, attackHitboxWidth, attackHitboxHeight);
		lineScan = new Hitbox(x, y + lineScanOffset, lineScanWidth, lineScanHeight);
	}

	// --------------------------------------------------
	// This method is used to update an enemy ant entity.
	// --------------------------------------------------
	void EnemyAnt::Update(float deltaTime)
	{
		if (!lungeFlag) {
			UpdateDirection();
			MoveEnemyAnt(deltaTime);

			//make decision timer
			if (!makeDecisionFlag) {
				if (makeDecisionTimer >= makeDecisionCooldown) {
					makeDecisionFlag = true;
					makeDecisionTimer = 0.f;
				}
				else {
					makeDecisionTimer += deltaTime;
				}
			}

			//attack cooldown timer
			if (lungeCooldownFlag) {
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
			//is attacking
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

		legsAnimation->UpdateAnimation(deltaTime);
		SetPosition(x, y);
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
			//entity on entity collision
			if (TestBoxCollision(hitbox, entity)) {
				ApplyEntityCollision(entity);
				GetAntUnstuck(entity);
			}

			//entity on attack hitbox collision
			if (lungeFlag) {
				Player* player = dynamic_cast<Player*>(entity);
				if (player != nullptr && TestBoxCollision(attackHitbox, entity)) {
					player->TakeDamage();
					lungeFlag = false;
					lungeDurationTimer = 0.f;
				}
			}

			//entity on attack range collision
			if (makeDecisionFlag && !lungeCooldownFlag) {
				if (TestBoxCollision(lineScan, entity)) {
					int distanceVectorX = entity->GetPosition()[0] - x;
					int distanceVectorY = entity->GetPosition()[1] - y;
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
		
		//attack decision
		if (playerInLineOfSide) {
			if ((rand() & 1) == 0) {
				legsAnimation->SetTimePerFrame(lungeTimePerFrameWalkingAnimation);
				lungeFlag = true;
				lungeCooldownFlag = true;
			}
			makeDecisionFlag = false;
		}
	}

	// --------------------------------------------------
	// This method is used to draw an enemy ant entity
	// on to the screen.
	// --------------------------------------------------
	void EnemyAnt::Render(Tmpl8::Surface* screen)
	{
		legsAnimation->SetPosition(x - (bodyAnimation->GetWidth()) / 2, y - (bodyAnimation->GetHeight() / 2));
		bodyAnimation->SetPosition(x - (bodyAnimation->GetWidth()) / 2, y - (bodyAnimation->GetHeight() / 2));
		
		legsAnimation->DrawAnimation(screen);
		bodyAnimation->DrawAnimation(screen);
	}

	// --------------------------------------------------
	// This method is used to make an enemy ant entity take
	// damage.
	// --------------------------------------------------
	void EnemyAnt::TakeDamage() {
		makeDecisionFlag = false;
		makeDecisionTimer = 0.f;

		lungeFlag = false;
		lungeCooldownFlag = false;
		lungeDurationTimer = 0.f;
		legsAnimation->SetTimePerFrame(timePerframeWalkingAnimation);

		if (--ragdollHealt <= 0) {
			roomCallback->RemoveEntity(this);
		}
	}

	// --------------------------------------------------
	// This method is used to set the room callback for
	// an enemy ant entity.
	// --------------------------------------------------
	void EnemyAnt::SetRoomCallback(RoomCallback* callback)
	{
		roomCallback = callback;
	}

	// --------------------------------------------------
	// This method is used to set the position of an enemy
	// ant entity.
	// --------------------------------------------------
	void EnemyAnt::SetPosition(int iX, int iY)
	{
		x = iX;
		y = iY;
		hitbox->SetPosition(x, y);

		switch (direction)
		{
		case Direction::UP:
		case Direction::DOWN:
			attackHitbox->SetPosition(x, y + attackHitboxOffset);
			lineScan->SetPosition(x, y + lineScanOffset);
			break;

		case Direction::LEFT:
		case Direction::RIGHT:
			attackHitbox->SetPosition(x + attackHitboxOffset, y);
			lineScan->SetPosition(x + lineScanOffset, y);
			break;
		}
	}

	// --------------------------------------------------
	// This method is used to set the direction of an 
	// enemy ant entity.
	// --------------------------------------------------
	void EnemyAnt::SetDirection(Direction iDirection)
	{
		direction = iDirection;

		legsAnimation->SetCurrentYFrame((int)direction);
		bodyAnimation->SetCurrentYFrame((int)direction);

		switch (direction)
		{
		case Direction::UP:
			attackHitboxOffset = -std::abs(attackHitboxOffset);
			lineScanOffset = -std::abs(lineScanOffset);
			hitbox->SetWidth(width);
			hitbox->SetHeight(height);
			attackHitbox->SetWidth(attackHitboxWidth);
			attackHitbox->SetHeight(attackHitboxHeight);
			lineScan->SetWidth(lineScanWidth);
			lineScan->SetHeight(lineScanHeight);
			break;

		case Direction::RIGHT:
			attackHitboxOffset = std::abs(attackHitboxOffset);
			lineScanOffset = std::abs(lineScanOffset);
			hitbox->SetWidth(height);
			hitbox->SetHeight(width);
			attackHitbox->SetWidth(attackHitboxHeight);
			attackHitbox->SetHeight(attackHitboxWidth);
			lineScan->SetWidth(lineScanHeight);
			lineScan->SetHeight(lineScanWidth);
			break;

		case Direction::DOWN:
			attackHitboxOffset = std::abs(attackHitboxOffset);
			lineScanOffset = std::abs(lineScanOffset);
			hitbox->SetWidth(width);
			hitbox->SetHeight(height);
			attackHitbox->SetWidth(attackHitboxWidth);
			attackHitbox->SetHeight(attackHitboxHeight);
			lineScan->SetWidth(lineScanWidth);
			lineScan->SetHeight(lineScanHeight);
			break;

		case Direction::LEFT:
			attackHitboxOffset = -std::abs(attackHitboxOffset);
			lineScanOffset = -std::abs(lineScanOffset);
			hitbox->SetWidth(height);
			hitbox->SetHeight(width);
			attackHitbox->SetWidth(attackHitboxHeight);
			attackHitbox->SetHeight(attackHitboxWidth);
			lineScan->SetWidth(lineScanHeight);
			lineScan->SetHeight(lineScanWidth);
			break;
		}
	}

	// --------------------------------------------------
	// This method is used to get the direction of an enemy
	// ant entity.
	// --------------------------------------------------
	Direction EnemyAnt::GetDirection()
	{
		return direction;
	}

	// --------------------------------------------------
	// This mehtod is used to get the sprite of an enemy
	// ant entity.
	// --------------------------------------------------
	Animation* EnemyAnt::GetSprite()
	{
		return bodyAnimation;
	}

	// --------------------------------------------------
	// This destructor is used to safely free the memory 
	// of the properties of an enemy ant entity.
	// --------------------------------------------------
	EnemyAnt::~EnemyAnt()
	{
		if (legsAnimation != nullptr) {
			delete legsAnimation;
			legsAnimation = nullptr;
		}

		if (bodyAnimation != nullptr) {
			delete bodyAnimation;
			bodyAnimation = nullptr;
		}

		if (attackHitbox != nullptr) {
			delete attackHitbox;
			attackHitbox = nullptr;
		}

		if (lineScan != nullptr) {
			delete lineScan;
			lineScan = nullptr;
		}
	}

	// --------------------------------------------------
	// This method is used to update the current movement
	// direction of an enemy ant according to the output
	// of the a* path finding algorithm.
	// --------------------------------------------------
	void EnemyAnt::UpdateDirection(bool bypassCheck)
	{
		std::vector<AStarNode*> path;

		switch (direction)
		{
		case Direction::UP:
			path = AStar::GetIntance()->FindPath(this, std::vector<int>{x, y + hitbox->GetHalfHeight()}, std::vector<int>{x, y - hitbox->GetHalfHeight()}, bypassCheck);
			break;

		case Direction::RIGHT:
			path = AStar::GetIntance()->FindPath(this, std::vector<int>{x - hitbox->GetHalfWidth(), y}, std::vector<int>{x + hitbox->GetHalfWidth(), y}, bypassCheck);
			break;

		case Direction::DOWN:
			path = AStar::GetIntance()->FindPath(this, std::vector<int>{x, y - hitbox->GetHalfHeight()}, std::vector<int>{x, y + hitbox->GetHalfHeight()}, bypassCheck);
			break;

		case Direction::LEFT:
			path = AStar::GetIntance()->FindPath(this, std::vector<int>{x + hitbox->GetHalfWidth(), y}, std::vector<int>{x - hitbox->GetHalfWidth(), y}, bypassCheck);
			break;
		}

		if (path.size() > 1) {
			std::vector<int> directionVector{ path[1]->GetGridX() - path[0]->GetGridX(), path[1]->GetGridY() - path[0]->GetGridY() };

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
	// Thid method is used to move an enemy ant entitie
	// according the current movement direction.
	// --------------------------------------------------
	void EnemyAnt::MoveEnemyAnt(float deltaTime)
	{
		distanceMoved = 0;

		switch (direction)
		{
		case Direction::UP:
			distanceMoved = (int)(speed * (deltaTime / 1000));
			y -= distanceMoved;
			break;
			
		case Direction::RIGHT:
			distanceMoved = (int)(speed * (deltaTime / 1000));
			x += distanceMoved;
			break;

		case Direction::DOWN:
			distanceMoved = (int)(speed * (deltaTime / 1000));
			y += distanceMoved;
			break;

		case Direction::LEFT:
			distanceMoved = (int)(speed * (deltaTime / 1000));
			x -= distanceMoved;
			break;
		}
	}

	// --------------------------------------------------
	// This method is used to make an enemy ant entity 
	// move in the current direction with an icreased 
	// movement speed.
	// --------------------------------------------------
	void EnemyAnt::Lunge(float deltaTime)
	{
		distanceMoved = 0;

		switch (direction)
		{
		case Direction::UP:
			distanceMoved = (int)((speed + lungeSpeedIncrease) * (deltaTime / 1000));
			y -= distanceMoved;
			break;

		case Direction::RIGHT:
			distanceMoved = (int)((speed + lungeSpeedIncrease) * (deltaTime / 1000));
			x += distanceMoved;
			break;

		case Direction::DOWN:
			distanceMoved = (int)((speed + lungeSpeedIncrease) * (deltaTime / 1000));
			y += distanceMoved;
			break;

		case Direction::LEFT:
			distanceMoved = (int)((speed + lungeSpeedIncrease) * (deltaTime / 1000));
			x -= distanceMoved;
			break;
		}
	}

	// --------------------------------------------------
	// This method is used to update the movement direction
	// of an enemy ant entity inorder to attempt to get
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
			switch (direction)
			{
			case Direction::UP:
			case Direction::DOWN:
				ApplyVerticalTileMapCollision(hitboxPointIndex, hitbox->GetBoxPoints()[hitboxPointIndex][1]);
				break;

			case Direction::LEFT:
			case Direction::RIGHT:
				ApplyHorizontalTileMapCollision(hitboxPointIndex, hitbox->GetBoxPoints()[hitboxPointIndex][0]);
				break;
			}
		}
	}
}