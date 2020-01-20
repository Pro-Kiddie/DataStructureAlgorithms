//Problem: https://open.kattis.com/problems/competitivearcadebasketball

#include <bits/stdc++.h>

using namespace std;

int main(){
    // freopen("sample02.in", "r", stdin);
    int n, p, m;
    cin >> n >> p >> m; cin.get();
    string name;
    unordered_map<string, int> players(n);
    while(n--){
        cin >> name;
        players[name] = 0;
    }
    bool winner = false;
    unordered_set<string> winners; // Keep track of user who have already won. 
    while(m--){
        cin >> name;
        int score; cin >> score; cin.get();
        players[name] += score;
        if (players[name] >= p && winners.count(name) == 0){ // If winner won already, then every future increase in score will cause his name to print out
            winner = true;
            winners.insert(name);
            cout << name << " wins!\n";
        }
    }
    if(!winner) cout << "No winner!\n";
    return 0;
}