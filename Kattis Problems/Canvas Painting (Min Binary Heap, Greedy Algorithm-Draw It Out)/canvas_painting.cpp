//Problem: https://open.kattis.com/problems/canvas

#include <bits/stdc++.h>

using namespace std;
typedef long long ll;

int main(){
    // freopen("sample.in", "r", stdin);
    int T; cin >> T;
    while(T--){
        int N; cin >> N;
        priority_queue<ll, vector<ll>, greater<ll>> canvasses;
        while(N--){
            ll s; cin >> s;
            canvasses.push(s);
        }

        ll minInk = 0;
        if(canvasses.size() == 1) {}//minInk = canvasses.top(); Wrong! if only 1 canvas no ink is required to paint it to have distinct colour!!!
        else{
            while(canvasses.size() != 1){
                ll a = canvasses.top(); canvasses.pop();
                ll b = canvasses.top(); canvasses.pop();
                minInk += (a + b);
                canvasses.push((a + b));
            }
        }
        cout << minInk << endl;
    }
    return 0;
}