
#include <iostream>
#include <string>

// znacznik konca listy
class Null_type {};

template<typename H, typename T>
struct Type_list {
    typedef H head;
    typedef T tail;
};


// Length - dlugosc listy typow 

template<typename TList>
struct Length;

template<>
struct Length<Null_type> {
    enum { value = 0 };
};

template<typename H, typename T>
struct Length<Type_list<H, T>> {
    enum { value = 1 + Length<T>::value };
};


// At - dostep do elementu pod indeksem 

template<typename TList, std::size_t I>
struct At;

// indeks 0 -> glowa listy
template<typename H, typename T>
struct At<Type_list<H, T>, 0> {
    typedef H result;
};

// indeks I -> szukaj w ogonie pod indeksem I-1
template<typename H, typename T, std::size_t I>
struct At<Type_list<H, T>, I> {
    typedef typename At<T, I - 1>::result result;
};


// Contains - czy dany typ jest w liscie 

template<typename TList, typename U>
struct Contains;

// pusta lista - nie ma szukanego typu
template<typename U>
struct Contains<Null_type, U> {
    enum { value = false };
};

// glowa == szukany typ -> znaleziono
template<typename Tail, typename U>
struct Contains<Type_list<U, Tail>, U> {
    enum { value = true };
};

// glowa != szukany -> szukaj w ogonie
template<typename Head, typename Tail, typename U>
struct Contains<Type_list<Head, Tail>, U> {
    enum { value = Contains<Tail, U>::value };
};


int main() {
    // lista: (int, double, std::string)
    typedef Type_list<int,
            Type_list<double,
            Type_list<std::string, Null_type>>> lista;

    std::cout << "Length <lista> = " << Length<lista>::value << "\n";
    std::cout << "At <lista, 1> = " << typeid(At<lista, 1>::result).name() << "\n";
    std::cout << "Contains<lista, int> = " << Contains<lista, int>::value << "\n";
    std::cout << "Contains<lista, float> = " << Contains<lista, float>::value << "\n";

    return 0;
}