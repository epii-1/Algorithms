//https://liu.kattis.com/problems/dominant
//Leif Eriksson
//leier318
//Bloody bad solution, but it just makes it
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
#include <list>

using namespace std;

#define _UNLOCKED 1
#if _UNLOCKED
#define gc() getchar_unlocked()
#else
#define gc() getchar()
#endif

struct node {
    vector<char> m;
    string s;
    bool good{ true };
};

bool operator< (const node & lhs, const node & rhs) {
    return lhs.s.length() > rhs.s.length() || (lhs.s.length() == rhs.s.length() && lhs.m > rhs.m);
}

int main() {
    ios::sync_with_stdio(false);
    cout.tie(nullptr);
    cin.tie(nullptr);

    vector<node> v;

    char c{ ' ' };
    string s;
    v.reserve(15000);
    while (c != '1' && c != EOF) {
        s = "";
        while (!((c <= 'z' && c >= 'a') || c == EOF || c == '1'))
            c = gc();
        if (c == EOF || c == '1')
            break;
        v.emplace_back();
        v.back().m.reserve(15);
        while (c <= 'z' && c >= 'a') {
            s += c;
            v.back().m.push_back(c);
            c = gc();
        }
        v.back().s = s;
        sort(v.back().m.begin(), v.back().m.end());
    }

    sort(v.begin(), v.end());

    vector<char>::const_iterator mit{ v[0].m.begin() };
    vector<char>::const_iterator mit2{ v[0].m.begin() };
    bool good;
    for (auto it{ v.begin() }, it2{ it }; it != v.end(); ++it) {
        if (it->good) {
            it2 = it;
            for (++it2; it2 != v.end(); ++it2) {
                if (it2->good && it->s.length() > it2->s.length()) {
                    mit = it->m.begin();
                    mit2 = it2->m.begin();
                    good = true;
                    while (mit != it->m.end() && mit2 != it2->m.end()) {
                        while (mit != it->m.end() && *mit < *mit2) ++mit;
                        //cout << (mit != it->m.end()) << " " << (mit2 != it2->m.end()) << "\n";
                        if (mit != it->m.end() && *mit == *mit2) {
                            ++mit;
                            ++mit2;
                        }
                        else {
                            good = false;
                            break;
                        }
                    }
                    if (mit2 != it2->m.end())
                        good = false;

                    it2->good = !good;
                }
            }
        }
    }

    int b(v.size());
    for (int i(0); i < b; ++i) {
        if (!v[i].good) {
            swap(v[i], v[--b]);
            --i;
        }
    }

    sort(v.begin(), v.begin() + b, [](const node & lhs, const node & rhs)->bool {return lhs.s < rhs.s; });
    for (node &n : v)
        if (n.good) {
            printf("%s\n", n.s.c_str());
        }
        else
            break;

    system("Pause");
    return 0;
}