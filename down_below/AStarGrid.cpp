#include "AStarGrid.h"

namespace HillRaider
{
	// --------------------------------------------------
	//
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
	//
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
	//
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
	//
	// --------------------------------------------------
	std::vector<std::vector<AStarNode*>> AStarGrid::GetNodeGrid()
	{
		return nodeGrid;
	}

	// --------------------------------------------------
	//
	// --------------------------------------------------
	AStarNode* AStarGrid::GetNodeFromGrid(int x, int y)
	{
		return nodeGrid[y / 64][x / 64];
	}

	// --------------------------------------------------
	//
	// --------------------------------------------------
	std::vector<AStarNode*> AStarGrid::GetNeighbouringNodes(AStarNode* node)
	{
		std::vector<AStarNode*> nodeList;

		for (int offset = -1; offset <= 1; offset += 2) {
			if ((node->GetGridY() + offset) < nodeGrid.size() && (node->GetGridY() + offset) >= 0) {
				nodeList.push_back(nodeGrid[node->GetGridY() + offset][node->GetGridX()]);
			}

			if ((node->GetGridX() + offset) < nodeGrid[0].size() && (node->GetGridX() + offset) >= 0) {
				nodeList.push_back(nodeGrid[node->GetGridY()][node->GetGridX() + offset]);
			}
		}

		return nodeList;
	}

	// --------------------------------------------------
	//
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