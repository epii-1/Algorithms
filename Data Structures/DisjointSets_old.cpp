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

//Simple generator class
struct c_unique {
    int current{ 0 };
    c_unique() { }
    int operator()() { return ++current; }
} UniqueNumber;

//Simple one-directional tree
struct myTree {
    int i;
    int size{ 1 };
    myTree * parent{ nullptr };

    myTree(int i) : i{ i } {}
    myTree() {}

    myTree * top() {
        if (parent == nullptr)
            return this;
        return parent = parent->top();
    }
};

//all our elements
vector<myTree> v;

inline void _union(int a, int b) {
    myTree * one(v[a].top()), *two(v[b].top());
    if (one != two) {
        //Set to biggest as parent to flatten the tree as much as possible (Rich-get-Richer)
        if (one->size > two->size) {
            two->parent = one;
            one->size += two->size;
        }
        else {
            one->parent = two;
            two->size += one->size;
        }
    }
}

inline bool same(int a, int b) {
    return v[a].top() == v[b].top();
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n, q;
    fastScan(n);
    fastScan(q);

    //Just create all elements
    v.resize(n);
    generate(v.begin(), v.end(), UniqueNumber);

    char eq = '=';
    char question = '?';
    string yes("yes\n");
    string no("no\n");

    while (--q > -1) {
        char t = getchar_unlocked();
        while (t != eq && t != question)
            t = getchar_unlocked();

        int i, j;
        fastScan(i);
        fastScan(j);
        if (t == eq) {
            _union(i, j);
        }
        else if (t == question) {
            if (same(i, j))
                printf("%s", yes.c_str());
            else
                printf("%s", no.c_str());
        }
    }

    return 0;
}