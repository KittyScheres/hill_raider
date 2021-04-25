#pragma once

#include "entity.h"

namespace HillRaider
{
	// --------------------------------------------------
	// The room callback can be used by entity classes to
	// interact with a room class instance.
	// --------------------------------------------------
	class RoomCallback
	{
	public:
		virtual void RemoveEntity(Entity* entity) {}
	};
}