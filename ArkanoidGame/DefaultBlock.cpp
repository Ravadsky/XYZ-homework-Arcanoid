#include "DefaultBlock.h"

Arcanoid::DefaultBlock::DefaultBlock(sf::Vector2f Position) : Block(Position)
{
}

void Arcanoid::DefaultBlock::OnCollision(LevelObject* otherObject)
{
	MarkToRemove();
}
