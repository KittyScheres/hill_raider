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
	Direction Entity::GetDirection() {
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
		case Direction::UP:
			if ((nX > -0.75f && nX < 0.75f) && nY < 0.f) {
				y += distanceMoved;
			}
			break;

		case Direction::RIGHT:
			if ((nY > -0.75f && nY < 0.75f) && nX > 0.f) {
				x -= distanceMoved;
			}
			break;

		case Direction::DOWN:
			if ((nX > -0.75f && nX < 0.75f) && nY > 0.f) {
				y -= distanceMoved;
			}
			break;

		case Direction::LEFT:
			if ((nY > -0.75f && nY < 0.75f) && nX < 0.f) {
				x += distanceMoved;
			}
			break;
		}

		this->SetPosition(x, y);
	}

	// --------------------------------------------------
	// This method is used to check the tile map collision
	// for an entity.
	// --------------------------------------------------
	void Entity::CheckTileMapCollision(short& _hitboxPoint, char& _collisionChar, TileMap* tileMap) {
		std::vector<std::vector<int>> hitboxPoints = hitbox->GetBoxPoints();
		char collisionChar = ' ';
		short index = 0;

		for (int i = 0; i < 4; i++) {
			if (tileMap->GetCollision(hitboxPoints[i][0], hitboxPoints[i][1]) != ' ' && collisionChar != 'x') {
				_collisionChar = tileMap->GetCollision(hitboxPoints[i][0], hitboxPoints[i][1]);
				_hitboxPoint = i;
			}
		}
	}

	// --------------------------------------------------
	// This method is used to push an entity away from
	// tile map obsticals the entity has collided with 
	// while moving in a vertical direction.
	// --------------------------------------------------
	void Entity::ApplyVerticalTileMapCollision(int hitboxPointIndex, int hitboxPointYPos)
	{
		switch (hitboxPointIndex & 2)
		{
		case 0:
			SetPosition(x, y + (64 - (hitboxPointYPos & 63)));
			break;

		case 2:
			SetPosition(x, y - (hitboxPointYPos & 63));
			break;
		}

	}

	// --------------------------------------------------
	// This method is used to push an entity away from
	// tile map obsticals the entity has collided with 
	// while moving in a horizontal direction.
	// --------------------------------------------------
	void Entity::ApplyHorizontalTileMapCollision(int hitboxPointIndex, int hitboxPointXPos)
	{
		switch (hitboxPointIndex & 1)
		{
		case 0:
			SetPosition(x + (64 - (hitboxPointXPos & 63)), y);
			break;

		case 1:
			SetPosition(x - (hitboxPointXPos & 63), y);
			break;
		}
	}
}