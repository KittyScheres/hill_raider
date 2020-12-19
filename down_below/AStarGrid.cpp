#include "AStarGrid.h"

namespace HillRaider
{
	// --------------------------------------------------
	//
	// --------------------------------------------------
	AStarGrid::AStarGrid(TileMap* tileMap)
	{
		for (int y = 0; y < TileMap::TILE_MAP_HEIGHT; y++) {
			std::vector<AStarNode*> newRow;
			for (int x = 0; x < TileMap::TILE_MAP_WIDHT; x++) {
				int xPos = x * tileMap->GetTileWidth();
				int yPos = y * tileMap->GetTileHeight();

				if (tileMap->GetCollision(xPos, yPos) != ' ') {
					AStarNode* newNode = new AStarNode(xPos, yPos, AStarNode::WalkableNode::NOT_WALKABLE);
					newNode->SetDebugColor(255 << 16);
					newRow.push_back(newNode);
				}
				else {
					newRow.push_back(new AStarNode(xPos, yPos, AStarNode::WalkableNode::WALKABLE));
				}
			}
			nodeGrid.push_back(newRow);
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
				if (node->GetWalkable() == AStarNode::WalkableNode::WALKABLE) {
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