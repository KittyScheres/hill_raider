#include "Entity.h"

namespace HillRaider
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
	void Entity::SetPosition(int iX, int iY)
	{
		x = iX;
		y = iY;
		hitbox->SetPosition(x, y);
	}

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
	Entity::MovementDirection Entity::GetDirection() {
		return direction;
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
		if (hitbox != nullptr) {
			delete hitbox;
			hitbox = nullptr;
		}
	}

	// --------------------------------------------------
	//
	// --------------------------------------------------
	bool Entity::TestBoxCollision(Hitbox* myHitbox, Entity* otherEntity)
	{
		bool collide = false;

		int vectorX = otherEntity->GetPosition()[0] - myHitbox->GetPosition()[0];
		int vectorY = otherEntity->GetPosition()[1] - myHitbox->GetPosition()[1];
		float magnatude = sqrtf((vectorX * vectorX) + (vectorY * vectorY));

		// check for circel collision
		if (magnatude < (myHitbox->GetHalfDiameter() + otherEntity->GetHitbox()->GetHalfDiameter())) {
			std::vector<std::vector<int>> myHitboxPoints = myHitbox->GetBoxPoints();
			std::vector<std::vector<int>> entityHitboxPoints = otherEntity->GetHitbox()->GetBoxPoints();

			// check for box collision
			if (((myHitboxPoints[0][0] <= entityHitboxPoints[1][0] && myHitboxPoints[0][0] >= entityHitboxPoints[0][0]) || (myHitboxPoints[1][0] >= entityHitboxPoints[0][0] && myHitboxPoints[1][0] <= entityHitboxPoints[1][0])) && ((myHitboxPoints[0][1] <= entityHitboxPoints[2][1] && myHitboxPoints[0][1] >= entityHitboxPoints[0][1]) || (myHitboxPoints[2][1] >= entityHitboxPoints[0][1] && myHitboxPoints[2][1] <= entityHitboxPoints[2][1])) ||
				((myHitboxPoints[0][0] < entityHitboxPoints[0][0] && myHitboxPoints[1][0] > entityHitboxPoints[1][0]) && ((myHitboxPoints[0][1] >= entityHitboxPoints[0][1] && myHitboxPoints[0][1] <= entityHitboxPoints[2][1]) || (myHitboxPoints[2][1] >= entityHitboxPoints[0][1] && myHitboxPoints[2][1] <= entityHitboxPoints[2][1]))) ||
				((myHitboxPoints[0][1] < entityHitboxPoints[0][1] && myHitboxPoints[2][1] > entityHitboxPoints[2][1]) && ((myHitboxPoints[0][0] >= entityHitboxPoints[0][0] && myHitboxPoints[0][0] <= entityHitboxPoints[1][0]) || (myHitboxPoints[1][0] >= entityHitboxPoints[0][0] && myHitboxPoints[1][0] <= entityHitboxPoints[1][0])))) {
				collide = true;
				
			}
		}

		return collide;
	}

	// --------------------------------------------------
	//
	// --------------------------------------------------
	void Entity::ApplyEntityCollision(Entity* otherEntity) {
		int vX = otherEntity->GetPosition()[0] - x;
		int vY = otherEntity->GetPosition()[1] - y;
		float mag = sqrtf((vX * vX) + (vY * vY));
		float nX = vX / mag;
		float nY = vY / mag;

		switch (direction)
		{
		case Entity::MovementDirection::UP:
			if ((nX > -0.75f && nX < 0.75f) && nY < 0.f) {
				y += distanceMoved;
			}
			break;

		case Entity::MovementDirection::RIGHT:
			if ((nY > -0.75f && nY < 0.75f) && nX > 0.f) {
				x -= distanceMoved;
			}
			break;

		case Entity::MovementDirection::DOWN:
			if ((nX > -0.75f && nX < 0.75f) && nY > 0.f) {
				y -= distanceMoved;
			}
			break;

		case Entity::MovementDirection::LEFT:
			if ((nY > -0.75f && nY < 0.75f) && nX < 0.f) {
				x += distanceMoved;
			}
			break;
		}

		this->SetPosition(x, y);
	}
}