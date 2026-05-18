
#include <iostream>
#include <memory>

int main() {
    int* zwykly = nullptr;
    std::unique_ptr<int> u;
    std::shared_ptr<int> s;
    std::weak_ptr<int> w;

    std::cout << "sizeof(int*) = " << sizeof(zwykly) << "\n";
    std::cout << "sizeof(unique_ptr<int>) = " << sizeof(u) << "\n";
    std::cout << "sizeof(shared_ptr<int>) = " << sizeof(s) << "\n";
    std::cout << "sizeof(weak_ptr<int>) = " << sizeof(w) << "\n";

    // unique_ptr ma rozmiar zwyklego wskaznika (przechowuje tylko sam wskaznik).
    // shared_ptr i weak_ptr maja rozmiar dwoch wskaznikow,
    // bo dodatkowo trzymaja wskaznik na blok kontrolny z licznikiem referencji.

    return 0;
}
