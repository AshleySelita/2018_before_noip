#include <cstdio>
const int MAXN = 100010;
const int MAXM = 100010;
struct EDGE{
    int to, next;
}edge[MAXN << 1];
int n, m, root, mod, opt, tot, top, x, y, z;
int beg[MAXN], dep[MAXN], dfn[MAXN], size[MAXN], link[MAXN],
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
    inline void dfs1(int now) {
        size[now] = 1; int tmp(0), maxa(0);
        for (int i = head[now]; i; i = edge[i].next)
            if((tmp = edge[i].to) != fa[now]) {
                dep[tmp] = dep[now] + 1; fa[tmp] = now;
                dfs1(tmp);
                size[now] += size[tmp];
                if(size[tmp] > maxa) maxa = size[tmp], son[now] = tmp;
            }
    }
    inline void dfs2(int now, int top) {
        dfn[now] = ++tot; link[tot] = beg[now]; ltop[now] = top;
        if(!son[now]) return ;
        dfs2(son[now], top); int tmp(0);
        for (int i = head[now]; i; i = edge[i].next)
            if((tmp = edge[i].to) != fa[now] && tmp != son[now])
                dfs2(tmp, tmp);
        return ;
    }
}
using namespace DFS;
namespace TALIKE_ARRAY{
    int Ray1[MAXN], Ray2[MAXN];
    inline int lowbit(int x) {return x & (-x);}
    inline void update(int *Ray, int pos, int x) {
        while(pos <= n) {
            Ray[pos] = (Ray[pos] + x) % mod;
            pos += lowbit(pos);
        }
        return ;
    }
    inline int query(int *Ray, int pos) {
        int ans(0);
        while(pos) {
            ans = (Ray[pos] + ans) % mod;
            pos -= lowbit(pos);
        }
        return ans % mod;
    }
}
using namespace TALIKE_ARRAY;
namespace TREECUT{
    inline void sp_add() {
        scanf("%d%d%d", &x, &y, &z); z %= mod;
        while(ltop[x] != ltop[y]) {
            if(dep[ltop[x]] < dep[ltop[y]]) swap(x, y);
            update(Ray1, dfn[ltop[x]], z); update(Ray1, dfn[x] + 1, -z);
            update(Ray2, dfn[ltop[x]], (dfn[ltop[x]] - 1) * z); 
            update(Ray2, dfn[x] + 1, (-z) * dfn[x]);
        }
        if(dep[x] > dep[y]) swap(x, y);
        update(Ray1, dfn[x], z); update(Ray1, dfn[y] + 1, -z);
        update(Ray2, dfn[x], (dfn[x] - 1) * z);
        update(Ray2, dfn[y] + 1, (-z) * dfn[y]);
    }
    inline void sp_query() {
        scanf("%d%d", &x, &y); int ans(0), sum1(0), sum2(0);
        while(ltop[x] != ltop[y]) {
            if(dep[ltop[x]] < dep[ltop[y]]) swap(x, y);
            sum1 = ((dfn[ltop[x]] - 1) * query(Ray1, dfn[ltop[x]] - 1) - query(Ray2, dfn[ltop[x]] - 1)) % mod;
            sum2 = ((dfn[x]) * query(Ray1, dfn[x]) - query(Ray2, dfn[x])) % mod;
            ans = (ans + sum2 - sum1) % mod;
        }
        if(dep[x] > dep[y]) swap(x, y);
        sum1 = ((dfn[x] - 1) * query(Ray1, dfn[x] - 1) - query(Ray2, dfn[x] - 1)) % mod;
        sum2 = ((dfn[y]) * query(Ray1, dfn[y]) - query(Ray2, dfn[y])) % mod;
        ans = (ans + sum2 - sum1) % mod;
        printf("%d\n", ans);
        return ;
    }
    inline void st_add() {
        scanf("%d%d", &x, &z); z %= mod;
        update(Ray1, dfn[x], z); update(Ray1, dfn[x] + size[x], -z);
        update(Ray2, dfn[x], (dfn[x] - 1) * z);
        update(Ray2, dfn[x] + size[x], (-z) * (dfn[x] + size[x] - 1));
    }
    inline void st_query() {
        scanf("%d", &x); int ans(0);
        int sum1 = ((dfn[x] - 1) * query(Ray1, dfn[x] - 1) - query(Ray2, dfn[x] - 1));
        int sum2 = ((dfn[x] + size[x] - 1) * query(Ray1, dfn[x] + size[x] - 1) - query(Ray2, dfn[x] - size[x] - 1)) % mod;
        ans = (ans + sum1 + sum2) % mod;
        printf("%d\n", ans);
        return ;
    }
}
using namespace TREECUT;
int main() {
    freopen("linkcut.in", "r", stdin);
    scanf("%d%d%d%d", &n, &m, &root, &mod);
    for (int i = 1; i <= n; ++i)
        scanf("%d", &beg[i]), beg[i] %= mod,
        update(Ray1, i, beg[i] - beg[i - 1]), 
        update(Ray2, i, (i - 1) * (beg[i] - beg[i - 1]));
    for (int i = 1; i < n; ++i)
        scanf("%d%d", &x, &y), add_edge(x, y);
    dfs1(root); dfs2(root, root);
    for (int i = 1; i <= m; ++i) {
        scanf("%d", &opt);
        switch(opt) {
            case 1: {sp_add();break;}
            case 2: {sp_query();break;}
            case 3: {st_add();break;}
            case 4: {st_query();break;}
        }
    }
}