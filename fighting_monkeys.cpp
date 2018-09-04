#include <cstdio>
typedef long long ll;
const int MOD = 9999991;
int n;
ll ans;
inline ll calc(int x){
    ll mul = 1;
    for (int i = 1; i <= x; ++i)
        mul = (mul * i) % MOD;
    return mul;
}
inline ll fast_pow(int a, int b) {
    ll x(1), base(a);
    while(b){
        b % 2 ? x = (x * base) % MOD : false;
        base = (base * base) % MOD;
        b /= 2;
    }
    return x % MOD;
}
int main() {
    scanf("%d", &n);
    ans = calc(n - 1);
    ans *= fast_pow(n, n - 2);
    printf("%lld\n", ans % MOD);
    return 0;
}