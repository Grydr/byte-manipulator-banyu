#include "include/byte-manipulator.hpp"
#include <cstdint>
#include <cstring>
#include <iostream>
#include <iterator>
#include <sys/types.h>
#include <vector>

const int back_left_thruster = 500;
const int middle_left_thruster = 500;
const int top_left_thruster = 500;
const int back_right_thruster = 500;
const int middle_right_thruster = 500;
const int top_right_thruster = 500;
const int pid = 1;
const int takeBall = 1;
const int dropBall = 1;

// void intToBit(int val) {
//    uint8_t bits[8] = {0};
//
//    while (val != 0 && i > 0) {
//       int rem = val % 2;
//       bits[i - 1] = rem;
//
//       val = val / 2;
//       i -= 1;
//    }
//
//    int len = sizeof(bits) / sizeof(bits[0]);
//    std::cout << "Bits of " << val << ": ";
//    for (int j = 1; j < len; j++) {
//       std::cout << static_cast<int>(bits[j]);
//    }
//    std::cout << std::endl;
// }

void reverseArray(uint8_t *array, size_t arrSize) {
   for (size_t i = 0; i < arrSize / 2; i++) {
      uint8_t temp = array[i];
      array[i] = array[arrSize - i - 1];
      array[arrSize - i - 1] = temp;
   }
}

int main() {
   uint8_t temp = back_left_thruster >> 8;
   uint8_t thruster[8] = {
       (uint8_t)back_left_thruster,
       temp,
   };
   reverseArray(thruster, std::size(thruster));

   for (size_t i = 0; i < std::size(thruster); i++) {
      std::cout << "thruster value at index " << i << ": " << static_cast<uint>(thruster[i]) << std::endl;
   }
   std::cout << "thruster size: " << std::size(thruster) << std::endl;

   // int thrusterLen = sizeof(thruster);
   uint a = thruster[6];
   uint b = thruster[7];
   a = a << 8;

   int res = a | b;
   std::cout << "real result is: " << res << std::endl;
   return 0;
}
