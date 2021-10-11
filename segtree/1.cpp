#include <cstdio>
#include <algorithm>

#define lson l, mid, rt << 1
#define rson mid + 1, r, rt << 1 | 1

const int maxN = 100000;
long long tree[maxN << 2], lazy[maxN << 2];

inline void pushup(int rt)
{
    tree[rt] = tree[rt << 1] + tree[rt << 1 | 1];
}

inline void pushdown(int rt, int m)
{
    if (lazy[rt])
    {
        int ls = rt << 1, rs = rt << 1 | 1;
        lazy[ls] += lazy[rt];
        lazy[rs] += lazy[rt];
        tree[ls] += lazy[rt] * (m - (m >> 1));
        tree[rs] += lazy[rt] * (m >> 1);
        lazy[rt] = 0;
    }
}

void build(int l, int r, int rt)
{
    lazy[rt] = 0;
    if (l == r)
    {
        scanf("%lld", &tree[rt]);
        return;
    }
    int mid = (l + r) >> 1;
    build(lson);
    build(rson);
    pushup(rt);
}

void update(int L, int R, int c, int l, int r, int rt)
{
    if (L <= l && r <= R)
    {
        lazy[rt] += c;
        tree[rt] += (long long)c * (r - l + 1);
        return;
    }
    pushdown(rt, r - l + 1);
    int mid = (l + r) >> 1;
    if (L <= mid)
        update(L, R, c, lson);
    if (mid < R)
        update(L, R, c, rson);
    pushup(rt);
}

long long query(int L, int R, int l, int r, int rt)
{
    if (L <= l && r <= R)
        return tree[rt];
    pushdown(rt, r - l + 1);
    int mid = (l + r) >> 1;
    long long ret = 0;
    if (L <= mid)
        ret += query(L, R, lson);
    if (mid < R)
        ret += query(L, R, rson);
    return ret;
}

int main()
{
    int N, Q;
    scanf("%d%d", &N, &Q);
    build(1, N, 1);
    while (Q--)
    {
        char op[2];
        int a, b, c;
        scanf("%s", op);
        if (op[0] == 'Q')
        {
            scanf("%d%d", &a, &b);
            printf("%lld\n", query(a, b, 1, N, 1));
        }
        else
        {
            scanf("%d%d%d", &a, &b, &c);
            update(a, b, c, 1, N, 1);
        }
    }
    return 0;
}