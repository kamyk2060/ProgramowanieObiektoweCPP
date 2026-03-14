#include <iostream>
#include <vector>
using namespace std;

// --- Polimorfizm statyczny ---

void info(int wartosc) { cout << "[int] " << wartosc << "\n"; }
void info(double wartosc) { cout << "[double] " << wartosc << "\n"; }
void info(const string& wartosc) { cout << "[string] " << wartosc << "\n"; }

// --- Polimorfizm dynamiczny ---

class Figura {
public:
    virtual double pole()  const = 0;
    virtual double obwod() const = 0;
    virtual string nazwa() const = 0;

    void wypisz() const {
        cout << nazwa() << " | pole=" << pole() << " | obwod=" << obwod() << "\n";
    }

    virtual ~Figura() {}
};

class Prostokat : public Figura {
    double a, b;
public:
    Prostokat(double a, double b) : a(a), b(b) {}
    double pole()  const override { return a * b; }
    double obwod() const override { return 2 * (a + b); }
    string nazwa() const override { return "Prostokat"; }
};

class Kolo : public Figura {
    double r;
    static constexpr double PI = 3.14159;
public:
    Kolo(double r) : r(r) {}
    double pole()  const override { return PI * r * r; }
    double obwod() const override { return 2 * PI * r; }
    string nazwa() const override { return "Kolo"; }
};

class Trojkat : public Figura {
    double a, h;
public:
    Trojkat(double a, double h) : a(a), h(h) {}
    double pole()  const override { return (a * h) / 2.0; }
    double obwod() const override { return 3 * a; }
    string nazwa() const override { return "Trojkat"; }
};


int main() {
    cout << "Polimorfizm statyczny\n";
    info(42);
    info(3.14);
    info("Czesc!");

    cout << "\nPolimorfizm dynamiczny\n";
    vector<Figura*> figury = {
        new Prostokat(4, 5),
        new Kolo(3),
        new Trojkat(6, 4)
    };

    for (const Figura* f : figury) f->wypisz();
    for (Figura* f : figury) delete f;

    return 0;
}