#include <cstdio>
const int MAXN = 100010;
const int MAXM = 100010;
struct EDGE{
    int to, next, wgh;
}edge[MAXN << 1];
int n, m, u, v, w, top;
int head[MAXN], dep[MAXN];//, fa[MAXN][18], mulxor[MAXN][18];
int fa[MAXN], mulxor[MAXN];
inline void swap(int &a, int &b) {a ^= b ^= a ^= b;}
inline void add_edge(int u, int v, int w) {
    edge[++top].next = head[u];
    edge[top].to = v;
    edge[top].wgh = w;
    head[u] = top;

    edge[++top].next = head[v];
    edge[top].to = u;
    edge[top].wgh = w;
    head[v] = top;

    return ;
}
/*inline void dfs(int now, int pre) {
    dep[now] = dep[pre] + 1; fa[now][0] = pre; 
    for (int i = 1; i < 18; ++i) {
        fa[now][i] = fa[fa[now][i - 1]][i - 1];
        mulxor[now][i] = mulxor[now][i - 1] ^ mulxor[fa[now][i - 1]][i - 1];
    }
    int tmp(0);
    for (int i = head[now]; i; i = edge[i].next)
        if((tmp = edge[i].to) != pre) {
            mulxor[tmp][0] = edge[i].wgh;
            dfs(tmp, now);
        }
}
inline void Mul_lca(int x, int y) {
    if(dep[x] < dep[y]) swap(x, y);
    int ans(0);
    for (int i = 17; i >= 0; --i) 
        if(dep[fa[x][i]] >= dep[y]){
            ans ^= mulxor[x][i];
            x = fa[x][i];
        }
    if(x == y) {printf("%d\n", ans); return ;}
    for (int i = 17; i >= 0; --i) 
        if(fa[x][i] != fa[y][i]) {
            ans = ans ^ mulxor[x][i] ^ mulxor[y][i];
            x = fa[x][i]; y = fa[y][i];
        }
    ans = ans ^ mulxor[x][0] ^ mulxor[y][0];
    printf("%d\n", ans);
    return ;
}*/
inline void dfs(int now, int bef) {
    dep[now] = dep[bef] + 1;
    int tmp(0);
    for (int i = head[now]; i; i = edge[i].next)
        if((tmp = edge[i].to) != bef) {
            mulxor[tmp] = mulxor[now] ^ edge[i].wgh;
            dfs(tmp, now);
        }
}
int main() {
    scanf("%d", &n);
    for (int i = 1; i < n; ++i)
        scanf("%d%d%d", &u, &v, &w), add_edge(u, v, w);
    dfs(1, 0);
    scanf("%d", &m);
    for (int i = 1; i <= m; ++i) {
        scanf("%d%d", &u, &v);
        printf("%d\n", mulxor[u] ^ mulxor[v]);
    }
    return 0;
}