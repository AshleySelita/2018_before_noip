#include <cstdio>
const int MAXN = 30010;
int n, m, k, a, b;
bool flag;
int main() {
    scanf("%d%d%d", &k, &m, &n);
    for (int i = 1; i <= m; ++i) {
        scanf("%d%d", &a, &b);
        if(!a && b) {printf("%d ", i); flag = true;}
        else if(!a) {continue;}
        else if(b * (k / a) >= n) printf("%d ", i), flag = true;
    }
    if(!flag) printf("-1\n");
    return 0;
}