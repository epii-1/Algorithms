
#include <cmath>
#include <vector>
#include "2D\Point.cpp"

template <typename T = long double>
class Line {
public:
    Point<T> p1, p2;

    T length() const {
        return p1.dist(p2);
    }

    std::pair<T, T> getFunc() const {
        //Get funktion for the line
        //as <k,m>
        T k{ (p2.y - p1.y) / (p2.x - p1.x) };
        if (std::isinf(k))
            //If k is inf, m value is treated as y value
            return { k, p1.x };
        T m{ p1.y - k*p1.x };
        return { k, m };
    }

    T ortK() const {
        //k for ortogonal line
        return -1.0 / getFunc().first;
    }

	std::pair<T, T> ortFunc(const Point<T>& p) const {
        T k{ ortK() };
        if (std::isinf(k))
            //If k is inf, m value is treated as y value
            return { k, p.y };
        T m{ p.y - k*p.x };
        return { k,m };
    }

    bool on(const Point<T>& p) const {
    //Is point on the line?
		std::pair<T, T> f{ getFunc() };
        if (std::isnan(f.first))
            //Not a line, it's a point!
            return p == p1;

        if (std::isinf(f.first))
			return std::abs(p.x - p1.x) < _DELTA &&
			((p.y - p1.y < _DELTA && p.y - p2.y > -_DELTA)
				|| (p.y - p2.y < _DELTA && p.y - p1.y > -_DELTA));

        return std::abs(f.first*p.x + f.second - p.y) < _DELTA &&
			((p.x - p1.x < _DELTA && p.x - p2.x > -_DELTA) ||
			(p.x - p1.x > -_DELTA && p.x - p2.x < _DELTA));
    }

    Point<T> intersect(const std::pair<T, T>& f, const std::pair<T, T>& of) const {
        //Get intersectionpoint of lines (can be outside of the lines)
        if (std::isinf(f.first))
            return Point<T>(f.second, f.second*of.first + of.second);

        if (std::isinf(of.first))
            return Point<T>(of.second, of.second*f.first + f.second);

        T x{ (f.second - of.second) / (of.first - f.first) };
        return Point<T>(x, f.first*x + f.second);
    }

    Point<T> intersect(const std::pair<T, T>& of) const {
       return intersect(getFunc(), of);
    }

    Point<T> intersect(const Line<T>& o) const {
        //Get intersectionpoint of lines (can be outside of the lines)
        return intersect(o.getFunc());
    }

	std::vector<Point<T>> fullIntersect(const Line<T>& o) const {
        //Get intersectionpoint of lines
        //Only points on both line
        //return two points if interval
        std::pair<T, T> f{ getFunc() };
		std::pair<T, T> of{ o.getFunc() };

        if (std::isnan(f.first)) {
            if (o.on(p1))
                return { p1 };
            return {};
        }
        if (std::isnan(of.first)) {
            if (on(o.p1))
                return { o.p1 };
            return {};
        }
        if (std::abs(f.first - of.first) < _DELTA || (std::isinf(f.first) && std::isinf(of.first))) {
			if (std::abs(f.second - of.second) > _DELTA)
				return {};

            if (on(o.p1)) {
                if (o.p1 != p1 && o.on(p1)) 
                    return { o.p1, p1 };

                if (o.p1 != p2 && o.on(p2)) 
                    return { o.p1, p2 };

                if (on(o.p2)) 
                    return { o.p1, o.p2 };

                return { o.p1 };
            }
            if (on(o.p2)) {
                if (o.p2 != p1 && o.on(p1)) 
                    return { o.p2, p1 };

                if (o.p2 != p2 && o.on(p2)) 
                    return { o.p2, p2 };

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
        Point<T> inter(intersect(ortFunc(p)));
        if (on(inter))
            dist = p.dist(inter);
        else
            dist = std::min(p.dist(p1), p.dist(p2));
        return dist;
    }
private:
	const static long double _DELTA;
};

template <typename T>
const long double Line<T>::_DELTA{ 0.000000001 };