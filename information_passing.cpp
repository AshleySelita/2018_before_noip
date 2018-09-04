#include <cstdio>
const int MAXN = 200010;
int n, ans(0x7fffffff), st, cnt;
int to[MAXN], dep[MAXN], vis[MAXN];
inline void dfs(int now, int bef, int cnt) {
    if(vis[now]) {
        if(vis[now] == cnt) {ans = ans < (dep[bef] - dep[now] + 1) ? ans : (dep[bef] - dep[now] + 1);}
        return ;
    }
    vis[now] = cnt;
    dep[now] = dep[bef] + 1;
    dfs(to[now], now, cnt);
    return ;
}
int main() {
    scanf("%d", &n);
    for (int i = 1; i <= n; ++i)
        scanf("%d", &to[i]);
    for (int i = 1; i <= n; ++i)
        if(!vis[i]) dfs(i, 0, ++cnt);
    printf("%d\n", ans);
    return 0;
}