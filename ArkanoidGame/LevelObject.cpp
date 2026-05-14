#include "LevelObject.h"
#include "Sprite.h"

namespace Arcanoid
{
	LevelObject::LevelObject(TextureType type, sf::Vector2f Position)
	{
		ObjectSprite.setTexture(AssetController::Instance().GetTexture(type));

		SetSize(BASE_SPRITE_SCALE);

		ObjectPosition = Position;
		ObjectSprite.setPosition(ObjectPosition);
	}

	void LevelObject::Update()
	{
	}

	void LevelObject::OnCollision(LevelObject& otherObject)
	{

	}

	void LevelObject::SetSize(float size)
	{
		ObjectSprite.setScale(sf::Vector2f(size, size));
		SetSpriteRelativeOrigin(ObjectSprite, 0.5f, 0.5f);
	}

	void LevelObject::Draw(sf::RenderWindow& window)
	{
		window.draw(ObjectSprite);
	}

	void LevelObject::Move(sf::Vector2f offset)
	{
		ObjectPosition += offset;
		ObjectSprite.setPosition(ObjectPosition);

		if (CheckSpriteIntersectionWithBorders(ObjectSprite.getGlobalBounds()))
		{
			ObjectPosition -= offset;
			ObjectSprite.setPosition(ObjectPosition);
		}

	}

	sf::FloatRect LevelObject::GetBounds()
	{
		return ObjectSprite.getGlobalBounds();
	}
	sf::Vector2f  LevelObject::GetPosition()
	{
		return ObjectPosition;
	}
}

