#include "Ball.h"

namespace Arcanoid
{
	Arcanoid::Ball::Ball(sf::Vector2f Position) : LevelObject(TextureType::Ball, Position)
	{
		Radius = (ObjectSprite.getLocalBounds().height / 2) * BASE_SPRITE_SCALE;
	}

	void Arcanoid::Ball::Update()
	{
		Move(Direction * INITIAL_SPEED);

		sf::FloatRect SpriteRectangle = ObjectSprite.getGlobalBounds();

		if (SpriteRectangle.left <= 0 or SpriteRectangle.left + SpriteRectangle.width >= SCREEN_WIDTH)
		{
			SwapXDirection();
		}
		if (SpriteRectangle.top <= 0)
		{
			SwapYDirection();
		}

	}
	void Ball::SwapXDirection()
	{
		Direction = sf::Vector2f(-Direction.x, Direction.y);
	}
	void Ball::SwapYDirection()
	{
		Direction = sf::Vector2f(Direction.x, -Direction.y);

	}
	void Ball::SetYDirection()
	{
		Direction = sf::Vector2f(Direction.x, -INITIAL_DIRECTION.y);
	}
	float Ball::GetRadius()
	{
		return Radius;
	}
}

