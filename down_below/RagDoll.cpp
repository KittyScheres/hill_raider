#include "RagDoll.h"

#include <cstdio>

namespace HillRaider
{
	// --------------------------------------------------
	//
	// --------------------------------------------------
	RagDoll::RagDoll(RoomCallback* iCallback, int iX, int iY, float iSpeed, int iWidth, int iHeight): Entity(iX, iY, iWidth, iHeight)
	{
		callback = iCallback;
		speed = iSpeed;
		ragDollSprite = new Image("assets/gameplay/entities/ragdoll.png", x, y);
	}

	// --------------------------------------------------
	//
	// --------------------------------------------------
	void RagDoll::Update(float deltaTime)
	{
		UpdateDirection();
		MoveRagdoll(deltaTime);
		hitbox->SetPosition(x, y);
	}

	// --------------------------------------------------
	//
	// --------------------------------------------------
	void RagDoll::LateUpdate(std::vector<Entity*> entityList)
	{
		for (auto entity : entityList) {
			if (TestBoxCollision(hitbox, entity)) {
				ApplyEntityCollision(entity);
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
				direction = Entity::MovementDirection::UP;
			}
			else if (directionVector == std::vector<int>{1, 0}) {
				direction = Entity::MovementDirection::RIGHT;
			}
			else if (directionVector == std::vector<int>{0, 1}) {
				direction = Entity::MovementDirection::DOWN;
			}
			else if (directionVector == std::vector<int>{-1, 0}) {
				direction = Entity::MovementDirection::LEFT;
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