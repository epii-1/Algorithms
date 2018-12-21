//https://liu.kattis.com/problems/aspenavenue
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
#include <bits/stdc++.h>

using namespace std;

//https://www.geeksforgeeks.org/fast-io-for-competitive-programming/
template<typename T>
void fastScan(T &number)
{
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


int main() {

    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.precision(17);

    int nr;
    long double Le;
    int W;

    long double left{ 0 };
    long double right{ 0 };

    fastScan(nr);
    fastScan(Le);
    fastScan(W);

    vector<int> pos(nr);
    int W2 = W*W;


    long double s = Le / ((nr - 2) / 2);
    int t2;
    int i;
    for (i = 0; i < nr; ++i) {
        fastScan(t2);
        pos[i] = t2;
    }

    sort(pos.begin(), pos.end());

    long double m{ 0 };

    m += pos[0];
    left += s;


    int ha = nr / 2;
    int c;
    long double t;
    long double leftcl;
    long double leftcr;
    long double ml;
    long double mr;
    long double mro;
    long double mln;
    long double mrn;
    bool goRight = true;
    int j;
    for (i = 1; i < nr - 1; ++i) {

        c = pos[i];
        if (c - left > 0.0000001 || right - Le > 0.0000001) {

            m += abs(c - left);
            left += s;
        }
        else if (Le - left < 0.0000001) {

            t = c - right;
            m += sqrt(t*t + W2);
            right += s;
        }
        else {
            leftcl = left + s;
            leftcr = left;
            ml = m + left - c;
            t = c - right;
            mr = m + sqrt(t*t + W2);
            mro = mr;

            goRight = true;

            for (j = i + 1; Le - leftcr > 0.0000001; ++j) {
                if (pos[j] < leftcr) {

                    ml += abs(pos[j] - leftcl);
                    mr += leftcr - pos[j];
                    leftcl += s;
                    leftcr += s;
                }
                else {
                    t = pos[j] - right;
                    mln = ml + sqrt(t*t + W2);

                    mrn = mr + abs(leftcr - pos[j]);

                    if (mln < mrn) {

                        goRight = false;
                        left = leftcl;
                        m = ml;
                        i = j - 1;
                        break;
                    }
                    ml += abs(leftcl - pos[j]);
                    mr = mrn;
                    leftcr = leftcl;
                    leftcl += s;
                }
            }
            if (goRight) {
                right += s;
                m = mro;
            }
        }
    }

    m += Le - pos[nr - 1];
    cout << fixed << m << "\n";

    return 0;

}