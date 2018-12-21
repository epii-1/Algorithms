//https://liu.kattis.com/problems/caching
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

using namespace std;

//https://www.geeksforgeeks.org/fast-io-for-competitive-programming/
template<typename T>
void fastScan(T &number)
{
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

    if (c == '.') {
        c = getchar();
        T pot(0.1);
        for (; (c>47 && c<58); c = getchar(), pot *= 0.1)
            number += (c - 48)*pot;
    }
}

//All hail wikipedia :)The theoretically optimal page replacement algorithm
//The theoretically optimal page replacement algorithm(also known as OPT, clairvoyant replacement algorithm,
//or Bélády's optimal page replacement policy)[3][4][5] is an algorithm that works as follows: when a page 
//needs to be swapped in, the operating system swaps out the page whose next use will occur farthest in the 
//future. For example, a page that is not going to be used for the next 6 seconds will be swapped out over a 
//page that is going to be used within the next 0.4 seconds.

//This algorithm cannot be implemented in a general purpose operating system because it is impossible to 
//compute reliably how long it will be before a page is going to be used, except when all software that will 
//run on a system is either known beforehand and is amenable to static analysis of its memory reference
//patterns, or only a class of applications allowing run - time analysis.Despite this limitation, algorithms 
//exist[citation needed] that can offer near - optimal performance — the operating system keeps track of all 
//pages referenced by the program, and it uses those data to decide which pages to swap in and out on 
//subsequent runs.This algorithm can offer near - optimal performance, but not on the first run of a program, 
//and only if the program's memory reference pattern is relatively consistent each time it runs.

//Analysis of the paging problem has also been done in the field of online algorithms. Efficiency of 
//randomized online algorithms for the paging problem is measured using amortized analysis.
struct myPair {
    int i = 0;
    int next = 0;
    myPair(int i, int next) : i{ i }, next{ next } {}
};

bool operator<(const myPair & lhs, const myPair & rhs) {
    return lhs.next < rhs.next;
}

int optCache(int c, int n, const vector<int> & a) {
    vector<pair<int, vector<int>>> m(n);

    for (int i{ 0 }; i < a.size(); ++i) {
        m[a[i]].second.push_back(i);
    }

    for (int i{ 0 }; i < n; ++i)
        m[i].second.push_back(std::numeric_limits<int>::max());

    //char is faster than bool :)
    vector<char> inMemory(n, 0);
    priority_queue<myPair> pq;

    int r{ 0 };
    int size{ 0 };
    for (int i{ 0 }; i < a.size(); ++i) {
        ++m[a[i]].first;
        if (!inMemory[a[i]]) {
            ++r;
            ++size;
            if (size > c) {
                bool retry = true;
                while (retry) {
                    myPair now{ pq.top() };
                    pq.pop();
                    if (inMemory[now.i] == 1 && m[now.i].second[m[now.i].first] > i) {
                        inMemory[now.i] = 0;
                        retry = false;
                    }
                }
            }
        }
        pq.emplace(myPair{ a[i] , m[a[i]].second[m[a[i]].first] });
        inMemory[a[i]] = 1;
    }
    return r;
}

int main() {

    ios::sync_with_stdio(false);
    cout.precision(17);
    cin.tie(nullptr);
    cout.tie(nullptr);

    //Input
    int c, n, a;
    fastScan(c);
    fastScan(n);
    fastScan(a);
    vector<int> v;
    v.reserve(a);
    for (int i = 0; i < a; ++i) {
        int t1;
        fastScan(t1);
        v.push_back(t1);
    }

    //Solve
    cout << optCache(c, n, v) << "\n";

    return 0;

}