#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <algorithm>

int n, cnt, node[100001], edge[200000], next[200000], series[100001], range[100001][2], a[100001], mark[100001];

void dfs(int x)
{
    mark[x] = 1;
    int location = ++cnt;
    series[location] = x;
    range[x][0] = location;
    int val = node[x];
    while (val != -1)
    {
        if (!mark[edge[val]])
            dfs(edge[val]);
        val = next[val];
    }
    range[x][1] = cnt;
}

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

int query(int x)
{
    int sum = 0;
    while (x)
    {
        sum += a[x];
        x -= lowbit(x);
    }
    return sum;
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
    int m;
    scanf("%d", &n);
    memset(node, -1, sizeof(node));
    for (int i = 0; i < n - 1; i++)
    {
        int x, y;
        scanf("%d%d", &x, &y);
        edge[i * 2] = y;
        next[i * 2] = node[x];
        node[x] = i * 2;
        edge[i * 2 + 1] = x;
        next[i * 2 + 1] = node[y];
        node[y] = i * 2 + 1;
    }
    cnt = -1;
    memset(mark, 0, sizeof(mark));
    dfs(1);
    for (int i = 1; i <= n; i++)
        a[i] = 1;
    for (int i = 1; i <= n; i++)
    {
        int j = i + (i & -i);
        if (j <= n)
            a[j] = a[j] + a[i];
    }
    scanf("%d", &m);
    memset(mark, 0, sizeof(mark));
    for (;m; m--)
    {
        char c;
        int x;
        scanf("%*c%c%d", &c, &x);
        if (c == 'Q')
            printf("%d\n", query(range[x][1] + 1) - query(range[x][0]));
        else
            if (mark[x])
            {
                update(range[x][0] + 1, 1);
                mark[x] = 0;
            }
            else
            {
                update(range[x][0] + 1, -1);
                mark[x] = 1;
            }
    }
}