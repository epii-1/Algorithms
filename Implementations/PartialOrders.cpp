#include <iostream>
#include <vector>
#include <algorithm> 
#include <iterator> 
#include <stack>
#include <string>
#include <ctime>
#include <set>
#include <map>
#include <chrono>

#define OUTPUT 0
#define BASE 4 //4
#define SIZEBASE 2 //2


using namespace std;

template<typename T>
bool intersects(const set<T> &L, const set<T> &R) {
    auto it1(L.begin()), it2(R.begin());
    while (it1 != L.end() && it2 != R.end()) {
        if (*it1 < *it2)
            ++it1;
        else if (*it1 > *it2)
            ++it2;
        else return true;
    }
    return false;
}

template<typename T>
bool seteq(const set<T> &L, const set<T> &R) {
    auto it1(L.begin()), it2(R.begin());
    while (it1 != L.end() && it2 != R.end()) {
        if (*it1 != *it2)
            return false;
        ++it1, ++it2;
    }
    return it1 == L.end() && it2 == R.end();
}

template<typename T>
bool subset(const set<T> &L, const set<T> &R) {
    auto it1(L.begin()), it2(R.begin());
    while (it1 != L.end() && it2 != R.end()) {
        if (*it1 == *it2)
            ++it1, ++it2;
        else if (*it1 > *it2)
            ++it2;
        else if (*it1 < *it2)
            return false;
    }
    return it1 == L.end();
}

template<typename T>
bool propsubset(const set<T> &L, const set<T> &R) {
    auto it1(L.begin()), it2(R.begin());
    bool proper{ false };
    while (it1 != L.end() && it2 != R.end()) {
        if (*it1 == *it2)
            ++it1, ++it2;
        else if (*it1 > *it2) {
            ++it2;
            proper = true;
        }
        else if (*it1 < *it2)
            return false;
    }
    return it1 == L.end() && proper;
}

unsigned int choose(unsigned char n, unsigned char m) {
    unsigned int ans{ 1 };
    unsigned int i;
    m = max(static_cast<int>(m), n - m);
    for (i= m+1; i <= n; ++i) {
        ans *= i;
    }
    m = n - m;
    for (i= 2; i <= m; ++i) {
        ans /= i;
    }
    return ans;
}

class Graph{
public:
    const unsigned char size;
    vector<vector<bool>> V;

    Graph(unsigned char s) : size(s), V(s, vector<bool>(s)) {}

    void print() {
        for (unsigned char i{ 0 }; i < size; ++i) {
            for (unsigned char j{ 0 }; j < size; ++j) {
                printf("%d %d ", i, j);
                if (V[i][j])
                    printf("<\n");
                else if (V[j][i])
                    printf(">\n");
                else
                    printf("||\n");
            }
        }
    }
};

class Problem {
public:
    const unsigned char size;
    vector<vector<unsigned char>> C;
    const unsigned long long id;
    const unsigned long long sizeId;

    bool sat(Graph* G) {
        unsigned int  i{ 0 }, j{ 0 };
        for (i=0; i < size; ++i) {
            for (j = 0; j < i; ++j) {
                switch (C[i][j])
                {
                case 0:
                    //Nothing allowed
                    return false;
                case 1:
                    //i<j
                    if(!G->V[i][j])
                        return false;
                    break;
                case 2:
                    //i||j
                    if (G->V[i][j] || G->V[j][i])
                        return false;
                    break;
                case 3:
                    //i(<,||)j
                    if (G->V[j][i])
                        return false;
                    break;
                case 4:
                    //i>j
                    if (!G->V[j][i])
                        return false;
                    break;
                case 5:
                    //i(<,>)j
                    if (!G->V[i][j] && !G->V[j][i])
                        return false;
                    break;
                case 6:
                    //i(||,>)j
                    if (G->V[i][j])
                        return false;
                    break;
                case 7:
                    //i(<,||,>)j
                    break;
                default:
                    printf("Huh?\n");
                    break;
                }
            }
        }
        return true;
    }

    Problem(unsigned char s) : size(s), C(s,vector<unsigned char>(s)), id(pow(BASE,s)), sizeId(pow(SIZEBASE*BASE,s)) {
        unsigned char  i{ 0 }, j{ 0 };
        /*C[1][0] = 2;
        C[2][0] = 2;
        C[3][0] = 1;
        C[4][0] = 2;
        C[5][0] = 1;
        C[6][0] = 1;

        C[2][1] = 4;
        C[3][1] = 2;
        C[4][1] = 4;
        C[5][1] = 2;
        C[6][1] = 2;
        
        C[3][2] = 1;
        C[4][2] = 2;
        C[5][2] = 2;
        C[6][2] = 2;

        C[4][3] = 2;
        C[5][3] = 2;
        C[6][3] = 2;

        C[5][4] = 2;
        C[6][4] = 1;

        C[6][5] = 1;*/

        for (i = 0; i < size; ++i) {
            for (j = 0; j < i; ++j) {
                C[i][j] = 1 + rand() % 7;
                switch (C[i][j])
                {
                case 0:
                    //Nothing allowed
                    C[j][i] = 0; 
                    break;
                case 1:
                    //i<j
                    C[j][i] = 4;
                    break;
                case 2:
                    //i||j
                    C[j][i] = 2;
                    break;
                case 3:
                    //i(<,||)j
                    C[j][i] = 6;
                    break;
                case 4:
                    //i>j
                    C[j][i] = 1;
                    break;
                case 5:
                    //i(<,>)j
                    C[j][i] = 5;
                    break;
                case 6:
                    //i(||,>)j
                    C[j][i] = 3;
                    break;
                case 7:
                    //i(<,||,>)j
                    C[j][i] = 7;
                    break;
                default:
                    printf("Huh?\n"); 
                    break;
                }
#if OUTPUT >= 1
                printf("%d %d ", i,j);
                relaToStr(C[i][j]);
                printf("\n");
#endif
            }
        }
    }

    Problem(unsigned char s, int r) : size(s), C(s, vector<unsigned char>(s)), id(pow(BASE, s)), sizeId(pow(SIZEBASE * BASE, s)) {
        unsigned char  i{ 0 }, j{ 0 };
        for (i = 0; i < size; ++i) {
            for (j = 0; j < i; ++j) {
                C[i][j] = 1 + r % 7;
                r /= 7;
                switch (C[i][j])
                {
                case 0:
                    //Nothing allowed
                    C[j][i] = 0;
                    break;
                case 1:
                    //i<j
                    C[j][i] = 4;
                    break;
                case 2:
                    //i||j
                    C[j][i] = 2;
                    break;
                case 3:
                    //i(<,||)j
                    C[j][i] = 6;
                    break;
                case 4:
                    //i>j
                    C[j][i] = 1;
                    break;
                case 5:
                    //i(<,>)j
                    C[j][i] = 5;
                    break;
                case 6:
                    //i(||,>)j
                    C[j][i] = 3;
                    break;
                case 7:
                    //i(<,||,>)j
                    C[j][i] = 7;
                    break;
                default:
                    printf("Huh?\n");
                    break;
                }

#if OUTPUT >= 1
                printf("%d %d ", i, j);
                relaToStr(C[i][j]);
                printf("\n");
#endif
            }
        }
    }

    Problem(const Problem &p, const vector<unsigned char> &v) : size(v.size()), C(v.size(), vector<unsigned char>(v.size())), id(pow(BASE, v.size())), sizeId(pow(SIZEBASE * BASE, v.size())) {
        unsigned char  i{ 0 }, j{ 0 };

        for (; i < v.size(); ++i) {
            for (j = 0; j < i; ++j) {
                C[i][j] = p.C[v[i]][v[j]];
                switch (C[i][j])
                {
                case 0:
                    //Nothing allowed
                    C[j][i] = 0;
                    break;
                case 1:
                    //i<j
                    C[j][i] = 4;
                    break;
                case 2:
                    //i||j
                    C[j][i] = 2;
                    break;
                case 3:
                    //i(<,||)j
                    C[j][i] = 6;
                    break;
                case 4:
                    //i>j
                    C[j][i] = 1;
                    break;
                case 5:
                    //i(<,>)j
                    C[j][i] = 5;
                    break;
                case 6:
                    //i(||,>)j
                    C[j][i] = 3;
                    break;
                case 7:
                    //i(<,||,>)j
                    C[j][i] = 7;
                    break;
                default:
                    printf("Huh?\n");
                    break;
                }
#if OUTPUT >= 1
                printf("%d %d ", i, j);
                relaToStr(C[i][j]);
                printf("\n");
#endif
            }
        }
    }

    static void relaToStr(unsigned char r)  {
        switch (r)
        {
        case 0:
            //Nothing allowed
            printf("()");
            return;
        case 1:
            //i<j
            printf("(<)");
            return;
        case 2:
            //i||j
            printf("(||)");
            return;
        case 3:
            //i(<,||)j
            printf("(<,||)");
            return;
        case 4:
            //i>j
            printf("(>)");
            return;
        case 5:
            //i(<,>)j
            printf("(<,>)");
            return;
        case 6:
            //i(||,>)j
            printf("(||,>)");
            return;
        case 7:
            //i(<,||,>)j
            printf("(<,||,>)");
            return;
        default:
            printf("Huh?\n");
            return;
        }
    }

    void print() const{
        unsigned char  i{ 0 }, j{ 0 };
        for (i = 0; i < size; ++i) {
            for (j = 0; j < i; ++j) {
                printf("%d %d ", i, j);
                relaToStr(C[i][j]);
                printf("\n");
            }
        }
    }
};

Graph* permSolv(const Problem* P) {
    vector<unsigned char> p(P->size);
    unsigned char i{ 0 }, j{ 0 }, ii{ 0 }, jj{ 0 }, k, kk;
    unsigned char c,c2;
    bool test{ true };
    for (; i < P->size; ++i) {
        p[i] = i;
    }
    Graph* G{ new Graph(P->size) };
    int trynr(0);
    do {
        if((++trynr%10000)==0)
            printf("try %d\n", trynr);

        //Reset graph
        for (i = 0; i < P->size; ++i) {
            //printf("%d ", p[i]);
            for (j = 0; j < P->size; ++j) {
                G->V[i][j] = false;
            }
        }
        test = true;
        //printf("\n");

        for (jj = 1; jj < P->size; ++jj) {
            //printf("jj %d\n", jj);
            for (ii = jj-1; ii < unsigned char(-1); --ii) {
                //printf("ii %d\n", ii);
                i = p[ii];
                j = p[jj];
                c = P->C[i][j];
                //printf("c ");
                //Problem::relaToStr(c);
                //printf("\n");
                if (c == 4) {
                    ii = 0;
                    jj = P->size;
                    test = false;
                }
                else {
                    //i<j strictly in this permutation
                    if ((c == 1 || c == 5) && !G->V[i][j]) {
                        G->V[i][j] = true;
                        //Update everything k<i<j
                        for (kk = ii - 1; kk < unsigned char(-1); --kk) {
                            //printf("kk %d\n", kk);
                            k = p[kk];
                            if (G->V[k][i]) {
                                G->V[k][j] = true;

                                c2 = P->C[k][j];

                                //printf("c2 ");
                                //Problem::relaToStr(c2);
                                //printf("\n");
                                //k||j strictly in this permutation
                                if (c2 == 2 || c2 == 6) {
                                    kk = 0;
                                    ii = 0;
                                    jj = P->size;
                                    test = false;
                                }
                            }
                        }
                    }
                }
            }
        }
        if (test) {
            return G;
        }

    } while (std::next_permutation(p.begin(), p.end()));
    delete G;
    return nullptr;
}

Graph* permSolv2(const Problem* P) {
    vector<unsigned char> p(P->size);
    unsigned char i{ 0 }, j{ 0 }, ii{ 0 }, jj{ 0 }, k, kk;
    unsigned char c, c2;
    bool test{ true };
    for (; i < P->size; ++i) {
        p[i] = i;
    }
    Graph* G{ new Graph(P->size) };
    int trynr(0);
    do {
        if ((++trynr % 10000) == 0)
            printf("try %d\n", trynr);

        //Reset graph
        for (i = 0; i < P->size; ++i) {
            //printf("%d ", p[i]);
            for (j = 0; j < P->size; ++j) {
                G->V[i][j] = false;
            }
        }
        test = true;
        //printf("\n");

        for (jj = 1; jj < P->size; ++jj) {
            //printf("jj %d\n", jj);
            for (ii = jj - 1; ii < unsigned char(-1); --ii) {
                //printf("ii %d\n", ii);
                i = p[ii];
                j = p[jj];
                c = P->C[i][j];
                //printf("c ");
                //Problem::relaToStr(c);
                //printf("\n");
                if (c == 4) {
                    ii = 0;
                    jj = P->size;
                    test = false;
                }
                else {
                    //i<j strictly in this permutation
                    if ((c == 1 || c == 5) && !G->V[i][j]) {
                        G->V[i][j] = true;
                        //Update everything k<i<j
                        for (kk = ii - 1; kk < unsigned char(-1); --kk) {
                            //printf("kk %d\n", kk);
                            k = p[kk];
                            if (G->V[k][i]) {
                                G->V[k][j] = true;

                                c2 = P->C[k][j];

                                //printf("c2 ");
                                //Problem::relaToStr(c2);
                                //printf("\n");
                                //k||j strictly in this permutation
                                if (c2 == 2 || c2 == 6) {
                                    kk = 0;
                                    ii = 0;
                                    jj = P->size;
                                    test = false;
                                }
                            }
                        }
                    }
                    else if (!G->V[i][j]) {
                        //we let i||j, but fail it if i>j
                        if (i > j && jj-ii == 1) {
                            //printf("Kill!\n");
                            ii = 0;
                            jj = P->size;
                            test = false;
                        }
                    }
                }
            }
        }
        if (test) {
            return G;
        }

    } while (std::next_permutation(p.begin(), p.end()));
    delete G;
    return nullptr;
}

struct State {
    unsigned long long id, subId;
    set<unsigned char> L, G, Ic; 
    vector<unsigned char> v;
    unsigned char size;
    set<State*> n;
    State *bn1, *bn2, *bn3;
    pair<State*, unsigned char> parent;

    State() {}
    State(State* S, unsigned long long sub) : id(S->id), subId(sub), L(S->L), G(S->G), Ic(S->Ic), v(S->v), size(S->size+1) {}

    void addN(State *nb) {
        if (nb != this) {
            n.insert(nb);
            nb->n.insert(this);
        }
    }
};

bool validPosition(const Problem* P, State* S, unsigned char v) {
    unsigned char c, s;
    for (int i{ 0 }; i < P->size; ++i) {
        if (i == v || !(s=S->v[i])) {
            continue;
        }
        switch (P->C[i][v])
        {
        case 0:
            //Nothing allowed
            return false;
        case 1:
            //i<j
            if(s != 1)
                return false;
            break;
        case 2:
            //i||j
            if (s != 3)
                return false;
            break;
        case 3:
            //i(<,||)j
            if (s == 2)
                return false;
            break;
        case 4:
            //i>j
            if (s != 2)
                return false;
            break;
        case 5:
            //i(<,>)j
            if (s == 3)
                return false;
            break;
        case 6:
            //i(||,>)j
            if (s == 1)
                return false;
            break;
        case 7:
            //i(<,||,>)j
            break;
        default:
            printf("Huh?\n");
            break;
        }
    }
    return true;
}

void expand(const unsigned long long idBase, const unsigned long long idSize, State* S, unsigned char v, map<unsigned long long, State*> &m, vector<bool> & sh) {

#if OUTPUT >= 2
        printf("\n");
        printf("\n");
        printf("%d ", S->id);
        for (int i = 0; i < S->v.size(); ++i) {
            printf("%d:%d ", i, S->v[i]);
        }
        printf("\nExpands with %d:\n", v);
#endif
        unsigned long long id, idb1, idb2, idb3, powid, powid2, powid3;
    State *s1,*s2,*s3, tmp, *b11, *b13, *b22, *b23, *b31, *b32, *b33;

    //Basic expand of first 3
    powid = pow(BASE, v);
    powid3 = pow(2, v);
    powid2 = idBase * powid3;
    id = S->id + powid + powid2 + idSize;
    powid3 += S->subId;
    idb1 = S->bn1->id + powid + powid2 + idSize;
    idb2 = S->bn2->id + powid*2 + powid2 + idSize;
    idb3 = S->bn3->id + powid*3 + powid2 + idSize;
    auto tryEmp{ m.try_emplace(id, nullptr) };
    if (tryEmp.second)
        tryEmp.first->second = new State(S, powid3);
    s1 = tryEmp.first->second;
    if (tryEmp.second) {

        s1->id = id;
        s1->L.emplace(v);
        s1->parent = { S,v };
        s1->v[v] = 1;

        //try creating bases
        tryEmp = m.try_emplace(idb1, nullptr);
        if (tryEmp.second)
            tryEmp.first->second = new State(S->bn1, powid3);
        b11 = tryEmp.first->second;
        if (tryEmp.second) {
            b11->id = idb1;
            b11->L.emplace(v);
            b11->parent = { S,v };
            b11->v[v] = 1;
#if OUTPUT >= 2
                printf("b1 %d ", b11->id);
                for (int i = 0; i < b11->v.size(); ++i) {
                    printf("%d:%d ", i, b11->v[i]);
                }
                printf("\n");
#endif
        }

        tryEmp = m.try_emplace(idb2, nullptr);
        if (tryEmp.second)
            tryEmp.first->second = new State(S->bn2, powid3);
        b22 = tryEmp.first->second;
        if (tryEmp.second) {
            b22->id = idb2;
            b22->G.emplace(v);
            b22->parent = { S,v };
            b22->v[v] = 2;
#if OUTPUT >= 2
                printf("b2 %d ", b22->id);
                for (int i = 0; i < b22->v.size(); ++i) {
                    printf("%d:%d ", i, b22->v[i]);
                }
                printf("\n");
#endif
        }

        tryEmp = m.try_emplace(idb3, nullptr);
        if (tryEmp.second)
            tryEmp.first->second = new State(S->bn3, powid3);
        b33 = tryEmp.first->second;
        if (tryEmp.second) {
            b33->id = idb3;
            b33->Ic.emplace(v);
            b33->parent = { S,v };
            b33->v[v] = 3;
#if OUTPUT >= 2
                printf("b3 %d ", b33->id);
                for (int i = 0; i < b33->v.size(); ++i) {
                    printf("%d:%d ", i, b33->v[i]);
                }
                printf("\n");
#endif

            //We really only need to try and create 1
            //If one exists, they all do
            b11->addN(b22);
            b11->addN(b33);
            b22->addN(b33);

            b11->bn1 = b11;
            b22->bn1 = b11;
            b33->bn1 = b11;
            b11->bn2 = b22;
            b22->bn2 = b22;
            b33->bn2 = b22;
            b11->bn3 = b33;
            b22->bn3 = b33;
            b33->bn3 = b33;

            sh[powid3] = true;

        }

        s1->bn1 = b11;
        s1->bn2 = b22;
        s1->bn3 = b33;
    }
    else {
        b11 = m.find(idb1)->second;
        b22 = m.find(idb2)->second;
        b33 = m.find(idb3)->second;
    }
#if OUTPUT >= 2
        printf("%d ", s1->id);
        for (int i = 0; i < s1->v.size(); ++i) {
            printf("%d:%d ", i, s1->v[i]);
        }
        printf("\n");
#endif

    id += powid;
    tryEmp = m.try_emplace(id, nullptr);
    if (tryEmp.second)
        tryEmp.first->second = new State(S, powid3);
    s2 = tryEmp.first->second;
    if (tryEmp.second) {
        s2->id = id;
        s2->G.emplace(v);
        s2->parent = { S,v };
        s2->v[v] = 2;
        s2->bn1 = b11;
        s2->bn2 = b22;
        s2->bn3 = b33;
    }
#if OUTPUT >= 2
        printf("%d ", s2->id);
        for (int i = 0; i < s2->v.size(); ++i) {
            printf("%d:%d ", i, s2->v[i]);
        }
        printf("\n");
#endif

    id += powid;
    tryEmp = m.try_emplace(id, nullptr);
    if (tryEmp.second)
        tryEmp.first->second = new State(S, powid3);
    s3 = tryEmp.first->second;
    if (tryEmp.second) {
        s3->id = id;
        s3->Ic.emplace(v);
        s3->parent = { S,v };
        s3->v[v] = 3;
        s3->bn1 = b11;
        s3->bn2 = b22;
        s3->bn3 = b33;
    }

#if OUTPUT >= 2
        printf("%d ", s3->id);
        for (int i = 0; i < s3->v.size(); ++i) {
            printf("%d:%d ", i, s3->v[i]);
        }
        printf("\n");
#endif

    s1->addN(s2);
    s1->addN(s3);
    s2->addN(s3);
    b11->addN(s1);
    b22->addN(s1);
    b33->addN(s1);
    b11->addN(s2);
    b22->addN(s2);
    b33->addN(s2);
    b11->addN(s3);
    b22->addN(s3);
    b33->addN(s3);
    //Done with the basic expand

    //Expand of base
    if (S->G.empty()) {
        id = S->bn1->id + powid * 3 + powid2 + idSize;
        tryEmp = m.try_emplace(id, nullptr);
        if (tryEmp.second)
            tryEmp.first->second = new State(S->bn1, powid3);
        b13 = tryEmp.first->second;
        if (tryEmp.second) {
            b13->id = id;
            b13->Ic.emplace(v);
            b13->parent = { S,v };
            b13->v[v] = 3;
            b13->bn1 = b11;
            b13->bn2 = b22;
            b13->bn3 = b33;
        }
#if OUTPUT >= 2
        printf("b13 %d ", b13->id);
        for (int i = 0; i < b13->v.size(); ++i) {
            printf("%d:%d ", i, b13->v[i]);
        }
        printf("\n");
#endif
    }
    else
    {
        b13 = b11;
    }

    if (S->L.empty()) {
        id = S->bn2->id + powid * 3 + powid2 + idSize;
        tryEmp = m.try_emplace(id, nullptr);
        if (tryEmp.second)
            tryEmp.first->second = new State(S->bn2, powid3);
        b23 = tryEmp.first->second;
        if (tryEmp.second) {
            b23->id = id;
            b23->Ic.emplace(v);
            b23->parent = { S,v };
            b23->v[v] = 3;
            b23->bn1 = b11;
            b23->bn2 = b22;
            b23->bn3 = b33;
        }

#if OUTPUT >= 2
        printf("b23 %d ", b23->id);
        for (int i = 0; i < b23->v.size(); ++i) {
            printf("%d:%d ", i, b23->v[i]);
        }
        printf("\n");
#endif
    }
    else
    {
        b23 = b22;
    }

    id = S->bn3->id + powid + powid2 + idSize;
    for (int i : S->L) {
        id -= pow(BASE, i) * 2;
    }
    tryEmp = m.try_emplace(id, nullptr);
    if (tryEmp.second)
        tryEmp.first->second = new State(S->bn3, powid3);
    b31 = tryEmp.first->second;
    if (tryEmp.second) {
        b31->id = id;
        b31->L.emplace(v);
        b31->parent = { S,v };
        b31->v[v] = 1;
        for (int i : S->L) {
            b31->L.emplace(i);
            b31->Ic.erase(i);
            b31->v[i] = 1;
        }
        b31->bn1 = b11;
        b31->bn2 = b22;
        b31->bn3 = b33;
    }
#if OUTPUT >= 2
        printf("b31 %d ", b31->id);
    for (int i = 0; i < b31->v.size(); ++i) {
        printf("%d:%d ", i, b31->v[i]);
    }
    printf("\n");
#endif

    id = S->bn3->id + powid*2 + powid2 + idSize;
    for (int i : S->G) {
        id -= pow(BASE, i);
    }
    tryEmp = m.try_emplace(id, nullptr);
    if (tryEmp.second)
        tryEmp.first->second = new State(S->bn3, powid3);
    b32 = tryEmp.first->second;
    if (tryEmp.second) {
        b32->id = id;
        b32->G.emplace(v);
        b32->parent = { S,v };
        b32->v[v] = 2;
        for (int i : S->G) {
            b32->G.emplace(i);
            b32->Ic.erase(i);
            b32->v[i] = 2;
        }
        b32->bn1 = b11;
        b32->bn2 = b22;
        b32->bn3 = b33;
    }
#if OUTPUT >= 2
    printf("b32 %d ", b32->id);
    for (int i = 0; i < b32->v.size(); ++i) {
        printf("%d:%d ", i, b32->v[i]);
    }
    printf("\n");
#endif

    s1->addN(b13);
    s1->addN(b23);
    s1->addN(b31);
    s1->addN(b32);
    s2->addN(b13);
    s2->addN(b23);
    s2->addN(b31);
    s2->addN(b32);
    s3->addN(b13);
    s3->addN(b23);
    s3->addN(b31);
    s3->addN(b32);

    b11->addN(b13);
    b11->addN(b23);
    b11->addN(b31);
    b11->addN(b32);
    b22->addN(b13);
    b22->addN(b23);
    b22->addN(b31);
    b22->addN(b32);
    b33->addN(b13);
    b33->addN(b23);
    b33->addN(b31);
    b33->addN(b32);

    b13->addN(b23);
    b13->addN(b31);
    b13->addN(b32);

    b23->addN(b31);
    b23->addN(b32);

    b31->addN(b32);


    //Expand of neighbours
    State *n1{ nullptr }, *n2{ nullptr };
    for (State* it : S->n) {
        if (intersects(it->G, S->L)) {
            id = it->id + powid * 2 + powid2 + idSize;
            tryEmp = m.try_emplace(id, nullptr);
            if (tryEmp.second)
                tryEmp.first->second = new State(it, powid3);
            n1 = tryEmp.first->second;
            if (tryEmp.second) {
                n1->id = id;
                n1->G.emplace(v);
                n1->parent = { S,v };
                n1->v[v] = 2;
                n1->addN(b11);
                n1->addN(b22);
                n1->addN(b33);
                n1->bn1 = b11;
                n1->bn2 = b22;
                n1->bn3 = b33;
            }
            n1->addN(s1);
            n1->addN(s2);
            n1->addN(s3);

            n1->addN(b13);
            n1->addN(b23);
            n1->addN(b31);
            n1->addN(b32);

#if OUTPUT >= 2
                printf("%d ", n1->id);
                for (int i = 0; i < n1->v.size(); ++i) {
                    printf("%d:%d ", i, n1->v[i]);
                }
                printf("\n");
#endif
        }
        else if (intersects(it->L, S->G)) {
            id = it->id + powid + powid2 + idSize;
            tryEmp = m.try_emplace(id, nullptr);
            if (tryEmp.second)
                tryEmp.first->second = new State(it, powid3);
            n1 = tryEmp.first->second;
            if (tryEmp.second) {
                n1->id = id;
                n1->L.emplace(v);
                n1->parent = { S,v };
                n1->v[v] = 1;
                n1->addN(b11);
                n1->addN(b22);
                n1->addN(b33);
                n1->bn1 = b11;
                n1->bn2 = b22;
                n1->bn3 = b33;
            }
            n1->addN(s1);
            n1->addN(s2);
            n1->addN(s3);

            n1->addN(b13);
            n1->addN(b23);
            n1->addN(b31);
            n1->addN(b32);

#if OUTPUT >= 2
            printf("%d ", n1
                    ->id);
            for (int i = 0; i < n1->v.size(); ++i) {
                printf("%d:%d ", i, n1->v[i]);
            }
            printf("\n");
#endif
        }
        else {
            id = it->id + powid * 3 + powid2 + idSize;
            tryEmp = m.try_emplace(id, nullptr);
            if (tryEmp.second)
                tryEmp.first->second = new State(it, powid3);
            n1 = tryEmp.first->second;
            if (tryEmp.second) {
                n1->id = id;
                n1->Ic.emplace(v);
                n1->parent = { S,v };
                n1->v[v] = 3;
                n1->addN(b11);
                n1->addN(b22);
                n1->addN(b33);
                n1->bn1 = b11;
                n1->bn2 = b22;
                n1->bn3 = b33;
            }
            n1->addN(s1);
            n1->addN(s2);
            n1->addN(s3);

            n1->addN(b13);
            n1->addN(b23);
            n1->addN(b31);
            n1->addN(b32);

#if OUTPUT >= 2
                printf("%d ", n1->id);
                for (int i = 0; i < n1->v.size(); ++i) {
                    printf("%d:%d ", i, n1->v[i]);
                }
                printf("\n");
#endif

            if (subset(it->L, S->L) && subset(S->G, it->G)) {
                id = it->id + powid * 2 + powid2 + idSize;
                tryEmp = m.try_emplace(id, nullptr);
                if (tryEmp.second)
                    tryEmp.first->second = new State(it, powid3);
                n2 = tryEmp.first->second;
                if (tryEmp.second) {
                    n2->id = id;
                    n2->G.emplace(v);
                    n2->parent = { S,v };
                    n2->v[v] = 2;
                    n2->addN(b11);
                    n2->addN(b22);
                    n2->addN(b33);
                    n2->bn1 = b11;
                    n2->bn2 = b22;
                    n2->bn3 = b33;
                }
                n2->addN(n1);
                n2->addN(s1);
                n2->addN(s2);
                n2->addN(s3);

                n2->addN(b13);
                n2->addN(b23);
                n2->addN(b31);
                n2->addN(b32);

#if OUTPUT >= 2
                    printf("%d ", n2->id);
                    for (int i = 0; i < n2->v.size(); ++i) {
                        printf("%d:%d ", i, n2->v[i]);
                    }
                    printf("\n");
#endif
            }
            if (subset(it->G, S->G) && subset(S->L, it->L)) {
                id = it->id + powid + powid2 + idSize;
                tryEmp = m.try_emplace(id, nullptr);
                if (tryEmp.second)
                    tryEmp.first->second = new State(it, powid3);
                n2 = tryEmp.first->second;
                if (tryEmp.second) {
                    n2->id = id;
                    n2->L.emplace(v);
                    n2->parent = { S,v };
                    n2->v[v] = 1;
                    n2->addN(b11);
                    n2->addN(b22);
                    n2->addN(b33);
                    n2->bn1 = b11;
                    n2->bn2 = b22;
                    n2->bn3 = b33;
                }
                n2->addN(n1);
                n2->addN(s1);
                n2->addN(s2);
                n2->addN(s3);

                n2->addN(b13);
                n2->addN(b23);
                n2->addN(b31);
                n2->addN(b32);

#if OUTPUT >= 2
                    printf("%d ", n2->id);
                    for (int i = 0; i < n2->v.size(); ++i) {
                        printf("%d:%d ", i, n2->v[i]);
                    }
                    printf("\n");
#endif
            }
        }
    }

#if OUTPUT >= 3
    system("Pause");
#endif
}

pair<Graph*, unsigned char> DPSolv(const Problem* P) {
    unsigned char v;
    unsigned long long subId{0};
    bool solve{ false };
    vector<bool> speedHelper(pow(2,P->size), false);
    unsigned int aliveCount{ 1 };
    unsigned char oldSize(0);
    map<unsigned long long, State*> m;
    State* s{ new State };
    s->id = 0;
    s->v.resize(P->size);
    s->parent = { nullptr, -1 };
    s->bn1 = s;
    s->bn2 = s;
    s->bn3 = s;
    s->subId = 0;
    s->size = 0;
    speedHelper[0] = true;

    m.insert({ 0,s });
    unsigned int stateNr(0);
    for (auto it(m.begin()); it != m.end(); ++it){
        if ((++stateNr % 1000) == 0)
            printf("state %d\n", stateNr);
        s = it->second;
        if (oldSize < s->size) {
            if (aliveCount) {
#if OUTPUT >= 2
                printf("killed on size %lu\n", oldSize-1);
#endif
                it = m.end();
                break;
            }
            else {
                ++oldSize;
                aliveCount = choose(P->size, s->size);
#if OUTPUT >= 2
                printf("count set to %lu\n", aliveCount);
#endif
            }
        }
        if (speedHelper[s->subId]) {
            speedHelper[s->subId] = false;
            --aliveCount;
#if OUTPUT >= 2
            printf("%lu visited the first time, %lu still alive\n", s->subId, aliveCount);
#endif
        }
#if OUTPUT >= 2
            printf("id %d\n", s->id);
            printf("%d ", s->id);
            for (int i = 0; i < s->v.size(); ++i) {
                printf("%d:%d ", i, s->v[i]);
            }
            printf("\n");
#endif
            for (v = 0; v < P->size; ++v) {
                if (!s->v[v]) {
                    if (validPosition(P, s, v)) {
                        expand(P->id, P->sizeId, s, v, m, speedHelper);
                    }

#if OUTPUT >= 2
                    else
                        printf("unvalid %d\n", v);
#endif
                    }
                }
            if (speedHelper.back()) {
                solve = true;
                break;
            }
        }
    

#if OUTPUT >= 2
    auto it = m.rbegin();
    printf("end %d\n", it->second->id);
    for (int i = 0; i < it->second->v.size(); ++i) {
        printf("%d:%d ", i, it->second->v[i]);
    }
    printf("\n");
#endif
    printf("size %d\n", m.size());

    Graph* G(nullptr);

    if (solve) {//m.find(pow(4, P->size) - 1) != m.end()) {
        printf("Solution!\n");
        G = new Graph(P->size);
        State* s(m.rbegin()->second);
        while (s->parent.first != nullptr) {
            v = s->parent.second;
            s = s->parent.first;
#if OUTPUT >= 2
            printf("graph build %d\n", s->id);
            for (int i = 0; i < s->v.size(); ++i) {
                printf("%d:%d ", i, s->v[i]);
            }
            printf("\n");
#endif
            for (int i : s->L) {
                for (int j : s->G) {
                    G->V[i][j] = true;
                }
                G->V[i][v] = true;
            }
            for (int j : s->G) {
                G->V[v][j] = true;
            }
#if OUTPUT >= 2
            G->print();
#endif
        }
    }

    //No memory leaks please
    for (auto it(m.begin()); it != m.end(); ++it) {
        delete it->second;
    }
    
    return { G, oldSize+1 };
}

bool checkSubs(const Problem& P, unsigned char n, unsigned char i, vector<unsigned char> &v) {
    if (!n) {
        Problem e(P, v);
        Graph *G(permSolv2(&e));
        bool ret(G != nullptr);
        delete G;
        return ret;
    }
    else {
        --n;
        for (int j{ 0 }; j < i; ++j) {
            v[n] = j;
            if (!checkSubs(P, n, j, v))
                return false;
        }
        return true;
    }
}

#define RANDOM 0

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);

    /*


    18763


21559


21993

18293

1584733861


1 0 (||,>)
2 0 (||)
2 1 (>)
3 0 (<)
3 1 (||)
3 2 (<,>)


    */

    std::srand(static_cast<long unsigned int>(std::chrono::high_resolution_clock::now().time_since_epoch().count()));
    long unsigned int seed(rand());
    //seed = 3863331080; //size 7
    //seed = 612602168; //size 9
    //seed = 1927547004; // size 12
    std::srand(seed);
    printf("%lu seed\n", seed);
    long unsigned int tt(static_cast<long unsigned int>(std::chrono::high_resolution_clock::now().time_since_epoch().count()));
    int nr(0), solved(0), earlybads(0), nonsolved(0);
    int size(10);
    int earlyTestSize(0);
    printf("Input problem sizes:\n");
    cin >> size;
    printf("Input early test sizes:\n");
    cin >> earlyTestSize;
    printf("\n");
    vector<unsigned char> testVector(earlyTestSize);
    //for(;nr < 2*pow(7,size*(size-1)/2-1);++nr){
    for (; true; ++nr) {
        printf("nr %d, solved %d, nonsolved %d, early bads %d\n", nr, solved, nonsolved, earlybads);
        //if (nr % 10 == 0)
        //    printf("nr %d\n", nr);
#if RANDOM = 1
        if (tt != static_cast<long unsigned int>(std::chrono::high_resolution_clock::now().time_since_epoch().count())) {
            tt = static_cast<long unsigned int>(std::chrono::high_resolution_clock::now().time_since_epoch().count());
            seed = tt;
        }
        else
            seed = rand();

        std::srand(seed);


        printf("%lu seed\n", seed);
#endif
        Problem e(size);
        //Problem e(size, nr);

        //check that the problem is not wrong for x variables already
        if (checkSubs(e, earlyTestSize, size, testVector)) {
            //Problem e(size, nr);
            //++nr;

            pair<Graph*, unsigned char> F{ DPSolv(&e) };
            Graph* H{ F.first };
            //Graph* G{ permSolv2(&e) };
            //Graph* G2{ permSolv2(&e) };

            if (H != nullptr) {
                if (e.sat(H)) {
                    solved++;
                    printf("confirmed\n");
                }
                else {
                    printf("Failure!\n");
                    e.print();
                    printf("Failure!\n");
                    H->print();
                    system("Pause");
                }
                //H->print();
            }
            else {
                if (checkSubs(e, F.second, size, vector<unsigned char>(F.second))) {
                    printf("worked?\n");
                    Graph* G{ permSolv2(&e) };
                    if (G == nullptr) {
                        ++nonsolved;
                        printf("nope\n");
                    }
                    else {
                        G->print();
                        if (e.sat(G)) {
                            printf("worked!\n");
                            if (H == nullptr || !e.sat(H)) {
                                system("Pause");
                            }
                        }
                    }
                    delete G;
                }
                else {
                    ++nonsolved;
                }
                //Graph* G{ permSolv2(&e) };
                /*if (G == nullptr)
                {
                    printf("nope\n");
                    if (H != nullptr)
                        system("Pause");
                }
                else {
                    G->print();
                    if (e.sat(G))
                    {
                        printf("worked\n");
                        if (H == nullptr || !e.sat(H)) {
                            system("Pause");
                        }
                    }
                }
                delete G;*/
            }
            delete H;
        }
        else
        {
            printf("Early bad\n");
            ++earlybads;
        }
    }




    system("Pause");
}