//Leif Eriksson
//leier318
//https://open.kattis.com/problems/linearrecurrence
//http://fusharblog.com/solving-linear-recurrence-for-programming-contest/
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

#ifndef _UNLOCKED
#define _UNLOCKED 1
#if _UNLOCKED
#define gc() getchar_unlocked()
#else
#define gc() getchar()
#endif
#endif


template<typename T>
inline void first(T &number, T& c) {
	number = 0;
	// extract current character from buffer
	c = gc();
	while (!(c > 47 && c < 58))
		c = gc();
}

template<typename T>
inline void set_negative(T& c, bool& negative) {
	if (c == '-') {
		// number is negative
		negative = true;

		// extract the next character from the buffer
		c = gc();
	}
}

template<typename T>
inline void first_negative(T &number, T& c, bool& negative) {
	number = 0;
	// extract current character from buffer
	c = gc();
	while (!(c == '-' || (c > 47 && c < 58)))
		c = gc();

	set_negative(c, negative);
}

template<typename T>
inline bool first_bool(T &number, T& c) {
	number = 0;
	// extract current character from buffer
	c = gc();
	while (!(c == EOF || (c > 47 && c < 58)))
		c = gc();

	return c != EOF;
}

template<typename T>
inline bool first_negative_bool(T &number, T& c, bool& negative) {
	number = 0;
	// extract current character from buffer
	c = gc();
	while (!(c == '-' || c == EOF || (c > 47 && c < 58)))
		c = gc();

	set_negative(c, negative);

	return c != EOF;
}

template<typename T>
inline void loop(T &number, T& c) {
	// Keep on extracting characters if they are integers
	// i.e ASCII Value lies from '0'(48) to '9' (57)
	for (; (c>47 && c<58); c = gc())
		number = number * 10 + c - 48;
}

template<typename T>
inline void decimal(T &number, T& c) {
	if (c == '.') {
		c = gc();
		for (T pot(0.1); (c>47 && c<58); c = gc(), pot *= 0.1)
			number += (c - 48)*pot;
	}
}

template<typename T>
inline void end_negative(T &number, bool& negative) {
	// if scanned input has a negative sign, negate the
	// value of the input number
	if (negative)
		number *= -1;
}


template<typename T>
void fsnd(T &number) {
	//variable to indicate sign of input number
	bool negative{ false };
	register T c;

	first_negative(number, c, negative);
	loop(number, c);
	decimal(number, c);
	end_negative(number, negative);
}


template<typename T>
char fsndc(T &number) {
	//variable to indicate sign of input number
	bool negative{ false };
	register T c;

	first_negative(number, c, negative);
	loop(number, c);
	decimal(number, c);
	end_negative(number, negative);
	return c;
}

template<typename T>
bool fsndb(T &number) {
	//variable to indicate sign of input number
	bool negative{ false };
	register T c;

	if (!first_negative_bool(number, c, negative))
		return false;
	loop(number, c);
	decimal(number, c);
	end_negative(number, negative);
	return true;
}


template<typename T>
void fsd(T &number) {
	register T c;

	first(number, c);
	loop(number, c);
	decimal(number, c);
}


template<typename T>
char fsdc(T &number) {
	register T c;

	first(number, c);
	loop(number, c);
	decimal(number, c);
	return c;
}

template<typename T>
void fs(T &number) {
	register T c;

	first(number, c);
	loop(number, c);
}


template<typename T>
char fsc(T &number) {
	register T c;

	first(number, c);
	loop(number, c);
	return c;
}

template<typename T>
char fsb(T &number) {
	register T c;

	if (!first_bool(number, c))
		return false;
	loop(number, c);
	return true;
}

template<typename T>
void fsn(T &number) {
	//variable to indicate sign of input number
	bool negative{ false };
	register T c;

	first_negative(number, c, negative);
	loop(number, c);
	end_negative(number, negative);
}


template<typename T>
char fsnc(T &number) {
	//variable to indicate sign of input number
	bool negative{ false };
	register T c;

	first_negative(number, c, negative);
	loop(number, c);
	end_negative(number, negative);
	return c;
}

template<typename T>
bool fsnb(T &number) {
	//variable to indicate sign of input number
	bool negative{ false };
	register T c;

	if (!first_negative_bool(number, c, negative))
		return false;
	loop(number, c);
	end_negative(number, negative);
	return true;
}

using namespace std;

vector<vector<long long>>
matMul
(const vector<vector<long long>> &a, const vector<vector<long long>> &b, long long m) {
	size_t i(0), j, k;
	const size_t N(a.size());
	vector<vector<long long>> c(N, vector<long long>(N, 0));
	for (; i < N - 1; ++i) {
		for (j = 0; j < N; ++j)
			for (k = 0; k < N - 1; ++k)
				c[i][j] = (c[i][j] + a[i][k] * b[k][j]) % m;
		c[i][N - 1] = (c[i][N - 1] + a[i][N - 1] * b[N - 1][N - 1]) % m;
	}

	c[N - 1][N - 1] = 1;
	return c;
}

vector<vector<long long>>
matPow(const vector<vector<long long>> &a, long long p, long long m) {
	if (p <= 1)
		return a;
	if (p % 2 == 1)
		return matMul(a, matPow(matMul(a, a, m), p / 2, m), m);
	return matPow(matMul(a, a, m), p / 2, m);
}


int main() {
	ios::sync_with_stdio(false);
	cout.tie(nullptr);
	cin.tie(nullptr);

	unsigned int N, Q;
	long long t, M;
	long long s;
	size_t i(0);

	fs(N);
	++N;
	vector<long long> f(N);
	vector<vector<long long>> T(N, vector<long long>(N, 0));
	fsn(f[--N]);
	for (; i < N; ++i) {
		T[i][i + 1] = 1;
		fsn(T[N - 1][N - 1 - i]);
	}
	T[N][N] = 1;

	for (i = 0; i < N; ++i)
		fsn(f[i]);

	fs(Q);
	++N;
	++Q;
	copy(f.begin(), f.end(), std::ostream_iterator<long long>(cout, " "));
	cout << "\n\n";
	for (i = 0; i < N; ++i) {
		copy(T[i].begin(), T[i].end(), std::ostream_iterator<long long>(cout, " "));
		cout << "\n";
	}
	cout << "\n";
	while (--Q) {
		fs(t);
		fs(M);
		if (t < N - 1) {
			printf("%lld\n", f[t] % M);
		}
		else {
			vector<vector<long long>> nt(matPow(T, t + 2 - N, M));
			for (i = 0; i < N; ++i) {
				copy(nt[i].begin(), nt[i].end(), std::ostream_iterator<long long>(cout, " "));
				cout << "\n";
			}
			cout << "\n";
			s = 0;
			for (i = 0; i < N; ++i) {
				s = (s + nt[N - 2][i] * f[i]) % M;
			}
			printf("%lld\n", (s + M) % M);
		}
	}

	system("Pause");
	return 0;
}

/*
2
5 7 9
36713 5637282
10
1 10000
1375 1
3781 23
34683447233 1571385

*/