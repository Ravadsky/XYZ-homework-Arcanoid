#include "AssetController.h"
#include "assert.h"
#include "GameSettings.h"

namespace Arcanoid
{
	AssetController& AssetController::Instance()
	{
		static AssetController instance;
		return instance;
	}

	sf::Texture& AssetController::GetTexture(TextureType type)
	{
		switch (type)
		{
		case (TextureType::Block):
			return blockTexture;
		case (TextureType::Ball):
			return ballTexture;
		case (TextureType::Platform):
			return platformTexture;
		}
	}

	sf::SoundBuffer& AssetController::GetSoundBuffer(SoundType type)
	{
		switch (type)
		{
		case (SoundType::Death):
			return deathSoundBuffer;
		case (SoundType::Destroy):
			return destroyBlockSoundBuffer;
		case (SoundType::Ricochet):
			return ricochetSoundBuffer;
		}
	}

	AssetController::AssetController()
	{
		// Init textures
		assert(blockTexture.loadFromFile(TEXTURES_PATH + "Block.png"));
		assert(platformTexture.loadFromFile(TEXTURES_PATH + "Platform.png"));
		assert(ballTexture.loadFromFile(TEXTURES_PATH + "Ball.png"));
		// Init sounds
		assert(destroyBlockSoundBuffer.loadFromFile(SOUNDS_PATH + "DestroyBlock.wav"));
		assert(deathSoundBuffer.loadFromFile(SOUNDS_PATH + "Death.wav"));
		assert(ricochetSoundBuffer.loadFromFile(SOUNDS_PATH + "Ricochet.wav"));
	}
}

