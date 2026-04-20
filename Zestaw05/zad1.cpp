
#include <iostream>
#include <string>
#include <vector>

template<typename T>
class is_class {
    typedef char one;
    typedef struct { char c[2]; } two;

    // pierwsza funkcja pasuje tylko gdy T jest klasa/struktura
    // (bo int U::* ma sens tylko dla takich typow)
    template<typename U> static one test(int U::*);
    // druga funkcja pasuje do czegokolwiek 
    template<typename U> static two test(...);

public:
    enum { yes = (sizeof(test<T>(0)) == sizeof(one)) };
};


// typy testowe
class MojaKlasa { int x; };
struct MojaStruktura { double y; };


int main() {
    
    std::cout << "int: " << is_class<int>::yes << "\n";
    std::cout << "double: " << is_class<double>::yes << "\n";
    std::cout << "int*: " << is_class<int*>::yes << "\n";
    std::cout << "MojaKlasa: " << is_class<MojaKlasa>::yes << "\n";
    std::cout << "MojaStruktura: " << is_class<MojaStruktura>::yes << "\n";
    std::cout << "std::string: " << is_class<std::string>::yes << "\n";
    return 0;
}