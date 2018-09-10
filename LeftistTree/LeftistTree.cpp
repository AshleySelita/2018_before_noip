#include <cstdio>
const int MAXN = 100010;
const int MAXM = 100010;
struct Node{
    int lson, rson;
    Node() {lson = rson = 0;}
}node[MAXN];
int n, m, opt, x, y;
int dis[MAXN], val[MAXN], fa[MAXN];
bool del[MAXN];
inline void swap(int &x, int &y) {x ^= y ^= x ^= y;}
inline int find(int x) {
    while(fa[x]) x = fa[x];
    return x;
}
inline int merge(int x, int y) {
    if(!x || !y) return (x + y);
    if(val[x] > val[y] || (val[x] == val[y] && x > y)) swap(x, y);
    int& lson = node[x].lson; int& rson = node[x].rson;
    rson = merge(rson, y);
    fa[rson] = x;
    if(dis[lson] < dis[rson]) swap(lson, rson);
    dis[x] = dis[rson] + 1;
    return x;
}
inline void p_union() {
    scanf("%d%d", &x, &y);
    if(del[x] || del[y]) return ;
    int fx = find(x), fy = find(y);
    if(fx == fy) return ;
    merge(fx, fy);
}
inline void delte() {
    scanf("%d", &x); int fx = find(x);
    if(del[x]) {printf("-1\n"); return ;}
    printf("%d\n", val[fx]);
    del[fx] = true; val[fx] = -1;
    fa[node[fx].lson] = fa[node[fx].rson] = 0;
    merge(node[fx].lson, node[fx].rson);
    return ;
}
int main() {
    scanf("%d%d", &n, &m);
    for (int i = 1; i <= n; ++i) scanf("%d", &val[i]);
    dis[0] = -1;
    for (int i = 1; i <= m; ++i) {
        scanf("%d", &opt);
        switch(opt) {
            case 1: {p_union(); break;}
            case 2: {delte(); break;}
        }
    }
    return 0;
}