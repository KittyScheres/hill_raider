#include "FoodPointsPickup.h"

namespace HillRaider
{
	// --------------------------------------------------
	// This constructor is used to setup the properties
	// for a food points pickup entity.
	// --------------------------------------------------
	FoodPointsPickup::FoodPointsPickup(short points, int x, int y): Entity(x, y, 44, 38)
	{
		m_FoodPickupTexture = new Image("assets/entities/food_pickup.png", 0, 0);
		m_FoodPickupTexture->SetPosition(m_X - (m_FoodPickupTexture->GetWidth() / 2), m_Y - (m_FoodPickupTexture->GetHeight() / 2));
		m_Points = points;
	}

	// --------------------------------------------------
	// This method is used to draw the food poins pickup
	// on to the screen.
	// --------------------------------------------------
	void FoodPointsPickup::Render(Tmpl8::Surface* screen)
	{
		m_FoodPickupTexture->DrawImage(screen);
	}

	// --------------------------------------------------
	// This method is used to set the room callback for 
	// a food points pickup entity.
	// --------------------------------------------------
	void FoodPointsPickup::SetRoomCallback(RoomCallback* callback)
	{
		m_RoomCallback = callback;
	}

	// --------------------------------------------------
	// This method is used to set the position of a food
	// points pickup entity.
	// --------------------------------------------------
	void FoodPointsPickup::SetPosition(int x, int y)
	{
		m_X = x;
		m_Y = y;
		m_Hitbox->SetPosition(m_X, m_Y);
		m_FoodPickupTexture->SetPosition(m_X - (m_FoodPickupTexture->GetWidth() / 2), m_Y - (m_FoodPickupTexture->GetHeight() / 2));
	}

	// --------------------------------------------------
	// This method is used to remove a food points pickup
	// entity from a room.
	// --------------------------------------------------
	void FoodPointsPickup::RemoveFoodPointsPickup()
	{
		m_RoomCallback->RemoveEntity(this);
	}

	// --------------------------------------------------
	// This method is used to get the points value of a 
	// food points pickup entity.
	// --------------------------------------------------
	short FoodPointsPickup::GetPoints()
	{
		return m_Points;
	}

	// --------------------------------------------------
	// This deconstructor is used to safely free the 
	// memory of the properties of a food points pickup
	// entity.
	// --------------------------------------------------
	FoodPointsPickup::~FoodPointsPickup()
	{
		if (m_FoodPickupTexture != nullptr) {
			delete m_FoodPickupTexture;
			m_FoodPickupTexture = nullptr;
		}
	}
}