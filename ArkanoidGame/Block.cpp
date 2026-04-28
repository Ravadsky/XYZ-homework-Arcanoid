#include "Block.h"

namespace Arcanoid
{
	Block::Block(sf::Vector2f Position) : LevelObject("Block", Position)
	{
		ObjectSprite.setColor(GetRandomColor());
	}
}