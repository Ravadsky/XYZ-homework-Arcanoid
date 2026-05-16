#pragma once
#include "Block.h"

namespace Arcanoid
{
	class DefaultBlock :
		public Block
	{
	public:
		DefaultBlock(sf::Vector2f Position);

		virtual void OnCollision(LevelObject* otherObject) override;

	};
}


