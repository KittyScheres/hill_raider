#include "Entity.h"

namespace HillRaider
{
	// --------------------------------------------------
	// This constructor is used to setup the properties 
	// for a basic entity.
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
	// This method is used to set the position of an entity.
	// --------------------------------------------------
	void Entity::SetPosition(int iX, int iY)
	{
		x = iX;
		y = iY;
		hitbox->SetPosition(x, y);
	}

	// --------------------------------------------------
	// This method is used to get the position of an entity.
	// --------------------------------------------------
	std::vector<int> Entity::GetPosition()
	{
		return std::vector<int> {x, y};
	}

	// --------------------------------------------------
	// This method is used to get the width of an entity.
	// --------------------------------------------------
	int Entity::GetWidth()
	{
		return width;
	}

	// --------------------------------------------------
	// This method is used to get the height of an entity.
	// --------------------------------------------------
	int Entity::GetHeight()
	{
		return height;
	}

	// --------------------------------------------------
	// This method is used to get the direction an entity
	// is facing.
	// --------------------------------------------------
	Entity::MovementDirection Entity::GetDirection() {
		return direction;
	}

	// --------------------------------------------------
	// This method is used to get the hitbox of an entity.
	// --------------------------------------------------
	Hitbox* Entity::GetHitbox()
	{
		return hitbox;
	}
	
	// --------------------------------------------------
	// This deconstructor is used to safely free the memory
	// for the propeties of a basic entity.
	// --------------------------------------------------
	Entity::~Entity()
	{
		if (hitbox != nullptr) {
			delete hitbox;
			hitbox = nullptr;
		}
	}

	// --------------------------------------------------
	// This method is used to check for box on box collision.
	// --------------------------------------------------
	bool Entity::TestBoxCollision(Hitbox* myHitbox, Entity* otherEntity)
	{
		bool collide = false;

		int vectorX = otherEntity->GetPosition()[0] - myHitbox->GetPosition()[0];
		int vectorY = otherEntity->GetPosition()[1] - myHitbox->GetPosition()[1];
		float magnatude = sqrtf((float)(vectorX * vectorX) + (float)(vectorY * vectorY));

		// check for circel collision
		if (magnatude < (myHitbox->GetCircleRadius() + otherEntity->GetHitbox()->GetCircleRadius())) {
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
	// This method is used to stop the movement of an entity
	// when it is necessary.
	// --------------------------------------------------
	void Entity::ApplyEntityCollision(Entity* otherEntity) {
		int vX = otherEntity->GetPosition()[0] - x;
		int vY = otherEntity->GetPosition()[1] - y;
		float mag = sqrtf((float)(vX * vX) + (float)(vY * vY));
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