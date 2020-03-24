template<typename T = double>
class Line {
public:
    Point<T> p1, p2;

    T length() const {
        return p1.dist(p2);
    }

    pair<T, T> getFunc() const {
        //Get funktion for the line
        //as <k,m>
        T k{ (p2.y - p1.y) / (p2.x - p1.x) };
        if (isinf(k))
            //If k is inf, m value is treated as y value
            return { k, p1.x };
        T m{ p1.y - k*p1.x };
        return { k, m };
    }

    T ortK() const {
        //k for ortogonal line
        return -1.0 / getFunc().first;
    }

    pair<T, T> ortFunc(const Point<T>& p) const {
        //Get function for ortogonal line that passes through point p
        //as <k,m>
        T k{ ortK() };
        if (isinf(k))
            //If k is inf, m value is treated as y value
            return { k, p.y };
        T m{ p.y - k*p.x };
        return { k,m };
    }

    bool on(const Point & p) const {
        //Is point on the line?
        pair<T, T> f{ getFunc() };
        if (isnan(f.first)) {
            //Not a line, it's a point!
            return p == p1;
        }
        if (isinf(abs(f.first))) {
            return abs(p.x - p1.x) < 0.000000001 &&
                ((p.y - p1.y < 0.000000001 && p.y - p2.y > -0.000000001)
                    || (p.y - p2.y < 0.000000001 && p.y - p1.y > -0.000000001));
        }
        return abs(f.first*p.x + f.second - p.y) < 0.000000001 &&
            ((p.x - p1.x < 0.000000001 && p.x - p2.x > -0.000000001) ||
            (p.x - p1.x > -0.000000001 && p.x - p2.x < 0.000000001));
    }
    Point<T> intersect(const pair<T, T> f, const pair<T, T> of) const {
        //Get intersectionpoint of lines (can be outside of the lines)
        if (isinf(abs(f.first))) {
            return Point<T>(f.second, f.second*of.first + of.second);
        }
        if (isinf(abs(of.first))) {
            return Point<T>(of.second, of.second*f.first + f.second);
        }
        T x{ (f.second - of.second) / (of.first - f.first) };
        return Point<T>(x, f.first*x + f.second);
    }

    Point<T> intersect(const pair<T, T> of) const {
        //Get intersectionpoint of lines (can be outside of the lines)
        return intersect(getFunc(), of);
    }

    Point<T> intersect(const Line<T>& o) const {
        //Get intersectionpoint of lines (can be outside of the lines)
        return intersect(o.getFunc());
    }

    vector<Point<T>> fullIntersect(const Line<T>& o) const {
        //Get intersectionpoint of lines
        //Only points on both line
        //return two points if interval
        pair<T, T> f{ getFunc() };
        pair<T, T> of{ o.getFunc() };

        if (isnan(f.first)) {
            if (o.on(p1))
                return { p1 };
            return {};
        }
        if (isnan(of.first)) {
            if (on(o.p1))
                return { o.p1 };
            return {};
        }
        
        if (abs(f.first - of.first) < 0.000000001 || (isinf(f.first) && isinf(of.first))) {
            //Parallel lines
            if (abs(f.second - of.second) > 0.000000001)
                return {};

            if (on(o.p1)) {
                if (o.p1 != p1 && o.on(p1)) {
                    return { o.p1, p1 };
                }
                if (o.p1 != p2 && o.on(p2)) {
                    return { o.p1, p2 };
                }
                if (on(o.p2)) {
                    return { o.p1, o.p2 };
                }
                return { o.p1 };
            }
            if (on(o.p2)) {
                if (o.p2 != p1 && o.on(p1)) {
                    return { o.p2, p1 };
                }
                if (o.p2 != p2 && o.on(p2)) {
                    return { o.p2, p2 };
                }
                return { o.p2 };
            }
            return { p1, p2 };
        }

        Point<T> p(intersect(f, of));
        if (on(p) && o.on(p))
            return { p };

        return {};

    }

    T dist(const Point<T> & p) const {
        //Distance from line to point
        T dist;
        Point inter(intersect(ortFunc(p)));
        if (on(inter))
            dist = p.dist(inter);
        else
            dist = min(p.dist(p1), p.dist(p2));
        return dist;
    }

};