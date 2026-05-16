#include "Block.h"
#include "Sprite.h"

namespace Arcanoid
{
	int Block::CompletedBlockCount = 0;

	Block::Block(sf::Vector2f Position) : LevelObject(TextureType::Block, Position)
	{
		ObjectSprite.setColor(GetRandomColor());
	}

	Block::~Block()
	{
		CompletedBlockCount++;
	}

	void Block::OnCollision(LevelObject* otherObject)
	{
	}
}