//Leif Eriksson
#include <iostream>
#include <vector>
#include <algorithm>
#include <cmath>
#include <random>
#include <iterator>
#include <tuple>
#include <string>
#include <functional>
#include <queue>
#include <set>
#include <unordered_set>
#include <iterator>
#include <sstream>
#include <map>
#include <bitset>
#include <list>

using namespace std;

template<typename T>
void fastFill(T* v, const T& x, size_t n) {
	if (n == 0)
		return;
	size_t s(1);
	*v = x;
	while (s + s <= n) {
		memcpy((v + s), v, s * sizeof(x));
		s += s;
	}
	memcpy((v + s), v, (n - s) * sizeof(x));
}

struct myBitset {
	myBitset(size_t s, bool val = false) : _trueSize{ s }, _s((s >> 3) + bool(s & 7)), _v(_s, 255 * val) {
		//_v = new char[_s];
		//fastFill(_v, (char)(255 * val), _s);
	}

	bool inline operator[] (size_t index) const {
		return _v[index >> 3] & _c[index & 7];
	}

	void inline set(size_t index, bool val) {
		if (val) {
			_v[index >> 3] |= _c[index & 7];
		}
		else {
			_v[index >> 3] &= _n[index & 7];
		}
	}

	void inline flip(size_t index) {
		set(index, !(_v[index >> 3] & _c[index & 7]));
	}

	size_t count() const {
		return count(0, _trueSize);
	}

	size_t count(const size_t from, const size_t to) const {
		const size_t _to((to >> 3) + bool(to & 7));
		size_t nr{ 0 }, i;
		for (size_t i{ from >> 3 }; i < _to; ++i) {
			nr += (((_v[i] & 1) + ((_v[i] & 2) >> 1)) + (((_v[i] & 4) >> 2) + ((_v[i] & 8) >> 3))) +
				((((_v[i] & 16) >> 4) + ((_v[i] & 32) >> 5)) + (((_v[i] & 64) >> 6) + ((_v[i] & 128) >> 7)));
		}
		for (i = from - (from & 7); i < from; ++i)
			nr -= operator[](i);
		for (i = to; i < _to << 3; ++i)
			nr -= operator[](i);
		return nr;
	}

	//~myBitset() {
	//    delete[] _v;
	//}

	const static vector<char> _c;
	const static vector<char> _n;
	const size_t _trueSize;
	const size_t _s;
	vector<char> _v;
	//char *_v;
};

const vector<char> myBitset::_c{ char(1), char(2), char(4), char(8),
char(16), char(32), char(64), char(128) };
const vector<char> myBitset::_n{ char(254), char(253), char(251), char(247),
char(239), char(223), char(191), char(127) };

size_t prime_sieve(long long n, vector<long long> & prime, myBitset& p) {
	//Hur mycket jag än försöker rulla ut någon av looparna verkar det inte göra någon skillnad
	//Utan count kommer den ner på 0.13s

	//Simple klarar det på 0.16s
	//0.14s utan count

	//Bra med ~200 rader kod för 0.01s :)
	//https://liu.kattis.com/submissions/2887308

	prime.clear();
	//prime.reserve(n);
	prime.emplace_back(2);
	prime.emplace_back(3);
	prime.emplace_back(5);
	//i, j, i*2, n/2, i*i/2, (i+1)*(i+1)/2-i*i/2, n2/2
	size_t nr{ 0 };
	long long i, j, i2, nh, sqh{ 24 }, derh{ 16 }, n2h, wall, i3;

	//myBitset p(i >> 1, 1);
	p.set(0, 0);

	if (n >= 5) {
		++nr;
		if (n >= 3) {
			++nr;
			if (n >= 2)
				++nr;
		}
	}

	nh = n >> 1;
	n2h = nh - 30;
	for (i = 4; i < n2h; i += 30) {
		p.set(i, 0);
		p.set(i + 15, 0);
		p.set(i + 3, 0);
		p.set(i + 18, 0);
		p.set(i + 6, 0);
		p.set(i + 21, 0);
		p.set(i + 9, 0);
		p.set(i + 24, 0);
		p.set(i + 12, 0);
		p.set(i + 27, 0);
	}
	for (; i < nh; i += 3)
		p.set(i, 0);
	for (i = 12; i < n2h; i += 30) {
		p.set(i, 0);
		p.set(i + 20, 0);
		p.set(i + 5, 0);
		p.set(i + 25, 0);
		p.set(i + 10, 0);
		p.set(i + 15, 0);
	}
	for (; i < nh; i += 5)
		p.set(i, 0);

	n2h = (n - n % 30) >> 1;

	for (i = 3; sqh < n2h;) {
		//7
		if (p[i]) {
			i2 = (i << 1) + 1;
			prime.emplace_back(i2);
			++nr;
			i3 = i2 << 3;
			wall = nh - i3;
			for (j = sqh; j < wall; j += i3) {
				p.set(j, 0);
				p.set(j + i2, 0);
				p.set(j + (i2 << 1), 0);
				p.set(j + (i2 << 1) + i2, 0);
				p.set(j + (i2 << 2), 0);
				p.set(j + (i2 << 2) + i2, 0);
				p.set(j + i3 - (i2 << 1), 0);
				p.set(j + i3 - i2, 0);
			}
			for (; j < nh; j += i2)
				p.set(j, 0);
		}
		sqh += derh + derh + 4, derh += 8, i += 2;

		//11
		if (p[i]) {
			i2 = (i << 1) + 1;
			prime.emplace_back(i2);
			i3 = i2 << 3;
			++nr;
			wall = nh - i3;
			for (j = sqh; j < wall; j += i3) {
				p.set(j, 0);
				p.set(j + i2, 0);
				p.set(j + (i2 << 1), 0);
				p.set(j + (i2 << 1) + i2, 0);
				p.set(j + (i2 << 2), 0);
				p.set(j + (i2 << 2) + i2, 0);
				p.set(j + i3 - (i2 << 1), 0);
				p.set(j + i3 - i2, 0);
			}
			for (; j < nh; j += i2)
				p.set(j, 0);
		}
		sqh += derh, derh += 4, ++i;

		//13
		if (p[i]) {
			i2 = (i << 1) + 1;
			prime.emplace_back(i2);
			i3 = i2 << 3;
			++nr;
			wall = nh - i3;
			for (j = sqh; j < wall; j += i3) {
				p.set(j, 0);
				p.set(j + i2, 0);
				p.set(j + (i2 << 1), 0);
				p.set(j + (i2 << 1) + i2, 0);
				p.set(j + (i2 << 2), 0);
				p.set(j + (i2 << 2) + i2, 0);
				p.set(j + i3 - (i2 << 1), 0);
				p.set(j + i3 - i2, 0);
			}
			for (; j < nh; j += i2)
				p.set(j, 0);
		}
		sqh += derh + derh + 4, derh += 8, i += 2;

		//17
		if (p[i]) {
			i2 = (i << 1) + 1;
			prime.emplace_back(i2);
			i3 = i2 << 3;
			++nr;
			wall = nh - i3;
			for (j = sqh; j < wall; j += i3) {
				p.set(j, 0);
				p.set(j + i2, 0);
				p.set(j + (i2 << 1), 0);
				p.set(j + (i2 << 1) + i2, 0);
				p.set(j + (i2 << 2), 0);
				p.set(j + (i2 << 2) + i2, 0);
				p.set(j + i3 - (i2 << 1), 0);
				p.set(j + i3 - i2, 0);
			}
			for (; j < nh; j += i2)
				p.set(j, 0);
		}
		sqh += derh, derh += 4, ++i;

		//19
		if (p[i]) {
			i2 = (i << 1) + 1;
			prime.emplace_back(i2);
			i3 = i2 << 3;
			++nr;
			wall = nh - i3;
			for (j = sqh; j < wall; j += i3) {
				p.set(j, 0);
				p.set(j + i2, 0);
				p.set(j + (i2 << 1), 0);
				p.set(j + (i2 << 1) + i2, 0);
				p.set(j + (i2 << 2), 0);
				p.set(j + (i2 << 2) + i2, 0);
				p.set(j + i3 - (i2 << 1), 0);
				p.set(j + i3 - i2, 0);
			}
			for (; j < nh; j += i2)
				p.set(j, 0);
		}
		sqh += derh + derh + 4, derh += 8, i += 2;

		//23
		if (p[i]) {
			i2 = (i << 1) + 1;
			prime.emplace_back(i2);
			i3 = i2 << 3;
			++nr;
			wall = nh - i3;
			for (j = sqh; j < wall; j += i3) {
				p.set(j, 0);
				p.set(j + i2, 0);
				p.set(j + (i2 << 1), 0);
				p.set(j + (i2 << 1) + i2, 0);
				p.set(j + (i2 << 2), 0);
				p.set(j + (i2 << 2) + i2, 0);
				p.set(j + i3 - (i2 << 1), 0);
				p.set(j + i3 - i2, 0);
			}
			for (; j < nh; j += i2)
				p.set(j, 0);
		}
		sqh += derh * 3 + 12, derh += 12, i += 3;

		//29
		if (p[i]) {
			i2 = (i << 1) + 1;
			prime.emplace_back(i2);
			i3 = i2 << 3;
			++nr;
			wall = nh - i3;
			for (j = sqh; j < wall; j += i3) {
				p.set(j, 0);
				p.set(j + i2, 0);
				p.set(j + (i2 << 1), 0);
				p.set(j + (i2 << 1) + i2, 0);
				p.set(j + (i2 << 2), 0);
				p.set(j + (i2 << 2) + i2, 0);
				p.set(j + i3 - (i2 << 1), 0);
				p.set(j + i3 - i2, 0);
			}
			for (; j < nh; j += i2)
				p.set(j, 0);
		}
		sqh += derh, derh += 4, ++i;

		//31
		if (p[i]) {
			i2 = (i << 1) + 1;
			prime.emplace_back(i2);
			i3 = i2 << 3;
			++nr;
			wall = nh - i3;
			for (j = sqh; j < wall; j += i3) {
				p.set(j, 0);
				p.set(j + i2, 0);
				p.set(j + (i2 << 1), 0);
				p.set(j + (i2 << 1) + i2, 0);
				p.set(j + (i2 << 2), 0);
				p.set(j + (i2 << 2) + i2, 0);
				p.set(j + i3 - (i2 << 1), 0);
				p.set(j + i3 - i2, 0);
			}
			for (; j < nh; j += i2)
				p.set(j, 0);
		}
		sqh += derh * 3 + 12, derh += 12, i += 3;
	}

	for (; sqh < nh; sqh += derh, derh += 4, ++i)
		if (p[i]) {
			i2 = (i << 1) + 1;
			prime.emplace_back(i2);
			i3 = i2 << 3;
			++nr;
			wall = nh - i3;
			for (j = sqh; j < wall; j += i3) {
				p.set(j, 0);
				p.set(j + i2, 0);
				p.set(j + (i2 << 1), 0);
				p.set(j + (i2 << 1) + i2, 0);
				p.set(j + (i2 << 2), 0);
				p.set(j + (i2 << 2) + i2, 0);
				p.set(j + i3 - (i2 << 1), 0);
				p.set(j + i3 - i2, 0);
			}
			for (; j < nh; j += i2)
				p.set(j, 0);
		}

	i2 = (i << 1) + 1;
	long long maxx{ min(i2 - i2 % 30 + 30,n) >> 1 };

	for (; i < maxx; ++i) {
		if (p[i])
			prime.emplace_back((i << 1) + 1);
	}

	for (; i < n2h;) {
		//1
		if (p[i])
			prime.emplace_back((i << 1) + 1);
		i += 3;

		//7
		if (p[i]) {
			prime.emplace_back((i << 1) + 1);
		}
		i += 2;

		//11
		if (p[i]) {
			prime.emplace_back((i << 1) + 1);
		}
		++i;

		//13
		if (p[i]) {
			prime.emplace_back((i << 1) + 1);
		}
		i += 2;

		//17
		if (p[i]) {
			prime.emplace_back((i << 1) + 1);
		}
		++i;

		//19
		if (p[i]) {
			prime.emplace_back((i << 1) + 1);
		}
		i += 2;

		//23
		if (p[i]) {
			prime.emplace_back((i << 1) + 1);
		}
		i += 3;

		//29
		if (p[i]) {
			prime.emplace_back((i << 1) + 1);
		}
		++i;
	}

	for (; i < nh; ++i) {
		if (p[i])
			prime.emplace_back((i << 1) + 1);
	}

	return p.count(i, n >> 1) + nr;
}

int main() {
	ios::sync_with_stdio(false);
	cin.tie(nullptr);
	cout.tie(nullptr);

	long long max(999966663333);
	long long maxP(1000100);

	vector<long long> primes;

	myBitset p(maxP >> 1, 1);
	prime_sieve(maxP, primes, p);
	long long s(0);
	for (int i(0); primes[i] * primes[i] < max; ++i) {
		long long p1(primes[i]);
		long long p2(primes[i + 1]);
		//if(i % 1000 == 0)
		//	cout << " " << p1 << " " << p2 << " " << (p1*p2) << "\n";
		long long low(p1*p1);
		long long high(p2*p2);
		for (long long j(low + p1); j < high && j < max; j += p1) {
			//cout << "a " << j << "\n";
			s += j;
		}
		for (long long j(min(high - p2, max - max % p2)); j > low; j -= p2) {
			//cout << "b " << j << "\n";
			s += j;
		}
		if (p1*p2 < max) {
			//cout << "c " << (p1 * p2) << "\n";
			s -= p1 * p2 * 2;
		}
	}

	cout << s << "\n";
	system("Pause");

}