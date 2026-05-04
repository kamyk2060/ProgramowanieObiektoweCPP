#include <iostream>
#include <cmath>

// silnia 
template <int N>
struct Factorial {
    // dla duzych silni
    static constexpr long long val = (long long)N * Factorial<N - 1>::val;
};

template <>
struct Factorial<0> {
    static constexpr long long val = 1;
};

// x do potegi 
template <int N>
inline double pow_int(double x) {
    return x * pow_int<N - 1>(x);
}

template <>
inline double pow_int<0>(double) { return 1.0; }


template <int K, int N>
struct Sin {
    static inline double calc(double x) {
        double znak = (K % 2 == 0) ? 1.0 : -1.0;
        double wyraz = znak * pow_int<2 * K + 1>(x) / Factorial<2 * K + 1>::val;
        return wyraz + Sin<K + 1, N>::calc(x);
    }
};

// doszlismy do N-tego wyrazu, koniec sumowania
template <int N>
struct Sin<N, N> {
    static inline double calc(double) { return 0.0; }
};

// sin_taylor<N>(x) liczy sume pierwszych N wyrazow
template <int N>
inline double sin_taylor(double x) {
    return Sin<0, N>::calc(x);
}

int main() {

    double x = 0.707;

    std::cout << "x = " << x << std::endl;
    std::cout << "sin_taylor<1>(x) = " << sin_taylor<1>(x) << std::endl;
    std::cout << "sin_taylor<2>(x) = " << sin_taylor<2>(x) << std::endl;
    std::cout << "sin_taylor<5>(x) = " << sin_taylor<5>(x) << std::endl;
    std::cout << "sin_taylor<10>(x) = " << sin_taylor<10>(x) << std::endl;
    std::cout << "std::sin(x) = " << std::sin(x) << std::endl;

  

    return 0;
}
