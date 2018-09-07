#include <cstdio>
const int MAXN = 100010;
const int MAXM = 100010;
struct EDGE{
    int to, next;
}edge[MAXN << 1];
int n, m, root, mod, opt, tot, top, x, y, z;
int beg[MAXN], dep[MAXN], dfn[MAXN], size[MAXN], 
    fa[MAXN], son[MAXN], ltop[MAXN], segtree[MAXN << 2], lazy[MAXN << 2], head[MAXN];
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
inline void add_edge(int u, int v) {
    edge[++top].to = v;
    edge[top].next = head[u];
    head[u] = top;

    edge[++top].to = u;
    edge[top].next = head[v];
    head[v] = top;

    return ;
}
int main() {
    scanf("%d%d%d%d", &n, &m, &root, &mod);
    for (int i = 1; i <= n; ++i)
        scanf("%d", &beg[i]);
    for (int i = 1; i < n; ++i)
        scanf("%d%d", &x, &y), add_edge(x, y);
    dfs_num(root); dfs_treecut(root, root);
}