#include <math.h>
#include <vector>
#include <cmath>
#include <stdexcept>
#include <iostream>

template <class T>
class RootishArray {
private:
  std::vector<T*> blocks;
  int n;

  int i2b(int i) const {
    double db = (-3.0 + sqrt(9+8*i)) / 2.0;
    return (int)ceil(db);
  }

  void grow() {
    int new_size = blocks.size() + 1;
    blocks.push_back(new T[new_size]);
  }

  void shrink() {
    int r = blocks.size();
    while (r > 0 && (r - 2)*(r - 1)/2 >= n) {
      delete [] blocks[r-1];
      blocks.pop_back();
      r--;
    }
  }
  
public:
  RootishArray() : n(0) {}

  ~RootishArray() {
    clear();
  }

  void clear() {
    for (T* block : blocks) {
      delete [] block;
    }
    blocks.clear();
    n=0;
  }

  int size() const {
    return n;
  }

  bool empty() const {
    return n == 0;
  }
  
  T get(int i) const {
    if (i < 0 || i >= n) {
      throw std::out_of_range("Index out of bounds");
    }
    int b = i2b(i);
    int j = i - b * (b + 1) / 2;
    return blocks[b][j];
  }

  T set(int i , T x) { 
    if (i < 0 || i >= n) {
      throw std::out_of_range("Index out of bounds");
    }
    int b = i2b(i);
    int j = i - b * (b + 1) / 2;
    T oldval = blocks[b][j];
    blocks[b][j] = x;
    return oldval;
  }

  void add(int i, T x) {
    if (i < 0 || i > n) {
      throw std::out_of_range("Index out of bounds"); 
  }
    int r = blocks.size();
    if (r * (r + 1)/ 2 < n + 1) {
      grow();
    }

    n++;
    for(int j = n - 1; j > i ; j--) {
      set(j, get(j -1));
    }
    set(i, x);
  }

  T remove(int i) {
    if (i < 0 || i >= n) {
      throw std::out_of_range("Index out of bounds");
    } 

    T x = get(i);
    for(int j = i; j < n-1; j++) {
      set(j, get(j + 1));
    }
    n--;
    
    int r = blocks.size();
    if ((r-2) * (r-1)/2 >= n) {
      shrink();
    }
    return x;
  }

  void push_back( T x) {
    add(n, x);
  }




  T pop_back() {
    if (empty()) {
      throw std::runtime_error("Cannot pop from empty stack");
    }
    return remove(n- 1);
  }
  
   // Debug function to visualize structure
    void printStructure() const {
        std::cout << "RootishArrayStack with " << n << " elements:\n";
        int element_idx = 0;
        
        for (int b = 0; b < blocks.size(); b++) {
            std::cout << "Block " << b << " (capacity " << (b+1) << "): [";
            
            for (int j = 0; j < b + 1; j++) {
                if (element_idx < n) {
                    std::cout << blocks[b][j];
                    element_idx++;
                } else {
                    std::cout << "_";
                }
                if (j < b) std::cout << ", ";
            }
            std::cout << "]\n";
            
            if (element_idx >= n) break;
        }
        
        // Calculate waste
        int r = blocks.size();
        int total_capacity = r * (r + 1) / 2;
        std::cout << "Space usage: " << n << "/" << total_capacity 
                  << " (" << (100.0 * n / total_capacity) << "% efficient)\n\n";
    }
};

// Example usage and testing
int main() {
    RootishArray<int> stack;
    
    // Add some elements
    for (int i = 0; i < 10; i++) {
        stack.push_back(i * 10);
    }
    
    stack.printStructure();
    
    // Test access
    std::cout << "Element at index 7: " << stack.get(7) << std::endl;
    
    // Test insertion
    stack.add(3, 999);
    std::cout << "\nAfter inserting 999 at index 3:\n";
    stack.printStructure();
    
    // Test removal
    int removed = stack.remove(5);
    std::cout << "Removed element: " << removed << std::endl;
    stack.printStructure();
    
    return 0;
}
