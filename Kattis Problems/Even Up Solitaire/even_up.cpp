//Problem: https://nus.kattis.com/problems/evenup

#include <bits/stdc++.h>

using namespace std;

int main(){
    // freopen("evenup-02.in", "r", stdin);
    int n; cin >> n;
    stack<int> cards;
    while(n--){
        int num; cin >> num;
        if(!cards.empty() && (cards.top() + num) % 2 == 0) cards.pop();
        else cards.push(num);
    }
    cout << cards.size();
    return 0;
}