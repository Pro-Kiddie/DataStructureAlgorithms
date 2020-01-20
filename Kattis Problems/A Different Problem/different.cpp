//Problem: https://nus.kattis.com/problems/different
#include <iostream>

int main(void) {
    long long a, b;
    //The Kattis Judging system input from cin
    //Read the sample input for how you should store the input from cin line by line
    //Submitting solution that reads input from a file as shown in "different_input_from_file.cpp" will cause the Juding system to fail
    while (std::cin >> a >> b)
        std::cout << std::abs(a-b) << std::endl;
    return 0;
}