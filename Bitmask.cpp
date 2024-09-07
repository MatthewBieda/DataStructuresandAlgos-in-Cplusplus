#include <iostream>
#include <bitset>

class Bitmask {
private:
    unsigned int mask; // The bitmask stored as an unsigned integer

public:
    // Constructor
    Bitmask() : mask(0) {}

    // Set a bit at a specific position
    void setBit(int position) {
        mask |= (1 << position);
    }

    // Clear a bit at a specific position
    void clearBit(int position) {
        mask &= ~(1 << position);
    }

    // Toggle a bit at a specific position
    void toggleBit(int position) {
        mask ^= (1 << position);
    }

    // Check if a bit at a specific position is set
    bool isBitSet(int position) const {
        return (mask & (1 << position)) != 0;
    }

    // Print the bitmask
    void print() const {
        std::cout << "Bitmask: " << std::bitset<32>(mask) << std::endl;
    }
};

int main() {
    Bitmask bm;

    // Set some bits
    bm.setBit(1);
    bm.setBit(4);
    bm.setBit(7);

    // Print the bitmask
    bm.print(); // Should print: 00000000000000000000000010010010

    // Check some bits
    std::cout << "Bit at position 1 is set: " << bm.isBitSet(1) << std::endl;
    std::cout << "Bit at position 2 is set: " << bm.isBitSet(2) << std::endl;

    // Toggle a bit
    bm.toggleBit(4);
    bm.print(); // Should print: 00000000000000000000000010000010

    // Clear a bit
    bm.clearBit(1);
    bm.print(); // Should print: 00000000000000000000000010000000

    return 0;
}

