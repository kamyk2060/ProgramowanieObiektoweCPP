#include <iostream>
#include <cstring>
using namespace std;

// Szablon ogolny
template<typename T>
struct sum_traits {
    typedef T sum_type;
    static sum_type zero() { return sum_type(); }
};

// Specjalizacje z funkcja zero()
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

// Funkcja sum - inicjalizacja total przez sum_traits<T>::zero()
template<typename T>
typename sum_traits<T>::sum_type sum(T* beg, T* end) {
    typedef typename sum_traits<T>::sum_type sum_type;
    sum_type total = sum_traits<T>::zero();
    while (beg != end) {
        total += *beg;
        ++beg;
    }
    return total;
}

int main() {
    char name[] = "@ @ @";
    int dlugosc = strlen(name);
    cout << "sum(char) = " << sum(name, name + dlugosc) << endl;

    int tab_int[] = {1, 2, 3, 4, 5};
    cout << "sum(int) = " << sum(tab_int, tab_int + 5) << endl;

    double tab_dbl[] = {1.5, 2.5, 3.0};
    cout << "sum(double) = " << sum(tab_dbl, tab_dbl + 3) << endl;

    float tab_flt[] = {1.1f, 2.2f, 3.3f};
    cout << "sum(float) = " << sum(tab_flt, tab_flt + 3) << endl;

    // Pusty zakres - total == zero()
    cout << "sum(pusty) = " << sum(tab_int, tab_int) << endl;

    return 0;
}