#include <iostream>
#include <vector>
#include <list>
#include <set>
using namespace std;

template <typename InputIterator,typename T>
T accumulate(InputIterator first, InputIterator last, T init) {
    T total = init;
    for ( ; first != last; ++first)
        total += *first;
    return total;
}

int main() {
    vector<int> v = {1, 2, 3, 4, 5};
    cout << "vector<int>: " << accumulate(v.begin(), v.end(), 0) << "\n";

    list<double> l = {1.5, 2.5, 3.0};
    cout << "list<double>: " << accumulate(l.begin(), l.end(), 0.0) << "\n";

    // Suma czesci kontenera z wartoscia poczatkowa 100
    cout << "v + init=100: " << accumulate(v.begin(), v.end(), 100) << "\n";

    return 0;
}
