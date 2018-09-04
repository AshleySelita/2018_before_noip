#include <algorithm>
#include <cstdio>
const int MAXN = 10010;
const int MAXM = 50010;
const int MAXQ = 30010;
const int MAXZ = 100010;
struct EDGE{
    int to, fr, wgh;
}edge[MAXM << 1];
struct TreeEDGE{
    int to, wgh, next;
}treeedge[MAXN << 1];
int n, m, u, v, w, q, top, topt;
int head[MAXN], headt[MAXN], f[MAXN];

inline void add_edge(int u, int v, int w) {
    edge[++top].fr = u;
    edge[top].to = v;
    edge[top].wgh = w;

    edge[++top].fr = v;
    edge[top].to = u;
    edge[top].wgh = w;

    return ;
}
inline void AddEdge(int u, int v, int w) {
    treeedge[++topt].next = headt[u];
    treeedge[topt].to = v;
    treeedge[topt].wgh = w;
    
    treeedge[++topt].next = headt[v];
    treeedge[topt].to = u;
    treeedge[topt].wgh = w;

    return ;
}

inline int find(int x) {
    if(f[x] != x) f[x] = find(f[x]);
    return f[x];
}
inline void unionn(int u, int v) {
    int uu = find(u), vv = find(v);
    if(uu != vv) f[uu] = vv;
}


inline bool cmp(EDGE a, EDGE b) {return (a.wgh > b.wgh);}

int main() {
    scanf("%d%d", &n, &m);
    for (int i = 1; i <= n; ++i) f[i] = i;
    for (int i = 1; i <= n; ++i)
        scanf("%d%d%d", &u, &v, &w), add_edge(u, v, w);
    std::sort(edge + 1, edge + (m << 1) + 1, cmp);
    int tot(0), uf(0), vf(0);
    for (int i = 1; i <= m; ++i) {
        u = edge[i].fr; v = edge[i].to; w = edge[i].wgh;
        uf = find(u); vf = find(v);
        if(uf == vf) {continue;}
        AddEdge(u, v, w); unionn(u, v);
    }
    for (int i = 1; i <= n; ++i) {
        
    }
}