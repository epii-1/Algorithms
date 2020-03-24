#include <vector>
#include <cmath>
#include "2D\Line.cpp"
#include "2D\Point.cpp"
#include "Number Theory\sgn.cpp"

enum InOutOn {
    IN, OUT, ON
};

template <typename T = long double>
class Poly {
public:
    std::vector<Line<T>> lines;

    T area() const {
        T area{ 0.0 };

        // Calculate value of shoelace formula
        size_t j(lines.size() - 1);
        for (size_t i{ 0 }; i < lines.size(); ++i)
        {
            area += (lines[j].p1.x + lines[i].p1.x) * (lines[j].p1.y - lines[i].p1.y);
            j = i;  // j is previous vertex to i
        }

        // Return absolute value
        return area * 0.5;
    }

    InOutOn in(const Point<T>& p) const {
        size_t i{ 0 };
        for (; i < lines.size(); ++i) {
            if (lines[i].on(p))
                return ON;
        }
        std::pair<T, T> f{ 0, p.y };
		size_t n;
        //I have no clue which implementation is best nowdays, so I'm keeping both
		Point<T> inter;
		std::pair<T, T> of;
		T t, nt;
		for (i = 0; i < lines.size(); ++i) {
			of = lines[i].getFunc();
			if (of.first != 0.0) {
				Point<T> inter{ lines[i].intersect(f) };
				if (inter.x - p.x > -_DELTA && lines[i].on(inter) && inter != lines[i].p1)
					if (inter == lines[i].p2) {
						t = sgn(lines[i].p1.y - p.y);
						n = (i + 1) % lines.size();
						while (lines[n].p2.y == p.y) n = (n + 1) % lines.size();
						nt = sgn(lines[n].p2.y - p.y) ;
						if (t != nt)
							++intersects;
					}
					else
						++intersects;
			}
		}
        
        return intersects % 2 ? IN : OUT;
/*
        vector<Point<T>> pv;
        for (i = 0; i < lines.size(); ++i) {
            if (!lines[i].getFunc().first) {
                Point<T> inter{ lines[i].intersect(f) };
                if (inter.x > p.x && lines[i].on(inter)) {
                    pv.push_back(inter);
                    if (inter != lines[i].p1 && inter != lines[i].p2)
                        ++intersects;
                    ++intersects;
                }
            }
        }

        return (intersects >> 1) & 1 ? IN : OUT;
        */
    }
private:
	const static long double _DELTA;
};

template <typename T>
const long double Poly<T>::_DELTA{ 0.000000001 };