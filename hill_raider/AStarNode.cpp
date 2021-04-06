#include "AStarNode.h"

namespace HillRaider
{
	// --------------------------------------------------
	// This constructor is used to setup the properties
	// for the node class.
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
	// This method is used to set wether this node can be
	// walked on or not.
	// --------------------------------------------------
	void AStarNode::SetWalkable(bool iWalkable)
	{
		walkable = iWalkable;
	}

	// --------------------------------------------------
	// This method is used to set the g cost of a node.
	// The g cost of a node is the distance between the
	// staring node and the currently selected node.
	// --------------------------------------------------
	void AStarNode::SetGCost(int g)
	{
		gCost = g;
	}

	// --------------------------------------------------
	// This method is used to set the h cost of a node.
	// The h cost of a node is the distance between the
	// end node and the currently selected node.
	// --------------------------------------------------
	void AStarNode::SetHCost(int h)
	{
		hCost = h;
	}

	// --------------------------------------------------
	// This method is used to set the parent for a node.
	// --------------------------------------------------
	void AStarNode::SetParent(AStarNode* iParent)
	{
		parent = iParent;
	}

	// --------------------------------------------------
	// This method is used to get the position of a node.
	// --------------------------------------------------
	std::vector<int>  AStarNode::GetPosition()
	{
		return std::vector<int>{ x, y };
	}

	// --------------------------------------------------
	// This method is used to get the walkable state of a
	// node.
	// --------------------------------------------------
	bool AStarNode::GetWalkable()
	{
		return walkable;
	}

	// --------------------------------------------------
	// This method is used to get the x position of the node
	// on the node grid.
	// --------------------------------------------------
	int AStarNode::GetGridX()
	{
		return gridX;
	}

	// --------------------------------------------------
	// This method is used to get the y position of the node
	// on the node grid.
	// --------------------------------------------------
	int AStarNode::GetGridY()
	{
		return gridY;
	}

	// --------------------------------------------------
	// This method is used to get the g cost of a node.
	// The g cost of a node is the distance between the
	// staring node and the currently selected node.
	// --------------------------------------------------
	int AStarNode::GetGCost()
	{
		return gCost;
	}

	// --------------------------------------------------
	// This method is used to get the h cost of a node.
	// The h cost of a node is the distance between the
	// end node and the currently selected node.
	// --------------------------------------------------
	int AStarNode::GetHCost()
	{
		return hCost;
	}

	// --------------------------------------------------
	// This method is used to get the f cost of a node.
	// The f cost of a node is the combined cost of the
	// g and the h cost.
	// --------------------------------------------------
	int AStarNode::GetFCost()
	{
		return gCost + hCost;
	}

	// --------------------------------------------------
	// This method is used to get the parent node of a node.
	// --------------------------------------------------
	AStarNode* AStarNode::GetParent()
	{
		return parent;
	}
}