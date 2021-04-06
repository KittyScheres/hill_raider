#pragma once

#include <vector>
#include "surface.h"

namespace HillRaider
{
	// --------------------------------------------------
	// This class is used to create nodes for the node grid
	// which is used for the a* path finding implementation.
	// This class is one of 3 classes which have been created
	// with the help of a tutorial for the implementation
	// of the a* path finding algorithm.
	// --------------------------------------------------
	class AStarNode
	{
	private:
		bool walkable = true;
		int gridX = 0;
		int gridY = 0;
		int x = 0;
		int y = 0;
		int gCost = 0;
		int hCost = 0;
		AStarNode* parent = nullptr;

	public:
		AStarNode(int iX, int iY, bool iWalkable, int iGridX, int iGridY);
		void SetWalkable(bool iWalkable);
		void SetGCost(int g);
		void SetHCost(int h);
		void SetParent(AStarNode* iParent);
		std::vector<int> GetPosition();
		bool GetWalkable();
		int GetGridX();
		int GetGridY();
		int GetGCost();
		int GetHCost();
		int GetFCost();
		AStarNode* GetParent();
	};
}