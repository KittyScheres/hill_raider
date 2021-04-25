#include "aStarGrid.h"

namespace HillRaider
{
	// --------------------------------------------------
	// This constuctor is used to setup a node grid for the
	// the grid class.
	// --------------------------------------------------
	AStarGrid::AStarGrid(TileMap* tileMap)
	{
		m_Map = tileMap;

		for (int y = 0; y < TileMap::c_s_TileMapHeight; y++) {
			std::vector<AStarNode*> newRow;
			for (int x = 0; x < TileMap::c_s_TileMapWidth; x++) {
				int xPos = x * tileMap->GetTileWidth();
				int yPos = y * tileMap->GetTileHeight();

				if (tileMap->GetCollision(xPos, yPos) != ' ') {
					AStarNode* newNode = new AStarNode(xPos, yPos, false, x, y);
					newRow.push_back(newNode);
				}
				else {
					newRow.push_back(new AStarNode(xPos, yPos, true, x, y));
				}
			}
			m_NodeGrid.push_back(newRow);
		}
	}

	// --------------------------------------------------
	// This method is used to reset the walkable state
	// for all of the nodes on the node map.
	// --------------------------------------------------
	void AStarGrid::ResetWalkableNodes()
	{
		for (std::vector<AStarNode*> nodeLine : m_NodeGrid) {
			for (AStarNode* node : nodeLine) {
				node->SetWalkable(m_Map->GetCollision(node->GetPosition()[0], node->GetPosition()[1]) == ' ');
			}
		}
	}

	// --------------------------------------------------
	// This method is used to get the node grid.
	// --------------------------------------------------
	std::vector<std::vector<AStarNode*>> AStarGrid::GetNodeGrid()
	{
		return m_NodeGrid;
	}

	// --------------------------------------------------
	// This method is used to get a spesific node from the
	// node grid.
	// --------------------------------------------------
	AStarNode* AStarGrid::GetNodeFromGrid(int x, int y)
	{
		return m_NodeGrid[y / 64][x / 64];
	}

	// --------------------------------------------------
	// This method is used to get all of the neighbouring
	// nodes of a spesific node.
	// --------------------------------------------------
	std::vector<AStarNode*> AStarGrid::GetNeighbouringNodes(AStarNode* node)
	{
		std::vector<AStarNode*> nodeList;

		for (int offset = -1; offset <= 1; offset += 2) {
			if ((node->GetGridY() + offset) < (int)m_NodeGrid.size() && (node->GetGridY() + offset) >= 0) {
				nodeList.push_back(m_NodeGrid[node->GetGridY() + offset][node->GetGridX()]);
			}

			if ((node->GetGridX() + offset) < (int)m_NodeGrid[0].size() && (node->GetGridX() + offset) >= 0) {
				nodeList.push_back(m_NodeGrid[node->GetGridY()][node->GetGridX() + offset]);
			}
		}

		return nodeList;
	}

	// --------------------------------------------------
	// This method is used to safely free the memory of
	// the node grid.
	// --------------------------------------------------
	AStarGrid::~AStarGrid()
	{
		for (std::vector<AStarNode*> nodeMapRow : m_NodeGrid) {
			for (AStarNode* node : nodeMapRow) {
				delete node;
				node = nullptr;
			}
		}

		m_NodeGrid.clear();
	}
}