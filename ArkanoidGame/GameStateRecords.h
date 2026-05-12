#pragma once
#include "GameStateBase.h"

#include <vector>

namespace Arcanoid
{
	class GameStateRecordsData: public GameStateBase
	{
	private:
		sf::Text titleText;
		std::vector<sf::Text> tableTexts;
		sf::Text hintText;

	public:
		GameStateRecordsData();
		~GameStateRecordsData();

		virtual void HandleWindowEvent(const sf::Event& event) override;
		virtual void Update(float timeDelta) override;
		virtual void Draw(sf::RenderWindow& window) override;
	};
}
