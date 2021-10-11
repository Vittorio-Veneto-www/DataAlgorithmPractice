#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <algorithm>

int n, a[300001], num[300001], d[300001];

int lowbit(int x)
{
    return x & -x;
}

int query(int x)
{
    int ans = 0;
    while (x)
    {
        ans = std::max(ans, a[x]);
        x -= lowbit(x);
    }
    return ans;
}

void update(int x, int dx)
{
    while (x <= n)
    {
        a[x] = std::max(a[x], dx);
        x += lowbit(x);
    }
}

int main(void)
{
    scanf("%d", &n);
    for (int i = 0; i < n; i++)
        scanf("%d", num + i);
    memcpy(d, num, sizeof(num));
    std::sort(d, d + n);
    int size = std::unique(d, d + n) - d;
    int ans = 0;
    memset(a, 0, sizeof(a));
    for (int i = 0; i < n; i++)
    {
        int x = std::lower_bound(d, d + size, num[i]) - d + 1;
        int y = query(x - 1) + 1;
        ans = std::max(ans, y);
        update(x, y);
    }
    printf("%d\n", ans);
}