
#include <iostream>
#include <cassert>
#include <ostream>
#include <algorithm>






template <typename T>
class Array {
private:
    T* a;
    int length; // Total capacity of the array
    int n; // current number of elements in use
      
    void resize() {
        Array<T> b(std::max(1, 2 * n));
        std::copy(a, a + n, b.a);
		b.n = n;
        *this = std::move(b);
    }

public:
    Array(int len) : length(len), n(0) {
        a = new T[length];
        std::cout << "Created array of size " << length << std::endl;
    }
    
    ~Array() {
        if (a != nullptr) {
            delete[] a;
            std::cout << "Destroyed array" << std::endl;
        }
    }
    
    // Copy constructor
    Array(const Array<T>& other) : length(other.length), n(other.n) {
        a = new T[length];
        std::copy(other.a, other.a + n, a);
        std::cout << "Copied array" << std::endl;
    }
    
    // Copy assignment operator
    Array<T>& operator=(const Array<T>& other) {
        if (this == &other) {
            return *this;
        }
        
        delete[] a;
        length = other.length;
        n = other.n;
        a = new T[length];
        std::copy(other.a, other.a + n, a);
        std::cout << "Copy assigned array" << std::endl;
        return *this;
    }
    
    // Move assignment operator (fixed signature)
    Array<T>& operator=(Array<T>&& other) noexcept {
        if (this == &other) {
            return *this;
        }
        
        if (a != nullptr) {
            delete[] a;
        }
        
        a = other.a;
        other.a = nullptr;
        length = other.length;
        other.length = 0;
        n = other.n;
        other.n = 0;
        
        std::cout << "Moved array ownership" << std::endl;
        return *this;
    }
    
    T& operator[](int i) {
        assert(i >= 0 && i < n); // Should check against n, not length
        return a[i];
    }
    
    const T& operator[](int i) const {
        assert(i >= 0 && i < n); // Should check against n, not length
        return a[i];
    }
    
    int size() const {
        return n; // Return number of elements in use, not capacity
    }
    
    int capacity() const {
        return length;
    }
    
    T get(int i) const {
        assert(i >= 0 && i < n);
        return a[i];
    }
    
    T set(int i, T x) {
        assert(i >= 0 && i < n);
        T y = a[i];
        a[i] = x;
        return y;
    }
    
    T remove(int i) {
        assert(i >= 0 && i < n);
        T x = a[i];
        std::copy(a + i + 1, a + n, a + i);
        n--;
        return x;
    }
    
    void add(int i, T x) {
        assert(i >= 0 && i <= n); // Can insert at position n (end)
        if (n + 1 > length) {
            resize();
        }
        std::copy_backward(a + i, a + n, a + n + 1);
        a[i] = x;
        n++;
    }
    
    void push_back(T x) {
        add(n, x);
    }
};




int main() {
    std::cout << "--- Creating array ---\n";
    Array<int> arr(2);

    std::cout << "--- Adding elements ---\n";
    arr.push_back(10);  // [10]
    arr.push_back(20);  // [10, 20]
    arr.push_back(30);  // [10, 20, 30] → triggers resize

    std::cout << "Array contents:\n";
    for (int i = 0; i < arr.size(); ++i) {
        std::cout << arr[i] << " ";
    }
    std::cout << "\nSize: " << arr.size() << ", Capacity: " << arr.capacity() << "\n\n";

    std::cout << "--- Inserting at index 1 ---\n";
    arr.add(1, 15);  // [10, 15, 20, 30]
    for (int i = 0; i < arr.size(); ++i)
        std::cout << arr[i] << " ";
    std::cout << "\n\n";

    std::cout << "--- Setting index 2 to 25 ---\n";
    arr.set(2, 25);  // [10, 15, 25, 30]
    for (int i = 0; i < arr.size(); ++i)
        std::cout << arr[i] << " ";
    std::cout << "\n\n";

    std::cout << "--- Removing index 0 ---\n";
    arr.remove(0);   // [15, 25, 30]
    for (int i = 0; i < arr.size(); ++i)
        std::cout << arr[i] << " ";
    std::cout << "\n\n";

    std::cout << "--- Testing copy constructor ---\n";
    Array<int> copiedArr = arr;
    for (int i = 0; i < copiedArr.size(); ++i)
        std::cout << copiedArr[i] << " ";
    std::cout << "\n\n";

    std::cout << "--- Testing move assignment ---\n";
    Array<int> movedArr(1);
    movedArr = std::move(copiedArr);
    for (int i = 0; i < movedArr.size(); ++i)
        std::cout << movedArr[i] << " ";
    std::cout << "\n";

    std::cout << "--- All tests completed ---\n";
    return 0;
}

