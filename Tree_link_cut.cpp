#include <cstdio>
const int MAXN = 100010;
const int MAXM = 100010;
struct EDGE{
    int to, next;
}edge[MAXN << 1];
int n, m, root, mod, opt, tot, top, x, y, z;
int beg[MAXN], dep[MAXN], dfn[MAXN], size[MAXN], 
    fa[MAXN], son[MAXN], ltop[MAXN], head[MAXN];
inline void add_edge(int u, int v) {
    edge[++top].to = v;
    edge[top].next = head[u];
    head[u] = top;

    edge[++top].to = u;
    edge[top].next = head[v];
    head[v] = top;

    return ;
}
inline void swap(int &a, int &b) {a ^= b ^= a ^= b;}
namespace DFS{
    inline void dfs_num(int now) {
        size[now] = 1; int tmp(0);
        for (int i = head[now]; i; i = edge[i].next)
            if((tmp = edge[i].to) != fa[now]) {
                fa[tmp] = now;
                dfs_num(tmp);
                size[now] += size[tmp];
                if(size[tmp] > size[son[now]]) son[now] = tmp;
            }
    }
    inline void dfs_treecut(int now, int top) {
        dfn[now] = ++tot; ltop[now] = top;
        if(!son[now]) return ;
        dfs_treecut(son[now], top); int tmp(0);
        for (int i = head[now]; i; i = edge[i].next)
            if((tmp = edge[i].to) != fa[now] && tmp != son[now])
                dfs_treecut(tmp, tmp);
    }
}
using namespace DFS;
namespace SEGTREE{
    #define lson(x) (x << 1)
    #define rson(x) (x << 1 | 1)
    int segtree[MAXN << 2], lazy[MAXN << 2];
    inline void build(int now, int l, int r) {
        if(l == r) {segtree[now] = beg[l] % mod; return ;}
        int mid = (l + r) >> 1;
        build(lson(now), l, mid); build(rson(now), mid + 1, r);
        segtree[now] = (segtree[lson(now)] + segtree[rson(now)]) % mod;
    }
    inline void pushdown(int now, int l, int r) {
        if(!lazy[now]) return ;
        int mid = (l + r) >> 1; lazy[now] %= mod;
        segtree[lson(now)] = (segtree[lson(now)] + (mid - l + 1) * lazy[now]) % mod;
        segtree[rson(now)] = (segtree[rson(now)] + (r - mid) * lazy[now]) % mod;
        lazy[lson(now)] += lazy[now]; lazy[rson(now)] += lazy[now];
    }
    inline void update(int now, int l, int r, int L, int R, int val) {
        if(l > R || r < L) return ;
        if(L <= l && r <= R) {
            segtree[now] = (segtree[now] + (r - l + 1) * val) % mod;
            lazy[now] = (lazy[now] + val) % mod;
            return ;
        }
        pushdown(now, l, r);
        int mid = (l + r) >> 1;
        update(lson(now), l, mid, L, R, val); update(rson(now), mid + 1, r, L, R, val);
        segtree[now] = (segtree[lson(now)] + segtree[rson(now)]) % mod;
        return ;
    }
    inline int query(int now, int l, int r, int L, int R) {
        if(l > R || r < L) return 0;
        if(L <= l && r <= R) return segtree[now];
        pushdown(now, l, r);
        int mid = (l + r) >> 1;
        return (query(now, l, mid, L, R) + query(now, mid + 1, r, L, R)) % mod;
    }
}
using namespace SEGTREE;
namespace TREECUT{
    inline void sp_add() {
        scanf("%d%d%d", &x, &y, &z);
        z %= mod;
        while(ltop[x] != ltop[y]) {
            if(dep[ltop[x]] < dep[ltop[y]]) swap(x, y);
            update(1, 1, n, dfn[ltop[x]], dfn[x], z);
            x = fa[ltop[x]];
        }
        if(dep[x] > dep[y]) swap(x, y);
        update(1, 1, n, dfn[x], dfn[y], z);
        return ;
    }
    inline void sp_sum() {
        scanf("%d%d", &x, &y);
        int ans(0);
        while(ltop[x] != ltop[y]) {
            if(dep[ltop[x]] < dep[ltop[y]]) swap(x, y);
            ans = (ans + query(1, 1, n, dfn[ltop[x]], dfn[x])) % mod;
            x = fa[ltop[x]];
        }
        if(dep[x] > dep[y]) swap(x, y);
        ans = (ans + query(1, 1, n, dfn[x], dfn[y])) % mod;
        printf("%d\n", ans);
        return ;
    }
    inline void st_add() {
        scanf("%d%d", &x, &z); z %= mod;
        update(1, 1, n, dfn[x], dfn[x] + size[x] - 1, z);
        return ;
    }
    inline void st_sum() {
        scanf("%d", &x);
        printf("%d\n", query(1, 1, n, dfn[x], dfn[x] + size[x] - 1) % mod);
        return ;
    }
}
using namespace TREECUT;
int main() {
    scanf("%d%d%d%d", &n, &m, &root, &mod);
    for (int i = 1; i <= n; ++i)
        scanf("%d", &beg[i]);
    for (int i = 1; i < n; ++i)
        scanf("%d%d", &x, &y), add_edge(x, y);
    dfs_num(root); dfs_treecut(root, root);
    build(1, 1, n);
    for (int i = 1; i <= m; ++i) {
        scanf("%d", &opt);
        switch(opt) {
            case 1: {sp_add(); break;}
            case 2: {sp_sum(); break;}
            case 3: {st_add(); break;}
            case 4: {st_sum(); break;}
        }
    }
    return 0;
}