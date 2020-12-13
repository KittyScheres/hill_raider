#include "AStar.h"

namespace DownBelow
{
	AStar* AStar::instance = nullptr;

	AStar* AStar::GetIntance()
	{
		if (instance == nullptr) {
			instance = new AStar();
		}

		return instance;
	}

	void AStar::DestroyInstance()
	{
		delete instance;
		instance = nullptr;
	}
		
	void AStar::SetEndGoal(Entity* entity)
	{
		endGoal = entity;
	}
	
	void AStar::SetTileMap(TileMap* tileMap)
	{
		currentTileMap = tileMap;
		movementDirections.clear();
		movementDirections.push_back(std::vector<int> {0, (currentTileMap->GetTileHeight() * -1) / 2});
		movementDirections.push_back(std::vector<int> {currentTileMap->GetTileWidth() / 2, 0});
		movementDirections.push_back(std::vector<int> {0, currentTileMap->GetTileHeight() / 2});
		movementDirections.push_back(std::vector<int> {(currentTileMap->GetTileWidth() * -1) / 2, 0});
	}

	std::vector<std::vector<int>> AStar::FindPath(std::vector<int> startPosition)
	{
		std::vector<std::vector<std::vector<int>>> paths;
		paths.push_back(std::vector<std::vector<int>> {startPosition});

		while (false) {
			std::vector<std::vector<std::vector<int>>> possioblePaths;
			std::vector<int> values;

			for (auto path : paths) {
				for (auto direction : movementDirections) {
					std::vector<int> newPos{ path[path.size() - 1][0] + direction[0], path[path.size() - 1][1] + direction[1] };
					if (currentTileMap->GetCollision(newPos[0], newPos[1]) == ' ' && !CheckForRepeat(paths, newPos)) {
						std::vector<std::vector<int>> newPath = path;
						newPath.push_back(newPos);
						possioblePaths.push_back(newPath);
						values.push_back(GetValue(endGoal->GetPosition(), newPos) + GetValue(startPosition, newPos));
					}
				}
			}

			int lowestValueIndex = 0;
			for (auto value : values) {
				if (value < values[lowestValueIndex]) {
					lowestValueIndex = std::distance(values.begin(), std::find(values.begin(), values.end(), value));
				}
			}

			paths.push_back(possioblePaths[lowestValueIndex]);
		}

		for (auto path : paths) {
			printf("x:%i, y%i\n-\n", endGoal->GetPosition()[0] - path[path.size() - 1][0], endGoal->GetPosition()[1] - path[path.size() - 1][1]);
		}

		printf("-----------\n\n");

		return paths[0];
	}

	AStar::AStar() {}

	AStar::~AStar() {}

	int AStar::GetValue(std::vector<int> comparePos, std::vector<int> newPos) {
		int valueX = comparePos[0] - newPos[0];
		int valueY = comparePos[1] - newPos[1];

		if (valueX < 0) {
			valueX = -valueX;
		}

		if (valueY < 0) {
			valueY = -valueY;
		}

		return valueX + valueY;
	}

	bool AStar::CheckForRepeat(std::vector<std::vector<std::vector<int>>> paths, std::vector<int> newPos)
	{
		bool hasRepeat = false;

		for (auto path : paths) {
			for (auto pos : path) {
				if (pos[0] == newPos[0] && pos[1] == newPos[1]) {
					hasRepeat = true;
				}
			}
		}

		return hasRepeat;
	}
}