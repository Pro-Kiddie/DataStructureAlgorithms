//Problem: https://nus.kattis.com/problems/bubbletea

#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

void printVec(const vector<int>& v){
    for(auto i : v){
        cout << i << " ";
    }
    cout << endl;
}

int main(){
    //freopen("1.in", "r", stdin);
    int N; cin >> N;
    vector<int> teas(N);
    //teas.reserve(N);
    for(int& i : teas){
        cin >> i;
    }
    //printVec(teas);
    int M; cin >> M;
    vector<int> toppings(M);
    for (int& i : toppings){
        cin >> i;
    }
    vector<int> cheapest_prices(N);
    for(int i = 0; i < N; i++){
        int teaPrice = teas[i];
        int T; cin >> T;
        vector<int> prices(T);
        for(int& t : prices){
            int index; cin >> index; index--; //0-based index
            t = teaPrice + toppings[index];
        }
        cheapest_prices[i] = *min_element(prices.begin(), prices.end());
    }
    //Better option of finding the cheapest price of each tea
    // ll best = (ll) 2 << 60; Very large number
    // for(ll i = 0; i < n; i++) {
    //     ll p;
    //     cin >> p;

    //     for(ll j = 0; j < p; j++) {
    //         ll temp;
    //         cin >> temp;

    //         best = min(best, teas[i] + toppings[temp-1]);
    //     }
    // }
    int cheapest_tea = *min_element(cheapest_prices.begin(), cheapest_prices.end());
    unsigned int money; cin >> money;
    int ans = ( money/cheapest_tea - 1 );
    //Cound be 0 - 1 = -1
    ans = max(ans, 0);
    cout << ans;

    return 0;
}