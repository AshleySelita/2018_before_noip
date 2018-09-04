#include <cstdio>
int n, w, s, t, a, ans;
inline void check(int x) {
    if(s <= x && t >= x) ans++;
    return ;
}
int main() {
    scanf("%d%d%d", &n, &s, &t);
    scanf("%d", &w); check(w);
    for (int i = 2; i <= n; ++i) {
        scanf("%d", &a);
        check(w += a);
    }
    printf("%d\n", ans);
    return 0;
}