//Problem: https://nus.kattis.com/problems/speedlimit

#include <iostream>

using namespace std;

int main(){
    //freopen("sample.in","r",stdin);
    int n;
    while (cin >> n){
        if (n == -1) break;
        int total_time = 0, total_mile = 0;
        while(n--){
            int speed, time;
            cin >> speed >> time;
            total_mile += (speed * (time - total_time));
            total_time = time;
        }
        cout << total_mile << " miles" << endl;
    }
    return 0;
}