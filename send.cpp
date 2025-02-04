// #include "include/byte-manipulator.hpp"
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

void writeToBuf(int data, uint8_t *buf, size_t size, int bufPos) {
   buf[bufPos] = data >> 8;
   buf[bufPos + 1] = data & 0xFF;
}

int main() {
   uint8_t buffer[8];

   for (size_t i = 0; i < std::size(buffer); i++) {
      std::cout << "buffer value at index " << i << ": " << (uint)buffer[i] << std::endl;
   }
   std::cout << "buffer size: " << std::size(buffer) << std::endl;

   // int bufferLen = sizeof(buffer);
   uint a = buffer[6];
   uint b = buffer[7];
   a = a << 8;

   int res = a | b;
   std::cout << "real result is: " << res << std::endl;
   std::cout << "size of one of the thruster is: " << sizeof(back_left_thruster) << std::endl;
   return 0;
}
