#include <cstdio>
#define lson(x) (x << 1)
#define rson(x) (x << 1 | 1)
const int MAXN = 100010;
const int MAXM = 100010;
struct EDGE{
    int to, next;
}edge[MAXN << 1];
int n, m, u, v, top, tot;
int head[MAXN], dep[MAXN], ltop[MAXN], dfn[MAXN],
    size[MAXN], fa[MAXN], son[MAXN], segtree[MAXN << 2], lazy[MAXN << 2];
char opt[5];
inline void swap(int &x, int &y) {x ^= y ^= x ^= y;}
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
            dfs1(tmp);
            size[now] += size[tmp];
            if(size[tmp] > size[son[now]]) son[now] = tmp;
        }
    return ;
}
inline void dfs2(int now, int top) {
    dfn[now] = ++tot; ltop[now] = top;
    if(!son[now]) return ;
    dfs2(son[now], top);
    int tmp(0);
    for (int i = head[now]; i; i = edge[i].next)
        if((tmp = edge[i].to) != son[now] && tmp != fa[now])
            dfs2(tmp, tmp);
    return ;
}
inline void pushdown(int now, int l, int r) {
    if(!lazy[now]) {return ;} int mid = (l + r) >> 1;
    segtree[lson(now)] += (mid - l + 1) * lazy[now]; lazy[lson(now)] += lazy[now];
    segtree[rson(now)] += (r - mid) * lazy[now]; lazy[rson(now)] += lazy[now];
    lazy[now] = 0;
    return ;
}
inline void update(int now, int l, int r, int L, int R, int val) {
    if(l > R || r < L) return ;
    if(L <= l && r <= R) {
        segtree[now] += (r - l + 1) * val;
        lazy[now] += val; return ;
    }
    pushdown(now, l, r); int mid = (l + r) >> 1;
    update(lson(now), l, mid, L, R, val);
    update(rson(now), mid + 1, r, L, R, val);
    segtree[now] = segtree[lson(now)] + segtree[rson(now)];
    return ;
}
inline int query(int now, int l, int r, int L, int R) {
    if(l > R || r < L) return 0;
    if(L <= l && r <= R) {return segtree[now];}
    pushdown(now, l, r); int mid = (l + r) >> 1;
    return (query(lson(now), l, mid, L, R) + query(rson(now), mid + 1, r, L, R));
}
inline void sp_add() {
    scanf("%d%d", &u, &v);
    while(ltop[u] != ltop[v]) {
        if(dep[ltop[u]] < dep[ltop[v]]) swap(u, v);
        update(1, 1, n, dfn[ltop[u]], dfn[u], 1);
        u = fa[ltop[u]];
    }
    if(dep[u] > dep[v]) swap(u, v);
    update(1, 1, n, dfn[u], dfn[v], 1);
    update(1, 1, n, dfn[u], dfn[u], -1);
    return ;
}
inline void sp_qry() {
    scanf("%d%d", &u, &v); 
    int ans(0), num = dfn[u] > dfn[v] ? dfn[u] : dfn[v];
    ans = query(1, 1, n, num, num);
    printf("%d\n", ans);
    return ;
}
int main() {
    //freopen("Grass.in", "r", stdin);
    scanf("%d%d", &n, &m);
    for (int i = 1; i < n; ++i)
        scanf("%d%d", &u, &v), add_edge(u, v);
    dfs1(1); dfs2(1, 1);
    for (int i = 1; i <= m; ++i) {
        scanf("%s", opt);
        switch(opt[0]) {
            case 'P': {sp_add(); break;}
            case 'Q': {sp_qry(); break;}
        }
    }
    return 0;
}