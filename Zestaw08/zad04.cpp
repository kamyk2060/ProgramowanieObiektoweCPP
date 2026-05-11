#include <iostream>
#include <cmath>

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

// Suma
template <typename LHS, typename RHS>
class AddExpr {
    LHS _lhs;
    RHS _rhs;
public:
    AddExpr(const LHS &l, const RHS &r) : _lhs(l), _rhs(r) {}
    double operator()(double x) { return _lhs(x) + _rhs(x); }
};

template <typename LHS, typename RHS>
AddExpr<LHS, RHS> operator+(const LHS &l, const RHS &r) {
    return AddExpr<LHS, RHS>(l, r);
}

template <typename LHS>
AddExpr<LHS, Constant> operator+(const LHS &l, double r) {
    return AddExpr<LHS, Constant>(l, Constant(r));
}

template <typename RHS>
AddExpr<Constant, RHS> operator+(double l, const RHS &r) {
    return AddExpr<Constant, RHS>(Constant(l), r);
}

// Iloraz
template <typename LHS, typename RHS>
class DivExpr {
    LHS _lhs;
    RHS _rhs;
public:
    DivExpr(const LHS &l, const RHS &r) : _lhs(l), _rhs(r) {}
    double operator()(double x) { return _lhs(x) / _rhs(x); }
};

template <typename LHS, typename RHS>
DivExpr<LHS, RHS> operator/(const LHS &l, const RHS &r) {
    return DivExpr<LHS, RHS>(l, r);
}

template <typename RHS>
DivExpr<Constant, RHS> operator/(double l, const RHS &r) {
    return DivExpr<Constant, RHS>(Constant(l), r);
}

template <typename LHS>
DivExpr<LHS, Constant> operator/(const LHS &l, double r) {
    return DivExpr<LHS, Constant>(l, Constant(r));
}

// sin
template <typename Arg>
class SinExpr {
    Arg _arg;
public:
    SinExpr(const Arg &arg) : _arg(arg) {}
    double operator()(double x) { return std::sin(_arg(x)); }
};

template <typename Arg>
SinExpr<Arg> sin(const Arg &a) {
    return SinExpr<Arg>(a);
}

int main() {
    Variable x;

    // Calka z 1/(1+x) po [0,1] = ln(2) ~= 0.693
    std::cout << "integrate(1.0/(1.0+x), 0, 1, 0.001) = "
              << integrate(1.0 / (1.0 + x), 0, 1, 0.001) << std::endl;

    // Calka z sin(x) po [0,pi] = 2
    std::cout << "integrate(sin(x), 0, pi, 0.001) = "
              << integrate(sin(x), 0, 3.1415926, 0.001) << std::endl;

    // Calka z sin(x+1) po [0,1]
    std::cout << "integrate(sin(x+1.0), 0, 1, 0.001) = "
              << integrate(sin(x + 1.0), 0, 1, 0.001) << std::endl;

    // Calka z 1/sin(x+1) po [0,1]
    std::cout << "integrate(1.0/sin(x+1.0), 0, 1, 0.001) = "
              << integrate(1.0 / sin(x + 1.0), 0, 1, 0.001) << std::endl;

    return 0;
}
