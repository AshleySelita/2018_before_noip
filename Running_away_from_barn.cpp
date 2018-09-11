#include <cstdio>
typedef long long ll;
const int MAXN = 200010;
int n, m, fa[MAXN][19], ans[MAXN];
ll l, dis[MAXN];
int main() {
    scanf("%d%lld", &n, &l); ans[1] = 1;
    for (int i = 2; i <= n; ++i) {
        scanf("%d%lld", &fa[i][0], &dis[i]);
        dis[i] += dis[fa[i][0]];
        for (int j = 1; j < 19; ++j)
            fa[i][j] = fa[fa[i][j - 1]][j - 1];
        int iter(i);
        for (int j = 18; j >= 0; --j)
            if(dis[i] - dis[fa[iter][j]] <= l) iter = fa[iter][j];
        ans[i]++; ans[fa[iter][0]]--;
    }
    for (int i = n; i >= 1; --i)
        ans[fa[i][0]] += ans[i];
    for (int i = 1; i <= n; ++i)
        printf("%d\n", ans[i]);
    return 0;
}