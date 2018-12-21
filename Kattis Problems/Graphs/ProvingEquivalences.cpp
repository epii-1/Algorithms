//https://liu.kattis.com/problems/equivalences
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
#include <stack>
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
    for (; (c > 47 && c < 58); c = getchar_unlocked())
        number = number * 10 + c - 48;
}

struct Node {
    int i{ -1 };
    int index{ -1 };
    int lowlink;
    vector<int> proves;
    vector<int> provedBy;
    bool onStack{ false };
};

//algorithm tarjan is
//input : graph G = (V, E)
//output : set of strongly connected components(sets of vertices)
void strongconnect(Node & v, int & index, stack<Node*> & S, vector<Node> & V,
    vector<set<int>> & o) {
    // Set the depth index for v to the smallest unused index
    v.index = index;
    v.lowlink = index;
    ++index;
    S.push(&v);
    v.onStack = true;

    // Consider successors of v
    for (int wi : v.proves) {
        if (V[wi].index == -1) {
            // Successor w has not yet been visited; recurse on it
            strongconnect(V[wi], index, S, V, o);
            v.lowlink = min(v.lowlink, V[wi].lowlink);
        }
        else if (V[wi].onStack) {
            // Successor w is in stack S and hence in the current SCC
            // If w is not on stack, then (v, w) is a cross-edge in the DFS tree and 
            //must be ignored
            // Note: The next line may look odd - but is correct.
            // It says w.index not w.lowlink; that is deliberate and from the original paper
            v.lowlink = min(v.lowlink, V[wi].index);
        }
    }

    // If v is a root node, pop the stack and generate an SCC

    if (v.lowlink == v.index) {
        //start a new strongly connected component
        o.push_back(set<int>());
        o[o.size() - 1].insert(v.i);
        while (S.top()->i != v.i) {
            Node *w(S.top());
            S.pop();
            w->onStack = false;
            //add w to current strongly connected component
            o[o.size() - 1].insert(w->i);
        }
        //  output the current strongly connected component
        S.pop();
        v.onStack = false;
    }
}

int main() {
    ios::sync_with_stdio(false);
    cout.tie(nullptr);
    cin.tie(nullptr);

    int N, n, m, i, k, x, y;
    fastScan(N);
    ++N;
    pair<int, int> start;
    while (--N) {
        //input blablabla
        fastScan(n);
        fastScan(m);
        vector<Node> nodes(n);
        int roots(n), leafs(n);
        for (i = 0; i < n; ++i)
            nodes[i].i = i;
        for (i = 0; i < m; ++i) {
            fastScan(x);
            fastScan(y);
            --x;
            --y;
            if (nodes[x].proves.size() == 0)
                --leafs;
            nodes[x].proves.push_back(y);
            if (nodes[y].provedBy.size() == 0)
                --roots;
            nodes[y].provedBy.push_back(x);
        }
        int index(0);
        stack<Node*> s;// : = empty array
        vector<set<int>> newNodes;
        for (i = 0; i < n; ++i) {
            if (nodes[i].index == -1) {
                strongconnect(nodes[i], index, s, nodes, newNodes);
            }
        }
        if (newNodes.size() == 1)
            printf("0\n");
        else {
            for (i = 0; i < newNodes.size(); ++i) {
                if (newNodes[i].size() > 1) {
                    int size(newNodes[i].size());
                    bool isRoot{ true }, isLeaf{ true };
                    for (int j : newNodes[i]) {
                        int size2(nodes[j].proves.size());
                        for (k = 0; k < size2 && isLeaf; ++k) {
                            isLeaf = (newNodes[i].find(nodes[j].proves[k]) != newNodes[i].end());
                        }
                        size2 = nodes[j].provedBy.size();
                        for (k = 0; k < size2 && isRoot; ++k) {
                            isRoot = (newNodes[i].find(nodes[j].provedBy[k]) != newNodes[i].end());
                        }
                        if (!isRoot && !isLeaf)
                            break;
                    }
                    if (isRoot)
                        ++roots;
                    if (isLeaf)
                        ++leafs;
                }
            }
            printf("%d\n", max(leafs, roots));
        }
    }

    return 0;
}

/*
2
4 0
3 3
1 2
1 3
2 1
*/