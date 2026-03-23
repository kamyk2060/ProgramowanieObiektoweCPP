
#include <iostream>
#include <cstring>

using namespace std;


template <typename T>
T max(T a, T b) {
    cout << "  max(T, T)" << endl;
    return (a > b) ? a : b;
}

template <typename T>
T* max(T* a, T* b) {
    cout << "  max(T*, T*)" << endl;
    return (*a > *b) ? a : b;
}

template <typename T>
T max(T* data, size_t n) {
    cout << "  max(T*, size_t)" << endl;
    T wynik = data[0];
    for (size_t i = 1; i < n; ++i)
        if (data[i] > wynik)
            wynik = data[i];
    return wynik;
}



char *max(char *a,char *b) {
    cout << "  max(char*, char*)" << endl;
    return (strcmp(a, b) > 0) ? a : b;
}

const char* max(const char* a, const char* b) {
    cout << "  max(const char*, const char*)" << endl;
    return (strcmp(a, b) > 0) ? a : b;
}

template<typename T> 
const T* max(T* a, const T* b) {
    return ((*a) > (*b)) ? a : b;
}

template<> 
const char* max(char* a, const char* b) {
    return (strcmp(a, b) > 0) ? a : b;
}

int main() {

    cout << "max(3,7) = " << ::max(3, 7) << endl;
    cout << "max(3.14, 2.71) = " << ::max(3.14, 2.71) << endl;
 
    int a = 10, b = 20;
    cout << "max(&10, &20) = " << *::max(&a, &b) << endl;
 
    double t[] = {5, 3, 9, 1, 7};
    cout << "max(tab, 5) = " << ::max(t, (size_t)5) << endl;
 
    char s1[] = "alfa";
    char s2[] = "beta";
    cout << "max(alfa, beta) = " << ::max(s1, s2) << endl;
 
    const char* c1 = "xyz";
    const char* c2 = "abc";
    cout << "max(xyz, abc) = " << ::max(c1, c2) << endl;
 
    char m[] = "hello";
    const char* c3 = "world";
    cout << "max(hello, world) = " << ::max(m, c3) << endl;

    return 0;
}