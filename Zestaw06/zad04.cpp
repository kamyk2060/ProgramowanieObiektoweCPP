#include <iostream>
#include <algorithm>
#include <cstdlib>

struct No_checking_policy {
    static void check_push(size_t, size_t) {}
    static void check_pop(size_t) {}
    static void check_top(size_t) {}
};

class Abort_on_error_policy {
public:
    static void check_push(size_t top, size_t size) {
        if (top >= size) {
            std::cerr << "proba wlozenia elementu na pelny stos: abort" << std::endl;
            std::abort();
        }
    }
    static void check_pop(size_t top) {
        if (top == 0) {
            std::cerr << "proba zdjecia elementu z pustego stosu: abort" << std::endl;
            std::abort();
        }
    }
    static void check_top(size_t top) {
        if (top == 0) {
            std::cerr << "proba odczytu wierzcholka pustego stosu: abort" << std::endl;
            std::abort();
        }
    }
};

// Alokator statyczny 
template <typename T, size_t N>
class Static_table_allocator {
protected:
    typedef T rep_type[N];
    rep_type _rep;

    void init(size_t) {}
    void expand_if_needed(size_t) {}
    void shrink_if_needed(size_t) {}
    void dealocate() {}
    static size_t size() { return N; }
};
    
// Alokator dynamiczny 
template <typename T, size_t N>
class Dynamic_table_allocator {
protected:
    typedef T* rep_type;
    rep_type _rep;
    size_t _size;

    void init(size_t n) {
        _size = n;
        _rep = new T[_size];
    }

    void expand_if_needed(size_t top) {
        if (top == _size) {
            _size = 2 * _size;
            T *tmp = new T[_size];
            std::copy(_rep, _rep + top, tmp);
            delete[] _rep;
            _rep = tmp;
        }
    }

    void shrink_if_needed(size_t) {}

    void dealocate() {
        delete[] _rep;
    }

    size_t size() const { return _size; }
};

template <typename T = int, size_t N = 100,
          typename Checking_policy = No_checking_policy,
          template<typename U, size_t M> class Allocator_policy = Static_table_allocator>
class Stack : private Checking_policy, private Allocator_policy<T, N> {
private:
    size_t _top;

    // Nazwy zalezne z klasy bazowej - sciagamy przez using
    using Allocator_policy<T, N>::_rep;
    using Allocator_policy<T, N>::init;
    using Allocator_policy<T, N>::expand_if_needed;
    using Allocator_policy<T, N>::shrink_if_needed;
    using Allocator_policy<T, N>::dealocate;
    using Allocator_policy<T, N>::size;

public:
    Stack(size_t n = N) : _top(0) {
        init(n);
    }

    void push(const T &val) {
        expand_if_needed(_top);
        Checking_policy::check_push(_top, size());
        _rep[_top++] = val;
    }

    void pop() {
        Checking_policy::check_pop(_top);
        --_top;
        shrink_if_needed(_top);
    }

    const T& top() const {
        Checking_policy::check_top(_top);
        return _rep[_top - 1];
    }

    bool is_empty() const {
        return !_top;
    }

    ~Stack() {
        dealocate();
    }
};

int main() {
    Stack<int, 10, Abort_on_error_policy, Static_table_allocator> s1;
    for (int i = 1; i <= 5; ++i) s1.push(i * 2);
    std::cout << "s1 (static) wierzcholek: " << s1.top() << std::endl;
    s1.pop();
    std::cout << "s1 po pop: " << s1.top() << std::endl;

    Stack<int, 4, No_checking_policy, Dynamic_table_allocator> s2(4);
    for (int i = 0; i < 8; ++i) s2.push(i + 1);
    std::cout << "s2 (dynamic) wierzcholek: " << s2.top() << std::endl;

    std::cout << "Zawartosc s2 od gory: ";
    while (!s2.is_empty()) {
        std::cout << s2.top() << " ";
        s2.pop();
    }
    std::cout << std::endl;

    return 0;
}
