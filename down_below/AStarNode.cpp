#include "AStarNode.h"

namespace HillRaider
{
	// --------------------------------------------------
	//
	// --------------------------------------------------
	AStarNode::AStarNode(int iX, int iY, WalkableNode iWalkable)
	{
		x = iX;
		y = iY;
		walkable = iWalkable;
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
	void AStarNode::SetWalkable(WalkableNode iWalkable)
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
	AStarNode::WalkableNode AStarNode::GetWalkable()
	{
		return walkable;
	}
}