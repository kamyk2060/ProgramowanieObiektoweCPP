// Trzy warianty: swobodny dostep, dwukierunkowy, gorszy niz dwukierunkowy
#include <iostream>
using std::cin;
using std::cout;
using std::endl;

#include <list>
using std::list;

#include <forward_list>
using std::forward_list;

#include <vector>
using std::vector;

#include <iterator>
using std::iterator_traits;
using std::forward_iterator_tag;
using std::bidirectional_iterator_tag;
using std::random_access_iterator_tag;


// Wersja dla iteratorow gorszych niz dwukierunkowe (input/forward)
template <typename Iter>
int operacja_impl(Iter i, forward_iterator_tag)
{
    cout << "Iterator jednokierunkowy (gorszy niz dwukierunkowy).\n";
    return 1;
}

// Wersja dla iteratorow dwukierunkowych
template <typename Iter>
int operacja_impl(Iter i, bidirectional_iterator_tag)
{
    cout << "Iterator dwukierunkowy.\n";
    return 2;
}

// Wersja dla iteratorow o swobodnym dostepie
template <typename Iter>
int operacja_impl(Iter i, random_access_iterator_tag)
{
    cout << "Iterator o swobodnym dostepie.\n";
    return 3;
}


template <typename Iter>
inline int operacja(Iter i)
{
    return operacja_impl(i, typename iterator_traits<Iter>::iterator_category());
}


int main()
{
    // forward_list -> forward_iterator (gorszy niz dwukierunkowy)
    forward_list<int> fl;
    operacja(fl.begin());

    // list -> bidirectional_iterator
    list<int> l;
    operacja(l.begin());

    // vector -> random_access_iterator
    vector<int> v;
    operacja(v.begin());

    // wskaznik -> random_access_iterator
    int t[3];
    operacja(t);

    return 0;
}