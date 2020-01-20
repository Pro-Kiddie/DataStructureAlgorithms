//Problem: https://nus.kattis.com/problems/joinstrings

#include <iostream>
#include <vector>
#include <string>
#include <list>

using namespace std;

int main(){
    //freopen("3.in","r",stdin);
    int n; cin >> n;
    vector<list<string>> strings(n);
    for(list<string>& l : strings){
        string line; cin >> line;
        l.push_back(line);
    }
    // for(auto i : strings){
    //     for(auto j : i){
    //         cout << j << endl;
    //     }
    // }
    if (n == 1){ //(1 ≤ N ≤ 10^5) -> When n is 1, there will be 0 operations, the below for loop will not be executed 
        cout << strings[0].front();
    }
    for(int i = 0; i < n-1; i++){
        int a, b;
        cin >> a >> b;
        a--; b--; //convert 1-based indexing to 0-based indexing
        strings[a].splice(strings[a].end(), strings[b]); //joining two lists by making tail pointer of 1 list pointing at the head of another
        //splice() has time complexity of O(1) -> http://www.cplusplus.com/reference/list/list/splice/
        //strings[b] list now becomes empty
        if (i == n-2){
            for(string& s : strings[a]){
                cout << s;
            }
        }
    }
    return 0;
}

// #include <bits/stdc++.h>
// using namespace std;

// int main() { -> Time limit exceeded
//   ios::sync_with_stdio(false); cin.tie(NULL);
//   int N; cin >> N; cin.get();
//   vector<string> S(N); // [0..N-1]
//   for (int i = 0; i < N; ++i) { // O(N)
//     string Si; getline(cin, Si);
//     S[i] = Si;
//   }
//   --N;
//   int a = 0, b;
//   while (N--) { // O(N-1?) = O(N) -> total O(N^2)
//     cin >> a >> b; --a; --b; // go to 0-based indexing, O(1)
//     S[a] = S[a]+S[b]; // is this O(1)? 
//     // Need to create a larger string
//     // Copy S[a] & S[b] into the larger string
//     // Hence O(N)
//     //S[b] = ""; // actually not necessary, O(1)
//   }
//   cout << S[a] << endl;
//   return 0;
// }
