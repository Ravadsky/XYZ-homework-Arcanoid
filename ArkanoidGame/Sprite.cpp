#include "Sprite.h"
#include "GameSettings.h"

#include "LevelObject.h"
#include "Ball.h"

namespace Arcanoid
{
	void InitSprite(sf::Sprite& sprite, float desiredWidth, float desiredHeight, const sf::Texture& texture)
	{
		sprite.setTexture(texture);
		SetSpriteRelativeOrigin(sprite, 0.5f, 0.5f);
		SetSpriteSize(sprite, desiredWidth, desiredHeight);
	}

	void DrawSprite(const sf::Sprite& sprite, sf::RenderWindow& window)
	{
		window.draw(sprite);
	}

	sf::Vector2f GetRandomSpritePositionInRectangle(const sf::Sprite& sprite, const sf::FloatRect& rect)
	{
		sf::Vector2f result;
		const auto spriteWidth = sprite.getGlobalBounds().width;
		const auto spriteHeight = sprite.getGlobalBounds().height;
		result.x = rand() / (float)RAND_MAX * (rect.width - 2 * spriteWidth) + rect.left + spriteWidth;
		result.y = rand() / (float)RAND_MAX * (rect.height - 2 * spriteHeight) + rect.top + spriteHeight;
		return result;
	}

	void SetSpriteSize(sf::Sprite& sprite, float desiredWidth, float desiredHeight)
	{
		sf::FloatRect spriteRect = sprite.getGlobalBounds();
		sf::Vector2f scale = { desiredWidth / spriteRect.width, desiredHeight / spriteRect.height };
		sprite.setScale(scale);
	}

	void SetSpriteRelativeOrigin(sf::Sprite& sprite, float originX, float originY)
	{
		sf::FloatRect spriteRect = sprite.getLocalBounds();
		sprite.setOrigin(originX * spriteRect.width, originY * spriteRect.height);
	}

	void SetSpriteRandomPosition(sf::Sprite& sprite, const sf::FloatRect& rect, const std::list<sf::Sprite>& collection)
	{
		do {
			const auto newPosition = GetRandomSpritePositionInRectangle(sprite, rect);
			sprite.setPosition(newPosition);
		} while (FullCheckCollisions(collection.begin(), collection.end(), sprite));
	}

	bool CheckSpriteIntersection(const sf::Sprite& sprite1, const sf::Sprite& sprite2) {
		const auto distance = sprite1.getPosition() - sprite2.getPosition();
		if (sqrtf(distance.x * distance.x + distance.y * distance.y) * 2 < sprite1.getGlobalBounds().width + sprite2.getGlobalBounds().width) {
			return true;
		}
		return false;
	}

	bool CheckSpriteIntersectionWithBorders(sf::FloatRect SpriteRect)
	{
		if (SpriteRect.left < 0 or SpriteRect.left + SpriteRect.width > SCREEN_WIDTH or SpriteRect.top < 0 or SpriteRect.top + SpriteRect.height > SCREEN_HEGHT)
			return true;
		else
			return false;
	}

	bool CheckCollisionWithBall(LevelObject& object, Ball& ball)
	{
		sf::FloatRect ObjectRect = object.GetBounds();
		sf::Vector2f BallPos = ball.GetPosition();
		float BallRadius = ball.GetRadius();

		float ClosestX = std::max(ObjectRect.left, std::min(BallPos.x, ObjectRect.left + ObjectRect.width));
		float ClosestY = std::max(ObjectRect.top, std::min(BallPos.y, ObjectRect.top + ObjectRect.height));

		float DeltaX = BallPos.x - ClosestX;
		float DeltaY = BallPos.y - ClosestY;

		// Корень - дорогая операция, поэтому я оставил в квадратах
		float Distance = DeltaX * DeltaX + DeltaY * DeltaY;
		return Distance <= BallRadius * BallRadius;
	}

	EAxis GetCollisionAxis(LevelObject& object, Ball& ball)
	{
		sf::FloatRect ObjectRect = object.GetBounds();
		sf::Vector2f BallPos = ball.GetPosition();
		float BallRadius = ball.GetRadius();

		float ClosestX = std::max(ObjectRect.left, std::min(BallPos.x, ObjectRect.left + ObjectRect.width));
		float ClosestY = std::max(ObjectRect.top, std::min(BallPos.y, ObjectRect.top + ObjectRect.height));
			
		sf::Vector2f Distance = BallPos - sf::Vector2f(ClosestX, ClosestY);

		return (std::abs(Distance.x) > std::abs(Distance.y)) ? EAxis::XAxis : EAxis::YAxis;
	}

	sf::Color GetRandomColor()
	{
		int r, g, b;
		r = rand() % 256;
		g = rand() % 256;
		b = rand() % 256;

		return sf::Color(r, g, b);
	}

	sf::Color GetRandomColorWithTransparency()
	{
		int r, g, b;
		r = rand() % 246 + 10;
		g = rand() % 246 + 10;
		b = rand() % 246 + 10;

		return sf::Color(r, g, b, 200);
	}

	sf::Vector2f GetVectorBetweenSprites(const sf::Sprite& spriteFrom, const sf::Sprite& spriteTo) {
		const auto result = spriteTo.getPosition() - spriteFrom.getPosition();
		return result;
	}

	float GetManhattanDistanceBetweenSprites(const sf::Sprite& spriteFrom, const sf::Sprite& spriteTo) {
		const auto result = spriteTo.getPosition() - spriteFrom.getPosition();
		return std::fabs(result.x) + std::fabs(result.y);
	}
}
