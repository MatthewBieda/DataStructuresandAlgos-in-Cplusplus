#include <iostream>
#include <sstream>
#include <vector>
#include <string>

std::vector<std::string> split(const std::string& str, char delimiter) {
    std::vector<std::string> tokens;
    std::string token;
    std::istringstream tokenStream(str);

    while (std::getline(tokenStream, token, delimiter)) {
	tokens.push_back(token);
    }

    return tokens;
}

int main() {
    std::string str = "Hello,world,this,is,C++";
    char delimiter = ',';
    std::vector<std::string> result = split(str, delimiter);

    for (const std::string& token: result) {
	std::cout << token << std::endl;
    }
}
