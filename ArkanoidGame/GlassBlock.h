#pragma once
#include "Block.h"

namespace Arcanoid
{
    class GlassBlock :
        public Block
    {
    public:
        GlassBlock(sf::Vector2f Position);

        virtual void OnCollision(LevelObject* otherObject) override;
    };
}


