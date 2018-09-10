#include <cctype>
#include <cstdio>
typedef long long ll;
const int MAXN = 300010;
const int MAXM = 300010;
const int MAXK = 51;
const int N = 10000;
const int MOD = 998244353;
namespace USING_VAR{
    struct EDGE{
        int to, next;
    }edge[MAXN << 1];
    int n, m, u, v, k, top, tot;
    int head[MAXN], dep[MAXN], dfn[MAXN], ltop[MAXN],
        fa[MAXN], son[MAXN], size[MAXN];
    ll talike[MAXK][MAXN];
    char buf[N], *p = buf, *end = buf;
}using namespace USING_VAR;
namespace PRE_FUNCTION{
    inline int lowbit(int x) {return ((-x) & x);}
    inline ll fs_pow(int a, int b) {
        ll ans(1), base(a);
        while(b) {
            if(b & 1) ans = (ans * base) % MOD;
            base = (base * base) % MOD;
            b >>= 1;
        }
        return (ans % MOD);
    }
    inline void swap(int &a, int &b) {a ^= b ^= a ^= b;}
    inline char Get_char() {
        if(p == end) {
            if(feof(stdin)) return (0);
            p = buf; end = buf + fread(buf, 1, N, stdin);
        }
        return *(p++);
    }
    inline void Get_int(int &x) {
        x = 0; char c(0);
        while(!isdigit(c = Get_char()));
        do {x = (x << 1) + (x << 3) + (c ^ 48);}
        while(isdigit(c = Get_char()));
        return ;
    }
    inline void add_edge(int u, int v) {
        edge[++top].to = u;
        edge[top].next = head[v];
        head[v] = top;

        edge[++top].to = v;
        edge[top].next = head[u];
        head[u] = top;
    }
}using namespace PRE_FUNCTION;
/*namespace TALIKE{
    inline void update(ll val, int pos, int k) {
        ll* Ray = talike[k];
        while(pos <= n) {
            Ray[pos] = (Ray[pos] + val) % MOD;
            pos += lowbit(pos);
        }
        return ;
    }
    inline ll query(int pos, int k) {
        if(!pos) return 0;
        ll* Ray = talike[k]; ll ans(0);
        while(pos) {
            ans = (ans + Ray[pos]) % MOD;
            pos -= lowbit(pos);
        }
        return (ans % MOD);
    }
}using namespace TALIKE;*/
namespace DFS{
    inline void dfs1(int now) {
        size[now] = 1; int tmp(0);
        for (int i = head[now]; i; i = edge[i].next)
            if((tmp = edge[i].to) != fa[now]) {
                fa[tmp] = now; dep[tmp] = dep[now] + 1;
                dfs1(tmp); size[now] += size[tmp];
                if(size[tmp] > size[son[now]]) son[now] = tmp;
            }
        return ;
    }
    inline void dfs2(int now, int top) {
        dfn[now] = ++tot; ltop[now] = top;
        for (int i = 1; i <= 50; ++i)
            talike[i][tot] = talike[i][tot - 1] + fs_pow(dep[now], i);
            /*update(fs_pow(dep[now], i), dfn[now], i);*/
        if(!son[now]) {return ;}
        dfs2(son[now], top); int tmp(0);
        for (int i = head[now]; i; i = edge[i].next)
            if((tmp = edge[i].to) != fa[now] && tmp != son[now])
                dfs2(tmp, tmp);
        return ;
    }
}using namespace DFS;
namespace TREECUT{
    inline void sp_qry() {
        Get_int(u), Get_int(v), Get_int(k);
        ll* Ray = talike[k];
        ll ans(0);
        while(ltop[u] != ltop[v]) {
            if(dep[ltop[u]] < dep[ltop[v]]) swap(u, v);
            ans = (ans + Ray[dfn[u]] - Ray[dfn[ltop[u]] - 1]) % MOD;
            u = fa[ltop[u]];
        }
        if(dep[u] > dep[v]) swap(u, v);
        ans = (ans + Ray[dfn[v]] - Ray[dfn[u] - 1]) % MOD;
        printf("%lld\n", ans);
        return ;
    }
}using namespace TREECUT;
int main() {
    //freopen("calc.in", "r", stdin);
    Get_int(n);
    for (int i = 1; i < n; ++i)
        Get_int(u), Get_int(v), add_edge(u, v);
    dfs1(1); dfs2(1, 1);
    Get_int(m);
    for (int i = 1; i <= m; ++i) sp_qry();
    return 0;
}