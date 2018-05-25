//https://liu.kattis.com/problems/frogger
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

struct Node {
    Node(int x, int y, long long t) : x(x), y(y), t(t) {}
    Node() {}
    int x, y;
    long long t;
};

pair<int, int> goal;


long long Solve(pair<int, int> start, vector<vector<vector<char>>> & matrix, long long x) {

    queue<Node> q;

    Node curr, neighbor;
    int m(matrix[0].size()), cm;


    vector<vector<vector<bool>>> visited(matrix.size(), vector<vector<bool>>(matrix[0].size(),
        vector<bool>(matrix[0][0].size(), false)));

    q.emplace(start.first, start.second, 0);
    visited[start.first][start.second][0] = false;

    while (!q.empty()) {
        //Get the the current best
        curr = q.front(), q.pop();
        cm = curr.t%m;


        if (curr.x == goal.first && curr.y == goal.second) {
            return curr.t;
        }

        //For all neighbors
        neighbor = curr;
        ++neighbor.t;
        if (neighbor.t <= x) {
            cm = neighbor.t%m;
            if (matrix[neighbor.x][neighbor.y][cm] != 'X'
                && !visited[neighbor.x][neighbor.y][cm]) {

                visited[neighbor.x][neighbor.y][cm] = true;
                q.push(neighbor);
            }
            ++neighbor.x;
            if (neighbor.x < matrix.size() && matrix[neighbor.x][neighbor.y][cm] != 'X'
                && !visited[neighbor.x][neighbor.y][cm]) {

                visited[neighbor.x][neighbor.y][cm] = true;
                q.push(neighbor);
            }
            neighbor.x -= 2;
            if (neighbor.x > -1 && matrix[neighbor.x][neighbor.y][cm] != 'X'
                && !visited[neighbor.x][neighbor.y][cm]) {

                visited[neighbor.x][neighbor.y][cm] = true;
                q.push(neighbor);
            }
            ++neighbor.x;
            ++neighbor.y;
            if (neighbor.y < m && matrix[neighbor.x][neighbor.y][cm] != 'X'
                && !visited[neighbor.x][neighbor.y][cm]) {

                visited[neighbor.x][neighbor.y][cm] = true;
                q.push(neighbor);
            }
            neighbor.y -= 2;
            if (neighbor.y > -1 && matrix[neighbor.x][neighbor.y][cm] != 'X'
                && !visited[neighbor.x][neighbor.y][cm]) {

                visited[neighbor.x][neighbor.y][cm] = true;
                q.push(neighbor);
            }
        }
    }

    return -1;
}

int main() {
    ios::sync_with_stdio(false);
    cout.tie(nullptr);
    cin.tie(nullptr);

    int N, n, m, i, j, k;
    long long x, r;
    char c;
    fastScan(N);
    ++N;
    pair<int, int> start;
    while (--N) {
        //input blablabla
        fastScan(x);
        fastScan(n);
        fastScan(m);

        n += 2;
        vector<vector<vector<char>>> matrix(n, vector<vector<char>>(m, vector<char>(m)));
        c = getchar_unlocked();
        for (i = 0; i < n; ++i) {
            while (!(c == 'O' || c == 'G' || c == 'F' || c == 'X')) c = getchar_unlocked();
            for (j = 0; j < m; ++j) {
                for (k = 0; k < m; ++k) {
                    if (i % 2 == n % 2)
                        matrix[i][(j + k) % m][k] = c;
                    else
                        matrix[i][(j + m - k) % m][k] = c;
                }
                if (c == 'F')
                    start = make_pair(i, j);
                else if (c == 'G') {
                    goal = make_pair(i, j);
                }
                c = getchar_unlocked();
            }
        }

        r = Solve(start, matrix, x);

        if (r == -1)
            printf("The problem has no solution.\n");
        else
            printf("The minimum number of turns is %lld.\n", r);

    }

    return 0;
}