#include <iostream>
#include <algorithm>

template<typename T>
class ArrayStack {
private:
  T* a;
  int n;
  int capacity;

  void resize() {
    int new_capacity = std::max(2* capacity, 1);
    T* b = new T[new_capacity];
    for(int i = 0; i < n ; ++i)
      b[i] = a[i];
    delete [] a;
    a= b;
    capacity = new_capacity;

  }

public:
    ArrayStack(int cap = 1) {
        capacity = std::max(cap, 1); // initialize before use!
        a = new T[capacity];         // now safe
        n = 0;
    }
      // Copy constructor
    ArrayStack(const ArrayStack& other) {
        capacity = other.capacity;
        n = other.n;
        a = new T[capacity];
        for (int i = 0; i < n; ++i)
            a[i] = other.a[i];
    }

    // Copy assignment operator
    ArrayStack& operator=(const ArrayStack& other) {
        if (this != &other) {
            delete[] a;  // clean up old memory
            capacity = other.capacity;
            n = other.n;
            a = new T[capacity];
            for (int i = 0; i < n; ++i)
                a[i] = other.a[i];
        }
        return *this;
    }
  ~ArrayStack() {
    delete [] a;
  }

  int size() const {
    return n;
  }

  T get(int i) const {
    return a[i];
  }

  T set(int i, T x) {
    T old = a[i];
    a[i] = x;
    return old;
  }

  void add(int i , T x) {
    if (n == capacity) resize();
    for ( int j = n; j > i; --j)
      a[j] = a[j -1];
    a[i] = x;
    ++n;
  }

  T remove(int i) {
    T x = a[i];
    for (int j = i; j < n-1; ++j)
      a[j] = a[j + 1];
    --n;
    return x;
  }
	
};


template<typename T>
class DualArrayDeque {
private:
  ArrayStack<T> front, back;

  void balance() {
    if (3* front.size() < back.size() || 3* back.size() < front.size()) {
      int n = this->size();
      int nf = n/2;
      int nb = n - nf;
      
      ArrayStack<T>
        new_front(std::max(2*nf, 1));
      for (int i = 0; i < nf; ++i)
        new_front.add(0, this->get(i));
      
      ArrayStack<T>
        new_back(std::max(2*nb, 1));
      for ( int i = 0; i < nb; ++i)
        new_back.add(i, this->get(nf + i));

      front = new_front;
      back = new_back;
    }
  }

public:
  DualArrayDeque() : front(), back() {}

  int size() const {
    return front.size() + back.size();
  }
 T get(int i) const {
    if ( i < front.size()) {
      return front.get(front.size() - i -1);
    } else {
      return back.get(i - front.size());
    }
  } 

  T set(int i , T x) {
    if (i < front.size()) {
      return front.set(front.size() - i - 1, x);
    } else {
    return back.set(i - front.size(), x);
    }
  }

  void add(int i ,T x) {
    if (i < front.size()) {
      front.add(front.size() - i, x);
    } else {
      back.add(i - front.size(), x);
    }
    balance();
  }
   
  T remove(int i ) {
    T x;
    if (i < front.size()) {
      x = front.remove(front.size() -i -1);
    } else {
      x = back.remove(i - front.size());
    }
    balance();
    return x;
  }

};

int main() {
    DualArrayDeque<int> dq;

    dq.add(0, 10);  // [10]
    dq.add(1, 20);  // [10, 20]
    dq.add(1, 15);  // [10, 15, 20]

    std::cout << "Initial elements:\n";
    for (int i = 0; i < dq.size(); ++i)
        std::cout << dq.get(i) << ' ';
    std::cout << "\n";

    dq.set(1, 16);  // [10, 16, 20]
    std::cout << "After setting index 1 to 16:\n";
    for (int i = 0; i < dq.size(); ++i)
        std::cout << dq.get(i) << ' ';
    std::cout << "\n";

    int removed = dq.remove(0);  // removes 10
    std::cout << "Removed element: " << removed << "\n";

    std::cout << "Final deque state:\n";
    for (int i = 0; i < dq.size(); ++i)
        std::cout << dq.get(i) << ' ';
    std::cout << "\n";

    return 0;
}

