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
		std::vector<std::vector<AStarNode*>> nodeGrid;
	public:
		AStarGrid(TileMap* tileMap);
		void DebugRender(Tmpl8::Surface* screen);
		std::vector<std::vector<AStarNode*>> GetNodeGrid();
		AStarNode* GetNodeFromGrid(int x, int y);
		~AStarGrid();
	};
}