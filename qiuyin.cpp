#include <algorithm>
#include <cstdio>
#include <cmath>
const int MAXN = 100010;
const int MAXM = 7000010;
int n, m, q, u, v, t;
double p;
int h(1), tl, h1(1), t1(0), h2(1), t2(0), tail(0);
int a[MAXN], que1[MAXM], que2[MAXM];
int fin[(MAXM << 1) + MAXN];
inline bool cmp(int a, int b) {return a > b;}
inline int find() {
    int x(0);
    if(h > tl) {
        if(que1[h1] > que2[h2]) {x = que1[h1++];}
        else {x = que2[h2++];}
    }
    else if(que1[h1] > que2[h2]) {
        if(a[h] > que1[h1]) {x = a[h++];}
        else {x = que1[h1++];}
    }
    else {
        if(a[h] > que2[h2]) {x = a[h++];}
        else {x = que2[h2++];}
    }
    return x;
}
int main() {
    scanf("%d%d%d%d%d%d", &n, &m, &q, &u, &v, &t);
    tl = n; p = double(u) / v;
    for (int i = 1; i <= n; ++i)
        scanf("%d", &a[i]);
    int sum(0), tmp(0);
    std::sort(a + 1, a + n + 1, cmp);
    for (int i = 1; i <= m; ++i) {
        tmp = find() + sum;
        int a1 = floor(p * double(tmp)), a2 = tmp - a1;
        sum += q; a1 -= sum; a2 -= sum;
        que1[++t1] = a1; que2[++t2] = a2;
        !(i % t) ? printf("%d ", tmp) : false;
    }
    putchar('\n');
    for (int i = h; i <= tl; ++i) fin[++tail] = a[i];
    for (int i = h1; i <= t1; ++i) fin[++tail] = que1[i];
    for (int i = h2; i <= t2; ++i) fin[++tail] = que2[i];
    std::sort(fin + 1, fin + tail + 1, cmp);
    for (int i = 1; i <= tail; ++i)
        !(i % t) ? printf("%d ", fin[i] + sum) : false;
    putchar('\n');
    return 0;
}