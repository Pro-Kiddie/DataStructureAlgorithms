//Problem: https://nus.kattis.com/problems/vote

#include <iostream>

using namespace std;

int main(){
    freopen("vote-01.in","r", stdin);
    int t; cin >> t;
    while(t--){
        int n; cin >> n;
        int cur_max; cin >> cur_max;
        int cur_max_index = 1;
        int sum = cur_max, vote, pre_vote = cur_max;
        bool no_winner = true;
        for(int i = 2; i <= n; i++){
            cin >> vote;
            sum += vote;
            if (vote > cur_max) {
                cur_max = vote;
                cur_max_index = i;
            }
            if (vote != pre_vote) no_winner = false;
            pre_vote = vote;
        }
        if (no_winner) cout << "no winner";
        else if ((cur_max/(double)sum) > 0.5) cout << "majority winner " << cur_max_index;
        else cout << "minority winner " << cur_max_index;
        cout << endl;
    }

    return 0;
}