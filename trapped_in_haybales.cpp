#include <algorithm>
#include <cstdio>
const int MAXN = 100010;
struct HAY{
    int s, p;
}hay[MAXN];
int n, b, l, r, pos, ans(0x7fffffff);
inline bool cmp(HAY a, HAY b) {return (a.p == b.p) ? (a.s < b.s) : (a.p < b.p);}
int main() {
    scanf("%d%d", &n, &b);
    for (int i = 1; i <= n; ++i)
        scanf("%d%d", &hay[i].s, &hay[i].p);
    std::sort(hay + 1, hay + n + 1, cmp);
    for (int i = 1; i <= n; ++i)
        if(hay[i].p > b) {pos = i; break;}
    l = pos - 1; r = pos;
    while(true) {
        if(l < 1 || r > n) break;
        if((hay[r].p - hay[l].p) <= hay[l].s && 
            (hay[r].p - hay[l].p) <= hay[r].s) {
            printf("0\n"); return 0;
        }
        if(hay[r].p - hay[l].p > hay[r].s) {r++; continue;}
        if(hay[r].p - hay[l].p > hay[l].s) {
            ans = std::min(ans, hay[r].p - hay[l].p - hay[l].s); l--;
        }
    }
    l = pos - 1; r = pos;
    while(true) {
        if(l < 1 || r > n) break;
        if((hay[r].p - hay[l].p) <= hay[l].s && 
            (hay[r].p - hay[l].p) <= hay[r].s) {
            printf("0\n"); return 0;
        }
        if(hay[r].p - hay[l].p > hay[l].s) {l--; continue;}
        if(hay[r].p - hay[l].p > hay[r].s) {
            ans = std::min(ans, hay[r].p - hay[l].p - hay[r].s); r++;
        }
    }
    printf("%d\n", ans == (0x7fffffff) ? -1 : ans);
    return 0;
}