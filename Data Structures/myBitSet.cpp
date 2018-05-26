struct myBitset {
    myBitset(size_t s, bool val = false) {
        _s = s >> 3;

        if (s & 7)
            ++_s;

        _v.resize(_s, 255 * val);
    }

    bool inline operator[] (size_t index) {
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

    void inline flip(size_t index) {
        set(index, !(_v[index >> 3] & _c[index & 7]));
    }

    const static vector<char> _c;
    const static vector<char> _n;
    size_t _s;
    vector<char> _v;
};