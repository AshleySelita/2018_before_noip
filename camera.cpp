#include <cstdio>
const int MAXN = 110;
int n, num, x;
int a[MAXN][MAXN], pos[510], inner[510], rpos[110];
bool ppp[MAXN];
struct QUEUE {
    int head, tail, a[MAXN];
    bool push(int x) {a[++tail] = x; return true;}
    int pop() {return (a[++head]);}
    bool empty() {return (head == tail);}
    void clear() {head = tail = 0;}
}que;
int main() {
    scanf("%d", &n);
    for (int i = 1; i <= n; ++i) {
        scanf("%d%d", &x, &a[i][0]);
        pos[x] = i; rpos[i] = x;
        for (int j = 1; j <= a[i][0]; ++j)
            scanf("%d", &a[i][j]), inner[a[i][j]]++;
    }
    for (int i = 1; i <= n; ++i)
        (!inner[rpos[i]]) ? que.push(i), ppp[i] = true : false;
    while(!que.empty()) {
        int tmp = que.pop(); int aaa(0);
        for (int i = 1; i <= a[tmp][0]; ++i){
            inner[(aaa = a[tmp][i])]--;
            ((!inner[aaa]) && (!ppp[pos[aaa]])) ? que.push(pos[aaa]), ppp[pos[aaa]] = true : false;
        }
    }
    for (int i = 1; i <= n; ++i)
        !ppp[i] ? num++ : false;
    num ? printf("%d\n", num) : printf("YES\n");
    return 0;
}