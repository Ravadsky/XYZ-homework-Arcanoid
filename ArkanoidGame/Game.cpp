#include "Game.h"
#include <assert.h>
#include <algorithm>

#include "GameStatePlaying.h"
#include "GameStateGameOver.h"
#include "GameStatePauseMenu.h"
#include "GameStateMainMenu.h"
#include "GameStateRecords.h"

namespace Arcanoid
{
	Game::Game()
	{
		// Generate fake records table
		recordsTable =
		{
			{"John", BLOCK_MAX_COUNT - 1},
			{"Jane", BLOCK_MAX_COUNT / 2 + 2 },
			{"Alice", BLOCK_MAX_COUNT / 3 },
			{"Bob", BLOCK_MAX_COUNT / 4 - 1 },
			{"Clementine", BLOCK_MAX_COUNT / 6 },
		};

		SwitchStateTo(GameStateType::MainMenu);
	}

	Game::~Game()
	{
		Shutdown();
	}

	void Game::HandleWindowEvents(sf::RenderWindow& window)
	{
		sf::Event event;
		while (window.pollEvent(event))
		{
			// Close window if close button or Escape key pressed
			if (event.type == sf::Event::Closed)
			{
				window.close();
			}

			if (stateStack.size() > 0)
			{
				stateStack.back().HandleWindowEvent(event);
			}
		}
	}

	bool Game::Update(float timeDelta)
	{
		if (gameStateContext.stateChangeType == GameStateChangeType::Switch)
		{
			// Shutdown all game states
			while (stateStack.size() > 0)
			{
				stateStack.back().Shutdown();
				stateStack.pop_back();
			}
		}
		else if (gameStateContext.stateChangeType == GameStateChangeType::Pop)
		{
			// Shutdown only current game state
			if (stateStack.size() > 0)
			{
				stateStack.back().Shutdown();
				stateStack.pop_back();
			}
		}

		// Initialize new game state if needed
		if (gameStateContext.pendingGameStateType != GameStateType::None)
		{
			stateStack.emplace_back(gameStateContext.pendingGameStateType, gameStateContext.pendingGameStateIsExclusivelyVisible);
		}

		gameStateContext.Reset();

		if (stateStack.size() > 0)
		{
			stateStack.back().Update(timeDelta);
			return true;
		}

		return false;
	}

	void Game::Draw(sf::RenderWindow& window)
	{
		if (stateStack.size() > 0)
		{
			std::vector<GameState*> visibleGameStates;

			for (auto it = stateStack.rbegin(); it != stateStack.rend(); ++it)
			{
				visibleGameStates.push_back(&(*it));
				if (it->isStateExclusivelyVisible())
				{
					break;
				}
			}

			for (auto it = visibleGameStates.rbegin(); it != visibleGameStates.rend(); ++it)
			{
				(**it).Draw(window);
			}
		}
	}

	void Game::Shutdown()
	{
		// Shutdown all game states
		while (stateStack.size() > 0)
		{
			stateStack.back().Shutdown();
			stateStack.pop_back();
		}

		gameStateContext.Reset();
	}

	void Game::PushState(GameStateType stateType, bool isExclusivelyVisible)
	{
		gameStateContext.Set(GameStateChangeType::Push, stateType, isExclusivelyVisible);
	}

	void Game::PopState()
	{
		gameStateContext.Set(GameStateChangeType::Pop, GameStateType::None, false);
	}

	void Game::SwitchStateTo(GameStateType newState)
	{
		gameStateContext.Set(GameStateChangeType::Switch, newState, false);
	}

	bool Game::IsEnableOptions(GameOptions option) const
	{
		const bool isEnable = ((std::uint8_t)options & (std::uint8_t)option) != (std::uint8_t)GameOptions::Empty;
		return isEnable;
	}

	void Game::SetOption(GameOptions option, bool value)
	{
		if (value) {
			options = (GameOptions)((std::uint8_t)options | (std::uint8_t)option);
		}
		else {
			options = (GameOptions)((std::uint8_t)options & ~(std::uint8_t)option);
		}
	}

	int Game::GetRecordByPlayerId(const std::string& playerId) const
	{
		auto it = recordsTable.find(playerId);
		return it == recordsTable.end() ? 0 : it->second;
	}

	void Game::UpdateRecord(const std::string& playerId, int score)
	{
		recordsTable[playerId] = std::max(recordsTable[playerId], score);
	}


	GameState::GameState(GameStateType GameType, bool pendingIsExclusivelyVisible)
	{
		type = GameType;
		isExclusivelyVisible = pendingIsExclusivelyVisible;
		switch (type)
		{
		case GameStateType::MainMenu:
		{
			data = new GameStateMainMenuData();
			break;
		}
		case GameStateType::Playing:
		{
			data = new GameStatePlayingData();
			break;
		}
		case GameStateType::GameOver:
		{
			data = new GameStateGameOverData();
			break;
		}
		case GameStateType::ExitDialog:
		{
			data = new GameStatePauseMenuData();
			break;
		}
		case GameStateType::Records:
		{
			data = new GameStateRecordsData();
			break;
		}
		default:
			assert(false); // We want to know if we forgot to implement new game state
			break;
		}
	}

	void GameState::Shutdown()
	{
		if (data)
		{
			data->Shutdown();
		}
		delete data;
		data = nullptr;
	}

	void GameState::HandleWindowEvent(sf::Event& event)
	{
		if (data)
		{
			data->HandleWindowEvent(event);
		}
	}

	void GameState::Update(float timeDelta)
	{
		if (data)
		{
			data->Update(timeDelta);
		}
	}

	void GameState::Draw(sf::RenderWindow& window)
	{
		if (data)
		{
			data->Draw(window);
		}
	}

	bool GameState::isStateExclusivelyVisible()
	{
		return isExclusivelyVisible;
	}

	void GameStateContext::Reset()
	{
		stateChangeType = GameStateChangeType::None;
		pendingGameStateType = GameStateType::None;
		pendingGameStateIsExclusivelyVisible = false;
	}

	void GameStateContext::Set(GameStateChangeType ChangeType, GameStateType StateType, bool isExclusivelyVisible)
	{
		stateChangeType = ChangeType;
		pendingGameStateType = StateType;
		pendingGameStateIsExclusivelyVisible = isExclusivelyVisible;
	}
}
