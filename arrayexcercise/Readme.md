# Array excercises

## 1. Bulk Insertion Optimization

Explanation
This exercise is about implementing an addAll(i, c) method that inserts all elements from a collection c into a list at position i.
Why repeated calls to add(i, x) are inefficient:

Multiple Shifts: Each call to add(i, x) requires shifting all elements from position i onwards to the right by one position. If you're adding k elements, you'd perform this shifting operation k times.
Time Complexity:

Each add(i, x) takes O(n-i) time for shifting
Doing this k times gives O(k × (n-i)) total time
This is much worse than necessary


Multiple Resizing: If the array needs to grow during the process, you might trigger multiple resize operations instead of just one.

More Efficient Approach:
Instead of repeated calls to add(i, x), you should:

Single Shift: Shift all elements from position i onwards to the right by k positions (where k is the size of collection c) in one operation.
Bulk Insert: Copy all elements from collection c directly into positions i through i+k-1.
Single Resize: Check if you need to resize the array only once at the beginning.


