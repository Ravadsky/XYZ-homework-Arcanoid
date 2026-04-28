#include "GameStatePlaying.h"

#include "Application.h"
#include "Game.h"
#include "Text.h"
#include <sstream>

#include "LevelObject.h"
#include "Ball.h"
#include "block.h"

namespace Arcanoid
{
	GameStatePlayingData::GameStatePlayingData() : GameStateBase()
	{
		// Init textures
		assert(blockTexture.loadFromFile(TEXTURES_PATH + "Block.png"));
		assert(platformTexture.loadFromFile(TEXTURES_PATH + "Platform.png"));
		assert(ballTexture.loadFromFile(TEXTURES_PATH + "Ball.png"));
		// Init sounds
		assert(destroyBlockSoundBuffer.loadFromFile(SOUNDS_PATH + "DestroyBlock.wav"));
		assert(deathSoundBuffer.loadFromFile(SOUNDS_PATH + "Death.wav"));
		assert(ricochetSoundBuffer.loadFromFile(SOUNDS_PATH + "Ricochet.wav"));

		destroyBlockSound.setBuffer(destroyBlockSoundBuffer);
		deathSound.setBuffer(deathSoundBuffer);
		ricochetSound.setBuffer(ricochetSoundBuffer);

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

		Platform = new LevelObject("Platform", sf::Vector2f(SCREEN_WIDTH / 2, SCREEN_HEGHT - 200.f));

		ball = new Ball(sf::Vector2f(SCREEN_WIDTH / 2, SCREEN_HEGHT / 2));

		sf::Vector2f BlockPos;
		float XOffset = 160.f;
		float YOffset = 80.f;
		for (int x = 0; x < BLOCK_COLUMNS; x++)
		{
			for (int y = 0; y < BLOCK_ROWS; y++)
			{
				BlockPos = sf::Vector2f(XOffset / 2+ x * XOffset, YOffset / 2+ y * YOffset);
				BlocksOnLevel.push_back(new Block(BlockPos));
			}
		}
	}

	void GameStatePlayingData::Shutdown()
	{
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
			Platform->Move(sf::Vector2f(-20.f, 0.f));
		}
		else if (sf::Keyboard::isKeyPressed(sf::Keyboard::D) or sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
		{
			Platform->Move(sf::Vector2f(20.f, 0.f));
		}

		ball->Update();

		if (ball->GetPosition().y < Platform->GetPosition().y)
		{
			if (CheckCollisionWithBall(*Platform, *ball))
				ball->SetYDirection();
		}
	
		for (auto iterator = BlocksOnLevel.begin(); iterator != BlocksOnLevel.end(); )
		{
			Block* CurrentBlock = *iterator;
			if (CheckCollisionWithBall(*CurrentBlock, *ball))
			{
				CompletedBlockCount++;
				delete CurrentBlock;
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

		Platform->Draw(window);
		for (auto block : BlocksOnLevel)
		{
			block->Draw(window);
		}
		ball->Draw(window);


		scoreText.setOrigin(GetTextOrigin(scoreText, { 0.f, 0.f }));
		scoreText.setPosition(10.f, 10.f);
		window.draw(scoreText);

		sf::Vector2f viewSize = window.getView().getSize();
		inputHintText.setPosition(viewSize.x - 10.f, 10.f);
		window.draw(inputHintText);
	}


}
