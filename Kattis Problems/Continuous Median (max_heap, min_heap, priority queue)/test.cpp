#include <iostream>

int main(){
    unsigned int a = 1e9;
    unsigned int b = 1e9;
    unsigned int c = (unsigned int)(a + b)/2.0;
    std::cout << c << std::endl;
    return 0;
}