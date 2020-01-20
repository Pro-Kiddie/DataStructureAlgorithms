//Problem: https://nus.kattis.com/problems/combinationlock

#include <iostream>
#include <fstream>

int degree_wrong(int pass1, int pass2){
    // 40 Calibration Marks on the Lock (0-39)
    // Do calculation in Calibrated marks and times final result by 9; 40 Marks = 360 degree
    // abs(pass1 - pass2) is WRONG! IT DOES NOT ALWAYS GIVE YOU THE CLOCKWISE DEGREES BETWEEN PASS1 & PASS2
    // E.g. pass1=10, pass2=0; abs(10-0) = 10 * 9 = 90 Degrees -> CORRECT!
    // E.g. pass1=0, pass2=10; abs(0-10) = 10 * 9 = 90 Degrees -> WRONG!; From 0 to 10 Clockwise is 270 Degree
    int degree = static_cast<int>(std::abs(pass1 - pass2) / 40.0f * 360);
    return 360 - degree;
}

int clockwise_degree(int start, int end){
    // To always find the CLOCKWISE DEGREES between the start and end:
    // (start - end + 40) % 40
    // E.g. ((10 - 0) + 40) % 40 = 10
    // E.g. ((0 - 10) + 40) % 40 = 30
    // Negative difference means the difference gives you ANTI-CLOCKWISE DEGREES between start and end -> +40 to get the CLOCKWISE DEGREES
    // %40 is to wrap back to cancel the effect of +40 if the difference is positive 
    return (start - end + 40) % 40 * 9;
    // Times 9 to give degree
}

int main(){
    int start, pass1, pass2, pass3, result;
    //std::ifstream infile("combinationlock.in");
    while (std::cin >> start >> pass1 >> pass2 >> pass3){
        //If input is "0 0 0 0", signifies the previous line is last case -> Break
        if(start == 0 && pass1 == 0 && pass2 == 0 && pass3 == 0) break;

        // Steps:
        // Turn the lock clockwise 2 full turns from start
        // Continue turning clockwise until the pass1 is reached
        // Need to find the anti-clockwise degree between start and pass1
        // Turn the lock anti-clockwise 1 full turn from pass1
        // Continue turning anti-clockwise until pass2 is reached
        // Need to find the anti-clockwise degree between pass1 and pass2
        // Turn the lock clockwise again until the pass3 is reached

        // 3 Compulsory full turns
        result = 0 + 360 * 3;
        // From start to pass1, clockwise
        result += clockwise_degree(start, pass1);
        // From pass1 to pass2, anti-clockwise
        // a to b (anti-clockwise) = b to a (clockwise)
        // Therefore:
        result += clockwise_degree(pass2, pass1);
        // pass2 to pass3 (clockwise)
        result += clockwise_degree(pass2, pass3);
        std::cout << result << std::endl;
    }
    //std::cout << -30 % 40 << std::endl;
    return 0;
}