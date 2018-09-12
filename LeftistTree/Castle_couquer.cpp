#include <cstdio>
#define re register
typedef long long ll;
const int MAXN = 300010;
const int MAXM = 300010;
struct Node{
    int lson, rson;
}node[MAXN];
struct EDGE{
    int to, next;
}edge[MAXN];
int n, m, f, top;
int fa[MAXN], dis[MAXN], head[MAXN], st[MAXM], root[MAXN], dep[MAXN], doc[MAXN], kcc[MAXN];
ll val[MAXM], def[MAXN], chn[MAXN], mul[MAXN], add[MAXN];
bool Mul[MAXN];
inline void swap(int &a, int &b) {a ^= b ^= a ^= b;}
inline void add_edge(int u, int v) {
    edge[++top].to = v;
    edge[top].next = head[u];
    head[u] = top;
    return ;
}
inline void cal(int now, ll a, ll b) {
    if(!now) return ;
    val[now] *= a; val[now] += b;
    mul[now] *= a; add[now] *= a; add[now] += b;
    return ;
}
inline void pushdown(int now) {
    cal(node[now].lson, mul[now], add[now]);
    cal(node[now].rson, mul[now], add[now]);
    mul[now] = 1; add[now] = 0;
}
int merge(int x, int y) {
    if(!x || !y) return (x + y);
    pushdown(x); pushdown(y);
    if(val[x] > val[y]) swap(x, y);
    int& lson = node[x].lson; int& rson = node[x].rson;
    rson = merge(rson, y); fa[rson] = x;
    if(dis[lson] < dis[rson]) swap(lson, rson);
    dis[x] = dis[rson] + 1;
    return x;
}
inline int del(int now) {
    int lson = node[now].lson, rson = node[now].rson;
    fa[lson] = fa[rson] = 0;
    return merge(lson, rson);
}
void dfs(int now, int pre) {
    dep[now] = dep[pre] + 1; int tmp(0);
    for (re int i = head[now]; i; i = edge[i].next)
        dfs((tmp = edge[i].to), now), root[now] = merge(root[now], root[tmp]);
    while(root[now] && val[root[now]] < def[now]) {
        pushdown(root[now]);
        doc[now]++; kcc[root[now]] = dep[st[root[now]]] - dep[now];
        root[now] = del(root[now]);
    }
    Mul[now] ? cal(root[now], chn[now], 0) : cal(root[now], 1, chn[now]);
    return ;
}
int main() {
    //freopen("F:\\MZQ\\Workspace\\LeftistTree\\castle.in", "r", stdin);
    //freopen("castle.out", "w", stdout);
    scanf("%d%d", &n, &m); dis[0] = -1;
    for (re int i = 1; i <= n; ++i) scanf("%lld", &def[i]);
    int ttmp(0);
    for (re int i = 2; i <= n; ++i) {
        scanf("%d%d%lld", &f, &ttmp, &chn[i]); Mul[i] = ttmp;
        add_edge(f, i);
    }
    for (re int i = 1; i <= m; ++i) {
        scanf("%lld%d", &val[i], &st[i]);
        mul[i] = 1; root[st[i]] = merge(root[st[i]], i);
    }
    dfs(1, 0);
    while(root[1]) {
        pushdown(root[1]);
        kcc[root[1]] = dep[st[root[1]]];
        root[1] = del(root[1]);
    }
    for (re int i = 1; i <= n; ++i) printf("%d\n", doc[i]);
    for (re int i = 1; i <= m; ++i) printf("%d\n", kcc[i]);
    return 0;
}