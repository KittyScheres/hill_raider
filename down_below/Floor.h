#pragma once

#include "Player.h"
#include "Room.h"
#include "AStar.h"

namespace DownBelow
{
	class Floor
	{
	public:
		enum class MoveDirection {UP = 0, RIGHT, DOWN, LEFT};

	private:
		Room* floorMap[3][3];
		int currentRoom[2];

	public:
		Floor();
		void Update(float deltaTime);
		void Render(Tmpl8::Surface* screen);
		void LateUpdate(Player* player);
		Room* GetCurrentRoom();
		void MoveToNextRoom(MoveDirection direction);
		~Floor();
	};
}