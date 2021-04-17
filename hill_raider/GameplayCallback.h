#pragma once

#include "Direction.h"

namespace HillRaider
{
	// -------------------------------------------------------------------
	// The gameplay callback contains methods which can be used by the
	// player to interact with the gameplay state.
	// -------------------------------------------------------------------
	class GameplayCallback
	{
	public:
		virtual bool HasRoomBeenCleared() { return true; }
		virtual void MovePlayerToNextRoom(Direction direction) {}
		virtual void PlayerHasWonTheGame() {}
	};
}