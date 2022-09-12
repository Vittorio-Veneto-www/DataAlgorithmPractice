#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <algorithm>
#include <cmath>

#define maxN 200000
#define lson l, mid, rt << 1
#define rson mid + 1, r, rt << 1 | 1

long long tree[maxN << 2][2], lazy[maxN << 2];

inline void pushup(int rt)
{
    tree[rt][0] = std::max(tree[rt << 1][0], tree[rt << 1 | 1][0]);
    tree[rt][1] = tree[rt << 1][1] + tree[rt << 1 | 1][1];
}

inline void pushdown(int l, int r, int rt)
{
    if (lazy[rt] != -1)
    {
        int mid = (l + r) >> 1;
        tree[rt << 1][0] = lazy[rt];
        tree[rt << 1][1] = lazy[rt] * (mid - l + 1);
        tree[rt << 1 | 1][0] = lazy[rt];
        tree[rt << 1 | 1][1] = lazy[rt] * (r - mid);
        lazy[rt << 1] = lazy[rt << 1 | 1] = lazy[rt];
        lazy[rt] = -1;
    }
}

void build(int l, int r, int rt)
{
    if (l == r)
    {
        scanf("%lld", &tree[rt][0]);
        tree[rt][1] = tree[rt][0];
        return;
    }
    int mid = (l + r) >> 1;
    build(lson);
    build(rson);
    pushup(rt);
}

void update(long long x, int L, int R, int l, int r, int rt)
{
    if (L <= l && r <= R)
    {
        lazy[rt] = x;
        tree[rt][0] = x;
        tree[rt][1] = x * (r - l + 1);
        return;
    }
    pushdown(l, r, rt);
    int mid = (l + r) >> 1;
    if (mid >= L)
        update(x, L, R, lson);
    if (mid < R)
        update(x, L, R, rson);
    pushup(rt);
}

long long query1(int L, int R, int l, int r, int rt)
{
    if (L <= l && r <= R)
        return tree[rt][0];
    if (R < l || r < L)
        return 0;
    pushdown(l, r, rt);
    int mid = (l + r) >> 1;
    long long ans = 0;
    if (mid >= L)
        ans = std::max(ans, query1(L, R, lson));
    if (mid < R)
        ans = std::max(ans, query1(L, R, rson));
    return ans;
}

long long query2(int L, int R, int l, int r, int rt)
{
    if (L <= l && r <= R)
        return tree[rt][1];
    if (R < l || r < L)
        return 0;
    pushdown(l, r, rt);
    int mid = (l + r) >> 1;
    long long ans = 0;
    if (mid >= L)
        ans += query2(L, R, lson);
    if (mid < R)
        ans += query2(L, R, rson);
    return ans;
}

int main(void)
{
    int n, m;
    scanf("%d%d", &n, &m);
    memset(lazy, -1, sizeof(lazy));
    build(1, n, 1);
    int x, y, z;
    while (m--)
    {
        scanf("%d", &x);
        if (x == 1)
        {
            scanf("%d%d%d", &x, &y, &z);
            update(z, x, y, 1, n, 1);
        }
        else if (x == 2)
        {
            scanf("%d%d", &x, &y);
            printf("%lld\n", query1(x, y, 1, n, 1));
        }
        else
        {
            scanf("%d%d", &x, &y);
            printf("%lld\n", query2(x, y, 1, n, 1));
        }
    }
}