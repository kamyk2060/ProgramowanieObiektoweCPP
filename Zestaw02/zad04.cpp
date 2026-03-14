#include <iostream>
#include <vector>
#include <algorithm>
#include <functional>
using namespace std;

template <class T>
class SequenceGen {
    T aktualna;
    T krok;
public:
    SequenceGen(T start, T krok) : aktualna(start), krok(krok) {}

    T operator()() {
        T wynik = aktualna;
        aktualna += krok;
        return wynik;
    }
};

int main() {
    vector<int> v(20);
    generate_n(v.begin(), 20, SequenceGen<int>(1, 2));

    cout << "int: ";
    for (int x : v) cout << x << " ";
    cout << "\n";

    vector<int>::iterator it = find_if(v.begin(), v.end(), bind2nd(greater<int>(), 4));
    if (it != v.end())
        cout << "Int pierwszy wiekszy od 4: " << *it << "\n";

    return 0;
}