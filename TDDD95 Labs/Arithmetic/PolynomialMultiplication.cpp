//https://liu.kattis.com/problems/polymul2
//Leif Eriksson
//leier318
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
#include <complex>
#include <valarray>
#include "Implementations\FastScan.cpp"
#include "Arithmetic\Polynom.cpp"

using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);

    size_t T;
    size_t n;
    size_t i;
    long long c;

	std::valarray<std::complex<double>> a1;
	std::valarray<std::complex<double>> a2;
    fs(T);
    ++T;
    while (--T) {
        fs(n);
        ++n;
        a1.resize(n);
        for (i = 0; i < n; ++i) {
			fsnd(c);
            a1[i] = c;
        }

		fs(n);
        ++n;
        a2.resize(n);
        for (i = 0; i < n; ++i) {
			fsnd(c);
            a2[i] = c;
        }

		Poly<double> p1(a1);
		p1 *= Poly<double>(a2);

        p1.print();
    }

    return 0;
}