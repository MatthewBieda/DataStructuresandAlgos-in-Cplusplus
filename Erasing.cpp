#include <vector>
#include <algorithm> // for std::remove
#include <iostream>

int main() {
    std::vector<int> vec = {1, 2, 3, 4, 2, 5, 2, 6};

    // Remove all occurrences of the value 2
    // Erase-remove idiom
    vec.erase(std::remove(vec.begin(), vec.end(), 2), vec.end());

    // Now vec contains {1, 3, 4, 5, 6}
    std::cout << "Using Erase-Remove idiom" << std::endl;
    for (const int& v: vec) {
	std::cout << v;
    }
    std::cout << std::endl;

    // Using std::erase (C++ 20)
    std::vector<int> vec2 = {1, 2, 3, 4, 2, 5, 2, 6};

    // Remove all occurrences of the value 2
    std::erase(vec2, 2);

    // Now vec contains {1, 3, 4, 5, 6}
    
    std::cout << "Using std::delete" << std::endl;
    for (const int& v2: vec2) {
	std::cout << v2;
    }
    std::cout << std::endl;

    // Using std::erase_if
    // Remove elements based on a condition
    std::vector<int> vec3 = {1, 2, 3, 4, 2, 5, 2, 6};

    // Remove all even numbers
    std::erase_if(vec3, [](int x) { return x % 2 == 0; });

    // Now vec contains {1, 3, 5}
    std::cout << "Using std::erase_if" << std::endl;
    for (const int& v3: vec3) {
    	std::cout << v3;
    }
    std::cout << std::endl;

    return 0;
}

