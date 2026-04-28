#pragma once
#include "SFML/Graphics.hpp"
#include "SFML/Audio.hpp"
#include "GameSettings.h"
#include "assert.h"

class Game;

namespace Arcanoid
{
	class GameStateBase
	{
	protected:
		sf::Font font;

	public:
		GameStateBase();
		virtual ~GameStateBase() {};
		virtual void Shutdown() = 0;
		virtual void HandleWindowEvent(const sf::Event& event) = 0;
		virtual void Update(float timeDelta) = 0;
		virtual void Draw(sf::RenderWindow& window) = 0;
	};
}
