#include <iostream>
using namespace std;
 
class Counter {
    size_t m_counter{};    
public:
    Counter() : m_counter(0){};
 
    Counter(const Counter&) = delete;
    Counter& operator=(const Counter&) = delete;
 
    ~Counter() {}
 
    void reset() { m_counter = 0; }
    size_t get() { return m_counter; }

    // Prefix
    void operator++() { ++m_counter; }
    void operator--() { --m_counter; } 
    // Postfix
    void operator++(int) { m_counter++; }
    void operator--(int) { m_counter--; }

    friend ostream& operator<<(ostream& os, const Counter& counter)
    {
        return os << "Counter Value : " << counter.m_counter << endl;
    }
};
 
template <typename T>
class Shared_ptr 
{
    Counter* counter; // Reference counter    
    T* ptr; // Shared pointer

public:
    explicit Shared_ptr(T* ptr = nullptr) {
        this->ptr = ptr;
        counter = new Counter();
        if (ptr) (*counter)++;
    }
 
    // Copy constructor
    Shared_ptr(Shared_ptr<T>& sp) {
        ptr = sp.ptr;
        counter = sp.counter;
        (*counter)++;
    }
 
    size_t use_count() { return counter->get(); }
 
    T* get() { return ptr; }
 
    T& operator*() { return *ptr; }
    T* operator->() { return ptr; }
   
    ~Shared_ptr() {
        (*counter)--;
        if (counter->get() == 0) {
            delete counter;
            delete ptr;
        }
    }
 
    friend ostream& operator<<(ostream& os, Shared_ptr<T>& sp) {
        os << "Address pointed : " << sp.get() << endl;
        return os << *(sp.counter) << endl;
    }
};
 
int main()
{
    // p pointing to an integer.
    Shared_ptr<int> p(new int(151));
    cout << "# Shared pointer p\n";
    *p = 100;
    cout << "p's value now: " << *p << endl;
    cout << p;
 
    {
        // q pointing to same integer which p is pointing to 
        // Shared pointer reference counter should have increased now to 2.
        Shared_ptr<int> q = p;
        cout << "# Shared pointers p, q\n";
        cout << p << q;

        {
            // r pointing to same integer which p and q are pointing to.
            // Shared pointer reference counter should have increased now to 3.
            Shared_ptr<int> r(q);
            cout << "# Shared pointers p, q, r\n";
            cout << p << q << r;
        }
 
        // r is out of scope. It would have been deleted.
        // So shared pointer reference counter should have decreased now to 2.
        cout << "# Shared pointers p, q\n";
        cout << p << q;
    }
 
    // q is out of scope.
    // It would have been destructed.
    // So shared pointer reference counter
    // should have decreased now to 1.
    cout << "# Shared pointers p\n";
    cout << p << endl;
}
