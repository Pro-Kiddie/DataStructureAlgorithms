// Problem: https://nus.kattis.com/problems/knightjump

// Graph Question Template

#include <bits/stdc++.h>

using namespace std;

#define INF 1e9

typedef pair<int, int> ii;
typedef vector<ii> vii;
typedef vector<int> vi;
typedef long long ll;

enum { UNVISITED, EXPLORED, VISITED };

int dr[] = {2,2,-2,-2,1,1,-1,-1}; 
int dc[] = {1,-1,1,-1,2,-2,2,-2}; 
//for (int i = 0; i < 4; i++) {
     //int rr = r + dr[i]; // Form neighbour coordinates
     //int cc = c + dc[i];
     //if (rr < 0 || rr >= R) continue;
     //if (cc < 0 || cc >= C) continue;
//}


int main(){
	ios::sync_with_stdio(false); cin.tie(NULL);
    // freopen("2.in", "r", stdin);
    int N; cin >> N; cin.get();
    char board[100][100];
    memset(board, 0, sizeof(board));
    int kr, kc;
    for(int i = 0; i < N; i++){
        for (int j = 0; j < N; j++){
            cin >> board[i][j];
            if(board[i][j] == 'K'){
                kr = i;
                kc = j;
            }
        }
        cin.get();
    }

    // for(int i = 0; i < N; i++){
    //     for (int j = 0; j < N; j++){
    //         cout << board[i][j];
    //     }
    //     cout << endl;
    // }

    int dist[N][N];
    memset(dist, -1, sizeof(dist)); // -1 means unvisited, 0 means source and the rest means the no of steps from source
    dist[kr][kc] = 0;
    queue<ii> q; q.push({kr,kc});
    while(!q.empty()){
        auto& coord = q.front(); q.pop();
        int r = coord.first;
        int c = coord.second;
        // Visit neighbours
        for(int i = 0; i < 8; i++){
            int rr = r + dr[i];
            int cc = c + dc[i];
            if(rr < 0 || rr >= N || cc < 0 || cc >= N) continue;
            if(board[rr][cc] == '#') continue;
            if(dist[rr][cc] != -1) continue;
            dist[rr][cc] = dist[r][c] + 1;
            q.push({rr, cc});
        }
    }

    dist[0][0] == -1 ? cout << -1 : cout << dist[0][0]; 

	return 0;
}