//Problem: https://nus.kattis.com/sessions/syek8x/problems/anotherbrick

#include <iostream>
using namespace std;

int main(){
    freopen("2.in", "r", stdin);
    int h, w, n;
    cin >> h >> w >> n;
    int laid = 0;
    while (n--){
        int brick;
        cin >> brick;
        laid += brick;

        if (h == 0) {
            break; 
        }
        if(laid > w){
            cout << "NO" << endl;
            return 0;
        }
        else if(laid == w){
            h--;
            laid = 0;
        }
    }

    if (h != 0){
        cout << "NO" << endl;
    }else{
        cout << "YES" << endl;
    }
    return 0;
}