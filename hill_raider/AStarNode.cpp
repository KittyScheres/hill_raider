#include "AStarNode.h"

namespace HillRaider
{
	// --------------------------------------------------
	//
	// --------------------------------------------------
	AStarNode::AStarNode(int iX, int iY, bool iWalkable, int iGridX, int iGridY)
	{
		x = iX;
		y = iY;
		walkable = iWalkable;
		gridX = iGridX;
		gridY = iGridY;
	}

	// --------------------------------------------------
	//
	// --------------------------------------------------
	void AStarNode::RenderNode(Tmpl8::Surface* screen)
	{
		for (int iY = 0; iY < 64; iY++) {
			if ((y + iY) < screen->GetHeight()) {
				for (int iX = 0; iX < 64; iX++) {
					if ((x + iX) < screen->GetWidth()) {
						screen->GetBuffer()[(x + iX) + ((y + iY) * screen->GetWidth())] = debugColor;
					}
				}
			}
		}
	}

	// --------------------------------------------------
	//
	// --------------------------------------------------
	void AStarNode::SetWalkable(bool iWalkable)
	{
		walkable = iWalkable;
	}

	// --------------------------------------------------
	//
	// --------------------------------------------------
	void AStarNode::SetDebugColor(int iDebugColor)
	{
		debugColor = iDebugColor;
	}

	// --------------------------------------------------
	//
	// --------------------------------------------------
	void AStarNode::SetGCost(int g)
	{
		gCost = g;
	}

	// --------------------------------------------------
	//
	// --------------------------------------------------
	void AStarNode::SetHCost(int h)
	{
		hCost = h;
	}

	// --------------------------------------------------
	//
	// --------------------------------------------------
	void AStarNode::SetParent(AStarNode* iParent)
	{
		parent = iParent;
	}

	// --------------------------------------------------
	//
	// --------------------------------------------------
	std::vector<int>  AStarNode::GetPosition()
	{
		return std::vector<int>{ x, y };
	}

	// --------------------------------------------------
	//
	// --------------------------------------------------
	bool AStarNode::GetWalkable()
	{
		return walkable;
	}

	// --------------------------------------------------
	//
	// --------------------------------------------------
	int AStarNode::GetGridX()
	{
		return gridX;
	}

	// --------------------------------------------------
	//
	// --------------------------------------------------
	int AStarNode::GetGridY()
	{
		return gridY;
	}

	// --------------------------------------------------
	//
	// --------------------------------------------------
	int AStarNode::GetGCost()
	{
		return gCost;
	}

	// --------------------------------------------------
	//
	// --------------------------------------------------
	int AStarNode::GetHCost()
	{
		return hCost;
	}

	// --------------------------------------------------
	//
	// --------------------------------------------------
	int AStarNode::GetFCost()
	{
		return gCost + hCost;
	}

	// --------------------------------------------------
	//
	// --------------------------------------------------
	AStarNode* AStarNode::GetParent()
	{
		return parent;
	}
}