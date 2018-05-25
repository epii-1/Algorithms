//https://liu.kattis.com/problems/suffixarrayreconstruction
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
#include <iterator>
#include <sstream>
#include <map>
#include <bitset>
#include <stack>
#include <complex>
#include <bits/stdc++.h>
#include <list>

using namespace std;
//https://www.geeksforgeeks.org/fast-io-for-competitive-programming/
template<typename T>
void fastScan(T &number)
{
    register T c;

    number = 0;

    // extract current character from buffer
    c = getchar_unlocked();
    while (!(c > 47 && c < 58))
        c = getchar();

    // Keep on extracting characters if they are integers
    // i.e ASCII Value lies from '0'(48) to '9' (57)
    for (; (c > 47 && c < 58); c = getchar_unlocked())
        number = number * 10 + c - 48;
}

int main() {
    ios::sync_with_stdio(false);
    cout.tie(nullptr);
    cin.tie(nullptr);

    int n;
    fastScan(n);
    ++n;

    string s1;
    string s2;
    string* sp;
    char c;
    int l, s, i, j, j2, k;
    while (--n) {
        int l, s;
        fastScan(l);
        fastScan(s);
        vector<char> v(l, '*');
        bool good{ true };
        c = '-';
        for (i = 0; i < s; ++i) {
            s1 = "";
            s2 = "";
            fastScan(k);
            while (!((c <= 'z' && c >= 'a') || (c <= 'Z' && c >= 'A') || c == '*' || c == '.'))
                c = getchar_unlocked();

            sp = &s1;
            while ((c <= 'z' && c >= 'a') || (c <= 'Z' && c >= 'A') || c == '*' || c == '.') {
                if (c != '*')
                    *sp += c;
                else
                    sp = &s2;
                c = getchar_unlocked();
            }
            if (good) {
                for (j = k - 1, j2 = 0; j < l && j2 < s1.length(); ++j, ++j2) {
                    if (v[j] == '*')
                        v[j] = s1[j2];
                    else if (v[j] != s1[j2]) {
                        cout << "IMPOSSIBLE\n";
                        good = false;
                    }
                }
                if (good) {
                    for (j = l - 1, j2 = s2.length() - 1; j > k - 2 && j2 > -1; --j, --j2) {
                        if (v[j] == '*')
                            v[j] = s2[j2];
                        else if (v[j] != s2[j2]) {
                            cout << "IMPOSSIBLE\n";
                            good = false;
                        }
                    }
                }
            }
        }
        if (good) {
            for (char c : v)
                if (c == '*')
                    good = false;
            if (good) {
                copy(v.begin(), v.end(), ostream_iterator<char>(cout, ""));
                cout << "\n";
            }
            else
                cout << "IMPOSSIBLE\n";
        }
    }

    return 0;
}