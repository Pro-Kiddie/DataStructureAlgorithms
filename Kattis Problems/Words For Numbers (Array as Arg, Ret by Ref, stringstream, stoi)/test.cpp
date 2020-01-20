#include <iostream>
#include <string>

using namespace std;

void test(const string& num){
    cout << stoi(num) << endl;
}

int main(){
    string s = "Hello World";
    s[1] = 'o';
    cout << s << endl;
    return 0;
}