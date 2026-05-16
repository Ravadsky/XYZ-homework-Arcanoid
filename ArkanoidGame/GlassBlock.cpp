#include "GlassBlock.h"
#include "Sprite.h"

namespace Arcanoid
{
	GlassBlock::GlassBlock(sf::Vector2f Position) : Block(Position)
	{
		CollisionPreset = ECollisionPreset::Overlap;
		GetRandomColorWithTransparency();
	}

	void GlassBlock::OnCollision(LevelObject* otherObject)
	{
		MarkToRemove();
	}
}