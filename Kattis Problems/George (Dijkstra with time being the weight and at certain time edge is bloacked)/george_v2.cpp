// Problem: https://open.kattis.com/problems/george

// Graph Question Template

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

vi pred;

void printPath(int e){
    if(pred[e] == -1) {
        cout << e << " ";
        return;
    }
    printPath(pred[e]);
    cout << e << " ";
}

void debug(const vector<vii>& AL){
    for(int i = 0; i < AL.size(); i++){
        cout << "Vertex " << i << ": ";
        for(auto p : AL[i]){
            cout << " (" << p.first << "," << p.second << ") ";
        }
        cout << endl;
    }
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
    // freopen("george.2.in", "r", stdin);
    int N, M; cin >> N >> M;
    vector<vii> AL(N, vii());
    int A, B, K, G; cin >> A >> B >> K >> G;
    A--; B--; //1-based indexing
    vi g_route(G);
    for(int& u : g_route) {
        cin >> u;
        u--;
    }
    while(M--){
        int A, B, L; cin >> A >> B >> L;
        A--; B--;
        AL[A].push_back({B, L});
        AL[B].push_back({A, L});
    }
    // debug(AL);
    // for(int& u : g_route) cout << u << " ";
    map<ii, ii> g_timing;
    vi times(G); times[0] = 0;
    for (int i = 0; i + 1 < G; ++i) {
        for (auto& e : AL[g_route[i]]) {
            if (e.first == g_route[i + 1]) {
                times[i + 1] = times[i] + e.second;
                g_timing[{g_route[i], g_route[i + 1]}] = {times[i], times[i + 1]};
                g_timing[{g_route[i + 1], g_route[i]}] = {times[i], times[i + 1]};
                break;
            }
        }
    }
    // for(auto& p : g_timing){
    //     cout << "At Vertex: " << p.first << ", George reaches there at time: " << p.second << endl;
    // } 
    vi l_timing(N, INF); l_timing[A] = K;
    priority_queue<ii, vii, greater<ii>> pq;
    pq.push({K, A});
    while(!pq.empty()){
        auto t_u = pq.top(); pq.pop();
        int t = t_u.first; int u = t_u.second;
        if(l_timing[u] != t) continue;
        for(auto v_w : AL[u]){
            int v, w; tie(v, w) = v_w;
            int time = t + w;
            if(g_timing.find({u,v}) != g_timing.end()){ // George travelled this edge
                if (t >= g_timing[{u,v}].first){
                    time = max(time, g_timing[{u,v}].second + w);
                }
            }
            if(time < l_timing[v]){
                l_timing[v] = time;
                pq.push({l_timing[v], v});
            }
        }
    }
    cout << l_timing[B] - K;
	return 0;
}