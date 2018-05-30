//https://liu.kattis.com/problems/eulerianpath
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
#include <list>

using namespace std;

//https://www.geeksforgeeks.org/fast-io-for-competitive-programming/
template<typename T>
void fastScan(T &number) {
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
    vector<int> edges;
    int i{ 0 }, to{ 0 }, from{ 0 };
};

bool eulerianPathDeep(vector<Node> & nodes, int i, list<int> & l, const int e, const int e2) {
    Node* curr{ &nodes[i] };
    //DF walk untill we get stuck
    while (true) {
        Node* next{ &(nodes[curr->edges[curr->i]]) };
        i = curr->edges[curr->i];

        ++curr->i;
        if (i == e) //We found a cycle, can return it
            return true;

        l.push_back(i); //Add to path

        if (i == e2) //We found the start, we can return it
            return false;

        if (next->i == next->from) //This is bad
            return false; //Next is already full

        curr = next;
    }
}

//Recheck everything along to path to se if some node still have unused edges
bool recheck(vector<Node> & nodes, list<int> & l) {
    auto it{ l.begin() };
    for (; it != l.end(); ++it) {
        while (nodes[*it].i < nodes[*it].from) {
            list<int> l2;
            if (eulerianPathDeep(nodes, *it, l2, *it, *l.begin())) {
                //Add the newfound cycle
                l2.push_front(*it);
                it = l.insert(it, l2.begin(), l2.end());
            }
            else //Bad Path
                return false;

        }
    }
    return true;
}

bool eulerianPath(vector<Node> & nodes, list<int> & l) {
    int s{ 0 }, i;

    //Find a logical startnode
    //(Should add a check to only do this is oddIn,
    //Else it should only make sure first node got from > 0)
    for (i = 0; i < nodes.size(); ++i) {
        if (nodes[i].from > nodes[i].to) {
            s = i;
            break;
        }
        //if(nodes[i].from > 0) s = i; //Read comment down bellow
    }

    //Interesting. Is this really correct? What if we have a full cycle without node 0?

    //Walk from start (or node 0)
    eulerianPathDeep(nodes, s, l, -1, -1);
    l.push_front(s);

    //Recheck
    if (!recheck(nodes, l))
        return false;

    //Find unvisited nodes
    for (i = 0; i < nodes.size(); ++i)
        if (nodes[i].i < nodes[i].from)
            return false;

    return true;
}


int main() {
    ios::sync_with_stdio(false);
    cout.tie(nullptr);
    cin.tie(nullptr);

    int n, m, i, j, t1, t2;
    int m2;
    int oddOut{ 0 }, oddIn{ 0 };
    vector<Node> nodes;
    while (true) {
        //input blablabla
        fastScan(n);
        fastScan(m);

        if (n == 0 && m == 0)
            return 0;

        //nodes.clear();
        fill(nodes.begin(), min(nodes.end(), nodes.begin() + n), Node());
        nodes.resize(n);
        m2 = m;
        ++m;
        oddOut = oddIn = 0;
        while (--m) {
            //input blablabla
            fastScan(t1);
            fastScan(t2);
            nodes[t1].edges.emplace_back(t2);
            ++nodes[t1].from;
            ++nodes[t2].to;

            //Keeping count on odds nodes
            /*if (t1 != t2) {
            if (nodes[t1].from == nodes[t1].to + 1)
            ++oddOut;
            else if (nodes[t1].from == nodes[t1].to)
            --oddIn;
            if (nodes[t2].from + 1 == nodes[t2].to)
            ++oddIn;
            else if (nodes[t2].from == nodes[t2].to)
            --oddOut;
            }*/
        }

        //If there are more then 1 start, or more then 1 end,
        //Or 1 end without start
        //Or 1 start without end
        //We cant find a E-path
        //(Or if we find 2 disjoint cycles)
        list<int> l;
        if (oddIn > 1 || oddOut > 1 || oddIn != oddOut || !eulerianPath(nodes, l))
            cout << "Impossible\n";

        else {
            copy(l.begin(), l.end(), std::ostream_iterator<int>(cout, " "));

            cout << "\n";
        }
    }


    return 0;
}
/*
2 3
0 1
1 0
1 0

6 8
2 3
0 1
0 2
3 4
4 0
0 1
1 0
1 3


4 4
0 1
1 2
1 3
2 3
2 2
0 1
1 0
2 1
0 1
3 6
0 1
0 0
0 1
1 0
0 0
2 0
2 2
0 1
0 0
2 2
0 0
0 1
*/