#include "aStar.h"

namespace HillRaider
{
	AStar* AStar::s_Instance = nullptr;

	// --------------------------------------------------
	// This method is used to get the instance of the 
	// AStar singleton class.
	// --------------------------------------------------
	AStar* AStar::GetIntance()
	{
		if (s_Instance == nullptr) {
			s_Instance = new AStar();
		}

		return s_Instance;
	}

	// --------------------------------------------------
	// This method is used to destroy the instance of the 
	// AStar singleton class.
	// --------------------------------------------------
	void AStar::DestroyInstance()
	{
		delete s_Instance;
		s_Instance = nullptr;
	}

	// --------------------------------------------------
	// This method is used to set the node map for the
	// current room.
	// --------------------------------------------------
	void AStar::SetNodeMap(TileMap* tileMap) {
		if (m_NodeMap != nullptr) {
			delete m_NodeMap;
		}

		m_NodeMap = new AStarGrid(tileMap);
	}

	// --------------------------------------------------
	// This method is used to set a reference to the
	// enemy entity list of the current room.
	// --------------------------------------------------
	void AStar::SetEntitiesListReference(std::list<Entity*>* const entitiesList)
	{
		m_EntitiesListReference = entitiesList;
	}

	// --------------------------------------------------
	// This method is used to set the end goal for the
	// path finding algorithm.
	// --------------------------------------------------
	void AStar::SetEndGoal(Entity* entity)
	{
		m_EndGoal = entity;
	}

	// --------------------------------------------------
	// This method is used to get a walkable path for the
	// enemy ai. This method has been created with the help
	// of a tutorial.
	// --------------------------------------------------
	std::vector<AStarNode*> AStar::FindPath(Entity* pathFindingEntity, std::vector<int> startPosition, std::vector<int> comparePosition, bool bypassCheck)
	{
		std::vector<AStarNode*> path;

		AStarNode* startNode = m_NodeMap->GetNodeFromGrid(startPosition[0], startPosition[1]);
		AStarNode* compareNode = m_NodeMap->GetNodeFromGrid(comparePosition[0], comparePosition[1]);
		AStarNode* endNode = m_NodeMap->GetNodeFromGrid(m_EndGoal->GetPosition()[0], m_EndGoal->GetPosition()[1]);

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
				for (AStarNode* neighbour : m_NodeMap->GetNeighbouringNodes(currentNode)) {
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

			m_NodeMap->ResetWalkableNodes();
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

		for (Entity* entity : *m_EntitiesListReference) {
			if (entity != pathFindingEntity) {
				switch (entity->GetDirection()) {
				case Direction::UP:
					entityNode = m_NodeMap->GetNodeFromGrid(entity->GetHitbox()->GetPosition()[0], (entity->GetHitbox()->GetPosition()[1] + entity->GetHitbox()->GetHalfHeight()));
					infrontOfEntityNode = m_NodeMap->GetNodeGrid()[entityNode->GetGridY() - 1][entityNode->GetGridX()];
					break;

				case Direction::RIGHT:
					entityNode = m_NodeMap->GetNodeFromGrid((entity->GetHitbox()->GetPosition()[0] - entity->GetHitbox()->GetHalfWidth()), (entity->GetHitbox()->GetPosition()[1]));
					infrontOfEntityNode = m_NodeMap->GetNodeGrid()[entityNode->GetGridY()][entityNode->GetGridX() + 1];
					break;

				case Direction::DOWN:
					entityNode = m_NodeMap->GetNodeFromGrid(entity->GetHitbox()->GetPosition()[0], (entity->GetHitbox()->GetPosition()[1] - entity->GetHitbox()->GetHalfHeight()));
					infrontOfEntityNode = m_NodeMap->GetNodeGrid()[entityNode->GetGridY() + 1][entityNode->GetGridX()];
					break;

				case Direction::LEFT:
					entityNode = m_NodeMap->GetNodeFromGrid((entity->GetHitbox()->GetPosition()[0] + entity->GetHitbox()->GetHalfWidth()), (entity->GetHitbox()->GetPosition()[1]));
					infrontOfEntityNode = m_NodeMap->GetNodeGrid()[entityNode->GetGridY()][entityNode->GetGridX() - 1];
					break;
				}

				entityNode->SetWalkable(false);
				infrontOfEntityNode->SetWalkable(false);
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

		while (currentNode != startNode)
		{
			path.push_back(currentNode);
			currentNode = currentNode->GetParent();
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
		if (m_NodeMap != nullptr) {
			delete m_NodeMap;
			m_NodeMap = nullptr;
		}
	}
}