//Leif Eriksson
#include <vector>
#include <cstring>

#define FENWICK_MODULUS false
#define FENWICK_VECTOR_UPDATE false
template<typename T, typename S = int>
class FenwickTree {
    /*            n  --> No. of elements present in input array.
    BITree[0..n] --> Array that represents Binary Indexed Tree.
    arr[0..n-1]  --> Input array for whic prefix sum is evaluated. */
public:

    FenwickTree(S n
#if FENWICK_MODULUS
        , T mod
#endif
    ) : _n{ n + 1 }, _v(n + 1)
#if FENWICK_MODULUS
        , mod(mod)
#endif
#if FENWICK_VECTOR_UPDATE
        , _u(n + 1)
#endif
    {}

    // Constructs and returns a Binary Indexed Tree for given
    // array of size n.
    FenwickTree(const std::vector<T> &v
#if FENWICK_MODULUS
        , T mod
#endif
    ) : _n{ v.size() + 1 }, _v(v.size() + 1)
#if FENWICK_MODULUS
        , mod(mod)
#endif
#if FENWICK_VECTOR_UPDATE
        , _u(v.size() + 1)
#endif
    {
        // Store the actual values in BITree[] using update()
        for (S i(0); i < v.size(); ++i)
            update(i, v[i]);
    }

    // Constructs and returns a Binary Indexed Tree for given
    // size and value.
    FenwickTree(const S &n, const T &value
#if FENWICK_MODULUS
        , T mod
#endif
    ) : _n{ n + 1 }, _v(n + 1)
#if FENWICK_MODULUS
        , mod(mod)
#endif
#if FENWICK_VECTOR_UPDATE
        , _u(n + 1)
#endif
    {
        S i{ 1 }, j;
        T t;
        _v[1] = value;
        while (i + i < _n) {
            _v[i] = i * value;
#if FENWICK_MODULUS
            _v[i] %= mod;
#endif
            memcpy((&_v[1] + i), &_v[1], i * sizeof(value));
            i <<= 1;
        }
        if (i < _n) {
            _v[i] = i * value;
#if FENWICK_MODULUS
            _v[i] %= mod;
#endif
            memcpy((&_v[1] + i), &_v[1], (n - i) * sizeof(value));
        }
    }

    // Returns sum of arr[0..index]. This function assumes
    // that the array is preprocessed and partial sums of
    // array elements are stored in BITree[].
    T sum(S index) const {
        T sum{ 0 }; // Iniialize result

        ++index; // index in BITree[] is 1 more than the index in arr[]

                 // Traverse ancestors of BITree[index]
        while (index > 0) {
            // Add current element of BITree to sum
            sum += _v[index];
#if FENWICK_MODULUS
            sum %= mod;
#endif
            // Move index to parent node in getSum View
            index -= index & (-index);
        }
        return sum;
    }

    //Including
    T sum(S index, S index2) const {
#if FENWICK_MODULUS
        return (mod + sum(index2) - sum(index - 1)) % mod;
#else
        return sum(index2) - sum(index - 1);
#endif
    }

#if FENWICK_VECTOR_UPDATE
    //Add values of vector v to index i, and j units forwards
    void vector_add(const std::vector<T> &v, S i, S j) {
        ++i;

        //fastFill(&_u[0], 0, _n);
        //++j;
        int index(0), index2;
        for (; index < j; ++index) {
            // Add 'val' to current node of BI Tree
            _v[index + i] += v[index] + _u[index + i];
            _u[index + i] = 0;
#if FENWICK_MODULUS
            _v[index + i] %= mod;
#endif
            index2 = index + i + ((index + i) & (-(index + i)));
            if (index2 < _n) {
                _u[index2] += v[index] + _u[index + i];
#if FENWICK_MODULUS
                _u[index2] %= mod;
#endif
            }
        }
        index = index + i - 1;
        index += index & (-index);
        // Traverse all ancestors and add 'val'
        while (index < _n) {
            _v[index] += _u[index];
            _u[index] = 0;
#if FENWICK_MODULUS
            _v[index] %= mod;
#endif
            index2 = index + (index & (-index));
            if (index2 < _n) {
                _u[index2] += _u[index];
#if FENWICK_MODULUS
                _u[index2] %= mod;
#endif
            }
            // Update index to that of parent in update View
            index = index2;
        }
    }

    //Subtract values of vector v to index i, and j units forwards
    void vector_sub(const std::vector<T> &v, S i, S j) {
        ++i;

        //fastFill(&_u[0], 0, _n);

        int index(0), index2;
        for (; index < j; ++index) {
            // Subtract 'val' to current node of BI Tree
#if FENWICK_MODULUS
            _v[index + i] += mod - (v[index] + _u[index + i]) % mod;
            _u[index + i] = 0;
            _v[index + i] %= mod;
#else
            _v[index + i] -= v[index] + _u[index + i];
#endif

            index2 = index + i + ((index + i) & (-(index + i)));
            if (index2 < _n) {
                _u[index2] += v[index] + _u[index + i];
#if FENWICK_MODULUS
                _u[index2] %= mod;
#endif
            }
        }
        index = index + i - 1;
        index += index & (-index);
        // Traverse all ancestors and add 'val'
        while (index < _n) {
#if FENWICK_MODULUS
            _v[index] += mod - _u[index] % mod;
            _u[index] = 0;
            _v[index] %= mod;
#else
            _v[index] -= _u[index];
#endif

            index2 = index + (index & (-index));
            if (index2 < _n) {
                _u[index2] += _u[index];
#if FENWICK_MODULUS
                _u[index2] %= mod;
#endif
            }
            // Update index to that of parent in update View
            index = index2;
        }
    }
#endif

    // Updates a node in Binary Index Tree (BITree) at given index
    // in BITree.  The given value 'val' is added to BITree[i] and 
    // all of its ancestors in tree.
    void update(S index, T val) {
        // index in BITree[] is 1 more than the index in arr[]
        ++index;

        // Traverse all ancestors and add 'val'
        while (index < _n) {
            // Add 'val' to current node of BI Tree
            _v[index] += val;
#if FENWICK_MODULUS
            _v[index] %= mod;
#endif

            // Update index to that of parent in update View
            index += index & (-index);
        }
    }

private:
    const S _n;
    std::vector<T> _v;
#if FENWICK_MODULUS
    const T mod;
#endif
#if FENWICK_VECTOR_UPDATE
    std::vector<T> _u;
#endif
};