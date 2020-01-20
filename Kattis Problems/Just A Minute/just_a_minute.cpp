//Problem: https://nus.kattis.com/problems/justaminute

#include <iostream>

using namespace std;

int main(){
    // freopen("justaminute.02.in","r",stdin);
    int n; cin >> n;
    int sum_min = 0, sum_sl_sec = 0;
    while(n--){
        int m; cin >> m;
        int s; cin >> s;
        sum_min += m;
        sum_sl_sec += s;
    }
    //Avg length of an SL minute
    //Total no of seconds waited / 60s = Total minutes waited
    //SL display sum_min
    //Avg length of SL min = total minutes / sum_min

    double result = ((double)sum_sl_sec/60)/sum_min;
    cout << fixed;
    cout.precision(9);
    if (result > 1) cout << result << endl;
    else cout << "measurement error" << endl;

    return 0;
}