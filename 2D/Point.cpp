
#include <cmath>
#include "Number Theory\GCD.cpp"

template <typename T = long double>
class Point;

template <typename T = long double>
bool operator<(const Point<T>& lhs, const Point<T>& rhs);
template <typename T = long double>
bool compY(const Point<T>& lhs, const Point<T>& rhs);

template<typename T>
class Point {
	friend bool operator< <T>(const Point<T>& lhs, const Point<T>& rhs);
	friend bool compY<T>(const Point<T>& lhs, const Point<T>& rhs);
public:
	T x, y;

	Point() {}
	Point(T x, T y) : x(x), y(y) {}

	bool operator==(const Point<T>& o) const {
		return std::abs(x - o.x) < _DELTA && std::abs(y - o.y) < _DELTA;
	}

	bool operator<=(const Point<T>& o) const {
		return operator==(o) || *this < o;
	}

	bool operator!=(const Point<T>& o) const {
		return !operator==(o);
	}

	template<typename K>
	Point<T>& operator*(const K& o) {
		x *= o;
		y *= o;
		return *this;
	}

	template<typename K>
	Point<T>& operator/(const K& o) {
		K t{ 1.0 / o };
		return operator*(t);
	}

	Point<T>& operator+(const Point<T>& o) {
		x += o.x;
		y += o.y;
		return *this;
	}

	Point<T>& operator-(const Point<T>& o) {
		x -= o.x;
		y -= o.y;
		return *this;
	}

	T dist(const Point<T>& o) const {
		T tx(x - o.x);
		T ty(y - o.y);
		return std::sqrt(tx*tx + ty * ty);
	}

	T sDist(const Point<T>& o) const {
		T tx(x - o.x);
		T ty(y - o.y);
		return tx * tx + ty * ty;
	}

	T crossProduct(const Point<T>& o) const {
		return x * o.y - y * o.x;
	}

	T scalarProduct(const Point<T>& o) const {
		return x * o.x + y * o.y;
	}

	T angl(const Point<T>& o) const {
		return std::atan2(x - o.x, y - o.y);
	}

	template <typename I = long long>
	std::pair<I, I> getSlope(const Point<T>& o) const {
        //Get the slope of two points
        //Recommended to not use with non-intereger points
		I dy(y - o.y);
		I dx(x - o.x);
		if ((dy < 0 && dx < 0) || (dy > 0 && dx < 0)) {
			dy = -dy;
			dx = -dx;
		}
		I g{ gcd(std::abs(dy),dx) };
		return { dy / g, dx / g };
	}

private:
	const static long double _DELTA;
};

template <typename T>
const long double Point<T>::_DELTA{ 0.000000001 };

template <typename T>
bool operator<(const Point<T>& lhs, const Point<T>& rhs) {
	return lhs.x < rhs.x || (std::abs(lhs.x - rhs.x) < Point<T>::_DELTA && lhs.y < rhs.y);
}

template <typename T>
bool compY(const Point<T>& lhs, const Point<T>& rhs) {
	return lhs.y < rhs.y || (std::abs(lhs.y - rhs.y) < Point<T>::_DELTA && lhs.x < rhs.x);
}