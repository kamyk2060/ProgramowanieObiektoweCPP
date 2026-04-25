#include <iostream>
#include <string>
#include <map>
#include <stdexcept>
using std::cout;


struct Kolor {
    unsigned char r, g, b;

    Kolor() : r(0), g(0), b(0) {}
    Kolor(unsigned char r_, unsigned char g_, unsigned char b_)
        : r(r_), g(g_), b(b_) {}
};

std::ostream& operator<<(std::ostream& os, const Kolor& k) {
    os << "RGB(" << (int)k.r << ", " << (int)k.g << ", " << (int)k.b << ")";
    return os;
}

 
// Domyslna polityka - rzuca wyjatek przy nieznanej nazwie
class PolitykaWyjatek {
public:
    Kolor nieznanyKolor(std::string nazwa) {
        throw std::runtime_error("Nieznany kolor: " + nazwa);
    }
};

// Alternatywna polityka jako zwykla klasa - zwraca ustalony kolor szary
class PolitykaDomyslnyKolor {
public:
    Kolor nieznanyKolor(std::string) {
        return Kolor(128, 128, 128);
    }
};

// Ta sama polityka w wersji szablonu - kolor domyslny przez trzy parametry
template <unsigned char R, unsigned char G, unsigned char B>
class PolitykaDomyslnyKolorT {
public:
    Kolor nieznanyKolor(std::string) {
        return Kolor(R, G, B);
    }
};

// Polityka z oryginalnego glownego programu
class MojaPolityka {
public:
    Kolor nieznanyKolor(std::string) {
        return Kolor();
    }
};


template <typename Polityka = PolitykaWyjatek>
class FabrykaKolorow : private Polityka {
    std::map<std::string, Kolor> slownik;
public:
    FabrykaKolorow() {
        slownik["czarny"] = Kolor(0, 0, 0);
        slownik["bialy"] = Kolor(255, 255, 255);
        slownik["czerwony"] = Kolor(255, 0, 0);
        slownik["zielony"] = Kolor(0, 255, 0);
        slownik["niebieski"] = Kolor(0, 0, 255);
    }

    Kolor zwrocKolor(std::string nazwa) {
        std::map<std::string, Kolor>::iterator it = slownik.find(nazwa);
        if (it != slownik.end())
            return it->second;
        return Polityka::nieznanyKolor(nazwa);
    }
};


FabrykaKolorow<> fabryka;
FabrykaKolorow<MojaPolityka> moja_fabryka;
FabrykaKolorow<PolitykaDomyslnyKolor> fabryka_szara;
FabrykaKolorow<PolitykaDomyslnyKolorT<255, 105, 180>> fabryka_rozowa;

int main() {
    try {
        cout << fabryka.zwrocKolor("zielony") << '\n';
        cout << fabryka.zwrocKolor("green") << '\n';
    } catch(...) {
        cout << "Zlapano wyjatek.\n";
    }

    cout << "--- MojaPolityka (czarny Kolor()) ---\n";
    cout << moja_fabryka.zwrocKolor("zielony") << '\n';
    cout << moja_fabryka.zwrocKolor("green") << '\n';

    cout << "--- PolitykaDomyslnyKolor (szary) ---\n";
    cout << fabryka_szara.zwrocKolor("zielony") << '\n';
    cout << fabryka_szara.zwrocKolor("green") << '\n';

    cout << "--- PolitykaDomyslnyKolorT<255,105,180> (rozowy) ---\n";
    cout << fabryka_rozowa.zwrocKolor("zielony") << '\n';
    cout << fabryka_rozowa.zwrocKolor("green") << '\n';

    return 0;
}
