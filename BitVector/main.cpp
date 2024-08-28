// BitVector.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include "bitvector.hpp"

int main()
{
    uint8_t a8 = 0b00001111; // 15 in decimal
    
    bitvector vec(a8);
    vec.print_bitvector();
    auto x = vec.getbit(0);
    vec.setbit(6);
    vec.print_bitvector();
    vec.flipbit(6);
    vec.print_bitvector();
    vec.clearbit(1);
    vec.print_bitvector();
    std::cout << vec.bitcount() << "\n";

   uint8_t b8 = 0b00110011; // 51 in decimal
   uint8_t result8 = addbits(a8, b8);
   bitvector vec2(result8);
   vec2.print_bitvector();
    
}

