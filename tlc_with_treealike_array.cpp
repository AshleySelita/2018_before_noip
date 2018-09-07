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
    inline void update(int *Ray, int x, int pos) {
        while(pos <= n) {
            Ray[pos] = (Ray[pos] + x) % mod;
            pos += lowbit(pos);
        }
        return ;
    }
    inline int query(int *Ray, int x, int pos) {
        int ans(0);
        while(pos) {
            ans = (Ray[pos] + ans) % mod;
            pos -= lowbit(pos);
        }
        return ans;
    }
}
using namespace TALIKE_ARRAY;
namespace TREECUT{
    inline void sp_add() {
        scanf("%d%d%d", &x, &y, &z); int ans(0);
        while(ltop[x] != ltop[y]) {
            if(dep[ltop[x]] < dep[ltop[y]]) swap(x, y);
            
        }
        if(dep[x] > dep[y]) swap(x, y);
    }
}
int main() {
    scanf("%d%d%d%d", &n, &m, &root, &mod);
    for (int i = 1; i <= n; ++i)
        scanf("%d", &beg[i]), 
        update(Ray1, beg[i] - beg[i - 1], i), 
        update(Ray2, (i - 1) * (beg[i] - beg[i - 1]), i);
    for (int i = 1; i < n; ++i)
        scanf("%d%d", &x, &y), add_edge(x, y);
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