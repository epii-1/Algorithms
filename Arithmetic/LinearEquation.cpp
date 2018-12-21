//https://liu.kattis.com/problems/equationsolver
//Leif Eriksson 
//leier318

#include <vector>
#include <utility>


enum Solution {
	INCONSISTENT, MULTIPLE, SOLVED
};

class LinearEquation {
private:
	static const long double _EPSILON;
public:
	template<typename T>
	static Solution solve(std::vector<std::vector<T>*>& a, std::vector<T>& b) {
		std::vector<bool> t;
		return _solve(a, b, false, t);
	}
	template<typename T>
	static Solution solve(std::vector<std::vector<T>*>& a, std::vector<T>& b, std::vector<bool> & known) {
		return _solve(a, b, true, known);
	}

private:
	template<typename T>
	static Solution _solve(std::vector<std::vector<T>*>& a, std::vector<T>& b, bool partial, std::vector<bool> & known) {
		size_t i, j, k, maxI; //Indexes
		T maxVal;
		const size_t n{ b.size() };
		size_t back(n); //size, and position of the back (first before 0-column)

		std::vector<size_t> columnIndex(n);
		for (i = 0; i < n; ++i) columnIndex[i] = i;

		bool zeroRowExists{ false };
		//Reduce matrix to topright
		for (i = 0; i < n; ++i) {
			maxVal = 0;
			while (maxVal < _EPSILON) {
				//Find the bigges value and begin there to reduce floating point errors
				for (j = i; j < n; ++j)
					if (maxVal < abs(a[j]->at(columnIndex[i]))) {
						maxVal = abs(a[j]->at(columnIndex[i]));
						maxI = j;
					}

				//Biggest value is ~0, push column to end
				if (maxVal < _EPSILON) {
					zeroRowExists = true;
					//Back is current, time to end it
					if (--back <= i) {
						back = i;
						i = n;
						break;
					}

					std::swap(columnIndex[i], columnIndex[back]);
				}
			}

			//End it
			if (i == n)
				break;

			//Swap max row to current
			std::swap(a[i], a[maxI]);
			std::swap(b[i], b[maxI]);

			T invers(1.0L / a[i]->at(columnIndex[i])); //Mult is faster than div, so :D
			T mult;
			//Add current/max row to all other rows to remove their current variable to 0
			for (j = partial ? 0 : i + 1; j < n; ++j) {
				if (i != j) {
					mult = a[j]->at(columnIndex[i]) * invers; //We have already done the divison, so mult
					a[j]->at(columnIndex[i]) = 0;

					//For all variables
					for (k = i + 1; k < n; ++k)
						a[j]->at(columnIndex[k]) -= a[i]->at(columnIndex[k]) * mult;

					b[j] -= b[i] * mult;
				}
			}
		}

		if (zeroRowExists) {

			//All the [back x back]-matrix will a 0-matrix
			//We already know it's multiple, now we just need to find 1 b-value != 0
			//To know that it's inconsistent
			for (i = back; i < n; ++i) {
				if (std::abs(b[i]) > _EPSILON) {
					return INCONSISTENT;
				}
			}

			if (!partial)
				return MULTIPLE;
		}

		if (!partial) {
			//Reduce matrix to diagonal and get values
			//This looks odd dosent it? but as -1 is max unsigned...
			for (i = n - 1; i < -1; --i) {
				//Calculate value of variable (b[i] will contain it)
				b[i] /= a[i]->at(columnIndex[i]);

				//Remove this variable from all rows above
				for (j = 0; j < i; ++j)
					b[j] -= a[j]->at(columnIndex[i]) * b[i];
			}
		}
		else {
			std::vector<T> tmpResult(n);
			//Get values

			//This looks odd dosent it? but as -1 is max unsigned...
			for (i = back - 1; i < -1; --i) {
				known[columnIndex[i]] = true;

				//If any multiplier in the back != 0, this variable will be dependant on an unknown
				//and thereby unknown
				for (j = back; j < n; ++j) {
					if (std::abs(a[i]->at(columnIndex[j])) > _EPSILON) {
						known[columnIndex[i]] = false;
						break;
					}
				}

				if (known[columnIndex[i]]) {
					//Calculate value of variable (b[i] will contain it)
					//We have to store it temporary to have the correct index for the result;
					tmpResult[columnIndex[i]] = b[i] / a[i]->at(columnIndex[i]);

				}
			}

			//Set the correct result to the correct variable
			std::copy(tmpResult.begin(), tmpResult.end(), b.begin());
		}
		return SOLVED;
	}
};


const long double LinearEquation::_EPSILON{ 0.0000000001 };