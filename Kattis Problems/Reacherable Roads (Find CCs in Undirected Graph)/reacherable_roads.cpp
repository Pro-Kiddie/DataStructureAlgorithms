//Problem: https://nus.kattis.com/problems/reachableroads

#include <bits/stdc++.h>

using namespace std;

typedef pair<int, int> ii;
typedef vector<ii> vii;
typedef vector<int> vi;

enum { UNVISITED, VISITED };

vector<vi> AL;
vi status;

void DFS(int u){
    status[u] = VISITED;
    for(auto v : AL[u]){
        if(status[v] == UNVISITED){
            DFS(v);
        }
    }
}

int main(){
    // freopen("sample.in", "r", stdin);
    int n; cin >> n;
    while(n--){
        int m; cin >> m;
        AL.assign(m, vi());
        status.assign(m, UNVISITED);
        int r; cin >> r;
        for(int i = 0; i < r; i++){
            int u, v; cin >> u >> v;
            AL[u].push_back(v);
            AL[v].push_back(u); // ALL ROADS ARE BIDIRECTIONAL -> Wrong answer without this line
            // If not added edge (v, u) -> a lot of few edges and becomes a directed graph -> much more Connected Components
        }
        int numCC = 0;
        for(int i = 0; i < m; i++){
            if(status[i] == UNVISITED){
                DFS(i);
                numCC++;
            }
        }
        cout << numCC - 1 << '\n';
    }
    return 0;
}