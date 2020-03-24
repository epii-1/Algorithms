template<typename T = double>
class Point {
public:
    T x, y;

    Point() {}
    Point(T x, T y) : x(x), y(y) {}

    bool operator==(const Point<T>& o) const {
        return abs(x - o.x) < 0.000000001 && abs(y - o.y) <  0.000000001;
    }

    bool operator!=(const Point<T>& o) const {
        return !operator==(o);
    }

    template<typename K>
    Point<T>& operator*(const K& o) {
        x *= o;
        y *= o;
        return *this;
    }

    template<typename K>
    Point<T>& operator/(const K& o) {
        K t{ 1.0 / o };
        return operator*(t);
    }

    Point<T>& operator+(const Point<T>& o) {
        x += o.x;
        y += o.y;
        return *this;
    }

    Point<T>& operator-(const Point<T>& o) {
        x -= o.x;
        y -= o.y;
        return *this;
    }

    T dist(const Point<T>& o) const {
        T tx(x - o.x);
        T ty(y - o.y);
        return sqrt(tx*tx + ty*ty);
    }

    T crossProduct(const Point<T>& o) const {
        return x*o.y - y*o.x;
    }

    T scalarProduct(const Point<T>& o) const {
        return x*o.x + y*o.y;
    }

    T angl(const Point<T>& o) const {
        return atan2(x - o.x, y - o.y);
    }

    pair<T, T> getSlope(const Point<T>& o) const {
        //Get the slope of two points
        //Recommended to not use with non-intereger points
        T dy(y - o.y);
        T dx(x - o.x);
        if ((dy < 0 && dx < 0) || (dy > 0 && dx < 0)) {
            dy = -dy;
            dx = -dx;
        }
        T g{ gcd(abs(dy),abs(dx)) };
        return { dy / g, dx / g };
    }
};

template<typename T=double>
bool operator<(const Point<T>& lhs, const Point<T>& rhs) {
    return lhs.x < rhs.x || (lhs.x == rhs.x && lhs.y < rhs.y);
}