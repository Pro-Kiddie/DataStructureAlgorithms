//Problem: https://open.kattis.com/problems/cd

#include <bits/stdc++.h>

using namespace std;

int main(){
    // freopen("A.0.in", "r", stdin);
    int N, M;
    cin >> N >> M;
    while(N != 0 && M != 0){
        vector<int> jack(N); 
        vector<int> jill(M);
        for(int& i : jack) cin >> i;
        for(int& i : jill) cin >> i;
        // for(int& i : jill) cout << i << " "; cout << endl;
        int count = 0;
        // Two pointers method to find intersection of 2 sorted array
        int i = 0, j = 0;
        while(i < N && j < M){
            if(jack[i] == jill[j]) {
                count++;
                i++; j++;
            }
            else{
                if(jack[i] < jill[j]) i++;
                else j++;
            }
        }
        cout << count << endl;
        cin >> N >> M;
    }
    return 0;
}