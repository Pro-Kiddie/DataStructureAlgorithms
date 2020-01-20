

#include <bits/stdc++.h>

using namespace std;

enum {VISITED, UNVISITED};
typedef pair<int, int> ii;
typedef vector<ii> vii;
typedef vector<int> vi;

int dr[] = {1, -1, 0, 0}; // Can add 1, -1, -1, 1 for diagonal access
int dc[] = {0, 0, 1, -1}; // Can add 1, -1, 1, -1 for diagonal access
vector<vi> AM;
vector<vi> status;
int H, W;

bool Sense_Draft(int r, int c){
    for(int i = 0; i < 4; i++){
        int rr = r + dr[i];
        int cc = c + dc[i];
        if (rr < 0 || rr >= H) continue;
        if (cc < 0 || cc >= W) continue;
        if(AM[rr][cc] == 'T') return true;
    }
    return false;
}

int DFS_Grid(int r, int c){
    status[r][c] = VISITED;
    if(Sense_Draft(r, c)) return AM[r][c] == 'G' ? 1 : 0;
    if(AM[r][c] == '#') return 0;
    int gold = 0;
    for(int i = 0; i < 4; i++){
        int rr = r + dr[i];
        int cc = c + dc[i];
        if (rr < 0 || rr >= H) continue;
        if (cc < 0 || cc >= W) continue;
        if(status[rr][cc] == UNVISITED){
            gold += DFS_Grid(rr, cc);
        }
    }
    if(AM[r][c] == 'G') gold++;
    return gold;
}

int main(){
	ios::sync_with_stdio(false); cin.tie(NULL);
    // freopen("gold-2.in", "r", stdin);
    cin >> W >> H; cin.get();
    AM.assign(H, vi(W));
    status.assign(H, vi(W));
    int PR, PC;
    for(int i = 0; i < H; i++){
        for(int j = 0; j < W; j++){
            char c; cin >> c;
            AM[i][j] = c;
            if(c == 'P'){
                PC = j;
                PR = i; 
            }
            status[i][j] = UNVISITED;
        }
        cin.get();
    }

    int gold = DFS_Grid(PR, PC);
    cout << gold;
	return 0;
}