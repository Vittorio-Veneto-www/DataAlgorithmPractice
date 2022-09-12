#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <algorithm>
#include <cmath>

int fa[100000], a[100000];

int getfa(int x)
{
    if (x != fa[x])
        fa[x] = getfa(fa[x]);
    return fa[x];
}

void uni(int x, int y)
{
    int fax = getfa(x), fay = getfa(y);
    fa[fax] = fay;
}

int main(void)
{
    int n, m;
    scanf("%d%d", &n, &m);
    for (int i = 0; i < n; i++)
        fa[i] = i;
    int x, y;
    while (m--)
    {
        scanf("%d%d", &x, &y);
        x--, y--;
        uni(x, y);
    }
    memset(a, 0, sizeof(a));
    for (int i = 0 ; i < n; i++)
        a[getfa(i)] = 1;
    int sum = 0;
    for (int i = 0 ; i < n; i++)
        sum += a[i];
    printf("%d\n", sum);
}