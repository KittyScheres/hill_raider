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
	std::vector<AStarNode*> AStar::FindPath(std::vector<int> startPosition)
	{
		std::vector<AStarNode*> path;

		AStarNode* startNode = nodeMap->GetNodeFromGrid(startPosition[0], startPosition[1]);
		AStarNode* endNode = nodeMap->GetNodeFromGrid(endGoal->GetPosition()[0], endGoal->GetPosition()[1]);

		std::list<AStarNode*> openSet;
		std::unordered_set<AStarNode*> closedSet;
		openSet.push_back(startNode);

		while (openSet.size() > 0) {
			// check for node clossesd to endNode
			AStarNode* currentNode = *openSet.begin();
			for (std::list<AStarNode*>::iterator i = openSet.begin(); i != openSet.end(); i++) {
				if ((*i)->GetFCost() < currentNode->GetFCost() || ((*i)->GetFCost() == currentNode->GetFCost() && (*i)->GetHCost() < currentNode->GetHCost())) {
					currentNode = (*i);
				}
			}

			// add current node to closed set
			openSet.remove(currentNode);
			closedSet.insert(currentNode);

			// check if endNode has been reached
			if (currentNode == endNode) {
				path = RetracePath(startNode, endNode);
				break;
			}

			// add available neighbour nodes to open set
			for (AStarNode* neighbour : nodeMap->GetNeighbouringNodes(currentNode)) {
				if (neighbour->GetWalkable() == AStarNode::WalkableNode::NOT_WALKABLE || closedSet.find(neighbour) != closedSet.end()) {
					continue;
				}

				int newPathToNeighbour = currentNode->GetGCost() + GetDistanceBetween(currentNode, neighbour);
				
				if (newPathToNeighbour < neighbour->GetGCost() || std::find(openSet.begin(), openSet.end(), neighbour) == openSet.end()) {
					neighbour->SetGCost(newPathToNeighbour);
					neighbour->SetHCost(GetDistanceBetween(currentNode, endNode));
					neighbour->SetParent(currentNode);

					if (std::find(openSet.begin(), openSet.end(), neighbour) == openSet.end()) {
						openSet.push_back(neighbour);
					}
				}
			}
		}

		return path;
	}
	
	// --------------------------------------------------
	//
	// --------------------------------------------------
	std::vector<AStarNode*> AStar::RetracePath(AStarNode* startNode, AStarNode* endNode)
	{
		std::vector<AStarNode*> path;
		AStarNode* currentNode = endNode;
		currentNode->SetDebugColor(0);

		while (currentNode != startNode)
		{
			path.push_back(currentNode);
			currentNode = currentNode->GetParent();
			currentNode->SetDebugColor(0);
		}

		path.push_back(currentNode);
		std::reverse(path.begin(), path.end());
		
		return path;
	}

	// --------------------------------------------------
	//
	// --------------------------------------------------
	int AStar::GetDistanceBetween(AStarNode* node1, AStarNode* node2)
	{
		int distanceX = std::abs(node1->GetGridX() - node2->GetGridX());
		int distanceY = std::abs(node1->GetGridY() - node2->GetGridY());

		return (10 * distanceX) + (10 * distanceY);
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