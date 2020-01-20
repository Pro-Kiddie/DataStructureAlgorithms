// Problem: https://nus.kattis.com/problems/10kindsofpeople

// Users of binary have to stay in the zones marked with a zero. 
// Users of decimal have to stay in the zones marked with a one.
// Figure out if it is possible for either type of person to get between various locations of interest
    // A binary person (0) can move to its neighbour grid if the neighbour is a binary zone
    // Same as a decimal person (1)
    // DFS
        // Set the global flag to true if grid is end point and return
        // return if grid is different from what yourself is 

// People can move north, south, east or west, but cannot move diagonally
// Output binary if a binary user can start from location r1,c1 and move to location r2,c2. 
// Output decimal if a decimal user can move between the two locations. 
// Otherwise, output neither.

#include <bits/stdc++.h>

using namespace std;

#define INF 1e9

typedef pair<int, int> ii;
typedef vector<ii> vii;
typedef vector<int> vi;

enum { UNVISITED, VISITED };

int dr[] = {1, -1, 0, 0}; // Can add 1, -1, -1, 1 for diagonal access
int dc[] = {0, 0, 1, -1}; // Can add 1, -1, 1, -1 for diagonal access

vector<vector<char>> grid;
vector<vi> visited;
int R, C;
int sr, sc, er, ec;
bool reached;

void dfs(int sr, int sc, char person){
    visited[sr][sc] = VISITED;
    if (grid[sr][sc] != person) return;
    if (sr == er && sc == ec){
        reached = true;
        return;
    }
    for (int i = 0; i < 4; i++) {
        int rr = sr + dr[i]; // Form neighbour coordinates
        int cc = sc + dc[i];
        if (rr < 0 || rr >= R) continue;
        if (cc < 0 || cc >= C) continue;
        if (visited[rr][cc] == VISITED) continue;
        dfs(rr, cc, person); 
    }
}

int main(){
	ios::sync_with_stdio(false); cin.tie(NULL);
    // freopen("sample-00.in", "r", stdin);
    cin >> R >> C;
    grid.assign(R, vector<char>(C));
    visited.assign(R, vi(C, UNVISITED));
    for(int i = 0; i < R; i++){
        for(int j = 0; j < C; j++){
            char c; cin >> c;
            grid[i][j] = c;
        }
        cin.get();
    }
    int n; cin >> n;
    while(n--){
        cin >> sr >> sc >> er >> ec;
        sr--; sc--; er--; ec--;
        bool either = false;
        reached = false;
        dfs(sr, sc, '0');
        if(reached){
            cout << "binary\n";
            either = true;
        }
        reached = false;
        visited = vector<vi>(R, vi(C, UNVISITED));
        dfs(sr, sc, '1');
        if(reached){
            cout << "decimal\n";
            either = true;
        }
        if(!either) cout << "neither\n";
    }

	return 0;
}