
#include <iostream>
using namespace std;

template<typename T, typename U> 
T convert(U u) {
    return static_cast<T>(u);
}

template<> 
int convert<int, double>(double u) {
    return static_cast<int>(u);
}

template<> 
double convert<double, double>(double u) {
    return static_cast<double>(u);
}

int main() {
    cout << "convert<int>(3.14) = " << convert<int>(3.14) << endl;
    cout << "convert<double>(2.71) = " << convert<double>(2.71) << endl;
    cout << "convert<float>(9.99) = " << convert<float>(9.99) << endl;
    cout << "convert<char>(65) = '" << convert<char>(65) << "'" << endl;
}