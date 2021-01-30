#include "FoodPointsPickup.h"

namespace HillRaider
{
	// --------------------------------------------------
	// This constructor is used to setup the properties
	// for a food points pickup entity.
	// --------------------------------------------------
	FoodPointsPickup::FoodPointsPickup(short iPoints, int iX, int iY): Entity(iX, iY, 44, 38)
	{
		foodPickupTexture = new Image("assets/entities/food_pickup.png", 0, 0);
		foodPickupTexture->SetPosition(x - (foodPickupTexture->GetWidth() / 2), y - (foodPickupTexture->GetHeight() / 2));
		points = iPoints;
	}

	// --------------------------------------------------
	// This method is used to draw the food poins pickup
	// on to the screen.
	// --------------------------------------------------
	void FoodPointsPickup::Render(Tmpl8::Surface* screen)
	{
		foodPickupTexture->DrawImage(screen);
	}

	// --------------------------------------------------
	// This method is used to set the room callback for 
	// a food points pickup entity.
	// --------------------------------------------------
	void FoodPointsPickup::SetRoomCallback(RoomCallback* iCallback)
	{
		callback = iCallback;
	}

	// --------------------------------------------------
	// This method is used to set the position of a food
	// points pickup entity.
	// --------------------------------------------------
	void FoodPointsPickup::SetPosition(int iX, int iY)
	{
		x = iX;
		y = iY;
		hitbox->SetPosition(x, y);
		foodPickupTexture->SetPosition(x - (foodPickupTexture->GetWidth() / 2), y - (foodPickupTexture->GetHeight() / 2));
	}

	// --------------------------------------------------
	// This method is used to remove a food points pickup
	// entity from a room.
	// --------------------------------------------------
	void FoodPointsPickup::RemoveFoodPointsPickup()
	{
		callback->RemoveEntity(this);
	}

	// --------------------------------------------------
	// This method is used to get the points value of a 
	// food points pickup entity.
	// --------------------------------------------------
	short FoodPointsPickup::GetPoints()
	{
		return points;
	}

	// --------------------------------------------------
	// This deconstructor is used to safely free the 
	// memory of the properties of a food points pickup
	// entity.
	// --------------------------------------------------
	FoodPointsPickup::~FoodPointsPickup()
	{
		if (foodPickupTexture != nullptr) {
			delete foodPickupTexture;
			foodPickupTexture = nullptr;
		}
	}
}