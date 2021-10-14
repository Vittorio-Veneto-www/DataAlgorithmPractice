#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <algorithm>

#define lson l, mid, rt << 1
#define rson mid + 1, r, rt << 1 | 1

const int maxN = 10000;
int len[maxN << 2], lp[maxN << 2], rp[maxN << 2], num[maxN << 2], cnt[maxN << 2];
int x[maxN];

class Edge
{
    public:
        int l, r, y, t;
        Edge(){}
        Edge(int l, int r, int y, int t):l(l), r(r), y(y), t(t){}
        int operator<(const Edge &a) const
        {
            return y < a.y;
        }
};

Edge edge[maxN];

inline void pushup(int l, int r, int rt)
{
    if (cnt[rt])
    {
        lp[rt] = 1;
        rp[rt] = 1;
        len[rt] = x[r + 1] - x[l];
        num[rt] = 1;
    }
    else if (l == r)
    {
        len[rt] = 0;
        lp[rt] = 0;
        rp[rt] = 0;
        num[rt] = 0;
    }
    else
    {
        len[rt] = len[rt << 1] + len[rt << 1 | 1];
        lp[rt] = lp[rt << 1];
        rp[rt] = rp[rt << 1 | 1];
        num[rt] = num[rt << 1] + num[rt << 1 | 1] - (rp[rt << 1] & lp[rt << 1 | 1]);
    }
}

void build(int l, int r, int rt)
{
    len[rt] = 0;
    lp[rt] = 0;
    rp[rt] = 0;
    num[rt] = 0;
    cnt[rt] = 0;
    if (l == r)
        return;
    int mid = (l + r) >> 1;
    build(lson);
    build(rson);
}

void update(int L, int R, int c, int l, int r, int rt)
{
    if (L <= l && r <= R)
    {
        cnt[rt] += c;
        pushup(l, r, rt);
        return;
    }
    int mid = (l + r) >> 1;
    if (L <= mid)
        update(L, R, c, lson);
    if (mid < R)
        update(L, R, c, rson);
    pushup(l, r, rt);
}

int main()
{
    int n;
    scanf("%d", &n);
    int k = 0;
    for (int i = 0; i < n; i++)
    {
        int x1, y1, x2, y2;
        scanf("%d%d%d%d", &x1, &y1, &x2, &y2);
        edge[i * 2] = Edge(x1, x2, y1, 1);
        x[i * 2] = x1;
        edge[i * 2 + 1] = Edge(x1, x2, y2, -1);
        x[i * 2 + 1] = x2;
    }
    std::sort(x, x + n * 2);
    std::sort(edge, edge + n * 2);
    int size = std::unique(x, x + n * 2) - x;
    build(0, size, 1);
    int ans = 0, res = 0;
    for (int i = 0; i < n * 2; i++)
    {
        int l = std::lower_bound(x, x + size, edge[i].l) - x;
        int r = std::lower_bound(x, x + size, edge[i].r) - x - 1;
        update(l, r, edge[i].t, 0, size, 1);
        ans += abs(len[1] - res);
        res = len[1];
        if (i != n * 2 - 1)
            ans += (edge[i + 1].y - edge[i].y) * num[1] * 2;
    }
    printf("%d", ans);
}