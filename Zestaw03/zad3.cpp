// Zadanie 3 - specjalizacje szablonu klasy Stack
// g++ -std=c++17 -o zad3 zad3.cpp

#include <iostream>
using namespace std;

template<typename T, int N = 100> class Stack {
    T data[N];
    unsigned top_idx = 0;
public:
    void push(T e) { data[top_idx++] = e; }
    T pop() { return data[--top_idx]; }
    bool empty() const { return top_idx == 0; }
    static const char* info() { return "Stack<T,N>"; }
};

template<typename T> class Stack<T, 666> {
    T data[666];
    unsigned top_idx = 0;
public:
    void push(T e) { data[top_idx++] = e; }
    T pop() { return data[--top_idx]; }
    bool empty() const { return top_idx == 0; }
    static const char* info() { return "Stack<T,666>"; }
};

template<typename T, int N> class Stack<T*, N> {
    T* data[N];
    unsigned top_idx = 0;
public:
    void push(T* e) { data[top_idx++] = e; }
    T* pop() { return data[--top_idx]; }
    bool empty() const { return top_idx == 0; }
    static const char* info() { return "Stack<T*,N>"; }
};

template<int N> class Stack<double, N> {
    double data[N];
    unsigned top_idx = 0;
public:
    void push(double e) { data[top_idx++] = e; }
    double pop() { return data[--top_idx]; }
    bool empty() const { return top_idx == 0; }
    static const char* info() { return "Stack<double,N>"; }
};

template<int N> class Stack<int*, N> {
    int* data[N];
    unsigned top_idx = 0;
public:
    void push(int* e) { data[top_idx++] = e; }
    int* pop() { return data[--top_idx]; }
    bool empty() const { return top_idx == 0; }
    static const char* info() { return "Stack<int*,N>"; }
};

template<> class Stack<double, 666> {
    double data[666];
    unsigned top_idx = 0;
public:
    void push(double e) { data[top_idx++] = e; }
    double pop() { return data[--top_idx]; }
    bool empty() const { return top_idx == 0; }
    static const char* info() { return "Stack<double,666>"; }
};

template<> class Stack<double*, 44> {
    double* data[44];
    unsigned top_idx = 0;
public:
    void push(double* e) { data[top_idx++] = e; }
    double* pop() { return data[--top_idx]; }
    bool empty() const { return top_idx == 0; }
    static const char* info() { return "Stack<double*,44>"; }
};

int main() {
    cout << Stack<int, 10>::info() << endl;
    cout << Stack<int, 666>::info() << endl;
    cout << Stack<int*, 10>::info() << endl;
    cout << Stack<double, 10>::info() << endl;
    cout << Stack<double, 666>::info() << endl;
    cout << Stack<double*, 44>::info() << endl;
    cout << Stack<char*, 5>::info() << endl;

    Stack<int, 10> s;
    s.push(42);
    s.push(17);
    cout << s.pop() << " " << s.pop() << endl;
}