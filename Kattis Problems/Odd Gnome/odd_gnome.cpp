//Problem: https://nus.kattis.com/problems/oddgnome

#include <iostream>
#include <vector>

using namespace std;

int main(){
    // freopen("sample01.in", "r", stdin);
    int n; cin >> n; cin.get();
    while(n--){
        int index=1, g, pre, cur;
        cin >> g; g--;
        cin >> pre;
        bool found = false;
        while(g--){
            index++;
            cin >> cur;
            if(cur != (pre+1) && !found) {
                cout << index << endl;
                found = true;
            }
            pre = cur;
        }
    }
    return 0;
}

// int main() {
//     //freopen("sample01.in", "r", stdin);
//     int n;
//     cin >> n;
//     cin.get();  //consume '\n'
//     while (n--) {
//         int g;
//         cin >> g;
//         vector<int> gnomes(g);
//         for (int& i : gnomes) {
//             cin >> i;
//         }
//         for (int i = 0; i < g - 1; i++) {
//             if (gnomes[i + 1] != (gnomes[i] + 1)) {
//                 cout << i + 1 + 1 << endl;
//                 break;
//             }
//         }
//     }
//     return 0;
// }