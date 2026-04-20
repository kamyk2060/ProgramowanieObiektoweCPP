
#include <iostream>
#include <vector>
#include <cassert>
#include <string>

// If_then_else potrzebne dla Promote
template<bool flag, typename T1, typename T2>
struct If_then_else {
    typedef T1 Result;
};

template<typename T1, typename T2>
struct If_then_else<false, T1, T2> {
    typedef T2 Result;
};


// jesli typy maja rozny rozmiar - wybieramy wiekszy
// jesli taki sam rozmiar - liczymy na specjalizacje
template<typename T1, typename T2>
struct Promote {
    typedef typename If_then_else<(sizeof(T1) > sizeof(T2)), T1,
            typename If_then_else<(sizeof(T1) < sizeof(T2)),T2,
            void>::Result >::Result Result;
};

// dla identycznych typow
template<typename T>
struct Promote<T, T> {
    typedef T Result;
};

// Makro uproszczajace definiowanie specjalizacji
#define MK_PROMOTE(T1, T2, Tr)             \
    template<> struct Promote<T1, T2> {    \
        typedef Tr Result;                 \
    };                                     \
    template<> struct Promote<T2, T1> {    \
        typedef Tr Result;                 \
    };


MK_PROMOTE(bool, char, int)
MK_PROMOTE(bool, unsigned char, int)
MK_PROMOTE(bool, signed char, int)

  
// Operator dodawania wektorow 
template<typename T, typename U>
std::vector<typename Promote<T, U>::Result>
operator+(const std::vector<T>& a, const std::vector<U>& b) {
    assert(a.size() == b.size());
    
    typedef typename Promote<T, U>::Result Wynik;
    std::vector<Wynik> res(a.size());
    
    for (size_t i = 0; i < a.size(); ++i) {
        res[i] = static_cast<Wynik>(a[i]) + static_cast<Wynik>(b[i]);
    }
    
    return res;
}


// Funkcja pomocnicza do wypisania wektora
template<typename T>
void drukuj(const std::string& nazwa, const std::vector<T>& v) {
    std::cout << nazwa << " = [ ";
    for (const auto& x : v) std::cout << x << " ";
    std::cout << "]\n";
}


int main() {
    
    // Test 1: double + int (double ma wiekszy rozmiar)
    std::vector<double> x = {1.5, 2.5, 3.5};
    std::vector<int> l = {10, 20, 30};

    auto wynik1 = x + l;
    drukuj("double + int", wynik1);
    std::cout << "  rozmiar elementu: " << sizeof(wynik1[0]) << "\n\n";

    // Test 2: int + int (identyczne typy)
    std::vector<int> a = {1, 2, 3};
    std::vector<int> b = {10, 20, 30};
    auto wynik2 = a + b;
    drukuj("int + int", wynik2);
    std::cout << "  rozmiar elementu: " << sizeof(wynik2[0]) << "\n\n";

    // Test 3: float + double
    std::vector<float> f = {1.1f, 2.2f, 3.3f};
    std::vector<double> d = {0.01, 0.02, 0.03};
    auto wynik3 = f + d;
    drukuj("float + double", wynik3);
    std::cout << "  rozmiar elementu: " << sizeof(wynik3[0]) << "\n\n";

    // Test 4: sprawdzenie specjalizacji Promote
    std::cout << "Promote<int, int>::Result - rozmiar: " 
              << sizeof(Promote<int, int>::Result) << "\n";
    std::cout << "Promote<int, double>::Result - rozmiar: " 
              << sizeof(Promote<int, double>::Result) << "\n";

    return 0;
}