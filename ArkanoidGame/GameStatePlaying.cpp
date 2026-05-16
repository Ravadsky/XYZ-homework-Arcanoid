#include "GameStatePlaying.h"

#include "Application.h"
#include "Game.h"
#include "Text.h"
#include <sstream>

#include "LevelObject.h"
#include "Ball.h"
#include "Platform.h"

#include "DefaultBlock.h"
#include "DurableBlock.h"
#include "GlassBlock.h"

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
		scoreText.setString("Blocks: 0");

		inputHintText.setFont(font);
		inputHintText.setCharacterSize(24);
		inputHintText.setFillColor(sf::Color::White);
		inputHintText.setString("Use A - move left, D - move right, ESC - pause");
		inputHintText.setOrigin(GetTextOrigin(inputHintText, { 1.f, 0.f }));

		InitializeScene();
	}

	GameStatePlayingData::~GameStatePlayingData()
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
		GetPlayerInput();

		ball->Update();

		// Если платформа находится ниже шарика
		if (ball->GetPosition().y < platform->GetPosition().y)
		{
			if (CheckCollisionWithBall(*platform, *ball))
				ball->SetDirection(EAxis::YAxis);
		}

		CheckCollisionsOnScene();

		RemoveMarkedObjects();

		if (ball->GetBounds().top + ball->GetBounds().height >= SCREEN_HEGHT)
		{
			deathSound.play();

			Game& game = Application::Instance().GetGame();

			game.UpdateRecord(PLAYER_NAME, Block::GetCompletedBlockCount());
			game.PushState(GameStateType::GameOver, false);

		}

		if (Block::GetCompletedBlockCount() == BLOCK_MAX_COUNT)
		{
			deathSound.play();

			Game& game = Application::Instance().GetGame();

			game.UpdateRecord(PLAYER_NAME, Block::GetCompletedBlockCount());
			game.PushState(GameStateType::GameWinOver, false);
		}

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

		scoreText.setString("Blocks: " + std::to_string(Block::GetCompletedBlockCount()));
		scoreText.setOrigin(GetTextOrigin(scoreText, { 0.f, 0.f }));
		scoreText.setPosition(10.f, 10.f);
		window.draw(scoreText);

		sf::Vector2f viewSize = window.getView().getSize();
		inputHintText.setPosition(viewSize.x - 10.f, 10.f);
		window.draw(inputHintText);
	}

	void GameStatePlayingData::GetPlayerInput()
	{
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::A) or sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
		{
			platform->Move(sf::Vector2f(-PLAYER_BASE_SPEED, 0.f));
		}
		else if (sf::Keyboard::isKeyPressed(sf::Keyboard::D) or sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
		{
			platform->Move(sf::Vector2f(PLAYER_BASE_SPEED, 0.f));
		}
	}

	void GameStatePlayingData::InitializeScene()
	{
		platform = std::make_unique<Platform>(sf::Vector2f(SCREEN_WIDTH / 2, SCREEN_HEGHT - 100.f));

		ball = std::make_unique <Ball>(sf::Vector2f(SCREEN_WIDTH / 2, SCREEN_HEGHT / 2));

		sf::Vector2f BlockPos;
		float XOffset = 160.f;
		float YOffset = 80.f;
		BlocksOnLevel.clear();
		for (int x = 0; x < BLOCK_COLUMNS; x++)
		{
			for (int y = 0; y < BLOCK_ROWS; y++)
			{
				BlockPos = sf::Vector2f(XOffset / 2 + x * XOffset, YOffset / 2 + y * YOffset);

				SpawnBlock(BlockPos);
			}
		}

		Block::InitCompletedBlockCount();
	}

	void GameStatePlayingData::SpawnBlock(sf::Vector2f BlockPosition)
	{
		// TODO - рандомный выбор блоков
		int random_index = std::rand() % 4;
		switch (random_index)
		{
		case 0:
		case 1:
			BlocksOnLevel.push_back(std::make_unique<DefaultBlock>(BlockPosition));
			break;
		case 2:
			BlocksOnLevel.push_back(std::make_unique<DurableBlock>(BlockPosition));
			break;
		case 3:
			BlocksOnLevel.push_back(std::make_unique<GlassBlock>(BlockPosition));
			break;
		}
	}

	void GameStatePlayingData::RemoveMarkedObjects()
	{
		for (auto iterator = BlocksOnLevel.begin(); iterator != BlocksOnLevel.end(); )
		{
			LevelObject* CurrentObject = iterator->get();
			if (CurrentObject->isMarkedToRemove())
				iterator = BlocksOnLevel.erase(iterator);
			else
				iterator++;
		}
	}

	void GameStatePlayingData::CheckCollisionsOnScene()
	{
		for (auto iterator = BlocksOnLevel.begin(); iterator != BlocksOnLevel.end(); )
		{
			Block* CurrentBlock = iterator->get();
			if (CheckCollisionWithBall(*CurrentBlock, *ball))
			{
				ball->OnCollision(CurrentBlock);
				CurrentBlock->OnCollision(ball.get());

				break;
			}
			iterator++;
		}
	}


}
