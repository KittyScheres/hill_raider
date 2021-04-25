#include "entity.h"

namespace HillRaider
{
	// --------------------------------------------------
	// This constructor is used to setup the properties 
	// for a basic entity.
	// --------------------------------------------------
	Entity::Entity(int x, int y, int width, int height)
	{
		m_X = x;
		m_Y = y;
		m_Width = width;
		m_Height = height;
		m_Hitbox = new Hitbox(m_X, m_Y, m_Width, m_Height);
	}

	// --------------------------------------------------
	// This method is used to set the position of an entity.
	// --------------------------------------------------
	void Entity::SetPosition(int x, int y)
	{
		m_X = x;
		m_Y = y;
		m_Hitbox->SetPosition(m_X, m_Y);
	}

	// --------------------------------------------------
	// This method is used to get the position of an entity.
	// --------------------------------------------------
	std::vector<int> Entity::GetPosition()
	{
		return std::vector<int> {m_X, m_Y};
	}

	// --------------------------------------------------
	// This method is used to get the width of an entity.
	// --------------------------------------------------
	int Entity::GetWidth()
	{
		return m_Width;
	}

	// --------------------------------------------------
	// This method is used to get the height of an entity.
	// --------------------------------------------------
	int Entity::GetHeight()
	{
		return m_Height;
	}

	// --------------------------------------------------
	// This method is used to get the direction an entity
	// is facing.
	// --------------------------------------------------
	Direction Entity::GetDirection() {
		return m_Direction;
	}

	// --------------------------------------------------
	// This method is used to get the hitbox of an entity.
	// --------------------------------------------------
	Hitbox* Entity::GetHitbox()
	{
		return m_Hitbox;
	}
	
	// --------------------------------------------------
	// This deconstructor is used to safely free the memory
	// for the propeties of a basic entity.
	// --------------------------------------------------
	Entity::~Entity()
	{
		if (m_Hitbox != nullptr) {
			delete m_Hitbox;
			m_Hitbox = nullptr;
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
		int vectorX = otherEntity->GetPosition()[0] - m_X;
		int vectorY = otherEntity->GetPosition()[1] - m_Y;
		float magnitude = sqrtf((float)(vectorX * vectorX) + (float)(vectorY * vectorY));
		float normalizedVectorX = vectorX / magnitude;
		float normalizedVectorY = vectorY / magnitude;

		switch (m_Direction)
		{
		case Direction::UP:
			if ((normalizedVectorX > -0.75f && normalizedVectorX < 0.75f) && normalizedVectorY < 0.f) {
				m_Y += m_DistanceMoved;
			}
			break;

		case Direction::RIGHT:
			if ((normalizedVectorY > -0.75f && normalizedVectorY < 0.75f) && normalizedVectorX > 0.f) {
				m_X -= m_DistanceMoved;
			}
			break;

		case Direction::DOWN:
			if ((normalizedVectorX > -0.75f && normalizedVectorX < 0.75f) && normalizedVectorY > 0.f) {
				m_Y -= m_DistanceMoved;
			}
			break;

		case Direction::LEFT:
			if ((normalizedVectorY > -0.75f && normalizedVectorY < 0.75f) && normalizedVectorX < 0.f) {
				m_X += m_DistanceMoved;
			}
			break;
		}

		this->SetPosition(m_X, m_Y);
	}

	// --------------------------------------------------
	// This method is used to check the tile map collision
	// for an entity.
	// --------------------------------------------------
	void Entity::CheckTileMapCollision(short& _hitboxPoint, char& _collisionChar, TileMap* tileMap) {
		std::vector<std::vector<int>> hitboxPoints = m_Hitbox->GetBoxPoints();

		for (int i = 0; i < 4; i++) {
			if (tileMap->GetCollision(hitboxPoints[i][0], hitboxPoints[i][1]) != ' ' && _collisionChar != 'x') {
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
			SetPosition(m_X, m_Y + (64 - (hitboxPointYPos & 63)));
			break;

		case 2:
			SetPosition(m_X, m_Y - (hitboxPointYPos & 63));
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
			SetPosition(m_X + (64 - (hitboxPointXPos & 63)), m_Y);
			break;

		case 1:
			SetPosition(m_X - (hitboxPointXPos & 63), m_Y);
			break;
		}
	}
}