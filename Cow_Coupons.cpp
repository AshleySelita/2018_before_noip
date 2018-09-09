#include <algorithm>
#include <cstdio>
#include <queue>
typedef long long ll;
const int MAXN = 50010;
struct Node{
    int x; int id;
    Node(int a,int b) {x = a, id = b;}
    bool operator < (const Node &a) const{return x > a.x;}
};
int n, k, ans;
int p[MAXN], c[MAXN];
ll m;
bool vis[MAXN];
std::priority_queue<Node> q1, q2;
std::priority_queue<ll, std::vector<ll>, std::greater<ll> > cen;
int main() {
    scanf("%d%d%lld", &n, &k, &m);
    for (int i = 1; i <= n; ++i)
        scanf("%d%d", &p[i], &c[i]),
        q1.push(Node(p[i], i)), q2.push(Node(c[i], i));
    for (int i = 1; i <= k; ++i) cen.push(0);
    int cnt(0);
    while(m > 0 && cnt < n) {
        while(vis[q1.top().id]) q1.pop();
        while(vis[q2.top().id]) q2.pop();
        if(cen.top() + q2.top().x < q1.top().x) {
            Node tmp = q2.top();
            ll tot = cen.top() + tmp.x;
            if(m < tot) break;
            m -= tot; cen.pop(); cen.push(p[tmp.id] - c[tmp.id]);
            vis[tmp.id] = true;
        }
        else {
            Node tmp = q1.top();
            ll tot = tmp.x;
            if(m < tot) break;
            m -= tot; q1.pop();
        }
        cnt++;
    }
    printf("%d\n", cnt);
    return 0;
}