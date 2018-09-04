#include <algorithm>
#include <cstdio>
#include <cstring>
const int MAXN = 2010;
const int MAXM = 4000010;
struct EDGE{
    int next, to, wgh;
}edge[MAXM << 1];
struct QUEUE{
    int head, tail, a[MAXN << 2];
    int pop() {return a[++head];}
    void push(int x) {a[++tail] = x;}
    bool empty() {return (head == tail);}
    void clear() {head = tail = 0;}
}que;
int n, m, u, v, w, top;
int head[MAXN], dis[MAXN], cnt[MAXN], map[MAXN][MAXN];
bool inque[MAXN];
inline void add_edge(int u, int v, int w) {
    edge[++top].next = head[u];
    edge[top].to = v;
    edge[top].wgh = w;
    head[u] = top;

    return ;
}
int main() {
    scanf("%d%d", &n, &m);
    memset(map, 0x3f, sizeof map);
    for (int i = 1; i <= m; ++i) {
        scanf("%d%d%d", &u, &v, &w); //add_edge(u, v, w);
        map[u][v] = std::min(map[u][v], w);
    }
    memset(dis, 0x3f, sizeof dis);
    dis[1] = 0; cnt[1] = 1; que.push(1);
    int now(0), to(0), wgh(0);
    while(!que.empty()) {
        now = que.pop();
        inque[now] = false;
        if(now == n) {continue;}
        for (int i = 1; i <= n; ++i) {
            to = i; wgh = map[now][i];
            if(dis[to] == dis[now] + wgh) cnt[to] += cnt[now];
            if(dis[to] > dis[now] + wgh) {
                dis[to] = dis[now] + wgh;
                cnt[to] = cnt[now];
            }
            if(!inque[to] && cnt[to]) {que.push(to); inque[to] = true;}
        }
        cnt[now] = 0;
    }
    if(dis[n] == 0x3f3f3f3f) printf("No answer\n");
    else printf("%d %d\n", dis[n], cnt[n]);
    return 0;
}