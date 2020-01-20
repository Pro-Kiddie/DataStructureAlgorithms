//Problem: https://open.kattis.com/problems/fire3


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
template <size_t R, size_t C>
void debug_grid(char (&grid)[R][C]){
    for(int i = 0 ; i < R; i++){
            for(int j = 0; j < C; j++){
                cout <<  grid[i][j];
            }
            cout << endl;
        }
}

int main(){
	ios::sync_with_stdio(false); cin.tie(NULL);
    // freopen("2.in", "r", stdin);
    int R, C; cin >> R >> C; cin.get();
    char grid[R][C];
    int Jx, Jy, Fx, Fy;
    for(int i = 0 ; i < R; i++){
        for(int j = 0; j < C; j++){
            cin >> grid[i][j];
            if(grid[i][j] == 'J'){
                Jx = i; Jy = j;
            }
            if(grid[i][j] == 'F'){
                Fx = i; Fy = j;
            }
        }
        cin.get();
    }
    // for(int i = 0 ; i < R; i++){
    //         for(int j = 0; j < C; j++){
    //             cout <<  grid[i][j];
    //         }
    //         cout << endl;
    // }
    vector<vi> F_visited(R, vi(C, UNVISITED));
    vector<vi> J_visited(R, vi(C, UNVISITED));
    F_visited[Fx][Fy] = VISITED;
    J_visited[Jx][Jy] = VISITED;
    queue<pair<int, int>> Fq; Fq.push({Fx, Fy});
    queue<pair<int, int>> Jq; Jq.push({Jx, Jy});
    int layer = -1;
    int fire_srcs = 1;
    int joe_srcs = 1;
    while(true){
        int new_fire_srcs = 0;
        for(int j = 0; j < fire_srcs; j++){
            auto x_y = Fq.front(); Fq.pop();
            for(int i = 0; i < 4; i++){
                int rr = dr[i] + x_y.first;
                int cc = dc[i] + x_y.second;
                if(rr < 0 || rr >= R) continue;
                if(cc < 0 || cc >= C) continue;
                if(grid[rr][cc] == '#') continue;
                if(F_visited[rr][cc] == VISITED) continue;
                F_visited[rr][cc] = VISITED;
                grid[rr][cc] = 'F';
                Fq.push({rr, cc});
                new_fire_srcs++;
            }
        }
        fire_srcs = new_fire_srcs;
        layer++;
        auto x_y = Jq.front(); Jq.pop();
        bool impossible = true;
        bool escaped = false;
        for(int j = 0; j < joe_srcs; j++){
            int new_joe_srcs = 0;
            for(int i = 0; i < 4; i++){
                int rr = dr[i] + x_y.first;
                int cc = dc[i] + x_y.second;
                if(rr < 0 || rr >= R || cc < 0 || cc >= C){
                    layer++;
                    cout << layer;
                    return 0;
                }
                if(grid[rr][cc] == '#' || grid[rr][cc] == 'F') continue;
                if(J_visited[rr][cc] == VISITED) continue;
                if(grid[rr][cc] == '.' || grid[rr][cc] == 'J'){
                    impossible = false;
                    J_visited[rr][cc] = VISITED;
                    Jq.push({rr, cc});
                    new_joe_srcs++;
                }
            }
            joe_srcs = new_joe_srcs;
        }
        if(impossible){
            cout << "IMPOSSIBLE";
            break;
        }
    }
	return 0;
}