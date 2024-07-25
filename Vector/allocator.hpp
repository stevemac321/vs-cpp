#pragma once
#include <stdexcept>
#include <new> // for placement new
#include "heap.h"

namespace stevemac
{
#ifndef HEAP_SIZE_BYTES
#define HEAP_SIZE_BYTES 4096
#endif

    template <typename T, std::size_t N = HEAP_SIZE_BYTES>
    class StaticHeap {
        static constexpr std::size_t heapSize = N / sizeof(T);
        std::aligned_storage_t<sizeof(T), alignof(T)> buffer[heapSize];
        bool used[heapSize] = { false };

    public:
        template <typename... Args>
        T* allocate(Args&&... args) {
            for (std::size_t i = 0; i < heapSize; ++i) {
                if (!used[i]) {
                    used[i] = true;
                    return new (&buffer[i]) T(std::forward<Args>(args)...);
                }
            }
            return nullptr; // No space available
        }

        void deallocate(T* ptr) {
            for (std::size_t i = 0; i < heapSize; ++i) {
                if (ptr == reinterpret_cast<T*>(&buffer[i])) {
                    ptr->~T();
                    used[i] = false;
                    return;
                }
            }
        }
    };
    template <typename T, std::size_t N = HEAP_SIZE_BYTES>
    struct allocator {

        using value_type = T;
        using pointer = T*;
        using const_pointer = const T*;
        using reference = T&;
        using const_reference = const T&;
        using size_type = std::size_t;
        using difference_type = std::ptrdiff_t;

        static StaticHeap<T, N> heap;

        pointer allocate(size_type n) {
            if (n > static_cast<size_type>(std::numeric_limits<long>::max() / sizeof(T))) {
                throw std::overflow_error("Allocation size is too large");
            }
            // Allocate memory for n objects
            return static_cast<T*>(Heap_Malloc(static_cast<long>(n * sizeof(T))));
        }

        void deallocate(pointer p, size_type n = 0) {
            heap.deallocate(p);
        }

        template<typename... Args>
        void construct(pointer p, Args&&... args) {
            new (p) T(std::forward<Args>(args)...); // placement new
        }

        void destroy(pointer p) { p->~T(); }

        size_type max_size() const { return _max; }

        const size_type _max = 1048576;
    };

    template <typename T, std::size_t N>
    StaticHeap<T, N> allocator<T, N>::heap;

} // end of namespace
