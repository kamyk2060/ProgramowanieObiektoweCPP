#include <iostream>


template <int K>
struct Kontener {
    int rozmiar = K;       
    void info() {
        std::cout << "Kontener o rozmiarze: " << K << std::endl;
    }
};


template <template <int> class C, int K>
void f(C<K> obj) {
    std::cout << "Wartosc K = " << K << std::endl;
    obj.info();
}

int main() {

    Kontener<5>  k5;
    Kontener<10> k10;
    f(k5);   
    f(k10); 
    
    return 0;
}