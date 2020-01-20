//Problem: https://nus.kattis.com/problems/greedilyincreasing

#include <bits/stdc++.h>

using namespace std;

int main(){
    // freopen("3.in", "r", stdin);
    int N; cin >> N;
    int cur = 0;
    vector<int> result;
    while(N--){
        int num; cin >> num;
        if(num > cur) {
            result.push_back(num);
            cur = num;
        }
    }
    cout << result.size() << endl;
    for(int& i : result) {
        cout << i << " ";
    }
    return 0;
}