#include <cstddef>
#include <cstdint>
#include <cstdlib>
#include <cstring>
#include <iostream>
#include <sys/types.h>

const int back_left_thruster = 477;
const int middle_left_thruster = -350;
const int top_left_thruster = -244;
const int back_right_thruster = 500;
const int middle_right_thruster = 500;
const int top_right_thruster = 500;

// flags
const int pid = 1;
const int takeBall = 1;
const int dropBall = 1;

// const char *thruster_names[] = {"back_left_thruster", "middle_left_thruster", "top_left_thruster", "back_right_thruster", "middle_right_thruster", "top_right_thruster"};

void storeThruster(uint8_t *data, int value, size_t pos) {
   bool isNegative = (value < 0);
   int absValue = std::abs(value);

   data[pos] = static_cast<uint8_t>(absValue & 0xFF); // High byte (8 bits)

   uint8_t msb = ((absValue >> 8) & 0x01) << pos;
   data[6] |= msb; // Low byte (1 bits)

   uint8_t signBit = isNegative ? 1 : 0;
   if (pos < 2) {
      data[6] |= signBit << (pos + 6);
   } else {
      data[7] |= signBit << (pos - 2);
   }
}

void readThruster(uint8_t *data, std::string thrusterName, size_t pos) {
   uint16_t msb = (data[6] >> pos) & 0x01;
   uint16_t value = data[pos] | msb << 8;

   int signBit;
   if (pos < 2) {
      signBit = (data[6] >> (pos + 6)) & 0x01;
   } else {
      signBit = (data[7] >> (pos - 2)) & 0x01;
   }

   value = signBit ? -value : value;
   std::cout << thrusterName << ": " << std::dec << value << std::endl;
}

void storeFlags(uint8_t *data) {
   data[7] |= (pid ? 0x10 : 0x00);
   data[7] |= (takeBall ? 0x20 : 0x00);
   data[7] |= (dropBall ? 0x40 : 0x00);
}

void readFlags(uint8_t *data) {
   bool pidVal = data[7] & 0x10;
   bool takeVal = data[7] & 0x20;
   bool dropVal = data[7] & 0x40;

   std::cout << "PID: " << pidVal << "\nTake: " << takeVal << "\nDrop: " << dropVal << "\n";
}

int main() {
   uint8_t data[8] = {0}; // 0-5 LSB, 6 MSB, 7 Flags

   // thrusters
   storeThruster(data, back_left_thruster, 0);    // Bytes 0-1
   storeThruster(data, middle_left_thruster, 1);  // Bytes 2-3
   storeThruster(data, top_left_thruster, 2);     // Bytes 4-5
   storeThruster(data, back_right_thruster, 3);   // Bytes 6-7
   storeThruster(data, middle_right_thruster, 4); // Bytes 8-9
   storeThruster(data, top_right_thruster, 5);    // Bytes 10-11

   // print the packed data per bytes
   std::cout << "Bytes data:\n";
   for (int i = 0; i < sizeof(data); ++i) {
      std::cout << "Byte " << i << ": 0x" << std::hex << static_cast<int>(data[i]) << "\n";
   }
   std::cout << "\n";

   // print the values of thrusters
   std::cout << "Thruster values:\n";
   readThruster(data, "back_left_thruster", 0);    // Bytes 0-1
   readThruster(data, "middle_left_thruster", 1);  // Bytes 2-3
   readThruster(data, "top_left_thruster", 2);     // Bytes 4-5
   readThruster(data, "back_right_thruster", 3);   // Bytes 6-7
   readThruster(data, "middle_right_thruster", 4); // Bytes 8-9
   readThruster(data, "top_right_thruster", 5);    // Bytes 10-11
   std::cout << std::endl;

   storeFlags(data);

   // print flags
   std::cout << "flags:\n";
   readFlags(data);

   return 0;
}
