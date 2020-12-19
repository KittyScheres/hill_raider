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
		int x = 0;
		int y = 0;
		int debugColor = (127 << 16) + (127 << 8) + 127;
	public:
		AStarNode(int iX, int iY, WalkableNode iWalkable);
		void RenderNode(Tmpl8::Surface* screen);
		void SetWalkable(WalkableNode iWalkable);
		void SetDebugColor(int iDebugColor);
		WalkableNode GetWalkable();
	};
}