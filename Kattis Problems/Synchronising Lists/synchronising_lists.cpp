//Problem: https://nus.kattis.com/problems/synchronizinglists

#include <bits/stdc++.h>

using namespace std;

int main(){
    // freopen("sample.in", "r", stdin);
    int n; cin >> n;
    while(n != 0){
        vector<int> list1(n);
        unordered_map<int, int> index;
        for(int i = 0; i < n; ++i){
            int num; cin >> num;
            list1[i] = num;
            index[num] = i;
        }
        vector<int> list2(n);
        for(auto& i : list2) cin >> i;
        sort(list1.begin(), list1.end());
        sort(list2.begin(), list2.end());
        vector<int> result(n);
        for(int i = 0; i < n; i++){
            result[index[list1[i]]] = list2[i];
        }
        for(int& i : result) cout << i << endl;
        cout << endl;
        cin >> n;
    }
    return 0;
}