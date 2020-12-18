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
		distanceMoved = (int)(speed * (deltaTime / 1000));
		x += distanceMoved;
		ragDollSprite->SetPosition(x - (ragDollSprite->GetWidth() / 2), y - (ragDollSprite->GetHeight() / 2));
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
		hitbox->RenderHitbox(screen);
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
}