//https://liu.kattis.com/problems/spiderman
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

using namespace std;

struct state {
    int mh;
    string s;
    int ch;
    int i;
    state(int mh, string s, int ch, int i) : mh{ mh }, s{ s }, ch{ ch }, i{ i } {}

    state(const state & o) : mh{ o.mh }, s{ o.s }, ch{ o.ch }, i{ o.i } {}

    bool operator< (const state & o) {
        return mh < o.mh || (mh == o.mh && i > o.i);
    }
};

bool operator< (const state & lhs, const state & rhs) {
    return lhs.mh > rhs.mh || (lhs.mh == rhs.mh && lhs.i > rhs.i);
}

int main() {

    ios::sync_with_stdio(NULL);
    cout.precision(17);

    int n;
    cin >> n;

    for (int j = 0; j < n; ++j) {
        int m;
        cin >> m;

        if (m == 0) {
            cout << "\n";
            continue;
        }

        vector<int> s(m);
        int sum = 0;
        for (int i = 0; i < m; ++i) {
            cin >> s[i];
            sum += s[i];
        }

        if (sum % 2 == 1) {
            cout << "IMPOSSIBLE\n";
            continue;
        }
        else {
            vector<set<int>> dp(m, set<int>());
            priority_queue<state> pq;

            state first(s[0], "U", s[0], 0);

            pq.emplace(first);
            bool solved = false;
            while (!pq.empty()) {
                state curr(pq.top());
                set<int>* setp = &dp[curr.i];
                pq.pop();
                if (setp->find(curr.ch) == setp->end()) {
                    setp->insert(curr.ch);

                    ++curr.i;

                    if (curr.i == m) {
                        if (curr.ch == 0) {
                            cout << curr.s << "\n";
                            solved = true;
                            break;
                        }
                    }
                    else {

                        state up(curr);
                        state down(curr);

                        up.ch += s[curr.i];
                        if (up.ch > up.mh)
                            up.mh = up.ch;
                        up.s += "U";

                        pq.emplace(up);

                        down.ch -= s[curr.i];
                        if (down.ch >= 0) {
                            down.s += "D";
                            pq.emplace(down);
                        }
                    }
                }
            }
            if (!solved) {
                cout << "IMPOSSIBLE\n";
            }
        }
    }

    return 0;

}
