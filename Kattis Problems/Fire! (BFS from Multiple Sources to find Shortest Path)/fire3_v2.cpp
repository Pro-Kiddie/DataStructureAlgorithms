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

    int dist[2][R][C];
    memset(dist, -1, sizeof(dist));
    queue<ii> q[2];
    for (int i = 0; i < R; ++i) {
        for (int j = 0; j < C; ++j) {
            cin >> grid[i][j];
            if (grid[i][j] == 'J') {
                q[0].push({i, j});
                dist[0][i][j] = 0;
                grid[i][j] = '.';
            } else if (grid[i][j] == 'F') { // can be multiple fires
                q[1].push({i, j});
                dist[1][i][j] = 0;
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

    // calculate shortest distance to the edges of grid for from both Joe and Fire(s)
    for (int k = 0; k < 2; ++k) {
        int x, y;
        while (!q[k].empty()) {
            tie(x, y) = q[k].front();
            q[k].pop();
            for (int d = 0; d < 4; ++d) {
                int rr = x + dr[d];
                int cc = y + dc[d];
                // only start BFS into neighbour cells if rr & cc are valid and grid[rr][cc] is '.' and dist[k][rr][cc] is not visited
                if (0 <= rr && rr < R && 0 <= cc && cc < C && grid[rr][cc] == '.' && dist[k][rr][cc] == -1) {
                    dist[k][rr][cc] = 1 + dist[k][x][y];
                    q[k].push({rr, cc});
                }
            }
        }
    }

    int ans = INF;
    for (int i = 0; i < R; ++i) {
        for (int j = 0; j < C; j += C - 1) { // for each row only check the 1st cell and last cell
            // if joe visited there and (fire never visit there or both visited there but joe reached there earlier than fire)
            if (dist[0][i][j] != -1 && (dist[1][i][j] == -1 || dist[0][i][j] < dist[1][i][j]))
                ans = min(ans, dist[0][i][j] + 1);
        }
    }

    for (int j = 0; j < C; ++j) {
        for (int i = 0; i < R; i += R - 1) { // for each column, check only cell in 1st row and last row
            if (dist[0][i][j] != -1 && (dist[1][i][j] == -1 || dist[0][i][j] < dist[1][i][j]))
                ans = min(ans, dist[0][i][j] + 1);
        }
    }

    if (ans == INF)
        printf("IMPOSSIBLE\n");
    else
        printf("%d\n", ans);

    return 0;
} 