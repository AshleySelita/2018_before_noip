#include <cstdio>
#define lson(x) (x << 1)
#define rson(x) (x << 1 | 1)
const int MAXN = 100010;
const int MAXQ = 100010;
struct EDGE{
    int to, next;
}edge[MAXN << 1];
int n, q, x, top, tot;
int head[MAXN], size[MAXN], fa[MAXN], son[MAXN],
    ltop[MAXN], dfn[MAXN], segtree[MAXN << 2], lazy[MAXN << 2];
char cmd[10];
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
    size[now] = 1;
    int tmp(0), maxa(0);
    for (int i = head[now]; i; i = edge[i].next)
        if((tmp = edge[i].to) != fa[now]) {
            fa[tmp] = now;
            dfs1(tmp);
            size[now] += size[tmp];
            if(size[tmp] > maxa) maxa = size[tmp], son[now] = tmp;
        }
}
inline void dfs2(int now, int top) {
    dfn[now] = ++tot; ltop[now] = top;
    if(!son[now]) return ;
    dfs2(son[now], top); int tmp(0);
    for (int i = head[now]; i; i = edge[i].next)
        if((tmp = edge[i].to) != fa[now] && tmp != son[now])
            dfs2(tmp, tmp);
}
inline void pushdown(int now, int l, int r) {
    if(lazy[now] == -1) return ;
    int mid = (l + r) >> 1;
    segtree[lson(now)] = lazy[now] ? mid - l + 1 : 0; lazy[lson(now)] = lazy[now];
    segtree[rson(now)] = lazy[now] ? r - mid : 0; lazy[rson(now)] = lazy[now];
    lazy[now] = -1;
    return ;
}
inline int update(int now, int l, int r, int L, int R, int val) {
    if(l > R || r < L) return 0;
    if(L <= l && r <= R) {
        int tmp = segtree[now];
        segtree[now] = val ? r - l + 1 : 0;
        lazy[now] = val;
        return tmp;
    }
    pushdown(now, l, r);
    int mid = (l + r) >> 1;
    int lval = update(lson(now), l, mid, L, R, val), 
    rval = update(rson(now), mid + 1, r, L, R, val);
    segtree[now] = segtree[lson(now)] + segtree[rson(now)];
    return (lval + rval);
}
inline void inst(int x) {
    int ans = 0;
    while(ltop[x]) {
        ans += dfn[x] - dfn[ltop[x]] + 1 - update(1, 1, n, dfn[ltop[x]], dfn[x], 1);
        x = fa[ltop[x]];
    }
    ans += dfn[x] - dfn[ltop[x]] + 1 - update(1, 1, n, dfn[ltop[x]], dfn[x], 1);
    printf("%d\n", ans);
}
inline void uninst(int x) {
    printf("%d\n", update(1, 1, n, dfn[x], dfn[x] + size[x] - 1, 0));
    return ;
}
int main() {
    //freopen("testdata.in", "r", stdin);
    //freopen("out.out", "w", stdout);
    scanf("%d", &n);
    for (int i = 1; i < n; ++i)
        scanf("%d", &x), add_edge(i, x);
    dfs1(0); dfs2(0, 0);
    scanf("%d", &q);
    for (int i = 1; i <= q; ++i) {
        scanf("%s%d", cmd, &x);
        if(cmd[0] == 'i') inst(x);
        else uninst(x);
    }
    return 0;
}