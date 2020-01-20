//Problem: https://nus.kattis.com/problems/apples

#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

void printGrid(const vector<vector<char>>& grid){
    for(int i = 0; i < grid.size(); ++i){
        for(int j = 0; j < grid[0].size(); ++j){
            cout << grid[i][j];
        }
        cout << endl;
    }
}

vector<vector<char>> transpose(const vector<vector<char>>& grid){
    int R, C;
    R = grid.size();
    C = grid[0].size();
    vector<vector<char>> tGrid(C, vector<char>(R));
    for(int i = 0; i < R; ++i){
        for(int j = 0; j < C; ++j){
            tGrid[j][i] = grid[i][j];
        }
    }
    return tGrid;
}

int main(){
    // freopen("2.in", "r", stdin);
    int R, C; cin >> R >> C;
    vector<vector<char>> grid(R, vector<char>(C));

    // Initalize the grid;
    for(int i = 0; i < R; ++i){
        for(int j = 0; j < C; ++j){
            cin >> grid[i][j];
        }
    }

    // Transpose the grid for processing later
    auto tGrid = transpose(grid);

    // For each Lane, get the obstacles index
    // Later will sort from index 0 to index of 1st obstacle, index of 1st obstacle + 1 to 2nd obstacle  and ...
    // algorithm sort() sort from 1st iterator to 2nd iterator, not including the element pointed by 2nd iterator
    for(auto& lane : tGrid){
        vector<int> obstacles_index;
        // Since will sort from index of (obstacles + 1) to 2nd obstacle, the first index should be -1 which will be 0 when added 1
        obstacles_index.push_back(-1);
        for(int i = 0; i < lane.size(); i++){
            if(lane[i] == '#') obstacles_index.push_back(i);
        }
        // Will sort from last obstacle to end of array, need to push the size of lane to last ele of obstacles_index
        // so lane.begin() + lane.size() makes the iterator point beyond the last ele
        obstacles_index.push_back(lane.size());

        // Sort each lane according to the index in obstacles_index
        // Ascii values: '.' = 46 and 'a' = 97
        for(int i = 0; i < obstacles_index.size() - 1; ++i){
            sort(lane.begin() + obstacles_index[i]+1, lane.begin() + obstacles_index[i + 1]);
        }
    }
    
    // Transpose the grid again
    tGrid = transpose(tGrid);

    // Print the Grid
    printGrid(tGrid);
    return 0;
}