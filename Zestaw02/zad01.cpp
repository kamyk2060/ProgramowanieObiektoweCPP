#include <iostream>



// 1. Polimorfizm statyczny
// Przeciążanie funkcji
int dodaj(int a, int b) { return a + b; }
double dodaj(double a, double b) { return a + b; }

// 2. Polimorfizm dynamiczny
class Zwierze {
public:
    virtual void dzwiek() { std::cout << "..."; }
};

class Pies : public Zwierze {
public:
    void dzwiek() override { std::cout << "Hau!"; }
};

class Kot : public Zwierze {
public:
    void dzwiek() override { std::cout << "Miau!"; }
};


// 3. Funkcja wirtualna
class Pojazd {
public:
    virtual void jedz() = 0;  // Czysta funkcja wirtualna -> klasa abstrakcyjna
};

// Pojazd p; // Błąd kompilacji!
class Samochod : public Pojazd {
public:
    void jedz() override { std::cout << "Samochod jedzie"; }
};


 // 4. Klasa abstrakcyjna
class Figura {          // klasa abstrakcyjna
public:
    virtual double pole() = 0;  // czysta funkcja wirtualna
    virtual double obwod() = 0;  // czysta funkcja wirtualna
    virtual ~Figura() {}
};

class Prostokat : public Figura {
    double a, b;
public:
    Prostokat(double a, double b) : a(a), b(b) {}
    double pole()  override { return a * b; }
    double obwod() override { return 2 * (a + b); }
};



int main () {

    
    // 1. Polimorfizm statyczny
    // Polimorfizm statyczny (zwany też polimorfizmem czasu kompilacji) to mechanizm, w którym wybór odpowiedniej funkcji/metody dokonywany jest przez kompilator jeszcze przed uruchomieniem programu.
    // Realizowany jest głównie przez:

    // przeciążanie funkcji (function overloading) – wiele funkcji o tej samej nazwie, różniących się listą parametrów,
    // szablony (templates) – kompilator generuje konkretne wersje kodu dla różnych typów.

    // Kompilator już w trakcie kompilacji wie, którą wersję wywołać
    dodaj(2, 3);       // int
    dodaj(2.0, 3.0);   // double

    

    // 2. Polimorfizm dynamiczny
    // Polimorfizm dynamiczny (zwany też polimorfizmem czasu wykonania) to mechanizm, w którym wybór odpowiedniej metody dokonywany jest dopiero w trakcie działania programu, w zależności od rzeczywistego typu obiektu.
    // Realizowany jest przez:

    // dziedziczenie + funkcje wirtualne,
    // wywołanie przez wskaźnik lub referencję do klasy bazowej.

    Zwierze* z = new Pies();
    z->dzwiek(); // decyzja podjęta w trakcie działania programu

    // 3. Funkcja wirtualna
    // Funkcja wirtualna to metoda klasy zadeklarowana ze słowem kluczowym virtual, która może zostać nadpisana (overridden) w klasie pochodnej. Dzięki niej możliwy jest polimorfizm dynamiczny.
    std::cout << std::endl;
    Pojazd* s = new Samochod();
    s->jedz();

    // 4. Klasa abstrakcyjna
    // Klasa abstrakcyjna to klasa, która zawiera co najmniej jedną czystą funkcję wirtualną.
    // Nie można tworzyć obiektów klasy abstrakcyjnej — służy ona wyłącznie jako szablon/kontrakt dla klas pochodnych, które muszą zaimplementować wszystkie czyste metody wirtualne.
    std::cout << std::endl;
    // Figura f;           // BŁĄD! Nie można tworzyć obiektów klasy abstrakcyjnej
    Figura* f = new Prostokat(3, 4);  // OK - wskaźnik na klasę bazową
    std::cout << f->pole();    // 12

    return 0;
}