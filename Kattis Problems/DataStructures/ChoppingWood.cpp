//https://liu.kattis.com/problems/chopwood
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
#include <unordered_map>
#include <stack>
#include <bitset>
#include <bits/stdc++.h>

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
        c = getchar_unlocked();


    // Keep on extracting characters if they are integers
    // i.e ASCII Value lies from '0'(48) to '9' (57)
    for (; (c>47 && c<58); c = getchar_unlocked())
        number = number * 10 + c - 48;

}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);

    int n;
    fastScan(n);

    vector<int> avalible(n + 2, -1);
    vector<int> inV(n + 1);
    vector<int> output(n);

    int i;
    int t;
    for (int i = 0; i < n; ++i) {
        fastScan(t);
        inV[i] = t;
        if (t <= n)
            avalible[t] = i;
    }
    if (inV[n - 1] != n + 1) {
        printf("Error\n");
        return 0;
    }

    priority_queue<int, std::vector<int>, std::greater<int>> pq;
    for (i = 1; i <= n; ++i)
        if (avalible[i] == -1)
            pq.push(i);

    int index(1);
    for (i = 0; i < n; ++i) {
        index = pq.top(), pq.pop();
        if (avalible[index] >= i) {
            printf("Error\n");
            return 0;
        }
        output[i] = index;
        if (avalible[inV[i]] == i)
            pq.push(inV[i]);
    }

    printf("\n");
    copy(output.begin(), output.end(), ostream_iterator<int>(cout, "\n"));

    return 0;
}