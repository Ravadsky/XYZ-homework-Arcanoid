#pragma once
#include "GameStateBase.h"
#include <vector>
#include <memory>

namespace Arcanoid
{
	class Ball;
	class Block;
	class Platform;

	class GameStatePlayingData : public GameStateBase
	{
	private:
		// UI data
		sf::Text scoreText;
		sf::Text inputHintText;
		sf::RectangleShape background;

		// Sounds
		sf::Sound destroyBlockSound;
		sf::Sound deathSound;
		sf::Sound ricochetSound;

		std::unique_ptr<Platform> platform;
		std::unique_ptr<Ball> ball;
		std::vector<std::unique_ptr<Block>> BlocksOnLevel;

		bool GameOver = false;
		int CompletedBlockCount = 0;

	public:
		GameStatePlayingData();
		~GameStatePlayingData();

		virtual void HandleWindowEvent(const sf::Event& event) override;
		virtual void Update(float timeDelta) override;
		virtual void Draw(sf::RenderWindow& window) override;

	};
}
