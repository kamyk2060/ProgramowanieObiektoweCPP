
// weak_ptr - sluzy do obserwowania obiektu zarzadzanego przez shared_ptr
// bez zwiekszania licznika referencji.
// Nie pozwala bezposrednio dostac sie do obiektu - trzeba wywolac lock(),
// ktora zwraca shared_ptr (lub pusty jesli obiekt juz nie istnieje).

#include <iostream>
#include <memory>
#include <string>

class Wezel {
public:
    std::string nazwa;
    std::shared_ptr<Wezel> nastepny;
    std::weak_ptr<Wezel> poprzedni; 

    Wezel(const std::string& n) : nazwa(n) {
        std::cout << "Konstruktor: " << nazwa << "\n";
    }
    ~Wezel() {
        std::cout << "Destruktor: " << nazwa << "\n";
    }
};

int main() {
    std::cout << "--- Przyklad:\n";
    std::weak_ptr<int> obserwator;
    {
        std::shared_ptr<int> mocny = std::make_shared<int>(42);
        obserwator = mocny;
        std::cout << "licznik referencji: " << mocny.use_count() << "\n";
        std::cout << "obserwator.expired()? " << obserwator.expired() << "\n";

        // lock() zwraca shared_ptr - mozna bezpiecznie uzyc obiektu
        if (auto p = obserwator.lock()) {
            std::cout << "wartosc przez weak_ptr: " << *p << "\n";
        }
    } // mocny znika, obiekt jest usuwany

    std::cout << "\nPo wyjsciu shared_ptr z zakresu:\n";
    std::cout << "obserwator.expired()? " << obserwator.expired() << "\n";
    if (auto p = obserwator.lock()) {
        std::cout << "wartosc: " << *p << "\n";
    } else {
        std::cout << "obiekt juz nie istnieje\n";
    }

    std::cout << "\nKoniec main\n";
    return 0;
}
