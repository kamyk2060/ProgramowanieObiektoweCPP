#include <iostream>


template<typename T>
T maksimum(T a, T b) {
    return (a < b) ? a : b;
}


int main() {

    std::cout << maksimum(5, 10) << std::endl;           // int
    std::cout << maksimum(3.14, 2.71) << std::endl;      // double
    std::cout << maksimum('a', 'z') << std::endl;         // char

    return 0;
}