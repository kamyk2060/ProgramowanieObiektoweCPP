
#include <iostream>
#include <memory>
#include <string>

class Zasob {
public:
    std::string nazwa;
    Zasob(const std::string& n) : nazwa(n) {
        std::cout << "Konstruktor: " << nazwa << "\n";
    }
    ~Zasob() {
        std::cout << "Destruktor: " << nazwa << "\n";
    }
};

int main() {
    std::cout << "Tworze sp1\n";
    std::shared_ptr<Zasob> sp1 = std::make_shared<Zasob>("zasob");
    std::cout << "licznik = " << sp1.use_count() << "\n\n";

    {
        std::cout << "Tworze sp2 (kopia sp1)\n";
        std::shared_ptr<Zasob> sp2 = sp1;
        std::cout << "licznik = " << sp1.use_count() << "\n";

        {
            std::cout << "\nTworze sp3 (kopia sp2)\n";
            std::shared_ptr<Zasob> sp3 = sp2;
            std::cout << "licznik = " << sp1.use_count() << "\n";
            std::cout << "Wychodze z wewnetrznego bloku...\n";
        }
        std::cout << "licznik po znikniecu sp3 = " << sp1.use_count() << "\n";
        std::cout << "Wychodze ze srodkowego bloku...\n";
    }
    std::cout << "licznik po znikniecu sp2 = " << sp1.use_count() << "\n";

    std::cout << "\nResetuje sp1 - to ostatni wlasciciel\n";
    sp1.reset(); // teraz licznik = 0, destruktor zostanie wywolany
    std::cout << "Po reset() - obiekt juz usuniety\n";

    return 0;
}
