#include <algorithm>
#include <cstdio>
#define re register
typedef long long ll;
const int MAXN = 100010;
int n, w;
ll ans(-0x7ffffffffffffff);
ll a[MAXN], b[MAXN];
ll suma[MAXN], sumb[MAXN];
int main() {
    scanf("%d%d", &n, &w);
    for (re int i = 1; i <= n; ++i) {
        scanf("%lld", &a[i]), suma[i] = a[i] + suma[i - 1];
    }
    for (re int i = 1; i <= n; ++i) {
        scanf("%lld", &b[i]), sumb[i] = b[i] + sumb[i - 1];
    }
    re ll now(0);
    re int iter(0);
    for (re int i = n; i >= 1; --i) {
        iter = 0;
        now = suma[n] - suma[i - 1];
        for (re int j = n; j >= 1; --j)
            if(sumb[n] - sumb[j - 1] >= now) {iter = j; break;}
        if(!iter) break;
        ans = std::max(ans, now - (n - i + 1 + n - iter + 1) * w);
    }
    for (re int i = n; i >= 1; --i) {
        iter = 0;
        now = sumb[n] - sumb[i - 1];
        for (re int j = n; j >= 1; --j)
            if(suma[n] - suma[j - 1] >= now) {iter = j; break;}
        if(!iter) break;
        ans = std::max(ans, now - (n - i + 1 + n - iter + 1) * w);
    }
    printf("%lld\n", ans);
    return 0;
}