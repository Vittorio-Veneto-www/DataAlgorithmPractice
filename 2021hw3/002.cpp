#include <cstdio>
#include <algorithm>
#include <map>

#define lson l, mid, rt << 1
#define rson mid + 1, r, rt << 1 | 1

const int maxN = 40000;
int tree[maxN << 2];

inline void pushup(int rt)
{
    tree[rt] = tree[rt << 1] & tree[rt << 1 | 1];
}

void build(int l, int r, int rt)
{
    tree[rt] = 0;
    if (l == r)
        return;
    int mid = (l + r) >> 1;
    build(lson);
    build(rson);
    pushup(rt);
}

void update(int L, int R, int l, int r, int rt)
{
    if (tree[rt])
        return;
    if (L <= l && r <= R)
    {
        tree[rt] = 1;
        return;
    }
    int mid = (l + r) >> 1;
    if (L <= mid)
        update(L, R, lson);
    if (mid < R)
        update(L, R, rson);
    pushup(rt);
}

int query(int L, int R, int l, int r, int rt)
{
    if (tree[rt])
        return 1;
    if (L <= l && r <= R)
        return tree[rt];
    int mid = (l + r) >> 1;
    int ret = 1;
    if (L <= mid)
        ret &= query(L, R, lson);
    if (mid < R)
        ret &= query(L, R, rson);
    return ret;
}

std::map<int, int> map;

int main()
{
    int T, a[10000][2], b[20000];
    scanf("%d", &T);
    while (T--)
    {
        int n;
        scanf("%d", &n);
        for (int i = 0; i < n; i++)
            scanf("%d%d", &a[i][0], &a[i][1]), b[i << 1] = a[i][0], b[i << 1 | 1] = a[i][1];
        std::sort(b, b + (n << 1));
        map.clear();
        int ord = 1;
        map.insert(std::make_pair(b[0], ord));
        for (int i = 1; i < n << 1; i++)
            if (b[i] != b[i - 1])
                if (b[i] == b[i - 1] + 1)
                {
                    ord++;
                    map.insert(std::make_pair(b[i], ord));
                }
                else
                {
                    ord += 2;
                    map.insert(std::make_pair(b[i], ord));
                }
        for (int i = 0; i < n; i++)
            a[i][0] = map[a[i][0]], a[i][1] = map[a[i][1]];
        build(1, ord, 1);
        int cnt = 0;
        for (int i = n - 1; i >= 0; i--)
        {
            if (!query(a[i][0], a[i][1], 1, ord, 1))
                cnt++;
            update(a[i][0], a[i][1], 1, ord, 1);
        }
        printf("%d\n", cnt);
    }
    return 0;
}