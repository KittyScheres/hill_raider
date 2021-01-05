#include "EnemyAnt.h"

namespace HillRaider
{
	// --------------------------------------------------
	//
	// --------------------------------------------------
	EnemyAnt::EnemyAnt(int iX, int iY): Entity(iX, iY, 38, 62)
	{
		legsAnimation = new Animation("assets/entities/red_ant_legs.png", 4, 4, timePerframeWalkingAnimation, iX, iY, true);
		bodyAnimation = new Animation("assets/entities/red_ant_body.png", 4, 4, 75.f, iX, iY, false);
		attackHitbox = new Hitbox(x, y + attackHitboxOffset, attackHitboxWidth, attackHitboxHeight);
		lineScan = new Hitbox(x, y + lineScanOffset, lineScanWidth, lineScanHeight);
	}

	// --------------------------------------------------
	//
	// --------------------------------------------------
	void EnemyAnt::Update(float deltaTime)
	{
		if (!lungeFlag) {
			UpdateDirection();
			MoveRagdoll(deltaTime);

			if (!makeDecisionFlag) {
				if (makeDecisionTimer >= makeDecisionCooldown) {
					makeDecisionFlag = true;
					makeDecisionTimer = 0.f;
				}
				else {
					makeDecisionTimer += deltaTime;
				}
			}

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
	//
	// --------------------------------------------------
	void EnemyAnt::LateUpdate(std::list<Entity*> entityList)
	{
		float smallestDistance = 10000.f;
		bool playerInLineOfSide = false;

		for (auto entity : entityList) {
			if (TestBoxCollision(hitbox, entity)) {
				ApplyEntityCollision(entity);
				GetAntUnstuck(entity);
			}

			if (lungeFlag) {
				Player* player = dynamic_cast<Player*>(entity);
				if (player != nullptr && TestBoxCollision(attackHitbox, entity)) {
					player->TakeDamage();
					lungeFlag = false;
					lungeDurationTimer = 0.f;
				}
			}

			if (makeDecisionFlag && !lungeCooldownFlag) {
				if (TestBoxCollision(lineScan, entity)) {
					int distanceVectorX = entity->GetPosition()[0] - x;
					int distanceVectorY = entity->GetPosition()[1] - y;
					float distance = sqrtf((distanceVectorX * distanceVectorX) + (distanceVectorY * distanceVectorY));
					Player* player = dynamic_cast<Player*>(entity);
					if (player != nullptr && distance < smallestDistance) {
						playerInLineOfSide = true;
						smallestDistance = distance;
					}
					else if(distance < smallestDistance) {
						playerInLineOfSide = false;
						smallestDistance = distance;
					}
				}
			}			
		}

		if (playerInLineOfSide) {
			if ((rand() & 2) == 2) {
				legsAnimation->SetTimePerFrame(lungeTimePerFrameWalkingAnimation);
				lungeFlag = true;
				lungeCooldownFlag = true;
			}
			makeDecisionFlag = false;
		}
	}

	// --------------------------------------------------
	//
	// --------------------------------------------------
	void EnemyAnt::Render(Tmpl8::Surface* screen)
	{
		legsAnimation->SetPosition(x - (bodyAnimation->GetWidth()) / 2, y - (bodyAnimation->GetHeight() / 2));
		bodyAnimation->SetPosition(x - (bodyAnimation->GetWidth()) / 2, y - (bodyAnimation->GetHeight() / 2));
	
		legsAnimation->DrawAnimation(screen);
		bodyAnimation->DrawAnimation(screen);
	}

	// --------------------------------------------------
	//
	// --------------------------------------------------
	void EnemyAnt::TakeDamage() {
		if (--ragdollHealt <= 0) {
			callback->RemoveEntity(this);
		}
	}

	// --------------------------------------------------
	//
	// --------------------------------------------------
	void EnemyAnt::SetRoomCallback(RoomCallback* iCallback)
	{
		callback = iCallback;
	}

	// --------------------------------------------------
	//
	// --------------------------------------------------
	void EnemyAnt::SetPosition(int iX, int iY)
	{
		x = iX;
		y = iY;
		hitbox->SetPosition(x, y);

		switch (direction)
		{
		case Entity::MovementDirection::UP:
		case Entity::MovementDirection::DOWN:
			attackHitbox->SetPosition(x, y + attackHitboxOffset);
			lineScan->SetPosition(x, y + lineScanOffset);
			break;

		case Entity::MovementDirection::LEFT:
		case Entity::MovementDirection::RIGHT:
			attackHitbox->SetPosition(x + attackHitboxOffset, y);
			lineScan->SetPosition(x + lineScanOffset, y);
			break;
		}
	}

	// --------------------------------------------------
	//
	// --------------------------------------------------
	void EnemyAnt::SetDirection(Entity::MovementDirection iDirection)
	{
		direction = iDirection;

		legsAnimation->SetCurrentYFrame((int)direction);
		bodyAnimation->SetCurrentYFrame((int)direction);

		switch (direction)
		{
		case Entity::MovementDirection::UP:
			attackHitboxOffset = -std::abs(attackHitboxOffset);
			lineScanOffset = -std::abs(lineScanOffset);
			hitbox->SetWidth(width);
			hitbox->SetHeight(height);
			attackHitbox->SetWidth(attackHitboxWidth);
			attackHitbox->SetHeight(attackHitboxHeight);
			lineScan->SetWidth(lineScanWidth);
			lineScan->SetHeight(lineScanHeight);
			break;

		case Entity::MovementDirection::RIGHT:
			attackHitboxOffset = std::abs(attackHitboxOffset);
			lineScanOffset = std::abs(lineScanOffset);
			hitbox->SetWidth(height);
			hitbox->SetHeight(width);
			attackHitbox->SetWidth(attackHitboxHeight);
			attackHitbox->SetHeight(attackHitboxWidth);
			lineScan->SetWidth(lineScanHeight);
			lineScan->SetHeight(lineScanWidth);
			break;

		case Entity::MovementDirection::DOWN:
			attackHitboxOffset = std::abs(attackHitboxOffset);
			lineScanOffset = std::abs(lineScanOffset);
			hitbox->SetWidth(width);
			hitbox->SetHeight(height);
			attackHitbox->SetWidth(attackHitboxWidth);
			attackHitbox->SetHeight(attackHitboxHeight);
			lineScan->SetWidth(lineScanWidth);
			lineScan->SetHeight(lineScanHeight);
			break;

		case Entity::MovementDirection::LEFT:
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
	//
	// --------------------------------------------------
	Entity::MovementDirection EnemyAnt::GetDirection()
	{
		return direction;
	}

	// --------------------------------------------------
	//
	// --------------------------------------------------
	Animation* EnemyAnt::GetSprite()
	{
		return bodyAnimation;
	}

	// --------------------------------------------------
	//
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
	//
	// --------------------------------------------------
	void EnemyAnt::UpdateDirection(bool bypassCheck)
	{
		std::vector<AStarNode*> path;

		switch (direction)
		{
		case Entity::MovementDirection::UP:
			path = AStar::GetIntance()->FindPath(this, std::vector<int>{x, y + hitbox->GetHalfHeight()}, std::vector<int>{x, y - hitbox->GetHalfHeight()}, bypassCheck);
			break;

		case Entity::MovementDirection::RIGHT:
			path = AStar::GetIntance()->FindPath(this, std::vector<int>{x - hitbox->GetHalfWidth(), y}, std::vector<int>{x + hitbox->GetHalfWidth(), y}, bypassCheck);
			break;

		case Entity::MovementDirection::DOWN:
			path = AStar::GetIntance()->FindPath(this, std::vector<int>{x, y - hitbox->GetHalfHeight()}, std::vector<int>{x, y + hitbox->GetHalfHeight()}, bypassCheck);
			break;

		case Entity::MovementDirection::LEFT:
			path = AStar::GetIntance()->FindPath(this, std::vector<int>{x + hitbox->GetHalfWidth(), y}, std::vector<int>{x - hitbox->GetHalfWidth(), y}, bypassCheck);
			break;
		}

		if (path.size() > 1) {
			std::vector<int> directionVector{ path[1]->GetGridX() - path[0]->GetGridX(), path[1]->GetGridY() - path[0]->GetGridY() };

			if (directionVector == std::vector<int>{0, -1}) {
				SetDirection(Entity::MovementDirection::UP);
			}
			else if (directionVector == std::vector<int>{1, 0}) {
				SetDirection(Entity::MovementDirection::RIGHT);
			}
			else if (directionVector == std::vector<int>{0, 1}) {
				SetDirection(Entity::MovementDirection::DOWN);
			}
			else if (directionVector == std::vector<int>{-1, 0}) {
				SetDirection(Entity::MovementDirection::LEFT);
			}
		}
	}

	// --------------------------------------------------
	//
	// --------------------------------------------------
	void EnemyAnt::MoveRagdoll(float deltaTime)
	{
		distanceMoved = 0;

		switch (direction)
		{
		case Entity::MovementDirection::UP:
			distanceMoved = (int)(speed * (deltaTime / 1000));
			y -= distanceMoved;
			break;
			
		case Entity::MovementDirection::RIGHT:
			distanceMoved = (int)(speed * (deltaTime / 1000));
			x += distanceMoved;
			break;

		case Entity::MovementDirection::DOWN:
			distanceMoved = (int)(speed * (deltaTime / 1000));
			y += distanceMoved;
			break;

		case Entity::MovementDirection::LEFT:
			distanceMoved = (int)(speed * (deltaTime / 1000));
			x -= distanceMoved;
			break;
		}
	}

	// --------------------------------------------------
	//
	// --------------------------------------------------
	void EnemyAnt::Lunge(float deltaTime)
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

	// --------------------------------------------------
	//
	// --------------------------------------------------
	void EnemyAnt::GetAntUnstuck(Entity* entity) {
		Player* player = dynamic_cast<Player*>(entity);
		if (player == nullptr) {
			UpdateDirection(true);
		}
	}
}