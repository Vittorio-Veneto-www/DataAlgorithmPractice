#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <algorithm>
#include <cmath>

unsigned a[50][2];
double f[50][50][2];

double dis(int x, int y)
{
    return sqrt((a[x][0] - a[y][0]) * (a[x][0] - a[y][0]) + (a[x][1] - a[y][1]) * (a[x][1] - a[y][1]));
}

int main(void)
{
    int n;
    while (scanf("%d", &n) != EOF)
    {
        for (int i = 0; i < n; i++)
            scanf("%u%u", &a[i][0], &a[i][1]);
        for (int i = 0; i < n; i++)
            for (int j = 0; j < n; j++)
                f[i][j][0] = 1e50, f[i][j][1] = 1e50;
        f[0][0][0] = 0;
        f[0][0][1] = 0;
        for (int i = 1; i < n; i++)
            for (int j = 0; j < i; j++)
            {
                f[i][j][0] = std::min(f[i][j][0], f[i - 1][j][0] + dis(i - 1, i));
                f[i][i - 1][0] = std::min(f[i][i - 1][0], f[i - 1][j][1] + dis(j, i));
                f[i][j][1] = std::min(f[i][j][1], f[i - 1][j][1] + dis(i - 1, i));
                f[i][i - 1][1] = std::min(f[i][i - 1][1], f[i - 1][j][0] + dis(j, i));
            }
        double ans = 1e50;
        for (int i = 0; i < n; i++)
        {
            ans = std::min(ans, f[n - 1][i][0] + dis(i, n - 1));
            ans = std::min(ans, f[n - 1][i][1] + dis(i, n - 1));
        }
        printf("%.2lf\n", ans);
    }
}