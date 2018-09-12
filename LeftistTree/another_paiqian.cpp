#include <cctype>
#include <cstdio>
typedef long long ll;
const int MAXN = 100010;
const int N = 10000;
struct Node{
    int lson, rson;
    void clear() {lson = rson = 0;}
}node[MAXN];
struct EDGE{
    int to, next;
}edge[MAXN];
int n, top, f; 
int root[MAXN], head[MAXN], dis[MAXN], num[MAXN];
ll m, ans = (-0x7fffffff);
ll val[MAXN], ldshp[MAXN], tot[MAXN];
char buf[N], *p = buf, *end = buf;
inline char Get_char() {
    if(p == end) {
        if(feof(stdin)) return 0;
        p = buf; end = buf + fread(buf, 1, N, stdin);
    }
    return *(p++);
}
template<class _T>
inline void Get_inte(_T &x) {
    x = 0; char c(0);
    while(!isdigit(c = Get_char()));
    do {x = x * 10 + (c ^ 48);}
    while(isdigit(c = Get_char()));
    return ;
}
template<class _T>
inline void Write_inte(_T x){
    if(x > 9) Write_inte(x / 10);
    putchar(x % 10 + '0');
    return ;
}
inline ll max(ll a, ll b) {return (a > b ? a : b);}
inline void swap(int &a, int &b) {a ^= b ^= a ^= b;}
inline bool add_edge(int u, int v) {
    edge[++top].to = v;
    edge[top].next = head[u];
    head[u] = top;
    return true;
}
inline void maintain(int now) {
    int lson = node[now].lson, rson = node[now].rson;
    num[now] = num[lson] + num[rson] + 1;
    tot[now] = tot[lson] + tot[rson] + val[now];
    dis[now] = dis[rson] + 1;
    return ;
}
inline int merge(int u, int v) {
    if(!u || !v) return (u + v);
    if(val[u] < val[v]) swap(u, v);
    int& lson = node[u].lson; int& rson = node[u].rson;
    rson = merge(rson, v);
    if(dis[lson] < dis[rson]) swap(lson, rson);
    maintain(u);
    return u;
}
inline int del(int now) {
    return merge(node[now].lson, node[now].rson);
}
inline void dfs(int now) {
    int tmp(0);
    for (int i = head[now]; i; i = edge[i].next) {
        dfs((tmp = edge[i].to)); root[now] = merge(root[now], root[tmp]);
    }
    while(tot[root[now]] > m) root[now] = del(root[now]);
    ans = max(ans, num[root[now]] * ldshp[now]);
    return ;
}
int main() {
    Get_inte(n); Get_inte(m);
    for (int i = 1; i <= n; ++i) {
        Get_inte(f); Get_inte(val[i]); Get_inte(ldshp[i]);
        f ? add_edge(f, i) : false; num[i] = 1; tot[i] = val[i];
        root[i] = merge(root[i], i);
    }
    dfs(1);
    Write_inte(ans); putchar('\n');
    return 0;
}