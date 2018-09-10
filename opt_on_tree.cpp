#include <cstdio>
#define lson(x) (x << 1)
#define rson(x) (x << 1 | 1)
typedef long long ll;
const int MAXN = 100010;
const int MAXM = 100010;
struct EDGE{
    int to, next;
}edge[MAXN << 1];
int n, m, u, v, opt, x, a, top, tot;
int head[MAXN], dfn[MAXN], dep[MAXN], ltop[MAXN],
    fa[MAXN], son[MAXN], size[MAXN], st[MAXN], link[MAXN];
ll segtree[MAXN << 2], lazy[MAXN << 2];
inline void add_edge(int u, int v) {
    edge[++top].to = v;
    edge[top].next = head[u];
    head[u] = top;

    edge[++top].to = u;
    edge[top].next = head[v];
    head[v] = top;

    return ;
}
inline void dfs1(int now) {
    size[now] = 1; int tmp(0);
    for (int i = head[now]; i; i = edge[i].next)
        if((tmp = edge[i].to) != fa[now]) {
            fa[tmp] = now; dep[tmp] = dep[now] + 1;
            dfs1(tmp); size[now] += size[tmp];
            if(size[tmp] > size[son[now]]) son[now] = tmp;
        }
    return ;
}
inline void dfs2(int now, int top) {
    dfn[now] = ++tot; link[tot] = now; ltop[now] = top;
    if(!son[now]) {return ;}
    dfs2(son[now], top); int tmp(0);
    for (int i = head[now]; i; i = edge[i].next)
        if((tmp = edge[i].to) != son[now] && tmp != fa[now])
            dfs2(tmp, tmp);
    return ;
}
inline void bulid(int now, int l, int r) {
    if(l == r) {segtree[now] = st[link[l]]; return ;}
    int mid = (l + r) >> 1;
    bulid(lson(now), l, mid); bulid(son(now), mid + 1, r);
    segtree[now] = segtree[lson(now)] + segtree[rson(now)];
    return ;
}
int main() {
    scanf("%d%d", &n, &m);
    for (int i = 1; i <= n; ++i) scanf("%d", &st[i]);
    for (int i = 1; i < n; ++i)
        scanf("%d%d", &u, &v), add_edge(u, v);
    dfs1(1); dfs2(1, 1); build(1, 1, n);
    for (int i = 1; i <= m; ++i) {
        scanf("%d", &opt);
        switch(opt){
            case 1:{op_add();}
            case 2:{st_add();}
            case 3:{tr_qry();}
        }
    }
    return 0;
}