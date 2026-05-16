#pragma once
#include "Block.h"

namespace Arcanoid
{
	class DurableBlock :
		public Block
	{
	private:
		const int StartEndurance = 3;
		int CurrentEndurance = StartEndurance;

	public:
		DurableBlock(sf::Vector2f Position);

		virtual void OnCollision(LevelObject* otherObject) override;
	};
}

