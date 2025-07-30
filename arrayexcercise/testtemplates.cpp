#include <iostream>
#include <vector>
#include <algorithm>
#include <chrono>
#include <cmath>
#include <functional>
#include <cassert>
#include <random>
#include <iomanip>
/*
=============================================================================
CHAPTER 2.7 - ARRAY-BASED DATA STRUCTURES EXERCISES
=============================================================================
*/

// =============================================================================
// Exercise 2.1 - How can we optimize bulk insertion operations?
// Problem: addAll method using repeated add() calls is inefficient
// =============================================================================

template<typename T>
class ArrayStack {
private:
    T* a;           // backing array
    int n;          // number of elements
    int capacity;   // current capacity of array
    
    void resize() {
        // TODO: Implement resize operation
        // Hint: typically double the capacity when growing
        int new_capacity = std::max(1, capacity * 2);
        T* new_array = new T[new_capacity];
        
        for (int i = 0; i < n; i++) {
            new_array[i] = a[i];
        }
        
        delete[] a;
        a = new_array;
        capacity = new_capacity;
    }

public:
    ArrayStack() : n(0), capacity(1) {
        a = new T[capacity];
    }
    
    ~ArrayStack() {
        delete[] a;
    }
    
    // Copy constructor for testing
    ArrayStack(const ArrayStack& other) : n(other.n), capacity(other.capacity) {
        a = new T[capacity];
        for (int i = 0; i < n; i++) {
            a[i] = other.a[i];
        }
    }
    
    // Basic operations
    void add(int i, T x) {
        // TODO: Implement single element insertion
        if (i < 0 || i > n) throw std::out_of_range("Index out of bounds");
        if (n >= capacity) resize();
        
        // Shift elements to the right
        for (int j = n; j > i; j--) {
            a[j] = a[j-1];
        }
        
        a[i] = x;
        n++;
    }
    
    T get(int i) const {
        if (i < 0 || i >= n) throw std::out_of_range("Index out of bounds");
        return a[i];
    }
    
    int size() const {
        return n;
    }
    
    void print() const {
        std::cout << "[";
        for (int i = 0; i < n; i++) {
            std::cout << a[i];
            if (i < n-1) std::cout << ", ";
        }
        std::cout << "]" << std::endl;
    }
    
    // Exercise 2.1: Implement these two methods
    
    // Method 1: Inefficient implementation using repeated add() calls
    template<typename Container>
    void addAll_inefficient(int i, const Container& c) {
        // TODO: Implement using repeated calls to add(i, x)
        // This should demonstrate why this approach is slow
        int pos = i;
        for (const auto& element : c) {
            add(pos, element);
            pos++;
        }
    }
    
    // Method 2: Efficient implementation 
    template<typename Container>
    void addAll_efficient(int i, const Container& c) {
        // TODO: Implement efficient version
        // Steps:
        // 1. Calculate how many elements to insert (k = c.size())
        if (i < 0 || i > n) throw std::out_of_range("Index out of bounds");
        
        int k = c.size();
        if (k == 0) return;
        
        // 2. Check if resize is needed (if n + k > capacity)
        while (n + k > capacity) {
            resize();
        }
        
        // 3. Perform single shift operation to make space
        for (int j = n - 1; j >= i; j--) {
            a[j + k] = a[j];
        }
        
        // 4. Copy all elements from container c at once
        int pos = i;
        for (const auto& element : c) {
            a[pos] = element;
            pos++;
        }
        
        // 5. Update n
        n += k;
    }
};

// Helper function to create test data for Exercise 2.1
std::vector<int> createTestData(int size) {
    std::vector<int> data;
    for (int i = 0; i < size; i++) {
        data.push_back(i * 10);
    }
    return data;
}

// =============================================================================
// Exercise 2.2 - How can we implement memory-efficient array operations?
// Problem: ArrayStack wastes memory after remove() operations
// =============================================================================

template<typename T>
class MemoryEfficientArrayStack {
private:
    T* a;
    int n;
    int capacity;
    
    void resize() {
        // TODO: Implement smart resizing
        // Hint: Consider shrinking when array is 1/4 full
        
    }

public:
    MemoryEfficientArrayStack() : n(0), capacity(1) {
        a = new T[capacity];
    }
    ~MemoryEfficientArrayStack() {
        delete[] a;
    T remove(int i) {
        // TODO: Implement remove with proper memory management
        // Key issue: After shifting elements, set the last position to null
        // This prevents memory leaks in garbage-collected languages
        
    }
    
    void add(int i, T x) {
        // TODO: Implement add operation
        
    }
    
    T get(int i) const {
        if (i < 0 || i >= n) throw std::out_of_range("Index out of bounds");
        return a[i];
    }
    int getCapacity() const { return capacity; }
    
    int size() const { return n; }
    double memoryUtilization() const {
        return capacity > 0 ? (double)n / capacity : 0.0;
    }
};

// =============================================================================
// Exercise 2.3 - Can we implement a stack that grows in both directions?
// Problem: Design a deque-like structure using a single array
// =============================================================================

template<typename T>
class BidirectionalArrayStack {
private:
    T* a;
    int capacity;
    int front;  // index of first element
    int back;   // index after last element
    
    void resize() {
        // TODO: Implement resize for bidirectional growth
        // Hint: Copy elements to center of new array
        
    }

public:
    BidirectionalArrayStack() : capacity(1), front(0), back(0) {
        a = new T[capacity];
    }
    
    ~BidirectionalArrayStack() {
        delete[] a;
    }
    
    // Exercise 2.3: Implement bidirectional operations
    void pushFront(T x) {
        // TODO: Add element to front of array
        
    }
    
    void pushBack(T x) {
        // TODO: Add element to back of array
        
    }
    
    T popFront() {
        // TODO: Remove and return front element
        
    }
    
    T popBack() {
        // TODO: Remove and return back element
        
    }
    
    bool empty() const {
        return front == back;
    }
    
    int size() const {
        return back - front;
    }
};

// =============================================================================
// Exercise 2.4 - How can we minimize space overhead in array-based lists?
// Problem: Implement RootishArrayStack space analysis
// =============================================================================

class RootishArrayStack {
private:
    std::vector<std::vector<int>*> blocks;
    int n;  // number of elements
    
    int i2b(int i) const {
        // TODO: Implement index-to-block conversion
        // Formula: block containing element i is approximately sqrt(2*i)
        
    }
    
    void grow() {
        // TODO: Add a new block of appropriate size
        // Block r should have size r+1
        
    }
    
    void shrink() {
        // TODO: Remove empty blocks from the end
        
    }

public:
    RootishArrayStack() : n(0) {}
    
    ~RootishArrayStack() {
        for (auto block : blocks) {
            delete block;
        }
    }
    
    // Exercise 2.4: Implement space-efficient operations
    int get(int i) {
        // TODO: Find correct block and index within block
        
    }
    
    void set(int i, int x) {
        // TODO: Set value at position i
        
    }
    
    void add(int i, int x) {
        // TODO: Insert element and manage blocks
        
    }
    
    int remove(int i) {
        // TODO: Remove element and shrink if necessary
        
    }
    
    // Analysis methods
    int totalCapacity() const {
        int total = 0;
        for (const auto* block : blocks) {
            total += block->capacity();
        }
        return total;
    }
    
    double spaceEfficiency() const {
        int total_capacity = totalCapacity();
        return total_capacity > 0 ? (double)n / total_capacity : 0.0;
    }
};

// =============================================================================
// Exercise 2.5 - What happens when array operations are applied to null arrays?
// Problem: Implement robust error handling
// =============================================================================

template<typename T>
class RobustArrayStack {
private:
    T* a;
    int n;
    int capacity;
    
public:
    RobustArrayStack() : a(nullptr), n(0), capacity(0) {}
    
    // Exercise 2.5: Add comprehensive error checking
    void add(int i, T x) {
        // TODO: Handle null array, invalid indices, etc.
        // Consider: What if i < 0? What if i > n? What if array is null?
        
    }
    
    T remove(int i) {
        // TODO: Safe removal with error checking
        
    }
    
    T get(int i) const {
        // TODO: Safe access with bounds checking
        
    }
    
    // Utility methods for testing edge cases
    bool isValid() const {
        return a != nullptr && capacity >= n && n >= 0;
    }
};

// =============================================================================
// Exercise 2.6 - How do different resizing strategies affect performance?
// Problem: Compare various array resizing policies
// =============================================================================

enum class ResizePolicy {
    DOUBLE,           // Traditional: multiply by 2
    GOLDEN_RATIO,     // Multiply by golden ratio ≈ 1.618
    ADDITIVE,         // Add fixed amount
    CUSTOM
};

template<typename T>
class ConfigurableArrayStack {
private:
    T* a;
    int n;
    int capacity;
    ResizePolicy policy;
    double growth_factor;
    
    void resize() {
        int new_capacity;
        switch (policy) {
            case ResizePolicy::DOUBLE:
                // TODO: Implement doubling strategy
                break;
            case ResizePolicy::GOLDEN_RATIO:
                // TODO: Implement golden ratio strategy
                break;
            case ResizePolicy::ADDITIVE:
                // TODO: Implement additive strategy
                break;
            case ResizePolicy::CUSTOM:
                // TODO: Use custom growth factor
                break;
        }
        
        // TODO: Allocate new array and copy elements
    }

public:
    ConfigurableArrayStack(ResizePolicy p = ResizePolicy::DOUBLE, double factor = 2.0) 
        : n(0), capacity(1), policy(p), growth_factor(factor) {
        a = new T[capacity];
    }
    
    // Exercise 2.6: Implement operations that use the configurable resize
    void add(int i, T x) {
        // TODO: Implement with configurable resizing
        
    }
    
    // Performance metrics
    struct PerformanceMetrics {
        int resize_count;
        int total_memory_allocated;
        double average_utilization;
    };
    
    PerformanceMetrics getMetrics() const {
        // TODO: Return performance statistics
        return {};
    }
};





// =============================================================================
// COMPREHENSIVE TEST SUITE
// =============================================================================

class TestFramework {
private:
    int tests_passed = 0;
    int tests_failed = 0;
    
public:
    void assert_equal(int expected, int actual, const std::string& test_name) {
        if (expected == actual) {
            std::cout << "✓ " << test_name << " PASSED" << std::endl;
            tests_passed++;
        } else {
            std::cout << "✗ " << test_name << " FAILED: expected " << expected 
                      << ", got " << actual << std::endl;
            tests_failed++;
        }
    }
    
    void assert_true(bool condition, const std::string& test_name) {
        if (condition) {
            std::cout << "✓ " << test_name << " PASSED" << std::endl;
            tests_passed++;
        } else {
            std::cout << "✗ " << test_name << " FAILED" << std::endl;
            tests_failed++;
        }
    }
    
    void assert_throws(std::function<void()> func, const std::string& test_name) {
        try {
            func();
            std::cout << "✗ " << test_name << " FAILED: expected exception" << std::endl;
            tests_failed++;
        } catch (...) {
            std::cout << "✓ " << test_name << " PASSED" << std::endl;
            tests_passed++;
        }
    }
    
    void print_summary() {
        std::cout << "\n=== Test Summary ===" << std::endl;
        std::cout << "Passed: " << tests_passed << std::endl;
        std::cout << "Failed: " << tests_failed << std::endl;
        std::cout << "Total:  " << (tests_passed + tests_failed) << std::endl;
    }
};

// =============================================================================
// Exercise 2.1 Tests - Bulk Insertion Optimization
// =============================================================================

void testExercise2_1() {
    std::cout << "\n=== Exercise 2.1: Bulk Insertion Optimization Tests ===" << std::endl;
    TestFramework tf;
    
    // Test 1: Basic functionality test
    {
        ArrayStack<int> stack;
        for (int i = 0; i < 5; i++) {
            stack.add(i, i * 2);
        }
        
        std::vector<int> testData = {100, 200, 300};
        
        // Test inefficient method
        ArrayStack<int> stack1 = stack;
        stack1.addAll_inefficient(2, testData);
        
        tf.assert_equal(8, stack1.size(), "Inefficient addAll - correct size");
        tf.assert_equal(0, stack1.get(0), "Inefficient addAll - element 0");
        tf.assert_equal(2, stack1.get(1), "Inefficient addAll - element 1");
        tf.assert_equal(100, stack1.get(2), "Inefficient addAll - inserted element 0");
        tf.assert_equal(200, stack1.get(3), "Inefficient addAll - inserted element 1");
        tf.assert_equal(300, stack1.get(4), "Inefficient addAll - inserted element 2");
        tf.assert_equal(4, stack1.get(5), "Inefficient addAll - shifted element");
        
        // Test efficient method
        ArrayStack<int> stack2 = stack;
        stack2.addAll_efficient(2, testData);
        
        tf.assert_equal(8, stack2.size(), "Efficient addAll - correct size");
        tf.assert_equal(0, stack2.get(0), "Efficient addAll - element 0");
        tf.assert_equal(2, stack2.get(1), "Efficient addAll - element 1");
        tf.assert_equal(100, stack2.get(2), "Efficient addAll - inserted element 0");
        tf.assert_equal(200, stack2.get(3), "Efficient addAll - inserted element 1");
        tf.assert_equal(300, stack2.get(4), "Efficient addAll - inserted element 2");
        tf.assert_equal(4, stack2.get(5), "Efficient addAll - shifted element");
    }
    
    // Test 2: Edge cases
    {
        ArrayStack<int> stack;
        std::vector<int> empty_data;
        
        // Insert empty collection
        stack.addAll_efficient(0, empty_data);
        tf.assert_equal(0, stack.size(), "Empty collection insertion");
        
        // Insert at beginning
        std::vector<int> front_data = {1, 2, 3};
        stack.addAll_efficient(0, front_data);
        tf.assert_equal(3, stack.size(), "Insert at beginning - size");
        tf.assert_equal(1, stack.get(0), "Insert at beginning - first element");
        
        // Insert at end
        std::vector<int> end_data = {4, 5};
        stack.addAll_efficient(stack.size(), end_data);
        tf.assert_equal(5, stack.size(), "Insert at end - size");
        tf.assert_equal(5, stack.get(4), "Insert at end - last element");
    }
    
    // Test 3: Performance comparison
    {
        std::cout << "\nPerformance Comparison:" << std::endl;
        std::vector<int> sizes = {100, 500, 1000};
        
        for (int size : sizes) {
            ArrayStack<int> s1, s2;
            
            // Pre-populate
            for (int i = 0; i < size/2; i++) {
                s1.add(i, i);
                s2.add(i, i);
            }
            
            std::vector<int> testData(size/4);
            std::iota(testData.begin(), testData.end(), 1000);
            
            // Time inefficient method
            auto start = std::chrono::high_resolution_clock::now();
            s1.addAll_inefficient(size/4, testData);
            auto end = std::chrono::high_resolution_clock::now();
            auto inefficient_time = std::chrono::duration_cast<std::chrono::microseconds>(end - start);
            
            // Time efficient method
            start = std::chrono::high_resolution_clock::now();
            s2.addAll_efficient(size/4, testData);
            end = std::chrono::high_resolution_clock::now();
            auto efficient_time = std::chrono::duration_cast<std::chrono::microseconds>(end - start);
            
            std::cout << "Size " << size << ": Inefficient=" << inefficient_time.count() 
                      << "μs, Efficient=" << efficient_time.count() << "μs";
            if (efficient_time.count() > 0) {
                double speedup = (double)inefficient_time.count() / efficient_time.count();
                std::cout << ", Speedup=" << std::fixed << std::setprecision(2) << speedup << "x";
            }
            std::cout << std::endl;
        }
    }
    
    // Test 4: Error handling
    {
        ArrayStack<int> stack;
        std::vector<int> data = {1, 2, 3};
        
        tf.assert_throws([&]() { stack.addAll_efficient(-1, data); }, 
                        "Negative index throws exception");
        tf.assert_throws([&]() { stack.addAll_efficient(1, data); }, 
                        "Index beyond size throws exception");
    }
}

// =============================================================================
// Exercise 2.2 Tests - Memory-Efficient Operations
// =============================================================================

void testExercise2_2() {
    std::cout << "\n=== Exercise 2.2: Memory-Efficient Operations Tests ===" << std::endl;
    TestFramework tf;
    
    // Test 1: Basic remove functionality
    {
        MemoryEfficientArrayStack<int> stack;
        
        // Add elements
        for (int i = 0; i < 10; i++) {
            stack.add(i, i * 10);
        }
        
        tf.assert_equal(10, stack.size(), "Initial size after adds");
        
        // Remove from middle
        int removed = stack.remove(5);
        tf.assert_equal(50, removed, "Removed correct element");
        tf.assert_equal(9, stack.size(), "Size after remove");
        tf.assert_equal(60, stack.get(5), "Elements shifted correctly");
    }
    
    // Test 2: Memory utilization tracking
    {
        MemoryEfficientArrayStack<int> stack;
        
        // Fill up the stack
        for (int i = 0; i < 100; i++) {
            stack.add(i, i);
        }
        
        double initial_util = stack.memoryUtilization();
        std::cout << "Initial utilization: " << std::fixed << std::setprecision(2) 
                  << initial_util * 100 << "%" << std::endl;
        
        // Remove many elements
        for (int i = 0; i < 75; i++) {
            stack.remove(0);
        }
        
        double after_removes = stack.memoryUtilization();
        std::cout << "After removes: " << std::fixed << std::setprecision(2) 
                  << after_removes * 100 << "%" << std::endl;
        
        tf.assert_true(after_removes < 0.5, "Memory utilization should trigger resize");
    }
    
    // Test 3: Shrinking behavior test
    {
        MemoryEfficientArrayStack<int> stack;
        
        // Add many elements to force growth
        for (int i = 0; i < 1000; i++) {
            stack.add(i, i);
        }
        
        int large_capacity = stack.getCapacity();
        
        // Remove most elements
        for (int i = 0; i < 900; i++) {
            stack.remove(0);
        }
        
        int small_capacity = stack.getCapacity();
        
        tf.assert_true(small_capacity < large_capacity, "Array should shrink after removes");
        tf.assert_equal(100, stack.size(), "Correct size after removes");
    }
    
    // Test 4: Edge cases
    {
        MemoryEfficientArrayStack<int> stack;
        
        // Remove from empty stack
        tf.assert_throws([&]() { stack.remove(0); }, "Remove from empty stack throws");
        
        // Add one, remove one repeatedly
        for (int i = 0; i < 10; i++) {
            stack.add(0, i);
            int removed = stack.remove(0);
            tf.assert_equal(i, removed, "Add/remove cycle " + std::to_string(i));
            tf.assert_equal(0, stack.size(), "Size zero after remove " + std::to_string(i));
        }
    }
}

// =============================================================================
// Exercise 2.3 Tests - Bidirectional Array Stack
// =============================================================================

void testExercise2_3() {
    std::cout << "\n=== Exercise 2.3: Bidirectional Array Stack Tests ===" << std::endl;
    TestFramework tf;
    
    // Test 1: Basic push/pop operations
    {
        BidirectionalArrayStack<int> stack;
        
        tf.assert_true(stack.empty(), "Initially empty");
        tf.assert_equal(0, stack.size(), "Initial size zero");
        
        // Push to front and back
        stack.pushFront(10);
        stack.pushBack(20);
        stack.pushFront(5);
        stack.pushBack(25);
        
        tf.assert_equal(4, stack.size(), "Size after pushes");
        tf.assert_true(!stack.empty(), "Not empty after pushes");
        
        // Pop from both ends
        int front = stack.popFront();
        tf.assert_equal(5, front, "Pop front returns correct value");
        
        int back = stack.popBack();
        tf.assert_equal(25, back, "Pop back returns correct value");
        
        tf.assert_equal(2, stack.size(), "Size after pops");
    }
    
    // Test 2: Alternating operations
    {
        BidirectionalArrayStack<int> stack;
        
        // Sequence: front(1), back(2), front(3), back(4)
        // Result should be: [3, 1, 2, 4]
        stack.pushFront(1);
        stack.pushBack(2);
        stack.pushFront(3);
        stack.pushBack(4);
        
        // Pop in order: 3, 4, 1, 2
        tf.assert_equal(3, stack.popFront(), "First pop front");
        tf.assert_equal(4, stack.popBack(), "First pop back");
        tf.assert_equal(1, stack.popFront(), "Second pop front");
        tf.assert_equal(2, stack.popBack(), "Second pop back");
        
        tf.assert_true(stack.empty(), "Empty after all pops");
    }
    
    // Test 3: Resize behavior
    {
        BidirectionalArrayStack<int> stack;
        
        // Fill from both ends to trigger resize
        for (int i = 0; i < 100; i++) {
            if (i % 2 == 0) {
                stack.pushFront(i);
            } else {
                stack.pushBack(i);
            }
        }
        
        tf.assert_equal(100, stack.size(), "Size after mixed pushes");
        
        // Verify we can still operate after resize
        stack.pushFront(-1);
        stack.pushBack(101);
        tf.assert_equal(102, stack.size(), "Size after resize operations");
        
        tf.assert_equal(-1, stack.popFront(), "Front after resize");
        tf.assert_equal(101, stack.popBack(), "Back after resize");
    }
    
    // Test 4: Error handling
    {
        BidirectionalArrayStack<int> stack;
        
        tf.assert_throws([&]() { stack.popFront(); }, "Pop front from empty throws");
        tf.assert_throws([&]() { stack.popBack(); }, "Pop back from empty throws");
    }
    
    // Test 5: Performance test
    {
        BidirectionalArrayStack<int> stack;
        
        auto start = std::chrono::high_resolution_clock::now();
        
        // Mixed operations
        for (int i = 0; i < 10000; i++) {
            stack.pushFront(i);
            stack.pushBack(i);
            if (i % 3 == 0 && !stack.empty()) {
                stack.popFront();
            }
            if (i % 5 == 0 && !stack.empty()) {
                stack.popBack();
            }
        }
        
        auto end = std::chrono::high_resolution_clock::now();
        auto duration = std::chrono::duration_cast<std::chrono::microseconds>(end - start);
        
        std::cout << "10K mixed operations took: " << duration.count() << "μs" << std::endl;
        std::cout << "Final size: " << stack.size() << std::endl;
    }
}

// =============================================================================
// Exercise 2.4 Tests - RootishArrayStack Space Efficiency
// =============================================================================

void testExercise2_4() {
    std::cout << "\n=== Exercise 2.4: RootishArrayStack Space Efficiency Tests ===" << std::endl;
    TestFramework tf;
    
    // Test 1: Basic operations
    {
        RootishArrayStack stack;
        
        // Add elements
        for (int i = 0; i < 10; i++) {
            stack.add(i, i * 10);
        }
        
        tf.assert_equal(10, stack.size(), "Size after adds");
        
        // Check values
        for (int i = 0; i < 10; i++) {
            tf.assert_equal(i * 10, stack.get(i), "Get element " + std::to_string(i));
        }
        
        // Test set operation
        stack.set(5, 999);
        tf.assert_equal(999, stack.get(5), "Set operation works");
    }
    
    // Test 2: Space efficiency analysis
    {
        std::cout << "\nSpace Efficiency Analysis:" << std::endl;
        
        std::vector<int> sizes = {10, 50, 100, 500, 1000};
        
        for (int n : sizes) {
            RootishArrayStack stack;
            
            // Fill with n elements
            for (int i = 0; i < n; i++) {
                stack.add(i, i);
            }
            
            int total_capacity = stack.totalCapacity();
            double efficiency = stack.spaceEfficiency();
            double theoretical_overhead = std::sqrt(2.0 * n);
            
            std::cout << "n=" << n 
                      << ", capacity=" << total_capacity 
                      << ", efficiency=" << std::fixed << std::setprecision(3) << efficiency
                      << ", overhead=" << (total_capacity - n)
                      << ", theoretical_overhead≈" << std::fixed << std::setprecision(1) << theoretical_overhead
                      << std::endl;
            
            // Space efficiency should be reasonable (> 50% for larger arrays)
            if (n >= 100) {
                tf.assert_true(efficiency > 0.5, "Space efficiency > 50% for n=" + std::to_string(n));
            }
        }
    }
    
    // Test 3: Block structure verification
    {
        RootishArrayStack stack;
        
        // Add elements to create multiple blocks
        for (int i = 0; i < 15; i++) {  // Should create blocks of size 1, 2, 3, 4, 5
            stack.add(i, i * 100);
        }
        
        // Verify we can access all elements
        for (int i = 0; i < 15; i++) {
            tf.assert_equal(i * 100, stack.get(i), "Block access test " + std::to_string(i));
        }
    }
    
    // Test 4: Dynamic growth and shrinking
    {
        RootishArrayStack stack;
        
        // Grow the stack
        for (int i = 0; i < 100; i++) {
            stack.add(i, i);
        }
        
        int large_capacity = stack.totalCapacity();
        
        // Shrink the stack
        for (int i = 0; i < 80; i++) {
            stack.remove(0);
        }
        
        int small_capacity = stack.totalCapacity();
        
        tf.assert_true(small_capacity <= large_capacity, "Capacity should not increase after removes");
        tf.assert_equal(20, stack.size(), "Correct size after removes");
        
        // Verify remaining elements are correct
        for (int i = 0; i < 20; i++) {
            tf.assert_equal(i + 80, stack.get(i), "Remaining element " + std::to_string(i));
        }
    }
    
    // Test 5: Random operations
    {
        RootishArrayStack stack;
        std::vector<int> reference;
        std::mt19937 rng(42);
        
        for (int op = 0; op < 1000; op++) {
            if (reference.empty() || rng() % 3 == 0) {
                // Add operation
                int pos = reference.empty() ? 0 : rng() % (reference.size() + 1);
                int value = rng() % 1000;
                
                stack.add(pos, value);
                reference.insert(reference.begin() + pos, value);
            } else {
                // Remove operation  
                int pos = rng() % reference.size();
                stack.remove(pos);
                reference.erase(reference.begin() + pos);
            }
        }
        
        auto end = std::chrono::high_resolution_clock::now();
        auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(end - start);
        
        tf.assert_equal((int)reference.size(), stack.size(), "Final size consistency");
        std::cout << "Stress test completed in " << duration.count() << "ms" << std::endl;
        
        auto metrics = stack.getMetrics();
        std::cout << "Total resizes: " << metrics.resize_count << std::endl;
        std::cout << "Average utilization: " << std::fixed << std::setprecision(3) 
                  << metrics.average_utilization << std::endl;
    }
}

// =============================================================================
// UPDATED MAIN FUNCTION TO RUN ALL TESTS
// =============================================================================

int main() {
    std::cout << "=== Chapter 2.7: Array-Based Data Structure Exercises - COMPLETE TEST SUITE ===" << std::endl;
    
    testExercise2_1();
    testExercise2_2(); 
    testExercise2_3();
    testExercise2_4();
    testExercise2_5();
    testExercise2_6();
    
    std::cout << "\n=== All Tests Completed ===" << std::endl;
    return 0;
}begin() + pos, value);
            } else {
                // Remove operation
                int pos = rng() % reference.size();
                
                int stack_val = stack.remove(pos);
                int ref_val = reference[pos];
                reference.erase(reference.begin() + pos);
                
                tf.assert_equal(ref_val, stack_val, "Random operation " + std::to_string(op));
            }
            
            // Verify size matches
            tf.assert_equal((int)reference.size(), stack.size(), "Size consistency " + std::to_string(op));
        }
    }
}

// =============================================================================
// Exercise 2.5 Tests - Robust Error Handling
// =============================================================================

void testExercise2_5() {
    std::cout << "\n=== Exercise 2.5: Robust Error Handling Tests ===" << std::endl;
    TestFramework tf;
    
    // Test 1: Null/uninitialized array handling
    {
        RobustArrayStack<int> stack;
        
        tf.assert_true(stack.isValid(), "Initially valid state");
        
        // Test operations on empty/null array
        tf.assert_throws([&]() { stack.get(0); }, "Get from empty array throws");
        tf.assert_throws([&]() { stack.remove(0); }, "Remove from empty array throws");
        
        // Add should initialize array if needed
        stack.add(0, 42);
        tf.assert_equal(42, stack.get(0), "Add initializes array");
        tf.assert_true(stack.isValid(), "Valid after first add");
    }
    
    // Test 2: Boundary condition testing
    {
        RobustArrayStack<int> stack;
        
        // Test negative indices
        tf.assert_throws([&]() { stack.add(-1, 10); }, "Negative index in add throws");
        tf.assert_throws([&]() { stack.get(-1); }, "Negative index in get throws");
        tf.assert_throws([&]() { stack.remove(-1); }, "Negative index in remove throws");
        
        // Add some elements
        for (int i = 0; i < 5; i++) {
            stack.add(i, i * 10);
        }
        
        // Test index beyond size
        tf.assert_throws([&]() { stack.add(6, 60); }, "Index beyond size+1 in add throws");
        tf.assert_throws([&]() { stack.get(5); }, "Index beyond size in get throws");
        tf.assert_throws([&]() { stack.remove(5); }, "Index beyond size in remove throws");
        
        // Test valid boundary cases
        stack.add(5, 50);  // Should work (index == size)
        tf.assert_equal(50, stack.get(5), "Add at size boundary works");
    }
    
    // Test 3: Integer overflow scenarios
    {
        RobustArrayStack<int> stack;
        
        // This would be hard to test with actual overflow, so we test the logic
        // Test with large valid indices
        for (int i = 0; i < 1000; i++) {
            stack.add(i, i);
        }
        
        tf.assert_equal(1000, stack.size(), "Large array operations work");
        tf.assert_equal(999, stack.get(999), "Access to large index works");
    }
    
    // Test 4: State consistency after errors
    {
        RobustArrayStack<int> stack;
        
        // Add some elements
        for (int i = 0; i < 5; i++) {
            stack.add(i, i);
        }
        
        int original_size = stack.size();
        
        // Try invalid operations
        try { stack.add(-1, 999); } catch (...) {}
        try { stack.get(10); } catch (...) {}
        try { stack.remove(-1); } catch (...) {}
        
        // Verify state is unchanged
        tf.assert_equal(original_size, stack.size(), "Size unchanged after failed operations");
        tf.assert_true(stack.isValid(), "Array still valid after errors");
        
        // Verify data integrity
        for (int i = 0; i < original_size; i++) {
            tf.assert_equal(i, stack.get(i), "Data intact after errors " + std::to_string(i));
        }
    }
    
    // Test 5: Resource cleanup testing
    {
        // Test that destructor works correctly even with errors
        for (int trial = 0; trial < 10; trial++) {
            RobustArrayStack<int>* stack = new RobustArrayStack<int>();
            
            // Add some elements
            for (int i = 0; i < 100; i++) {
                stack->add(i, i);
            }
            
            // Try some invalid operations
            try { stack->get(-1); } catch (...) {}
            try { stack->remove(1000); } catch (...) {}
            
            // Delete should not crash
            delete stack;
        }
        
        tf.assert_true(true, "Memory cleanup works correctly");
    }
}

// =============================================================================
// Exercise 2.6 Tests - Resizing Strategy Comparison
// =============================================================================

void testExercise2_6() {
    std::cout << "\n=== Exercise 2.6: Resizing Strategy Comparison Tests ===" << std::endl;
    TestFramework tf;
    
    // Test 1: Basic functionality for each strategy
    {
        std::vector<ResizePolicy> policies = {
            ResizePolicy::DOUBLE,
            ResizePolicy::GOLDEN_RATIO,
            ResizePolicy::ADDITIVE,
            ResizePolicy::CUSTOM
        };
        
        std::vector<std::string> policy_names = {
            "DOUBLE", "GOLDEN_RATIO", "ADDITIVE", "CUSTOM"
        };
        
        for (size_t p = 0; p < policies.size(); p++) {
            ConfigurableArrayStack<int> stack(policies[p], 1.5);
            
            // Add elements to trigger resizes
            for (int i = 0; i < 100; i++) {
                stack.add(i, i * 10);
            }
            
            tf.assert_equal(100, stack.size(), policy_names[p] + " - correct size");
            
            // Verify elements
            for (int i = 0; i < 100; i++) {
                tf.assert_equal(i * 10, stack.get(i), policy_names[p] + " - element " + std::to_string(i));
            }
        }
    }
    
    // Test 2: Performance comparison
    {
        std::cout << "\nPerformance Comparison (1000 operations):" << std::endl;
        std::cout << std::left << std::setw(15) << "Policy" 
                  << std::setw(12) << "Time(μs)" 
                  << std::setw(12) << "Resizes" 
                  << std::setw(15) << "Memory(KB)" 
                  << "Efficiency" << std::endl;
        std::cout << std::string(60, '-') << std::endl;
        
        struct PolicyTest {
            ResizePolicy policy;
            std::string name;
            double factor;
        };
        
        std::vector<PolicyTest> tests = {
            {ResizePolicy::DOUBLE, "Double", 2.0},
            {ResizePolicy::GOLDEN_RATIO, "Golden", 1.618},
            {ResizePolicy::ADDITIVE, "Additive", 100},
            {ResizePolicy::CUSTOM, "Custom1.5", 1.5},
            {ResizePolicy::CUSTOM, "Custom1.2", 1.2}
        };
        
        for (const auto& test : tests) {
            ConfigurableArrayStack<int> stack(test.policy, test.factor);
            
            auto start = std::chrono::high_resolution_clock::now();
            
            // Perform operations
            for (int i = 0; i < 1000; i++) {
                stack.add(i, i);
            }
            
            auto end = std::chrono::high_resolution_clock::now();
            auto duration = std::chrono::duration_cast<std::chrono::microseconds>(end - start);
            
            auto metrics = stack.getMetrics();
            
            std::cout << std::left << std::setw(15) << test.name
                      << std::setw(12) << duration.count()
                      << std::setw(12) << metrics.resize_count
                      << std::setw(15) << (metrics.total_memory_allocated / 1024)
                      << std::fixed << std::setprecision(3) << metrics.average_utilization
                      << std::endl;
        }
    }
    
    // Test 3: Memory usage patterns
    {
        std::cout << "\nMemory Usage Analysis:" << std::endl;
        
        ConfigurableArrayStack<int> doubler(ResizePolicy::DOUBLE);
        ConfigurableArrayStack<int> golden(ResizePolicy::GOLDEN_RATIO);
        
        std::vector<int> sizes = {10, 50, 100, 500, 1000};
        
        for (int size : sizes) {
            // Reset stacks
            doubler = ConfigurableArrayStack<int>(ResizePolicy::DOUBLE);
            golden = ConfigurableArrayStack<int>(ResizePolicy::GOLDEN_RATIO);
            
            // Fill both stacks
            for (int i = 0; i < size; i++) {
                doubler.add(i, i);
                golden.add(i, i);
            }
            
            auto double_metrics = doubler.getMetrics();
            auto golden_metrics = golden.getMetrics();
            
            std::cout << "Size " << size 
                      << ": Double(" << double_metrics.resize_count << " resizes, "
                      << std::fixed << std::setprecision(3) << double_metrics.average_utilization << " util)"
                      << ", Golden(" << golden_metrics.resize_count << " resizes, "
                      << std::fixed << std::setprecision(3) << golden_metrics.average_utilization << " util)"
                      << std::endl;
        }
    }
    
    // Test 4: Stress test with mixed operations
    {
        std::cout << "\nStress Test (10K mixed operations):" << std::endl;
        
        ConfigurableArrayStack<int> stack(ResizePolicy::DOUBLE);
        std::mt19937 rng(42);
        std::vector<int> reference;
        
        auto start = std::chrono::high_resolution_clock::now();
        
        for (int op = 0; op < 10000; op++) {
            if (reference.empty() || rng() % 3 == 0) {
                // Add operation
                int pos = reference.empty() ? 0 : rng() % (reference.size() + 1);
                int value = rng() % 10000;
                
                stack.add(pos, value);
                reference.insert(reference.
/*
=============================================================================
EXERCISE IMPLEMENTATION GUIDE
=============================================================================

Exercise 2.2 - Memory Management:
- Focus: Prevent memory leaks after remove() operations
- Key insight: Set unused array positions to null/default values
- Test: Monitor memory usage with repeated add/remove cycles

Exercise 2.3 - Bidirectional Growth:
- Focus: Implement deque functionality with single array
- Key insight: Track front and back pointers, resize by centering
- Test: Operations at both ends should be efficient

Exercise 2.4 - Space Efficiency:
- Focus: RootishArrayStack with √n space overhead
- Key insight: Use blocks of increasing size (1, 2, 3, ...)
- Test: Space usage should be n + O(√n)

Exercise 2.5 - Error Handling:
- Focus: Robust operations with comprehensive error checking
- Key insight: Validate inputs, handle null arrays gracefully
- Test: All edge cases should be handled without crashes

Exercise 2.6 - Resizing Strategies:
- Focus: Compare performance of different growth policies
- Key insight: Trade-offs between memory usage and resize frequency
- Test: Benchmark different strategies with various workloads

=============================================================================
*/
  
