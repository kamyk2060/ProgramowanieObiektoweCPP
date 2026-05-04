#include <iostream>

template <size_t N, typename T>
struct DotHelper {
    static inline T calc(T *x, T *y) {
        return x[N - 1] * y[N - 1] + DotHelper<N - 1, T>::calc(x, y);
    }
};

// dla N=0
template <typename T>
struct DotHelper<0, T> {
    static inline T calc(T *, T *) { return T(); }
};


template <size_t N, typename T>
inline T dot(T *x, T *y) {
    return DotHelper<N, T>::calc(x, y);
}

int main() {
    // Dla typu int
    int ai[4] = {1, 2, 3, 4};
    int bi[4] = {4, 3, 2, 1};
    std::cout << "dot<4,int>(a,b) = " << dot<4>(ai, bi) << std::endl;
    // 1*4 + 2*3 + 3*2 + 4*1 = 20

    // Dla typu double
    double ad[3] = {1.5, 2.5, 3.5};
    double bd[3] = {2.0, 2.0, 2.0};
    std::cout << "dot<3,double>(a,b) = " << dot<3>(ad, bd) << std::endl;
    // 3.0 + 5.0 + 7.0 = 15.0

    return 0;
}
