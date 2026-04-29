#include "GameStatePlaying.h"

#include "Application.h"
#include "Game.h"
#include "Text.h"
#include <sstream>

#include "LevelObject.h"
#include "Ball.h"
#include "block.h"
#include "Platform.h"

namespace Arcanoid
{
	GameStatePlayingData::GameStatePlayingData() : GameStateBase()
	{
		destroyBlockSound.setBuffer(AssetController::Instance().GetSoundBuffer(SoundType::Destroy));
		deathSound.setBuffer(AssetController::Instance().GetSoundBuffer(SoundType::Death));
		ricochetSound.setBuffer(AssetController::Instance().GetSoundBuffer(SoundType::Ricochet));

		// Init background
		background.setSize(sf::Vector2f(SCREEN_WIDTH, SCREEN_HEGHT));
		background.setPosition(0.f, 0.f);
		background.setFillColor(sf::Color(40, 40, 40));

		scoreText.setFont(font);
		scoreText.setCharacterSize(24);
		scoreText.setFillColor(sf::Color::Yellow);

		inputHintText.setFont(font);
		inputHintText.setCharacterSize(24);
		inputHintText.setFillColor(sf::Color::White);
		inputHintText.setString("Use A - move left, D - move right, ESC - pause");
		inputHintText.setOrigin(GetTextOrigin(inputHintText, { 1.f, 0.f }));

		platform = std::make_unique<Platform>(sf::Vector2f(SCREEN_WIDTH / 2, SCREEN_HEGHT - 200.f));

		ball = std::make_unique < Ball>(sf::Vector2f(SCREEN_WIDTH / 2, SCREEN_HEGHT / 2));

		sf::Vector2f BlockPos;
		float XOffset = 160.f;
		float YOffset = 80.f;
		BlocksOnLevel.clear();
		for (int x = 0; x < BLOCK_COLUMNS; x++)
		{
			for (int y = 0; y < BLOCK_ROWS; y++)
			{
				BlockPos = sf::Vector2f(XOffset / 2 + x * XOffset, YOffset / 2 + y * YOffset);
				BlocksOnLevel.push_back(std::make_unique<Block>(BlockPos));
			}
		}
	}

	void GameStatePlayingData::Shutdown()
	{
		platform.reset();
		ball.reset();
		BlocksOnLevel.clear();
	}

	void GameStatePlayingData::HandleWindowEvent(const sf::Event& event)
	{
		if (event.type == sf::Event::KeyPressed)
		{
			if (event.key.code == sf::Keyboard::Escape)
			{
				Application::Instance().GetGame().PushState(GameStateType::ExitDialog, false);
			}
		}
	}

	void GameStatePlayingData::Update(float timeDelta)
	{
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::A) or sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
		{
			platform->Move(sf::Vector2f(-20.f, 0.f));
		}
		else if (sf::Keyboard::isKeyPressed(sf::Keyboard::D) or sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
		{
			platform->Move(sf::Vector2f(20.f, 0.f));
		}

		ball->Update();

		if (ball->GetPosition().y < platform->GetPosition().y)
		{
			if (CheckCollisionWithBall(*platform, *ball))
				ball->SetYDirection();
		}

		for (auto iterator = BlocksOnLevel.begin(); iterator != BlocksOnLevel.end(); )
		{
			Block* CurrentBlock = iterator->get();
			if (CheckCollisionWithBall(*CurrentBlock, *ball))
			{
				CompletedBlockCount++;
				iterator = BlocksOnLevel.erase(iterator);
			}
			else
			{
				iterator++;
			}
		}

		if (ball->GetBounds().top + ball->GetBounds().height >= SCREEN_HEGHT)
			GameOver = true;

		if (CompletedBlockCount == BLOCK_MAX_COUNT)
			GameOver = true;

		if (GameOver)
		{
			deathSound.play();

			Game& game = Application::Instance().GetGame();

			game.UpdateRecord(PLAYER_NAME, CompletedBlockCount);
			game.PushState(GameStateType::GameOver, false);

		}

		scoreText.setString("Blocks: " + std::to_string(CompletedBlockCount));
	}

	void GameStatePlayingData::Draw(sf::RenderWindow& window)
	{
		// Draw background
		window.draw(background);

		for (auto& block : BlocksOnLevel)
		{
			block->Draw(window);
		}
		platform->Draw(window);
		ball->Draw(window);


		scoreText.setOrigin(GetTextOrigin(scoreText, { 0.f, 0.f }));
		scoreText.setPosition(10.f, 10.f);
		window.draw(scoreText);

		sf::Vector2f viewSize = window.getView().getSize();
		inputHintText.setPosition(viewSize.x - 10.f, 10.f);
		window.draw(inputHintText);
	}


}
