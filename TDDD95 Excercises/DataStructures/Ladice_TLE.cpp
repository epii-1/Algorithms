//https://liu.kattis.com/sessions/prsaxh/problems/ladice
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
#include <stdio.h>
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

vector<bool> knownFails;
vector<pair<int, int>> v;

bool tryInsert(int a, int b) {

    if (knownFails[a])
        return false;

    /*if(seen[a] ){
    knownFails[a] = true;
    return false;
    }*/

    //seen[a] = true;
    knownFails[a] = true;
    if (v[a].first == -1 || tryInsert(v[a].first, v[a].second)) {
        v[a] = make_pair(b, a);
        knownFails[a] = false;
        return true;
    }

    //knownFails[a] = true;
    return false;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);

    int N, n2, L, a, b;

    fastScan(N);
    fastScan(L);

    v.resize(L, make_pair(-1, -1));
    knownFails.resize(L, false);

    ++N;
    while (--N) {
        fastScan(a);
        fastScan(b);
        --a;
        --b;
        if (v[a].first == -1) {
            v[a] = make_pair(b, a);
            printf("LADICA\n");
        }
        else if (v[b].first == -1) {
            v[b] = make_pair(a, b);
            printf("LADICA\n");
        }
        else {
            //vector<bool> seena(L, false), seenb(L, false);
            if (tryInsert(a, b)) {
                printf("LADICA\n");
            }
            else if (tryInsert(b, a)) {
                //knownFails[a] = true;
                printf("LADICA\n");
            }
            else {
                //knownFails[a] = true;
                //knownFails[b] = true;
                printf("SMECE\n");
            }
        }
    }

    return 0;
}
