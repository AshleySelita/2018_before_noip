#include <cstdio>
#define lson(x) (x << 1)
#define rson(x) (x << 1 | 1)
const int MAXN = 50010;
struct EDGE {
    int to, next;
}edge[MAXN << 1];
int n, m, u, v, top, tot;
int head[MAXN], dep[MAXN], fa[MAXN], son[MAXN], 
    ltop[MAXN], dfn[MAXN], size[MAXN], segtree[MAXN << 2], lazy[MAXN << 2];
inline void swap(int &x, int &y) {x ^= y ^= x ^= y;}
inline int max(int x, int y) {return x > y ? x : y;}
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
    size[now] = 1; int tmp(0), maxa(0);
    for (int i = head[now]; i; i = edge[i].next)
        if((tmp = edge[i].to) != fa[now]) {
            fa[tmp] = now; dep[tmp] = dep[now] + 1;
            dfs1(tmp);
            size[now] += size[tmp];
            if(size[tmp] > maxa) maxa = size[tmp], son[now] = tmp;
        }
    return ;
}
inline void dfs2(int now, int top) {
    dfn[now] = ++tot; ltop[now] = top;
    if(!son[now]) return ;
    dfs2(son[now], top); int tmp(0);
    for (int i = head[now]; i; i = edge[i].next)
        if((tmp = edge[i].to) != fa[now] && tmp != son[now])
            dfs2(tmp, tmp);
    return ;
}
inline void pushdown(int now) {
    if(!lazy[now]) return ;
    segtree[lson(now)] += lazy[now]; segtree[rson(now)] += lazy[now];
    lazy[lson(now)] += lazy[now]; lazy[rson(now)] += lazy[now];
    lazy[now] = 0;
}
inline void update(int now, int l, int r, int L, int R, int val) {
    if(l > R || r < L) return ;
    if(L <= l && r <= R) {
        segtree[now] += val;
        lazy[now] += val;
        return ;
    }
    pushdown(now);
    int mid = (l + r) >> 1;
    update(lson(now), l, mid, L, R, val);
    update(rson(now), mid + 1, r, L, R, val);
    segtree[now] = max(segtree[lson(now)], segtree[rson(now)]);
    return ;
}
inline int query(int now, int l, int r, int L, int R) {
    if(l > R || r < L) return 0;
    if(L <= l && r <= R) {return segtree[now];}
    pushdown(now);
    int mid = (l + r) >> 1;
    return max(query(lson(now), l, mid, L, R), query(rson(now), mid + 1, r, L, R));
}
inline void sp_add(int u, int v, int val) {
    while(ltop[u] != ltop[v]) {
        if(dep[ltop[u]] < dep[ltop[v]]) swap(u, v);
        update(1, 1, n, dfn[ltop[u]], dfn[u], val);
        u = fa[ltop[u]];
    }
    if(dep[u] > dep[v]) swap(u, v);
    update(1, 1, n, dfn[u], dfn[v], val);
    return ;
}
inline int all_qry() {return (query(1, 1, n, 1, n));}
int main() {
    //freopen("maxflow.in", "r", stdin);
    //freopen("maxflow.out", "w", stdout);
    scanf("%d%d", &n, &m);
    for (int i = 1; i < n; ++i)
        scanf("%d%d", &u, &v), add_edge(u, v);
    dfs1(1); dfs2(1, 1);
    for (int i = 1; i <= m; ++i) {
        scanf("%d%d", &u, &v);
        sp_add(u, v, 1);
        /*for (int i = 1; i <= n; ++i)
            printf("%d ", query(1, 1, n, i, i));
        putchar('\n');*/
    }
    printf("%d\n", all_qry());
    return 0;
}