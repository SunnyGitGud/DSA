#include <iostream>
#include <vector>
#include <stdexcept>
#include <cassert>

template<typename T>
class ArrayDeque {
protected:
    std::vector<T> a;  // backing array
    int n;             // number of elements
    int j;             // index of first element

    virtual void resize() {
        std::vector<T> b(std::max(1, 2 * n));
        for (int k = 0; k < n; k++) {
            b[k] = a[(j + k) % a.size()];
        }
        a = b;
        j = 0;
    }

public:
    ArrayDeque() : n(0), j(0) {
        a.resize(1);
    }

    virtual ~ArrayDeque() {}

    int size() const {
        return n;
    }

    T get(int i) const {
        if (i < 0 || i >= n) {
            throw std::out_of_range("Index out of range");
        }
        return a[(j + i) % a.size()];
    }

    T set(int i, const T& x) {
        if (i < 0 || i >= n) {
            throw std::out_of_range("Index out of range");
        }
        T y = a[(j + i) % a.size()];
        a[(j + i) % a.size()] = x;
        return y;
    }

    virtual void add(int i, const T& x) {
        if (i < 0 || i > n) {
            throw std::out_of_range("Invalid add position");
        }
        if (n + 1 > a.size()) {
            resize();
        }
        if (i < n / 2) {
            // Shift left part left
            j = (j == 0) ? a.size() - 1 : j - 1;
            for (int k = 0; k <= i - 1; k++) {
                a[(j + k) % a.size()] = a[(j + k + 1) % a.size()];
            }
        } else {
            // Shift right part right
            for (int k = n; k > i; k--) {
                a[(j + k) % a.size()] = a[(j + k - 1) % a.size()];
            }
        }
        a[(j + i) % a.size()] = x;
        n++;
    }

    bool add(const T& x) {
        add(n, x);
        return true;
    }

    T remove(int i) {
        if (i < 0 || i >= n) {
            throw std::out_of_range("Index out of range");
        }
        T x = a[(j + i) % a.size()];
        if (i < n / 2) {
            // Shift left part right
            for (int k = i; k > 0; k--) {
                a[(j + k) % a.size()] = a[(j + k - 1) % a.size()];
            }
            j = (j + 1) % a.size();
        } else {
            // Shift right part left
            for (int k = i; k < n - 1; k++) {
                a[(j + k) % a.size()] = a[(j + k + 1) % a.size()];
            }
        }
        n--;
        if (3 * n < a.size()) {
            resize();
        }
        return x;
    }

    // Debug method
    void print() const {
        std::cout << "[";
        for (int i = 0; i < n; i++) {
            std::cout << get(i);
            if (i < n - 1) std::cout << ", ";
        }
        std::cout << "]";
    }
};

template<typename T>
class BDeque : public ArrayDeque<T> {
public:
    BDeque(int b) {
        this->n = 0;           // number of elements
        this->j = 0;           // index of first element
        this->a.resize(b+1);   // create array of size b+1
    }
    
    ~BDeque() { }        // C++ Question: Why is this necessary?
    
    void add(int i, T x) {
        ArrayDeque<T>::add(i, x);  // delegate to parent
    }
    
    bool add(T x) {
        ArrayDeque<T>::add(this->size(), x);  // add at end
        return true;
    }
    
    void resize() override {}     // override to prevent resizing
};

template<typename T>
class SEList {
private:
    struct Node {
        BDeque<T> d;
        Node* prev;
        Node* next;

        Node(int b) : d(b), prev(nullptr), next(nullptr) {}
    };

    struct Location {
        Node* u;
        int j;
        Location() : u(nullptr), j(0) {}
        Location(Node* node, int index) : u(node), j(index) {}
    };

    int n;          // total number of elements
    int b;          // block size
    Node dummy;     // sentinel node

    void getLocation(int i, Location& ell) {
        if (i < 0 || i >= n) {
            throw std::out_of_range("Index out of range");
        }

        if (i < n / 2) {
            // Search forward
            Node* u = dummy.next;
            while (i >= u->d.size()) {
                i -= u->d.size();
                u = u->next;
            }
            ell.u = u;
            ell.j = i;
        } else {
            // Search backward
            Node* u = &dummy;
            int idx = n;
            while (i < idx) {
                u = u->prev;
                idx -= u->d.size();
            }
            ell.u = u;
            ell.j = i - idx;
        }
    }

    Node* addBefore(Node* target) {
        Node* newNode = new Node(b);
        newNode->next = target;
        newNode->prev = target->prev;
        target->prev->next = newNode;
        target->prev = newNode;
        return newNode;
    }

    void removeNode(Node* node) {
        node->prev->next = node->next;
        node->next->prev = node->prev;
        delete node;
    }

    void spread(Node* u) {
        Node* w = u;
        // Find position b blocks ahead or at the end
        for (int j = 0; j < b && w->next != &dummy; j++) {
            w = w->next;
        }
        // Create new empty block
        w = addBefore(w);

        // Redistribute elements backwards
        while (w != u) {
            while (w->d.size() < b && w->prev->d.size() > 0) {
                T x = w->prev->d.remove(w->prev->d.size() - 1);
                w->d.add(0, x);
            }
            w = w->prev;
        }
    }

    void gather(Node* u) {
        Node* w = u;
        // Collect elements from up to b blocks
        for (int j = 0; j < b - 1 && w->next != &dummy; j++) {
            while (w->d.size() < b && w->next->d.size() > 0) {
                T x = w->next->d.remove(0);
                w->d.add(x);
            }
            w = w->next;
        }
        
        // Remove empty blocks
        while (w != u && w != &dummy) {
            Node* toRemove = w;
            w = w->prev;
            if (toRemove->d.size() == 0) {
                removeNode(toRemove);
            }
        }
    }

public:
    SEList(int blockSize = 3) : n(0), b(blockSize), dummy(blockSize) {
        dummy.next = &dummy;
        dummy.prev = &dummy;
    }

    ~SEList() {
        clear();
    }

    int size() const {
        return n;
    }

    bool empty() const {
        return n == 0;
    }

    T get(int i) {
        Location ell;
        getLocation(i, ell);
        return ell.u->d.get(ell.j);
    }

    T set(int i, const T& x) {
        Location ell;
        getLocation(i, ell);
        T y = ell.u->d.get(ell.j);
        ell.u->d.set(ell.j, x);
        return y;
    }

    void add(const T& x) {
        Node* last = dummy.prev;
        if (last == &dummy || last->d.size() == b + 1) {
            last = addBefore(&dummy);
        }
        last->d.add(x);
        n++;
    }

    void add(int i, const T& x) {
        if (i < 0 || i > n) {
            throw std::out_of_range("Index out of range");
        }

        if (i == n) {
            add(x);
            return;
        }

        Location ell;
        getLocation(i, ell);
        Node* u = ell.u;
        int r = 0;

        // Look for space within b blocks
        Node* temp = u;
        while (r < b && temp != &dummy && temp->d.size() == b + 1) {
            temp = temp->next;
            r++;
        }

        if (r == b) {
            // Case 3: b blocks each with b+1 elements - need to spread
            spread(u);
            // After spreading, we can insert at the original location
        } else if (temp == &dummy) {
            // Case 2: ran off the end - add new node
            temp = addBefore(&dummy);
        }

        // Find the actual insertion point after potential spreading
        u = ell.u;
        while (u->d.size() == b + 1 && u->next != &dummy) {
            u = u->next;
        }

        // Work backwards, shifting elements
        while (u != ell.u) {
            if (u->prev->d.size() > 0) {
                T x = u->prev->d.remove(u->prev->d.size() - 1);
                u->d.add(0, x);
            }
            u = u->prev;
        }

        u->d.add(ell.j, x);
        n++;
    }

    T remove(int i) {
        if (i < 0 || i >= n) {
            throw std::out_of_range("Index out of range");
        }

        Location ell;
        getLocation(i, ell);
        T y = ell.u->d.get(ell.j);

        Node* u = ell.u;
        u->d.remove(ell.j);

        // Check if we need to gather elements
        if (u->d.size() < b - 1) {
            // Count consecutive blocks with size < b
            Node* temp = u;
            int consecutiveSmall = 0;
            while (temp != &dummy && temp->d.size() < b) {
                consecutiveSmall++;
                temp = temp->next;
            }
            
            if (consecutiveSmall >= b) {
                gather(u);
            } else {
                // Borrow from adjacent blocks
                while (u->d.size() < b - 1 && u->next != &dummy && u->next->d.size() > b - 1) {
                    T x = u->next->d.remove(0);
                    u->d.add(x);
                }
                while (u->d.size() < b - 1 && u->prev != &dummy && u->prev->d.size() > b - 1) {
                    T x = u->prev->d.remove(u->prev->d.size() - 1);
                    u->d.add(0, x);
                }
            }
        }

        // Remove empty blocks
        if (u->d.size() == 0 && u != &dummy) {
            removeNode(u);
        }

        n--;
        return y;
    }

    void clear() {
        while (dummy.next != &dummy) {
            removeNode(dummy.next);
        }
        n = 0;
    }
      void print() const {
        std::cout << "SEList (n=" << n << ", b=" << b << "): ";
        Node* current = dummy.next;
        while (current != &dummy) {
            current->d.print();
            current = current->next;
            if (current != &dummy) std::cout << " -> ";
        }
        std::cout << std::endl;
    }
   void printDetailed() const {
        std::cout << "=== SEList Detailed View ===" << std::endl;
        std::cout << "Total elements: " << n << ", Block size: " << b << std::endl;
        
        Node* current = dummy.next;
        int blockIndex = 0;
        int globalIndex = 0;
        
        while (current != &dummy) {
            std::cout << "Block " << blockIndex << " (size=" << current->d.size(); 
            current->d.print();
            std::cout << " [global indices " << globalIndex << "-" << (globalIndex + current->d.size() - 1) << "]";
            std::cout << std::endl;
            
            globalIndex += current->d.size();
            blockIndex++;
            current = current->next;
        }
        std::cout << "=========================" << std::endl;
    }
   bool validate() const {
        Node* current = dummy.next;
        int totalElements = 0;
        int blockCount = 0;
        
        while (current != &dummy) {
            totalElements += current->d.size();
            blockCount++;
            
            // Check block size constraints
            // All blocks except the last should have b to b+1 elements
            // The last block can have any number from 1 to b+1 elements
            if (current->next != &dummy) { // not the last block
                if (current->d.size() < b - 1 || current->d.size() > b + 1) {
                    std::cout << "Block size violation: non-last block has " << current->d.size() 
                              << " elements, should be between " << (b-1) << " and " << (b+1) << std::endl;
                    return false;
                }
            } else { // last block
                if (current->d.size() < 1 || current->d.size() > b + 1) {
                    std::cout << "Last block size violation: has " << current->d.size() 
                              << " elements, should be between 1 and " << (b+1) << std::endl;
                    return false;
                }
            }
            current = current->next;
        }
        
        if (totalElements != n) {
            std::cout << "Element count mismatch: counted " << totalElements 
                      << " but n=" << n << std::endl;
            return false;
        }
        
        return true;
    }
};


// Test and demonstration code
int main() {
    std::cout << "=== SEList Implementation Demo (with ArrayDeque inheritance) ===" << std::endl;
    
    // Test BDeque first
    std::cout << "\n=== Testing BDeque (inherits from ArrayDeque) ===" << std::endl;
    BDeque<int> bdeque(3); // capacity = 4
    
       
    
    // Add some elements
    bdeque.add(10);
    bdeque.add(20);
    bdeque.add(30);
    std::cout << "After adding 10, 20, 30: ";
    bdeque.print();
    std::cout << " (size: " << bdeque.size() << ")" << std::endl;
    
    // Insert at beginning
    bdeque.add(0, 5);
    std::cout << "After inserting 5 at position 0: ";
    bdeque.print();
    std::cout << " (size: " << bdeque.size() << ")" << std::endl;
    
    // Test capacity limit - BDeque should not resize beyond initial size
    std::cout << "Trying to add 4th element (should work since capacity is 4): ";
    bdeque.add(40);
    bdeque.print();
    std::cout << " (size: " << bdeque.size() << ")" << std::endl;
    
    // Remove some elements
    int removed = bdeque.remove(1);
    std::cout << "Removed element at position 1: " << removed << ", result: ";
    bdeque.print();
    std::cout << std::endl;
    
    std::cout << "\n=== Testing SEList ===" << std::endl;
    
    // Create SEList with block size 3
    SEList<int> list(3);
    
    std::cout << "\n1. Adding elements to end:" << std::endl;
    for (int i = 1; i <= 15; i++) {
        list.add(i * 10);
        if (i <= 8 || i % 3 == 0) {  // Show first 8 and then every 3rd
            std::cout << "Added " << i * 10 << ": ";
            list.print();
        }
    }
    
    std::cout << "\n2. Detailed view:" << std::endl;
    list.printDetailed();
    
    std::cout << "\n3. Testing get operations:" << std::endl;
    for (int i = 0; i < list.size(); i += 3) {
        std::cout << "list.get(" << i << ") = " << list.get(i) << std::endl;
    }
    
    std::cout << "\n4. Testing set operations:" << std::endl;
    int oldValue = list.set(5, 999);
    std::cout << "list.set(5, 999) returned old value: " << oldValue << std::endl;
    list.print();
    
    std::cout << "\n5. Testing insertions at various positions:" << std::endl;
    list.add(0, -10);  // Insert at beginning
    std::cout << "Inserted -10 at position 0: ";
    list.print();
    
    list.add(8, 555);  // Insert in middle
    std::cout << "Inserted 555 at position 8: ";
    list.print();
    
    std::cout << "\n6. Detailed view after insertions:" << std::endl;
    list.printDetailed();
    
    std::cout << "\n7. Testing removals:" << std::endl;
    int removed2 = list.remove(0);  // Remove from beginning
    std::cout << "Removed element at position 0: " << removed2 << std::endl;
    list.print();
    
    removed2 = list.remove(5);  // Remove from middle
    std::cout << "Removed element at position 5: " << removed2 << std::endl;
    list.print();
    
    std::cout << "\n8. Final detailed view:" << std::endl;
    list.printDetailed();
    
    std::cout << "\n9. Validation check:" << std::endl;
    if (list.validate()) {
        std::cout << "✓ SEList structure is valid!" << std::endl;
    } else {
        std::cout << "✗ SEList structure validation failed!" << std::endl;
    }
    
    std::cout << "\n10. Testing edge cases:" << std::endl;
    
    // Test with smaller list to trigger spread/gather operations
    SEList<int> smallList(2);
    std::cout << "Created SEList with block size 2" << std::endl;
    
    // Fill it up to trigger block splitting
    for (int i = 1; i <= 8; i++) {
        smallList.add(i);
    }
    std::cout << "After adding 8 elements: ";
    smallList.printDetailed();
    
    // Insert in middle to potentially trigger spread
    smallList.add(2, 99);
    std::cout << "After inserting 99 at position 2: ";
    smallList.printDetailed();
    
    // Remove elements to potentially trigger gather
    smallList.remove(3);
    smallList.remove(3);
    smallList.remove(3);
    std::cout << "After removing 3 elements: ";
    smallList.printDetailed();
    
    if (smallList.validate()) {
        std::cout << "✓ Small list validation passed!" << std::endl;
    }
    
    return 0;
}
