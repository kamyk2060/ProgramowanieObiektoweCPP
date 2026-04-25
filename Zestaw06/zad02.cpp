#include <iostream>
#include <cstdlib>

// Wytyczna: brak sprawdzania zakresu
struct No_checking_policy {
    static void check_push(size_t, size_t) {}
    static void check_pop(size_t) {}
    static void check_top(size_t) {}
};

// Wytyczna: przerywanie dzialania przy bledzie
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

template <typename T = int, size_t N = 100,
          typename Checking_policy = No_checking_policy>
class Stack {
private:
    T _rep[N];
    size_t _top;
public:
    Stack() : _top(0) {}

    void push(const T &val) {
        Checking_policy::check_push(_top, N);
        _rep[_top++] = val;
    }

    void pop() {
        Checking_policy::check_pop(_top);
        --_top;
    }

    const T& top() const {
        Checking_policy::check_top(_top);
        return _rep[_top - 1];
    }

    bool is_empty() const {
        return !_top;
    }
};

int main() {
    Stack<int, 5> s_no_check;
    for (int i = 0; i < 5; ++i) s_no_check.push(i * 10);
    std::cout << "s_no_check wierzcholek: " << s_no_check.top() << std::endl;

    Stack<int, 3, Abort_on_error_policy> s_abort;
    s_abort.push(1);
    s_abort.push(2);
    s_abort.push(3);
    std::cout << "s_abort wierzcholek: " << s_abort.top() << std::endl;
    s_abort.pop();
    std::cout << "s_abort po pop: " << s_abort.top() << std::endl;

    // Odkomentowanie spowoduje abort:
    // s_abort.push(4); s_abort.push(5); s_abort.push(6);

    return 0;
}
