// Problem: https://nus.kattis.com/problems/islands3

// Each grid square is either land (denoted as ‘L’), water (denoted as ‘W’), or covered by clouds (denoted as ‘C’). 
// Clouds mean that the surface could either be land or water; you cannot tell.
// An island is a region of land where every grid cell in the island is connected to every other by some path
// and every leg of the path only goes up, down, left or right
    // Lands connected diagonally is not an island.

// determine the minimum number of islands 

// Assume all Cs are land
// Loop through the grid and for all unvisited L, start dfs
    // in DFS, only propogate DFS if cell is not visited, is not W


#include <bits/stdc++.h>

using namespace std;

#define INF 1e9

typedef pair<int, int> ii;
typedef vector<ii> vii;
typedef vector<int> vi;

enum { UNVISITED, VISITED };

int dr[] = {1, -1, 0, 0}; // Can add 1, -1, -1, 1 for diagonal access
int dc[] = {0, 0, 1, -1}; // Can add 1, -1, 1, -1 for diagonal access
//for (int i = 0; i < 4; i++) {
     //int rr = r + dr[i]; // Form neighbour coordinates
     //int cc = c + dc[i];
     //if (rr < 0 || rr >= R) continue;
     //if (cc < 0 || cc >= C) continue;
//}

vector<vector<char>> grid;
vector<vi> visited;
int R, C;

void dfs(int r, int c){
    visited[r][c] = VISITED;
    for (int i = 0; i < 4; i++) {
        int rr = r + dr[i]; // Form neighbour coordinates
        int cc = c + dc[i];
        if (rr < 0 || rr >= R) continue;
        if (cc < 0 || cc >= C) continue;
        if (visited[rr][cc] == VISITED) continue;
        if (grid[rr][cc] == 'W') continue;
        dfs(rr, cc);
    }
}

int main(){
	ios::sync_with_stdio(false); cin.tie(NULL);
    // freopen("Islands-0002.in", "r", stdin);
    cin >> R >> C; cin.get();
    grid.assign(R, vector<char>(C));
    visited.assign(R, vector<int>(C, UNVISITED));

    for(int i = 0; i < R; i++){
        for(int j = 0; j < C; j++){
            char c; cin >> c;
            grid[i][j] = c;
        }
        cin.get();
    }

    // for(int i = 0; i < R; i++){
    //     for(int j = 0; j < C; j++){
    //         cout << grid[i][j] << " ";
    //     }
    //     cout << endl;
    // }

    int islands = 0;
    for(int i = 0; i < R; i++){
        for(int j = 0; j < C; j++){
            if(visited[i][j] == UNVISITED && grid[i][j] == 'L'){
                dfs(i, j);
                islands++;
            }
        }
    }
    cout << islands;
	return 0;
}