#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <algorithm>

int n, a[32002], cnt[32001];

int lowbit(int x)
{
    return x & -x;
}

int query(int x)
{
    int ans = 0;
    while (x)
    {
        ans += a[x];
        x -= lowbit(x);
    }
    return ans;
}

void update(int x, int dx)
{
    while (x <= n)
    {
        a[x] += dx;
        x += lowbit(x);
    }
}

int main(void)
{
    n = 32001;
    int m;
    scanf("%d", &m);
    memset(a, 0, sizeof(a));
    for (int i = 0; i < m; i++)
    {
        int x;
        scanf("%d%*d", &x);
        x++;
        cnt[query(x)]++;
        update(x, 1);
    }
    for (int i = 0; i < m; i++)
        printf("%d\n", cnt[i]);
}