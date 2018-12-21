//Leif Eriksson
//leier318
#include <iostream>
#include <vector>
#include <algorithm>
#include <cmath>
#include <random>
#include <tuple>
#include <string>
#include <functional>
#include <queue>
#include <set>
#include <unordered_set>
#include <unordered_map>
#include <iterator>
#include <sstream>
#include <map>
#include <bitset>
#include <stack>
#include <complex>
#include <iomanip>
#include <fstream>

using namespace std;

#define _UNLOCKED 1
#if _UNLOCKED
#define gc() getchar_unlocked()
#else
#define gc() getchar()
#endif

//https://www.geeksforgeeks.org/fast-io-for-competitive-programming/
template<typename T>
void fastScan(T &number) {
	//variable to indicate sign of input number
	bool negative{ false };
	register T c;

	number = 0;

	// extract current character from buffer
	c = gc();
	while (!(c == '-' || (c > 47 && c < 58)))
		c = gc();

	if (c == '-') {
		// number is negative
		negative = true;

		// extract the next character from the buffer
		c = gc();
	}

	// Keep on extracting characters if they are integers
	// i.e ASCII Value lies from '0'(48) to '9' (57)
	for (; (c>47 && c<58); c = gc())
		number = number * 10 + c - 48;

	// if scanned input has a negative sign, negate the
	// value of the input number
	if (negative)
		number *= -1;
}


int gcd(int a, int b) {
	if (a < b)
		swap(a, b);
	int c;
	while (b != 0) {
		c = b;
		b = a % b;
		a = c;
	}
	return a;
}

class Point {
public:
	int x, y;

	Point() {}
	Point(int x, int y) : x(x), y(y) {}

	bool operator==(const Point& o) const {
		return abs(x - o.x) < 0.000000001 && abs(y - o.y) <  0.000000001;
	}

	bool operator!=(const Point& o) const {
		return !operator==(o);
	}

	template<typename K>
	Point& operator*(const K& o) {
		x *= o;
		y *= o;
		return *this;
	}

	template<typename K>
	Point& operator/(const K& o) {
		K t{ 1.0 / o };
		return operator*(t);
	}

	Point& operator+(const Point& o) {
		x += o.x;
		y += o.y;
		return *this;
	}

	Point& operator-(const Point& o) {
		x -= o.x;
		y -= o.y;
		return *this;
	}

	long double dist(const Point& o) const {
		long double tx(x - o.x);
		long double ty(y - o.y);
		return sqrt(tx * tx + ty * ty);
	}

	long double crossProduct(const Point& o) const {
		return x * o.y - y * o.x;
	}

	long double scalarProduct(const Point& o) const {
		return x * o.x + y * o.y;
	}

	long double angl(const Point& o) const {
		return atan2(x - o.x, y - o.y);
	}

	pair<int, int> getSlope(const Point& o) const {
		int dy(y - o.y);
		int dx(x - o.x);
		if ((dy < 0 && dx < 0) || (dy > 0 && dx < 0)) {
			dy = -dy;
			dx = -dx;
		}
		int g{ gcd(abs(dy),abs(dx)) };
		//cout << dy << " " << dx << " " << g << "\n";
		return { dy / g, dx / g };
	}
};

// Three points are a counter - clockwise turn if ccw > 0, clockwise if
// ccw < 0, and collinear if ccw = 0 because ccw is a determinant that
// gives twice the signed  area of the triangle formed by p1, p2 and p3.
int ccw(const Point & p1, const Point & p2, const Point & p3) {
	return (p2.x - p1.x)*(p3.y - p1.y) - (p2.y - p1.y)*(p3.x - p1.x);
}

deque<int> convexHull_grahamScan(vector<Point> &p) {

	//let N be number of points
	size_t N{ p.size() };

	if (N <= 2) {
		if (N <= 1 || p[0] == p[1])
			return { 0 };
		return { 0,1 };
	}

	//let points[N] be the array of points

	//swap points[0] with the point with the lowest y - coordinate
	Point min{ p[0] };
	int m{ 0 }, i;

	sort(p.begin(), p.end(), [](const Point& l, const Point& r)->bool {return l.y < r.y || (l.y == r.y && l.x < r.x); });


	//sort points by polar angle with points[0]
	vector<pair<double, int>> v(N - 1);

	for (i = 1; i < N; ++i)
		v[i - 1] = { p[i] != p[0] ? atan2(p[i].y - p[0].y, p[i].x - p[0].x) : -100, i };

	stable_sort(v.begin(), v.end());

	v.emplace_back(0, 0);

	//printf("1add %d %d\n", p[0].x, p[0].y);
	//let stack = NULL
	deque<int> s{ 0 };
	//push points[0] to stack
	//push points[1] to stack
	//push points[2] to stack
	//s.push_back(0);
	i = 0;
	while (i < N - 1 && p[0] == p[v[i].second]) ++i;
	if (i == N - 1)
		return s;
	//printf("2add %d %d\n", p[v[i].second].x, p[v[i].second].y);
	s.push_back(v[i].second);
	++i;
	while (i < N - 1 && p[s.back()] == p[v[i].second]) ++i;
	if (i == N - 1)
		return s;
	int top{ v[i].second };
	++i;
	while (i < N - 1 && ccw(p[0], p[s.back()], p[top]) == 0) {
		//printf("swap %d %d %d %d\n", p[s.back()].x, p[s.back()].y, p[top].x, p[top].y);
		s.back() = top;
		top = v[i].second;
		++i;
	}
	for (; i < N - 1; ++i) {
		while (!s.empty() && ccw(p[s.back()], p[top], p[v[i].second]) <= 0) {
			top = s.back();
			s.pop_back();
			//printf("remove %d %d\n", p[top].x, p[top].y);
		}
		//if (p[v[i].second] != p[top]) {
		//printf("3add %d %d\n", p[top].x, p[top].y);
		s.push_back(top);
		top = v[i].second;
		//}
	}
	if ((p[0] != p[top]) && ccw(p[s.back()], p[top], p[0]) >= 0) {
		//printf("4add %d %d\n", p[top].x, p[top].y);
		if ((p[0] != p[top]) && ccw(p[s.back()], p[top], p[0]) > 0) {
			s.push_back(top);
		}
		else
			s.back() = top;
	}
	return s;
}

int main() {
	ios::sync_with_stdio(false);
	cout.tie(nullptr);
	cin.tie(nullptr);

	int n, m, x1, x2, x3, x4, y1, y2, y3, y4, i;
	vector<Point> p;

	while (true) {
		fastScan(n);
		if (n == 0)
			break;
		p.resize(n);
		for (i = 0; i < n; ++i) {
			fastScan(p[i].x);
			fastScan(p[i].y);
		}
		auto r{ convexHull_grahamScan(p) };
		printf("%zu\n", r.size());
		for (auto &a : r) {
			printf("%d %d\n", p[a].x, p[a].y);
		}
	}

	return 0;
}