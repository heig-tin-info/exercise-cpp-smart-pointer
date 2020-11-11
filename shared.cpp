#include <iostream>
using namespace std;
  
template <typename T>
class Shared_ptr 
{
    size_t* counter; // Reference counter    
    T* ptr; // Shared pointer

public:
    explicit Shared_ptr(T* ptr = nullptr) {
        this->ptr = ptr;
        counter = new size_t();
        if (ptr) (*counter)++;
    }
 
    // Copy constructor
    Shared_ptr(Shared_ptr<T>& sp) {
        ptr = sp.ptr;
        counter = sp.counter;
        (*counter)++;
    }
 
    size_t use_count() { return counter; }
 
    T* get() { return ptr; }
 
    T& operator*() { return *ptr; }
    T* operator->() { return ptr; }
   
    ~Shared_ptr() {
        (*counter)--;
        if (counter == 0) {
            delete counter;
            delete ptr;
        }
    }
 
    friend ostream& operator<<(ostream& os, Shared_ptr<T>& sp) {
        return os << "P(" << sp.get() << " x " << *sp.counter << ")" << endl;
    }
};
 
int main()
{
    // p pointing to an integer.
    Shared_ptr<int> p(new int(151));
    cout << "# Shared pointer p\n";
    *p = 100;
    cout << "p's value now: " << *p << endl;
    cout << p << endl;
 
    {
        // q pointing to same integer which p is pointing to 
        // Shared pointer reference counter should have increased now to 2.
        Shared_ptr<int> q = p;
        cout << "# Shared pointers p, q\n";
        cout << p << q << endl;

        {
            // r pointing to same integer which p and q are pointing to.
            // Shared pointer reference counter should have increased now to 3.
            Shared_ptr<int> r(q);
            cout << "# Shared pointers p, q, r\n";
            cout << p << q << r << endl;
        }
 
        // r is out of scope. It would have been deleted.
        // So shared pointer reference counter should have decreased now to 2.
        cout << "# Shared pointers p, q\n";
        cout << p << q << endl;
    }
 
    // q is out of scope.
    // It would have been destructed.
    // So shared pointer reference counter
    // should have decreased now to 1.
    cout << "# Shared pointers p\n";
    cout << p << endl;
}
