//Problem: https://open.kattis.com/problems/oddmanout

#include <bits/stdc++.h>

using namespace std;

int main(){
    // freopen("1.in", "r", stdin);
    int N; cin >> N;
    for(int i = 1 ; i <= N; i++){
        int G; cin >> G;
        unordered_set<unsigned int> guests(G);
        while(G--){
            unsigned int C; cin >> C;
            auto itr = guests.find(C);
            // Cannot find -> insert
            if(itr == guests.end()) guests.insert(C);
            // Found -> Erase
            else guests.erase(itr);
        }
        printf("Case #%d: ", i);
        // The left over C in guests will be the odd one out
        auto itr = guests.begin();
        for(; itr != guests.end(); itr++){
            cout << *itr << endl;
        }

    }
    return 0;
}