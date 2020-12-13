#include "RagDoll.h"

#include <cstdio>

namespace DownBelow
{
	// --------------------------------------------------
	//
	// --------------------------------------------------
	RagDoll::RagDoll(int iX, int iY, float iSpeed, int iWidth, int iHeight): Entity(iX, iY, iWidth, iHeight)
	{
		speed = iSpeed;
		direction = Entity::MovementDirection::RIGHT;
		ragDollSprite = new Image("assets/gameplay/entities/ragdoll.png", x, y);
	}

	// --------------------------------------------------
	//
	// --------------------------------------------------
	void RagDoll::Update(float deltaTime)
	{
		AStar::GetIntance()->FindPath(GetPosition());
		distanceMoved = (int)(speed * (deltaTime / 1000));
		x += distanceMoved;
		hitbox->SetPosition(x, y);
		ragDollSprite->SetPosition(x - (ragDollSprite->GetWidth() / 2), y - (ragDollSprite->GetHeight() / 2));
	}

	// --------------------------------------------------
	//
	// --------------------------------------------------
	void RagDoll::LateUpdate(std::vector<Entity*> entityList)
	{
		for (auto entity : entityList) {
			if (TestBoxCollision(entity)) {
				ApplyEntityCollision(entity);
				ragDollSprite->SetPosition(x - (ragDollSprite->GetWidth() / 2), y - (ragDollSprite->GetHeight() / 2));
				hitbox->SetPosition(x, y);
			}
		}
	}

	// --------------------------------------------------
	//
	// --------------------------------------------------
	void RagDoll::Render(Tmpl8::Surface* screen)
	{
		ragDollSprite->DrawImage(screen);
	}

	// --------------------------------------------------
	//
	// --------------------------------------------------
	void RagDoll::SetPosition(int iX, int iY)
	{
		x = iX;
		y = iY;
		hitbox->SetPosition(x, y);
		ragDollSprite->SetPosition(x - (ragDollSprite->GetWidth() / 2), y - (ragDollSprite->GetHeight() / 2));
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
		delete ragDollSprite;
		ragDollSprite = nullptr;
	}
}