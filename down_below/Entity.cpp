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
			if (((myHitbox[0][0] <= entityHitbox[1][0] && myHitbox[0][0] >= entityHitbox[0][0]) || (myHitbox[1][0] >= entityHitbox[0][0] && myHitbox[1][0] <= entityHitbox[1][0])) && ((myHitbox[0][1] <= entityHitbox[2][1] && myHitbox[0][1] >= entityHitbox[0][1]) || (myHitbox[2][1] >= entityHitbox[0][1] && myHitbox[2][1] <= entityHitbox[2][1])) ||
				((myHitbox[0][0] < entityHitbox[0][0] && myHitbox[1][0] > entityHitbox[1][0]) && ((myHitbox[0][1] >= entityHitbox[0][1] && myHitbox[0][1] <= entityHitbox[2][1]) || (myHitbox[2][1] >= entityHitbox[0][1] && myHitbox[2][1] <= entityHitbox[2][1]))) ||
				((myHitbox[0][1] < entityHitbox[0][1] && myHitbox[2][1] > entityHitbox[2][1]) && ((myHitbox[0][0] >= entityHitbox[0][0] && myHitbox[0][0] <= entityHitbox[1][0]) || (myHitbox[1][0] >= entityHitbox[0][0] && myHitbox[1][0] <= entityHitbox[1][0])))) {
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