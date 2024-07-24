#pragma once

// Function to heapify a subtree rooted with node i which is an index in arr[].
// n is the size of the heap.
void heapify(int arr[], int n, int i) {
    int largest = i; // Initialize largest as root
    int left = 2 * i + 1; // left child
    int right = 2 * i + 2; // right child

    // If left child is larger than root
    if (left < n && arr[left] > arr[largest])
        largest = left;

    // If right child is larger than largest so far
    if (right < n && arr[right] > arr[largest])
        largest = right;

    // If largest is not root
    if (largest != i) {
        std::swap(arr[i], arr[largest]);

        // Recursively heapify the affected sub-tree
        heapify(arr, n, largest);
    }
}

// Main function to sort an array of given size using heap sort
void heap_sort(int arr[], const size_t n) {

    // Build heap (rearrange array)
    for (int i = n / 2 - 1; i >= 0; i--)
        heapify(arr, n, i);

    // One by one extract an element from heap
    for (int i = n - 1; i > 0; i--) {
        // Move current root to end
        std::swap(arr[0], arr[i]);

        // Call max heapify on the reduced heap
        heapify(arr, i, 0);
    }
}

void test_heap_sort() {
     TEST_BEGIN("test_merge_sort 1")
    int a[] = {12, 11, 13, 5, 6, 7};
    int b[] = {5, 6, 7, 11, 12, 13};
    heap_sort(a, __countof(a));
    ASSERT_ITER_EQ(std::begin(a), std::end(a), std::begin(b), std::end(b)); 
     TEST_END("test_merge_sort 1")

    
}

