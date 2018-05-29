//https://liu.kattis.com/problems/dominant
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
#include <list>

using namespace std;

struct node {
    map<char, int> m;
    string s;
    bool good = true;

    friend ostream& operator<<(ostream& os, const node& n) {
        os << n.s;
        return os;
    }

};

struct so {
    bool const operator()(const node & lhs, const node & rhs) {
        return lhs.s < rhs.s;
    }
};

bool operator< (const node & lhs, const node & rhs) {
    return lhs.s.length() > rhs.s.length();
}

int main() {
    ios::sync_with_stdio(false);
    cout.tie(nullptr);
    cin.tie(nullptr);

    vector<node> v;

    char c{ ' ' };
    string s;
    while (c != '1' && c != EOF) {
        s = "";
        while (!((c <= 'z' && c >= 'a') || c == EOF || c == '1'))
            c = getchar();
        if (c == EOF || c == '1')
            break;
        while (c <= 'z' && c >= 'a') {
            s += c;
            c = getchar();
        }
        v.emplace_back();
        v.back().s = s;
        for (char c : s)
            v.back().m[c] += 1;
    }

    sort(v.begin(), v.end());

    for (auto it{ v.begin() }; it != v.end(); ++it) {
        if (it->good) {
            auto it2{ it };
            for (++it2; it2 != v.end(); ++it2) {
                if (it2->good /*&& it2->m.size() >= it2->m.size()*/) {
                    auto mit{ it->m.begin() };
                    auto mit2{ it2->m.begin() };
                    bool good{ it->m.size() > it2->m.size() || it->s.length() > it2->s.length() };
                    while (mit != it->m.end() && mit2 != it2->m.end()) {
                        while (mit != it->m.end() && mit->first < mit2->first) ++mit;
                        //cout << (mit != it->m.end()) << " " << (mit2 != it2->m.end()) << "\n";
                        if (mit != it->m.end() && mit->first == mit2->first && mit->second >= mit2->second) {
                            if (mit->second > mit2->second)
                                good = true;
                            ++mit;
                            ++mit2;
                        }
                        else {
                            good = false;
                            break;
                        }
                    }
                    it2->good = !good;
                }
            }
        }
    }

    sort(v.begin(), v.end(), so());
    for (node n : v)
        if (n.good) {
            cout << n.s << "\n";
        }
    //copy(v.begin(), v.end(), ostream_iterator<node>(cout, "\n"));

    system("Pause");
    return 0;
}