//Problem: https://nus.kattis.com/problems/server

#include <bits/stdc++.h>

using namespace std;

int main(){
    // freopen("server-02.in", "r", stdin);
    int n; cin >> n;
    int T; cin >> T;
    int sum = 0;
    int i = 0;
    for(; i < n; i++){
        int t; cin >> t;
        sum += t;
        if(sum > T) break;
    }
    cout << i;
    return 0;
}