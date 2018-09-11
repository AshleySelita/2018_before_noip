#include <cstdio>
typedef long long ll;
const int MAXN = 300010;
const int MAXM = 300010;
struct EDGE{
    int to, next;
}edge[MAXN << 1];
int n, m, f, top;
int fa[MAXN], dis[MAXN], head[MAXN];
ll val[MAXN], def[MAXN], chn[MAXN];
bool Mul[MAXN];
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
    scanf("%d", &n, &m);
    for (int i = 1; i <= n; ++i) scanf("%lld", &def[i]);
    for (int i = 1; i <= n; ++i) {
        scanf("%d%d%d", &f, &Mul[i], &chn[i]);
        add_edge(f, i);
    }
}