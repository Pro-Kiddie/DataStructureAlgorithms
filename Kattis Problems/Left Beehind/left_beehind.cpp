//Problem: https://nus.kattis.com/problems/leftbeehind

#include <iostream>

using namespace std;

int main(){
    // freopen("test0.in","r",stdin);
    int x, y;
    while(cin >> x >> y){
        if (x == 0 && y == 0) break;
        else if((x + y) == 13) cout << "Never speak again." << endl;
        else if(x > y) cout << "To the convention." << endl;
        else if(x < y) cout << "Left beehind." << endl;
        else cout << "Undecided." << endl; //x == y
    }
    return 0;
}