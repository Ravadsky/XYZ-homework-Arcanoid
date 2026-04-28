#pragma once
#include "GameStateBase.h"
#include <vector>

namespace Arcanoid
{
	class LevelObject;
	class Ball;
	class Block;

	class GameStatePlayingData : public GameStateBase
	{
	private:
		// Resources
		sf::Texture blockTexture;
		sf::Texture platformTexture;
		sf::Texture ballTexture;

		sf::SoundBuffer destroyBlockSoundBuffer;
		sf::SoundBuffer deathSoundBuffer;
		sf::SoundBuffer ricochetSoundBuffer;

		// UI data
		sf::Text scoreText;
		sf::Text inputHintText;
		sf::RectangleShape background;

		// Sounds
		sf::Sound destroyBlockSound;
		sf::Sound deathSound;
		sf::Sound ricochetSound;

		LevelObject* Platform;
		Ball* ball;
		std::vector<Block*> BlocksOnLevel;

		bool GameOver = false;
		int CompletedBlockCount = 0;

	public:
		GameStatePlayingData();
		virtual void Shutdown() override;
		virtual void HandleWindowEvent(const sf::Event& event) override;
		virtual void Update(float timeDelta) override;
		virtual void Draw(sf::RenderWindow& window) override;

	};
}
