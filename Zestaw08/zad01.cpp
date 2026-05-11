#include <iostream>
#include <cmath>

// Szablon calkujacy 
template <typename F>
double integrate(F f, double min, double max, double ds) {
    double integral = 0.0;
    for (double x = min; x < max; x += ds) {
        integral += f(x);
    }
    return integral * ds;
}

// Funktor sin(a*x)
class sina {
    double _a;
public:
    sina(double a) : _a(a) {}
    double operator()(double x) { return std::sin(_a * x); }
};

int main() {
    std::cout << "integrate(sina(0), 0, pi, 0.01) = "
              << integrate(sina(0), 0, 3.1415926, 0.01) << std::endl;
  
    std::cout << "integrate(sina(2), 0, pi, 0.01) = "
              << integrate(sina(2), 0, 3.1415926, 0.01) << std::endl;

 
    return 0;
}
