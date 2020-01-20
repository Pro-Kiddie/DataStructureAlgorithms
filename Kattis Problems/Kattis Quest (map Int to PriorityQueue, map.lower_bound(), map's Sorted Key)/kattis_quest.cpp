// Problem: https://nus.kattis.com/problems/kattissquest

#include <bits/stdc++.h>

using namespace std;

int main(){
    // freopen("1.in", "r", stdin);
    int N; cin >> N; cin.get();
    map<int, priority_queue<int>> pool;
    while(N--){
        string cmd; cin >> cmd;
        int E, G, X;
        if(cmd == "add"){
            cin >> E >> G; cin.get();
            auto itr = pool.find(E);
            if(itr == pool.end()){
                priority_queue<int> quests;
                quests.push(G);
                pool[E] = quests;
            }
            else{
                itr->second.push(G);
            }
        }
        else if(cmd == "query"){
            cin >> X; cin.get();
            long long earning = 0;
            while(X > 0 && !pool.empty()){
                // Find the correct quests with E equal or just smaller than X
                auto itr = pool.lower_bound(X);
                if(itr == pool.end()) itr--; // No quests has E required equal or bigger than X
                // Can just itr-- to get the smaller E as map's keys are ordered
                else if(itr->first > X && itr != pool.begin()) itr--; // lower_bound is bigger than X & there must be quests with lower E in front
                else if(itr->first > X && itr == pool.begin()) break; // lower_bound is bigger than X and no smaller E quests infront -> No more quests to be cleared
                // Get the quest with the E required but highest G in priority queue
                // cout << itr->first << endl;
                if(!itr->second.empty()){
                    earning += itr->second.top();
                    // Remove the quest
                    itr->second.pop();
                    X -= itr->first;
                }
                // If priority queue is empty after removal of quest, no more quest for this E
                // Remove the key and mapped priority queue
                if(itr->second.empty()){
                    pool.erase(itr);
                }
            }
            cout << earning << endl;
        }
    }
    return 0;
}