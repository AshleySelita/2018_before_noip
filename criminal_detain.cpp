#include <algorithm>
#include <cstdio>
const int MAXN = 20010;
const int MAXM = 100010;
struct EDGE{
    int fr, to, w;
}edge[MAXM];
int n, m, u, v, w, rf1, rf2;
int f[MAXN << 1];

inline int find(int x){
    if(x != f[x]) f[x] = find(f[x]);
    return f[x];
}
inline void unionn(int u, int v) {
    int uu = find(u), vv = find(v);
    if(uu != vv) f[uu] = vv;
    return ;
}

inline bool cmp(EDGE a, EDGE b) {return a.w > b.w;}

int main() {
    //freopen("testdata.in", "r", stdin);
    //freopen("test.out", "w", stdout);
    scanf("%d%d", &n, &m);
    for (int i = 1; i <= n << 1; ++i) f[i] = i;
    for (int i = 1; i <= m; ++i)
        scanf("%d%d%d", &edge[i].fr, &edge[i].to, &edge[i].w);
    std::sort(edge + 1, edge + m + 1, cmp);
    /*for (int i = 1; i <= m; ++i)
        printf("%d %d %d\n", edge[i].fr, edge[i].to, edge[i].w);*/
    for (int i = 1; i <= m; ++i) {
        u = edge[i].fr; v = edge[i].to; w = edge[i].w;
        if(find(u) == find(v)) {printf("%d\n", w); return 0;}
        unionn(u, v + n); unionn(v, u + n);
    }
    printf("%d\n", 0);
    return 0;
}