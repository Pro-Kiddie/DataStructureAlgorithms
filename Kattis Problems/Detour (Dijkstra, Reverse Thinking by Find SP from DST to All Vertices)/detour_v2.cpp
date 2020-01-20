// Problem: https://nus.kattis.com/problems/detour

// might have chosen a route such that, at no intersection, the bus goes in the direction that is pointed to by the signs
// figure out whether there exists a bus route that satisfies this requirement
// A traffic sign pointing in the direction of the shortest route to Amsterdam is placed at every intersection
// there is a unique optimal route to Amsterdam from every intersection. -> only 1 shortest path from every intersection

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
vi status;
vector<vii> AL;
set<ii> banned_edges;
vi path;

void dfs(int u){
    status[u] = VISITED;
    for(auto v_w : AL[u]){
        if(status[v_w.first] == VISITED) continue;
        if(banned_edges.find({u, v_w.first}) != banned_edges.end()) continue;
        dfs(v_w.first);
        path[v_w.first] = u;
    }
}

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

void debug_dist(const vector<ll>& dist){
    for(int i = 0; i < dist.size(); i++){
        cout << "Shortest distance at Vertex " << i << ": " << dist[i] << endl;
    }
}


int main(){
	ios::sync_with_stdio(false); cin.tie(NULL);
    // freopen("sample-1.in", "r", stdin);
    int n, m; cin >> n >> m;
    AL.assign(n, vii());
    while(m--){
        int a, b, d; cin >> a >> b >> d;
        AL[a].push_back({b, d});
        AL[b].push_back({a, d});
    }
    // debug(AL);
    vector<ll> dist(n, INF);
    dist[1] = 0; // instead of finding shortest distance from every intersection to 1, reverse thinking, find shortest distance from 1 to every other
    // n*(logV(V+E)) reduced to logV(V+E)
    set<pair<ll, ll>> pq;
    for(int i = 0; i < n; i++) pq.insert({dist[i], i});
    pred.assign(n, -1);
    while(!pq.empty()){
        auto d_u = *pq.begin(); pq.erase(pq.begin());
        ll d = d_u.first; ll u = d_u.second;
        for(auto v_w : AL[u]){
            if(dist[v_w.first] > d + v_w.second){
                pq.erase(pq.find({dist[v_w.first], v_w.first}));
                dist[v_w.first] = d + v_w.second;
                pq.insert({dist[v_w.first], v_w.first});
                pred[v_w.first] = u;
            }
        }
    }
    // debug_dist(dist);
    // for(auto i : pred) cout << i << " ";
    // for(int i = 0; i < n; i++){
    //     cout << "Shortest Path to Vertex " << i << ": ";
    //     printPath(i);
    //     cout << endl;
    // }
    
    for(int i = 0; i < n; i++){
        int dst = i;
        while(dst != -1){
            if(pred[dst] == -1) break;
            banned_edges.insert({dst, pred[dst]});
            // banned_edges.insert({pred[dst], dst});
            dst = pred[dst];
        }
    }
    // for(auto p : banned_edges){
    //     cout << "(" << p.first << "," << p.second << ") ";
    // }

    status.assign(n, UNVISITED);
    path.assign(n, -1);
    dfs(0);

    if(status[1] == UNVISITED) cout << "impossible";
    else {
        deque<int> ans;
        int dst = 1;
        while(dst != -1){
            ans.push_front(dst);
            dst = path[dst];
        }
        cout << ans.size() << " ";
        for(auto i : ans) cout << i << " ";
    }

	return 0;
}