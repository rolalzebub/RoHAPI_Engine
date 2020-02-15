#pragma once

namespace RoHAPI {

	template <typename T>
	inline T Clamp(T value, T max, T min)
	{
		if (value > max)
			return max;
		if (value < min)
			return min;

		return value;
	}

	template <typename T>
	inline T Rad2Deg(T rad)
	{
		return (T)(rad * (180 / PI));
	}

	template <typename T>
	inline T Deg2Rad(T deg)
	{
		return (T)(deg * (PI / 180));
	}


	template <typename T>
	inline T lerp(T a, T b, float s)
	{
		return a + (b - a) * s;
	}

#define MAX(a,b) a>b? a: b;
#define MIN(a,b) a<b? a: b;

#define Vec2 Vector2

	// Templatised Vector 2 class
	template <typename T>
	class Vector2
	{
	public:
		//Constructors
		Vector2<T>() : x(0), y(0) {};
		Vector2<T>(T ix) : x(ix), y(ix) {};
		Vector2<T>(T ix, T iy) : x(ix), y(iy) {};

		inline T Length()
		{
			return sqrt(x * x + y * y);
		}

		inline Vec2<T> Normalize()
		{
			Vec2<T> vector;
			T length = Length();

			if (length != 0)
			{
				vector.x = x / length;
				vector.y = y / length;
			}

			return vector;
		}

		//Operator overloads
		Vec2<T> operator=(const Vec2<T>& rhs)
		{
			x = rhs.x;
			y = rhs.y;
			return *this;
		}

		Vec2<T> operator+=(const Vec2<T>& rhs)
		{
			x += rhs.x;
			y += rhs.y;
			return *this;
		}

		Vec2<T> operator-=(const Vec2<T>& rhs)
		{
			x -= rhs.x;
			y -= rhs.y;
			return *this;
		}

		Vec2<T> operator*=(const Vec2<T>& rhs)
		{
			x *= rhs.x;
			y *= rhs.y;
			return *this;
		}

		Vec2<T> operator/=(const Vec2<T>& rhs)
		{
			x /= rhs.x;
			y /= rhs.y;
			return *this;
		}

		Vec2<T> operator-(const Vec2<T>& rhs)
		{
			return Vec2<T>(x - rhs.x, y - rhs.y);
		}

		Vec2<T> operator+(const Vec2<T>& rhs)
		{
			return Vec2<T>(x + rhs.x, y + rhs.y);
		}

		Vec2<T> operator*(const Vec2<T>& rhs)
		{
			return Vec2<T>(x * rhs.x, y * rhs.y);
		}

		Vec2<T> operator/(const Vec2<T>& rhs)
		{
			return Vec2<T>(x / rhs.x, y / rhs.y);
		}

		// versions of vec2 variables
		union {
			struct {
				T x, y;
			};
			struct {
				T r, g;
			};
			struct
			{
				T width, height;
			};
			struct
			{
				T start, end;
			};
		};
	};

	//Common types
#define Vec2i Vec2<int>
#define Vec2d Vec2<double>
#define Vec2f Vec2<float>
#define Vec2ui Vec2<unsigned int>

	template <typename T>
	T Distance(const Vec2<T>& p1, const Vec2<T>& p2)
	{
		T dx = p2.x - p1.x;
		T dy = p2.y - p1.y;

		return (T)sqrt((T)(dx * dx + dy * dy));
	}

	enum RectStates
	{
		Overlaps,
		Encapsulated,
		Surrounds,
		Separated
	};
	struct Vec4d {
		double top;
		double bottom;
		double left;
		double right;
	};
	class Rect
	{
	private:
		double top, bottom, left, right;
	public:
		Rect(Vec2i size) { top = 0; bottom = size.y; left = 0; right = size.x; }
		Rect() { top = 0; bottom = 0; left = 0; right = 0; }
		Rect(double top_, double bottom_, double left_, double right_) :
			top(top_), bottom(bottom_), left(left_), right(right_) {}
		~Rect() {}

		double Width() const
		{
			return right - left;
		}

		double Height() const
		{
			return bottom - top;
		}

		Rect* GetRect() { return this; };

		RectStates CheckState(const Rect& other) {
			if (right < other.right &&
				left > other.left&&
				top > other.top&&
				bottom < other.bottom)
			{
				return RectStates::Encapsulated;
			}
			else if (right > other.right&&
				left < other.left &&
				top < other.top &&
				bottom > other.bottom)
			{
				return RectStates::Surrounds;
			}
			else if (right > other.left ||
				left < other.right ||
				top < other.bottom ||
				bottom > other.top)
			{
				return RectStates::Separated;
			}
			else
				return RectStates::Overlaps;
		}

		RectStates CheckState(const Vec2i& pos)
		{
			if (right > pos.x&& left < pos.x && top > pos.y&& bottom < pos.y)
				return RectStates::Encapsulated;
			else
				return RectStates::Separated;
		}

		Vec4d GetRectDims() { return Vec4d{ top, bottom, left, right }; };

		void Translate(int x, int y)
		{
			left += x;
			right += x;
			top += y;
			bottom += y;
		}

		bool Intersects(const Rect& other)
		{
			/*if (left > other.right || right<other.left || top > other.bottom || bottom < other.top)
				return false;
			return true;*/

			if ((top > other.bottom) ||			//check for completely outside along y-axis
				bottom < other.top)
				return false;

			if (left > other.right ||		//check for completely outside along x-axis
				right < other.left)
				return false;

			if ((other.top >= top &&												//check for intersection along y-axis
				other.top <= bottom) ||
				(other.bottom >= top &&
					other.bottom <= bottom))
			{
				if ((other.left >= left &&
					other.left <= right) ||								//check for intersection along x-axis
					(other.right >= left &&
						other.right <= right)) {
					return true;
				}
			}
		}

		template<typename T>
		bool InsideBounds(Vector2<T> point)
		{
			if (point.x > left&& point.x < right
				&& point.y > top&& point.y < bottom)
				return true;

			return false;
		}

	};
}

