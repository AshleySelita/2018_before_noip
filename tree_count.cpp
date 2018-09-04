#include <cmath>
#include <cstdio>
typedef long long ll;
int n, a[160], x, tot;
inline double fast_pow(int a, int b) {
    ll x = 1, base = a; bool flag = true;
    if(b < 0) {b *= -1; flag = false;}
    while(b) {
        (b % 2) ? x *= base : false;
        base *= base;
        b /= 2;
    }
    return flag ? x : 1.0 / x;
}
int main() {
    scanf("%d", &n);
    a[2]++; a[n - 1]--;
    for (int i = 1; i <= n; ++i){
        scanf("%d", &x), a[2]--, a[x]++, tot += x;
        if(x == 0 && n != 1) {printf("0\n"); return 0;}
    }
    if(tot != (n - 1) * 2) {printf("0\n"); return 0;}
    for (int i = 1; i <= n; ++i)
        a[i] += a[i - 1];
    double ans = 1;
    for (int i = 1; i <= n; ++i)
        ans *= fast_pow(i, a[i]);
    if(ans - floor(ans) < ceil(ans) - ans) printf("%lld\n", ll(floor(ans)));
    else printf("%lld\n", ll(ceil(ans)));
    return 0;
}