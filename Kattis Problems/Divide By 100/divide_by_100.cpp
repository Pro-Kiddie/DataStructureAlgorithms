//Problem: https://nus.kattis.com/problems/divideby100

#include <iostream>

using namespace std;

int main(){
    // freopen("divideby100-01.in","r",stdin);
    int n, m; // where 1≤N -> N can be very large
    cin >> n >> m;
    cout.precision(13);
    cout << (n/(double)m);
    return 0;
}