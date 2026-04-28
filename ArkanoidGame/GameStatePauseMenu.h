#pragma once
#include "GameStateBase.h"

#include "Menu.h"

namespace Arcanoid
{
	class GameStatePauseMenuData : public GameStateBase
	{
	private:
		sf::RectangleShape background;
		sf::Text titleText;

		Menu menu;
	public:
		GameStatePauseMenuData();
		virtual void Shutdown() override;
		virtual void HandleWindowEvent(const sf::Event& event) override;
		virtual void Update(float timeDelta) override;
		virtual void Draw(sf::RenderWindow& window) override;

	};
}
