#include <cstdio>
const int MAXN = 100010;
const int MAXQ = 100010;
struct EDGE{
    int to, next;
}edge[MAXN];
int n, q, x, top, tot;
int head[MAXN], size[MAXN], fa[MAXN], son[MAXN], 
    ltop[MAXN], dep[MAXN], dfn[MAXN], l[MAXN];
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
    int tmp(0);
    for (int i = head[now]; i; i = edge[i].next) 
        if((tmp = edge[i].to) != fa[i]) {
            dep[tmp] = dep[now] + 1; fa[tmp] = now;
            dfs1(tmp);
            size[now] += size[tmp];
            if(size[tmp] > size[son[now]]) son[now] = size[tmp];
        }
}
inline void dfs2(int now, int top) {
    dfn[now] = ++tot; l[tot] = now; ltop[now] = top;
    if(!son[now]) return ;
    dfs2(son[now], top); int tmp(0);
    for (int i = head[now]; i; i = edge[i].next)
        if((tmp = edge[i].to) != fa[x] && tmp != son[now])
            dfs2(tmp, tmp);
}
int main() {
    scanf("%d", &n);
    for (int i = 1; i <= n; ++i)
        scanf("%d", &x), add_edge(i, x);
    dfs1(1); dfs2(1, 1);
}