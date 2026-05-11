#include <iostream>

template <typename F>
double integrate(F f, double min, double max, double ds) {
    double integral = 0.0;
    for (double x = min; x < max; x += ds) {
        integral += f(x);
    }
    return integral * ds;
}

class Variable {
public:
    double operator()(double x) { return x; }
};

class Constant {
    double _c;
public:
    Constant(double c) : _c(c) {}
    double operator()(double) { return _c; }
};

// suma
template <typename LHS, typename RHS>
class AddExpr {
    LHS _lhs;
    RHS _rhs;
public:
    AddExpr(const LHS &l, const RHS &r) : _lhs(l), _rhs(r) {}
    double operator()(double x) {
        return _lhs(x) + _rhs(x);
    }
};

// Operator+ dla dwoch dowolnych funktorow
template <typename LHS, typename RHS>
AddExpr<LHS, RHS> operator+(const LHS &l, const RHS &r) {
    return AddExpr<LHS, RHS>(l, r);
}

// lewa strona dowolny funktor, prawa double
template <typename LHS>
AddExpr<LHS, Constant> operator+(const LHS &l, double r) {
    return AddExpr<LHS, Constant>(l, Constant(r));
}

// lewa strona double, prawa dowolny funktor
template <typename RHS>
AddExpr<Constant, RHS> operator+(double l, const RHS &r) {
    return AddExpr<Constant, RHS>(Constant(l), r);
}

int main() {
    Variable x;

    // Calka z x po [0,1] = 0.5
    std::cout << "integrate(x, 0, 1, 0.001) = "
              << integrate(x, 0, 1, 0.001) << std::endl;

    // Calka z (x + 1) po [0,1] = 0.5 + 1 = 1.5
    std::cout << "integrate(x + 1.0, 0, 1, 0.001) = "
              << integrate(x + 1.0, 0, 1, 0.001) << std::endl;

    // Calka z (2 + x) po [0,1] = 2 + 0.5 = 2.5
    std::cout << "integrate(2.0 + x, 0, 1, 0.001) = "
              << integrate(2.0 + x, 0, 1, 0.001) << std::endl;

    // Calka z (x + x) = 2x po [0,1] = 1
    std::cout << "integrate(x + x, 0, 1, 0.001) = "
              << integrate(x + x, 0, 1, 0.001) << std::endl;

    return 0;
}
