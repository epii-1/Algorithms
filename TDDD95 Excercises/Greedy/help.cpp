//https://liu.kattis.com/problems/help2
#include <iostream>
#include <vector>
#include <algorithm>
#include <cmath>
#include <random>
#include <iterator>
#include <tuple>
#include <string>
#include <functional>
#include <queue>
#include <set>
#include <unordered_set>
#include <iterator>
#include <sstream>
#include <map>

using namespace std;


struct box {
    box* b = nullptr;
    string s;
    box(string s) : s{ s } {}
    box* top() {
        if (b == nullptr)
            return this;
        return b->top();
    }
    void merge(box * a) {
        a = a->top();
        //cout << "merge " << this << " " << a << endl;
        if (a != this) {
            string s1 = get();
            if (b != nullptr) {
                b->merge(a);
            }
            else {
                b = a;
            }
            if (s1 != "" && s1.at(0) != '<') {
                a->set(s1);
            }
            set(get());
        }
    }
    string get() {
        //cout << "get\n";
        if (b != nullptr)
            return b->get();
        return s;
    }
    string get2() {
        string s = get();
        if (s.at(0) == '<')
            return "a";
        return s;
    }
    void set(string ns) {
        if (b != nullptr)
            return b->set(ns);
        s = ns;
    }
};


int main() {

    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);
    cout.precision(17);

    int n;
    string stri;
    getline(cin, stri);

    n = stoi(stri);

    for (int asd = 0; asd < n; ++asd) {
        getline(cin, stri);
        istringstream iss(stri);
        vector<string> w1{ istream_iterator<string>{iss},
            istream_iterator<string>{} };


        getline(cin, stri);
        istringstream iss2(stri);
        vector<string> w2{ istream_iterator<string>{iss2},
            istream_iterator<string>{} };


        if (w1.size() != w2.size()) {
            cout << "-\n";
            continue;
        }

        map<string, box*> m1;
        map<string, box*> m2;

        for (int i = 0; i < w1.size(); ++i) {
            //cout << i << endl;
            if (w1[i].at(0) == '<') {
                //cout << "first\n";
                auto a = m1.find(w1[i]);
                //cout << "first\n";
                if (a == m1.end()) {
                    //cout << "first4\n";
                    m1.insert(make_pair(w1[i], new box(w2[i])));
                    //cout << "first4\n";
                    a = m1.find(w1[i]);
                    //cout << "first4\n";
                }
                //cout << "first\n" << a->second << "\n";
                //cout << a->second->get() << endl;
                if (w2[i].at(0) == '<') {
                    //cout << "first1\n";
                    auto b = m2.find(w2[i]);
                    if (b != m2.end()) {
                        //cout << "first1\n";
                        a->second->merge(b->second);
                    }
                }
                else if (a->second->get().at(0) == '<') {
                    //cout << "first2\n";
                    a->second->set(w2[i]);
                }
            }
            if (w2[i].at(0) == '<') {
                //cout << "second\n";
                auto a = m2.find(w2[i]);
                //cout << "second\n";
                if (a == m2.end()) {
                    //cout << "second4\n";
                    m2.insert(make_pair(w2[i], new box(w1[i])));
                    //cout << "second4\n";
                    a = m2.find(w2[i]);
                    //cout << "second4\n";
                }
                //cout << "second\n" << a->second << "\n";
                //cout << a->second->get() << endl;
                if (w1[i].at(0) == '<') {
                    //cout << "second1\n";
                    auto b = m1.find(w1[i]);
                    if (b != m1.end()) {
                        //cout << "second1\n";
                        a->second->merge(b->second);
                    }
                }
                else if (a->second->get().at(0) == '<') {
                    //cout << "second2\n";
                    a->second->set(w1[i]);
                }
            }
            if (w1[i] != w2[i]) {
                if (w2[i].at(0) != '<' && w1[i].at(0) != '<') {
                    //cout << "other\n";
                    break;
                }
            }
        }


        string out = "";

        for (int i = 0; i < w1.size(); ++i) {
            if (w1[i].at(0) == '<') {
                w1[i] = m1.find(w1[i])->second->get2();
            }
            if (w2[i].at(0) == '<') {
                w2[i] = m2.find(w2[i])->second->get2();
            }
            if (w1[i] == w2[i]) {
                out += w1[i] + " ";
            }
            else {
                out = "-";
                break;
            }
        }

        cout << out << "\n";

        for (auto it : m1) {
            delete it.second;
        }

        for (auto it : m2) {
            delete it.second;
        }
    }


    return 0;

}
/*
7
<a> <b> f
<a> <b> <b>
<a> <b> <b>
<a> <b> f
<a> <b> <b>
<b> <b> f
<b> <b> f
<a> <b> <b>
<a> <a> <b> <b> <c> <c> <b>
a <a> <a> <b> <b> <c> <c>
<a> <a> <b> <b> <c> <c> <d> <d>
a <a> <a> <b> <b> <c> <c> a
<a> <a> <b> <b> <c> <c> <d> <d>
<d> <a> <a> <b> a <c> <c> <d>
*/