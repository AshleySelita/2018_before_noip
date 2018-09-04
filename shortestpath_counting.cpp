#include <cctype>
#include <cstdio>
#include <cstring>
const int MAXN = 1000010;
const int MAXM = 2000010;
const int N = 10000;
const int MOD = 100003;
struct EDGE{
    int next, to;
}edge[MAXM << 1];
struct QUEUE{
    int head, tail, a[MAXN << 1];
    int pop() {return a[++head];}
    void push(int x) {a[++tail] = x;}
    bool empty() {return (head == tail);}
    void clear() {head = tail = 0;}
}que;
int n, m, u, v, top;
int head[MAXN], dis[MAXN], cnt[MAXN];
char buf[N], *p = buf, *end = buf;
inline char Get_char() {
    if(p == end) {
        if(feof(stdin)) return ('\0');
        p = buf; end = buf + fread(buf, 1, N, stdin);
    }
    return *(p++);
}
inline void Get_int(int &x) {
    x = 0; char c(0);
    while(!isdigit(c = Get_char()));
    do {x = (x << 1) + (x << 3) + (c ^ 48);}
    while(isdigit(c = Get_char()));
    return ;
}
inline void add_edge(int u, int v) {
    edge[++top].next = head[u];
    edge[top].to = v;
    head[u] = top;

    edge[++top].next = head[v];
    edge[top].to = u;
    head[v] = top;
}
int main() {
    Get_int(n); Get_int(m);
    for (int i = 1; i <= m; ++i) {
        Get_int(u), Get_int(v);
        if(u == v) continue;
        add_edge(u, v);
    }
    memset(dis, 0x3f, sizeof dis);
    dis[1] = 1; cnt[1] = 1; que.push(1);
    int now(0), tmp(0);
    while(!que.empty()) {
        now = que.pop();
        for (int i = head[now]; i; i = edge[i].next) {
            tmp = edge[i].to;
            if(dis[tmp] == dis[now] + 1) {cnt[tmp] = (cnt[tmp] + cnt[now]) % MOD;}
            if(dis[tmp] > dis[now] + 1) {
                dis[tmp] = dis[now] + 1;
                cnt[tmp] = cnt[now]; 
                que.push(tmp);
            }
        }
    }
    for (int i = 1; i <= n; ++i)
        printf("%d\n", dis[i] == 0x3f3f3f3f ? 0 : cnt[i]);
    return 0;
}