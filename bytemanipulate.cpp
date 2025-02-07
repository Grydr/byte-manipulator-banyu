#include <cstddef>
#include <cstdint>
#include <cstring>
#include <iostream>
#include <sys/types.h>

const int back_left_thruster = 477;
const int middle_left_thruster = 350;
const int top_left_thruster = 244;
const int back_right_thruster = 500;
const int middle_right_thruster = 500;
const int top_right_thruster = 500;

// flags
const int pid = 1;
const int takeBall = 1;
const int dropBall = 1;

const char *thruster_names[] = {"back_left_thruster", "middle_left_thruster", "top_left_thruster", "back_right_thruster", "middle_right_thruster", "top_right_thruster"};

void storeThruster(uint8_t *data, int value, size_t pos) {
   data[pos] = static_cast<uint8_t>(value); // High byte (8 bits)

   uint8_t mask = (value >> 8) << pos;
   data[6] |= mask; // Low byte (1 bits)
}

void readThruster(uint8_t *data, std::string thruster, size_t pos) {
   int mask = (data[6] >> pos) & 0x01;
   int value = data[pos] | mask << 8;
   std::cout << thruster << ": " << std::dec << value << std::endl;
}

void storeFlags(uint8_t *data, bool flags) {}

int main() {
   uint8_t data[8] = {0}; // 0-5 LSB, 6 MSB, 7 Flags

   // thrusters
   storeThruster(data, back_left_thruster, 0);    // Bytes 0-1
   storeThruster(data, middle_left_thruster, 1);  // Bytes 2-3
   storeThruster(data, top_left_thruster, 2);     // Bytes 4-5
   storeThruster(data, back_right_thruster, 3);   // Bytes 6-7
   storeThruster(data, middle_right_thruster, 4); // Bytes 8-9
   storeThruster(data, top_right_thruster, 5);    // Bytes 10-11

   // flags
   data[7] |= pid ? 0x01 : 0x00;      // Bit 0
   data[7] |= takeBall ? 0x02 : 0x00; // Bit 1
   data[7] |= dropBall ? 0x04 : 0x00; // Bit 2

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

   // print flags
   bool ex_pid = data[7] & 0x01;
   bool ex_take = (data[7] >> 1) & 0x01;
   bool ex_drop = (data[7] >> 2) & 0x01;

   std::cout << "flags:\n";
   std::cout << "PID: " << ex_pid << "\nTake: " << ex_take << "\nDrop: " << ex_drop << "\n";

   return 0;
}
