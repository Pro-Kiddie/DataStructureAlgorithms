//Problem: https://nus.kattis.com/sessions/syek8x/problems/2048

#include <array>
#include <iostream>
#include <algorithm>

using namespace std;

const static int SIZE = 4;

array<int, SIZE> slide(const array<int, SIZE>& row) {
    //Tiles slide as far as possible in the chosen direction until they are stopped another tile or the edge
    //Remove all the 0s in the row to slide
    array<int, SIZE> temp = {0};  //Initialize with all 0s
    for (int i = 0, j = 0; i < SIZE; ++i) {
        if (row[i] == 0)
            continue;
        else
            temp[j++] = row[i];
    }

    //Merge if tile and next tile is same
    for (int i = 0; i < SIZE - 1; ++i) {
        if (temp[i] == 0) continue;
        if (temp[i] == temp[i + 1]) {
            temp[i] *= 2;
            temp[i + 1] = 0;
        }
    }

    //Need to slide again as merging introduced 0
    array<int, SIZE> result = {0};
    for (int i = 0, j = 0; i < SIZE; ++i) {
        if (temp[i] == 0)
            continue;
        else
            result[j++] = temp[i];
    }

    return result;
}

int main() {
    //freopen("4.in", "r", stdin);
    array<array<int, SIZE>, SIZE> board;

    for (int i = 0; i < SIZE; ++i) {
        for (int j = 0; j < SIZE; ++j) {
            cin >> board[i][j];
        }
    }

    int direction;
    cin >> direction;

    if (direction == 0) {  // left
        //No need to pass in direction
        //If merge up, just retrieve the 1D array from down to top and pass into merge() which will always combine in left direction
        //Need to copy back the returned array in down to top direction
        for (int i = 0; i < SIZE; ++i) {
            board[i] = slide(board[i]);
        }
    }

    else if (direction == 2){ //right
        for(int i = 0; i < SIZE; ++i){
            reverse(board[i].begin(), board[i].end());
            auto temp = slide(board[i]);
            reverse(temp.begin(), temp.end());
            board[i] = temp;
        }
    }

    else if (direction == 1) {  //up
        array<int, SIZE> temp;
        for (int i = 0; i < SIZE; ++i) { //Transverse columns 
            //Transvers 2D-array from bottom to top
            temp[0] = board[0][i];
            temp[1] = board[1][i];
            temp[2] = board[2][i];
            temp[3] = board[3][i];
            temp = slide(temp);
            board[0][i] = temp[0];
            board[1][i] = temp[1];
            board[2][i] = temp[2];
            board[3][i] = temp[3];
        }
    }

    else if (direction == 3) {  //down
        array<int, SIZE> temp;
        for (int i = 0; i < SIZE; ++i) { 
            //Transvers 2D-array from bottom to top
            temp[0] = board[3][i];
            temp[1] = board[2][i];
            temp[2] = board[1][i];
            temp[3] = board[0][i];
            temp = slide(temp);
            board[3][i] = temp[0];
            board[2][i] = temp[1];
            board[1][i] = temp[2];
            board[0][i] = temp[3];
        }
    }

    //print out the board after slide in direction specified
    for (int i = 0; i < SIZE; ++i) {
        for (int j = 0; j < SIZE; ++j) {
            cout << board[i][j] << " ";
        }
        cout << endl;
    }

    // array<int,SIZE> array = {2,0,0,2};
    // auto result = slide(array);

    // for(int num : result) cout << num << ",";

    return 0;
}