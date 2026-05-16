#include "DurableBlock.h"
#include "Sprite.h"

namespace Arcanoid
{
	DurableBlock::DurableBlock(sf::Vector2f Position) : Block(Position)
	{
	}

	void DurableBlock::OnCollision(LevelObject* otherObject)
	{
		ObjectSprite.setColor(GetRandomColor());

		CurrentEndurance--;

		if (CurrentEndurance == 0)
		{
			MarkToRemove();
		}
	}
}