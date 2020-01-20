//Problem: https://nus.kattis.com/problems/autori

#include <iostream>
#include <string>
#include <sstream>

using namespace std;

int main(){
    //freopen("autori.3.in","r",stdin);
    string line;
    cin >> line; //cin read in tokens until delimiter which default is whitespaces (including space, spaces, tab, \n)
    //getline() default delimiter is \n

    stringstream iss(line);
    string name;
    while(getline(iss, name, '-')){ //O(N); or more specifically O(100) as maximum 100 characters
    //read until '-' stop and continue
        cout << name[0];
    }
    return 0;
