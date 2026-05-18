// Zadanie 1
// unique_ptr - inteligentny wskaznik z wylacznym wlascicielem zasobu.
//   Nie mozna go kopiowac, mozna tylko przenosic (std::move).
//   Gdy unique_ptr wychodzi poza zakres, automatycznie wywoluje delete.
//
// shared_ptr - inteligentny wskaznik z liczeniem referencji.
//   Wielu wspolwlascicieli moze trzymac ten sam zasob.
//   Kazda kopia zwieksza licznik, kazde znikniecie zmniejsza.
//   Gdy licznik = 0, obiekt jest usuwany.

#include <iostream>
#include <memory>
#include <string>

struct Obiekt {
    std::string nazwa;
    Obiekt(const std::string& n) : nazwa(n) {
        std::cout << "Konstruktor: " << nazwa << "\n";
    }
    ~Obiekt() {
        std::cout << "Destruktor: " << nazwa << "\n";
    }
};

int main() {
    std::cout << "--- unique_ptr ---\n";
    {
        std::unique_ptr<Obiekt> u = std::make_unique<Obiekt>("u1");
        // std::unique_ptr<Obiekt> u2 = u;         // blad - nie mozna kopiowac
        std::unique_ptr<Obiekt> u2 = std::move(u); // mozna przeniesc
        std::cout << "u jest pusty? " << (u == nullptr) << "\n";
        std::cout << "u2 trzyma: " << u2->nazwa << "\n";
    } // tu destruktor obiektu u1

    std::cout << "\n--- shared_ptr ---\n";
    {
        std::shared_ptr<Obiekt> s1 = std::make_shared<Obiekt>("s1");
        std::cout << "licznik referencji: " << s1.use_count() << "\n";
        {
            std::shared_ptr<Obiekt> s2 = s1; // kopia, licznik = 2
            std::cout << "licznik po kopii: " << s1.use_count() << "\n";
        } // s2 znika, licznik = 1
        std::cout << "licznik po wyjsciu s2 z zakresu: " << s1.use_count() << "\n";
    } // tu destruktor obiektu s1

    return 0;
}
