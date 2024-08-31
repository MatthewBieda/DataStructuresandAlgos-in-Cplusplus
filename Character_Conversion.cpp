#include <iostream>
#include <string>

// Convert a character to its numerical value assuming 'a' = 0, 'b' = 1, ..., 'z' = 25
int charToIndex(char c) {
    return c - 'a';
}

// Convert a numerical value back to a character assuming 0 = 'a', 1 = 'b', ..., 25 = 'z'
char indexToChar(int index) {
    return 'a' + index;
}

// Example usage
int main() {
    std::string input = "hello";
    std::string hashedString;

    for (char c : input) {
        int index = charToIndex(c);
        std::cout << "Character: " << c << " -> Index: " << index << std::endl;
        
        // Example hash calculation
        int hash_value = (index + 3) % 26; // Just an example of a simple hash function
        hashedString += indexToChar(hash_value);
    }

    std::cout << "Hashed String: " << hashedString << std::endl;

    return 0;
}

