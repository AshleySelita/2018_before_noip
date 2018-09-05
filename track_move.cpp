#include <algorithm>
#include <cstdio>
#include <cstring>
const int MAXN = 10010;
const int MAXM = 50010;
const int MAXQ = 30010;
const int MAXZ = 100010;
struct EDGE{
    int to, fr, wgh;
}edge[MAXM];
struct TreeEDGE{
    int to, wgh, next;
}treeedge[MAXN << 1];
int n, m, u, v, w, q, top, topt;
int head[MAXN], headt[MAXN], f[MAXN];
int dep[MAXN], fa[MAXN][20], mulmin[MAXN][20];

inline int min(int a, int b) {return (a < b ? a : b);}
inline void swap(int &a, int &b) {a ^= b; b ^= a; a ^= b;}

inline void add_edge(int u, int v, int w) {
    edge[++top].fr = u;
    edge[top].to = v;
    edge[top].wgh = w;

    return ;
}
inline void AddEdge(int u, int v, int w) {
    treeedge[++topt].next = headt[u];
    treeedge[topt].to = v;
    treeedge[topt].wgh = w;
    headt[u] = topt;
    
    treeedge[++topt].next = headt[v];
    treeedge[topt].to = u;
    treeedge[topt].wgh = w;
    headt[v] = topt;

    return ;
}

inline int find(int x) {
    if(f[x] != x) f[x] = find(f[x]);
    return f[x];
}
inline void unionn(int u, int v) {
    int uu = find(u), vv = find(v);
    if(uu != vv) f[uu] = vv;
}

inline void dfs(int now, int bef) {
    dep[now] = dep[bef] + 1;
    fa[now][0] = bef;
    for (int i = 1; i < 20; ++i) {
        fa[now][i] = fa[fa[now][i - 1]][i - 1];
        mulmin[now][i] = 
        min(mulmin[now][i - 1], mulmin[fa[now][i - 1]][i - 1]);
    }
    int tmp(0);
    for (int i = headt[now]; i; i = treeedge[i].next)
        if(!dep[(tmp = treeedge[i].to)]) {
            mulmin[tmp][0] = treeedge[i].wgh;
            dfs(tmp, now);
        }
}
inline void Mul_Lca(int u, int v) {
    if(dep[u] < dep[v]) swap(u, v);
    int ans(0x7fffffff);
    for (int i = 19; i >= 0; --i)
        if(dep[fa[u][i]] >= dep[v]) {
            ans = min(ans, mulmin[u][i]);
            u = fa[u][i];
        }
    if(u == v) {printf("%d\n", ans); return ;}
    for (int i = 19; i >= 0; --i)
        if(fa[u][i] != fa[v][i]) {
            ans = min(ans, min(mulmin[u][i], mulmin[v][i]));
            u = fa[u][i]; v = fa[v][i];
        }
    ans = min(ans, min(mulmin[u][0], mulmin[v][0]));
    printf("%d\n", ans);
    return ;
}

inline bool cmp(EDGE a, EDGE b) {return (a.wgh > b.wgh);}

int main() {
    //freopen("track.in", "r", stdin);
    memset(mulmin, 0x3f, sizeof mulmin);
    scanf("%d%d", &n, &m);
    for (int i = 1; i <= n; ++i) f[i] = i;
    for (int i = 1; i <= m; ++i)
        scanf("%d%d%d", &u, &v, &w), add_edge(u, v, w);
    std::sort(edge + 1, edge + m + 1, cmp);
    /*for (int i = 1; i <= m; ++i)
        printf("%d %d %d\n", edge[i].fr, edge[i].to, edge[i].wgh);*/
    int tot(0), uf(0), vf(0);
    for (int i = 1; i <= m; ++i) {
        u = edge[i].fr; v = edge[i].to; w = edge[i].wgh;
        uf = find(u); vf = find(v);
        if(uf == vf) {continue;}
        AddEdge(u, v, w); unionn(u, v);
        tot++; if(tot == n - 1) {break;}
    }
    for (int i = 1; i <= n; ++i)
        if(!dep[i]) dfs(i, 0);
    scanf("%d", &q);
    for (int i = 1; i <= q; ++i) {
        scanf("%d%d", &u, &v);
        if(find(u) != find(v)) printf("-1\n");
        else Mul_Lca(u, v);
    }
    return 0;
}