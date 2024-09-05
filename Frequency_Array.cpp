// When we want the frequency for constrained inputs, we can use a fixed-size array instead of a hashmap

#include <iostream>
#include <string>
#include <array>

void countFrequencies(const std::string& s) {
    // Frequency array for 'a' to 'z'
    std::array<int, 26> letterFreq = {}; 

    // Frequency array for digits '0' to '9'
    std::array<int, 10> digitFreq = {}; 

    for (char c : s) {
        if (c >= 'a' && c <= 'z') {
            letterFreq[c - 'a']++;
        } else if (c >= '0' && c <= '9') {
            digitFreq[c - '0']++;
        }
    }

    std::cout << "Letter Frequencies:" << std::endl;
    for (int i = 0; i < 26; ++i) {
        if (letterFreq[i] > 0) {
            std::cout << char('a' + i) << ": " << letterFreq[i] << std::endl;
        }
    }

    std::cout << "Digit Frequencies:" << std::endl;
    for (int i = 0; i < 10; ++i) {
        if (digitFreq[i] > 0) {
            std::cout << i << ": " << digitFreq[i] << std::endl;
        }
    }
}

int main() {
    std::string input = "example1234567890";
    countFrequencies(input);
    return 0;
}

