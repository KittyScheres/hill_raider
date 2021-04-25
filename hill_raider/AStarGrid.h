#pragma once

#include "surface.h"
#include "tileMap.h"
#include "aStarNode.h"
#include <vector>

namespace HillRaider
{
	// --------------------------------------------------
	// This class is used to create node grids which are used
	// for the a* pathfinding implementation. This class
	// is one of three classes which have been created with 
	// the help of a tutorial on the implementation of 
	// the a* path finding algorithm.
	// --------------------------------------------------
	class AStarGrid
	{
	private:
		TileMap* m_Map = nullptr;
		std::vector<std::vector<AStarNode*>> m_NodeGrid;

	public:
		AStarGrid(TileMap* tileMap);
		void ResetWalkableNodes();
		std::vector<std::vector<AStarNode*>> GetNodeGrid();
		AStarNode* GetNodeFromGrid(int x, int y);
		std::vector<AStarNode*> GetNeighbouringNodes(AStarNode* node);
		~AStarGrid();
	};
}