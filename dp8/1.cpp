#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <algorithm>

char a[101][10001];

int main(void)
{
    memset(a, 0, sizeof(a));
    a[0][0] = 1;
    for (int i = 1; i <= 100; i++)
        for (int j = 0; j <= 10000; j++)
            for (int k = 1; k <= i; k++)
                if (a[i - k][j - (i - k) * k])
                {
                    a[i][j] = 1;
                    break;
                }
    int n, m, cnt = 0;
    scanf("%d%d", &n, &m);
    while (n)
    {
        printf("Case %d: %d lines ", ++cnt, n);
        if (a[n][m])
            printf("with exactly %d crossings can cut the plane into %d pieces at most.\n", m, n + m + 1);
        else
            printf("cannot make exactly %d crossings.\n", m);
        scanf("%d%d", &n, &m);
    }
}