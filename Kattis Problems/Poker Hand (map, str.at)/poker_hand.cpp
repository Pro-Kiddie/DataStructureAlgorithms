//Problem: https://nus.kattis.com/problems/pokerhand

#include <iostream>
#include <string>
#include <map>

using namespace std;

int main(){
    // freopen("3.in","r",stdin);
    int i = 5;
    map<char,int> cards;
    while(i--){
        string card; cin >> card;
        char c = card.at(0);
        if (cards.count(c) == 0){
            cards[c] = 0;
        }
        cards[c] += 1;
    }
    int cur_max = 0;
    for(auto itr = cards.begin(); itr != cards.end(); itr++){
        if(itr->second > cur_max) cur_max = itr->second;
    }

    cout << cur_max << endl;

    return 0;
}