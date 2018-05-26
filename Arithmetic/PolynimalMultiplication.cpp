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
#include <bits/stdc++.h>

const long double PI{ 3.14159265358979323846264338328L };

typedef std::complex<double> Complex;
//typedef std::complex<long double> Complex;
typedef std::valarray<Complex> CArray;

using namespace std;

//https://www.geeksforgeeks.org/fast-io-for-competitive-programming/
template<typename T>
void fastScan(T &number) {
    //variable to indicate sign of input number
    bool negative = false;
    register T c;

    number = 0;

    // extract current character from buffer
    c = getchar_unlocked();
    while (!(c == '-' || (c > 47 && c < 58)))
        c = getchar_unlocked();

    if (c == '-')
    {
        // number is negative
        negative = true;

        // extract the next character from the buffer
        c = getchar_unlocked();
    }

    // Keep on extracting characters if they are integers
    // i.e ASCII Value lies from '0'(48) to '9' (57)
    for (; (c>47 && c<58); c = getchar_unlocked())
        number = number * 10 + c - 48;

    // if scanned input has a negative sign, negate the
    // value of the input number
    if (negative)
        number *= -1;
}

//https://rosettacode.org/wiki/Fast_Fourier_transform#C.2B.2B
// Cooley-Tukey FFT (in-place, breadth-first, decimation-in-frequency)
// Better optimized but less intuitive
void fft(CArray &x)
{
    // DFT
    unsigned int N( x.size()), k( N ), n;
    long double thetaT{ PI / N };
    Complex phiT(cos(thetaT), -sin(thetaT)), T;
    unsigned int a;
    unsigned int l;
    unsigned int b;
    Complex t;
    while (k > 1)
    {
        n = k;
        k >>= 1;
        phiT *= phiT;
        T = 1.0L;
        for (l = 0; l < k; ++l)
        {
            for (a = l; a < N; a += n)
            {
                b = a + k;
                t = x[a] - x[b];
                x[a] += x[b];
                x[b] = t * T;
            }
            T *= phiT;
        }
    }
    // Decimate
    unsigned int m(log2(N));
    for (a = 0; a < N; ++a) {
        b = a;
        // Reverse bits
        b = (((b & 0xaaaaaaaa) >> 1) | ((b & 0x55555555) << 1));
        b = (((b & 0xcccccccc) >> 2) | ((b & 0x33333333) << 2));
        b = (((b & 0xf0f0f0f0) >> 4) | ((b & 0x0f0f0f0f) << 4));
        b = (((b & 0xff00ff00) >> 8) | ((b & 0x00ff00ff) << 8));
        b = ((b >> 16) | (b << 16)) >> (32 - m);
        if (b > a)
        {
            swap(x[a], x[b]);
        }
    }
}

//https://rosettacode.org/wiki/Fast_Fourier_transform#C.2B.2B
// inverse fft (in-place)
void ifft(CArray& x)
{
    // conjugate the complex numbers
    for (size_t i{ 0 }; i < x.size(); ++i)
        x[i] = conj(x[i]);
    //x = x.apply(std::conj);

    // forward fft
    fft(x);

    // conjugate the complex numbers again
    for (size_t i{ 0 }; i < x.size(); ++i)
        x[i] = conj(x[i]);
    //x = x.apply(std::conj);

    // scale the numbers
    x /= x.size();
}

//Was going to extend this with addition and some optimizations for reusing polynoms
//But it's not needed for the lab so...
class Poly {
public:

    Poly(CArray & coef) : _coef(&coef) {}

    Poly& operator*=(Poly&& o) {
        _size = _coef->size() + o._coef->size();
        size_t s{ 1 };
        while (s < _size) s <<= 1;
        --_size;

        {
            //Pad with 0
            CArray tmp(*_coef);
            _coef->resize(s);
            copy(begin(tmp), end(tmp), begin(*_coef));
        }

        fft(*_coef);

        {
            //Pad with 0
            //This should be done with a temp array
            //But as we wont reuse polynoms for the example....
            CArray tmp(*o._coef);
            o._coef->resize(s);
            copy(begin(tmp), end(tmp), begin(*o._coef));

        }

        fft(*o._coef);


        for (size_t i{ 0 }; i < s; ++i)
            _coef->operator[](i) *= o._coef->operator[](i);

        ifft(*_coef);

        return *this;
    }

    void print() {
        string s{ "" };
        printf("%lu\n", (_size - 1));
        for (size_t i{ 0 }; i < _size; ++i) {
            printf("%.0f ", _coef->operator[](i).real());
        }
        printf("\n");
    }

private:
    size_t _size;
    CArray* _coef;
};

int main() {

    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);

    size_t T;
    size_t n;
    size_t i;
    long long c;

    CArray a1;
    CArray a2;
    fastScan(T);
    ++T;
    while (--T) {
        fastScan(n);
        ++n;
        a1.resize(n);
        for (i = 0; i < n; ++i) {
            fastScan(c);
            a1[i] = c;
        }

        fastScan(n);
        ++n;
        a2.resize(n);
        for (i = 0; i < n; ++i) {
            fastScan(c);
            a2[i] = c;
        }

        Poly p1(a1);
        p1 *= Poly(a2);

        p1.print();
    }

    return 0;
}