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
		RoomCallback* m_RoomCallback = nullptr;
		Image* m_FoodPickupTexture = nullptr;
		short m_Points = 0;

	public:
		FoodPointsPickup(short points, int x, int y);
		void Render(Tmpl8::Surface* screen);
		void SetRoomCallback(RoomCallback* callback);
		void SetPosition(int x, int y);
		void RemoveFoodPointsPickup();
		short GetPoints();
		~FoodPointsPickup();
	};
}