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
vi status;
vi predecessor;
vii back_edges;

void DFS_Cycles(int u){
    status[u] = EXPLORED;
    for(int v : AL[u]){
        if(status[v] == UNVISITED){
            predecessor[v] = u;
            DFS_Cycles(v);
        }
        else if (status[v] == EXPLORED){
            // Backedge detected
            back_edges.push_back({u, v});
        }
    }
    status[u] = VISITED;
}

int main(){
	ios::sync_with_stdio(false); cin.tie(NULL);
    freopen("sample.in", "r", stdin);
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
    status.assign(V, UNVISITED);
    predecessor.assign(V, -1);
    // Identify backedge vertex
    for(int i = 0; i < V; i++){
        if(status[i] == UNVISITED){
            DFS_Cycles(i);
        }
    }
    // Identify all vertices involved in the cycle in each backedge
    // From u all they way back to v using predecessor
    unordered_set<int> cycle_vertices;
    for(auto& p : back_edges){
        int src = p.first;
        int dst = p.second;
        cycle_vertices.insert(src);
        cycle_vertices.insert(dst);
        while(predecessor[src] != dst){
            cycle_vertices.insert(predecessor[src]);
            src = predecessor[src];
        }
    }
    // Debugging
    for(auto p : back_edges) cout << "(" << p.first << "," << p.second << ") ";
    cout << endl;
    for(auto i : predecessor) cout << i << " ";
    cout << endl;
    for(auto i : cycle_vertices) cout << i << " ";
    cout << endl;

    string src;
    while(cin >> src){
        int i = index[src];
        auto itr = cycle_vertices.find(i);
        cout << src << " ";
        itr != cycle_vertices.end() ? cout << "safe\n" : cout << "trapped\n";
    }
     
	return 0;
}