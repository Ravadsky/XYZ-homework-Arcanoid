#pragma once
#include <string>

namespace Arcanoid
{
	// Resources path
	const std::string RESOURCES_PATH = "Resources/";
	const std::string TEXTURES_PATH = RESOURCES_PATH + "Textures/";
	const std::string FONTS_PATH = RESOURCES_PATH + "Fonts/";
	const std::string SOUNDS_PATH = RESOURCES_PATH + "Sounds/";

	// Game Window
	const unsigned int SCREEN_WIDTH = 1280;
	const unsigned int SCREEN_HEGHT = 720;
	const std::string GAME_NAME = "Arcanoid";

	// System
	const float TIME_PER_FRAME = 1.f / 60.f; // 60 fps
	const int MAX_RECORDS_TABLE_SIZE = 5;
	const float BASE_SPRITE_SCALE = 4.f;

	// Player Parameters
	const std::string PLAYER_NAME = "Player";
	const float PLAYER_BASE_SPEED = 100.f;

	// Ball Parameters
	const float BALL_BASE_SPEED = 20.f;
	const sf::Vector2f INITIAL_DIRECTION{ 1.f, 1.f };
	const float INITIAL_SPEED{ 4.f };

	// Block Parameters
	const int BLOCK_COLUMNS = 8;
	const int BLOCK_ROWS = 4;
	const int BLOCK_MAX_COUNT = BLOCK_COLUMNS * BLOCK_ROWS;

}
