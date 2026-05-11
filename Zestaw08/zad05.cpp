#include <iostream>
#include <complex>
#include <cmath>

template <typename F, typename T>
T integrate(F f, T min, T max, T ds) {
    T integral = T();
    for (T x = min; x < max; x += ds) {
        integral += f(x);
    }
    return integral * ds;
}

// Wyrazenia bazowe sparametryzowane typem T
template <typename T>
class Variable {
public:
    T operator()(T x) const { return x; }
};

template <typename T>
class Constant {
    T _c;
public:
    Constant(T c) : _c(c) {}
    T operator()(T) const { return _c; }
};

template <typename T, typename LHS, typename RHS>
class AddExpr {
    LHS _lhs;
    RHS _rhs;
public:
    AddExpr(const LHS &l, const RHS &r) : _lhs(l), _rhs(r) {}
    T operator()(T x) const { return _lhs(x) + _rhs(x); }
};

template <typename T, typename LHS, typename RHS>
class MultExpr {
    LHS _lhs;
    RHS _rhs;
public:
    MultExpr(const LHS &l, const RHS &r) : _lhs(l), _rhs(r) {}
    T operator()(T x) const { return _lhs(x) * _rhs(x); }
};

// Klasa opakowujaca 
template <typename T, typename R = Variable<T> >
class Expr {
    R _rep;
public:
    Expr() {}
    Expr(R rep) : _rep(rep) {}
    T operator()(T x) const { return _rep(x); }
    R rep() const { return _rep; }
};

// Operator+ teraz dziala na Expr<T,...> wiec T da sie wydedukowac
template <typename T, typename LHS, typename RHS>
Expr<T, AddExpr<T, LHS, RHS> >
operator+(const Expr<T, LHS> &l, const Expr<T, RHS> &r) {
    return Expr<T, AddExpr<T, LHS, RHS> >(
        AddExpr<T, LHS, RHS>(l.rep(), r.rep())
    );
}

template <typename T, typename LHS>
Expr<T, AddExpr<T, LHS, Constant<T> > >
operator+(const Expr<T, LHS> &l, T r) {
    return Expr<T, AddExpr<T, LHS, Constant<T> > >(
        AddExpr<T, LHS, Constant<T> >(l.rep(), Constant<T>(r))
    );
}

template <typename T, typename RHS>
Expr<T, AddExpr<T, Constant<T>, RHS> >
operator+(T l, const Expr<T, RHS> &r) {
    return Expr<T, AddExpr<T, Constant<T>, RHS> >(
        AddExpr<T, Constant<T>, RHS>(Constant<T>(l), r.rep())
    );
}

// Mnozenie - tylko zeby pokazac ze cala maszyneria sie skaluje
template <typename T, typename LHS, typename RHS>
Expr<T, MultExpr<T, LHS, RHS> >
operator*(const Expr<T, LHS> &l, const Expr<T, RHS> &r) {
    return Expr<T, MultExpr<T, LHS, RHS> >(
        MultExpr<T, LHS, RHS>(l.rep(), r.rep())
    );
}

template <typename T, typename LHS>
Expr<T, MultExpr<T, LHS, Constant<T> > >
operator*(const Expr<T, LHS> &l, T r) {
    return Expr<T, MultExpr<T, LHS, Constant<T> > >(
        MultExpr<T, LHS, Constant<T> >(l.rep(), Constant<T>(r))
    );
}

int main() {
    // Wersja double
    Expr<double> x;
    std::cout << "integrate(x + 1.0, 0, 1, 0.001) = "
              << integrate(x + 1.0, 0.0, 1.0, 0.001) << std::endl;

    std::cout << "integrate(x * 2.0 + 1.0, 0, 1, 0.001) = "
              << integrate(x * 2.0 + 1.0, 0.0, 1.0, 0.001) << std::endl;

    // Wersja float 
    Expr<float> xf;
    std::cout << "integrate<float>(xf + 1.0f, 0, 1, 0.001) = "
              << integrate(xf + 1.0f, 0.0f, 1.0f, 0.001f) << std::endl;

    return 0;
}
