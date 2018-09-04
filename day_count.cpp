#include <algorithm>
#include <cstdio>
int n, x, l, ans, bef;
int main() {
    scanf("%d", &n);
    for (int i = 1; i <= n; ++i) {
        scanf("%d", &x);
        if(x > bef) l++;
        else {ans = std::max(ans, l); l = 1;}
        bef = x;
    }
    printf("%d\n", ans);
    return 0;
}