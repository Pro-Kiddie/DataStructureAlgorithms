//Problem: https://nus.kattis.com/sessions/syek8x/problems/simpleaddition

#include <iostream>
#include <string>
#include <algorithm>

using namespace std;

int main(){
    //freopen("2.in", "r", stdin);
    string n1, n2; getline(cin, n1); getline(cin, n2);

    //Make sure n2's length is longer or equal to n1
    if (n1.length() > n2.length()) swap(n1, n2); //swap content of variables

    //Reverse the two strings, so smallest digit at the start
    reverse(n1.begin(), n1.end()); 
    reverse(n2.begin(), n2.end());

    string result = "";

    int carry = 0;

    //Add the two numbers digit by digit and set carry accordingly
    for(int i=0; i < n1.length(); ++i){
        int sum = (int)(n1[i] - '0') + (int)(n2[i] - '0') + carry;
        //Push the digit to the result string
        result.push_back((char)(sum % 10 + '0'));
        //Calculate if carry should be set
        carry = sum/10;
    } 

    //Add the rest of the longer number
    for(int i=n1.length(); i < n2.length(); ++i){
        int sum = (int)(n2[i] - '0') + carry;
        result.push_back((char)(sum % 10 + '0'));
        //Should still calculate carry because if first digit is 9 and carry is set from previous for loop last iteration
        carry = sum/10;
    }

    //If two strings same length, 2nd loop will not be executed and carry is set
    if (carry){
        result.push_back((char)(1 + '0'));
    }

    //Reverse the result
    reverse(result.begin(), result.end());

    cout << result << endl;

    return 0;
}