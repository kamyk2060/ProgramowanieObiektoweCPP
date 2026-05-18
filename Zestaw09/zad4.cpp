// Dwie specjalizacje szablonu make_unique:
// 1) template<class T, class... Args> unique_ptr<T> make_unique(Args&&... args);
//    Tworzy pojedynczy obiekt typu T i przekazuje argumenty do jego konstruktora.
//  
//
// 2) template<class T> unique_ptr<T> make_unique(std::size_t size);
//    Tworzy tablice elementow typu T o podanym rozmiarze.
//    T w zapisie musi byc tablicowy, np. make_unique<int[]>(5).


#include <iostream>
#include <memory>
#include <string>

class Punkt {
public:
    int x, y;
    Punkt(int a, int b) : x(a), y(b) {
        std::cout << "Punkt(" << x << "," << y << ")\n";
    }
    Punkt() : x(0), y(0) {
        std::cout << "Punkt domyslny\n";
    }
    ~Punkt() {
        std::cout << "~Punkt(" << x << "," << y << ")\n";
    }
};

int main() {
    std::cout << "Specjalizacja 1: pojedynczy obiekt z argumentami\n";
    auto p = std::make_unique<Punkt>(3, 7);
    std::cout << "p = (" << p->x << "," << p->y << ")\n";

    std::cout << "\nSpecjalizacja 2: tablica obiektow\n";
    auto tab = std::make_unique<Punkt[]>(3); // 3 obiekty domyslne
    for (int i = 0; i < 3; ++i) {
        tab[i].x = i;
        tab[i].y = i * 10;
    }
    for (int i = 0; i < 3; ++i) {
        std::cout << "tab[" << i << "] = (" << tab[i].x << "," << tab[i].y << ")\n";
    }

    std::cout << "\nTablica int\n";
    auto liczby = std::make_unique<int[]>(5);
    for (int i = 0; i < 5; ++i) liczby[i] = i * i;
    for (int i = 0; i < 5; ++i) std::cout << liczby[i] << " ";
    std::cout << "\n";

    std::cout << "\nKoniec main - destruktory:\n";
    return 0;
}
