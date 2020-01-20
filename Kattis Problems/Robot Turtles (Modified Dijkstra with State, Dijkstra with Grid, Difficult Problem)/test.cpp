#include <iostream>
#include <iomanip>
#include <string>
#include <sstream>
#include <fstream>
#include <cassert>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <cmath>
#include <algorithm>
#include <utility>
#include <vector>
#include <queue>
#include <map>
#include <set>
#include <unordered_map>
#include <unordered_set>
#include <bitset>
#include <complex>

using namespace std;

using ll = long long;
using ld = long double;
using pii = pair<int, int>;

constexpr int dx[] = {0, 1, 0, -1};
constexpr int dy[] = {1, 0, -1, 0};

struct state {
    int x, y, d, dist;

    bool operator<(const state& other) const {
        return other.dist <= dist;
    }

    bool operator==(const state& other) const {
        return x == other.x and y == other.y and d == other.d;
    }
};

char grid[10][10];
int dist[10][10][4];
int previous[10][10][4];

void print_sol(state start, state fin) {
    string ret;
    state cur = fin;
    while (!(cur == start)) {
        if (previous[cur.x][cur.y][cur.d] == 0) {
            ret.push_back('F');
            cur.x -= dx[cur.d];
            cur.y -= dy[cur.d];
        } else if (previous[cur.x][cur.y][cur.d] == 1) {
            ret.push_back('R');
            cur.d = (cur.d + 3) & 3;
        } else if (previous[cur.x][cur.y][cur.d] == 2) {
            ret.push_back('L');
            cur.d = (cur.d + 1) & 3;
        } else {
            ret.push_back('F');
            ret.push_back('X');
            cur.x -= dx[cur.d];
            cur.y -= dy[cur.d];
        }
    }

    reverse(begin(ret), end(ret));
    printf("%s\n", ret.c_str());
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(0); cout.tie(0);
    freopen("sample004.in", "r", stdin);
    int gx, gy;
    for (int i = 0; i < 8; ++i) {
        scanf("%s", grid[i]);
        for (int j = 0; j < 8; ++j) {
            if (grid[i][j] == 'D') {
                gx = i;
                gy = j;
                grid[i][j] = '.';
            }
        }
    }

    memset(previous, -1, sizeof(previous));

    state start {7, 0, 0, 0};
    priority_queue<state> pq;
    pq.push(start);
    memset(dist, -1, sizeof(dist));
    memset(previous, -1, sizeof(previous));
    dist[start.x][start.y][start.d] = 0;

    while (!pq.empty()) {
        state cur = pq.top();
        pq.pop();

        if (dist[cur.x][cur.y][cur.d] != cur.dist)
            continue;

        if (cur.x == gx and cur.y == gy) {
            print_sol(start, cur);
            return 0;
        }

        // forward
        int nx = cur.x + dx[cur.d];
        int ny = cur.y + dy[cur.d];
        if (0 <= nx and nx < 8 and 0 <= ny and ny < 8 and grid[nx][ny] == '.') {
            int new_dist = cur.dist + 1;
            if (dist[nx][ny][cur.d] == -1 or new_dist < dist[nx][ny][cur.d]) {
                dist[nx][ny][cur.d] = new_dist;
                previous[nx][ny][cur.d] = 0;
                pq.push({nx, ny, cur.d, new_dist});
            }
        }

        // left
        int nd = (cur.d + 1) & 3;
        if (dist[cur.x][cur.y][nd] == -1 or cur.dist + 1 < dist[cur.x][cur.y][nd]) {
            dist[cur.x][cur.y][nd] = cur.dist + 1;
            previous[cur.x][cur.y][nd] = 1;
            pq.push({cur.x, cur.y, nd, cur.dist + 1});
        }

        // right
        nd = (cur.d + 3) & 3;
        if (dist[cur.x][cur.y][nd] == -1 or cur.dist + 1 < dist[cur.x][cur.y][nd]) {
            dist[cur.x][cur.y][nd] = cur.dist + 1;
            previous[cur.x][cur.y][nd] = 2;
            pq.push({cur.x, cur.y, nd, cur.dist + 1});
        }

        // ice
        if (0 <= nx and nx < 8 and 0 <= ny and ny < 8 and grid[nx][ny] == 'I') {
            int new_dist = cur.dist + 2;
            if (dist[nx][ny][cur.d] == -1 or new_dist < dist[nx][ny][cur.d]) {
                dist[nx][ny][cur.d] = new_dist;
                previous[nx][ny][cur.d] = 3;
                pq.push({nx, ny, cur.d, new_dist});
            }
        }
    }

    printf("%s\n", "no solution");

    return 0;
}