#pragma once

#include "surface.h"

namespace HillRaider
{
	class AStarNode
	{
	public:
		enum class WalkableNode
		{
			WALKABLE = 0,
			NOT_WALKABLE
		};

	private:
		WalkableNode walkable = WalkableNode::WALKABLE;
		int gridX = 0;
		int gridY = 0;
		int x = 0;
		int y = 0;
		int debugColor = (127 << 16) + (127 << 8) + 127;
		int gCost = 0;
		int hCost = 0;
		AStarNode* parent = nullptr;

	public:
		AStarNode(int iX, int iY, WalkableNode iWalkable, int iGridX, int iGridY);
		void RenderNode(Tmpl8::Surface* screen);
		void SetWalkable(WalkableNode iWalkable);
		void SetDebugColor(int iDebugColor);
		void SetGCost(int g);
		void SetHCost(int h);
		void SetParent(AStarNode* iParent);
		WalkableNode GetWalkable();
		int GetGridX();
		int GetGridY();
		int GetGCost();
		int GetHCost();
		int GetFCost();
		AStarNode* GetParent();
	};
}