// Problem: https://open.kattis.com/problems/terraces

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

vector<vi> grid;
vector<vi> status;
int R, C;

int DFS(int r, int c, int height){
    if(grid[r][c] != height) return 0;
    status[r][c] = VISITED;
    int ans = 0;
    for(int i = 0; i < 4; i++){
        int rr = r + dr[i];
        int cc = c + dc[i];
        if(rr >= 0 && rr < R && cc >= 0 && cc < C && status[rr][cc] == UNVISITED){
            ans += DFS(rr, cc, height);
        }
    }
    return ans + 1;
}

bool DFS_flow(int r, int c, int height){
    // cout << "Visited: (" << r << "," << c << ")" << endl;
    if(grid[r][c] < height) return true;
    if(grid[r][c] > height) return false;
    status[r][c] = VISITED;
    bool flow = false;
    for(int i = 0; i < 4; i++){
        int rr = r + dr[i];
        int cc = c + dc[i];
        if(rr >= 0 && rr < R && cc >= 0 && cc < C && status[rr][cc] == UNVISITED){
            // cout << rr << "," << cc << endl;
            flow = flow || DFS_flow(rr, cc, height);
        }
    }
    return flow;
}

int main(){
	ios::sync_with_stdio(false); cin.tie(NULL);
    // freopen("terraces-01-04.in", "r", stdin);
    cin >> C >> R;
    grid.assign(R, vi(C));
    for(int i = 0; i < R; i++){
        for(int j = 0; j < C; j++){
            cin >> grid[i][j];
            // cout << grid[i][j];
        }
        // cout << endl;
    }
    int CC = 0;
    unordered_map<int, int> size;
    unordered_map<int, pair<int, int>> coord;
    status.assign(R, vi(C, UNVISITED));
    for(int i = 0; i < R; i++){
        for(int j = 0; j < C; j++){
            if(status[i][j] == UNVISITED){
                int num = DFS(i, j, grid[i][j]);
                size[CC] = num;
                coord[CC] = {i, j};
                CC++;
            }
        }
    }
    // for(auto& p : size){
    //     cout << "CC: " << p.first << " Size: " << p.second << endl;;
    // }

    int ans = 0;
    for(auto& p : coord){
        status.assign(R, vi(C, UNVISITED));
        bool flow = DFS_flow(p.second.first, p.second.second, grid[p.second.first][p.second.second]);
        if(!flow) ans += size[p.first];
    }

    cout << ans;
	return 0;
}