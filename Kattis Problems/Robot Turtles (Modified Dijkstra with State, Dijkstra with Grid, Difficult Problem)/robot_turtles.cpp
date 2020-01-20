// Problem: https://open.kattis.com/problems/robotturtles

// Graph Question Template

#include <bits/stdc++.h>

using namespace std;

#define INF 1e9

typedef pair<int, int> ii;
typedef vector<ii> vii;
typedef vector<int> vi;
typedef long long ll;

enum { UNVISITED, EXPLORED, VISITED };
enum { FORWARD, TURN_LEFT, TURN_RIGHT, LASER};

int dr[] = {0, 1, 0, -1}; // R D L U 
int dc[] = {1, 0, -1, 0}; // Must start with R and in clockwise or anti-clockwise direction


// vi pred;

// void printPath(int e){
//     if(pred[e] == -1) {
//         cout << e << " ";
//         return;
//     }
//     printPath(pred[e]);
//     cout << e << " ";
// }

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

// void debug_shortest_path(int V){
//     for(int i = 0; i < V; i++){
//         cout << "Shortest Path to Vertex " << i << ": ";
//         printPath(i);
//         cout << endl;
//     }
// }

struct state{
    int r, c, facing, moves;

    bool operator<(const state& other) const{ // pq by default smaller will be placed at back
        return moves > other.moves; // overloading < operator. When this returns true, placed at back
    }

    bool operator==(const state& other) const{
        return r == other.r && c == other.c && facing == other.facing;
    }
    bool operator!=(const state& other) const{
        return !(*this == other); 
    }
};

int moves[8][8][4];
int pred[8][8][4];

void print_sol(state start, state dst){
    vector<char> path;
    while(dst != start){
        if(pred[dst.r][dst.c][dst.facing] == FORWARD){
            path.push_back('F');
            dst.r -= dr[dst.facing];
            dst.c -= dc[dst.facing];
        }
        else if(pred[dst.r][dst.c][dst.facing] == TURN_RIGHT){
            path.push_back('R');
            dst.facing = (dst.facing + 3) % 4; // Turn left to undo turn right
        }
        else if(pred[dst.r][dst.c][dst.facing] == TURN_LEFT){
            path.push_back('L');
            dst.facing = (dst.facing + 1) % 4;
        }
        else if(pred[dst.r][dst.c][dst.facing] == LASER){
            path.push_back('F');
            path.push_back('X');
            dst.r -= dr[dst.facing];
            dst.c -= dc[dst.facing];
        }
    }
    reverse(path.begin(), path.end());
    for(auto c : path) cout << c;
}

int main(){
	ios::sync_with_stdio(false); cin.tie(NULL);
    // freopen("sample003.in", "r", stdin);
    char grid[8][8];
    int Dr, Dc;
    for(int i = 0; i < 8; i++){
        for(int j = 0; j < 8; j++){
            cin >> grid[i][j];
            if(grid[i][j] == 'D'){
                Dr = i; Dc = j;
                grid[i][j] = '.';
            }
            // cout << grid[i][j];
        }
        cin.get();
        // cout << endl;
    }
    // cout << Dr << " " << Dc << endl;
    memset(moves, -1, sizeof(moves)); // No need to set moves = INF as as long as cell not visited, will be visited and moves will be set
    memset(pred, -1, sizeof(pred));
    priority_queue<state> pq;
    state start = {7,0,0,0}; //r=7, c=0, facing=0, moves=0
    // pq.push({0,0,0,1});
    // pq.push({0,0,0,0});
    // pq.push({0,0,0,2});
    // pq.push({0,0,0,2});
    // while(!pq.empty()){
    //     auto s = pq.top();
    //     cout << s.moves << endl;
    //     pq.pop();
    // }
    pq.push(start); 
    moves[start.r][start.c][start.facing] = 0;
    while(!pq.empty()){
        state u = pq.top(); pq.pop();
        if(moves[u.r][u.c][u.facing] != u.moves) continue;
        // cout << "Visited: (" << u.r << "," << u.c << ") " << "Facing: " << u.facing << endl;
        if(u.r == Dr && u.c == Dc){
            // Destination reached
            print_sol(start, u);
            return 0;
        }

        // Move forward to next cell in the direction it is facing
        int rr = u.r + dr[u.facing];
        int cc = u.c + dc[u.facing];
        if(rr >= 0 && rr < 8 && cc >= 0 && cc < 8 && grid[rr][cc] == '.'){
            if(moves[rr][cc][u.facing] == -1 || moves[rr][cc][u.facing] > u.moves + 1){
                moves[rr][cc][u.facing] = u.moves + 1;
                pred[rr][cc][u.facing] = FORWARD;
                pq.push({rr, cc, u.facing, u.moves + 1});
            }
        }

        // Move forward to next cell but next cell is ICE
        if(rr >= 0 && rr < 8 && cc >= 0 && cc < 8 && grid[rr][cc] == 'I'){
            if(moves[rr][cc][u.facing] == -1 || moves[rr][cc][u.facing] > u.moves + 2){
                moves[rr][cc][u.facing] = u.moves + 2; // Must destroy ice and move forward, hence +2
                pred[rr][cc][u.facing] = LASER;
                pq.push({rr, cc, u.facing, u.moves + 2});
            }
        }

        // In the same cell, can turn left or right. Simulate and push to pq
        // Turn right
        int facing_new = (u.facing + 1) % 4; // 0->1, 1->2, 2->3, (3->4)%4 = 0 // Right -> Down, Down -> Left, Left -> Up, Up -> Right
        if(moves[u.r][u.c][facing_new] == -1 || moves[u.r][u.c][facing_new] > u.moves + 1){
            moves[u.r][u.c][facing_new] = u.moves + 1;
            pred[u.r][u.c][facing_new] = TURN_RIGHT;
            pq.push({u.r, u.c, facing_new, u.moves + 1});
        }

        // Turn Left
        facing_new = (u.facing + 3) % 4;
        if(moves[u.r][u.c][facing_new] == -1 || moves[u.r][u.c][facing_new] > u.moves + 1){
            moves[u.r][u.c][facing_new] = u.moves + 1;
            pred[u.r][u.c][facing_new] = TURN_LEFT;
            pq.push({u.r, u.c, facing_new, u.moves + 1});
        } 
    }

    cout << "no solution";

	return 0;
}