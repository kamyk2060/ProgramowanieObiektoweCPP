
#include <iostream>
#include <vector>
using namespace std;

template<typename T, int N = 100, typename R = T*> class Stack;

template<typename T, int N> class Stack<T, N, T*> {
    T data[N];
    unsigned top_idx = 0;
public:
    void push(T e) { data[top_idx++] = e; }
    T pop() { return data[--top_idx]; }
    bool empty() const { return top_idx == 0; }
};

template<typename T, int N, template<typename E> class Sequence>
class Stack<T, N, Sequence<T> > {
    Sequence<T> container;
public:
    void push(T e) { container.push_back(e); }
    T pop() { T val = container.back(); container.pop_back(); return val; }
    bool empty() const { return container.empty(); }
};

int main() {
    Stack<int, 100> s_default;
    s_default.push(10);
    s_default.push(20);
    s_default.push(30);
    cout << "s_default:" << endl;
    while (!s_default.empty())
        cout << "  " << s_default.pop() << endl;

    Stack<int, 0, vector<int>> s_container;
    s_container.push(100);
    s_container.push(200);
    s_container.push(300);
    cout << "s_container:" << endl;
    while (!s_container.empty())
        cout << "  " << s_container.pop() << endl;
}