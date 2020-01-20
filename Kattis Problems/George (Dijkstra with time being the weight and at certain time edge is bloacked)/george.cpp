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

// Compare this with v2. Lesson learnt, think harder before coding!
// This version still get WA on 3rd test case. Got corner cases cannot think of.
// Think harder at first, make more observations before coding then will have lesser bug and easier to code.

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
    unordered_map<int, int> g_timing(2*G);
    g_timing[g_route[0]] = 0;
    for(int i = 1; i < g_route.size(); i++){
        int u = g_route[i-1]; int v = g_route[i];
        int timing;
        for(auto& p : AL[u]){
            if(p.first == v) timing = p.second;
        }
        g_timing[v] = g_timing[u] + timing;
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
            bool g_reached_u = g_timing.find(u) != g_timing.end(); // if george reached u
            bool g_reached_v = g_timing.find(v) != g_timing.end(); // if george reached v
            
            if(g_reached_u && g_reached_v){ // traveling an edge that George travels too
                int g_u_t = g_timing[u]; int g_v_t = g_timing[v];
                if(g_u_t > g_v_t){ // George travels from v to u
                    if(t < g_u_t && t >= g_v_t){ // reached u and want to go v but George still travilng from v to u
                        int wait_t = g_u_t - t;
                        int new_t = t + wait_t + w;
                        if(l_timing[v] > new_t){
                            l_timing[v] = new_t;
                            pq.push({new_t, v});
                        }
                    }
                    else{ // reached u and George already finished travelling from v to u
                        if(l_timing[v] > t + w){
                            l_timing[v] = t + w;
                            pq.push({l_timing[v], v});
                        }
                    }
                }
                else{ // George travels from u to v
                    if(t >= g_u_t && t < g_v_t){ // reached u and wants to go v but George still traveling from u to v
                        int wait_t = g_v_t - t;
                        int new_t = t + wait_t + w;
                        if(l_timing[v] > new_t){
                            l_timing[v] = new_t;
                            pq.push({new_t, v});
                        }
                    }
                    else{ // reached u and want to go v and George already finished travelling from u to v
                        if(l_timing[v] > t + w){
                            l_timing[v] = t + w;
                            pq.push({l_timing[v], v});
                        }
                    }
                }
            }
            else{ // travelling an edge that George did not travel
                if(l_timing[v] > t + w){
                    l_timing[v] = t + w;
                    pq.push({l_timing[v], v});
                }
            }
        }
    }
    cout << l_timing[B] - K;
	return 0;
}