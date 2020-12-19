#pragma once

#include "AStarGrid.h"
#include "Entity.h"
#include "TileMap.h"

namespace HillRaider
{
	class AStar
	{
	private:
		static AStar* instance;
		AStarGrid* nodeMap = nullptr;
		Entity* endGoal = nullptr;
		std::vector<std::vector<int>> movementDirections;
	public:
		static AStar* GetIntance();
		static void DestroyInstance();
		void SetNodeMap(TileMap* tileMap);
		void SetEndGoal(Entity* entity);
		void DebugRenderNodeMap(Tmpl8::Surface* screen);
		std::vector<std::vector<int>> FindPath(std::vector<int> startPosition);
	private:
		AStar();
		~AStar();
	};
}