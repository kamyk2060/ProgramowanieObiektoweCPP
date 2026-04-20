
#include <iostream>
#include <string>

template<typename T, typename U>
class Is_convertible {
    typedef char one;
    typedef struct { char c[2]; } two;

    // Tym razem korzystamy ze zwyklych przeciazonych funkcji
    static one test(U);      // wybierana gdy argument pasuje do U
    static two test(...);    // wybierana gdy nic innego nie pasuje
    static T makeT();        // zwraca obiekt typu T 

public:
    enum {
        yes = sizeof(test(makeT())) == sizeof(one),
        same_type = false
    };
};

// Specjalizacja dla identycznych typow
template<typename T>
class Is_convertible<T, T> {
public:
    enum {
        yes = true,
        same_type = true
    };
};


// Klasy do testow dziedziczenia
class Bazowa {};
class Pochodna : public Bazowa {};
class Niezwiazana {};


int main() {
    
    std::cout << "int -> double: yes=" << Is_convertible<int, double>::yes 
              << ", same=" << Is_convertible<int, double>::same_type << "\n";
    
    std::cout << "double -> int: yes=" << Is_convertible<double, int>::yes
              << ", same=" << Is_convertible<double, int>::same_type << "\n";
    
    std::cout << "int -> int: yes=" << Is_convertible<int, int>::yes
              << ", same=" << Is_convertible<int, int>::same_type << "\n";
    
    std::cout << "Pochodna* -> Bazowa*: yes=" << Is_convertible<Pochodna*, Bazowa*>::yes
              << ", same=" << Is_convertible<Pochodna*, Bazowa*>::same_type << "\n";
    
    std::cout << "Bazowa* -> Pochodna*: yes=" << Is_convertible<Bazowa*, Pochodna*>::yes
              << ", same=" << Is_convertible<Bazowa*, Pochodna*>::same_type << "\n";
    
    std::cout << "Niezwiazana -> Bazowa: yes=" << Is_convertible<Niezwiazana, Bazowa>::yes
              << ", same=" << Is_convertible<Niezwiazana, Bazowa>::same_type << "\n";
    

    return 0;
}