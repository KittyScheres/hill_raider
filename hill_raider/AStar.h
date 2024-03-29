#pragma once

#include "aStarGrid.h"
#include "entity.h"
#include "tileMap.h"
#include <list>
#include <unordered_set>
#include <math.h>

namespace HillRaider
{
	// --------------------------------------------------
	// This singleton class is used for the a* pathfinding 
	// algorithm implementation which is used by the AI to 
	// follow the player. This class is one of three classes 
	// which have been created with the help of a tutorial 
	// on the implementation of the a* pathfinding algorithm.
	// --------------------------------------------------
	class AStar
	{
	private:
		static AStar* s_Instance;
		AStarGrid* m_NodeMap = nullptr;
		std::list<Entity*>* m_EntitiesListReference = nullptr;
		Entity* m_EndGoal = nullptr;

	public:
		static AStar* GetIntance();
		static void DestroyInstance();
		void SetNodeMap(TileMap* tileMap);
		void SetEntitiesListReference(std::list<Entity*>* const entitiesList);
		void SetEndGoal(Entity* entity);
		std::vector<AStarNode*> FindPath(Entity* pathFindingEntity, std::vector<int> startPosition, std::vector<int> comparePosition, bool bypassCheck);
		
	private:
		AStar() {};
		void SetNonWalkableEntityNodes(Entity* pathFindingEntity);
		std::vector<AStarNode*> RetracePath(AStarNode* startNode, AStarNode* endNode);
		int GetDistanceBetween(AStarNode* node1, AStarNode* node2);
		~AStar();
	};
}