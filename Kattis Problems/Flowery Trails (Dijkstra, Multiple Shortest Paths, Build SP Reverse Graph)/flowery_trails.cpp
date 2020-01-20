// Problem: https://open.kattis.com/problems/flowerytrails

#include <bits/stdc++.h>

using namespace std;

#define INF 1e9

typedef pair<int, int> ii;
typedef vector<ii> vii;
typedef vector<int> vi;
typedef long long ll;

enum { UNVISITED, EXPLORED, VISITED };

int dr[] = {1, -1, 0, 0}; // Can add 1, -1, -1, 1 for diagonal access
int dc[] = {0, 0, 1, -1}; // Can add 1, -1, 1, -1 for diagonal access
//for (int i = 0; i < 4; i++) {
     //int rr = r + dr[i]; // Form neighbour coordinates
     //int cc = c + dc[i];
     //if (rr < 0 || rr >= R) continue;
     //if (cc < 0 || cc >= C) continue;
//}

void debug(const vector<vii>& AL){
    for(int i = 0; i < AL.size(); i++){
        cout << "Vertex " << i << ": ";
        for(auto p : AL[i]){
            cout << " (" << p.first << "," << p.second << ") ";
        }
        cout << endl;
    }
}


// void printPath(int e){
//     if(pred[e] == -1) {
//         cout << e << " ";
//         return;
//     }
//     printPath(pred[e]);
//     cout << e << " ";
// }

int main(){
	ios::sync_with_stdio(false); cin.tie(NULL);
    // freopen("test01.in", "r", stdin);
    int P, T; cin >> P >> T;
    vector<vii> AL(P, vii());
    while(T--){
        int p1, p2, l; cin >> p1 >> p2 >> l;
        AL[p1].push_back({p2, l});
        AL[p2].push_back({p1, l});
    }
    // debug(AL);
    vector<ll> dist(P, INF);
    dist[0] = 0;
    priority_queue<ii, vii, greater<ii>> pq;
    pq.push({0, 0});
    // vi pred(P, -1); 
    vector<vii> pred; // Now a vertex can have more than 1 parent as there can be more than 1 shortest path
    pred.assign(P, vii());
    while(!pq.empty()){
        auto d_u = pq.top(); pq.pop();
        int d = d_u.first; int u = d_u.second;
        if(dist[u] < d) continue; // outdated {dist, u} pairs due to lazy deletion
        for(auto v_w : AL[u]){
            if(dist[v_w.first] > d + v_w.second){
                dist[v_w.first] = d + v_w.second;
                pq.push({dist[v_w.first], v_w.first});
                pred[v_w.first].clear(); // clear the previous predcessors as a shorter path is found
                pred[v_w.first].push_back({u, v_w.second});
            }
            else if(dist[v_w.first] == d + v_w.second){ // another shortest path found
                pred[v_w.first].push_back({u, v_w.second});
            }
        } 
    }
    // cout << dist[P-1] << endl;
    // printPath(P-1);
    // debug(pred); 
    // Print out the pred. It is like a directed graph by itself!!!
    // It is the reverse graph of all shortest paths from all vertices back tos ource vertex 0.
    // Different shortest paths from all vertices (including vertex P-1) to vertex 0
    // Draw it out to visualize
    // Use an BFS to only traverse along the shortest paths to add the distance
    ll ans = 0;
    queue<int> q;
    q.push(P-1);
    vi visited(P, UNVISITED);
    visited[P-1] = VISITED;
    while(!q.empty()){
        int u = q.front(); q.pop();
        // cout << "Visited: " << u << endl;
        for(auto& p_w : pred[u]){
            ans += p_w.second;
            if(visited[p_w.first] == UNVISITED){
                visited[p_w.first] = VISITED;
                q.push(p_w.first);
            }
        }
    }
    cout << ans * 2 << endl;
	return 0;
}