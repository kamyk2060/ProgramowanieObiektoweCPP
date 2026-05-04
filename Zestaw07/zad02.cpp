#include <iostream>

template <int N, int M>
struct Pow {
    enum { val = N * Pow<N, M - 1>::val };
};

template <int N>
struct Pow<N, 0> {
    enum { val = 1 };
};

int main() {
    std::cout << "2^0 = " << Pow<2, 0>::val << std::endl;
    std::cout << "2^10 = " << Pow<2, 10>::val << std::endl;
    std::cout << "3^4 = " << Pow<3, 4>::val << std::endl;
    std::cout << "5^3 = " << Pow<5, 3>::val << std::endl;

    return 0;
}
