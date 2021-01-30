#pragma once

#include "surface.h"
#include "TileMap.h"
#include "AStarNode.h"
#include <vector>

namespace HillRaider
{
	// --------------------------------------------------
	// This class is used to create node grids which are used
	// for the a* path finding implementation. This class
	// is one of 3 classes which have been created with 
	// the help of a tutorial for the implementation of 
	// the a* path finding algorithm.
	// --------------------------------------------------
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