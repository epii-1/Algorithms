//Leif Eriksson

#include <complex>
#include <valarray>
#include <cmath>

template<typename T = long double>
class FurierTransform {
public:
	//https://rosettacode.org/wiki/Fast_Fourier_transform#C.2B.2B
	// Cooley-Tukey FFT (in-place, breadth-first, decimation-in-frequency)
	// Better optimized but less intuitive
	void static fft(std::valarray<std::complex<T>> &x) {
		// DFT
		unsigned int N(x.size()), k(N), n;
		T thetaT(PI / N);
		std::complex<T> phiT(cos(thetaT), -sin(thetaT)), Tt;
		unsigned int a;
		unsigned int l;
		unsigned int b;
		std::complex<T> t;
		while (k > 1) {
			n = k;
			k >>= 1;
			phiT *= phiT;
			Tt = 1.0L;
			for (l = 0; l < k; ++l) {
				for (a = l, b = l + k; a < N; a += n, b += n) {
					t = x[a] - x[b];
					x[a] += x[b];
					x[b] = t * Tt;
				}
				Tt *= phiT;
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
				swap(x[a], x[b]);
		}
	}

	//https://rosettacode.org/wiki/Fast_Fourier_transform#C.2B.2B
	// inverse fft (in-place)
	void static ifft(std::valarray<std::complex<T>>& x, bool is_real = false) {
		size_t i{ 0 };

		// conjugate the complex numbers
		for (; i < x.size(); ++i)
			x[i] = conj(x[i]);
		//x = x.apply(std::conj);

		// forward fft
		fft(x);

		// conjugate the complex numbers again
		if (!is_real)
			for (i = 0; i < x.size(); ++i)
				x[i] = conj(x[i]);
		//x = x.apply(std::conj);

		// scale the numbers
		T inv(1.0L / x.size());
		x *= inv;
	}
private:
	const static T PI;
};

template<typename T>
const T FurierTransform<T>::PI(3.14159265358979323846264338328L);