#include <iostream>
#include <bitset>

// Function to check if a number is odd
bool isOdd(int x) {
    return x & 1;
}

// Function to check if a number is even
bool isEven(int x) {
    return !(x & 1);
}

// Function to toggle a bit at a given position
int toggleBit(int x, int bitPosition) {
    return x ^ (1 << bitPosition);
}

// Function to set a bit at a given position
int setBit(int x, int bitPosition) {
    return x | (1 << bitPosition);
}

// Function to clear a bit at a given position
int clearBit(int x, int bitPosition) {
    return x & ~(1 << bitPosition);
}

// Function to check if a bit is set at a given position
bool isBitSet(int x, int bitPosition) {
    return x & (1 << bitPosition);
}

// Function to count the number of set bits in an integer
int countSetBits(int x) {
    return __builtin_popcount(x);
}

// Function to find the lowest set bit
int lowestSetBit(int x) {
    return x & -x;
}

// Function to get the next higher power of two
int nextPowerOfTwo(int x) {
    return 1 << (32 - __builtin_clz(x - 1));
}

// Function to count the number of trailing zeroes in an integer
int countTrailingZeroes(int x) {
    return __builtin_ctz(x);
}

// Function to reverse the bits of an integer
unsigned int reverseBits(unsigned int x) {
    x = ((x >> 1) & 0x55555555) | ((x & 0x55555555) << 1);
    x = ((x >> 2) & 0x33333333) | ((x & 0x33333333) << 2);
    x = ((x >> 4) & 0x0F0F0F0F) | ((x & 0x0F0F0F0F) << 4);
    x = ((x >> 8) & 0x00FF00FF) | ((x & 0x00FF00FF) << 8);
    x = (x >> 16) | (x << 16);
    return x;
}

int main() {
    int num = 29; // Example number
    int bitPosition = 3; // Example bit position

    std::cout << "Number: " << num << std::endl;
    std::cout << "Is Odd: " << isOdd(num) << std::endl;
    std::cout << "Is Even: " << isEven(num) << std::endl;
    std::cout << "Toggle Bit at Position " << bitPosition << ": " << toggleBit(num, bitPosition) << std::endl;
    std::cout << "Set Bit at Position " << bitPosition << ": " << setBit(num, bitPosition) << std::endl;
    std::cout << "Clear Bit at Position " << bitPosition << ": " << clearBit(num, bitPosition) << std::endl;
    std::cout << "Is Bit Set at Position " << bitPosition << ": " << isBitSet(num, bitPosition) << std::endl;
    std::cout << "Count Set Bits: " << countSetBits(num) << std::endl;
    std::cout << "Lowest Set Bit: " << lowestSetBit(num) << std::endl;
    std::cout << "Next Higher Power of Two: " << nextPowerOfTwo(num) << std::endl;
    std::cout << "Count Trailing Zeroes: " << countTrailingZeroes(num) << std::endl;
    std::cout << "Reverse Bits: " << std::bitset<32>(reverseBits(num)) << std::endl;

    return 0;
}

