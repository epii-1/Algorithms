class myBitset {
private:
    const static vector<char> _c;
    const static vector<char> _n;
    vector<char> _v;
    size_t _s;
public:
    myBitset(size_t s) {
        _s = s / 8;

        if (s & 7)
            ++_s;

        _v.resize(_s, 0);
    }

    myBitset(size_t s, bool val) {
        _s = s / 8;

        if (s & 7)
            ++_s;

        _v.resize(_s, 255 * val);
    }

    bool operator[] (size_t index) {
        return _v[index / 8] & _c[index & 7];
    }

    void set(size_t index, bool val) {
        if (val) {
            _v[index / 8] |= _c[index & 7];
        }
        else {
            _v[index / 8] &= _n[index & 7];
        }
    }

    void flip(size_t index) {
        set(index, !(_v[index / 8] & _c[index & 7]));
    }
};

const vector<char> myBitset::_c{ char(1), char(2), char(4), char(8),
char(16), char(32), char(64), char(128) };
const vector<char> myBitset::_n{ char(254), char(253), char(251), char(247),
char(239), char(223), char(191), char(127) };