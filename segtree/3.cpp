#include <cstdio>
#include <algorithm>

#define lson l, mid, rt << 1
#define rson mid + 1, r, rt << 1 | 1

const int maxN = 8000;
int tree[maxN << 2];

void build(int l, int r, int rt)
{
    tree[rt] = r - l + 1;
    if (l == r)
        return;
    int mid = (l + r) >> 1;
    build(lson);
    build(rson);
}

int query(int x, int l, int r, int rt)
{
    tree[rt]--;
    if (l == r)
        return l;
    int mid = (l + r) >> 1;
    long long ret = 0;
    if (x <= tree[rt << 1])
        return query(x, lson);
    else
        return query(x - tree[rt << 1], rson);
}

int main()
{
    int n, a[8000], b[8000];
    scanf("%d", &n);
    for (int i = 1; i < n; i++)
        scanf("%d", &a[i]);
    a[0] = 0;
    build(1, n, 1);
    for (int i = n - 1; i != -1; i--)
        b[i] = query(a[i] + 1, 1, n, 1);
    for (int i = 0; i < n; i++)
        printf("%d\n", b[i]);
}