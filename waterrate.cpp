#include <cstdio>
int x, a, b, c, n;
int ans1, ans2;
int main() {
    scanf("%d%d%d%d%d", &x, &a, &b, &c, &n);
    ans1 = x * n;
    ans2 = a + (n > b ? c * (n - b) : 0);
    printf("%d\n", ans1 > ans2 ? ans2 : ans1);
    return 0;
}