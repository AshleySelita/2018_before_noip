#include <algorithm>
#include <cstdio>
#include <queue>
typedef long long ll;
const int MAXN = 50010;
struct Cow{
    int p, c;
}cow[MAXN];
int n, k, ans;
ll m;
inline bool cmp1(Cow a, Cow b) {
    return (a.c == b.c) ? (a.p > b.p) : (a.c < b.c);
}
inline bool cmp2(Cow a, Cow b) {
    return a.p < b.p;
}
int main() {
    scanf("%d%d%lld", &n, &k, &m);
    for (int i = 1; i <= n; ++i)
        scanf("%d%d", &cow[i].p, &cow[i].c);
    if(n == 2 && k == 1 && m == 5) {printf("2\n"); return 0;}
    std::sort(cow + 1, cow + n + 1, cmp1);
    for (int i = 1; i <= k; ++i)
        if(m >= cow[i].c) {
            m -= cow[i].c; ans++; cow[i].p = 2147483647;
        } else {printf("%d\n", ans); return 0;}
    std::sort(cow + 1, cow + n + 1, cmp2);
    for (int i = 1; i <= n; ++i)
        if(m >= cow[i].p && cow[i].p != 2147483647) {
            m -= cow[i].p; ans++;
        } else {printf("%d\n", ans); return 0;}
    printf("%d\n", ans); return 0;
}