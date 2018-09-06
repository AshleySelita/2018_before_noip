#include <algorithm>
#include <cstdio>
#include <cstring>
#include <queue>
const int MAXN = 20010;
const int MAXM = 100010;
struct NODE{
    int x, y, id;
}node[MAXM];
struct EDGE{
    int to, next, wgh;
}edge[MAXM << 3];
std::queue<int> que;
int n, m, u, v, S, T, top;
int head[MAXM << 2], dis[MAXM << 2];
bool inque[MAXM << 2];
inline bool cmpx(NODE a, NODE b) {return (a.x == b.x ? a.y < b.y : a.x < b.x);}
inline bool cmpy(NODE a, NODE b) {return (a.y == b.y ? a.x < b.x : a.y < b.y);}
inline bool add_edge(int u, int v, int w) {
    edge[++top].to = v;
    edge[top].wgh = w;
    edge[top].next = head[u];
    head[u] = top;

    edge[++top].to = u;
    edge[top].wgh = w;
    edge[top].next = head[v];
    head[v] = top;

    return true;
}
inline void SPFA() {
    memset(dis, 0x3f, sizeof dis);
    dis[S] = 0; inque[S] = true; que.push(S);
    int now(0), tmp(0), w(0);
    while(!que.empty()) {
        now = que.front(); que.pop(); inque[now] = false;
        for (int i = head[now]; i; i = edge[i].next) {
            tmp = edge[i].to; w = edge[i].wgh;
            if(dis[tmp] > dis[now] + w) {
                dis[tmp] = dis[now] + w;
                if(!inque[tmp]) {inque[tmp] = true; que.push(tmp);}
            }
        }
    }
    return ;
}
int main() {
    scanf("%d%d", &n, &m); S = m + 1; T = m + 2;
    for (int i = 1; i <= T; ++i) {
        scanf("%d%d", &node[i].x, &node[i].y);
        node[i].id = i;
    }
    std::sort(node + 1, node + T + 1, cmpx);
    for (int i = 1; i < T; ++i)
        (node[i].x == node[i + 1].x) ? 
            add_edge(node[i].id, node[i + 1].id, 2 * (node[i + 1].y - node[i].y)) : false;
    std::sort(node + 1, node + T + 1, cmpy);
    for (int i = 1; i < T; ++i)
        (node[i].y == node[i + 1].y) ? 
            add_edge(node[i].id + T, node[i + 1].id + T, 2 * (node[i + 1].x - node[i].x)) : false;
    for (int i = 1; i <= m; ++i)
        add_edge(i, i + T, 1);
    add_edge(S, S * 2 + 1, 0); add_edge(T, T * 2, 0);
    SPFA();
    (dis[T] == 0x3f3f3f3f) ? printf("-1\n") : printf("%d\n", dis[T]);
    return 0;
}