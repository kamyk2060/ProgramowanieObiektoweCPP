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
template <typename T, size_t N = 0>
struct Static_table_allocator {
    typedef T rep_type[N];
    void init(rep_type &, size_t) {}
    void expand_if_needed(rep_type &, size_t) {}
    void shrink_if_needed(rep_type &, size_t) {}
    void dealocate(rep_type &) {}
    static size_t size() { return N; }
};

// Alokator dynamiczny 
template <typename T, size_t N>
struct Dynamic_table_allocator {
    typedef T* rep_type;
    size_t _size;

    void init(rep_type &rep, size_t n) {
        _size = n;
        rep = new T[_size];
    }

    void expand_if_needed(rep_type &rep, size_t top) {
        if (top == _size) {
            _size = 2 * _size;
            T *tmp = new T[_size];
            std::copy(rep, rep + top, tmp);
            delete[] rep;
            rep = tmp;
        }
    }

    void shrink_if_needed(rep_type &, size_t) {}

    void dealocate(rep_type &rep) {
        delete[] rep;
    }

    size_t size() const { return _size; }
};

template <typename T = int, size_t N = 100,
          typename Checking_policy = No_checking_policy,
          template<typename U, size_t M> class Allocator_policy = Static_table_allocator>
class Stack {
private:
    typedef typename Allocator_policy<T, N>::rep_type rep_type;
    rep_type _rep;
    size_t _top;
    Allocator_policy<T, N> alloc;
public:
    Stack(size_t n = N) : _top(0) {
        alloc.init(_rep, n);
    }

    void push(const T &val) {
        alloc.expand_if_needed(_rep, _top);
        Checking_policy::check_push(_top, alloc.size());
        _rep[_top++] = val;
    }

    void pop() {
        Checking_policy::check_pop(_top);
        --_top;
        alloc.shrink_if_needed(_rep, _top);
    }

    const T& top() const {
        Checking_policy::check_top(_top);
        return _rep[_top - 1];
    }

    bool is_empty() const {
        return !_top;
    }

    ~Stack() {
        alloc.dealocate(_rep);
    }
};

int main() {
    // Stos ze statyczna alokacja
    Stack<int, 10, Abort_on_error_policy, Static_table_allocator> s1;
    for (int i = 1; i <= 5; ++i) s1.push(i);
    std::cout << "s1 (static) wierzcholek: " << s1.top() << std::endl;

    // Stos z dynamiczna alokacja - startuje od 4, sam sie powieksza do ~16
    Stack<int, 4, No_checking_policy, Dynamic_table_allocator> s2(4);
    for (int i = 0; i < 10; ++i) s2.push(i * 5);
    std::cout << "s2 (dynamic) wierzcholek: " << s2.top() << std::endl;

    std::cout << "Zawartosc s2 od gory: ";
    while (!s2.is_empty()) {
        std::cout << s2.top() << " ";
        s2.pop();
    }
    std::cout << std::endl;

    return 0;
}
