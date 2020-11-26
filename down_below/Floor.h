#pragma once

#include "Room.h"

namespace DownBelow
{
	class Floor
	{
	public:
		enum MoveDirection {UP = 0, RIGHT, DOWN, LEFT};

	private:
		Room* floorMap[3][3];
		int currentRoom[2];

	public:
		Floor();
		void Render(Tmpl8::Surface* screen);
		Room* GetCurrentRoom();
		void MoveToNextRoom(MoveDirection direction);
		~Floor();
	};
}