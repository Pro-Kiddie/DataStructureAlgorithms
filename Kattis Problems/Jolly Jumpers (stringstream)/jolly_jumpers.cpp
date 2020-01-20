//Problem: https://open.kattis.com/problems/jollyjumpers
// A sequence of n numbers (n < 3000) is called Jolly Jumper if the absolute values of the differences between 
// the successive elements take on all possible values from 1 through n-1

#include <bits/stdc++.h>

using namespace std;

int main(){
    // freopen("1.in", "r", stdin);
    string line;
    while(getline(cin, line)){
        stringstream iss(line);
        int n; iss >> n;
        vector<bool> diffs(n, false);
        int pre; iss >> pre;
        for(int i = 1; i < n; i++){
            int num; iss >> num;
            unsigned int diff = abs(num - pre);
            // cout << diff << endl;
            pre = num;
            if(diff > n-1) continue;
            else{
                diffs[diff] = true;
            }
        }
        bool jollySeq = true;
        for(int i = 1; i < n; i++){
            jollySeq &= diffs[i];
        }
        cout << (jollySeq ? "Jolly" : "Not jolly") << endl;
    }
    return 0;
}