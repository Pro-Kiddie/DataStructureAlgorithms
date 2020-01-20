// Problem: https://open.kattis.com/problems/gold

// KEYS:
// If the player stands next to (i.e., immediately up, down, left, or right of) one or more traps, she will “sense a draft” 
// but will not know from what direction the draft comes, or how many traps she’s near.
// How much gold can a player get playing with an optimal strategy and always being sure that the square she walked into was safe
    // She stops walking to any neighbour cell if she "sense a draft"
    // BFS
        // Everytime a new cell is from queue, check its neighbours if equal to 'T'
        // If equal to 'T' then does not add any neighbour to queue becuase it is not safe anymore
        // otherwise if equal to '.' or 'G', add to queue

#include <bits/stdc++.h>

using namespace std;

enum {VISITED, UNVISITED};

int main(){
	ios::sync_with_stdio(false); cin.tie(NULL);
    // freopen("gold-1.in", "r", stdin);
    int W, H; cin >> W >> H; cin.get();
    char AM[H][W];
    int PR, PC;
    int status[H][W];
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
    // debug(AM);
    // for(int i = 0; i < H; i++){
    //     for (int j = 0; j < W; j++){
    //         cout << AM[i][j] << " ";
    //     }
    //     cout << endl;
    // }

    queue<pair<int, int>> q;
    q.push({PR, PC});
    int gold = 0;
    while(!q.empty()){
        auto [r, c] = q.front(); q.pop();
        
        if(status[r][c] == VISITED) continue; // If dont put it here, there will be double visiting and cause double counting of G
        status[r][c] = VISITED;
        // cout << "visited: " << r << "," << c << endl; 
        // Printing out the visited nodes very useful for debugging of graph traversal. Each node should only be visited once

        if(AM[r][c] == 'G') gold++;

        bool safe = true;
        // Explore neighbours
        int dr[] = {1, -1, 0, 0}; // Can add 1, -1, -1, 1 for diagonal access
        int dc[] = {0, 0, 1, -1}; // Can add 1, -1, 1, -1 for diagonal access
        for (int i = 0; i < 4; i++) {
            int rr = r + dr[i]; // Form neighbour coordinates
            int cc = c + dc[i];
            if (rr < 0 || rr >= H) continue;
            if (cc < 0 || cc >= W) continue;
            if(AM[rr][cc] == 'T') safe = false;
        }

        if(safe){
            for (int i = 0; i < 4; i++) {
                int rr = r + dr[i]; // Form neighbour coordinates
                int cc = c + dc[i];
                if (rr < 0 || rr >= H) continue;
                if (cc < 0 || cc >= W) continue;
                // if(status[rr][cc] == VISITED) continue;
                if(AM[rr][cc] == 'G' || AM[rr][cc] == '.') q.push({rr, cc});
            }
        }
        
    }
    cout << gold;
	return 0;
}