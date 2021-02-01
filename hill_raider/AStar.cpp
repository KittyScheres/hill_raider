#include "AStar.h"

namespace HillRaider
{
	AStar* AStar::instance = nullptr;

	// --------------------------------------------------
	// This method is used to get the instance of the 
	// AStar singleton class.
	// --------------------------------------------------
	AStar* AStar::GetIntance()
	{
		if (instance == nullptr) {
			instance = new AStar();
		}

		return instance;
	}

	// --------------------------------------------------
	// This method is used to destroy the instance of the 
	// AStar singleton class.
	// --------------------------------------------------
	void AStar::DestroyInstance()
	{
		delete instance;
		instance = nullptr;
	}

	// --------------------------------------------------
	// This method is used to set the node map for the
	// current room.
	// --------------------------------------------------
	void AStar::SetNodeMap(TileMap* tileMap) {
		if (nodeMap != nullptr) {
			delete nodeMap;
		}

		nodeMap = new AStarGrid(tileMap);
	}

	// --------------------------------------------------
	// This method is used to set a reference to the
	// enemy entity list of the current room.
	// --------------------------------------------------
	void AStar::SetEntitiesListReference(std::list<Entity*>* const entitiesList)
	{
		entitiesListReference = entitiesList;
	}

	// --------------------------------------------------
	// This method is used to set the end goal for the
	// path finding algorithm.
	// --------------------------------------------------
	void AStar::SetEndGoal(Entity* entity)
	{
		endGoal = entity;
	}

	// --------------------------------------------------
	// This method is used to draw the node map on to the
	// screen. This mehtod will only be used for debug 
	// purposes.
	// --------------------------------------------------
	void AStar::DebugRenderNodeMap(Tmpl8::Surface* screen)
	{
		if (nodeMap != nullptr) {
			nodeMap->DebugRender(screen);
		}
	}

	// --------------------------------------------------
	// This method is used to get a walkable path for the
	// enemy ai. This method has been created with the help
	// of a tutorial.
	// --------------------------------------------------
	std::vector<AStarNode*> AStar::FindPath(Entity* pathFindingEntity, std::vector<int> startPosition, std::vector<int> comparePosition, bool bypassCheck)
	{
		std::vector<AStarNode*> path;

		AStarNode* startNode = nodeMap->GetNodeFromGrid(startPosition[0], startPosition[1]);
		AStarNode* compareNode = nodeMap->GetNodeFromGrid(comparePosition[0], comparePosition[1]);
		AStarNode* endNode = nodeMap->GetNodeFromGrid(endGoal->GetPosition()[0], endGoal->GetPosition()[1]);

		std::list<AStarNode*> openSet;
		std::unordered_set<AStarNode*> closedSet;
		openSet.push_back(startNode);

		if ((startNode == compareNode) || bypassCheck) {
			SetNonWalkableEntityNodes(pathFindingEntity);
			startNode->SetWalkable(true);
			endNode->SetWalkable(true);

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
					if (!neighbour->GetWalkable() || closedSet.find(neighbour) != closedSet.end()) {
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

			nodeMap->ResetWalkableNodes();
		}
		
		return path;
	}

	// --------------------------------------------------
	// This method is used to the the nodes wich have been
	// occupied by an enemy ai to not walkable.
	// --------------------------------------------------
	void AStar::SetNonWalkableEntityNodes(Entity* pathFindingEntity)
	{
		AStarNode* entityNode = nullptr;
		AStarNode* infrontOfEntityNode = nullptr;

		for (Entity* entity : *entitiesListReference) {
			if (entity != pathFindingEntity) {
				switch (entity->GetDirection()) {
				case Entity::MovementDirection::UP:
					entityNode = nodeMap->GetNodeFromGrid(entity->GetHitbox()->GetPosition()[0], (entity->GetHitbox()->GetPosition()[1] + entity->GetHitbox()->GetHalfHeight()));
					infrontOfEntityNode = nodeMap->GetNodeGrid()[entityNode->GetGridY() - 1][entityNode->GetGridX()];
					break;

				case Entity::MovementDirection::RIGHT:
					entityNode = nodeMap->GetNodeFromGrid((entity->GetHitbox()->GetPosition()[0] - entity->GetHitbox()->GetHalfWidth()), (entity->GetHitbox()->GetPosition()[1]));
					infrontOfEntityNode = nodeMap->GetNodeGrid()[entityNode->GetGridY()][entityNode->GetGridX() + 1];
					break;

				case Entity::MovementDirection::DOWN:
					entityNode = nodeMap->GetNodeFromGrid(entity->GetHitbox()->GetPosition()[0], (entity->GetHitbox()->GetPosition()[1] - entity->GetHitbox()->GetHalfHeight()));
					infrontOfEntityNode = nodeMap->GetNodeGrid()[entityNode->GetGridY() + 1][entityNode->GetGridX()];
					break;

				case Entity::MovementDirection::LEFT:
					entityNode = nodeMap->GetNodeFromGrid((entity->GetHitbox()->GetPosition()[0] + entity->GetHitbox()->GetHalfWidth()), (entity->GetHitbox()->GetPosition()[1]));
					infrontOfEntityNode = nodeMap->GetNodeGrid()[entityNode->GetGridY()][entityNode->GetGridX() - 1];
					break;
				}

				entityNode->SetWalkable(false);
				entityNode->SetDebugColor(255 << 16);
				infrontOfEntityNode->SetWalkable(false);
				infrontOfEntityNode->SetDebugColor(255 << 16);
			}
		}
	}

	// --------------------------------------------------
	// This method is used to create a list with nodes that
	// creat a walkable path for the enemy ai.
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
	// This method is used to get the distance between two
	// nodes on the node map.
	// --------------------------------------------------
	int AStar::GetDistanceBetween(AStarNode* node1, AStarNode* node2)
	{
		int distanceX = std::abs(node1->GetGridX() - node2->GetGridX());
		int distanceY = std::abs(node1->GetGridY() - node2->GetGridY());

		return (10 * distanceX) + (10 * distanceY);
	}

	// --------------------------------------------------
	// This mehtod is used to safly free the memory for 
	// the node map used by the AStar class.
	// --------------------------------------------------
	AStar::~AStar() {
		if (nodeMap != nullptr) {
			delete nodeMap;
			nodeMap = nullptr;
		}
	}
}