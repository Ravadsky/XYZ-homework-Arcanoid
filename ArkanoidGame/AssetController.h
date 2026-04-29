#pragma once
#include "SFML/Graphics.hpp"
#include "SFML/Audio.hpp"

enum class TextureType
{
	Block,
	Platform,
	Ball,
};

enum class SoundType
{
	Death,
	Destroy,
	Ricochet,
};

namespace Arcanoid
{
	class AssetController
	{
	private:
		// Resources
		sf::Texture blockTexture;
		sf::Texture platformTexture;
		sf::Texture ballTexture;

		sf::SoundBuffer destroyBlockSoundBuffer;
		sf::SoundBuffer deathSoundBuffer;
		sf::SoundBuffer ricochetSoundBuffer;

	public:
		AssetController();

		AssetController(const AssetController& app) = delete;
		AssetController& operator= (const AssetController&) = delete;
		static AssetController& Instance();

		sf::Texture& GetTexture(TextureType type);
		sf::SoundBuffer& GetSoundBuffer(SoundType type);
	};


}


