// Problem: https://nus.kattis.com/problems/shortestpath1

// Graph Question Template

#include <bits/stdc++.h>

using namespace std;

#define INF 1e9

typedef pair<int, int> ii;
typedef tuple<int, int, int> iii;
typedef vector<ii> vii;
typedef vector<int> vi;
typedef long long ll;

enum { UNVISITED,
       EXPLORED,
       VISITED };

int dr[] = {1, -1, 0, 0};  // Can add 1, -1, -1, 1 for diagonal access
int dc[] = {0, 0, 1, -1};  // Can add 1, -1, 1, -1 for diagonal access
//for (int i = 0; i < 4; i++) {
//int rr = r + dr[i]; // Form neighbour coordinates
//int cc = c + dc[i];
//if (rr < 0 || rr >= R) continue;
//if (cc < 0 || cc >= C) continue;
//}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(NULL);
    // freopen("shortestpath1.in", "r", stdin);
    int n, m, q, s;
    while (cin >> n >> m >> q >> s, !(n == 0 && m == 0 && q == 0 && s == 0)) {
        // cout << "hello";
        vector<iii> EL(m);
        for (int i = 0; i < m; i++) {
            int u, v, w;
            cin >> u >> v >> w;
            EL[i] = {u, v, w};
        }

        // for(int i = 0 ; i < m; i++){
        //     auto& edge = EL[i];
        //     cout << get<0>(edge) << "," << get<1>(edge) << "," << get<2>(edge) << endl;
        // }
        vi dist(n, INF);
        dist[s] = 0;

        for (int i = 0; i < n - 1; i++) {
            bool relaxed = false;
            for (auto& edge : EL) {
                int u = get<0>(edge);
                int v = get<1>(edge);
                int w = get<2>(edge);
                if (dist[u] == INF) continue;
                if (dist[v] > dist[u] + w) {
                    dist[v] = dist[u] + w;
                    relaxed = true;
                }
            }
            if (!relaxed) break;
        }

        while (q--) {
            int d;
            cin >> d;
            dist[d] == INF ? cout << "Impossible\n" : cout << dist[d] << "\n";
        }

        cout << "\n";
    }
        return 0;
}