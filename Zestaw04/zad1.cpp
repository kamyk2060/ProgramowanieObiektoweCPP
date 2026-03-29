#include <iostream>
#include <cstring>
using namespace std;

// Szablon ogolny - domyslnie sum_type == T
template<typename T>
struct sum_traits {
    typedef T sum_type;
};

// Specjalizacje
template<> struct sum_traits<char> {
    typedef int sum_type;
};

template<> struct sum_traits<int> {
    typedef long int sum_type;
};

template<> struct sum_traits<float> {
    typedef double sum_type;
};

template<> struct sum_traits<double> {
    typedef double sum_type;
};

// Funkcja sum - typ total pochodzi z sum_traits
template<typename T>
typename sum_traits<T>::sum_type sum(T* beg, T* end) {
    typedef typename sum_traits<T>::sum_type sum_type;
    sum_type total = sum_type();
    while (beg != end) {
        total += *beg;
        ++beg;
    }
    return total;
}

int main() {
    // char: '@'=64, ' '=32 => 64+32+64+32+64 = 256, miesci sie w int
    char name[] = "@ @ @";
    int dlugosc = strlen(name);
    cout << "sum(char) = " << sum(name, name + dlugosc) << endl;

    int tab_int[] = {1, 2, 3, 4, 5};
    cout << "sum(int) = " << sum(tab_int, tab_int + 5) << endl;

    double tab_dbl[] = {1.5, 2.5, 3.0};
    cout << "sum(double) = " << sum(tab_dbl, tab_dbl + 3) << endl;

    float tab_flt[] = {1.1f, 2.2f, 3.3f};
    cout << "sum(float) = " << sum(tab_flt, tab_flt + 3) << endl;

    return 0;
}