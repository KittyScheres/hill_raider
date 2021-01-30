#pragma once

#include "Image.h"
#include "RoomCallback.h"
#include "Entity.h"

namespace HillRaider
{
	// --------------------------------------------------
	// This class is used to create and keep track of
	// food points pickup entities for the game.
	// --------------------------------------------------
	class FoodPointsPickup: public Entity
	{
	private:
		RoomCallback* callback = nullptr;
		Image* foodPickupTexture = nullptr;
		short points = 0;

	public:
		FoodPointsPickup(short iPoints, int iX, int iY);
		void Render(Tmpl8::Surface* screen);
		void SetRoomCallback(RoomCallback* iCallback);
		void SetPosition(int iX, int iY);
		void RemoveFoodPointsPickup();
		short GetPoints();
		~FoodPointsPickup();
	};
}