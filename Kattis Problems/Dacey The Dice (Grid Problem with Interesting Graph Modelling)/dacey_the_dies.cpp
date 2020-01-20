// Problem: https://nus.kattis.com/problems/daceydice

// Keys:
// Dacey starts at one of the N2 locations with 1 dot at the top and 2 dots facing right, 6 dots at the bottom, 5 dots facing left, 4 dots facing upwards, and 3 dots facing downwards.
// door will only open when Dacey is standing on top of the door with the side with five dots facing downwards
// wicked gigantic magnet
// Dacey the Dice can only move by rolling over, which changes both Dacey’s position and orientation. 
// For example, if Dacey has 1 dot at the top and 2 dots facing left, and rolls right to the adjacent location, Dacey will afterwards have 1 dot facing right and 2 dots at the top

// Solution Logic:
// Start DFS with the starting orientation (5 facing left)
    // We only care about the orientation of 5, where it is facing after each roll to neighour cells
// The dice visited the a cell with 1 orientation does not mean cannot visit the same cell with another orientation
    // Cannot simply mark the grid (x,y) as visited but mark (x, y, orientation as visited)
    // Just make sure do not revisit the same cell with same orientation
// Return DFS when the cell content is 'H' and orientation is bottom
// Also returns when all possible rolls to neighbour cells with different orientation are done
// After generating the r, c for neighbours, before actually DFS into the cell, must check 
    // r & c within grid
    // Cell content is not '*'
    // The cell is not visited with same orientation before

// Graph Question Template

#include <bits/stdc++.h>

using namespace std;

typedef pair<int, int> ii;
typedef vector<ii> vii;
typedef vector<int> vi;

enum { TOP, BOTTOM, LEFT, RIGHT, FRONT, BACK };

int N;
set<tuple<int, int, int>> visited;
vector<vector<char>> AM;
bool safe;

int move_right(int orient){
    switch(orient){
        case TOP: return RIGHT;
        case LEFT: return TOP;
        case RIGHT: return BOTTOM;
        case BOTTOM: return LEFT;
        default: return orient;
    }
}

int move_left(int orient){
    switch(orient){
        case TOP: return LEFT;
        case LEFT: return BOTTOM;
        case RIGHT: return TOP;
        case BOTTOM: return RIGHT;
        default: return orient;
    }
}

int move_up(int orient){
    switch(orient){
        case TOP: return FRONT;
        case BACK: return TOP;
        case FRONT: return BOTTOM;
        case BOTTOM: return BACK;
        default: return orient;
    }
}

int move_down(int orient){
    switch(orient){
        case TOP: return BACK;
        case BACK: return BOTTOM;
        case FRONT: return TOP;
        case BOTTOM: return FRONT;
        default: return orient;
    }
}

bool is_valid_cell(int r, int c, int orient){
    if (r < 0 || r >= N || c < 0 || c >= N) return false;
    if (AM[r][c] == '*') return false;
    if (visited.find({r, c, orient}) != visited.end()) return false;
    return true;
    // return (r >= 0 && r < N && c >= 0 && c < N && AM[r][c] != '*' && visited.find({r, c, orient}) == visited.end());
}

void DFS_ROLL_ORIENTATION(int r, int c, int orient){
    if(AM[r][c] == 'H' && orient == BOTTOM){
        safe = true;
        return;
    }
    // Standard DFS, mark this cell with this orentation as visited
    visited.insert({r, c, orient});
    // Visit neighbours
    int rr, cc, new_orient;
    // Move right
    rr = r; cc = c + 1;
    new_orient = move_right(orient);
    if(is_valid_cell(rr, cc, new_orient)) DFS_ROLL_ORIENTATION(rr, cc, new_orient);
    // Move left
    rr = r; cc = c - 1;
    new_orient = move_left(orient);
    if(is_valid_cell(rr, cc, new_orient)) DFS_ROLL_ORIENTATION(rr, cc, new_orient); 
    // Move up
    rr = r - 1; cc = c;
    new_orient = move_up(orient);
    if(is_valid_cell(rr, cc, new_orient)) DFS_ROLL_ORIENTATION(rr, cc, new_orient);
    // Move down
    rr = r + 1; cc = c;
    new_orient = move_down(orient);
    if(is_valid_cell(rr, cc, new_orient)) DFS_ROLL_ORIENTATION(rr, cc, new_orient);
}

int main(){
	ios::sync_with_stdio(false); cin.tie(NULL);
    // freopen("daceydice-01.in", "r", stdin);
    int TC; cin >> TC;
    while(TC--){
        cin >> N; cin.get();
        visited.clear();
        AM.clear();
        AM.assign(N, vector<char>(N));
        int SR, SC;
        safe = false;
        for(int i = 0 ; i < N; i++){
            for(int j = 0; j < N; j++){
                cin >> AM[i][j];
                if(AM[i][j] == 'S'){
                    SR = i; SC = j;
                }
            }
            cin.get();
        }
        
        // for(int i = 0 ; i < N; i++){
        //         for(int j = 0; j < N; j++){
        //             cout << AM[i][j];
        //         }
        //         cout << endl;
        // } 

        DFS_ROLL_ORIENTATION(SR, SC, LEFT);
        safe ? cout << "Yes" : cout << "No";
        cout << "\n";
    }
	return 0;
}
