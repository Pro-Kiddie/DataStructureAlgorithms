// Problem: https://open.kattis.com/problems/brexit

// Graph Question Template

// Time Limit Exceeded -> Can't figure out what is the bug

#include <bits/stdc++.h>

using namespace std;

typedef pair<int, int> ii;
typedef vector<ii> vii;
typedef vector<int> vi;

enum { LEFT };

int C, P, X, L;
vector<vi> AL;
vi country_status;
bool stay;

void DFS(int u){
    // Check if the country u will leave or not
    int num_neighbours = AL[u].size();
    int count = 0;
    for(auto v : AL[u]){
        if(country_status[v] == LEFT){
            count++;
            if(count * 2 >= num_neighbours){
                country_status[u] = LEFT;
                if(u == X) {
                    stay = false;
                    return;
                }
            }
        }
    }

    // Only propogate (DFS) if country u left -> chain effect 
    // If it does not leave, then its neighbours will definitely not leave
    if(country_status[u] == LEFT){
        for(auto v : AL[u]) {
            if(country_status[v] != LEFT){ // Only DFS back to country which haven't left -> prevent cycle
                DFS(v);
            }
        }
    }
}

int main(){
	ios::sync_with_stdio(false); cin.tie(NULL);
    freopen("sample-4.in", "r", stdin);
    cin >> C >> P >> X >> L;
    X--; L--; // Original 1-based index
    AL.assign(C, vi());
    while(P--){
        int A, B; cin >> A >> B;
        A--; B--;
        AL[A].emplace_back(B);
        AL[B].emplace_back(A);
    }
    stay = true;
    if(X == L) stay = false;
    else{
        country_status.assign(C, -1);
        country_status[L] = LEFT;
        DFS(L);        
    }
    stay ? cout << "stay" : cout << "leave";
	return 0;
}