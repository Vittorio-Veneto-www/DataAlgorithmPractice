#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <algorithm>

int n, a[1025][1025], num[1025][1025];

int lowbit(int x)
{
    if (!x)
        return 0;
    int cnt = 0;
    while (!(x & 1))
    {
        x >>= 1;
        cnt++;
    }
    return 1 << cnt;
}

int query(int x, int y)
{
    int sum = 0;
    while (x)
    {
        int cur = y;
        while (cur)
        {
            sum += a[x][cur];
            cur -= lowbit(cur);
        }
        x -= lowbit(x);
    }
    return sum;
}

void update(int x, int y, int dx)
{
    if (num[x][y] + dx < 0)
        dx = -num[x][y];
    num[x][y] += dx;
    while (x <= n)
    {
        int cur = y;
        while (cur <= n)
        {
            a[x][cur] += dx;
            cur += lowbit(cur);
        }
        x += lowbit(x);
    }
}

int main(void)
{
    scanf("%*d%d", &n);
    memset(a, 0, sizeof(a));
    memset(num, 0, sizeof(num));
    int type;
    scanf("%d", &type);
    while (type != 3)
    {
        if (type == 1)
        {
            int x, y, a;
            scanf("%d%d%d", &x, &y, &a);
            x++, y++;
            update(x, y, a);
        }
        else
        {
            int l, b, r, t;
            scanf("%d%d%d%d", &l, &b, &r, &t);
            r++, t++;
            printf("%d\n", query(r, t) - query(r, b) - query(l, t) + query(l, b));
        }
        scanf("%d", &type);
    }
}