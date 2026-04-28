#pragma once
#include "GameStateBase.h"

#include "Menu.h"

namespace Arcanoid
{
	class GameStateMainMenuData: public GameStateBase
	{
	private:
		Menu menu;

	public:
		GameStateMainMenuData();
		virtual void Shutdown() override;
		virtual void HandleWindowEvent(const sf::Event& event) override;
		virtual void Update(float timeDelta) override;
		virtual void Draw(sf::RenderWindow& window) override;
	};
}
