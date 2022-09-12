#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <algorithm>
#include <cmath>

#define maxN 200000
#define lson l, mid, rt << 1
#define rson mid + 1, r, rt << 1 | 1

long long tree[maxN << 2];

inline void pushup(int rt)
{
    tree[rt] = tree[rt << 1] + tree[rt << 1 | 1];
}

void build(int l, int r, int rt)
{
    if (l == r)
    {
        scanf("%d", &tree[rt]);
        return;
    }
    int mid = (l + r) >> 1;
    build(lson);
    build(rson);
    pushup(rt);
}

void update(int x, int y, int l, int r, int rt)
{
    if (l == r)
    {
        tree[rt] += y;
        return;
    }
    int mid = (l + r) >> 1;
    if (x <= mid)
        update(x, y, lson);
    else
        update(x, y, rson);
    pushup(rt);
}

long long query(int L, int R, int l, int r, int rt)
{
    if (L <= l && r <= R)
        return tree[rt];
    if (R < l || r < L)
        return 0;
    int mid = (l + r) >> 1;
    long long ans = 0;
    if (mid >= L)
        ans += query(L, R, lson);
    if (mid < R)
        ans += query(L, R, rson);
    return ans;
}

int main(void)
{
    int n, m;
    scanf("%d%d", &n, &m);
    build(1, n, 1);
    int x, y, z;
    while (m--)
    {
        scanf("%d%d%d", &x, &y, &z);
        if (x == 1)
            update(y, z, 1, n, 1);
        else
            printf("%lld\n", query(y, z, 1, n, 1));
    }
}