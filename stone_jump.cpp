#include <cstdio>
const int MAXN = 50010;
const int MAXM = 50010;
int l, n, m;
int a[MAXN];
inline bool check(int x) {
    int last(0), sum(0);
    for (int i = 1; i <= n; ++i) {
        (a[i] - last) < x ? sum++ : last = a[i];
    }
    return sum <= m;
}
int main() {
    scanf("%d%d%d", &l, &n, &m);
    for (int i = 1; i <= n; ++i)
        scanf("%d", &a[i]);
    int left(1), right(l), mid(0), ans(0);
    while(left <= right) {
        mid = (left + right) >> 1;
        check(mid) ? ans = mid, left = mid + 1 : right = mid - 1;
    }
    printf("%d\n", ans);
    return 0;
}