#pragma once

#include "surface.h"
#include <vector>

namespace HillRaider
{
	// --------------------------------------------------
	// This class is used to create nodes for the node grid
	// which is used for the a* pathfinding implementation.
	// This class is one of three classes which have been created
	// with the help of a tutorial on the implementation
	// of the a* path finding algorithm.
	// --------------------------------------------------
	class AStarNode
	{
	private:
		bool m_Walkable = true;
		int m_GridX = 0;
		int m_GridY = 0;
		int m_X = 0;
		int m_Y = 0;
		int m_GCost = 0;
		int m_HCost = 0;
		AStarNode* m_Parent = nullptr;

	public:
		AStarNode(int x, int y, bool walkable, int gridX, int gridY);
		void SetWalkable(bool walkable);
		void SetGCost(int gCost);
		void SetHCost(int hCost);
		void SetParent(AStarNode* parent);
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