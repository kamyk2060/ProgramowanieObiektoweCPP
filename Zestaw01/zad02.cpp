#include <iostream>
#include <string>
#include <sstream>

template<typename T, typename U> 
T convert(U value) {
    return T(value);
}


int main() {

    std::cout << convert<char>(65) << std::endl;    // A
    std::cout << convert<char>(66) << std::endl;    // B
    std::cout << convert<int>('A') << std::endl;    // 65

    
    return 0;
}