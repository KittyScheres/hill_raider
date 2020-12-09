#pragma once

#include "Entity.h"
#include "Image.h"

namespace DownBelow
{
	class RagDoll : public Entity
	{
	private:
		Image* ragDollSprite = nullptr;
		float speed = 0.f;
	public:
		RagDoll(int iX, int iY, float iSpeed, int iWidth, int iHeight);
		void Update(float deltaTime);
		void LateUpdate(std::vector<Entity*> entityList);
		void Render(Tmpl8::Surface* screen);
		void SetPosition(int iX, int iY);
		MovementDirection GetDirection();
		Image* GetSprite();
		~RagDoll();
	};
}