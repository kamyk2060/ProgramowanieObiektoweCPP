
#include <iostream>
#include <string>
#include <vector>
#include <list>
#include <map>

template<typename T>
class has_value_type {
    typedef char one;
    typedef struct { char c[2]; } two;

    // pierwsza funkcja pasuje tylko gdy U::value_type istnieje
    template<typename U> static one test(typename U::value_type*);
    // druga - wariadyczna, pasuje do czegokolwiek
    template<typename U> static two test(...);

public:
    enum { yes = (sizeof(test<T>(0)) == sizeof(one)) };
};


// wlasna klasa z typem stowarzyszonym
struct MojTyp {
    typedef double value_type;
};

// wlasna klasa bez typu stowarzyszonego
struct InnyTyp {
    int x;
};


int main() {

    // typy posiadajace value_type
    std::cout << "std::vector<int>: " << has_value_type<std::vector<int>>::yes << "\n";
    std::cout << "std::string: " << has_value_type<std::string>::yes << "\n";
    std::cout << "MojTyp (wlasny z value_type): " << has_value_type<MojTyp>::yes << "\n";

    std::cout << "\n";

    // typy nie posiadajace value_type
    std::cout << "int: " << has_value_type<int>::yes << "\n";
    std::cout << "double: " << has_value_type<double>::yes << "\n";
    std::cout << "char*: " << has_value_type<char*>::yes << "\n";
    std::cout << "InnyTyp (bez value_type): " << has_value_type<InnyTyp>::yes << "\n";

    return 0;
}