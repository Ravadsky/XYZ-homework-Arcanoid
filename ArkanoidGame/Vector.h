#pragma once

namespace Arcanoid
{
	template<typename T>
	class Vector2D
	{
	private:
		T x = (T)0;
		T y = (T)0;
	public:
		Vector2D<T> operator+(const Vector2D<T>& rhs)
		{
			return { x + rhs.x, y + rhs.y };
		}

		Vector2D<T> operator-(const Vector2D<T>& rhs)
		{
			return { x - rhs.x, y - rhs.y };
		}

		bool operator==(const Vector2D<T>& rhs)
		{
			return x == rhs.x && y == rhs.y;
		}

		inline float GetVectorLength()
		{
			return sqrtf(x * x + y * y);
		}

		template<typename U, typename V>
		U Convert(const V& v)
		{
			return { static_cast<decltype(U::x)>(v.x), static_cast<decltype(U::y)>(v.y) };
		}

	};

	using Vector2Df = Vector2D<float>;
	using Vector2Di = Vector2D<int>;
	using Position = Vector2Df;

}
