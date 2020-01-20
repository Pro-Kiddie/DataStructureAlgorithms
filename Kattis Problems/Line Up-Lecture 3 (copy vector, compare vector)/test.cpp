//Problem: https://nus.kattis.com/problems/lineup

#include <iostream>
#include <vector>
#include <string>
#include <algorithm>

using namespace std;

int main(){
    vector<string> v1 = {"hello","world"};
    vector<string> v2 = {"hello"};
    cout << (string("hello") == string("hello")) << endl;
    cout << (v1 == v2);
    return 0;
}