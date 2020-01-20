#include <iostream>
#include <fstream>

int main(void) {
    std::ifstream infile("sample.in");
    long long a = 0, b = 0;
    while (infile >> a >> b)
        std::cout << std::abs(a-b) << std::endl;
    infile.close();
    return 0;
}