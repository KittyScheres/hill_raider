#include "Entity.h"

namespace DownBelow
{
	// --------------------------------------------------
	//
	// --------------------------------------------------
	Entity::Entity(int iX, int iY, int iWidth, int iHeight)
	{
		x = iX;
		y = iY;
		width = iWidth;
		height = iHeight;
		hitbox = new Hitbox(x, y, width, height);
	}

	// --------------------------------------------------
	//
	// --------------------------------------------------
	void Entity::Update(float deltaTime) {}

	// --------------------------------------------------
	//
	// --------------------------------------------------
	void Entity::LateUpdate() {}

	// --------------------------------------------------
	//
	// --------------------------------------------------
	void Entity::Render(Tmpl8::Surface* screen) {}

	// --------------------------------------------------
	//
	// --------------------------------------------------
	std::vector<int> Entity::GetPosition()
	{
		return std::vector<int> {x, y};
	}

	// --------------------------------------------------
	//
	// --------------------------------------------------
	int Entity::GetWidth()
	{
		return width;
	}

	// --------------------------------------------------
	//
	// --------------------------------------------------
	int Entity::GetHeight()
	{
		return height;
	}

	// --------------------------------------------------
	//
	// --------------------------------------------------
	Hitbox* Entity::GetHitbox()
	{
		return hitbox;
	}
	
	// --------------------------------------------------
	//
	// --------------------------------------------------
	Entity::~Entity()
	{
		delete hitbox;
		hitbox = nullptr;
	}

	// --------------------------------------------------
	//
	// --------------------------------------------------
	bool Entity::TestBoxCollision(Entity* otherEntity)
	{
		bool collide = false;

		int vectorX = otherEntity->GetPosition()[0] - x;
		int vectorY = otherEntity->GetPosition()[1] - y;
		float magnatude = sqrtf((vectorX * vectorX) + (vectorY * vectorY));

		// check for circel collision
		if (magnatude < (hitbox->GetHalfDiameter() + otherEntity->GetHitbox()->GetHalfDiameter())) {
			std::vector<std::vector<int>> myHitbox = hitbox->GetBoxPoints();
			std::vector<std::vector<int>> entityHitbox = otherEntity->GetHitbox()->GetBoxPoints();

			// check for box collision
			if (((myHitbox[0][0] < entityHitbox[1][0] && myHitbox[0][0] > entityHitbox[0][0]) || (myHitbox[1][0] > entityHitbox[0][0] && myHitbox[1][0] < entityHitbox[1][0])) &&
				((myHitbox[0][1] < entityHitbox[2][1] && myHitbox[0][1] > entityHitbox[0][1]) || (myHitbox[2][1] > entityHitbox[0][1] && myHitbox[2][1] < entityHitbox[2][1]))) {
				collide = true;
			}
		}

		return collide;
	}
}