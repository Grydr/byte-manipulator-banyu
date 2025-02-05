#include <cstddef>
#include <cstdint>
#include <cstring>
#include <iostream>
#include <iterator>
#include <sys/types.h>
#include <vector>

const int back_left_thruster = 477;
const int middle_left_thruster = 350;
const int top_left_thruster = -244;
const int back_right_thruster = 500;
const int middle_right_thruster = 500;
const int top_right_thruster = 500;

// flags
const int pid = 1;
const int takeBall = 1;
const int dropBall = 1;

void storeThruster(uint8_t *data, int16_t value, size_t pos) {
   data[pos] = static_cast<uint8_t>((value >> 8)); // High byte
   data[pos + 1] = static_cast<uint8_t>(value);    // Low byte
}

int main() {
   uint8_t data[13] = {0}; // 12 bytes for thrusters, 1 byte for flags

   // thrusters
   storeThruster(data, back_left_thruster, 0);    // Bytes 0-1
   storeThruster(data, middle_left_thruster, 2);  // Bytes 2-3
   storeThruster(data, top_left_thruster, 4);     // Bytes 4-5
   storeThruster(data, back_right_thruster, 6);   // Bytes 6-7
   storeThruster(data, middle_right_thruster, 8); // Bytes 8-9
   storeThruster(data, top_right_thruster, 10);   // Bytes 10-11

   // flags
   data[12] |= pid ? 0x01 : 0x00;      // Bit 0
   data[12] |= takeBall ? 0x02 : 0x00; // Bit 1
   data[12] |= dropBall ? 0x04 : 0x00; // Bit 2

   // print the packed data per bytes
   std::cout << "Bytes data:\n";
   for (size_t i = 0; i < 13; ++i) {
      std::cout << "Byte " << std::dec << i << ": 0x" << std::hex << static_cast<int>(data[i]) << "\n";
   }
   std::cout << "\n";

   // print the values of thrusters
   const char *thruster_names[] = {"back_left_thruster", "middle_left_thruster", "top_left_thruster", "back_right_thruster", "middle_right_thruster", "top_right_thruster"};

   std::cout << "Thruster values:\n";
   for (size_t i = 0; i < 12; i += 2) {
      int16_t extracted = (static_cast<int16_t>(data[i]) << 8) | data[i + 1];
      std::cout << thruster_names[i / 2] << ": " << std::dec << extracted << "\n";
   }
   std::cout << "\n";

   // print flags
   bool ex_pid = data[12] & 0x01;
   bool ex_take = (data[12] >> 1) & 0x01;
   bool ex_drop = (data[12] >> 2) & 0x01;

   std::cout << "flags:\n";
   std::cout << "PID: " << ex_pid << "\nTake: " << ex_take << "\nDrop: " << ex_drop << "\n";

   return 0;
}
