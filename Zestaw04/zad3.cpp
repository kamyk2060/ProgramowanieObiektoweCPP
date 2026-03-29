#include <iostream>
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

// Wersja ogolna - z jawnie podana klasa cech (Traits)
template<typename Traits, typename T>
typename Traits::sum_type sum(T* beg, T* end) {
    typedef typename Traits::sum_type sum_type;
    sum_type total = Traits::zero();
    while (beg != end) {
        total += *beg;
        ++beg;
    }
    return total;
}

// Wersja domyslna - przechodzi do powyzszej z sum_traits<T>
template<typename T>
typename sum_traits<T>::sum_type sum(T* beg, T* end) {
    return sum<sum_traits<T>, T>(beg, end);
}

// Klasa cech wymuszajaca sumowanie char w char
struct char_sum {
    typedef char sum_type;
    static sum_type zero() { return 0; }
};

int main() {
    char name[] = "@ @ @";
    int dlugosc = strlen(name);

    // Domyslne wywolanie - sum_traits<char> -> total typu int
    cout << (int)sum(name, name + dlugosc) << endl;           // 256

    // Z jawna klasa cech char_sum - total typu char (przepelnienie)
    cout << (int)sum<char_sum>(name, name + dlugosc) << endl;  // 0

    // Mozna tez jawnie podac sum_traits<char> - to samo co domyslne
    cout << (int)sum<sum_traits<char>>(name, name + dlugosc) << endl; // 256

    return 0;
}