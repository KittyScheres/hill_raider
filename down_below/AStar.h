#pragma once

#include "AStarGrid.h"
#include "Entity.h"
#include "TileMap.h"
#include <list>
#include <unordered_set>
#include <math.h>

namespace HillRaider
{
	class AStar
	{
	private:
		static AStar* instance;
		AStarGrid* nodeMap = nullptr;
		Entity* endGoal = nullptr;
	public:
		static AStar* GetIntance();
		static void DestroyInstance();
		void SetNodeMap(TileMap* tileMap);
		void SetEndGoal(Entity* entity);
		void DebugRenderNodeMap(Tmpl8::Surface* screen);
		std::vector<AStarNode*> FindPath(std::vector<int> startPosition);
		std::vector<AStarNode*> RetracePath(AStarNode* startNode, AStarNode* endNode);
		int GetDistanceBetween(AStarNode* node1, AStarNode* node2);
	private:
		AStar();
		~AStar();
	};
}