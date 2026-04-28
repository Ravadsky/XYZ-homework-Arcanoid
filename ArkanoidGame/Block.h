#pragma once
#include "LevelObject.h"

namespace Arcanoid
{

	class Block :
		public LevelObject
	{
	public:
		Block(sf::Vector2f Position);
	};
}

