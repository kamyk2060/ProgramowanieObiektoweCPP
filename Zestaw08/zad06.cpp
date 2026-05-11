#include <iostream>

// Calkowanie 1D - funktor jedoargumentowy
template <typename F>
double integrate(F f, double min, double max, double ds) {
    double integral = 0.0;
    for (double x = min; x < max; x += ds) {
        integral += f(x);
    }
    return integral * ds;
}

// Calkowanie 2D - funktor dwuargumentowy
template <typename F>
double integrate2(F f, double xmin, double xmax,
                  double ymin, double ymax, double ds) {
    double integral = 0.0;
    for (double x = xmin; x < xmax; x += ds) {
        for (double y = ymin; y < ymax; y += ds) {
            integral += f(x, y);
        }
    }
    return integral * ds * ds;
}

// Pierwszy argument 
class First {
public:
    double operator()(double x) { return x; }
    double operator()(double x, double) { return x; }
};

// Drugi argument 
class Second {
public:
    double operator()(double, double y) { return y; }
};

// Stala - dziala dla obu wariantow
class Constant {
    double _c;
public:
    Constant(double c) : _c(c) {}
    double operator()(double) { return _c; }
    double operator()(double, double) { return _c; }
};

// Suma - oba operatory nawiasowe
template <typename LHS, typename RHS>
class AddExpr {
    LHS _lhs;
    RHS _rhs;
public:
    AddExpr(const LHS &l, const RHS &r) : _lhs(l), _rhs(r) {}
    double operator()(double x) { return _lhs(x) + _rhs(x); }
    double operator()(double x, double y) { return _lhs(x, y) + _rhs(x, y); }
};

// Iloczyn - oba operatory nawiasowe
template <typename LHS, typename RHS>
class MultExpr {
    LHS _lhs;
    RHS _rhs;
public:
    MultExpr(const LHS &l, const RHS &r) : _lhs(l), _rhs(r) {}
    double operator()(double x) { return _lhs(x) * _rhs(x); }
    double operator()(double x, double y) { return _lhs(x, y) * _rhs(x, y); }
};

// Operatory pozostaja bez zmian 
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

template <typename LHS, typename RHS>
MultExpr<LHS, RHS> operator*(const LHS &l, const RHS &r) {
    return MultExpr<LHS, RHS>(l, r);
}

template <typename LHS>
MultExpr<LHS, Constant> operator*(const LHS &l, double r) {
    return MultExpr<LHS, Constant>(l, Constant(r));
}

template <typename RHS>
MultExpr<Constant, RHS> operator*(double l, const RHS &r) {
    return MultExpr<Constant, RHS>(Constant(l), r);
}

int main() {
    First x;
    Second y;

    // Calka z (x + y) po kwadracie [0,1]x[0,1] = 1
    std::cout << "integrate2(x + y, [0,1]x[0,1], 0.01) = "
              << integrate2(x + y, 0, 1, 0, 1, 0.01) << std::endl;

    // Calka z (x*y) po [0,1]x[0,1] = 1/4
    std::cout << "integrate2(x * y, [0,1]x[0,1], 0.01) = "
              << integrate2(x * y, 0, 1, 0, 1, 0.01) << std::endl;


    return 0;
}
