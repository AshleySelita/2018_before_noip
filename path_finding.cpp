#include <cstdio>
#include <cstdlib>
const int MAXN = 10010;
const int MAXM = 200010;
struct EDGE{
    int to, next;
}edge[MAXM];
struct REDGE{
    int to, next;
}redge[MAXM];
struct QUEUE{
    int head, tail, a[MAXN];
    int pop() {return a[++head];}
    void push(int x) {a[++tail] = x;}
    bool empty() {return (head == tail);}
    void clear() {head = tail = 0;}
}que;
int n, m, s, t, u, v, top, rtop;
int head[MAXN], rhead[MAXN], dis[MAXN];
bool vis[MAXN], isget[MAXN], che[MAXN];
inline void add_edge(int u, int v) {
    edge[++top].to = v;
    edge[top].next = head[u];
    head[u] = top;

    redge[++rtop].to = u;
    redge[rtop].next = rhead[v];
    rhead[v] = rtop;

    return ;
}
inline void dfs(int now) {
    if(vis[now]) return ;
    vis[now] = true, isget[now] = true;
    for (int i = rhead[now]; i; i = redge[i].next)
        dfs(redge[i].to);
    return ;
}
int main() {
    //freopen("testdata.in", "r", stdin);
    scanf("%d%d", &n, &m);
    for (int i = 1; i <= m; ++i){
        scanf("%d%d", &u, &v);
        if(u == v) continue;
        add_edge(u, v);
    }
    scanf("%d%d", &s, &t); vis[t] = true;
    for (int i = rhead[t]; i; i = redge[i].next)
        dfs(redge[i].to);
    for (int i = 1; i <= n; ++i)
        if(!vis[i]) {
            for (int j = rhead[i]; j; j = redge[j].next)
                if(isget[redge[j].to]) isget[redge[j].to] = false;
        }
    isget[t] = true;
    if(isget[s]) que.push(s);
    int now(0), tmp(0);
    while(!que.empty()) {
        now = que.pop();
        for (int i = head[now]; i; i = edge[i].next)
            if(!che[(tmp = edge[i].to)] && isget[tmp])
                que.push(tmp), dis[tmp] = dis[now] + 1, che[tmp] = true;
        if(dis[t]) break;
    }
    printf("%d\n", dis[t] ? dis[t] : -1);
    return 0;
}