class Line {
public:
    Point p1, p2;

    long double length() const {
        return p1.dist(p2);
    }

    pair<long double, long double> getFunc() const {
        long double k{ (p2.y - p1.y) / (p2.x - p1.x) };
        if (isinf(k))
            return { k, p1.x };
        long double m{ p1.y - k*p1.x };
        return { k, m };
    }

    long double ortK() const {
        return -1.0 / getFunc().first;
    }

    pair<long double, long double> ortFunc(const Point& p) const {
        long double k{ ortK() };
        if (isinf(k))
            return { k, p.y };
        long double m{ p.y - k*p.x };
        return { k,m };
    }

    bool on(const Point & p) const {
        pair<long double, long double> f{ getFunc() };
        if (isnan(f.first)) {
            return p == p1;
        }
        if (isinf(abs(f.first))) {
            return p.x == p1.x &&
                ((p.y <= p1.y && p.y >= p2.y)
                    || (p.y <= p2.y && p.y >= p1.y));
        }
        return f.first*p.x + f.second == p.y &&
            ((p.x <= p1.x && p.x >= p2.x) ||
            (p.x >= p1.x && p.x <= p2.x));
    }
    Point intersect(const pair<long double, long double> f, const pair<long double, long double> of) const {
        if (isinf(abs(f.first))) {
            //cout << "f is inf\n";
            return Point(f.second, f.second*of.first + of.second);
        }
        if (isinf(abs(of.first))) {
            //cout << "of is inf\n";
            //cout << of.second << " " << of.second * f.first << "\n";
            return Point(of.second, of.second*f.first + f.second);
        }
        long double x{ (f.second - of.second) / (of.first - f.first) };
        return Point(x, f.first*x + f.second);
    }

    Point intersect(const pair<long double, long double> of) const {
        return intersect(getFunc(), of);
    }

    Point intersect(const Line& o) const {
        return intersect(o.getFunc());
    }

    vector<Point> fullIntersect(const Line& o) const {
        pair<long double, long double> f{ getFunc() };
        pair<long double, long double> of{ o.getFunc() };

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

        //cout << f.first << " " << of.first << "\n";

        if (f.first == of.first || (isinf(f.first) && isinf(of.first))) {
            //cout << "same\n";
            if (f.second != of.second)
                return {};

            if (on(o.p1)) {
                //cout << "o.p1 on\n";
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
                //cout << "o.p2 on\n";
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

        Point p(intersect(f, of));
        if (on(p) && o.on(p))
            return { p };

        return {};

    }

    long double dist(const Point & p) const {
        long double dist;
        Point inter(intersect(ortFunc(p)));
        if (on(inter))
            dist = p.dist(inter);
        else
            dist = min(p.dist(p1), p.dist(p2));
        return dist;
    }

};