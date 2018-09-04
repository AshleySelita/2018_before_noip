#include <algorithm>
#include <cstdio>
#include <cstring>
const int MAXN = 210;
const int MAXM = 40010;
const int MAXQ = 50010;
const int INF = 0x3f3f3f3f;
int n, m, u, v, w, q, x, y, t, k;
int map[MAXN][MAXN], fin[MAXN];
int main() {
    memset(map, 0x3f, sizeof map);
    memset(fin, 0x7f, sizeof fin);
    scanf("%d%d", &n, &m);
    for (int i = 0; i < n; ++i)
        scanf("%d", &fin[i]), map[i][i] = 0;
    for (int i = 1; i <= m; ++i)
        scanf("%d%d%d", &u, &v, &w), map[u][v] = map[v][u] = w;
    scanf("%d", &q);
    for (int p = 1; p <= q; ++p) {
        scanf("%d%d%d", &x, &y, &t);
        while(fin[k] <= t) {
            for (int i = 0; i < n; ++i)
                for (int j = 0; j < n; ++j)
                    map[i][j] = std::min(map[i][j], map[i][k] + map[k][j]);
            k++;
        }
        if(fin[x] > t || fin[y] > t || map[x][y] == INF) printf("-1\n");
        else printf("%d\n", map[x][y]);
    }
    return 0;
}