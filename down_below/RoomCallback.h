#pragma once

#include "Entity.h"

namespace DownBelow
{
	class RoomCallback
	{
	public:
		virtual void RemoveEntity(Entity* entity) {}
	};
}