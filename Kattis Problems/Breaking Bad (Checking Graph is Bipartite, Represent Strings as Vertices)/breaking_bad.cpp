// Problem: https://open.kattis.com/problems/breakingbad

#include <bits/stdc++.h>

using namespace std;

typedef pair<int, int> ii;
typedef vector<ii> vii;
typedef vector<int> vi;

enum { UNVISITED, VISITED };

bool BFS_Isbipartite(vector<vi>& AL, int src, vi& colour){
    colour[src] = 1;
    queue<int> q; q.push(src);
    while(!q.empty()){
        int u = q.front(); q.pop();
        for(auto v : AL[u]){
            if(colour[v] == -1){
                colour[v] = 1 - colour[u]; 
                q.push(v);
            }
            else if (colour[v] == colour[u]) return false;
        }
    }
    return true;
}

int main(){
	ios::sync_with_stdio(false); cin.tie(NULL);
    // freopen("2.in", "r", stdin);
    int N; cin >> N; cin.get();
    string item;
    unordered_map<string, int> item_index;
    vector<string> items(N);
    for(int i = 0; i < N; i++){
        cin >> item;
        items[i] = item;
        item_index[item] = i;
    }
    vector<vi> AL(N, vi());
    int M; cin >> M; cin.get();
    while(M--){
        string A, B; cin >> A >> B;
        AL[item_index[A]].push_back(item_index[B]);
        AL[item_index[B]].push_back(item_index[A]); // Bidirectional -> undirected
    }

    vi colour(N, -1);
    bool possible = true;
    for(int u = 0; u < N; u++){
        if(colour[u] == -1){
            if(BFS_Isbipartite(AL, u, colour) == false) {
                possible = false;
                break;
            }
        }
    }
    if(!possible) cout << "impossible\n";
    else{
        for(int i = 0; i < N; i++){
            if(colour[i] == 1) cout << items[i] << " ";
        }
        cout << endl;
        for(int i = 0; i < N; i++){
            if(colour[i] == 0) cout << items[i] << " ";
        }
    } 
	return 0;
}