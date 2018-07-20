//Leif Eriksson
#include <vector>
#include <algorithm>
#include <cmath>
#include "2D\Point.cpp"

template <typename T = long long>
size_t number_of_colinear(const std::vector<Point> & v) {
	std::vector<std::pair<T, T>> m(v.size());
	size_t maxN{ 1 };
	size_t i{ 0 }, j;
	size_t c;
	std::pair<T, T> l;
	if (v.size() == 1)
		return 1;
	for (; i < v.size() - maxN; ++i) {
		for (j = i + 1; j < v.size(); ++j) 
			m[j - i - 1] = v[i].template getSlope<T>(v[j]);

		std::sort(m.begin(), m.begin() + v.size() - i - 1);
		l = m[0];
		c = 2;
		for (j = 1; j < v.size() - i - 1 - std::min((maxN - c), size_t{ 0 }); ++j) {
			if (m[j] == l)
				++c;
			else {
				if (c > maxN)
					maxN = c;
				c = 2;
				l = m[j];
			}
		}
		if (c > maxN)
			maxN = c;
	}
	return maxN;
}
