// Problem: https://nus.kattis.com/problems/texassummers

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

long long weight(const ii& src, const ii& spot){ // weight is calculated on the fly using sqrt((x1-x2)^ + (y1-y2)^2)
    int x = spot.first - src.first;
    int y = spot.second - src.second;
    return x*x + y*y; 
}

int main(){
	ios::sync_with_stdio(false); cin.tie(NULL);
    // freopen("samp3.in", "r", stdin);
    int n; cin >> n;
    n += 2;
    vii spots(n); // in the grid, every shady spot is reachable to every other shady spot
    for(int i = 0; i < n; i++){
        int x, y; cin >> x >> y;
        spots[i] = {x, y};
    }
    
    // for(auto p : spots){
    //     cout << "Distance of spot (" << p.first << "," << p.second << ") from src: " << weight(spots[n-2], p) << endl;
    // }

    vector<ll> dist(n, INF);
    dist[n-2] = 0;
    priority_queue<pair<ll, int>, vector<pair<ll, int>>, greater<pair<ll, int>>> pq;
    pq.push({weight(spots[n-2], spots[n-2]), n-2});
    pred.assign(n, -1);
    while(!pq.empty()){ // ultimately is finding the shortest distance between domitary and classroom while using as much shady spots as possible
        auto d_u = pq.top(); pq.pop();
        ll d = d_u.first; int u = d_u.second;
        if(dist[u] < d) continue;
        for(int v = 0; v < n; v++){ 
            if(dist[v] > d + weight(spots[u], spots[v])){
                dist[v] = d + weight(spots[u], spots[v]);
                pq.push({dist[v], v}); // must use modified dijkstra as the nearest shady spot popped from pq's best dist might not be finalized 
                pred[v] = u;
            }
        }
    }
    // printPath(n-1);
    deque<int> path;
    int dst = pred[n-1];
    // cout << pred[3] << endl;
    while(pred[dst] != -1){
        path.push_front(dst);
        dst = pred[dst];
    }
    if(path.size() == 0) cout << "-";
    else for(auto i : path) cout << i << endl;
	return 0;
}