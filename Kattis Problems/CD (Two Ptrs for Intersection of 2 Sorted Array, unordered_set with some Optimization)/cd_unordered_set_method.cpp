//Problem: https://open.kattis.com/problems/cd

#include <bits/stdc++.h>

using namespace std;

int main(){
    // freopen("A.0.in", "r", stdin);
    int N, M; cin >> N >> M;
    while(N != 0 && M != 0){
        unordered_set<int> cd(N > M ? N : M);
        // cd.reserve(N > M ? N : M);
        // cout << cd.bucket_count() << endl;
        int num, count = 0;
        while(N--){
            cin >> num;
            cd.insert(num);
        }
        while(M--){
            cin >> num;
            auto result = cd.insert(num);
            if(!result.second) count++;
        }
        cout << count << endl;
        cin >> N >> M;
    }
    return 0;
}