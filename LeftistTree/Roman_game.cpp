#include <cstdio>
const int MAXN = 1000010;
const int MAXM = 100010;
struct Node {
    int lson, rson;
    Node(): lson(0), rson(0) {}
    Node(int a, int b): lson(a), rson(b) {}
}node[MAXN];
int n, m, x, y;
int fa[MAXN], dis[MAXN], val[MAXN];
bool vis[MAXN]; char opt[5];
inline void swap(int &a, int &b) {a ^= b ^= a ^= b;}
inline int find(int x) {
    while(fa[x]) 
        x = fa[x];
    return x;
}
inline int merge(int u, int v) {
    if(!u || !v) return (u + v);
    if(val[u] > val[v]) swap(u, v);
    int& lson = node[u].lson; int& rson = node[u].rson;
    rson = merge(rson, v); fa[rson] = u;
    if(dis[lson] < dis[rson]) swap(lson, rson);
    dis[u] = dis[rson] + 1;
    return u;
}
inline void Mer() {
    scanf("%d%d", &x, &y);
    if(vis[x] || vis[y]) return ;
    int fx = find(x), fy = find(y);
    if(fx == fy) return ;
    merge(fx, fy);
    return ;
}
inline void Kill() {
    scanf("%d", &x);
    if(vis[x]) {printf("0\n"); return ;}
    int fx = find(x);
    printf("%d\n", val[fx]);
    vis[fx] = true; val[fx] = -1;
    fa[node[fx].lson] = fa[node[fx].rson] = 0;
    merge(node[fx].lson, node[fx].rson);
    return ;
}
int main() {
    //freopen("roman.in", "r", stdin);
    scanf("%d", &n); dis[0] = -1;
    for (int i = 1; i <= n; ++i)
        scanf("%d", &val[i]);
    scanf("%d", &m);
    for (int i = 1; i <= m; ++i) {
        scanf("%s", opt);
        switch(opt[0]) {
            case 'M': {Mer(); break;}
            case 'K': {Kill(); break;}
        }
    }
    return 0;
}