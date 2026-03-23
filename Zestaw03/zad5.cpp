
#include <iostream>
#include <set>
#include <functional>
using namespace std;

int main() {
    set<int, less<int>> rosnacy = {5, 3, 8, 1, 9, 2, 7, 4, 6};
    cout << "less: ";
    for (int v : rosnacy) cout << v << " ";
    cout << endl;

    set<int, greater<int>> malejacy = {5, 3, 8, 1, 9, 2, 7, 4, 6};
    cout << "greater: ";
    for (int v : malejacy) cout << v << " ";
    cout << endl;

    malejacy.insert(10);
    malejacy.insert(0);
    malejacy.insert(5);
    cout << "po insert: ";
    for (int v : malejacy) cout << v << " ";
    cout << endl;
}