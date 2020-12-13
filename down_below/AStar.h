#pragma once

#include "Entity.h"
#include "TileMap.h"

namespace DownBelow
{
	class AStar
	{
	private:
		static AStar* instance;
		Entity* endGoal = nullptr;
		TileMap* currentTileMap = nullptr;
		std::vector<std::vector<int>> movementDirections;
	public:
		static AStar* GetIntance();
		static void DestroyInstance();
		void SetEndGoal(Entity* entity);
		void SetTileMap(TileMap* tileMap);
		std::vector<std::vector<int>> FindPath(std::vector<int> startPosition);
	private:
		AStar();
		~AStar();
		int GetValue(std::vector<int> comparePos, std::vector<int> newPos);
		int GetVectorIndex(std::vector<int>, int value);
		bool CheckForRepeat(std::vector<std::vector<std::vector<int>>> paths, std::vector<int> newPos);
	};
}