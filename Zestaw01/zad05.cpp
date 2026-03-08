#include <iostream>
using namespace std;

template<typename T>
class Stack {
public:
    static const size_t N = 100;

    typedef T value_type;

private:
    T rep[N];
    size_t top;

public:
    Stack() : top(0) {}

    void push(T val) { rep[top++] = val; }
    T pop() { return rep[--top]; }
    bool is_empty() const { return (top == 0); }
};

template<typename StackType>
typename StackType::value_type sum_stosu(StackType s) {
    typename StackType::value_type suma = typename StackType::value_type(0);
    while (!s.is_empty()) {
        suma += s.pop();
    }
    return suma;
}

int main() {
   
    Stack<string> st;
    st.push("ania");
    st.push("asia");
    st.push("basia");

    while (!st.is_empty()) {
        cout << st.pop() << endl;
    }

    //sumowanie
    Stack<int> si;
    si.push(10);
    si.push(20);
    si.push(30);
    cout << "Suma int: " << sum_stosu(si) << endl;   // 60

    Stack<double> sd;
    sd.push(1.5);
    sd.push(2.5);
    sd.push(3.0);
    cout << "Suma double: " << sum_stosu(sd) << endl; // 7.0


}