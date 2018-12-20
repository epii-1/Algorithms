//https://open.kattis.com/sessions/ghkq7h/problems/numbersetseasy
//Leif Eriksson
//leier318
//Ugly bruteforce, but works
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
#include <iomanip>
#include <memory>
#include <cstdint>
#include <cstring>

using namespace std;

#define _UNLOCKED 1
#if _UNLOCKED
#define gc() getchar_unlocked()
#else
#define gc() getchar()
#endif

//https://www.geeksforgeeks.org/fast-io-for-competitive-programming/
template<typename T>
void fastScan(T &number) {
    register T c;

    number = 0;

    // extract current character from buffer
    c = gc();
    while (!(c > 47 && c < 58))
        c = gc();

    // Keep on extracting characters if they are integers
    // i.e ASCII Value lies from '0'(48) to '9' (57)
    for (; (c>47 && c<58); c = gc())
        number = number * 10 + c - 48;
}

template<typename T>
void fastFill(T* v, const T& x, size_t n) {
    if (n == 0)
        return;
    size_t s(1);
    *v = x;
    while (s + s <= n) {
        memcpy((v + s), v, s * sizeof(x));
        s += s;
    }
    memcpy((v + s), v, (n - s) * sizeof(x));
}

struct myBitset {
	myBitset(size_t s, bool val = false) : _trueSize{ s }, _s((s >> 3) + bool(s & 7)), _v{ new char[_s] }, _allocSize{ _s } {
		fastFill(_v, (char)(255 * val), _s);
	}

	~myBitset() {
		delete[] _v;
	}

    bool inline operator[] (size_t index) const {
        return _v[index >> 3] & _c[index & 7];
    }

    void inline set(size_t index, bool val) {
        if (val) {
            _v[index >> 3] |= _c[index & 7];
        }
        else {
            _v[index >> 3] &= _n[index & 7];
        }
    }

	void resize(size_t newSize, bool val) {
		if (newSize > _trueSize) {
			size_t _newSize((newSize >> 3) + bool(newSize & 7));
			if (_newSize > _allocSize) {
				char *t(new char[_newSize]);
				memcpy(t, _v, _newSize * sizeof(char));
				fastFill(t + _allocSize, (char)(255 * val), _newSize - _allocSize);
			}
			for (size_t i{ _trueSize }; i < newSize; ++i)
				set(i, val);
			_trueSize = newSize;
			_allocSize = _newSize;	
		} 
		else if (newSize < _trueSize) 
			_trueSize = newSize; //Frankly, we dont give a shit
	}

    void inline flip(size_t index) {
        set(index, !(_v[index >> 3] & _c[index & 7]));
    }

    size_t count() const {
        return count(0, _trueSize);
    }

    size_t count(const size_t from, const size_t to) const {
        const size_t _to((to >> 3) + bool(to & 7));
        size_t nr{ 0 }, i;
        for (size_t i{ from >> 3 }; i < _to; ++i) {
            nr += (((_v[i] & 1) + ((_v[i] & 2) >> 1)) + (((_v[i] & 4) >> 2) + ((_v[i] & 8) >> 3))) +
                ((((_v[i] & 16) >> 4) + ((_v[i] & 32) >> 5)) + (((_v[i] & 64) >> 6) + ((_v[i] & 128) >> 7)));
        }
        for (i = from - (from & 7); i < from; ++i)
            nr -= operator[](i);
        for (i = to; i < _to << 3; ++i)
            nr -= operator[](i);
        return nr;
    }

    const static vector<char> _c;
    const static vector<char> _n;
    size_t _trueSize;
    size_t _s;
	size_t _allocSize;
	char *_v;
};

const vector<char> myBitset::_c{ char(1), char(2), char(4), char(8),
char(16), char(32), char(64), char(128) };
const vector<char> myBitset::_n{ char(254), char(253), char(251), char(247),
char(239), char(223), char(191), char(127) };

#define RETURN_PRIME true
#define PRIME_COUNT false
#define RETURN_SET true
size_t prime_sieve(int n 
#if RETURN_PRIME
    , vector<int> & prime
#endif
#if RETURN_SET
    , myBitset& p
#endif   
    ) {
    //Hur mycket jag än försöker rulla ut någon av looparna verkar det inte göra någon skillnad
    //Utan count kommer den ner på 0.13s

    //Simple klarar det på 0.16s
    //0.14s utan count

    //Bra med ~200 rader kod för 0.01s :)
    //https://liu.kattis.com/submissions/2887308

#if RETURN_SET == false
    myBitset p(n >> 1, 1);
#endif

#if RETURN_PRIME
    if(n > 1)
        prime.emplace_back(2);
    if (n > 2)
        prime.emplace_back(3);
    if (n > 4)
        prime.emplace_back(5);
#endif
    //i, j, i*2, n/2, i*i/2, (i+1)*(i+1)/2-i*i/2, n2/2
    int i, j, i2, nh, sqh{ 24 }, derh{ 16 }, n2h, wall, i3;

    p.set(0, 0);

#if PRIME_COUNT
    size_t nr{ 0 };
    if (n >= 5) {
        ++nr;
        if (n >= 3) {
            ++nr;
            if (n >= 2)
                ++nr;
        }
    }
#endif

    nh = n >> 1;
    n2h = nh - 30;
    for (i = 4; i < n2h; i += 30) {
        p.set(i, 0);
        p.set(i + 15, 0);
        p.set(i + 3, 0);
        p.set(i + 18, 0);
        p.set(i + 6, 0);
        p.set(i + 21, 0);
        p.set(i + 9, 0);
        p.set(i + 24, 0);
        p.set(i + 12, 0);
        p.set(i + 27, 0);
    }
    for (; i < nh; i += 3)
        p.set(i, 0);
    for (i = 12; i < n2h; i += 30) {
        p.set(i, 0);
        p.set(i + 20, 0);
        p.set(i + 5, 0);
        p.set(i + 25, 0);
        p.set(i + 10, 0);
        p.set(i + 15, 0);
    }
    for (; i < nh; i += 5)
        p.set(i, 0);

    n2h = (n - n % 30) >> 1;

    for (i = 3; sqh < n2h;) {
        //7
        if (p[i]) {
            i2 = (i << 1) + 1;
#if RETURN_PRIME
            prime.emplace_back(i2);
#endif
#if PRIME_COUNT
            ++nr;
#endif
            i3 = i2 << 3;
            wall = nh - i3;
            for (j = sqh; j < wall; j += i3) {
                p.set(j, 0);
                p.set(j + i2, 0);
                p.set(j + (i2 << 1), 0);
                p.set(j + (i2 << 1) + i2, 0);
                p.set(j + (i2 << 2), 0);
                p.set(j + (i2 << 2) + i2, 0);
                p.set(j + i3 - (i2 << 1), 0);
                p.set(j + i3 - i2, 0);
            }
            for (; j < nh; j += i2)
                p.set(j, 0);
        }
        sqh += derh + derh + 4, derh += 8, i += 2;

        //11
        if (p[i]) {
            i2 = (i << 1) + 1;
#if RETURN_PRIME
            prime.emplace_back(i2);
#endif
#if PRIME_COUNT
            ++nr;
#endif
            i3 = i2 << 3;
            wall = nh - i3;
            for (j = sqh; j < wall; j += i3) {
                p.set(j, 0);
                p.set(j + i2, 0);
                p.set(j + (i2 << 1), 0);
                p.set(j + (i2 << 1) + i2, 0);
                p.set(j + (i2 << 2), 0);
                p.set(j + (i2 << 2) + i2, 0);
                p.set(j + i3 - (i2 << 1), 0);
                p.set(j + i3 - i2, 0);
            }
            for (; j < nh; j += i2)
                p.set(j, 0);
        }
        sqh += derh, derh += 4, ++i;

        //13
        if (p[i]) {
            i2 = (i << 1) + 1;
#if RETURN_PRIME
            prime.emplace_back(i2);
#endif
#if PRIME_COUNT
            ++nr;
#endif
            i3 = i2 << 3;
            wall = nh - i3;
            for (j = sqh; j < wall; j += i3) {
                p.set(j, 0);
                p.set(j + i2, 0);
                p.set(j + (i2 << 1), 0);
                p.set(j + (i2 << 1) + i2, 0);
                p.set(j + (i2 << 2), 0);
                p.set(j + (i2 << 2) + i2, 0);
                p.set(j + i3 - (i2 << 1), 0);
                p.set(j + i3 - i2, 0);
            }
            for (; j < nh; j += i2)
                p.set(j, 0);
        }
        sqh += derh + derh + 4, derh += 8, i += 2;

        //17
        if (p[i]) {
            i2 = (i << 1) + 1;
#if RETURN_PRIME
            prime.emplace_back(i2);
#endif
#if PRIME_COUNT
            i3 = i2 << 3;
            ++nr;
#endif
            i3 = i2 << 3;
            wall = nh - i3;
            for (j = sqh; j < wall; j += i3) {
                p.set(j, 0);
                p.set(j + i2, 0);
                p.set(j + (i2 << 1), 0);
                p.set(j + (i2 << 1) + i2, 0);
                p.set(j + (i2 << 2), 0);
                p.set(j + (i2 << 2) + i2, 0);
                p.set(j + i3 - (i2 << 1), 0);
                p.set(j + i3 - i2, 0);
            }
            for (; j < nh; j += i2)
                p.set(j, 0);
        }
        sqh += derh, derh += 4, ++i;

        //19
        if (p[i]) {
            i2 = (i << 1) + 1;
#if RETURN_PRIME
            prime.emplace_back(i2);
#endif
#if PRIME_COUNT
            ++nr;
#endif
            i3 = i2 << 3;
            wall = nh - i3;
            for (j = sqh; j < wall; j += i3) {
                p.set(j, 0);
                p.set(j + i2, 0);
                p.set(j + (i2 << 1), 0);
                p.set(j + (i2 << 1) + i2, 0);
                p.set(j + (i2 << 2), 0);
                p.set(j + (i2 << 2) + i2, 0);
                p.set(j + i3 - (i2 << 1), 0);
                p.set(j + i3 - i2, 0);
            }
            for (; j < nh; j += i2)
                p.set(j, 0);
        }
        sqh += derh + derh + 4, derh += 8, i += 2;

        //23
        if (p[i]) {
            i2 = (i << 1) + 1;
#if RETURN_PRIME
            prime.emplace_back(i2);
#endif
#if PRIME_COUNT
            ++nr;
#endif
            i3 = i2 << 3;
            wall = nh - i3;
            for (j = sqh; j < wall; j += i3) {
                p.set(j, 0);
                p.set(j + i2, 0);
                p.set(j + (i2 << 1), 0);
                p.set(j + (i2 << 1) + i2, 0);
                p.set(j + (i2 << 2), 0);
                p.set(j + (i2 << 2) + i2, 0);
                p.set(j + i3 - (i2 << 1), 0);
                p.set(j + i3 - i2, 0);
            }
            for (; j < nh; j += i2)
                p.set(j, 0);
        }
        sqh += derh * 3 + 12, derh += 12, i += 3;

        //29
        if (p[i]) {
            i2 = (i << 1) + 1;
#if RETURN_PRIME
            prime.emplace_back(i2);
#endif
#if PRIME_COUNT
            ++nr;
#endif
            i3 = i2 << 3;
            wall = nh - i3;
            for (j = sqh; j < wall; j += i3) {
                p.set(j, 0);
                p.set(j + i2, 0);
                p.set(j + (i2 << 1), 0);
                p.set(j + (i2 << 1) + i2, 0);
                p.set(j + (i2 << 2), 0);
                p.set(j + (i2 << 2) + i2, 0);
                p.set(j + i3 - (i2 << 1), 0);
                p.set(j + i3 - i2, 0);
            }
            for (; j < nh; j += i2)
                p.set(j, 0);
        }
        sqh += derh, derh += 4, ++i;

        //31
        if (p[i]) {
            i2 = (i << 1) + 1;
#if RETURN_PRIME
            prime.emplace_back(i2);
#endif
#if PRIME_COUNT
            ++nr;
#endif
            i3 = i2 << 3;
            wall = nh - i3;
            for (j = sqh; j < wall; j += i3) {
                p.set(j, 0);
                p.set(j + i2, 0);
                p.set(j + (i2 << 1), 0);
                p.set(j + (i2 << 1) + i2, 0);
                p.set(j + (i2 << 2), 0);
                p.set(j + (i2 << 2) + i2, 0);
                p.set(j + i3 - (i2 << 1), 0);
                p.set(j + i3 - i2, 0);
            }
            for (; j < nh; j += i2)
                p.set(j, 0);
        }
        sqh += derh * 3 + 12, derh += 12, i += 3;
    }

    for (; sqh < nh; sqh += derh, derh += 4, ++i)
        if (p[i]) {
            i2 = (i << 1) + 1;
#if RETURN_PRIME
            prime.emplace_back(i2);
#endif
#if PRIME_COUNT
            ++nr;
#endif
            i3 = i2 << 3;
            wall = nh - i3;
            for (j = sqh; j < wall; j += i3) {
                p.set(j, 0);
                p.set(j + i2, 0);
                p.set(j + (i2 << 1), 0);
                p.set(j + (i2 << 1) + i2, 0);
                p.set(j + (i2 << 2), 0);
                p.set(j + (i2 << 2) + i2, 0);
                p.set(j + i3 - (i2 << 1), 0);
                p.set(j + i3 - i2, 0);
            }
            for (; j < nh; j += i2)
                p.set(j, 0);
        }

#if RETURN_PRIME

    i2 = (i << 1) + 1;
    int maxx{ min(i2 - i2 % 30 + 30,n) >> 1 };

    for (; i < maxx; ++i) {
        if (p[i]) {
	        prime.emplace_back((i << 1) + 1);
#if PRIME_COUNT
            ++nr;
#endif
        }
    }

    for (; i < n2h;) {
        //1
        if (p[i]) {
	        prime.emplace_back((i << 1) + 1);
#if PRIME_COUNT
            ++nr;
#endif
        }
        i += 3;

        //7
        if (p[i]) {
	        prime.emplace_back((i << 1) + 1);
#if PRIME_COUNT
            ++nr;
#endif
        }
        i += 2;

        //11
        if (p[i]) {
	        prime.emplace_back((i << 1) + 1);
#if PRIME_COUNT
            ++nr;
#endif
        }
        ++i;

        //13
        if (p[i]) {
	        prime.emplace_back((i << 1) + 1);
#if PRIME_COUNT
            ++nr;
#endif
        }
        i += 2;

        //17
        if (p[i]) {
	        prime.emplace_back((i << 1) + 1);
#if PRIME_COUNT
            ++nr;
#endif
        }
        ++i;

        //19
        if (p[i]) {
	        prime.emplace_back((i << 1) + 1);
#if PRIME_COUNT
            ++nr;
#endif
        }
        i += 2;

        //23
        if (p[i]) {
	        prime.emplace_back((i << 1) + 1);
#if PRIME_COUNT
            ++nr;
#endif
        }
        i += 3;

        //29
        if (p[i]) {
	        prime.emplace_back((i << 1) + 1);
#if PRIME_COUNT
            ++nr;
#endif
        }
        ++i;
    }

    for (; i < nh; ++i) {
        if (p[i]) {
	        prime.emplace_back((i << 1) + 1);
#if PRIME_COUNT
            ++nr;
#endif
        }
    }

#if PRIME_COUNT
    return nr;
#endif
#endif
#if PRIME_COUNT
    return p.count(i, n >> 1) + nr;
#endif
    return 1;
}

#define DISJOINT_SET_SIZE 1
// To represent Disjoint Sets
//negative rank indicate parent, with semi-height -i
//positive rank indicate child with parent i
template <typename T = int>
struct DisjointSets {

	// Constructor.
    DisjointSets(T n) : rnk(new T[n])
#if DISJOINT_SET_SIZE == 1
        , size(n)
#endif
    {
     // Allocate memory
     // Initially, all vertices are in
     // different sets and have rank -1.
     //parent = new T[n];
        fastFill(rnk, -1, n);
    }

	~DisjointSets() {
		delete[] rnk;
	}

	// Find the parent of a node 'u'
	// Path Compression
	T find(T x) {
		// Make the parent of the nodes in the path
		//from u--> parent[u] point to parent[u] 
		if (rnk[x] > -1)
			return rnk[x] = find(rnk[x]);
		//while (rnk[x] > -1) {
		//	if (rnk[rnk[x]] > -1)
		//		rnk[x] = rnk[rnk[x]];
		//	x = rnk[x];
		//}
		return x;
	}

	// Union by rank
	void merge_old(T x, T y) {
		if ((x = find(x)) == (y = find(y)))
			return;
			
#if DISJOINT_SET_SIZE == 1
        --size;
#endif
		//Make tree with smaller height
		//a subtree of the other tree 
		if (rnk[x] > rnk[y])
			swap(x, y);
		else if (rnk[x] == rnk[y])
			--rnk[x];
        //Should we upate the rnk of x if the graph gets flatter?
        //How should we detect that?
		rnk[y] = x;
	}

	// Union by rank
	T merge(T x, T y) {
		return mergeFind1(x, y);
	}

#if DISJOINT_SET_SIZE == 1
    T getSize() { return size; }
#endif

private:
#if DISJOINT_SET_SIZE == 1
    T size;
#endif
	T * rnk;

	// Union by rank
	T _merge(T x, T y) {
		if (x == y)
			return x;
#if DISJOINT_SET_SIZE
        --size;
#endif
		//Make tree with smaller height
		//a subtree of the other tree 
		if (rnk[x] > rnk[y])
			swap(x, y);
		else if (rnk[x] == rnk[y])
			--rnk[x];
		return rnk[y] = x;
	}

	T mergeFind2(T x, T y) {
		/* Make the parent of the nodes in the path
		from u--> parent[u] point to parent[u] */
		if (rnk[y] > -1)
			return rnk[y] = mergeFind2(x, rnk[y]);
		return _merge(x, y);
	}

	T mergeFind1(T x, T y) {
		/* Make the parent of the nodes in the path
		from u--> parent[u] point to parent[u] */
		if (rnk[x] > -1)
			return rnk[x] = mergeFind1(rnk[x], y);
		return mergeFind2(x, y);
	}
};


int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);


    int a, b, p, i, j, l, c, k, t;
    vector<int> p_v;
    p_v.reserve(1000001);
    myBitset pr(1000001 >> 1, 1);
    
    prime_sieve(1000001, p_v, pr);

    fastScan(t);
    for (int t2(1); t2 <= t; ++t2) {

        fastScan(a);
        fastScan(b);
        fastScan(p);
        DisjointSets<int> ds(b - a + 1);
        
        vector<vector<int>> m(b - a + 1);

        for (i = a, j = 0; i <= b; ++i, ++j) {
            if (2 >= p && i % 2 == 0) {
                m[j].push_back(2);
            }
            for (l = p; l <= b && l <= i; l+=2) {
                if (pr[l >> 1] && i % l == 0) {
                    m[j].push_back(l);
                }
            }
        }

        for (i = 0; i < b - a; ++i) {
            c = ds.find(i)
            for (j = i + 1; j < b - a + 1; ++j) {
                if (c != ds.find(j)) {
                    for (l = 0; l < m[i].size(); ++l) {
                        for (k = 0; k < m[j].size(); ++k) {
                            if (m[i][l] == m[j][k]) {
                                c = ds.merge(i, j);
                                break;
                            }
                        }
                    }
                }
            }
        }

        printf("Case #%d: %d\n", t2, ds.getSize());
    }

    system("Pause");
    return 0;
}

/*
2
10 20 5
10 20 3
*/
