#include "Ball.h"
#include "Sprite.h"

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
			SwapDirection(EAxis::XAxis);
		}
		if (SpriteRectangle.top <= 0)
		{
			SwapDirection(EAxis::YAxis);
		}

	}

	void Ball::OnCollision(LevelObject& otherObject)
	{
		SwapDirection(GetCollisionAxis(otherObject, *this));
	}

	void Ball::SwapDirection(EAxis axis)
	{
		switch (axis)
		{
		case EAxis::XAxis:
			Direction = sf::Vector2f(-Direction.x, Direction.y);
			break;
		case EAxis::YAxis:
			Direction = sf::Vector2f(Direction.x, -Direction.y);
			break;
		}
	}

	void Ball::SetDirection(EAxis axis)
	{
		switch (axis)
		{
		case EAxis::XAxis:
			Direction = sf::Vector2f(INITIAL_DIRECTION.x, Direction.y);
			break;
		case EAxis::YAxis:
			Direction = sf::Vector2f(Direction.x, -INITIAL_DIRECTION.y);
			break;
		}

		
	}

	float Ball::GetRadius()
	{
		return Radius;
	}
}

