#pragma once
#include <SFML/Graphics.hpp>

#include "Sprite.h"
#include "GameSettings.h"
#include <unordered_map>
#include "GameStateBase.h"

namespace Arcanoid
{
	enum class GameOptions: std::uint8_t
	{
		InfiniteApples = 1 << 0,
		WithAcceleration = 1 << 1,

		Default = InfiniteApples | WithAcceleration,
		Empty = 0
	};

	enum class GameStateType
	{
		None = 0,
		MainMenu,
		Playing,
		GameOver,
		GameWinOver,
		ExitDialog,
		Records,
	};

	class GameState
	{
	private:
		GameStateType type = GameStateType::None;
		std::unique_ptr< GameStateBase> data;
		bool isExclusivelyVisible = false;

	public:
		GameState(GameStateType GameType, bool pendingIsExclusivelyVisible);
		void Shutdown();
		void HandleWindowEvent(sf::Event& event);
		void Update(float timeDelta);
		void Draw(sf::RenderWindow& window);
		bool isStateExclusivelyVisible();
	};

	enum class GameStateChangeType
	{
		None,
		Push,
		Pop,
		Switch
	};

	class GameStateContext
	{
	private:
		GameStateChangeType stateChangeType = GameStateChangeType::None;
		GameStateType pendingGameStateType = GameStateType::None;
		bool pendingGameStateIsExclusivelyVisible = false;
	public:
		void Reset();
		void Set(GameStateChangeType ChangeType, GameStateType StateType, bool isExclusivelyVisible = false);
		GameStateChangeType GetStateChangeType();
		GameStateType GetPendingGameStateType();
		bool IsPendingGameStateIsExclusivelyVisible();
	};

	class Game
	{
	public:
		using RecordsTable = std::unordered_map<std::string, int>;

		Game();
		~Game();

		void HandleWindowEvents(sf::RenderWindow& window);
		bool Update(float timeDelta); // Return false if game should be closed
		void Draw(sf::RenderWindow& window);
		void Shutdown();

		bool IsEnableOptions(GameOptions option) const;
		void SetOption(GameOptions option, bool value);

		const RecordsTable& GetRecordsTable() const { return recordsTable; }
		int GetRecordByPlayerId(const std::string& playerId) const;
		void UpdateRecord(const std::string& playerId, int score);

		void PushState(GameStateType stateType, bool isExclusivelyVisible);
		void SwitchStateTo(GameStateType newState);
		void PopState();

		
	private:
		std::vector<GameState> stateStack;
		GameOptions options = GameOptions::Default;

		GameStateContext gameStateContext;

		RecordsTable recordsTable;
	};

}
