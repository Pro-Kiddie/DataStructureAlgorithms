//Matric number:  
//Full name:  
//Lab group number:  
//Lab group TA:  

// Graph Question Template

#include <bits/stdc++.h>

using namespace std;

typedef pair<int, int> ii;
typedef vector<ii> vii;
typedef vector<int> vi;

enum { STAY, LEFT };

int main(){
	ios::sync_with_stdio(false); cin.tie(NULL);
    // freopen("sample-2.in", "r", stdin);
    int C, P, X, L;
    cin >> C >> P >> X >> L;
    X--; L--;
    vector<vi> AL(C, vi());
    vi country_status(C, STAY);
    vi num_neighbour(C, 0);
    vi neighbour_left(C, 0);
    while(P--){
        int A, B; cin >> A >> B;
        A--; B--;

        AL[A].emplace_back(B);
        neighbour_left[A]++;
        num_neighbour[A]++;

        AL[B].emplace_back(A);
        neighbour_left[B]++;
        num_neighbour[B]++;
    }
    // BFS -> Setup Source
    // Only source neighbours will be affected
    country_status[L] = LEFT;
    queue<int> q;
    for(auto v : AL[L]){
        q.push(v);
        neighbour_left[v]--;
    }
    while(!q.empty()){
        int u = q.front(); 
        q.pop();
        if(country_status[u] == LEFT) continue; // Ensure left country is not being visited again -> its neighbours will not enqueue again -> infinite loop
        if (neighbour_left[u] * 2 <= num_neighbour[u]){
            country_status[u] = LEFT;
            for(auto v : AL[u]){
                neighbour_left[v]--;
                q.push(v);
            }
        }
    }
    (country_status[X] == LEFT) ? cout << "leave" : cout << "stay";
	return 0;
}