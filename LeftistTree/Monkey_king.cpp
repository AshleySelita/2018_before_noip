#include <cstdio>
#include <cstring>
const int MAXN = 100010;
const int MAXM = 100010;
struct Node {
    int lson, rson;
    Node(): lson(0), rson(0) {}
    void clear() {lson = rson = 0;}
}node[MAXN];
int n, m, u, v;
int dis[MAXN], val[MAXN], fa[MAXN];
inline int find(int x) {
    while(fa[x]) x = fa[x];
    return x;
}
inline void swap(int &x, int &y) {x ^= y ^= x ^= y;}
inline int merge(int u, int v) {
    if(!u || !v) return (u + v);
    if(val[u] < val[v]) swap(u, v);
    int& lson = node[u].lson; int& rson = node[u].rson;
    rson = merge(rson, v);
    fa[rson] = u;
    if(dis[lson] < dis[rson]) swap(lson, rson);
    dis[u] = dis[rson] + 1;
    return u;
}
inline int del(int x) {
    int lson = node[x].lson, rson = node[x].rson;
    fa[lson] = fa[rson] = 0;
    val[x] /= 2; node[x].clear(); dis[x] = 0;
    return merge(lson, rson);
}
inline void work() {
    scanf("%d%d", &u, &v);
    int fu = find(u), fv = find(v);
    if(fu == fv) {printf("-1\n"); return ;}
    int uroot = del(fu), vroot = del(fv);
    uroot = merge(uroot, fu); vroot = merge(vroot, fv);
    merge(uroot, vroot);
    printf("%d\n", val[find(u)]);
    return ;
}
inline void init() {
    memset(node, 0, sizeof node);
    memset(fa, 0, sizeof fa);
    memset(dis, 0, sizeof dis);
    return ;
}
int main() {
    //freopen("F:\\MZQ\\Workspace\\LeftistTree\\monkey.in", "r", stdin);
    //freopen("monkey.out", "w", stdout);
    while(scanf("%d", &n) != EOF) {
        init();
        for (int i = 1; i <= n; ++i)
            scanf("%d", &val[i]);
        scanf("%d", &m);
        for (int i = 1; i <= m; ++i) 
            work();
    }
    return 0;
}