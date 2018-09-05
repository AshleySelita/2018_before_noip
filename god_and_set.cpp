#include <cstdio>
typedef long long ll;
const int MAXN = 10000010;
int T, p, tot;
int prime[MAXN], phi[MAXN];
bool istprime[MAXN];
inline void init() {
    istprime[1] = true; phi[1] = 1;
    for (int i = 2; i <= MAXN; ++i) {
        if(!istprime[i]) prime[++tot] = i, phi[i] = i - 1;
        for (int j = 1; j <= tot && i * prime[j] <= MAXN; ++j)
            if(!(i % prime[j])) {
                phi[i * prime[j]] = phi[i] * prime[j]; 
                istprime[i * prime[j]] = true;
                break;
            }
            else {
                phi[i * prime[j]] = phi[i] * (prime[j] - 1);
                istprime[i * prime[j]] = true;
            }
    }
}
inline int Qpow(int a, int b, int mod) {
    ll x = 1, base = a;
    while(b) {
        (b & 1) ? x = (x * base) % mod : false;
        base = (base * base) % mod;
        b /= 2;
    }
    return int(x % mod);
}
inline int exphi(int mod){
    if(mod == 1) return 0;
    return Qpow(2, exphi(phi[mod]) + phi[mod], mod);
}
int main() {
    init();
    scanf("%d", &T);
    for (int i = 1; i <= T; ++i) {
        scanf("%d", &p);
        printf("%d\n", exphi(p));
    }
    return 0;
}