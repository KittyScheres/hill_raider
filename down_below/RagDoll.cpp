#include "RagDoll.h"

#include <cstdio>

namespace HillRaider
{
	// --------------------------------------------------
	//
	// --------------------------------------------------
	RagDoll::RagDoll(int iX, int iY, float iSpeed, int iWidth, int iHeight): Entity(iX, iY, iWidth, iHeight)
	{
		speed = iSpeed;
		ragDollSprite = new Image("assets/gameplay/entities/ragdoll.png", x, y);
		attackHitbox = new Hitbox(x, y + attackHitboxOffset, attackHitboxWidth, attackHitboxHeight);
		lineScan = new Hitbox(x, y + lineScanOffset, lineScanWidth, lineScanHeight);
	}

	// --------------------------------------------------
	//
	// --------------------------------------------------
	void RagDoll::Update(float deltaTime)
	{
		attackFlag = false;

		UpdateDirection();
		MoveRagdoll(deltaTime);
		SetPosition(x, y);
	}

	// --------------------------------------------------
	//
	// --------------------------------------------------
	void RagDoll::LateUpdate(std::list<Entity*> entityList)
	{
		for (auto entity : entityList) {
			if (TestBoxCollision(hitbox, entity)) {
				ApplyEntityCollision(entity);
			}

			Player* player = dynamic_cast<Player*>(entity);
			if (player != nullptr && TestBoxCollision(lineScan, entity)) {
				
			}
		}
	}

	// --------------------------------------------------
	//
	// --------------------------------------------------
	void RagDoll::Render(Tmpl8::Surface* screen)
	{
		ragDollSprite->SetPosition(x - (ragDollSprite->GetWidth()) / 2, y - (ragDollSprite->GetHeight() / 2));
		ragDollSprite->DrawImage(screen);
		hitbox->RenderHitbox(screen);
		attackHitbox->RenderHitbox(screen);
		lineScan->RenderHitbox(screen);
	}

	// --------------------------------------------------
	//
	// --------------------------------------------------
	void RagDoll::TakeDamage() {
		if (--ragdollHealt <= 0) {
			callback->RemoveEntity(this);
		}
	}

	// --------------------------------------------------
	//
	// --------------------------------------------------
	void RagDoll::SetRoomCallback(RoomCallback* iCallback)
	{
		callback = iCallback;
	}

	// --------------------------------------------------
	//
	// --------------------------------------------------
	void RagDoll::SetPosition(int iX, int iY)
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
	void RagDoll::SetDirection(Entity::MovementDirection iDirection)
	{
		direction = iDirection;

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
	Entity::MovementDirection RagDoll::GetDirection()
	{
		return direction;
	}

	// --------------------------------------------------
	//
	// --------------------------------------------------
	Image* RagDoll::GetSprite()
	{
		return ragDollSprite;
	}

	// --------------------------------------------------
	//
	// --------------------------------------------------
	RagDoll::~RagDoll()
	{
		if (ragDollSprite != nullptr) {
			delete ragDollSprite;
			ragDollSprite = nullptr;
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
	void RagDoll::UpdateDirection()
	{
		std::vector<AStarNode*> path;

		switch (direction)
		{
		case Entity::MovementDirection::UP:
			path = AStar::GetIntance()->FindPath(std::vector<int>{x, y + hitbox->GetHalfHeight()}, std::vector<int>{x, y - hitbox->GetHalfHeight()});
			break;

		case Entity::MovementDirection::RIGHT:
			path = AStar::GetIntance()->FindPath(std::vector<int>{x - hitbox->GetHalfWidth(), y}, std::vector<int>{x + hitbox->GetHalfWidth(), y});
			break;

		case Entity::MovementDirection::DOWN:
			path = AStar::GetIntance()->FindPath(std::vector<int>{x, y - hitbox->GetHalfHeight()}, std::vector<int>{x, y + hitbox->GetHalfHeight()});
			break;

		case Entity::MovementDirection::LEFT:
			path = AStar::GetIntance()->FindPath(std::vector<int>{x + hitbox->GetHalfWidth(), y}, std::vector<int>{x - hitbox->GetHalfWidth(), y});
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
	void RagDoll::MoveRagdoll(float deltaTime)
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
}