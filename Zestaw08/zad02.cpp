#include <iostream>

template <typename F>
double integrate(F f, double min, double max, double ds) {
    double integral = 0.0;
    for (double x = min; x < max; x += ds) {
        integral += f(x);
    }
    return integral * ds;
}

// Zmienna x 
class Variable {
public:
    double operator()(double x) { return x; }
};

// Stala 
class Constant {
    double _c;
public:
    Constant(double c) : _c(c) {}
    double operator()(double) { return _c; }
};

int main() {
    Variable x;

    // Calka z x po przedziale [0,1] = 1/2
    std::cout << "integrate(x, 0, 1, 0.001) = "
              << integrate(x, 0, 1, 0.001) << std::endl;

    // Calka ze stalej 1 po przedziale [0,1] = 1
    std::cout << "integrate(Constant(1.0), 0, 1, 0.001) = "
              << integrate(Constant(1.0), 0, 1, 0.001) << std::endl;

    // Calka ze stalej 2.5 po przedziale [0,4] = 10
    std::cout << "integrate(Constant(2.5), 0, 4, 0.001) = "
              << integrate(Constant(2.5), 0, 4, 0.001) << std::endl;

    return 0;
}
