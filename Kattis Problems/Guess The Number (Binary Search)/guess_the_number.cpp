//Problem: https://nus.kattis.com/problems/guess

#include <bits/stdc++.h>

using namespace std;

int main(){
    bool guessed = false;
    string response;
    int low = 0, high = 1001;
    do{
        int mid = (low + high) / 2;
        cout << mid << "\n"; cout << flush;
        cin >> response;
        if(response == "correct") guessed = true;
        else if (response == "lower") high = mid - 1;
        else if (response == "higher") low = mid + 1;
    }while(!guessed);
}