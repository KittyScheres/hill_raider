#pragma once

#include "Entity.h"

namespace HillRaider
{
	class RoomCallback
	{
	public:
		virtual void RemoveEntity(Entity* entity) {}
	};
}