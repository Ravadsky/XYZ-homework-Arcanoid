#include "LevelObject.h"

namespace Arcanoid
{
	LevelObject::LevelObject(std::string TextureName, sf::Vector2f Position)
	{
		ObjectTexture.loadFromFile(TEXTURES_PATH + TextureName + ".png");
		ObjectSprite.setTexture(ObjectTexture);

		SetSize(BASE_SPRITE_SCALE);

		ObjectPosition = Position;
		ObjectSprite.setPosition(ObjectPosition);
	}

	void LevelObject::Update()
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

