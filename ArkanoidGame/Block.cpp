#include "Block.h"

namespace Arcanoid
{
	Block::Block(sf::Vector2f Position) : LevelObject(TextureType::Block, Position)
	{
		ObjectSprite.setColor(GetRandomColor());
	}
}