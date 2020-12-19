#include "AStar.h"

namespace HillRaider
{
	AStar* AStar::instance = nullptr;

	// --------------------------------------------------
	//
	// --------------------------------------------------
	AStar* AStar::GetIntance()
	{
		if (instance == nullptr) {
			instance = new AStar();
		}

		return instance;
	}

	// --------------------------------------------------
	//
	// --------------------------------------------------
	void AStar::DestroyInstance()
	{
		delete instance;
		instance = nullptr;
	}

	// --------------------------------------------------
	//
	// --------------------------------------------------
	void AStar::SetNodeMap(TileMap* tileMap) {
		if (nodeMap != nullptr) {
			delete nodeMap;
		}

		nodeMap = new AStarGrid(tileMap);
	}

	// --------------------------------------------------
	//
	// --------------------------------------------------
	void AStar::SetEndGoal(Entity* entity)
	{
		endGoal = entity;
	}

	// --------------------------------------------------
	//
	// --------------------------------------------------
	void AStar::DebugRenderNodeMap(Tmpl8::Surface* screen)
	{
		if (nodeMap != nullptr) {
			nodeMap->DebugRender(screen);
		}
	}

	// --------------------------------------------------
	//
	// --------------------------------------------------
	std::vector<std::vector<int>> AStar::FindPath(std::vector<int> startPosition)
	{
		std::vector<std::vector<std::vector<int>>> paths;
		paths.push_back(std::vector<std::vector<int>> {startPosition});
		nodeMap->GetNodeFromGrid(startPosition[0], startPosition[1])->SetDebugColor(0);
		nodeMap->GetNodeFromGrid(endGoal->GetPosition()[0], endGoal->GetPosition()[1])->SetDebugColor(0);
		return paths[0];
	}

	// --------------------------------------------------
	//
	// --------------------------------------------------
	AStar::AStar() {}

	// --------------------------------------------------
	//
	// --------------------------------------------------
	AStar::~AStar() {
		if (nodeMap != nullptr) {
			delete nodeMap;
			nodeMap = nullptr;
		}
	}
}