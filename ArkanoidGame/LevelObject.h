#pragma once
#include "SFML/Graphics.hpp"
#include "SFML/Audio.hpp"
#include "GameSettings.h"
#include "Sprite.h"

namespace Arcanoid
{
	class LevelObject
	{
	protected:
		sf::Sprite ObjectSprite;
		sf::Texture ObjectTexture;
		sf::Vector2f ObjectPosition;

	public:
		LevelObject(std::string TextureName, sf::Vector2f Position);
		virtual ~LevelObject() {}

		virtual void Update();

		void SetSize(float size);
		void Draw(sf::RenderWindow& window);
		void Move(sf::Vector2f offset);

		sf::FloatRect GetBounds();
		sf::Vector2f GetPosition();
	};
}


