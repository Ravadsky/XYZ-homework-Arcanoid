#pragma once
#include "LevelObject.h"

namespace Arcanoid
{

	class Block :
		public LevelObject
	{
	private:
		static int CompletedBlockCount;

	public:
		Block(sf::Vector2f Position);
		virtual ~Block();

		virtual void OnCollision(LevelObject* otherObject) override;

		static inline int GetCompletedBlockCount()
		{
			return CompletedBlockCount;
		}
		static inline void InitCompletedBlockCount()
		{
			CompletedBlockCount = 0;
		}
	};
}

