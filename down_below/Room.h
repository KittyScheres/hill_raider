#pragma once

#include "Player.h"
#include "TileMap.h"
#include "RagDoll.h"

namespace DownBelow
{
	class Room
	{
	private:
		TileMap* tileMap = nullptr;
		RagDoll* entity = nullptr;

	public:
		Room(TileMap* iTilemap);
		void Update(float deltaTime);
		void Render(Tmpl8::Surface* screen);
		void LateUpdate(Player* player);
		TileMap* GetTileMap();
		~Room();
	};
}