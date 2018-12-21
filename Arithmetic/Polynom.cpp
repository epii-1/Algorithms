//https://liu.kattis.com/problems/polymul2
//Leif Eriksson

#include <complex>
#include <valarray>
#include <cmath>
#include <algorithm>
#include <iostream>
#include "Arithmetic\FurierTransform.cpp"


//Was going to extend this with addition and some optimizations for reusing polynoms
//But it's not needed for the lab so...
template<typename T = long double>
class Poly {
public:

	Poly(std::valarray<std::complex<T>> & coef) : _coef(&coef) {}

	Poly& operator*=(Poly&& o) {
		_size = _coef->size() + o._coef->size();
		size_t s{ 1 };
		while (s < _size) s <<= 1;
		--_size;

		{
			//Pad with 0
			std::valarray<std::complex<T>> tmp(s);
			copy(begin(*_coef), end(*_coef), begin(tmp));
			*_coef = std::move(tmp);
		}

		FurierTransform<T>::fft(*_coef);

		{
			//Pad with 0
			//This should be done with a temp array
			//But as we wont reuse polynoms for the example....
			std::valarray<std::complex<T>> tmp(s);
			copy(begin(*o._coef), end(*o._coef), begin(tmp));
			*o._coef = std::move(tmp);

		}

		FurierTransform<T>::fft(*o._coef);


		for (size_t i{ 0 }; i < s; ++i)
			_coef->operator[](i) *= o._coef->operator[](i);

		FurierTransform<T>::ifft(*_coef, true);

		return *this;
	}

	void print() {
		printf("%lu\n", (_size - 1));
		for (size_t i{ 0 }; i < _size; ++i) {
			printf("%d ", (int)round(_coef->operator[](i).real()));
		}
		printf("\n");
	}

private:
	size_t _size;
	std::valarray<std::complex<T>>* _coef;
};