#include "AStarNode.h"

namespace HillRaider
{
	// --------------------------------------------------
	// This constructor is used to setup the properties
	// for the node class.
	// --------------------------------------------------
	AStarNode::AStarNode(int x, int y, bool walkable, int gridX, int gridY)
	{
		m_X = x;
		m_Y = y;
		m_Walkable = walkable;
		m_GridX = gridX;
		m_GridY = gridY;
	}

	// --------------------------------------------------
	// This method is used to set wether this node can be
	// walked on or not.
	// --------------------------------------------------
	void AStarNode::SetWalkable(bool walkable)
	{
		m_Walkable = walkable;
	}

	// --------------------------------------------------
	// This method is used to set the g cost of a node.
	// The g cost of a node is the distance between the
	// staring node and the currently selected node.
	// --------------------------------------------------
	void AStarNode::SetGCost(int gCost)
	{
		m_GCost = gCost;
	}

	// --------------------------------------------------
	// This method is used to set the h cost of a node.
	// The h cost of a node is the distance between the
	// end node and the currently selected node.
	// --------------------------------------------------
	void AStarNode::SetHCost(int hCost)
	{
		m_HCost = hCost;
	}

	// --------------------------------------------------
	// This method is used to set the parent for a node.
	// --------------------------------------------------
	void AStarNode::SetParent(AStarNode* parent)
	{
		m_Parent = parent;
	}

	// --------------------------------------------------
	// This method is used to get the position of a node.
	// --------------------------------------------------
	std::vector<int>  AStarNode::GetPosition()
	{
		return std::vector<int>{ m_X, m_Y };
	}

	// --------------------------------------------------
	// This method is used to get the walkable state of a
	// node.
	// --------------------------------------------------
	bool AStarNode::GetWalkable()
	{
		return m_Walkable;
	}

	// --------------------------------------------------
	// This method is used to get the x position of the node
	// on the node grid.
	// --------------------------------------------------
	int AStarNode::GetGridX()
	{
		return m_GridX;
	}

	// --------------------------------------------------
	// This method is used to get the y position of the node
	// on the node grid.
	// --------------------------------------------------
	int AStarNode::GetGridY()
	{
		return m_GridY;
	}

	// --------------------------------------------------
	// This method is used to get the g cost of a node.
	// The g cost of a node is the distance between the
	// staring node and the currently selected node.
	// --------------------------------------------------
	int AStarNode::GetGCost()
	{
		return m_GCost;
	}

	// --------------------------------------------------
	// This method is used to get the h cost of a node.
	// The h cost of a node is the distance between the
	// end node and the currently selected node.
	// --------------------------------------------------
	int AStarNode::GetHCost()
	{
		return m_HCost;
	}

	// --------------------------------------------------
	// This method is used to get the f cost of a node.
	// The f cost of a node is the combined cost of the
	// g and the h cost.
	// --------------------------------------------------
	int AStarNode::GetFCost()
	{
		return m_GCost + m_HCost;
	}

	// --------------------------------------------------
	// This method is used to get the parent node of a node.
	// --------------------------------------------------
	AStarNode* AStarNode::GetParent()
	{
		return m_Parent;
	}
}