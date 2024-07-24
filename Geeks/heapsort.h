#include <cstdio>

#define _countof(x) (sizeof(x) / sizeof((x)[0]))

void exch(int a[], int i, int j) {
    int t = a[i];
    a[i] = a[j];
    a[j] = t;
}

void sink(int a[], int k, size_t n) {
    while (2 * k + 1 < n) { // Changed condition to account for 0-based index
        int j = 2 * k + 1; // Left child index
        if (j + 1 < n && a[j] < a[j + 1]) {
            j++; // Use right child instead of left child if it's larger
        }
        if (a[k] >= a[j]) {
            break; // If parent is larger than both children, stop sinking
        }
        exch(a, k, j);
        k = j;
    }
}

void heap_sort(int a[], size_t n) {
    // Build heap (rearrange array)
    for (int k = n / 2 - 1; k >= 0; k--) {
        sink(a, k, n);
    }

    // One by one extract elements from heap
    for (size_t i = n - 1; i > 0; i--) {
        exch(a, 0, i); // Move current root to end
        sink(a, 0, i); // Call max heapify on the reduced heap
    }
}

int main() {
    int a[] = {'S', 'O', 'R', 'T', 'E', 'X', 'A', 'M', 'P', 'L', 'E'};
    size_t len = _countof(a);
    heap_sort(a, len);
    for (size_t i = 0; i < len; i++) {
        printf("%c ", a[i]);
    }
    puts("\n");
}

