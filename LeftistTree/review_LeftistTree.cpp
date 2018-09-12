#include <cstdio>
const int MAXN = 100010;
const int MAXM = 100010;
struct Node{
    int lson, rson;
    void clear() {lson = rson = 0;}
}node[MAXN];
int n, m, x, y, opt;
int fa[MAXN], val[MAXN], dis[MAXN];
bool vis[MAXN];
inline void swap(int &a, int &b) {a ^= b ^= a ^= b;}
inline int find(int x) {
    while(fa[x]) x = fa[x];
    return x;
}
int merge(int u, int v) {
    if(!u || !v) return (u + v);
    if(val[u] > val[v] || ((val[u] == val[v]) && u > v)) swap(u, v);
    int& lson = node[u].lson; int& rson = node[u].rson;
    rson = merge(rson, v); fa[rson] = u;
    if(dis[lson] < dis[rson]) swap(lson, rson);
    dis[u] = dis[rson] + 1;
    return u;
}
inline void del(int now) {
    int lson = node[now].lson, rson = node[now].rson;
    vis[now] = true; val[now] = -1; node[now].clear();
    fa[lson] = fa[rson] = 0;
    merge(lson, rson);
}
inline void p_union() {
    scanf("%d%d", &x, &y);
    if(vis[x] || vis[y]) return ;
    int fx = find(x), fy = find(y);
    if(fx == fy) return ;
    merge(fx, fy);
    return ; 
}
inline void p_remov() {
    scanf("%d", &x);
    if(vis[x]) {printf("%d\n", -1); return ;}
    int fx = find(x); printf("%d\n", val[fx]);
    del(fx); return ;
}
int main() {
    scanf("%d%d", &n, &m);
    for (int i = 1; i <= n; ++i) scanf("%d", &val[i]);
    for (int i = 1; i <= m; ++i) {
        scanf("%d", &opt);
        switch(opt) {
            case 1: {p_union(); break;}
            case 2: {p_remov(); break;}
        }
    }
    return 0;
}