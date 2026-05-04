#include <iostream>

// x^N = (x^(N/2))^2  gdy N parzyste  -> 1 podzial + 1 mnozenie
// x^N = x * x^(N-1)  gdy N nieparzyste

// N parzyste
template <int N, bool Parzyste = (N % 2 == 0)>
struct PowFast {
    static inline double calc(double x) {
        double half = PowFast<N / 2>::calc(x);
        return half * half;
    }
};

//  nieparzyste
template <int N>
struct PowFast<N, false> {
    static inline double calc(double x) {
        return x * PowFast<N - 1>::calc(x);
    }
};

// Przypadki bazowe
template <>
struct PowFast<0, true> {
    static inline double calc(double) { return 1.0; }
};

template <>
struct PowFast<1, false> {
    static inline double calc(double x) { return x; }
};


template <int N>
inline double pow_fast(double x) {
    return PowFast<N>::calc(x);
}

int main() {
    double x = 2.0;

    std::cout << "pow_fast<4>(x) = " << pow_fast<4>(x) << std::endl;
    std::cout << "pow_fast<5>(x) = " << pow_fast<5>(x) << std::endl;
    std::cout << "pow_fast<10>(x) = " << pow_fast<10>(x) << std::endl;

    return 0;
}
