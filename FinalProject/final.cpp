#include <iostream>
#include <fstream>
#include <string>

int main() {
    std::ifstream file("example.txt");
    std::string word;

    if (!file) {
        std::cerr << "Error opening file.\n";
        return 1;
    }

    while (file >> word) {
        std::cout << word << std::endl;
    }

    file.close();
    return 0;
}

