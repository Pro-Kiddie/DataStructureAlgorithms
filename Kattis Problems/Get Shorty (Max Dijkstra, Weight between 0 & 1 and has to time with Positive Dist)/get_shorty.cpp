// Problem: https://open.kattis.com/problems/getshorty

// Graph Question Template

#include <bits/stdc++.h>

using namespace std;

#define INF 1e9

typedef pair<int, double> id;
typedef vector<id> vid;
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

vi pred;

void printPath(int e){
    if(pred[e] == -1) {
        cout << e << " ";
        return;
    }
    printPath(pred[e]);
    cout << e << " ";
}


void debug(const vector<vid>& AL){
    for(int i = 0; i < AL.size(); i++){
        cout << "Vertex " << i << ": ";
        for(auto p : AL[i]){
            cout << " (" << p.first << "," << p.second << ") ";
        }
        cout << endl;
    }
    cout << endl;
}


void debug_dist(const vector<int>& dist){
    for(int i = 0; i < dist.size(); i++){
        cout << "Shortest distance at Vertex " << i << ": " << dist[i] << endl;
    }
}

void debug_shortest_path(int V){

    // for(int i = 0; i < V; i++){
    //     cout << "Shortest Path to Vertex " << i << ": ";
    //     printPath(i);
    //     cout << endl;
    // }
}


int main(){
	ios::sync_with_stdio(false); cin.tie(NULL);
    // freopen("getshorty.in", "r", stdin);
    int n,m;
    while(cin >> n >> m, n != 0 && m != 0){
        vector<vid> AL(n, vid());
        while(m--){
            int u, v; double f;
            cin >> u >> v >> f;
            AL[u].push_back({v, f});
            AL[v].push_back({u, f});
        }
        // debug(AL);
        vector<double> size(n, 0);
        size[0] = 1;
        priority_queue<pair<double, int>> pq;
        pq.push({1, 0});
        while(!pq.empty()){
            auto s_u = pq.top(); pq.pop();
            double s = s_u.first; int u = s_u.second;
            // cout << "Popped: (" << s << "," << u << ")\n";
            if(size[u] < s) continue;
            for(auto v_f : AL[u]){
                // cout << "Visiting Neighbour: (" << size[v_f.first] << "," << v_f.second << ")" << endl;
                if(size[v_f.first] < s * v_f.second){
                    size[v_f.first] = s * v_f.second;
                    pq.push({size[v_f.first], v_f.first});
                }
            }
        }
        // cout << endl;
        printf("%.4lf\n", size[n-1]);
    }

	return 0;
}