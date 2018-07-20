#include <utility>

template <typename T>
T gcd(T a, T b) {
	if (a < b)
		std::swap(a, b);
	T c;
	while (b != 0) {
		c = b;
		b = a % b;
		a = c;
	}
	return a;
}