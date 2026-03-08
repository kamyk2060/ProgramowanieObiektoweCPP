#include <iostream>

template<size_t N, typename T>
T dot_product(T *a, T *b) {
    T result = 0.0;
    for (size_t i {}; i < N; ++i) {
        result += a[i] * b[i];
    }

    return result;
}


int main() {

    int a[] = {1, 2, 3};
    int b[] = {4, 5, 6};
    std::cout << "Iloczyn skalarny: " << dot_product<3>(a, b) << std::endl;  // 1*4 + 2*5 + 3*6 = 32
    
    return 0;
}