#pragma once
#include <stdexcept>
#include <new> // For placement new
#include <cstddef>
#include <type_traits>

template <typename T, std::size_t N = 4096>
class StaticHeap {
    static constexpr std::size_t heapSize = N / sizeof(T);
    typename std::aligned_storage<sizeof(T), alignof(T)>::type buffer[heapSize];
    bool used[heapSize] = { false };

public:
    template <typename... Args>
    T* allocate(std::size_t n) {
        for (std::size_t i = 0; i <= heapSize - n; ++i) {
            bool available = true;
            for (std::size_t j = 0; j < n; ++j) {
                if (used[i + j]) {
                    available = false;
                    break;
                }
            }
            if (available) {
                for (std::size_t j = 0; j < n; ++j) {
                    used[i + j] = true;
                    new (&buffer[i + j]) T();
                }
                return reinterpret_cast<T*>(&buffer[i]);
            }
        }
        return nullptr; // No space available
    }

    void deallocate(T* ptr, std::size_t n) {
        for (std::size_t i = 0; i < heapSize; ++i) {
            if (ptr == reinterpret_cast<T*>(&buffer[i])) {
                for (std::size_t j = 0; j < n; ++j) {
                    (ptr + j)->~T();
                    used[i + j] = false;
                }
                return;
            }
        }
    }
};


namespace stevemac
{
    template <typename T>
    struct allocator {
        using value_type = T;
        using pointer = T*;
        using const_pointer = const T*;
        using reference = T&;
        using const_reference = const T&;
        using size_type = std::size_t;
        using difference_type = std::ptrdiff_t;

        // Create an instance of StaticHeap
        static StaticHeap<T> heap;

        pointer allocate(size_type n) {
            if (n > static_cast<size_type>(std::numeric_limits<long>::max() / sizeof(T))) {
                throw std::overflow_error("Allocation size is too large");
            }
            // Allocate memory for n objects
            return heap.allocate(n);
        }

        void deallocate(pointer p, size_type n = 0) {
            heap.deallocate(p, n);
        }

        void construct(pointer p, const_reference val) {
            new (p) T(val);
        }

        void destroy(pointer p) {
            p->~T();
        }

        size_type max_size() const {
            return _max;
        }

        const size_type _max = 1048576;
    };

    template <typename T>
    StaticHeap<T> allocator<T>::heap;
} // end of namespace



