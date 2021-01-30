#include "AStarGrid.h"

namespace HillRaider
{
	// --------------------------------------------------
	// This constuctor is used to setup a node grid for the
	// the grid class.
	// --------------------------------------------------
	AStarGrid::AStarGrid(TileMap* tileMap)
	{
		map = tileMap;

		for (int y = 0; y < TileMap::TILE_MAP_HEIGHT; y++) {
			std::vector<AStarNode*> newRow;
			for (int x = 0; x < TileMap::TILE_MAP_WIDHT; x++) {
				int xPos = x * tileMap->GetTileWidth();
				int yPos = y * tileMap->GetTileHeight();

				if (tileMap->GetCollision(xPos, yPos) != ' ') {
					AStarNode* newNode = new AStarNode(xPos, yPos, false, x, y);
					newNode->SetDebugColor(255 << 16);
					newRow.push_back(newNode);
				}
				else {
					newRow.push_back(new AStarNode(xPos, yPos, true, x, y));
				}
			}
			nodeGrid.push_back(newRow);
		}
	}

	// --------------------------------------------------
	// This method is used to reset the walkable state
	// for all of the nodes on the node map.
	// --------------------------------------------------
	void AStarGrid::ResetWalkableNodes()
	{
		for (std::vector<AStarNode*> nodeLine : nodeGrid) {
			for (AStarNode* node : nodeLine) {
				node->SetWalkable(map->GetCollision(node->GetPosition()[0], node->GetPosition()[1]) == ' ');
			}
		}
	}

	// --------------------------------------------------
	// This method is used to draw all of the nodes in the
	// node map on to the screen. This mehtod will only be
	// used for debug purposes.
	// --------------------------------------------------
	void AStarGrid::DebugRender(Tmpl8::Surface* screen)
	{
		for (std::vector<AStarNode*> nodeRow : nodeGrid) {
			for (AStarNode* node : nodeRow) {
				node->RenderNode(screen);
				if (node->GetWalkable()) {
					node->SetDebugColor((127 << 16) + (127 << 8) + 127);
				}
			}
		}
	}

	// --------------------------------------------------
	// This method is used to get the node grid.
	// --------------------------------------------------
	std::vector<std::vector<AStarNode*>> AStarGrid::GetNodeGrid()
	{
		return nodeGrid;
	}

	// --------------------------------------------------
	// This method is used to get a spesific node from the
	// node grid.
	// --------------------------------------------------
	AStarNode* AStarGrid::GetNodeFromGrid(int x, int y)
	{
		return nodeGrid[y / 64][x / 64];
	}

	// --------------------------------------------------
	// This method is used to get all of the neighbouring
	// nodes of a spesific node.
	// --------------------------------------------------
	std::vector<AStarNode*> AStarGrid::GetNeighbouringNodes(AStarNode* node)
	{
		std::vector<AStarNode*> nodeList;

		for (int offset = -1; offset <= 1; offset += 2) {
			if ((node->GetGridY() + offset) < (int)nodeGrid.size() && (node->GetGridY() + offset) >= 0) {
				nodeList.push_back(nodeGrid[node->GetGridY() + offset][node->GetGridX()]);
			}

			if ((node->GetGridX() + offset) < (int)nodeGrid[0].size() && (node->GetGridX() + offset) >= 0) {
				nodeList.push_back(nodeGrid[node->GetGridY()][node->GetGridX() + offset]);
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
		for (std::vector<AStarNode*> nodeMapRow : nodeGrid) {
			for (AStarNode* node : nodeMapRow) {
				delete node;
				node = nullptr;
			}
		}

		nodeGrid.clear();
	}
}