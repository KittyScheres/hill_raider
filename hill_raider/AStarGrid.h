#pragma once

#include "surface.h"
#include "TileMap.h"
#include "AStarNode.h"
#include <vector>

namespace HillRaider
{
	class AStarGrid
	{
	private:
		TileMap* map = nullptr;
		std::vector<std::vector<AStarNode*>> nodeGrid;

	public:
		AStarGrid(TileMap* tileMap);
		void ResetWalkableNodes();
		void DebugRender(Tmpl8::Surface* screen);
		std::vector<std::vector<AStarNode*>> GetNodeGrid();
		AStarNode* GetNodeFromGrid(int x, int y);
		std::vector<AStarNode*> GetNeighbouringNodes(AStarNode* node);
		~AStarGrid();
	};
}