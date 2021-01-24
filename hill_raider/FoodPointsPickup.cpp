#include "FoodPointsPickup.h"

namespace HillRaider
{
	// --------------------------------------------------
	//
	// --------------------------------------------------
	FoodPointsPickup::FoodPointsPickup(short iPoints, int iX, int iY): Entity(iX, iY, 44, 38)
	{
		foodPickupTexture = new Image("assets/entities/food_pickup.png", 0, 0);
		foodPickupTexture->SetPosition(x - (foodPickupTexture->GetWidth() / 2), y - (foodPickupTexture->GetHeight() / 2));
		points = iPoints;
	}

	// --------------------------------------------------
	//
	// --------------------------------------------------
	void FoodPointsPickup::Render(Tmpl8::Surface* screen)
	{
		foodPickupTexture->DrawImage(screen);
	}

	// --------------------------------------------------
	//
	// --------------------------------------------------
	void FoodPointsPickup::SetRoomCallback(RoomCallback* iCallback)
	{
		callback = iCallback;
	}

	// --------------------------------------------------
	//
	// --------------------------------------------------
	void FoodPointsPickup::SetPosition(int iX, int iY)
	{
		x = iX;
		y = iY;
		hitbox->SetPosition(x, y);
		foodPickupTexture->SetPosition(x - (foodPickupTexture->GetWidth() / 2), y - (foodPickupTexture->GetHeight() / 2));
	}

	// --------------------------------------------------
	//
	// --------------------------------------------------
	void FoodPointsPickup::RemoveFoodPointsPickup()
	{
		callback->RemoveEntity(this);
	}

	// --------------------------------------------------
	//
	// --------------------------------------------------
	short FoodPointsPickup::GetPoints()
	{
		return points;
	}

	// --------------------------------------------------
	//
	// --------------------------------------------------
	FoodPointsPickup::~FoodPointsPickup()
	{
		if (foodPickupTexture != nullptr) {
			delete foodPickupTexture;
			foodPickupTexture = nullptr;
		}
	}
}