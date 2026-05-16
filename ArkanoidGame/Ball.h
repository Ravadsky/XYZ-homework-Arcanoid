#pragma once
#include "LevelObject.h"

namespace Arcanoid
{
    class Ball :
        public LevelObject
    {
    private:
        sf::Vector2f Direction = INITIAL_DIRECTION;
        float Radius;

    public:
        Ball(sf::Vector2f Position);

        virtual void Update() override;
        virtual void OnCollision(LevelObject* otherObject) override;

        void SwapDirection(EAxis axis);
        void SetDirection(EAxis axis);

        float GetRadius();

    };
}