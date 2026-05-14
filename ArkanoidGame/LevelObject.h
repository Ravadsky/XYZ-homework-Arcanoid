#pragma once
#include "SFML/Graphics.hpp"
#include "SFML/Audio.hpp"
#include "GameSettings.h"
#include "AssetController.h"

enum class EAxis
{
	XAxis,
	YAxis,
};

namespace Arcanoid
{
	class LevelObject
	{
	protected:
		sf::Sprite ObjectSprite;
		sf::Vector2f ObjectPosition;

	public:
		LevelObject(TextureType type, sf::Vector2f Position);
		virtual ~LevelObject() {}

		virtual void Update();
		virtual void OnCollision(LevelObject& otherObject);

		void SetSize(float size);
		void Draw(sf::RenderWindow& window);
		void Move(sf::Vector2f offset);

		sf::FloatRect GetBounds();
		sf::Vector2f GetPosition();
	};
}


