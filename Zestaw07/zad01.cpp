#include <iostream>

template <int N>
struct Factorial {
    enum { val = N * Factorial<N - 1>::val };
};

template <>
struct Factorial<0> {
    enum { val = 1 };
};

int main() {
    std::cout << "0! = " << Factorial<0>::val << std::endl;
    std::cout << "4! = " << Factorial<4>::val << std::endl;
    std::cout << "5! = " << Factorial<5>::val << std::endl;

    return 0;
}
