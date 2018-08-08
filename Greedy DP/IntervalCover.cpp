//Leif Eriksson

#include <vector>
#include <algorithm>
#include <tuple>

template<typename T = double>
struct myInterval{
    T a, b;
    int i;
    myInterval(){}
    myInterval(T a, T b, int i) : a{a}, b{b}, i{i} {}
};

template<typename T = double>
bool operator< (const myInterval<T> & lhs, const myInterval<T> & rhs){
    return lhs.a < rhs.a;
}

template<typename T = double>
std::vector<int> cover(std::pair<T, T> interval, std::vector<myInterval<T>> intervals){
    sort(intervals.begin(), intervals.end());

    std::vector<int> result;

    //Quick sanitycheck
    if(intervals[0].a > interval.first)
        return result;

    myInterval<T> curr(intervals[0]);

    //loop untill whole interval covered
    int i{ 1 };
    bool found{ true };
    do{
        for(; i < intervals.size() && intervals[i].a <= interval.first; ++i){
            if(curr.b < intervals[i].b){
                curr = intervals[i];
                found = true;
            }
        }

        //Controll
        if(!found || found && (curr.a > interval.first || curr.b < interval.first)){
            result.clear();
            return result;
        }

        result.push_back(curr.i);
        interval.first = curr.b;
        found = false;
    }while(interval.first < interval.second);

    return result;
}