#include <iostream>

template <size_t N>
struct InnerHelper {
    static inline double calc(double *x, double *y) {
        return x[N - 1] * y[N - 1] + InnerHelper<N - 1>::calc(x, y);
    }
};

// Przypadek bazowy: pusty iloczyn = 0
template <>
struct InnerHelper<0> {
    static inline double calc(double *, double *) { return 0.0; }
};

template <size_t N>
inline double inner(double *x, double *y) {
    return InnerHelper<N>::calc(x, y);
}

int main() {
    double a[5] = {1.0, 2.0, 3.0, 4.0, 5.0};
    double b[5] = {5.0, 4.0, 3.0, 2.0, 1.0};

    std::cout << "a = [1, 2, 3, 4, 5]" << std::endl;
    std::cout << "b = [5, 4, 3, 2, 1]" << std::endl;
    std::cout << "inner<5>(a, b) = " << inner<5>(a, b) << std::endl;
    // 1*5 + 2*4 + 3*3 + 4*2 + 5*1 = 5+8+9+8+5 = 35

    double c[3] = {1.0, 0.0, 0.0};
    double d[3] = {0.0, 1.0, 0.0};
    std::cout << "inner<3> wektorow ortogonalnych = " << inner<3>(c, d) << std::endl;

    

    return 0;
}
