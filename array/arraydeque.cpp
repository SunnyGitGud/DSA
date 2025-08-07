
#include <iostream>
#include <cassert>
#include <algorithm>

template <typename T>
class Array {
private:
    T* a;
    int length;  // total capacity
    int n;       // current number of elements
    int j;       // start index (head)

    void resize() {
        int old_length = length;
        // double capacity (at least 1)
        length = std::max(1, 2 * old_length);
        T* new_a = new T[length];

        // copy elements in order from old buffer
        for (int i = 0; i < n; ++i) {
            new_a[i] = a[(j + i) % old_length];
        }

        delete[] a;
        a = new_a;
        j = 0;

        std::cout << "Resized from " << old_length
                  << " to " << length << std::endl;
    }

public:
    // ctor
    Array(int len = 1)
      : length(len), n(0), j(0), a(new T[len])
    {
        std::cout << "Created array of size " << length << std::endl;
    }

    // dtor
    ~Array() {
        delete[] a;
        std::cout << "Destroyed array" << std::endl;
    }

    // copy ctor
    Array(const Array<T>& other)
      : length(other.length),
        n(other.n),
        j(0),                // we'll normalize head to 0
        a(new T[other.length])
    {
        // copy in logical order
        for (int i = 0; i < n; ++i) {
            a[i] = other.get(i);
        }
        std::cout << "Copied array" << std::endl;
    }

    // copy assign
    Array<T>& operator=(const Array<T>& other) {
        if (this != &other) {
            delete[] a;
            length = other.length;
            n      = other.n;
            j      = 0;
            a      = new T[length];
            for (int i = 0; i < n; ++i) {
                a[i] = other.get(i);
            }
            std::cout << "Copy assigned array" << std::endl;
        }
        return *this;
    }

    // move assign
    Array<T>& operator=(Array<T>&& other) noexcept {
        if (this != &other) {
            delete[] a;
            a       = other.a;
            length  = other.length;
            n       = other.n;
            j       = other.j;

            other.a      = nullptr;
            other.length = 0;
            other.n      = 0;
            other.j      = 0;

            std::cout << "Moved array ownership" << std::endl;
        }
        return *this;
    }

    // size & capacity
    int size() const     { return n;        }
    int capacity() const { return length;   }
    bool empty() const   { return n == 0;   }

    // random-access
    T& operator[](int i) {
        assert(i >= 0 && i < n);
        return a[(j + i) % length];
    }
    const T& operator[](int i) const {
        assert(i >= 0 && i < n);
        return a[(j + i) % length];
    }

    // get/set
    T get(int i) const {
        assert(i >= 0 && i < n);
        return a[(j + i) % length];
    }
    T set(int i, T x) {
        assert(i >= 0 && i < n);
        int idx = (j + i) % length;
        T old = a[idx];
        a[idx] = x;
        return old;
    }

    // insert at index i
    void add(int i, T x) {
        assert(i >= 0 && i <= n);
        if (n == length) resize();

        // choose the shorter shift
        if (i < n/2) {
            // shift frontward: increment j backwards
            j = (j == 0 ? length-1 : j-1);
            for (int k = 0; k < i; ++k) {
                a[(j + k) % length] = a[(j + k + 1) % length];
            }
        } else {
            // shift backward: move tail forward
            for (int k = n; k > i; --k) {
                a[(j + k) % length] = a[(j + k - 1) % length];
            }
        }

        a[(j + i) % length] = x;
        ++n;
    }

    // remove at index i
    T remove(int i) {
        assert(i >= 0 && i < n);
        int idx = (j + i) % length;
        T val = a[idx];

        if (i < n/2) {
            // shift the prefix right
            for (int k = i; k > 0; --k) {
                a[(j + k) % length]
                  = a[(j + k - 1) % length];
            }
            j = (j + 1) % length;
        } else {
            // shift the suffix left
            for (int k = i; k < n-1; ++k) {
                a[(j + k) % length]
                  = a[(j + k + 1) % length];
            }
        }

        --n;
        return val;
    }

    // queue‐style helpers
    void push_back(T x) { add(n, x);          }
    T pop_front()       { return remove(0);   }

    // debug print
    void print() const {
        std::cout << "[";
        for (int i = 0; i < n; ++i) {
            std::cout << get(i)
                      << (i+1<n ? ", " : "");
        }
        std::cout << "]\n";
    }
};

int main() {
    std::cout << "--- Initial Push ---\n";
    Array<int> arr(2); // Small initial size to trigger resizing
    arr.push_back(10);
    arr.push_back(20);
    arr.push_back(30); // Triggers resize
    arr.print();       // [10, 20, 30]

    std::cout << "\n--- Insert at index 1 ---\n";
    arr.add(1, 15);
    arr.print();       // [10, 15, 20, 30]

    std::cout << "\n--- Remove at index 2 ---\n";
    int removed = arr.remove(2); // Removes 20
    std::cout << "Removed: " << removed << '\n';
    arr.print();       // [10, 15, 30]

    std::cout << "\n--- Pop front ---\n";
    int popped = arr.pop_front(); // Removes 10
    std::cout << "Popped front: " << popped << '\n';
    arr.print();       // [15, 30]

    std::cout << "\n--- Get/Set ---\n";
    std::cout << "get(1): " << arr.get(1) << '\n'; // 30
    int old = arr.set(1, 99);
    std::cout << "set(1, 99), old value: " << old << '\n';
    arr.print();       // [15, 99]

    std::cout << "\n--- Access with operator[] ---\n";
    for (int i = 0; i < arr.size(); ++i) {
        std::cout << "arr[" << i << "] = " << arr[i] << '\n';
    }

    std::cout << "\n--- Force wraparound and resize ---\n";
    for (int i = 0; i < 10; ++i) {
        arr.push_back(100 + i);
    }
    arr.print();

    std::cout << "\n--- Remove all elements ---\n";
    while (!arr.empty()) {
        std::cout << "Pop: " << arr.pop_front() << '\n';
        arr.print();
    }

    std::cout << "\n--- Copy Constructor ---\n";
    arr.push_back(42);
    arr.push_back(43);
    Array<int> copy = arr; // Copy constructor
    copy.print();          // [42, 43]

    std::cout << "\n--- Copy Assignment ---\n";
    Array<int> assign(1);
    assign = arr;          // Copy assignment
    assign.print();        // [42, 43]

    std::cout << "\n--- Move Assignment ---\n";
    Array<int> moved = std::move(assign); // Move assignment
    moved.print();        // [42, 43]
    std::cout << "assign.size(): " << assign.size() << '\n'; // Should be 0

    std::cout << "\n--- Done ---\n";
    return 0;
}

