// Problem: https://nus.kattis.com/problems/runningmom

// Approach 1: Detecting cycles
// Guarantee that the MoM can keep running for as long as might be necessary -> Graph should contains cycle
// Make sure our MoM never gets stuck in a city from which there is no escape
// There is an escape from some location if there is an infinitely long sequence of cities the MoM could fly to making one flight each day


// Approach 2: Detecting vertices with zero out-degree
// Zero out degree must be an dead end
// Start with vertex with zero out-degree and bfs from there
// Only push to queue if neighbour has zero out-degree after minusing
// https://github.com/mpfeifer1/Kattis/blob/master/runningmom.cpp


#include <bits/stdc++.h>

using namespace std;

typedef pair<int, int> ii;
typedef vector<ii> vii;
typedef vector<int> vi;

enum { UNVISITED, EXPLORED, VISITED };

vector<vi> AL;
unordered_set<int> visited; // Stores all the visited node for DFS starting from a particular src

bool DFS_Cycles(int u){
    visited.insert(u);
    for(auto v : AL[u]){
        // if a neighbour node is visited along the DFS path, that means part of cycle
        if(visited.find(v) != visited.end()) return true;
        else{
            visited.insert(v);
            // Not visited yet, DFS to that neighbour
           if(DFS_Cycles(v)) return true;
            // If DFS reach dead_end (no cycle) then it will return false
            // Must remove all the vertices along the path to dead end, so DFS can continue
           else visited.erase(v); 
        }
    }
    return false; // No cycle
}

int main(){
	ios::sync_with_stdio(false); cin.tie(NULL);
    // freopen("sample.in", "r", stdin);
    unordered_map<string, int> index;
    int n, V = 0; cin >> n; cin.get();
    for(int i = 0; i < n; i++){
        string u; cin >> u;
        string v; cin >> v;
        auto itr_src = index.find(u);
        auto itr_dst = index.find(v);
        if(itr_src == index.end() && itr_dst == index.end()){
            AL.push_back(vi());
            index[u] = V++;
            AL.push_back(vi());
            index[v] = V++;
            AL[index[u]].push_back(index[v]);
        }
        else if(itr_src == index.end() && itr_dst != index.end()){
            AL.push_back(vi());
            index[u] = V++;
            AL[index[u]].push_back(itr_dst->second);
        }
        else if(itr_src != index.end() && itr_dst == index.end()){
            AL.push_back(vi());
            index[v] = V++;
            AL[index[u]].push_back(index[v]);
        }
        else if(itr_src != index.end() && itr_dst != index.end()){
            AL[index[u]].push_back(index[v]);
        }
    }
    string src;
    while(cin >> src){
        int i = index[src];
        visited.clear(); // Clear for visited nodes for previous src
        cout << src << " ";
        if(DFS_Cycles(i)){
            cout << "safe";
        }else{
            cout << "trapped";
        }
        cout << endl;
    }
     
	return 0;
}