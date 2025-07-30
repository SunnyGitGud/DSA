#include <iostream>
#include <vector>
#include <initializer_list>
#include <chrono>

template<typename T>
class ArrayStack {
private:
    T* a;           // backing array
    int n;          // number of elements
    int capacity;   // current capacity of array
    
    void resize() {
        // TODO: Implement resize operation
        // Hint: typically double the capacity when growing
        
    }

public:
    ArrayStack() : n(0), capacity(1) {
        a = new T[capacity];
    }
    
    ~ArrayStack() {
        delete[] a;
    }
    
    // Basic operations (you may need these for testing)
    void add(int i, T x) {
        // TODO: Implement single element insertion
        // This is the inefficient method we want to avoid using repeatedly
        
    }
    
    T get(int i) {
        if (i < 0 || i >= n) throw std::out_of_range("Index out of bounds");
        return a[i];
    }
    
    int size() const {
        return n;
    }
    
    void print() {
        std::cout << "[";
        for (int i = 0; i < n; i++) {
            std::cout << a[i];
            if (i < n-1) std::cout << ", ";
        }
        std::cout << "]" << std::endl;
    }
    
    // EXERCISE 2.1: Implement these two methods
    
    // Method 1: Inefficient implementation using repeated add() calls
    template<typename Container>
    void addAll_inefficient(int i, const Container& c) {
        // TODO: Implement using repeated calls to add(i, x)
        // This should demonstrate why this approach is slow
        
    }
    
    // Method 2: Efficient implementation 
    template<typename Container>
    void addAll_efficient(int i, const Container& c) {
        // TODO: Implement efficient version
        // Steps:
        // 1. Calculate how many elements to insert (k = c.size())
        // 2. Check if resize is needed (if n + k > capacity)
        // 3. Perform single shift operation to make space
        // 4. Copy all elements from container c at once
        // 5. Update n
        
    }
};

// Helper function to create test data
std::vector<int> createTestData(int size) {
    std::vector<int> data;
    for (int i = 0; i < size; i++) {
        data.push_back(i * 10);
    }
    return data;
}

// Performance testing function
template<typename T>
void performanceTest() {
    std::cout << "\n=== Performance Test ===" << std::endl;
    
    // Test with different sizes
    std::vector<int> sizes = {100, 500, 1000, 2000};
    
    for (int size : sizes) {
        ArrayStack<int> stack1, stack2;
        
        // Pre-populate with some data
        for (int i = 0; i < size/2; i++) {
            stack1.add(i, i);
            stack2.add(i, i);
        }
        
        auto testData = createTestData(size/4);
        int insertPos = size/4; // Insert in middle
        
        // Test inefficient method
        auto start = std::chrono::high_resolution_clock::now();
        stack1.addAll_inefficient(insertPos, testData);
        auto end = std::chrono::high_resolution_clock::now();
        auto inefficient_time = std::chrono::duration_cast<std::chrono::microseconds>(end - start);
        
        // Test efficient method
        start = std::chrono::high_resolution_clock::now();
        stack2.addAll_efficient(insertPos, testData);
        end = std::chrono::high_resolution_clock::now();
        auto efficient_time = std::chrono::duration_cast<std::chrono::microseconds>(end - start);
        
        std::cout << "Size: " << size 
                  << ", Inefficient: " << inefficient_time.count() << "μs"
                  << ", Efficient: " << efficient_time.count() << "μs"
                  << ", Speedup: " << (double)inefficient_time.count() / efficient_time.count() << "x"
                  << std::endl;
    }
}

int main() {
    std::cout << "=== Exercise 2.1: Efficient addAll Implementation ===" << std::endl;
    
    // Basic functionality test
    ArrayStack<int> stack;
    
    // Add some initial elements
    for (int i = 0; i < 5; i++) {
        stack.add(i, i * 2);
    }
    
    std::cout << "Initial stack: ";
    stack.print();
    
    // Test data to insert
    std::vector<int> testData = {100, 200, 300};
    
    // Test inefficient method
    std::cout << "\nTesting inefficient addAll at position 2:" << std::endl;
    ArrayStack<int> stack1 = stack; // Copy for testing
    stack1.addAll_inefficient(2, testData);
    std::cout << "Result: ";
    stack1.print();
    
    // Test efficient method
    std::cout << "\nTesting efficient addAll at position 2:" << std::endl;
    ArrayStack<int> stack2 = stack; // Copy for testing
    stack2.addAll_efficient(2, testData);
    std::cout << "Result: ";
    stack2.print();
    
    // Performance comparison
    performanceTest<int>();
    
    return 0;
}

/*
TODO: Complete the following methods:

1. resize() - Double the capacity and copy elements
2. add(int i, T x) - Insert single element at position i
3. addAll_inefficient() - Use repeated add() calls
4. addAll_efficient() - Use single shift + bulk copy

Key points to remember:
- Handle edge cases (i out of bounds, empty container)
- Ensure proper memory management
- The efficient version should be O(n + k) vs O(k * n) for inefficient
- Test with different insertion positions and container sizes

Expected time complexities:
- addAll_inefficient: O(k * (n - i)) where k = container size
- addAll_efficient: O((n - i) + k) = O(n + k)
*/
