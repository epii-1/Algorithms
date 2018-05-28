//https://liu.kattis.com/problems/equationsolver
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
#include <iterator>
#include <sstream>
#include <map>
#include <bitset>

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

    if (c == '-') {
        // number is negative
        negative = true;

        // extract the next character from the buffer
        c = getchar_unlocked();
    }

    // Keep on extracting characters if they are integers
    // i.e ASCII Value lies from '0'(48) to '9' (57)
    for (; (c>47 && c<58); c = getchar_unlocked())
        number = number * 10 + c - 48;

    if (c == '.') {
        c = getchar_unlocked();
        T pot(0.1);
        for (; (c>47 && c<58); c = getchar_unlocked(), pot *= 0.1)
            number += (c - 48)*pot;
    }

    // if scanned input has a negative sign, negate the
    // value of the input number
    if (negative)
        number *= -1;
}


const long double epsilon{ 0.0000000001 };

template<typename T>
bool solve(vector<vector<T>*>& a, vector<T>& b) {
    size_t i, j, k, maxI; //Indexes
    T maxVal;
    size_t n{ b.size() }, back(n); //size, and position of the back (first before 0-column)

    vector<size_t> columnIndex(n);
    for (i = 0; i < n; ++i) columnIndex[i] = i;

    bool zeroRowExists{ false };

    //Reduce matrix to topright
    for (i = 0; i < n; ++i) {
        maxVal = 0;
        while (maxVal < epsilon) {
            //Find the bigges value and begin there to reduce floating point errors
            for (j = i; j < n; ++j)
                if (maxVal < abs(a[j]->at(columnIndex[i]))) {
                    maxVal = abs(a[j]->at(columnIndex[i]));
                    maxI = j;
                }

            //Biggest value is ~0, push column to end
            if (maxVal < epsilon) {
                zeroRowExists = true;
                //Back is current, time to end it
                if (--back <= i) {
                    back = i;
                    i = n;
                    break;
                }

                swap(columnIndex[i], columnIndex[back]);
            }
        }

        //End it
        if (i == n)
            break;

        //Swap max row to current
        swap(a[i], a[maxI]);
        swap(b[i], b[maxI]);

        T invers(1.0L / a[i]->at(columnIndex[i])); //Mult is faster than div, so :D
        T mult;
        //Add current/max row to all other rows to remove their current variable to 0
        for (j = i + 1; j < n; ++j) {
            mult = a[j]->at(columnIndex[i]) * invers; //We have already done the divison, so mult
            a[j]->at(columnIndex[i]) = 0;

            //For all variables
            for (k = i + 1; k < n; ++k)
                a[j]->at(columnIndex[k]) -= a[i]->at(columnIndex[k]) * mult;

            b[j] -= b[i] * mult;
        }
    }

    if (zeroRowExists) {

        //All the [back x back]-matrix will a 0-matrix
        //We already know it's multiple, now we just need to find 1 b-value != 0
        //To know that it's inconsistent
        for (i = back; i < n; ++i) {
            if (abs(b[i]) > epsilon) {
                //printf("inconsistent");
                cout << "inconsistent";
                return false;
            }
        }

        cout << "multiple";
        //printf("multiple");
        return false;
    }
    else {
        //Reduce matrix to diagonal and get values

        //This looks odd dosent it? but as -1 is max unsigned...
        for (i = n - 1; i < -1; --i) {
            //Calculate value of variable (b[i] will contain it)
            b[i] /= a[i]->at(columnIndex[i]);

            //Remove this variable from all rows above
            for (j = 0; j < i; ++j)
                b[j] -= a[j]->at(columnIndex[i]) * b[i];
        }
        return true;
    }
}

int main() {
    ios::sync_with_stdio(false);
    //cout.precision(17);
    cout.tie(nullptr);
    cin.tie(nullptr);

    int n, i, j;

    vector<vector<long double>> a2;
    vector<vector<long double>*> a;
    vector<long double> b;

    while (true) {
        //Input
        fastScan(n);
        if (n == 0)
            break;
        //return 0;

        //Storing shits in pointers instead of vectors to not have to swap the actual vectors :)
        a2.resize(n, vector<long double>(n));
        a.resize(n);
        for (i = 0; i < n; ++i) {
            a2[i].resize(n);
            a[i] = &(a2[i]);
            for (j = 0; j < n; ++j) {
                fastScan(a2[i][j]);
            }
        }
        b.resize(n);
        for (i = 0; i < n; ++i) 
            fastScan(b[i]);

        //Solve
        bool solved{ solve(a, b) };

        //Output
        if (solved)
            copy(b.begin(), b.end(), ostream_iterator<long double>(cout, " "));
        //printf("\n");
        cout << "\n";
    }

    return 0;
}