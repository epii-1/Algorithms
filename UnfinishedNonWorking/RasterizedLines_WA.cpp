//https://liu.kattis.com/problems/rasterized
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
    for (; (c > 47 && c < 58); c = getchar())
        number = number * 10 + c - 48;
}

int main() {
    ios::sync_with_stdio(false);
    cout.tie(nullptr);
    cin.tie(nullptr);

    long long T, N, N2, a;
    fastScan(T);
    ++T;

    while (--T) {
        fastScan(N);
        N2 = N;
        vector<long long> v;
        if (N % 2 == 0) {
            while (N2 % 2 == 0) N2 /= 2;
            v.push_back(2);
            //for (long long i = 2; i < N; i += 2)
            //    v.push_back(i);
        }
        long long j = 3;
        for (; j * j <= N2; j += 2) {
            if (N2 % j == 0) {
                v.push_back(j);
                //for (long long i{ j }; i < N && i < j*j; i += j + j)
                //    v.push_back(i);
                while (N2 % j == 0)
                    N2 /= j;
            }
        }
        if (N2 != 1)
            v.push_back(N2);
        //for (long long i{ j }; i < N && i < j*j; i += j + j)
        //    v.push_back(i);

        a = 1;
        if (N > 1) {
            a = 3;
            //cout << "done\n";
            for (long long n : v) {
                if (n == 2) {
                    for (long long m{ n }; m < N; m *= n) {
                        for (long long i{ max(N - m, m) + 1 }; i <= N; ++i) {
                            //cout << i << " " << i + i % m << "\n";
                            if (i + i % m == N) {
                                //cout << " " << i << " " << m << " " << N - m << " " << N - i + m << endl;
                                a += 2;
                            }
                        }
                    }
                }
                else {
                    for (long long m{ n }; m < N && m <= n * n; m += n) {
                        for (long long i{ max(N - m, m) }; i <= N; i += n) {
                            //cout << i << " " << i + i % m << "\n";
                            if (i + i % m == N) {
                                //cout << " " << i << " " << m << " " << N - m << " " << N - i + m << endl;
                                a += 2;
                            }
                        }
                    }
                    for (long long m{ n*n*n }; m < N; m *= n) {
                        for (long long i{ max(N - m, m) }; i <= N; i += n) {
                            //cout << i << " " << i + i % m << "\n";
                            if (i + i % m == N) {
                                //cout << " " << i << " " << m << " " << N - m << " " << N - i + m << endl;
                                a += 2;
                            }
                        }
                    }
                }
            }
        }

        printf("%lld\n", a);

    }

    system("Pause");
    return 0;
}