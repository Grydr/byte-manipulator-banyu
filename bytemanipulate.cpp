#include <cstdint>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <iostream>

// Thrusters
const int back_left_thruster = -140;
const int middle_left_thruster = -350;
const int top_left_thruster = -244;
const int back_right_thruster = -350;
const int middle_right_thruster = 500;
const int top_right_thruster = 500;

// Flags
const int pid = 0;
const int takeBall = 0;
const int dropBall = 1;

/*
   data[0-5] 8 bits for thrusters
   data[6] 6 bits for thrusters msb (overflow) + 2 bits for signBit
   data[7] 4 bits for the remaining signBit + 3 bits for flags
*/

void storeThruster(uint8_t *data, int value, int pos) {
   bool isNegative = (value < 0);
   int absValue = std::abs(value);

   // store all the 8th bit
   data[pos] = static_cast<uint8_t>(absValue & 0xFF);

   // get the 9th bit (if exist) and store it in data[6]
   uint8_t msb = ((absValue >> 8) & 0x01) << pos;
   data[6] |= msb;

   // store the signBit in both data[6] & data[7]
   uint8_t signBit = isNegative ? 0x01 : 0x00;
   if (pos < 2) {
      data[6] |= signBit << (pos + 6);
   } else {
      data[7] |= signBit << (pos - 2);
   }
}

void readThruster(uint8_t *data, std::string thrusterName, int pos) {
   uint16_t msb = ((data[6] >> pos) & 0x01) << 8;
   int value = data[pos] | msb;

   int signBit;
   if (pos < 2) {
      signBit = (data[6] >> (pos + 6)) & 0x01;
   } else {
      signBit = (data[7] >> (pos - 2)) & 0x01;
   }

   if (signBit) {
      value = -1 * value;
   }
   std::cout << thrusterName << ": " << std::dec << value << std::endl;
}

void storeFlags(uint8_t *data, bool flagVal, int pos) {
   if (pos > 2) {
      fprintf(stderr, "ERROR: flags input position exceed array size\n");
      exit(1);
   }
   data[7] |= static_cast<uint8_t>(flagVal) << (pos + 4);
}

void readFlags(uint8_t *data, std::string flagName, int pos) {
   if (pos > 2) {
      fprintf(stderr, "ERROR: flags read position exceed array size\n");
      exit(1);
   }
   bool value = (data[7] >> (pos + 4)) & 0x01;
   std::cout << flagName << ": " << value << std::endl;
}

int main() {
   uint8_t data[8] = {0}; // 0-5 LSB, 6 MSB, 7 Flags

   // store thrusters
   storeThruster(data, back_left_thruster, 0);    // Bytes 0
   storeThruster(data, middle_left_thruster, 1);  // Bytes 1
   storeThruster(data, top_left_thruster, 2);     // Bytes 2
   storeThruster(data, back_right_thruster, 3);   // Bytes 3
   storeThruster(data, middle_right_thruster, 4); // Bytes 4
   storeThruster(data, top_right_thruster, 5);    // Bytes 5

   // store flags
   storeFlags(data, pid, 0);
   storeFlags(data, takeBall, 1);
   storeFlags(data, dropBall, 2);

   // print the packed data per bytes
   std::cout << "Bytes data:\n";
   for (int i = 0; i < sizeof(data); ++i) {
      std::cout << "Byte " << i << ": 0x" << std::hex << static_cast<int>(data[i]) << "\n";
   }
   std::cout << "\n";

   // print the values of thrusters
   std::cout << "Thruster values:\n";
   readThruster(data, "back_left_thruster", 0);    // Bytes 0
   readThruster(data, "middle_left_thruster", 1);  // Bytes 1
   readThruster(data, "top_left_thruster", 2);     // Bytes 2
   readThruster(data, "back_right_thruster", 3);   // Bytes 3
   readThruster(data, "middle_right_thruster", 4); // Bytes 4
   readThruster(data, "top_right_thruster", 5);    // Bytes 5
   std::cout << std::endl;

   // print flags
   std::cout << "flags:\n";
   readFlags(data, "PID", 0);
   readFlags(data, "Take Ball", 1);
   readFlags(data, "Drop Ball", 2);
   std::cout << std::endl;

   return 0;
}
