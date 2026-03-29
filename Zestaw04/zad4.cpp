#include <iostream>
#include <iterator>
#include <vector>
#include <list>
#include <cstring>
using namespace std;

// Klasy cech
template<typename T>
struct sum_traits {
    typedef T sum_type;
    static sum_type zero() { return sum_type(); }
};

template<> struct sum_traits<char> {
    typedef int sum_type;
    static sum_type zero() { return 0; }
};

template<> struct sum_traits<int> {
    typedef long int sum_type;
    static sum_type zero() { return 0; }
};

template<> struct sum_traits<float> {
    typedef double sum_type;
    static sum_type zero() { return 0.0; }
};

template<> struct sum_traits<double> {
    typedef double sum_type;
    static sum_type zero() { return 0.0; }
};

// Wersja z jawna klasa cech + iteratory
template<typename Traits, typename II>
typename Traits::sum_type sum(II beg, II end) {
    typedef typename Traits::sum_type sum_type;
    sum_type total = Traits::zero();
    while (beg != end) {
        total += *beg;
        ++beg;
    }
    return total;
}

// Wersja domyslna - iterator_traits wyciaga value_type
template<typename II>
typename sum_traits<typename iterator_traits<II>::value_type>::sum_type sum(II beg, II end) {
    typedef typename iterator_traits<II>::value_type value_type;
    return sum<sum_traits<value_type>, II>(beg, end);
}

// Klasa cech wymuszajaca sumowanie char w char
struct char_sum {
    typedef char sum_type;
    static sum_type zero() { return 0; }
};

int main() {
    // Wskazniki - iterator_traits<T*>::value_type == T
    char name[] = "@ @ @";
    int dlugosc = strlen(name);
    cout << "sum wskaznik(char) = " << sum(name, name + dlugosc) << endl;

    int tab[] = {10, 20, 30, 40};
    cout << "sum wskaznik(int) = " << sum(tab, tab + 4) << endl;

    // vector<int> 
    vector<int> vec = {100, 200, 300};
    cout << "sum vector<int> = " << sum(vec.begin(), vec.end()) << endl;

    // list<double> 
    list<double> lst = {1.1, 2.2, 3.3};
    cout << "sum list<double> = " << sum(lst.begin(), lst.end()) << endl;

    // vector<char> z jawna klasa cech
    vector<char> znaki = {'@', ' ', '@', ' ', '@'};
    cout << "sum vector<char> domyslne = " << sum(znaki.begin(), znaki.end()) << endl;
    cout << "sum<char_sum> vector<char> = " << (int)sum<char_sum>(znaki.begin(), znaki.end()) << endl;

    return 0;
}