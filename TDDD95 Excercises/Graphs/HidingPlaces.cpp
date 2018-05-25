//https://liu.kattis.com/problems/hidingplaces
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
#include <complex>
//#include <bits/stdc++.h>

using namespace std;

//https://www.geeksforgeeks.org/fast-io-for-competitive-programming/
template<typename T>
void fastScan(T &number) {
    register T c;

    number = 0;

    // extract current character from buffer
    c = getchar();
    while (!(c > 47 && c < 58))
        c = getchar();

    // Keep on extracting characters if they are integers
    // i.e ASCII Value lies from '0'(48) to '9' (57)
    for (; (c>47 && c<58); c = getchar())
        number = number * 10 + c - 48;
}


int main() {
    ios::sync_with_stdio(false);
    cout.tie(nullptr);
    cin.tie(nullptr);

    int N, n;
    char c;
    fastScan(N);
    ++N;

    queue<std::complex<short>> q;

    vector<std::complex<short>> dirs(8);

    dirs[0] = std::complex<short>(2, 1);
    dirs[1] = std::complex<short>(2, -1);
    dirs[2] = std::complex<short>(-2, 1);
    dirs[3] = std::complex<short>(-2, -1);
    dirs[4] = std::complex<short>(1, 2);
    dirs[5] = std::complex<short>(-1, 2);
    dirs[6] = std::complex<short>(1, -2);
    dirs[7] = std::complex<short>(-1, -2);

    vector<char> cv(8);
    vector<char> iv(8);

    for (int i{ 0 }; i < 8; ++i) {
        cv[i] = 'a' + i;
        iv[i] = '1' + i;
    }

    std::complex<short> curr, newp;
    int curri;
    while (--N) {

        vector<vector<short>> v(8, vector<short>(8, -1));

        c = getchar();
        while (c < 97 || c > 104) c = getchar();
        fastScan(n);

        q.emplace(c - 97, n - 1);
        v[c - 97][n - 1] = 0;

        int maxx{ 0 };
        vector<std::complex<short>> o;

        while (!q.empty()) {
            curr = q.front(), q.pop();
            curri = v[curr.real()][curr.imag()];
            if (curri > maxx) {
                o.clear();
                maxx = curri;
            }
            o.push_back(curr);
            ++curri;
            for (std::complex<short> i : dirs) {
                newp = curr + i;
                if (-1 < newp.real() && newp.real() < 8 && -1 < newp.imag() && newp.imag() < 8 &&
                    v[newp.real()][newp.imag()] == -1) {
                    q.push(newp);
                    v[newp.real()][newp.imag()] = curri;
                }
            }
        }

        sort(o.begin(), o.end(), [](const std::complex<short> & l, const std::complex<short> & r)
            ->bool { return l.imag() > r.imag() || (l.imag() == r.imag() && l.real() < r.real()); });

        cout << maxx << " ";
        for (std::complex<short> s : o) {
            cout << cv[s.real()] << iv[s.imag()] << " ";
        }
        cout << "\n";
    }

    return 0;
}