enum InOutOn {
    IN, OUT, ON
};

template<typename T = double>
class Poly {
public:
    vector<Line<T>> lines;

    T area() const {
        T area{ 0.0 };

        // Calculate value of shoelace formula
        int j(lines.size() - 1);
        for (int i{ 0 }; i < lines.size(); ++i)
        {
            area += (lines[j].p1.x + lines[i].p1.x) * (lines[j].p1.y - lines[i].p1.y);
            j = i;  // j is previous vertex to i
        }

        // Return absolute value
        return area / 2.0;
    }

    InOutOn in(const Point& p) const {
        int i{ 0 };
        for (; i < lines.size(); ++i) {
            if (lines[i].on(p))
                return ON;
        }
        pair<T, long double> f{ 0, p.y };
        int intersects{ 0 };
        vector<Point<T>> pv;
        for (i = 0; i < lines.size(); ++i) {
            if (lines[i].getFunc().first != 0) {
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
    }
};