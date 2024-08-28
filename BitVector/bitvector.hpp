#include <iostream>
#include <cassert>
#include <concepts>
#include <type_traits>
#include <bitset>
// see gibhub/stevemac321/CS-Latex with pdfs on bitwise operations.

// Define a concept that checks for unsigned integral types
template<typename T>
concept UnsignedBitwiseOperable = std::is_integral_v<T> && std::is_unsigned_v<T> && requires(T a, T b) {
    { a& b };   // Bitwise AND
    { a | b };   // Bitwise OR
    { a^ b };   // Bitwise XOR
    { ~a };      // Bitwise NOT
    { a << 1 };  // Left shift
    { a >> 1 };  // Right shift
};


template<UnsignedBitwiseOperable T>
class bitvector {
    T vec = T();
    size_t len = sizeof(T) * 8;

public:
    bitvector() {}
    bitvector(T v) :vec(v) { len = sizeof(T) * 8; }

    T getbit(size_t pos)
    {
        return (vec >> pos) & 1;
    }
    void setbit(size_t pos)
    {
        vec |= (T(1) << pos);  // Set the bit at 'pos' to 1
    }
    void clearbit(size_t pos) 
    {
        vec &= ~(T(1) << pos); // Clear the bit at 'pos' to 0
    }
    void flipbit(size_t pos) { vec ^= (1 << pos);  }
    size_t bitcount() 
    {
        T x = vec;
        size_t count = 0;
        while (x > 0) {
            count += (x & 1);
            x >>= 1;
        }
        return count;
    }
    void print_bitvector()
    {
        std::cout << std::bitset<sizeof(T) * 8>(vec) << "\n";
    }
};

template<UnsignedBitwiseOperable T>
T addbits(T a, T b)
{
    T sum = T();
    size_t carry = 0;
    size_t len = sizeof(T) * 8;


    for (size_t i = 0; i < len; i++) {
        size_t a_bit = (a >> i) & 1;
        size_t  b_bit = (b >> i) & 1;

        size_t sum_bit = a_bit ^ b_bit ^ carry;
        carry = (a_bit & b_bit) | (b_bit & carry) | (carry & a_bit);

        sum |= sum_bit << i;
        
    }

    if (carry) {
        sum |= 1 << (len - 1);
    }
    return sum;
}
