#pragma once
#include "LevelObject.h"

namespace Arcanoid
{
	class Platform :
		public LevelObject
	{
	public:
		Platform(sf::Vector2f Position);
	};
}


