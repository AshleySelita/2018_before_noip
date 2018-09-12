#include <cstdio>
typedef long long ll;
const int MAXN = 100010;
struct Node{
    int lson, rson;
    void clear() {lson = rson = 0;}
}node[MAXN];
struct EDGE{
    int to, next;
}edge[MAXN];
int n, top, f; 
int root[MAXN], head[MAXN], fa[MAXN], dis[MAXN];
ll m, ans = (-0x7fffffff);
ll val[MAXN], ldshp[MAXN];
template<class _T>
inline _T max(_T a, _T b) {return (a > b ? a : b);}
template<class _T>
inline void swap(_T &a, _T &b) {a ^= b ^= a ^= b;}
inline bool add_edge(int u, int v) {
    edge[++top].to = v;
    edge[top].next = head[u];
    head[u] = top;
    return ;
}
int merge(int u, int v) {
    if(!u || !v) return (u + v);
    if(val[u] > val[v]) swap(u, v);
    int& lson = node[u].lson; int& rson = node[u].rson;
    rson = merge(rson, v); fa[rson] = u;
    if(dis[lson] < dis[rson]) swap(lson, rson);
    dis[u] = dis[rson] + 1;
    return u;
}
inline int del(int now) {
    int lson = node[now].lson, rson = node[now].rson;
    fa[lson] = fa[rson] = 0; node[now].clear();
    return merge(lson, rson);
}
void dfs(int now) {

}
int main() {
    scanf("%d%lld", &n, &m);
    for (int i = 1; i <= n; ++i) {
        scanf("%d%lld%lld", &f, &val[i], &ldshp[i]);
        f ? add_edge(f, i) : false;
    }
    dfs(1);
    printf("%lld\n", ans);
    return 0;
}