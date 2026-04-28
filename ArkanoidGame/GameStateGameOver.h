#pragma once
#include "GameStateBase.h"

namespace Arcanoid
{
	class GameStateGameOverData : public GameStateBase
	{
	private:
		float timeSinceGameOver = 0.f;

		// UI data
		sf::RectangleShape background;
		sf::Text gameOverText;
		sf::Text hintText;
		std::vector<sf::Text> recordsTableTexts;

	public:
		GameStateGameOverData();
		virtual void Shutdown() override;
		virtual void HandleWindowEvent(const sf::Event& event) override;
		virtual void Update(float timeDelta) override;
		virtual void Draw(sf::RenderWindow& window) override;
	};

}
